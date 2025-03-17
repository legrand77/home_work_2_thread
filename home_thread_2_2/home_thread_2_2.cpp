
#include <iostream>
#include<thread>
#include <chrono>
#include <mutex>
#include <windows.h>
#include <vector>

using namespace std;

mutex m;

void drawROWprogress(int x, int y) {
    this_thread::sleep_for(100ms);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    char p(219);
    char p1(220);
    int progress{0}; 
    auto start = chrono::high_resolution_clock::now();
     do{   
        int pos{};
        COORD position = {x, y}; 
        SetConsoleCursorPosition(hConsole, position); 
        unique_lock<mutex> l(m);
        this_thread::sleep_for(100ms);
        int barWidth = 50; 
        pos = (barWidth * progress)/100; 
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) cout << p;
            else if (i == pos) cout << p1;
            else cout << " ";
        } 
        cout <<  progress << " % ";
        COORD position1 = { x, y };
        SetConsoleCursorPosition(hConsole, position1);
        progress+=5;
        this_thread::sleep_for(10ms);
        l.unlock();
     } while (progress < 101); 
     COORD position1 = {x+70, y };
     SetConsoleCursorPosition(hConsole, position1);
     auto end = chrono::high_resolution_clock::now();
     chrono::duration<double> time = end-start;
     cout << time.count() << " s " << endl;
     COORD position = {x, y };
     SetConsoleCursorPosition(hConsole, position); 
};


int main()
{
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    vector<thread> T; 
    int N{10};
    cout << "#" << "    #id " << "                         Progress Bar"  << "                        %   "<<"                 time ";
    for (size_t i = 0; i < N; i++) {
        T.push_back(thread(drawROWprogress, 18, i+1));
        COORD position = {0, i+1};
       SetConsoleCursorPosition(hConsole, position);
        cout  << i+1 << " #id = " << T[i].get_id();
    }; 
    for (auto &i : T) {
        i.join();
    };
    COORD position = { 0, N+1 };
    SetConsoleCursorPosition(hConsole, position);
    return EXIT_SUCCESS;
}
