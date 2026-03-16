#include "Parser.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "Types.h"
#include "Util.h"

namespace gallery {
namespace {

std::vector<std::string> readMeaningfulLines(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Could not open file: " + path);
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        const auto commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }
        line = trim(line);
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    return lines;
}

std::pair<std::string, std::string> splitKeyValue(const std::string& line) {
    const auto pos = line.find(':');
    if (pos == std::string::npos) {
        return {trim(line), ""};
    }
    const std::string key = trim(line.substr(0, pos));
    const std::string value = stripQuotes(trim(line.substr(pos + 1)));
    return {key, value};
}

double parseDoubleOrThrow(const std::string& value, const std::string& field) {
    try {
        return std::stod(value);
    } catch (...) {
        throw std::runtime_error("Invalid numeric value for '" + field + "': " + value);
    }
}

bool parseBool(const std::string& value) {
    const std::string s = toLower(value);
    return s == "true" || s == "yes" || s == "1";
}

}  // namespace

Gallery loadGallery(const std::string& path) {
    const auto lines = readMeaningfulLines(path);
    Gallery gallery;

    bool inZones = false;
    Zone current;
    bool haveCurrent = false;

    for (const auto& line : lines) {
        if (line == "gallery:") {
            continue;
        }
        if (line == "zones:") {
            inZones = true;
            continue;
        }
        auto [key, value] = splitKeyValue(line);
        if (key == "name") {
            gallery.name = value;
            continue;
        }
        if (inZones && startsWith(line, "- ")) {
            if (haveCurrent) {
                gallery.zones.push_back(current);
            }
            current = Zone{};
            haveCurrent = true;
            std::string remainder = trim(line.substr(2));
            if (!remainder.empty()) {
                auto [subKey, subValue] = splitKeyValue(remainder);
                if (subKey == "id") current.id = subValue;
            }
            continue;
        }
        if (haveCurrent) {
            if (key == "id") current.id = value;
            else if (key == "room") current.room = value;
            else if (key == "type") current.type = parseZoneType(value);
            else if (key == "capacity") current.capacity = parseDoubleOrThrow(value, "capacity");
            else if (key == "light") current.light = parseDoubleOrThrow(value, "light");
            else if (key == "supports_video") current.supportsVideo = parseBool(value);
        }
    }

    if (haveCurrent) {
        gallery.zones.push_back(current);
    }

    if (gallery.zones.empty()) {
        throw std::runtime_error("Gallery file contains no zones: " + path);
    }

    return gallery;
}

Show loadShow(const std::string& path) {
    const auto lines = readMeaningfulLines(path);
    Show show;

    bool inArtworks = false;
    Artwork current;
    bool haveCurrent = false;

    for (const auto& line : lines) {
        if (line == "show:") {
            continue;
        }
        if (line == "artworks:") {
            inArtworks = true;
            continue;
        }
        auto [key, value] = splitKeyValue(line);
        if (!inArtworks && key == "title") {
            show.title = value;
            continue;
        }
        if (inArtworks && startsWith(line, "- ")) {
            if (haveCurrent) {
                show.artworks.push_back(current);
            }
            current = Artwork{};
            haveCurrent = true;
            std::string remainder = trim(line.substr(2));
            if (!remainder.empty()) {
                auto [subKey, subValue] = splitKeyValue(remainder);
                if (subKey == "id") current.id = subValue;
            }
            continue;
        }
        if (haveCurrent) {
            if (key == "id") current.id = value;
            else if (key == "title") current.title = value;
            else if (key == "type") current.type = parseArtworkType(value);
            else if (key == "size") current.size = parseDoubleOrThrow(value, "size");
            else if (key == "light_sensitivity") current.lightSensitivity = parseDoubleOrThrow(value, "light_sensitivity");
            else if (key == "preferred_room") current.preferredRoom = value;
        }
    }

    if (haveCurrent) {
        show.artworks.push_back(current);
    }

    if (show.artworks.empty()) {
        throw std::runtime_error("Show file contains no artworks: " + path);
    }

    return show;
}

ScoringConfig loadScoring(const std::string& path) {
    const auto lines = readMeaningfulLines(path);
    ScoringConfig cfg;

    for (const auto& line : lines) {
        if (line == "scoring:") {
            continue;
        }
        auto [key, value] = splitKeyValue(line);
        if (value.empty()) continue;

        if (key == "type_match_reward") cfg.typeMatchReward = parseDoubleOrThrow(value, key);
        else if (key == "type_mismatch_penalty") cfg.typeMismatchPenalty = parseDoubleOrThrow(value, key);
        else if (key == "capacity_overflow_penalty") cfg.capacityOverflowPenalty = parseDoubleOrThrow(value, key);
        else if (key == "unplaced_penalty") cfg.unplacedPenalty = parseDoubleOrThrow(value, key);
        else if (key == "room_preference_reward") cfg.roomPreferenceReward = parseDoubleOrThrow(value, key);
        else if (key == "duplicate_zone_penalty") cfg.duplicateZonePenalty = parseDoubleOrThrow(value, key);
        else if (key == "light_penalty_multiplier") cfg.lightPenaltyMultiplier = parseDoubleOrThrow(value, key);
    }

    return cfg;
}

}  // namespace gallery
