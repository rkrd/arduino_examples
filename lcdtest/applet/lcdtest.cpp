#include "Arduino.h"
#ifdef __cplusplus
extern "C" void __cxa_pure_virtual(void) { while(1); }
#endif

/* 
 *  20 character 4 line I2C Display
 *  Backpack Interface labelled "LCM1602 IIC  A0 A1 A2"
 */

#include <Wire.h>
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


void setup()
{
	Serial.begin(9600);

    // initialize the lcd for 20 chars 2 lines and turn on backlight
	lcd.begin(20,2);

	for(int i = 0; i< 3; i++) {
		lcd.backlight();
		delay(250);
		lcd.noBacklight();
		delay(250);
	}
	lcd.backlight();

	lcd.setCursor(3,0);
	lcd.print("Hello, world!");
	delay(1000);
	// Wait and then tell user they can start the Serial Monitor and type in characters to
	// Display. (Set Serial Monitor option to "No Line Ending")
	lcd.setCursor(0,0);
	lcd.print("Start Serial Monitor");
	lcd.setCursor(0,1);
	lcd.print("Type chars 2 display");   


}

void loop()
{
    // when characters arrive over the serial port...
    if (Serial.available()) {
        delay(100);
        lcd.clear();
        while (Serial.available() > 0) {
            lcd.write(Serial.read());
        }
    }
}
#include <Arduino.h>

int main(void)
{
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();
    
	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}
        
	return 0;
}

