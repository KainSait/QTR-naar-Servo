#include <Servo.h>
#include <QTRSensors.h>
QTRSensors qtr;
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

//------QTR>servo
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
unsigned long tijd = 0;
int pos = 112;    // variable to store the servo position
int knop = 0;
int knop2 = 0;
int knop3 = 0;
int knop4 = 0;
int knop5 = 0;
int knop6 = 0;
int knop7 = 0;
int knop8 = 0;

int knopwaarde = 0;

int Snelheid = 1; 
//-------QTR>servo




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
  esc.writeMicroseconds(2400);

//----------Calibratie QTR
  //QTR SENSOR CALIBRATIE
  // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]) {
    A0, A1, A2, A3, A4, A5, A6, A7
  }, SensorCount);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

  // analogRead() takes about 0.1 ms on an AVR.
  // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
  // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);

  //QTR CALIBRATIE END

  // Breng servo naar start positie [Code start hier]
  myservo.attach(13);  // attaches the servo on pin 9 to the servo object

}

//--------------------------------------------------------------------------------------------------------------------------
void loop() {
//--------------------------------------------------------------------------------------------
//QTR berekende waardes naar boolean veranderen
  if (sensorValues[0] > 700) {
    knop = 1;
  }
  else if (sensorValues[0] < 700) {
    knop = 0;
  }

  if (sensorValues[1] > 700) {
    knop2 = 1;
  }
  else if (sensorValues[1] < 700) {
    knop2 = 0;
  }

  if (sensorValues[2] > 700) {
    knop3 = 1;
  }
  else if (sensorValues[2]< 700) {
    knop3 = 0;
  }

  if (sensorValues[3] > 700) {
    knop4 = 1;
  }
  else if (sensorValues[3] < 700) {
    knop4 = 0;
  }

  if (sensorValues[4] > 700) {
    knop5 = 1;
  }
  else if (sensorValues[4] < 700) {
    knop5 = 0;
  }

  if (sensorValues[5] > 700) {
    knop6 = 1;
  }
  else if (sensorValues[5] < 700) {
    knop6 = 0;
  }

  if (sensorValues[6] > 700) {
    knop7 = 1;
  }
  else if (sensorValues[6] < 700) {
    knop7 = 0;
  }

  if (sensorValues[7] > 700) {
    knop8 = 1;
  }
  else if (sensorValues[7] < 700)  {
    knop8 = 0;
  }


  //--------------------------------------------------------------------------------------------------------------------------------------
  //Calibratie waarde omzetten
  // read calibrated sensor values and obtain a measure of the line position
  // from 0 to 5000 (for a white line, use readLineWhite() instead)
  uint16_t position = qtr.readLineBlack(sensorValues);


  // print the sensor values as numbers from 0 to 1000, where 0 means maximum
  // reflectance and 1000 means minimum reflectance, followed by the line
  // position
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(position);
  //END
  //---------------------------------------------------------------------------------------------------------------------------------------------------------
  //Besturen regels
  //Servo controls
 if (knop == 1) {
    knopwaarde = 8;
  }

  if (knop2 == 1 && knop == 0) { 
    knopwaarde = 7;
  }

  if (knop3 == 1 && knop2 == 0 && knop == 0) {
    knopwaarde = 6;
  }

  if (knop4 == 1 && knop3 == 0 && knop2 == 0 && knop == 0) {
    knopwaarde = 5;
  }

  if (knop5 == 1 && knop6 == 0 && knop7 == 0 && knop8 == 0)  {
    knopwaarde = 4;
  }

  if (knop6 == 1 && knop7 == 0 && knop8 == 0) {
    knopwaarde = 3;
  }

  if (knop7 == 1 && knop8 == 0) {
    knopwaarde = 2;
  }

  if (knop8 == 1) {
    knopwaarde = 1;
  }

  Serial.print(knopwaarde);
  //-----------------------------------------------------------------------------------------------------------------------------------------
  // Servo verplaatsen
  switch (knopwaarde) {
    case 1:
      while (pos != 82) {                                   //Als servo positie niet 82 is blijf op tellen of aftrekken met snelheid van Variable "Snelheid" tot servo positie 82 is
        if (pos < 82 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos ++;
          Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
        if (pos > 82 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos --;
          Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
      }
      break;

    case 2:
      while (pos != 92) {
        if (pos < 92 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos ++;
          Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
        if (pos > 92 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos --;
          Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
      }
      break;

    case 3:
      while (pos != 102) {
        if (pos < 102 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos ++;
          Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
        if (pos > 102 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos --;
          Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
      }
      break;

    case 4:
      while (pos != 112) {
        if (pos < 112 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos ++;
          Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
        if (pos > 112 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos --;
          Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
      }
      break;

    case 5:
      while (pos != 112) {
        if (pos < 112 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos ++;
          Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
        if (pos > 112 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos --;
          Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
      }
      break;
    case 6:
      while (pos != 122) {
        if (pos < 122 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos ++;
          //Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
        if (pos > 122 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos --;
          //Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
      }
      break;

    case 7:
      while (pos != 132) {
        if (pos < 132 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos ++;
          //Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
        if (pos > 132 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos --;
          //Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
      }
      break;

    case 8:
      while (pos != 142) {
        if (pos < 142 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos ++;
          //Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
        if (pos > 142 && (millis() - tijd) > Snelheid) {
          tijd = millis();
          pos --;
          //Serial.println(pos);
          myservo.write(pos);
          delay(15);
        }
      }
      break;
  }
//------------------------------------------------------------------------------------
  
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
  esc.writeMicroseconds(1760);
  }
else if (Start_MEM == 0  ) {
  esc.writeMicroseconds(2400);
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


  
