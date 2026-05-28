#pragma once

#include "TeamProfile.hpp"
#include "RaceEnums.hpp"

#include <vector>

class TireBlowoutException : public std::exception {

    public:

        const char* what() const noexcept override { return "CRITICAL: Tire structural failure! Car must retire."; }

};

class RaceVehicle {

    protected:

        inline static int next_vin = 8000;
        const int vinNumber;
        TeamProfile team;
        TireCompound currentTires;

    public:

        RaceVehicle(const TeamProfile& team, const TireCompound& currentTires) :vinNumber{next_vin++}, team{team}, currentTires{currentTires} {}
        virtual ~RaceVehicle() = default;

        virtual void printTelemetry() const = 0;

        const int getID() const { return vinNumber; }
        TeamProfile getTeam() const { return team; }
        TireCompound getTyres() const { return currentTires; }

};

class OpenWheel : public RaceVehicle {

    protected:

        double aeroDownforce;
    
    public:

        OpenWheel(const TeamProfile& team, const TireCompound& currentTires, double aeroDownforce) : RaceVehicle(team, currentTires), aeroDownforce{aeroDownforce} {}
        virtual ~OpenWheel() = default;

};

class EnduranceCar : public RaceVehicle {

    protected:

        double fuelCapacity;

    public:

        EnduranceCar(const TeamProfile& team, const TireCompound& currentTires, double fuelCapacity) : RaceVehicle(team, currentTires), fuelCapacity{fuelCapacity} {}
        virtual ~EnduranceCar() = default;

};

class FormulaV10 : public OpenWheel {

    private:

        int engineWear;
    
    public:

        FormulaV10(const TeamProfile& team, const TireCompound& currentTires, double aeroDownforce, int engineWear) : OpenWheel(team, currentTires, aeroDownforce), engineWear{engineWear} {}
        
        void printTelemetry() const override; 

};

class HypercarLMDh : public EnduranceCar {

    private:

        bool hybridEngaged;
    
    public:

        HypercarLMDh(const TeamProfile& team, const TireCompound& currentTires, double fuelCapacity, bool hybridEngaged) : EnduranceCar(team, currentTires, fuelCapacity), hybridEngaged{hybridEngaged} {}

        void printTelemetry() const override;

};

class IDRSProtocol {

    protected:

        bool drsEnabled;

    public:

        IDRSProtocol(bool drsEnabled = false) : drsEnabled{drsEnabled} {}
        virtual ~IDRSProtocol() = default;

        virtual void toggleDRS() = 0;

        bool getDRS() const {

            return drsEnabled;

        }

};

class IPitstopSystem {

    public:

        IPitstopSystem() = default;
        virtual ~IPitstopSystem() = default;

        virtual void performPitstop(TireCompound newTire) = 0;

};

class FormulaUltimate : public OpenWheel, public IDRSProtocol, public IPitstopSystem {

    private:

        double tireWear;

    public: // - do poprawy konstruktor

        FormulaUltimate(const TeamProfile& team, const TireCompound& currentTires, double aeroDownforce, double tireWear) : OpenWheel(team, currentTires, aeroDownforce), IDRSProtocol(), IPitstopSystem(), tireWear{tireWear} {}

        void printTelemetry() const override;
        void toggleDRS() override;
        void performPitstop(TireCompound newTire) override; 

};

class SessionManager {

    protected:

        std::vector<RaceVehicle*> grid;

    public:

        SessionManager() = default;

        void addVehicle(RaceVehicle* v) { grid.push_back(v); }
        void processLap();

        void enforceWeatherRules(TireCompound mandatoryTire);

};
