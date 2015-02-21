#include "Ultrasonic.h" // inclui a biblioteca do sensor ultrassônico

#define echoPin 11 // Pino "Echo" do sensor ultrassônico
#define trigPin 13 // Pino "Trig" do sensor ultrassônico

// right = MotorDois
// left = MotorPin

// ### Declarando variáveis ###

int MotorPin =  A0 ; // Motor Dois na porta A0
int MotorDois =  A1 ;  // Motor Dois na porta A1
int inPin = 12 ; // Pino de leitura do sensor óptico
boolean valor ; // variável que guarda o valor atual do sensor óptico
boolean anterior = false ; // variável que guarda o valor anterior do sensor óptico
unsigned long cont = 0 ;  // Contador de quantas vezes a cor branca foi lida logo após a cor preta


Ultrasonic ultrasonic(13,11); // Inicia o sensor ultrassônico

// função que lê o sensor ótico e transforma em booleano , porque eu curto variáveis booleanas
boolean bw() { 
  valor = digitalRead(inPin);
  if ( valor == HIGH ) {
    return true ;
  } 
  if ( valor == LOW ) {
    return false ;
  } 
}

// Função que faz o carrinho andar para a direita se "cont" for par ou para a esquerda se "cont" for ímpar
void WALK_MORE() { 
  if ( (cont % 2) == 0 ) {
    analogWrite(MotorDois, 130); // liga MotorDois
    analogWrite(MotorPin, 0); // Desliga MotorPim
  } else if ( (cont % 2) == 1 ) {
    analogWrite(MotorDois, 0);
    analogWrite(MotorPin, 130);
  }
}

// Função que altera "cont" baseado na leitura atual do sensor óptico e se a última cor lida é preta
void WALK( boolean respect ) {
  if ( respect == true && respect != anterior ) {
    anterior = respect ;
    cont++ ;
    WALK_MORE() ;
  } 
  else if ( respect == false && anterior != respect  ) {
    anterior = respect ;
  }
}

//Função que vira o carrinho se ele ver algum obstáculo . P.s : o delay() pode variar de acordo com o seu motor , atrito da roda , etc .
void viravira ( int distancia ) {
  if ( ( distancia >= 5 ) && ( distancia <= 20 ) ){ //Valores menores que 5 são bugs do leitor
    analogWrite(MotorDois, 0);
    analogWrite(MotorPin, 255); // Vira para a direita
    delay(450) ;
    analogWrite(MotorDois, 255); // Em frente
    analogWrite(MotorPin, 255);
    delay(500) ;
    analogWrite(MotorDois, 255); // Vira para esquerda
    analogWrite(MotorPin, 0);
    delay(450) ;
    analogWrite(MotorDois, 255); // Em frente
    analogWrite(MotorPin, 255);
    delay(500) ;
    analogWrite(MotorDois, 255); // Vira para a direita
    analogWrite(MotorPin, 0);
    delay(450) ;
    analogWrite(MotorDois, 255); // Em frente
    analogWrite(MotorPin, 255);
    delay(450) ;
  }
}

// Inicilizando a "nuvem"
void setup() {
  Serial.begin(9600); // Liga o serial
  // Setando os modos dos pinos
  pinMode(inPin , INPUT);
  pinMode(echoPin , INPUT) ;
  pinMode(trigPin , OUTPUT) ;
  pinMode(MotorPin, OUTPUT);
  pinMode(MotorDois, OUTPUT);
}

void loop() {
  valor = bw() ; // Lê o valor atual do sensor ótico
  WALK(valor) ; // Envia para função "WALK"

  digitalWrite(trigPin, LOW ) ; // Desliga o pino "trigPin" do sensor ultrassônico
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH) ; // Liga o pino "trigPin" do sensor ultrassônico
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW ) ; // Desliga o pino "trigPin" do sensor ultrassônico
  int distancia = (ultrasonic.Ranging(CM)) ; // Lê a distância atual do sensor ultrassônico
  viravira( distancia ) ; // Envia para a função "viravira"

  valor = bw() ; // Lê o valor atual do sensor ótico , denovo para aumentar a precisão
  WALK(valor) ; // Envia para função "WALK"

}