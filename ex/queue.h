#include <vector>
#include <set>
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
        if (!empty())
        {
            // std::lower_bound; std::upper_bound -- binary search
            while (pos < size() && _items[pos] > val)
                pos++;
            if (pos < _num && _items[pos] == val)
                return;
        }
        _items.emplace(_items.begin()+pos, val);

        if (_items.size() == _num+1)
            _items.pop_back();        
    }

    T top() {
        assert(!empty());
        return _items[0]; 
    }

    bool empty() {
        return _items.empty();
    }

    T remove() {
        T val = _items[0];
        _items.erase(_items.begin());
        return val;
    }

    size_t size() {
        return _items.size();
    }
};

//std::set is a Red-Black tree internally, "sorted"
template <typename T>
class SetQueue {
public:
    std::set< T, std::greater<T> > _items;
    unsigned _num;

    SetQueue(unsigned num)
    : _num(num) {}

    void insert(T val)
    {
        _items.insert(val);

        if (_items.size() == _num+1)
            _items.erase(std::prev(_items.end()));
    }

    T top() {
        assert(!empty());
        return *_items.begin();
    }

    bool empty() {
        return _items.empty();
    }

    T remove() {
        T val = top();
        _items.erase(_items.begin());
        return val;
    }

    size_t size() {
        return _items.size();
    }
};

