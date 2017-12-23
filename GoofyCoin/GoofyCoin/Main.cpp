#include "stdafx.h"
#include "GoofyCoin.h"
#include <string>
#include <iostream>
#include "CryptoFunctions.h"
#include "ecc.h"

int main() {
	Goofy g;
	auto c = g.createCoin();
	std::cout << c << std::endl;
	
	auto d = g.createCoin();
	std::cout << d << std::endl;

	User alice;
	auto transaction = g.transferCoin(c, alice);
	std::cout << uintArrayToString(transaction.get(), ECC_BYTES * 2);
	//sigDemo();

	int x;
	std::cin >> x;
    return 0;
}
