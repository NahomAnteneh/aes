#ifndef AES_HPP
#define AES_HPP

#include <array>
#include <vector>
#include <cstdint>

class AES
{
public:
    static constexpr size_t BLOCK_SIZE = 16; // 128 bits
    static constexpr size_t KEY_SIZE = 16;   // 128 bits
    static constexpr size_t NUM_ROUNDS = 10; // For AES-128

    explicit AES(const std::array<uint8_t, KEY_SIZE> &key);

    std::vector<uint8_t> encrypt(const std::vector<uint8_t> &plaintext);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t> &ciphertext);

private:
    using State = std::array<std::array<uint8_t, 4>, 4>;
    using RoundKey = std::array<uint8_t, BLOCK_SIZE>;
    std::array<RoundKey, NUM_ROUNDS + 1> roundKeys;

    // Key expansion
    void keyExpansion(const std::array<uint8_t, KEY_SIZE> &key);
    void generateRoundKey(size_t round);

    // Encryption steps
    void addRoundKey(State &state, const RoundKey &key);
    void subBytes(State &state);
    void shiftRows(State &state);
    void mixColumns(State &state);

    // Decryption steps
    void invSubBytes(State &state);
    void invShiftRows(State &state);
    void invMixColumns(State &state);

    // Helper functions
    static uint8_t gmul(uint8_t a, uint8_t b); // Galois Field multiplication
    static State createState(const std::vector<uint8_t> &input, size_t offset);
    static std::vector<uint8_t> stateToVector(const State &state);
};

#endif // AES_HPP