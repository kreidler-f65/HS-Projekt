//*******************************************************************************************************************************************************************************
//Bestimmung von Vcc durch nachmessen von 2.5V Referenz
//*******************************************************************************************************************************************************************************

double measuringVcc(){
  double  Vcc;
  double  tmpVREF = analogRead(VREF);
  Vcc=(2480/tmpVREF)*1023;
//  Serial.print("\t VREF: ");
//  Serial.print(analogRead(VREF)); 
//  Serial.print("\t Vcc: ");
//  Serial.print(Vcc);
  return Vcc;
  }


//*******************************************************************************************************************************************************************************
// Akku Überwachung: Ausgabe in einer Zeile des LCD Displays der aktuellen Spannung und des aktuellen Zustandes in Voll, Laden und Leer. Dieser Zustand wird auch zurückgegeben.
//*******************************************************************************************************************************************************************************
int battservice (int tmpRow){

  int tempReadVolt = analogRead(BATT_SPG);
  float tempVolts = tempReadVolt * measuringVcc() /1023000*3  ;
  lcd.setCursor(0, tmpRow);
  lcd.print("Spg:      V         ");
  lcd.setCursor(5, tmpRow);
  lcd.print(tempVolts);
  lcd.setCursor(15, tmpRow);
  if (tempVolts>11.6){                                   //Akku Voll
    lcd.print(" Voll");
    return 2;  
    }
  else if(11.6>tempVolts & tempVolts>11.4){              //Akku laden 
    lcd.print("Laden");
    return 1;
    }
  else if(11.4>tempVolts){                              //Akku leer    
    lcd.print(" Leer");
    return 0;
    }
}

//********************************************************************************************************************************************************************************
//Rückgabe der aktuellen Drehzahl in Umdrehungen/Minute der Kurbel
//********************************************************************************************************************************************************************************
int RotationSpeed (){
  unsigned long RotateTime = 0;
  digitalWrite(M_FORCE, LOW);                                          //definierte Kraft auf dem Motor
  RotateTime = (pulseIn(VOB, HIGH,50000) + pulseIn(VOB, LOW,50000))*120;
  analogWrite(M_FORCE, Speed);                                         //Rückschalten auf eingestellte Kraft

  unsigned long rpm = (1/(RotateTime*0.000001))*60;                    //berechnung Drehzahl in Umdrehungen pro Minute
  int rpmint =int(rpm);
  return rpmint;
  }


//********************************************************************************************************************************************************************************
//Rückgabe des aktuellen Stromes in 0-255 bei 0-5000mA
//********************************************************************************************************************************************************************************
  
int RotationCurrent (){
  double  Vcc = measuringVcc();
  double  mVperAmp = 185; 
  double  measuredvalue=0;
  double  ACSoffset= Vcc/2; 
  double  Voltage = 0;
  double Amps = 0;
  int mAmps=0;
  double  tmpValue = 0;
  int M_FORCE_control_old = digitalRead(M_FORCE_control);
  int tmpM_FORCE_control = digitalRead(M_FORCE_control);
  while(1){    //Warten auf steigende Flanke
    if(M_FORCE_control_old==0 && tmpM_FORCE_control==1){
      break;
      } 
    M_FORCE_control_old = tmpM_FORCE_control;
    tmpM_FORCE_control = digitalRead(M_FORCE_control);
    }
  int i;
  int x;
  for(x=0; x<=4; x++){
    digitalWrite(M_FORCE, HIGH); 
    for(i = 0; i<=19; i++){                                              //100 Messwerte bestimmen und aufsummieren
      tmpValue = tmpValue + analogRead(STROM_MESS);
      }
    analogWrite(M_FORCE, Speed);
    delay(10);
  }
  
  measuredvalue=(tmpValue/100)+4.5;                                       //Mittelwert bestimmen   +14 Digits korrektur
  Voltage = measuredvalue * Vcc / 1023 ;                                 //gemessene Spannung bestimmen
  Amps = ((Voltage - ACSoffset) / mVperAmp);                             //Strom ausrechnen
  Amps = abs(Amps);                                                     //Strom absolut wert
  Amps =  (int)(Amps*100)/100.0;                                   //Strom Runden 2 Nachkommastellen
  mAmps= int (Amps*1000);                                                      //Strom in mA
  mAmps = min(mAmps,2000);                                                //Strom max 5000mA
  mAmps = map(mAmps,0,2000,0,255);
  
//  Serial.print("\t mVolt: ");
//  Serial.print(Voltage);
//  Serial.print("\t messuredValue: ");
//  Serial.print(measuredvalue);
//  Serial.print("\t Vcc: ");
//  Serial.print(Vcc);
  return mAmps;
}


//********************************************************************************************************************************************************************************
//Bootscreen
//********************************************************************************************************************************************************************************
void bootscreen (int showtime){                               //Übergabe der Anzeigezeit in sek.
  lcd.setCursor(0,0);
  lcd.print("Handtrainer         ");
  lcd.setCursor(0,1);
  lcd.print("Version 1.00        ");
  lcd.setCursor(0,2);
  lcd.print("Manuel Rude         "); 
  lcd.setCursor(19,3);
  lcd.print("s");  
  while(showtime>=0){
    lcd.setCursor(18,3);
    lcd.print(showtime);
    showtime--; 
    delay(1000); 
    }
  }
  

//********************************************************************************************************************************************************************************
//Drehrichtung ermitteln   
//1=rechtsdrehen
//2=Linksdrehend
//-1 = Stop
//********************************************************************************************************************************************************************************

int rotating_direction(){
  unsigned long time = millis();
  tmpdirection = -1;
  attachPinChangeInterrupt(VOA, ISR_rotating_direction, RISING);      //Interrupt VOA aktivieren
  
  while (tmpdirection == -1){                                         //Warten auf Interrupt
    if (millis()-time>=300){                                          //Timeout
       return -1;
      }
    }
  detachPinChangeInterrupt(VOA);                                      //Interrupt VOA deaktivieren
  if  (tmpdirection == 1){                            
   return 1;
   } 
  else if(tmpdirection == 2){
   return 2;
   } 
  else{
  
   } 
}      

  
//********************************************************************************************************************************************************************************
//ISR Drehrichtung ermitteln   
//********************************************************************************************************************************************************************************

void ISR_rotating_direction(){
  int ReadVOB = digitalRead(VOB);                                      // Auswertung Zustand VOB
  if (ReadVOB ==0) {
    tmpdirection = 1;
    return;
    }
  else if (ReadVOB == 1){
    tmpdirection = 2;
    return;    
    }
  else {
    tmpdirection = -1;
    return;   
  }
  return;
}

//********************************************************************************************************************************************************************************
//Schreiben einer Intger in 2 EEprom bytes
//********************************************************************************************************************************************************************************

void eepromWriteunsignedInt(int adr, unsigned int wert) {
  byte low, high;
  low=wert&0xFF;
  high=(wert>>8)&0xFF;
  EEPROM.write(adr, low); // dauert 3,3ms 
  EEPROM.write(adr+1, high);
  return;
}

//********************************************************************************************************************************************************************************
//Lesen einer Intger aus 2 EEprom bytes
//********************************************************************************************************************************************************************************

unsigned int eepromReadunsignedInt(int adr) {
byte low, high;
  low=EEPROM.read(adr);
  high=EEPROM.read(adr+1);
  return low + ((high << 8)&0xFF00);
}

 
//**********************************************************************************************************************************************************************************
//Zahl einlesen; Übergabe der Enter Taste, Spalte und der Zeile
//**********************************************************************************************************************************************************************************
 
unsigned int readNumber(char enter, int Col, int Row){
  unsigned int number= NULL;
  char readKey;
  int i;
  for(i=Col;i<=19;i++){
    lcd.setCursor(i,Row);
    lcd.print(" ");
    }
  while(1){
    
    readKey = customKeypad.getKey();
       Serial.println("\t readKey: ");
       Serial.print(readKey);
       Serial.println("\t number: ");
       Serial.print(number);
    
    if((readKey == '0') || (readKey == '1')|| (readKey == '2')|| (readKey == '3')|| (readKey == '4')|| (readKey == '5')|| (readKey == '6')|| (readKey == '7')|| (readKey == '8')|| (readKey == '9')){                                   //erfassung Zahl                       
      lcd.setCursor(Col,Row);
      number = number * 10 + (readKey - '0');
      lcd.print(number);
      }
      
    else if (readKey == enter){
    for (i=Col;i<=19;i++){
      lcd.setCursor(i,Row);
      lcd.print(" ");
      }
      return number;
      }
  }
}
