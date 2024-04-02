#include <faasm/faasm.h>
#include <faasm/serialization.h>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    // Read a function state
    size_t size = faasmReadFunctionStateSize();
    // printf the size
    printf("Size of Function State: %ld\n", size);

    // It means it is invoked in first time
    // Write a function State
    std::vector<uint8_t> k1 = { 1, 2, 3, 4, 5 };
    std::vector<uint8_t> k2 = { 2, 3, 4, 5, 6, 7, 8 };
    std::vector<uint8_t> k3 = { 3, 4, 5, 6, 7, 8 };

    std::map<std::string, std::vector<uint8_t>> functionState =
      std::map<std::string, std::vector<uint8_t>>();
    functionState["k1"] = k1;
    functionState["k2"] = k2;
    functionState["k3"] = k3;

    std::vector<uint8_t> functionStateBytes =
      faasm::serializeFuncState(functionState);
    faasmWriteFunctionState(functionStateBytes.data(),
                            functionStateBytes.size());

    size = faasmReadFunctionStateSize();
    // Read a function state
    std::vector<uint8_t> buffer(size);
    faasmReadFunctionState(buffer.data(), size);
    functionState = faasm::deserializeFuncState(buffer);

    // Print the function state
    for (auto const& x : functionState) {
        std::cout << x.first << " : ";
        for (auto const& y : x.second) {
            std::cout << +y << " ";
        }
        std::cout << std::endl;
    }
    std::vector<uint8_t> k4;
    k4.reserve(10000);
    for (uint16_t i = 1; i <= 10000; ++i) {
        k4.push_back(1);
    }
    functionState["k4"] = k4;
    functionStateBytes = faasm::serializeFuncState(functionState);
    faasmWriteFunctionState(functionStateBytes.data(),
                            functionStateBytes.size());
    size = faasmReadFunctionStateSize();
    // Read a function state
    std::vector<uint8_t> buffer1(size);
    faasmReadFunctionState(buffer1.data(), size);
    functionState = faasm::deserializeFuncState(buffer1);

    // Print the function state
    for (auto const& x : functionState) {
        std::cout << x.first << " : ";
        for (auto const& y : x.second) {
            std::cout << +y << " ";
        }
        std::cout << std::endl;
    }

    // // size_t size = faasmReadFunctionStateSize();
    // // Cleanup
    // delete functionState;

    return 0;
}
