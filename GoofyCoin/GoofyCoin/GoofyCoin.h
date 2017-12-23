#pragma once
#include <string>
#include <iostream>
#include "CryptoFunctions.h"
#include <memory>

class Coin {
public:
	Coin(std::string data, std::unique_ptr<uint8_t[]> sig) : data(data), sig(std::move(sig)) {}
	std::string data;
	std::unique_ptr<std::uint8_t[]> sig;
private:
	Coin();
};

class Goofy {
public:
	Coin createCoin();
	Goofy();

private:
	int nextID();
	int currentID;
	KeyPair keyPair;
};

class Owner {
	void transferCoin(Coin c, Owner newOwner);
};

std::ostream & operator<<(std::ostream & s, const Coin & c);
