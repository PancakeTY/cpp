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
    uint8_t* readData = faasmReadFunctionStatePtrLock();
    size_t readSize = 0;
    if (readData != nullptr) {
        readSize = faasmReadFunctionStateSize();
    } else {
        printf("function state is still not initilized, initializing it\n");
    }
    std::map<std::string, std::vector<uint8_t>> functionState;
    functionState["k1"] = { 1, 2, 3, 4, 5 };
    functionState["k2"] = { 2, 3, 4, 5, 6, 7, 8 };

    std::vector<uint8_t> functionStateBytes =
      faasm::serializeFuncState(functionState);

    faasmWriteFunctionStateUnlock(functionStateBytes.data(),
                                  functionStateBytes.size());

    // Read it again and compare it.
    readData = faasmReadFunctionStatePtrLock();
    if (readData != nullptr) {
        readSize = faasmReadFunctionStateSize();
    } else {
        printf("error: function state is not written\n");
        faasmFunctionStateUnlock();
        return 1;
    }
    std::vector<uint8_t> buffer(readData, readData + readSize);
    functionState = faasm::deserializeFuncState(buffer);

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
