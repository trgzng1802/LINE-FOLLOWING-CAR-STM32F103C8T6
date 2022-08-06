
#define AIN1 3
#define AIN2 4
#define BIN1 5
#define BIN2 6

void setup() {
  Serial.begin(9600);
  
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  
}
 
void loop() {
  
  analogWrite(AIN1, 50);
  digitalWrite(AIN2,LOW);
  analogWrite(BIN1, 50);
  digitalWrite(BIN2,LOW);
}
