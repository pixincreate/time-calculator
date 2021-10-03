/*
The idea is to automate the time line update process and throw the added interval of timelines.
Everytime the program is run, it checks whether the laptop is charging or not.
If not, it checks whether it is connected to the internet.
Again, if not, it considers as No-Power.
Immediately, it fetches the present in hh1:mm1 format and stores in a string and goes to sleep.
When the presence of Internet / charger is detected, it updates the existing string and calculates the interval.

to-do: Put a shortcut in the autostart folder to make the code run at start up
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <windows.h>

using namespace std;

int databaseUpdate = 0, totalSeconds = 0, dashes = 0;
string yesterday;

int concat(int a, int b) {
	string s1 = to_string(a - 48);
	string s2 = to_string(b - 48);
	return stoi(s1 + s2);
}

void sleepBrother(int stat){
    clock_t startClock = clock();
    float secondsAhead = stat * CLOCKS_PER_SEC;
    while(clock() < startClock + secondsAhead);
		return;
}

int batteryStatus() {
	SYSTEM_POWER_STATUS status;
    GetSystemPowerStatus(&status);
		return status.ACLineStatus;
}

int internetStatus() {
	if(system("ping > nul www.google.com") == 1)  // system() right here is evil and threat to pc security!
		return 0;
	return 1;
}

string presentTime() {
	string Time, month, today, timing, year;

	time_t currentTime = time(0);
	char *date = ctime(& currentTime);

	for(int i = 11; i <= 15; i++)
		Time += date[i];

	month = string() + date[4] + date[5] + date[6];
	today = string() + date[8] + date[9];
	year = string() + date[20] + date[21] + date[22] + date[23];

	timing = today + '-' + month + '-' + year + ' ' + Time + " -- ";

	if(today > yesterday)
		dashes = 1;

	return timing;
}

string timelineUpdate(string timeline, int power_cut_status) {
	int hh1, hh2, mm1, mm2, minutes, hours;

	if (power_cut_status == 1) {
		hh1 = concat(timeline[12], timeline[13]);
		mm1 = concat(timeline[15], timeline[16]);

		ofstream outfile;
		outfile.open("E:\Coding\Cpp\time-calculator\Database\powercut.txt");
		outfile << timeline;
		outfile.close();
		yesterday = string() + timeline[0] + timeline[1];
	}
	else if (power_cut_status == 0) {
		hh2 = concat(timeline[21], timeline[22]);
		mm2 = concat(timeline[24], timeline[25]);

		ofstream outfile;
		outfile.open("E:\Coding\Cpp\time-calculator\Database\powercut.txt");
		outfile << hh2 << ":" << mm2 << "\n";
		if(dashes == 1)
			outfile << "---------------------------------------------------\n";
		outfile.close();
	}
	int totalSecondsBefore = hh1 * 3600 + mm1 * 60;
	int totalSecondsAfter = hh2 * 3600 + mm2 * 60;
	totalSeconds += (totalSecondsAfter - totalSecondsBefore);

	minutes = (totalSeconds / 60) % 60;
	hours = minutes / 60;

	if(power_cut_status == 0) {
		cout << "\nTotal time		: " << setw(2) << setfill('0') << hours << "h:" << setw(2) << setfill('0') << int(minutes%60) << "m\n";
		cout << "Total time(in seconds)	: " << totalSeconds << "\n";
	}

	if(totalSeconds > 1) {
		hh1 = hh2 = mm1 = mm2 = 0;
	}
}

bool powerStat() {
	if(batteryStatus() == 0) {
		if(internetStatus() == 0) {
			if(databaseUpdate == 0) {
				timelineUpdate(presentTime(), 1);  // 1 here indicates the power is cut
				databaseUpdate = 1;
				return 1;
			}
		}
	}
	else if(batteryStatus() == 1) {
			if(internetStatus() == 1) {
				if(databaseUpdate == 1) {
					timelineUpdate(presentTime(), 0);  // 0 here indicates the power is exist
					databaseUpdate = 0;  // Reset the update counter
					return 0;
				}
			}
	}
}

int main() {
	while(true) {
		if(powerStat() == 1)
			sleepBrother(90);  // Sova says that!
		else if(powerStat() == 0) {
			sleepBrother(90);
		}
	}
return 0;
}
