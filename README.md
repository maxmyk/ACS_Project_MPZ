# ACS_Project_MPZ
Authors (team): <mark><a href="https://github.com/Bohdan213">Пелех Богдан</a>, <a href="https://github.com/maxmyk">Михасюта Максим</a>, <a href="https://github.com/fazhur">Журба Федір</a></mark><br>

![first scheme](https://github.com/maxmyk/ACS_Project_MPZ/blob/main/first_level_scheme.png?raw=true)
![second scheme](https://github.com/maxmyk/ACS_Project_MPZ/blob/main/second_level_scheme.png?raw=true)
# Description

Final iteration.

What we have done:
* Mesh via WiFI
* RF24 communication
* WiFi connection to local server
* Local web server

## Prerequisites

Hardware:
 - NODEMCU
 - ARDUINO
 - NRF24L01
 - NRF24L01 breakout board
 - DHT11
 
Software:
 - Arduino IDE ready to work with ESP8266

### Installation

#### Clone the project

```bash
git clone https://github.com/maxmyk/ACS_Project_MPZ
cd ACS_Project_MPZ
```

### Usage

Upload code to corresponding microcontrollers
Change WiFi SSID and PASSWORD at WIFI_PASS.h files

#### 1-st level (Sensors)
Transmitter, Transmitter2: upload to Arduino Nano or Uno. We do not guarantee it'll work at other models.  Then connect as shown <a href="https://github.com/maxmyk/ACS_Project_MPZ/blob/main/first_level_scheme.png">here</a>

#### 2-nd level (Mesh)
ESP_mesh: upload to NodeMCU and connect as shown <a href="https://github.com/maxmyk/ACS_Project_MPZ/blob/main/second_level_scheme.png">here</a>

#### 3-rd level (HUB)
Bridge: upload to NodeMCU
Hub: upload to NodeMCU
Connection:
| Bridge | Hub |
|--------|-----|
| Gnd    | Gnd |
| D5     | D6  |
| D6     | D5  |

***Important! WiFi you are connecting to should be on channel 1***

### Important!

* There may be some trouble connecting NRF24L01!
* Some NodeMCUs require specific drivers and may not work right away
* Make sure to use proper bootloader settings when uploading the code
* Check the wiring at least twice, most of the problems are at this step
