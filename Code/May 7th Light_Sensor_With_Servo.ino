#include <Servo.h>
//declare variables
Servo myservo;
const int pResistor = A0; 
const int ledClose=11; 
const int ledOpen=9;      
int value=0;   

bool isOpen = false;

//set up connections
void setup(){
 myservo.attach(10);
 pinMode(ledClose, OUTPUT);  
 pinMode(ledOpen, OUTPUT);
 pinMode(pResistor, INPUT);
 Serial.begin(9600);
}
//if the light level is greater than a certain number, run Open(). Else, run close. Also double check if the blinds are already open/closed and act accordingly. 
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
//detach the servo, basically do nothing
void Idle()
{
  myservo.detach();
}
//close the blinds by turning the servo, and also turning on a little LED to help communicate the action
void Close()
{
     myservo.attach(10);
      digitalWrite(ledOpen, LOW);
      digitalWrite(ledClose, HIGH);
      myservo.write(180); 
      delay(4000);
      myservo.detach(); 
      isOpen = true;
}
//open the blinds by turning the servo, and also turning on a little LED to help communicate the action
void Open()
{
   myservo.attach(10);
    digitalWrite(ledOpen, HIGH); 
    digitalWrite(ledClose, LOW);
    myservo.write(-180);
    delay(4000);
    myservo.detach();   
    isOpen = false;
}
