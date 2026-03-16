#include "Evaluator.h"

#include <cmath>
#include <vector>

#include "Types.h"

namespace gallery {

Evaluator::Evaluator(ScoringConfig config) : config_(config) {}

double Evaluator::evaluate(LayoutState& state, const Gallery& gallery, const Show& show) const {
    state.breakdown = {};
    std::vector<int> zoneUseCount(gallery.zones.size(), 0);

    for (std::size_t i = 0; i < show.artworks.size(); ++i) {
        const Artwork& art = show.artworks[i];
        const int zoneIndex = state.placement[i];

        if (zoneIndex < 0 || static_cast<std::size_t>(zoneIndex) >= gallery.zones.size()) {
            state.breakdown.unplaced += config_.unplacedPenalty;
            continue;
        }

        const Zone& zone = gallery.zones[zoneIndex];
        zoneUseCount[zoneIndex] += 1;

        if (isCompatible(art.type, zone.type)) {
            state.breakdown.compatibility += config_.typeMatchReward;
        } else {
            state.breakdown.compatibility += config_.typeMismatchPenalty;
        }

        if (art.size > zone.capacity) {
            state.breakdown.capacity += config_.capacityOverflowPenalty;
        }

        const double excessLight = std::max(0.0, zone.light - art.lightSensitivity);
        state.breakdown.light -= excessLight * config_.lightPenaltyMultiplier;

        if (!art.preferredRoom.empty() && art.preferredRoom == zone.room) {
            state.breakdown.roomPreference += config_.roomPreferenceReward;
        }
    }

    for (int count : zoneUseCount) {
        if (count > 1) {
            state.breakdown.duplicateUse += (count - 1) * config_.duplicateZonePenalty;
        }
    }

    state.score = state.breakdown.total();
    return state.score;
}

}  // namespace gallery
