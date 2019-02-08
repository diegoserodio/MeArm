// LEGENDA:
// SERVOS::
////////////
// GARRA --- I/O 3 --- 90 -> 130 ---- 1º
// PESCOÇO --- I/O 5 --- 20 -> 190 ---- 2º
// SERVO ESQUERDA --- I/O 9 --- 130 -> 200 ----- 4º
// SERVO DIREITA --- I/O 6 --- 90 -> 150 ------ 3º
////////////
// JOYSTICK::
////////////
// A1 = Y LEFT // FRENTE DIMINUI
// A0 = X LEFT // DIREITA DIMINUI
// A2 = Y RIGHT // FRENTE DIMINUI
// A3 = X RIGHT // DIREITA DIMINUI
// 0 = RIGHT BUTTON // APERTA --> 0

// INSTRUÇÕES:
// O MEARM ENCONTRA-SE NO MOMENTO FUNCIONAL. FOI INSERIDA, POR ÚLTIMO, UMA FUNÇÃO DE MEMÓRIA NO BRAÇO 
// QUE REGISTRA 5 POSIÇÕES DOS SERVOS E DEPOIS REPETE ESTE MOVIMENTOS DE FORMA CÍCLICA E AUTÔNOMA
// PARA USAR ESSA FUNÇÃO, O MEARM PRECISA ESTAR CONECTADO À FONTE E A UM COMPUTADOR ATRAVÉS DO CABO USB,
// SEGURE O JOYSTICK ESQUERDO ATÉ QUE SEJA VISTA UMA INDICAÇÃO NOS LEDS DA PLACA DE CONTROLE (ELES PISCARAM DUAS VEZES),
// AGORA POSICIONE O BRAÇO NA POSIÇÃO DESEJADA E APERTE UMA VEZ O JOYSTICK DIREITO, OS LEDS PISCARAM UMA VEZ INDICANDO QUE AQUELA POSIÇÃO FOI REGISTRADA
// REPITA ESSE ÚLTIMO PASSO ATÉ QUE SEJAM ARMAZENADAS 5 POSIÇÕES NA MEMÓRIA DO PROGRAMA, E ENTÃO O MEARM COMECARÁ A REPETIR SEUS PASSOS DE FORMA CÍCLICA
// INFELIZMENTE AINDA NÃO FOI IMPLEMENTADA UMA FUNÇÃO PARA PARAR ESTÁ REPETIÇÃO, SENDO NECESSÁRIO REINICIAR O CHIPKIT

#include <Servo.h> 

int leftyS;
int leftxS;
int rightyS;
int rightxS;
int led1 = 12;
int led2 = 11;
int led3 = 2;
int led4 = 4;
int rightButton = 0;
int lefty = 100;
int leftx = 100;
int righty = 120;
int rightx = 150;
bool isRemembering = false;
bool doCycle = false;
int posCounter = 0;
int positionsAmont = 40;

// Arrays para armazenar posições dos servos para a função de memória
int garraPos[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int pescocoPos[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int servoEPos[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int servoDPos[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
 
Servo garra;
Servo pescoco;
Servo servoE;
Servo servoD;
 
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  garra.attach(3);
  pescoco.attach(5);
  servoE.attach(9);
  servoD.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  leftyCount(); // Verifica a variação no eixo Y do joystick esquerdo e atribui essa variação à variável "lefty"
  leftxCount(); // Verifica a variação no eixo X do joystick esquerdo e atribui essa variação à variável "leftx"
  rightyCount(); // Verifica a variação no eixo Y do joystick direito e atribui essa variação à variável "righty"
  rightxCount(); // Verifica a variação no eixo X do joystick direito e atribui essa variação à variável "rightx"

  //Atualiza a posição dos servos
  garra.write(righty);
  pescoco.write(leftx);
  servoE.write(rightx);
  servoD.write(lefty);
  delay(60);

  //Condição para permitir salvar posições e executá-las
  if(isRemembering == true){
    if(doCycle == false){ //Se ainda está salvando
     rememberPositions(righty, rightx, lefty, leftx); //Salva as posições
    }else{ //Se está executando as posições
     stopCycle(); //Para o ciclo se pressionado o botão
     servoToPos(righty, rightx, lefty, leftx); //Leva os servos da última posição até a primeira posição salva e executa o ciclo salvo
    }
  }else{
    validateRemembering(); //Inicia a sequência de salvamento e execução ao pressionar o botão
  }
}

