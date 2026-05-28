#include "Sensors.hpp"

std::string TemperatureSensor::getReading() const {

    return "Temperature is " + std::to_string(currentTemp) + " C.";

}

std::string SmogSensor::getReading() const {

    return "Air quality scan completed.";

}

std::string AirQualityToString(AirQuality quality) {

    switch(quality) {

        case AirQuality::EXCELLENT : return "EXCELLENT";
        case AirQuality::GOOD : return "GOOD";
        case AirQuality::HAZARDOUS : return "HAZARDOUS";
        case AirQuality::POOR : return "POOR";
        default: return "UNKNOWN";
 
    }

}
