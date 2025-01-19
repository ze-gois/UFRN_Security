#include <iostream>
#include "state.h"
#include "display.h"
#include "input.h"

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
            std::cerr << "Unknown state!" << std::endl;
            break;
    }
}

// State-specific behavior
void handleIdleState() {
    std::cout << "System is IDLE (disarmed). Waiting for 'arm' command...\n";
    // Simulate receiving an "arm" command
    char command;
    std::cout << "Enter 'a' to ARM the system: ";
    std::cin >> command;
    if (command == 'a') {
        transitionToState(AlarmState::ARMED);
    }
}

void handleArmedState() {
    std::cout << "System is ARMED. Monitoring sensors...\n";
    // Simulate sensor input or disarm command
    char command;
    std::cout << "Enter 't' for TRIGGER, 'd' to DISARM: ";
    std::cin >> command;
    if (command == 't') {
        transitionToState(AlarmState::TRIGGERED);
    } else if (command == 'd') {
        transitionToState(AlarmState::IDLE);
    }
}

void handleTriggeredState() {
    std::cout << "ALARM TRIGGERED! Sounding buzzer...\n";
    // Simulate disarm command
    char command;
    std::cout << "Enter 'd' to DISARM: ";
    std::cin >> command;
    if (command == 'd') {
        transitionToState(AlarmState::IDLE);
    }
}

void handleTamperState() {
    std::cout << "TAMPER DETECTED! Taking action...\n";
    // Simulate resolving the tamper situation
    transitionToState(AlarmState::IDLE);
}

void handleFaultState() {
    std::cout << "FAULT DETECTED! Please check the system...\n";
    // Simulate fault recovery
    transitionToState(AlarmState::IDLE);
}

void handleConfigurationState() {
    std::cout << "Entering CONFIGURATION mode...\n";
    // Simulate configuration setup
    char command;
    std::cout << "Enter 'e' to EXIT configuration: ";
    std::cin >> command;
    if (command == 'e') {
        transitionToState(AlarmState::IDLE);
    }
}

// State transition logic
void transitionToState(AlarmState newState) {
    std::cout << "Transitioning from " << static_cast<int>(currentState)
              << " to " << static_cast<int>(newState) << "...\n";
    currentState = newState;
}