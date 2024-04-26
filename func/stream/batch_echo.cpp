#include "faasm/faasm.h"
#include "faasm/input.h"
#include "faasm/serialization.h"

#include <map>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

/**
 * Writes the input to the output
 */
int main(int argc, char* argv[])
{
    std::vector<uint8_t> vec = faasm::getInputVec();
    size_t inputLen = vec.size();

    // Handle empty input
    if (inputLen == 0) {
        const char* output = "Nothing to echo";
        faasmSetOutput(output, strlen(output));
        return 0;
    }

    std::map<std::string, std::string> inputMap =
      faasm::deserializeMapBinary(vec);
    // printf the inputMap
    for (const auto& pair : inputMap) {
        printf("Key: %s Value: %s\n", pair.first.c_str(), pair.second.c_str());
    }

    // faasmSetOutput(inputStr, inputLen);

    return 0;
}
