#include <iostream>
#include <cstdlib>

bool isPrime(size_t n) {
        
	for(size_t i = 2; i < n; i++) {
	    if ( n % i == 0 )
		return false; 
	}
	return true;
}

int main( int argc, char *argv[] )  {

    size_t n = atoi(argv[1]);
    size_t num = 1;
    size_t prime = 2;

    for( size_t i = 3; num < n; i++ ) {
        if (isPrime(i)) {
            num++;
            prime = i;
        }
    }

    std::cout << prime << '\n';
    return 0;
}
