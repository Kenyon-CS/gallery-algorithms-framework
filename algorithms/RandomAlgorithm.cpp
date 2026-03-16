#include "Algorithm.h"
#include "Types.h"

#include <memory>
#include <random>
#include <stdexcept>

namespace gallery {
namespace {

class RandomAlgorithm final : public Algorithm {
public:
    LayoutState solve(const Gallery& gallery, const Show& show, const Evaluator& evaluator) override {
        LayoutState state(show.artworks.size());
        state.algorithmName = name();

        if (gallery.zones.empty()) {
            evaluator.evaluate(state, gallery, show);
            return state;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, static_cast<int>(gallery.zones.size()) - 1);

        for (std::size_t i = 0; i < show.artworks.size(); ++i) {
            state.placement[i] = dist(gen);
        }

        evaluator.evaluate(state, gallery, show);
        return state;
    }

    std::string name() const override { return "random"; }
};

}  // namespace

std::unique_ptr<Algorithm> makeGreedyAlgorithm();

std::unique_ptr<Algorithm> createAlgorithm(const std::string& name) {
    const std::string lowered = toLower(name);
    if (lowered == "greedy") {
        return makeGreedyAlgorithm();
    }
    if (lowered == "random") {
        return std::make_unique<RandomAlgorithm>();
    }
    throw std::runtime_error("Unknown algorithm: " + name + ". Supported: greedy, random");
}

}  // namespace gallery
