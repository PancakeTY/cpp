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
    // get the inputMap (inputdata)
    std::vector<uint8_t> vec = faasm::getInputVec();

    size_t index = 0; // Reset index if reusing buffer
    std::map<std::string, std::map<std::string, std::string>> inputMap =
      faasm::deserializeNestedMap(vec, index);

    // get the functionstate
    size_t readSize = faasmReadFunctionStateSizeLock();
    std::map<std::string, std::vector<uint8_t>> functionState;
    if (readSize == 0) {
        functionState["partitionStateKey"] = {};
    } else {
        std::vector<uint8_t> stateBuffer(readSize);
        faasmReadFunctionState(stateBuffer.data(), readSize);
        functionState = faasm::deserializeFuncState(stateBuffer);
    }

    // get the partitionstate from functionstate
    std::map<std::string, std::vector<uint8_t>> parFunctionState;
    if (functionState["partitionStateKey"].size() != 0) {
        parFunctionState =
          faasm::deserializeParState(functionState["partitionStateKey"]);
    }

    /*
    Begin the loop
    */

    for (size_t i = 0; i < inputMap.size(); i++) {
        // get the input for this spefic function invoke.
        std::string inputParStr = inputMap[std::to_string(i)]["partitionInputKey"];
    
        // increament the count
        int count = 0;
        if (parFunctionState.find(inputParStr) != parFunctionState.end()) {
            count = faasm::uint8VToUint32(parFunctionState[inputParStr]);
        }
        count++;
        parFunctionState[inputParStr] = faasm::uint32ToUint8V(count);
    }
    
    // Print the parFunctionState
    std::cout << "Printing the partitioned function state" << std::endl;
    for (auto const& x : parFunctionState) {
        std::cout << x.first << " : " << faasm::uint8VToUint32(x.second) << std::endl;
    }

    /*
    After the loop
    */
    functionState["partitionStateKey"] =
      faasm::serializeParState(parFunctionState);
    // write data back
    std::vector<uint8_t> functionStateBytes =
      faasm::serializeFuncState(functionState);
    faasmWriteFunctionStateUnlock(functionStateBytes.data(),
                                  functionStateBytes.size());

    return 0;
}
