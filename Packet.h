#pragma once

#include <pcap.h>
#include <vector>

using namespace std;

class Packet
{
public:
	Packet();
	~Packet();
	void save_paket(int time_sec, int time_usec, int save_len, int orig_len, vector<char>& data);
	int get_save_len();

private:
	pcap_pkthdr header;
	vector <char> data;
	int time_sec = 0;
	int time_usec = 0;
	int save_len = 0;
	int orig_len = 0;
};