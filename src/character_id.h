#pragma once
#ifndef CATA_SRC_CHARACTER_ID_H
#define CATA_SRC_CHARACTER_ID_H

#include <iosfwd>

class JsonIn;
class JsonOut;

class character_id // character numeric IDs.
{
    public:
        character_id() : value( -1 ) {} // initialize the character id var with a negative int

        explicit character_id( int i ) : value( i ) { // initialize the private value var
        }
        // the id is valid if it is greater than 0
        bool is_valid() const {
            return value > 0;
        }
        // get the character_id value
        int get_value() const { 
            return value;
        }

        character_id &operator++() { // id nonce...?
            ++value; // ++var uses a number var, then increases it after the statement...?
            return *this;
        }

        void serialize( JsonOut & ) const; // serialize for JSON
        void deserialize( JsonIn & ); // deserialize JSON

    private:
        int value; // the ID value
};

inline bool operator==( character_id l, character_id r )
{
    return l.get_value() == r.get_value();
}

inline bool operator!=( character_id l, character_id r )
{
    return l.get_value() != r.get_value();
}

inline bool operator<( character_id l, character_id r )
{
    return l.get_value() < r.get_value();
}

std::ostream &operator<<( std::ostream &o, character_id id );

#endif // CATA_SRC_CHARACTER_ID_H
