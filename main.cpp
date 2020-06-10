//Hello World!
//PES Groep 3
//Dit is een test

#include "mbed.h"

// I/O lijst

// Inputs
    InterruptIn start_Button(PA_5);                     // Knop om de robotsofzuiger te starten.

    InterruptIn US_LV(PA_6);                            // Ultrasoonsensor die links voorin gemonteerd is (zie technische tekeningen).
    InterruptIn US_RV(PA_6);                            // Ultrasoonsensor die rechts voorin gemonteerd is (zie technische tekeningen).

    InterruptIn US_LA(PA_7);                            // Ultrasoonsensor die links achterin gemonteerd is (zie technische tekeningen).
    InterruptIn US_RA(PB_6);                            // Ultrasoonsensor die rechts voorin gemonteerd is (zie technische tekeningen).

    InterruptIn IR_LV(PC_7);                                                                               
    InterruptIn IR_RV(PA_9);

    InterruptIn IR_LA(PA_8);
    InterruptIn IR_RA(PB_10);


int main(){

    
    

    while(true){
        
    }
}
