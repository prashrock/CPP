//g++ -std=c++11 -Wall -g -o string_time_conversion string_time_conversion.cc
/**
 * Given a time in AM/PM format, convert it to military (24-hour) time.
 * Note: Midnight is 12:00:00AM on a 12-hour clock and 00:00:00 on a 24-hour
 * clock. Noon is 12:00:00PM on a 12-hour clock and 12:00:00 on a 24-hour
 * clock.
 * Input Format
 * A time in 12-hour clock format (i.e.: hh:mm:ssAM or hh:mm:ssPM), where
 * 01.hh.12.
 * Output Format
 * Convert and print the given time in 24-hour format, where 00.hh.23.
 * Example:
 * 07:05:45PM   ->  19:05:45
 */
#include <iostream>          /* std::cout        */
#include <iomanip>           /* std::setw        */
#include <cmath>             /* pow              */
#include <algorithm>         /* std::swap        */
#include <string>            /* std::string      */
using namespace std;

string time_convert(string time) {
	/* Extract the last two characters (am/pm)               */
	string ampm = time.substr(time.size() - 2, 2);
	/* Extract the hour (1st 2 characters in the string)     */
	int    hour = stoi(time.substr(0, time.find(':')));
	/* If time is PM and its not 12:00:00 PM, add 12         */
	if     (ampm.compare("PM") == 0 && hour != 12)
		time = std::to_string(hour + 12) + time.substr(time.find(':'));
	/* If time is AM and it is 12:XX:XX AM, replace with 00  */
	else if(ampm.compare("AM") == 0 && hour == 12)
		time = "00" + time.substr(time.find(':'));
	/* Remove the AM/PM as we have already converted string  */
	time = time.substr(0, time.size() - 2);
	//cout << time;
	return time;
}

int main()
{
	if     (time_convert("12:00:00PM").compare("12:00:00"))
		cout << "Error: Failed to convert 12:00:00PM" << endl;
	else if(time_convert("12:00:00AM").compare("00:00:00"))
		cout << "Error: Failed to convert 12:00:00AM" << endl;
	else if(time_convert("07:35:45PM").compare("19:35:45"))
		cout << "Error: Failed to convert 07:35:45PM" << endl;
	else if(time_convert("09:45:12AM").compare("09:45:12"))
		cout << "Error: Failed to convert 09:45:12AM" << endl;
	else
		cout << "Info: All manual test-cases passed" << endl;
	return 0;
}
