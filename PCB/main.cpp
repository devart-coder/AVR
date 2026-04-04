#define F_CPU 16000000UL
#include <Nano.h>
#include <Delay.h>
#include <Buffer.h>
using namespace Nano;
int main()
{
    char test_1[] = {'H','e','l','l', 'o', '\0'};
    char test_2[] = {'A','B','C','D','\0'};
    Buffer b1 = Buffer("Hello");
    Buffer b2 = Buffer(test_2);
    // Buffer b3 = Buffer("Test_3");
    // auto test_3 = "    ";
    while(1){

        System.out.print("Test_1: ");
        System.out.print(b1);
        System.out.print(" Size: ");
        System.out.print(b1.size());
        System.out.print(" ");
        System.out.print(" IndexOf 'l': ");
        System.out.print(b1.indexOf('l'));
        System.out.print(" isStartWith \"Hel\": ");
        System.out.print(b1.startWith("Hel"));
        System.out.print(" isStartWith \"Hela\": ");
        System.out.print(b1.startWith("Hela"));
        System.out.println("");
        // System.out.print("Test_2: ");
        // System.out.print(b3);
        // System.out.print(" Set(3,'D'): ");
        // System.out.print(b3);
        // System.out.print(" ");
        // System.out.print(b2);

        delayMs(1000);
    }
    return 0;
}
