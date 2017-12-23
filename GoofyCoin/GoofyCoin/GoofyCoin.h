#pragma once
#include <string>
#include <iostream>
#include "CryptoFunctions.h"
#include <memory>

class Coin {
public:
	Coin(std::string data, std::shared_ptr<uint8_t[]> sig, int id) : data(data), sig(std::move(sig)), id(id) {}
	std::string data;
	std::shared_ptr<std::uint8_t[]> sig;
	int id;
private:
	Coin();
};

class User {
public:
	std::shared_ptr<uint8_t[]> transferCoin(Coin c, User newOwner);
	std::shared_ptr<uint8_t[]> getPublicKey();
protected:
	KeyPair keyPair;
};

class Goofy : public User {
public:
	Coin createCoin();
	Goofy();

private:
	int nextID();
	int currentID;
};

std::ostream & operator<<(std::ostream & s, const Coin & c);
