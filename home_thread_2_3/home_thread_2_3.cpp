#define _USE_MATH_DEFINES
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <windows.h>
#include <vector>

using namespace std;


class Data {
public:
    Data(int a1, double b1, string s1) {a = a1; b = b1; s = s1;};
    mutex m;
    int a{};
    double b{};
    string s{};
};

void swap1(Data& x, Data& y) {

    int temp_a{};
    double temp_b{};
    string temp_s{};
    x.m.lock();
    y.m.lock();

    temp_a = x.a;
    x.a = y.a;
    y.a = temp_a;

    temp_b = x.b;
    x.b = y.b;
    y.b = temp_b;

    temp_s = x.s;
    x.s = y.s;
    y.s = temp_s;

    x.m.unlock();
    y.m.unlock();
}

void swap2(Data& x, Data& y) {

    scoped_lock L{x.m, y.m};

    int temp_a{};
    double temp_b{};
    string temp_s{};

    temp_a = x.a;
    x.a = y.a;
    y.a = temp_a;

    temp_b = x.b;
    x.b = y.b;
    y.b = temp_b;

    temp_s = x.s;
    x.s = y.s;
    y.s = temp_s;
}

void swap3(Data& x, Data& y) {

    unique_lock<mutex> l(x.m);
    unique_lock<mutex> l1(y.m);
    int temp_a{};
    double temp_b{};
    string temp_s{};

    temp_a = x.a;
    x.a = y.a;
    y.a = temp_a;

    temp_b = x.b;
    x.b = y.b;
    y.b = temp_b;

    temp_s = x.s;
    x.s = y.s;
    y.s = temp_s;
    l.unlock();
    l1.unlock();

}


int main(){

    Data x1(1, 2.4, "e");
    Data y1(4, 3.4, "p");

    thread t1(swap1,ref(x1), ref(y1));  
    thread t2(swap1, ref(x1), ref(y1));
    thread t3(swap2, ref(x1), ref(y1));
    thread t4(swap2, ref(x1), ref(y1));
    thread t5(swap3, ref(x1), ref(y1));
    thread t6(swap3, ref(x1), ref(y1));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    cout << y1.a << endl;
    return EXIT_SUCCESS;

}

