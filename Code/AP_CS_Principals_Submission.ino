//for a list, use a 'dictionary' or 2D array to say if like: if the light level is x, then set the percetnage of openness to the percentage that corresponds with x.
//and for param 1 is the light level for Open function
//and for param 2 is another variable that signifies the percentage the blinds are already on

 
#include <Servo.h>
//declare variables
Servo myservo;
const int pResistor = A0; 
const int ledClose=11; 
const int ledOpen=9;      
int value=0;
int previousValue = 0; 

int currentState = 0;


//vvv column 1 is the light level max for the row
//vvv column 2 is the turnDuration for the servo to open and close the blinds
//vvv column 3 is the "value" at which the current state of the blinds are at (ie. 0 = fully closed, 1 = half open, 2 = fully open)
int lightTable [3][3] = {
  {10,0, 0},
  {100,2000, 1},
  {800,4000, 2}
};

//set up connections
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
if(value != previousValue)
  {
    Change(value);
  }
  previousValue = value;
  delay(2000);
}
void Change(int lightlevel)
{
  if(lightlevel<800 && lightlevel >=100)
  {
    CheckIfDiff(lightTable[2][2]);
  }
  if(lightlevel<100 && lightlevel >= 10)
  {
    
    CheckIfDiff(lightTable[1][2]);
    
  }
  if(lightlevel< 10)
  {
    CheckIfDiff(lightTable[0][2]);
  }
}

bool CheckIfDiff(int proposedState)
{
  if(proposedState == currentState)
  {
    return false;    
  }
  else
  {
    ChangeState(proposedState);
  }
}

void ChangeState(int newState)
{
  myservo.attach(10);

  if(newState > currentState)
  {
    myservo.write(-180);
    delay(lightTable[newState][1] - lightTable[currentState][1]);
  }
  else
  {
    myservo.write(180);
    delay(lightTable[currentState][1] - lightTable[newState][1]);
  }


  
  myservo.detach();





  
  currentState = newState; 
}



//delay = 4000 is the time it takes from fully open to fully closed and visa versa
