# 🌦️ Weather Monitoring System dengan ESP8266

Proyek ini adalah sistem pemantauan cuaca berbasis **ESP8266**, yang mengukur **suhu, tekanan udara, intensitas cahaya, kecepatan angin**, dan **mendeteksi hujan**. Data ditampilkan di **LCD** dan dikirim ke **Telegram** secara otomatis! 📡📲

---

## 🛠️ Perangkat Keras yang Digunakan
✅ **ESP8266** (NodeMCU) - Otak dari proyek ini
✅ **BMP280** - Sensor suhu & tekanan udara 🌡️
✅ **BH1750** - Sensor intensitas cahaya ☀️
✅ **Sensor Hujan** - Mendeteksi curah hujan 🌧️
✅ **Sensor Kecepatan Angin** - Mengukur kecepatan angin 💨
✅ **LCD I2C 16x2** - Menampilkan data secara real-time 📟
✅ **Kabel Jumper & Breadboard** - Untuk koneksi perangkat

---

## 🔧 Instalasi dan Penggunaan

### 1️⃣ Persiapan Perangkat Lunak
💾 Pastikan Anda sudah menginstal **Arduino IDE**
🛠️ Tambahkan board **ESP8266** melalui Board Manager
📥 Instal library berikut via Library Manager di Arduino IDE:
  - `Adafruit BMP280`
  - `BH1750`
  - `LiquidCrystal I2C`
  - `UniversalTelegramBot`

### 2️⃣ Koneksi Perangkat Keras
Hubungkan perangkat sesuai dengan tabel berikut:

| Perangkat | Pin ESP8266 |
|-----------|------------|
| BMP280    | I2C (SDA, SCL) |
| BH1750    | I2C (SDA, SCL) |
| Sensor Hujan | D1 |
| Sensor Kecepatan Angin | D5 |
| LCD 16x2 | I2C (SDA, SCL) |

### 3️⃣ Konfigurasi WiFi & Telegram
🔹 Ubah `ssid` dan `password` dengan informasi WiFi Anda.
🔹 Masukkan `botToken` dari Bot Telegram.
🔹 Gunakan **@userinfobot** di Telegram untuk mendapatkan `chatID`.

### 4️⃣ Unggah Kode ke ESP8266
🔌 Sambungkan ESP8266 ke PC
⚙️ Pilih board **NodeMCU 1.0** di Arduino IDE
🚀 Unggah kode

---

## 📌 Cara Kerja
1️⃣ ESP8266 membaca data dari sensor **suhu, tekanan, cahaya, kecepatan angin, dan hujan**. 
2️⃣ Data ditampilkan di **LCD** dalam waktu nyata. 
3️⃣ Data dikirim ke **Telegram** setiap **10 detik**.

---

## 📋 Contoh Output di Telegram 📲
```
🌡️ Data Sensor Cuaca 🌡️
Suhu: 25.3°C
Tekanan: 1013 hPa
Intensitas Cahaya: 300 lx
Kecepatan Angin: 2.5 km/s
Sensor Hujan: Tidak Ada Hujan ☀️
```
🔌 Diagram Rangkaian

Berikut adalah diagram rangkaian sistem pemantauan cuaca:

![schematic](https://github.com/user-attachments/assets/637be179-84f9-41e6-b72b-caf6161eeb59)
---

## 🚀 Pengembangan Lebih Lanjut
💡 **Tambahkan fitur prediksi cuaca** menggunakan AI 📊
💾 **Simpan data ke server atau Google Sheets** untuk analisis jangka panjang ☁️
🔋 **Gunakan tenaga surya** agar lebih ramah lingkungan 🌱

📢 Jangan ragu untuk bereksperimen dan meningkatkan proyek ini! Semoga bermanfaat! 😊🚀
