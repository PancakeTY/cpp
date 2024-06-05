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
        "a picture is worth a thousand words but actions speak louder",
        "the grass is always greener on the other side of the fence",
        "honesty is the best policy especially when dealing with difficult "
        "situations",
        "time heals all wounds but some scars remain as reminders of the past",
        "practice makes perfect so never give up on your dreams and goals",
        "you cant judge a book by its cover looks can be deceiving",
        "every cloud has a silver lining always look for the positive side",
        "an ounce of prevention is worth a pound of cure in health",
        "its better to have loved and lost than never to have loved at all",
        "a journey of a thousand miles begins with a single step forward",
        "absence makes the heart grow fonder but distance can be challenging",
        "actions speak louder than words so show your intentions through your "
        "deeds",
        "birds of a feather flock together finding comfort in similarities",
        "when life gives you lemons make lemonade and stay optimistic",
        "the early bird catches the worm so wake up early for success",
        "knowledge is power so always strive to learn and grow everyday",
        "a friend in need is a friend indeed always be supportive",
        "better late than never but never late is always better",
        "dont count your chickens before they hatch plan your moves wisely",
        "good things come to those who wait patience is a virtue",
        "two heads are better than one teamwork always leads to success",
        "you reap what you sow so always do your very best",
        "a penny saved is a penny earned be frugal and wise",
        "dont put all your eggs in one basket diversify your efforts",
        "fortune favors the brave take risks to achieve great success",
        "great minds think alike but fools seldom differ be very discerning"
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