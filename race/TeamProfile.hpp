#pragma once
#include <string>
#include <utility>

class TeamProfile {
private:
    std::string teamName;
    int pitCrewSkill;

public:
    TeamProfile(std::string name, int skill) : teamName(std::move(name)), pitCrewSkill(skill) {}
    
    std::string getName() const { return teamName; }
    int getSkill() const { return pitCrewSkill; }
};
