#pragma once
#include <string>

enum class SecurityClearance {
    PUBLIC = 0,
    RESTRICTED = 1,
    CONFIDENTIAL = 2,
    TOP_SECRET = 3
};

enum class OSType {
    LINUX_SERVER = 10,
    WINDOWS_WORKSTATION = 20,
    CUSTOM_FIRMWARE = 30
};
