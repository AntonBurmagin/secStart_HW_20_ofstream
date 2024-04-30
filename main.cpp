#include <iostream>
#include <fstream>
#include <ctime>

bool salaryListFormat(std::string name, std::string surname, int salary, std::string date) {
    if (salary >= 0 && name.size() > 0 && surname.size() > 0 && date[2] == ':' && date[5] == ':') {
        std::string day = date.substr(0, 2);
        std::string month = date.substr(3, 2);
        std::string year = date.substr(6, 4);
        std::cout << day << " " << month << " " << year << std::endl;
        if ("01" <= day && day <= "31" && "01" <= month && month <= "12" && "2020" <= year && year <= "2024")
            return true;
    }
    return false;
}

int main() {
    //20.5.1 salary list write in file
    /*
    std::fstream file("salary-list.txt", std::ios::app);
    if (file.is_open()) 
    {
        std::cout << "Input data (name, surname, salary, date):\n";
        std::string name, surname, date;
        int salary;
        for (int i = 0; i < 2; ) 
        {
            std::cin >> name >> surname >> salary >> date;
            if (salaryListFormat(name, surname, salary, date)) 
            {
                file << name << " " << surname << " " << salary << " " << date << std::endl;
                i++;
            } else 
            {
                std::cout << "Incorrect information forme!" << std::endl;
            }
        }
        file.close();
    } else 
    {
        std::cout << "Couldn't open file!" << std::endl;
    }
    */

    //20.5.2 random input in .txt file
    /*
    std::ofstream file("painting.txt");
    if (file.is_open()) {
        std::cout << "Open\n";
        bool correctInput = false;
        int height, width;
        do {
            std::cout << "Input height and width:" << std::endl;
            std::cin >> height >> width;
            if (height > 0 && width > 0)
                correctInput = true;
        } while (!correctInput);

        std::srand(std::time(nullptr));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                file << std::rand() % 2;
            }
            file << std::endl;
        }
        file.close();
    }
    */
    

}