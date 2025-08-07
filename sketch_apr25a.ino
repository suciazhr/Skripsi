#include <math.h> // untuk log10()

// Konfigurasi pin dan konstanta
const int sensorPin = A1;                // Pin analog untuk sensor GUVA-S12SD
const float Vref = 3.3;                  // Tegangan referensi Arduino
const int jumlahSampel = 100;            // Jumlah pembacaan untuk averaging
const float intensitasAwal = 8;      // Intensitas awal (

void setup() {
  Serial.begin(9600);
  Serial.println("Sensor GUVA-S12SD: Intensitas UV, UV Index & Absorbansi");
}

void loop() {
  // === Averaging pembacaan ADC ===
  long totalADC = 0;
  for (int i = 0; i < jumlahSampel; i++) {
    totalADC += analogRead(sensorPin);
    delay(50);
  }
  float rataADC = totalADC / (float)jumlahSampel;

  // === Konversi ke tegangan (V) ===
  float tegangan = (rataADC * Vref) / 1023.0;

  // === Hitung intensitas UV (mW/cm²) ===
  float intensitasUV = 22.3051 * tegangan - 2.3185;  // Berdasarkan hasil kalibrasi

  // === Konversi ke tegangan (mV) ===
  float teganganmV = tegangan * 1000.0;


  // === Hitung Absorbansi ===
  float absorbansi = 0;
  if (intensitasUV > 0) {
    absorbansi = log10(intensitasAwal / intensitasUV);
  } else {
    absorbansi = 0;  // Hindari log10(0) jika sensor belum membaca nilai valid
  }

  // === Tampilkan hasil ke Serial Monitor ===
  Serial.print("ADC: ");
  Serial.print(rataADC);
  Serial.print(" | Tegangan: ");
  Serial.print(tegangan, 3);
  Serial.print(" V | Tegangan: ");
  Serial.print(teganganmV, 1);
  Serial.print(" mV | Intensitas: ");
  Serial.print(intensitasUV, 2);
  Serial.print(" | Absorbansi: ");
  Serial.println(absorbansi, 3);

  delay(1000); // jeda antar pembacaan
}
