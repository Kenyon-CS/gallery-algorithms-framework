#pragma once

#include <string>
#include <vector>

namespace gallery {

struct ScoreBreakdown {
    double compatibility = 0.0;
    double capacity = 0.0;
    double light = 0.0;
    double roomPreference = 0.0;
    double unplaced = 0.0;
    double duplicateUse = 0.0;
    double total() const {
        return compatibility + capacity + light + roomPreference + unplaced + duplicateUse;
    }
};

class LayoutState {
public:
    std::vector<int> placement;  // artwork index -> zone index, -1 means unplaced
    ScoreBreakdown breakdown;
    double score = 0.0;
    std::string algorithmName;

    explicit LayoutState(std::size_t artworkCount = 0)
        : placement(artworkCount, -1) {}
};

}  // namespace gallery
