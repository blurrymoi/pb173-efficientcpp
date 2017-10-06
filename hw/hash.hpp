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
        //cout << "inserting item " << item << endl;
        auto h = std::make_unique< H<Key,T> >( item );
        insert( std::move( h ) );
    }

    //not fetching item directly so that i can return nullptr
    H<Key,T>* find ( Key hash )
    {
        H<Key,T>* ret;
        if (!items[hash % size]) return nullptr;
        else ret = items[hash % size].get();
        do {
                if ( ret && ret->hash == hash )
                    return ret;
                if ( !ret->next ) 
                    return nullptr;
                ret = ret->next.get();
            } while(1);
    }
private:
    void insert( std::unique_ptr< H<Key,T> > h )
    {
        T val = h->item;//DELETE
        size_t index = h->hash % size;
        if ( !items[index] ) {
            //cout << "wasempty" << endl;
            items[index] = std::move( h );
        } else {
            //cout << "wasnotempty" << endl;
            H< Key,T >* place = items[index].get();
            
            do {
                if ( place && place->item == h->item ) {  
                    //cout << "!items match" << endl;
                    return;
                }
                if ( !place->next ) break;
                place = place->next.get();
            } while(1);

            place->next = std::move(h);
        }

        //cout << "inserted: item - " << val << endl;       
        num_items++;

        //if (ratio.bad) rehash()
        if ( ((float)num_items/size) > ((float)3/5) ) {

            /*
            cout << "** rehashing **" << endl;
            cout << "** num_items => " << num_items << endl;
            cout << "** size => " << size << endl;
            */
            
            size *= 2;
            items.resize( size );
            //printhashy();
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
        //cout << "maybe stacked" << endl;
        //printhashy();

        num_items = 0;
        while ( !stuff_that_needs_rehashing.empty() ) {
            std::unique_ptr< H<Key,T> > item = std::move( stuff_that_needs_rehashing.top() ); 
            stuff_that_needs_rehashing.pop();

            std::unique_ptr< H<Key,T> > next = std::move( item );
            std::unique_ptr< H<Key,T> > nextnext;

            do {
                if (next)
                    nextnext = std::move(next->next);
                insert( std::move( next ) );

                //cout << "post INSERT in REHASH" << endl;
                //printhashy();

                if ( !nextnext )
                    break;
                else
                    next = std::move( nextnext );
                //items.insert(item);
            } while (1);         
        }
    }

public:
    void printhashy()
    {
        cout << "##########" << endl;
        for(size_t i = 0; i < size; ++i) {
            cout << i << ": " << endl;            
            if (!items[i])
                cout << "NULL" << endl;
            else {
                auto h = items[i].get();
                while (h) {
                    cout << "item: " << h->item << endl;
                    cout << "hash: " << h->hash << endl;
                    h = h->next.get();
                }
            }
        }
        cout << "num items :: " << num_items << endl;
        cout << "##########" << endl;
            
    }
};
