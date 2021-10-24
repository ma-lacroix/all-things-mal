class Solution {
public:
    
    std::map<int,int> inv;
        
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> solu;
        for(size_t i {0};i<nums.size();++i){
            inv[nums.at(i)]+=1;
        }
        
        std::map<int, int>::iterator it;
        for (it = inv.begin(); it != inv.end(); it++){
            std::map<int, int>::iterator it2;
            for(it2 = std::next(it);it2 != inv.end();it2++){
                std::map<int, int>::iterator it3;
                for(it3 = std::next(it2);it3 != inv.end();it3++){
                    if(it->first+it2->first+it3->first == 0){
                        solu.push_back({it->first,it2->first,it3->first});
                    }
                }
            }
            if(it->second>=2){
                std::map<int, int>::iterator it4;
                int key = (it->first*2)*(-1);
                if(key!=-key){
                    for(it4 = inv.find(key);it4!=inv.end();it4++){
                            solu.push_back({it->first,it->first,it4->first});
                            break;
                    }   
                }
            }
        }
        
        if(inv[0]>2){
            std::vector<int> temp {0,0,0};
            solu.push_back(temp);
        }
        
        return solu;
    }
};
