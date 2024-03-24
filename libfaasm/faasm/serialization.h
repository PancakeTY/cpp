#ifndef FAASM_SERIALIZATION_H
#define FAASM_SERIALIZATION_H
#include <cstdint>
#include <vector>
#include <map>
#include <string>
namespace faasm {
// Serialiazion and Deserialization from uint8_t vetors to uint32_t
uint32_t uint8VToUint32(const std::vector<uint8_t>& bytes);
std::vector<uint8_t> uint32ToUint8V(uint32_t value);
// Serialiazion and Deserialization from uint8_t vetors to Map<string,string>
std::vector<uint8_t> mapToUint8V(const std::map<std::string, std::string>& map);
std::map<std::string, std::string> uint8VToMap(const std::vector<uint8_t>& bytes);
// Serialiazion and Deserialization from uint8_t vetors to Map<string,int>
std::vector<uint8_t> mapIntToUint8V(const std::map<std::string, int>& map);
std::map<std::string, int> uint8VToMapInt(const std::vector<uint8_t>& bytes);
}
#endif