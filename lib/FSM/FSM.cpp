#include "FSM.h"

FSM::FSM() {

  /* Initialize current input. */
  Input currentInput = { false,false,false,false,false,false,false,false };

  /* Set state. */
  currentState = Init;
}

Input FSM::newInput(bool reset, bool goToPairingMode, bool localSetupComplete,
                    bool serverRegistrationComplete, bool bleWaiting,
                    bool bleConnected, bool wifiConnecting, bool wifiConnected) {

  Input input = { reset, goToPairingMode, localSetupComplete,
                  serverRegistrationComplete, bleWaiting,bleConnected,
                  wifiConnecting, wifiConnected };
  return input;
}

State FSM::setInput(Input currInput) {
  
  State newState = changeState(currentState, currInput);
  return newState;
}

State FSM::changeState(State currState, Input currInput) {

  // bool sanitizedInputs[NUM_FLAGS] = sanitizeInputs(newFlags);

  State newState = determineNextState(currState, currInput);
  currentState = newState;

  Output newOutput = determineNextOutput(currState, currInput);
  currentOutput = newOutput;

  return newState;
}

State FSM::determineNextState(State currState, Input currInput) {

  if (currInput.reset) {
    return Init;
  } else if (currInput.goToPairingMode) {
    return WaitingBLE;
  }

  switch(currState) {
    case Init: 
      if (currInput.localSetupComplete) {
        return WaitingWifi;
      } else {
        return WaitingBLE;
      }

    case WaitingBLE: 
      if (currInput.bleConnected) {
        return UserPaired;
      }
      break;

    case UserPaired: 
      if (currInput.localSetupComplete) {
        return WaitingWifi;
      }
      break;

    case WaitingWifi: 
      // Check if local configuration is complete.
      if (!currInput.localSetupComplete) {
        if (currInput.bleConnected) {
          return UserPaired;
        } else {
          return WaitingBLE;
        }
      }

      // Check if wifi connection and server registration is complete.
      if (currInput.wifiConnected) {
        if (currInput.serverRegistrationComplete) {
          return Operational;
        } else {
          return WaitingServerSetup;
        }
      }
      break;

    case WaitingServerSetup: 
      // Check if local configuration is complete.
      if (!currInput.localSetupComplete) {
        if (currInput.bleConnected) {
          return UserPaired ;
        } else {
          return WaitingBLE;
        }
      }

      // Check if server response was received.
      if (currInput.localSetupComplete 
          && currInput.serverRegistrationComplete) {
        return Operational;
      }
      break;

    case Operational: 
      // Check if necessary configurations are ready.
      if (!currInput.localSetupComplete 
          || !currInput.serverRegistrationComplete) {
        return Init;
      }
      break; 

    default: return Init;         
  }

  return currState;
}