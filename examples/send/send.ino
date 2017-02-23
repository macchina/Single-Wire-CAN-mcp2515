/*
  Written in 2017 by Blaž Pongrac B.S., RoboSap, Institute of Technology, Ptuj (www.robosap-institut.eu) for Macchina LLC

  To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

  You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

#include <mcp_swcan.h>
#include <SPI.h>

const int SPI_CS_PIN = 78; // PB23

SWcan SW_CAN(SPI_CS_PIN);   // Set CS pin

void setup()
{
  Serial.begin(115200);
  SW_CAN.setupSW(0x00);
  delay(100);
  SW_CAN.mode(3); // Go to normal mode. 0 - Sleep, 1 - High Speed, 2 - High Voltage Wake-Up, 3 - Normal
  delay(1000);
}

unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};

void loop()
{
  // Extended frame needs to be used
  // send data:  id = 0x00, extended frame, data len = 8, stmp: data buf
  SW_CAN.sendMsgBuf(0x00, 1, 8, stmp);
  delay(100);                       // send data per 100ms
}
