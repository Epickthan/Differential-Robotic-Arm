int IN1pin = 7;
int IN2pin = 8;
int ENApin = 6;
int potPin = A3; // Potentiometer output connected to analog pin 3
int potVal = 0; // Variable to store the input from the potentiometer
int pot_i = 0;
int pot_f = 0;

#include <Servo.h>
int length = 2;

Servo servo1;
Servo servo2;
Servo servo3;

int target1 = 90;
int target2 = 90;
int curr1 = 90;
int curr2 = 90;

int button_pins[] = {4,3,2};
int led_pins[] = {13,12,11};
int button_trigs[] = {0,0,0};
int prev_trigs[] = {0,0,0};

void setup() {
  Serial.begin(9600);
  /*
  pinMode(IN1pin, OUTPUT);
  pinMode(IN2pin, OUTPUT);
  pinMode(ENApin, OUTPUT);
  */
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(8);

  servo1.write(130);
  servo2.write(50);
  servo3.write(15);

  for (int i = 0; i < sizeof(button_pins); i++){
    pinMode(button_pins[i], INPUT);
    pinMode(led_pins[i], OUTPUT);
    
  }
}


void loop() {

  /*
  potVal = analogRead(potPin);
  if (potVal < 500) {
    
    digitalWrite(IN1pin,LOW);
    digitalWrite(IN2pin, HIGH);

    analogWrite(ENApin,255);
  } else {
    
    digitalWrite(IN1pin,HIGH);
    digitalWrite(IN2pin, LOW);

    analogWrite(ENApin,255);
  }

  
   digitalWrite(IN1pin,LOW);
  digitalWrite(IN2pin, HIGH);

  analogWrite(ENApin,255);
  */
  
  /*
  Serial.println(String(button_trigs[0]) +  String(button_trigs[1]) + String(button_trigs[2]) );
  
  for (int i = 0; i < sizeof(button_pins); i++){
    button_trigs[i] = digitalRead(button_pins[i]);
    
    
    if (button_trigs[i] == 1) {
      digitalWrite(led_pins[i], LOW);
    } else if (button_trigs[i] == 0) {
      digitalWrite(led_pins[i], HIGH);
    } 
    
    
  }
  button_trigs[0] = digitalRead(button_pins[0]);
  if (button_trigs[0] == 1) {
    digitalWrite(led_pins[0], LOW);
  } else if (button_trigs[0] == 0) {
    digitalWrite(led_pins[0], HIGH);
  } 
  button_trigs[1] = digitalRead(button_pins[1]);
  if (button_trigs[1] == 1) {
    digitalWrite(led_pins[1], LOW);
  } else if (button_trigs[1] == 0) {
    digitalWrite(led_pins[1], HIGH);
  } 
  */
  button_trigs[0] = digitalRead(button_pins[0]);
  button_trigs[1] = digitalRead(button_pins[1]);
  button_trigs[2] = digitalRead(button_pins[2]);
  for (int i = 0; i < sizeof(button_pins)/sizeof(button_pins[0]); i++){
    
    if (prev_trigs[i] != button_trigs[i] and button_trigs[i] == HIGH){
      prev_trigs[i] = int(button_trigs[i]);
      servo_move(i);
    }

    if (prev_trigs[i] != button_trigs[i] and button_trigs[i] == LOW){
      prev_trigs[i] = int(button_trigs[i]);
      servo_unmove(i);
    }

    if (button_trigs[i] == HIGH) {
      digitalWrite(led_pins[i], LOW);
    } else if (button_trigs[i] == LOW) {
      digitalWrite(led_pins[i], HIGH);
    } 
    
  }
  delay(10);

  if (curr1 < target1){
    curr1 += 2;
  } else if (curr1 > target1){
    curr1 -= 2;
  }

  if (curr2 < target2){
    curr2 += 2;
  } else if (curr1 > target2){
    curr2 -= 2;
  }
  servo1.write(curr1);
  servo2.write(curr2);

}

void servo_move(int index){
  switch (index){
    case 0:
      Serial.println("1");
      target1 = 160;
      target2 = 20;
      break;
    case 1:
      Serial.println("2");
      target1 = 170;
      target2 = 170;
      break;
    case 2:
      Serial.println("3");
      servo3.write(40);
      break;

  }
}

void servo_unmove(int index){
  switch (index){
    case 0:
      Serial.println("1");
      target1 = 90;
      target2 = 90;
      break;
    case 1:
      Serial.println("2");
      target1 = 90;
      target2 = 90;
      break;
    case 2:
      Serial.println("3");
      servo3.write(0);
      break;

  }
}

