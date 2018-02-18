#include <SPI.h>

set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;

void setup() {

  pinMode(slaveSelectPin, OUTPUT);

  SPI.begin();
}

void loop() {

  for (int channel = 0; channel < 6; channel++) {

    for (int level = 0; level < 255; level++) {
      digitalPotWrite(channel, level);
      delay(10);
    }

    delay(100);

    for (int level = 0; level < 255; level++) {
      digitalPotWrite(channel, 255 - level);
      delay(10);
    }
  }

}

void digitalPotWrite(int address, int value) {

  digitalWrite(slaveSelectPin, LOW);

  SPI.transfer(address);
  SPI.transfer(value);

  digitalWrite(slaveSelectPin, HIGH);
}