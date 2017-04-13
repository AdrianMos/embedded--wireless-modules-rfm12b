#include "local.h"
#include "data.h"
#include "RF.h"

///////////////////////////// DATA_code (u8 in, u8 * out) ///////
//codare Huffman a datelor
//codeaza 4 biti in 8 biti
//intrarea: 0000 i3 i5 i6 i7
//iesirea: C0 C1 C2 i3 C4 i5 i6 i7


//C1 = i3 + i5 + i7
//C2 = i3 + i6 + i7
//C4 = i5 + i6 + i7
//C0 = C1 + C2 + i3 + C4 + i5 + i6 + i7

#define C1(in) (GET_BIT(in, 3) ^ GET_BIT(in, 2) ^ GET_BIT(in, 0))
#define C2(in) (GET_BIT(in, 3) ^ GET_BIT(in, 1) ^ GET_BIT(in, 0))
#define C4(in) (GET_BIT(in, 2) ^ GET_BIT(in, 1) ^ GET_BIT(in, 0))
#define C0(in) (GET_BIT(in, 6) ^ GET_BIT(in, 5) ^ GET_BIT(in, 4) ^ GET_BIT(in,3) ^ GET_BIT(in,2) ^ GET_BIT(in,1) ^ GET_BIT(in,0))


void DATA_code(u8 in, u8 *out1)
{
    u8 out = in; //0000 i3 i5 i6 i7

    if (C1(in))         SET_BIT(out, 6); //C1=1;
    else                CLR_BIT(out, 6); //C1=0;

    if (C2(in))         SET_BIT(out, 5); //C2=1;
    else                CLR_BIT(out, 5); //C2=0;

    if (C4(in))         SET_BIT(out, 3); //C4=1;
    else                CLR_BIT(out, 3); //C4=0;

    //C4 a fost suprapus peste i3
    //i3 trebuie recopiat pe pozitia 4
    if (GET_BIT(in, 3)) SET_BIT(out, 4);
    else                CLR_BIT(out, 4);

    //pentru calculul lui C0 se tine cont de C1,C2,C3
    //de aceea citim bitii din variabila out, unde avem calculat C1,C2,C3
    if (C0(out))        SET_BIT(out, 7);  //C0=1
    else                CLR_BIT(out, 7);  //C0=0


    *out1=out;
}

///////////////////////////// DATA_decode (u8 in, u8 *out1) ///////
//decodare Huffman a datelor
//decodeaza 8 biti in 4 biti de informatie utila
//intrarea: C0' C1' C2' i3' C4' i5' i6' i7'
//iesirea: 0000 i3 i5 i6 i7
//returneaza 0 daca exista erori ce nu pot fi corectate (2 erori) si 


//z4 = C4 + i5 + i6 + i7
//z2 = C2 + i3 + i6 + i7
//z1 = C1 + i3 + i5 + i7
//z0 = C0+C1+C2+i3+C4+i5+i6+i7
#define z4(in) (GET_BIT(in,3) ^ GET_BIT(in,2) ^ GET_BIT(in,1) ^ GET_BIT(in,0))
#define z2(in) (GET_BIT(in,5) ^ GET_BIT(in,4) ^ GET_BIT(in,1) ^ GET_BIT(in,0))
#define z1(in) (GET_BIT(in,6) ^ GET_BIT(in,4) ^ GET_BIT(in,2) ^ GET_BIT(in,0))
#define z0(in) (GET_BIT(in,7) ^ GET_BIT(in,6) ^ GET_BIT(in,5) ^ GET_BIT(in,4) ^ GET_BIT(in,3) ^ GET_BIT(in,2) ^ GET_BIT(in,1) ^ GET_BIT(in,0))

u8 DATA_decode(u8 in, u8 *out1)
{
    u8 out=in;
    if (in!=0)
    {
        if(z0(in)==0)//z0==0
        {
            //z==0
            if ((z1(in)==0) && (z2(in)==0) && (z4(in)==0))
            {
                // -> nu exista erori sau nu exista erori corectabile prin cod
                //nu se efectueaza nici o operatie de corectie
            }
            //z!=1  => detectie erori duble
            else if ((z1(in)==0) || (z2(in)==0) || (z4(in)==0))
            {
                *out1 = DATA_EROARE_DUBLA;
                return 0;
            }
        }
        else //z0==1
        {
            //z!=0
            if (z1(in) || z2(in) || z4(in)) 
            {
                //exista eroare corectabila
                
                //neaga valoarea bitului eronat
                //7-4*z4+2*z2+z1+z0 ne da pozitia bitului
                //se face un sau exclusiv intre iesire si 0001000 (1 in pozitia eronata)
                
                out = out ^ (1<< (8-(4*z4(in)+2*z2(in)+z1(in)+z0(in))));
            }

            //cazul z==0 => C0 e eronat
            //{
                  // nu ne intereseaza cazul
            //}
        }

        //C0' C1' C2' i3' C4' i5' i6' i7'
        //copiaza bitul i3 in pozitia lui C4
        if (GET_BIT(out, 4))    SET_BIT(out, 3);
        else                    CLR_BIT(out, 3);

        out=out & 0x0F; //pune primii 4 biti pe o
        //=> 0000 i3 i4 i5 i6

        *out1=out;
        return 1; //eroarea a fost corectata sau nu au existat erori
    }
    return 0;
}

///////////////////////////// DATA_code_and_send (u8 in) //////////////////
//codeaza bitii de intrare si ii transmite

void DATA_code_and_send(u8 in)
{
    u8 coded_first_4, coded_last_4;
    //imparte cei 8 biti de date in 2 grupe de cate 4 biti
    //apoi fiecare grupa este codata in 8 biti => 2*8 biti
    DATA_code(in >> 4,   &coded_first_4);
    DATA_code(in & 0x0F, &coded_last_4);

    //trimite cei 2*8 biti codati
    RF_send_data(coded_first_4);
    RF_send_data(coded_last_4);
}

///////////////////////////// DATA_receive_and_decode (u8 *out) ///////
//receptioneaza datele (2*8 biti)
//decodare Huffman
//decodeaza 2*8 biti in 2*4 biti de informatie utila
//combina cele 2 grupe de catre 4 biti de informatie => 8 biti de iesire

u8 DATA_receive_and_decode(u8 *out)
{
    u8 out1, out2;

    DATA_decode(  RF_receive(),  &out1); //receptioneaza si decodeaza 8 biti
    DATA_decode(  RF_receive(),  &out2); //receptioneaza si decodeaza 8 biti

    if((out1!=DATA_EROARE_DUBLA) && (out2!=DATA_EROARE_DUBLA)) //daca nu exista erori
    {
        out1 = out1<<4;    //deplasare cu 4 biti spre stanga a lui out1 => b0b1b2b3 0 0 0 0
        out1 = out1 | out2;//combinarea grupelor de 4 biti              => b0b1b2b3b4b5b6b7

        *out = out1;
        return 1;
    }
    else 
    {
        return DATA_EROARE_DUBLA;
    }
}