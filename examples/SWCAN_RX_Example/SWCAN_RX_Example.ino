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
    SCAN.mode(3);

	SerialUSB.println("Ready ...");
}

byte i=0;

// CAN message frame (actually just the parts that are exposed by the MCP2515 RX/TX buffers)
CAN_FRAME message;

void loop() {
	
	if (SCAN.GetRXFrame(message)) {
		// Print message
		SerialUSB.print("ID: ");
		SerialUSB.println(message.id,HEX);
		SerialUSB.print("Extended: ");
		if(message.extended) {
			SerialUSB.println("Yes");
		} else {
			SerialUSB.println("No");
		}
		SerialUSB.print("Length: ");
		SerialUSB.println(message.length,DEC);
		for(i=0;i<message.length;i++) {
			SerialUSB.print(message.data.byte[i],HEX);
			SerialUSB.print(" ");
		}
		SerialUSB.println();
		SerialUSB.println();
	}
}
