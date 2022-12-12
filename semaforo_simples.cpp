// C++ code

#define red 10
#define ylw 8
#define grn 7
#define red2 5
#define ylw2 4
#define grn2 3
#define btn 2


unsigned long myTime; 
bool state = false;


void setup()
{
  pinMode(red, OUTPUT);
  pinMode(ylw, OUTPUT);
  pinMode(grn, OUTPUT);
  
  digitalWrite(red, HIGH);
  digitalWrite(red2, HIGH);
  
  Serial.begin (9600);
 
}

void high(char l){
  if(l == 'r'){
  	digitalWrite(red, HIGH);
    digitalWrite(ylw, LOW);
    digitalWrite(grn, LOW);
  } else if(l == 'y'){
    digitalWrite(red, LOW);
    digitalWrite(ylw, HIGH);
    digitalWrite(grn, LOW);
  } else if(l == 'g'){
    digitalWrite(red, LOW);
    digitalWrite(ylw, LOW);
    digitalWrite(grn, HIGH);
  }
  
}

void high2(char l){
  if(l == 'r'){
  	digitalWrite(red2, HIGH);
    digitalWrite(ylw2, LOW);
    digitalWrite(grn2, LOW);
  } else if(l == 'y'){
    digitalWrite(red2, LOW);
    digitalWrite(ylw2, HIGH);
    digitalWrite(grn2, LOW);
  } else if(l == 'g'){
    digitalWrite(red2, LOW);
    digitalWrite(ylw2, LOW);
    digitalWrite(grn2, HIGH);
  }
  
}

void loop() {
  
  if(state == true){
    high('g');
    delay(1000);
    high('y');
    delay(1000);
    high('r');
    delay(1000);
    state = !state;
  } else if(state == false){
    high2('g');
    delay(1000);
    high2('y');
    delay(1000);
    high2('r');
    delay(1000);
    state = !state;
  }
  
  
}