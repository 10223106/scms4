#pragma once
#ifndef CIRCUITSIMULATOR_H
#define CIRCUITSIMULATOR_H

#include "olcPixelGameEngine.h"
#include "Menu.h"
#include "VoltageDivider.h" 
#include <string>

enum class AppState {
    MENU,
    CREDIT, 
    SIMULATION,
    VOLTAGE_DIVIDER,
    SERIES_PARALLEL,

    //for VOLTAGE DIVIDER METHODS
    ENTER_RESISTOR1,  // Added state for entering resistor 1
    ENTER_RESISTOR2,  // Added state for entering resistor 2
    SHOW_OUTPUT_VOLTAGE // Added state for displaying output voltage 

};

class CircuitSimulator : public olc::PixelGameEngine {
public:
    CircuitSimulator();

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

private:
    AppState currentState;
    Menu menu;

    std::string resistor1Input, resistor2Input;  // Variables to store the user input for resistors
    double resistor1Value, resistor2Value;  // Variables to store the parsed resistor values 
    double GetUserInputNumber(const std::string& prompt, double defaultValue );
    void HandleResistorInput(std::string& input, double& value, const std::string& prompt, AppState nextState);
    void AddText(float x, float y, const std::string& text, olc::Pixel color = olc::WHITE); 

    // State methods for each AppState
    void InitializeMenuState();
    //void InitializeSimulationState();
    void InitializeVoltageDividerState();
    //void InitializeSeriesParallelState();
    void InitializeCreditState();

    bool HandleMenuState(); 
    //void HandleSimulationState();
    void HandleVoltageDividerState();
    //void HandleSeriesParallelState();
    void HandleCreditState();

    //pointer
    VoltageDivider* voltageDivider = nullptr; //stupid pointer
    //std::unique_ptr<VoltageDivider> voltageDivider = nullptr; //smart pointer 
};

#endif // CIRCUITSIMULATOR_H