#include <vector>
#include <functional> //std::hash
#include <memory> //unique_ptr
#include <stack>

using namespace std;

template < typename Key, typename T >
struct H
{
    decltype( std::hash<Key>{}(T()) ) hash;
    T item;
    std::unique_ptr< H > next = nullptr;

    H( T item ) : item( item ) {
        hash = std::hash< Key >{}( item );
    }
};

template < typename Key, typename T >
class HashLinked {
public:
    using Item = H< Key,T >;
    using Item_UPtr = std::unique_ptr< Item >;

    std::vector< Item_UPtr > items;
    size_t size = 512;
    size_t num_items = 0;

    HashLinked() {
        items.resize( size );
    }

    void insert( T item )
    {
        auto h = std::make_unique< Item >( item );
        insert( std::move( h ) );
    }

    void erase( T item )
    {
        Item h = Item( item );
        Item *current;
        if ( items[h.hash % size] )
        {
            current = items[h.hash % size].get();
            if ( current->hash == h.hash ) {
                items[ h.hash % size ] = std::move( current->next );
                num_items--;
            }
            else
                while( current->next )
                {
                    if ( current->next->hash == h.hash ) {
                        current->next = std::move( current->next->next );
                        num_items--;
                    }
                    else
                        current = (current->next).get();
                }
        }
        if ( (double(num_items)/size) < (1.0/10) )
            rehash();
    }

    Item* find ( T item )
    {
        Item h = Item( item );
        Item* ret;
        if ( !items[h.hash % size] ) 
            return nullptr;
        else
            ret = items[h.hash % size].get();
        do 
        {
            if ( ret && ret->hash == h.hash )
                return ret;
            if ( !ret->next ) 
                return nullptr;
            ret = ret->next.get();
        } while(1);
    }

private:
    void insert( Item_UPtr h )
    {
        size_t index = h->hash % size;
        if ( !items[index] ) {
            items[index] = std::move( h );
        } else {
            Item* place = items[index].get();
            do {
                if ( place && place->item == h->item )
                    return;
                if ( !place->next )
                    break;

                place = place->next.get();
            } while(1);

            place->next = std::move(h);
        }
        num_items++;

        if ( (double(num_items)/size) > (3.0/5) )
            rehash();
    }

    void rehash()
    {
        std::stack< Item_UPtr > to_rehash;

        for( auto& i : items )
            if( i )
                to_rehash.push( move(i) );

        size *= 2;
        items.resize( size );
        num_items = 0;

        while ( !to_rehash.empty() ) {
            Item_UPtr item = std::move( to_rehash.top() ); 
            to_rehash.pop();

            Item_UPtr next = std::move( item );
            Item_UPtr nextnext;

            do {
                if ( next )
                    nextnext = std::move( next->next );
                insert( std::move( next ) );

                if ( !nextnext )
                    break;
                else
                    next = std::move( nextnext );
            } while (1);         
        }
    }
};

enum State { Exists, NotExists, Tombstone };

template < typename Key, typename Value >
class HashProbing {

    struct ItemPair {
        bool exists;
        Value val;
        decltype( std::hash< Key >{}( Value() ) ) hash;

        ItemPair() : exists( false ) {}

        ItemPair( Value v )
            : exists( true ), 
              val( v ), 
              hash( std::hash< Key >{}( v ) ) {}

        ItemPair( const ItemPair& ) = default;
        ItemPair& operator=( ItemPair& ) = default;
        ItemPair& operator=( ItemPair&& ) = default;

        operator bool() {
            return exists;        
        }
    };

public:
    using Item = ItemPair;

    std::vector< Item > items;
    size_t size = 512;
    size_t num_items = 0;

    HashProbing() {
        items.resize( size );
    }

    void insert( Value val )
    { 
        insert( Item( val ) );
    }

    void insert( Item item )
    {
        unsigned index = item.hash % size;
        do {
            if ( !(items[index]) ) {
                items[index] = item;
                break;
            }
            else
                index = (index + 1) % size;
        } while(1);

        num_items++;

        if ( (double(num_items)/size) > (2.0/3) )
            rehash();
    }

    Item find ( Value item )
    {
        auto hash = std::hash< Key >{}( item );
        size_t index = hash % size;
        do {
            if ( items[index] ) {
                if ( items[index].val == item )
                    return items[index];
                else
                    index = (index + 1) % size;
            }
            else
                return Item();
        } while(1);
    }

    void rehash()
    {
        std::stack< Item > to_rehash;

        for( size_t i = 0; i < size; ++i ) {
            if( items[i] ) {
                to_rehash.push( items[i] );
                items[i].exists = false;
            }
        }

        size *= 2;
        items.resize( size );
        num_items = 0;

        while ( !to_rehash.empty() ) {
            Item item = to_rehash.top(); 
            to_rehash.pop();
            insert( item );
        }   
    }
};
