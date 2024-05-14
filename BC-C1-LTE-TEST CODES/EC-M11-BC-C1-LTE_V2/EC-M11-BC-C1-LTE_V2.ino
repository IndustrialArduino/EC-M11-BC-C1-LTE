// EC-M11-EG-C1
/*
 * Analog Input Test
 * Digital Input Test
 * RS-485 Serial print
 * 12V Booster Enable / Disable
 * 
 */
#include <Adafruit_ADS1X15.h>

#define DIGITAL_IN1 35

#define I2C_SCL 17
#define I2C_SDA 16

#define ADS1115_INT 21

Adafruit_ADS1115 ads1;

void setup() {
  Serial.begin(115200);
  Wire.begin(16,17);

  Serial.println("The device is powered up");
  
  pinMode(35, INPUT);    // Digital Input 1
  pinMode(21, INPUT);    // ADS1115 Interrupt

  pinMode(36, INPUT);    // Analog input-battery voltage monitor 
  pinMode(13, OUTPUT);    // 12V boosted output enable
  
  if (!ads1.begin(0x49)) {
    Serial.println("Failed to initialize ADS 1 .");
    while (1);
  }
}

void loop() {
  Serial.print("\nI1: ");Serial.println(digitalRead(35));
  
  int16_t adc0, adc1, adc2, adc3;
  adc0 = ads1.readADC_SingleEnded(0);
  adc1 = ads1.readADC_SingleEnded(1);
  adc2 = ads1.readADC_SingleEnded(2);
  adc3 = ads1.readADC_SingleEnded(3);

  Serial.println("-----------------------------------------------------------");
  Serial.print("AIN1: "); Serial.print(adc0); Serial.println("  ");
  Serial.print("AIN2: "); Serial.print(adc1); Serial.println("  ");
  Serial.print("SOLAR: "); Serial.print(adc2); Serial.println("  ");

  Serial.print("Battery Voltage: ");Serial.println(readBattery());
  delay(800);
}

int readBattery(){
  unsigned int analog_value;
  analog_value = analogRead(36);
  return analog_value;
}
