#pragma once

#include <string>
#include <vector>
#include "Zone.h"

namespace gallery {

class Gallery {
public:
    std::string name;
    std::vector<Zone> zones;
};

}  // namespace gallery
