#include "lib/FSM/FSM.h" 

struct LocalData {
  char* WifiSSID;
  char* WifiPassword;
  char* UserUUID;
  bool localSetupComplete;
  bool serverRegistrationComplete;
};

FSM fsm;
BLEManager bleManager;
WifiManager wifiManager;

LocalData localData;

void setup() {
  Serial.begin(115200);

  /* Set up finite state machine and wireless managers. */
  fsm = FSM();
  bleManager = BLEManager(serverCallbacks, characteristicCallbacks);
  wifiManager = WifiManager();

  /* Load stored state from EEPROM. */
  localData = loadFromStorage('localData');
  localData.localSetupComplete = isLocalSetupComplete(localData);
  localData.serverRegistrationComplete = isServerRegistrationComplete(localData);

  Input currentInput = loadFromStorage('currentInput');
  currentInput.reset = false;
  currentInput.goToPairingMode = false;
  currentInput.localSetupComplete = localData.localSetupComplete;
  currentInput.serverRegistrationComplete = localData.serverRegistrationComplete;
  currentInput.bleWaiting = false;
  currentInput.bleConnected = false;
  currentInput.wifiConnected = false;
  currentInput.wifiConnecting = false;

  /* Provide fsm with current status. */
  fsm.setInput(currentInput);
}

void loop() {

  fsm.update();

  Input input = fsm.currentInput;

  switch (fsm.currentState) {
    case Init: 
      if (localData.localSetupComplete) {
        wifiManager.connect(void *callback(){
          input.wifiConnected = true;
          if (localData.serverRegistrationComplete) {
            input.Operational = true;
          } else {
            registerWithServer();
            input.WaitingServerSetup = true;
          }
        });
        input.wifiConnecting = true;
      } 

      bleManager.advertise();

      input.bleWaiting = true;
      break;

    case WaitingBLE:
      
      break;

    case UserPaired:
      if (!localData.serverRegistrationComplete) {
        input.serverRegistrationComplete = false;
      }
      // Set local.localSetupComplete to false when ble is connected.
      input.localSetupComplete = localData.localSetupComplete;
      break;

    case WaitingWifi:
      break;

    case WaitingServerSetup:
      break;

    case Operational:
      break;

    default: 
      Input resetInput = fsm.newInput(true, false, false, false, 
        false, false, false, false);
      fsm.setInput(resetInput);
      break;       
  }

}