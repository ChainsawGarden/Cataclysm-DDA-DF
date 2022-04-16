#include "lua_console.h"

#include <map>

#include "catalua.h"
#include "input.h"
#include "string_input_popup.h"
#include "point.h" // has `struct point` predefs

// lua_console::lua_console() : cWin( catacurses::newwin( lines, width, 0, 0 ) ),
lua_console::lua_console() : 
    cWin( catacurses::newwin( lines, width, point_zero ) ),
    iWin( catacurses::newwin( 1, width, point_zero ) )
{
    #ifndef LUA
        text_stack.push_back( {_( "This build does not support Lua." ), c_red} );
    #else
        text_stack.push_back( {_( "Welcome to the Lua console! Here you can enter Lua code." ), c_green} );
    #endif
        text_stack.push_back( {_( "Press [Esc] to close the Lua console." ), c_blue} );
}

lua_console::~lua_console() = default; // Console destructor

// Handles input meant for the console; currently handles Escape, and N/P PAGE buttons.
std::string lua_console::get_input()
{
    std::map<long, std::function<bool()>> callbacks {
        {
            KEY_ESCAPE, [this]()
            {
                this->quit();
                return false;
            }
        },
        {
            KEY_NPAGE, [this]()
            {
                this->scroll_up();
                return false;
            }
        },
        {
            KEY_PPAGE, [this]()
            {
                this->scroll_down();
                return false;
            }
        } };
    string_input_popup popup;
    // popup.window( iWin, 0, 0, width )
    popup.window(iWin, point_zero, width)
    .max_length( width )
    .identifier( "LUA" );
    popup.callbacks = callbacks;
    popup.query();
    return popup.text();
}

// Draws text in the cWin window.
void lua_console::draw()
{
    werase( cWin );

    // Some juggling to make sure text is aligned with the bottom of the console.
    int stack_size = text_stack.size() - scroll; // get the text stack size
    for( int i = lines; i > lines - stack_size && i >= 0; i-- ) { // iterate through the text stack
        auto line = text_stack[stack_size - 1 - ( lines - i )]; // get the line
        // mvwprintz( cWin, point(i - 1, 0), line.second, line.first ); // print the line
        mvwprintz( cWin, point(0, i-1), line.second, line.first ); // print the line
    }

    wrefresh( cWin );
}

// Sets "done" to True.
void lua_console::quit()
{
    done = true;
}

// Scrolls up the console.
void lua_console::scroll_down()
{
    scroll = std::min( std::max( ( static_cast<int>( text_stack.size() ) ) - lines, 0 ), scroll + 1 );
    draw();
}

// Scrolls down the console.
void lua_console::scroll_up()
{
    scroll = std::max( 0, scroll - 1 );
    draw();
}

// Reads from the console's input.
void lua_console::read_stream( std::stringstream &stream, nc_color text_color )
{
    std::string line;
    while( std::getline( stream, line ) ) {
        for( auto str : foldstring( line, width ) ) {
            text_stack.push_back( {str, text_color} );
        }
    }
    stream.str( std::string() ); // empty the buffer
    stream.clear();
}

// Reads input and executes Lua
void lua_console::run()
{
    while( !done ) {
        draw();

        std::string input = get_input();

#ifdef LUA // if Lua is enabled.
        call_lua( input );

        read_stream( lua_output_stream, c_white );
        read_stream( lua_error_stream, c_red );
#else // if Lua is not enabled.
        text_stack.push_back( {_( "This build does not support Lua." ), c_red} );
        text_stack.push_back( {_( "Press [Esc] to close the Lua console." ), c_blue} );
#endif // LUA
    }
}