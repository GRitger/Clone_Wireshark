#include "PacketSequence.h"
#include <iostream>
using namespace std;
PacketSequence::PacketSequence()
{
    //errbuf[0] = '\0';
}

PacketSequence::PacketSequence(string& path)
{
    //errbuf[0] = '\0';
    open(path);
}

PacketSequence::~PacketSequence()
{
    close();
}

unsigned int PacketSequence::read32()
{
	unsigned int value;
    file.read((char*)&value, 4);
    return value;
}

unsigned short PacketSequence::read16()
{
    unsigned short value;
    file.read((char*)&value, 2);
    return value;
}

void PacketSequence::open(string& path)
{
    if (path.find('"') != string::npos){
		path.erase(remove(path.begin(), path.end(), '"'), path.end());
    }
    file.open(path, ios::binary);
    file_name = path.substr(path.find_last_of("/\\") + 1);
}

void PacketSequence::close()
{
    if (file.is_open())
    {
		file.close();
    }

    errbuf[0] = '\0';
}


const char* PacketSequence::lastError()
{
    return (errbuf[0] != '\0') ? errbuf : "OK";
}

void PacketSequence::statistik()
{
    std::cout << "Количество пакетов в файле: " << count_paket << '\n';
    std::cout << "Минимальный размер пакета: " << min_len << '\n';
    std::cout << "Максимальный размер пакета: " << max_len << '\n';
    std::cout << "Средний размер пакета: " << sr_len << '\n';
}
void PacketSequence::header()
{ 
    magic_number = read32();
	version_major = read16();
    version_major = read16();
	thiszone = read32();
	sigfigs = read32();
	paket_len = read32();
    networ = read32();
    std::cout << "Информаци о файле: " << file_name << '\n';
    std::cout << "Старшая версия формата: " << version_major << '\n';
    std::cout << "Младшая версия формата: " << version_minor << '\n';
    std::cout << "Максимальная длина сохраняемой части: " << paket_len << '\n';
    std::cout << "Тип канального уровня: " << networ << '\n';
    std::cout << "Обратный порядок байт: " << ((magic_number != 0) ? "нет" : "да") << '\n';
}

void PacketSequence::read_pakets() {
    while (1) {
        if (!file) break;
        count_paket++;
        Packet temp;
        int time_sec = read32();
        int time_usec = read32();
        int save_len = read32();
        int orig_len = read32();
		vector <char> data(save_len);
        file.read(data.data(), save_len);
        temp.save_paket(time_sec, time_usec, save_len, orig_len, data);
        pakets.push_back(temp);
        min_len = min(temp.get_save_len(), min_len);
        max_len = max(temp.get_save_len(), max_len);
		sum += temp.get_save_len();
    }
	sr_len = sum / count_paket;
}