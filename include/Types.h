#pragma once

#include <cctype>
#include <stdexcept>
#include <string>

namespace gallery {

enum class ZoneType {
    Wall,
    Floor,
    Ceiling,
    Video,
    Unknown
};

enum class ArtworkType {
    Wall,
    Floor,
    Ceiling,
    Video,
    Unknown
};

inline std::string toLower(std::string s) {
    for (char& c : s) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return s;
}

inline ZoneType parseZoneType(const std::string& raw) {
    const std::string s = toLower(raw);
    if (s == "wall") return ZoneType::Wall;
    if (s == "floor") return ZoneType::Floor;
    if (s == "ceiling") return ZoneType::Ceiling;
    if (s == "video") return ZoneType::Video;
    return ZoneType::Unknown;
}

inline ArtworkType parseArtworkType(const std::string& raw) {
    const std::string s = toLower(raw);
    if (s == "wall") return ArtworkType::Wall;
    if (s == "floor") return ArtworkType::Floor;
    if (s == "ceiling") return ArtworkType::Ceiling;
    if (s == "video") return ArtworkType::Video;
    return ArtworkType::Unknown;
}

inline std::string toString(ZoneType t) {
    switch (t) {
        case ZoneType::Wall: return "wall";
        case ZoneType::Floor: return "floor";
        case ZoneType::Ceiling: return "ceiling";
        case ZoneType::Video: return "video";
        default: return "unknown";
    }
}

inline std::string toString(ArtworkType t) {
    switch (t) {
        case ArtworkType::Wall: return "wall";
        case ArtworkType::Floor: return "floor";
        case ArtworkType::Ceiling: return "ceiling";
        case ArtworkType::Video: return "video";
        default: return "unknown";
    }
}

inline bool isCompatible(ArtworkType a, ZoneType z) {
    return (a == ArtworkType::Wall && z == ZoneType::Wall) ||
           (a == ArtworkType::Floor && z == ZoneType::Floor) ||
           (a == ArtworkType::Ceiling && z == ZoneType::Ceiling) ||
           (a == ArtworkType::Video && z == ZoneType::Video);
}

}  // namespace gallery
