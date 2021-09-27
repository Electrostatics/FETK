#include "f2c.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef KR_headers
VOID r_cnjg(r, z) realcomplex *r, *z;
#else
VOID r_cnjg(realcomplex *r, realcomplex *z)
#endif
{
	real zi = z->i;
	r->r = z->r;
	r->i = -zi;
	}
#ifdef __cplusplus
}
#endif
