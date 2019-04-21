#include "DHT.h"

// Temp && Humidity
#define DHTPIN 7     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

// CO2
const int AOUTpin=0;
const int DOUTpin=8;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(DOUTpin, INPUT);
  dht.begin();
}

void loop() {
  // Wait one second between measurements
  delay(1000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Read co2
  int co2 = analogRead(AOUTpin);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  Serial.print(F("Humidity "));
  Serial.print(h);
  Serial.print(F(";Temperature "));
  Serial.print(t);
  Serial.print(F(";CO "));
  Serial.print(co2);
  Serial.println("#");
}
