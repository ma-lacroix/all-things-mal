#include <thread>
#include <iostream>

class Cleaners {
public:
    Cleaners() {};
    void clean() {
        std::cout << "cleaning ship..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "cleaning ship done!" << std::endl;
    }
    ~Cleaners() {};
};

class EngineCrew {
public:
    EngineCrew() {};
    void move() {
        std::cout << "moving ship..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        // TODO: does not print! 
        std::cout << "moving ship done!" << std::endl;
    }
    void stop() {
        std::cout << "stopping ship..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(6000));
        // TODO: does not print!
        std::cout << "stopping ship done!" << std::endl;
    }
    ~EngineCrew() {};
};

class Captain {

public:
    Cleaners cleaners;
    EngineCrew engineCrew;
    Captain(Cleaners *cleaners, EngineCrew *engineCrew) {
        this->cleaners = *cleaners;
        this->engineCrew = *engineCrew;
    }
    void move_forward() {
        std::cout << "Captain says: move forward" << std::endl;
        cleaners.clean();
    }
    void stop_moving() {
        std::cout << "Captain says: stop moving" << std::endl;
    }
    void clean_ship() {
        std::cout << "Captain says: clean ship" << std::endl;
    }
    ~Captain() {
        cleaners.~Cleaners();
        engineCrew.~EngineCrew();
    };
};

int main() {

    std::cout << "Starting program" << std::endl;
    
    Cleaners *cleaners = new Cleaners();
    EngineCrew *engineCrew = new EngineCrew();
    Captain *captain = new Captain(cleaners, engineCrew);
    
    int user_input = 0;

    while (user_input != 100) {
        
        std::cout << "Enter input: " << std::endl;
        std::cin >> user_input;

        if (user_input == 1) {
            std::thread thread1(&Captain::clean_ship, *captain);
            thread1.detach();
        } else if (user_input == 2) {
            std::thread thread2(&Captain::move_forward, *captain);
            thread2.join();
        } else if (user_input == 3){
            std::thread thread3(&Captain::stop_moving, *captain);
            thread3.join();
        } else {
            std::cout << "Invalid input" << std::endl;
        }
        

        std::cout << "Understood!" << std::endl;

    }

    return 0;
}