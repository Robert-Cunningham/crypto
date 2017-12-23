#include "stdafx.h"
#include "ecc.h"
#include "ecc.c"
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <algorithm>
#include "picosha2.h"
#include "GoofyCoin.h"
#include "CryptoFunctions.h"

KeyPair::KeyPair() {
	this->publicKey = std::make_shared<std::uint8_t[]>(ECC_BYTES + 1);
	this->privateKey = std::make_shared<std::uint8_t[]>(ECC_BYTES);
	ecc_make_key(publicKey.get(), privateKey.get());
}

void sigDemo() {
	uint8_t* publicKey = new uint8_t[ECC_BYTES+1];
	uint8_t* privateKey = new uint8_t[ECC_BYTES];

	int ret = ecc_make_key(publicKey, privateKey);

	printKeys(publicKey, privateKey);
	std::cout << std::endl;

	uint8_t* signature = new uint8_t[ECC_BYTES * 2];

	std::string message = "secret";

	ecdsa_sign(privateKey, getHash(message), signature);
	std::cout << "Signed message: " << uintArrayToString(signature, ECC_BYTES * 2);

	std::cout << "Verified? " << ecdsa_verify(publicKey, getHash(message), signature);
	
	std::cout << "Hash: " << uintArrayToString(getHash("hash"), 32) << std::endl;
}

void printKeys(uint8_t* publicKey, uint8_t* privateKey) {
	std::cout << "Public Key: " << uintArrayToString(publicKey, ECC_BYTES + 1) << ". \nPrivate Key: " << uintArrayToString(privateKey, ECC_BYTES) << ". ";
}

std::string uintArrayToString(uint8_t* input, int length) {
	std::stringstream out;
	for (int i = 0; i < length; i++) {
		out << " " + uint8ToString(input[i]);
	}
	return out.str();
}

std::string uint8ToString(uint8_t in) {
	std::unique_ptr<std::stringstream> out = std::make_unique<std::stringstream>();
	(*out) << std::hex << static_cast<int>(in);
	std::string upper = out->str();

	for (int i = 0; i < (out->str()).length(); i++) {
		upper[i] = toupper(out->str()[i]);
	}

	return upper;
}

uint8_t* getHash(std::string in) {
	uint8_t* out = new uint8_t[32];
	picosha2::hash256(in.begin(), in.end(), out, out + 32);
	return out;
} 
