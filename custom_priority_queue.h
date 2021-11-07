#include <queue>
#include "Node.h"

using namespace std;
//https://stackoverflow.com/questions/16749723/how-i-can-find-value-in-priority-queue 
//https://stackoverflow.com/questions/19467485/how-to-remove-element-not-at-top-from-priority-queue

template<
    class T,
    class Container = vector<T>,
    class Compare = greater<typename Container::value_type>
> class custom_priority_queue : public priority_queue<T, Container, Compare>
{
public:

    bool find(const T&val) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first!=last) {
            if (*first==val) return true;
            ++first;
        }
        return false;
    };

	bool remove(const T& state){
		auto first = this->c.begin();
		auto last = this->c.end();
		while (first!=last){
			if (*first == state){
				this->c.erase(first);
				return true;
			}
			++first;
		}
		return false;
	}

};