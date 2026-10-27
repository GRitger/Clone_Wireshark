#include "PacketSequence.h"
#include <iostream>
using namespace std;
PacketSequence::PacketSequence()
{
    file_descriptor = nullptr;
    errbuf[0] = '\0';
}

PacketSequence::PacketSequence(string& path)
{
    file_descriptor = nullptr;
    errbuf[0] = '\0';
    open(path);
}

PacketSequence::~PacketSequence()
{
    close();
}

void PacketSequence::open(string& path)
{
    if (path.find('"') != string::npos){
		path.erase(remove(path.begin(), path.end(), '"'), path.end());
    }
    file_descriptor = pcap_open_offline(path.c_str(), errbuf);
    file_name = path.substr(path.find_last_of("/\\") + 1);
}

void PacketSequence::close()
{
    if (file_descriptor != nullptr)
    {
        pcap_close(file_descriptor);
        file_descriptor = nullptr;
    }

    errbuf[0] = '\0';
}

bool PacketSequence::isOpen()
{
    return file_descriptor != nullptr;
}
const char* PacketSequence::lastError()
{
    return (errbuf[0] != '\0') ? errbuf : "OK";
}

void PacketSequence::statistik()
{
    
}
void PacketSequence::header()
{ 
    version_major = pcap_major_version(file_descriptor);
    version_minor = pcap_minor_version(file_descriptor);
    paket_len = pcap_snapshot(file_descriptor);
    networ = pcap_datalink(file_descriptor);
    magic_number = pcap_is_swapped(file_descriptor);
    std::cout << "Информаци о файле: " << file_name << '\n';
    std::cout << "Старшая версия формата: " << version_major << '\n';
    std::cout << "Младшая версия формата: " << version_minor << '\n';
    std::cout << "Максимальная длина сохраняемой части: " << paket_len << '\n';
    std::cout << "Тип канального уровня: " << networ << '\n';
    std::cout << "Обратный порядок байт: " << ((magic_number != 0) ? "нет" : "да") << '\n';
}

void PacketSequence::read_pakets() {
    pcap_pkthdr* header;
    const u_char* data;
    while (pcap_next_ex(file_descriptor, &header, &data) == 1) {
        count_paket++;
        Packet temp;
        temp.save_paket(header, data);
        pakets.push_back(temp);
        min_len = min(temp.get_save_len(), min_len);
        max_len = max(temp.get_save_len(), max_len);
    }
}