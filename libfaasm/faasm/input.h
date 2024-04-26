#ifndef FAASM_INPUT_H
#define FAASM_INPUT_H

#include "faasm/core.h"
#include <vector>

namespace faasm {
const char* getStringInput(const char* defaultValue);

const std::vector<uint8_t> getInputVec();

void setStringOutput(const char* val);

int getIntInput();

int* parseStringToIntArray(const char* inStr, int expected);
}

#endif
