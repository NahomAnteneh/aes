#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include "aes.hpp"

void printUsage(const char *programName)
{
    std::cerr << "Usage: " << programName << " [options]\n"
              << "Options:\n"
              << "  -e, --encrypt        Encrypt mode\n"
              << "  -d, --decrypt        Decrypt mode\n"
              << "  -i, --input FILE     Input file\n"
              << "  -o, --output FILE    Output file\n"
              << "  -k, --key KEY        Hex key (32 characters for AES-128)\n"
              << "\nExample:\n"
              << "  " << programName << " -e -i input.txt -o encrypted.bin -k 000102030405060708090a0b0c0d0e0f\n";
}

std::vector<uint8_t> readFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Cannot open input file: " + filename);
    }

    return std::vector<uint8_t>(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>());
}

void writeFile(const std::string &filename, const std::vector<uint8_t> &data)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Cannot open output file: " + filename);
    }
    file.write(reinterpret_cast<const char *>(data.data()), data.size());
}

std::array<uint8_t, AES::KEY_SIZE> parseKey(const std::string &keyStr)
{
    if (keyStr.length() != AES::KEY_SIZE * 2)
    {
        throw std::runtime_error("Key must be exactly " +
                                 std::to_string(AES::KEY_SIZE * 2) +
                                 " hexadecimal characters");
    }

    std::array<uint8_t, AES::KEY_SIZE> key;
    for (size_t i = 0; i < AES::KEY_SIZE; i++)
    {
        std::string byteStr = keyStr.substr(i * 2, 2);
        key[i] = static_cast<uint8_t>(std::stoi(byteStr, nullptr, 16));
    }
    return key;
}

int main(int argc, char *argv[])
{
    bool encrypt = false;
    bool decrypt = false;
    std::string inputFile;
    std::string outputFile;
    std::string keyStr;

    // Parse command line arguments
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-e" || arg == "--encrypt")
        {
            encrypt = true;
        }
        else if (arg == "-d" || arg == "--decrypt")
        {
            decrypt = true;
        }
        else if ((arg == "-i" || arg == "--input") && i + 1 < argc)
        {
            inputFile = argv[++i];
        }
        else if ((arg == "-o" || arg == "--output") && i + 1 < argc)
        {
            outputFile = argv[++i];
        }
        else if ((arg == "-k" || arg == "--key") && i + 1 < argc)
        {
            keyStr = argv[++i];
        }
        else if (arg == "-h" || arg == "--help")
        {
            printUsage(argv[0]);
            return 0;
        }
    }

    // Validate arguments
    if (inputFile.empty() || outputFile.empty() || keyStr.empty())
    {
        std::cerr << "Error: Input file, output file, and key are required\n";
        printUsage(argv[0]);
        return 1;
    }

    if (encrypt == decrypt)
    {
        std::cerr << "Error: Must specify either encrypt (-e) or decrypt (-d)\n";
        printUsage(argv[0]);
        return 1;
    }

    try
    {
        // Parse the key and create AES instance
        auto key = parseKey(keyStr);
        AES aes(key);

        // Read input file
        auto input = readFile(inputFile);

        // Perform encryption or decryption
        std::vector<uint8_t> output;
        if (encrypt)
        {
            output = aes.encrypt(input);
        }
        else
        {
            output = aes.decrypt(input);
        }

        // Write output file
        writeFile(outputFile, output);

        std::cout << "Operation completed successfully.\n";
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
