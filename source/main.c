#include <sys/file.h>
#include <stdio.h>
#include <string.h>
#include <ppu-lv2.h>
#include <lv2/process.h>
#include <sys/process.h>


int main()
{
#ifdef _BDVD_BUILD_
	#ifdef FILEMANAGER
		sysProcessExitSpawn2("/dev_bdvd/PS3_GAME/USRDIR/FileManager.self", NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_1M);
		return 0;
	#endif
	sysProcessExitSpawn2("/dev_bdvd/PS3_GAME/USRDIR/ManaGunZ.self", NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_1M);
	return 0;
#endif

#ifdef FILEMANAGER
	sysProcessExitSpawn2("/dev_hdd0/game/FILEMANAG/USRDIR/FileManager.self", NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_1M);
	return 0;
#endif

 
	FILE* fp;
	char self_path[50];
	char launcher_id[10]={0};

	fp = fopen("/dev_hdd0/vsh/pushlist/game.dat", "rb");
	if(fp!=NULL) {	
		fread(launcher_id, 9, 1, fp);
		fclose(fp);
	} else {
// for RPCS3
#ifdef FILEMANAGER
		strcpy(launcher_id, "FILEMANAG");
#else
		strcpy(launcher_id, "MANAGUNZ0");
#endif
	}
	launcher_id[9]=0;
	
	sprintf(self_path, "/dev_hdd0/game/%s/USRDIR/ManaGunZ.self", launcher_id);
	
	sysProcessExitSpawn2(self_path, NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_1M);
	
	return 0;

}