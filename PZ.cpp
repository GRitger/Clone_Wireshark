#include "PacketSequence.h"
#include <iostream>
#include <string>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


    std::cout << "Введите путь к pcap-файлу: " << std::endl;
    std::string path;
    std::getline(std::cin, path);
    PacketSequence packets(path);
    int option = 0;
    while (option != -1) {
        switch (option)
        {
        case 0:
            std::cout << "========== МЕНЮ ==========" << std::endl;
            std::cout << "0. Показать меню" << std::endl;
            std::cout << "1. Показать информацию о файле" << std::endl;
            std::cout << "2. Показать статистику пакетов" << std::endl;
            std::cout << "3. Показать статистику" << std::endl;
            std::cout << "4. Закрыть файл" << std::endl;
            std::cout << "-1. Выход" << std::endl;
            std::cout << "Выберите пункт: ";
            cin >> option;
            break;
        case 1:
            packets.header();
            cin >> option;
            break;
        case 2:
            packets.statistik();
            cin >> option;
            break;
        case -1:
            break;
        }
    }
    return 0;
}