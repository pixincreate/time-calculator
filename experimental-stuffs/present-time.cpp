#include <bits/stdc++.h>
#include <string>
#include <typeinfo>

using namespace std;

//  Sat Oct 02 21:58:41 2021
//  date-month-year hh:mm

int concat(int a, int b) {
	string s1 = to_string(a - 48);
	string s2 = to_string(b - 48);
	return stoi(s1 + s2);
}

int main() {
	string presentTime, month, today, day, year;

	time_t now = time(0);
	char *date = ctime(& now);

	cout << date << endl;

	for(int i = 11; i <= 15; i++)
	presentTime += date[i];

	int hh = concat(presentTime[0], presentTime[1]);
	int mm = concat(presentTime[3], presentTime[4]);

	month = string() + date[4] + date[5] + date[6];
	today = string() + date[8] + date[9];
	year = string() + date[20] + date[21] + date[22] + date[23];

	day = today + '-' + month + '-' + year + ' ' + presentTime;

	cout << day;
return 0;
}
