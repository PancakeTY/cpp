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
    printf("chained_d- inputMap size: %ld\n", inputMap.size());
    // Create a list of words

    for (int i = 0; i < inputMap.size(); i++) {
        // Get a random number from 0 to size of messages
        std::string message = inputMap[std::to_string(i)]["key1"];
        printf("chained_d- the input is: %s\n", message.c_str());
    }
    return 0;
}