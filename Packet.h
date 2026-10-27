#pragma once

#include <pcap.h>
#include <vector>

using namespace std;

class Packet
{
public:
	Packet();
	~Packet();
	void save_paket(pcap_pkthdr* header, const u_char* data);
	int get_save_len();

private:
	pcap_pkthdr header;
	vector <u_char> data;
	int time_sec = 0;
	int time_usec = 0;
	int save_len = 0;
	int orig_len = 0;
};