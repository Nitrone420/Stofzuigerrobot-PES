/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
 // Gemaakt door Burak Koyuncu (groep 3)

#include "mbed.h"
#include "platform/mbed_thread.h"

// I/O lijst

// Inputs
InterruptIn Start_Button(D13);                   // D13 Knop om de robotsofzuiger te starten. 

InterruptIn US_V(D10);                           // D12 Ultrasoonsensor die links voorin gemonteerd is (zie technische tekeningen).
InterruptIn US_A(D8);                            // D10 Ultrasoonsensor die rechts voorin gemonteerd is (zie technische tekeningen).

InterruptIn IR_V(D9);                            // D11 Infraroodsensor die links voorin gemonteerd is (zie technische tekeningen).                                                                  
InterruptIn IR_A(D7);                            // D9 Infraroodsensor die rechts voorin gemonteerd is (zie technische tekeningen).

AnalogIn AN_Potmeter(A0);                        // Potmeter voor het bepalen van accuniveau.

// Outputs
DigitalOut M_Links_v(D6);                        // D7 Linker motor vooruit (zie technische tekeningen).
DigitalOut M_rechts_v(D4);                       // D5 Rechter motor vooruit (zie technische tekeningen).

DigitalOut M_Links_A(D5);                       // D6 Linker motor achteruit (zie technische tekeningen).
DigitalOut M_rehts_A(D3);                       // D4 Rechter motor achteruit (zie technische tekeningen).



// Datatype voor debouncen.

int time_last_click_1 = false;                      // Tijd is 0 miliseconden.
int time_last_click_2 = false;                      // Tijd is 0 miliseconden
int time_last_click_3 = false;                      // Tijd is 0 miliseconden
int time_last_click_4 = false;                      // Tijd is 0 miliseconden
int time_last_click_5 = false;                      // Tijd is 0 miliseconden

int debounce_time = 250;                            // In miliseconden.

bool Start_Button_is_pressed = false;

bool US_V_is_pressed = false;
bool US_A_is_pressed = false;

bool IR_V_is_pressed = false;
bool IR_A_is_pressed = false;

Timer debounce_1;
Timer debounce_2;
Timer debounce_3;
Timer debounce_4;
Timer debounce_5;


// functies
void start_button_pressed();                        // Debouncen van de Strart_Button. zie voor definietie lijn 321.

void US_V_pressed();                                // Debouncen van de sensor US_V (knop). zie voor definietie lijn 327.
void US_A_pressed();                                // Debouncen van de sensor US_A (knop). zie voor definietie lijn 333.

void IR_V_pressed();                                // Debouncen van de sensor IR_v (knop). zie voor definietie lijn 339.
void IR_A_pressed();                                // Debouncen van de sensor IR_A (knop). zie voor definietie lijn 345.

int main(){

    
    Start_Button.mode(PullUp);
    Start_Button.fall(&start_button_pressed);
    debounce_1.start();

    US_V.mode(PullUp);
    US_V.fall(&US_V_pressed);
    debounce_2.start();

    US_A.mode(PullUp);
    US_A.fall(&US_A_pressed);
    debounce_3.start();

    IR_V.mode(PullUp);
    IR_V.fall(&IR_V_pressed);
    debounce_4.start();

    IR_A.mode(PullUp);
    IR_A.fall(&IR_A_pressed);
    debounce_5.start();




    enum state{OFF, WACHT, RIJDEN, ONTWIJKEN_R, ONTWIJKEN_L, DRAAIEN};

    bool OFF_first = true;
    bool WACHT_first = true;

    bool RIJDEN_first = true;
    bool ONTWIJKEN_R_first = true;
    bool ONTWIJKEN_L_first = true;
    bool DRAAIEN_first = true;

    bool STOP_A = false;

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
                }
            
                //do
                if(Start_Button_is_pressed){
                    
                    Start_Button_is_pressed = false;
                    OFF_first = true;

                    next_state = WACHT;
                }

                // exit
                if(next_state != current_state){
                    printf("OFF exit \n");
                }

            break;

            case WACHT:

                //entry
                if(WACHT_first){
                    WACHT_first = false;
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
                    printf("WACHT exit \n");
                }

            break;

            case RIJDEN:

                //entry
                if(RIJDEN_first){

                    RIJDEN_first = false;

                    M_rechts_v = true;
                    M_Links_v = true;

                    M_rehts_A = false;
                    M_Links_A = false;
                    printf("Rijden entry \n");
                }
            
                //do
                if(US_V_is_pressed || IR_V_is_pressed){

                    RIJDEN_first = true;
                    US_V_is_pressed = false;
                    IR_V_is_pressed = false;
                    
                    next_state = ONTWIJKEN_R;
                    printf("Rijden do \n");
                }

                // exit
                if(next_state != current_state){
                    printf("Rijden exit \n");
                }

            break;

            case ONTWIJKEN_R:

                //entry
                if(ONTWIJKEN_R_first){

                    ONTWIJKEN_R_first = false;

                    M_Links_v = false;
                    M_rechts_v = false;

                    M_Links_A = true;
                    M_rehts_A = true;

                    achteruit.start();

                    printf("ONTWIJKEN_R entry \n");
                }
            
                //do
                if( achteruit.read_ms() >= 5000 ||  IR_A_is_pressed || US_A_is_pressed ){ //2 sec

                    ONTWIJKEN_R_first = true;
                    US_A_is_pressed = false;
                    IR_A_is_pressed = false;
                    next_state = DRAAIEN;

                    achteruit.stop();
                    achteruit.reset();
                    printf("ONTWIJKEN_R do \n");
                }

                // exit
                if(next_state != current_state){
                    printf("ONTWIJKEN_R exit \n");
                }
            break;

            case DRAAIEN:

                //entry
                if(DRAAIEN_first){
                    DRAAIEN_first = false;
                    M_Links_v = true;
                    M_Links_A = false;

                    M_rechts_v = false;
                    M_rehts_A = true;

                    draaien.start();
                    printf("DRAAIEN entry \n");
                }
            
                //do
                if(draaien.read_ms() >= 5000 ){
                    DRAAIEN_first = true;
                    next_state = RIJDEN;

                    draaien.stop();
                    draaien.reset();
                    printf("DRAAIEN do \n");
                }

                // exit
                if(next_state != current_state){
                    printf("DRAAIEN exit \n");
                }



            break;

            default:

                printf("Invalid state /n");

            break;
        }
    }
    return 0;
}

// definitie van de functies

void start_button_pressed(){
    if(debounce_1.read_ms() - time_last_click_1 > debounce_time){
        time_last_click_1 = debounce_1.read_ms();
        Start_Button_is_pressed = true;
    }
}

void US_V_pressed(){
    if(debounce_2.read_ms() - time_last_click_2 > debounce_time){
        time_last_click_2 = debounce_2.read_ms();
        US_V_is_pressed = true;
    }
}

void US_A_pressed(){
    if(debounce_3.read_ms() - time_last_click_3 > debounce_time){
        time_last_click_3 = debounce_3.read_ms();
        US_A_is_pressed = true;
    }
}

void IR_V_pressed(){
    if(debounce_4.read_ms() - time_last_click_4 > debounce_time){
        time_last_click_4 = debounce_4.read_ms();
        IR_V_is_pressed = true;
    }
}

void IR_A_pressed(){
    if(debounce_5.read_ms() - time_last_click_5 > debounce_time){
        time_last_click_5 = debounce_5.read_ms();
        IR_A_is_pressed = true;
    }
}
