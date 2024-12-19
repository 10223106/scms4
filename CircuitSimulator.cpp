#include "Menu.h"
#include "olcPixelGameEngine.h"
#include "CircuitSimulator.h"
#include "Resistor.h"
#include "VoltageDivider.h" 

CircuitSimulator::CircuitSimulator() {
    sAppName = "Simple Circuit Managing System";
}

bool CircuitSimulator::OnUserCreate() {
    currentState = AppState::MENU;
    InitializeMenuState(); 
    return true;
}

bool CircuitSimulator::OnUserUpdate(float fElapsedTime) {
    Clear(olc::BLACK); 

    switch (currentState) {
    case AppState::MENU:
        if (!HandleMenuState()) {  // If HandleMenuState() returns false, exit the app
            return false;  // Exit the app
        } 
        break; 
        if (GetKey(olc::Key::ENTER).bPressed) {
            switch (menu.GetSelectedOption()) {
            case 0:
                currentState = AppState::CREDIT;
                break;
            case 1:
                currentState = AppState::SIMULATION;
                break;
            case 2:
                currentState = AppState::VOLTAGE_DIVIDER;
                break;
            case 3:
                currentState = AppState::SERIES_PARALLEL;
                break;
            case 4: //exit
                return false;
            }
        }
        break;
    case AppState::CREDIT: 
        HandleCreditState(); 
        break;
    case AppState::SIMULATION:
        AddText(5, 10, "This feature is not ready", olc::WHITE);
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            currentState = AppState::MENU;
        }
        break;

    case AppState::VOLTAGE_DIVIDER:
        //AddText(5, 10, "Testing entering right state", olc::WHITE);
        HandleVoltageDividerState();
        break;

    //case AppState::ENTER_RESISTOR1:
    //    AddText(10, 30, "Enter Resistor 1 Value (Ohms):", olc::WHITE);
    //    // Handle user input or further logic here
    //    break; 
    //case AppState::ENTER_RESISTOR1:
    //case AppState::ENTER_RESISTOR2:
    //   HandleVoltageDividerState();
    //    break;
    case AppState::SERIES_PARALLEL:
        //AddText(5, 10, "Testing entering right state", olc::WHITE);
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            currentState = AppState::MENU;
        }
        break;
    }

    return true;
}

//MENU=========
void CircuitSimulator::InitializeMenuState() {
    menu.AddOption("Welcome to SCMS", { 5, 10 });

    menu.AddOption("1. Circuit Simulation", { 20, 30 });
    menu.AddOption("2. Voltage Divider", { 20, 50 });
    menu.AddOption("3. Series/Parallel Resistor", { 20, 70 });
    menu.AddOption("4. Exit", { 20, 90 }); 
}

bool CircuitSimulator::HandleMenuState() {
    menu.HandleInput(this);
    menu.Draw(this);

    if (GetKey(olc::Key::ENTER).bPressed) {
        switch (menu.GetSelectedOption()) {
        case 0: currentState = AppState::CREDIT; break;
        case 1: currentState = AppState::SIMULATION; break;
        case 2: currentState = AppState::VOLTAGE_DIVIDER; break;
        case 3: currentState = AppState::SERIES_PARALLEL; break;
        case 4: return false;  // Exit the app
        }
    }
    return true;
}
//CREDIT======
void CircuitSimulator::InitializeCreditState() {
    // Add CREDIT 
    AddText(5, 10, "Simple Circuit Managing System", olc::WHITE);
    AddText(20, 30, "OOP Project - ECE2023", olc::WHITE);
    AddText(20, 50, "Dang Minh Truc - 10223106", olc::WHITE);
    AddText(20, 70, "Tran Dinh Hoang Quan - 10223098", olc::WHITE);
    AddText(20, 90, "Le Nguyen Minh Thi - 17115", olc::WHITE);
    AddText(5, 110, "Press ESC to go back to menu", olc::WHITE);
}
void CircuitSimulator::HandleCreditState() {
    InitializeCreditState();
    if (GetKey(olc::Key::ESCAPE).bPressed) {
        currentState = AppState::MENU;
    }
} 
//VOLTAGE DIVIDER =====
void CircuitSimulator::InitializeVoltageDividerState() {
    //AddText(10, 50, "2 Testing entering right state", olc::WHITE);
    AddText(10, 10, "Voltage Divider State Initialized", olc::WHITE);
    AddText(10, 30, "Enter Resistor 1 Value (Ohms): ", olc::WHITE);
    resistor1Input = "";  // Clear previous input (if any)
    
    currentState = AppState::ENTER_RESISTOR1;  // Switch state to capture Resistor 1 input 
    //std::cout << "Switched to ENTER_RESISTOR1 state" << std::endl; 
    //HandleVoltageDividerState(); //recursive call
} 
//void CircuitSimulator::HandleVoltageDividerState() {
//    // Initialize only once, before transitioning into the Enter Resistor 1 state
//    //AddText(5, 10, "Testing entering right state", olc::WHITE);
//    static bool isInitialized = false;  // Flag to ensure initialization happens only once
//    // Initialize voltage divider state only once
//    if (currentState == AppState::VOLTAGE_DIVIDER && !isInitialized) {
//        InitializeVoltageDividerState();
//        isInitialized = true;  // Set flag to avoid reinitializing
//        return; //exit function to prevent additional processing
//    }
//    // Reset initialization when transitioning to a new state
//    if (currentState != AppState::VOLTAGE_DIVIDER) {
//        isInitialized = false;
//    }
//
//    double outputVoltage = 0.0;
//    
//    switch (currentState) {
//    case AppState::VOLTAGE_DIVIDER:
//        // This is where we display the initialization message
//        AddText(5, 100, "Error: Still in VOLTAGE_DIVIDER state.", olc::RED); 
//        break;
//    case AppState::ENTER_RESISTOR1:
//        // Display and gather user input for Resistor 1
//        //AddText(5, 10, "Testing entering right state", olc::WHITE);
//        if (GetKey(olc::Key::ENTER).bPressed) {
//            try {
//                resistor1Value = std::stod(resistor1Input);
//                AddText(10, 50, "Resistor 1: " + resistor1Input + " Ohms", olc::WHITE);
//                currentState = AppState::ENTER_RESISTOR2;  // Proceed to next resistor
//            }
//            catch (...) {
//                AddText(10, 50, "Invalid Resistor 1 input.", olc::RED);
//            }
//        }
//        else {
//            for (char digit = '0'; digit <= '9'; ++digit) {
//                if (GetKey(static_cast<olc::Key>(olc::Key::K0 + (digit - '0'))).bPressed) {
//                    resistor1Input.push_back(digit);
//                }
//            }
//            if (GetKey(olc::Key::BACK).bPressed && resistor1Input.length() > 0) {
//                resistor1Input.pop_back();  // Handle backspace
//            }
//        }
//        break;
//
//    case AppState::ENTER_RESISTOR2:
//        AddText(10, 70, "Enter Resistor 2 Value (Ohms): ", olc::WHITE);
//        if (GetKey(olc::Key::ENTER).bPressed) {
//            try {
//                resistor2Value = std::stod(resistor2Input);
//                AddText(10, 90, "Resistor 2: " + resistor2Input + " Ohms", olc::WHITE);
//
//                // Normal pointer - deallocate when exit this state
//                voltageDivider = new VoltageDivider();  // Allocate memory for VoltageDivider
//                voltageDivider->addComponent(new Resistor(resistor1Value));  // Add Resistor 1
//                voltageDivider->addComponent(new Resistor(resistor2Value));  // Add Resistor 2
//
//                currentState = AppState::SHOW_OUTPUT_VOLTAGE;  // Proceed to display output voltage
//            }
//            catch (...) {
//                AddText(10, 90, "Invalid Resistor 2 input.", olc::RED);
//            }
//        }
//        else {
//            for (char digit = '0'; digit <= '9'; ++digit) {
//                if (GetKey(static_cast<olc::Key>(olc::Key::K0 + (digit - '0'))).bPressed) {
//                    resistor2Input.push_back(digit);
//                }
//            }
//            if (GetKey(olc::Key::BACK).bPressed && resistor2Input.length() > 0) {
//                resistor2Input.pop_back();  // Handle backspace
//            }
//        }
//        break;
//
//    case AppState::SHOW_OUTPUT_VOLTAGE:
//        AddText(10, 110, "Voltage Divider Output", olc::WHITE);
//        double inputVoltage = GetUserInputNumber("Enter Input Voltage (V): ", 5.0);
//        outputVoltage = voltageDivider->calculateOutputVoltage(inputVoltage);
//        AddText(10, 130, "Output Voltage: " + std::to_string(outputVoltage) + " V", olc::WHITE);
//    
//        if (GetKey(olc::Key::ESCAPE).bPressed) {
//            delete voltageDivider;  // Clean up memory
//            voltageDivider = nullptr;  // Avoid dangling pointer 
//            currentState = AppState::MENU;
//        }
//    //default:
//        break;
//    }
//    
//} 
void CircuitSimulator::HandleVoltageDividerState() {
    static bool isInitialized = false;

    // Initialize once when entering the state
    if (!isInitialized) {
        AddText(10, 10, "Voltage Divider State Initialized", olc::WHITE);
        AddText(10, 30, "Enter Resistor 1 Value (Ohms): ", olc::WHITE);
        resistor1Input.clear();  // Reset input
        currentState = AppState::ENTER_RESISTOR1;  // Transition to next state
        isInitialized = true;
        return;
    }

    switch (currentState) {
    case AppState::ENTER_RESISTOR1:
        HandleResistorInput(resistor1Input, resistor1Value, "Enter Resistor 1 Value (Ohms):", AppState::ENTER_RESISTOR2);
        break;

    case AppState::ENTER_RESISTOR2:
        HandleResistorInput(resistor2Input, resistor2Value, "Enter Resistor 2 Value (Ohms):", AppState::SHOW_OUTPUT_VOLTAGE);
        break;

    case AppState::SHOW_OUTPUT_VOLTAGE:
        double inputVoltage = GetUserInputNumber("Enter Input Voltage (V): ", 5.0);
        double outputVoltage = (inputVoltage * resistor2Value) / (resistor1Value + resistor2Value);
        AddText(10, 110, "Output Voltage: " + std::to_string(outputVoltage) + " V", olc::WHITE);

        if (GetKey(olc::Key::ESCAPE).bPressed) {
            delete voltageDivider;  // Clean up memory
            //voltageDivider = nullptr;  // Avoid dangling pointer
            currentState = AppState::MENU;
            isInitialized = false;  // Reset initialization
        }
        break;

    //default:
        break;
    }
}
//INPUTNUMBER=======
double CircuitSimulator::GetUserInputNumber(const std::string& prompt, double defaultValue) {
    // Store the user input string (default to provided value)
    std::string userInput = std::to_string(defaultValue);
    bool inputComplete = false; // Flag to track input completion

    // Show the prompt to the user
    AddText(10, 10, prompt, olc::WHITE);

    // Loop until user presses Enter to submit the input
    while (!inputComplete) {
        // Draw the current user input on the screen
        AddText(10, 30, "Input: " + userInput, olc::WHITE);

        // Handle backspace (delete last character)
        if (GetKey(olc::Key::BACK).bPressed && userInput.length() > 0) {
            userInput.pop_back();
        }

        // Handle number input (digits 0-9)
        for (char digit = '0'; digit <= '9'; ++digit) {
            if (GetKey(static_cast<olc::Key>(olc::Key::K0 + (digit - '0'))).bPressed) { 
                // Add the pressed digit to the input string
                userInput.push_back(digit);
            }
        }

        // Handle decimal point (.)
        if (GetKey(olc::Key::PERIOD).bPressed && userInput.find('.') == std::string::npos) {
            userInput.push_back('.');
        }

        // When Enter is pressed, try to convert the string to a number
        if (GetKey(olc::Key::ENTER).bPressed) {
            try {
                // Convert the string to a double
                double number = std::stod(userInput);
                return number;  // Return the valid number
            }
            catch (const std::invalid_argument& e) {
                // If input is invalid, show error message
                AddText(10, 50, "Invalid input, please enter a valid number.", olc::RED);
            }
        }

        // Allow a small delay to prevent excessive CPU usage
        Sleep(10);
    }

    // Return the default value if input is not valid or the user cancelled input
    return defaultValue;
}
//HELPER FUNCTION
void CircuitSimulator::HandleResistorInput(std::string& input, double& value, const std::string& prompt, AppState nextState) {
    AddText(10, 30, prompt + " " + input, olc::WHITE);

    if (GetKey(olc::Key::ENTER).bPressed) {
        try {
            value = std::stod(input);
            currentState = nextState;  // Transition to next state
        }
        catch (...) {
            AddText(10, 50, "Invalid input. Please try again.", olc::RED);
        }
    }
    else {
        for (char digit = '0'; digit <= '9'; ++digit) {
            if (GetKey(static_cast<olc::Key>(olc::Key::K0 + (digit - '0'))).bPressed) {
                input.push_back(digit);
            }
        }
        if (GetKey(olc::Key::BACK).bPressed && !input.empty()) {
            input.pop_back();
        }
    }
}
//FOR LAYOUT ==========
void CircuitSimulator::AddText(float x, float y, const std::string& text, olc::Pixel color ) {
    float scale = 0.8f; // Adjust this value to make text smaller
    DrawStringDecal({ x, y }, text, color, { scale, scale }); // Scale text by 0.5 
} 