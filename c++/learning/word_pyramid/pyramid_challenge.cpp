// Text pyramid challenge - user enters a string, which is then mirrored and printed in a pyramid format
// WIP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// +----------- Globals -----------+

string message;
string full_word;
vector<string> mirror;

// +----------- Functions -----------+

string enter_word() {
// takes in a basic string message
    string message;
    cout << "Enter a message: ";
    cin >> message;
    cout << "\n" << endl;
    return message;
}

string get_full_word(string message) {
// takes a string and mirrors it

    string inverted;
    int mes_len = message.length()-1;

    for (size_t i = 0; i < mes_len ; ++i) {
        char letter = message.at(mes_len-i);
        inverted.push_back(letter);
    }
    
    string full_word = message + inverted;
    return full_word;
}

vector<string> loop_mirror (string full_word) {
// creates a loop string vector

    vector <string> mirror;
    int full_len = full_word.length()-1;
    mirror.push_back(full_word);
    for (size_t i = 0; full_len-(i*2) > 0; i++) {
        full_word.replace(i,1," ");
        full_word.replace(full_len-i,1," ");
        mirror.push_back(full_word);
    }
    return mirror;
}

string pyramid (vector<string> mirror){
// prints out the pyramid-style message

    int mirror_size = mirror.size();
    
    for (size_t i=1; mirror_size-i>0; ++i) {
        int pos = mirror_size-i;
        cout << mirror.at(pos) << endl;
    }
    cout << mirror.at(0) << "\n"<< endl;

    return "";
}

int main () {
// work in progress - testing basic string logic

    message = enter_word();
    full_word = get_full_word(message);
    mirror = loop_mirror(full_word);
    pyramid(mirror);

    cout << "Program terminated" << endl;

    return 0;
}