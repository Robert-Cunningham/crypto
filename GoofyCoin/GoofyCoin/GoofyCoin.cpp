#include "stdafx.h"
#include "GoofyCoin.h"
#include "CryptoFunctions.h"
#include "picosha2.h"
#include "ecc.h"
#include <memory>

Coin Goofy :: createCoin() {
	std::string data = "Create Coin " + std::to_string(this->nextID());
	auto sig = std::make_unique<std::uint8_t[]>(ECC_BYTES * 2);
	ecdsa_sign(this->keyPair.publicKey.get(), getHash(data), sig.get());
	Coin c (data, std::move(sig));
	return c;
}

std::ostream& operator<<(std::ostream& s, const Coin& c) {
	return s << c.data << " [" << uintArrayToString(c.sig.get(), ECC_BYTES*2) << "]";
}

Goofy::Goofy() {
	this->currentID = 0;
	ecc_make_key(this->keyPair.privateKey.get(), this->keyPair.publicKey.get());
}

int Goofy::nextID() {
	this->currentID++;
	return this->currentID- 1;
}