#ifndef FAASM_SERIALIZATION_H
#define FAASM_SERIALIZATION_H
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <cstddef> 

// THERE MUST BE SAME TO THE FAABRIC SERIALIZATION !
namespace faasm {

std::size_t hashVector(const std::vector<uint8_t>& vec);

// Serialiazion and Deserialization from uint8_t vetors to uint32_t
uint32_t uint8VToUint32(const std::vector<uint8_t>& bytes);
std::vector<uint8_t> uint32ToUint8V(uint32_t value);

// Serialiazion and Deserialization from uint8_t vetors to Map<string,string>
std::vector<uint8_t> serializeMapBinary(const std::map<std::string, std::string>& map);
std::map<std::string, std::string> deserializeMapBinary(
  const std::vector<uint8_t>& buffer);

// Serialiazion and Deserialization from uint8_t vetors to Map<string,int>
std::vector<uint8_t> mapIntToUint8V(const std::map<std::string, int>& map);
std::map<std::string, int> uint8VToMapInt(const std::vector<uint8_t>& bytes);

// Serialiazion and Deserialization from function State to uint8_t vetors
std::vector<uint8_t> serializeFuncState(
  const std::map<std::string, std::vector<uint8_t>>& map);
std::map<std::string, std::vector<uint8_t>> deserializeFuncState(
  const std::vector<uint8_t>& bytes);

// Serialiazion and Deserialization of Paritioned State Input (same as FuncState)
std::vector<uint8_t> serializeParState(
  const std::map<std::string, std::vector<uint8_t>>& map);
std::map<std::string, std::vector<uint8_t>> deserializeParState(
  const std::vector<uint8_t>& bytes);
}

#endif