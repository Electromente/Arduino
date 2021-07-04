#define echoPin 8 // attach pin D8 Arduino to pin Echo of HC-SR04
#define trigPin 9 //attach pin D9 Arduino to pin Trig of HC-SR04
#define LEDW 6 // attach pin PWM6 Arduino to RedLed
#define LEDOK 4 // attach pin D4 Arduino to Greenled
#define buzzerpin 10 // attach pin D2 Arduino to buzzer

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int valorled; // variable for the Led brightnes value
String strd, cm, warning; // variable for string to serialprint

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(LEDW, OUTPUT); // Sets RedLed as an OUTPUT
  pinMode(LEDOK, OUTPUT); // Sets greenLed as an OUTPUT
  pinMode(buzzerpin, OUTPUT); // Sets buzzer as an OUTPUT
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
  strd = String("Distance: "); // Distance string
  cm = String(" cm"); // centimeter string
  warning = String("Warning!!! "); // warning string
}
// main program run each functions
void loop() {
  measure();
  serialp();
  led();
  buzzer();
}

// measure the distance using HC-SR04
void measure(){
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}

// print distance to serialport and advice the warning of the value is less than 10cm
void serialp(){
  strd += distance;
  strd += cm;
  if (distance >= 10){
    Serial.println(strd);
  }
  else {
    warning += strd;
    Serial.println(warning);
  }
  strd = String("Distance: ");
  warning = String("Warning!!! ");
}

// led brightness and color status
void led() {
    valorled = map(distance,0,30,255,0);
  if (valorled <= 0){
    valorled = 0;
  }
  if (valorled == 0){
    digitalWrite(LEDOK,HIGH);
    analogWrite(LEDW,0);
  }
  else{
    digitalWrite(LEDOK,LOW);
    analogWrite(LEDW,valorled);
  }
}

// warning buzzer if the sensor measurment is less than 10cm
void buzzer(){
  if (valorled >= 170){
    tone(buzzerpin,2000);
  }
  else {
    noTone(buzzerpin);
  }
}
