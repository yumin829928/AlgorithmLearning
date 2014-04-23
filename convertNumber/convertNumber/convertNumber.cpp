// convertNumber.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

string convertToExcel(int num) {
    string result;
    bool positive = true;
	if (num < 0) {
		positive = false;
		num = -num;
	}
	
	int cur_digit;
	char cur_char;
    while (num) {
		bool minus_one = false;
		cur_digit = num % 26;
		if (cur_digit == 0) {
			minus_one = true;
			cur_digit = 26;
		}
		cur_char = 'A' + cur_digit - 1;
		result = cur_char + result;
		num = num / 26;
		if (num > 0 && minus_one) {
			--num;
		}
	}
	
	if (!positive) {
		result = '-' + result;
	}
	
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "-52 convert to " << convertToExcel(-52) << endl;
	cout << "702 convert to " << convertToExcel(702) << endl;
	cout << "703 convert to " << convertToExcel(703) << endl;
	cout << "53 convert to " << convertToExcel(53) << endl;
	cout << "77 convert to " << convertToExcel(77) << endl;

	return 0;
}

