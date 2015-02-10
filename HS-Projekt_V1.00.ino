#include <PinChangeInt.h>
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <math.h>

 //Pins setup
 //Analog
 const int STROM_MESS = 0;
 const int BATT_SPG = 1;
 //Digital
 const int TAST1 = 23;
 const int TAST2 = 25;
 const int TAST3 = 27;
 const int TAST4 = 29;
 const int TAST5 = 31;
 const int TAST6 = 33;
 const int TAST7 = 35;
 const int TAST8 = 37;
 
 const int VOB = 14;
 const int VOA = 15;
 
 const int M_FORCE = 8;
 
 const int SD_B = 7;
 const int IN_B = 6;
 const int SD_A = 5;
 const int IN_A = 4;
 const int Funk4_int = 0;
 const int Funk2_int = 1;
 const int Funk1_int = 4;
 const int Funk3_int = 5;
 const int Funk4 = 2;
 const int Funk2 = 3;
 const int Funk1 = 19;
 const int Funk3 = 18;
 
 
 //Variablen
 char selected = '*';
 int battstate = 0; //Batteriestatus 0=Leer, 1=Laden, 2=Voll 
 int Speed = 0;
 unsigned long starttime;
 unsigned long stoptime;
 
 bool drivefor = false;
 bool driveback = false;
 bool brake = false;
 bool roll = false;
 
 
 
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
byte rowPins[ROWS] = {TAST1, TAST2, TAST3, TAST4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {TAST5, TAST6, TAST7, TAST8}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


//Display
LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display


//lcd.print("                    ");

void setup() {
  
  pinMode(VOA,INPUT);
  pinMode(VOB,INPUT); 
  pinMode(SD_B,OUTPUT);
  pinMode(IN_B,OUTPUT);
  pinMode(SD_A,OUTPUT);
  pinMode(IN_A,OUTPUT);
   
  lcd.init(); 
  lcd.backlight();
  lcd.begin(20,4);
  lcd.clear();
//bootscreen(3);              //Übergabe der Anzeigezeit in sek.
  Serial.begin(9600);
}

void loop() {
//  battstate = battservice(2);
 pinMode(M_FORCE,OUTPUT);
  analogWrite(M_FORCE, 100);
  Speed = RotationSpeed();
// for(int i = 0; i<=255; i++){
//  DriveFor(i);
//  delay(50);
//   }
// for(int i = 255; i>=0; i--){
//  DriveFor(i);
//  delay(50);
//   }
// for(int i = 0; i<=255; i++){
//  DriveBack(i);
//  delay(50);
//   }
// for(int i = 255; i>=0; i--){
//  DriveBack(i);
//  delay(50);
//   }
//  DriveBack(200);
//  delay(1000);
//RotationCurrent();

  attachInterrupt(Funk3_int, EmergBreak, RISING);
  attachInterrupt(Funk4_int, EmergRoll, RISING);
  attachInterrupt(Funk1_int, EmergDrivFor, RISING);
  attachInterrupt(Funk2_int, EmergDrivBack, RISING);
  
  lcd.setCursor(0,1);
  lcd.print("Speed:    rpm     ");
  lcd.setCursor(7,1);
  lcd.print(Speed);
  
 switch(selected) {
  case '*':
//  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Fahren:             ");
  lcd.setCursor(0,3);
  lcd.print("Einstellungen #     ");
  break;
  
  case '#':
//  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Einstellungen:             ");
  lcd.setCursor(0,3);
  lcd.print("Fahren *            ");
  break;
  } 

selected = customKeypad.getKey();
delay(500);
Serial.print("\n"); // new line
  

}
