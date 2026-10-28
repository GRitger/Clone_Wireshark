#include "Ethernet.h"

Ethernet::Ethernet(){}
Ethernet::~Ethernet(){}

void Ethernet::set_header(unsigned char dist_mac[6], unsigned char src_mac[6], unsigned short type) {
	for (int i = 0; i < 6; i++) {
		this->dist_mac[i] = dist_mac[i];
		this->src_mac[i] = src_mac[i];
	}
	this->type = type;
}

bool Ethernet::read(vector<unsigned char>& data, int len) {
	if (len < 14) {
		return false;
	}
	for (int i = 0; i < 6; i++) {
		dist_mac[i] = data[i];
		src_mac[i] = data[6 + i];
	}
	type = (data[12] << 8) | data[13];
	return true;
}
void Ethernet::print()
{
	cout << "--- Ethernet ---" << '\n';
	cout << "MAC получателя:  " << macToString(dist_mac) << '\n';
	cout << "MAC отправителя: " << macToString(src_mac) << '\n';
	cout << "Тип протокола: " << print_type(type) << '\n';
}