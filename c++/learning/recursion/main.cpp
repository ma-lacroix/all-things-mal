// Using this to write solutions to Leetcode problems

#include <iostream>
#include <vector>

class Solution {
public:

    void sub_eval(std::vector<std::vector<int>> events, int& maxnum, int counter){
        if(events.size()==0){
            return;
        }else{
            ++counter;
            if(counter>maxnum){
                std::cout << counter << " is > " << maxnum << std::endl;
                maxnum = counter;
            }
        std::cout << "\nCounter: " << counter << std::endl;
            for(size_t i {0};i<events.size();++i){
                std::cout << "Checking: " << events.at(i).at(0) << ", " << events.at(i).at(1) << std::endl;
                int start = events.at(i).at(0);
                int end = events.at(i).at(1);
                std::vector<std::vector<int>> sub_events;
                for(size_t j {0};j<events.size();++j){
                    if(start <= events.at(j).at(0) & end<=events.at(j).at(1) & i!=j){
                        std::cout << "Adding: " << events.at(j).at(0) << ", " << events.at(j).at(1) << std::endl;
                        sub_events.push_back(events.at(j));
                    }
                }
                sub_eval(sub_events,maxnum,counter);
            }        
        }
    }

    int maxEvents(std::vector<std::vector<int>>& events) {
        std::sort(events.begin(), events.end());
        int counter = {0};
        int maxnum = {0};
        sub_eval(events,maxnum, counter);
        return maxnum;
    }
};

int main() 
{  
    // std::vector<std::vector<int>> events = {{1,2},{2,3},{3,4},{1,2}};
    std::vector<std::vector<int>> events = {{1,4},{4,4},{2,2},{3,4},{1,1}};
    // std::vector<std::vector<int>> events = {{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7}};
    // std::vector<std::vector<int>> events = {{1,5},{2,4},{3,5},{1,2},{5,6},{5,7},{6,7}};
    Solution sol;
    int solution = sol.maxEvents(events);
    std::cout << "Max number of events: "<< solution << std::endl;
    return 0;
}
