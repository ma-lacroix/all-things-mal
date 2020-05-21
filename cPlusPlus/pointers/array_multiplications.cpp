// exercise: create 2 arrays in the heap and multiply each element from the first one with the second

#include <iostream>

using namespace std;

int *gen_array(size_t size) {
// generates an array with random values
    int *heap_storage = nullptr;
    heap_storage = new int[size];
    for (size_t i = 0; i < size; ++i) {
        *(heap_storage+i) = rand() % 30;
    }
    return heap_storage;
}

void display_array(int *ar, size_t size) {
// displays the array elements
    for (size_t i=0;i<size;++i){
        cout << ar[i] << " ";
    }
    cout << endl;
}

void *apply_all(int *ar1, size_t size1, int *ar2, size_t size2) {
// multiplies each element from the first array with the second
    size_t final_size = size1*size2;
    int *final_array = nullptr;
    int k = 0;
    final_array = new int[final_size];

    for (size_t i = 0;i<size1;++i) {
        for (size_t j = 0;j<size2;++j) {
            final_array[k] = ar1[i]*ar2[j];
            k+=1;
        }
    }

    display_array(final_array,final_size);
    return 0;
}

int main () {

    size_t size1,size2;
    int *array1,*array2,*array3 = nullptr; 
    cout << "Enter the first and second array sizes seperated by a space: ";
    cin >> size1;
    cin >> size2;
    if (size1 > 0 & size2 > 0) {
        array1 = gen_array(size1);
        array2 = gen_array(size2);
        cout << "The first array is: " << endl;
        display_array(array1,size1);
        cout << "The second array is: " << endl;
        display_array(array2,size2);

        cout << "The multiplication results are: " << endl;
        apply_all(array1,size1,array2,size2);
    }
    else {
        cout << "Please try again." << endl << endl;
    }

    return 0;
}
