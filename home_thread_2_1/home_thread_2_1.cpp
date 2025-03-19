#define _USE_MATH_DEFINES
#include <Windows.h>
#include "Timer.h"
#include<iostream>
#include<thread>
#include<atomic>

typedef enum memory_order {
	memory_order_relaxed,
	//memory_order_consume,
	//memory_order_acquire,
	//memory_order_release,
	//memory_order_acq_rel,
	//memory_order_seq_cst,
} memory_order;


using namespace std;

void func1(atomic<int>& count, atomic<int>& max_client) {
	while (count != max_client) {
		this_thread::sleep_for(1s);
		consol_parameter::SetColor(15, 0);
		cout << "client " << count.operator++() << " " << endl;
		
	}
}

void func2(atomic<int>& count, atomic<int>& max_client) {
	atomic<int>val{};
	while (!(count == 0 && val == 1)) {
		this_thread::sleep_for(2s);
		consol_parameter::SetColor(10, 0);
		if (count == max_client) val.store(1);
		cout << "operation " << count.operator--() << " " << endl;
	}
}

int main() {
	atomic<int> count;
	atomic<int> max_client;
	max_client.store(5);
	thread t1(func1, ref(count), ref(max_client));
	thread t2(func2, ref(count), ref(max_client));
	t1.join();
	t2.join();
	return EXIT_SUCCESS;
}