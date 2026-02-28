#include <iostream>
#include <string>
using namespace std;

/*******************************************************************************
 * Function prototypes
*******************************************************************************/

unsigned fact(unsigned);
unsigned fib(unsigned);
unsigned mult(unsigned, unsigned);
unsigned power(unsigned, unsigned);
unsigned product(unsigned, unsigned);

//Added tail-recursive prototypes 
static unsigned factTR(unsigned, unsigned);
static unsigned fibTR(unsigned, unsigned, unsigned);
static unsigned multTR(unsigned, unsigned, unsigned);
static unsigned powerTR(unsigned, unsigned, unsigned);
static unsigned productTR(unsigned, unsigned, unsigned);

/*******************************************************************************
 * Description:
 * Starting point of the program. Calls various recursive functions that can be
 * optimized using tail recursion.
 * 
 * Input:
 * N/A
 *
 * Output:
 * An integer to signal to the OS the exit code.
*******************************************************************************/

int main() {
    // try a ridiculous case that won't work without tail recursion
    cout << "6 * 123000 = " << mult(6, 123000) << endl;
    
    // these functions can't demonstrate the usefulness of tail recursion
    // due to data type overflow, but still, good practice
    cout << "3 ^ 10 = " << power(3, 10) << endl;
    cout << "8 * 9 * ... * 15 = " << product(8, 15) << endl;
    cout << "10! = " << fact(10) << endl;

    // without tail recursion, this next call is going to take a while
    cout << "50th Fibonacci number is " << fib(50) << endl;

    // terminate
    return 0;
}

/*******************************************************************************
 * Function definitions below are NOT tail recursive!
 * TODO: make them tail recursive :)
*******************************************************************************/

unsigned fact(unsigned n) {
    return factTR(n, 1);
}

unsigned fib(unsigned n) {
    return fibTR(n, 0, 1);
}

unsigned mult(unsigned x, unsigned y) {
    return multTR(x, y, 0);
}

unsigned power(unsigned x, unsigned y) {
    return powerTR(x, y, 1);
}

unsigned product(unsigned x, unsigned y) {
    return productTR(x, y, 1);
}





static unsigned factTR(unsigned n, unsigned acc) {
    if (n <= 1) return acc;
    return factTR(n - 1, acc * n);
}

static unsigned fibTR(unsigned n, unsigned a, unsigned b) {
    if (n == 0) return a;
    return fibTR(n - 1, b, a + b);
}

static unsigned multTR(unsigned x, unsigned y, unsigned acc) {
    if (y == 0) return acc;
    return multTR(x, y - 1, acc + x);
}

static unsigned powerTR(unsigned x, unsigned y, unsigned acc) {
    if (y == 0) return acc;
    return powerTR(x, y - 1, acc * x);
}

static unsigned productTR(unsigned x, unsigned y, unsigned acc) {
    if (x > y) return acc;
    return productTR(x + 1, y, acc * x);
}
















/*
unsigned fact(unsigned n) {
    // base cases (combined)
    if (n <= 1) {
        return 1;
    }

    // recursive case
    unsigned res = fact(n - 1);
    return res * n;
}

unsigned fib(unsigned n) {
    // base case 1
    if (n == 0) {
        return 0;
    }

    // base case 2
    else if (n == 1) {
        return 1;
    }

    // recursive case
    return fib(n - 1) + fib(n - 2);
}

unsigned mult(unsigned x, unsigned y) {
    // base case
    if (y == 0) {
        return 0;
    }

    // recursive case
    unsigned res = mult(x, y - 1);
    return res + x;
}

unsigned power(unsigned x, unsigned y) {
    // base case
    if (y == 0) {
        return 1;
    }

    // recursive case
    unsigned res = power(x, y - 1);
    return res * x;
}

unsigned product(unsigned x, unsigned y) {
    // base case
    if (x == y) {
        return x;
    }

    // recursive case
    unsigned p = product(x + 1, y);
    return p * x;
}
*/ 
