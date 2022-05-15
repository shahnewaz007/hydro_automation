# Hydro Automation System

### [Youtube Review](https://youtu.be/yxo0-mrZXUs)
https://youtu.be/yxo0-mrZXUs


HYDROPONICS refers to growing of plants in a liquid nutrient solution.
It is even easier to grow some plants in areas of week soil conditions like
deserts. Hydro automation sets specific parameters like temperature, light, humidity, CO2, and air according to the needs of the plants to establish the most optimal growing conditions and allows plants to grow successfully. We have built a hardware system that will automatically adjust these parameters analyzing current condition. This system have these following features. Temperature and Humidity Control, Water Level, Air control, Security, Notification and Alert etc. We have used Arduino Mega, keypad, LCD, Buzzer, DHT sensor, PIR sensor, Ultra Sonic sensor etc. to build this system.

**Design**

![Circuit](https://user-images.githubusercontent.com/39572828/168495382-f310836b-e807-4da1-b50b-93b3cc9018da.JPG)



Working Procedure:

1.	To operate this whole system, we use the keypad for giving commands. After powering the device, the system asks to give password for logging in which is displayed in the LCD screen. We use the keypad of password entry. After logging in, a main menu is showed in the display. 



                      **Main Menu**
            -----------------------------

                1.	Temperature and Humidity
                2.	Water Level
                3.	Gas Condition
                4.	Start Water Pump
                5.	Start Exhaust Fan
                6.	Exit

These commands can be given using the keypad number keys. 


•	Temperature and Humidity: Check the current temperature and humidity by pressing 1 and go back to main menu by pressing 0.
•	Water Level: Check the current water level condition by pressing 2 and go back to main menu by pressing 0.
•	Gas Condition: Check the current system gas condition by pressing 3 and go back to main menu by pressing 0.
•	Start Water Pump: Start the water pump by pressing 4 and stops the pump and go back by pressing 0.
•	Start Exhaust Fan: Start the exhaust fans by pressing 5 and stops and go back by pressing 0. 
•	Exit: Logout the system by pressing 6.


2.	All the sensors are working in the background to keep the system in a stable Condition.

a.	Temperature and Humidity Control: The full system has an ideal temperature and humidity to keep the plant growth normal. So we use DHT Sensor to monitor the temperature and humidity regularly in the background. We use LDR sensor as we have to use artificial light in this system. When the temperature and Humidity measured by the DHT sensor is higher than ideal value, the system shows a warning and suggest to adjust the light intensity.

b.	Water Level: Water has a vital role in here as there is no use of soil. But we need to keep the water level at ideal rate so that the plants don’t sink in the excess water or dry for less water. So we use Ultra sonic sensor to measure the water level regularly. When the water level is lower than usual, the system shows a warning in the display and starts water pump to supply water. The pump stops automatically when the water level become normal.


c.	Air control: Our project is not only for hydroponic cultivation but also for whole hydroponic system. We use Gas sensor to measure the gas and smoke in the system and there is exhaust fan set up. When the gas level is higher than normal, the exhaust fans starts to pull away the bad air outside and enter the fresh air in the system. The display shows the warning and fan on/off condition during this time. 

d.	Security: For security assurance, we use PIR sensor to detect unauthorized movement in the system and use burglar Alarm to notify the owner. When user logs out the system, the PIR sensor remains active and if it detects any movement, the burglar alarm starts and it continues until the owner logs in with valid password. 
