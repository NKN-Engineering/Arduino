#include <HX711.h>
// HX711.DOUT  - pin A0
// HX711.PD_SCK - pin A1
HX711 scale(A0, A1); 

boolean isWeight;
const int ledPin = 12;
int tareWeightValue;
int iterationNumber;
int delayTime = 50;
int weightValue;
int errorMarginIterationNumber = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
scale.set_scale(2280.f);    // this value is obtained by calibrating the scale with known weights; see the README for details
scale.tare();

tareWeightValue = scale.read_average(20);  //the wieght before the fat baby sits down

iterationNumber = 0;
pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


  Serial.print("Weight :");                        // ---------Weight in terms of KG-------------
  Serial.print(scale.get_units()*0.1, 1);
  Serial.println("KG");
  
  Serial.print("Baby :");
  Serial.println(isWeight);
  Serial.print("For ");
  Serial.print(iterationNumber);
  Serial.println(" Iterations");
  Serial.println();
  
  weightValue = (scale.get_units()*0.1);

  if (abs(weightValue)>=10){
      isWeight = true;
      digitalWrite(ledPin, HIGH);
      delay(delayTime);
      digitalWrite(ledPin, LOW);
      delay(delayTime);
      digitalWrite(ledPin, HIGH);
      delay(delayTime);
      digitalWrite(ledPin, LOW);
      delay(delayTime);
      digitalWrite(ledPin, HIGH);
      delay(delayTime);
      digitalWrite(ledPin, LOW);
      delay(100);
      iterationNumber = ((iterationNumber)+1);
        
  } else {
      digitalWrite(ledPin, LOW);
      errorMarginIterationNumber = ((errorMarginIterationNumber)+1);
      if (errorMarginIterationNumber = 3){
        errorMarginIterationNumber = 0;
        iterationNumber = 0;
      }
  }
 delay(1000);
}


