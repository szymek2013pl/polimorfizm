#pragma once

#include "Sensors.hpp"

#include <list>
#include <memory>

class MonitoringStation {

    private:
    
        std::list<std::unique_ptr<Sensor>> sensors;

    public:

        MonitoringStation() = default;

        void addSensor(std::unique_ptr<Sensor> newSensor) { 

            sensors.push_back(std::move(newSensor));

        }

        void loadTemperatureSensorSafe(const std::string& loc, double temp);
        void generateDailyReport() const;

};
