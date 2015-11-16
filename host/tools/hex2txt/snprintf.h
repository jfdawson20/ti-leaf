/* snprintf() implementation taken from comp.lang.c.moderated post by Larry Jones:

From: Larry Jones (scjones@thor.sdrc.com)
Subject: Re: snprintf implementation in pre C99 C 
Group:comp.lang.c.moderated
Date:2000/02/01 

Igor Boukanov (boukanov@sentef2.fi.uib.no) wrote:
>
> Does anybody know about simple (and small) snprintf implementation purely 
> in the C89 standard? I would like to use such a code on systems that lack 
> it. It does not need to be fast and may require larger buffers then a real 
> snprintf will need.

It's not pretty, but it is simple and, I believe, correct and C89 conforming.
*/

#include <stdarg.h>
#include <stdio.h>

#ifndef HAVE_RESTRICT
#define restrict
#endif

int vsnprintf(char * restrict s, size_t n, const char * restrict f, va_list a);
int snprintf(char * restrict s, size_t n, const char * restrict f, ...);
