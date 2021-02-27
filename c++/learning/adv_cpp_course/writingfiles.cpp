// simple example how to write files

#include <iostream>
#include <fstream>
#include <string>

std::fstream openFile(std::string f){
    std::fstream outfile;
    outfile.open(f,std::ios::out);
    return outfile;
}

void writeLines(std::fstream &f, std::string m, int n){
    for(int i {0};i<n;++i){
        f << "Line " << i+1 << " " << m << std::endl;
    }
}

int main(){
    std::fstream outfile = openFile("text.txt");
    if(outfile.is_open()){
        writeLines(outfile,"This is amazing",10);
        outfile.close();
    }
    return 0;
}