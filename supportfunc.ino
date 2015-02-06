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
  delay(250);                                             //Warten
  PCintPort::detachInterrupt(VOB);                        //Interupt von VOA deaktivieren 
  int rpm = 0;
  rpm = (RotateSpeedCount/(0.25*120))*60;                    //berechnung Drehzahl in Umdrehungen pro Minute
  return rpm;
  }


void RotationCount (){
  RotateSpeedCount++;
  }
  
  
