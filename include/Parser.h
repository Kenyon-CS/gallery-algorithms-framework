#pragma once

#include <string>
#include "Gallery.h"
#include "ScoringConfig.h"
#include "Show.h"

namespace gallery {

Gallery loadGallery(const std::string& path);
Show loadShow(const std::string& path);
ScoringConfig loadScoring(const std::string& path);

}  // namespace gallery
