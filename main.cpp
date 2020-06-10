//Hello World!
//PES Groep 3
//Dit is een test

#include "mbed.h"
#include "platform/mbed_thread.h"

// I/O lijst

// Inputs
InterruptIn Start_Button(PA_5);                    // Knop om de robotsofzuiger te starten.

InterruptIn US_V(PA_6);                            // Ultrasoonsensor die links voorin gemonteerd is (zie technische tekeningen).
InterruptIn US_A(PA_7);                            // Ultrasoonsensor die rechts voorin gemonteerd is (zie technische tekeningen).

InterruptIn IR_V(PB_6);                            // Infraroodsensor die links voorin gemonteerd is (zie technische tekeningen).                                                                  
InterruptIn IR_A(PC_7);                            // Infraroodsensor die rechts voorin gemonteerd is (zie technische tekeningen).

AnalogIn AN_Potmeter(A0);                          // Potmeter voor het bepalen van accuniveau.

// Outputs
DigitalOut M_Links_v(PA_8);                        // Linker motor vooruit (zie technische tekeningen).
DigitalOut M_rechts_v(PB_10);                      // Rechter motor vooruit (zie technische tekeningen).

DigitalOut M_Links_A(PB_4);                        // Linker motor achteruit (zie technische tekeningen).
DigitalOut M_rehts_A(PB_5);                        // Rechter motor achteruit (zie technische tekeningen).

DigitalOut AN_groen_1(PB_3);                       // Toelaatbare werk spanning is 100%.
DigitalOut AN_groen_2(PA_10);                      // Toelaatbare werk spanning is 75%.
DigitalOut AN_oranje(PA_2);                        // Toelaatbare werk spanning is 50%.
DigitalOut AN_rood(PA_3);                          // Toelaatbare werk spanning is 25%.


int main(){

    enum state{OFF, WACHT, RIJDEN, ONTWIJKEN};

    bool OFF_first = true;
    bool WACHT_first = true;

    bool RIJDEN_first = true;
    bool ONTWIJKEN_first = true;

    int current_state;
    int next_state = OFF;

    Timer wachten;

    while(true){

        current_state = next_state;

        switch(current_state){

            case OFF:

                //entry
                if(OFF_first){
                    OFF_first = false;
                    AN_groen_1 = 1;
                    AN_groen_2 = 1;
                    AN_oranje = 1;
                    AN_rood = 1;
                }
            
                //do
                if(Start_Button){
                    current_state = WACHT;
                   // Start_Button == false; ?? moet start_button boolean worden en moet er dan ook debounce functie gemaakt worden
                   OFF_first = true;
                }

                // exit
                if(next_state != current_state){
                    printf("OFF exit");
                }

            break;

            case WACHT:

                //entry
                if(WACHT_first){
                    WACHT_first = false;
                    wachten.start();
                }
            
                //do
                if(wachten.read_ms() >= 500){
                    wachten.reset();
                    next_state = RIJDEN;
                }

                // exit
                if(next_state != current_state){
                    printf("WACHT exit");
                }

            break;

            case RIJDEN:

                //entry
                if(RIJDEN_first){
                    RIJDEN_first = false;
                    M_rechts_v = true;
                    M_Links_v = true;
                }
            
                //do
                if(US_V || US_A || IR_V || IR_A){

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

                printf("Invalid state /n");

            break;
        }
    }
    return 0;
}
