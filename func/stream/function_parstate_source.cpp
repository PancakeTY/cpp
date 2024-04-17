#include "faasm/core.h"
#include "faasm/faasm.h"
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
    // Create a list of words
    std::vector<std::string> messages = { "cat", "dog", "pig" };
    // Get a random number from 0 to size of messages
    int random_number = faasm::randomInteger(0, messages.size() - 1);
    // Return a random sentence
    std::string message = messages[random_number];
    printf("WordCount source: Created Random sentence: %s\n", message.c_str());

    std::map<std::string, std::vector<uint8_t>> input;
    input["partitionInputKey"] =
      std::vector<uint8_t>(message.begin(), message.end());
    std::vector<uint8_t> inputBytes = faasm::serializeParState(input);
    printf("output inputyByes: %s\n", inputBytes.data());
    faasmChainNamed("function_parstate", inputBytes.data(), inputBytes.size());
    return 0;
}