int buttonPin2 = 2; // nomeia o pino2 do arduino como buttonPin2
int buttonPin3 = 3; // nomeia o pino3 do arduino como buttonPin3
int ledPin = 13;    // nomeia o pino13 do arduino como ledPin 

int buttonStatus2;  // Variavel de estado do buttonPin2
int buttonStatus3;  // Variavel de estado do buttonPin2

int pot1;
int pot2;
int botao1;
int botao2;

void setup() {
  pinMode(ledPin, OUTPUT);            //Pino13 como saida 
  pinMode(buttonPin2, INPUT_PULLUP);  //Pino2 como entrada com resistor de pullup interno
  pinMode(buttonPin3, INPUT_PULLUP);  //Pino3 como entrada com resistor de pullup interno
  Serial.begin(9600);				   //Inicialica a comunicação serial
}

void loop() {
  pot1 = analogRead(A0);
  pot2 = analogRead(A1);

  botao1 = map (pot1, 0, 1023, 0, 255);
  botao2 = map (pot2, 0, 1023, 0, 255);
  buttonStatus2 = digitalRead(buttonPin2);
  buttonStatus3 = digitalRead(buttonPin3);

  if (buttonStatus2 == LOW){   
    digitalWrite(ledPin, HIGH);                            // Então acenda o led
    Serial.println(String("A") + botao1);
    delay(500);                                            // delay de 0,5 seg.
  }

  if (buttonStatus3 == LOW){   
    digitalWrite (ledPin, LOW);                            // Então apaga o led
    Serial.println(String("B") + botao2);
    delay(500);                                            // delay de 0,5 seg.
  }

}