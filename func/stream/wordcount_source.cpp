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

    // Create a list of words
    std::vector<std::string> messages = {
        "the cow jumped over the moon",
        "an apple a day keeps the doctor away",
        "four score and seven years ago",
        "snow white and the seven dwarfs",
        "i am at two with nature",
        "the quick brown fox jumps over the lazy dog",
        "the early bird catches the worm",
        "to be or not to be that is the question",
        "ask not what your country can do for you ask what you can do for your country",
        "i think therefore i am",
        "the only thing we have to fear is fear itself",
        "i have nothing to offer but blood toil tears and sweat",
        "i came i saw i conquered",
        "the pen is mightier than the sword",
        "when in the course of human events",
        "the bigger they are the harder they fall",
        "the best laid schemes of mice"
    };

    // Iterate over the input data and create a random sentence for each
    for (int i = 0; i < inputMap.size(); i++) {
        // Get a random number from 0 to size of messages
        int random_number = faasm::randomInteger(0, messages.size() - 1);
        // Return a random sentence
        std::string message = messages[random_number];

        // Prepare for chain call
        std::map<std::string, std::string> chainedInput;
        chainedInput["sentence"] = message;
        std::vector<uint8_t> chainedInputBytes;
        faasm::serializeMap(chainedInputBytes, chainedInput);
        // Chain call next function.
        faasmChainNamedId("wordcount_split",
                          chainedInputBytes.data(),
                          chainedInputBytes.size(),
                          i);
    }

    faasmChainInvoke();
    return 0;
}