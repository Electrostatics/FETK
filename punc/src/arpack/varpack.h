extern int cgetv0_(integer *ido, char *bmat, integer *itry, logical *initv, integer *n, integer *j, complex *v, integer *ldv, complex *resid, real *rnorm, integer *ipntr, complex *workd, integer *ierr, ftnlen bmat_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: clarnv_ 14 4 4 4 4 8 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: cvout_ 14 6 4 4 8 4 13 124 */
extern int cnaitr_(integer *ido, char *bmat, integer *n, integer *k, integer *np, integer *nb, complex *resid, real *rnorm, complex *v, integer *ldv, complex *h__, integer *ldh, integer *ipntr, complex *workd, integer *info, ftnlen bmat_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: second_ 14 1 6 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: cgetv0_ 14 14 4 13 4 12 4 4 8 4 8 6 4 8 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cvout_ 14 6 4 4 8 4 13 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clanhs_ 6 6 13 4 8 4 8 124 */
/*:ref: cmout_ 14 8 4 4 4 8 4 4 13 124 */
extern int cnapps_(integer *n, integer *kev, integer *np, complex *shift, complex *v, integer *ldv, complex *h__, integer *ldh, complex *resid, complex *q, integer *ldq, complex *workl, complex *workd);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: second_ 14 1 6 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: cvout_ 14 6 4 4 8 4 13 124 */
/*:ref: clanhs_ 6 6 13 4 8 4 8 124 */
/*:ref: clartg_ 14 5 8 8 6 8 8 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: cmout_ 14 8 4 4 4 8 4 4 13 124 */
extern int cnaup2_(integer *ido, char *bmat, integer *n, char *which, integer *nev, integer *np, real *tol, complex *resid, integer *mode, integer *iupd, integer *ishift, integer *mxiter, complex *v, integer *ldv, complex *h__, integer *ldh, complex *ritz, complex *bounds, complex *q, integer *ldq, complex *workl, integer *ipntr, complex *workd, real *rwork, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: cgetv0_ 14 14 4 13 4 12 4 4 8 4 8 6 4 8 4 124 */
/*:ref: cnaitr_ 14 16 4 13 4 4 4 4 8 6 8 4 8 4 4 8 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: cneigh_ 14 11 6 4 8 4 8 8 8 4 8 6 4 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cngets_ 14 7 4 13 4 4 8 8 124 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: cvout_ 14 6 4 4 8 4 13 124 */
/*:ref: csortc_ 14 6 13 12 4 8 8 124 */
/*:ref: cnapps_ 14 13 4 4 4 8 8 4 8 4 8 8 4 8 8 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: cmout_ 14 8 4 4 4 8 4 4 13 124 */
extern int cnaupd_(integer *ido, char *bmat, integer *n, char *which, integer *nev, real *tol, complex *resid, integer *ncv, complex *v, integer *ldv, integer *iparam, integer *ipntr, complex *workd, complex *workl, integer *lworkl, real *rwork, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: cstatn_ 14 0 */
/*:ref: second_ 14 1 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: cnaup2_ 14 27 4 13 4 13 4 4 6 8 4 4 4 4 8 4 8 4 8 8 8 4 8 4 8 6 4 124 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: cvout_ 14 6 4 4 8 4 13 124 */
extern int cneigh_(real *rnorm, integer *n, complex *h__, integer *ldh, complex *ritz, complex *bounds, complex *q, integer *ldq, complex *workl, real *rwork, integer *ierr);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: cmout_ 14 8 4 4 4 8 4 4 13 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clahqr_ 14 13 12 12 4 4 4 8 4 8 4 4 8 4 4 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cvout_ 14 6 4 4 8 4 13 124 */
/*:ref: ctrevc_ 14 17 13 13 12 4 8 4 8 4 8 4 4 4 8 6 4 124 124 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
extern int cneupd_(logical *rvec, char *howmny, logical *select, complex *d__, complex *z__, integer *ldz, complex *sigma, complex *workev, char *bmat, integer *n, char *which, integer *nev, real *tol, complex *resid, integer *ncv, complex *v, integer *ldv, integer *iparam, integer *ipntr, complex *workd, complex *workl, integer *lworkl, real *rwork, integer *info, ftnlen howmny_len, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: cvout_ 14 6 4 4 8 4 13 124 */
/*:ref: cngets_ 14 7 4 13 4 4 8 8 124 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clahqr_ 14 13 12 12 4 4 4 8 4 8 4 4 8 4 4 */
/*:ref: cmout_ 14 8 4 4 4 8 4 4 13 124 */
/*:ref: ctrsen_ 14 17 13 13 12 4 8 4 8 4 8 4 6 6 8 4 4 124 124 */
/*:ref: cgeqr2_ 14 7 4 4 8 4 8 8 4 */
/*:ref: cunm2r_ 14 14 13 13 4 4 4 8 4 8 8 4 8 4 124 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: ctrevc_ 14 17 13 13 12 4 8 4 8 4 8 4 4 4 8 6 4 124 124 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: ctrmm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
extern int cngets_(integer *ishift, char *which, integer *kev, integer *np, complex *ritz, complex *bounds, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: csortc_ 14 6 13 12 4 8 8 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: cvout_ 14 6 4 4 8 4 13 124 */
extern int csortc_(char *which, logical *apply, integer *n, complex *x, complex *y, ftnlen which_len);
/*:ref: slapy2_ 6 2 6 6 */
extern int cstatn_(void);
/* comlen timing_ 124 */
extern int dgetv0_(integer *ido, char *bmat, integer *itry, logical *initv, integer *n, integer *j, doublereal *v, integer *ldv, doublereal *resid, doublereal *rnorm, integer *ipntr, doublereal *workd, integer *ierr, ftnlen bmat_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dlarnv_ 14 4 4 4 4 7 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
extern int dlaqrb_(logical *wantt, integer *n, integer *ilo, integer *ihi, doublereal *h__, integer *ldh, doublereal *wr, doublereal *wi, doublereal *z__, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlanhs_ 7 6 13 4 7 4 7 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlanv2_ 14 10 7 7 7 7 7 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
extern int dnaitr_(integer *ido, char *bmat, integer *n, integer *k, integer *np, integer *nb, doublereal *resid, doublereal *rnorm, doublereal *v, integer *ldv, doublereal *h__, integer *ldh, integer *ipntr, doublereal *workd, integer *info, ftnlen bmat_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: second_ 14 1 6 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: dgetv0_ 14 14 4 13 4 12 4 4 7 4 7 7 4 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlanhs_ 7 6 13 4 7 4 7 124 */
/*:ref: dmout_ 14 8 4 4 4 7 4 4 13 124 */
extern int dnapps_(integer *n, integer *kev, integer *np, doublereal *shiftr, doublereal *shifti, doublereal *v, integer *ldv, doublereal *h__, integer *ldh, doublereal *resid, doublereal *q, integer *ldq, doublereal *workl, doublereal *workd);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: second_ 14 1 6 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: dlanhs_ 7 6 13 4 7 4 7 124 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dmout_ 14 8 4 4 4 7 4 4 13 124 */
extern int dnaup2_(integer *ido, char *bmat, integer *n, char *which, integer *nev, integer *np, doublereal *tol, doublereal *resid, integer *mode, integer *iupd, integer *ishift, integer *mxiter, doublereal *v, integer *ldv, doublereal *h__, integer *ldh, doublereal *ritzr, doublereal *ritzi, doublereal *bounds, doublereal *q, integer *ldq, doublereal *workl, integer *ipntr, doublereal *workd, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dgetv0_ 14 14 4 13 4 12 4 4 7 4 7 7 4 7 4 124 */
/*:ref: dnaitr_ 14 16 4 13 4 4 4 4 7 7 7 4 7 4 4 7 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: dneigh_ 14 11 7 4 7 4 7 7 7 7 4 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dngets_ 14 10 4 13 4 4 7 7 7 7 7 124 */
/*:ref: dnconv_ 14 6 4 7 7 7 7 4 */
/*:ref: dsortc_ 14 7 13 12 4 7 7 7 124 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dnapps_ 14 14 4 4 4 7 7 7 4 7 4 7 7 4 7 7 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dmout_ 14 8 4 4 4 7 4 4 13 124 */
extern int dnaupd_(integer *ido, char *bmat, integer *n, char *which, integer *nev, doublereal *tol, doublereal *resid, integer *ncv, doublereal *v, integer *ldv, integer *iparam, integer *ipntr, doublereal *workd, doublereal *workl, integer *lworkl, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dstatn_ 14 0 */
/*:ref: second_ 14 1 6 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dnaup2_ 14 27 4 13 4 13 4 4 7 7 4 4 4 4 7 4 7 4 7 7 7 7 4 7 4 7 4 124 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
extern int dnconv_(integer *n, doublereal *ritzr, doublereal *ritzi, doublereal *bounds, doublereal *tol, integer *nconv);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlapy2_ 7 2 7 7 */
extern int dneigh_(doublereal *rnorm, integer *n, doublereal *h__, integer *ldh, doublereal *ritzr, doublereal *ritzi, doublereal *bounds, doublereal *q, integer *ldq, doublereal *workl, integer *ierr);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dmout_ 14 8 4 4 4 7 4 4 13 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dlaqrb_ 14 10 12 4 4 4 7 4 7 7 7 4 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: dtrevc_ 14 16 13 13 12 4 7 4 7 4 7 4 4 4 7 4 124 124 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
extern int dneupd_(logical *rvec, char *howmny, logical *select, doublereal *dr, doublereal *di, doublereal *z__, integer *ldz, doublereal *sigmar, doublereal *sigmai, doublereal *workev, char *bmat, integer *n, char *which, integer *nev, doublereal *tol, doublereal *resid, integer *ncv, doublereal *v, integer *ldv, integer *iparam, integer *ipntr, doublereal *workd, doublereal *workl, integer *lworkl, integer *info, ftnlen howmny_len, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: dngets_ 14 10 4 13 4 4 7 7 7 7 7 124 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlahqr_ 14 14 12 12 4 4 4 7 4 7 7 4 4 7 4 4 */
/*:ref: dmout_ 14 8 4 4 4 7 4 4 13 124 */
/*:ref: dtrsen_ 14 20 13 13 12 4 7 4 7 4 7 7 4 7 7 7 4 4 4 4 124 124 */
/*:ref: dgeqr2_ 14 7 4 4 7 4 7 7 4 */
/*:ref: dorm2r_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dtrevc_ 14 16 13 13 12 4 7 4 7 4 7 4 4 4 7 4 124 124 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dtrmm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
extern int dngets_(integer *ishift, char *which, integer *kev, integer *np, doublereal *ritzr, doublereal *ritzi, doublereal *bounds, doublereal *shiftr, doublereal *shifti, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dsortc_ 14 7 13 12 4 7 7 7 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
extern int dsaitr_(integer *ido, char *bmat, integer *n, integer *k, integer *np, integer *mode, doublereal *resid, doublereal *rnorm, doublereal *v, integer *ldv, doublereal *h__, integer *ldh, integer *ipntr, doublereal *workd, integer *info, ftnlen bmat_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: second_ 14 1 6 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: dgetv0_ 14 14 4 13 4 12 4 4 7 4 7 7 4 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
extern int dsapps_(integer *n, integer *kev, integer *np, doublereal *shift, doublereal *v, integer *ldv, doublereal *h__, integer *ldh, doublereal *resid, doublereal *q, integer *ldq, doublereal *workd);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
extern int dsaup2_(integer *ido, char *bmat, integer *n, char *which, integer *nev, integer *np, doublereal *tol, doublereal *resid, integer *mode, integer *iupd, integer *ishift, integer *mxiter, doublereal *v, integer *ldv, doublereal *h__, integer *ldh, doublereal *ritz, doublereal *bounds, doublereal *q, integer *ldq, doublereal *workl, integer *ipntr, doublereal *workd, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dgetv0_ 14 14 4 13 4 12 4 4 7 4 7 7 4 7 4 124 */
/*:ref: dsaitr_ 14 16 4 13 4 4 4 4 7 7 7 4 7 4 4 7 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: dseigt_ 14 8 7 4 7 4 7 7 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsgets_ 14 8 4 13 4 4 7 7 7 124 */
/*:ref: dsconv_ 14 5 4 7 7 7 4 */
/*:ref: dsortr_ 14 6 13 12 4 7 7 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dsapps_ 14 12 4 4 4 7 7 4 7 4 7 7 4 7 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
extern int dsaupd_(integer *ido, char *bmat, integer *n, char *which, integer *nev, doublereal *tol, doublereal *resid, integer *ncv, doublereal *v, integer *ldv, integer *iparam, integer *ipntr, doublereal *workd, doublereal *workl, integer *lworkl, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dstats_ 14 0 */
/*:ref: second_ 14 1 6 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dsaup2_ 14 26 4 13 4 13 4 4 7 7 4 4 4 4 7 4 7 4 7 7 7 4 7 4 7 4 124 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
extern int dsconv_(integer *n, doublereal *ritz, doublereal *bounds, doublereal *tol, integer *nconv);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dlamch_ 7 2 13 124 */
extern int dseigt_(doublereal *rnorm, integer *n, doublereal *h__, integer *ldh, doublereal *eig, doublereal *bounds, doublereal *workl, integer *ierr);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dstqrb_ 14 6 4 7 7 7 7 4 */
extern int dsesrt_(char *which, logical *apply, integer *n, doublereal *x, integer *na, doublereal *a, integer *lda, ftnlen which_len);
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dseupd_(logical *rvec, char *howmny, logical *select, doublereal *d__, doublereal *z__, integer *ldz, doublereal *sigma, char *bmat, integer *n, char *which, integer *nev, doublereal *tol, doublereal *resid, integer *ncv, doublereal *v, integer *ldv, integer *iparam, integer *ipntr, doublereal *workd, doublereal *workl, integer *lworkl, integer *info, ftnlen howmny_len, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: dsgets_ 14 8 4 13 4 4 7 7 7 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dsesrt_ 14 8 13 12 4 7 4 7 4 124 */
/*:ref: dsortr_ 14 6 13 12 4 7 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dgeqr2_ 14 7 4 4 7 4 7 7 4 */
/*:ref: dorm2r_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
extern int dsgets_(integer *ishift, char *which, integer *kev, integer *np, doublereal *ritz, doublereal *bounds, doublereal *shifts, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dsortr_ 14 6 13 12 4 7 7 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
extern int dsortc_(char *which, logical *apply, integer *n, doublereal *xreal, doublereal *ximag, doublereal *y, ftnlen which_len);
/*:ref: dlapy2_ 7 2 7 7 */
extern int dsortr_(char *which, logical *apply, integer *n, doublereal *x1, doublereal *x2, ftnlen which_len);
extern int dstatn_(void);
/* comlen timing_ 124 */
extern int dstats_(void);
/* comlen timing_ 124 */
extern int dstqrb_(integer *n, doublereal *d__, doublereal *e, doublereal *z__, doublereal *work, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaev2_ 14 7 7 7 7 7 7 7 7 */
/*:ref: dlae2_ 14 5 7 7 7 7 7 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: dlasr_ 14 12 13 13 13 4 4 7 7 7 4 124 124 124 */
/*:ref: dlasrt_ 14 5 13 4 7 4 124 */
extern int sgetv0_(integer *ido, char *bmat, integer *itry, logical *initv, integer *n, integer *j, real *v, integer *ldv, real *resid, real *rnorm, integer *ipntr, real *workd, integer *ierr, ftnlen bmat_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: slarnv_ 14 4 4 4 4 6 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
extern int slaqrb_(logical *wantt, integer *n, integer *ilo, integer *ihi, real *h__, integer *ldh, real *wr, real *wi, real *z__, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slanhs_ 6 6 13 4 6 4 6 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slanv2_ 14 10 6 6 6 6 6 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
extern int snaitr_(integer *ido, char *bmat, integer *n, integer *k, integer *np, integer *nb, real *resid, real *rnorm, real *v, integer *ldv, real *h__, integer *ldh, integer *ipntr, real *workd, integer *info, ftnlen bmat_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: second_ 14 1 6 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: sgetv0_ 14 14 4 13 4 12 4 4 6 4 6 6 4 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slanhs_ 6 6 13 4 6 4 6 124 */
/*:ref: smout_ 14 8 4 4 4 6 4 4 13 124 */
extern int snapps_(integer *n, integer *kev, integer *np, real *shiftr, real *shifti, real *v, integer *ldv, real *h__, integer *ldh, real *resid, real *q, integer *ldq, real *workl, real *workd);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: second_ 14 1 6 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: slanhs_ 6 6 13 4 6 4 6 124 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: smout_ 14 8 4 4 4 6 4 4 13 124 */
extern int snaup2_(integer *ido, char *bmat, integer *n, char *which, integer *nev, integer *np, real *tol, real *resid, integer *mode, integer *iupd, integer *ishift, integer *mxiter, real *v, integer *ldv, real *h__, integer *ldh, real *ritzr, real *ritzi, real *bounds, real *q, integer *ldq, real *workl, integer *ipntr, real *workd, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: sgetv0_ 14 14 4 13 4 12 4 4 6 4 6 6 4 6 4 124 */
/*:ref: snaitr_ 14 16 4 13 4 4 4 4 6 6 6 4 6 4 4 6 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: sneigh_ 14 11 6 4 6 4 6 6 6 6 4 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sngets_ 14 10 4 13 4 4 6 6 6 6 6 124 */
/*:ref: snconv_ 14 6 4 6 6 6 6 4 */
/*:ref: ssortc_ 14 7 13 12 4 6 6 6 124 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: snapps_ 14 14 4 4 4 6 6 6 4 6 4 6 6 4 6 6 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: smout_ 14 8 4 4 4 6 4 4 13 124 */
extern int snaupd_(integer *ido, char *bmat, integer *n, char *which, integer *nev, real *tol, real *resid, integer *ncv, real *v, integer *ldv, integer *iparam, integer *ipntr, real *workd, real *workl, integer *lworkl, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: sstatn_ 14 0 */
/*:ref: second_ 14 1 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: snaup2_ 14 27 4 13 4 13 4 4 6 6 4 4 4 4 6 4 6 4 6 6 6 6 4 6 4 6 4 124 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
extern int snconv_(integer *n, real *ritzr, real *ritzi, real *bounds, real *tol, integer *nconv);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slapy2_ 6 2 6 6 */
extern int sneigh_(real *rnorm, integer *n, real *h__, integer *ldh, real *ritzr, real *ritzi, real *bounds, real *q, integer *ldq, real *workl, integer *ierr);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: smout_ 14 8 4 4 4 6 4 4 13 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: slaqrb_ 14 10 12 4 4 4 6 4 6 6 6 4 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: strevc_ 14 16 13 13 12 4 6 4 6 4 6 4 4 4 6 4 124 124 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
extern int sneupd_(logical *rvec, char *howmny, logical *select, real *dr, real *di, real *z__, integer *ldz, real *sigmar, real *sigmai, real *workev, char *bmat, integer *n, char *which, integer *nev, real *tol, real *resid, integer *ncv, real *v, integer *ldv, integer *iparam, integer *ipntr, real *workd, real *workl, integer *lworkl, integer *info, ftnlen howmny_len, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: sngets_ 14 10 4 13 4 4 6 6 6 6 6 124 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slahqr_ 14 14 12 12 4 4 4 6 4 6 6 4 4 6 4 4 */
/*:ref: smout_ 14 8 4 4 4 6 4 4 13 124 */
/*:ref: strsen_ 14 20 13 13 12 4 6 4 6 4 6 6 4 6 6 6 4 4 4 4 124 124 */
/*:ref: sgeqr2_ 14 7 4 4 6 4 6 6 4 */
/*:ref: sorm2r_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: strevc_ 14 16 13 13 12 4 6 4 6 4 6 4 4 4 6 4 124 124 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: strmm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
extern int sngets_(integer *ishift, char *which, integer *kev, integer *np, real *ritzr, real *ritzi, real *bounds, real *shiftr, real *shifti, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: ssortc_ 14 7 13 12 4 6 6 6 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
extern int ssaitr_(integer *ido, char *bmat, integer *n, integer *k, integer *np, integer *mode, real *resid, real *rnorm, real *v, integer *ldv, real *h__, integer *ldh, integer *ipntr, real *workd, integer *info, ftnlen bmat_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: second_ 14 1 6 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: sgetv0_ 14 14 4 13 4 12 4 4 6 4 6 6 4 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
extern int ssapps_(integer *n, integer *kev, integer *np, real *shift, real *v, integer *ldv, real *h__, integer *ldh, real *resid, real *q, integer *ldq, real *workd);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: second_ 14 1 6 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
extern int ssaup2_(integer *ido, char *bmat, integer *n, char *which, integer *nev, integer *np, real *tol, real *resid, integer *mode, integer *iupd, integer *ishift, integer *mxiter, real *v, integer *ldv, real *h__, integer *ldh, real *ritz, real *bounds, real *q, integer *ldq, real *workl, integer *ipntr, real *workd, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: sgetv0_ 14 14 4 13 4 12 4 4 6 4 6 6 4 6 4 124 */
/*:ref: ssaitr_ 14 16 4 13 4 4 4 4 6 6 6 4 6 4 4 6 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: sseigt_ 14 8 6 4 6 4 6 6 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssgets_ 14 8 4 13 4 4 6 6 6 124 */
/*:ref: ssconv_ 14 5 4 6 6 6 4 */
/*:ref: ssortr_ 14 6 13 12 4 6 6 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: ssapps_ 14 12 4 4 4 6 6 4 6 4 6 6 4 6 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
extern int ssaupd_(integer *ido, char *bmat, integer *n, char *which, integer *nev, real *tol, real *resid, integer *ncv, real *v, integer *ldv, integer *iparam, integer *ipntr, real *workd, real *workl, integer *lworkl, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: sstats_ 14 0 */
/*:ref: second_ 14 1 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ssaup2_ 14 26 4 13 4 13 4 4 6 6 4 4 4 4 6 4 6 4 6 6 6 4 6 4 6 4 124 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
extern int ssconv_(integer *n, real *ritz, real *bounds, real *tol, integer *nconv);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: slamch_ 6 2 13 124 */
extern int sseigt_(real *rnorm, integer *n, real *h__, integer *ldh, real *eig, real *bounds, real *workl, integer *ierr);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sstqrb_ 14 6 4 6 6 6 6 4 */
extern int ssesrt_(char *which, logical *apply, integer *n, real *x, integer *na, real *a, integer *lda, ftnlen which_len);
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int sseupd_(logical *rvec, char *howmny, logical *select, real *d__, real *z__, integer *ldz, real *sigma, char *bmat, integer *n, char *which, integer *nev, real *tol, real *resid, integer *ncv, real *v, integer *ldv, integer *iparam, integer *ipntr, real *workd, real *workl, integer *lworkl, integer *info, ftnlen howmny_len, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
/*:ref: ssgets_ 14 8 4 13 4 4 6 6 6 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: ssesrt_ 14 8 13 12 4 6 4 6 4 124 */
/*:ref: ssortr_ 14 6 13 12 4 6 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sgeqr2_ 14 7 4 4 6 4 6 6 4 */
/*:ref: sorm2r_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
extern int ssgets_(integer *ishift, char *which, integer *kev, integer *np, real *ritz, real *bounds, real *shifts, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: ssortr_ 14 6 13 12 4 6 6 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: svout_ 14 6 4 4 6 4 13 124 */
extern int ssortc_(char *which, logical *apply, integer *n, real *xreal, real *ximag, real *y, ftnlen which_len);
/*:ref: slapy2_ 6 2 6 6 */
extern int ssortr_(char *which, logical *apply, integer *n, real *x1, real *x2, ftnlen which_len);
extern int sstatn_(void);
/* comlen timing_ 124 */
extern int sstats_(void);
/* comlen timing_ 124 */
extern int sstqrb_(integer *n, real *d__, real *e, real *z__, real *work, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaev2_ 14 7 6 6 6 6 6 6 6 */
/*:ref: slae2_ 14 5 6 6 6 6 6 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: slasr_ 14 12 13 13 13 4 4 6 6 6 4 124 124 124 */
/*:ref: slasrt_ 14 5 13 4 6 4 124 */
extern int zgetv0_(integer *ido, char *bmat, integer *itry, logical *initv, integer *n, integer *j, doublecomplex *v, integer *ldv, doublecomplex *resid, doublereal *rnorm, integer *ipntr, doublecomplex *workd, integer *ierr, ftnlen bmat_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: zlarnv_ 14 4 4 4 4 9 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: zvout_ 14 6 4 4 9 4 13 124 */
extern int znaitr_(integer *ido, char *bmat, integer *n, integer *k, integer *np, integer *nb, doublecomplex *resid, doublereal *rnorm, doublecomplex *v, integer *ldv, doublecomplex *h__, integer *ldh, integer *ipntr, doublecomplex *workd, integer *info, ftnlen bmat_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: second_ 14 1 6 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: zgetv0_ 14 14 4 13 4 12 4 4 9 4 9 7 4 9 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zvout_ 14 6 4 4 9 4 13 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlanhs_ 7 6 13 4 9 4 9 124 */
/*:ref: zmout_ 14 8 4 4 4 9 4 4 13 124 */
extern int znapps_(integer *n, integer *kev, integer *np, doublecomplex *shift, doublecomplex *v, integer *ldv, doublecomplex *h__, integer *ldh, doublecomplex *resid, doublecomplex *q, integer *ldq, doublecomplex *workl, doublecomplex *workd);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: second_ 14 1 6 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: zvout_ 14 6 4 4 9 4 13 124 */
/*:ref: zlanhs_ 7 6 13 4 9 4 9 124 */
/*:ref: zlartg_ 14 5 9 9 7 9 9 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zmout_ 14 8 4 4 4 9 4 4 13 124 */
extern int znaup2_(integer *ido, char *bmat, integer *n, char *which, integer *nev, integer *np, doublereal *tol, doublecomplex *resid, integer *mode, integer *iupd, integer *ishift, integer *mxiter, doublecomplex *v, integer *ldv, doublecomplex *h__, integer *ldh, doublecomplex *ritz, doublecomplex *bounds, doublecomplex *q, integer *ldq, doublecomplex *workl, integer *ipntr, doublecomplex *workd, doublereal *rwork, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zgetv0_ 14 14 4 13 4 12 4 4 9 4 9 7 4 9 4 124 */
/*:ref: znaitr_ 14 16 4 13 4 4 4 4 9 7 9 4 9 4 4 9 4 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: dvout_ 14 6 4 4 7 4 13 124 */
/*:ref: zneigh_ 14 11 7 4 9 4 9 9 9 4 9 7 4 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zngets_ 14 7 4 13 4 4 9 9 124 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: zvout_ 14 6 4 4 9 4 13 124 */
/*:ref: zsortc_ 14 6 13 12 4 9 9 124 */
/*:ref: znapps_ 14 13 4 4 4 9 9 4 9 4 9 9 4 9 9 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zmout_ 14 8 4 4 4 9 4 4 13 124 */
extern int znaupd_(integer *ido, char *bmat, integer *n, char *which, integer *nev, doublereal *tol, doublecomplex *resid, integer *ncv, doublecomplex *v, integer *ldv, integer *iparam, integer *ipntr, doublecomplex *workd, doublecomplex *workl, integer *lworkl, doublereal *rwork, integer *info, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: zstatn_ 14 0 */
/*:ref: second_ 14 1 6 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: znaup2_ 14 27 4 13 4 13 4 4 7 9 4 4 4 4 9 4 9 4 9 9 9 4 9 4 9 7 4 124 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: zvout_ 14 6 4 4 9 4 13 124 */
extern int zneigh_(doublereal *rnorm, integer *n, doublecomplex *h__, integer *ldh, doublecomplex *ritz, doublecomplex *bounds, doublecomplex *q, integer *ldq, doublecomplex *workl, doublereal *rwork, integer *ierr);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: zmout_ 14 8 4 4 4 9 4 4 13 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlahqr_ 14 13 12 12 4 4 4 9 4 9 4 4 9 4 4 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zvout_ 14 6 4 4 9 4 13 124 */
/*:ref: ztrevc_ 14 17 13 13 12 4 9 4 9 4 9 4 4 4 9 7 4 124 124 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
extern int zneupd_(logical *rvec, char *howmny, logical *select, doublecomplex *d__, doublecomplex *z__, integer *ldz, doublecomplex *sigma, doublecomplex *workev, char *bmat, integer *n, char *which, integer *nev, doublereal *tol, doublecomplex *resid, integer *ncv, doublecomplex *v, integer *ldv, integer *iparam, integer *ipntr, doublecomplex *workd, doublecomplex *workl, integer *lworkl, doublereal *rwork, integer *info, ftnlen howmny_len, ftnlen bmat_len, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zvout_ 14 6 4 4 9 4 13 124 */
/*:ref: zngets_ 14 7 4 13 4 4 9 9 124 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlahqr_ 14 13 12 12 4 4 4 9 4 9 4 4 9 4 4 */
/*:ref: zmout_ 14 8 4 4 4 9 4 4 13 124 */
/*:ref: ztrsen_ 14 17 13 13 12 4 9 4 9 4 9 4 7 7 9 4 4 124 124 */
/*:ref: zgeqr2_ 14 7 4 4 9 4 9 9 4 */
/*:ref: zunm2r_ 14 14 13 13 4 4 4 9 4 9 9 4 9 4 124 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: ztrevc_ 14 17 13 13 12 4 9 4 9 4 9 4 4 4 9 7 4 124 124 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: ztrmm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
extern int zngets_(integer *ishift, char *which, integer *kev, integer *np, doublecomplex *ritz, doublecomplex *bounds, ftnlen which_len);
/* comlen debug_ 96 */
/* comlen timing_ 124 */
/*:ref: second_ 14 1 6 */
/*:ref: zsortc_ 14 6 13 12 4 9 9 124 */
/*:ref: ivout_ 14 6 4 4 4 4 13 124 */
/*:ref: zvout_ 14 6 4 4 9 4 13 124 */
extern int zsortc_(char *which, logical *apply, integer *n, doublecomplex *x, doublecomplex *y, ftnlen which_len);
/*:ref: dlapy2_ 7 2 7 7 */
extern int zstatn_(void);
/* comlen timing_ 124 */
extern int cmout_(integer *lout, integer *m, integer *n, complex *a, integer *lda, integer *idigit, char *ifmt, ftnlen ifmt_len);
extern int cvout_(integer *lout, integer *n, complex *cx, integer *idigit, char *ifmt, ftnlen ifmt_len);
extern int dmout_(integer *lout, integer *m, integer *n, doublereal *a, integer *lda, integer *idigit, char *ifmt, ftnlen ifmt_len);
extern int dvout_(integer *lout, integer *n, doublereal *sx, integer *idigit, char *ifmt, ftnlen ifmt_len);
extern integer icnteq_(integer *n, integer *array, integer *value);
extern int icopy_(integer *n, integer *lx, integer *incx, integer *ly, integer *incy);
extern int iset_(integer *n, integer *value, integer *array, integer *inc);
extern int iswap_(integer *n, integer *sx, integer *incx, integer *sy, integer *incy);
extern int ivout_(integer *lout, integer *n, integer *ix, integer *idigit, char *ifmt, ftnlen ifmt_len);
extern int second_(real *t);
/*:ref: etime_ 6 1 6 */
extern int smout_(integer *lout, integer *m, integer *n, real *a, integer *lda, integer *idigit, char *ifmt, ftnlen ifmt_len);
extern int svout_(integer *lout, integer *n, real *sx, integer *idigit, char *ifmt, ftnlen ifmt_len);
extern int zmout_(integer *lout, integer *m, integer *n, doublecomplex *a, integer *lda, integer *idigit, char *ifmt, ftnlen ifmt_len);
extern int zvout_(integer *lout, integer *n, doublecomplex *cx, integer *idigit, char *ifmt, ftnlen ifmt_len);
