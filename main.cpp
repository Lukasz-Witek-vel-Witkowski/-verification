/*
 * @Author: Your name
 * @Date:   2020-05-01 13:16:27
 * @Last Modified by:   Your name
 * @Last Modified time: 2020-05-04 01:15:34
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#define fileArduino "plikArduino.txt"
#define filePC "plikpc.txt"
void load(std::ifstream &file, std::string nameFile, std::vector<std::tuple<std::string, std::string, std::string, std::string>> &V);
void analizer(std::vector<std::tuple<std::string, std::string, std::string, std::string>> &V_a, std::vector<std::tuple<std::string, std::string, std::string, std::string>> &V_p);
int main()
{
    std::cout << "Start programu\n";
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> V_arduino;
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> V_pc;
    std::ifstream f_Arduino;
    load(f_Arduino, fileArduino, V_arduino);
    std::ifstream f_PC;
    load(f_PC, filePC, V_pc);
    analizer(V_arduino, V_pc);
    return 0;
}
void load(std::ifstream &file, std::string nameFile, std::vector<std::tuple<std::string, std::string, std::string, std::string>> &V)
{
    file.open(nameFile.c_str());
    if (file.good())
    {
        std::string temp;
        std::tuple<std::string, std::string, std::string, std::string> tup;
        int j{};
        size_t pointer{};
        std::string pc[4];
        const int ptr = 0;
        while (!file.eof())
        {
            std::getline(file, temp);
            for (int i = 0; i < 4; i++)
            {
                pointer = temp.find("|");
                if (pointer != std::string::npos)
                {
                    temp = temp.substr(pointer + 1);
                }

                pointer = temp.find("|");
                //std::cout << temp.substr(0, pointer) << "\n";
                pc[j] = temp.substr(0, pointer);
                j++;
                j = j % 4;
                const_cast<int &>(ptr) = j;
            }
            std::get<0>(tup) = pc[0];
            std::get<1>(tup) = pc[1];
            std::get<2>(tup) = pc[2];
            std::get<3>(tup) = pc[3];
            V.push_back(tup);
            // std::cout << V.size() << "\n";
        }
        file.close();
    }
    else
    {
        std::cout << "Problem z odczytem pliku " << nameFile << "\n";
    }
}
void analizer(std::vector<std::tuple<std::string, std::string, std::string, std::string>> &V_a, std::vector<std::tuple<std::string, std::string, std::string, std::string>> &V_p)
{
    //! V_a arduino
    //! V_p pc
    std::string ar[4]{};
    std::string pc[4]{};
    int Size = V_p.size();
    int is_OK = 0;
    int is_ok_one = 0;
    // std::vector<std::tuple<std::string, std::string, std::string, std::string>>::iterator y = V_a.begin();
    for (auto x : V_p)
    {
        std::tie(pc[0], pc[1], pc[2], pc[3]) = x;
        {
            for (auto y : V_a)
            {
                std::tie(ar[0], ar[1], ar[2], ar[3]) = y;
                //  if (y == V_a.end())
                //     break;
                if (pc[0] == ar[0] && pc[1] == ar[1] && pc[2] == ar[2] && pc[3] == ar[3])
                {
                /* for (int i = 0; i < 4; i++)
                    {
                        std::cout << pc[i] << "-" << ar[i] << "\t";
                    }
                    std::cout << "\n";*/
                    is_OK++;
                    break;
                }
            }
            for (auto y : V_a)
            {
                std::tie(ar[0], ar[1], ar[2], ar[3]) = y;
                if (pc[0] == ar[0])
                {
                    is_ok_one++;
                    break;
                }
            }
            for (auto y : V_a)
            {
                std::tie(ar[0], ar[1], ar[2], ar[3]) = y;
                if (pc[1] == ar[1])
                {
                    is_ok_one++;
                    break;
                }
            }
            for (auto y : V_a)
            {
                std::tie(ar[0], ar[1], ar[2], ar[3]) = y;
                if (pc[2] == ar[2])
                {
                    is_ok_one++;
                    break;
                }
            }
            for (auto y : V_a)
            {
                std::tie(ar[0], ar[1], ar[2], ar[3]) = y;
                if (pc[3] == ar[3])
                {
                    is_ok_one++;
                    break;
                }
            }
        }
    }
    double x = is_OK;
    double max = Size;
    std::cout << "wynik prawodlowej transmisji = " << (x * 100) / max << " [%]\n";
    std::cout << "wynik pojedynczego byta = " << (is_ok_one * 100) / (max * 4) << " [%]\n";
}