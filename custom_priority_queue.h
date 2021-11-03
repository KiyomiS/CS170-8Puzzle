#include <queue>
#include "Node.h"
//https://stackoverflow.com/questions/16749723/how-i-can-find-value-in-priority-queue 
//https://stackoverflow.com/questions/19467485/how-to-remove-element-not-at-top-from-priority-queue

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class custom_priority_queue : public std::priority_queue<T, Container, Compare>
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

    bool remove(const T& value) {
        auto first = std::find(this->c.begin(), this->c.end(), value);
        if (first != this->c.end()) {
            this->c.erase(first);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
        }
        else {
            return false;
        }
    }

	bool isGreater(const T& state){
		auto first = this->c.begin();
		auto last = this->c.end();
		while (first != last){
			if (*first == state){
				if (*first > state){
					return true;
				}
			}
			++first;
		}
		return false;
	}

};