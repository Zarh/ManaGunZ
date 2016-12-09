/*
   This file is part of trpex project.
   Copyright (C) 2010 Red Squirrel.

   trpex is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 3 of the License, or (at your
   option) any later version.

   trpex is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with trpex. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* For MkDir: */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
/* For ntohl */
#include <arpa/inet.h>
#include <sys/file.h>

extern void Delete(char* path);
extern void print_load(char *format, ...);

void trophy_extract(char *trp_path)
{
    FILE *f, *o;
    int c = 64, i = 0, z, fine;
    char s[16], *h, path[128];
	
	char out[255];
	strcpy(out, trp_path);
	strtok(out, ".");
	
	Delete(out);
	if (mkdir(out, 0777) != 0) {
		print_load("Error : failed to create folder");
		return;
	}

    f = fopen(trp_path,"r");
    if (f == NULL)
    {
        print_load("Error: unable to open input file!");
        return;
    }

    if (fseek(f,100,SEEK_SET) < 0)
    {
        print_load("Error: unable to get header size!");
        fclose(f);
        return;
    }
    if (fread(&fine,4,1,f) < 1)
    {
        print_load("Error: unable to get header size!");
        fclose(f);
        return;
    }
    fine = ntohl(fine);

    while (c < fine)
    {
        if (fseek(f,c,SEEK_SET) < 0)
        {
            print_load("Error: unable to get internal filenames!");
            c = fine;
            fclose(f);
            return;
        }
        if (fread(&s,16,1,f) < 1)
        {
            print_load("Error: unable to get internal filenames!");
            c = fine;
            fclose(f);
            return;
        }
        print_load("> %s",s);

        if (fseek(f,20,SEEK_CUR) < 0)
        {
            print_load("Error: unable to get internal file content!");
            c = fine;
            fclose(f);
            return;
        }
        if (fread(&i,4,1,f) < 1)
        {
            print_load("Error: unable to get internal file content!");
            c = fine;
            fclose(f);
            return;
        }
        i = ntohl(i);

        if (fseek(f,4,SEEK_CUR) < 0)
        {
            print_load("Error: unable to get internal file content!");
            c = fine;
            fclose(f);
            return;
        }
        if (fread(&z,4,1,f) < 1)
        {
            print_load("Error: unable to get internal file content!");
            c = fine;
            fclose(f);
            return;
        }
        z = ntohl(z);
        if (fseek(f,i,SEEK_SET) < 0)
        {
            print_load("Error: unable to get internal file content!");
            c = fine;
            fclose(f);
            return;
        }
        h = (char*)malloc(z);
        if (fread(h,z,1,f) < 1)
        {
            print_load("Error: unable to get internal file content!");
            c = fine;
            fclose(f);
            return;
        }

        if (out != NULL) sprintf(path,"%s/%s",out,s);
        else sprintf(path, "%s", s);
        o = fopen(path,"w");
        if (o == NULL)
        {
            print_load("Error: unable to open output file!");
            c = fine;
            fclose(f);
            return;
        }
        else
        {
            if (fwrite(h,z,1,o) < 1)
            {
                print_load("Error: unable to write output file content!");
                fclose(f);
                fclose(o);
                c = fine;
                return;
            }
        }
        fclose(o);
        c += 64;
        free(h);
    }

    fclose(f);
}
