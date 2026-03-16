#pragma once

#include <string>
#include "Types.h"

namespace gallery {

struct Zone {
    std::string id;
    std::string room;
    ZoneType type = ZoneType::Unknown;
    double capacity = 0.0;
    double light = 0.5;
    bool supportsVideo = false;
};

}  // namespace gallery
