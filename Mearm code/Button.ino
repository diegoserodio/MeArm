//Registra se o botão foi pressionado
bool btnHold(int btnPin){
  int btnHoldCounter = 0;
  if(digitalRead(btnPin) == 0){
    while(digitalRead(btnPin) == 0){
      btnHoldCounter++;
      delay(10);
      if(btnHoldCounter > 100){
        return true;
        break;
      }
    }
    return false;
  }else{
    return false;
  }
}

//Registra se o botão foi clicado
bool btnClick(int btnPin){
  if(digitalRead(btnPin) == 0){
    while(digitalRead(btnPin) == 0){
    }
    return true;
  }else{
    return false;
  }
}

//Verifica se o botão foi pressionado ou clicado
String btnState(int btnPin){
  int btnHoldCounter = 0;
  String state = "";
  if(digitalRead(btnPin) == 0){
    while(digitalRead(btnPin) == 0){
      btnHoldCounter++;
      delay(10);
      if(btnHoldCounter > 100){
        state = "hold";
        break;
      }
    }
    if(btnHoldCounter < 100){
        state = "clicked";
    }
  }
  return state;
}
