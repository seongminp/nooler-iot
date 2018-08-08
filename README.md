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
  - `Serial.begin(115200)`
  - Init BLE server
  - Init Wifi
  - Init reset/pair button

#### `WAITING_BLE`
- Start advertising BLE server.

#### `USER_PAIRED`
- Receive data(user uuid, Wifi information, etc.) from user through BLE.

#### `WAITING_WIFI`
- Attempt to connect to provided Wifi.

#### `WAITING_SERVER_SETUP`
- Sync with server.
- Subscribe to MQTT.

#### `OPERATIONAL`

#### Flags
|               |`INIT`|`WAITING_BLE`|`USER_PAIRED`|`WAITING_WIFI`|`WAITING_SERVER_SETUP`|`OPERATIONAL`|
| ----------------------         |:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
| `LOCAL_SETUP_COMPLETE`         |`false`|`false`|`false`|`true` |`true` |`true` |
| `SERVER_REGISTRATION_COMPLETE` |`false`|`false`|`false`|`false`|`false`|`true`|
| `BLE_WAITING`                  |`false`|`true` |`false`|`false`|`false`|`false`|
| `BLE_CONNECTED`                |`false`|`false`|`true` |`false`|`false`|`false`|
| `WIFI_CONNECTING`              |`false`|`false`|`false`|`true` |`false`|`false`|
| `WIFI_CONNECTED`               |`false`|`false`|`false`|`false`|`true` |`true` |




