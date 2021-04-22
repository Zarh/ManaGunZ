#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <zlib.h>
#include <malloc.h>

#include "ird_gz.h"

#define CHUNK 16384

#define windowBits 15
#define ENABLE_ZLIB_GZIP 32
#define GZIP_ENCODING 16

char copy_file[128];
char copy_src[128];
char copy_dst[128];

u64 gathering_total_size;
u64 copy_current_size;
u8 copy_cancel;

int GZ_compress(char *source, int sourceLen, char **dest, int *destLen)
{
    z_stream stream;
    int err;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)source;
    stream.avail_in = (uInt)sourceLen;
    stream.next_out = (Bytef *) *dest;
    stream.avail_out = (uInt) *destLen;
    
    err = deflateInit2(&stream, Z_BEST_COMPRESSION, Z_DEFLATED, windowBits | GZIP_ENCODING, 8, Z_DEFAULT_STRATEGY);
    if (err != Z_OK) return err;

    *destLen = deflateBound(&stream, sourceLen);
    *dest = malloc(*destLen);
    if(*dest == NULL) {
        deflateEnd(&stream);
        return Z_BUF_ERROR;
    }
   
    stream.next_out = (Bytef *) *dest;
    stream.avail_out = (uInt) *destLen;

    err = deflate(&stream, Z_FINISH);
    if (err != Z_STREAM_END) {
        deflateEnd(&stream);
        free(*dest);
        *destLen=0;
        return err == Z_OK ? Z_BUF_ERROR : err;
    }
    *destLen = stream.total_out;

    err = deflateEnd(&stream);
    if (err != Z_OK) {
        free(*dest);
        *destLen=0;
    }
    
    return err;
}

int GZ_compress2(FILE *source, int sourceLen, char **dest, int *destLen)
{
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    
    ret = deflateInit2(&strm, Z_BEST_COMPRESSION, Z_DEFLATED, windowBits | GZIP_ENCODING, 8, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK) {
        print_load("Error : deflateInit2");
        return ret;
    }

    *dest=NULL;
    
    gathering_total_size = sourceLen;
    copy_current_size = 0;
    u32 buffsize = CHUNK;
    
    do {
        if( CHUNK < sourceLen - copy_current_size ) {
            flush = Z_NO_FLUSH;
            buffsize = CHUNK;
        } else {
            flush = Z_FINISH;
            buffsize = sourceLen - copy_current_size;
        }
        
        if(copy_cancel) {
           (void)deflateEnd(&strm);
           if(*dest) free(*dest);
           print_load("cancel");
           return Z_ERRNO;
        }
        
        memset(in, 0, CHUNK);
        
        strm.avail_in = fread(in, 1, buffsize, source);
        
        if( strm.avail_in != buffsize ) {
            (void)deflateEnd(&strm);
            if(*dest) free(*dest);
            print_load("Error : fread ret %X != buffsize %X", strm.avail_in, buffsize);
            return Z_ERRNO;
        }
        
        copy_current_size += buffsize;
        
        strm.next_in = in;

        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush);
            assert(ret != Z_STREAM_ERROR);
            have = CHUNK - strm.avail_out;
            
            *dest = realloc(*dest, strm.total_out);
            memcpy(*dest + strm.total_out - have, out, have);
            
            if(copy_cancel) {
                 print_load("cancel");
                (void)inflateEnd(&strm);
                if(*dest) free(*dest);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */
    
    *destLen = strm.total_out;
    
    /* clean up and return */
    (void)deflateEnd(&strm);
    return Z_OK;
}

int GZ_compress3(FILE *source, FILE *dest)
{
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    
    ret = deflateInit2(&strm, Z_BEST_COMPRESSION, Z_DEFLATED, windowBits | GZIP_ENCODING, 8, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK)
        return ret;
    
    copy_current_size=0;
    /* compress until end of file */
    do {
        flush = Z_NO_FLUSH;
        strm.avail_in = fread(in, 1, CHUNK, source);
        if( strm.avail_in != CHUNK ) {
            flush = Z_FINISH;
        }
        
        strm.next_in = in;
        
        copy_current_size += strm.avail_in;
        
        if(copy_cancel) {
            (void)deflateEnd(&strm);
            return Z_ERRNO;
        }
        
        /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush);    /* no bad return value */
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have) {
                (void)deflateEnd(&strm);
                return Z_ERRNO;
            }
            if(copy_cancel) {
                (void)deflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */
    
    /* clean up and return */
    (void)deflateEnd(&strm);
    return Z_OK;
}

int GZ_compress5(char *source, char *dest)
{
    int ret=Z_ERRNO;
	
	FILE *in=NULL;
	FILE *out=NULL;
	
	in= fopen(source, "rb");
	if( in==NULL ) {
		printf("Error : failed to open file_in");
		goto error;
	}
	out= fopen(dest, "wb");
	if( out==NULL ) {
		printf("Error : failed to open file_out");
		goto error;
	}
	
	if( GZ_compress3(in, out) != Z_OK ) goto error;
	
	ret=Z_OK;
error:
	FCLOSE(in);
	FCLOSE(out);
	
	return ret;
}

int GZ_decompress(char *source, int sourceLen, char **dest, int *destLen)
{
    
//https://stackoverflow.com/questions/9715046/find-the-size-of-the-file-inside-a-gzip-file/9727599#9727599    
    memcpy(destLen, source+sourceLen-4, 4);
    *dest = (char *) malloc(*destLen);
    if(*dest==NULL) return Z_BUF_ERROR;
    
   int err;
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)source;
    stream.avail_in = (uInt)sourceLen;
    stream.next_out = (Bytef *) *dest;
    stream.avail_out = (uInt) *destLen;
    
    err = inflateInit2(&stream, windowBits | ENABLE_ZLIB_GZIP);
    if (err != Z_OK) {
        free(*dest);
        *destLen=0;
        return err;
    }
    
    err = inflate(&stream, Z_FINISH);
    if (err != Z_STREAM_END) {
        inflateEnd(&stream);
        free(*dest);
        *destLen=0;
        return err == Z_OK ? Z_BUF_ERROR : err;
    }
    
    err = inflateEnd(&stream);
    if( err != Z_OK ) {
        free(*dest);
        *destLen=0;
        return err;
    }
    
    return err;
}

int GZ_decompress3(FILE *source, FILE *dest)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    
    ret = inflateInit2(&strm, windowBits | ENABLE_ZLIB_GZIP);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;
        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            //case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int GZ_decompress4(char *source, int sourceLen, FILE *dest)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    
    ret = inflateInit2(&strm, windowBits | ENABLE_ZLIB_GZIP);
    if (ret != Z_OK) return ret;
    
    gathering_total_size = sourceLen;
    copy_current_size = 0;
    u32 buffsize = CHUNK;
    
    do {
        
        if( CHUNK < sourceLen - copy_current_size ) {
            buffsize = CHUNK;
        } else {
            buffsize = sourceLen - copy_current_size;
        }
        
        memcpy(in, source + copy_current_size, buffsize);
        strm.avail_in = buffsize;

        copy_current_size += buffsize;

        if(copy_cancel) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        
        strm.next_in = in;
        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            //case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            if(copy_cancel) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);
    
    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int GZ_decompress5(char *source, char *dest)
{
    int ret=Z_ERRNO;
	
	FILE *in=NULL;
	FILE *out=NULL;
	
	in= fopen(source, "rb");
	if( in==NULL ) {
		printf("Error : failed to open file_in");
		goto error;
	}
	out= fopen(dest, "wb");
	if( out==NULL ) {
		printf("Error : failed to open file_out");
		goto error;
	}
	
	if( GZ_decompress3(in, out) != Z_OK ) goto error;
	
	ret=Z_OK;
error:
	FCLOSE(in);
	FCLOSE(out);
	
	return ret;
}

int GZ_decompress6(FILE *source, int sourceLen, char **dest, int destLen)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    
    ret = inflateInit2(&strm, windowBits | ENABLE_ZLIB_GZIP);
    if (ret != Z_OK) return ret;
    
    *dest=NULL;
    u32 current_size = 0;
    u32 buffsize = CHUNK;
    do {
        if( CHUNK < sourceLen - current_size ) {
            buffsize = CHUNK;
        } else {
            buffsize = sourceLen - current_size;
        }
        strm.avail_in = fread(in, 1, buffsize, source);
        if( strm.avail_in != buffsize ) {
            (void)deflateEnd(&strm);
            if(*dest) free(*dest);
            return Z_ERRNO;
        }
        current_size += buffsize;
        strm.next_in = in;
        
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);
            if(ret != Z_OK && ret != Z_STREAM_END) {
                (void)inflateEnd(&strm);
                if(*dest) free(*dest);
                return ret;
            }
            
            have = CHUNK - strm.avail_out;
            *dest = realloc(*dest, strm.total_out);
            memcpy(*dest + strm.total_out - have, out, have);
            
            if( destLen <= strm.total_out) break;
        } while (strm.avail_out == 0);
        if( destLen <= strm.total_out) break;
    } while (ret != Z_STREAM_END);
    
    if(ret == Z_STREAM_END) ret=Z_OK;
    
    (void)inflateEnd(&strm);
    return ret;
}

int GZ_decompress7(char *source, int sourceLen, char *dest)
{
    FILE *f=NULL;
    f = fopen(dest, "wb");
    if(f == NULL) return Z_ERRNO;
    
    int ret = GZ_decompress4(source, sourceLen, f);
    
    fclose(f);
    
    return ret;
}

int GZ_decompress8(char *source, char **dest, int destLen)
{
    FILE *f;
    
    f = fopen(source, "rb");
    if(f==NULL) return Z_ERRNO;
    
    fseek (f , 0 , SEEK_END);
	int file_size = ftell (f);
	fseek(f, 0, SEEK_SET);
    
    
    int ret = GZ_decompress6(f, file_size, dest, destLen);
    
    fclose(f);
    
    return ret;
}
