#include <windows.h>
#include <iostream>

using namespace std;

int batteryStatus() {
	SYSTEM_POWER_STATUS status;
    GetSystemPowerStatus(&status);
		return status.ACLineStatus;
}


int internetStatus() {
	if(system("ping www.google.com") == 1)  // no internet
		return 0;  // returns no internet
	return 1;  // internet exist!
}


int main() {
	cout << batteryStatus() << endl << internetStatus() << endl;
	return 0;
}
