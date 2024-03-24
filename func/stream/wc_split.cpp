#include "faasm/core.h"
#include "faasm/faasm.h"
#include "faasm/input.h"
#include <random>
#include <string>
#include <vector>
int main(int argc, char* argv[])
{
    const char* inputCStr = faasm::getStringInput("");
    std::string inputSentence(inputCStr); // Convert to std::string

    // Split the inputSentence by space and store in a vector
    std::string word;
    if (inputSentence.empty()) {
        printf("WordCount Split: No input sentence\n");
        return 0;
    }
    for (char x : inputSentence) {
        if (x == ' ') {
            if (!word.empty()) {
                faasmChainNamed("wc_count",
                                reinterpret_cast<const uint8_t*>(word.c_str()),
                                word.size());
                word.clear();
            }
        } else {
            word = word + x;
        }
    }
    if (!word.empty()) {
        faasmChainNamed("wc_count",
                        reinterpret_cast<const uint8_t*>(word.c_str()),
                        word.size());
    }
    return 0;
}