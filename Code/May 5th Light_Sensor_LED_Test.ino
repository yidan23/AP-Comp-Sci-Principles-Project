const int pResistor = A0; 
const int ledPin=9;       

int value=0;          

void setup(){
 pinMode(ledPin, OUTPUT);  
 pinMode(pResistor, INPUT);
 Serial.begin(9600);
}

void loop(){
  value = analogRead(pResistor);
  Serial.println(value);
  if (value > 800){
    digitalWrite(ledPin, LOW);
  }
  else{
    digitalWrite(ledPin, HIGH); 
  }

  delay(500); //Small delay
}
