#pragma once

#include <pcap.h>
#include <string>
#include <vector>
#include  "Packet.h"

using namespace std;
class PacketSequence
{
public:
    PacketSequence();
    PacketSequence(string& path);
    PacketSequence(PacketSequence& other);
    ~PacketSequence();

    void open(string& path);
    void close();
    bool isOpen();
    const char* lastError();
    void statistik();
    void header();
    void read_pakets();

private:
    int magic_number = 0;
    int version_major = 0;
    int version_minor = 0;
    int paket_len = 0;
    int networ = 0;
    int min_len = 10000000000000000;
    long long sr_len = 0;
    int max_len = 0;
    long long sum = 0;
    int count_paket = 0;
    vector<Packet> pakets;
    pcap_t* file_descriptor = nullptr;
    char errbuf[PCAP_ERRBUF_SIZE];
    string file_name;
};
