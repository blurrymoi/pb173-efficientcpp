#include <vector>
#include <algorithm>
#include <assert.h>

//std::chrono
//time na cmd
//POSIX clock <<
//-O2 optimalizace you want

// something about not repeating values
template <typename T>
class BoundedQueue {
public:
    std::vector<T> _items;
    unsigned _num;

    BoundedQueue(unsigned num)
    : _num(num)
    {
        _items.reserve(_num); //
    }

    void insert(T val)
    {
        unsigned pos = 0;
        while (_items[pos] > val)
            pos++;
        _items.emplace(_items.begin()+pos, val);

        if (_items.size() == _num+1)
            _items.pop_back();        
    }

    T top() {
        assert(!_items.empty());
        return _items[0]; 
    }

    bool empty() { return _items.empty(); }

    T remove() {
        T val = _items[0];
        _items.erase(_items.begin());
        return val;
    }

    size_t size() {
        return _items.size();
    }
};

template <typename T>
class SetQueue {
public:
    std::set<T> _items;
    unsigned _num;

    SetQueue(unsigned num)
    : _num(num) {}

    void insert(T val)
    {
        _items.insert(val);
    }
};
