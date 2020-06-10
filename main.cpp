//Hello World!
//PES Groep 3
//Dit is een test

#include "mbed.h"
#include "platform/mbed_thread.h"

// I/O lijst

// Inputs
InterruptIn start_Button(PA_5);                    // Knop om de robotsofzuiger te starten.

InterruptIn US_V(PA_6);                            // Ultrasoonsensor die links voorin gemonteerd is (zie technische tekeningen).
InterruptIn US_A(PA_7);                            // Ultrasoonsensor die rechts voorin gemonteerd is (zie technische tekeningen).

InterruptIn IR_V(PB_6);                            // Infraroodsensor die links voorin gemonteerd is (zie technische tekeningen).                                                                  
InterruptIn IR_A(PC_7);                            // Infraroodsensor die rechts voorin gemonteerd is (zie technische tekeningen).

// Outputs
DigitalOut M_Links(PA_8);
DigitalOut M_rechts(PB_10);
DigitalOut AN(PB_4);


int main(){

    enum state{OFF, WACHT, RIJDEN, ONTWIJKEN};

    bool OFF_first = true;
    bool WACHT_first = true;

    bool RIJDEN_first = true;
    bool ONTWIJKEN_first = true;

    while(true){

        switch(){

            case OFF:

                //entry
                if(){

                }
            
                //do
                if(){

                }

                // exit
                if(){

                }

            break;

            case WACHT:

                //entry
                if(){

                }
            
                //do
                if(){

                }

                // exit
                if(){

                }

            break;

            case RIJDEN:

                //entry
                if(){

                }
            
                //do
                if(){

                }

                // exit
                if(){

                }

            break;

            case ONTWIJKEN:

                //entry
                if(){

                }
            
                //do
                if(){

                }

                // exit
                if(){

                }

            break;

            default:
                printf("Invalid state ")
            break;
        }
    }
    return 0;
}
