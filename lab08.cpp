#include <iostream>
#include <string>
using namespace std;

/*******************************************************************************
 * Function prototypes
*******************************************************************************/
// unsigned prevents negative values... so will only be able to store positive values
// This block declares the public functions that the main() calls
unsigned fact(unsigned); // computes the factorial of n(n!) n(n-1)(n-2)(n-3)...
unsigned fib(unsigned); // computes the nth Fibonacci number
unsigned mult(unsigned, unsigned); // Multiplies two numbers using recursion (recursion means a function calls itself)
unsigned power(unsigned, unsigned); // Computes the power of x (x^y) recursively 
unsigned product(unsigned, unsigned); // Computes x * (x+1) * ... * y

// Tail-recursive prototypes(declares the functions)
// The helper functions are declared static so they have internal linkage, which means they are only accessible within this soure file.
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
// In the original cases multiplication happens after recursion returns value, so function takes longer
// In tail recursion, multiplication happens before the recursive calls..  it's the very last thing the function does 

// In the original recursive functions, multiplication occurs after the recursive calls, meaning the function has pending work and must build up a call stack. 
// In the tail recursive version, multiplication happens before the recursive call, and the recursive call is the final operation. 
// This allows the recursion to work more efficieneltly. 
unsigned fact(unsigned n) {
    return factTR(n, 1); // This is first function definition, & its saying "start the helper function with n and an initial accumulator value of 1"
} // multiplying by 1 does not change the value... it keeps value the same initially 

unsigned fib(unsigned n) {
    return fibTR(n, 0, 1); // This is the public Fibonacci function. It calls the tail recursive helper fibTR, and the values...
} // 0 and 1 are the starting Fibonacci numbers. 0 represents F(0) and 1 represents F(1). The helper function shifts these...
// values forward to compute the nth Fibonacci number 

unsigned mult(unsigned x, unsigned y) {
    return multTR(x, y, 0); // The mult function initializes the accumalotor to 0 and calls the tail-recursive helper multYR...
} // Since multiplication is embedded as repeated addition, the accumulator stores the running sum of x added y times. 

unsigned power(unsigned x, unsigned y) {
    return powerTR(x, y, 1); // The power function initiliazes the accumulator to 1 and calls the tail-recursive helper powerTR...
} // The accumulator stores the product as x is multiplied y times. Because the recursive call is the final operation, the implementation is....
// tail recursive 

unsigned product(unsigned x, unsigned y) {
    return productTR(x, y, 1); //function definiton for the product function, which is going to initialize the accumulator to 1
}// this function will give us the product of all the values in between x and y, if the y is greater than x 



// static helper functions
// This function returns the factorial of a # n
static unsigned factTR(unsigned n, unsigned acc) {
    if (n <= 1) return acc; // in the original func. we returned 1 but now we return acc because acc contains the multiplication result
    return factTR(n - 1, acc * n); // Call 1: factTR(3,1), n=3 > 1 so the return statement is executed, and we get factTR(3-1, 1 * 3) = factTR(2, 3),
    // Call 2: factTR(2,3) which becomes factTR(2-1, 3 * 2) = factTR(1, 6). Call 3: factTR(1, 6)... becuz n = 1 we return acc which now equal 6. <-- 3!(factorial of 3) 
}

// This functions computes and returns the nth Fibonacci number
static unsigned fibTR(unsigned n, unsigned a, unsigned b) {
    if (n == 0) return a; // if n = 0, then return the value of a 
    return fibTR(n - 1, b, a + b); // If n is > 0, for ex. Call 1: if n = 3, fibTR will become fibTR(2, 1, 1). Call 2: n=2, a=1, b=1, fibTr now is fibTR(1, 1, 2)....
} // Call 3: n=1, a=1, b=2, so fibTR becomes fibTR(0, 2, 3). Call 4: n=0, a=2, b=3, so fibTR returns 2 because of base case zero rule. 

// returns the product of two numbers: x & y 
static unsigned multTR(unsigned x, unsigned y, unsigned acc) {
    if (y == 0) return acc; // if y=0, then return accumulator value 
    return multTR(x, y - 1, acc + x); // Call 1: (3, 2, 0)... where x=3, y=2, & acc is alr = 0. multTR becomes multTR(3, 1, 3). Call(2): x=3, y=1, acc=3....
} // so multTR becomes multTR(3, 0, 6). Call(3): because y equals zero, base case says we return accumulator, so func returns 6 which is our answer for 3 * 2. 

// returns a product of the power of a number
static unsigned powerTR(unsigned x, unsigned y, unsigned acc) {
    if (y == 0) return acc; // if y = 0, then return accumulator value 
    return powerTR(x, y - 1, acc * x); // Call 1: (2, 3, 1). x=2, y=3, & acc alr is initilaized to 1. For call(1) powerTR will become powerTr(2, 2, 2). 
} // For Call2: x=2, y=2, & acc=2, so then powerTR becomes powerTR(2, 1, 4)/ Call(3): x=2, y=1 & acc=4, so powerTR becomes powerTR(2, 0, 8). 
// For Call4: y=0, and because base case says of y=0 return the accumulator, in Call(4), the accumualotr value of 8 is returned, which is our answer for 2^3. 

// returns the product of all the values in between x and y 
static unsigned productTR(unsigned x, unsigned y, unsigned acc) {
    if (x > y) return acc; // If x > y, then return the value of the accumulator... if x is greater than y initially, the function returns the accumulator which is 1 becuase there r no values betwee x and y to multiply <--- edge case (the function is defined to multiply from x upward to y)
    return productTR(x + 1, y, acc * x); // Call 1: if input is (1, 3, 1), which means x=1, y=3, acc=1, then productTr will become productTr(2, 3, 1).
} // For Call(2): x=2, y=3, acc=1, so productTr(3, 3, 2). For Call(3): x=3, y=3, acc=2, so productTr becomes productTr(4, 3, 6). 
// For Call(4): x=4, y=3, acc=6, because x=4 > y=3, then due to base case the func returns values of accumulator which is 6 <-- 1*2*3=6
































/*
unsigned fact(unsigned n) {
    // base cases (combined)
    if (n <= 1) { // If n is less than or equal to 1, then return the factorial of 0 or 1 as 1 
        return 1;
    }

    // recursive case
    unsigned res = fact(n - 1); // but if n is greater than 1 then, call fat(n-1), which computes the entire factorial of (n-1)
    return res * n; //Call 1: fact(3), res = fact(2), return res * 3; Call 2: fact(2), res = fact(1), return res * 2; Call 3: fact(1),
    this call returns 1; so call 3 returns 1, now we go back to call 2 and return = 1 * 2 = 2, the we go back to call 1 where return = 2 * 3 = 6

    // each call would keep running until res = 1.... after that is only when the multiplication happens in the function 
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
    unsigned res = power(x, y - 1); // calls power(x, y-1), waits for it to finish, then multiplies by x, then returns
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
