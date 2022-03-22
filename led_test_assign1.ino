#define LED_PIN_A 13
#define LED_PIN_B 12
#define LED_PIN_C 11
#define LED_PIN_D 10

//Check if all leds are correctly put on the breadboard by making turning them on and off

//led turning on/off one by one
int current = 10;
int counter = 1; 
//-----
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN_A, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
  pinMode(LED_PIN_C, OUTPUT);
  pinMode(LED_PIN_D, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN_A,HIGH);
  digitalWrite(LED_PIN_B,HIGH);
  digitalWrite(LED_PIN_C,HIGH);
  digitalWrite(LED_PIN_D,HIGH);
  delay(1000);
  digitalWrite(LED_PIN_A,LOW);
  digitalWrite(LED_PIN_B,LOW);
  digitalWrite(LED_PIN_C,LOW);
  digitalWrite(LED_PIN_D,LOW);
  /*
   * digitalWrite(current,LOW);
   * if(current == 13 || (current == 10 && counter ==-1)){
   *  counter=-counter;
   * }
   * current+=counter;
   * digitalWrite(current,HIGH);
   * delay(100);
   */
}
