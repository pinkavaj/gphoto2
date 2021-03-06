/* qcam-linux.h -- Linux-specific routines for accessing QuickCam */

/* Version 0.1, January 2, 1996 */
/* Version 0.5, August 24, 1996 */


/******************************************************************

Copyright (C) 1996 by Scott Laird

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL SCOTT LAIRD BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

******************************************************************/

#include <asm/io.h>


//#define read_lpstatus(q)	(inb((q)->port+1))
//#define read_lpcontrol(q)	(inb((q)->port+2))
//#define read_lpdata(q)		(inb((q)->port))
//#define write_lpdata(q,d)	(outb((d),(q)->port))
//#define write_lpcontrol(q,d)	(outb((d),(q)->port+2))

