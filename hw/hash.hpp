/* 
    Hash tables
    methods: insert(Value), find(Key)    
    a) linked-list buckets
    b) linear probing and rehashing
    -- compare w/ std::set and std::unordered_set
    -- bonus: beat std::unordered_set by > 10% 
*/

#include <vector>
#include <functional> //std::hash
#include <memory> //unique_ptr
#include <iostream> //DELETE
#include <stack>

using namespace std;

template < typename Key, typename T >
struct H
{
    decltype( std::hash<Key>{}(T()) ) hash;
    T item;
    std::unique_ptr< H > next = nullptr;

    H(T item) : item(item) {
        hash = std::hash< Key >{}(item);
    }
};


template < typename Key, typename T >
class HashLinked {
public:
    std::vector< std::unique_ptr< H< Key,T > > > items;
    size_t size = 2;//512;
    size_t num_items = 0;

    HashLinked() {
        items.resize(size);
    }

    void insert( T item )
    {
        cout << "inserting item " << item << endl;
        auto h = std::make_unique< H<Key,T> >( item );
        cout << "h.item " << h->item << endl;

        insert( h );
    }
private:
    void insert( std::unique_ptr< H<Key,T> >& h )
    {
        //place free        
        if ( !items[h->hash % size] ) {
            items[h->hash % size] = std::move(h);
        } else {
            H< Key,T >* place = items[h->hash % size].get();
            while( place->next ) {
                if ( place->item == h->item ) { //"set"
                    cout << "!items match" << endl;
                    return;
                }
                place = place->next.get();
            }
            place->next = std::move(h);
        }

        cout << "inserted: item - " << h->item << endl;       
        num_items++;

        //if (ratio.bad) rehash()
        if ( (num_items/size) > (2/3) ) {
            size *= 2;
            items.resize( size );
            rehash();
        }
    }

    void rehash()
    {
        std::stack< std::unique_ptr< H<Key,T> > > stuff_that_needs_rehashing;

        //eh
        for( auto& i : items ){
            if( i ) {
                stuff_that_needs_rehashing.push( move(i) );
            }
        }

        while ( !stuff_that_needs_rehashing.empty() ) {
            std::unique_ptr< H<Key,T> > item = std::move( stuff_that_needs_rehashing.top() ); 
                       stuff_that_needs_rehashing.pop();
            do {
                insert( item );
                std::unique_ptr< H<Key,T> > item = std::move(item->next);
                //items.insert(item);
            } while (item);         
        }
    }
};
