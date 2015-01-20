/*
 *
 *  Iter Vehemens ad Necem (IVAN)
 *  Copyright (C) Timo Kiviluoto
 *  Released under the GNU General
 *  Public License
 *
 *  See LICENSING which should be included
 *  along with this file for more details
 *
 */

#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__
#include <cstdint>
#include "pragmas.h"

typedef unsigned char uchar;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint32_t ulong;
typedef int32_t col16;
typedef ushort packcol16;
typedef ulong col24;
typedef int32_t alpha;
typedef uint8_t packalpha;
typedef int32_t priority;
typedef uint8_t packpriority;
typedef uint8_t paletteindex;

typedef const int ctruth;
typedef const unsigned char cuchar;
typedef const unsigned short cushort;
typedef const unsigned int cuint;
typedef const unsigned long culong;
typedef const int ccol16;
typedef const ushort cpackcol16;
typedef const ulong ccol24;
typedef const int calpha;
typedef const uchar cpackalpha;
typedef const int cpriority;
typedef const uchar cpackpriority;
typedef const uchar cpaletteindex;

#endif
