#ifndef DISPLAY_H
#define DISPLAY_H

#define DISP_UNU	0x5F
#define DISP_DOI	0x32
#define DISP_TREI	0x16
#define DISP_PATRU  0x1D
#define DISP_CINCI  0x94
#define DISP_SASE   0x90
#define DISP_SAPTE	0x5E
#define DISP_OPT	0x10
#define DISP_NOUA	0x14
#define DISP_ZERO	0x50
#define DISP_E	    0xB0
#define DISP_P   	0x38
#define DISP_MINUS	0xBF

#define SET_DOT_POINT(x) ((x)=((x) & ~0x10))

extern void DISP_genereaza_caracterele(u8 in, u8 *char1, u8 *char2);



#endif
