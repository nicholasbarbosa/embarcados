#include <LiquidCrystal.h>
#define Rs 7
#define En 6
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define red 12
#define ylw 11
#define grn 10
#define blue 9
#define btn 8

LiquidCrystal lcd(7,6,5,4,3,2);

int leituraBotao;
int conta;

void setup ()
{
  pinMode(blue, OUTPUT);
  pinMode(grn, OUTPUT);
  pinMode(ylw, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(btn, INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("SEMAFORO");
  lcd.setCursor(1,1);
  lcd.print("BOTAO PEDESTRE");
  delay(1000);
}

void loop()
{
  leituraBotao = digitalRead(btn);
  
  if(leituraBotao == HIGH ){
    lcd.clear(); 
    lcd.setCursor(1,0);
    lcd.print("BOTAO PEDESTRE");
    lcd.setCursor(1,1);
    lcd.print("ACIONADO");
          
  	while(conta < 10){
      high('b');
      lcd.setCursor(13,1);
      lcd.print(conta);
      delay(500);
      conta ++;
    }

    conta = 0;
  } digitalWrite(blue, LOW);
  
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("SEMAFORO");
  lcd.setCursor(5,1);
  lcd.print("ABERTO");
  high('g');
  delay(8000);

  
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("SEMAFORO");
  lcd.setCursor(4,1);
  lcd.print("EM ALERTA");
  high('y');
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("SEMAFORO");
  lcd.setCursor(4,1);
  lcd.print("FECHADO");
  high('r');
  delay(8000);
}

void high(char c){
  if(c == 'g'){
    digitalWrite(grn, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(ylw, LOW);

  }
  if(c == 'y'){
    digitalWrite(grn, LOW);
    digitalWrite(red, LOW);
    digitalWrite(ylw, HIGH);

  }
  if(c == 'r'){
    digitalWrite(grn, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(ylw, LOW);

  }
  if(c == 'b'){
  	digitalWrite(grn, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(ylw, LOW);
	  digitalWrite(blue, HIGH);
  }
}