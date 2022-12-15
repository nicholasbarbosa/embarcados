#define red 13
#define ylw 12
#define grn 11
#define red2 10
#define ylw2 9
#define grn2 8
#define redP1 7 
#define grnP1 6
#define redP2 5
#define grnP2 4
#define btn 2

unsigned long time = 0;
unsigned long myTime = 0; //tempo atual 
unsigned long previousTime = 0; //tempo anterior

bool cycle= 0;
bool btnState = 0;
bool previousState = 0;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(ylw, OUTPUT);
  pinMode(grn, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(ylw2, OUTPUT);
  pinMode(grn2, OUTPUT);
  pinMode(redP1, OUTPUT);
  pinMode(grnP1, OUTPUT);
  pinMode(redP2, OUTPUT);
  pinMode(grnP2, OUTPUT);
  pinMode(btn, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  myTime = millis();
  time = myTime - previousTime;
  btnRead();
  trafficlightCycles();
}

void lights(bool led1,bool led2,bool led3,bool led4,bool led5, bool led6,bool led7, bool led8,bool led9, bool led10){
 digitalWrite(red,led1);
 digitalWrite(ylw,led2);
 digitalWrite(grn,led3);
 digitalWrite(redP1,led4);
 digitalWrite(grnP1,led5);
 digitalWrite(red2,led6);
 digitalWrite(ylw2,led7);
 digitalWrite(grn2,led8);
 digitalWrite(redP2,led9);
 digitalWrite(grnP2,led10);
}
void trafficLights(){
  if(time <= 4000){
    lights(1,0,0,0,1,0,1,0,1,0); 
    //lights(1, 0, 0, 0, 1, 0, 0, 1, 1, 0);
  }
  else if(time > 4000 && time <= 6000){
    lights(0,0,1,0,1,1,0,0,1,0); 
    //lights(1, 0, 0, 0, 1, 0, 1, 0, 1, 0);
  }
  else if(time > 6000 && time <= 10000){
    lights(0,1,0,0,1,1,0,0,1,0); 
    //lights(0, 0, 1, 1, 0, 1, 0, 0, 0, 1); 
  }
  else if(time > 10000 && time <= 12000){
    lights(1,0,0,1,0,0,0,1,0,1); 
    //lights(0, 1, 0, 1, 0, 1, 0, 0, 0, 1); 
    cycle = !cycle;
  }
  else{
  	previousTime =  myTime;
  }
  
}

void btnRead(){ //altera o estado
  btnState = digitalRead(btn);
  if(btnState == 0 &&  previousState == 1){
  cycle = !cycle;
  }
  previousState = btnState;
}

void trafficlightCycles(){
  if(cycle == 1){
  	trafficLights();
  }
  else{
  lights(1,0,0,1,0,0,0, 1, 0,1); 
  previousTime = myTime;
 }
}