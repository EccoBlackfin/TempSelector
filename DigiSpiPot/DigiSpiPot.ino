// include the SPI library:
#include <SPI.h>


// set pins as the slave select for the digital pots:
const int slave100k = 4;
const int slave10k1 = 5;
const int slave10k2 = 6;

void setup() {
  // set the SelectPins as outputs:
  pinMode(slave100k, OUTPUT);
  pinMode(slave10k1, OUTPUT);
  pinMode(slave10k2, OUTPUT);
  
  // initialize SPI:
  SPI.begin();
}

void loop() {
  for (int channel = 0; channel < 2; channel++) {
    // change the resistance on this channel from min to max:
    for (int level = 0; level < 255; level++) {
      digitalPotWrite(channel, level);
      delay(10);
    }
    // wait a second at the top:
    delay(100);
    // change the resistance on this channel from max to min:
    for (int level = 0; level < 255; level++) {
      digitalPotWrite(channel, 255 - level);
      delay(10);
    }
  }

}
// This is the 100K pot section
void dig100kWrite(int address, int value) {
  digitalWrite(slave100k, LOW);  //select the 100k pot
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(slave100k, HIGH);
}
void dig10k1Write(int address, int value) {
  digitalWrite(slave10k1, LOW);  //select the first 10k pot
  byte command = 0xB0; //0xB0 = 10110000 
  command += address; 
  SPI.transfer(command); 
  byte byte1 = (value >> 8);
  byte byte0 = (value & 0xFF);
  SPI.transfer(byte1);
  SPI.transfer(byte2);
  digitalWrite(slave10k1, LOW)
}

/*
  void digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
*/
}
