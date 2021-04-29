/*

JOGO DA MEMORIA - COM ARDUINO E SERIAL

*/

String recebido;
String sequenciaNumerica = "";
int led;
long numeroGerado;
char stateGame = 0;
int sequencia;
bool acabou = false;


void setup() {
  // Iniciar comunicacao serie
  Serial.begin(9600);
  // Definir LEDs como OUTPUTs pinos 8,9 e 10
  for(int led = 5; led <= 10; led++){
    pinMode(led, OUTPUT);
  } 
  // Definir a seed do gerador de números aleatórios
  randomSeed(analogRead(0));

}
/*
stateGame = 0 -- inicio do jogo
stateGame = 1 -- jogo nivel 1
stateGame = 2 -- jogo nivel 2
stateGame = 3 -- jogo nivel 3
stateGame = 4 -- jogo nivel 4
stateGame = 5 -- jogo nivel 5
stateGame = 6 -- jogo nivel 6
stateGame = 7 -- fim de jogo "Game over"
stateGame = 8 -- jogar novamente?
*/

void loop() {
 if (!acabou) { 
  realLoop();
 }
}

void realLoop() {
  switch (stateGame) {
    case 0:
      // inicio de jogo
      Serial.println("***** INICIO *****");
      Serial.println("Comecar? (s/n)");
      leserial();
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Jogo começando...");
        piscaled(600,3);
      } else {
        erro();    
      }
      break;
    case 1:
      // Nivel 1 
      nivel(1);
      geraSequencia(1000, 3, 1); 
      leserial();
      if (recebido == sequenciaNumerica){
        parabens(2);
      } else {
        erro();     
      }
      break;
    case 2:
      // Nivel 2 
      nivel(2);
      geraSequencia(1000, 5, 2); 
      leserial();
      if (recebido == sequenciaNumerica){
        parabens(3);
      } else {
        erro();     
      }
      break;
	case 3:
	  // Nivel 3
	  nivel(3);
      geraSequencia(900, 7, 3);
      leserial();
      if (recebido == sequenciaNumerica){
	    parabens(4);
      } else {
        erro();      
      }
      break;
    case 4:                                                 
	  // Nivel 4
	  nivel(4);
      geraSequencia(900, 9, 4);
      leserial();
      if (recebido == sequenciaNumerica){
        parabens(5);
      } else {
        erro();      
      }
      break;
    case 5:                                                  
	  // Nivel 5
	  nivel(5);
      geraSequencia(800, 11, 5);
      leserial();
      if (recebido == sequenciaNumerica){
        parabens(6);
      } else {
        erro();     
      }
      break;
     case 6:                                                  
	  // Nivel 6
	  nivel(6);
      geraSequencia(700, 13, 6);
      leserial();
      if (recebido == sequenciaNumerica){
        parabens(8);
      } else {
        erro();     
      }
      break;
    case 7:
      // Game over!!!
      Serial.println("Game Over"); 
      piscaled(100,5);
      stateGame = 8;
      
      break;
    case 8:
      Serial.println("jogar novamente? (s/n)"); 
      leserial();
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Jogo comecando...");
        piscaled(1000,3);
      } else {
        stateGame = 7;
        Serial.println("Jogo nao iniciado"); 
        piscaled(300,5);
        acabou = true;  
      }
      break; 
  }
}

void leserial(){

  Serial.println("* Insira sua resposta *");

  // Aguardar a resposta do usuario
  while (Serial.available() == 0)
  {}

  // Guardar o valor introduzido pelo utilizador no Serial Monitor numa String user
  if (Serial.available())
  {
    recebido = Serial.readString();
  }
}

void piscaled(int tempo, int vezes){
  for(int i = 0;i < vezes; i++){
    for(int led = 5; led <= 10; led++){
      digitalWrite(led, HIGH);
    }
    delay(tempo);
    for(int led = 5; led <= 10; led++){
      digitalWrite(led, LOW);
    }
    delay(tempo);
  }
}

void geraSequencia (int tempo, int sequencia, char nivel){
  // Criar uma lista de inteiros com o tamanho que e passado como argumento
  int ordemLeds[sequencia];
  if(nivel >= 4 ){
  	// Gerar sequencia aleatoria
	for (int i = 0; i < sequencia; i++){
	  numeroGerado = random(1, 7);
	  ordemLeds[i] = numeroGerado;
    }
  }
  else{
    // Gerar sequencia aleatoria
    for (int i = 0; i < sequencia; i++){
      numeroGerado = random(1, 4);
      ordemLeds[i] = numeroGerado;
    }
  }
  

  // Inicialmente, a String sequenciaNumerica é uma String vazia
  sequenciaNumerica = "";

  // Pisca os LEDs na sequencia gerada
  for (int j = 0; j < sequencia; j++){
    led = ordemLeds[j];
    if (led == 1){
      digitalWrite(5, HIGH);
      delay(tempo);
      digitalWrite(5, LOW);
      delay(tempo);
    }else if (led == 2){
      digitalWrite(6, HIGH);
      delay(tempo);
      digitalWrite(6, LOW);
      delay(tempo);
    }else if (led == 3){
      digitalWrite(7, HIGH);
      delay(tempo);
      digitalWrite(7, LOW);
      delay(tempo);
    }else if (led == 4){
      digitalWrite(8, HIGH);
      delay(tempo);
      digitalWrite(8, LOW);
      delay(tempo);
    }else if (led == 5){
      digitalWrite(9, HIGH);
      delay(tempo);
      digitalWrite(9, LOW);
      delay(tempo);
    }else if (led == 6){
      digitalWrite(10, HIGH);
      delay(tempo);
      digitalWrite(10, LOW);
      delay(tempo);
    }
    // Converte a lista numa String   
    sequenciaNumerica = sequenciaNumerica + led;
  }
}

void erro(){
  stateGame = 7;
  Serial.println("Erroooo!!!"); 
  piscaled(300,5); 
}

char parabens(char state){
  Serial.println("Parabens! proximo nivel.");
  piscaled(1000,3);
  return stateGame = state;
}

void nivel(int nivel){
  Serial.println(String("***** Nivel ") + nivel + " *****");
}