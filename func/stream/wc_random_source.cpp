#include "faasm/core.h"
#include "faasm/faasm.h"
#include "faasm/random.h"
#include <random>
#include <string>
#include <vector>
int main(int argc, char* argv[])
{
    std::vector<std::string> messages = {
        "the cow jumped over the moon",
        "an apple a day keeps the doctor away",
        "four score and seven years ago",
        "snow white and the seven dwarfs",
        "i am at two with nature"
    };
    // Get a random number from 0 to size of messages
    int random_number = faasm::randomInteger(0, messages.size() - 1);
    // Return a random sentence
    std::string message = messages[random_number];
    printf("WordCount source: Created Random sentence: %s\n",
           message.c_str());
    // Call the split function
    faasmChainNamed("wc_split",
                    reinterpret_cast<const uint8_t*>(message.c_str()),
                    message.size());
    return 0;
}