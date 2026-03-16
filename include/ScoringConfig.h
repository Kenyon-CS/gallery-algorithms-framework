#pragma once

namespace gallery {

struct ScoringConfig {
    double typeMatchReward = 15.0;
    double typeMismatchPenalty = -50.0;
    double capacityOverflowPenalty = -80.0;
    double unplacedPenalty = -120.0;
    double roomPreferenceReward = 10.0;
    double duplicateZonePenalty = -100.0;
    double lightPenaltyMultiplier = 40.0;
};

}  // namespace gallery
