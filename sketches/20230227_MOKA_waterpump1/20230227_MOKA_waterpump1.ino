
// 20230227_MOKA_waterpump1.ino

// Last update: Mon Feb 27 16:40:02 AST 2023

// pins for the LEDs
const int LEDpins[3] = {11, 10, 9};
int LEDs[3] = {0, 0, 0};

// pins for pumpus and solenoides
const int Xpins[3] = {2, 3, 4};
boolean Xprev[3] = { false, false, false };

// pins for water level sensor
const int WLSpins[3] = {A3, A4, A5};
const int WLSpows[3] = {7, 6, 5};
int WLSvals[3] = {0, 0, 0};
const int WLS_LOW = 250;
const int WLS_HIGH = 500;
int WLSlimit[3] = {350, 350, 350};

// pins for the Buttons
const int SWpins[3] = {A3, A4, A5};

// pins for the Potentiometers
const int POTpins[3] = {A0, A1, A2};

void setup() {
  // initialize serial:
  Serial.begin(57600);
  // make the LEDLEDpins outputs:
  for (int i = 0; i <= 2; i++) {
    pinMode(LEDpins[i], OUTPUT);
    digitalWrite(LEDpins[i], LOW);
    pinMode(Xpins[i], OUTPUT);
    digitalWrite(Xpins[i], HIGH); // negative logic
    pinMode(SWpins[i], INPUT);
    pinMode(WLSpows[i], OUTPUT);
    digitalWrite(WLSpows[i], LOW);
  }
}

void loop() {}

void loop2() {
  // print keyword and millis
  Serial.print("SW/Pot\t");
  Serial.print(millis()); Serial.print("\t");

  // print six numbers (three sets of Buttons and Pots) in one string with TABs:
  for (int i = 0; i <= 2; i++) {
    pinMode(SWpins[i], INPUT_PULLUP);
    boolean x = (digitalRead(SWpins[i]) == LOW);
    pinMode(SWpins[i], INPUT);
    int s = readWLS(WLSpows[i], WLSpins[i]);
    if (false /*s < WLSlimit[i]*/) {
      // digitalWrite(Xpins[i], HIGH);
    } else {
      if ( x != Xprev[i] ) {
        // Any change in the status of this button is reflected in the LED and pump/solenoid.
        analogWrite(LEDpins[i], x ? 0 : 255);
        digitalWrite(Xpins[i], x ? LOW : HIGH);
        Xprev[i] = x;
      }
    }
    Serial.print(s); Serial.print("\t");
    Serial.print(x); Serial.print("\t");
    Serial.print(analogRead(POTpins[i])); Serial.print("\t");
  }
  Serial.println();

  if (Serial.available() > 0) {
    //
    uint32_t d = millis();
    while (Serial.available() > 0) {
      // Suppose every line contains three sets of numbers.
      for (int i = 0; i <= 2; i++) {
        // If the number of digits in a line is not a multiple of 3,
        // then one or two single line breaks must be entered.
        // See also: https://www.arduino.cc/reference/en/language/functions/communication/serial/parseint/
        LEDs[i] = Serial.parseInt();
      }
      if (Serial.read() == '\n') {
        Serial.print("LED\t");
        Serial.print(millis()); Serial.print("\t");
        // Fade the three LEDs and print the three numbers in one line separated by TABs:
        for (int i = 0; i <= 2; i++) {
          // constrain the values to 0 - 255
          LEDs[i] = constrain(LEDs[i], 0, 255);
          analogWrite(LEDpins[i], 255 - LEDs[i]);
          digitalWrite(Xpins[i], (LEDs[i] > 127) ? LOW : HIGH); // Negative logic
          Serial.print(LEDs[i]); Serial.print("\t");
        }
        Serial.println();
      }
    }
  } else {
    delay(200);
  }
}

//This is a function used to get the reading
int readWLS(int _sensorPower, int _sensorPin) {
  digitalWrite(_sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  int _val = analogRead(_sensorPin);    // Read the analog value form sensor
  digitalWrite(_sensorPower, LOW);   // Turn the sensor OFF
  return _val;             // send current reading
}
