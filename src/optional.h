#pragma once
#ifndef CATA_SRC_OPTIONAL_H
#define CATA_SRC_OPTIONAL_H

#include <initializer_list>
#include <stdexcept>
#include <type_traits>

#include "cata_assert.h"

namespace cata
{

class bad_optional_access : public std::logic_error
{
    public:
        bad_optional_access() : logic_error( "cata::optional: no value contained" ) { }
};

struct nullopt_t {
    explicit constexpr nullopt_t( int ) {}
};
static constexpr nullopt_t nullopt{ 0 };

struct in_place_t {
    explicit in_place_t() = default;
};
static constexpr in_place_t in_place{ };

template<typename T> // template for optional-class objects.
class optional // the optional class
{
    private:
        using StoredType = typename std::remove_const<T>::type; // stored type...?
        union {
            char dummy; // what is dummy used for?
            StoredType data; // what is this data?
        };
        bool full; // whether or not (something) is full

        T &get() { // templated get method; does a cata_assert and returns the `data` member.
            cata_assert( full );
            return data;
        }
        const T &get() const { // templated get method, though for `const` members.
            cata_assert( full );
            return data;
        }

        template<typename... Args>
        void construct( Args &&... args ) { // construct() does a cata assert, creates a new StoredType, and sets member `full` to True.
            cata_assert( !full );
            new( &data )StoredType( std::forward<Args>( args )... );
            full = true;
        }
        void destruct() { // calls the `data` member's StoredType deconstructor
            data.~StoredType();
        }

    public:
        constexpr optional() noexcept : dummy(), full( false ) { } // optional::optional constructor; what does noexcept do?
        // NOLINTNEXTLINE(google-explicit-constructor)
        constexpr optional( const nullopt_t ) noexcept : dummy(), full( false ) { } // optional::optional constructor that takes a nullopt_t.

        optional( const optional &other ) : full( false ) { // define the constructor with an (optional &other) param. if "other" is full, then call its get() method.
            if( other.full ) {
                construct( other.get() );
            }
        }
        optional( optional &&other ) noexcept : full( false ) { // define the constructor with double-addressed "other" param. if other is full, call construct with the param
            if( other.full ) {                                  // of std::move, and std::move has the param of other.get
                construct( std::move( other.get() ) );
            }
        }
        template<typename... Args> // template w/ args; uses optional constructor, takes an "in_place_t", Args (from template) and a list of args addresses ? come back to this
        explicit optional( in_place_t, Args &&... args ) : data( std::forward<Args>( args )... ),
            full( true ) { }

        template<typename U, typename... Args> // template with typename U. Typename with multiple args. Optional constructor takes an "in_place_t", initializer list "ilist" and args.
        explicit optional( in_place_t, std::initializer_list<U> ilist,
                           Args &&... args ) : data( ilist,
                                       std::forward<Args>( args )... ), full( true ) { }

        template < typename U = T,
                   typename std::enable_if <
                       !std::is_same<optional<T>, typename std::decay<U>::type>::value &&
                       std::is_constructible < T, U && >::value &&
                       std::is_convertible < U &&, T >::value, bool >::type = true >
        // NOLINTNEXTLINE(bugprone-forwarding-reference-overload, google-explicit-constructor)
        optional( U && t )
            : optional( in_place, std::forward<U>( t ) ) { }

        template < typename U = T,
                   typename std::enable_if <
                       !std::is_same<optional<T>, std::decay<U>>::value &&
                       std::is_constructible < T, U && >::value &&
                       !std::is_convertible < U &&, T >::value, bool >::type = false >
        // NOLINTNEXTLINE(bugprone-forwarding-reference-overload)
        explicit optional( U && t )
            : optional( in_place, std::forward<U>( t ) ) { }

        ~optional() {
            reset();
        }

        constexpr const T *operator->() const {
            return &get();
        }
        T *operator->() {
            return &get();
        }
        constexpr const T &operator*() const {
            return get();
        }
        T &operator*() {
            return get();
        }

        constexpr explicit operator bool() const noexcept {
            return full;
        }
        constexpr bool has_value() const noexcept {
            return full;
        }

        T &value() {
            if( !full ) {
                throw bad_optional_access();
            }
            return get();
        }
        const T &value() const {
            if( !full ) {
                throw bad_optional_access();
            }
            return get();
        }

        template<typename O>
        T value_or( O &&other ) const {
            return full ? get() : static_cast<T>( other );
        }

        template<class... Args>
        T &emplace( Args &&... args ) {
            reset();
            construct( std::forward<Args>( args )... );
            return get();
        }
        template<class U, class... Args>
        T &emplace( std::initializer_list<U> ilist, Args &&... args ) {
            reset();
            construct( ilist, std::forward<Args>( args )... );
            return get();
        }

        void reset() noexcept {
            if( full ) {
                full = false;
                destruct();
            }
        }

        optional &operator=( nullopt_t ) noexcept {
            reset();
            return *this;
        }
        optional &operator=( const optional &other ) {
            if( full && other.full ) {
                get() = other.get();
            } else if( full ) {
                reset();
            } else if( other.full ) {
                construct( other.get() );
            }
            return *this;
        }
        optional &operator=( optional &&other ) noexcept {
            if( full && other.full ) {
                get() = std::move( other.get() );
            } else if( full ) {
                reset();
            } else if( other.full ) {
                construct( std::move( other.get() ) );
            }
            return *this;
        }
        template < class U = T,
                   typename std::enable_if <
                       !std::is_same<optional<T>, typename std::decay<U>::type>::value &&
                       std::is_constructible < T, U && >::value &&
                       std::is_convertible < U &&, T >::value, bool >::type = true >
        optional & operator=( U && value ) {
            if( full ) {
                get() = std::forward<U>( value );
            } else {
                construct( std::forward<U>( value ) );
            }
            return *this;
        }
        template<class U>
        optional &operator=( const optional<U> &other ) {
            if( full && other.full ) {
                get() = other.get();
            } else if( full ) {
                reset();
            } else if( other.full ) {
                construct( other.get() );
            }
            return *this;
        }
        template<class U>
        optional &operator=( optional<U> &&other ) {
            if( full && other.full ) {
                get() = std::move( other.get() );
            } else if( full ) {
                reset();
            } else if( other.full ) {
                construct( std::move( other.get() ) );
            }
            return *this;
        }

        void swap( optional &other ) {
            using std::swap;

            if( full && other.full ) {
                swap( get(), other.get() );
            } else if( other.full() ) {
                construct( std::move( other.get() ) );
                other.destruct();
            } else if( full ) {
                other.construct( std::move( get() ) );
                destruct();
            }
        }
};

template<class T, class U>
constexpr bool operator==( const optional<T> &lhs, const optional<U> &rhs )
{
    if( lhs.has_value() != rhs.has_value() ) {
        return false;
    } else if( !lhs ) {
        return true;
    } else {
        return *lhs == *rhs;
    }
}

template< class T, class U >
constexpr bool operator!=( const optional<T> &lhs, const optional<U> &rhs )
{
    return !operator==( lhs, rhs );
}

} // namespace cata

#endif // CATA_SRC_OPTIONAL_H
