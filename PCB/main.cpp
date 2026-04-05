#define F_CPU 16000000UL
#include <Nano.h>
#include <Delay.h>
#include <Buffer.h>
using namespace Nano;
int main()
{
    char test_1[] = {'A','B','C','D','\0'};
    // Buffer b1 = Buffer(test_1);
    // Buffer<uint16_t, 16> b2 = Buffer<uint16_t, 16>("");
    while(1){
        // System.out.print("Test_1: ");
        // System.out.print(b1);
        // System.out.print(" Size: ");
        // System.out.print(b1.size());
        // System.out.print(" ");
        // System.out.print(" IndexOf 'l': ");
        // System.out.print(b1.indexOf('l'));
        // System.out.print(" isStartWith \"Hel\": ");
        // System.out.print(b1.startWith("Hel"));
        // System.out.print(" isStartWith \"Hela\": ");
        // System.out.print(b1.startWith("Hela"));
        // System.out.print(" replace('A','a'): ");
        // System.out.print(b1.replace('A','a'));
        // System.out.print(" replaceIf(): ");
        // System.out.print(b1.replaceIf([](char c){ return c=='B';},'b'));
        // System.out.print(" set(2,'c'): ");
        // System.out.print(b1.set(2,'c'));
        // System.out.print(" capacity: ");
        // System.out.print(b1.capacity());
        // System.out.print(" set(10,'c'): ");
        // System.out.print(b1.set(2,'c'));
        // System.out.println("");

        // System.out.print("Test_2: ");
        // System.out.print(b2);
        // System.out.print(" capacity(): ");
        // System.out.print(b2.capacity());
        // System.out.print(" isEmpty(): ");
        // System.out.print(b2.isEmpty());
        // System.out.println(" ");

        delayMs(1000);
    }
    return 0;
}
