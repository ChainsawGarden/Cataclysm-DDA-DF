# HEADER
## current_main_header.h
> HEADER GUARDS: **CATA_SRC_MONSTER_H**

> *Defines the `monster` object (which entails animals, zombies, extraterrestrials...) and its attributes*.
---
## "INCLUDES" SECTION
### STANDARD C++ LIBRARY FILES
### HEADER FILES
`monster.h` - Imports the main monster object code.

# C++
## HEADERS

## NAMESPACE/CLASS/ETC STRUCTURE
### structure_name

## FUNCTIONS / METHODS
```c++
void setpos( const tripoint &p ) override;
```
> **DESCRIPTION**
>
> Ultimately sets the position via tripoint.
>> **PARAMS**
>>
>> `const tripoint &`
>> - The target tripoint that our character's position will be set to. For example, if our current position is (0, 0, 0) and the target is (1, 1, 1), we will move to (1, 1, 1).

```c++
inline const tripoint &pos() const override
```
> **DESCRIPTION**
>
> Ultimately returns the position via tripoint.

```c++
int variable;
```
> **DESCRIPTION**
>
> The description goes here.

# NOTES
- POINT