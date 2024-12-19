#include "Resistor.h"

Resistor::Resistor(double value) : Component("Resistor", value) {}

double Resistor::getValue() const {
    return value;  // Return the resistance value
}

string Resistor::getType() const {
    return "Resistor";  // Return the type of component
}