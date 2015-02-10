//********************************************************************************************************************************************************************************
//ISR NOT-Vorwärtsfahren über Fernbedienung, solange Taste gedrückt -> Fahrzeug fährt Vorwärts, ISR wird im Bremsmodus verlassen
//********************************************************************************************************************************************************************************  

void EmergDrivFor (){
  noInterrupts(); 
  digitalWrite(SD_B, HIGH);
  digitalWrite(IN_B, LOW);
  digitalWrite(IN_A, HIGH);
  digitalWrite(SD_A, HIGH);
  pinMode(Funk1,INPUT);
  while(digitalRead(Funk1)==HIGH){     //Taste gedrückt und gehalten -> Vorwärtsfahren
    }
  digitalWrite(SD_A, LOW);              //Austrudeln 500ms
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, LOW);
  interrupts(); 
  delay(500);
  digitalWrite(SD_A, HIGH);            //Bremsen Maximal
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, HIGH);
  }

//********************************************************************************************************************************************************************************
//ISR NOT-Rückwärtsfahren über Fernbedienung, solange Taste gedrückt -> Fahrzeug fährt Rückwärts, ISR wird im Bremsmodus verlassen
//********************************************************************************************************************************************************************************  
  
void EmergDrivBack (){
  noInterrupts();
  digitalWrite(SD_A, HIGH);
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, HIGH);
  digitalWrite(SD_B, HIGH);
  pinMode(Funk2,INPUT);
  while(digitalRead(Funk2)==HIGH){     //Taste gedrückt und gehalten -> Rückwärtsfahren
    }
  digitalWrite(SD_A, LOW);              //Austrudeln 500ms
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, LOW);
  interrupts();
  delay(500);
  digitalWrite(SD_A, HIGH);            //Bremsen Maximal
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, HIGH); 
  }

//********************************************************************************************************************************************************************************
//ISR Notbremsung über Fernbedienung, solange Taste gedrückt wird sicher gebremst, ISR wird im Bremsmodus verlassen
//********************************************************************************************************************************************************************************  
void EmergBreak (){
  noInterrupts();                       //Interrupts ausschalten
  digitalWrite(SD_A, LOW);              //Austrudeln 100ms
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, LOW);
  delay(100);
  digitalWrite(SD_A, HIGH);
  int i = 0;                            //Langsames Abbremsen des Motors
  for (i=0; i<=255; i++){
    analogWrite(SD_B, i);
    delay(2);
    }
  digitalWrite(SD_A, HIGH);            //Bremsen Maximal
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, HIGH);
  pinMode(Funk3,INPUT);
  while(digitalRead(Funk3)==HIGH){     //Taste gedrückt und gehalten -> Bremsen
    }
  interrupts();                        //Interrupts einschalten
  }

//********************************************************************************************************************************************************************************
//ISR NOT-Rollen über Fernbedienung, solange Taste gedrückt -> Fahrzeug kann rollen, ISR wird im Bremsmodus verlassen
//********************************************************************************************************************************************************************************  
  
void EmergRoll (){
  noInterrupts();                       //Interrupts ausschalten
  digitalWrite(SD_A, LOW);              //Freilauf
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, LOW);
  pinMode(Funk4,INPUT);
  while(digitalRead(Funk4)==HIGH){     //Taste gedrückt und gehalten -> Rollen
    }
  digitalWrite(SD_A, HIGH);            //Bremsen Maximal
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, HIGH);
  interrupts();
  }
