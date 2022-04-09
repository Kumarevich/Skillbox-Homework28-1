#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

std::vector<std::string> result_table;
std::mutex result_table_access;

void swimmer(int speed, std::string name) {
    int distance = 100;
    int time = 0;
    while (distance > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        distance -= speed;
        std::cout << name << std::endl;
        std::cout << "distance: " << 100 - distance << std::endl;
        ++time;
    }
    std::string result = name + ": " + std::to_string(time) + " sec.";
    result_table_access.lock();
    result_table.push_back(result);
    result_table_access.unlock();
}

int main() {
    int speed[6];
    std::string name[6];
    for (int i = 0; i < 6; ++i) {
        std::cout << "Input the " << i + 1 << " swimmer name and speed: ";
        std::cin >> name[i] >> speed[i];
    }
    std::thread swimmer1(swimmer, speed[0], name[0]);
    std::thread swimmer2(swimmer, speed[1], name[1]);
    std::thread swimmer3(swimmer, speed[2], name[2]);
    std::thread swimmer4(swimmer, speed[3], name[3]);
    std::thread swimmer5(swimmer, speed[4], name[4]);
    std::thread swimmer6(swimmer, speed[5], name[5]);
    swimmer1.join();
    swimmer2.join();
    swimmer3.join();
    swimmer4.join();
    swimmer5.join();
    swimmer6.join();

    for (int i = 0; i < result_table.size(); ++i) {
        std::cout << result_table[i] << std::endl;
    }
    return 0;
}
