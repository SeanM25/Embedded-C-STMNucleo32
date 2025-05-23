#include <stdio.h>
#include "BOARD.h"
#include <Buttons.h>


static u_int8_t last_button_state = BUTTON_EVENT_NONE; // Gets previous state of buttons after each call to event checler

static u_int8_t debounce_timer = BUTTON_EVENT_NONE; // Debounce timer initialized to 0

// These are the return values of Button_States() for each of the buttons note I'm looking at them Left --> Right

#define button1val 8
#define button2val 4
#define button3val 2
#define button4val 1


void Buttons_Init(void){ // Intialize our buttons

    // This function actually does nothing?



}

uint8_t Buttons_CheckEvents(void){

    uint8_t Button_pressed = BUTTON_EVENT_NONE; // Intially no buttons are pressed

    uint8_t statusButton = BUTTON_STATES(); // Get status of each of the buttons

        //printf("%d\n", statusButton);

if(debounce_timer > 0){ // If we still must debounce just return the intial state of the button

    debounce_timer--; // Decrement debouncer

    return Button_pressed; // Return button pressed
}


if(statusButton == last_button_state){  // If no new buttons have been pressed

    return BUTTON_EVENT_NONE; // Indicate no button event
    
}


// For Buttons 1 - 4 I check to see if the button has both been pressed and changed from its previous state
// If both these conditions are met then we update the Button_pressed variable for each of the buttons


// Button 1

if((statusButton & button1val) && (last_button_state & button1val) == 0){ // Has button 1's status changed (pressed down)?

    Button_pressed |= BUTTON_EVENT_1DOWN; // If so its down


} else if ((statusButton & button1val) == 0 && (last_button_state & button1val)){ // If the buttons state hasnt changed (up)

    Button_pressed |= BUTTON_EVENT_1UP; // Its up
}

// Button 2

if((statusButton & button2val) && (last_button_state & button2val) == 0){

    Button_pressed |= BUTTON_EVENT_2DOWN;


} else if ((statusButton & button2val) == 0 && (last_button_state & button2val)){

    Button_pressed |= BUTTON_EVENT_2UP;
}

// Button 3

if((statusButton & button3val) && (last_button_state & button3val) == 0){

    Button_pressed |= BUTTON_EVENT_3DOWN;


} else if ((statusButton & button3val) == 0 && (last_button_state & button3val)){

    Button_pressed |= BUTTON_EVENT_3UP;
}

// Button 4

if((statusButton & button4val) && (last_button_state & button4val) == 0){

    Button_pressed |= BUTTON_EVENT_4DOWN;


} else if ((statusButton & button4val) == 0 && (last_button_state & button4val)){

    Button_pressed |= BUTTON_EVENT_4UP;
}

debounce_timer = BUTTONS_DEBOUNCE_PERIOD; // Set debounce timer to given button debounce value


last_button_state = statusButton; // updtate previous button status

    return Button_pressed; // return which button was pressed
}