// Arduino ESP-32 CapButton Library
// https://github.com/dl9sec/JC_CapButton
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
// Copyright (C) 2019 by Thorsten Godau (dl9sec) and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
// Adapted Jack Christensen's great Button library to ESP-32 capacitive buttons.

#include "JC_CapButton.h"

/*----------------------------------------------------------------------*
/ initialize a CapButton object and the pin it's connected to.          *
/-----------------------------------------------------------------------*/
void CapButton::begin()
{
    if ( touchRead(m_pin) < m_thHold )
	{
	  m_state = LOW;
	}
	else
	{
	  m_state = HIGH;
	}
	pinMode(m_pin, INPUT); // Inserted as workaround for unstable values if several instances are declared
    if (m_invert) m_state = !m_state;
    m_time = millis();
    m_lastState = m_state;
    m_changed = false;
    m_lastChange = m_time;
}

/*----------------------------------------------------------------------*
/ returns the state of the button, true if pressed, false if released.  *
/ does debouncing, captures and maintains times, previous state, etc.   *
/-----------------------------------------------------------------------*/
bool CapButton::read()
{
    bool pinVal;
	
	uint32_t ms = millis();
	if ( touchRead(m_pin) < m_thHold )
	{
	  pinVal = LOW;
	}
	else
	{
	  pinVal = HIGH;
	}
	pinMode(m_pin, INPUT);  // Inserted as workaround for unstable values if several instances are declared
	if (m_invert) pinVal = !pinVal;
    if (ms - m_lastChange < m_dbTime)
    {
        m_changed = false;
    }
    else
    {
        m_lastState = m_state;
        m_state = pinVal;
        m_changed = (m_state != m_lastState);
        if (m_changed) m_lastChange = ms;
    }
    m_time = ms;
    return m_state;
}

/*----------------------------------------------------------------------*
 * isPressed() and isReleased() check the button state when it was last *
 * read, and return false (0) or true (!=0) accordingly.                *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool CapButton::isPressed()
{
    return m_state;
}

bool CapButton::isReleased()
{
    return !m_state;
}

/*----------------------------------------------------------------------*
 * wasPressed() and wasReleased() check the button state to see if it   *
 * changed between the last two reads and return false (0) or           *
 * true (!=0) accordingly.                                              *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool CapButton::wasPressed()
{
    return m_state && m_changed;
}

bool CapButton::wasReleased()
{
    return !m_state && m_changed;
}

/*----------------------------------------------------------------------*
 * pressedFor(ms) and releasedFor(ms) check to see if the button is     *
 * pressed (or released), and has been in that state for the specified  *
 * time in milliseconds. Returns false (0) or true (!=0) accordingly.   *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool CapButton::pressedFor(uint32_t ms)
{
    return m_state && m_time - m_lastChange >= ms;
}

bool CapButton::releasedFor(uint32_t ms)
{
    return !m_state && m_time - m_lastChange >= ms;
}

/*----------------------------------------------------------------------*
 * lastChange() returns the time the button last changed state,         *
 * in milliseconds.                                                     *
 *----------------------------------------------------------------------*/
uint32_t CapButton::lastChange()
{
    return m_lastChange;
}
