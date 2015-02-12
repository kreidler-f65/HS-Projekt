//********************************************************************************************************************************************************************************
//Fahren Werte von -255 bis 255 werden verarbeitet
// 0 = Fahrzeug steht -> Bremsen
// Wert > 0 = Fahrzeug fährt mit Wert vorwärts
// Wert < 0 = Fahrzeug fährt mit Wert rückwerts
//********************************************************************************************************************************************************************************  

void Drive (int DriveForSpeed){
  if(DriveForSpeed=0){                   // 0 = Fahrzeug steht -> Bremsen
    digitalWrite(SD_A, HIGH);            //Bremsen Maximal
    digitalWrite(IN_A, LOW);
    digitalWrite(IN_B, LOW);
    digitalWrite(SD_B, HIGH);
    }
  else if(DriveForSpeed>0){              // Wert > 0 = Fahrzeug fährt mit Wert vorwärts
    digitalWrite(SD_B, HIGH);
    digitalWrite(IN_B, LOW);
    digitalWrite(IN_A, HIGH);
    analogWrite(SD_A, DriveForSpeed);
    }
  else if (DriveForSpeed<0){            // Wert < 0 = Fahrzeug fährt mit Wert rückwerts
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
