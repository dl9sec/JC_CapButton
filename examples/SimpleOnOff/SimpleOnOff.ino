// Arduino ESP-32 CapButton Library
// https://github.com/dl9sec/JC_CapButton
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
// Copyright (C) 2019 by Thorsten Godau (dl9sec) and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
// Adapted Jack Christensen's great Button library to ESP-32 capacitive buttons.
//
// Example sketch to turn an LED on and off with a capacitive button.

#include <JC_CapButton.h>       // https://github.com/dl9sec/JC_CapButton

// pin assignments
const byte
    BUTTON_PIN(13),             // connect a capacitive button to this pin
    LED_PIN(1);                 // the standard Arduino "pin 1" LED

CapButton myCapBtn(BUTTON_PIN); // define the button

void setup()
{
    myCapBtn.begin();           // initialize the button object
    pinMode(LED_PIN, OUTPUT);   // set the LED pin as an output
}

void loop()
{
    static bool ledState;       // a variable that keeps the current LED status
    myCapBtn.read();            // read the button

    if (myCapBtn.wasReleased()) // if the button was released, change the LED state
    {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}

