# HEADER
## line.h
> HEADER GUARDS: **CATA_SRC_LINE_H**
> This library provides "line-drawing" functionality for the game's 3D environment.
### HEADERS
`point.h` - For map-points (coordinates)?
`units_fwd.h` - Units for some sort of measurements?

> The type IDs are for accessing that particular attribute when it comes to getting their skill level for calculations.
# C++
## HEADERS

## NAMESPACE/CLASS/ETC STRUCTURE

### enum class direction : unsigned

### structure_name
### 

## FUNCTIONS
```c++
void iso_tangent( double distance, const units::angle &vertex );
```
> **DESCRIPTION**
>
> Triangle math! Calculates the base of an isosceles triangle, using the distance of one of the equal lengths, and a vertex of the unequal angle.
> Returns the rough length of the base.
> 
> (Comment directly from source file)
> /**
> * Calculate base of an isosceles triangle
> * @param distance one of the equal lengths
> * @param vertex the unequal angle
> * @returns base in equivalent units to distance
> */

> **PARAMS**
>
> - `distance`
>   - Distance of one of the equal lengths of the triangle.
> - `vertex`
>   - Vertex of the unequal angle.


```c++
inline constexpr unsigned make_xyz_unit( const tripoint & );
```
> **DESCRIPTION**
>
> Combines the XYZ-sign of each component (which can be a value between -1 and 1) into a single `int` integer.
> Numbers beyond the "-1, 1" range must use the `make_xyz( const tripoint & )` function.

> **PARAMS**
>
> The params go here.

```c++
void make_xyz();
```
> **DESCRIPTION**
>
> A more general version of the `make_xyz_unit( const tripoint &p )` function, that gives the correct values for larger inputs.

> **PARAMS**
>
> The params go here.

## VARIABLES
```c++
extern bool trigdist;
```
> **DESCRIPTION**
>
> The description goes here.

```c++
int variable;
```
> **DESCRIPTION**
>
> The description goes here.

# NOTES
- POINT