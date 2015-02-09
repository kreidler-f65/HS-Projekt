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


int RotationSpeed (){
  RotateSpeedCount = 0;
  PCintPort::attachInterrupt(VOB,RotationCount,RISING );  //Interupt von VOA aktivieren                                       
  delay(500);                                             //Warten
  PCintPort::detachInterrupt(VOB);                        //Interupt von VOA deaktivieren 
  int rps = 0;
  rps = (RotateSpeedCount/(0.5*120));                    //berechnung Drehzahl in Umdrehungen pro Minute
  return rps;
  }


void RotationCount (){
  RotateSpeedCount++;
  }
 
 void RotationCurrent (){
   
pinMode(M_FORCE,OUTPUT);
digitalWrite(M_FORCE, HIGH);

int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double Amps = 0;
int tmpRawValue = 0;
int i = 0;
for(i=0; i<=20; i++){
 
 tmpRawValue = tmpRawValue + analogRead(STROM_MESS);
 
 }
 RawValue=tmpRawValue/i;
 Voltage = (RawValue / 1023.0) * 5000; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp);
 
 
 Serial.print("Raw Value = " ); // shows pre-scaled value 
 Serial.print(RawValue); 
 Serial.print("\t mV = "); // shows the voltage measured 
 Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("\t Amps = "); // shows the voltage measured 
 Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
 return;  
   }
  
