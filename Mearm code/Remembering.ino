//Verifica se o botão foi pressionado e permite o modo de memorização
void validateRemembering(){
  bool btnIsHold = btnHold(rightButton);
  if(btnIsHold == true){
    isRemembering = true;
    blinkLedsTwice();
  }
}

//Salva as posições recebidas
void rememberPositions(int g, int e, int d, int p){
  String btnStatus = btnState(rightButton);
  if(btnStatus == "clicked"){
    garraPos[posCounter] = g;
    pescocoPos[posCounter] = p;
    servoEPos[posCounter] = e;
    servoDPos[posCounter] = d;
    posCounter++;
    blinkLedsOnce();
  }
  else if(btnStatus == "hold" || posCounter >= positionsAmont){
    doCycle = true;
    blinkLedsTwice();
  }
}

// Essa função posicionará os servos, de forma cíclica e lenta, até as posições que foram registradas na memória
void servoToPos(int rightyPos, int rightxPos, int leftyPos, int leftxPos){ 
  /*garra.write(rightyPos);
  servoE.write(rightxPos);
  servoD.write(leftyPos);
  pescoco.write(leftxPos);*/
  for(int pos = 0; pos < positionsAmont; pos++){
    if(garraPos[pos] != -1 && servoEPos[pos] != -1 && servoDPos[pos] != -1 && pescocoPos[pos] != -1){ //Verifica se tem alguma posição salva

      // Essas variáveis indicam a diferença entre as posições que cada servo precisa ir e as posições em que cada um deles estão no momento
      // Quando essas variáveis chegam a zero, significa que o servo chegou na posição desejada e então muda-se o alvo para a próxima posição na Array
      int servoGPos = garraPos[pos] - rightyPos;
      int servoEsqPos = servoEPos[pos] - rightxPos;
      int servoDirPos = servoDPos[pos] - leftyPos;
      int servoPPos = pescocoPos[pos] - leftxPos;

      // Estes "while"s levarão os servos de forma gradual e lenta até as posições desejadas
      /*while(servoGPos != 0){
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
      }*/

      while(servoGPos != 0 || servoEsqPos != 0 || servoDirPos != 0 || servoPPos != 0){
        if(servoGPos > 0){
          rightyPos = rightyPos + 1;
          garra.write(rightyPos);
        }
        else if(servoGPos < 0){
          rightyPos = rightyPos - 1;
          garra.write(rightyPos);
        }
        
        if(servoEsqPos > 0){
          rightxPos = rightxPos + 1;
          servoE.write(rightxPos);
        }
        else if(servoEsqPos < 0){
          rightxPos = rightxPos - 1;
          servoE.write(rightxPos);
        }

        if(servoDirPos > 0){
          leftyPos = leftyPos + 1;
          servoD.write(leftyPos);
        }
        else if(servoDirPos < 0){
          leftyPos = leftyPos - 1;
          servoD.write(leftyPos);
        }

        if(servoPPos > 0){
          leftxPos = leftxPos + 1;
          pescoco.write(leftxPos);
        }
        else if(servoPPos < 0){
          leftxPos = leftxPos - 1;
          pescoco.write(leftxPos);
        }
        servoGPos = garraPos[pos] - rightyPos;
        servoEsqPos = servoEPos[pos] - rightxPos;
        servoDirPos = servoDPos[pos] - leftyPos;
        servoPPos = pescocoPos[pos] - leftxPos;

        if(servoGPos == 0 && servoEsqPos == 0 && servoDirPos == 0 && servoPPos == 0){
          delay(300);
        }else{
          delay(40); 
        }
      }
    }else{
      break;
    }
  }
}

//Para as repetições se o botão for pressionado
void stopCycle(){
  bool btnIsHolded = btnHold(rightButton);
  if(btnIsHolded == true){
    for(int p = 0; p < positionsAmont; p++){
      garraPos[p] = -1;
      pescocoPos[p] = -1;
      servoEPos[p] = -1;
      servoDPos[p] = -1;
    }
    posCounter = 0;
    doCycle = false;
    isRemembering = false;
    blinkLedsTwice();
  }
}

