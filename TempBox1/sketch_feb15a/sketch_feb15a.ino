#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

char * Str1[][5] = { {"-40", "-35", "0", "35", "40"},{"195K", "148K", "27K", "7K", "6K"} };
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnUP     1
#define btnDOWN   2
#define btnNONE   5
int arrayPos    = 2;
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
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Array"); // print a simple message
 Serial.begin(2400);
}

void loop() {
lcd.setCursor(6,0);            // move cursor to first line "o" and 6 spaces over
lcd.print(Str1[1][arrayPos]);

lcd.setCursor(0,1);
 lcd_key = read_LCD_buttons(); 
 switch (lcd_key)
 {
   case btnUP:
     {
     lcd.print("Plus  5");
     arrayPos ++ 1;
     delay(100);
     break;
     }
   case btnDOWN:
     {
     lcd.print("Minus 5");
     arrayPos -- 1;
     delay(100);
     break;
     }
   case btnNONE:
     {
      lcd.print("Nothing");
      break;
     }

}
}
