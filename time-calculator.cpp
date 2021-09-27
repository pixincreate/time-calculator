#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int concat(int a, int b) {  //			Concatination of digits(that are in char type) takes place here.
	string s1 = to_string(a - 48);  //	Converts to ASCII value, and hence negated by 48 to get actual decimal value.
	string s2 = to_string(b - 48);
	return stoi(s1 + s2);  //			Returns Integer sum of s1 and s2.
}

int main() {
	cout << "This program initially takes a limit and a set of timelines in the only format that is given below.";
	cout << "If valid inputs are given, then you'll receive total time in both hh:mm and seconds as an output.\n";
	cout << "This tiny simple little code is written by PiX.\n\n";
	cout << "Timeline format: hh1:mm1-hh2:mm2\n\n";

	int hours = 0, minutes = 0, limit = 0, totalSeconds = 0, totalTime = 0;

	cout << "Type the total number of entries: ";
	cin >> limit;	//					Takes a limit, i.e., max number of entries.
	cout << "\n";

	string timeline;
	for(int i = 0; i < limit; i++) {
		cout << "Enter timeline for entry " << i+1 << ": ";
		cin >> timeline;  //			Takes user input in Timeline format until Limit is satisfied.

		if(timeline[2] != ':' || timeline[5] != '-' || timeline[8] != ':') {  //			If Timeline format is incorrect, returns 0.
			cout << "\nTimeline format incorrect!\n";
			return 0;
		}
		int hh1 = concat(timeline[0], timeline[1]);  //                                     Function call to convert 2 individual chars to 1 Int.
		int mm1 = concat(timeline[3], timeline[4]);
		int hh2 = concat(timeline[6], timeline[7]);
		int mm2 = concat(timeline[9], timeline[10]);

		int totalSecondsBefore = hh1 * 3600 + mm1 * 60;  //									Total Seconds for hh1 and hh2 are Calculated
		int totalSecondsAfter = hh2 * 3600 + mm2 * 60;
		totalSeconds += (totalSecondsAfter - totalSecondsBefore);  //						Difference of Total Seconds is calculated and appended.
	}

	minutes = totalSeconds / 60;  //														hours and minutes are calculated.
	hours = minutes / 60;

	cout << "\nTotal time		: " << setw(2) << setfill('0') << hours << "h:" << setw(2) << setfill('0') << int(minutes%60) << "m\n";
	cout << "Total time(in seconds)	: " << totalSeconds << "\n";  //						Final Output

return 0;
}
