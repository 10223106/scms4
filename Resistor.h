#pragma once
// Resistor.h
#ifndef RESISTOR_H
#define RESISTOR_H
#define RESISTOR_H 

#include "Component.h"

class Resistor : public Component {
public:
    Resistor(double value);  // Constructor to initialize the resistor value
    double getValue() const override;  // Implementing getValue for Resistor
    string getType() const override;   // Implementing getType for Resistor
};


#endif // !RESISTOR_H 