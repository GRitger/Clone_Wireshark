#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Ethernet {
public:
	Ethernet();
	~Ethernet();
	void print();
	void decode();
	void set_header(unsigned char dist_mac[6], unsigned char src_mac[6], unsigned short type);
	bool read(vector<unsigned char>& data, int len);
	string macToString(unsigned char mac[6]);
	string print_type(unsigned short type);
private:
	unsigned char dist_mac[6];
	unsigned char src_mac[6];
	unsigned short type;
};