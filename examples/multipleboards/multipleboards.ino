/*
 * This example demonstrates how to configure two Adc4One boards. One is a 12 bit
 * board and the other one is a 16 bit board. The 12 bit hardware is wired to respond
 * to 0x48 addresses and the 16 bit board is wired to respond to 0x49 addresses.
 */
#include <Wire.h>
#include <Adc4One.h>

#define SCL_PIN      14
#define SDA_PIN      2

Adc4One ads12(ADS1015_ADDRESS);     /* This is the 12 bit board object (address 0x48) */
Adc4One ads16(ADS1015_ADDRESS_1);   /* And this is the 16 bit board (address 0x49) */

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from multiple Adc4One boards on channels AIN0..7");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // Before we start using the ADS instances we need to configure the ADC type.
  ads12.init();         // Default is ADS1015 (The 12 bit A/D)
  ads16.init(ADS1115);  // Initialize this object to handle the 16 bit A/D
 
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  Wire.begin(SDA_PIN, SCL_PIN);
}

void loop(void) 
{
  int16_t adc0, adc1, adc2, adc3;

  adc0 = ads12.readADC_SingleEnded(0);
  adc1 = ads12.readADC_SingleEnded(1);
  adc2 = ads12.readADC_SingleEnded(2);
  adc3 = ads12.readADC_SingleEnded(3);

  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("AIN3: "); Serial.println(adc3);

  adc0 = ads16.readADC_SingleEnded(0);
  adc1 = ads16.readADC_SingleEnded(1);
  adc2 = ads16.readADC_SingleEnded(2);
  adc3 = ads16.readADC_SingleEnded(3);

  Serial.print("AIN4: "); Serial.println(adc0);
  Serial.print("AIN5: "); Serial.println(adc1);
  Serial.print("AIN6: "); Serial.println(adc2);
  Serial.print("AIN7: "); Serial.println(adc3);
  
  Serial.println(" ");
  
  delay(1000);
}
