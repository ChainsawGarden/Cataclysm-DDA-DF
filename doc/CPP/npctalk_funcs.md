# HEADER
## npctalk.h
### HEADER GUARDS: **CATA_SRC_NPCTALK_H**
> This header file holds the data concerning NPC-to-Player talking behavior.
### HEADERS
`type_id.h` - For creating `string_id` objects; uses the following type_ids:
- `skill_id`: for calculating skill training time.
- `proficiency_id`: for calculating proficiency training time.
- `matype_id`: for calculating martial art style training cost.

> The type IDs are for accessing that particular attribute when it comes to getting their skill level for calculations.
# C++
## HEADERS

## NAMESPACE
### talk_function
```c++
void nothing( npc &p )
```
> **DESCRIPTION**
>
> Does nothing.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void assign_mission( npc & )
```
> **DESCRIPTION**
>
> Assigns an NPC a mission that may be completed by the player.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void mission_success( npc & )
```
> **DESCRIPTION**
>
> Increases NPC opinion of you. Increases the NPC's faction's general opinion of you, and also increases a faction's power.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void mission_failure( npc & )
```
> **DESCRIPTION**
>
> Sets the opinion (usually negative) and fails the NPC's given mission.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void clear_mission( npc & )
```
> **DESCRIPTION**
>
> Erases the NPC's given mission.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void mission_reward( npc & )
```
> **DESCRIPTION**
>
> Rewards the player with an item. Uses `npc_trading::trade(npc, int cost, std::string &deal)`.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

> **NOTES**
> - `npc_trading` is a namespace, containing [].
> - `npc_trading::trade` is a function.

```c++
void mission_favor( npc & )
```
> **DESCRIPTION**
>
> This function has not yet been defined. It is assumed that this function may allow the player to ask the NPC for favors-- as all `mission_*` functions directly affect the player (from the NPC)

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void give_equipment( npc & )
```
> **DESCRIPTION**
>
> Adds a random item from the NPC's inventory into the player's inventory. Changes the ownership to the player's. Uses namespace `npc_trading`.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void give_aid( npc & )
```
> **DESCRIPTION**
>
> Heals each of the player's bodyparts and stops bleeding. How much HP is healed is based on a calculation ( 5 * rng(2, 5) )[[*Five multiplied by a random number two-through-five, with 2, 3, 4, and 5 being the possible numbers in-between.*]]. Gives the NPC the "Busy" effect for 30 minutes. Removes bite, bleed, and infections 

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void give_all_aid( npc & )
```
> **DESCRIPTION**
>
> Calls `void give_aid( npc & )` (which heals the player) and heals other nearby NPCs through iteration. Heal code is non-abstracted; meaning the same code (with some nuances) for the player heal is written verbatim for iterations.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void buy_horse( npc & )
```
> **DESCRIPTION**
>
> Spawns a horse near the NPC.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void buy_cow( npc & )
```
> **DESCRIPTION**
>
> Spawns a cow near the NPC.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void buy_chicken( npc & )
```
> **DESCRIPTION**
>
> Spawns a cow near the NPC.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void bionic_install( npc & )
```
> **DESCRIPTION**
>
> Pays an NPC to install a bionic.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void bionic_remove( npc & )
```
> **DESCRIPTION**
>
> Pays an NPC to remove a bionic.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void dismount( npc & )
```
> **DESCRIPTION**
>
> Dismounts the specified NPC from a horse.

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

```c++
void find_mount( npc & )
```
> **DESCRIPTION**
>
> Finds a horse for the NPC to mount. Iterates through all critters nearby, checks mountability, adds the job, and sets the `chosen_mount` variable to a pointer to `g->shared_from( critter ).

> **PARAMS**
> - npc
>   - The specific NPC mission-giver.

# NOTES
- Why is classes `item`, `json_talk_topic`, `npc`, and `time_duration` being defined here (near top)? Not a bug, just curious.
    - `class item` already exists in its own header/source files.
    - `class json_talk_topic` exists in `dialogue.h`
    - `class npc` exists in its own header/source files.
    - `class time_duration` already exists in `calendar.h`