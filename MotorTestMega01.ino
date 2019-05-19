const uint8_t led = 13;
const uint8_t potPin = A0;

uint8_t ledState = HIGH;
uint32_t currentMillis = 0;
uint32_t delayMillis = 500;

uint16_t currentPot = 150;
uint16_t hysterysis = 3;

char buf[10];

void setup() {
  Serial.begin(115200);    //Initiate serial port
  delay(100);
  Serial1.begin(9600);
  delay(100);
  Serial2.begin(9600);
  delay(100);

  //Wait for motor to finish initiation routine - If you give commands to motor on power on it may behave irratically
  pinMode(led, OUTPUT);    //Setup LED pin as output
  digitalWrite(led, LOW);    //LED On
  delay(5000);
  digitalWrite(led, HIGH);

  //Serial.println("X");    //Auto Calibration command, Required only once when using motor for the first time, after running onces parameters are stored in motor controller.
  //delay(5000);            //Wait for 5 Seconds for calibration
  //
  //  Serial.println("E125");    //Set I2C slave address for motor. If more than one motor is to be controlled on I2C bus every motor needs different address which can be set using this command.
  //                             //Required only once when using motor for the first time, after running onces parameters are stored in motor controller.
  //  delay(500);                //Allow to store setting
  //
  //
  //Serial1.println("X");
  delay(100);
  //Serial2.println("X");
  //delay(5000);
  Serial1.println("Y");
  Serial.println("M1: Y");
  delay(100);
  Serial2.println("Y");
  Serial.println("M2: Y");
  delay(3000);
  Serial1.println("M255");  //Set maximum speed of motor, useful when using G command for going to specific encoder position.
  Serial.println("M1: M255");
  delay(100);
  Serial2.println("M255");
  Serial.println("M2: M255");
  delay(1000);              //Allow to store setting
  Serial1.println("D5");
  Serial.println("M1: D5");
  delay(100);
  Serial2.println("D5");
  Serial.println("M2: D5");
  delay(1000);
  Serial1.println("G475");  //Set damping - acceleration and decceleration
  Serial.println("M1: G475");
  delay(1000);
  //Serial2.println("S100");
  //delay(2000);
  Serial2.println("G700");
  Serial.println("M2: G700");
  delay(2000);
  //Allow to store setting
  currentMillis = millis();
}

void beat() {
  Serial1.println("G475");
  Serial2.println("G700");
  Serial.println("M1: G700");
  Serial.println("M2: G700");
  delay(125);
  Serial1.println("G-200");
  Serial2.println("G650");
  Serial.println("M1: G-200");
  Serial.println("M2: G650");
  //delay(5);
}

void beatM2() {
  Serial2.println("G700");
  Serial.println("M2: G700");
  delay(60);
  Serial2.println("G300");
  Serial.println("M2: G-200");
  //delay(5);
}

void setMotorSpeed() {
  uint16_t temp = analogRead(potPin);
  uint16_t tempMap = map(temp, 512, 1023, 0, 255);
  if (tempMap > (currentPot + hysterysis) || tempMap < (currentPot - hysterysis)) {
    currentPot = tempMap;
    //Serial.print("S");
    //Serial.println(currentPot);
    snprintf (buf, 10, "S%d", currentPot);
    //Serial.println(buf);
    //return currentPot;
  }
  //else return currentPot;
}

void seq1() {
  delay(200);
  beat();
  delay(150);
  beat();
  delay(150);
  beat();
  delay(200);
  beat();
  delay(150);
  beat();
  delay(225);
  beat();
}

void seq2() {
  delay(170);
  beat();
  delay(200);
  beat();
  delay(300);
  beat();
  delay(200);
  beat();
  delay(400);
  beat();
  delay(225);
  beat();
}

void seq3() {
  delay(300);
  beat();
  delay(250);
  beat();
  delay(100);
  beat();
  delay(70);
  beat();
  delay(100);
  beat();
  delay(50);
  beat();
}

void seqM2_1() {
  delay(200);
  beatM2();
  delay(150);
  beatM2();
  delay(150);
  beatM2();
  delay(200);
  beatM2();
  delay(150);
  beatM2();
  delay(225);
  beatM2();
}

void seqM2_2() {
  delay(170);
  beatM2();
  delay(200);
  beatM2();
  delay(300);
  beatM2();
  delay(200);
  beatM2();
  delay(400);
  beatM2();
  delay(225);
  beatM2();
}

void seqM2_3() {
  delay(300);
  beatM2();
  delay(250);
  beatM2();
  delay(100);
  beatM2();
  delay(70);
  beatM2();
  delay(100);
  beatM2();
  delay(50);
  beatM2();
}

void loop() {
  if (millis() - currentMillis > delayMillis) {
    //setMotorSpeed();

    if (ledState == HIGH) {
      ledState = LOW;
      digitalWrite(led, ledState);

    }
    else if (ledState == LOW) {
      ledState = HIGH;
      digitalWrite(led, ledState);

    }
    currentMillis = millis();

  }

  for (int n = 0 ; n < 4 ; n++) {

    switch (n) {
      case 1:
        seq2();
        //delay(10);
        //seqM2_2();
        break;

      case 2:
        seq3();
        //delay(10);
        //seqM2_3();
        break;

      default:
        seq1();
        //delay(10);
        //seqM2_1();
        break;
    }
  }


  //  delay(200);
  //  beat();
  //  delay(150);
  //  beat();
  //  delay(150);
  //  beat();
  //  delay(200);
  //  beat();
  //  delay(150);
  //  beat();
  //  delay(225);
  //  beat();

}

//Serial.println("M255");  //Set maximum speed
//Serial.println("G214000000");  //Go to Encoder Position 3600 - 2 rotations
//delay(100);

//  Serial.println("M125");  //Set maximum speed
//  Serial.println("G3600");  //Go to Encoder Position 3600 - 2 rotations
//  delay(100);
//
//  Serial.println("M50");  //Set slow speed
//  Serial.println("G3600");     //Go back to encoder position 0
//  delay(100);
//
//  Serial.println("M20");  //Set maximum speed
//  Serial.println("G3600");  //Go to Current Encoder Position + 1800 counts (relative position - go +1800 counts from current position)
//  delay(100);
//
//  Serial.println("M10");    //Set slow speed
//  Serial.println("G3600"); //Go to Current Encoder Position - 100 counts (relative position - go -1000 counts from current position)
//  delay(100);


/*
  //Following commands (S) run motor at constand speed at with given acceleration-decceleration without position control, however it uses encoder to regulate speed.
  Serial.println("S255");    //Run motor at max speed - 255 in forward direction
  digitalWrite(led, 1);
  delay(5000);

  Serial.println("S-50");    //Run motor in rever at 50 speed
  digitalWrite(led, 0);
  delay(5000);

  Serial.println("S0");    //Speed 0, stop motor
  delay(100);

  Serial.println("P0");    //Set current encoder position as 0
  delay(2000);

*/
