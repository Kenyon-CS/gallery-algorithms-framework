#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

#include "Algorithm.h"
#include "Parser.h"

namespace {

void printUsage() {
    std::cout << "Usage:\n"
              << "  planner <gallery.yaml> <show.yaml> <algorithm> [scoring.yaml]\n\n"
              << "Algorithms:\n"
              << "  greedy\n"
              << "  random\n";
}

}  // namespace

int main(int argc, char* argv[]) {
    try {
        if (argc < 4 || argc > 5) {
            printUsage();
            return 1;
        }

        const std::string galleryPath = argv[1];
        const std::string showPath = argv[2];
        const std::string algorithmName = argv[3];

        gallery::Gallery gallery = gallery::loadGallery(galleryPath);
        gallery::Show show = gallery::loadShow(showPath);
        gallery::ScoringConfig scoring = (argc == 5)
            ? gallery::loadScoring(argv[4])
            : gallery::ScoringConfig{};

        gallery::Evaluator evaluator(scoring);
        auto algorithm = gallery::createAlgorithm(algorithmName);
        gallery::LayoutState result = algorithm->solve(gallery, show, evaluator);

        std::cout << "Gallery Planner\n";
        std::cout << "===============\n";
        std::cout << "Gallery:   " << gallery.name << "\n";
        std::cout << "Show:      " << show.title << "\n";
        std::cout << "Algorithm: " << result.algorithmName << "\n\n";

        std::cout << "Score Breakdown\n";
        std::cout << "---------------\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Compatibility:   " << result.breakdown.compatibility << "\n";
        std::cout << "Capacity:        " << result.breakdown.capacity << "\n";
        std::cout << "Lighting:        " << result.breakdown.light << "\n";
        std::cout << "Room Preference: " << result.breakdown.roomPreference << "\n";
        std::cout << "Unplaced:        " << result.breakdown.unplaced << "\n";
        std::cout << "Duplicate Use:   " << result.breakdown.duplicateUse << "\n";
        std::cout << "TOTAL:           " << result.score << "\n\n";

        std::cout << "Placements\n";
        std::cout << "----------\n";
        for (std::size_t i = 0; i < show.artworks.size(); ++i) {
            const auto& art = show.artworks[i];
            const int zoneIndex = result.placement[i];
            if (zoneIndex < 0) {
                std::cout << art.id << " (" << art.title << ") -> UNPLACED\n";
            } else {
                const auto& zone = gallery.zones[static_cast<std::size_t>(zoneIndex)];
                std::cout << art.id << " (" << art.title << ") -> "
                          << zone.id << " [room=" << zone.room
                          << ", type=" << gallery::toString(zone.type)
                          << ", cap=" << zone.capacity << "]\n";
            }
        }

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 2;
    }
}
