#include "faasm/core.h"
#include "faasm/faasm.h"
#include "faasm/input.h"
#include "faasm/random.h"
#include <faasm/serialization.h>
#include <iostream>
#include <map>
#include <random>
#include <stdio.h>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    // get the inputMap (inputdata)
    std::vector<uint8_t> vec = faasm::getInputVec();
    size_t index = 0;
    std::map<std::string, std::map<std::string, std::string>> inputMap =
      faasm::deserializeNestedMap(vec, index);
    // printf the inputMap size
    printf("chained_b- inputMap size: %ld\n", inputMap.size());

    for (int i = 0; i < inputMap.size(); i++) {
        // Return a random sentence
        std::string message = inputMap[std::to_string(i)]["key1"];
        printf("chained_b- the input is: %s\n", message.c_str());

        std::map<std::string, std::string> input;
        input["key1"] = message;
        input["key2"] = "key2value";
        std::vector<uint8_t> inputBytes;
        faasm::serializeMap(inputBytes, input);

        faasmChainNamedId("chained_c", inputBytes.data(), inputBytes.size(), i);
        faasmChainNamedId("chained_d", inputBytes.data(), inputBytes.size(), i);
    }
    return 0;
}