unsigned long PulseTime = 0;    
int MicroswitchMEM = 0;  // Geheugen om de stand van de Microswitch te onthouden
int Microswitch = 19;     // De microswitch zit aangesloten op PIN 2
int BumperReset = 8;     // De reset voor de bumper zit aangesloten op PIN 3
int BLUEPIN = 9;         // Blauw zit aangesloten op PIN 9
int GREENPIN = 10;       // Groen zit aangesloten op PIN 10
int RODEPIN = 11;        // Rood zit aangesloten op PIN 11
const int trigPin = 37;  // Trig zit aangesloten op PIN 12
const int echoPin = 38;  // Echo zit aangesloten op PIN 13

long duration;  // Tijd in microsecondes gedetecteerd door de ultrasoon sensor
int distance;   // De afstand in cm van de ultrasoon sensor tot het gedetecteerde voorwerp


void setup() {
  pinMode(Microswitch, INPUT_PULLUP);  // Veranderd de Microswitch naar een Input
  pinMode(BumperReset, INPUT);         // veranderd de BumperReset knop naar een Input
  pinMode(trigPin, OUTPUT);            // Veranderd de trigPin naar een Output
  pinMode(echoPin, INPUT);             // Veranderd de echoPin naar een Input
  Serial.begin(9600);                  // Starts the serial communication
}


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



  // RESPONSE GEDEELTE

  if (digitalRead(Microswitch) == HIGH) {  // Schakelt de rode Leds in en de blauwe Leds uit als de gemeten afstand lager dan 30 is
    GeleLeds();
    MicroswitchMEM = 1;
  } else if (MicroswitchMEM == 0) {
    GroeneLeds();
  }

  if (distance < 30) {  // Schakelt de rode Leds in en de blauwe Leds uit als de gemeten afstand lager dan 30 is
    GeleLeds();
    MicroswitchMEM = 1;

    
  } else if (MicroswitchMEM == 0) {
    GroeneLeds();
  }

  if (MicroswitchMEM == 1 && digitalRead(BumperReset) == HIGH) {
    MicroswitchMEM = 0;
  }




  // einde void loop
}



void BlueLeds() {
  analogWrite(BLUEPIN, 255);
  analogWrite(GREENPIN, 0);
  analogWrite(RODEPIN, 0);
}
void GroeneLeds() {
  analogWrite(BLUEPIN, 0);  // Schakelt de blauwe Leds in en de rode Leds uit als de gemeten afstand niet lager dan 30 is
  analogWrite(GREENPIN, 255);
  analogWrite(RODEPIN, 0);
}

void GeleLeds () {
  analogWrite(RODEPIN, 255);
  analogWrite(GREENPIN, 50);
  analogWrite(BLUEPIN, 100);
}
  
