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

int vsnprintf(char * restrict s, size_t n, const char * restrict f, va_list a)
{
   int len;
   static FILE *fp = NULL;

   if (!fp) {
      fp = tmpfile();
      if (!fp) return -1;
   }
   len = vfprintf(fp, f, a);
   if (len < 0) return len;
   rewind(fp);
   if (n-- > 0) {
      if (n > len) n = len;
      if (n > 0) fread(s, n, 1, fp);
      s[n] = '\0';
   } return len;
}


int snprintf(char * restrict s, size_t n, const char * restrict f, ...)
{
   va_list ap;

   va_start(ap, f);
   n = vsnprintf(s, n, f, ap);
   va_end(ap);
   return n;
}


#ifdef TEST

int main()
{
   char buf[80];
   int n;

   n = snprintf(NULL, 0, "%g", 3.14159265);
   printf("snprintf(NULL, 0, \"%%g\", 3.14159265) = %d\n", n);
   strcpy(buf, "123456");
   n = snprintf(buf, 1, "%g", 3.14159265);
   printf("snprintf(buf, 1, \"%%g\", 3.14159265) = %d\n", n);
   printf("  buf = \"%s\"\n", buf);
   printf("  buf[2] = '%c'\n", buf[2]);
   n = snprintf(buf, 2, "%g", 3.14159265);
   printf("snprintf(buf, 2, \"%%g\", 3.14159265) = %d\n", n);
   printf("  buf = \"%s\"\n", buf);
   printf("  buf[2] = '%c'\n", buf[2]);
   n = snprintf(buf, 3, "%g", 3.14159265);
   printf("snprintf(buf, 3, \"%%g\", 3.14159265) = %d\n", n);
   printf("  buf = \"%s\"\n", buf);
   printf("  buf[2] = '%c'\n", buf[2]);
   n = snprintf(buf, 80, "%g", 3.14159265);
   printf("snprintf(buf, 80, \"%%g\", 3.14159265) = %d\n", n);
   printf("  buf = \"%s\"\n", buf);
   return 0;
}

#endif

