#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


//Tastatur

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {3, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//Display


LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

 //Pins setup
 //Analog
 const int STROM_MESS = 97;
 const int BATT_SPG = 96;
 //Digital
 const int TAST1 = 77;
 const int TAST2 = 75;
 const int TAST3 = 73;
 const int TAST4 = 71;
 const int TAST5 = 59;
 const int TAST6 = 57;
 const int TAST7 = 55;
 const int TAST8 = 53;
 
 const int VOB = 70;
 const int VOA = 51;
 
 const int M_FORCE = 17;
 
 const int SD_B = 16;
 const int IN_B = 15;
 const int SD_A = 5;
 const int IN_A = 1;
 const int INTER0 = 6;
 const int INTER1 = 7;
 const int INTER4 = 45;
 const int INTER5 = 46;

void setup() {
 lcd.init(); 
 lcd.backlight();
 lcd.begin(20,4);
 lcd.clear();
 lcd.setCursor(0,0); //Start at character 0 on line 0
 lcd.print("Use Serial Mon");
 lcd.setCursor(0,1);
 lcd.print("Type to display");
 lcd.setCursor(0,2); //Start at character 0 on line 0
 lcd.print("Use Serial Mon");
 lcd.setCursor(0,3);
 lcd.print("Type to display");

}

void loop() {
  // put your main code here, to run repeatedly:

}
