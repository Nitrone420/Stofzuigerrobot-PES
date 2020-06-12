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

int time_last_click = false;                        // Tijd is 0 miliseconden.
int debounce_time = 250;                            // In miliseconden.

bool Start_Button_is_pressed = false;

Timer debounce;

void start_button_pressed(){
    if(debounce.read_ms() - time_last_click >= debounce_time)
    time_last_click = debounce.read_ms();
    Start_Button_is_pressed = true;
}

int main(){

    Start_Button.mode(PullUp);
    Start_Button.fall(&start_button_pressed);
    debounce.start();




    enum state{OFF, WACHT, RIJDEN, ONTWIJKEN_R, ONTWIJKEN_L, DRAAIEN};

    bool OFF_first = true;
    bool WACHT_first = true;

    bool RIJDEN_first = true;
    bool ONTWIJKEN_R_first = true;
    bool ONTWIJKEN_L_first = true;
    bool DRAAIEN_first = true;

    int current_state;
    int next_state = OFF;

    int Afgrond_detectie = 3;                   // afstand in centimeters.
    int Object_detectie = 5;                    // afstand in centimeters.

    Timer wachten;
    Timer achteruit;
    Timer draaien;

    while(true){

        current_state = next_state;

        switch(current_state){

            case OFF:

                //entry
                if(OFF_first){
                    OFF_first = false;
                    AN_groen_1 = true;
                    AN_groen_2 = true;
                    AN_oranje = true;
                    AN_rood = true;
                }
            
                //do
                if(Start_Button_is_pressed){
                    
                    Start_Button_is_pressed = false;
                    OFF_first = true;

                    current_state = WACHT;
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
                    AN_groen_1 = true;
                    AN_groen_2 = true;
                    AN_oranje = true;
                    AN_rood = true;

                    wachten.start();
                }
            
                //do
                if(wachten.read_ms() >= 5000){
                    WACHT_first = true;
                    next_state = RIJDEN;

                    wachten.stop();
                    wachten.reset();
                    
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

                    AN_groen_1 = true;
                    AN_groen_2 = true;
                    AN_oranje = true;
                    AN_rood = true;
                }
            
                //do
                if(US_V >= Object_detectie){
                    RIJDEN_first = true;
                    next_state = ONTWIJKEN_R;
                }

                if(IR_V >= Afgrond_detectie){
                    RIJDEN_first = true;
                    next_state = ONTWIJKEN_R;
                }

                // exit
                if(next_state != current_state){

                }

            break;

            case ONTWIJKEN_R:

                //entry
                if(ONTWIJKEN_R_first){
                    ONTWIJKEN_R_first = false;
                    M_Links_A = true;
                    M_rehts_A = true;

                    AN_groen_1 = true;
                    AN_groen_2 = true;
                    AN_oranje = true;
                    AN_rood = true;

                    achteruit.start();

                }
            
                //do
                if(achteruit.read_ms() >= 2000 ){

                    ONTWIJKEN_R_first = true;
                    next_state = DRAAIEN;

                    achteruit.stop();
                    achteruit.reset();
                }

                // exit
                if(next_state != current_state){

                }
            
            case ONTWIJKEN_L:

                //entry
                if(ONTWIJKEN_L_first){
                    ONTWIJKEN_L_first = false;
                    M_Links_A = true;
                    M_rehts_A = true;

                    AN_groen_1 = true;
                    AN_groen_2 = true;
                    AN_oranje = true;
                    AN_rood = true;

                    achteruit.start();

                }
            
                //do
                if(achteruit.read_ms() >= 2000 ){
                    ONTWIJKEN_L_first = true;
                    next_state = DRAAIEN;

                    achteruit.stop();
                    achteruit.reset();
                }

                // exit
                if(next_state != current_state){

                }



            break;

            case DRAAIEN:

                //entry
                if(DRAAIEN_first){
                    DRAAIEN_first = false;
                    M_Links_v = true;
                    M_rehts_A = true;

                    AN_groen_1 = true;
                    AN_groen_2 = true;
                    AN_oranje = true;
                    AN_rood = true;

                    draaien.start();

                }
            
                //do
                if(draaien.read_ms() >= 1000 ){
                    DRAAIEN_first = true;
                    next_state = RIJDEN;

                    draaien.stop();
                    draaien.reset();
                }

                // exit
                if(next_state != current_state){

                }



            break;

            default:

                printf("Invalid state /n");

            break;
        }
    }
    return 0;
}
