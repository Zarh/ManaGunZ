/*
 * main.c - This file is part of RCOMage
 *
 * Copyright (C) ZiNgA BuRgA <zingaburga@hotmail.com>
 *
 * This software is distributed under the terms of the GNU Lesser General Public
 * License ("LGPL") version 2.1, as published by the Free Software Foundation.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/file.h>
#include <sys/stat.h>

#include "strfuncs.h"
#include "general.h"
#include "rcomain.h"
#include "xml.h"
#include "rcodump.h"
#include "vaghandler.h"
#include "vsmx.h"
#include "configscan.h"

#define FAILED		0
#define SUCCESS		1

int rco_dump(char *sRcoFile)
{	
	char sXmlFile[255];
	char sResDir[255];
	char sResImgDir[255];
	char sResSndDir[255];
	char sResMdlDir[255];
	char sResTxtDir[255];
	char sResVsmxDir[255];
	
	uint8_t sTextOutput = TRUE;
	uint8_t sConvVsmx = TRUE;
	uint8_t sConvVag = TRUE;
	configLoadTagmap ();
	configLoadMiscmap ();
	
	// avoid to extract in dev_flash
	if(strstr(sRcoFile, "dev_usb") || strstr(sRcoFile, "dev_hdd")) { 
		strcpy(sResDir, sRcoFile);
		sResDir[strlen(sResDir)-4] = 0;
	} else {
		strcpy(sResDir, "/dev_hdd0/tmp");
		mkdir(sResDir, 0777);
		strcat(sResDir, "/RCO");
		mkdir(sResDir, 0777);
		strcat(sResDir, strrchr(sRcoFile, '/'));
		sResDir[strlen(sResDir)-4] = 0;
	}

	sprintf(sResImgDir, "%s/Images", sResDir);
	sprintf(sResSndDir, "%s/Sounds", sResDir);
	sprintf(sResMdlDir, "%s/Models", sResDir);
	sprintf(sResTxtDir, "%s/Text", sResDir);
	sprintf(sResVsmxDir, "%s/VSMX", sResDir);
	sprintf(sXmlFile, "%s/log.xml", sResDir);
	
	mkdir(sResDir, 0777);

    rRCOFile *rco = read_rco(sRcoFile);
	if (!rco) return FAILED;
	
	uint8_t sndDumped = FALSE;
	
	if(rco->tblImage) {
		mkdir(sResImgDir, 0777);
		strcat(sResImgDir, "/");
		dump_resources(rco->labels, rco->tblImage, RCOXML_TABLE_IMG_FMT, sResImgDir);
	}	
	if(rco->tblSound) {
		mkdir(sResSndDir, 0777);
		strcat(sResSndDir, "/");
		dump_resources(rco->labels, rco->tblSound, RCOXML_TABLE_SOUND_FMT,	sResSndDir);
		sndDumped = TRUE;
	}
	if(rco->tblModel) {
		mkdir(sResMdlDir, 0777);
		strcat(sResMdlDir, "/");
		dump_resources(rco->labels, rco->tblModel, RCOXML_TABLE_MODEL_FMT, sResMdlDir);
	}
	if(rco->tblText) {
		mkdir(sResTxtDir, 0777);
		strcat(sResTxtDir, "/");
		dump_text_resources(rco->labels, rco->tblText, TRUE, sResTxtDir, sTextOutput);
	}
	if (rco->tblVSMX) {
		mkdir(sResVsmxDir, 0777);
		strcat(sResVsmxDir, "/");
		rRCOEntry *rcoNode;
		for (rcoNode = rco->tblMain.firstChild; rcoNode; rcoNode = rcoNode->next) {
			if (rcoNode->id == RCO_TABLE_VSMX) {
				char defName[] = "vsmx";
				char *label = defName;
				if (rcoNode->labelOffset) label = rco->labels + rcoNode->labelOffset;
				print_load(" %s", label);
				
				sprintf(sResVsmxDir + strlen (sResVsmxDir), "%s.vsmx", label);
				if(!dump_resource (sResVsmxDir, rcoNode, dump_output_data)) {
					if (rcoNode->labelOffset) {
						warning ("Unable to dump VSMX resource '%s'.", label);
					} else {
						warning ("Unable to dump VSMX resource.");
					}
				}
				sprintf(sResVsmxDir + strlen (sResVsmxDir), "%s.txt", label);
				if(!dump_resource (sResVsmxDir, rcoNode, dump_output_vsmxdec)) {
					if (rcoNode->labelOffset) {
						warning ("Unable to dump VSMX resource '%s'.", label);
					} else {
						warning ("Unable to dump VSMX resource.");
					}
				}

				strcpy (rcoNode->srcFile, sResVsmxDir);
				rcoNode->srcAddr = 0;
				rcoNode->srcCompression = RCO_DATA_COMPRESSION_NONE;
			}
		}
	}
	
	FILE *fp;
	fp = fopen(sXmlFile, "w");
	if (fp==NULL) {
		error("Unable to create file %s", &strrchr(sXmlFile, '/')[1] );
		return FAILED;
	}

    int sndDumpVar = (sndDumped ? 1 : 0);
	
	if (sndDumped && sConvVag)
		sndDumpVar = 2;
	if (!write_xml (rco, fp, sResTxtDir,!sTextOutput, sndDumpVar, sConvVsmx))
		return FAILED;

    return SUCCESS;
}
