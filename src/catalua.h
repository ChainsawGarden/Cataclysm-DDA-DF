#pragma once
#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wunused-function" // ignores the function
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant" // should fix linux errors


#ifndef CATALUA_H
#define CATALUA_H

#include <list>
#include <sstream>
#include <string>

// modern addition: extern C for properly importing these lua libs.
extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
} // add lua libs


#include "creature.h"
#include "character_id.h"
#include "enums.h"
#include "iuse.h"
#include "int_id.h"
#include "item.h"
#include "type_id.h"


// modern additions
#include "weather_type.h" // for weather typing stuff
#include "string_input_popup.h" // for string input
#include "item_factory.h" // for item factory stuff
#include "monstergenerator.h" // for mongen stuff
#include "ui.h" // for ui stuff
#include "calendar.h" // for calendar / time based stuff
#include "coordinates.h" // for coords / positions / location based stuff
#include "overmap.h" // for overmap class and stuff
#include "omdata.h" // for overmap data

// callback arg types
enum CallbackArgumentType : int {
    Integer,
    Number,
    Double = Number,
    Float = Number,
    Boolean,
    String,
    Tripoint,
    Item,
    Reference_Creature,
    Enum_BodyPart, // bodypart Enum
    Id_BodyPart, // bodypart ID
    Character_Id,
    Weather_Id
};
// callback args
struct CallbackArgument {
    CallbackArgumentType type;

    int value_integer;
    float value_number;
    bool value_boolean;
    std::string value_string;
    tripoint value_tripoint;
    item value_item;
    Creature *value_creature;
    body_part value_body_part; // is value body part modern?
    const int_id<body_part_type> value_body_part_id; // value body part id is modern
    character_id value_character_id; // value character is modern
    weather_type_id value_weather_id; // value weather is modern 

    // the below `CallbackArgument` "things" are constructors with various overloads.
    // The weird syntax spooked me, but rest assured, ":type(xyz)" & ":value_integer(xyz)" initialize private variables.
    CallbackArgument( int arg_value ) :
    //CallbackArgument( character_id arg_value ) :
        type( CallbackArgumentType::Integer ), value_integer( arg_value ) {
    }
    CallbackArgument( double arg_value ) :
    //CallbackArgument( character_id arg_value ) :
        type( CallbackArgumentType::Number ), value_number( arg_value ) {
    }
    CallbackArgument( float arg_value ) :
    //CallbackArgument( character_id arg_value ) :
        type( CallbackArgumentType::Number ), value_number( arg_value ) {
    }
    CallbackArgument( bool arg_value ) :
    //CallbackArgument( character_id arg_value ) :
        type( CallbackArgumentType::Boolean ), value_boolean( arg_value ) {
    }
    CallbackArgument( const std::string &arg_value ) :
    //CallbackArgument( character_id arg_value ) :
        type( CallbackArgumentType::String ), value_string( arg_value ) {
    }
    CallbackArgument( const tripoint &arg_value ) :
    //CallbackArgument( character_id arg_value ) :
        type( CallbackArgumentType::Tripoint ), value_tripoint( arg_value ) {
    }
    CallbackArgument( const item &arg_value ) :
    //CallbackArgument( character_id arg_value ) :
        type( CallbackArgumentType::Item ), value_item( arg_value ) {
    }
    CallbackArgument( Creature *&arg_value ) :
    //CallbackArgument( character_id arg_value ) :
        type( CallbackArgumentType::Reference_Creature ), value_creature( arg_value ) {
    }
    CallbackArgument( const body_part &arg_value ) : // Bodypart enums.
        type( CallbackArgumentType::Enum_BodyPart ), value_body_part( arg_value ) {
    }
    CallbackArgument( const int_id<body_part_type> arg_value) : // Bodypart ID
        type( CallbackArgumentType::Id_BodyPart ), value_body_part_id( arg_value ) {
    }
    CallbackArgument( character_id arg_value ) :
        type( CallbackArgumentType::Character_Id ), value_character_id( arg_value ) {
    }
    CallbackArgument( string_id<weather_type> arg_value ) :
        type( CallbackArgumentType::Weather_Id ), value_weather_id( arg_value ) {
    }
    // CallbackArgument(  arg_value ) :
    //     type( CallbackArgumentType:: ), value_character_id( arg_value ) {
    // }
#ifdef LUA

    void Save(); // from Legacy, void function Save was the only one here.
    
#endif //LUA
};
// callback arg container
typedef std::list<CallbackArgument> CallbackArgumentContainer;

class map; // lua map
class monster; // lua monster?
class time_point; // lua timepoints?
struct mapgendata; // lua map generation data?
struct oter_t; // overterrain?

using oter_id = int_id<oter_t>; // other_id is an int_id

extern std::stringstream lua_output_stream; // string fstream for general output?
extern std::stringstream lua_error_stream; // string fstream for errors?

#ifdef LUA // second lua section; outside of the CallbackArgument struct.
    extern lua_State *lua_state; // the lua state variable

    using overmap_direction = om_direction::type; // alias for overmap direction type
    int luah_store_in_registry( lua_State *L, int stackpos );
    void luah_remove_from_registry( lua_State *L, int item_index );
    void luah_setmetatable( lua_State *L, const char *metatable_name );
    void luah_setglobal( lua_State *L, const char *name, int index );
    std::string lua_tostring_wrapper( lua_State *const L, const int stack_position );
    bool lua_report_error( lua_State *L, int err, const char *path, bool simple );

    void update_globals( lua_State *L );

    // std::unique_ptr<iuse_actor> clone() const;

    /**
     * Base interface for values, that are copied into Luas own memory (and thereby managed by Lua).
     * The class creates a metatable for the wrapped objects, this is all set up via
     * generate_bindings.lua.
     * Usage: there are two main functions you might need: @ref push and @ref get.
     * - @ref push copies the object into Luas memory and pushes a reference to it on the stack.
     *   It is like @ref lua_pushnumber, only it pushes a whole object.
     * - @ref get reads a value from the stack and returns a reference to it (the memory of the object
     *   is managed by Lua and is kept until the garbage collector frees it).
     *
     * You can expect the following behavior:
     * \code
     * const Foo &myfoo = get_my_foo( ... );
     * LuaValue<Foo>::push( L, myfoo ); // copies myfoo
     * ... // give control back to Lua, wait for a callback from it,
     * Foo &thefoo = LuaValue<Foo>::get( L, 1 ); // get the first argument of the callback
     * thefoo.something(); // do something with it, not that myfoo and thefoo are different objects
     * \endcode
     *
     * @param T is the type of object that should be managed. It must be copy-constructible.
     */
    template<typename T>
    class LuaValue
    {
        private:
            /** Defined by generate_bindings.lua in catabindings.cpp */
            static const char *const METATABLE_NAME;
            /** Defined by generate_bindings.lua in catabindings.cpp */
            static const luaL_Reg FUNCTIONS[];
            /** Defined by generate_bindings.lua in catabindings.cpp */
            using MRMap = std::map<std::string, int( * )( lua_State * )>;
            static const MRMap READ_MEMBERS;
            /** Defined by generate_bindings.lua in catabindings.cpp */
            using MWMap = std::map<std::string, int( * )( lua_State * )>;
            static const MWMap WRITE_MEMBERS;

            /*@{*/
            /**
             * @name Dynamic type conversion for Lua, or so.
             *
             * (Disclaimer: don't feel bad for not understanding this, I don't either.)
             *
             * get_subclass is a generated function, it checks whether the value at stack_index
             * is one of the direct subclasses of T (this check is recursive).
             * If one type matches, it returns a pointer to the object.
             *
             * Normally the function would be defined as `T* get_subclass(...)`, but if T is
             * already a pointer (e.g. Creature*), we end with `Creature** get_subclass`.
             * The problem is that a `monster**` can not be converted to `Creature**` and thereby
             * not be returned via this function (trust me, I tried, one may be able to use a
             * reinterpret_cast, but that is evil).
             * We need a simple pointer (not a pointer-to-pointer).
             *
             * We get the simple pointer by removing the pointer from T via the std thingy, which gives us
             * @ref Type. A reference to that is returned by @ref get.
             *
             * Reading user data from Lua gives a T*, so it must be converted to Type&, which may either
             * be just one dereferencing (if T*==Type*) or two (if T*==Type**).
             * One dereferencing is always done int @ref get, the (conditional) second is done in @ref cast.
             * The two overloads match either a Type* (which dereferences the parameter) or a Type&
             * (which just returns the reference without any changes).
             *
             * Maybe an example will help:
             * For T = monster* the function monster::die(Creature*) needs a Creature as parameter.
             * Try this in Lua: `game.zombie(0):die(player)`
             * Lua will check the parameter to be of type LuaValue<Creature*>, this means checking the
             * metatable (whether it's the very same as the one generated by LuaValue<Creature*>::get_metatable)
             * However, `player` has a different table (from LuaValue<player*>), so Lua would complain
             * about the wrong of the argument.
             * `LuaValue<Creature*>::get_subclass` is hard coded (via the code generator) to
             * check whether the value is actually a `Character*`, or a `monster*` (direct subclasses).
             * If so, a pointer the those objects (converted to `Creature*`) is returned. `cast()` will
             * simply pass that pointer through and the caller can return the `Creature*`.
             *
             * Now assume T = point (and assume tripoint inherit from point, why not?)
             * A function calls for a `point`, the input is a tripoint, so the metatables don't match.
             * `get_subclass` is called and successfully extract a tripoint from the userdata. It
             * returns a pointer to the tripoint (converted to `point*`). The caller needs a point (or
             * a point reference), so the `point*` must be converted back to a reference.
             * This is done by the first `cast()` overload.
             */
            using Type = typename std::remove_pointer<T>::type;
            static Type *get_subclass( lua_State *S, int stack_index );
            template<typename P>
            static Type &cast( P *ptr ) {
                return *ptr;
            }
            template<typename P>
            static Type &cast( P &ptr ) {
                return ptr;
            }
            /*@}*/

            static int gc( lua_State *const L ) {
                T *object = static_cast<T *>( lua_touserdata( L, 1 ) );
                object->T::~T();
                lua_pop( L, 1 );
                return 0;
            }
            /**
             * Wrapper for the Lua __index entry in the metatable of the userdata.
             * It queries the actual metatable in case the call goes to a function (and does not request
             * and actual class member) and returns that function (if found).
             * If there is no function of the requested name, it looks up the name in @ref READ_MEMBERS,
             * if it's there, it calls the function that the entry refers to (which acts as a getter).
             * Finally it returns nil, which is what Lua would have used anyway.
             */
            static int index( lua_State *const L ) {
                // -2 is the userdata, -1 is the key (function to call)
                const char *const key = lua_tostring( L, -1 );
                if( key == nullptr ) {
                    luaL_error( L, "Invalid input to __index: key is not a string." );
                }
                if( luaL_getmetafield( L, -2, key ) != 0 ) {
                    // There is an entry of that name, return it.
                    lua_remove( L, -3 ); // remove userdata
                    lua_remove( L, -2 ); // remove key
                    // -1 is now the things we have gotten from luaL_getmetafield, return it.
                    return 1;
                }
                const auto iter = READ_MEMBERS.find( key );
                if( iter == READ_MEMBERS.end() ) {
                    // No such member or function
                    lua_pushnil( L );
                    return 1;
                }
                lua_remove( L, -1 ); // remove key
                // userdata is still there (now on -1, where it is expected by the getter)
                return iter->second( L );
            }
            /**
             * Wrapper for the Lua __newindex entry in the metatable of the userdata.
             * It looks up the name of the requested member in @ref WRITE_MEMBERS and (if found),
             * calls the function that the entry refers to (which acts as a setter).
             */
            static int newindex( lua_State *const L ) {
                // -3 is the userdata, -2 is the key (name of the member), -1 is the value
                const char *const key = lua_tostring( L, -2 );
                if( key == nullptr ) {
                    luaL_error( L, "Invalid input to __newindex: key is not a string." );
                }
                const auto iter = WRITE_MEMBERS.find( key );
                if( iter == WRITE_MEMBERS.end() ) {
                    luaL_error( L, "Unknown attribute" );
                }
                lua_remove( L, -2 ); // key, userdata is still there, but now on -2, and the value is on -1
                return iter->second( L );
            }
            /**
             * This loads the metatable (and adds the available functions) and pushes it on the stack.
             */
            static void get_metatable( lua_State *const L ) {
                // Create table (if it does not already exist), pushes it on the stack.
                // If the table already exists, we have already filled it, so we can return
                // without doing it again.
                if( luaL_newmetatable( L, METATABLE_NAME ) == 0 ) {
                    return;
                }
                // Push the metatable itself, the stack now contains two pointers to the same metatable
                lua_pushvalue( L, -1 );
                // Set the metatable of the new metatable (-2 on the stack) to be itself. Pretty meta, hu?
                // It also pops one value from the stack.
                lua_setmetatable( L, -2 );
                // Now set the actual functions of the metatable.
                luaL_setfuncs( L, &FUNCTIONS[0], 0 );

                // Push function pointer
                lua_pushcfunction( L, &gc );
                // -1 would be the function pointer, -2 is the metatable, the function pointer is popped
                lua_setfield( L, -2, "__gc" );
                lua_pushcfunction( L, &index );
                lua_setfield( L, -2, "__index" );
                lua_pushcfunction( L, &newindex );
                lua_setfield( L, -2, "__newindex" );
            }
            /**
             * Checks the metatable that of value at stack_index against the metatable of this
             * object (matching type T). Returns the stack in the same state as it was when called.
             */
            static bool has_matching_metatable( lua_State *const L, const int stack_index ) {
                if( lua_getmetatable( L, stack_index ) == 0 ) {
                    // value does not have a metatable, can not be valid at all.
                    return false;
                }
                get_metatable( L );
                const bool is_correct_metatable = lua_rawequal( L, -1, -2 );
                lua_remove( L, -1 );
                lua_remove( L, -1 );
                return is_correct_metatable;
            }

        public:
            static void load_metatable( lua_State *const L, const char *const global_name ) {
                // Create the metatable for the first time (or just retrieve it)
                get_metatable( L );
                if( global_name == nullptr ) {
                    // remove the table from stack, setglobal does this in the other branch,
                    // make it here manually to leave the stack in the same state.
                    lua_remove( L, -1 );
                } else {
                    lua_setglobal( L, global_name );
                }
            }
            template<typename U>
            static void push( lua_State *const L, const cata::optional<U> &value ) {
                if( value ) {
                    push( L, *value );
                } else {
                    lua_pushnil( L );
                }
            }
            template<typename ...Args,
                    typename std::enable_if<std::is_constructible<T, Args...>::value, int>::type = 0 >
            static void push( lua_State *const L, Args && ... args ) {
                // Push user data,
                T *value_in_lua = static_cast<T *>( lua_newuserdata( L, sizeof( T ) ) );
                // Push metatable,
                get_metatable( L );
                // -1 is the metatable, -2 is the uservalue, the table is popped
                lua_setmetatable( L, -2 );
                // This is where the copy happens:
                new( value_in_lua ) T( std::forward<Args>( args )... );
            }
            static int push_reg( lua_State *const L, const T &value ) {
                push( L, value );
                return luah_store_in_registry( L, -1 );
            }
            static Type &get( lua_State *const L, const int stack_index ) {
                luaL_checktype( L, stack_index, LUA_TUSERDATA );
                T *user_data = static_cast<T *>( lua_touserdata( L, stack_index ) );
                if( user_data == nullptr ) {
                    // luaL_error does not return at all.
                    luaL_error( L, "First argument to function is not a class" );
                }
                if( has_matching_metatable( L, stack_index ) ) {
                    return cast( *user_data );
                }
                Type *const subobject = get_subclass( L, stack_index );
                if( subobject == nullptr ) {
                    // luaL_argerror does not return at all.
                    luaL_argerror( L, stack_index, METATABLE_NAME );
                }
                return *subobject;
            }
            /** Checks whether the value at stack_index is of the type T. If so, @ref get can be used to get it. */
            static bool has( lua_State *const L, const int stack_index ) {
                if( !lua_isuserdata( L, stack_index ) ) {
                    return false;
                }
                if( has_matching_metatable( L, stack_index ) ) {
                    return true;
                }
                return get_subclass( L, stack_index ) != nullptr;
            }
            /** Raises a Lua error if the type of the value at stack_index is not compatible with T. */
            static void check( lua_State *const L, const int stack_index ) {
                luaL_checktype( L, stack_index, LUA_TUSERDATA );
                if( !has( L, stack_index ) ) {
                    // METATABLE_NAME is used here as the name of the type we expect.
                    luaL_argerror( L, stack_index, METATABLE_NAME );
                }
            }
    };

    /**
     * This is special wrapper (an extension) for references to objects which are not stored in Lua,
     * but are kept in the memory managed by C++. This class only stores and retrieves the pointers,
     * you have to make sure those pointers stay valid.
     *
     * Example (an @ref itype is loaded when a world is loaded and stays valid until the game ends):
     * \code
     * itype *it = type::find_type( "water" );
     * LuaReference<itype>::push( L, it ); // copies the pointer it
     * ... // give control back to Lua, wait for a callback from it,
     * itype &it = LuaValue<itype*>::get( L, 1 ); // get the first argument of the callback
     * assert(it.id == "water");
     * \endcode
     *
     * This class extends LuaValue by some pointer specific behavior:
     * - @ref push is overloaded to accept a reference to T (which will be converted to a pointer
     *   and stored). Additionally, if the pointer passed to @ref push is nullptr, nil will be pushed
     *   (this obviously does not work for references).
     *   \code
     *   Foo *x = ...;
     *   LuaReference<Foo>::push( L, x );
     *   LuaReference<Foo>::push( L, *x ); // both push calls do exactly the same.
     *   \endcode
     *   push is also overloaded to accept const and non-const references / pointers. The templated
     *   third parameter there makes sure that this is only done when T is not const. Otherwise we
     *   would end up with 2 identical push functions, both taking a const references.
     * - @ref get returns a proxy object. It contains the pointer to T. It will automatically convert
     *   to a reference / a pointer to T:
     *   \code
     *   void f_ptr( itype* );
     *   void f_ref( itype& );
     *   auto proxy = LuaReference<itype>::get( L, 1 );
     *   f_ptr( proxy ); // proxy converts to itype*
     *   f_ref( proxy ); // proxy converts to itype&
     *   itype *it = proxy;
     *   \endcode
     *   If you only need a reference (e.g. to call member functions or access members), use
     *   @ref LuaValue<T*>::get instead:
     *   \code
     *   itype &it = LuaValue<itype*>::get( L, 1 );
     *   std::string name = it.nname();
     *   \endcode
     */
    template<typename T>
    class LuaReference : private LuaValue<T *>
    {
        public:
            template<typename U = T>
            static void push( lua_State *const L, T *const value,
                            typename std::enable_if < !std::is_const<U>::value >::value_type * = nullptr ) {
                if( value == nullptr ) {
                    lua_pushnil( L );
                    return;
                }
                LuaValue<T *>::push( L, value );
            }
            template<typename U>
            static void push( lua_State *const L, const cata::optional<U> &value ) {
                if( value ) {
                    push( L, *value );
                } else {
                    lua_pushnil( L );
                }
            }
            // HACK: because Lua does not known what const is.
            static void push( lua_State *const L, const T *const value ) {
                if( value == nullptr ) {
                    lua_pushnil( L );
                    return;
                }
                LuaValue<T *>::push( L, const_cast<T *>( value ) );
            }
            template<typename U = T>
            static void push( lua_State *const L, T &value,
                            typename std::enable_if < !std::is_const<U>::value >::value_type * = nullptr ) {
                LuaValue<T *>::push( L, &value );
            }
            // HACK: because Lua does not known what const is.
            static void push( lua_State *const L, const T &value ) {
                LuaValue<T *>::push( L, const_cast<T *>( &value ) );
            }
            static int push_reg( lua_State *const L, T *const value ) {
                push( L, value );
                return luah_store_in_registry( L, -1 );
            }
            static int push_reg( lua_State *const L, T &value ) {
                return LuaValue<T *>::push_reg( L, &value );
            }
            /** A proxy object that allows to convert the reference to a pointer on-demand. The proxy object can
             * be used as argument to functions that expect either a pointer and to functions expecting a
             * reference. */
            struct proxy {
                T *ref;
                operator T *() {
                    return ref;
                }
                operator T &() {
                    return *ref;
                }
                T *operator &() {
                    return ref;
                }
            };
            /** Same as calling @ref get, but returns a @ref proxy containing the reference. */
            static proxy get( lua_State *const L, const int stack_position ) {
                return proxy{ &LuaValue<T *>::get( L, stack_position ) };
            }
            using LuaValue<T *>::has;
            using LuaValue<T *>::check;
    };

    class lua_iuse_wrapper : public iuse_actor {
        private:
            int lua_function;
         public:
        lua_iuse_wrapper( const int f, const std::string &type ) : iuse_actor( type ), lua_function( f ) {}
        ~lua_iuse_wrapper() override = default;
        // long use( player &, item &it, bool a, const tripoint &pos ) const override { // used to have "const override"
        cata::optional<int> use( player &, item &it, bool a, const tripoint &pos ) const override; // used to have "const override"
                                                                                              // on second thought, we might have to use `optional<long>`
                                                                                              // we also might start seeing errors related to this being a
                                                                                              // `cata::optional`; no worries, just figure out how the other
                                                                                              // `cata::optional`s are implemented, and follow suit.

            
        std::unique_ptr<iuse_actor> clone() const override;

        //iuse_actor *clone() const override { // used to be a pointer
        // std::unique_ptr<iuse_actor> clone() const override { // All the cool kids use "std::unique_ptr<typehere>" now.
        //     // pimp our return
        //     return std::make_unique<lua_iuse_wrapper> lua_iuse_wrapper( *this );
        //     // return new lua_iuse_wrapper( *this ); old return

        //     // what we're going to end up doing is make an external function that does this; the class method will call that function.
        // }

        //void load( JsonObject & ) override {}
        void load( const JsonObject & ) override {} // "probably doesn't need an override"... was my old thoughts. Now I'm thinking something a little different.
                                                    // all of the other `iuse`s in the `iuse_actor.h` use a JsonObject param defined as `const JsonObject &obj`.
                                                    // if this succeeds, then this would mean that ALL overrides previously removed from Lua code are simply missing the
                                                    // properly-defined params.
    };

    //void Item_factory::register_iuse_lua( const std::string &name, int lua_function );

    // class lua_mattack_wrapper; // we're putting it here now
    class lua_mattack_wrapper : public mattack_actor
    {
        private:
            int lua_function;

        public:
            lua_mattack_wrapper( const mattack_id &id, const int f ) :
                mattack_actor( id ),
                lua_function( f ) {}

            ~lua_mattack_wrapper() override = default;

            bool call( monster &m ) const override;

            std::unique_ptr<mattack_actor> clone() const override; // maybe get rid of override?

            void load_internal( const JsonObject &, const std::string & ) override; // override used to come directly after params
    };

    //void MonsterGenerator::register_monattack_lua( const std::string &name, int lua_function );

    void lua_callback_helper( const char *callback_name, const CallbackArgumentContainer &callback_args, int retsize = 0 );

    uilist *create_uilist();

    uilist *create_uilist_no_cancel();

    const ter_t &get_terrain_type( int id );

    // don't worry, the below are defined below this comment chain thing.

    // static time_point &get_calendar_turn_wrapper();

    // static time_duration get_time_duration_wrapper( const int t );

    // static std::string get_omt_id( const overmap &om, const tripoint &p );

    // static overmap_direction get_omt_dir( const overmap &om, const tripoint &p );

    // static std::string string_input_popup_wrapper( const std::string &title, int width, const std::string &desc );

    // gotta define statics where they stand
    static time_point &get_calendar_turn_wrapper()
    {
        return calendar::turn; // i wonder; will this old code work correctly on first try?
    }

    static time_duration get_time_duration_wrapper( const int t )
    {
        return time_duration::from_turns( t );
    }

    // static std::string get_omt_id( const overmap &om, const tripoint &p )
    static std::string get_omt_id( const overmap &om, const tripoint &p )
    {
        // return om.get_ter( p ).id().str(); // .get_ter() no longer exists in modern cata
        // return om.ter( p ).id().str();

        // for now, let's convert the simple tripoint to a `const tripoint_om_omt` object
        // const tripoint_om_omt &modern_pt(p.x, p.y, p.z); // create modern point object using tripoint
        // tripoint_om_omt &modern_pt(p.x, p.y, p.z); // create modern point object using tripoint // we might not need "const"
        const tripoint_om_omt &modern_pt{p.x, p.y, p.z}; // create modern point object using tripoint // we might still need "const"

        // return om.ter( p ).id().str();
        return om.ter( modern_pt ).id().str();
    }

    static overmap_direction get_omt_dir( const overmap &om, const tripoint &p )
    {
        // return om.get_ter( p ).obj().get_dir();
        // return om.ter( p ).obj().get_dir(); // previous method was "get_ter". try saying that 5x fast. instant midwesternite

        // const tripoint_om_omt &modern_pt(p.x, p.y, p.z); // create modern point object using tripoint
        // tripoint_om_omt &modern_pt(p.x, p.y, p.z); // create modern point object using tripoint // we might not need "const"
        const tripoint_om_omt &modern_pt{p.x, p.y, p.z}; // create modern point object using tripoint // we might not need "const"

        // return om.ter( p ).obj().get_dir(); // previous method was "get_ter". try saying that 5x fast. instant midwesternite
        return om.ter( modern_pt ).obj().get_dir(); // previous method was "get_ter". try saying that 5x fast. instant midwesternite
    }

    static std::string string_input_popup_wrapper( const std::string &title, int width,
            const std::string &desc )
    {
        // string_input_popup luastdinpop;
        return string_input_popup().title( title ).width( width ).description( desc ).query_string();
        // return luastdinpop.title( title ).width( width ).description( desc ).query_string(); // query string for lua
    }

    monster *get_monster_at( const tripoint &p );

    Creature *get_critter_at( const tripoint &p );

    monster *create_monster( const mtype_id &mon_type, const tripoint &p );

    // static void popup_wrapper( const std::string &text );

    // static void add_msg_wrapper( const std::string &text );

    // static bool query_yn_wrapper( const std::string &text );

    // static int game_items_at( lua_State *L );

    // static int game_get_item_groups( lua_State *L );

    // static int game_get_monster_types( lua_State *L );

    // static int game_choose_adjacent( lua_State *L );

    // static int game_register_iuse( lua_State *L );

    // static int game_register_monattack( lua_State *L );

    // static int traceback( lua_State *L );

    // void lua_dofile( lua_State *L, const char *path );

    // static int game_dofile( lua_State *L );

    // static int game_myPrint( lua_State *L );
#endif

/** If this returns 0, no lua function was defined to override behavior.
 *  If this returns 1, lua behavior was called and regular behavior should be omitted.
 */
int lua_monster_move( monster *m ); // lua monster override if 0

/**
 * Call the given string as lua code, used for interactive debugging.
 */
int call_lua( const std::string &tocall ); // the string is lua code, and this function runs it
// int lua_mapgen( map *m, const oter_id &terrain_type, const mapgendata &md, const time_point &t,
//                 float d, const std::string &scr ); // generate a map using lua code? oldcode
int lua_mapgen( map *m, const oter_id &terrain_type, const std::string &scr ); // generate a map using lua code?                

/**
 * Execute a callback that can be overridden by all mods with optional accessible arguments.
 */
void lua_callback( const char *callback_name, const CallbackArgumentContainer &callback_args ); // callback (takes the name and callback container)
void lua_callback( const char *callback_name ); // callback (takes only the name)

std::string lua_callback_getstring( const char *callback_name,
                                    const CallbackArgumentContainer &callback_args ); // Lua callback getstring... does it get a string via lua callback...?

/**
 * Load the main file of a lua mod.
 *
 * @param base_path The base path of the mod.
 * @param main_file_name The file name of the lua file, usually "main.lua"
 */
void lua_loadmod( const std::string &base_path, const std::string &main_file_name );

#endif