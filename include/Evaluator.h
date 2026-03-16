#pragma once

#include "Gallery.h"
#include "LayoutState.h"
#include "ScoringConfig.h"
#include "Show.h"

namespace gallery {

class Evaluator {
public:
    explicit Evaluator(ScoringConfig config = {});
    double evaluate(LayoutState& state, const Gallery& gallery, const Show& show) const;
    const ScoringConfig& config() const { return config_; }

private:
    ScoringConfig config_;
};

}  // namespace gallery
