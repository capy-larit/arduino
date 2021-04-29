#include <Adafruit_SSD1306.h>

#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 oled(128, 64);

char dado;		
int valor;
int valorPot1;
int valorPot2;

void setup() {
  Serial.begin(9600);				   //Inicialica a comunicação serial
  
  // configuração do display oled
  oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS); 
  oled.clearDisplay();
  oled.setTextSize(1); 
  oled.setTextColor(SSD1306_WHITE);
}

void loop() {  
 
  if(Serial.available() > 0){		// Se tem alguma coisa no buffer da serial
    dado = Serial.read();	
    
    if(dado == 'A'){
      valor = Serial.parseInt();
      oled.setCursor(10, 5);
      oled.setTextColor(BLACK);
      oled.println(String("Pot1: ") + valorPot1); 
      oled.setCursor(10, 5);
      oled.setTextColor(SSD1306_WHITE);
      oled.println(String("Pot1: ") + valor);
      valorPot1 = valor;
      oled.display();                          
    }//end if dado == 'A'

    if(dado == 'B'){
      valor = Serial.parseInt();
      oled.setCursor(10, 15);
      oled.setTextColor(BLACK);
      oled.println(String("Pot2: ") + valorPot2);
	  oled.setCursor(10, 15);
      oled.setTextColor(SSD1306_WHITE);
      oled.println(String("Pot2: ") + valor);  
      valorPot2 = valor;
      oled.display();                                   
    }//end if dado == 'B'

  }//end if Serial.available

}//end loop
