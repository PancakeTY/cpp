#include "faasm/faasm.h"
#include "faasm/input.h"
#include "faasm/serialization.h"
#include <cinttypes> // For PRIu32
#include <sstream>
#include <string>
#include <vector>
int main(int argc, char* argv[])
{
    const char* word = faasm::getStringInput("");
    size_t size = faasmReadStateSize(word);
    uint32_t newSize = 1;
    if (size != 0) {
        std::vector<uint8_t> bytes(size);
        faasmReadState(word, bytes.data(), size);
        uint32_t oldSize = faasm::uint8VToUint32(bytes);
        newSize = oldSize + 1;
    }
    std::vector<uint8_t> newBytes = faasm::uint32ToUint8V(newSize);
    // Print the word and newSize
    printf("WordCount count: The size of [ %s ] are changed to [%" PRIu32 "] \n",
           word,
           newSize);
    faasmWriteState(word, newBytes.data(), newBytes.size());
    return 0;
}