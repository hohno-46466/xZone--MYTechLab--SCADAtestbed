
// 20230227_MOKA_waterpump1.ino

// Last update: Mon Feb 27 16:40:02 AST 2023

#define LOOP_INTERVAL (200)

// pins for the LEDs (negative logic)
const int LEDpins[3] = {11, 10, 9};
int LEDs[3] = {0, 0, 0};

// pins for the pumps and solenoides (negative logic)
const int Xpins[3] = {4, 3, 2};
boolean Xprev[3] = {false, false, false};

// pins for WLS (water level sensor)
const int WLSpins[3] = {A3, A4, A5};
const int WLSpows[3] = {8, 12, 13};
int WLSvals[3] = {0, 0, 0};
const int WLS_LOW = 250; // Lower limit of WLS
const int WLS_HIGH = 500; // Upper limit of WLS
const int WLS_NOC = 800;  // if value is higher than this, WLS is not connected.
int WLSlimit[3] = {400, 400, 400};

// pins for the Buttons (negative logic)
const int SWpins[3] = {7, 6, 5};

// pins for the Potentiometers (analog value)
const int POTpins[3] = {A0, A1, A2};

void setup() {
  // make the LEDLEDpins outputs:
  for (int i = 0; i <= 2; i++) {
    pinMode(SWpins[i], INPUT_PULLUP);
    pinMode(LEDpins[i], OUTPUT); digitalWrite(LEDpins[i], HIGH);
    pinMode(Xpins[i], OUTPUT);   digitalWrite(Xpins[i], HIGH);
    pinMode(WLSpows[i], OUTPUT); digitalWrite(WLSpows[i], LOW);
  }
  // initialize serial:
  Serial.begin(57600);
  // LED blink 
  boolean f = false;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j <= 2; j++) { digitalWrite(LEDpins[j], f); }; 
    f = !f;
    delay(200);
  }
}

void loop() {
  // print keyword and millis
  Serial.print("SW/Pot\t");
  Serial.print(millis()); Serial.print("\t");

  // print numbers (three sets of Buttons and Pots) in one string with TABs:
  for (int i = 0; i <= 2; i++) {
    boolean ss = (digitalRead(SWpins[i]) == LOW); // switch status
    int wl = readWLS(WLSpows[i], WLSpins[i]); // water level
    boolean flagStop = ((wl < WLS_NOC) && (wl > WLSlimit[i])) ? true : false;
    if (flagStop) {
      digitalWrite(Xpins[i], HIGH); // stop the pump
    } else {
      if (ss != Xprev[i]) {
        // Any change in the status of this button is reflected in the LED and pump/solenoid.
        analogWrite(LEDpins[i], ss ? 0 : 255);  // 0: LED on, 255: LED off
        digitalWrite(Xpins[i], ss ? LOW : HIGH); // LOW: pump on, HIGH: pump off
      }
      Xprev[i] = ss;
    }
    Serial.print(ss); Serial.print("\t"); // 1: SW on, 0: SW off
    Serial.print(wl); Serial.print("\t"); // water level
    Serial.print(flagStop); Serial.print("\t"); // 1: forced stop, 0: not stopped
    Serial.print(analogRead(POTpins[i])); Serial.print("\t");
  }
  Serial.println();

  if (Serial.available() > 0) {
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
          LEDs[i] = constrain(LEDs[i], 0, 255); // constrain the values to 0 - 255
          analogWrite(LEDpins[i], 255 - LEDs[i]);
          digitalWrite(Xpins[i], (LEDs[i] > 127) ? LOW : HIGH); // Negative logic
          Serial.print(LEDs[i]); Serial.print("\t");
        }
        Serial.println();
      }
    }
  } else {
    // if nothing is read from serial port, just wait 200msec
    delay(LOOP_INTERVAL);
  }
}

int readWLS(int _sensorPower, int _sensorPin) {
  digitalWrite(_sensorPower, HIGH); // Turn the sensor ON
  delay(10); // wait 10 msec
  int _val = analogRead(_sensorPin); // Read the analog value form sensor
  digitalWrite(_sensorPower, LOW);   // Turn the sensor OFF
  return (_val); // send current reading
}
