#include "Sensors.hpp"
#include "MonitoringStation.hpp"

#include <iostream>
#include <typeinfo>

void MonitoringStation::loadTemperatureSensorSafe(const std::string& loc, double temp) {

    try {

        //std::unique_ptr<TemperatureSensor> sensor = std::make_unique<TemperatureSensor>(loc);
        addSensor(std::make_unique<TemperatureSensor>(loc, temp)); // - tutaj uzywamy rowniez konstruktora
        std::cout << " [OK] Zarejestrowano czujnik w: " << loc << std::endl;

    }

    catch (std::exception& e) {

        std::cout << " [Diagnostyka] Odrzucono sprzet z lokalizacji " << loc << ". Powod: " << e.what() << std::endl;

    }

}

void MonitoringStation::generateDailyReport() const {

    for (const auto& sensor : sensors) {

        std::cout << "- Sensor ID: " << sensor->getID() << " | Location: " << sensor->getLocation() << " | Class: " << typeid(*sensor).name() << std::endl;
        std::cout << " Reading: " << sensor->getReading() << std::endl;

        SmogSensor* sns = dynamic_cast<SmogSensor*>(sensor.get()); //get(), aby wyciagnac fizyczny adres z inteligentnego wskaznika

        if (sns != nullptr) {

            if (sns->getAirQuality() == AirQuality::HAZARDOUS) {

                std::cout << " !!! ALARM !!! Toxic Air Detected in " << sns->getLocation() << "!" <<std::endl;

            }

            std::cout << " Status: " << AirQualityToString(sns->getAirQuality()) << "(Level: " << static_cast<int>(sns->getAirQuality()) << std::endl;

        }

    }

}
