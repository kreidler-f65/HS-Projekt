void driveMenu (){
  int battstate = battservice(1);
  if(battstate==0){
    Break();
    lcd.setCursor(0,2);
    lcd.print("Batterie laden!     ");
    delay(1000);
    return;
    }
//   Serial.print("\t tmpRPM: ");
//   Serial.print(tmpRPM);
//   Serial.print("\t tmpRPM: ");
//   Serial.print(tmpRPM);
//   Serial.print("\t tmpRPM: ");
//   Serial.print(tmpRPM);
//   Serial.print("\t Test1 ");
//   Serial.print(tmpRPM);


  int tmpMulti= RPMMULTI*CURRENTMULTI;
  int setvalue = ((RPM*RPMMULTI)+(CURRENT*CURRENTMULTI))/(RPMMULTI*CURRENTMULTI);

  int tmpRPM = RotationSpeed ();
   Serial.print("\t tmpRPM: ");
   Serial.print(tmpRPM);
  int tmpCurrent = RotationCurrent();
   Serial.print("\t tmpCurrent: ");
   Serial.print(tmpCurrent);
  int actualvalue = ((tmpRPM*RPMMULTI)+(tmpCurrent*CURRENTMULTI))/tmpMulti;
   Serial.print("\t setvalue: ");
   Serial.print(setvalue);
   Serial.print("\t actualvalue: ");
   Serial.print(actualvalue);  
    lcd.setCursor(0,2);
    lcd.print("RPM:        I:      ");
    lcd.setCursor(5,2);  
    lcd.print(tmpRPM);
    lcd.setCursor(15,2);  
    lcd.print(tmpCurrent);
    
  if(kSpeed==0){
    analogWrite(M_FORCE,Speed);
    kSpeed = setvalue-actualvalue;
    }
    
   else if (kSpeed<0){
     if(kSpeed<-8){
       Speed=Speed+6;
       }
     else if(kSpeed<-4){
       Speed=Speed+3;
       }
     else {
       Speed++;
       }
    
    Speed = min(Speed,255);
    analogWrite(M_FORCE,Speed);
    kSpeed = setvalue-actualvalue;
    }
   else if (kSpeed>0){
     if(kSpeed<-8){
       Speed=Speed-14;
       }
     else if(kSpeed>4){
       Speed=Speed-8;
       }
     else {
       Speed--;
       Speed--;
       }
    Speed = max(Speed,1);
    analogWrite(M_FORCE,Speed);
    kSpeed = setvalue-actualvalue;
    }
   Serial.print("\t kSpeed: ");
   Serial.print(kSpeed);
   Serial.print("\t Speed: ");
   Serial.print(Speed);
  return;
  }

