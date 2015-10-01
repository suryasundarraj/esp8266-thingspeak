# esp8266-thingspeak
[image-graph]:images/analogGraph.png

Graphical Data Visualization of any Analog Sensor using Tiva C Series TM4C123G, ESP8266 and Thingspeak API without using any external chip.

### Installing the Arduino ESP8266 Core with the Boards Manager ###

- Download and Install Arduino 1.6.5 from [https://www.arduino.cc/en/Main/Software]
- Start Arduino and open Preferences window.
- Enter ```http://arduino.esp8266.com/stable/package_esp8266com_index.json``` into *Additional Board Manager URLs* field. You can add multiple URLs, separating them with commas.
- Open Boards Manager from Tools > Board menu and install *esp8266* platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).

####GRAPH USING THE RAW DATA OF THE SENSOR

![image][image-graph]
