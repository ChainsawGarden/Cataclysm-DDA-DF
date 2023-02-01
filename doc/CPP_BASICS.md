# C++ BASICS

For beginner developers (that know the basics of C++), these are the essential functions and basic conventions that CPP coders have 
---

## VARIABLES (global variables)
`g` - `game` class object. Defined in `game.h`. Has variables for the player, weather, scent maps, game scenario, etc.
- `u` - An `avatar` class object **within the `game` class.** You'd typically use this to refer to the current player.

`uistate` - `uistatedata` class object. Defined in `game.h`, handles the current game's User Interface (ui) state.

### PARAMETER CONVENTIONS
`u` - `player` class object. You'd typically use this to refer to the current player.

## MONSTER SPAWNING
### All of these functions return a `monster *`
### Spawn monster at specific location
```cpp
game::place_critter_at( const mtype_id &id, const tripoint &p )
game::place_critter_at( const shared_ptr_fast<monster> &mon, const tripoint &p )
```

### Spawn monster in a range around a position
```cpp
game::place_critter_around( const mtype_id &id, const tripoint &center, const int radius )
game::place_critter_around( const shared_ptr_fast<monster> &mon,
                                     const tripoint &center,
                                     const int radius,
                                     bool forced )
```

### Spawn monster within a volume
```cpp
game::place_critter_within( const mtype_id &id, const tripoint_range<tripoint> &range )
game::place_critter_within( const shared_ptr_fast<monster> &mon,
                                     const tripoint_range<tripoint> &range )
```

### Spawn a random hallucination at location
This function returns a bool, "did it succeed in spawning a hallucination?"
```cpp
game::spawn_hallucination( const tripoint &p )
```

(Credit to OrenAudeles#3657 for the monster spawn stuff above)