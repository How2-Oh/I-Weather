/* I, Weather
 *  A SparkFun Electronics RedStick Companion
 *  
 *  Based on the following libraries:
  * OneWire DS18B20 Thermometer
 *
 * RGB LED by BARRAGAN http://barraganstudio.com
 * 
 * The Watchdog & Sleep Mode code was lovingly adapted from
   Nathan Seidle's SparkFun Electronics Arduino code for
   H2OhNo!.


This sketch enables you to read a temperature from the  
connected DS18B20 and display the results on an PWM-
connected RGB LED.

RGB LED:
RedStick -------------------------------- RGB LED
3 -------------- 180-ohm resistor ------- 1 (Red)
5 -------------- 100-ohm resistor ------- 3 (Green)
6 -------------- 100-ohm resistor ------- 4 (Blue)
GND ------------------------------------- 2 (Common Cathode)

DS18B20:
RedStick --------------- DS18B20
VCC -------------------- VDD (pin #3)
10 --------------------- DQ (pin #2)
GND -------------------- GND (pin #1)
5V --- 4.7K resistor --- DQ (pin #2)

2xAAA Battery Pack:
RedStick ----------- Battery Pack
+ ------------------ Battery Red
- ------------------ Battery Black
*/

#include <OneWire.h>
#include <avr/sleep.h>

int i = 0; // An incremental timing variable for use during display

// Variables for the RGB LED
int RedPin = 3; //RED pin of the LED to PWM pin 3
int GreenPin = 5; // GREEN pin of the LED to PWM pin 5
int BluePin = 6; // BLUE pin of the LED to PWM pin 6
int brightness = 0; // LED brightness
int increment = 5; // brightness increment

// Our DS18B20 temperature variables
float celsius, fahrenheit;

OneWire  ds(10);  // Thermometer is on pin 10 (a 4.7K resistor is necessary)

volatile int watchdog_counter;

//This runs each time the watchdog wakes up
ISR(WDT_vect){
  watchdog_counter++;
}

void setup()
{

// Configure the RGB LED for OUTPUT
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

// Countdown to start R -> G -> B
  for (i=0; i<100; i++) {
    brightness = brightness + increment;  // increment brightness for next loop iteration
      if (brightness <= 0 || brightness >= 255)
        {
          increment = -increment;
        }
    brightness = constrain (brightness, 0, 255);
    analogWrite(RedPin, brightness);
// reverse the direction of the fading
    delay(20); // wait for 20 milliseconds to see the dimming effect
  }
  for (i=0; i<100; i++) {
    brightness = brightness + increment;  // increment brightness for next loop iteration
      if (brightness <= 0 || brightness >= 255)
        {
          increment = -increment;
        }
    brightness = constrain (brightness, 0, 255);
    analogWrite(GreenPin, brightness);
// reverse the direction of the fading
    delay(20); // wait for 20 milliseconds to see the dimming effect
  }
  for (i=0; i<100; i++) {
    brightness = brightness + increment;  // increment brightness for next loop iteration
      if (brightness <= 0 || brightness >= 255)
        {
          increment = -increment;
        }
    brightness = constrain (brightness, 0, 255);
    analogWrite(BluePin, brightness);
// reverse the direction of the fading
    delay(20); // wait for 20 milliseconds to see the dimming effect
  }
// Turn LED OFF
  brightness = 0;
  analogWrite(BluePin, brightness);
  analogWrite(RedPin, brightness);
  analogWrite(GreenPin, brightness);

// Our sleep code
watchdog_counter = 0;

//Power down all unnecessary hardware
set_sleep_mode(SLEEP_MODE_PWR_DOWN);
sleep_enable();
ADCSRA &= ~(1<<ADEN); //Disables the ADC

setup_watchdog(7); //Wake up after 2 sec
}

void loop() 
{
  sleep_mode(); //Go to sleep for approximately 300 sec = 5 min

  if(watchdog_counter > 150) {
    watchdog_counter = 0;

// Get the temperature
  updateTemp();

// According to human preferences, the ideal comfort temperature level = 68-78 degrees F
// Therefore, Green = Ideal Temperature
// Red = Hot Temperature
// Blue = Cold Temperature

  if (fahrenheit >= 68 && fahrenheit <= 78) {
      for (i=0; i<200; i++) {
    brightness = brightness + increment;  // increment brightness for next loop iteration
      if (brightness <= 0 || brightness >= 255)
        {
          increment = -increment;
        }
    brightness = constrain (brightness, 0, 255);
    analogWrite(GreenPin, brightness);
// reverse the direction of the fading
    delay(20); // wait for 20 milliseconds to see the dimming effect
  }
  // Now turn OFF LED
  brightness = 0;
  analogWrite(GreenPin, brightness);
  }

// Temperature above 78 is HOT
  if (fahrenheit > 78) {
      for (i=0; i<200; i++) {
    brightness = brightness + increment;  // increment brightness for next loop iteration
      if (brightness <= 0 || brightness >= 255)
        {
          increment = -increment;
        }
    brightness = constrain (brightness, 0, 255);
    analogWrite(RedPin, brightness);
// reverse the direction of the fading
    delay(20); // wait for 20 milliseconds to see the dimming effect
  }
  // Now turn OFF LED
  brightness = 0;
  analogWrite(RedPin, brightness);
  }
  
// Temperature below 68 is COLD
  if (fahrenheit < 68) {
      for (i=0; i<200; i++) {
    brightness = brightness + increment;  // increment brightness for next loop iteration
      if (brightness <= 0 || brightness >= 255)
        {
          increment = -increment;
        }
    brightness = constrain (brightness, 0, 255);
    analogWrite(BluePin, brightness);
// reverse the direction of the fading
    delay(20); // wait for 20 milliseconds to see the dimming effect
  }
  // Now turn OFF LED
  brightness = 0;
  analogWrite(BluePin, brightness);
  }
  }
}

// Grab the temperature from the sensor and determine the degrees in F
void updateTemp()
{
  byte j;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  //float celsius, fahrenheit;
  
  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return;
  }
  
  for( j = 0; j < 8; j++) {
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      return;
  }
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      //Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      //Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      //Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      //Serial.println("Device is not a DS18x20 family device.");
      return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( j = 0; j < 9; j++) {           // we need 9 bytes
    data[j] = ds.read();
  }

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }

  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
}

void setup_watchdog(int timerPrescaler) {

  if(timerPrescaler > 9) timerPrescaler = 9; //Adjust amount

  byte bb = timerPrescaler & 7;
  if (timerPrescaler > 7) bb |= (1<<5); //Set 5th bit if needed

  // This sequence can NOT be altered
  MCUSR &= ~(1<<WDRF); //Clear the watchdog reset
  WDTCSR |= (1<<WDCE) | (1<<WDE); //Set WD_change & WD both enable
  WDTCSR = bb; //Set new watchdog timeout
  WDTCSR |= _BV(WDIE); //Set interrupt enable
}
