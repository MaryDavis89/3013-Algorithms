## Program 3 - Graphs
### Due: 28<sup>th</sup> of October

# not done

### Overview

Create a graph structure with cities as __Vertices__ and no __Edges__ initially. Fully connect your cities by adding edges between cities that are close together. Basically create a connected graph of all the cities so that every city is reachable by ensuring that each vertex has a  degree of ***D*** (*in/out degree*), where each edge represents one of ***D*** closest cities to that vertex.

You should make sure that you can adjust the degree using a command line parameter and not hard coding it. 

Included in the folder is a [cities.json](./cities.json) file with 1000 cities along with some data about each city. You `Vertex` data type should hold all the information below.

```json
{
	"city": "Wichita Falls",
	"growth_from_2000_to_2013": 0.7,
	"latitude": 33.9137085,
	"longitude": -98.4933873,
	"population": 104898,
	"rank": 271,
	"state": "Texas"
}
```

Also included is the [json_helper.cpp](./json_helper.cpp) and [json.hpp](json.hpp) files. Using the json helper, you can read in the [cities.json](./cities.json) file just like our last project. 

Starting with the first city in the array, find the ***D*** closest cities and create edges between them. The edges are not directed. Your edge type should store the `distance` (as well as the `from` and `to`). Continue processing the rest of the cities adding edges until each city as ***D*** edges. Look out for pitfalls, like just because a city is close to another, you may not be able to connect them if it already has its max edges. 



### Deliverables

- Turn in a printed file with the first 25 cities and who they are connected to:

```
0001 : New York 
    1) City A (distance)
	2) City B (distance)
	3) City C (distance)
0002 : Los Angeles
    1) City A (distance)
	2) City B (distance)
	3) City C (distance)
0003 : Chicago
    1) City A (distance)
	2) City B (distance)
	3) City C (distance)
0004 : Houston
    1) City A (distance)
	2) City B (distance)
	3) City C (distance)
	...
0025 : Nashville-Davidson
    1) City A (distance)
	2) City B (distance)
	3) City C (distance)
```

### Comments

**Example Top Comment Block for every file you wrote code in ...**

```cpp
///////////////////////////////////////////////////////////////////////////////
//
// Date:             28 October 2019
// Title:            Program 3 - Graphs
// Semester:         Spring 2018
// Course:           CMPS 3013 
// Assignment:       A05
// Author:           (your name)
// Email:            (your email address)
// Files:            (list of source files)
// Description:
//       describe program here thoroughly
//
/////////////////////////////////////////////////////////////////////////////////
```

**Example Function Comment Block**

```cpp
/**
 * Swap
 * 
 * Description:
 *      Swaps to values in thier original memory locations
 * 
 * Params:
 *      int *a : location 1 (the '*' accesses the location to get the value)
 *      int *b : locatoin 2
 * 
 * Returns:
 *      void
 */
void swap(int *a, int *b) {
    int temp = *a; // put first value in temp location
    *a = *b;       // overwrite location1 with value at location2
    *b = temp;     // overwrite location2 with value from temp
}
```

### Deliverables

- In `assignments` create a folder called `A05`
- In `A05` place your code in a file called `graph_builder.cpp`
- Any and ALL files used to run your code MUST be in your repo.
- Include any input files you used to test your code as well.
- Comment your code. 
- Turn in a printed copy of your source code (DO NOT PRINT FROM GITHUB!!). 
  - There is a way to print source code from github, ask me in class to show you.
- Staple your pages together at the top left (very close to the corner).
- No hand writing on your pages at all! 
- Top page should be your first source code page with a BIG comment block that explains the program and tells me who you are with date etc.
