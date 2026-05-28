#pragma once

#include <string>
#include <cstdint>
#include <stdexcept>

enum class AirQuality {

    EXCELLENT = 0,
    GOOD = 1,
    POOR = 2,
    HAZARDOUS = 3

};

std::string AirQualityToString(AirQuality quality);

class Sensor {

    private:

        uint64_t sensorIDcounter = 1;
    
    protected:

        uint64_t sensorID;
        std::string location;  

    public:

        Sensor(std::string location) : sensorID{sensorIDcounter++}, location{location} {}
        virtual ~Sensor() = default;
        
        virtual std::string getReading() const = 0;

        uint64_t getID() const { return sensorID; }
        const std::string& getLocation() { return location; }

};

class TemperatureSensor : public Sensor {

    private:

        double currentTemp;

    public:

        TemperatureSensor(std::string location, double temp) : Sensor(location), currentTemp{temp} {

            if (temp < -273.13 || temp > 100.0) {

                throw std::out_of_range("Temparatura poza skala");

            }

        }

        std::string getReading() const override;

};

class SmogSensor : public Sensor {

    private:

        AirQuality aqlevel;

    public:

        SmogSensor(std::string location, AirQuality aqlevel) : Sensor(location), aqlevel{aqlevel} {}

        AirQuality getAirQuality() const {

            return aqlevel;

        }

        std::string getReading() const override;

};
