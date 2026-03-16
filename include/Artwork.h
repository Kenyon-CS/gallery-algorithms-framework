#pragma once

#include <string>
#include "Types.h"

namespace gallery {

struct Artwork {
    std::string id;
    std::string title;
    ArtworkType type = ArtworkType::Unknown;
    double size = 0.0;
    double lightSensitivity = 0.5;
    std::string preferredRoom;
};

}  // namespace gallery
