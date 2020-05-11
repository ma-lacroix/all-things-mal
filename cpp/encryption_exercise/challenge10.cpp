// Section 10
// Challenge - Substitution cipher using simple strings

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// ---- globals ----- //
string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
string key  = "0987654321XZNLWEBGJHQDYVTKFUOMPCIASRxznlwebgjhqdyvtkfuompciasr";

// ---- functions ----- //
string encrypt_message(string message, string alphabet, string key) {
// encrypts a message based of string array in main()

    string to_encrypt;
    for (size_t i = 0; i < message.length(); ++i) {
        int pos = 0;
        pos = alphabet.find(message.at(i));
        if (pos != -1) {
            to_encrypt.push_back(key.at(pos));
        } else {
            to_encrypt.push_back(message.at(i));
        }
        
    }

    cout << "\nEncrypted message: " << to_encrypt << endl;
    return to_encrypt;
}

string decrypt_message(string message, string alphabet, string key) {
// decrypts a message based of string array in main()

    string encrypted;
    for (size_t i = 0; i < message.length(); ++i) {
        int pos = 0;
        pos = key.find(message.at(i));
        if (pos != -1) {
            encrypted.push_back(alphabet.at(pos));
        } else {
            encrypted.push_back(message.at(i));
        }
        
    }

    cout << "\nDecrypted message: " << encrypted << "\n" << endl;
    return encrypted;
}

int main() {
    
    string message;
    string encrypted;
    cout << "Enter a message: " << endl;
    getline(cin,message);

    encrypted = encrypt_message(message,alphabet,key);
    decrypt_message(encrypted,alphabet,key);
        
    return 0;
}

