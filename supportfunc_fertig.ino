//*******************************************************************************************************************************************************************************
// Akku Überwachung: Ausgabe in einer Zeile des LCD Displays der aktuellen Spannung und des aktuellen Zustandes in Voll, Laden und Leer. Dieser Zustand wird auch zurückgegeben.
//*******************************************************************************************************************************************************************************
int battservice (int tmpRow){

  int tempReadVolt = analogRead(BATT_SPG);
  float tempVolts = tempReadVolt * 5.0 / 1024.0*3  ; 
  tempVolts = tempVolts - (tempVolts*0.005);              //Korrekturwert in %
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
  RotateTime = (pulseIn(VOB, HIGH) + pulseIn(VOB, LOW))*120;
  int rpm = 0;
  rpm = (1/(RotateTime*0.000001))*60;                    //berechnung Drehzahl in Umdrehungen pro Minute
  return rpm;
  }

//********************************************************************************************************************************************************************************
//Rückgabe des aktuellen Stromes in Ampere
//********************************************************************************************************************************************************************************
  
double RotationCurrent (){
  int mVperAmp = 185; 
  int measuredvalue= 0;
  int ACSoffset = 2500; 
  double Voltage = 0;
  double Amps = 0;
  int tmpvalue = 0;
  int i = 0;
  for(i=0; i<=20; i++){                                          //20 Messwerte bestimmen und aufsummieren
    tmpvalue = tmpValue + analogRead(STROM_MESS);
    }
  measuredvalue=tmpValue/i;                                        //Mittelwert bestimmen   
  Voltage = (measuredvalue / 1023.0) * 5000; // Gets you mV           //gemessene Spannung bestimmen
  Amps = ((Voltage - ACSoffset) / mVperAmp);                     //Strom ausrechnen
  return Amps;  
  }

