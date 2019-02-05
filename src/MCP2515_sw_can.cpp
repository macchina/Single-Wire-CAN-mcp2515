/*
  mcp_swcan.h
  2017 Copyright (c) Macchina LLC.  All right reserved.

  Author: Blaž Pongrac B.S., RoboSap, Institute of Technology, Ptuj (www.robosap-institut.eu)

  The MIT License (MIT)

  Copyright (c) 2017 Macchina LLC.

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
 */

#include "Arduino.h"
#include "SPI.h"
#include <MCP2515_sw_can.h>
#include "MCP2515_defs.h"

//Initalize the two mode pins and also set them to mode 3 which is normal mode
void SWcan::setupSW(unsigned long speed)
{
    Init(speed, 16);
    pinMode(SWC_M0, OUTPUT);
    pinMode(SWC_M1, OUTPUT);
    digitalWrite(SWC_M0, HIGH);
    digitalWrite(SWC_M1, HIGH);
}

void SWcan::mode(byte mode)
{
    switch (mode)
    {
    case 0:                        // Sleep Mode
        digitalWrite(SWC_M0, LOW);
        digitalWrite(SWC_M1, LOW);
        break;
    case 1:                        // High Speed
        digitalWrite(SWC_M0, HIGH);
        digitalWrite(SWC_M1, LOW);
        break;
    case 2:                        // High Voltage Wake-Up
        digitalWrite(SWC_M0, LOW);
        digitalWrite(SWC_M1, HIGH);
        break;
    case 3:                        // Normal Mode
        digitalWrite(SWC_M0, HIGH);
        digitalWrite(SWC_M1, HIGH);
        break;
    default:
        break;
    }
}
