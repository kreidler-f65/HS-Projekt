//********************************************************************************************************************************************************************************
//Fahren Werte von -255 bis 255 werden verarbeitet
// 0 = Fahrzeug steht -> Bremsen
// Wert > 0 = Fahrzeug fährt mit Wert vorwärts
// Wert < 0 = Fahrzeug fährt mit Wert rückwerts
//********************************************************************************************************************************************************************************  

void Drive (int DriveForSpeed){
  int sort =rotating_direction();
  DriveForSpeed = max(DriveForSpeed,MAXSPEED);
    if(sort==-1){                   // 0 = Fahrzeug steht -> Bremsen
    Break ();
    }
  else if((sort==1 && DIRECTION==1)||(sort==2 && DIRECTION==2)){              // Wert > 0 = Fahrzeug fährt mit Wert vorwärts
    digitalWrite(SD_B, HIGH);
    digitalWrite(IN_B, LOW);
    digitalWrite(IN_A, HIGH);
    analogWrite(SD_A, DriveForSpeed);
    }
  else if ((sort==1 && DIRECTION==2)||(sort==2 && DIRECTION==1)){            // Wert < 0 = Fahrzeug fährt mit Wert rückwerts
    map(DriveForSpeed,0,255,0,127);          //Halbe Geschwindigkeit bei Rückwärts fahren
    digitalWrite(SD_A, HIGH);
    digitalWrite(IN_A, LOW);
    digitalWrite(IN_B, HIGH);
    analogWrite(SD_B, abs(DriveForSpeed));
    }
  return;
  }

//********************************************************************************************************************************************************************************
//Bremsen
//********************************************************************************************************************************************************************************  

void Break (){
  digitalWrite(SD_A, LOW);              //Austrudeln 500ms
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, LOW);
  delay(200);
  digitalWrite(SD_A, HIGH);            //Bremsen Maximal
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  digitalWrite(SD_B, HIGH);
  }
