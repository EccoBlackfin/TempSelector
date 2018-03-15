#include <SPI.h>
#include <LCD16x2.h>
#include <Wire.h>

char * Str1[2][39] = { {"-40", "-35", "-30", "-25", "-20", "-15", "-10", "-5", "0", "5", "10", "15", "20", "25", "30", "35", "40", "45", "50", "55", "60", "65", "70", "75", "80", "85", "90", "95", "100", "105", "110", "115", "120", "125", "130", "135", "140", "145", "150"
},{"195.65", "148.17", "113.35", "87.56", "68.24", "53.65", "42.51", "33.89", "27.22", "22.02", "17.93", "14.67", "12.08", "10", "8.31", "6.95", "5.83", "4.92", "4.16", "3.54", "3.01", "2.59", "2.23", "1.92", "1.67", "1.45", "1.27", "1.11", "0.97", "0.86", "0.76", "0.67", "0.6", "0.53", "0.47", "0.42", "0.38", "0.34", "0.31"
} };
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnUP     1
#define btnDOWN   2
#define btnNONE   5
int arrayPos    = 0;
// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);
 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 150)  return btnUP; 
 if (adc_key_in < 306)  return btnDOWN; 
 return btnNONE;
 }

void setup() {
 Wire.begin;              // start the library
 lcd.lcdClear
 lcd.lcdGoToXY(0,0);
 lcd.lcdWrite("Temp: "); // print a simple message
}

void loop() {
lcd.lcdGoToXY(6,0);            // move cursor to first line "o" and 6 spaces over
lcd.lcdWrite(Str1[0][arrayPos]);
lcd.lcdWrite(" ");
lcd.lcdWrite((char)223);
lcd.lcdWrite("C     ");


lcd.lcdGoToXY(0,1);
 lcd_key = read_LCD_buttons(); 
 switch (lcd_key)
 {
   case btnUP:
     {
      if(arrayPos == 38){
      lcd.lcdWrite("Hi ");
      delay(1000);
      return;
     }
     lcd.lcdWrite("+5");
     lcd.lcdWrite((char)223);
     delay(200);
     ++arrayPos;
          break;
     }
   case btnDOWN:
     {
     if(arrayPos == 0){
      lcd.lcdWrite("Lo ");
      delay(1000);
      break;
     }
     lcd.lcdWrite("-5");
     lcd.lcdWrite((char)223);
     delay(200);
     --arrayPos;
          break;
     }
   case btnNONE:
     {
      lcd.lcdWrite("   ");
      break;
     }

}
lcd.lcdGoToXY(4,1);
lcd.lcdWrite(Str1[1][arrayPos]);
lcd.lcdWrite(" K");
lcd.lcdWrite((char)244);
lcd.lcdWrite("     ");
}
