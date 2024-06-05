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
    printf("function state example\n");
    // Locking the function state at first.
    size_t readSize = faasmReadFunctionStateSizeLock();
    std::map<std::string, std::vector<uint8_t>> functionState;
    if (readSize == 0) {
        printf("function state is still not initilized, initializing it\n");
        functionState["k1"] = { 1, 2, 3, 4, 5 };
        functionState["k2"] = { 2, 3, 4, 5, 6, 7, 8 };
    } else {
        printf("function state is already initialized\n");
        std::vector<uint8_t> stateBuffer(readSize);
        faasmReadFunctionState(stateBuffer.data(), readSize);
        functionState = faasm::deserializeFuncState(stateBuffer);
    }

    std::vector<uint8_t> functionStateBytes =
      faasm::serializeFuncState(functionState);
    printf("write function back\n");
    faasmWriteFunctionStateUnlock(functionStateBytes.data(),
                                  functionStateBytes.size());

    // Read it again and compare it.
    readSize = faasmReadFunctionStateSizeLock();
    functionState.clear();
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