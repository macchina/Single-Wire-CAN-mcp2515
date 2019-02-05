/*
  MCP2515 CAN Interface Using SPI
  
  Author: David Harding
  
  Created: 11/08/2010
  Modified: 6/26/12 by RechargeCar Inc.
  
  For further information see:
  
  http://ww1.microchip.com/downloads/en/DeviceDoc/21801e.pdf
  http://en.wikipedia.org/wiki/CAN_bus

  The MCP2515 Library files also contain important information.
  
  This sketch is configured to work with the 'Macchina' Automotive Interface board 
  manufactured by RechargeCar Inc. CS_PIN and INT_PIN are specific to this board.
  
  This sketch shows the most basic of steps to send and receive CAN messages.
  
  NOTE!!!  If you use this sketch to test on a live system I suggest that you comment out the
  send messages lines unless you are certain that they will have no detrimental effect! 


  This example code is in the public domain.
  
*/

#include <SPI.h>
#include <MCP2515_sw_can.h>

// Pin definitions specific to how the MCP2515 is wired up.
#ifdef MACCHINA_M2
#define CS_PIN  SPI0_CS3
#define INT_PIN SWC_INT
#else
#define CS_PIN  34
#define INT_PIN 38
#endif

// Create CAN object with pins as defined
SWcan SCAN(CS_PIN, INT_PIN);

void CANHandler() {
	SCAN.intHandler();
}

void setup() {
  delay(5000);
	SerialUSB.begin(115200);
	
	SerialUSB.println("Initializing ...");

	// Set up SPI Communication
	// dataMode can be SPI_MODE0 or SPI_MODE3 only for MCP2515
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.setDataMode(SPI_MODE0);
	SPI.setBitOrder(MSBFIRST);
	SPI.begin();
	
	// Initialize MCP2515 CAN controller at the specified speed and clock frequency
	// (Note:  This is the oscillator attached to the MCP2515, not the Arduino oscillator)
	//speed in KHz, clock in MHz
	SCAN.setupSW(33);
	
	attachInterrupt(INT_PIN, CANHandler, FALLING);
	SCAN.InitFilters(true);
    SCAN.mode(3); //3 = Normal, 2 = HV Wake up, 1 = High Speed, 0 = Sleep

	SerialUSB.println("Ready ...");
}

byte i=0;

// CAN message frame
CAN_FRAME message;

void loop() {
	message.id = 0x340;
	message.rtr = 0;
	message.extended = 0;
	message.length = 4;
	message.data.byte[0] = 0x23;
	message.data.byte[1] = 0xFE;
	message.data.byte[2] = 0x1D;
	message.data.byte[3] = 0x7A;
	SCAN.EnqueueTX(message);
	delay(2000);
	message.id = 0x100FFEE;
	message.rtr = 0;
	message.extended = 1;
	message.length = 6;
	message.data.byte[0] = 0x23;
	message.data.byte[1] = 0xFE;
	message.data.byte[2] = 0x1D;
	message.data.byte[3] = 0x7A;
	message.data.byte[4] = 0x1D;
	message.data.byte[5] = 0x7A;
	SCAN.mode(2); //use HV Wakeup sending
	SCAN.EnqueueTX(message); //send it
	delay(5); //wait a bit to make sure it was sent before ending HV Wake up
	SCAN.mode(3); //go back to normal mode
	delay(2000);
}
