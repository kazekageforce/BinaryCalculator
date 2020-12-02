#include "Binary.h"
#include <iostream>  
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <string>
using namespace std;
Binary::Binary() {}
Binary:: ~Binary() {}
void Binary::SetBinary(vector<int> bin) { binary = bin; }
vector<int> Binary::GetBinary() { return binary; }
void Binary::checkprint(vector<int> const& input) {
	for (int i = 0; i < input.size(); i++) {
		cout << input[i];
	}
	cout << endl;
};
vector<int> Binary::makeBinary(int var, int depth) {
	vector<int> arr;
	int c = 0;
	while (var != 0) {
		c = var % 2;
		var /= 2;
		arr.push_back(c);
	}
	if (arr.size() < depth)
	{
		while (arr.size() != depth) {
			arr.push_back(0);
		}
	}
	reverse(arr.begin(), arr.end());
	return arr;
};
vector<int> Binary::addBin(vector<int> a, vector<int> b) {
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int maxSize = a.size() > b.size() ? a.size() : b.size();  // number of bits is maximum of siza and sizeb
	vector<int> result;
	int carry = 0;
	for (int i = 0; i < maxSize; i++)
	{
		int bitA = i < a.size() && a[i] ? 1 : 0;     // test if bit in array a is set
		int bitB = i < b.size() && b[i] ? 1 : 0;     // test if bit in array b is set
		int sum = bitA + bitB + carry;            // calculate sum of all bits
		if (sum == 1 || sum == 3)
		{
			result.push_back(1);
		}
		else
		{
			result.push_back(0); // result bit is set if sum is equal 1 or 3
		}
		carry = sum > 1 ? 1 : 0;                  // carry bit is set if sum is eqaul 2 or 3
	}
	result.push_back(carry);// highest bit of result is carry bit
	reverse(result.begin(), result.end());
	return result;
};
vector<int> Binary::multiBin(vector<int> a, vector<int> b) {
	Binary* tmp = new Binary();
	vector<int> result;
	int n = tmp->decimal(b);
	for (int i = 0; i < n; i++) {
		result = tmp->addBin(result, a);
	}
	int sz = a.size() > b.size() ? a.size() : b.size();
	reverse(result.begin(), result.end());
	while (result.size() != sz)
	{
		result.pop_back();
	}
	reverse(result.begin(), result.end());
	return result;
};
vector<int> Binary::makeReverse(vector<int> arr) {
	vector<int> arr2(arr.cbegin(), arr.cend());
	replace(arr2.begin(), arr2.end(), 1, 3);
	replace(arr2.begin(), arr2.end(), 0, 1);
	replace(arr2.begin(), arr2.end(), 3, 0);
	return arr2;
};
vector<int> Binary::negative(int var, int depth) {
	vector<int> result, result1, result2, one;
	one = { 1 };
	Binary* tmp = new Binary();
	result = tmp->makeBinary(var, depth);
	reverse(result.begin(), result.end());
	if (pow(2, 2) < result.size() < pow(2, 3)) {
		while (result.size() != pow(2, 3)) {

			result.push_back(0);

		}
	}
	else {
		while (result.size() != pow(2, 3))
		{
			result.pop_back();
		}
	}
	reverse(result.begin(), result.end());
	result1 = tmp->makeReverse(result);
	result2 = tmp->addBin(result1, one);
	reverse(result2.begin(), result2.end());
	result2.pop_back();
	reverse(result2.begin(), result2.end());
	return result2;
}
vector<int> Binary::subBin(vector<int> a, vector<int> b) {
	Binary* newBin = new Binary();
	int dec1 = a.size();
	int dec2 = b.size();
	if (dec1 != dec2) {
		dec2 = dec1;
	}
	int d = newBin->decimal(b);
	vector<int> bin = newBin->negative(d, dec2);
	vector<int> sub = newBin->addBin(a, bin);
	reverse(sub.begin(), sub.end());
	sub.pop_back();
	reverse(sub.begin(), sub.end());
	return sub;
}
vector<int> Binary::divBin(vector<int> a, vector<int> b) {
	Binary* tmp = new Binary();
	vector<int> c;
	int a1 = tmp->decimal(a);
	int b1 = tmp->decimal(b);
	int c1 = a1 / b1;
	int c2 = c1 * b1;
	a = tmp->makeBinary(c2, a.size());
	int sz = a.size() >= b.size() ? a.size() : b.size();
	int k = 0;
	int i = 0;
	for (int i = 0; i < sz; i++) {
		while (a[i] == 1) {
			a = tmp->subBin(a, b);
			k++;
		}
	}
	vector<int> result2 = tmp->makeBinary(k, sz);
	return result2;
}
int Binary::decimal(vector<int> bin) {
	reverse(bin.begin(), bin.end());
	stringstream ss;
	copy(bin.begin(), bin.end(), ostream_iterator<int>(ss));
	string s = ss.str();
	int len = s.length();
	int n = len - 1;
	for (int i = 0; i < (len / 2); i++) {
		//Using the swap method to switch values at each index
		swap(s[i], s[n]);
		n = n - 1;
	}
	int value = 0;
	int indexCounter = 0;
	for (int i = s.length() - 1; i >= 0; i--) {

		if (s[i] == '1') {
			value += pow(2, indexCounter);
		}
		indexCounter++;
	}
	return value;
};
int Binary::negativedecimal(vector<int> bin) {
	Binary* newBin = new Binary();
	vector<int> one = { 1 };
	vector<int> tmp1 = newBin->makeReverse(bin);
	vector<int> tmp2 = newBin->addBin(tmp1, one);
	int dec = newBin->decimal(tmp2);
	int res = (-1) * dec;
	return res;
}
bool Binary::checkpositive(vector<int> bin) {
	Binary* newBin = new Binary();
	int dec = newBin->decimal(bin);
	if (dec > pow(2, bin.size() - 1) - 1) {
		return true;
	}
	else {
		return false;
	}
}
bool Binary::checknegative(vector<int> bin) {
	Binary* newBin = new Binary();
	vector<int> one = { 1 };
	vector<int> tmp1 = newBin->makeReverse(bin);
	vector<int> tmp2 = newBin->addBin(tmp1, one);
	int dec = newBin->decimal(tmp2);
	if ((-1) * dec < (-1) * pow(2, bin.size() - 1)) {
		return true;
	}
	else {
		return false;
	}
}
bool Binary::checksum(vector<int> bin) {
	Binary* newBin = new Binary();
	int dec = newBin->decimal(bin);
	if (dec > pow(2, bin.size() - 2) - 1) {
		return true;
	}
	else {
		return false;
	}
}
bool Binary::checknegsum(vector<int> bin) {
	Binary* newBin = new Binary();
	vector<int> one = { 1 };
	vector<int> tmp1 = newBin->makeReverse(bin);
	vector<int> tmp2 = newBin->addBin(tmp1, one);
	int dec = newBin->decimal(tmp2);
	if ((-1) * dec < (-1) * pow(2, bin.size() - 2)) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	Binary* newBin = new Binary();
	cout << "Please, choose the operation: " << endl;
	cout << "Press 1 to convert decimal to binary." << endl;
	cout << "Press 2 to add two numbers." << endl;
	cout << "Press 3 to substract two numbers." << endl;
	cout << "Press 4 to multiply two numbers." << endl;
	cout << "Press 5 to divide two numbers." << endl << endl;
	cout << "Your choice is: ";
	int operation;
	cin >> operation;
	if (operation == 1) {
		int dec, dep;
		cout << "Enter decimal to convert: ";
		cin >> dec;
		cout << "Enter its digital capacity: ";
		cin >> dep;
		if (dec >= 0) {
			vector<int> bin = newBin->makeBinary(dec, dep);
			if (newBin->checkpositive(bin)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Your binary is: ";
				newBin->checkprint(bin);
			}
		}
		else if (dec < 0) {
			int dec1 = (-1) * dec;
			vector<int> bin = newBin->negative(dec1, dep);
			if (newBin->checknegative(bin)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Your binary is: ";
				newBin->checkprint(bin);
			}
		}
	}
	else if (operation == 2) {
		int dec1, dep1, dec2, dep2;
		cout << "Enter first number: ";
		cin >> dec1;
		cout << "Enter its digital capacity: ";
		cin >> dep1;
		cout << "Enter second number: ";
		cin >> dec2;
		cout << "Enter its digital capacity: ";
		cin >> dep2;
		if (dec1 >= 0 && dec2 >= 0) {
			vector<int> bin1 = newBin->makeBinary(dec1, dep1);
			if (newBin->checkpositive(bin1)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin1);
				cout << endl;
			}
			vector<int> bin2 = newBin->makeBinary(dec2, dep2);
			if (newBin->checkpositive(bin2)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin2);
				cout << endl;
			}
			vector<int> sum = newBin->addBin(bin1, bin2);
			if (newBin->checksum(sum)) {
				cout << "The sum is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "The sum is: ";
				newBin->checkprint(sum);
				cout << "Sum check (convert to decimal): " << newBin->decimal(sum) << endl;
			}
		}
		if (dec1 < 0 && dec2 < 0) {
			int dec11 = (-1) * dec1;
			int dec22 = (-1) * dec2;
			vector<int> bin11 = newBin->negative(dec11, dep1);
			vector<int> bin22 = newBin->negative(dec22, dep2);
			if (newBin->checknegative(bin11)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin11);
				cout << endl;
			}
			if (newBin->checknegative(bin22)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin22);
				cout << endl;
			}
			vector<int> sum2 = newBin->addBin(bin11, bin22);
			if (newBin->checknegsum(sum2)) {
				cout << "The sum is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "The result of addition is: ";
				newBin->checkprint(sum2);
				cout << "Sum check (convert to decimal): " << newBin->negativedecimal(sum2) << endl;
			}
		}
		if (dec1 >= 0 && dec2 < 0) {
			int dec22 = (-1) * dec2;
			vector<int> bin1 = newBin->makeBinary(dec1, dep1);
			vector<int> bin22 = newBin->negative(dec22, dep2);
			if (newBin->checkpositive(bin1)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin1);
			}
			if (newBin->checknegative(bin22)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin22);
				cout << endl;
			}
			if (dec1 > dec22) {
				vector<int> bin2 = newBin->makeBinary(dec22, dep2);
				vector<int> sum = newBin->subBin(bin1, bin2);
				cout << "The result of addition is: ";
				newBin->checkprint(sum);
				cout << "Sum check (convert to decimal): " << newBin->decimal(sum) << endl;
			}
			if (dec1 < dec22) {
				vector<int> bin1 = newBin->makeBinary(dec1, dep1);
				vector<int> bin2 = newBin->makeBinary(dec22, dep2);
				vector<int> sum = newBin->subBin(bin2, bin1);
				int decimal = newBin->decimal(sum);
				vector<int> res = newBin->negative(decimal, sum.size());
				cout << "The result of addition is: ";
				newBin->checkprint(res);
				cout << "Sum check (convert to decimal): " << newBin->negativedecimal(res) << endl;
			}
		}
		if (dec1 < 0 && dec2 >= 0) {
			int dec11 = (-1) * dec1;
			vector<int> bin2 = newBin->makeBinary(dec2, dep2);
			vector<int> bin11 = newBin->negative(dec11, dep1);
			if (newBin->checknegative(bin11)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "First binary is: ";
				newBin->checkprint(bin11);
				cout << endl;
			}
			if (newBin->checkpositive(bin2)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "Second binary is: ";
				newBin->checkprint(bin2);
			}

			if (dec2 > dec11) {
				vector<int> bin1 = newBin->makeBinary(dec11, dep1);
				vector<int> sum = newBin->subBin(bin2, bin1);
				cout << "The result of addition is: ";
				newBin->checkprint(sum);
				cout << "Sum check (convert to decimal): " << newBin->decimal(sum) << endl;
			}
			if (dec2 < dec11) {
				vector<int> bin2 = newBin->makeBinary(dec2, dep2);
				vector<int> bin1 = newBin->makeBinary(dec11, dep1);
				vector<int> sum = newBin->subBin(bin1, bin2);
				int decimal = newBin->decimal(sum);
				vector<int> res = newBin->negative(decimal, sum.size());
				cout << "The result of addition is: ";
				newBin->checkprint(res);
				cout << "Sum check (convert to decimal): " << newBin->negativedecimal(res) << endl;
			}
		}
	}
	else if (operation == 3) {
		int dec1, dep1, dec2, dep2;
		cout << "Enter number to be subtracted from: ";
		cin >> dec1;
		cout << "Enter its digital capacity: ";
		cin >> dep1;
		cout << "Enter number to be subtracted: ";
		cin >> dec2;
		cout << "Enter its digital capacity: ";
		cin >> dep2;
		if (dec1 >= 0 && dec2 >= 0) {
			vector<int> bin1 = newBin->makeBinary(dec1, dep1);
			if (newBin->checkpositive(bin1)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin1);
				cout << endl;
			}
			vector<int> bin2 = newBin->makeBinary(dec2, dep2);
			if (newBin->checkpositive(bin2)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin2);
				cout << endl;
			}
			if (dec1 < dec2) {
				vector<int> sub = newBin->subBin(bin2, bin1);
				int sub1 = newBin->decimal(sub);
				vector<int>sub2 = newBin->negative(sub1, sub.size());
				cout << "The subtraction is: ";
				newBin->checkprint(sub2);
				cout << "Subtraction check (convert to decimal): " << newBin->negativedecimal(sub2) << endl;
			}
			else {
				vector<int> sub = newBin->subBin(bin1, bin2);
				cout << "The subtraction is: ";
				newBin->checkprint(sub);
				cout << "Subtraction check (convert to decimal): " << newBin->decimal(sub) << endl;
			}

		}
		if (dec1 < 0 && dec2 < 0) {
			int dec11 = (-1) * dec1;
			int dec22 = (-1) * dec2;
			if (dec11 < dec22) {
				vector<int> bin1 = newBin->makeBinary(dec11, dep1);
				vector<int> bin11 = newBin->negative(dec11, dep1);
				vector<int> bin2 = newBin->makeBinary(dec22, dep2);
				vector<int> bin22 = newBin->negative(dec22, dep2);
				if (newBin->checknegative(bin11)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << "First binary is: ";
					newBin->checkprint(bin11);
					cout << endl;
				}
				if (newBin->checknegative(bin22)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << "Second binary is: ";
					newBin->checkprint(bin22);
					cout << endl;
				}
				vector<int> sub = newBin->subBin(bin2, bin1);
				cout << "The sub is: ";
				newBin->checkprint(sub);
				cout << "Sub check (convert to decimal): " << newBin->decimal(sub) << endl;
			}
			if (dec11 > dec22) {
				vector<int> bin1 = newBin->makeBinary(dec11, dep1);
				vector<int> bin11 = newBin->negative(dec11, dep1);
				vector<int> bin2 = newBin->makeBinary(dec22, dep2);
				vector<int> bin22 = newBin->negative(dec22, dep2);
				if (newBin->checknegative(bin11)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << "First binary is: ";
					newBin->checkprint(bin11);
					cout << endl;
				}
				if (newBin->checknegative(bin22)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << "Second binary is: ";
					newBin->checkprint(bin22);
					cout << endl;
				}
				vector<int> sub = newBin->subBin(bin1, bin2);
				cout << "The sub is: ";
				newBin->checkprint(sub);
				cout << "Sub check (convert to decimal): " << (-1) * newBin->decimal(sub) << endl;
			}
		}
		if (dec1 >= 0 && dec2 < 0) {
			vector<int> bin1 = newBin->makeBinary(dec1, dep1);
			if (newBin->checkpositive(bin1)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin1);
				cout << endl;
			}
			int dec22 = (-1) * dec2;
			vector<int> bin2 = newBin->makeBinary(dec22, dep2);
			vector<int> bin22 = newBin->negative(dec22, dep2);
			if (newBin->checknegative(bin22)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin22);
				cout << endl;
			}
			vector<int> sum = newBin->addBin(bin1, bin2);
			if (newBin->checksum(sum)) {
				cout << "The sub is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "The sub is: ";
				newBin->checkprint(sum);
				cout << "Sub check (convert to decimal): " << newBin->decimal(sum) << endl;
			}
		}
		if (dec1 < 0 && dec2 >= 0) {
			int dec11 = (-1) * dec1;
			vector<int> bin11 = newBin->negative(dec11, dep1);
			vector<int> bin1 = newBin->makeBinary(dec11, dep1);
			vector<int> bin2 = newBin->makeBinary(dec2, dep2);
			if (newBin->checknegative(bin11)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin11);
				cout << endl;
			}
			if (newBin->checkpositive(bin2)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin2);
				cout << endl;
			}
			vector<int> sub = newBin->subBin(bin11, bin2);
			if (newBin->checknegsum(sub)) {
				cout << "The sub is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "The result of sub is: ";
				newBin->checkprint(sub);
				cout << "Sub check (convert to decimal): " << newBin->negativedecimal(sub) << endl;
			}
		}
	}
	else if (operation == 4) {
		int dec1, dep1, dec2, dep2;
		cout << "Enter first number: ";
		cin >> dec1;
		cout << "Enter its digital capacity: ";
		cin >> dep1;
		cout << "Enter second number: ";
		cin >> dec2;
		cout << "Enter its digital capacity: ";
		cin >> dep2;
		if (dec1 > 0 && dec2 > 0) {
			vector<int> bin1 = newBin->makeBinary(dec1, dep1);
			if (newBin->checkpositive(bin1)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin1);
				cout << endl;
			}

			vector<int> bin2 = newBin->makeBinary(dec2, dep2);
			if (newBin->checkpositive(bin2)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin2);
				cout << endl;
			}
			vector<int> mul = newBin->multiBin(bin1, bin2);
			if (newBin->checkpositive(mul)) {
				cout << "The multiplication is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "The result of multiplication is: ";
				newBin->checkprint(mul);
				cout << "Multiplication check (convert to decimal): " << newBin->decimal(mul) << endl;
			}
		}
		else if (dec1 < 0 && dec2 < 0) {
			int dec11 = (-1) * dec1;
			int dec22 = (-1) * dec2;
			vector<int> bin1 = newBin->makeBinary(dec11, dep1);
			vector<int> bin2 = newBin->makeBinary(dec22, dep2);
			vector<int> bin11 = newBin->negative(dec11, dep1);
			vector<int> bin22 = newBin->negative(dec22, dep2);
			if (newBin->checknegative(bin11)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin11);
				cout << endl;
			}
			if (newBin->checknegative(bin22)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin22);
				cout << endl;
			}
			vector<int> mul = newBin->multiBin(bin1, bin2);
			if (newBin->checkpositive(mul)) {
				cout << "The multiplication is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "The result of multiplication is: ";
				newBin->checkprint(mul);
				cout << "Multiplication check (convert to decimal): " << newBin->decimal(mul) << endl;
			}
		}
		else if (dec1 > 0 && dec2 < 0) {
			int dec22 = (-1) * dec2;
			vector<int> bin1 = newBin->makeBinary(dec1, dep1);
			if (newBin->checkpositive(bin1)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin1);
			}
			vector<int> bin2 = newBin->makeBinary(dec22, dep2);
			vector<int> bin22 = newBin->negative(dec22, dep2);
			if (newBin->checknegative(bin22)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin22);
				cout << endl;
			}
			vector<int> mul = newBin->multiBin(bin1, bin2);
			int mul1 = newBin->decimal(mul);
			vector<int> res = newBin->negative(mul1, mul.size());
			if (newBin->checknegative(res)) {
				cout << "The multiplication is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "The result of multiplication is: ";
				newBin->checkprint(res);
				cout << "Multiplication check (convert to decimal): " << newBin->negativedecimal(res) << endl;
			}
		}
		else if (dec1 < 0 && dec2 > 0) {
			int dec11 = (-1) * dec1;
			vector<int> bin1 = newBin->makeBinary(dec11, dep1);
			vector<int> bin11 = newBin->negative(dec11, dep1);
			if (newBin->checknegative(bin11)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin11);
			}
			vector<int> bin2 = newBin->makeBinary(dec2, dep2);
			if (newBin->checkpositive(bin2)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin2);
				cout << endl;
			}
			vector<int> mul = newBin->multiBin(bin1, bin2);
			int mul1 = newBin->decimal(mul);
			vector<int> res = newBin->negative(mul1, mul.size());
			if (newBin->checknegative(res)) {
				cout << "The multiplication is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "The result of multiplication is: ";
				newBin->checkprint(res);
				cout << "Multiplication check (convert to decimal): " << newBin->negativedecimal(res) << endl;
			}
		}
		else if (dec1 == 0 || dec2 == 0 || (dec1 == 0 && dec2 == 0)) {
			if (dec1 > 0) {
				vector<int> bin1 = newBin->makeBinary(dec1, dep1);
				if (newBin->checkpositive(bin1)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << endl;
					cout << "First binary is: ";
					newBin->checkprint(bin1);
					cout << endl;
				}
			}
			else if (dec2 > 0) {
				vector<int> bin2 = newBin->makeBinary(dec2, dep2);
				if (newBin->checkpositive(bin2)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << "Second binary is: ";
					newBin->checkprint(bin2);
					cout << endl;
				}
			}
			if (dec1 < 0) {
				int dec11 = (-1) * dec1;
				vector<int> bin1 = newBin->negative(dec11, dep1);
				if (newBin->checknegative(bin1)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << endl;
					cout << "First binary is: ";
					newBin->checkprint(bin1);
					cout << endl;
				}
			}
			if (dec2 < 0) {
				int dec22 = (-1) * dec2;
				vector<int> bin2 = newBin->negative(dec22, dep1);
				if (newBin->checknegative(bin2)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << endl;
					cout << "Second binary is: ";
					newBin->checkprint(bin2);
					cout << endl;
				}
			}
			vector<int> res;
			int sz = dep1 > dep2 ? dep1 : dep2;
			while (res.size() != sz) {
				res.push_back(0);
			}
			cout << "The result of multiplication is: ";
			newBin->checkprint(res);
			cout << "Multiplication check (convert to decimal): " << newBin->decimal(res) << endl;
		}
	}
	else if (operation == 5) {
		int dec1, dep1, dec2, dep2;
		cout << "Enter first number: ";
		cin >> dec1;
		cout << "Enter its digital capacity: ";
		cin >> dep1;
		cout << "Enter second number: ";
		cin >> dec2;
		cout << "Enter its digital capacity: ";
		cin >> dep2;
		if (dec1 > 0 && dec2 > 0) {
			vector<int> bin1 = newBin->makeBinary(dec1, dep1);
			if (newBin->checkpositive(bin1)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "First binary is: ";
				newBin->checkprint(bin1);
				cout << endl;
			}
			vector<int> bin2 = newBin->makeBinary(dec2, dep2);
			if (newBin->checkpositive(bin2)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin2);
				cout << endl;
			}
			vector<int> div = newBin->divBin(bin1, bin2);
			cout << "The result of division is: ";
			newBin->checkprint(div);
			cout << "Division check (convert to decimal): " << newBin->decimal(div) << endl;
		}
		else if (dec1 < 0 && dec2 < 0) {
			int dec11 = (-1) * dec1;
			int dec22 = (-1) * dec2;
			vector<int> bin1 = newBin->makeBinary(dec11, dep1);
			vector<int> bin2 = newBin->makeBinary(dec22, dep2);
			vector<int> bin11 = newBin->negative(dec11, dep1);
			vector<int> bin22 = newBin->negative(dec22, dep2);
			if (newBin->checknegative(bin11)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin11);
				cout << endl;
			}
			if (newBin->checknegative(bin22)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin22);
				cout << endl;
			}
			vector<int> div = newBin->divBin(bin1, bin2);
			cout << "The result of division is: ";
			newBin->checkprint(div);
			cout << "Division check (convert to decimal): " << newBin->decimal(div) << endl;
		}
		else if (dec1 > 0 && dec2 < 0) {
			int dec22 = (-1) * dec2;
			vector<int> bin1 = newBin->makeBinary(dec1, dep1);
			if (newBin->checkpositive(bin1)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin1);
			}
			vector<int> bin2 = newBin->makeBinary(dec22, dep2);
			vector<int> bin22 = newBin->negative(dec22, dep2);
			if (newBin->checknegative(bin22)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin22);
				cout << endl;
			}
			vector<int> div = newBin->divBin(bin1, bin2);
			int divv = newBin->decimal(div);
			vector<int> res = newBin->negative(divv, div.size());
			cout << "The result of division is: ";
			newBin->checkprint(res);
			cout << "Division check (convert to decimal): " << newBin->negativedecimal(res) << endl;
		}
		else if (dec1 < 0 && dec2 > 0) {
			int dec11 = (-1) * dec1;
			vector<int> bin1 = newBin->makeBinary(dec11, dep1);
			vector<int> bin11 = newBin->negative(dec11, dep1);
			if (newBin->checknegative(bin11)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << endl;
				cout << "First binary is: ";
				newBin->checkprint(bin11);
			}
			vector<int> bin2 = newBin->makeBinary(dec2, dep2);
			if (newBin->checkpositive(bin2)) {
				cout << "The number is out of range." << endl;
				exit(0);
			}
			else
			{
				cout << "Second binary is: ";
				newBin->checkprint(bin2);
				cout << endl;
			}
			vector<int> div = newBin->divBin(bin1, bin2);
			int divv = newBin->decimal(div);
			vector<int> res = newBin->negative(divv, div.size());
			cout << "The result of division is: ";
			newBin->checkprint(res);
			cout << "Division check (convert to decimal): " << newBin->negativedecimal(res) << endl;
		}
		else if (dec1 == 0 || dec2 == 0 || (dec1 == 0 && dec2 == 0)) {
			if (dec1 > 0) {
				vector<int> bin1 = newBin->makeBinary(dec1, dep1);
				if (newBin->checkpositive(bin1)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << endl;
					cout << "First binary is: ";
					newBin->checkprint(bin1);
					cout << endl;
				}
			}
			else if (dec2 > 0) {
				vector<int> bin2 = newBin->makeBinary(dec2, dep2);
				if (newBin->checkpositive(bin2)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << "Second binary is: ";
					newBin->checkprint(bin2);
					cout << endl;
				}
			}
			if (dec1 < 0) {
				int dec11 = (-1) * dec1;
				vector<int> bin1 = newBin->negative(dec11, dep1);
				if (newBin->checknegative(bin1)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << endl;
					cout << "First binary is: ";
					newBin->checkprint(bin1);
					cout << endl;
				}
			}
			if (dec2 < 0) {
				int dec22 = (-1) * dec2;
				vector<int> bin2 = newBin->negative(dec22, dep1);
				if (newBin->checknegative(bin2)) {
					cout << "The number is out of range." << endl;
					exit(0);
				}
				else
				{
					cout << endl;
					cout << "Second binary is: ";
					newBin->checkprint(bin2);
					cout << endl;
				}
			}

			if (dec1 == 0 && dec2 == 0) {
				cout << "Such way of division is impossible." << endl;
			}
			else if (dec1 == 0 && dec2 != 0) {
				vector<int> res;
				int sz = dep1 > dep2 ? dep1 : dep2;
				while (res.size() != sz) {
					res.push_back(0);
				}
				cout << "The result of division is: ";
				newBin->checkprint(res);
				cout << "Division check (convert to decimal): " << newBin->decimal(res) << endl;
			}
			else if (dec2 == 0 && dec1 != 0) {
				cout << "Such way of division is impossible." << endl;
			}

		}
	}
	else
	{
		cout << "No such operation." << endl;
	}
	return 0;
}
