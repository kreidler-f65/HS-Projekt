//*******************************************************************************************************************************************************************************
//Bestimmung von Vcc durch nachmessen von 2.5V Referenz
//*******************************************************************************************************************************************************************************

double measuringVcc(){
  double Vcc;
  Vcc=2.5/analogRead(VREF)*1023;
  return Vcc;
  }


//*******************************************************************************************************************************************************************************
// Akku Überwachung: Ausgabe in einer Zeile des LCD Displays der aktuellen Spannung und des aktuellen Zustandes in Voll, Laden und Leer. Dieser Zustand wird auch zurückgegeben.
//*******************************************************************************************************************************************************************************
int battservice (int tmpRow){

  int tempReadVolt = analogRead(BATT_SPG);
  float tempVolts = tempReadVolt * measuringVcc() / 1023*3  ;
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
//  bool M_Force_high = false;
//  while(M_Force_high==false){
//    if(digitalRead(M_FORCE_control)==HIGH){
      unsigned long RotateTime = (pulseIn(VOB, HIGH) + pulseIn(VOB, LOW))*120;
//      M_Force_high=true;
      int rpm = (1/(RotateTime*0.000001))*60;                    //berechnung Drehzahl in Umdrehungen pro Minute
      return rpm;
 //     }
//    }
  }


//********************************************************************************************************************************************************************************
//Rückgabe des aktuellen Stromes in Ampere
//********************************************************************************************************************************************************************************
  
double RotationCurrent (){
  bool M_Force_high = false;
  int mVperAmp = 185; 
  int measuredvalue= 0;
  int ACSoffset; 
  double Voltage = 0;
  double Amps = 0;
  int tmpValue = 0;
  ACSoffset=measuringVcc()/2;
//  while(M_Force_high==false){
//    if(digitalRead(M_FORCE_control)== HIGH){
    M_Force_high=true;
    int i;
    for(i = 0; i<=10; i++){                                          //10 Messwerte bestimmen und aufsummieren
      tmpValue = tmpValue + analogRead(STROM_MESS);
      }
    measuredvalue=tmpValue/i;                                        //Mittelwert bestimmen   
    Voltage = measuredvalue * measuringVcc() / 1023 ;           //gemessene Spannung bestimmen
    Amps = ((Voltage - ACSoffset) / mVperAmp);                     //Strom ausrechnen
    Serial.print("Volt: ");
    Serial.print(Voltage);
    return Amps;
//    } 
 // }

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
