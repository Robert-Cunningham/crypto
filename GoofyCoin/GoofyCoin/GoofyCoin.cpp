#include "stdafx.h"
#include "GoofyCoin.h"
#include "CryptoFunctions.h"
#include "picosha2.h"
#include "ecc.h"
#include <memory>

Coin Goofy :: createCoin() {
	int id = this->nextID();
	std::string data = "Create Coin " + std::to_string(id);
	auto sig = std::make_unique<std::uint8_t[]>(ECC_BYTES * 2);
	ecdsa_sign(this->keyPair.publicKey.get(), getHash(data), sig.get());
	Coin c (data, std::move(sig), id);
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

std::shared_ptr<uint8_t[]> User::transferCoin(Coin c, User newOwner) {
	std::string statement = "Pay " + std::to_string(c.id) + " from " + uintArrayToString(this->keyPair.publicKey.get(), ECC_BYTES + 1) + " to " + uintArrayToString(newOwner.getPublicKey().get(), ECC_BYTES + 1);
	auto out = std::make_shared<uint8_t[]>(ECC_BYTES * 2);
	ecdsa_sign(this->keyPair.privateKey.get(), getHash(statement), out.get());
	return out;
}

std::shared_ptr<uint8_t[]> User::getPublicKey() {
	return this->keyPair.publicKey;
}
