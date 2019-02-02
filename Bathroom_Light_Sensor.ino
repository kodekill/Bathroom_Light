//PWM pins = 3, 5, 6, 9, 10, and 11

#define LED1 3                                                // pin for lights
#define LED2 9
#define LED3 10
#define PIR 7                                                 // pin for Motion sensor

int PHOTO = A0;
int POT = A1;

bool pirState = LOW;                                          // we start, assuming no motion detected
int Photo_Val = 0;                                            // variable for photoresistor
int Pot_Val = 0;                                              // variable for potentiometer
int Pir_Val = 0;                                              // variable for reading the motion status

//const int TIME = 1500;
const long TIME = 120000;


void setup() {
  pinMode(LED1, OUTPUT);                                       // declare LED strip
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  
  pinMode(PIR, INPUT);                                        // declare Motion sensor
  Serial.begin(9600);
}


void loop() {
  readSensors();
  printSensorValues();
  motionLogic();
  
  delay(20);
}

void(* resetFunc)(void) = 0;

/**
 * Read Motion & Potentiometer & Read Photoresistor Sensors
 */
void readSensors(){
  Photo_Val = analogRead(PHOTO);
  Pot_Val = analogRead(POT);
  Pir_Val = digitalRead(PIR);
}


/**
 * Principal code, checks if PIR was set HIGH
 * turns lights on for TIME and then turns off
 */
void motionLogic(){
  if ((Pir_Val == HIGH) && (Photo_Val <= Pot_Val)) {          // check if the input is HIGH
    glowLED();
    onLED();
    delay(TIME);
    
    glowOFF();
    offLED();
    pirState = LOW;
    
    delay(10);
  } 
}


/**
 * Serial out sensor inputs
 */
void printSensorValues(){
  Serial.print("Photo_Val = ");
  Serial.println(Photo_Val);
  
  Serial.print("Pot_Val =   ");
  Serial.println(Pot_Val);
  
//  Serial.print("Pir_Val = ");
//  Serial.println(Pir_Val);
}


/**
 * Slowly turn LED's on
 */
void glowLED(){

  for(int x = 0; x < 30; x++){
    analogWrite(LED1, x);
    analogWrite(LED2, x);
    analogWrite(LED3, x);
    delay(60);
  }
  
  for(int x = 30; x < 255; x++){
    analogWrite(LED1, x);
    analogWrite(LED2, x);
    analogWrite(LED3, x);
    delay(10);
  }
}

/**
 * Slowly turn LED's off
 */
void glowOFF(){
    for(int x = 255; x > 0; x--){
    analogWrite(LED1, x);
    analogWrite(LED2, x);
    analogWrite(LED3, x);
    delay(2);
  }
}


/**
 * Turn Strip ON
 */
void onLED(){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
}


/**
 * Turn Strip OFF
 */
void offLED(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  resetFunc();
}
