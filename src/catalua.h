#pragma once
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
#include "item_factory.h" // for item factory stuff
#include "monstergenerator.h" // for mongen stuff
#include "ui.h" // for ui stuff
#include "calendar.h" // for calendar / time based stuff
#include "coordinates.h" // for coords / positions / location based stuff
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
    using overmap_direction = om_direction::type; // alias for overmap direction type
    int luah_store_in_registry( lua_State *L, int stackpos );
    void luah_remove_from_registry( lua_State *L, int item_index );
    void luah_setmetatable( lua_State *L, const char *metatable_name );
    void luah_setglobal( lua_State *L, const char *name, int index );
    std::string lua_tostring_wrapper( lua_State *const L, const int stack_position );
    bool lua_report_error( lua_State *L, int err, const char *path, bool simple );

    void update_globals( lua_State *L );

    class lua_iuse_wrapper : public iuse_actor {
        private:
            int lua_function;
         public:
        lua_iuse_wrapper( const int f, const std::string &type ) : iuse_actor( type ), lua_function( f ) {}
        ~lua_iuse_wrapper() override = default;
        // long use( player &, item &it, bool a, const tripoint &pos ) const override { // used to have "const override"
        cata::optional<int> use( player &, item &it, bool a, const tripoint &pos ) const override { // used to have "const override"
                                                                                              // on second thought, we might have to use `optional<long>`

            // We'll be using lua_state a lot!
            lua_State *const L = lua_state;

            // If it's a lua function, the arguments have to be wrapped in
            // lua userdata's and passed on the lua stack.
            // We will now call the function f(player, item, active)

            update_globals( L );

            // Push the lua function on top of the stack
            lua_rawgeti( L, LUA_REGISTRYINDEX, lua_function );

            // TODO: also pass the player object, because of NPCs and all
            //       I guess

            // Push the item on top of the stack.
            const int item_in_registry = LuaReference<item>::push_reg( L, it );
            // Push the "active" parameter on top of the stack.
            lua_pushboolean( L, a );
            // Push the location of the item.
            const int tripoint_in_registry = LuaValue<tripoint>::push_reg( L, pos );

            // Call the iuse function
            int err = lua_pcall( L, 3, 1, 0 );
            lua_report_error( L, err, "iuse function" );

            // Make sure the now outdated parameters we passed to lua aren't
            // being used anymore by setting a metatable that will error on
            // access.
            luah_remove_from_registry( L, item_in_registry );
            luah_setmetatable( L, "outdated_metatable" );
            luah_remove_from_registry( L, tripoint_in_registry );
            luah_setmetatable( L, "outdated_metatable" );

            return lua_tointeger( L, -1 );
        }

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

    class lua_mattack_wrapper;

    //void MonsterGenerator::register_monattack_lua( const std::string &name, int lua_function );

    //void lua_callback_helper( const char *callback_name, const CallbackArgumentContainer &callback_args, int retsize = 0 );

    uilist *create_uilist();

    uilist *create_uilist_no_cancel();

    const ter_t &get_terrain_type( int id );

    // static calendar &get_calendar_turn_wrapper();

    // static time_duration get_time_duration_wrapper( const int t );

    // static std::string get_omt_id( const overmap &om, const tripoint &p );

    // static overmap_direction get_omt_dir( const overmap &om, const tripoint &p );

    // static std::string string_input_popup_wrapper( const std::string &title, int width, const std::string &desc );

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