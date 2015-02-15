#include <PinChangeInt.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

 //Pins setup
 //Analog
 const int VREF = 0;
 const int BATT_SPG = 1;
 const int STROM_MESS = 2;
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
 const int M_FORCE_control = 9;

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


//Adressen EEprom

const int adrPW = 0; //unsigned int daher Adresse 0 und 1
const int adrMAXSPEED =2;
const int adrRPM =3;
const int adrRPMMULTI =4;
const int adrCURRENT =5;
const int adrCURRENTMULTI =6;
const int adrDIREKTION=7;


 //Variablen
 int battstate = 0; //Batteriestatus 0=Leer, 1=Laden, 2=Voll
 int Speed = 1;
 int kSpeed = 0;
 int tmpdirection = -1;
 int CountH = 1;
 int maxMenuH=2;  
 char Key;
 int MAXSPEED=0;
 int RPM;
 int RPMMULTI;
 int CURRENT;
 int CURRENTMULTI;
 int DIRECTION;
 int directioncount=0;
 float messdirection=0;
 boolean Brakeaktive=false; 


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
  pinMode(M_FORCE_control,INPUT);
  pinMode(M_FORCE,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.begin(20,4);
  lcd.clear();
//bootscreen(3);              //Übergabe der Anzeigezeit in sek.
  Serial.begin(9600);
  attachInterrupt(Funk3_int, EmergBreak, RISING);
  attachInterrupt(Funk4_int, EmergRoll, RISING);
  attachInterrupt(Funk1_int, EmergDrivFor, RISING);
  attachInterrupt(Funk2_int, EmergDrivBack, RISING);
  analogWrite(M_FORCE,Speed);
  
  MAXSPEED=EEPROM.read(adrMAXSPEED);                                        //Einstellungnen aus EEPROM laden
  RPM=EEPROM.read(adrRPM);
  RPMMULTI=EEPROM.read(adrRPMMULTI);
  CURRENT=EEPROM.read(adrCURRENT);
  CURRENTMULTI=EEPROM.read(adrCURRENTMULTI);
  DIRECTION=EEPROM.read(adrDIREKTION); 
}

void loop() {
  
      if (CountH==0){
      CountH=maxMenuH;
      }
    else if (CountH>maxMenuH){
      CountH=1;
      }
//   Serial.print("\t Key Vor: ");
// Serial.print(Key);
   Key = customKeypad.getKey();
    switch(Key){
      case '*':
        CountH--;
        break;
      case '#':
        CountH++;
        break;
      default: break;
      }

  switch(CountH) {

  case 1:
    lcd.setCursor(0,0);
    lcd.print("Drive:              ");
    lcd.setCursor(0,3);
    lcd.print("left: *    right: # ");
    driveMenu();
    break;

  case 2:
    lcd.setCursor(0,0);
    lcd.print("Setup:              ");
    battservice(1);
    lcd.setCursor(0,2);
    lcd.print("Enter Setup press D ");
    lcd.setCursor(0,3);
    lcd.print("left: *    right: # ");
    Serial.print("\t Key: ");
    Serial.print(Key);
    if(Key=='D'){
      setupMenu();
      }

    break;
  }

Serial.print("\n"); // new line

}
