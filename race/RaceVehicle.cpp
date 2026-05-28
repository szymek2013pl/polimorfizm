#include "RaceVehicle.hpp"

#include <iostream>

void FormulaV10::printTelemetry() const {

    std::cout << "[F-V10] VIN: " << vinNumber << " | Team: " << team.getName() << " (Pit Skill: " << team.getSkill() << ") | Tires: " << tire_to_string(currentTires) << " | Downforce: " << aeroDownforce << "kg | Wear: " << engineWear << "%" << std::endl;  

}

void HypercarLMDh::printTelemetry() const {

    std::string h = "";

    if (hybridEngaged) {

        h = "ON";

    }

    else {

        h = "OFF";

    }
    
    std::cout << "[LMDh] VIN: " << vinNumber << " | Team: " << team.getName() << " | Fuel: " << fuelCapacity << "L | Hybrid: " << h << std::endl;

}

void FormulaUltimate::printTelemetry() const {

    std::string d = "";
    
    if (drsEnabled) {

        d = "ENABLED";

    }

    else {

        d  = "DISABLED";

    }
    
    std::cout << "[ULTIMATE] VIN: " << vinNumber << " | Tires: " << tire_to_string(currentTires) << " | Wear: " << tireWear << " | DRS: " << d << std::endl;

}

void FormulaUltimate::toggleDRS() {

    if (drsEnabled) {

        drsEnabled = false;

    }

    else {

        drsEnabled = true;

    }

    std::cout << "DRS status changed" << std::endl;

}

void FormulaUltimate::performPitstop(TireCompound newTire) {

    if (tireWear > 95.0) {

        throw TireBlowoutException();

    }

    else {

        currentTires = newTire;
        tireWear = 0.0;

        std::cout << "Pitstop complete. Fitted: " << tire_to_string(newTire) << " (Code: " << static_cast<int>(newTire) << std::endl;

    }

}

void SessionManager::processLap() {

    for (auto car : grid) {

        car->printTelemetry();

        IDRSProtocol* drs = dynamic_cast<IDRSProtocol*>(car);

        if (drs != nullptr) {

            drs->toggleDRS();

        }

        IPitstopSystem* pit = dynamic_cast<IPitstopSystem*>(car);

        if (pit != nullptr) {

            try {

                pit->performPitstop(TireCompound::SOFT);

            }

            catch (TireBlowoutException& e) {

                std::cout << e.what() << std::endl;
                std::cout << "[STEWARD] Vehicle removed from track" << std::endl;

            }

        }

    }

}

void SessionManager::enforceWeatherRules(TireCompound mandatoryTire) {

    for (auto car : grid) {

        if (car->getTyres() != mandatoryTire) {

            std::cout << "Penalty issued to VIN: " << car->getID() << ". Wrong tire compound!" << std::endl;
            continue;

        }

        else {

            switch(car->getTyres()) {

                case TireCompound::WET : std::cout << "Safety confirmed for wet conditions." << std::endl;
                break;
                case TireCompound::SOFT : std::cout << "Agressive strategy detected." << std::endl;
                break;
                case TireCompound::MEDIUM : std::cout << "Balanced strategy detected." << std::endl;
                break;

            }

        }

    }

}
