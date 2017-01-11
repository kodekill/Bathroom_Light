#define PIN 8                  // pin for lights
#define PIR 9                  // pin for PIR sensor
//#define TIME 5000

#define TIME 180000

int PHOTO = A1;
int POT = A2;
int pirState = LOW;            // we start, assuming no motion detected

int Photo_Val = 0;
int Pot_Value = 0;        
int val = 0;                   // variable for reading the pin status

void setup() {
  pinMode(PIN, OUTPUT);        // declare light as output
  pinMode(PIR, INPUT);         // declare sensor as input
  //Serial.begin(9600);
}

void loop() {
  Photo_Val = analogRead(PHOTO);
  Pot_Value = analogRead(POT);

  val = digitalRead(PIR);      // read input value
  if ((val == HIGH) && (Photo_Val <= Pot_Value)) {           // check if the input is HIGH
    if (pirState == LOW) {     // we have just turned on
      //Serial.println("ON");
      pirState = HIGH;         // We only want to print on the output change, not state
      digitalWrite(PIN, HIGH);
      delay(TIME);
    }
  }

  else {
    if (pirState == HIGH) {    // we have just turned of
      //Serial.println("OFF");
      pirState = LOW;         // We only want to print on the output change, not state
      digitalWrite(PIN, LOW);
    }
  }
  //Serial.print("Photo Value = ");
  //Serial.print(Photo_Val);

  //Serial.print("  Pot Value = ");
  //Serial.println(Pot_Value);
  delay(20);
}
