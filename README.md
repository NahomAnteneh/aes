# AES File Encryptor

AES File Encryptor is a command-line tool for encrypting and decrypting files using the AES-128 encryption algorithm. This project demonstrates the implementation of AES encryption and decryption in C++.

## Project Structure
.gitignore build/ aes aes.o main.o Makefile src/ aes.cpp aes.hpp main.cpp

- `src/`: Contains the source code files.
  - `aes.cpp`: Implementation of the AES class.
  - `aes.hpp`: Header file for the AES class.
  - `main.cpp`: Main program file that provides the command-line interface.
- `build/`: Directory for build artifacts.
- `Makefile`: Build script for compiling the project.
- `.gitignore`: Specifies files and directories to be ignored by Git.

## Prerequisites

- C++17 compatible compiler (e.g., `g++`)
- Make

## Building the Project

To build the project, run the following command:

```sh
make
This will compile the source files and generate the aes executable in the build directory.

Usage
The aes executable provides a command-line interface for encrypting and decrypting files.

Command-Line Options
Usage: aes [options]
Options:
  -e, --encrypt        Encrypt mode
  -d, --decrypt        Decrypt mode
  -i, --input FILE     Input file
  -o, --output FILE    Output file
  -k, --key KEY        Hex key (32 characters for AES-128)

Example:
  aes -e -i input.txt -o encrypted.bin -k 000102030405060708090a0b0c0d0e0f
```