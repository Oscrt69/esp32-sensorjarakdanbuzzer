#include <WiFi.h>
#include "ThingSpeak.h"

// --- Pengaturan Jaringan ---
const char* ssid = "MODALNAPA";         
const char* password = "MAKASILAN";  

// --- Pengaturan ThingSpeak ---
unsigned long myChannelNumber = 3095428;      
const char * myWriteAPIKey = "YQ68HMUJ07A3JLDM"; 
WiFiClient client;

// --- Pengaturan Pin Hardware ---
#define PIN_TRIG 3
#define PIN_ECHO 2
#define PIN_BUZZER 5 // Pin untuk Buzzer

void setup() {
  Serial.begin(115200);
  Serial.println("Memulai program...");

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, HIGH); // Pastikan buzzer mati di awal

  // --- Koneksi ke WiFi ---
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Terhubung!");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());

  // Inisialisasi ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // --- Bagian Pembacaan Sensor (Tidak berubah) ---
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  long duration = pulseIn(PIN_ECHO, HIGH);
  float distanceCM = duration / 58.0;

  // Tampilkan hasil di Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distanceCM);
  Serial.println(" cm");

  // --- Logika Buzzer (Tidak berubah, tetap Active LOW) ---
  if (distanceCM <= 15 && distanceCM > 0) {
    digitalWrite(PIN_BUZZER, LOW);
  } else {
    digitalWrite(PIN_BUZZER, HIGH);
  }

  // --- Mengirim Data ke ThingSpeak ---
  // Hanya kirim jika jaraknya valid (lebih besar dari 0)
  if (distanceCM > 0) {
    // Set Field 1 dengan nilai jarak
    ThingSpeak.setField(1, distanceCM);
    
    // Tulis data ke ThingSpeak
    int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (httpCode == 200) {
      Serial.println("Data berhasil dikirim ke ThingSpeak.");
    } else {
      Serial.println("Gagal mengirim data. Error: " + String(httpCode));
    }
  } else {
    Serial.println("Data jarak tidak valid, pengiriman dibatalkan.");
  }
  
  delay(20000); 
}
