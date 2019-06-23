// Arduino ESP-32 CapButton Library
// https://github.com/dl9sec/JC_CapButton
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
// Copyright (C) 2019 by Thorsten Godau (dl9sec) and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
// Adapted Jack Christensen's great Button library to ESP-32 capacitive buttons.
//
// Example sketch to demonstrate toggle buttons.

#include <JC_CapButton.h>       // https://github.com/dl9sec/JC_CapButton

// pin assignments
const byte
    LED1_PIN(32),               // connect an LED to ground, through an appropriate current limiting resistor
    LED2_PIN(33),               // connect an LED to ground, through an appropriate current limiting resistor
    BUTTON1_PIN(12),            // connect a capacitive button to this pin
    BUTTON2_PIN(13);            // connect a capacitive button to this pin

ToggleCapButton                 // define the buttons
    capbtn1(BUTTON1_PIN),       // this button's initial state is off
    capbtn2(BUTTON2_PIN, true); // this button's initial state is on

void setup()
{
    // initialize the button objects
    capbtn1.begin();
    capbtn2.begin();

    // set the LED pins as outputs
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);

    // show the initial states
    digitalWrite(LED1_PIN, capbtn1.toggleState());
    digitalWrite(LED2_PIN, capbtn2.toggleState());
}

void loop()
{
    // read the buttons
    capbtn1.read();
    capbtn2.read();

    // if button state changed, update the LEDs
    if (capbtn1.changed()) digitalWrite(LED1_PIN, capbtn1.toggleState());
    if (capbtn2.changed()) digitalWrite(LED2_PIN, capbtn2.toggleState());
}
