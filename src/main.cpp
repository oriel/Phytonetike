#include <WProgram.h>

//frente dir = 2
// frente esq = 5

// tras esq 3
// tras dir 1

// isso precisa ir pro arquivo.h>

void mediumMovement();
void colisaoFrenteHappened();
void colisaoTrasHappened(); 
void crazyMovement();
void littleMovement();
void stopMove();

// ANALOG PINS
//int temperaturaPin = 0;
int umidadePin = 0;
int ldrTras =  1;
int ldrFrente = 2;

// DIGITAL PINS
int colisaoTras = 12; //2
int colisaoFrente = 11; //3
int forward = 2; //Movimenta motor pra frente
int backwards = 7; //Movimenta motor pra trás
int left = 10; //Movimenta motor pra esquerda
int right = 13; //Movimenta motor pra direita


int soundPin = 8;

// GLOBAL VARS
int direcao = 1; // 1 frente 0 tras

// VERIFICA LUZ
int limiarLuz= 1000; // limiarLuzque define a "luz agradável"
int limiarUmidade = 750;
//VALUES
int luzTras;
int luzFrente;
int temperatura;
int umidade;
 
void setup()   {     
  Serial.begin(9600);
  //ANALOG
  //pinMode(temperaturaPin, INPUT);  
  pinMode(umidadePin, INPUT); 
  pinMode(ldrTras, INPUT);
  pinMode(ldrFrente, INPUT);
  //DIGITAL
  pinMode(colisaoTras, INPUT);
  pinMode(colisaoFrente, INPUT);
  pinMode(soundPin, OUTPUT);
}

void loop()                    
{
 
  int luzTras = analogRead(ldrTras);
  int luzFrente = analogRead(ldrFrente);
  //int temperatura = analogRead(temperaturaPin);
  int umidade = analogRead(umidadePin);
  
  // DEBUGS
  Serial.print("\nluzTras:");
  Serial.print(luzTras);
  Serial.print("\nluzFrente:");
  Serial.print(luzFrente);
  Serial.print("\nUmidade:");
  Serial.print(umidade);
 
  colisaoFrenteHappened(); 
  colisaoTrasHappened();
 

  //Se umidade menor que limiar Umidade, executa movimento doidão
  if (umidade > limiarUmidade) {
     crazyMovement();
     // som de alegria \o/ águaaaaa eeeeeeeeeeeeeeeee :-D
     Serial.println("recebeu agua!");
     for (int i=0; i<5; i++) tone(soundPin, map(umidade, 600, 800, 1000, 2000), 100);
  }
 
  //Senão, verifiza luz
  else {
    Serial.print("\n\n #### Verificando luz!");
    // se a luz de um dos sensores estiver acima do limiar, planta fica parada
    if ((luzTras >= limiarLuz) || (luzFrente >= limiarLuz)) {
        Serial.print("\n\nfica parada!");
        stopMove();
        digitalWrite(backwards, 0);
        pinMode(backwards, INPUT);
        digitalWrite(forward, 0);
        pinMode(forward, INPUT);
     
    // senão, se movimenta em direção do sensor com mais luminosidade 
    }
    else {
     if (luzTras > luzFrente) {
        Serial.print("\n\nandando pra trás!!");
        direcao = 0;
        colisaoTrasHappened();
        mediumMovement();
      } else {
        Serial.print("\n\nandando pra frente!!");
        direcao = 1;
        colisaoFrenteHappened();
        mediumMovement(); 
      }
     
    }
  }
  
  // som do passo
  for (int i=0; i<5; i++) tone(soundPin, map(umidade, 600, 800, 1000, 2000), 10);
 
} 
 
// FUNCOES AUXILIARES 

void tone(int speakerPin, int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
 
void stopMove()   
{
  digitalWrite(backwards, 0);
  pinMode(backwards, INPUT);
  digitalWrite(forward, 0);
  pinMode(forward, INPUT);
  // digitalWrite(left, 0);
  // pinMode(left, INPUT);
  // digitalWrite(right, 0);
  // pinMode(right, INPUT);
}

void moveForward()
{
  stopMove();
  pinMode(forward, OUTPUT);
  digitalWrite(forward, 1);          
  }

void moveLeft()
{
  stopMove();
  pinMode(left, OUTPUT);
  digitalWrite(left, 1);          
  }


void moveRight()
{
  stopMove();
  pinMode(right, OUTPUT);
  digitalWrite(right, 1);          
  }


void moveBackwards()
{
  stopMove();
  pinMode(backwards, OUTPUT); 
  digitalWrite(backwards, 1);          
} 

void littleMovement()
{
    switch(direcao) {
   
    case 1:
    moveForward();
    delay(600);
    stopMove();
    delay(300);
    break;
 
    case 0:
    moveBackwards();
    delay(100);
    stopMove();
    delay(600);
    break;
  }
} 


void mediumMovement()
{
    switch(direcao) {
   
    case 1:
    moveForward();
    delay(1800);
    stopMove();
    delay(400);
    break;
 
    case 0:
    moveBackwards();
    delay(1800);
    stopMove();
    delay(400);
    break;
  }
} 

void crazyMovement()
{
  int i;
  for(i=0; i<1000; i++)
    stopMove();
    moveForward();
    delay(100);
    moveBackwards();
    delay(100);
}

 void colisaoFrenteHappened() {
    if (digitalRead(colisaoFrente)) {
      direcao = 0;
      pinMode(left, OUTPUT);
      digitalWrite(left, 1);          
      mediumMovement();
      mediumMovement();
      digitalWrite(left, 0);          
      Serial.println("\n\n !!!!! Colisao Frente");
    }
  }

void colisaoTrasHappened() {
    if (digitalRead(colisaoTras)) {
      direcao = 1;
      pinMode(right, OUTPUT);
      digitalWrite(right, 1);          
      mediumMovement();
      mediumMovement();
      digitalWrite(right, 0);          
      Serial.println("\n\n !!!! Colisao TRAS");
    }
  } 

