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
    // std::vector<unsigned long> Index = {1,2,3,4,5};
    // std::vector<unsigned long> xIndex = Index;
    // std::vector<std::string> Channels = {"paid","paid","free","free","free"};
    // std::vector<int> Visitors = {450,343,500,234,100};

    // df.load_data(std::move(Index),
    //             std::make_pair("Channels",Channels),
    //             std::make_pair("Visitors",Visitors),
    //             std::make_pair("xIndex",xIndex)
    //             );
      
    // df.write<std::ostream,
    //             unsigned long,
    //             std::string,
    //             int>(std::cout);

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
    
    int channel = df2.get_column<int>("Channel")[0];
    int visitors = df2.get_column<int>("Visitors")[0];


}

int main(){
    
    std::cout << "\nTesting 'Pandas' for C++\n" << std::endl;
    
    // testing_read_csv();
    testing_groupby();

    return 0;
}