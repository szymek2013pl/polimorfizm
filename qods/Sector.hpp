#pragma once
#include <string>

enum class Sector {
    LowOrbit,
    DeepSpace,
    LunarColony
};

inline std::string sector_to_string(Sector s) {
    switch(s) {
        case Sector::LowOrbit: return "Low Earth Orbit";
        case Sector::DeepSpace: return "Deep Space Sector";
        case Sector::LunarColony: return "Lunar Outpost";
    }
    return "Unknown";
}
