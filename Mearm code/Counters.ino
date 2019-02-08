void leftyCount(){
  leftyS = analogRead(A1);
  if (leftyS >= 300 && leftyS < 600){
    lefty = lefty - 1;
    digitalWrite(led1, HIGH);
  }
  else if (leftyS < 300){
    lefty = lefty - 5;
    digitalWrite(led1, HIGH);
  }
  else if (leftyS > 900 && leftyS <= 1000){
    lefty = lefty + 1;
    digitalWrite(led1, HIGH);
  }
  else if (leftyS > 1000){
    lefty = lefty + 5;
    digitalWrite(led1, HIGH);
  }
  else{
    digitalWrite(led1, LOW);
  }
  if(lefty >= 150){
    lefty = 150;
  }
  else if(lefty <= 90){
    lefty = 90;
  }
}

void leftxCount(){
  leftxS = analogRead(A0);
  if (leftxS >= 300 && leftxS < 600){
    leftx = leftx + 1;
    digitalWrite(led2, HIGH);
  }
  else if (leftxS < 300){
    leftx = leftx + 5;
    digitalWrite(led2, HIGH);
  }
  else if (leftxS > 900 && leftxS <= 1000){
    leftx = leftx - 1;
    digitalWrite(led2, HIGH);
  }
  else if (leftxS > 1000){
    leftx = leftx - 5;
    digitalWrite(led2, HIGH);
  }
  else{
    digitalWrite(led2, LOW);
  }
  if(leftx >= 190){
    leftx = 190;
  }
  else if(leftx <= 20){
    leftx = 20;
  }
}

void rightyCount(){
  rightyS = analogRead(A2);
  if (rightyS >= 300 && rightyS < 600){
    righty = righty - 1;
    digitalWrite(led3, HIGH);
  }
  else if (rightyS < 300){
    righty = righty - 5;
    digitalWrite(led3, HIGH);
  }
  else if (rightyS > 
  900 && rightyS <= 1000){
    righty = righty + 1;
    digitalWrite(led3, HIGH);
  }
  else if (rightyS > 1000){
    righty = righty + 5;
    digitalWrite(led3, HIGH);
  }
  else{
    digitalWrite(led3, LOW);
  }
  if(righty >= 130){
    righty = 130;
  }
  else if(righty <= 90){
    righty = 90;
  }
}

void rightxCount(){
  rightxS = analogRead(A3);
  if (rightxS >= 300 && rightxS < 600){
    rightx = rightx + 1;
    digitalWrite(led4, HIGH);
  }
  else if (rightxS < 300){
    rightx = rightx + 5;
    digitalWrite(led4, HIGH);
  }
  else if (rightxS > 900 && rightxS <= 1000){
    rightx = rightx - 1;
    digitalWrite(led4, HIGH);
  }
  else if (rightxS > 1000){
    rightx = rightx - 5;
    digitalWrite(led4, HIGH);
  }
  else{
    digitalWrite(led4, LOW);
  }
  if(rightx >= 200){
    rightx = 200;
  }
  else if(rightx <= 130){
    rightx = 130;
  }
}

