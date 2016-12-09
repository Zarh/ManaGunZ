#include "pad.h"
#include <sysutil/sysutil.h>
#include <sys/systime.h>

unsigned temp_pad = 0, new_pad = 0, old_pad = 0;

padInfo padinfo;
padData paddata;
int pad_alive=0;

int rumble1_on  = 0;
int rumble2_on  = 0;
int last_rumble = 0;

unsigned ps3pad_read()
{
    int n;

    padActParam actparam;

    unsigned butt = 0;

    pad_alive = 0;

    sysUtilCheckCallback();

    ioPadGetInfo(&padinfo);

    for(n = 0; n < MAX_PADS; n++) {
            
        if(padinfo.status[n])  {
                    
            ioPadGetData(n, &paddata);
            pad_alive = 1;
            butt = (paddata.button[2] << 8) | (paddata.button[3] & 0xff);

            /* Analog stick management */
            // if (paddata.button[6] < 0x10)
                // butt |= BUTTON_LEFT;
            // else if (paddata.button[6] > 0xe0)
                // butt |= BUTTON_RIGHT;
            // if (paddata.button[7] < 0x10)
                // butt |= BUTTON_UP;
            // else if (paddata.button[7] > 0xe0)
                // butt |= BUTTON_DOWN;

          //  if(butt) pad_last_time = sec;

            break;
        
        }
    }

		
    if(!pad_alive) butt = 0;
    else {
        actparam.small_motor = 0;
		actparam.large_motor = 0;
        
        if(rumble1_on) {
            
			actparam.large_motor = 255;
              
            rumble1_on++;
          
            if(rumble1_on > 15) rumble1_on = 0;
          
        }

        if(rumble2_on) {
           
            actparam.small_motor = 1;

            rumble2_on++;

            if(rumble2_on > 10) rumble2_on = 0;
        }

        last_rumble = n;

        ioPadSetActDirect(n, &actparam);
    }

    temp_pad = butt;

    new_pad = temp_pad & (~old_pad); old_pad = temp_pad;


return butt;
}
