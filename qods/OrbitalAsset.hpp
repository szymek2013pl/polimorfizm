#pragma once

#include "Sector.hpp"
#include "CryptoUtils.hpp"
#include "ClearenceProfile.hpp"

#include <vector>

class ShieldCollapseException : public std::exception {

    public:

        const char* what() const noexcept override { return "CRITICAL: Shield generators overloaded. Core exposed!"; }

};

class OrbitalAsset {

    protected:

        inline static int global_id = 500;
        const int assetId;
        Sector sector;
        ClearanceProfile profile;

    public:

        OrbitalAsset(const Sector& sector, const ClearanceProfile& profile) : assetId{global_id++}, sector{sector}, profile{profile} {}
        virtual ~OrbitalAsset() = default;

        virtual void broadcastStatus() const = 0;

        const int getAssetID() const { return assetId; }
        Sector getSector() const { return sector; }
        ClearanceProfile getProfile() const { return profile; }

};

class CommSatellite : public OrbitalAsset {

    protected:

        double uplinkBandwidth;

    public:    

        CommSatellite(const Sector& sector, const ClearanceProfile& profile, double uplinkBandwidth) : OrbitalAsset(sector, profile), uplinkBandwidth{uplinkBandwidth} {}
        virtual ~CommSatellite() = default;

};

class DefensePlatform : public OrbitalAsset {

    protected:

        int ammoCount;

    public:

        DefensePlatform(const Sector& sector, const ClearanceProfile& profile, int ammoCount) : OrbitalAsset(sector, profile), ammoCount{ammoCount} {}
        virtual ~DefensePlatform() = default;

};

class DeepSpaceRelay : public CommSatellite {

    private:

        bool isEncrypted;

    public:

        DeepSpaceRelay(const Sector& sector, const ClearanceProfile& profile, double uplinkBandwidth, bool isEncrypted) : CommSatellite(sector, profile, uplinkBandwidth), isEncrypted{isEncrypted} {}

        void broadcastStatus() const override;

};

class RailgunBattery : public DefensePlatform {

    private:

        double barrelWear;

    public:

        RailgunBattery(const Sector& sector, const ClearanceProfile& profile, int ammoCount, double barrelWear) : DefensePlatform(sector, profile, ammoCount), barrelWear{barrelWear} {}

        void broadcastStatus() const override;

};

class IShieldGenerator {

    protected:

        double shieldIntegrity;
    
    public:

        IShieldGenerator(double shieldIntegrity) : shieldIntegrity{shieldIntegrity} {}
        virtual ~IShieldGenerator() = default;

        virtual void absorbImpact(double damage) = 0;

};

class ITargetingSystem {

    public:

        ITargetingSystem() = default;
        virtual ~ITargetingSystem() = default;

        virtual void lockAndFire(OrbitalAsset* target) = 0;

};

class AegisCruiser : public DefensePlatform, public IShieldGenerator, public ITargetingSystem {

    public:

        AegisCruiser(const Sector& sector, const ClearanceProfile& profile, int ammoCount, double shieldIntegrity, int bonusArmor) : DefensePlatform(sector, profile, ammoCount), IShieldGenerator(shieldIntegrity + bonusArmor), ITargetingSystem() {} 

        void broadcastStatus() const override;
        void absorbImpact(double damage) override;
        void lockAndFire(OrbitalAsset* target) override;

};

class DefenseGrid {

    protected:

        std::vector<OrbitalAsset*> gridAssets;

    public:

        DefenseGrid() = default;

        void addAsset(OrbitalAsset* obj) { gridAssets.push_back(obj); }
        void simulateEngagement(double incomingVolley);

};
