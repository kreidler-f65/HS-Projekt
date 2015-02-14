//**********************************************************************************************************************************************************************************
//Einstellungs Menü
//**********************************************************************************************************************************************************************************
void setupMenu(){
 
//Password abfrage und uberprüfung  
 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Setup:              "); 
  lcd.setCursor(0,2);
  lcd.print("PW:                 ");
  lcd.setCursor(0,1);
  lcd.print("Password eingeben   ");
  lcd.setCursor(0,3);
  lcd.print("            Enter: D");

  unsigned int passwordsoll= eepromReadunsignedInt(adrPW);
  unsigned int Passwortist = readNumber('D', 4, 2);
  
  if(passwordsoll==Passwortist){
    lcd.setCursor(0,1);
    lcd.print("Password ok         ");
    lcd.setCursor(0,2);
    lcd.print("                    ");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("                    ");
    }
  else{
    lcd.setCursor(0,1);
    lcd.print("Password falsch         ");
    lcd.setCursor(0,2);
    lcd.print("                    ");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("                    ");
    return;
    }
  
   Break();                                        //Bremsen
  int maxMenu=8;                                   //Maximale Menü Einträge
  int Count = 1;
  char tmpKey='D';
  char tmpKeyA;
  char tmpKeyB;
  
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print("                    ");
  lcd.setCursor(0,3);
  lcd.print("l: *  r: #  Enter: D");
  while(tmpKey != NO_KEY){
    tmpKey = customKeypad.getKey();
    }

  while (1){
    
    MAXSPEED=EEPROM.read(adrMAXSPEED);                                        //Einstellungnen aus EEPROM laden
    RPM=EEPROM.read(adrRPM);
    RPMMULTI=EEPROM.read(adrRPMMULTI);
    CURRENT=EEPROM.read(adrCURRENT);
    CURRENTMULTI=EEPROM.read(adrCURRENTMULTI);
    DIRECTION=EEPROM.read(adrDIREKTION); 
    
    if (Count==0){
      Count=maxMenu;
      }
    else if (Count>maxMenu){
      Count=1;
      }

   tmpKey = customKeypad.getKey();

    switch(tmpKey){
      case '*':
        Count--;
        break;
      case '#':
        Count++;
        break;
      default: break;
      }

    switch(Count){
      case 1:
        lcd.setCursor(7,0);
        lcd.print("PW einstellen");
        if(tmpKey=='D'){
          unsigned int tmpPasswort=0;
          lcd.setCursor(0,1);
          lcd.print("PW: 0-65535 eingeben");
          lcd.setCursor(0,2);
          lcd.print("PW: ");
          lcd.setCursor(0,3);
          lcd.print("            Enter: D");
                   
          tmpPasswort = readNumber('D', 4, 2);
          lcd.setCursor(0,1);
          lcd.print("PW:        OK?      ");          
          lcd.setCursor(4,1);
          lcd.print(tmpPasswort);
          lcd.setCursor(0,2);
          lcd.print("                    ");    
          lcd.setCursor(0,3);
          lcd.print("OK: A   ESC: all Key");
          tmpKey = customKeypad.waitForKey();
          if(tmpKey=='A'){                                          //Password in EEprom speichen
            eepromWriteunsignedInt(adrPW, tmpPasswort);
            lcd.setCursor(0,1);
            lcd.print("Password gespeichert");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
            }
          else{
            lcd.setCursor(0,1);
            lcd.print("Vorgang Abgebrochen ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
            }
          lcd.setCursor(0,3);
          lcd.print("l: *  r: #  Enter: D");
                
          }
        break;
     
      case 2:
      lcd.setCursor(7,0);
        lcd.print("Max Speed    ");
        if(tmpKey=='D'){
          unsigned int tmpMAXSPEED=0;
          byte tmpMAXSPEEDbyte;
          lcd.setCursor(0,1);
          lcd.print("Max: 0-255 eingeben ");
          lcd.setCursor(0,2);
          lcd.print("Max: ");
          lcd.setCursor(0,3);
          lcd.print("old:        Enter: D");
          lcd.setCursor(5,3);
          lcd.print(MAXSPEED);
          
          tmpMAXSPEED = readNumber('D', 5, 2);
          if(tmpMAXSPEED>255){
              tmpMAXSPEED=255;
              }
          tmpMAXSPEEDbyte=lowByte(tmpMAXSPEED);
          lcd.setCursor(0,1);
          lcd.print("Speed:        OK?   ");          
          lcd.setCursor(8,1);
          lcd.print(tmpMAXSPEEDbyte);
          lcd.setCursor(0,2);
          lcd.print("                    ");    
          lcd.setCursor(0,3);
          lcd.print("OK: A   ESC: all Key");
          tmpKey = customKeypad.waitForKey();
          if(tmpKey=='A'){            //Password in EEprom speichen

            eepromWriteunsignedInt(adrMAXSPEED, tmpMAXSPEEDbyte);
            lcd.setCursor(0,1);
            lcd.print("MaxSpeed gespeichert");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
            }
          else{
            lcd.setCursor(0,1);
            lcd.print("Vorgang Abgebrochen ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
              }
            }
          lcd.setCursor(0,3);
          lcd.print("l: *  r: #  Enter: D");
        break;
      
      case 3:
        lcd.setCursor(7,0);
        lcd.print("rpm          ");
        
        if(tmpKey=='D'){
          unsigned int tmpRPM=0;
          byte tmpRPMbyte;
          lcd.setCursor(0,1);
          lcd.print("rpm: 0-255 eingeben ");
          lcd.setCursor(0,2);
          lcd.print("rpm: ");
          lcd.setCursor(0,3);
          lcd.print("old:        Enter: D");
          lcd.setCursor(5,3);
          lcd.print(RPM);
          tmpRPM = readNumber('D', 6, 2);
          if(tmpRPM>255){
              tmpRPM=255;
              }
          tmpRPMbyte=lowByte(tmpRPM);
          lcd.setCursor(0,1);
          lcd.print("rpm:        OK?     ");          
          lcd.setCursor(6,1);
          lcd.print(tmpRPMbyte);
          lcd.setCursor(0,2);
          lcd.print("                    ");    
          lcd.setCursor(0,3);
          lcd.print("OK: A   ESC: all Key");
          tmpKey = customKeypad.waitForKey();
          if(tmpKey=='A'){            //Password in EEprom speichen

            eepromWriteunsignedInt(adrRPM, tmpRPMbyte);
            lcd.setCursor(0,1);
            lcd.print("rpm gespeichert     ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
            }
          else{
            lcd.setCursor(0,1);
            lcd.print("Vorgang Abgebrochen ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
              }
            }
          lcd.setCursor(0,3);
          lcd.print("l: *  r: #  Enter: D");
        
        break;
      
      case 4:
        lcd.setCursor(7,0);
        lcd.print("rpm multi    ");
         
        if(tmpKey=='D'){
          unsigned int tmpRPMMULTI=0;
          byte tmpRPMMULTIbyte;
          lcd.setCursor(0,1);
          lcd.print("*: 0-10 eingeben    ");
          lcd.setCursor(0,2);
          lcd.print("multi: ");
          lcd.setCursor(0,3);
          lcd.print("old:        Enter: D");
          lcd.setCursor(5,3);
          lcd.print(RPMMULTI);
          tmpRPMMULTI = readNumber('D', 8, 2);
          if(tmpRPMMULTI>10){
              tmpRPMMULTI=10;
              }
          tmpRPMMULTIbyte=lowByte(tmpRPMMULTI);
          lcd.setCursor(0,1);
          lcd.print("multi:        OK?   ");          
          lcd.setCursor(8,1);
          lcd.print(tmpRPMMULTIbyte);
          lcd.setCursor(0,2);
          lcd.print("                    ");    
          lcd.setCursor(0,3);
          lcd.print("OK: A   ESC: all Key");
          tmpKey = customKeypad.waitForKey();
          if(tmpKey=='A'){            //Password in EEprom speichen

            eepromWriteunsignedInt(adrRPMMULTI, tmpRPMMULTIbyte);
            lcd.setCursor(0,1);
            lcd.print("multi gespeichert   ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
            }
          else{
            lcd.setCursor(0,1);
            lcd.print("Vorgang Abgebrochen ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
              }
            }
          lcd.setCursor(0,3);
          lcd.print("l: *  r: #  Enter: D");
        break;
      
      case 5:
        lcd.setCursor(7,0);
        lcd.print("Current      ");
        
        if(tmpKey=='D'){
          unsigned int tmpCURRENT=0;
          byte tmpCURRENTbyte;
          lcd.setCursor(0,1);
          lcd.print("I: 0-255 eingeben    ");
          lcd.setCursor(0,2);
          lcd.print("I: ");
          lcd.setCursor(0,3);
          lcd.print("old:        Enter: D");
          lcd.setCursor(5,3);
          lcd.print(CURRENT);
          tmpCURRENT = readNumber('D', 3, 2);
          if(tmpCURRENT>255){
              tmpCURRENT=255;
              }
          tmpCURRENTbyte=lowByte(tmpCURRENT);
          lcd.setCursor(0,1);
          lcd.print("I:        OK?   ");          
          lcd.setCursor(3,1);
          lcd.print(tmpCURRENTbyte);
          lcd.setCursor(0,2);
          lcd.print("                    ");    
          lcd.setCursor(0,3);
          lcd.print("OK: A   ESC: all Key");
          tmpKey = customKeypad.waitForKey();
          if(tmpKey=='A'){            //Password in EEprom speichen

            eepromWriteunsignedInt(adrCURRENT, tmpCURRENTbyte);
            lcd.setCursor(0,1);
            lcd.print("I gespeichert");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
            }
          else{
            lcd.setCursor(0,1);
            lcd.print("Vorgang Abgebrochen ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
              }
            }
          lcd.setCursor(0,3);
          lcd.print("l: *  r: #  Enter: D");        
        
        break;

      case 6:
        lcd.setCursor(7,0);
        lcd.print("Current multi");
        
        if(tmpKey=='D'){
          unsigned int tmpCURRENTMULTI=0;
          byte tmpCURRENTMULTIbyte;
          lcd.setCursor(0,1);
          lcd.print("I*: 0-10 eingeben ");
          lcd.setCursor(0,2);
          lcd.print("I*: ");
          lcd.setCursor(0,3);
          lcd.print("old:        Enter: D");
          lcd.setCursor(5,3);
          lcd.print(CURRENTMULTI);
          tmpCURRENTMULTI = readNumber('D', 4, 2);
          if(tmpCURRENTMULTI>10){
              tmpCURRENTMULTI=10;
              }
          tmpCURRENTMULTIbyte=lowByte(tmpCURRENTMULTI);
          lcd.setCursor(0,1);
          lcd.print("I*:        OK?      ");          
          lcd.setCursor(4,1);
          lcd.print(tmpCURRENTMULTIbyte);
          lcd.setCursor(0,2);
          lcd.print("                    ");    
          lcd.setCursor(0,3);
          lcd.print("OK: A   ESC: all Key");
          tmpKey = customKeypad.waitForKey();
          if(tmpKey=='A'){            //Password in EEprom speichen

            eepromWriteunsignedInt(adrCURRENTMULTI, tmpCURRENTMULTIbyte);
            lcd.setCursor(0,1);
            lcd.print("I gespeichert       ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
            }
          else{
            lcd.setCursor(0,1);
            lcd.print("Vorgang Abgebrochen ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
              }
            }
          lcd.setCursor(0,3);
          lcd.print("l: *  r: #  Enter: D");        
        
        
        break;

      case 7:
        lcd.setCursor(7,0);
        lcd.print("Direction    ");
        
        if(tmpKey=='D'){
          unsigned int tmpDIRECTION=0;
          byte tmpDIRECTIONbyte;
          lcd.setCursor(0,1);
          lcd.print("Li: 1 Re: 2 eingeben");
          lcd.setCursor(0,2);
          lcd.print("IST: ");
          lcd.setCursor(0,3);
          lcd.print("old:        Enter: D");
          lcd.setCursor(0,3);
          lcd.print(DIRECTION);
          tmpDIRECTION = readNumber('D', 5, 2);
          tmpDIRECTION = constrain(tmpDIRECTION,1,2);
          
          tmpDIRECTIONbyte=lowByte(tmpDIRECTION);
          lcd.setCursor(0,1);
          lcd.print("IST:        OK?     ");          
          lcd.setCursor(5,1);
          lcd.print(tmpDIRECTIONbyte);
          lcd.setCursor(0,2);
          lcd.print("                    ");    
          lcd.setCursor(0,3);
          lcd.print("OK: A   ESC: all Key");
          tmpKey = customKeypad.waitForKey();
          if(tmpKey=='A'){            //Password in EEprom speichen

            eepromWriteunsignedInt(adrDIREKTION, tmpDIRECTIONbyte);
            lcd.setCursor(0,1);
            lcd.print("Direction saved     ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
            }
          else{
            lcd.setCursor(0,1);
            lcd.print("Vorgang Abgebrochen ");
            lcd.setCursor(0,2);
            lcd.print("                    ");
            lcd.setCursor(0,3);
            lcd.print("                    ");
            delay(2000);
            lcd.setCursor(0,1);
            lcd.print("                    ");
              }
            }
          lcd.setCursor(0,3);
          lcd.print("l: *  r: #  Enter: D");        
        
        
        break;
      
      case 8:
        lcd.setCursor(7,0);
        lcd.print("Back press D ");
        if(tmpKey == 'D'){
          MAXSPEED=EEPROM.read(adrMAXSPEED);                                        //Einstellungnen aus EEPROM laden
          RPM=EEPROM.read(adrRPM);
          RPMMULTI=EEPROM.read(adrRPMMULTI);
          CURRENT=EEPROM.read(adrCURRENT);
          CURRENTMULTI=EEPROM.read(adrCURRENTMULTI);
          DIRECTION=EEPROM.read(adrDIREKTION); 
          return;
          }          
        break;
      } 
    }
 }

