void DriveFor (int DriveForSpeed){
  
  digitalWrite(SD_B, HIGH);
  digitalWrite(IN_B, LOW);
  digitalWrite(IN_A, HIGH);
  analogWrite(SD_A, DriveForSpeed);
  }
  
void DriveBack(int DriveForSpeed){
  
  digitalWrite(SD_A, HIGH);
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, HIGH);
  analogWrite(SD_B, DriveForSpeed);
  
  }

void Break (){
  
  
  }

void EmergDrivFor (){
  
  }
  
void EmergDrivBack (){

  }
  
void EmergBreak (){
  
  }
  
void EmergRoll (){
  
  }
