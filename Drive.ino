//********************************************************************************************************************************************************************************
//Fahren Werte von -255 bis 255 werden verarbeitet
// 0 = Fahrzeug steht -> Bremsen
// Wert > 0 = Fahrzeug fährt mit Wert vorwärts
// Wert < 0 = Fahrzeug fährt mit Wert rückwerts
//********************************************************************************************************************************************************************************  

void Drive (int DriveForSpeed){
  int sort =rotating_direction();
  //  //  Serial.print("\t rotating_direction: ");
  //  //  Serial.print(sort);
  DriveForSpeed = min(DriveForSpeed,MAXSPEED);
     
    if((sort==-1) || (sortold != sort)){                   // 0 = Fahrzeug steht -> Bremsen oder Richtungsänderung
    Break ();
    }
  else if((sort==1 && DIRECTION==1)||(sort==2 && DIRECTION==2)){              // Wert > 0 = Fahrzeug fährt mit Wert vorwärts
    digitalWrite(SD_B, HIGH);
    digitalWrite(IN_B, LOW);
    digitalWrite(IN_A, HIGH);
    analogWrite(SD_A, DriveForSpeed);
      Serial.print("\t FOR: ");
    Serial.print(DriveForSpeed);
    Brakeaktive=false;
    }
  else if ((sort==1 && DIRECTION==2)||(sort==2 && DIRECTION==1)){            // Wert < 0 = Fahrzeug fährt mit Wert rückwerts
    DriveForSpeed = map(DriveForSpeed,0,MAXSPEED,0,MAXSPEED/2);          //Halbe Geschwindigkeit bei Rückwärts fahren
    digitalWrite(SD_A, HIGH);
    digitalWrite(IN_A, LOW);
    digitalWrite(IN_B, HIGH);
    analogWrite(SD_B, DriveForSpeed);
       Serial.print("\t Back: ");
    Serial.print(DriveForSpeed);
    Brakeaktive=false;
    }
    sortold = sort;
  return;
  }

//********************************************************************************************************************************************************************************
//Bremsen
//********************************************************************************************************************************************************************************  

void Break (){
  
  if(Brakeaktive==false){
    
    digitalWrite(SD_A, LOW);              //Austrudeln 400ms
    digitalWrite(IN_A, LOW);
    digitalWrite(IN_B, LOW);
    digitalWrite(SD_B, LOW);
    delay(500);
    int i;
    for(i=0;i<=255;i++){
        digitalWrite(SD_A, HIGH);            //Bremsen auf Maximal
        digitalWrite(IN_A, LOW);
        digitalWrite(IN_B, LOW);
        analogWrite(SD_B, i);
        delay(2);
        Speed--;
        Speed=max(Speed,1);
        
      }
    Brakeaktive=true;
    }

  digitalWrite(SD_A, HIGH);            //Bremsen Maximal
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, HIGH);
  }
