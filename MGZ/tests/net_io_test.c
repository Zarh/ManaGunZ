// Host test of MGZ/source/net_io.c against a real ps3netsrv (writes and then
// deletes /PS3ISO/_mgz_nettest on the server). Build and run on a PC:
//   gcc -Wall -DNET_IO_HOST -I MGZ/source -o net_io_test MGZ/tests/net_io_test.c MGZ/source/net_io.c -lpthread
//   ./net_io_test <server ip> 38008
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "net_io.h"
#include <signal.h>
static int fails = 0;
#define CHECK(c, msg) do { if(c) printf("ok   %s\n", msg); else { printf("FAIL %s\n", msg); fails++; } } while(0)
#define D "/net0:/PS3ISO/_mgz_nettest"
static unsigned char A[1536*1024 + 123], C[300000], buf[2*1024*1024];
int main(int argc, char **argv)
{
	signal(SIGPIPE, SIG_IGN); setvbuf(stdout, NULL, _IONBF, 0);
	net_io_set_server(argv[1], atoi(argv[2]));
	for(size_t i=0;i<sizeof(A);i++) A[i]=(unsigned char)(i*7+3);
	for(size_t i=0;i<sizeof(C);i++) C[i]=(unsigned char)(i*13+1);
	struct stat st;
	net_mkdir(D); net_mkdir(D "/sub");
	CHECK(net_stat(D, &st)==0 && S_ISDIR(st.st_mode), "stat dir");
	CHECK(net_stat(D "/missing", &st)!=0, "stat missing");
	// write A in odd chunks
	net_file_t *w = net_fopen(D "/A.bin", "wb");
	CHECK(w!=NULL, "create A");
	size_t off=0, step=70000;
	while(off<sizeof(A)) { size_t n = sizeof(A)-off<step?sizeof(A)-off:step; if(net_fwrite(w, A+off, n)!=(int64_t)n) break; off+=n; }
	CHECK(off==sizeof(A), "write A");
	CHECK(net_fopen(D "/X.bin", "wb")==NULL, "second writer refused while A open");
	CHECK(net_fseek(w, 0, SEEK_SET) < 0, "seek back on write file refused");
	CHECK(net_fclose(w)==0, "close A");
	w = net_fopen(D "/C.bin", "wb"); net_fwrite(w, C, sizeof(C)); CHECK(net_fclose(w)==0, "write+close C");
	CHECK(net_stat(D "/A.bin", &st)==0 && st.st_size==(off_t)sizeof(A), "stat A size");
	// IRD case: read A while writing B (16 KiB chunks)
	net_file_t *r = net_fopen(D "/A.bin", "rb");
	w = net_fopen(D "/B.bin", "wb");
	CHECK(r && w, "open A for read + create B");
	size_t tot=0; int64_t n;
	while((n = net_fread(r, buf, 16384)) > 0) { if(net_fwrite(w, buf, n)!=n) break; tot+=n; }
	CHECK(n==0 && tot==sizeof(A), "copy A->B while both open");
	CHECK(net_fread(r, buf, 100)==0, "read at EOF returns 0");
	net_fclose(r); net_fclose(w);
	// verify B by reading back, interleaved with C (read file switching) + seeks
	net_file_t *rb = net_fopen(D "/B.bin", "rb"), *rc = net_fopen(D "/C.bin", "rb");
	CHECK(rb && rc, "open B and C for read");
	int same=1; size_t pb=0, pc=0;
	while(pb<sizeof(A)) {
		n = net_fread(rb, buf, 50000); if(n<=0 || memcmp(buf, A+pb, n)) { same=0; break; } pb+=n;
		if(pc<sizeof(C)) { n = net_fread(rc, buf, 33333); if(n<=0 || memcmp(buf, C+pc, n)) { same=0; break; } pc+=n; }
	}
	CHECK(same && pb==sizeof(A) && pc==sizeof(C), "interleaved reads of B and C match");
	net_fseek(rb, 1000000, SEEK_SET); n=net_fread(rb, buf, 10);
	CHECK(n==10 && !memcmp(buf, A+1000000, 10), "seek + read");
	CHECK(net_fseek(rb, -5, SEEK_END)==(int64_t)sizeof(A)-5, "seek from end");
	net_fclose(rb); net_fclose(rc);
	// big read crossing the 1 MiB chunking
	r = net_fopen(D "/A.bin", "rb"); n = net_fread(r, buf, sizeof(A));
	CHECK(n==(int64_t)sizeof(A) && !memcmp(buf, A, sizeof(A)), "single big read"); net_fclose(r);
	// directories (nested listing while another is open)
	w = net_fopen(D "/sub/s.txt", "wb"); net_fwrite(w, "x\n", 2); net_fclose(w);
	net_dir_t *d1 = net_opendir(D), *d2 = net_opendir(D "/sub");
	char name[512]; uint8_t isdir; uint64_t sz; int c1=0, c2=0, sawsub=0;
	while(net_readdir(d2, name, sizeof(name), &isdir, &sz)==0) c2++;
	while(net_readdir(d1, name, sizeof(name), &isdir, &sz)==0) { c1++; if(!strcmp(name,"sub") && isdir) sawsub=1; }
	CHECK(c1==4 && sawsub && c2==1, "nested opendir/readdir");
	net_closedir(d1); net_closedir(d2);
	w = net_fopen(D "/W.bin", "wb");
	CHECK(net_fopen(D "/missing", "rb")==NULL, "open missing file fails");
	CHECK(net_fopen(D, "rb")==NULL, "open a directory for reading fails");
	CHECK(net_fwrite(w, "abc", 3)==3 && net_fclose(w)==0 && net_stat(D "/W.bin", &st)==0 && st.st_size==3, "write file survives failed opens");
	net_unlink(D "/W.bin");
	// cleanup via unlink (file + dir)
	CHECK(net_unlink(D "/sub/s.txt")==0 && net_unlink(D "/sub")==0, "unlink file + dir");
	net_unlink(D "/A.bin"); net_unlink(D "/B.bin"); net_unlink(D "/C.bin");
	CHECK(net_unlink(D)==0, "rmdir test dir");
	printf("%s (%d failures)\n", fails ? "FAILED" : "ALL PASSED", fails);
	return fails != 0;
}
