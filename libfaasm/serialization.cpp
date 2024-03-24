#include "faasm/serialization.h"

namespace faasm {
// Transforms a uint8_t vector of bytes into a uint32_t
uint32_t uint8VToUint32(const std::vector<uint8_t>& bytes)
{
    uint32_t value = 0;
    for (int i = 0; i < 4; i++) {
        value = (value << 8) | bytes[i];
    }
    return value;
}
// Transforms unint32_t of bytes into a uint8_t vector
std::vector<uint8_t> uint32ToUint8V(uint32_t value)
{
    std::vector<uint8_t> bytes(4);
    for (int i = 0; i < 4; i++) {
        bytes[3 - i] = (value >> (i * 8)) & 0xFF;
    }
    return bytes;
}

// Transforms a map <string, int> into a uint8_t vector of bytes.
std::vector<uint8_t> mapIntToUint8V(const std::map<std::string, int>& map) {
    std::vector<uint8_t> bytes;
    for (const auto& pair : map) {
        std::string key = pair.first;
        int value = pair.second;
        bytes.push_back(static_cast<uint8_t>(key.size())); // Key length
        bytes.insert(bytes.end(), key.begin(), key.end()); // Key
        // Append 'int' value as four bytes
        for (int i = 3; i >= 0; --i) {
            bytes.push_back((value >> (i * 8)) & 0xFF);
        }
    }
    return bytes;
}

// Transforms a uint8_t vector of bytes into a map <string, int>.
std::map<std::string, int> uint8VToMapInt(const std::vector<uint8_t>& bytes) {
    std::map<std::string, int> map;
    size_t i = 0;
    while (i < bytes.size()) {
        uint8_t keyLen = bytes[i++];
        std::string key(bytes.begin() + i, bytes.begin() + i + keyLen);
        i += keyLen;
        // Read 'int' value from four bytes
        int value = 0;
        for (int j = 0; j < 4; ++j) {
            value |= (static_cast<int>(bytes[i + j]) << ((3 - j) * 8));
        }
        i += 4;
        map[key] = value;
    }
    return map;
}


}