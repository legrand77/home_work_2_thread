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
    lock(x.m, y.m);
    lock_guard<mutex> l(x.m, adopt_lock);
    lock_guard<mutex> l1(y.m, adopt_lock);
    x.a += y.a;
    y.a = x.a - y.a;
    x.a = x.a - y.a;
    x.b += y.b;
    y.b = x.b - y.b;
    x.b = x.b - y.b;
    swap(x.s, y.s);

    cout << endl << "ThreadId: " << this_thread::get_id() << ". after: " __FUNCTION__ << endl;
    cout << "value_ = " << x.s << ";" << endl;
    cout << "value_ = " << y.s << ";" << endl;
}

void swap2(Data& x, Data& y) {

    scoped_lock L{x.m, y.m};

    x.a += y.a;
    y.a = x.a - y.a;
    x.a = x.a - y.a;
    x.b += y.b;
    y.b = x.b - y.b;
    x.b = x.b - y.b;
    swap(x.s, y.s);

    cout << std::endl << "ThreadId: " << this_thread::get_id() << ". after: " __FUNCTION__ << endl;
    cout << "value_ = " << x.s << ";" << endl;
    cout << "value_ = " << y.s << ";" << endl;


}

void swap3(Data& x, Data& y) {

    unique_lock<mutex> l(x.m, defer_lock);
    unique_lock<mutex> l1(y.m, defer_lock);
    lock(l, l1);
    x.a += y.a;
    y.a = x.a - y.a;
    x.a = x.a - y.a;
    x.b += y.b;
    y.b = x.b - y.b;
    x.b = x.b - y.b;
    swap(x.s, y.s);

    cout << std::endl << "ThreadId: " << this_thread::get_id() << ". after: " __FUNCTION__ << endl;
    cout << "value_ = " << x.s << ";" << endl;
    cout << "value_ = " << y.s << ";" << endl;


}


int main(){

    Data x1(1, 2.4, "eee");
    Data y1(4, 3.4, "ppp");

    thread t1(swap1,ref(x1), ref(y1));  
    thread t2(swap2, ref(x1), ref(y1));
    thread t3(swap3, ref(x1), ref(y1));

    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;

}

