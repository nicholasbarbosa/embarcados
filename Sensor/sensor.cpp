#define red 13
#define ylw 12
#define grn 11
#define s 4

int dist = 0;

long readDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(grn, OUTPUT);
  pinMode(ylw, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(s, OUTPUT);
  
  Serial.begin (9600);
}

void loop(){

  dist = readDistance(s, s)*0.01723;
  Serial.println (dist);
  if (dist > 80) {
    digitalWrite(grn, HIGH);
    digitalWrite(ylw, LOW);
    digitalWrite(red, LOW);
  } else {
    if (dist > 60 && dist < 80) {
      digitalWrite(grn, LOW);
      digitalWrite(ylw, HIGH);
      digitalWrite(red, LOW);
    } else {
      digitalWrite(grn, LOW);
      digitalWrite(ylw, LOW);
      digitalWrite(red, HIGH);
    }
  }
  delay(10); 
}