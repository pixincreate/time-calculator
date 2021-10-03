#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

int batteryStatus() {
	SYSTEM_POWER_STATUS status;
    GetSystemPowerStatus(&status);
		return status.ACLineStatus;
}

void sleep(int stat){
    clock_t startClock = clock();
    float secondsAhead = stat * CLOCKS_PER_SEC;
    while(clock() < startClock+secondsAhead);
		return;
}

bool powerStat() {
	if(batteryStatus() == 0) {
		return 1;
	}
	else if(batteryStatus() == 1) {
		return 0;
	}
}

int main(){
	cout << "before 1 min.." << endl;
	int cnt = 0;
	while(true) {
		if(powerStat() == 1) {
			sleep(60);
			cnt += 1;
		}
		else if(powerStat() == 0) break;
	}
	cout << "after " << cnt << " min.." << endl;
    return 0;
}
