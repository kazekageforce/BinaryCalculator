#pragma once
#include <vector>
using namespace std;
class Binary {
private:
	vector<int> binary;
public:
	Binary();
	~Binary();
	void SetBinary(vector<int> bin);
	vector<int> GetBinary();
	void checkprint(vector<int> const& input);
	vector<int> makeBinary(int var, int depth);
	vector<int> makeReverse(vector<int> arr);
	vector<int> addBin(vector<int> a, vector<int> b);
	vector<int> negative(int var, int depth);
	vector<int> subBin(vector<int> a, vector<int> b);
	vector<int> multiBin(vector<int> a, vector<int> b);
	vector<int> divBin(vector<int> a, vector<int> b);
	bool checkpositive(vector<int> bin);
	bool checknegative(vector<int> bin);
	bool checksum(vector<int> bin);
	bool checknegsum(vector<int> bin);
	int decimal(vector<int> bin);
	int negativedecimal(vector<int> bin);
};