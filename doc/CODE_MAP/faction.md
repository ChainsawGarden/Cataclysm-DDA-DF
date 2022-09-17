# faction.h
> HEADER GUARDS: **CATA_SRC_FACTION_H**
> Adds factions.
### HEADERS
`character_id.h` - For indexing (ID-ing) specific Character-class objects (characters, like NPCs)
> The type IDs are for accessing that particular attribute when it comes to getting their skill level for calculations.
`color.h` - XXX
`translations.h` - For translating text to different languages.
`type_id.h` - For typing (types like string_id, int_id, etc)
# C++
## CLASS/NAMESPACE/ETC STRUCTURE
> namespace npc_factions
>> class faction_template
```c++
protected:
    void load_relations()
```

```c++
private:
    explicit faction_template( const JsonObject &jsobj )
```
> **DESCRIPTION**
>
> This is a constructor that I assume loads faction data from a JSON structure / file. As for what `explicit` is, refer to this: https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean

> **PARAMS**
>
> - jsobj
>   - The JSON object used.

```c++
public:
    void load( const JsonObject &jsobj )
```
> **DESCRIPTION**
>
> Loads the faction (template?) data into memory.

> **PARAMS**
>
> - jsobj
>   - The JSON object used.

```c++
public:
    static void check_consistency()
```
> **DESCRIPTION**
>
> Checks the consistency of the faction template's snippet data.

> **PARAMS**
>
> None.

```c++
public:
    static void reset()
```
> **DESCRIPTION**
>
> Clears all templates for NPC factions.

> **PARAMS**
>
> None.

**VARIABLES**

```c++
std::string name 
```
> **DESCRIPTION**
>
> The name of the faction.

```c++
int likes_u;
```
> **DESCRIPTION**
>
> Points that determine how well your faction likes you. Higher means you likely won't see a mutiny from your people.

```c++
int respects_u;
```
> **DESCRIPTION**
>
> Points that determine how well your faction respects you. Higher means you likely won't see a mutiny from your people.

```c++
bool known_by_u;
```
> **DESCRIPTION**
>
> For epilogue text; lone wolf NPCs (through mutiny?) 

```c++
faction_id id;
```
> **DESCRIPTION**
>
> The ID of the specific faction.

```c++
translation desc;
```
> **DESCRIPTION**
>
> Translation string. The description to be translated.

```c++
int size;
```
> **DESCRIPTION**
>
> Epilogue flavor text.

```c++
int power;
```
> **DESCRIPTION**
>
> Epilogue flavor text.

```c++
int food_supply
```
> **DESCRIPTION**
>
> Food supply for feeding your faction people for their labor.

```c++
int wealth;
```
> **DESCRIPTION**
>
> Epilogue flavor text.

```c++
bool lone_wolf_faction;
```
> **DESCRIPTION**
>
> If this faction is for one particular NPC?

```c++
itype_id currency;
```
> **DESCRIPTION**
>
> The itype ID for the faction's currency.

```c++
std::map<std::string, std::bitset<npc_factions::rel_types>> epilogue_data;
```
> **DESCRIPTION**
>
> <string, int?> mapping for NPC faction relations. Keyed by string-type.

#### class faction (*inherits from class faction_template*)
#### class faction_manager