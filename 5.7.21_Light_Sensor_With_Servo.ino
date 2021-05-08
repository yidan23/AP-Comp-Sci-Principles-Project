#include <Servo.h>

Servo myservo;
const int pResistor = A0; 
const int ledClose=11; 
const int ledOpen=9;      
int value=0;   

bool isOpen = false;

void setup(){
 myservo.attach(10);
 pinMode(ledClose, OUTPUT);  
 pinMode(ledOpen, OUTPUT);
 pinMode(pResistor, INPUT);
 Serial.begin(9600);
}

void loop(){ 
  value = analogRead(pResistor);
  Serial.println(value);
  if (value > 15){
    if(isOpen == true)
    {
        Open();
    }
    else
    {
     Idle();
    }
  }
  else{
    if(isOpen == false)
    {
      Close();
    }
    else
    {
      Idle();
    } 
  }
  delay(500); //Small delay
}
void Idle()
{
  myservo.detach();
}
void Close()
{
     myservo.attach(10);
      digitalWrite(ledOpen, LOW);
      digitalWrite(ledClose, HIGH);
      myservo.write(-180); 
      delay(4000);
      myservo.detach(); 
      isOpen = true;
}
void Open()
{
   myservo.attach(10);
    digitalWrite(ledOpen, HIGH); 
    digitalWrite(ledClose, LOW);
    myservo.write(180);
    delay(4000);
    myservo.detach();   
    isOpen = false;
}
