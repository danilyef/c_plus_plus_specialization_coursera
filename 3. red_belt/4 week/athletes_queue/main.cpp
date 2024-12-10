#include <list>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main() {
	std::list<int> athletes;
    std::unordered_map<int,list<int>::iterator> positions;
    std::vector<int> used_positions(100000);
	int Q,num_athl, num_in_front;
	std::cin >> Q;

	for(int i = 0; i< Q; ++i){
		cin >> num_athl >> num_in_front;
        if(used_positions[num_in_front] == 0){
            athletes.push_back(num_athl);
            
            auto last_it = athletes.end();
            --last_it;
            positions[num_athl] = last_it;
            used_positions[num_athl] = 1;

        } else{
            auto pos_list = positions[num_in_front];
            athletes.insert(pos_list,num_athl);
            //cout << "Position new athlete:" << *pos_list << endl;
            //cout << "Position previous athlete:" << *std::prev(pos_list) << endl;
            positions[num_athl] = std::prev(pos_list);
            used_positions[num_athl] = 1;
        }
	}
	for (auto it = athletes.begin(); it != athletes.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

	return 0;
}
