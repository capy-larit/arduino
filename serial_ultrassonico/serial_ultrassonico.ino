#include <Ultrasonic.h>

HC_SR04 sensor1(4,5); 				// (trigger, echo)
HC_SR04 sensor2(7,6); 				// (trigger, echo)

int servo1 = 9;							// sensor da cápsula
int servo2 = 10;							// sensor do tamanho

float distanciaAtual = sensor2.distance();	// essas variáveis vão impedir que o loop seja realizado sempre
float distanciaAntiga = -3;				// o loop só ocorrerá se a distância atual for diferente da antiga 
								
void setup() {
  Serial.begin(9600);
  pinMode(servo1, OUTPUT);					// define o pino 9 para o servo1
  pinMode(servo2, OUTPUT);					// define o pino 10 para o servo2
  servoPos(servo1, 0);					// posição inicial do servo1
  servoPos(servo2, 90);					// posição inicial do servo2
}

void loop() {
  // distância capturada pelos sensores
  Serial.println(String("Distância sensor distancia: ") + sensor1.distance() +String(" cm"));
  Serial.println(String("Distância sensor quantidade: ") + sensor2.distance() +String(" cm"));
  delay(500);
  									
  distanciaAtual = sensor2.distance(); 

  if(sensor1.distance() < 20){
    servoPos(servo1, 90);				// abre compartimento de cápsulas
    delay(10000);						// tempo para o usuário colocar a cápsula
    servoPos(servo1, 0);				// fecha compartimento de cápsulas
    delay(1000);
    
    if(sensor2.distance() > 30 && distanciaAtual != distanciaAntiga){					
      servoPos(servo2, 0);				// seleciona café longo (40ml)
      delay(500);
      servoPos(servo2, 90);			// volta para a posição de repouso
    }// fecha segundo if
    else if(sensor2.distance() <= 30 && distanciaAtual != distanciaAntiga){
      servoPos(servo2, 180); 			// seleciona café curto (20ml)
      delay(500);
      servoPos(servo2, 90);			// volta para a posição de repouso
    }//fecha else
    delay(1000);
    distanciaAntiga = distanciaAtual;
  }//fecha primeiro if
}//fecha loop

//Função que controla a posição do servo motor. 
void servoPos (int servo, int pos){
  int microPulso = map(pos, 0, 180, 1000, 2000);
  digitalWrite(servo, HIGH);
  delayMicroseconds(microPulso);
  digitalWrite(servo, LOW);
  delay(10);                   
}