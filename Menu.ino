//**********************************************************************************************************************************************************************************
//Einstellungs Menü
//**********************************************************************************************************************************************************************************
void setupMenu(){
  Break();
  nointerrupts();
  int maxMenu=5;                                   //Maximale Menü Einträge
  int Count = 1;
  char tmpKey;
  char tmpKeyA;
  char tmpKeyB;
  lcd.setCursor(0,3);
  lcd.print("left: *    right: # ");
  while (1){
    if (Count==0){
      Count=maxMenu;
      }
    else if (Count>maxMenu){
      Count=1;
      }
//   tmpKey = customKeypad.waitForKey();
   tmpKey = customKeypad.getKey();
//   if(tmpKeyB){
//     tmpKey = tmpKeyB;
//     }
    switch(tmpKey){
      case '*':
        Count--;
        break;
      case '#':
        Count++;
        break;
      default: break;
      }
//    Serial.print("\n Count: ");
//    Serial.print(Count);
//    Serial.print("\t tmpKey: ");
//    Serial.print(tmpKey);
//    Serial.print("\t tmpKeyA: ");
//    Serial.print(tmpKeyA);
    switch(Count){
      case 1:
        lcd.setCursor(0,2);
        lcd.print("Menu 1              ");
        break;
     
      case 2:
        lcd.setCursor(0,2);
        lcd.print("Menu 2              ");
        break;
      
      case 3:
        lcd.setCursor(0,2);
        lcd.print("Menu 3              ");
        break;
      
      case 4:
        lcd.setCursor(0,2);
        lcd.print("Menu 4              ");
        break;
      
      case 5:
        lcd.setCursor(0,2);
        lcd.print("Back press A        ");
        tmpKeyA = customKeypad.getKey();
        if(tmpKeyA == 'A'){
          interrupts(); 
          return;
           }
        else if(tmpKeyA == '*'){
            Count--;
            }
        else if(tmpKeyA == '#'){
            Count++;
            }
  

//          else {
//            tmpKey = tmpKeyA;
//                Serial.print("\t tmpKey1: ");
//      Serial.print(tmpKey);
//      Serial.print("\t tmpKeyA1: ");
//      Serial.print(tmpKeyA);
//            }   
//          
           
        break;
      } 
 //  delay(500);   
    }

 }
