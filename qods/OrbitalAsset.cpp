#include "OrbitalAsset.hpp"

#include <iostream>

void DeepSpaceRelay::broadcastStatus() const { // - generalnie w kazdym broadcastStatus nalezy obsluzyc te wszystkie zmienne zdefiniowane w innych plikach, za pomoca rowniez funkcji tam dostarczonych

    std::string s = "";

    if (isEncrypted) {

        s = "Yes";

    }

    else {

        s = "No";

    }
    
    std::cout << "[RELAY] ID: " << assetId << " | Sector: " << sector_to_string(sector) << " | Faction: " << profile.getFaction() << " (Lvl " << profile.getLevel() << " | Bandwidth: " << uplinkBandwidth << " | Encrypted: " << s << std::endl;

}

void RailgunBattery::broadcastStatus() const {

    std::cout << "[RAILGUN] ID: " << assetId << " | Sector: " << sector_to_string(sector) << " | Ammo: " << ammoCount << " | Wear: " << barrelWear << std::endl;

}

void AegisCruiser::broadcastStatus() const {

    std::cout << "[CRUISER] ID: " << assetId << " | Ammo: " << ammoCount << " | Shields: " << shieldIntegrity << " | Hash: " << CryptoUtils::generateCommsHash(assetId, profile.getLevel()) << std::endl;

}

void AegisCruiser::absorbImpact(double damage) {

    shieldIntegrity -= damage;

    if (shieldIntegrity < 0) {

        throw ShieldCollapseException();

    }

    else {

        std::cout << "Impact absorbed. Shields at " << shieldIntegrity << std::endl;

    }

}

void AegisCruiser::lockAndFire(OrbitalAsset* target) {

    if (ammoCount <= 0) {

        std::cout << "Click. Out of ammo." << std::endl;
        return;

    }

    CommSatellite* sat = dynamic_cast<CommSatellite*>(target);

    if (sat != nullptr) {

        std::cout << "Friendly fire protocol. Comm satellite ignored." << std::endl;

    }

    else {

        ammoCount -= 1;

        IShieldGenerator* shd = dynamic_cast<IShieldGenerator*>(target);

        if (shd!= nullptr) {

            shd->absorbImpact(50.0);

        }

        else {

            std::cout << "Target has no shields. Hull breached." << std::endl;

        }

    }

}

void DefenseGrid::simulateEngagement(double incomingVolley) {

    for (auto asset : gridAssets) {

        asset->broadcastStatus();
        
        IShieldGenerator* shd = dynamic_cast<IShieldGenerator*>(asset);

        if (shd != nullptr) {

            try {

                shd->absorbImpact(incomingVolley);

            }

            catch (ShieldCollapseException& e) {

                std::cout << e.what() << std::endl;
                std::cout << "[GRID] Rerouting emergency power..." << std::endl;

            }

            ITargetingSystem* trt = dynamic_cast<ITargetingSystem*>(shd); // - bardzo wazna linijka, trzeba bedzie powtorzyc, generalnie chodzi o to, ze moze byc obiekt, ktory ma tarcze i moze namierzac, 
                                                                          // - ma zwyczajnie dwa te interfejcy, tj aegisCruiser, wiec przeswietlamy dwukrotnie, bo klasa pochodna jest wszystkicj typow, po ktorych dziedziczy
            if (trt != nullptr) {

                trt->lockAndFire(gridAssets[0]);

            }

        }

        else {

            std::cout << "[GRID] Asset destroyed by volley..." << std::endl;
            
        }

    }

}
