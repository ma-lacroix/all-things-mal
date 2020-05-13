// Text pyramid challenge - user enters a string, which is then mirrored and printed in a pyramid format
// WIP

#include <iostream>
#include <string>

using namespace std;

// +----------- Globals -----------+

// +----------- Functions -----------+

// string enter_word() {
//     string message;
//     cout << "Enter a message: ";
//     cin >> message;
//     return message
// }

// string get_full_word(string message) {
// }

// string loop_mirror (string full_word) {
// }

int main () {
// work in progress - testing basic string logic

    string message;
    string inverted;

    cout << "Enter a message: ";
    cin >> message;
    int mes_len = message.length()-1;

    for (size_t i = 0; i < mes_len ; ++i) {
        char letter = message.at(mes_len-i);
        inverted.push_back(letter);
    }
    
    string full_word = message + inverted;
    int full_len = full_word.length()-1;

    cout << full_word << endl;

    for (size_t i = 0; full_len-(i*2) > 0; i++) {
        
        full_word.replace(i,1," ");
        full_word.replace(full_len-i,1," ");
        cout << full_word << endl;
    }

    // cout << full_word.begin() << " " << full_word.end() << endl;

    return 0;
}