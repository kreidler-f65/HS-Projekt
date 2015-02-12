//**********************************************************************************************************************************************************************************
//Einstellungs Menü
//**********************************************************************************************************************************************************************************
void setupMenu(){
  int maxMenu=5;                                   //Maximale Menü Einträge
  int Count = 1;
  char tmpKey;
  char tmpKeyA;
  lcd.setCursor(0,3);
  lcd.print("left: *    right: # ");
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
      }
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
        if(tmpKeyA=='A'){
           return;
           }
        break;
      }    
    }

 }
