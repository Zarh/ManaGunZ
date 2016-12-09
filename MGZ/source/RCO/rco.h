#ifndef _RCO_H
#define _RCO_H

int rco_help (void);
int rco_dump(char *sRcoFile);
int rco_compile (void);
int rco_rebuild (void);
// int rco_replace(void);
int rco_vagdec (void);
int rco_vagenc (void);
int rco_vsmxdec (void);
int rco_vsmxenc (void);

#endif
