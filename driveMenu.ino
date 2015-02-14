void driveMenu (){
  int battstate = battservice(1);
  if(battstate==0){
    Break();
    lcd.setCursor(0,2);
    lcd.print("Batterie laden!!!   ");
    return;
    }
  
  long setvalue = RPM*RPMMULTI+CURRENT*CURRENTMULTI;
  int tmpRPM = RotationSpeed ();
  int tmpCurrent = RotationCurrent ();
  long actualvalue = tmpRPM*RPMMULTI+tmpCurrent*CURRENTMULTI;
   Serial.print("\t setvalue: ");
   Serial.print(setvalue);
   Serial.print("\t actualvalue: ");
   Serial.print(actualvalue);  
  
  
  if(kSpeed==0){
    analogWrite(M_FORCE,Speed);
    kSpeed = setvalue-actualvalue;
    }
    
   else if (kSpeed<0){
    Speed++;
    analogWrite(M_FORCE,Speed);
    kSpeed = setvalue-actualvalue;
     
     
     }
   else if (kSpeed>0){
    Speed--;
    analogWrite(M_FORCE,Speed);
    kSpeed = setvalue-actualvalue;
     }
   Serial.print("\t kSpeed: ");
   Serial.print(kSpeed);
  return;
  }

