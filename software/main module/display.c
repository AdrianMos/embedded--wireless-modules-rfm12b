#include "local.h"
#include "display.h"


void DISP_genereaza_caracterele(u8 in, u8 *char1, u8 *char2)
{
if (in>99)
{
	*char1=DISP_MINUS;
	*char2=DISP_MINUS;
}
else
{

	u8 aux = (u8) (in / 10); //preia prima cifra din numar


	switch (aux) 			 //comanda ledurile segementului conform cifrei
		{
			case 0: 	*char1=DISP_ZERO;  break;
			case 1: 	*char1=DISP_UNU;   break;
			case 2: 	*char1=DISP_DOI;   break;
			case 3: 	*char1=DISP_TREI;  break;
			case 4: 	*char1=DISP_PATRU; break;
			case 5: 	*char1=DISP_CINCI; break;
			case 6: 	*char1=DISP_SASE;  break;
			case 7: 	*char1=DISP_SAPTE; break;
			case 8: 	*char1=DISP_OPT;   break;
			case 9: 	*char1=DISP_NOUA;  break;
			default:    *char1=DISP_E;     break;
		}


	aux = (u8) (in % 10);   //preia a doua cifra din numar

	switch (aux)			//comanda ledurile segementului conform cifrei
		{
			case 0: 	*char2=DISP_ZERO;  break;
			case 1: 	*char2=DISP_UNU;   break;
			case 2: 	*char2=DISP_DOI;   break;
			case 3: 	*char2=DISP_TREI;  break;
			case 4: 	*char2=DISP_PATRU; break;
			case 5: 	*char2=DISP_CINCI; break;
			case 6: 	*char2=DISP_SASE;  break;
			case 7: 	*char2=DISP_SAPTE; break;
			case 8: 	*char2=DISP_OPT;   break;
			case 9: 	*char2=DISP_NOUA;  break;
			default:    *char2=DISP_E;     break;
		}
}
}

/*

	case '0': 	PORTA=DISP_ZERO;
				break;

	case '1': 	PORTA=DISP_UNU;
				break;

	case '2': 	PORTA=DISP_DOI;
				break;

	case '3': 	PORTA=DISP_TREI;
				break;

	case '4': 	PORTA=DISP_PATRU;
				break;

	case '5': 	PORTA=DISP_CINCI;
				break;

	case '6': 	PORTA=DISP_SASE;
				break;

	case '7': 	PORTA=DISP_SAPTE;
				break;

	case '8': 	PORTA=DISP_OPT;
				break;

	case '9': 	PORTA=DISP_NOUA;
				break;


	case '-': 	PORTA=DISP_MINUS;
				break;

	case 'P': 	PORTA=DISP_P;
				break;

	case 'E': 	PORTA=DISP_E;
				break;


	default:    PORTA=0XFF;	//nu afiseaza nimic
				break;


*/
