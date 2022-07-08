#include <Servo.h>

//--------------------------------------------------------------------------------------------------------------------------
Servo esc;
unsigned long PulseTime = 0;    
int MicroswitchMEM = 0;  // Geheugen om de stand van de Microswitch te onthouden
int Microswitch = 19;     // De microswitch zit aangesloten op PIN 2
int BumperReset = 8;     // De reset voor de bumper zit aangesloten op PIN 3
int BLUEPIN = 9;         // Blauw zit aangesloten op PIN 9
int GREENPIN = 10;       // Groen zit aangesloten op PIN 10
int RODEPIN = 11;        // Rood zit aangesloten op PIN 11
const int trigPin = 37;  // Trig zit aangesloten op PIN 12
const int echoPin = 38;  // Echo zit aangesloten op PIN 13
const int Start_knop  = 8;
int Start_MEM   = 0;



long duration;  // Tijd in microsecondes gedetecteerd door de ultrasoon sensor
int distance;   // De afstand in cm van de ultrasoon sensor tot het gedetecteerde voorwerp


void setup() {
  pinMode(Start_knop, INPUT);
  pinMode(Microswitch, INPUT_PULLUP);  // Veranderd de Microswitch naar een Input
  pinMode(BumperReset, INPUT);         // veranderd de BumperReset knop naar een Input
  pinMode(trigPin, OUTPUT);            // Veranderd de trigPin naar een Output
  pinMode(echoPin, INPUT);             // Veranderd de echoPin naar een Input
  Serial.begin(9600);                  // Starts the serial communication
  esc.attach(12);
}

//--------------------------------------------------------------------------------------------------------------------------
void loop() {

  // ULTRASOON GEDEELTE


  digitalWrite(trigPin, LOW);  // Schakelt de trigPin uit
  delay(2);
  digitalWrite(trigPin, HIGH);  // Schakelt de trigPin aan voor 10 micro secondes
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // Leest de echoPin van de ultrasoon sensor, dit is gelijk aan de de tijd van de geluidsgolf in microsecondes
  distance = duration * 0.034 / 2;    // Het omrekenen van duration naar afstand in cm
  Serial.print("Distance: ");         // Geeft de afstand weer op de Serial Monitor
  Serial.println(distance);
  Serial.println(MicroswitchMEM);


  //--------------------------------------------------------------------------------------------------------------------------
  // RESPONSE GEDEELTE

  if (digitalRead(Microswitch) == HIGH) {  // Schakelt de rode Leds in en de blauwe Leds uit als de gemeten afstand lager dan 30 is
    GeleLeds();
    MicroswitchMEM = 1;
    Start_MEM = 0;
  } else if (MicroswitchMEM == 0) {
    GroeneLeds();
  }

  if (distance < 30) {  // Schakelt de rode Leds in en de blauwe Leds uit als de gemeten afstand lager dan 30 is
    GeleLeds();
    MicroswitchMEM = 1;
    Start_MEM = 0;

    
  } else if (MicroswitchMEM == 0) {
    GroeneLeds();
  }

  if (MicroswitchMEM == 1 && digitalRead(BumperReset) == HIGH) {
    MicroswitchMEM = 0;
  }

  //--------------------------------------------------------------------------------------------------------------------------
  // Start/stop cyclus
  
  if (digitalRead(BumperReset) == HIGH) {
  Start_MEM = 1;
  }

  // einde Start/stop cyclus
  //--------------------------------------------------------------------------------------------------------------------------
  // Motor aan stuur gedeelte

  
if (Start_MEM == 1 ) {
  esc.writeMicroseconds(1770);
  }
else if (Start_MEM == 0  ) {
  esc.writeMicroseconds(2400);
  Serial.println(Start_MEM);
  delay(250);
  }




  // einde void loop
}
  //--------------------------------------------------------------------------------------------------------------------------


void BlueLeds() {
  analogWrite(BLUEPIN, 255);
  analogWrite(GREENPIN, 0);
  analogWrite(RODEPIN, 0);
}
void GroeneLeds() {
  analogWrite(BLUEPIN, 0);  
  analogWrite(GREENPIN, 255);
  analogWrite(RODEPIN, 0);
}

void GeleLeds () {
  analogWrite(RODEPIN, 255);
  analogWrite(GREENPIN, 50);
  analogWrite(BLUEPIN, 100);
}


  
