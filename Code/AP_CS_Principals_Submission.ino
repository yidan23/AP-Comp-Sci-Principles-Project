#include <Servo.h>
Servo myservo;
const int lightSensor = A0;//device detecting and receiving the input (which is light/the sun)
int lightvalue = 0;//this is the input from the light sensor
int currentState = 0;//this represents the current state of the blinds (ie. 0 = fully closed, 1 = partially open, 2 = fully open)
int previousValue = 0;// represents the light value before a new light value was registered. This is used in comparison to the new one in the void loop.

//2D ARRAY EXPLANATION
//each row represents one of the three states in which the blinds/servo motor can be in. Row 1 holds values corresponding to a state of fully closed, Row 2 -> half open, Row 3 -> fully open.
//columm 1 holds the maximum light value for the respective state to be active (ie. if the light level detected is 180, then the blinds will be at a half open state
//column 2 holds the time (in milliseconds) that it takes for the servo to spin open to get to each state, starting from a state of fully closed. For example, to get to a state of fully closed,
//the servo needs to spin for 0 seconds starting from a state of fully closed. The servo needs to spin for 2000 seconds if it needs to go to a state of fully open from fully closed. etc.
//column 3 simply holds representative values for each state. Row 1/fully closed state has a value of 0, Row 2/partially open state has a value of 1, Row 3/fully open has a value of 2

int lightTable [3][3] = {
  {160,0, 0},
  {200,2000, 1},
  {800,4000, 2}
};

      
void setup(){ //setting up specifications for each component
 myservo.attach(10);
 pinMode(lightSensor, INPUT);
 Serial.begin(9600);
} 
void loop(){//loops forever as it takes in new lightvalue every 2000 miliseconds  from the light sensor
  lightvalue = analogRead(lightSensor);       
  Serial.println(lightvalue);                
  
if(lightvalue != previousValue)//if the light value is different from the one detected before, then there was a change in light level and call FindState               
  {
    FindState(lightvalue);
  }
  
  previousValue = lightvalue;                
  delay(2000);                               
}
void FindState(int lightlevel)//iterate through the 1st column of the rows to find the corresponding ideal value/state of the blinds (column 3)
{                                           
  for (int i = 0; i<3; i++)
  {
    if(lightlevel <= lightTable[i][0] && lightlevel > lightTable[i-1][0])
    {
      CheckIfDifferent(lightTable[i][2]);
    }  
  }
}

bool CheckIfDifferent(int proposedState)
{
  if(proposedState == currentState)//if the ideal/proposed state is already active, then dont do anything and stop the function
  {
    return false;    
  }
  else
  {
    ChangeState(proposedState);//if the ideal state and the current state are different, then run the function ChangeState and pass in state that the blinds should be in
  }
}
void ChangeState(int newState) 
{
  myservo.attach(10);                        

  if(newState > currentState)             
  {
    myservo.write(-180);
    delay(lightTable[newState][1] - lightTable[currentState][1]);//if new state is greater than current, turn the blinds open for the time difference of 2nd column of new state and 2nd column of current state.
  }
  else                                     
  {
    myservo.write(180);
    delay(lightTable[currentState][1] - lightTable[newState][1]);//if new state is less than current, turn the blinds closed direction for the time difference of the 2nd column of the current state and the 2nd column of the new state. 
  }  
  myservo.detach();                         
  currentState = newState;                 
}
