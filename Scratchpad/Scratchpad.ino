// btn1 = 14, btn2 = 13, btn3 = 11, btn4 = 7, btnnone = 15  This is just a note to remind me of the integer values of the buttons for the Olimex display.  Hopefully this doesn't change between displays.
#include <LCD16x2.h>
#include <Wire.h>
#include <SPI.h>

LCD16x2 lcd;                       //Tell the library what kind of display it is

char * Str1[2][39] = { {"-40", "-35", "-30", "-25", "-20", "-15", "-10", "-5 ", "0 ", "5 ", "10 ", "15 ", "20 ", "25 ", "30 ", "35 ", "40 ", "45 ", "50 ", "55 ", "60 ", "65 ", "70 ", "75 ", "80 ", "85 ", "90 ", "95 ", "100", "105", "110", "115", "120", "125", "130", "135", "140", "145", "150"
},{"195.65", "148.17", "113.35", " 87.56", " 68.24", " 53.65", " 42.51", " 33.89", " 27.22", " 22.02", " 17.93", " 14.67", " 12.08", " 10.00", "  8.31", "  6.95", "  5.83", "  4.92", "  4.16", "  3.54", "  3.01", "  2.59", "  2.23", "  1.92", "  1.67", "  1.45", "  1.27", "  1.11", "  0.97", "  0.86", "  0.76", "  0.67", "  0.6", "  0.53", "  0.47", "  0.42", "  0.38", "  0.34", "  0.31"
} };                               //the array that makes the magic happen.  Edit this as needed to update the temperatures

int arrayPos   = 13;                //starting position of the array

int buttons;                       //initiallize the buttons variable as an integer

void setup() {
 Wire.begin();                     // start the library
 lcd.lcdClear();                   // Clear the LCD
 lcd.lcdGoToXY(0,0);               // Move the cursor to the 0w0 wat's this position
 lcd.lcdWrite("Temp :     Deg C"); // Printing the permanent messages.  These won't change unless something is written over their position. 
 lcd.lcdGoToXY(12,2);
 lcd.lcdWrite("K Ohm");            // "" 
 lcd.lcdSetBlacklight(100);        // set the backlight, 0-255

}
void loop() {
  lcd.lcdGoToXY(7,1);
  lcd.lcdWrite(Str1[0][arrayPos]);  // Displays the selected temperature in the array, correlated with the resistance.
  lcd.lcdGoToXY(1,2);
  buttons = lcd.readButtons();      // Actually reading the buttons on the display
      switch (buttons)
  {
    case 11:
     {
      if(arrayPos == 38){           // Prevents it from reading past the end of the array, which has some fun results.
      lcd.lcdWrite("Hi ");
      delay(1000);
      return;
     }
     lcd.lcdWrite("+5");
     delay(200);
     ++arrayPos;
          break;
     }
   case 13:
     {
     if(arrayPos == 0){           // Prevents it from reading past the end beginning of the array, which has some fun results.
      lcd.lcdWrite("Lo ");
      delay(1000);
      break;
     }
     lcd.lcdWrite("-5");
     delay(200);
     --arrayPos;
          break;
     }
   case 14:
     {
     if(arrayPos == 0){
      lcd.lcdWrite("Lo ");
      delay(1000);
      break;
     }
     lcd.lcdWrite("-5");
     delay(200);
     --arrayPos;
          break;
     }
   case 7:
     {
      if(arrayPos == 38){
      lcd.lcdWrite("Hi ");
      delay(1000);
      return;
     }
     lcd.lcdWrite("+5");
     delay(200);
     ++arrayPos;
          break;
     }
   case 15:
     {
      lcd.lcdWrite("   ");
      break;
  }
}
lcd.lcdGoToXY(4,2);
lcd.lcdWrite(Str1[1][arrayPos]);        // Displays the selected resistance in the array, correlated with the temperature.
}
