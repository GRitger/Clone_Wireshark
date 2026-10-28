#include "Packet.h"

Packet::Packet(){}
Packet::~Packet(){}
void Packet::save_paket(int time_sec, int time_usec, int save_len, int orig_len,vector<char>& data) {
	this->time_sec = time_sec;
	this->time_usec = time_usec;
	this->save_len = save_len;
	this->orig_len = orig_len;
	this->data = data;
}

int Packet::get_save_len() {
	return save_len;
}
