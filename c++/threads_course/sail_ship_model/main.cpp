#include <chrono>
#include <queue>
#include <thread>
#include <iostream>

class Cleaners {

public:
    Cleaners() {};

    void cleaningCrewActivity(std::queue<int>& tasks) {
        while (true) {
            if (tasks.empty()) {
                std::cout << " Cleaning Crew - Activity Queue is empty: Waiting for 2 seconds\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
            } else {
                int currentActivity = tasks.front();
                tasks.pop();
                if (currentActivity == 100) {
                    std::cout << " Cleaning Crew - All Activities Completed - Exiting\n";
                    break;
                } else {
                    std::cout << " Cleaning Crew - Cleaning \n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    std::cout << " Cleaning Crew - Cleaning DONE \n";
                    std::cout << " Cleaning Crew is resting for 1 seconds after tiresome work \n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }
        }
    }

    ~Cleaners() {};
};

class EngineCrew {

public:
    std::queue<int> tasks;

public:
    EngineCrew() {};
    
    void engineCrewActivity(std::queue<int>& tasks) {

	while (true) {
		if (tasks.empty()) {
			std::cout << " Engine Crew - Activity Queue is empty: Waiting for 2 seconds\n";
			std::this_thread::sleep_for(std::chrono::seconds(3));
		} else {
			int currentActivity = tasks.front();
			tasks.pop();
			if (currentActivity == 100) {
				std::cout << " Engine Crew - All Activities Completed - Exiting\n";
				break;
			} else if (currentActivity == 2) {
				std::cout << " Engine Crew - Full Speed Ahead \n";
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				std::cout << " Engine Crew - Full Speed Ahead DONE \n";
 
			} else {
				std::cout << " Engine Crew - Full Speed Ahead \n";
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				std::cout << " Engine Crew - Full Speed Ahead DONE \n";
			}
			std::cout << " Engine Crew is resting for 1 seconds after tiresome work \n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}

    ~EngineCrew() {};
};

int main() {

    std::cout << "Starting program" << std::endl;

    Cleaners *cleaners = new Cleaners();
    EngineCrew *engineCrew = new EngineCrew();
    
    int user_input;
    std::queue<int> cleaningQueue, engineQueue;
    std::thread cleanerCrew_thread(&Cleaners::cleaningCrewActivity, *cleaners, std::ref(cleaningQueue));
    std::thread engineCrew_thread(&EngineCrew::engineCrewActivity, *engineCrew, std::ref(engineQueue));

    std::string menu = "\n1: clean the ship! \n" 
        "2: move the ship forward! \n"
        "3: stop the ship!\n" 
        "100: quit\n";

    while (true) {
        
        std::cout << menu;
        std::cout << "Enter the captain's order: " << std::endl;
        std::cin >> user_input;

        if (user_input == 1) {     
            cleaningQueue.push(1);            
        } else if (user_input == 2) {
            engineQueue.push(2);
        } else if (user_input == 3){
            engineQueue.push(3);
        } else if (user_input == 100) {
            std::cout << "\nDone!\n" << std::endl;
            cleaningQueue.push(100);
            engineQueue.push(100);
            break;
        } else {
            std::cout << "Invalid input" << std::endl;
        }
    }
    cleanerCrew_thread.join();
    engineCrew_thread.join();
    return 0;
}