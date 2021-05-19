#include <Servo.h> //allows use of servo functionalities

//declaring variables
Servo myservo;
const int lightSensor = A0; //device detecting and receiving the input (which is light/the sun)
int lightvalue = 0; //this is the input from the light sensor
int currentState = 0; //this represents the current state of the blinds (ie. 0 = fully closed, 1 = partially open, 2 = fully open)
int previousValue = 0; // represents the light value before a new light value was registered. This is used in comparison to the new one in the void loop.

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

//setting up specifications for each component
void setup(){
 myservo.attach(10);
 pinMode(lightSensor, INPUT);
 Serial.begin(9600);
} 
void loop(){ 
  lightvalue = analogRead(lightSensor);//light value = whatever number the light sensor detects
  Serial.println(lightvalue); //this is just for debugging; prints the current light value in console
  
if(lightvalue != previousValue)//if the light level changed, then run the function FindState and pass through the current light level
  {
    FindState(lightvalue);
  }
  
  previousValue = lightvalue;//the current light level is now the previous one as it will detect a new one
  delay(2000); //just reduces the amount of times the program has to loop a bit
}
void FindState(int lightlevel)
{
  //for loop iterates through the 1st column of the 2D array to see what the state (column 3 of array) of the blinds should be based on the light level, and 
  //then passes that proposed state to CheckIfDifferent  
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
    ChangeState(proposedState); //if the ideal state and the current state are different, then run the function ChangeState and pass in state that the blinds should be in
  }
}
void ChangeState(int newState)
{
  myservo.attach(10); //re-attach servo/ensure servo is attached. 

  if(newState > currentState)//if the ideal state (column 3 of the array) is greater than the current one, then turn the blinds open for the time difference between the new state and the current one (column 2 of array)
  {
    myservo.write(-180);
    delay(lightTable[newState][1] - lightTable[currentState][1]);
  }
  else //if the ideal state is less than the current one, then turn the blinds to close for the time difference of the current state and the new state.
  {
    myservo.write(180);
    delay(lightTable[currentState][1] - lightTable[newState][1]);
  }  
  myservo.detach();//detaches the servo to stop it from spinning completely
  
  currentState = newState;//now that the change is done, make the new state the current one
}
