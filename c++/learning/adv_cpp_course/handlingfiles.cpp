// simple example how to write files

#include <iostream>
#include <fstream>
#include <string>

std::fstream openFile(std::string f){
    std::fstream outfile;
    outfile.open(f,std::ios::out);
    return outfile;
}

std::fstream readFile(std::string f){
    std::fstream infile;
    infile.open(f,std::ios::in);
    return infile;
}

void writeLines(std::fstream &f, std::string m, int n){
    for(int i {0};i<n;++i){
        f << m << "," << (i+1)*std::rand()%10 << std::endl;
    }
}

int main(){
    std::fstream outfile = openFile("text.txt");
    if(outfile.is_open()){
        writeLines(outfile,"This is amazing",10);
        outfile.close();
    }
    std::fstream infile = readFile("text.txt");
    if(infile.is_open()){
        std::string line;
        while (infile){
            std::getline(infile,line,',');
            int num;
            infile >> num;
            infile >> std::ws;
            std::cout << line << " " << num << std::endl;
        }
    }else{
        std::cout << "can't open file " << std::endl;        
    }
    return 0;
}