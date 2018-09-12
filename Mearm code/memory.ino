void remember(int g, int e, int d, int p){
  if (remembering == false){ // Se ele ainda não está no modo de memorizar suas posições
  leftButtonState = digitalRead(leftButton);
  if(leftButtonState == 0){
    tempoOld = millis();
    leftButtonState = digitalRead(leftButton);
    while(leftButtonState == 0){
    leftButtonState = digitalRead(leftButton);
    tempo = millis() - tempoOld;
    if (tempo >= 2000){ // Se o botão do joystick esquerdo foi pressionado por pelo menos 2 segundos
    garraPos[posCounter] = g;
    pescocoPos[posCounter] = p;
    servoEPos[posCounter] = e;
    servoDPos[posCounter] = d;
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(800);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    posCounter = 1;
    tempo = 0;
    leftButtonState = 1;
    remembering = true;
    break;
  }
  }
  } 
  }
  else{ // Se ele está no modo de memorizar suas posições
    if(posCounter < 5){
     rightButtonState = digitalRead(rightButton);
    if(rightButtonState == 0){
      rightButtonState = digitalRead(rightButton);
      while(rightButtonState == 0){
      rightButtonState = digitalRead(rightButton);
      if(rightButtonState == 0){
        if(rightCounter < 5){
        rightCounter = rightCounter + 1;
      }
      else{
      rightButtonState = digitalRead(rightButton);
      if(rightButtonState == 0){
        rightButtonState = digitalRead(rightButton);
        while(rightButtonState == 0){
         rightButtonState = digitalRead(rightButton);
        } 
        // Aqui são feitas várias verificações para garantir que o botão direito foi realmente pressionado e solto e então as posições do servos são registradas,
        // entretanto no momento esta função só funciona como desejada se o meArm estiver conectado à fonte e ao computador simultaneamente, 
        // sendo este o único bug encontrado até agora
        garraPos[posCounter] = g;
        pescocoPos[posCounter] = p;
        servoEPos[posCounter] = e;
        servoDPos[posCounter] = d;
        posCounter = posCounter + 1;
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
      }else{
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
      }
      rightCounter = 0;
      } 
      }else{
       rightCounter = 0;  
      }
      }
    }   
    }
  }
}

void servoToPos(int rightyPos, int rightxPos, int leftyPos, int leftxPos){ // Essa função posicionará os servos, de forma cíclica e lenta, até as posições que foram registradas na memória
  garra.write(rightyPos);
  servoE.write(rightxPos);
  servoD.write(leftyPos);
  pescoco.write(leftxPos);
  for(int pos = 0; pos < 5; pos = pos + 1){
    
    // Essas variáveis indicam a diferença entre as posições que cada servo precisa ir e as posições em que cada um deles estão no momento
    // Quando essas variáveis chegam a zero, significa que o servo chegou na posição desejada e então muda-se o alvo para a próxima posição na Array
    int servoGPos = garraPos[pos] - rightyPos;
    int servoEsqPos = servoEPos[pos] - rightxPos;
    int servoDirPos = servoDPos[pos] - leftyPos;
    int servoPPos = pescocoPos[pos] - leftxPos;
    
    // Estes "While"s levaram os servos de forma gradual e lenta até as posições desejadas
    while(servoGPos != 0){
      if(servoGPos > 0){
        rightyPos = rightyPos + 1;
        garra.write(rightyPos);
        delay(20);
      }
      else if(servoGPos < 0){
        rightyPos = rightyPos - 1;
        garra.write(rightyPos);
        delay(20);
      }
      servoGPos = garraPos[pos] - rightyPos;
    }
    while(servoEsqPos != 0){
      if(servoEsqPos > 0){
        rightxPos = rightxPos + 1;
        servoE.write(rightxPos);
        delay(20);
      }
      else if(servoEsqPos < 0){
        rightxPos = rightxPos - 1;
        servoE.write(rightxPos);
        delay(20);
      }
      servoEsqPos = servoEPos[pos] - rightxPos;
    }
    while(servoDirPos != 0){
      if(servoDirPos > 0){
        leftyPos = leftyPos + 1;
        servoD.write(leftyPos);
        delay(20);
      }
      else if(servoDirPos < 0){
        leftyPos = leftyPos - 1;
        servoD.write(leftyPos);
        delay(20);
      }
      servoDirPos = servoDPos[pos] - leftyPos;
    }
    while(servoPPos != 0){
      if(servoPPos > 0){
        leftxPos = leftxPos + 1;
        pescoco.write(leftxPos);
        delay(20);
      }
      else if(servoPPos < 0){
        leftxPos = leftxPos - 1;
        pescoco.write(leftxPos);
        delay(20);
      }
      servoPPos = pescocoPos[pos] - leftxPos;
    }
  }
}

