
// 20230227_MOKA_waterpump1.ino

// Last update: Mon Feb 27 16:40:02 AST 2023

// pins for the LEDs
const int LEDpins[3] = {11, 10, 9};
int LEDs[3] = {0, 0, 0};
boolean Xprev[3] = { false, false, false };
const int Xpins[3] = {2, 3, 4};

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
    pinMode(Xpins[i], OUTPUT);
    pinMode(SWpins[i], INPUT_PULLUP);
  }
}

void loop() {
  // print keyword and millis
  Serial.print("SW/Pot\t");
  Serial.print(millis()); Serial.print("\t");

  // print six numbers (three sets of Buttons and Pots) in one string with TABs:
  for (int i = 0; i <= 2; i++) {
    boolean x = digitalRead(SWpins[i]);
    if ( x != Xprev[i] ) {
      analogWrite(LEDpins[i], x ? 255 : 0);
      digitalWrite(Xpins[i], x ? HIGH : LOW);
      Xprev[i] = x;
    }
    Serial.print(x); Serial.print("\t");
    Serial.print(analogRead(POTpins[i])); Serial.print("\t");
  }
  Serial.println();

  if (Serial.available() > 0) {
    uint32_t d = millis();
    while (Serial.available() > 0) {
      for (int i = 0; i <= 2; i++) {
        LEDs[i] = Serial.parseInt();
      }
      if (Serial.read() == '\n') {
        Serial.print("LED\t");
        Serial.print(millis()); Serial.print("\t");
        // fade the three LEDs and print the three numbers in one string with TABs:
        for (int i = 0; i <= 2; i++) {
          // constrain the values to 0 - 255
          LEDs[i] = constrain(LEDs[i], 0, 255);
          analogWrite(LEDpins[i], 255 - LEDs[i]);
          digitalWrite(Xpins[i], (LEDs[i] > 240) ? LOW : HIGH);
          Serial.print(LEDs[i]); Serial.print("\t");
        }
        Serial.println();
      }
    }
  } else {
    delay(200);
  }
}
