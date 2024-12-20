#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

// Konfigurasi WiFi
const char* ssid = "Not Found";  // SSID WiFi
const char* password = "gejok1221";  // Password WiFi

// Konfigurasi Telegram
const char* botToken = "7781671344:AAFOr4pL0G_DhSGFmqUTpcJvlXwQSMu7oK4";  // Token bot
const char* chatID = "1330911879";  // Chat ID pengguna

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

// Deklarasi sensor
Adafruit_BMP280 bmp;
BH1750 lightMeter(0x23);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin sensor
const int rainSensorPin = D1;
const int speedSensorPin = D5;  // Pin untuk sensor kecepatan (speed counter)

// Variabel untuk data sensor
float temperature, pressure, lightLevel, speed;
int rainValue;

// Variabel untuk menghitung kecepatan
volatile unsigned int pulseCount = 0;
unsigned long lastMillis = 0;
float speedValue = 0.0;

// Fungsi ISR untuk menghitung pulsa dari sensor kecepatan
void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  client.setInsecure();

  // Koneksi WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nTerhubung ke WiFi");

  // Inisialisasi LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Inisialisasi...");

  // Inisialisasi sensor BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 tidak terdeteksi!");
    lcd.print("BMP280 Error!");
    while (1);
  }

  // Inisialisasi sensor BH1750
  if (!lightMeter.begin()) {
    Serial.println("BH1750 tidak terdeteksi!");
    lcd.print("BH1750 Error!");
    while (1);
  }

  // Konfigurasi pin
  pinMode(rainSensorPin, INPUT);
  pinMode(speedSensorPin, INPUT_PULLUP);
  
  // Attach interrupt untuk sensor kecepatan
  attachInterrupt(digitalPinToInterrupt(speedSensorPin), countPulse, RISING);
}

void getSensorData() {
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure() / 100.0F;
  rainValue = digitalRead(rainSensorPin);
  lightLevel = lightMeter.readLightLevel();

  // Hitung kecepatan
  unsigned long currentMillis = millis();
  unsigned long interval = currentMillis - lastMillis;
  
  if (interval >= 1000) {  // Hitung setiap 1 detik
    speedValue = (pulseCount / 20.0);  // Contoh perhitungan untuk kecepatan
    pulseCount = 0;
    lastMillis = currentMillis;
  }
}

void sendTelegramMessage() {
  String message = "Data Sensor:\n";
  message += "Suhu: " + String(temperature) + " C\n";
  message += "Tekanan: " + String(pressure) + " hPa\n";
  message += "Intensitas Cahaya: " + String(lightLevel) + " lx\n";
  message += "Kecepatan: " + String(speedValue) + " km/s\n";
  message += "Sensor Hujan: ";
  message += (rainValue == LOW ? "Terdeteksi Hujan" : "Tidak Ada Hujan");
  
  bot.sendMessage(chatID, message, "");
}

void displayDataOnLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Suhu: " + String(temperature) + "C");
  lcd.setCursor(0, 1);
  lcd.print("Tek: " + String(pressure) + "hPa");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cahaya: " + String(lightLevel) + "lx");
  lcd.setCursor(0, 1);
  lcd.print("Kecepatan: " + String(speedValue) + "km/s");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hujan: ");
  lcd.print((rainValue == LOW ? "Ya" : "Tidak"));
  delay(1000);
}

void loop() {
  getSensorData();
  displayDataOnLCD();
  sendTelegramMessage();
  delay(10000);  // Kirim data setiap 10 detik
}