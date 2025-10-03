# esp32-sensorjarakdanbuzzer

| Nama                         | Nrp        |
| ---------------------------- | ---------- |
| Evan Christian Nainggolan  | 5027241053 |
| Oscaryavat Viryavan          | 5027241053 |

# 🚀 IoT Ultrasonic Distance Monitoring dengan ESP32 + ThingSpeak

<img width="700" height="400" alt="" src="https://github.com/user-attachments/assets/74f879be-217a-466a-990b-5b20627aeaa0" />

## Deskripsi
Proyek ini menggunakan **ESP32**, **sensor ultrasonik (HC-SR04)**, dan **buzzer** untuk mendeteksi jarak objek.  
Jika jarak objek **kurang dari 15 cm**, buzzer akan berbunyi.  
Data jarak yang terbaca juga dikirimkan ke **ThingSpeak** agar dapat dipantau secara real-time melalui grafik.

## Komponen yang Digunakan
- ESP32 DevKit (WiFi + IoT Ready)
- Sensor Ultrasonik HC-SR04
- Buzzer aktif
- Breadboard & Kabel Jumper
- ThingSpeak Account (gratis)

## 🛠️ Rangkaian
- **HC-SR04 TRIG** → GPIO 3 (ESP32)  
- **HC-SR04 ECHO** → GPIO 2 (ESP32)  
- **Buzzer** (+) → GPIO 5 (ESP32)  
- **Buzzer** (–) → GND (ESP32)  
- VCC HC-SR04 → 5V ESP32  
- GND HC-SR04 → GND ESP32  

## 💻 Kode Program
Kode lengkap ada di file [`main.ino`](./main.ino).  
Fitur utama:
- Membaca jarak menggunakan **ultrasonik**  
- Jika `distance < 15 cm`, buzzer berbunyi  
- Mengirim data jarak ke **ThingSpeak Channel** setiap 20 detik  

## 📊 Hasil di ThingSpeak
Data akan tampil dalam grafik seperti berikut:

![ThingSpeak Chart](https://thingspeak.com/channels/3095428/charts/1)

## 🔑 Konfigurasi
Sebelum upload, ubah bagian berikut pada kode:
```cpp
const char* ssid = "NAMA_WIFI";          // Ganti dengan SSID WiFi
const char* password = "PASSWORD_WIFI";  // Ganti dengan password WiFi
unsigned long myChannelNumber = XXXXXXX; // Ganti dengan Channel ID
const char * myWriteAPIKey = "XXXXXXXX"; // Ganti dengan Write API Key
