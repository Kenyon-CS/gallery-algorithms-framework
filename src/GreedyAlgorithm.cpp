#include "Algorithm.h"

#include <limits>

namespace gallery {

class GreedyAlgorithm final : public Algorithm {
public:
    LayoutState solve(const Gallery& gallery, const Show& show, const Evaluator& evaluator) override {
        LayoutState state(show.artworks.size());
        state.algorithmName = name();

        for (std::size_t i = 0; i < show.artworks.size(); ++i) {
            double bestScore = -std::numeric_limits<double>::infinity();
            int bestZone = -1;

            for (std::size_t z = 0; z < gallery.zones.size(); ++z) {
                LayoutState trial = state;
                trial.placement[i] = static_cast<int>(z);
                const double score = evaluator.evaluate(trial, gallery, show);
                if (score > bestScore) {
                    bestScore = score;
                    bestZone = static_cast<int>(z);
                }
            }

            state.placement[i] = bestZone;
            evaluator.evaluate(state, gallery, show);
        }

        evaluator.evaluate(state, gallery, show);
        return state;
    }

    std::string name() const override { return "greedy"; }
};

std::unique_ptr<Algorithm> makeGreedyAlgorithm() {
    return std::make_unique<GreedyAlgorithm>();
}

}  // namespace gallery
