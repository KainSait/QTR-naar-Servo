#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

unsigned long tijd = 0;
int pos = 112;    // variable to store the servo position
int knop = 13;
int knop2 = 12;
int knop3 = 11;
int knop4 = 10;
int knop5 = 8;
int knop6 = 7;
int knop7 = 6;
int knop8 = 5;

int Snelheid = 2;

void setup() {

  pinMode(knop, INPUT);
  pinMode(knop2, INPUT);
  pinMode(knop3, INPUT);
  pinMode(knop4, INPUT);
  pinMode(knop5, INPUT);
  pinMode(knop6, INPUT);
  pinMode(knop7, INPUT);
  pinMode(knop8, INPUT);



// Breng servo naar start positie [Code start hier]
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  
  if (pos < 111) {
  for (pos; pos <= 112; pos += 1) { // goes from 0 degrees to 90 degrees              
                                      // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  }
  if (pos > 113) {
  for (pos; pos >= 112; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
  }
// Breng servo naar start positie [Code eindigd hier]
}


void loop() {
//Als QTR sensor actief is beweeg de Servo
  if (digitalRead(knop) == HIGH) {                       
    while (pos != 82) {                                          //Als servo positie niet 82 is blijf op tellen of aftrekken met snelheid van Variable "Snelheid" tot servo positie 82 is
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
  }
  if (digitalRead(knop2) == HIGH) {
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
  }
  if (digitalRead(knop3) == HIGH) {
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
  }
    if (digitalRead(knop4) == HIGH) {
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
  }
      if (digitalRead(knop5) == HIGH) {
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
  }
      if (digitalRead(knop6) == HIGH) {
    while (pos != 122) {
      if (pos < 122 && (millis() - tijd) > Snelheid) {
        tijd = millis();
        pos ++;
        Serial.println(pos);
        myservo.write(pos);              
        delay(15);      
      }
      if (pos > 122 && (millis() - tijd) > Snelheid) {
        tijd = millis();
        pos --;
        Serial.println(pos);
        myservo.write(pos);              
        delay(15);      
      }
    }
  }
      if (digitalRead(knop7) == HIGH) {
    while (pos != 132) {
      if (pos < 132 && (millis() - tijd) > Snelheid) {
        tijd = millis();
        pos ++;
        Serial.println(pos);
        myservo.write(pos);              
        delay(15);      
      }
      if (pos > 132 && (millis() - tijd) > Snelheid) {
        tijd = millis();
        pos --;
        Serial.println(pos);
        myservo.write(pos);              
        delay(15);      
      }
    }
  }
      if (digitalRead(knop8) == HIGH) {
    while (pos != 142) {
      if (pos < 142 && (millis() - tijd) > Snelheid) {
        tijd = millis();
        pos ++;
        Serial.println(pos);
        myservo.write(pos);              
        delay(15);      
      }
      if (pos > 142 && (millis() - tijd) > Snelheid) {
        tijd = millis();
        pos --;
        Serial.println(pos);
        myservo.write(pos);              
        delay(15);      
      }
    }
  }

   //Einde code QTR sensor naar servo.
}
