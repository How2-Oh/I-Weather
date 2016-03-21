# I, Weather

Keep your "eye" on the weather. There are few areas in everyday life that suffer from data overload quite like the weather. All you want to know is, "what's it like outside right now?" Instead of a nice simple answer, you are deluged with more data points that you can sling a psychrometer at: dew points, inches of mercury (mercury!!), humidity, wind speed, and, of course, temperature. My kids don't want to know any of that "techie stuff," they just want to know is it "nice, hot, or cold" outside...right now.

<img src=https://cloud.githubusercontent.com/assets/16638894/13928000/fe0d1c22-ef61-11e5-9961-5e41cd3fcae9.JPG>

Today with the SparkFun Electronics RedStick and a couple of discrete parts, you can answer that simple weather question with "I, Weather."

Securely installed inside a beautifully designed 3D-printed custom case (files available on Thingiverse), "I, Weather" provides you with a clear, easy-to-understand weather synopsis. Optimized Arduino code (files available on GitHub) featuring a WatchDog timer enables "I, Weather" to sip just enough juice from its dual AAA battery pack to keep your weather fix going and going.

Here's how it works: the RedStick is safely mounted inside the battery pack within a custom 3D-printed lid. The temperature sensor and RGB LED are neatly arranged inside a 3D-printed button disc. Two "eye" openings in the button enable the sensor to reliably read the ambient air temperature and the LED to "wink" the current temperature. A back is glued (use Testors Cement for Plastic Models No. 3512) on the button for protecting the internal wiring from dust and debris.

When the power switch is turned ON, "I, Weather" performs a startup test of the RGB LED, pulsing red, green, and blue. Upon completion of this test, the WatchDog timer kicks in and puts the RedStick to "sleep" for approximately 5 minutes. After the 5 minute interval, "I, Weather" wakes up, grabs a quick temperature reading, and pulses the RGB LED twice with the appropriate color: green = "nice;" 68 - 78 degs F, red = "hot;" above 78 degs F, and blue = "cold;" below 68 degs F. [Hey, we live on the Gulf Coast; and below 68 degs F IS kinda cool.]

##Parts

* SparkFun RedStick #DEV-13741
* LED - RGB Diffused Common Cathode #COM-09264
* One Wire Digital Temperature Sensor DS18B20 #SEN-00245
* Battery Holder 2xAAA with Cover and Switch #PRT-09543
* 4.7K, 180-ohm (I used a 220-ohm), (2) 100-ohm Resistor Kit #COM-10969
* Hook-Up Wire - Assortment #PRT-11375
* 2-56 Machine Screw Fastener, two 2-56 Washers, one 2-56 Hex Nut #PRT-08993, #PRT-08995

##Step-by-Step

1. Download, read, and understand ALL of the datasheets, schematics, and tutorials from SparkFun Electronics for each of the parts.

2. Solder the 180-ohm (or, 220-ohm) resistor to pin 1 of the RGB LED.

3. Solder the two 100-ohm resistors to pins 3 and 4 of the LED.

4. Solder the 4.7K resistor between pins 2 and 3 of the DS18B20. The remaining steps are simple wiring connections.

5. Attach a yellow wire (avoid a red wire so that you'll minimize confusion with the red "power" wires used later in this project) to the 180-ohm resistor on pin 1, a green wire to the 100-ohm resistor on pin 3, a blue wire to the final 100-ohm resistor on pin 4, and a black wire to pin 2 of the LED.

6. Solder a brown wire (or, white wire) to pin 2, a red wire to pin 3, and a black wire to pin 1 of the DS18B20 sensor.

7. Connect the black wire from the LED (see Step 5) to pin 1 of the sensor.

8. The wiring harness is now complete.

9. Mould the wiring, resistors, sensor, and LED so that they all fit comfortably inside the button disc. The sensor should sit flush with the outside of one of the button's eye openings, while the LED should protrude through the other eye opening.

10. Snake all wiring through the opening in the base of the button and through a matching opening inside the battery lid.

11. Run the external red and black wires from the battery pack through the two wire openings in the battery lid.

12. Secure the button to the battery lid with the 2-56 hardware.

13. Solder ALL wire connections to the RedStick: yellow (from pin 1 of the LED) to pin 3, green to pin 5, blue to pin 6, brown (from pin 2 of the sensor) to pin 10, red from the sensor to pin VCC, black from the sensor to pin GND, red from the battery pack to +, and black from the battery pack to -.

14. Connect the RedStick to your PC and upload the IWeather.ino code. [NOTE: I used a USB port extender cable connecting the RedStick to the PC.]

15. Ensure "I, Weather" is performing its startup sequence and pulsing the correct temperature every five minutes before you disconnect the PC.

16. If everything checks out OK, remove the RedStick from the PC and insulate the bottom of the board with a piece of tape (i.e., so the metal batteries don't short circuit any of the board's connections).

17. Glue the back on the button and stuff all of the wiring and RedStick inside the battery lid. [NOTE: there's a slot in the lid for enabling the RedStick's USB "fingers" to stick out.]

18. Insert two AAA batteries, slide the battery lid closed, secure the battery pack with a piece of tape, and install "I, Weather" inside/outside away from direct sunlight and moisture.

##Bonus "Expert" Tips

The red Power Indicator LED is continually drawing precious amounts of power from the battery pack. Carefully study the RedStick schematic and remove this LED (D2) along with the 6.8K resistor (R2).

If your "I, Weather" is constantly "resetting" itself during or following assembly, the RedStick "reset" button (S1) might be the culprit. Again, carefully review the RedStick schematic and remove this button.

-end-
