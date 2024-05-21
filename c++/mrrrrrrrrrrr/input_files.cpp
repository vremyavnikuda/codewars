#include <fstream>
#include <string>
#include <iostream>

int main()
{

    std::ifstream file("kontolnaya_rabota_informatika/test2.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else
    {
        std::cerr << "Noo" << std::endl;
    }
    return 0;
}
