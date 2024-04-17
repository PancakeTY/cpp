#include "faasm/input.h"
#include <faasm/faasm.h>
#include <faasm/serialization.h>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

// We must register the function_state in scheduler!

int main(int argc, char* argv[])
{
    printf("function partition state example\n");

    const char* inputStr = faasm::getStringInput("noinput");
    // print the input data
    printf("function inputStr: %s\n", inputStr);

    size_t readSize = faasmReadFunctionStateSizeLock();
    std::map<std::string, std::vector<uint8_t>> functionState;
    printf("parstate readSize: %ld\n", readSize);
    if (readSize == 0) {
        printf("function state is still not initilized, initializing it\n");
        functionState["k1"] = { 1, 2, 3, 4, 5 };
        functionState["k2"] = { 2, 3, 4, 5, 6, 7, 8 };
        functionState["partitionStateKey"] = {};
    } else {
        printf("function state is already initialized\n");
        std::vector<uint8_t> stateBuffer(readSize);
        faasmReadFunctionState(stateBuffer.data(), readSize);
        functionState = faasm::deserializeFuncState(stateBuffer);
    }
    printf("read data finished");
    std::map<std::string, std::vector<uint8_t>> parFunctionState;
    if (functionState["partitionStateKey"].size() != 0) {
        parFunctionState =
          faasm::deserializeParState(functionState["partitionStateKey"]);
    }

    int count = 0;
    if (parFunctionState.find(inputStr) != parFunctionState.end()) {
        count = faasm::uint8VToUint32(parFunctionState[inputStr]);
    }
    count++;
    parFunctionState[inputStr] = faasm::uint32ToUint8V(count);
    functionState["partitionStateKey"] =
      faasm::serializeParState(parFunctionState);

    std::vector<uint8_t> functionStateBytes =
      faasm::serializeFuncState(functionState);
    printf("write back");
    faasmWriteFunctionStateUnlock(functionStateBytes.data(),
                                  functionStateBytes.size());

    printf("read again, and print the new data.");
    // Read it again and compare it.
    readSize = faasmReadFunctionStateSizeLock();
    functionState.clear();
    printf("parstate readSize: %ld\n", readSize);
    if (readSize == 0) {
        printf("error: function state is not written\n");
        faasmFunctionStateUnlock();
        return 1;
    } else {
        printf("function state is already initialized\n");
        std::vector<uint8_t> stateBuffer(readSize);
        faasmReadFunctionState(stateBuffer.data(), readSize);
        functionState = faasm::deserializeFuncState(stateBuffer);
    }

    // Print the function state
    for (auto const& x : functionState) {
        std::cout << x.first << " : ";
        for (auto const& y : x.second) {
            std::cout << +y << " ";
        }
        std::cout << std::endl;
    }
    faasmFunctionStateUnlock();
    return 0;
}
