# nooler-iot
Code to run on the ground

## State Machine Description

#### Constants
- `int MODE_BLE = 0` - The device is using its radio for BLE.
- `int MODE_WIFI = 1` - The device is using its radio for  Wifi.
- `char* HOST = http://www.example.com` - IP address of Nooler's server.
- `int hostPort = 80` - Port used by host.

#### Inputs 
- `bool` `SETUP_COMPLETE`
- `char*` `WIFI_SSID` - Wifi SSID
- `char*` `WIFI_PW` - Wifi password
- `int` `OPEATION_MODE`.

#### States 

#### `INIT`
###### entry
  - `Serial.begin(115200)`
  - Init BLE server
  - Init Wifi
  - Init reset button
  - `SETUP_COMPLETE` ? **go to** `WIFI_CONNECTING` : **go to** `BLE_CONNECTING`

#### `BLE_WAITING`
###### entry
- Terminate Wifi client.
- Set up BLE server

#### `BLE_CONNECTED`
###### entry
- Initiate periodic read from serial.

#### `WIFI_CONNECTING`
###### entry
- Terminate BLE client.

#### `WIFI_CONNECTED`
###### entry
- Sync with server.




