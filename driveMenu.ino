void driveMenu (){
  int battstate = battservice(1);
//  if(battstate==0){
//    Break();
//    lcd.setCursor(0,2);
//    lcd.print("Batterie laden!     ");
//    delay(1000);
//    return;
//    }
//   //  Serial.print("\t tmpRPM: ");
//   Serial.print(tmpRPM);
//   Serial.print("\t tmpRPM: ");
//   Serial.print(tmpRPM);
//   Serial.print("\t tmpRPM: ");
//   Serial.print(tmpRPM);
//   Serial.print("\t Test1 ");
//   Serial.print(tmpRPM);


  int tmpMulti= RPMMULTI+CURRENTMULTI;
  int setvalue = ((RPM*RPMMULTI)+(CURRENT*CURRENTMULTI))/(tmpMulti);

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
    kSpeed = setvalue-actualvalue;
    }
    
  else if (kSpeed<0){                        //Geschwindigkeit erhöhen
     if(kSpeed<-16){
       Speed=Speed+12;
       }
     else if(kSpeed<-8){
       Speed=Speed+6;
       }
     else if(kSpeed<-4){
       Speed=Speed+3;
       }
     else {
       Speed++;
       }
     }
     
  else if (kSpeed>0){                         //Geschwindigkeit verringern
     if(kSpeed<-16){
       Speed=Speed-28;
       }
     else if(kSpeed<-8){
       Speed=Speed-14;
       }
     else if(kSpeed>4){
       Speed=Speed-8;
       }
     else {
       Speed--;
       Speed--;
       }
     }      
  Speed = min(Speed,255);
  Speed = max(Speed,1);
  analogWrite(M_FORCE,Speed);                // Gegenkraft anpassen
  kSpeed = setvalue-actualvalue;
 
     Serial.print("\t kSpeed: ");
     Serial.print(kSpeed);
     Serial.print("\t Speed: ");
     Serial.print(Speed);
   
   int DriveSpeed = kSpeed-Speed+1;                //Fahrgeschwindigkeit berechnen
   DriveSpeed = max(DriveSpeed,0);
   DriveSpeed= map(DriveSpeed,setvalue,0,0,255);
     Serial.print("\t DriveSpeed: ");
     Serial.print(DriveSpeed);
   Drive(DriveSpeed);
    
   
   
  return;
  }

