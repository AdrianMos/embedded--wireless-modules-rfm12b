#include "local.h"

#include "IR.h"
#include "IR_conf.h"

u8 IR_previous_state=0;

void IR_init()
{
    CLR_BIT(IR_PORT_DIR, IR_PIN); //set read pin as input

    //timer 0 init
    //clock = clock_io/8 -> 010 (clock=1MHz/8 = 125kHz ) 
    CLR_BIT(TCCR2, 2);
    SET_BIT(TCCR2, 1);
    CLR_BIT(TCCR2, 0);

     
    //timer mode -> Clear Timer on CompareMatch (CTC) Mode   (WGM01:0 = 2)
    SET_BIT(TCCR2, 3);
    CLR_BIT(TCCR2, 6);

    //enable interrupt on match 
    SET_BIT(TIMSK, 7);       

    OCR2 = 11; //=> 10.5kHz
}

//returns IR_TRANSITION_LH for low  to high transition
//        IR_TRANSITION_HL for high to low  transition
//        IR_NO_TRANSITION_LOW  for no transition in  LOW level state
//          IR_NO_TRANSITION_HIGH for no transition in HIGH level state
u8 IR_transition()
{
    u8 IR_current_state = GET_BIT(IR_PORT_READ, IR_PIN);

    //high to low transition
    if((IR_current_state==0) && (IR_previous_state==1))
    {
          IR_previous_state=IR_current_state;
        return IR_TRANSITION_HL;
    }
    //low to high transition
    else if((IR_current_state==1) && (IR_previous_state==0))
    {
        IR_previous_state=IR_current_state;
        return IR_TRANSITION_LH;
    }
    //no transition
    else
    {
        //no transition,  low level
        if(IR_previous_state==0) 
            return IR_NO_TRANSITION_LOW;
        //no transition, high level
        else 
            return IR_NO_TRANSITION_HIGH;
    }
}
