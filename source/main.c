#include <sys/file.h>
#include <stdio.h>
#include <string.h>
#include <ppu-lv2.h>
#include <lv2/process.h>
#include <sys/process.h>

int main()
{

#ifdef FILEMANAGER
	sysProcessExitSpawn2("/dev_hdd0/game/FILEMANAG/USRDIR/FileManager.self", NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_1M);
	return 0;
#endif
#ifdef RPCS3
	sysProcessExitSpawn2("/dev_hdd0/game/MANAGUNZ0/USRDIR/ManaGunZ.self", NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_1M);
	return 0;
#endif
 
	FILE* fp;
	char self_path[50];
	char launcher_id[10];

	if((fp = fopen("/dev_hdd0/vsh/pushlist/game.dat", "r"))!=NULL) {
		fgets(launcher_id, 10, fp);
		fclose(fp);
	}
	sprintf(self_path, "/dev_hdd0/game/%s/USRDIR/ManaGunZ.self", launcher_id);
	
	sysProcessExitSpawn2(self_path, NULL, NULL, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_1M);
	
	return 0;

}