#include "Packet.h"

Packet::Packet(){}
Packet::~Packet(){}
void Packet::save_paket(pcap_pkthdr* header, const u_char* data) {
	time_sec = header->ts.tv_sec;
	time_usec = header->ts.tv_usec;
	save_len = header->caplen;
	orig_len = header->len;
	this->data.assign(data, data + header->caplen);
}

int Packet::get_save_len() {
	return save_len;
}
