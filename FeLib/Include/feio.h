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

#ifndef __FEIO_H__
#define __FEIO_H__

#include "v2.h"
#include "festring.h"

class bitmap;

typedef bool (*stringkeyhandler)(int, festring&);

class iosystem
{
  public:
    static festring ContinueMenu(col16, col16, const festring&);
    static int StringQuestion(festring&, const festring&, v2, col16, festring::sizetype,
                              festring::sizetype, bool, bool, stringkeyhandler = 0);
    static long NumberQuestion(const festring&, v2, col16, bool, bool = false);
    static long ScrollBarQuestion(const festring&, v2, long, long, long, long, long, col16, col16,
                                  col16, int, int, bool, void (*)(long) = 0);
    static int Menu(const bitmap*, v2, const festring&, const festring&, col16,
                    const festring& = CONST_S(""), const festring& = CONST_S(""));
    
	/* TODO: can be removed? */
	static void TextScreen(const festring&, col16 = 0xFFFF, bool = true, void (*)(bitmap*) = 0);
    static bool IsAcceptableForStringQuestion(char);
};

#endif
