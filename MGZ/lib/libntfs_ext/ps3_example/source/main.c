/* 
    (c) 2012 Estwald <www.elotrolado.net>

    "ps3_example" is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    "ps3_example" is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HMANAGER4.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <io/pad.h>

#include <tiny3d.h>
#include <libfont.h>

// font 0: 224 chr from 32 to 255, 16 x 32 pix 2 bit depth
#include "font.h"
#include "console.h"

#include "ntfs.h"
//#include "ext2.h"

int max_list = 0;

void list(char *path, int depth)
{
    DIR_ITER *pdir;
    struct stat st;
    char indent[PATH_MAX] = {0};
    char new_path[PATH_MAX] = {0};
    char filename[PATH_MAX] = {0};
    

    // Open the directory
    pdir = ps3ntfs_diropen(path);

    if (pdir) {

        // Build a directory indent (for better readability)
        memset(indent, ' ', depth * 2);
        indent[depth * 2] = 0;

        // List the contents of the directory
        while (ps3ntfs_dirnext(pdir, filename, &st) == 0) {
          
            if ((strcmp(filename, ".") == 0) || (strcmp(filename, "..") == 0))
                continue;

            max_list++;
            if(max_list > 10) break;

            
            sprintf(new_path, "%s/%s", path, filename);
            //ps3ntfs_stat(new_path, &st);
            // List the entry
            if (S_ISDIR(st.st_mode)) {
                DPrintf(" D %s%s/\n", indent, filename);

                // List the directories contents
                
                //list(new_path, depth + 1); // recursive list
               
            } else if (S_ISREG(st.st_mode)) {
                DPrintf(" F %s%s (%lu)\n", indent, filename, (unsigned long int)st.st_size);
            } else {
                DPrintf(" ? %s%s\n", indent, filename);
            }

        }

        // Close the directory
        ps3ntfs_dirclose(pdir);

    } else {
        DPrintf("opendir(%s) failure.\n", path);
    }

    return;
}

const DISC_INTERFACE *disc_ntfs[8]= {
    &__io_ntfs_usb000,
    &__io_ntfs_usb001,
    &__io_ntfs_usb002,
    &__io_ntfs_usb003,
    &__io_ntfs_usb004,
    &__io_ntfs_usb005,
    &__io_ntfs_usb006,
    &__io_ntfs_usb007
};

// mounts from /dev_usb000 to 007
ntfs_md *mounts[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
int mountCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int automountCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};


u32 ports_cnt = 0, old_ports_cnt = 0;

// NOTE: NTFS_Event_Mount() must be in the main loop. Automount count is 300 because 300 / 60 fps = 5 seconds
// to wait system operations before to mount the device

int NTFS_Event_Mount(int id) 
{
    int r = 0;

    ports_cnt &= ~(1<<id);
    if(PS3_NTFS_IsInserted(id)) ports_cnt |= 1<<id;

    if( ((ports_cnt>>id) & 1) && !((old_ports_cnt>>id) & 1)) automountCount[id] = 300; // enable delay event

    if(automountCount[id]>0) { // if delay counter ticks...
        automountCount[id]--; if(automountCount[id]==0) r = 1; // mount device
    }

    if( !((ports_cnt>>id) & 1) && ((old_ports_cnt>>id) & 1)) { // unmount device
        automountCount[id]=0; r = -1; 
    }

    old_ports_cnt = ports_cnt;

    return r;
}

int NTFS_UnMount(int id)
{
    int ret = 0;

    if (mounts[id]) {
    int k;
    for (k = 0; k < mountCount[id]; k++)
        if((mounts[id]+k)->name[0]) 
            {ret = 1; ntfsUnmount((mounts[id]+k)->name, true); (mounts[id]+k)->name[0] = 0;}

    free(mounts[id]); 
    mounts[id]= NULL;
    mountCount[id] = 0;
    }
    
    PS3_NTFS_Shutdown(id);

    return ret;
}

void NTFS_UnMountAll(void)
{ 
    int i;

    for(i = 0; i < 8; i++) {
        NTFS_UnMount(i);
    }
}

int NTFS_Test_Device(char *name)
{
    int k, i;

    for(k = 0; k < 8; k++) {
        for (i = 0; i < mountCount[k]; i++)
        if(!strncmp((mounts[k]+i)->name, name, 5 - 1 *( name[0] == 'e'))) 
            return ((mounts[k] + i)->interface->ioType & 0xff) - '0';
    }

    return -1;
    
}

char message[] ="This is a NTFS file test writing";
char buffer[1024];

//#define USE_DEVICE "/ntfs0:"
//#define USE_DEVICE "/ext0:"
//#define USE_DEVICE "/dev_usb000"

s32 main(s32 argc, const char* argv[])
{

    int count = 0;
    int n;
    padInfo padinfo;
	padData paddata;

    char *cur_device = "/ntfs0:";
    char path[1024];

    tiny3d_Init(1024*1024);
    tiny3d_Project2D();

    u32 * texture_mem = tiny3d_AllocTexture(64*1024*1024); // alloc 64MB of space for textures (this pointer can be global)    

    u32 * texture_pointer; // use to asign texture space without changes texture_mem

    if(!texture_mem) return 0; // fail!

    texture_pointer = texture_mem;

    ResetFont();
    texture_pointer = (u32 *) AddFontFromBitmapArray((u8 *) font  , (u8 *) texture_pointer, 32, 255, 16, 32, 2, BIT0_FIRST_PIXEL);

    initConsole();
    ioPadInit(7);


    DbgHeader("NTFS EXT2/3/4 Example");
    
   /*
    // Mount all NTFS volumes on all inserted block devices
    mountCount = ntfsMountAll(&mounts, NTFS_DEFAULT | NTFS_RECOVER);

   // mountCount = ntfsMountDevice (&__io_ntfs_usb000, &mounts, NTFS_DEFAULT | NTFS_RECOVER);
    
    if (mountCount == -1)
        DPrintf("Error whilst mounting devices (%i).\n", errno);
    else if (mountCount == 0)
        DPrintf("No NTFS volumes were found and/or mounted.\n");
    else
        DPrintf("%i NTFS volumes(s) mounted!\n\n", mountCount);
    */


    int i;

    count = 1;
    
    while(1) {
    if(count > 0) {
        count--;
        if(count == 0) {
            int k;
            initConsole();
            
            for(k = 0; k < 8; k++) {
                for (i = 0; i < mountCount[k]; i++)
                DPrintf("%i - %s:/ (%s) (from usb00%i)\n", i + 1, 
                (mounts[k]+i)->name, ntfsGetVolumeName((mounts[k] + i)->name), 
                    ((mounts[k] + i)->interface->ioType & 0xff) - '0');
            }

            
            int r;

            cur_device = NULL;
            r = NTFS_Test_Device("ext0"); DPrintf("\nTest ext0 %i\n" , r);
            if(r>=0 && !cur_device) cur_device = "/ext0:";

            r = NTFS_Test_Device("ext1"); DPrintf("Test ext1 %i\n" , r);
            if(r>=0 && !cur_device) cur_device = "/ext1:";

            r = NTFS_Test_Device("ext2"); DPrintf("Test ext2 %i\n" , r);
            if(r>=0 && !cur_device) cur_device = "/ext2:";

            r = NTFS_Test_Device("ext3"); DPrintf("Test ext3 %i\n" , r);
            if(r>=0 && !cur_device) cur_device = "/ext3:";

            r = NTFS_Test_Device("ntfs0"); DPrintf("Test ntfs0 %i\n" , r);
            if(r>=0 && !cur_device) cur_device = "/ntfs0:";

            r = NTFS_Test_Device("ntfs1"); DPrintf("Test ntfs1 %i\n" , r);
            if(r>=0 && !cur_device) cur_device = "/ntfs1:";

            r = NTFS_Test_Device("ntfs2"); DPrintf("Test ntfs2 %i\n" , r);
            if(r>=0 && !cur_device) cur_device = "/ntfs2:";

            r = NTFS_Test_Device("ntfs3"); DPrintf("Test ntfs3 %i\n" , r);
            if(r>=0 && !cur_device) cur_device = "/ntfs3:";

            if(!cur_device) cur_device = "/ntfs0:"; // by default
            
          

        }
    }

    DbgHeader("NTFS EXT2/3/4 Example");
    DbgMess("Press X to list device, O to test file and /\\ to exit");

    for(i = 0; i < 8 ; i++) {
        int r = NTFS_Event_Mount(i);

        if(r == 1) { // mount device
            
            NTFS_UnMount(i);

            mounts[i] = NULL;
            mountCount[i] = 0;

            mountCount[i] = ntfsMountDevice (disc_ntfs[i], &mounts[i], NTFS_DEFAULT | NTFS_RECOVER);
            
            if(mountCount[i]>0) {count = 1;} // update counter
        } else if(r == -1) { // unmount device
            NTFS_UnMount(i);
            count = 1;
        }
    }

    

  //  DbgMess();


    DbgDraw();
    tiny3d_Flip();
    ioPadGetInfo(&padinfo);

            for(n = 0; n < MAX_PADS; n++) {
                static u32 btn_flags = 0;
            
                if(padinfo.status[n]) {
                    
                    ioPadGetData(n, &paddata);
                   
                    if(paddata.BTN_CROSS) {
                        if((btn_flags & 1)==0){
                            btn_flags|=1;
                            max_list = 0;
                            initConsole();

                            count = 300;

                            DPrintf("Listing 10 entries from %s (5 seconds)\n", cur_device);
                            
                            sprintf(path, "%s", cur_device);

                            list(path, 0);
                           
                        }
        
                    } else btn_flags&=~1;

                    if(paddata.BTN_CIRCLE) {
                        if((btn_flags & 2)==0){
                            btn_flags|=2;
                            
                            DPrintf("\n\nWriting / Reading a file from %s\n", cur_device);
                            
                            sprintf(path, "%s/0text", cur_device);
                            
                            ps3ntfs_mkdir(path, 0777);

                            sprintf(path, "%s/0text/test.txt", cur_device);

                            int fd= ps3ntfs_open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
        
                            if(fd > 0) {

                                int i;
                                
                                i = ps3ntfs_write(fd, message, strlen(message));

                                if(i != strlen(message)) DPrintf("Error writing the file!\n");

                                ps3ntfs_close(fd);


                            } else DPrintf("Error creating the file!\n");

                            memset(buffer, 0, 1024);

                            sprintf(path, "%s/0text/test.txt", cur_device);

                            fd= ps3ntfs_open(path, O_RDONLY, 0);

             
                            if(fd > 0) {

                                int i;

                 // NOTE: for files > 2GB you can use  "s64  ps3ntfs_seek64(int fd, s64 pos, int dir);"
                                
                                int size = ps3ntfs_seek(fd, 0, SEEK_END);

                                DPrintf ("Size of file %i\n", size);

                                ps3ntfs_seek(fd, 0, SEEK_SET);
                                
                                i = ps3ntfs_read(fd, buffer, size);

                                if(i != size) DPrintf("Error reading the file!\n");

                                ps3ntfs_close(fd);


                            } else DPrintf("Error Reading the file!\n");

                            DPrintf("Readed From file: %s\n\n", buffer);
                        }
                            
 
                        
                    } else btn_flags&=~2;



                    if(paddata.BTN_TRIANGLE){
                       
                        goto out;				
        
                    }
                }
            }

    
           
    }

    out:;
    DPrintf("Umounting\n");
    DbgDraw();
    tiny3d_Flip();
 
    NTFS_UnMountAll();

	return 0;
}
