//**********************************************************************************************************************************************************************************
//Einstellungs Menü
//**********************************************************************************************************************************************************************************
void setupMenu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Setup:              "); 
  lcd.setCursor(0,2);
  lcd.print("PW:                 ");
  lcd.setCursor(0,1);
  lcd.print("Password eingeben   ");
  lcd.setCursor(0,3);
  lcd.print("            Enter: D");


  unsigned int passwordsoll= eepromReadunsignedInt(0);
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

  
  
  // Break();
 // noInterrupts();
  int maxMenu=7;                                   //Maximale Menü Einträge
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
          if(tmpKey=='A'){
            eepromWriteunsignedInt(0, tmpPasswort);
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
        break;
      
      case 3:
        lcd.setCursor(7,0);
        lcd.print("rpm          ");
        break;
      
      case 4:
        lcd.setCursor(7,0);
        lcd.print("rpm multi    ");
        break;
      
      case 5:
        lcd.setCursor(7,0);
        lcd.print("Current      ");
        break;

      case 6:
        lcd.setCursor(7,0);
        lcd.print("Current multi");
        break;
      
      case 7:
        lcd.setCursor(7,0);
        lcd.print("Back press D ");
        if(tmpKey == 'D'){
          return;
          }          
        break;
      } 
    }
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
    for (i=Col;i<=20;i++){
      lcd.setCursor(i,Row);
      lcd.print(" ");
      }
      return number;
      }
  }
}
