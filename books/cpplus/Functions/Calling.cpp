// Calling.cpp -- defining, prototyping, and calling a function

#include <iostream>

void Simple(); // function prototype

int main(void)
{
    using namespace std;
    cout << "main() will call the simple() function:\n";
    Simple();  // function call
    cout << "main() is finished with the simple() function.\n";
    return 0;
}

// function definition
void Simple()
{
    using namespace std;
    cout << "I'm but a simple function.\n";
}
