#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

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

std::vector<int> readATM(std::string path) {
    std::fstream file(path);
    std::vector<int> buff;
    int banknote;
    while (!file.eof()) {
        file >> banknote;
        buff.push_back(banknote);
    }
    file.close();
    return buff;
}

void refreshATM(std::string path, std::vector<int> buff) {
    std::fstream file(path);
    for (int i = 0; i < buff.size(); i++) {
        file << buff[i] << std::endl;
    }
    file.close();
}

void stateWrite (std::string path, std::vector<int> vec, int banknotes[]) {
    int count[6]= {0};
    int sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
        for (int j = 0; j < 6; j++) {
            if (vec[i] == banknotes[j]) {
                count[j]++;
            }
        }
    }
    std::fstream file(path);
    file << sum << std::endl;
    for (int j = 5; j > -1; j--) {
        file << count[j] << std::endl;
    }
    file.close();
}

void stateRead (std::string path, int &sum, int banknotes[]) {
    std::fstream file(path);
    file >> sum;
    int count[6]= {0};
    for (int j = 5; j > -1; j--) {
        file >> count[j];
    }
    std::cout << "The ATM sum is: " << sum << std::endl;
    for (int i = 5; i > -1; i--) {
        std::cout << banknotes[i] << " " << count[i] << std::endl;
    }
    file.close();
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
    
    //20.5.3 fishing from to file
    /*
    std::fstream lake("lake.txt");
    std::fstream basket("basket.txt", std::ios::app);
    if (lake.is_open() && basket.is_open()) {
        std::string fish;
        while (true) {
            std::cout << "What kind of fish? (quit to go home)" << std::endl;
            std::cin >> fish;
            if (fish == "quit")
                break;
            int count = 0;
            while (!lake.eof()) {
                std::string lakeFish;
                lake >> lakeFish;
                std::cout << lakeFish << std::endl;
                if (lakeFish == fish) {
                    basket << fish << std::endl;
                    count++;
                }
            }
            lake.seekg(0);
            std::cout << "Have caught " << count << " " << fish << std::endl;
        }
        std::cout << "Bon appetite!" << std::endl;
    }
    lake.close();
    basket.close();
    */

    //20.5.4 ATM
    std::fstream state ("ATM_state.bin");
    std::ofstream f("ATM.txt");
    
    int bankSum = 0;
    int banknotes[] = {100, 200, 500, 1000, 2000, 5000};
    bool emptyATM = true;
    int ATM_capacity = 10;
    if (state.is_open()) {
        emptyATM = false;
        stateRead("ATM_state.bin", bankSum, banknotes);
    } else {
        std::cout << "ATM is empty..." << std::endl;
    }
    state.close();

    while (true) {
        char command;
        std::cout << "Operation ('+' to fill the ATM, '-' to get money, 'q' - to quit):\n";
        std::cin >> command;
        if (command == 'q') {
            std::cout << "Good luck" << std::endl;
            break;
        } else if (command == '+') {
            std::vector<int> buff = readATM("ATM.txt");
            if (buff.size() != ATM_capacity) {
                buff.resize(ATM_capacity);
            }
            for (int i = 0; i < buff.size(); i++) {
                if (buff[i] == 0)
                    buff[i] = banknotes[std::rand() % 6];
            }
            refreshATM("ATM.txt", buff);
            std::cout << "ATM is filled!" << std::endl;
            if (emptyATM) {
                std::ofstream state;
                state.open("ATM_state.bin");
                emptyATM = false;
                state.close();
            }
            stateWrite("ATM_state.bin", buff, banknotes);

        } else if (command == '-') {
            if (!emptyATM) {
                int sum;
                std::cout << "What's the sum:" << std::endl;
                std::cin >> sum;
                if (sum > 0 && sum % 100 == 0) {
                    int safeSum = sum;
                    std::vector<int> buff = readATM("ATM.txt");
                    if (buff.size() != ATM_capacity) {
                       buff.resize(ATM_capacity);
                    }
                    int banknote = 5;
                    for (int i = 0; sum!= 0 && banknote != -1; i++) {
                        std::cout << sum << " " << i << " " << banknote << std::endl;
                        if (sum / banknotes[banknote] > 0 && buff[i] == banknotes[banknote]) {
                            sum -= banknotes[banknote];
                            buff[i] = 0;
                        }
                        if (sum / banknotes[banknote] == 0)
                            i = ATM_capacity - 1;
                        if(i == ATM_capacity - 1) {
                            i = -1;
                            banknote--;
                        }
                    }
                    if (sum == 0) {
                        std::cout << "You get your " << safeSum << std::endl;
                        refreshATM("ATM.txt", buff);
                        stateWrite("ATM_state.bin", buff, banknotes);
                    } else {
                        std::cout << "ATM doesn't have enough money" << std::endl;
                    }

                } else {
                    std::cout << "Incorrect sum." << std::endl;
                }
            } else {
                std::cout << "Sorry, ATM is empty." << std::endl;
            }
        } else {
            std::cout << "Unknown command, try again." << std::endl;
        }

        
    }
    state.close();
    f.close();


}