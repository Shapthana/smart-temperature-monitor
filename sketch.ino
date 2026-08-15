#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define LEDPIN 8
#define WINDOW_SIZE 5

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float readings[WINDOW_SIZE];
int readingIndex = 0;
int readingCount = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(LEDPIN, OUTPUT);
  randomSeed(analogRead(0));

  lcd.setCursor(0, 0);
  lcd.print("Smart Temp Mon.");
  delay(1500);
  lcd.clear();
}

float getRollingAverage() {
  float sum = 0;
  for (int i = 0; i < readingCount; i++) {
    sum += readings[i];
  }
  return sum / readingCount;
}

void loop() {
  // TEST MODE: simulate random temp/humidity instead of reading real sensor
  float temp = dht.readTemperature();
float humidity = dht.readHumidity();

  // "Feels like" temperature, factoring in humidity
  float heatIndex = dht.computeHeatIndex(temp, humidity, false);

  // Store heat index (not raw temp) in rolling window
  readings[readingIndex] = heatIndex;
  readingIndex = (readingIndex + 1) % WINDOW_SIZE;
  if (readingCount < WINDOW_SIZE) readingCount++;

  float avgHeatIndex = getRollingAverage();
  float threshold = avgHeatIndex + 2.0;

  bool fanOn = heatIndex > threshold;
  digitalWrite(LEDPIN, fanOn ? HIGH : LOW);

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print(" H:");
  lcd.print(humidity, 0);
  lcd.print("%  ");

  lcd.setCursor(0, 1);
  lcd.print("Feels:");
  lcd.print(heatIndex, 1);
  lcd.print(" ");
  lcd.print(fanOn ? "ON " : "OFF");

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" | Humidity: ");
  Serial.print(humidity);
  Serial.print(" | Heat Index: ");
  Serial.print(heatIndex);
  Serial.print(" | Avg: ");
  Serial.print(avgHeatIndex);
  Serial.print(" | Threshold: ");
  Serial.print(threshold);
  Serial.print(" | Fan: ");
  Serial.println(fanOn ? "ON" : "OFF");

  delay(2000);
}
