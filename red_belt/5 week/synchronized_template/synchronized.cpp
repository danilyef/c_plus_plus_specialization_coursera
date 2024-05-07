#include "test_runner.h"

#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;


template <typename T>
class Synchronized {
public:
	explicit Synchronized(T initial = T()): value(std::move(initial)){};

	struct Access {
		Access(T& value,mutex& m): ref_to_value(value), lock(m){};
		~Access(){};
		T& ref_to_value;
		lock_guard<mutex> lock;
	};

	Access GetAccess(){
		return {value,m};
	};
	
private:
	T value;
	mutex m;
};

void TestConcurrentUpdate() {
	Synchronized<string> common_string;

	const size_t add_count = 50000;
	auto updater = [&common_string, add_count] {
	for (size_t i = 0; i < add_count; ++i) {
		auto access = common_string.GetAccess();
		access.ref_to_value += 'a';
		}
	};

	auto f1 = async(updater);
	auto f2 = async(updater);

	f1.get();
	f2.get();

	ASSERT_EQUAL(common_string.GetAccess().ref_to_value.size(), 2 * add_count);
	}

vector<int> Consume(Synchronized<deque<int>>& common_queue) {
	vector<int> got;

	for (;;) {
		deque<int> q;

		{
			// We intentionally enclosed these two lines in curly braces to
			// reduce the size of the critical section. The consumer thread acquires
			// the mutex, moves all the contents of the shared queue into its
			// local variable, and releases the mutex. After that, it processes
			// the objects in the queue outside the critical section, allowing
			// the producer thread to concurrently place new objects into the queue.
			//
			// The size of the critical section significantly affects the performance
			// of multithreaded programs.
			auto access = common_queue.GetAccess();
			q = std::move(access.ref_to_value);
		}

		for (int item : q) {
			if (item > 0) {
			got.push_back(item);
			} else {
			return got;
			}
		}
	}
}


void TestProducerConsumer() {
	Synchronized<deque<int>> common_queue;

	auto consumer = async(Consume, ref(common_queue));

	const size_t item_count = 100000;
	for (size_t i = 1; i <= item_count; ++i) {
	common_queue.GetAccess().ref_to_value.push_back(i);
	}
	common_queue.GetAccess().ref_to_value.push_back(-1);

	vector<int> expected(item_count);
	iota(begin(expected), end(expected), 1);
	ASSERT_EQUAL(consumer.get(), expected);
}


int main() {
	TestRunner tr;
	RUN_TEST(tr, TestConcurrentUpdate);
	RUN_TEST(tr, TestProducerConsumer);
}
