#pragma once
#include <string>

enum class TireCompound {
    SOFT = 0,
    MEDIUM = 1,
    WET = 2
};

inline std::string tire_to_string(TireCompound t) {
    switch(t) {
        case TireCompound::SOFT: return "Soft Slick";
        case TireCompound::MEDIUM: return "Medium Slick";
        case TireCompound::WET: return "Heavy Wet";
    }
    return "Unknown";
}
