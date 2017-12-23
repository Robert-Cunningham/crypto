#include "stdafx.h"
#include "GoofyCoin.h"
#include <string>
#include <iostream>
#include "CryptoFunctions.h"

int main() {
	Goofy g;
	auto c = g.createCoin();
	std::cout << c << std::endl;
	
	auto d = g.createCoin();
	std::cout << d << std::endl;
	//sigDemo();

	int x;
	std::cin >> x;
    return 0;
}
