//********************************************************************************************************************************************************************************
//ISR NOT-Vorwärtsfahren über Fernbedienung, solange Taste gedrückt -> Fahrzeug fährt Vorwärts, ISR wird im Bremsmodus verlassen
//********************************************************************************************************************************************************************************  

void EmergDrivFor (){

  digitalWrite(SD_B, HIGH);
  digitalWrite(IN_B, LOW);
  digitalWrite(IN_A, HIGH);
  digitalWrite(SD_A, HIGH);
  while(digitalRead(Funk1)==HIGH){     //Taste gedrückt und gehalten -> Vorwärtsfahren
    }
  int i;
  for(i=0;i<=6000;i++){            //Austrudeln
    digitalWrite(SD_A, LOW);              
    digitalWrite(IN_A, LOW);
    digitalWrite(IN_B, LOW);
    digitalWrite(SD_B, LOW);
    }
  digitalWrite(SD_A, HIGH);            //Bremsen Maximal
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, HIGH);
  }

//********************************************************************************************************************************************************************************
//ISR NOT-Rückwärtsfahren über Fernbedienung, solange Taste gedrückt -> Fahrzeug fährt Rückwärts, ISR wird im Bremsmodus verlassen
//********************************************************************************************************************************************************************************  
  
void EmergDrivBack (){

  digitalWrite(SD_A, HIGH);
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, HIGH);
  digitalWrite(SD_B, HIGH);
  while(digitalRead(Funk2)==HIGH){     //Taste gedrückt und gehalten -> Rückwärtsfahren
    }
  int i;
  for(i=0;i<=6000;i++){            //Austrudeln
    digitalWrite(SD_A, LOW);              
    digitalWrite(IN_A, LOW);
    digitalWrite(IN_B, LOW);
    digitalWrite(SD_B, LOW);
    }
  digitalWrite(SD_A, HIGH);            //Bremsen Maximal
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, HIGH); 

  }

//********************************************************************************************************************************************************************************
//ISR Notbremsung über Fernbedienung, solange Taste gedrückt wird sicher gebremst, ISR wird im Bremsmodus verlassen
//********************************************************************************************************************************************************************************  
void EmergBreak (){                       
  
  int i;
  for(i=0;i<=6000;i++){            //Austrudeln
    digitalWrite(SD_A, LOW);              
    digitalWrite(IN_A, LOW);
    digitalWrite(IN_B, LOW);
    digitalWrite(SD_B, LOW);
    }
  digitalWrite(SD_A, HIGH);            //Bremsen Maximal
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, HIGH);
  while(digitalRead(Funk3)==HIGH){     //Taste gedrückt und gehalten -> Bremsen
    }

  }

//********************************************************************************************************************************************************************************
//ISR NOT-Rollen über Fernbedienung, solange Taste gedrückt -> Fahrzeug kann rollen, ISR wird im Bremsmodus verlassen
//********************************************************************************************************************************************************************************  
  
void EmergRoll (){
  digitalWrite(SD_A, LOW);              //Freilauf
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, LOW);
  while(digitalRead(Funk4)==HIGH){     //Taste gedrückt und gehalten -> Rollen
    }
  digitalWrite(SD_A, HIGH);            //Bremsen Maximal
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, HIGH);

  }
