#pragma once
#include "..//stdafx.h"

/*Type definitions for Node
Changing these types can affect memory usage as the nodes make the majority of memory usage
especially when there are many of them (100k+). Tune them to fit your requirements.
*/

//Unsigned types
typedef uint16_t edgeCount_t;
typedef uint16_t iterCounter_t;
typedef uint16_t ID_t;
//Signed types
typedef int16_t roadID_t;

//Must be set to a number greater than the longest possible distance in the graph.
#define REALLY_HIGH_NUMBER 1e20f