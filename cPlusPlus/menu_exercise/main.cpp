// Section 9 - Challenge - Build a menu that can manage a list of integers
// Author: Marc-Antoine Lacroix

#include <iostream>
#include <string>
#include <vector>

using namespace std;

char display_options() {
// this function displays the menu options
    
    string menu_options [7] = {"P - Print numbers","A - Add a number","M - Display mean of the numbers",\
                            "S - Display the smallest number","L - Display the largest number","Q - Quit \n",\
                            "\nPlease make your choice: "};

    for (int i = 0;i < sizeof(menu_options)/sizeof(menu_options[0]); ++i) {
        cout << menu_options[i] << endl;
    }
    char choice;
    cin >> choice;

    return choice;
}

int add_number(vector<int> &vec) {
// this function adds a number to the list

    int new_number = 0;
    cout << "\nPlease enter a new number: ";
    cin >> new_number;
    vec.push_back(new_number);

    return 0;
}

int print_numbers(vector<int> &vec) {
// this function prints the list

    int i = 0;
    cout << "\n[ ";
    while (i<vec.size()){
        cout << vec.at(i) << " ";
        i++;
    }
    cout << "]\n";

    return 0;
}

int calc_average(vector<int> &vec) {
// this function calculates the avg value of the list

    int total = 0;
    int length = vec.size();
    int i = 0;
    float avg = 0.0;
    while (i<length){
        total+=vec.at(i);
        i++;
    }
    avg = static_cast<float>(total/length);
    cout << "\nThe average number is: " << avg << endl;

    return 0;

}

int smallest_num(vector<int> &vec) {
// this function returns the smallest number of the list
    
    int smallest = vec.at(0);
    int length = vec.size();
    int i = 0;
    while (i<length){
        if (smallest > vec.at(i)) {
            smallest = vec.at(i);
        }
        i++;
    }
    cout << "\nThe smallest number is: " << smallest << endl;
    return 0;
}

int largest_num(vector<int> &vec) {
// this function returns the highest number of the list
    
    int largest = vec.at(0);
    int length = vec.size();
    int i = 0;
    while (i<length){
        if (largest < vec.at(i)) {
            largest = vec.at(i);
        }
        i++;
    }
    cout << "\nThe largest number is: " << largest << endl;
    return 0;
}

int main() {
    
    vector<int> vec;
    char selection;

    cout << "\nWelcome! " << endl;

    do {
        selection = toupper(display_options());
        cout << "\nYou have selected: " << selection << endl;
        if (selection=='A') {
            add_number(vec);
        }
        else if (selection=='P') {
            print_numbers(vec);
        }
        else if (selection=='M') {
            calc_average(vec);
        }
        else if (selection=='S') {
            smallest_num(vec);
        }
        else if (selection=='L') {
            largest_num(vec);
        }
        else {
            cout << "\nPlease enter a valid choice." << endl;
        }

    } while (selection!='Q');
        
    return 0;
}

