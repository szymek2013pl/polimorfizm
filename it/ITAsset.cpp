#include "ITAsset.hpp"

#include <iostream>

void DatabaseServer::printAssetDetails() const {

    std::cout << "Asset [ID: " << assetID << " - " << hostname << "(" << ipAddress << ") | OS Code: " << static_cast<int>(os) << " | SecLevel: " << static_cast<int>(clearance) << " -> DB_SERVER [Cores: " << cpuCores << ", RAM: " << ramGB << "GB, Storage: " << storageTB << "TB" << std::endl;

}

void Workstation::printAssetDetails() const {

    std::string is = "";

    if (isLaptop) {

        is = "Yes";

    }

    else {

        is = "No";

    }
    
    std::cout << "Asset [ID: " << assetID << " ] - " << hostname << "(" << ipAddress << ") | OS Code: " << static_cast<int>(os) << " | SecLevel: " << static_cast<int>(clearance) << " -> Workstation [Owner: " << assignedEmployee << ", Mobile: " << is << std::endl;

}

bool ServerNode::allocateResources(int reqCores, double reqRam, SecurityClearance reqClearance) {

    if (getSec() < reqClearance) {

        throw SecurityBreachException();

    }

    if (cpuCores >= reqCores && ramGB >= reqRam) {

        std::cout << "[" << hostname << "] Resources allocated successfully." << std::endl;
        return true;

    }

    else {

        std::cout << "[" << hostname << "] Allocation failed. Insufficient hardware." << std::endl;
        return false;

    }

}

void Datacenter::performSecurityAudit(SecurityClearance minClearance) {

    for (const auto& i : inventory) {

        i->printAssetDetails();

        try {
        
            ServerNode* sv = dynamic_cast<ServerNode*>(i);

            if (sv != nullptr) {

                sv->allocateResources(16, 32.0, minClearance);

            }
        }

        catch (SecurityBreachException& e) {

            std::cout << e.what() << std::endl;
            std::cout << "[AUDIT] Flagging server " << i->getHostname() << " for immediate review." << std::endl;

        }

        Workstation* wrk = dynamic_cast<Workstation*>(i);

        if (wrk != nullptr) {

            if (wrk->getLaptop()) {

                std::cout << "[AUDIT] Laptop " << wrk->getHostname() << " assigned to " << wrk->getEmployee() << " requires VPN token." << std::endl;

            }

        }

    }

}

void Datacenter::deployPatch(OSType targetOS) {

    for (const auto& t : inventory) {

        if (t->getOS() != targetOS) {

            std::cout << "[PATCH] Skipping" << t->getHostname() << " - OS mismatch" << std::endl;

        }

        else {

            DatabaseServer* d = dynamic_cast<DatabaseServer*>(t);

            if (d != nullptr) {

                std::cout << "[PATCH] Stopping DB services on " << d->getHostname() << "... Patching... Done" <<std::endl;

            }

            Workstation* wrk = dynamic_cast<Workstation*>(t);

            if (wrk != nullptr) {

                if (wrk->getSec() == SecurityClearance::TOP_SECRET || wrk->getSec() == SecurityClearance::CONFIDENTIAL) {

                    std::cout << "[PATCH] Updating " << wrk->getHostname() << " in background (Silent Mode)" <<std::endl;

                }

                else {

                    std::cout << "[PATCH] Prompting user " << wrk->getEmployee() << " on " << wrk->getHostname() << " for update." << std::endl;

                }

            }

        }

    }

}
