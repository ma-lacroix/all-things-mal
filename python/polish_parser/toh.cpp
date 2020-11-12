#include <iostream>
using namespace std; 

// Assuming n-th disk is bottom disk (count down) 
void tower(int n, char sourcePole, char destinationPole, char auxiliaryPole) { 	
    // Base case (termination condition) 
    if(0 == n){
        return; 
    }

    tower(n - 1, sourcePole, auxiliaryPole, destinationPole); 

    cout << "Move the disk "<< n << " from " << sourcePole <<" to "<< destinationPole << endl; 

    tower(n - 1, auxiliaryPole, destinationPole, sourcePole); 
} 

int main() 
{ 
	tower(3, 'S', 'D', 'A'); 	
	return 0; 
} 
