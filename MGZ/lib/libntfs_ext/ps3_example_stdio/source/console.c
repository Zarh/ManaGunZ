#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>


#include <tiny3d.h>
#include <libfont.h>


/*******************************************************************************************************************************************************/
/* CONSOLE DEBUG                                                                                                                                       */
/*******************************************************************************************************************************************************/

#define CONSOLE_WIDTH		(84)
#define CONSOLE_HEIGHT		(27)

static char dbg_str1[128];
static char dbg_str2[128];

static char dbg_data[128 * CONSOLE_HEIGHT];

int con_x = 0, con_y =0;

void cls2()
{
    tiny3d_Clear(0xff000000, TINY3D_CLEAR_ALL);
        
    // Enable alpha Test
    tiny3d_AlphaTest(1, 0x10, TINY3D_ALPHA_FUNC_GEQUAL);

   // Enable alpha blending.
            tiny3d_BlendFunc(1, TINY3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA | TINY3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA,
                TINY3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA | TINY3D_BLEND_FUNC_DST_ALPHA_ZERO,
                TINY3D_BLEND_RGB_FUNC_ADD | TINY3D_BLEND_ALPHA_FUNC_ADD);
}


void initConsole()
{
    con_x = 0; con_y =0;
    dbg_str1[0] = dbg_str2[0] = 0;
    memset(dbg_data, 0, 128 * CONSOLE_HEIGHT);
}

static char buff[4096];

void DbgHeader(char *str)
{
    strncpy(dbg_str1, str, 128);
}

void DbgMess(char *str)
{
    strncpy(dbg_str2, str, 128);
}


void DbgDraw()
{
    int n;

    cls2();

    SetFontColor(0x0fcf2fff, 0x00000000);

    SetFontAutoCenter(0);
    SetCurrentFont(0);
    SetFontSize(10, 16);

    
    for(n = 0; n < CONSOLE_HEIGHT; n++) {
       DrawString(0, 56 + n * 16, &dbg_data[128 * n]);
    }
    
    SetFontColor(0xffffffff, 0x00000000);
    SetCurrentFont(0);

    SetFontSize(14, 32);
    SetFontAutoCenter(1);

    DrawString(0, 16, dbg_str1);

    DrawString(0, 480, dbg_str2);

    SetFontAutoCenter(0);


}

void DPrintf(char *format, ...)
{
    char *str = (char *) buff;
    va_list	opt;
	
	va_start(opt, format);
	vsprintf( (void *) buff, format, opt);
	va_end(opt);

    while(*str) {
        if(*str == '\n') {
            con_y++;
            con_x = 0;
            if(con_y >= CONSOLE_HEIGHT) {
                con_y = CONSOLE_HEIGHT - 1;
                memcpy(dbg_data, dbg_data + 128, 128 * (CONSOLE_HEIGHT -1));
                dbg_data[128 * (CONSOLE_HEIGHT -1)] = 0;
            } else dbg_data[128 * con_y + con_x] = 0;
        } else {
            if(con_x < CONSOLE_WIDTH) {
                dbg_data[128 * con_y + con_x] = *str;
                dbg_data[128 * con_y + con_x + 1] = 0;
                con_x++;
            } else {
            con_y++;
            con_x = 0;
            if(con_y >= CONSOLE_HEIGHT) {
                con_y = CONSOLE_HEIGHT - 1;
                memcpy(dbg_data, dbg_data + 128, 128 * (CONSOLE_HEIGHT -1));
                dbg_data[128 * (CONSOLE_HEIGHT -1)] = 0;
               
            }
            
            dbg_data[128 * con_y + con_x] = *str;
            dbg_data[128 * con_y + con_x + 1] = 0;
            con_x++;
            }
        }

        str++;
    }

    //DbgDraw();
    //tiny3d_Flip();
}