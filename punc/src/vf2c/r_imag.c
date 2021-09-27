#include "f2c.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef KR_headers
double r_imag(z) realcomplex *z;
#else
double r_imag(realcomplex *z)
#endif
{
return(z->i);
}
#ifdef __cplusplus
}
#endif
