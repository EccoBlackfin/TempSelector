#include <SPI.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

char * Str1[2][39] = { {"-40", "-35", "-30", "-25", "-20", "-15", "-10", "-5", "0", "5", "10", "15", "20", "25", "30", "35", "40", "45", "50", "55", "60", "65", "70", "75", "80", "85", "90", "95", "100", "105", "110", "115", "120", "125", "130", "135", "140", "145", "150"
},{"195.65", "148.17", "113.35", "87.56", "68.24", "53.65", "42.51", "33.89", "27.22", "22.02", "17.93", "14.67", "12.08", "10", "8.31", "6.95", "5.83", "4.92", "4.16", "3.54", "3.01", "2.59", "2.23", "1.92", "1.67", "1.45", "1.27", "1.11", "0.97", "0.86", "0.76", "0.67", "0.6", "0.53", "0.47", "0.42", "0.38", "0.34", "0.31"
} };  // First row is displayed temperature, second row is displayed resistance, third row will be the actual data to be sent to the digipot

int lcd_key     = 0;
int adc_key_in  = 0;
                              // All the buttons are defined here
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnRIGHT  4
#define btnNONE   5

int tempSet      = 0;
int arrayPos1    = 0;
int arrayPos2    = 0;
int arrayPos3    = 0;
int arrayPos4    = 0;
int tempCir[2][4] = { {arrayPos1, arrayPos2, arrayPos3, arrayPos4},{1, 2, 3, 4} };
int read_LCD_buttons()                              // Read the buttons.  Since these are all on one analog port to save pins, it's actually a voltage reading from 0-1024.
{
 adc_key_in = analogRead(0);
 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 150)  return btnUP; 
 if (adc_key_in < 306)  return btnDOWN; 
 return btnNONE;
 }

void setup() {
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Temp ");
 lcd.print(tempCir[1][tempSet]);
 lcd.print(": ");           // print a simple message
 Serial.begin(2400);
}

void loop() {
lcd.setCursor(7,0);             // move cursor to first line "0" and 6 spaces over
lcd.print(Str1[0][tempCir[0][tempSet]]);   // Shows what the current temperature setting is.
lcd.print(" ");
lcd.print((char)223);           // Displays degree symbol
lcd.print("C     ");


lcd.setCursor(0,1);             // move cursor to second line, position 0
 lcd_key = read_LCD_buttons();  // What happens when each button is pushed, this is where the array position is shifted.
 switch (lcd_key)
 {
   case btnUP:
     {
      if(tempCir[0][tempSet] == 38){       // Prevents from going past the end of the array
      lcd.print("Hi ");
      delay(1000);
      return;
     }
     lcd.print("+5");
     lcd.print((char)223);
     delay(200);
     ++tempCir[0][tempSet];
          break;
     }
   case btnDOWN:
     {
     if(tempCir[0][tempSet] == 0){           // Prevents from going past the end of the array
      lcd.print("Lo ");
      delay(1000);
      break;
     }
     lcd.print("-5");
     lcd.print((char)223);
     delay(200);
     --tempCir[0][tempSet];
     break;
     }
   case btnLEFT:
     {
      if(tempSet == 0){
      break;
      }
      delay(200);
      --tempSet;
      break;
     }
   case btnRIGHT:
     {
      if(tempSet == 4){
      break;
      }
      delay(200);
      ++tempSet;
      break;
     }     
   case btnNONE:
     {
      lcd.print("   ");
      break;
     }

}
lcd.setCursor(4,1);
lcd.print(Str1[1][tempCir[0][tempSet]]);     // This is what shows you the resistance selected in the array.
lcd.print(" K");
lcd.print((char)244);                       // To display the omega symbol.
lcd.print("     ");
}
