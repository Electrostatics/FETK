extern int caxpy_(integer *n, realcomplex *ca, realcomplex *cx, integer *incx, realcomplex *cy, integer *incy);
extern int ccopy_(integer *n, realcomplex *cx, integer *incx, realcomplex *cy, integer *incy);
extern C_f cdotc_(realcomplex * ret_val, integer *n, realcomplex *cx, integer *incx, realcomplex *cy, integer *incy);
extern C_f cdotu_(realcomplex * ret_val, integer *n, realcomplex *cx, integer *incx, realcomplex *cy, integer *incy);
extern int cgbmv_(char *trans, integer *m, integer *n, integer *kl, integer *ku, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *x, integer *incx, realcomplex *beta, realcomplex *y, integer *incy, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cgemm_(char *transa, char *transb, integer *m, integer *n, integer *k, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *b, integer *ldb, realcomplex *beta, realcomplex *c__, integer *ldc, ftnlen transa_len, ftnlen transb_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cgemv_(char *trans, integer *m, integer *n, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *x, integer *incx, realcomplex *beta, realcomplex *y, integer *incy, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cgerc_(integer *m, integer *n, realcomplex *alpha, realcomplex *x, integer *incx, realcomplex *y, integer *incy, realcomplex *a, integer *lda);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cgeru_(integer *m, integer *n, realcomplex *alpha, realcomplex *x, integer *incx, realcomplex *y, integer *incy, realcomplex *a, integer *lda);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int chbmv_(char *uplo, integer *n, integer *k, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *x, integer *incx, realcomplex *beta, realcomplex *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int chemm_(char *side, char *uplo, integer *m, integer *n, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *b, integer *ldb, realcomplex *beta, realcomplex *c__, integer *ldc, ftnlen side_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int chemv_(char *uplo, integer *n, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *x, integer *incx, realcomplex *beta, realcomplex *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cher_(char *uplo, integer *n, real *alpha, realcomplex *x, integer *incx, realcomplex *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cher2_(char *uplo, integer *n, realcomplex *alpha, realcomplex *x, integer *incx, realcomplex *y, integer *incy, realcomplex *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cher2k_(char *uplo, char *trans, integer *n, integer *k, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *b, integer *ldb, real *beta, realcomplex *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cherk_(char *uplo, char *trans, integer *n, integer *k, real *alpha, realcomplex *a, integer *lda, real *beta, realcomplex *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int chpmv_(char *uplo, integer *n, realcomplex *alpha, realcomplex *ap, realcomplex *x, integer *incx, realcomplex *beta, realcomplex *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int chpr_(char *uplo, integer *n, real *alpha, realcomplex *x, integer *incx, realcomplex *ap, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int chpr2_(char *uplo, integer *n, realcomplex *alpha, realcomplex *x, integer *incx, realcomplex *y, integer *incy, realcomplex *ap, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int crotg_(realcomplex *ca, realcomplex *cb, real *c__, realcomplex *s);
extern int cscal_(integer *n, realcomplex *ca, realcomplex *cx, integer *incx);
extern int csrot_(integer *n, realcomplex *cx, integer *incx, realcomplex *cy, integer *incy, real *c__, real *s);
extern int csscal_(integer *n, real *sa, realcomplex *cx, integer *incx);
extern int cswap_(integer *n, realcomplex *cx, integer *incx, realcomplex *cy, integer *incy);
extern int csymm_(char *side, char *uplo, integer *m, integer *n, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *b, integer *ldb, realcomplex *beta, realcomplex *c__, integer *ldc, ftnlen side_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int csyr2k_(char *uplo, char *trans, integer *n, integer *k, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *b, integer *ldb, realcomplex *beta, realcomplex *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int csyrk_(char *uplo, char *trans, integer *n, integer *k, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *beta, realcomplex *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ctbmv_(char *uplo, char *trans, char *diag, integer *n, integer *k, realcomplex *a, integer *lda, realcomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ctbsv_(char *uplo, char *trans, char *diag, integer *n, integer *k, realcomplex *a, integer *lda, realcomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ctpmv_(char *uplo, char *trans, char *diag, integer *n, realcomplex *ap, realcomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ctpsv_(char *uplo, char *trans, char *diag, integer *n, realcomplex *ap, realcomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ctrmm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *b, integer *ldb, ftnlen side_len, ftnlen uplo_len, ftnlen transa_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ctrmv_(char *uplo, char *trans, char *diag, integer *n, realcomplex *a, integer *lda, realcomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ctrsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, realcomplex *alpha, realcomplex *a, integer *lda, realcomplex *b, integer *ldb, ftnlen side_len, ftnlen uplo_len, ftnlen transa_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ctrsv_(char *uplo, char *trans, char *diag, integer *n, realcomplex *a, integer *lda, realcomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern doublereal dasum_(integer *n, doublereal *dx, integer *incx);
extern int daxpy_(integer *n, doublereal *da, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
extern doublereal dcabs1_(doublecomplex *z__);
extern int dcopy_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
extern doublereal ddot_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
extern int dgbmv_(char *trans, integer *m, integer *n, integer *kl, integer *ku, doublereal *alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dgemm_(char *transa, char *transb, integer *m, integer *n, integer *k, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *beta, doublereal *c__, integer *ldc, ftnlen transa_len, ftnlen transb_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dgemv_(char *trans, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dger_(integer *m, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *a, integer *lda);
/*:ref: xerbla_ 14 3 13 4 124 */
extern doublereal dnrm2_(integer *n, doublereal *x, integer *incx);
extern int drot_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy, doublereal *c__, doublereal *s);
extern int drotg_(doublereal *da, doublereal *db, doublereal *c__, doublereal *s);
extern int drotm_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy, doublereal *dparam);
extern int drotmg_(doublereal *dd1, doublereal *dd2, doublereal *dx1, doublereal *dy1, doublereal *dparam);
extern int dsbmv_(char *uplo, integer *n, integer *k, doublereal *alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dscal_(integer *n, doublereal *da, doublereal *dx, integer *incx);
extern doublereal dsdot_(integer *n, real *sx, integer *incx, real *sy, integer *incy);
extern int dspmv_(char *uplo, integer *n, doublereal *alpha, doublereal *ap, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dspr_(char *uplo, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *ap, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dspr2_(char *uplo, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *ap, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dswap_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
extern int dsymm_(char *side, char *uplo, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *beta, doublereal *c__, integer *ldc, ftnlen side_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dsymv_(char *uplo, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dsyr_(char *uplo, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dsyr2_(char *uplo, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dsyr2k_(char *uplo, char *trans, integer *n, integer *k, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *beta, doublereal *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dsyrk_(char *uplo, char *trans, integer *n, integer *k, doublereal *alpha, doublereal *a, integer *lda, doublereal *beta, doublereal *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dtbmv_(char *uplo, char *trans, char *diag, integer *n, integer *k, doublereal *a, integer *lda, doublereal *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dtbsv_(char *uplo, char *trans, char *diag, integer *n, integer *k, doublereal *a, integer *lda, doublereal *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dtpmv_(char *uplo, char *trans, char *diag, integer *n, doublereal *ap, doublereal *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dtpsv_(char *uplo, char *trans, char *diag, integer *n, doublereal *ap, doublereal *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dtrmm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, ftnlen side_len, ftnlen uplo_len, ftnlen transa_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dtrmv_(char *uplo, char *trans, char *diag, integer *n, doublereal *a, integer *lda, doublereal *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dtrsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, ftnlen side_len, ftnlen uplo_len, ftnlen transa_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dtrsv_(char *uplo, char *trans, char *diag, integer *n, doublereal *a, integer *lda, doublereal *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern doublereal dzasum_(integer *n, doublecomplex *zx, integer *incx);
/*:ref: dcabs1_ 7 1 9 */
extern doublereal dznrm2_(integer *n, doublecomplex *x, integer *incx);
extern integer icamax_(integer *n, realcomplex *cx, integer *incx);
extern integer idamax_(integer *n, doublereal *dx, integer *incx);
extern integer isamax_(integer *n, real *sx, integer *incx);
extern integer izamax_(integer *n, doublecomplex *zx, integer *incx);
/*:ref: dcabs1_ 7 1 9 */
extern logical lsame_(char *ca, char *cb, ftnlen ca_len, ftnlen cb_len);
extern E_f sasum_(integer *n, real *sx, integer *incx);
extern int saxpy_(integer *n, real *sa, real *sx, integer *incx, real *sy, integer *incy);
extern E_f scasum_(integer *n, realcomplex *cx, integer *incx);
extern E_f scnrm2_(integer *n, realcomplex *x, integer *incx);
extern int scopy_(integer *n, real *sx, integer *incx, real *sy, integer *incy);
extern E_f sdot_(integer *n, real *sx, integer *incx, real *sy, integer *incy);
extern E_f sdsdot_(integer *n, real *sb, real *sx, integer *incx, real *sy, integer *incy);
extern int sgbmv_(char *trans, integer *m, integer *n, integer *kl, integer *ku, real *alpha, real *a, integer *lda, real *x, integer *incx, real *beta, real *y, integer *incy, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int sgemm_(char *transa, char *transb, integer *m, integer *n, integer *k, real *alpha, real *a, integer *lda, real *b, integer *ldb, real *beta, real *c__, integer *ldc, ftnlen transa_len, ftnlen transb_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int sgemv_(char *trans, integer *m, integer *n, real *alpha, real *a, integer *lda, real *x, integer *incx, real *beta, real *y, integer *incy, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int sger_(integer *m, integer *n, real *alpha, real *x, integer *incx, real *y, integer *incy, real *a, integer *lda);
/*:ref: xerbla_ 14 3 13 4 124 */
extern E_f snrm2_(integer *n, real *x, integer *incx);
extern int srot_(integer *n, real *sx, integer *incx, real *sy, integer *incy, real *c__, real *s);
extern int srotg_(real *sa, real *sb, real *c__, real *s);
extern int srotm_(integer *n, real *sx, integer *incx, real *sy, integer *incy, real *sparam);
extern int srotmg_(real *sd1, real *sd2, real *sx1, real *sy1, real *sparam);
extern int ssbmv_(char *uplo, integer *n, integer *k, real *alpha, real *a, integer *lda, real *x, integer *incx, real *beta, real *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int sscal_(integer *n, real *sa, real *sx, integer *incx);
extern int sspmv_(char *uplo, integer *n, real *alpha, real *ap, real *x, integer *incx, real *beta, real *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int sspr_(char *uplo, integer *n, real *alpha, real *x, integer *incx, real *ap, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int sspr2_(char *uplo, integer *n, real *alpha, real *x, integer *incx, real *y, integer *incy, real *ap, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int sswap_(integer *n, real *sx, integer *incx, real *sy, integer *incy);
extern int ssymm_(char *side, char *uplo, integer *m, integer *n, real *alpha, real *a, integer *lda, real *b, integer *ldb, real *beta, real *c__, integer *ldc, ftnlen side_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ssymv_(char *uplo, integer *n, real *alpha, real *a, integer *lda, real *x, integer *incx, real *beta, real *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ssyr_(char *uplo, integer *n, real *alpha, real *x, integer *incx, real *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ssyr2_(char *uplo, integer *n, real *alpha, real *x, integer *incx, real *y, integer *incy, real *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ssyr2k_(char *uplo, char *trans, integer *n, integer *k, real *alpha, real *a, integer *lda, real *b, integer *ldb, real *beta, real *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ssyrk_(char *uplo, char *trans, integer *n, integer *k, real *alpha, real *a, integer *lda, real *beta, real *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int stbmv_(char *uplo, char *trans, char *diag, integer *n, integer *k, real *a, integer *lda, real *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int stbsv_(char *uplo, char *trans, char *diag, integer *n, integer *k, real *a, integer *lda, real *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int stpmv_(char *uplo, char *trans, char *diag, integer *n, real *ap, real *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int stpsv_(char *uplo, char *trans, char *diag, integer *n, real *ap, real *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int strmm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, real *alpha, real *a, integer *lda, real *b, integer *ldb, ftnlen side_len, ftnlen uplo_len, ftnlen transa_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int strmv_(char *uplo, char *trans, char *diag, integer *n, real *a, integer *lda, real *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int strsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, real *alpha, real *a, integer *lda, real *b, integer *ldb, ftnlen side_len, ftnlen uplo_len, ftnlen transa_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int strsv_(char *uplo, char *trans, char *diag, integer *n, real *a, integer *lda, real *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int xerbla_(char *srname, integer *info, ftnlen srname_len);
extern int zaxpy_(integer *n, doublecomplex *za, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);
/*:ref: dcabs1_ 7 1 9 */
extern int zcopy_(integer *n, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);
extern Z_f zdotc_(doublecomplex * ret_val, integer *n, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);
extern Z_f zdotu_(doublecomplex * ret_val, integer *n, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);
extern int zdrot_(integer *n, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy, doublereal *c__, doublereal *s);
extern int zdscal_(integer *n, doublereal *da, doublecomplex *zx, integer *incx);
extern int zgbmv_(char *trans, integer *m, integer *n, integer *kl, integer *ku, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zgemm_(char *transa, char *transb, integer *m, integer *n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *beta, doublecomplex *c__, integer *ldc, ftnlen transa_len, ftnlen transb_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zgemv_(char *trans, integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zgerc_(integer *m, integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublecomplex *a, integer *lda);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zgeru_(integer *m, integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublecomplex *a, integer *lda);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zhbmv_(char *uplo, integer *n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zhemm_(char *side, char *uplo, integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *beta, doublecomplex *c__, integer *ldc, ftnlen side_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zhemv_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zher_(char *uplo, integer *n, doublereal *alpha, doublecomplex *x, integer *incx, doublecomplex *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zher2_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublecomplex *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zher2k_(char *uplo, char *trans, integer *n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublereal *beta, doublecomplex *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zherk_(char *uplo, char *trans, integer *n, integer *k, doublereal *alpha, doublecomplex *a, integer *lda, doublereal *beta, doublecomplex *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zhpmv_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *ap, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zhpr_(char *uplo, integer *n, doublereal *alpha, doublecomplex *x, integer *incx, doublecomplex *ap, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zhpr2_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublecomplex *ap, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zrotg_(doublecomplex *ca, doublecomplex *cb, doublereal *c__, doublecomplex *s);
extern int zscal_(integer *n, doublecomplex *za, doublecomplex *zx, integer *incx);
extern int zswap_(integer *n, doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);
extern int zsymm_(char *side, char *uplo, integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *beta, doublecomplex *c__, integer *ldc, ftnlen side_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zsyr2k_(char *uplo, char *trans, integer *n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *beta, doublecomplex *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zsyrk_(char *uplo, char *trans, integer *n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *beta, doublecomplex *c__, integer *ldc, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ztbmv_(char *uplo, char *trans, char *diag, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ztbsv_(char *uplo, char *trans, char *diag, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ztpmv_(char *uplo, char *trans, char *diag, integer *n, doublecomplex *ap, doublecomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ztpsv_(char *uplo, char *trans, char *diag, integer *n, doublecomplex *ap, doublecomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ztrmm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, ftnlen side_len, ftnlen uplo_len, ftnlen transa_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ztrmv_(char *uplo, char *trans, char *diag, integer *n, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ztrsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, ftnlen side_len, ftnlen uplo_len, ftnlen transa_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int ztrsv_(char *uplo, char *trans, char *diag, integer *n, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
