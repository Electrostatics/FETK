FETK
=============
Welcome to a *modified* version of the FETK (The Finite Element Toolkit).

The reason that this exists is to deal with issues that we've discovered in the FETK.  The FETK is open source software (see http://www.fetk.org), and yet it's not hosted in a manner that is conducive to forking and merge requests.  At least not to our knowledge.  Therefore we have created this *"fork"* until a more permanent solution presents itself.

In this file is a list of the changes that were made to the FETK, by library, file, function, and line number, along with a brief description of why the change was made.  I have taken great pains to comment each modification in the code, describing the purpose for each update.  I have also prefaced each comment with "APBS-KTS", so that they may be easily located.

MALOC
-----
Spurious errors are emitted under all circumstances because APBS code uses MALOC's scanf, and expects it to hand back results until there are no more tokens.  MALOC's version of scanf however prints error messages when it hits the end of the input.  I changed it so that it notices EOF, it reports it thusly, and doesn't spew dumb messages.
* vio.c, _"initialization"_, 103: Added an error field to the ASC struct to track EOF.
* vio.c, _Vio_scanf_, 1473-1480: Check the above error field to see if we are here because of an EOF.  If that's the case then just silently continue.  Otherwise, print the error because something really did go wrong.
* vio.c, _ascmem_create_, 1918: Initialize the error field to 0.
* vio.c, _ascmem_destroy_, 1938: Reset the error field to 0.
* vio.c, _asc_getToken_, 2159-2163: Commentary on the function.
* vio.c, _asc_getToken_, 2199-2205: More commentary.
* vio.c, _asc_getToken_, 2229-2236: Commented out a bug/unnecessary line of code; with explanation.
* vio.c, _asc_getToken_, 2248-2254: Remove unnecessary error message and set error field to EOF.
