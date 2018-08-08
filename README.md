# nooler-iot
Code to run on the ground

## State Machine Description

#### Constants
<!-- - `int MODE_BLE = 0` - The device is using its radio for BLE.
- `int MODE_WIFI = 1` - The device is using its radio for  Wifi. -->
- `char* HOST = http://www.nooler.com` - IP address of Nooler's server.
- `int hostPort = 80` - Port used by host.

#### Inputs 
<!-- Setup flags -->
- `bool` `LOCAL_SETUP_COMPLETE`
- `bool` `SERVER_REGISTRATION_COMPLETE`
<!-- BLE flags -->
- `bool` `BLE_WAITING`
- `bool` `BLE_CONNECTED`
<!-- Wifi flags -->
- `bool` `WIFI_CONNECTING`
- `bool` `WIFI_CONNECTED`
<!-- Wifi metadata -->
- `char*` `WIFI_SSID` - Wifi SSID
- `char*` `WIFI_PW` - Wifi password
<!-- - `int` `OPEATION_MODE` - Either `MODE_BLE` or `MODE_WIFI`. -->

#### States 

#### `INIT`
###### flags
`LOCAL_SETUP_COMPLETE = false`

`SERVER_REGISTRATION_COMPLETE = false`

`BLE_WAITING = false`

`BLE_CONNECTED = false`

`WIFI_CONNECTING = false`

`WIFI_CONNECTED = false`

###### entry
  - `Serial.begin(115200)`
  - Init BLE server
  - Init Wifi
  - Init reset/pair button

#### `WAITING_BLE`
###### flags
`LOCAL_SETUP_COMPLETE = false`

`SERVER_REGISTRATION_COMPLETE = false`

`BLE_WAITING = true`

`BLE_CONNECTED = false`

`WIFI_CONNECTING = false`

`WIFI_CONNECTED = false`

###### entry
- Start advertising BLE server.

#### `USER_PAIRED`
###### flags
`LOCAL_SETUP_COMPLETE = false`

`SERVER_REGISTRATION_COMPLETE = false`

`BLE_WAITING = false`

`BLE_CONNECTED = true`

`WIFI_CONNECTING = false`

`WIFI_CONNECTED = false`

###### entry
- Receive data(user uuid, Wifi information, etc.) from user through BLE.

#### `WAITING_WIFI`
###### flags
`LOCAL_SETUP_COMPLETE = true`

`SERVER_REGISTRATION_COMPLETE = false`

`BLE_WAITING = false`

`BLE_CONNECTED = false`

`WIFI_CONNECTING = true`

`WIFI_CONNECTED = false`

###### entry
- Attempt to connect to provided wifi.

#### `WAITING_SERVER_SETUP`
###### flags
`LOCAL_SETUP_COMPLETE = true`

`SERVER_REGISTRATION_COMPLETE = false`

`BLE_WAITING = false`

`BLE_CONNECTED = false`

`WIFI_CONNECTING = false`

`WIFI_CONNECTED = true`

###### entry
- Sync with server.
- Subscribe to MQTT.


#### `OPERATIONAL`
###### flags
`LOCAL_SETUP_COMPLETE = true`

`SERVER_REGISTRATION_COMPLETE = true`

`BLE_WAITING = false`

`BLE_CONNECTED = false`

`WIFI_CONNECTING = false`

`WIFI_CONNECTED = true`

###### entry




