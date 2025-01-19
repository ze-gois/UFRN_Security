#include <iostream>
#include "state.h"
#include "display.h"
#include "input.h"
#include "log.h"

// Current state of the alarm system
AlarmState currentState = AlarmState::IDLE;

// Main state handler
void handleState() {
    switch (currentState) {
        case AlarmState::IDLE:
            handleIdleState();
            break;
        case AlarmState::ARMED:
            handleArmedState();
            break;
        case AlarmState::TRIGGERED:
            handleTriggeredState();
            break;
        case AlarmState::TAMPER:
            handleTamperState();
            break;
        case AlarmState::FAULT:
            handleFaultState();
            break;
        case AlarmState::CONFIGURATION:
            handleConfigurationState();
            break;
        default:
            log("Unknown state!");
            break;
    }
}

// State-specific behavior
void handleIdleState() {
    char command;
    log("Enter 'a' to ARM the system: ");
    std::cin >> command;
    if (command == 'a') {
        transitionToState(AlarmState::ARMED);
    }
}

void handleArmedState() {
    log("System is ARMED. Monitoring sensors...\n");
    // Simulate sensor input or disarm command
    char command;
    log("Enter 't' for TRIGGER, 'd' to DISARM: ");
    std::cin >> command;
    if (command == 't') {
        transitionToState(AlarmState::TRIGGERED);
    } else if (command == 'd') {
        transitionToState(AlarmState::IDLE);
    }
}

void handleTriggeredState() {
    log("ALARM TRIGGERED! Sounding buzzer...\n");
    // Simulate disarm command
    char command;
    log("Enter 'd' to DISARM: ");
    std::cin >> command;
    if (command == 'd') {
        transitionToState(AlarmState::IDLE);
    }
}

void handleTamperState() {
    log("TAMPER DETECTED! Taking action...\n");
    // Simulate resolving the tamper situation
    transitionToState(AlarmState::IDLE);
}

void handleFaultState() {
    log("FAULT DETECTED! Please check the system...\n");
    // Simulate fault recovery
    transitionToState(AlarmState::IDLE);
}

void handleConfigurationState() {
    log("Entering CONFIGURATION mode...\n");
    // Simulate configuration setup
    char command;
    log("Enter 'e' to EXIT configuration: ");
    std::cin >> command;
    if (command == 'e') {
        transitionToState(AlarmState::IDLE);
    }
}

// Main state handler
std::string stateString(AlarmState alarmState) {
    switch (alarmState) {
        case AlarmState::IDLE:
            return "IDLE";
        case AlarmState::ARMED:
            return "ARMED";
        case AlarmState::TRIGGERED:
            return "TRIGGERED";
        case AlarmState::TAMPER:
            return "TAMPER";
        case AlarmState::FAULT:
            return "FAULT";
        case AlarmState::CONFIGURATION:
            return "CONFIGURATION";
        default:
            return "UNK";
    }
}

void transitionToState(AlarmState newState) {
    logf("Transitioning from %s to %s...\n", stateString(currentState), stateString(newState));
    currentState = newState;
}