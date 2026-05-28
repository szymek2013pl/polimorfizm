#pragma once

#include "Enums.hpp"

#include <string>
#include <vector>

class SecurityBreachException : public std::exception {

    public:

        const char* what() const noexcept override { return "ALERT: Insufficient clearance level detected! Connection terminated."; }

};

class ITAsset {

    protected:

        inline static int global_asset_id = 1000;
        const int assetID;
        std::string hostname;
        std::string ipAddress;
        SecurityClearance clearance;
        OSType os;

    public:

        ITAsset(std::string hostname, std::string ipAddress, SecurityClearance clearance, OSType os) : assetID{global_asset_id++}, hostname{hostname}, ipAddress{ipAddress}, clearance{clearance}, os{os} {}
        virtual ~ITAsset() = default;

        virtual void printAssetDetails() const = 0;

        const int getID() const { return assetID; }
        std::string getHostname() const { return hostname; }
        std::string getIP() const { return ipAddress; }
        SecurityClearance getSec() const { return clearance; }
        OSType getOS() const { return os; }

};

class ServerNode : public ITAsset {

    protected:

        int cpuCores;
        double ramGB;

    public:

        ServerNode(std::string hostname, std::string ipAddress, SecurityClearance clearance, OSType os, int cpuCores, double ramGB) : ITAsset(hostname, ipAddress, clearance, os), cpuCores{cpuCores}, ramGB{ramGB} {}
        virtual ~ServerNode() = default;

        virtual bool allocateResources(int reqCores, double reqRam, SecurityClearance reqClearance);

};

class DatabaseServer : public ServerNode {

    private:

        double storageTB;

    public:

        DatabaseServer(std::string hostname, std::string ipAddress, SecurityClearance clearance, OSType os, int cpuCores, double ramGB, double storageTB) : ServerNode(hostname, ipAddress, clearance, os, cpuCores, ramGB), storageTB{storageTB} {}
        
        void printAssetDetails() const override;

};

class Workstation : public ITAsset {

    private:

        std::string assignedEmployee;
        bool isLaptop;

    public:

        Workstation(std::string hostname, std::string ipAddress, SecurityClearance clearance, OSType os, std::string assignedEmployee, bool isLaptop) : ITAsset(hostname, ipAddress, clearance, os), assignedEmployee{assignedEmployee}, isLaptop{isLaptop} {}
        void printAssetDetails() const override;

        bool getLaptop() { return isLaptop; }
        std::string getEmployee() const { return assignedEmployee; }

};

class Datacenter {

    protected:

        std::vector<ITAsset*> inventory;

    public:

        void registerAsset(ITAsset* a) { inventory.push_back(a); }
        void performSecurityAudit(SecurityClearance minClearance);
        void deployPatch(OSType targetOS);

};
