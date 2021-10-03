#include <iostream>
#include <wininet.h>

// do the same in sockets

int main() {

	if(system("ping > nul www.google.com") == 1) {
		std::cout << "no internet";
		return 0;
	}
	std::cout << "yes internet";
	return 0;
}
