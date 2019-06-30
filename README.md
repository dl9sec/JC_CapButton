# Arduino ESP-32 CapButton Library
https://github.com/dl9sec/JC_CapButton  

## License
Arduino ESP-32 CapButton Library Copyright (C) 2019 Thorsten Godau (dl9sec) GNU GPL v3.0.

Based upon Arduino Button Library Copyright (C) 2018-2019 Jack Christensen GNU GPL v3.0 (see https://github.com/JChristensen/JC_Button).

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License v3.0 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/gpl.html>

## Introduction
The ESP-32 CapButton library is for debouncing and reading momentary capacitive buttons.  "Long presses" of arbitrary length can be detected. Works well in state machine constructs.  Use the read() function to read each button in the main loop, which should execute as fast as possible.

The simplest way to use a button with an ESP-32 is to wire the button at the appropriate GPIO pin (2, 4, 12, 13, 14, 15, 27, 32, 33).
The Button class constructor takes four arguments, but three have default values that work for a button wired in this manner.

A derived class, ToggleCapButton, implements button objects that need only "push-on, push-off" functionality.

Tested on an AZ-Delivery ESP-32 DevKitC.

[![Watch the video](https://github.com/dl9sec/JC_CapButton/blob/master/demovideo/ESP-32_JC_CapButton_Demo.png?raw=true)](https://github.com/dl9sec/JC_CapButton/blob/master/demovideo/ESP-32_JC_CapButton_Demo.mp4?raw=true)

## Examples
The following example sketches are included with the **CapButton** library:

- **SimpleOnOff**: Just turns the Arduino's pin 1 LED on and off.
- **LongPress**: Demonstrates detecting long and short button presses.
- **UpDown**: Counts up or down, one number at a time or rapidly by holding the button down.
- **Toggle**: Demonstrates ToggleButton functionality.


## Constructors

### CapButton(pin, dbTime, thHold, invert)
##### Description
The constructor defines a capacitiove button object.
##### Syntax
`Button(pin, dbTime, thHold, invert);`
##### Required parameter
**pin:** Arduino pin number that the capacitive button is connected to *(byte)*  
##### Optional parameters
**dbTime:** Debounce time in milliseconds. Defaults to 25ms if not given. *(unsigned long)*  
**thHold:** Threshold to detect a pushed button. Defaults to 50. *(byte)*  
**invert:** *false* interprets a high logic level to mean the button is pressed, *true* interprets a low level as pressed. *true* should be used when a pull-up resistor is employed, *false* for a pull-down resistor. Defaults to *true* if not given. *(bool)*
##### Returns
None.
##### Example
```c++
// capbutton connected to pin 13, 25ms debounce, threshold 50, logic inverted
CapButton myCapButton(13);

// same as above but this button needs a longer debounce time (50ms)
CapButton myCapButton(13, 50);

// a capbutton wired to pin 14, threshold set to 25 and inverted logic
CapButton myCapButton(14, 25, 30, false);
```

### ToggleCapButton(pin, initialState, dbTime, thHold, invert)
##### Description
The constructor defines a capacitive toggle button object, which has "push-on, push-off" functionality. The initial state can be on or off. See the section, [ToggleButton Library Functions](https://github.com/dl9sec/JC_CapButton#togglecapbutton-library-functions) for functions that apply specifically to the ToggleCapButton object. The ToggleCapButton class is derived from the CapButton class, so all CapButton functions are available, but because it is inherently a more limited concept, the special ToggleCapButton functions will be most useful, along with `begin()` and `read()`.
##### Syntax
`ToggleCapButton(pin, initialState, dbTime, thHold, invert);`
##### Required parameter
**pin:** Arduino pin number that the capacitive button is connected to *(byte)*  
##### Optional parameters
**initialState:** Initial state for the button. Defaults to off (false) if not given. *(bool)*  
**dbTime:** Debounce time in milliseconds. Defaults to 25ms if not given. *(unsigned long)*  
**thHold:** Threshold to detect a pushed button. Defaults to 50. *(int)*  
**invert:** *false* interprets a high logic level to mean the button is pressed, *true* interprets a low level as pressed. *true* should be used when a pull-up resistor is employed, *false* for a pull-down resistor. Defaults to *true* if not given. *(bool)*
##### Returns
None.
##### Example
```c++
// capbutton connected  pin 13, initial state off,
// 25ms debounce, theshold 50, logic inverted
ToggleCapButton myCapToggle(13);

// same as above but this capbutton is initially "on" and also
// needs a longer debounce time (50ms).
ToggleCapButton myCapToggle(13, true, 50);

// a capbutton wired to pin 14, threshold set to 25 and inverted logic
// initial state is off.
Button myButton(4, false, 25, 25, false);

```

## CapButton Library Functions

### begin()
##### Description
Initializes the Button object and the pin it is connected to.
##### Syntax
`myCapButton.begin();`
##### Parameters
None.
##### Returns
None.
##### Example
```c++
myCapButton.begin();
```
### read()
##### Description
Reads the button and returns a *boolean* value (*true* or *false*) to indicate whether the button is pressed. The read() function needs to execute very frequently in order for the sketch to be responsive. A good place for read() is at the top of loop(). Often, the return value from read() will not be needed if the other functions below are used.
##### Syntax
`myCapButton.read();`
##### Parameters
None.
##### Returns
*true* if the button is pressed, else *false* *(bool)*
##### Example
```c++
myCapButton.read();
```

### isPressed()
### isReleased()
##### Description
These functions check the button state from the last call to `read()` and return false or true accordingly. These functions **do not** cause the button to be read.
##### Syntax
`myCapButton.isPressed();`  
`myCapButton.isReleased();`
##### Parameters
None.
##### Returns
*true* or *false*, depending on whether the button has been pressed (released) or not *(bool)*
##### Example
```c++
if ( myCapButton.isPressed() )
{
	//do something
}
else
{
	//do something else
}
```

### wasPressed()
### wasReleased()
##### Description
These functions check the button state to see if it changed between the last two calls to `read()` and return false or true accordingly. These functions **do not** cause the button to be read. Note that these functions may be more useful than `isPressed()` and `isReleased()` since they actually detect a **change** in the state of the button, which is usually what we want in order to cause some action.
##### Syntax
`myCapButton.wasPressed();`  
`myCapButton.wasReleased();`
##### Parameters
None.
##### Returns
*true* or *false*, depending on whether the button was pressed (released) or not *(boolean)*
##### Example
```c++
if ( myCapButton.wasPressed() )
{
	//do something
}
```

### pressedFor(ms)
### releasedFor(ms)
##### Description
These functions check to see if the button is pressed (or released), and has been in that state for the specified time in milliseconds. Returns false or true accordingly. These functions are useful to detect "long presses". Note that these functions **do not** cause the button to be read.
##### Syntax
`myCapButton.pressedFor(ms);`  
`myCapButton.releasedFor(ms);`
##### Parameters
**ms:** The number of milliseconds *(unsigned long)*
##### Returns
*true* or *false*, depending on whether the button was pressed (released) for the specified time *(bool)*
##### Example
```c++
if ( myCapButton.pressedFor(1000) )
{
    // button has been pressed for one second
}
```

### lastChange()
##### Description
Under certain circumstances, it may be useful to know when a button last changed state. `lastChange()` returns the time the button last changed state, in milliseconds (the value is derived from the Arduino millis() function).
##### Syntax
`myCapButton.lastChange();`
##### Parameters
None.
##### Returns
The time in milliseconds when the button last changed state *(unsigned long)*
##### Example
```c++
unsigned long msLastChange = myCapButton.lastChange();
```

## ToggleCapButton Library Functions

### changed()
##### Description
Returns a boolean value (true or false) to indicate whether the toggle button changed state the last time `read()` was called.
##### Syntax
`myCapToggle.changed();`
##### Parameters
None.
##### Returns
*true* if the toggle state changed, else *false* *(bool)*
##### Example
```c++
if (myCapToggle.changed())
{
    // do something
}
else
{
    // do something different
}
```

### toggleState()
##### Description
Returns a boolean value (true or false) to indicate the toggle button state as of the last time `read()` was called.
##### Syntax
`myCapToggle.toggleState();`
##### Parameters
None.
##### Returns
*true* if the toggle is "on", else *false* *(bool)*
##### Example
```c++
if (myCapToggle.toggleState())
{
    // do something
}
else
{
    // do something different
}
```
