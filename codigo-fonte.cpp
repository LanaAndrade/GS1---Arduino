#include <DHT.h>
#include <LiquidCrystal.h>

DHT dht (2, DHT22);
const int vermelho = 13;
const int verde = 11;
const int buzzer = 10;
const int pirSensor = 12;
int pirState = LOW;      
int leituraPirSensor = 0;         
int potValor = 0;

LiquidCrystal lcd(9,8,7,6,5,4); 

float temperatura = 0;
float umidade = 0;
int volta = 0;
int tempoCorrido = 0;
int tempoLeitura = 0;
float temperaturaTotal = 0;
float umidadeTotal = 0;
float ldrValueTotal = 0;
float ldrValue = 0;


void setup() {
  pinMode(vermelho, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pirSensor, INPUT);
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
}

void loop() {

  tempoCorrido = millis();

  if(tempoCorrido - tempoLeitura >= 1000){

    leituraPirSensor = digitalRead(pirSensor);
    temperatura = dht.readTemperature();
    temperaturaTotal = temperatura + temperaturaTotal;
    umidade = dht.readHumidity();
    umidadeTotal = umidade + umidadeTotal;

    volta = volta + 1;

    if(volta == 5){

      leituraPirSensor = leituraPirSensor / 5;
      temperaturaTotal = temperaturaTotal / 5;
      umidadeTotal = umidadeTotal / 5;

      lcd.clear();

      if(temperaturaTotal > 8 && umidadeTotal > 60){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Temp e umid alta");
          lcd.setCursor(0,1);
          lcd.print(temperaturaTotal);
          lcd.print(" e ");
          lcd.print(umidadeTotal);
          digitalWrite(buzzer, HIGH);
          tone(buzzer, 1000);
          delay(3000);
      }
      else if(temperaturaTotal < 2 && umidadeTotal < 20){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Temp e umid alta");
          lcd.setCursor(0,1);
          lcd.print(temperaturaTotal);
          lcd.print(" e ");
          lcd.print(umidadeTotal);
          digitalWrite(buzzer, HIGH);
          tone(buzzer, 1000);
          delay(3000);
      }
      else if(temperaturaTotal > 8 && umidadeTotal < 20){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("T. alta U. baixa");
          lcd.setCursor(0,1);
          lcd.print(temperaturaTotal);
          lcd.print(" e ");
          lcd.print(umidadeTotal);
          digitalWrite(buzzer, HIGH);
          tone(buzzer, 1000);
          delay(3000);

      }
      else if(temperaturaTotal < 2 && umidadeTotal > 60){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("T. baixa U. alta");
          lcd.setCursor(0,1);
          lcd.print(temperaturaTotal);
          lcd.print(" e ");
          lcd.print(umidadeTotal);
          digitalWrite(buzzer, HIGH);
          tone(buzzer, 1000);
          delay(3000);

      }
      else if(temperaturaTotal > 8){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Temp alta");
          lcd.setCursor(0,1);
          lcd.print("Temperatura = "); 
          lcd.print(temperaturaTotal);
          digitalWrite(buzzer, HIGH);
          tone(buzzer, 1000);
          delay(3000);
      }
      else if(temperaturaTotal < 2){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Temp baixa");
          lcd.setCursor(0,1);
          lcd.print("Temperatura = "); 
          lcd.print(temperaturaTotal);
          digitalWrite(buzzer, HIGH);
          tone(buzzer, 1000);
          delay(3000);
      }
      else if(umidadeTotal > 60){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Umid alta");
          lcd.setCursor(0,1);
          lcd.print("Umidade = "); 
          lcd.print(umidadeTotal);
          digitalWrite(buzzer, HIGH);
          tone(buzzer, 1000);
          delay(3000);
      }
      else if(umidadeTotal < 20){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Umid alta");
          lcd.setCursor(0,1);
          lcd.print("Umidade = "); 
          lcd.print(umidadeTotal);
          digitalWrite(buzzer, HIGH);
          tone(buzzer, 1000);
          delay(3000);

      }   
      else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Temp e Umid Ok");
          lcd.setCursor(0,1);
          lcd.print(temperaturaTotal);
          lcd.print(" e ");
          lcd.print(umidadeTotal);
      }


    temperaturaTotal = 0;
    umidadeTotal = 0;
    volta = 0;
    }
    
  tempoLeitura = millis();
  }

  if (leituraPirSensor == HIGH) 
  {           
      digitalWrite(vermelho, HIGH);
      digitalWrite(verde, LOW);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Movimento");
      lcd.setCursor(0,1);
      lcd.print("detectado");
      delay(3000);
      lcd.clear();
  } 
  else
  {
      digitalWrite(verde, HIGH);
      digitalWrite(vermelho, LOW);
  }
}
