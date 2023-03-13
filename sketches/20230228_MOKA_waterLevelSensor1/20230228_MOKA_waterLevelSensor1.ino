// How Water Level Sensor Works and Interface it with Arduino
// See also: https://lastminuteengineers.com/water-level-sensor-arduino-tutorial/

// Last update: Tue Feb 28 12:38:34 AST 2023

// Sensor pins
#define sensorPower 6
#define sensorPin A4

#define WLS_L 250
#define WLS_H 500

// Value for storing water level
int val = 0;

void setup() {
  // Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW); // Set to LOW so no power flows through the sensor
  Serial.begin(57600);
}

void loop() {
  //get the reading from the function below and print it
  int level = readSensor();
  
  Serial.print("Water level: ");
  Serial.println(level);
  
  delay(200);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  val = analogRead(sensorPin);    // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // send current reading
}
