#pragma once

#include <string>
#include <vector>
#include "Artwork.h"

namespace gallery {

class Show {
public:
    std::string title;
    std::vector<Artwork> artworks;
};

}  // namespace gallery
