#pragma once
#include <string>
#include <utility>

class ClearanceProfile {
private:
    std::string factionName;
    int securityLevel;

public:
    ClearanceProfile(std::string faction, int level) : factionName(std::move(faction)), securityLevel(level) {}
    
    std::string getFaction() const { return factionName; }
    int getLevel() const { return securityLevel; }
};
