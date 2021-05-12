#include <Servo.h>

Servo myservo;

void setup() {
myservo.attach(10);
}
void loop() {
myservo.write(-180); 
delay(6000); 
myservo.detach(); 
delay(500); 
myservo.attach(10); 
myservo.write(180);
delay(6000); 
myservo.detach(); 
delay(500); 
myservo.attach(10);
}
