# esp32-sensorjarakdanbuzzer

| Nama                         | Nrp        |
| ---------------------------- | ---------- |
| Evan Christian Nainggolan  | 5027241026 |
| Oscaryavat Viryavan          | 5027241053 |

# 🚀 IoT Ultrasonic Distance Monitoring dengan ESP32 + ThingSpeak

<img width="300" height="700" alt="" src="https://github.com/user-attachments/assets/74f879be-217a-466a-990b-5b20627aeaa0" />

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

<img width="700" height="3750" src="https://github.com/user-attachments/assets/d923a4a0-8e31-4197-ae94-d9972f792b99"/>

## 🔑 Konfigurasi
Sebelum upload, ubah bagian berikut pada kode:
```cpp
const char* ssid = "NAMA_WIFI";          // Ganti dengan SSID WiFi
const char* password = "PASSWORD_WIFI";  // Ganti dengan password WiFi
unsigned long myChannelNumber = XXXXXXX; // Ganti dengan Channel ID
const char * myWriteAPIKey = "XXXXXXXX"; // Ganti dengan Write API Key
```

## Penjelasan Cara Kerja Kode 👨‍💻
---

### `setup()`
Fungsi `setup()` berjalan sekali saat ESP32 pertama kali dinyalakan atau di-reset.
* **Inisialisasi**: Memulai komunikasi `Serial` untuk *debugging*, mengatur mode pin untuk sensor (`TRIG` sebagai `OUTPUT`, `ECHO` sebagai `INPUT`), dan buzzer (sebagai `OUTPUT`).
* **Koneksi WiFi**: Mencoba terhubung ke jaringan WiFi menggunakan SSID dan password yang telah ditentukan. Proses ini akan ditampilkan di Serial Monitor.
* **Inisialisasi ThingSpeak**: Memulai koneksi klien ke server ThingSpeak.

### `loop()`
Fungsi `loop()` berjalan terus-menerus setelah `setup()` selesai.
* **Membaca Sensor**:
    * ESP32 mengirimkan sinyal ultrasonik pendek melalui pin `TRIG`.
    * Kemudian, ia "mendengarkan" pantulan sinyal tersebut melalui pin `ECHO`.
    * Waktu yang dibutuhkan sinyal untuk kembali (`duration`) diukur dan dikonversi menjadi jarak dalam sentimeter.
* **Logika Buzzer**:
    * Program memeriksa apakah jarak yang terukur kurang dari atau sama dengan 15 cm.
    * Jika ya, ia akan mengirim sinyal `LOW` ke buzzer untuk menyalakannya (karena modul buzzer ini bersifat **Active LOW**).
    * Jika tidak, ia akan mengirim sinyal `HIGH` untuk memastikan buzzer tetap mati.
* **Mengirim Data ke ThingSpeak**:
    * Program mengirimkan nilai jarak (`distanceCM`) ke `Field 1` di channel ThingSpeak Anda.
    * Program akan memeriksa status pengiriman. Jika berhasil, server akan merespons dengan kode `200`, yang akan ditampilkan di Serial Monitor.
* **Delay**:
    * Program akan berhenti selama **20 detik** (`delay(20000)`). Jeda ini sangat penting karena versi gratis ThingSpeak membatasi pengiriman data kira-kira setiap 15 detik. Jeda 20 detik memastikan kita tidak melanggar batas tersebut.
