#ifndef FSM_h
#define FSM_h

/* States */
// const int STATE_INIT = 0;
// const int STATE_WAITING_BLE = 1;
// const int STATE_USER_PAIRED = 2;
// const int STATE_WAITING_WIFI = 3;
// const int STATE_WAITING_SERVER_SETUP = 4;
// const int STATE_OPERATIONAL = 5;

enum State { Init,
             WaitingBLE,
             UserPaired,
             WaitingWifi,
             WaitingServerSetup,
             Operational };

// const int NUM_FLAGS = 8;

// /* Flag indices */
// const int RESET = 0;
// const int GO_TO_PAIRING_MODE = 1;
// const int LOCAL_SETUP_COMPLETE = 2;
// const int SERVER_REGISTRATION_COMPLETE = 3;
// const int BLE_WAITING = 4;
// const int BLE_CONNECTED = 5;
// const int WIFI_CONNECTING	= 6;
// const int WIFI_CONNECTED = 7;

struct Input {
  bool reset;
  bool goToPairingMode;
  bool localSetupComplete;
  bool serverRegistrationComplete;
  bool bleWaiting;
  bool bleConnected;
  bool wifiConnecting;
  bool wifiConnected;
};

struct Output {
  char* WifiSSID;
  char* WifiPassword;
  char* UserUUID;
};

class FSM {
  public:
    Input currentInput; 
    State currentState;
    Output currentOutput;
    FSM();
    Input newInput(bool reset, bool goToPairingMode, bool localSetupComplete,
                   bool serverRegistrationComplete, bool bleWaiting,
                   bool bleConnected, bool wifiConnecting, bool wifiConnected);            
    State setInput(Input);
  private:
    // bool *sanitizeInputs(bool newFlags[NUM_FLAGS]);
    State changeState(State currState, Input currInput);
    Input sanitizeInput(Input currInput);
    State determineNextState(State currState, Input currInput);
    Output determineNextOutput(State currState, Input currInput);
};

#endif