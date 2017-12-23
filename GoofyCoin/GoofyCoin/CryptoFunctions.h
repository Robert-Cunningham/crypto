#pragma once
#include <string>
#include <memory>

void printKeys(uint8_t* publicKey, uint8_t* privateKey);
std::string uint8ToString(uint8_t in);
std::string uintArrayToString(uint8_t* input, int length);
uint8_t* getHash(std::string in);
void sigDemo();

class KeyPair {
public:
	std::unique_ptr<uint8_t[]> publicKey;
	std::unique_ptr<uint8_t[]> privateKey;
	KeyPair();
};