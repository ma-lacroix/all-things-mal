#include <iostream>
#include <string>
#include "DataFrame/DataFrame.h"
#include "DataFrame/GroupbyAggregators.h"
#include <cassert>

typedef hmdf::StdDataFrame<unsigned long> Df;

void testing_read_csv()  {

    Df df;

    df.read("sample_data.csv");
    df.write<std::ostream,unsigned long,std::string,int>(std::cout);
    
    int example1 = df.get_column<int>("Visitors")[0];
    std::cout << "iloc:" << example1 << std::endl;

    std::vector<int> visitors = df.get_column<int>("Visitors");
    for(auto day: visitors){
        std::cout << day << std::endl;
    }
    
}

void testing_groupby() {

    Df df;    

    df.read("sample_data.csv");
    df.write<std::ostream,unsigned long,std::string,int>(std::cout);
                
    const Df df2 = df.groupby<hmdf::GroupbySum,
                        std::string,
                        // unsigned long,
                        std::string,
                        int>(hmdf::GroupbySum(),"Channels");
    df2.write<std::ostream,
                std::string,
                // unsigned long,
                int>(std::cout);
    
    for(int i = 0; i<2; ++i){ // check how to get size of grouped vector
        std::cout << df2.get_column<std::string>("Channels")[i] << " "; 
        std::cout << df2.get_column<int>("Visitors")[i] << " visitors" << std::endl;
    }

}

int main(){
    
    std::cout << "\nTesting 'Pandas' for C++\n" << std::endl;
    
    // testing_read_csv();
    testing_groupby();

    return 0;
}