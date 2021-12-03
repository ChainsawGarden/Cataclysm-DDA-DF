#pragma once
#ifndef CATALUA_H
#define CATALUA_H

#include <list>
#include <sstream>
#include <string>

#include "creature.h"
#include "character_id.h"
#include "enums.h"
#include "int_id.h"
#include "item.h"
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
    Character_Id
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
    body_part value_body_part;
    const int_id<body_part_type> value_body_part_id;
    character_id value_character_id;

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
#ifdef LUA
    void Save();
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

/** If this returns 0, no lua function was defined to override behavior.
 *  If this returns 1, lua behavior was called and regular behavior should be omitted.
 */
int lua_monster_move( monster *m ); // lua monster override if 0

/**
 * Call the given string as lua code, used for interactive debugging.
 */
int call_lua( const std::string &tocall ); // the string is lua code, and this function runs it
int lua_mapgen( map *m, const oter_id &terrain_type, const mapgendata &md, const time_point &t,
                float d, const std::string &scr ); // generate a map using lua code?

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