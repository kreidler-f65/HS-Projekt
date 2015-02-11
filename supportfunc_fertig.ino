//*******************************************************************************************************************************************************************************
//Bestimmung von Vcc durch nachmessen von 2.5V Referenz
//*******************************************************************************************************************************************************************************

double  measuringVcc(){
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
unsigned long RotationSpeed (){
  unsigned long RotateTime = 0;
  digitalWrite(M_FORCE, LOW);                                          //definierte Kraft auf dem Motor
  RotateTime = (pulseIn(VOB, HIGH) + pulseIn(VOB, LOW))*120;
  analogWrite(M_FORCE, Speed);                                         //Rückschalten auf eingestellte Kraft

  unsigned long rpm = (1/(RotateTime*0.000001))*60;                    //berechnung Drehzahl in Umdrehungen pro Minute
  return rpm;
  }


//********************************************************************************************************************************************************************************
//Rückgabe des aktuellen Stromes in Ampere
//********************************************************************************************************************************************************************************
  
double RotationCurrent (){
  double  Vcc = measuringVcc();
  double  mVperAmp = 185; 
  double  measuredvalue=0;
  double  ACSoffset= Vcc/2; 
  double  Voltage = 0;
  double Amps = 0;
  double  tmpValue = 0;
  
  int M_FORCE_control_old = digitalRead(M_FORCE_control);
  while(1){                                                                  //Warten auf steigende Flanke
    if(M_FORCE_control_old==0 && digitalRead(M_FORCE_control)==1){
      break;
      }    
    M_FORCE_control_old = digitalRead(M_FORCE_control);
    }

  int i;
  for(i = 0; i<=10; i++){                                          //10 Messwerte bestimmen und aufsummieren
    tmpValue = tmpValue + analogRead(STROM_MESS);
    }
  measuredvalue=(tmpValue/i)+3;                                        //Mittelwert bestimmen   
  Voltage = measuredvalue * Vcc / 1023 ;           //gemessene Spannung bestimmen
  Amps = ((Voltage - ACSoffset) / mVperAmp);                     //Strom ausrechnen
//  Serial.print("\t mVolt: ");
//  Serial.print(Voltage);
//  Serial.print("\t messuredValue: ");
//  Serial.print(measuredvalue);
//  Serial.print("\t Amps: ");
//  Serial.print(Amps);
  return Amps;
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
//********************************************************************************************************************************************************************************

int rotating_direction(){
  unsigned long time = millis();
  int oldVOB = digitalRead(VOB);
  int tmpVOB;
  int buffVOA[4] = {0, 0, 0, 0};
  int i;
  int x;
  int a;
  for(a=0; a<=1; a++){
    for(i=3; i>=0; i--){
      x=i-1;
      if(i>0){
        buffVOA[i]= buffVOA[x];
        }
      if(i==0){
        buffVOA[0]=digitalRead(VOA);
        }
      }
    }   
  
  
  while(1){                                                                  //Warten auf steigende Flanke
          Serial.print("\t [0]: ");
  Serial.print(buffVOA[0]);
        Serial.print("\t [1]: ");
  Serial.print(buffVOA[1]);
        Serial.print("\t [2]: ");
  Serial.print(buffVOA[2]);
        Serial.print("\t [3]: ");
  Serial.print(buffVOA[3]);
    tmpVOB = digitalRead(VOB);
    if(buffVOA[3]==0 && buffVOA[2]==0 && buffVOA[1]==1 && buffVOA[0]==1 && tmpVOB==0 && oldVOB==0 ){
      return 1;
      }    
    if(buffVOA[3]==0 && buffVOA[2]==0 && buffVOA[1]==1 && buffVOA[0]==1 && tmpVOB==1 && oldVOB==1){
      return 2;
      }


    if(millis()-time<=200){
      return 0;
      }  
   
   oldVOB = tmpVOB;   
    for(i=3; i>=0; i--){
      x=i-1;
      if(i>0){
        buffVOA[i]= buffVOA[x];
        }
      if(i==0){
        buffVOA[0]=digitalRead(VOA);
        }
      }
    }
  }
