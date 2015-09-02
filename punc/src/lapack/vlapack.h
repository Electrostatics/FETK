extern int cbdsqr_(char *uplo, integer *n, integer *ncvt, integer *nru, integer *ncc, real *d__, real *e, complex *vt, integer *ldvt, complex *u, integer *ldu, complex *c__, integer *ldc, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slasq1_ 14 5 4 6 6 6 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: clasr_ 14 12 13 13 13 4 4 6 6 8 4 124 124 124 */
/*:ref: slasv2_ 14 9 6 6 6 6 6 6 6 6 6 */
/*:ref: csrot_ 14 7 4 8 4 8 4 6 6 */
/*:ref: slas2_ 14 5 6 6 6 6 6 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int cgbbrd_(char *vect, integer *m, integer *n, integer *ncc, integer *kl, integer *ku, complex *ab, integer *ldab, real *d__, real *e, complex *q, integer *ldq, complex *pt, integer *ldpt, complex *c__, integer *ldc, complex *work, real *rwork, integer *info, ftnlen vect_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clargv_ 14 7 4 8 4 8 4 6 4 */
/*:ref: clartv_ 14 8 4 8 4 8 4 6 8 4 */
/*:ref: clartg_ 14 5 8 8 6 8 8 */
/*:ref: crot_ 14 7 4 8 4 8 4 6 8 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int cgbcon_(char *norm, integer *n, integer *kl, integer *ku, complex *ab, integer *ldab, integer *ipiv, real *anorm, real *rcond, complex *work, real *rwork, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clatbs_ 14 16 13 13 13 13 4 4 8 4 8 6 6 4 124 124 124 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csrscl_ 14 4 4 6 8 4 */
extern int cgbequ_(integer *m, integer *n, integer *kl, integer *ku, complex *ab, integer *ldab, real *r__, real *c__, real *rowcnd, real *colcnd, real *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
extern int cgbrfs_(char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, complex *ab, integer *ldab, complex *afb, integer *ldafb, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgbmv_ 14 14 13 4 4 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cgbtrs_ 14 12 13 4 4 4 4 8 4 4 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int cgbsv_(integer *n, integer *kl, integer *ku, integer *nrhs, complex *ab, integer *ldab, integer *ipiv, complex *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgbtrf_ 14 8 4 4 4 4 8 4 4 4 */
/*:ref: cgbtrs_ 14 12 13 4 4 4 4 8 4 4 8 4 4 124 */
extern int cgbsvx_(char *fact, char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, complex *ab, integer *ldab, complex *afb, integer *ldafb, integer *ipiv, char *equed, real *r__, real *c__, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen fact_len, ftnlen trans_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgbequ_ 14 12 4 4 4 4 8 4 6 6 6 6 6 4 */
/*:ref: claqgb_ 14 13 4 4 4 4 8 4 6 6 6 6 6 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgbtrf_ 14 8 4 4 4 4 8 4 4 4 */
/*:ref: clantb_ 6 11 13 13 13 4 4 8 4 6 124 124 124 */
/*:ref: clangb_ 6 8 13 4 4 4 8 4 6 124 */
/*:ref: cgbcon_ 14 13 13 4 4 4 8 4 4 6 6 8 6 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cgbtrs_ 14 12 13 4 4 4 4 8 4 4 8 4 4 124 */
/*:ref: cgbrfs_ 14 20 13 4 4 4 4 8 4 8 4 4 8 4 8 4 6 6 8 6 4 124 */
extern int cgbtf2_(integer *m, integer *n, integer *kl, integer *ku, complex *ab, integer *ldab, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
extern int cgbtrf_(integer *m, integer *n, integer *kl, integer *ku, complex *ab, integer *ldab, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: cgbtf2_ 14 8 4 4 4 4 8 4 4 4 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: claswp_ 14 7 4 8 4 4 4 4 4 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
extern int cgbtrs_(char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, complex *ab, integer *ldab, integer *ipiv, complex *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
/*:ref: ctbsv_ 14 12 13 13 13 4 4 8 4 8 4 124 124 124 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
extern int cgebak_(char *job, char *side, integer *n, integer *ilo, integer *ihi, real *scale, integer *m, complex *v, integer *ldv, integer *info, ftnlen job_len, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int cgebal_(char *job, integer *n, complex *a, integer *lda, integer *ilo, integer *ihi, real *scale, integer *info, ftnlen job_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
extern int cgebd2_(integer *m, integer *n, complex *a, integer *lda, real *d__, real *e, complex *tauq, complex *taup, complex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
extern int cgebrd_(integer *m, integer *n, complex *a, integer *lda, real *d__, real *e, complex *tauq, complex *taup, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clabrd_ 14 13 4 4 4 8 4 6 6 8 8 8 4 8 4 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: cgebd2_ 14 10 4 4 8 4 6 6 8 8 8 4 */
extern int cgecon_(char *norm, integer *n, complex *a, integer *lda, real *anorm, real *rcond, complex *work, real *rwork, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: clatrs_ 14 15 13 13 13 13 4 8 4 8 6 6 4 124 124 124 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csrscl_ 14 4 4 6 8 4 */
extern int cgeequ_(integer *m, integer *n, complex *a, integer *lda, real *r__, real *c__, real *rowcnd, real *colcnd, real *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
extern int cgees_(char *jobvs, char *sort, L_fp select, integer *n, complex *a, integer *lda, integer *sdim, complex *w, complex *vs, integer *ldvs, complex *work, integer *lwork, real *rwork, logical *bwork, integer *info, ftnlen jobvs_len, ftnlen sort_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cgebal_ 14 9 13 4 8 4 4 4 6 4 124 */
/*:ref: cgehrd_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cunghr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: chseqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: ctrsen_ 14 17 13 13 12 4 8 4 8 4 8 4 6 6 8 4 4 124 124 */
/*:ref: cgebak_ 14 12 13 13 4 4 4 6 4 8 4 4 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
extern int cgeesx_(char *jobvs, char *sort, L_fp select, char *sense, integer *n, complex *a, integer *lda, integer *sdim, complex *w, complex *vs, integer *ldvs, real *rconde, real *rcondv, complex *work, integer *lwork, real *rwork, logical *bwork, integer *info, ftnlen jobvs_len, ftnlen sort_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cgebal_ 14 9 13 4 8 4 4 4 6 4 124 */
/*:ref: cgehrd_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cunghr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: chseqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: ctrsen_ 14 17 13 13 12 4 8 4 8 4 8 4 6 6 8 4 4 124 124 */
/*:ref: cgebak_ 14 12 13 13 4 4 4 6 4 8 4 4 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
extern int cgeev_(char *jobvl, char *jobvr, integer *n, complex *a, integer *lda, complex *w, complex *vl, integer *ldvl, complex *vr, integer *ldvr, complex *work, integer *lwork, real *rwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cgebal_ 14 9 13 4 8 4 4 4 6 4 124 */
/*:ref: cgehrd_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cunghr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: chseqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: ctrevc_ 14 17 13 13 12 4 8 4 8 4 8 4 4 4 8 6 4 124 124 */
/*:ref: cgebak_ 14 12 13 13 4 4 4 6 4 8 4 4 124 124 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int cgeevx_(char *balanc, char *jobvl, char *jobvr, char *sense, integer *n, complex *a, integer *lda, complex *w, complex *vl, integer *ldvl, complex *vr, integer *ldvr, integer *ilo, integer *ihi, real *scale, real *abnrm, real *rconde, real *rcondv, complex *work, integer *lwork, real *rwork, integer *info, ftnlen balanc_len, ftnlen jobvl_len, ftnlen jobvr_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cgebal_ 14 9 13 4 8 4 4 4 6 4 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: cgehrd_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cunghr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: chseqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: ctrevc_ 14 17 13 13 12 4 8 4 8 4 8 4 4 4 8 6 4 124 124 */
/*:ref: ctrsna_ 14 20 13 13 12 4 8 4 8 4 8 4 6 6 4 4 8 4 6 4 124 124 */
/*:ref: cgebak_ 14 12 13 13 4 4 4 6 4 8 4 4 124 124 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int cgegs_(char *jobvsl, char *jobvsr, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *alpha, complex *beta, complex *vsl, integer *ldvsl, complex *vsr, integer *ldvsr, complex *work, integer *lwork, real *rwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cggbal_ 14 13 13 4 8 4 8 4 4 4 6 6 6 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: cgghrd_ 14 16 13 13 4 4 4 8 4 8 4 8 4 8 4 4 124 124 */
/*:ref: chgeqz_ 14 23 13 13 13 4 4 4 8 4 8 4 8 8 8 4 8 4 8 4 6 4 124 124 124 */
/*:ref: cggbak_ 14 13 13 13 4 4 4 6 6 4 8 4 4 124 124 */
extern int cgegv_(char *jobvl, char *jobvr, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *alpha, complex *beta, complex *vl, integer *ldvl, complex *vr, integer *ldvr, complex *work, integer *lwork, real *rwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cggbal_ 14 13 13 4 8 4 8 4 4 4 6 6 6 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: cgghrd_ 14 16 13 13 4 4 4 8 4 8 4 8 4 8 4 4 124 124 */
/*:ref: chgeqz_ 14 23 13 13 13 4 4 4 8 4 8 4 8 8 8 4 8 4 8 4 6 4 124 124 124 */
/*:ref: ctgevc_ 14 19 13 13 12 4 8 4 8 4 8 4 8 4 4 4 8 6 4 124 124 */
/*:ref: cggbak_ 14 13 13 13 4 4 4 6 6 4 8 4 4 124 124 */
extern int cgehd2_(integer *n, integer *ilo, integer *ihi, complex *a, integer *lda, complex *tau, complex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int cgehrd_(integer *n, integer *ilo, integer *ihi, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clahrd_ 14 10 4 4 4 8 4 8 8 4 8 4 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
/*:ref: cgehd2_ 14 8 4 4 4 8 4 8 8 4 */
extern int cgelq2_(integer *m, integer *n, complex *a, integer *lda, complex *tau, complex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int cgelqf_(integer *m, integer *n, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgelq2_ 14 7 4 4 8 4 8 8 4 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cgels_(char *trans, integer *m, integer *n, integer *nrhs, complex *a, integer *lda, complex *b, integer *ldb, complex *work, integer *lwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: cgelqf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmlq_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
extern int cgelsd_(integer *m, integer *n, integer *nrhs, complex *a, integer *lda, complex *b, integer *ldb, real *s, real *rcond, integer *rank, complex *work, integer *lwork, real *rwork, integer *iwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: cgebrd_ 14 11 4 4 8 4 6 6 8 8 8 4 4 */
/*:ref: cunmbr_ 14 17 13 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 124 */
/*:ref: clalsd_ 14 15 13 4 4 4 6 6 8 4 6 4 8 6 4 4 124 */
/*:ref: cgelqf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cunmlq_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
extern int cgelss_(integer *m, integer *n, integer *nrhs, complex *a, integer *lda, complex *b, integer *ldb, real *s, real *rcond, integer *rank, complex *work, integer *lwork, real *rwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: cgebrd_ 14 11 4 4 8 4 6 6 8 8 8 4 4 */
/*:ref: cunmbr_ 14 17 13 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 124 */
/*:ref: cungbr_ 14 11 13 4 4 4 8 4 8 8 4 4 124 */
/*:ref: cbdsqr_ 14 16 13 4 4 4 4 6 6 8 4 8 4 8 4 6 4 124 */
/*:ref: csrscl_ 14 4 4 6 8 4 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgelqf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmlq_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
extern int cgelsx_(integer *m, integer *n, integer *nrhs, complex *a, integer *lda, complex *b, integer *ldb, integer *jpvt, real *rcond, integer *rank, complex *work, real *rwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: cgeqpf_ 14 9 4 4 8 4 4 8 8 6 4 */
/*:ref: claic1_ 14 9 4 4 8 6 8 8 6 8 8 */
/*:ref: ctzrqf_ 14 6 4 4 8 4 8 4 */
/*:ref: cunm2r_ 14 14 13 13 4 4 4 8 4 8 8 4 8 4 124 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: clatzm_ 14 11 13 4 4 8 4 8 8 8 4 8 124 */
extern int cgelsy_(integer *m, integer *n, integer *nrhs, complex *a, integer *lda, complex *b, integer *ldb, integer *jpvt, real *rcond, integer *rank, complex *work, integer *lwork, real *rwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: cgeqp3_ 14 10 4 4 8 4 4 8 8 4 6 4 */
/*:ref: claic1_ 14 9 4 4 8 6 8 8 6 8 8 */
/*:ref: ctzrzf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: cunmrz_ 14 16 13 13 4 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
extern int cgeql2_(integer *m, integer *n, complex *a, integer *lda, complex *tau, complex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int cgeqlf_(integer *m, integer *n, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgeql2_ 14 7 4 4 8 4 8 8 4 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cgeqp3_(integer *m, integer *n, complex *a, integer *lda, integer *jpvt, complex *tau, complex *work, integer *lwork, real *rwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: claqps_ 14 14 4 4 4 4 4 8 4 4 8 6 6 8 8 4 */
/*:ref: claqp2_ 14 10 4 4 4 8 4 4 8 6 6 8 */
extern int cgeqpf_(integer *m, integer *n, complex *a, integer *lda, integer *jpvt, complex *tau, complex *work, real *rwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cgeqr2_ 14 7 4 4 8 4 8 8 4 */
/*:ref: cunm2r_ 14 14 13 13 4 4 4 8 4 8 8 4 8 4 124 124 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int cgeqr2_(integer *m, integer *n, complex *a, integer *lda, complex *tau, complex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int cgeqrf_(integer *m, integer *n, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgeqr2_ 14 7 4 4 8 4 8 8 4 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cgerfs_(char *trans, integer *n, integer *nrhs, complex *a, integer *lda, complex *af, integer *ldaf, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cgetrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int cgerq2_(integer *m, integer *n, complex *a, integer *lda, complex *tau, complex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int cgerqf_(integer *m, integer *n, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgerq2_ 14 7 4 4 8 4 8 8 4 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cgesc2_(integer *n, complex *a, integer *lda, complex *rhs, integer *ipiv, integer *jpiv, real *scale);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: claswp_ 14 7 4 8 4 4 4 4 4 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int cgesdd_(char *jobz, integer *m, integer *n, complex *a, integer *lda, real *s, complex *u, integer *ldu, complex *vt, integer *ldvt, complex *work, integer *lwork, real *rwork, integer *iwork, integer *info, ftnlen jobz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: cgebrd_ 14 11 4 4 8 4 6 6 8 8 8 4 4 */
/*:ref: sbdsdc_ 14 16 13 13 4 6 6 6 4 6 4 6 4 6 4 4 124 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: clacp2_ 14 8 13 4 4 6 4 8 4 124 */
/*:ref: cunmbr_ 14 17 13 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 124 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: cungbr_ 14 11 13 4 4 4 8 4 8 8 4 4 124 */
/*:ref: clarcm_ 14 9 4 4 6 4 8 4 8 4 6 */
/*:ref: clacrm_ 14 9 4 4 8 4 6 4 8 4 6 */
/*:ref: cgelqf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunglq_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
extern int cgesv_(integer *n, integer *nrhs, complex *a, integer *lda, integer *ipiv, complex *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgetrf_ 14 6 4 4 8 4 4 4 */
/*:ref: cgetrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
extern int cgesvd_(char *jobu, char *jobvt, integer *m, integer *n, complex *a, integer *lda, real *s, complex *u, integer *ldu, complex *vt, integer *ldvt, complex *work, integer *lwork, real *rwork, integer *info, ftnlen jobu_len, ftnlen jobvt_len);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: cgebrd_ 14 11 4 4 8 4 6 6 8 8 8 4 4 */
/*:ref: cungbr_ 14 11 13 4 4 4 8 4 8 8 4 4 124 */
/*:ref: cbdsqr_ 14 16 13 4 4 4 4 6 6 8 4 8 4 8 4 6 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: cunmbr_ 14 17 13 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 124 */
/*:ref: cgelqf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunglq_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
extern int cgesvx_(char *fact, char *trans, integer *n, integer *nrhs, complex *a, integer *lda, complex *af, integer *ldaf, integer *ipiv, char *equed, real *r__, real *c__, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen fact_len, ftnlen trans_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgeequ_ 14 10 4 4 8 4 6 6 6 6 6 4 */
/*:ref: claqge_ 14 11 4 4 8 4 6 6 6 6 6 13 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cgetrf_ 14 6 4 4 8 4 4 4 */
/*:ref: clantr_ 6 11 13 13 13 4 4 8 4 6 124 124 124 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: cgecon_ 14 10 13 4 8 4 6 6 8 6 4 124 */
/*:ref: cgetrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
/*:ref: cgerfs_ 14 18 13 4 4 8 4 8 4 4 8 4 8 4 6 6 8 6 4 124 */
extern int cgetc2_(integer *n, complex *a, integer *lda, integer *ipiv, integer *jpiv, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
extern int cgetf2_(integer *m, integer *n, complex *a, integer *lda, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
extern int cgetrf_(integer *m, integer *n, complex *a, integer *lda, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: cgetf2_ 14 6 4 4 8 4 4 4 */
/*:ref: claswp_ 14 7 4 8 4 4 4 4 4 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
extern int cgetri_(integer *n, complex *a, integer *lda, integer *ipiv, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctrtri_ 14 8 13 13 4 8 4 4 124 124 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int cgetrs_(char *trans, integer *n, integer *nrhs, complex *a, integer *lda, integer *ipiv, complex *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: claswp_ 14 7 4 8 4 4 4 4 4 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
extern int cggbak_(char *job, char *side, integer *n, integer *ilo, integer *ihi, real *lscale, real *rscale, integer *m, complex *v, integer *ldv, integer *info, ftnlen job_len, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int cggbal_(char *job, integer *n, complex *a, integer *lda, complex *b, integer *ldb, integer *ilo, integer *ihi, real *lscale, real *rscale, real *work, integer *info, ftnlen job_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
extern int cgges_(char *jobvsl, char *jobvsr, char *sort, L_fp selctg, integer *n, complex *a, integer *lda, complex *b, integer *ldb, integer *sdim, complex *alpha, complex *beta, complex *vsl, integer *ldvsl, complex *vsr, integer *ldvsr, complex *work, integer *lwork, real *rwork, logical *bwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len, ftnlen sort_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cggbal_ 14 13 13 4 8 4 8 4 4 4 6 6 6 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: cgghrd_ 14 16 13 13 4 4 4 8 4 8 4 8 4 8 4 4 124 124 */
/*:ref: chgeqz_ 14 23 13 13 13 4 4 4 8 4 8 4 8 8 8 4 8 4 8 4 6 4 124 124 124 */
/*:ref: ctgsen_ 14 24 4 12 12 12 4 8 4 8 4 8 8 8 4 8 4 4 6 6 6 8 4 4 4 4 */
/*:ref: cggbak_ 14 13 13 13 4 4 4 6 6 4 8 4 4 124 124 */
extern int cggesx_(char *jobvsl, char *jobvsr, char *sort, L_fp selctg, char *sense, integer *n, complex *a, integer *lda, complex *b, integer *ldb, integer *sdim, complex *alpha, complex *beta, complex *vsl, integer *ldvsl, complex *vsr, integer *ldvsr, real *rconde, real *rcondv, complex *work, integer *lwork, real *rwork, integer *iwork, integer *liwork, logical *bwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len, ftnlen sort_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cggbal_ 14 13 13 4 8 4 8 4 4 4 6 6 6 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: cgghrd_ 14 16 13 13 4 4 4 8 4 8 4 8 4 8 4 4 124 124 */
/*:ref: chgeqz_ 14 23 13 13 13 4 4 4 8 4 8 4 8 8 8 4 8 4 8 4 6 4 124 124 124 */
/*:ref: ctgsen_ 14 24 4 12 12 12 4 8 4 8 4 8 8 8 4 8 4 4 6 6 6 8 4 4 4 4 */
/*:ref: cggbak_ 14 13 13 13 4 4 4 6 6 4 8 4 4 124 124 */
extern int cggev_(char *jobvl, char *jobvr, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *alpha, complex *beta, complex *vl, integer *ldvl, complex *vr, integer *ldvr, complex *work, integer *lwork, real *rwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cggbal_ 14 13 13 4 8 4 8 4 4 4 6 6 6 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: cgghrd_ 14 16 13 13 4 4 4 8 4 8 4 8 4 8 4 4 124 124 */
/*:ref: chgeqz_ 14 23 13 13 13 4 4 4 8 4 8 4 8 8 8 4 8 4 8 4 6 4 124 124 124 */
/*:ref: ctgevc_ 14 19 13 13 12 4 8 4 8 4 8 4 8 4 4 4 8 6 4 124 124 */
/*:ref: cggbak_ 14 13 13 13 4 4 4 6 6 4 8 4 4 124 124 */
extern int cggevx_(char *balanc, char *jobvl, char *jobvr, char *sense, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *alpha, complex *beta, complex *vl, integer *ldvl, complex *vr, integer *ldvr, integer *ilo, integer *ihi, real *lscale, real *rscale, real *abnrm, real *bbnrm, real *rconde, real *rcondv, complex *work, integer *lwork, real *rwork, integer *iwork, logical *bwork, integer *info, ftnlen balanc_len, ftnlen jobvl_len, ftnlen jobvr_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: cggbal_ 14 13 13 4 8 4 8 4 4 4 6 6 6 4 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: cgghrd_ 14 16 13 13 4 4 4 8 4 8 4 8 4 8 4 4 124 124 */
/*:ref: chgeqz_ 14 23 13 13 13 4 4 4 8 4 8 4 8 8 8 4 8 4 8 4 6 4 124 124 124 */
/*:ref: ctgevc_ 14 19 13 13 12 4 8 4 8 4 8 4 8 4 4 4 8 6 4 124 124 */
/*:ref: ctgsna_ 14 22 13 13 12 4 8 4 8 4 8 4 8 4 6 6 4 4 8 4 4 4 124 124 */
/*:ref: cggbak_ 14 13 13 13 4 4 4 6 6 4 8 4 4 124 124 */
extern int cggglm_(integer *n, integer *m, integer *p, complex *a, integer *lda, complex *b, integer *ldb, complex *d__, complex *x, complex *y, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cggqrf_ 14 12 4 4 4 8 4 8 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: ctrsv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cunmrq_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
extern int cgghrd_(char *compq, char *compz, integer *n, integer *ilo, integer *ihi, complex *a, integer *lda, complex *b, integer *ldb, complex *q, integer *ldq, complex *z__, integer *ldz, integer *info, ftnlen compq_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clartg_ 14 5 8 8 6 8 8 */
/*:ref: crot_ 14 7 4 8 4 8 4 6 8 */
extern int cgglse_(integer *m, integer *n, integer *p, complex *a, integer *lda, complex *b, integer *ldb, complex *c__, complex *d__, complex *x, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cggrqf_ 14 12 4 4 4 8 4 8 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: ctrsv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: ctrmv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: cunmrq_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
extern int cggqrf_(integer *n, integer *m, integer *p, complex *a, integer *lda, complex *taua, complex *b, integer *ldb, complex *taub, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: cgerqf_ 14 8 4 4 8 4 8 8 4 4 */
extern int cggrqf_(integer *m, integer *p, integer *n, complex *a, integer *lda, complex *taua, complex *b, integer *ldb, complex *taub, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgerqf_ 14 8 4 4 8 4 8 8 4 4 */
/*:ref: cunmrq_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: cgeqrf_ 14 8 4 4 8 4 8 8 4 4 */
extern int cggsvd_(char *jobu, char *jobv, char *jobq, integer *m, integer *n, integer *p, integer *k, integer *l, complex *a, integer *lda, complex *b, integer *ldb, real *alpha, real *beta, complex *u, integer *ldu, complex *v, integer *ldv, complex *q, integer *ldq, complex *work, real *rwork, integer *iwork, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: cggsvp_ 14 28 13 13 13 4 4 4 8 4 8 4 6 6 4 4 8 4 8 4 8 4 4 6 8 8 4 124 124 124 */
/*:ref: ctgsja_ 14 28 13 13 13 4 4 4 4 4 8 4 8 4 6 6 6 6 8 4 8 4 8 4 8 4 4 124 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
extern int cggsvp_(char *jobu, char *jobv, char *jobq, integer *m, integer *p, integer *n, complex *a, integer *lda, complex *b, integer *ldb, real *tola, real *tolb, integer *k, integer *l, complex *u, integer *ldu, complex *v, integer *ldv, complex *q, integer *ldq, integer *iwork, real *rwork, complex *tau, complex *work, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgeqpf_ 14 9 4 4 8 4 4 8 8 6 4 */
/*:ref: clapmt_ 14 6 12 4 4 8 4 4 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cung2r_ 14 8 4 4 4 8 4 8 8 4 */
/*:ref: cgerq2_ 14 7 4 4 8 4 8 8 4 */
/*:ref: cunmr2_ 14 14 13 13 4 4 4 8 4 8 8 4 8 4 124 124 */
/*:ref: cunm2r_ 14 14 13 13 4 4 4 8 4 8 8 4 8 4 124 124 */
/*:ref: cgeqr2_ 14 7 4 4 8 4 8 8 4 */
extern int cgtcon_(char *norm, integer *n, complex *dl, complex *d__, complex *du, complex *du2, integer *ipiv, real *anorm, real *rcond, complex *work, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: cgttrs_ 14 12 13 4 4 8 8 8 8 4 8 4 4 124 */
extern int cgtrfs_(char *trans, integer *n, integer *nrhs, complex *dl, complex *d__, complex *du, complex *dlf, complex *df, complex *duf, complex *du2, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: clagtm_ 14 13 13 4 4 6 8 8 8 8 4 6 8 4 124 */
/*:ref: cgttrs_ 14 12 13 4 4 8 8 8 8 4 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int cgtsv_(integer *n, integer *nrhs, complex *dl, complex *d__, complex *du, complex *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cgtsvx_(char *fact, char *trans, integer *n, integer *nrhs, complex *dl, complex *d__, complex *du, complex *dlf, complex *df, complex *duf, complex *du2, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen fact_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgttrf_ 14 7 4 8 8 8 8 4 4 */
/*:ref: clangt_ 6 6 13 4 8 8 8 124 */
/*:ref: cgtcon_ 14 12 13 4 8 8 8 8 4 6 6 8 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cgttrs_ 14 12 13 4 4 8 8 8 8 4 8 4 4 124 */
/*:ref: cgtrfs_ 14 21 13 4 4 8 8 8 8 8 8 8 4 8 4 8 4 6 6 8 6 4 124 */
extern int cgttrf_(integer *n, complex *dl, complex *d__, complex *du, complex *du2, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cgttrs_(char *trans, integer *n, integer *nrhs, complex *dl, complex *d__, complex *du, complex *du2, integer *ipiv, complex *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: cgtts2_ 14 10 4 4 4 8 8 8 8 4 8 4 */
extern int cgtts2_(integer *itrans, integer *n, integer *nrhs, complex *dl, complex *d__, complex *du, complex *du2, integer *ipiv, complex *b, integer *ldb);
extern int chbev_(char *jobz, char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, real *w, complex *z__, integer *ldz, complex *work, real *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhb_ 6 9 13 13 4 4 8 4 6 124 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: chbtrd_ 14 14 13 13 4 4 8 4 6 6 8 4 8 4 124 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: csteqr_ 14 9 13 4 6 6 8 4 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int chbevd_(char *jobz, char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, real *w, complex *z__, integer *ldz, complex *work, integer *lwork, real *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhb_ 6 9 13 13 4 4 8 4 6 124 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: chbtrd_ 14 14 13 13 4 4 8 4 6 6 8 4 8 4 124 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: cstedc_ 14 14 13 4 6 6 8 4 8 4 6 4 4 4 4 124 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int chbevx_(char *jobz, char *range, char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, complex *q, integer *ldq, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, complex *z__, integer *ldz, complex *work, real *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhb_ 6 9 13 13 4 4 8 4 6 124 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: chbtrd_ 14 14 13 13 4 4 8 4 6 6 8 4 8 4 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: csteqr_ 14 9 13 4 6 6 8 4 6 4 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: cstein_ 14 13 4 6 6 4 6 4 4 8 4 6 4 4 4 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int chbgst_(char *vect, char *uplo, integer *n, integer *ka, integer *kb, complex *ab, integer *ldab, complex *bb, integer *ldbb, complex *x, integer *ldx, complex *work, real *rwork, integer *info, ftnlen vect_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cgerc_ 14 9 4 4 8 8 4 8 4 8 4 */
/*:ref: clartg_ 14 5 8 8 6 8 8 */
/*:ref: clargv_ 14 7 4 8 4 8 4 6 4 */
/*:ref: clartv_ 14 8 4 8 4 8 4 6 8 4 */
/*:ref: clar2v_ 14 8 4 8 8 8 4 6 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: crot_ 14 7 4 8 4 8 4 6 8 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
extern int chbgv_(char *jobz, char *uplo, integer *n, integer *ka, integer *kb, complex *ab, integer *ldab, complex *bb, integer *ldbb, real *w, complex *z__, integer *ldz, complex *work, real *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpbstf_ 14 7 13 4 4 8 4 4 124 */
/*:ref: chbgst_ 14 16 13 13 4 4 4 8 4 8 4 8 4 8 6 4 124 124 */
/*:ref: chbtrd_ 14 14 13 13 4 4 8 4 6 6 8 4 8 4 124 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: csteqr_ 14 9 13 4 6 6 8 4 6 4 124 */
extern int chbgvd_(char *jobz, char *uplo, integer *n, integer *ka, integer *kb, complex *ab, integer *ldab, complex *bb, integer *ldbb, real *w, complex *z__, integer *ldz, complex *work, integer *lwork, real *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpbstf_ 14 7 13 4 4 8 4 4 124 */
/*:ref: chbgst_ 14 16 13 13 4 4 4 8 4 8 4 8 4 8 6 4 124 124 */
/*:ref: chbtrd_ 14 14 13 13 4 4 8 4 6 6 8 4 8 4 124 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: cstedc_ 14 14 13 4 6 6 8 4 8 4 6 4 4 4 4 124 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
extern int chbgvx_(char *jobz, char *range, char *uplo, integer *n, integer *ka, integer *kb, complex *ab, integer *ldab, complex *bb, integer *ldbb, complex *q, integer *ldq, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, complex *z__, integer *ldz, complex *work, real *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpbstf_ 14 7 13 4 4 8 4 4 124 */
/*:ref: chbgst_ 14 16 13 13 4 4 4 8 4 8 4 8 4 8 6 4 124 124 */
/*:ref: chbtrd_ 14 14 13 13 4 4 8 4 6 6 8 4 8 4 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: csteqr_ 14 9 13 4 6 6 8 4 6 4 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: cstein_ 14 13 4 6 6 4 6 4 4 8 4 6 4 4 4 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int chbtrd_(char *vect, char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, real *d__, real *e, complex *q, integer *ldq, complex *work, integer *info, ftnlen vect_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clargv_ 14 7 4 8 4 8 4 6 4 */
/*:ref: clartv_ 14 8 4 8 4 8 4 6 8 4 */
/*:ref: crot_ 14 7 4 8 4 8 4 6 8 */
/*:ref: clartg_ 14 5 8 8 6 8 8 */
/*:ref: clar2v_ 14 8 4 8 8 8 4 6 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int checon_(char *uplo, integer *n, complex *a, integer *lda, integer *ipiv, real *anorm, real *rcond, complex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: chetrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
extern int cheev_(char *jobz, char *uplo, integer *n, complex *a, integer *lda, real *w, complex *work, integer *lwork, real *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhe_ 6 8 13 13 4 8 4 6 124 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: chetrd_ 14 11 13 4 8 4 6 6 8 8 4 4 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: cungtr_ 14 9 13 4 8 4 8 8 4 4 124 */
/*:ref: csteqr_ 14 9 13 4 6 6 8 4 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int cheevd_(char *jobz, char *uplo, integer *n, complex *a, integer *lda, real *w, complex *work, integer *lwork, real *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhe_ 6 8 13 13 4 8 4 6 124 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: chetrd_ 14 11 13 4 8 4 6 6 8 8 4 4 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: cstedc_ 14 14 13 4 6 6 8 4 8 4 6 4 4 4 4 124 */
/*:ref: cunmtr_ 14 16 13 13 13 4 4 8 4 8 8 4 8 4 4 124 124 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int cheevr_(char *jobz, char *range, char *uplo, integer *n, complex *a, integer *lda, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, complex *z__, integer *ldz, integer *isuppz, complex *work, integer *lwork, real *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clansy_ 6 8 13 13 4 8 4 6 124 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: chetrd_ 14 11 13 4 8 4 6 6 8 8 4 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: cstegr_ 14 22 13 13 4 6 6 6 6 4 4 6 4 6 8 4 4 6 4 4 4 4 124 124 */
/*:ref: cunmtr_ 14 16 13 13 13 4 4 8 4 8 8 4 8 4 4 124 124 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: cstein_ 14 13 4 6 6 4 6 4 4 8 4 6 4 4 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int cheevx_(char *jobz, char *range, char *uplo, integer *n, complex *a, integer *lda, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, complex *z__, integer *ldz, complex *work, integer *lwork, real *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhe_ 6 8 13 13 4 8 4 6 124 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: chetrd_ 14 11 13 4 8 4 6 6 8 8 4 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cungtr_ 14 9 13 4 8 4 8 8 4 4 124 */
/*:ref: csteqr_ 14 9 13 4 6 6 8 4 6 4 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: cstein_ 14 13 4 6 6 4 6 4 4 8 4 6 4 4 4 */
/*:ref: cunmtr_ 14 16 13 13 13 4 4 8 4 8 8 4 8 4 4 124 124 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int chegs2_(integer *itype, char *uplo, integer *n, complex *a, integer *lda, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: cher2_ 14 10 13 4 8 8 4 8 4 8 4 124 */
/*:ref: ctrsv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
/*:ref: ctrmv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
extern int chegst_(integer *itype, char *uplo, integer *n, complex *a, integer *lda, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: chegs2_ 14 9 4 13 4 8 4 8 4 4 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: chemm_ 14 14 13 13 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: cher2k_ 14 14 13 13 4 4 8 8 4 8 4 6 8 4 124 124 */
/*:ref: ctrmm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
extern int chegv_(integer *itype, char *jobz, char *uplo, integer *n, complex *a, integer *lda, complex *b, integer *ldb, real *w, complex *work, integer *lwork, real *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpotrf_ 14 6 13 4 8 4 4 124 */
/*:ref: chegst_ 14 9 4 13 4 8 4 8 4 4 124 */
/*:ref: cheev_ 14 12 13 13 4 8 4 6 8 4 6 4 124 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: ctrmm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
extern int chegvd_(integer *itype, char *jobz, char *uplo, integer *n, complex *a, integer *lda, complex *b, integer *ldb, real *w, complex *work, integer *lwork, real *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpotrf_ 14 6 13 4 8 4 4 124 */
/*:ref: chegst_ 14 9 4 13 4 8 4 8 4 4 124 */
/*:ref: cheevd_ 14 15 13 13 4 8 4 6 8 4 6 4 4 4 4 124 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: ctrmm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
extern int chegvx_(integer *itype, char *jobz, char *range, char *uplo, integer *n, complex *a, integer *lda, complex *b, integer *ldb, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, complex *z__, integer *ldz, complex *work, integer *lwork, real *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpotrf_ 14 6 13 4 8 4 4 124 */
/*:ref: chegst_ 14 9 4 13 4 8 4 8 4 4 124 */
/*:ref: cheevx_ 14 24 13 13 13 4 8 4 6 6 4 4 6 4 6 8 4 8 4 6 4 4 4 124 124 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: ctrmm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
extern int cherfs_(char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, complex *af, integer *ldaf, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: chemv_ 14 11 13 4 8 8 4 8 4 8 8 4 124 */
/*:ref: chetrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int chesv_(char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, integer *ipiv, complex *b, integer *ldb, complex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: chetrf_ 14 9 13 4 8 4 4 8 4 4 124 */
/*:ref: chetrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
extern int chesvx_(char *fact, char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, complex *af, integer *ldaf, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, integer *lwork, real *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: chetrf_ 14 9 13 4 8 4 4 8 4 4 124 */
/*:ref: clanhe_ 6 8 13 13 4 8 4 6 124 124 */
/*:ref: checon_ 14 10 13 4 8 4 4 6 6 8 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: chetrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
/*:ref: cherfs_ 14 18 13 4 4 8 4 8 4 4 8 4 8 4 6 6 8 6 4 124 */
extern int chetd2_(char *uplo, integer *n, complex *a, integer *lda, real *d__, real *e, complex *tau, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: chemv_ 14 11 13 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: cher2_ 14 10 13 4 8 8 4 8 4 8 4 124 */
extern int chetf2_(char *uplo, integer *n, complex *a, integer *lda, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cher_ 14 8 13 4 6 8 4 8 4 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: slapy2_ 6 2 6 6 */
extern int chetrd_(char *uplo, integer *n, complex *a, integer *lda, real *d__, real *e, complex *tau, complex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clatrd_ 14 10 13 4 4 8 4 6 8 8 4 124 */
/*:ref: cher2k_ 14 14 13 13 4 4 8 8 4 8 4 6 8 4 124 124 */
/*:ref: chetd2_ 14 9 13 4 8 4 6 6 8 4 124 */
extern int chetrf_(char *uplo, integer *n, complex *a, integer *lda, integer *ipiv, complex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clahef_ 14 11 13 4 4 4 8 4 4 8 4 4 124 */
/*:ref: chetf2_ 14 7 13 4 8 4 4 4 124 */
extern int chetri_(char *uplo, integer *n, complex *a, integer *lda, integer *ipiv, complex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: chemv_ 14 11 13 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int chetrs_(char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, integer *ipiv, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
extern int chgeqz_(char *job, char *compq, char *compz, integer *n, integer *ilo, integer *ihi, complex *a, integer *lda, complex *b, integer *ldb, complex *alpha, complex *beta, complex *q, integer *ldq, complex *z__, integer *ldz, complex *work, integer *lwork, real *rwork, integer *info, ftnlen job_len, ftnlen compq_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhs_ 6 6 13 4 8 4 6 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: clartg_ 14 5 8 8 6 8 8 */
/*:ref: crot_ 14 7 4 8 4 8 4 6 8 */
extern int chpcon_(char *uplo, integer *n, complex *ap, integer *ipiv, real *anorm, real *rcond, complex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: chptrs_ 14 9 13 4 4 8 4 8 4 4 124 */
extern int chpev_(char *jobz, char *uplo, integer *n, complex *ap, real *w, complex *z__, integer *ldz, complex *work, real *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhp_ 6 7 13 13 4 8 6 124 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: chptrd_ 14 8 13 4 8 6 6 8 4 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: cupgtr_ 14 9 13 4 8 8 8 4 8 4 124 */
/*:ref: csteqr_ 14 9 13 4 6 6 8 4 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int chpevd_(char *jobz, char *uplo, integer *n, complex *ap, real *w, complex *z__, integer *ldz, complex *work, integer *lwork, real *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhp_ 6 7 13 13 4 8 6 124 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: chptrd_ 14 8 13 4 8 6 6 8 4 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: cstedc_ 14 14 13 4 6 6 8 4 8 4 6 4 4 4 4 124 */
/*:ref: cupmtr_ 14 14 13 13 13 4 4 8 8 8 4 8 4 124 124 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int chpevx_(char *jobz, char *range, char *uplo, integer *n, complex *ap, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, complex *z__, integer *ldz, complex *work, real *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhp_ 6 7 13 13 4 8 6 124 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: chptrd_ 14 8 13 4 8 6 6 8 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: cupgtr_ 14 9 13 4 8 8 8 4 8 4 124 */
/*:ref: csteqr_ 14 9 13 4 6 6 8 4 6 4 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: cstein_ 14 13 4 6 6 4 6 4 4 8 4 6 4 4 4 */
/*:ref: cupmtr_ 14 14 13 13 13 4 4 8 8 8 4 8 4 124 124 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int chpgst_(integer *itype, char *uplo, integer *n, complex *ap, complex *bp, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctpsv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
/*:ref: chpmv_ 14 10 13 4 8 8 8 4 8 8 4 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: chpr2_ 14 9 13 4 8 8 4 8 4 8 124 */
/*:ref: ctpmv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
extern int chpgv_(integer *itype, char *jobz, char *uplo, integer *n, complex *ap, complex *bp, real *w, complex *z__, integer *ldz, complex *work, real *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpptrf_ 14 5 13 4 8 4 124 */
/*:ref: chpgst_ 14 7 4 13 4 8 8 4 124 */
/*:ref: chpev_ 14 12 13 13 4 8 6 8 4 8 6 4 124 124 */
/*:ref: ctpsv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
/*:ref: ctpmv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
extern int chpgvd_(integer *itype, char *jobz, char *uplo, integer *n, complex *ap, complex *bp, real *w, complex *z__, integer *ldz, complex *work, integer *lwork, real *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpptrf_ 14 5 13 4 8 4 124 */
/*:ref: chpgst_ 14 7 4 13 4 8 8 4 124 */
/*:ref: chpevd_ 14 16 13 13 4 8 6 8 4 8 4 6 4 4 4 4 124 124 */
/*:ref: ctpsv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
/*:ref: ctpmv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
extern int chpgvx_(integer *itype, char *jobz, char *range, char *uplo, integer *n, complex *ap, complex *bp, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, complex *z__, integer *ldz, complex *work, real *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpptrf_ 14 5 13 4 8 4 124 */
/*:ref: chpgst_ 14 7 4 13 4 8 8 4 124 */
/*:ref: chpevx_ 14 22 13 13 13 4 8 6 6 4 4 6 4 6 8 4 8 6 4 4 4 124 124 124 */
/*:ref: ctpsv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
/*:ref: ctpmv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
extern int chprfs_(char *uplo, integer *n, integer *nrhs, complex *ap, complex *afp, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: chpmv_ 14 10 13 4 8 8 8 4 8 8 4 124 */
/*:ref: chptrs_ 14 9 13 4 4 8 4 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int chpsv_(char *uplo, integer *n, integer *nrhs, complex *ap, integer *ipiv, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: chptrf_ 14 6 13 4 8 4 4 124 */
/*:ref: chptrs_ 14 9 13 4 4 8 4 8 4 4 124 */
extern int chpsvx_(char *fact, char *uplo, integer *n, integer *nrhs, complex *ap, complex *afp, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: chptrf_ 14 6 13 4 8 4 4 124 */
/*:ref: clanhp_ 6 7 13 13 4 8 6 124 124 */
/*:ref: chpcon_ 14 9 13 4 8 4 6 6 8 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: chptrs_ 14 9 13 4 4 8 4 8 4 4 124 */
/*:ref: chprfs_ 14 16 13 4 4 8 8 4 8 4 8 4 6 6 8 6 4 124 */
extern int chptrd_(char *uplo, integer *n, complex *ap, real *d__, real *e, complex *tau, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: chpmv_ 14 10 13 4 8 8 8 4 8 8 4 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: chpr2_ 14 9 13 4 8 8 4 8 4 8 124 */
extern int chptrf_(char *uplo, integer *n, complex *ap, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: chpr_ 14 7 13 4 6 8 4 8 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: slapy2_ 6 2 6 6 */
extern int chptri_(char *uplo, integer *n, complex *ap, integer *ipiv, complex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: chpmv_ 14 10 13 4 8 8 8 4 8 8 4 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int chptrs_(char *uplo, integer *n, integer *nrhs, complex *ap, integer *ipiv, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
extern int chsein_(char *side, char *eigsrc, char *initv, logical *select, integer *n, complex *h__, integer *ldh, complex *w, complex *vl, integer *ldvl, complex *vr, integer *ldvr, integer *mm, integer *m, complex *work, real *rwork, integer *ifaill, integer *ifailr, integer *info, ftnlen side_len, ftnlen eigsrc_len, ftnlen initv_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhs_ 6 6 13 4 8 4 6 124 */
/*:ref: claein_ 14 13 12 12 4 8 4 8 8 8 4 6 6 6 4 */
extern int chseqr_(char *job, char *compz, integer *n, integer *ilo, integer *ihi, complex *h__, integer *ldh, complex *w, complex *z__, integer *ldz, complex *work, integer *lwork, integer *info, ftnlen job_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: clahqr_ 14 13 12 12 4 4 4 8 4 8 4 4 8 4 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clanhs_ 6 6 13 4 8 4 6 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: clarfx_ 14 9 13 4 4 8 8 8 4 8 124 */
extern int clabrd_(integer *m, integer *n, integer *nb, complex *a, integer *lda, real *d__, real *e, complex *tauq, complex *taup, complex *x, integer *ldx, complex *y, integer *ldy);
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int clacgv_(integer *n, complex *x, integer *incx);
extern int clacon_(integer *n, complex *v, complex *x, real *est, integer *kase);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scsum1_ 6 3 4 8 4 */
/*:ref: icmax1_ 4 3 4 8 4 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
extern int clacp2_(char *uplo, integer *m, integer *n, real *a, integer *lda, complex *b, integer *ldb, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int clacpy_(char *uplo, integer *m, integer *n, complex *a, integer *lda, complex *b, integer *ldb, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int clacrm_(integer *m, integer *n, complex *a, integer *lda, real *b, integer *ldb, complex *c__, integer *ldc, real *rwork);
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
extern int clacrt_(integer *n, complex *cx, integer *incx, complex *cy, integer *incy, complex *c__, complex *s);
extern C_f cladiv_(complex * ret_val, complex *x, complex *y);
/*:ref: sladiv_ 14 6 6 6 6 6 6 6 */
extern int claed0_(integer *qsiz, integer *n, real *d__, real *e, complex *q, integer *ldq, complex *qstore, integer *ldqs, real *rwork, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: clacrm_ 14 9 4 4 8 4 6 4 8 4 6 */
/*:ref: claed7_ 14 22 4 4 4 4 4 4 6 8 4 6 4 6 4 4 4 4 4 6 8 6 4 4 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
extern int claed7_(integer *n, integer *cutpnt, integer *qsiz, integer *tlvls, integer *curlvl, integer *curpbm, real *d__, complex *q, integer *ldq, real *rho, integer *indxq, real *qstore, integer *qptr, integer *prmptr, integer *perm, integer *givptr, integer *givcol, real *givnum, complex *work, real *rwork, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaeda_ 14 14 4 4 4 4 4 4 4 4 6 6 4 6 6 4 */
/*:ref: claed8_ 14 21 4 4 4 8 4 6 6 4 6 6 8 4 6 4 4 4 4 4 4 6 4 */
/*:ref: slaed9_ 14 13 4 4 4 4 6 6 4 6 6 6 6 4 4 */
/*:ref: clacrm_ 14 9 4 4 8 4 6 4 8 4 6 */
/*:ref: slamrg_ 14 6 4 4 6 4 4 4 */
extern int claed8_(integer *k, integer *n, integer *qsiz, complex *q, integer *ldq, real *d__, real *rho, integer *cutpnt, real *z__, real *dlamda, complex *q2, integer *ldq2, real *w, integer *indxp, integer *indx, integer *indxq, integer *perm, integer *givptr, integer *givcol, real *givnum, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slamrg_ 14 6 4 4 6 4 4 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: csrot_ 14 7 4 8 4 8 4 6 6 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
extern int claein_(logical *rightv, logical *noinit, integer *n, complex *h__, integer *ldh, complex *w, complex *v, complex *b, integer *ldb, real *rwork, real *eps3, real *smlnum, integer *info);
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cladiv_ 8 3 8 8 8 */
/*:ref: clatrs_ 14 15 13 13 13 13 4 8 4 8 6 6 4 124 124 124 124 */
/*:ref: scasum_ 6 3 4 8 4 */
/*:ref: icamax_ 4 3 4 8 4 */
extern int claesy_(complex *a, complex *b, complex *c__, complex *rt1, complex *rt2, complex *evscal, complex *cs1, complex *sn1);
extern int claev2_(complex *a, complex *b, complex *c__, real *rt1, real *rt2, real *cs1, complex *sn1);
/*:ref: slaev2_ 14 7 6 6 6 6 6 6 6 */
extern int clags2_(logical *upper, real *a1, complex *a2, real *a3, real *b1, complex *b2, real *b3, real *csu, complex *snu, real *csv, complex *snv, real *csq, complex *snq);
/*:ref: slasv2_ 14 9 6 6 6 6 6 6 6 6 6 */
/*:ref: clartg_ 14 5 8 8 6 8 8 */
extern int clagtm_(char *trans, integer *n, integer *nrhs, real *alpha, complex *dl, complex *d__, complex *du, complex *x, integer *ldx, real *beta, complex *b, integer *ldb, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int clahef_(char *uplo, integer *n, integer *nb, integer *kb, complex *a, integer *lda, integer *ipiv, complex *w, integer *ldw, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
extern int clahqr_(logical *wantt, logical *wantz, integer *n, integer *ilo, integer *ihi, complex *h__, integer *ldh, complex *w, integer *iloz, integer *ihiz, complex *z__, integer *ldz, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clanhs_ 6 6 13 4 8 4 6 124 */
/*:ref: cladiv_ 8 3 8 8 8 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int clahrd_(integer *n, integer *k, integer *nb, complex *a, integer *lda, complex *tau, complex *t, integer *ldt, complex *y, integer *ldy);
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: ctrmv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int claic1_(integer *job, integer *j, complex *x, real *sest, complex *w, complex *gamma, real *sestpr, complex *s, complex *c__);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
extern int clals0_(integer *icompq, integer *nl, integer *nr, integer *sqre, integer *nrhs, complex *b, integer *ldb, complex *bx, integer *ldbx, integer *perm, integer *givptr, integer *givcol, integer *ldgcol, real *givnum, integer *ldgnum, real *poles, real *difl, real *difr, real *z__, integer *k, real *c__, real *s, real *rwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: csrot_ 14 7 4 8 4 8 4 6 6 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: slamc3_ 6 2 6 6 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
extern int clalsa_(integer *icompq, integer *smlsiz, integer *n, integer *nrhs, complex *b, integer *ldb, complex *bx, integer *ldbx, real *u, integer *ldu, real *vt, integer *k, real *difl, real *difr, real *z__, real *poles, integer *givptr, integer *givcol, integer *ldgcol, integer *perm, real *givnum, real *c__, real *s, real *rwork, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slasdt_ 14 7 4 4 4 4 4 4 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: clals0_ 14 24 4 4 4 4 4 8 4 8 4 4 4 4 4 6 4 6 6 6 6 4 6 6 6 4 */
extern int clalsd_(char *uplo, integer *smlsiz, integer *n, integer *nrhs, real *d__, real *e, complex *b, integer *ldb, real *rcond, integer *rank, complex *work, real *rwork, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clascl_ 14 11 13 4 4 6 6 4 4 8 4 4 124 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: csrot_ 14 7 4 8 4 8 4 6 6 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slasdq_ 14 17 13 4 4 4 4 4 6 6 6 4 6 4 6 4 6 4 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: slasrt_ 14 5 13 4 6 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: slasda_ 14 24 4 4 4 4 6 6 6 4 6 4 6 6 6 6 4 4 4 4 6 6 6 6 4 4 */
/*:ref: clalsa_ 14 26 4 4 4 4 8 4 8 4 6 4 6 4 6 6 6 6 4 4 4 4 6 6 6 6 4 4 */
extern E_f clangb_(char *norm, integer *n, integer *kl, integer *ku, complex *ab, integer *ldab, real *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clange_(char *norm, integer *m, integer *n, complex *a, integer *lda, real *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clangt_(char *norm, integer *n, complex *dl, complex *d__, complex *du, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clanhb_(char *norm, char *uplo, integer *n, integer *k, complex *ab, integer *ldab, real *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clanhe_(char *norm, char *uplo, integer *n, complex *a, integer *lda, real *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clanhp_(char *norm, char *uplo, integer *n, complex *ap, real *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clanhs_(char *norm, integer *n, complex *a, integer *lda, real *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clanht_(char *norm, integer *n, real *d__, complex *e, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f clansb_(char *norm, char *uplo, integer *n, integer *k, complex *ab, integer *ldab, real *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clansp_(char *norm, char *uplo, integer *n, complex *ap, real *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clansy_(char *norm, char *uplo, integer *n, complex *a, integer *lda, real *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clantb_(char *norm, char *uplo, char *diag, integer *n, integer *k, complex *ab, integer *ldab, real *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clantp_(char *norm, char *uplo, char *diag, integer *n, complex *ap, real *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern E_f clantr_(char *norm, char *uplo, char *diag, integer *m, integer *n, complex *a, integer *lda, real *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
extern int clapll_(integer *n, complex *x, integer *incx, complex *y, integer *incy, real *ssmin);
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: slas2_ 14 5 6 6 6 6 6 */
extern int clapmt_(logical *forwrd, integer *m, integer *n, complex *x, integer *ldx, integer *k);
extern int claqgb_(integer *m, integer *n, integer *kl, integer *ku, complex *ab, integer *ldab, real *r__, real *c__, real *rowcnd, real *colcnd, real *amax, char *equed, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
extern int claqge_(integer *m, integer *n, complex *a, integer *lda, real *r__, real *c__, real *rowcnd, real *colcnd, real *amax, char *equed, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
extern int claqhb_(char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, real *s, real *scond, real *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int claqhe_(char *uplo, integer *n, complex *a, integer *lda, real *s, real *scond, real *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int claqhp_(char *uplo, integer *n, complex *ap, real *s, real *scond, real *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int claqp2_(integer *m, integer *n, integer *offset, complex *a, integer *lda, integer *jpvt, complex *tau, real *vn1, real *vn2, complex *work);
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
/*:ref: scnrm2_ 6 3 4 8 4 */
extern int claqps_(integer *m, integer *n, integer *offset, integer *nb, integer *kb, complex *a, integer *lda, integer *jpvt, complex *tau, real *vn1, real *vn2, complex *auxv, complex *f, integer *ldf);
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: scnrm2_ 6 3 4 8 4 */
extern int claqsb_(char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, real *s, real *scond, real *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int claqsp_(char *uplo, integer *n, complex *ap, real *s, real *scond, real *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int claqsy_(char *uplo, integer *n, complex *a, integer *lda, real *s, real *scond, real *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int clar1v_(integer *n, integer *b1, integer *bn, real *sigma, real *d__, real *l, real *ld, real *lld, real *gersch, complex *z__, real *ztz, real *mingma, integer *r__, integer *isuppz, real *work);
/*:ref: slamch_ 6 2 13 124 */
extern int clar2v_(integer *n, complex *x, complex *y, complex *z__, integer *incx, real *c__, complex *s, integer *incc);
extern int clarcm_(integer *m, integer *n, real *a, integer *lda, complex *b, integer *ldb, complex *c__, integer *ldc, real *rwork);
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
extern int clarf_(char *side, integer *m, integer *n, complex *v, integer *incv, complex *tau, complex *c__, integer *ldc, complex *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cgerc_ 14 9 4 4 8 8 4 8 4 8 4 */
extern int clarfb_(char *side, char *trans, char *direct, char *storev, integer *m, integer *n, integer *k, complex *v, integer *ldv, complex *t, integer *ldt, complex *c__, integer *ldc, complex *work, integer *ldwork, ftnlen side_len, ftnlen trans_len, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: ctrmm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
extern int clarfg_(integer *n, complex *alpha, complex *x, integer *incx, complex *tau);
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: slapy3_ 6 3 6 6 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cladiv_ 8 3 8 8 8 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int clarft_(char *direct, char *storev, integer *n, integer *k, complex *v, integer *ldv, complex *tau, complex *t, integer *ldt, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: ctrmv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
extern int clarfx_(char *side, integer *m, integer *n, complex *v, complex *tau, complex *c__, integer *ldc, complex *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cgerc_ 14 9 4 4 8 8 4 8 4 8 4 */
extern int clargv_(integer *n, complex *x, integer *incx, complex *y, integer *incy, real *c__, integer *incc);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slapy2_ 6 2 6 6 */
extern int clarnv_(integer *idist, integer *iseed, integer *n, complex *x);
/*:ref: slaruv_ 14 3 4 4 6 */
extern int clarrv_(integer *n, real *d__, real *l, integer *isplit, integer *m, real *w, integer *iblock, real *gersch, real *tol, complex *z__, integer *ldz, integer *isuppz, real *work, integer *iwork, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slarrb_ 14 15 4 6 6 6 6 4 4 6 6 6 6 6 6 4 4 */
/*:ref: slarrf_ 14 13 4 6 6 6 6 4 4 6 6 6 6 4 4 */
/*:ref: cstein_ 14 13 4 6 6 4 6 4 4 8 4 6 4 4 4 */
/*:ref: clar1v_ 14 15 4 4 4 6 6 6 6 6 6 8 6 6 4 4 6 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cdotu_ 8 6 8 4 8 4 8 4 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: scnrm2_ 6 3 4 8 4 */
extern int clartg_(complex *f, complex *g, real *cs, complex *sn, complex *r__);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slapy2_ 6 2 6 6 */
extern int clartv_(integer *n, complex *x, integer *incx, complex *y, integer *incy, real *c__, complex *s, integer *incc);
extern int clarz_(char *side, integer *m, integer *n, integer *l, complex *v, integer *incv, complex *tau, complex *c__, integer *ldc, complex *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
/*:ref: cgerc_ 14 9 4 4 8 8 4 8 4 8 4 */
extern int clarzb_(char *side, char *trans, char *direct, char *storev, integer *m, integer *n, integer *k, integer *l, complex *v, integer *ldv, complex *t, integer *ldt, complex *c__, integer *ldc, complex *work, integer *ldwork, ftnlen side_len, ftnlen trans_len, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: ctrmm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
extern int clarzt_(char *direct, char *storev, integer *n, integer *k, complex *v, integer *ldv, complex *tau, complex *t, integer *ldt, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: ctrmv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
extern int clascl_(char *type__, integer *kl, integer *ku, real *cfrom, real *cto, integer *m, integer *n, complex *a, integer *lda, integer *info, ftnlen type_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
extern int claset_(char *uplo, integer *m, integer *n, complex *alpha, complex *beta, complex *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int clasr_(char *side, char *pivot, char *direct, integer *m, integer *n, real *c__, real *s, complex *a, integer *lda, ftnlen side_len, ftnlen pivot_len, ftnlen direct_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int classq_(integer *n, complex *x, integer *incx, real *scale, real *sumsq);
extern int claswp_(integer *n, complex *a, integer *lda, integer *k1, integer *k2, integer *ipiv, integer *incx);
extern int clasyf_(char *uplo, integer *n, integer *nb, integer *kb, complex *a, integer *lda, integer *ipiv, complex *w, integer *ldw, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
extern int clatbs_(char *uplo, char *trans, char *diag, char *normin, integer *n, integer *kd, complex *ab, integer *ldab, complex *x, real *scale, real *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: scasum_ 6 3 4 8 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ctbsv_ 14 12 13 13 13 4 4 8 4 8 4 124 124 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cladiv_ 8 3 8 8 8 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cdotu_ 8 6 8 4 8 4 8 4 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
extern int clatdf_(integer *ijob, integer *n, complex *z__, integer *ldz, complex *rhs, real *rdsum, real *rdscal, integer *ipiv, integer *jpiv);
/*:ref: claswp_ 14 7 4 8 4 4 4 4 4 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
/*:ref: cgecon_ 14 10 13 4 8 4 6 6 8 6 4 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: cgesc2_ 14 7 4 8 4 8 4 4 6 */
/*:ref: scasum_ 6 3 4 8 4 */
extern int clatps_(char *uplo, char *trans, char *diag, char *normin, integer *n, complex *ap, complex *x, real *scale, real *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: scasum_ 6 3 4 8 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ctpsv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cladiv_ 8 3 8 8 8 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cdotu_ 8 6 8 4 8 4 8 4 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
extern int clatrd_(char *uplo, integer *n, integer *nb, complex *a, integer *lda, real *e, complex *tau, complex *w, integer *ldw, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: chemv_ 14 11 13 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
extern int clatrs_(char *uplo, char *trans, char *diag, char *normin, integer *n, complex *a, integer *lda, complex *x, real *scale, real *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: scasum_ 6 3 4 8 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ctrsv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cladiv_ 8 3 8 8 8 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cdotu_ 8 6 8 4 8 4 8 4 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
extern int clatrz_(integer *m, integer *n, integer *l, complex *a, integer *lda, complex *tau, complex *work);
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: clarz_ 14 11 13 4 4 4 8 4 8 8 4 8 124 */
extern int clatzm_(char *side, integer *m, integer *n, complex *v, integer *incv, complex *tau, complex *c1, complex *c2, integer *ldc, complex *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
/*:ref: cgerc_ 14 9 4 4 8 8 4 8 4 8 4 */
extern int clauu2_(char *uplo, integer *n, complex *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
extern int clauum_(char *uplo, integer *n, complex *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: clauu2_ 14 6 13 4 8 4 4 124 */
/*:ref: ctrmm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: cherk_ 14 12 13 13 4 4 6 8 4 6 8 4 124 124 */
extern int cpbcon_(char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, real *anorm, real *rcond, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: clatbs_ 14 16 13 13 13 13 4 4 8 4 8 6 6 4 124 124 124 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csrscl_ 14 4 4 6 8 4 */
extern int cpbequ_(char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, real *s, real *scond, real *amax, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cpbrfs_(char *uplo, integer *n, integer *kd, integer *nrhs, complex *ab, integer *ldab, complex *afb, integer *ldafb, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: chbmv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cpbtrs_ 14 10 13 4 4 4 8 4 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int cpbstf_(char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cher_ 14 8 13 4 6 8 4 8 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
extern int cpbsv_(char *uplo, integer *n, integer *kd, integer *nrhs, complex *ab, integer *ldab, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpbtrf_ 14 7 13 4 4 8 4 4 124 */
/*:ref: cpbtrs_ 14 10 13 4 4 4 8 4 8 4 4 124 */
extern int cpbsvx_(char *fact, char *uplo, integer *n, integer *kd, integer *nrhs, complex *ab, integer *ldab, complex *afb, integer *ldafb, char *equed, real *s, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpbequ_ 14 10 13 4 4 8 4 6 6 6 4 124 */
/*:ref: claqhb_ 14 11 13 4 4 8 4 6 6 6 13 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cpbtrf_ 14 7 13 4 4 8 4 4 124 */
/*:ref: clanhb_ 6 9 13 13 4 4 8 4 6 124 124 */
/*:ref: cpbcon_ 14 11 13 4 4 8 4 6 6 8 6 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cpbtrs_ 14 10 13 4 4 4 8 4 8 4 4 124 */
/*:ref: cpbrfs_ 14 18 13 4 4 4 8 4 8 4 8 4 8 4 6 6 8 6 4 124 */
extern int cpbtf2_(char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cher_ 14 8 13 4 6 8 4 8 4 124 */
extern int cpbtrf_(char *uplo, integer *n, integer *kd, complex *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: cpbtf2_ 14 7 13 4 4 8 4 4 124 */
/*:ref: cpotf2_ 14 6 13 4 8 4 4 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: cherk_ 14 12 13 13 4 4 6 8 4 6 8 4 124 124 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
extern int cpbtrs_(char *uplo, integer *n, integer *kd, integer *nrhs, complex *ab, integer *ldab, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctbsv_ 14 12 13 13 13 4 4 8 4 8 4 124 124 124 */
extern int cpocon_(char *uplo, integer *n, complex *a, integer *lda, real *anorm, real *rcond, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: clatrs_ 14 15 13 13 13 13 4 8 4 8 6 6 4 124 124 124 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csrscl_ 14 4 4 6 8 4 */
extern int cpoequ_(integer *n, complex *a, integer *lda, real *s, real *scond, real *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cporfs_(char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, complex *af, integer *ldaf, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: chemv_ 14 11 13 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cpotrs_ 14 9 13 4 4 8 4 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int cposv_(char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpotrf_ 14 6 13 4 8 4 4 124 */
/*:ref: cpotrs_ 14 9 13 4 4 8 4 8 4 4 124 */
extern int cposvx_(char *fact, char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, complex *af, integer *ldaf, char *equed, real *s, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpoequ_ 14 7 4 8 4 6 6 6 4 */
/*:ref: claqhe_ 14 10 13 4 8 4 6 6 6 13 124 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cpotrf_ 14 6 13 4 8 4 4 124 */
/*:ref: clanhe_ 6 8 13 13 4 8 4 6 124 124 */
/*:ref: cpocon_ 14 10 13 4 8 4 6 6 8 6 4 124 */
/*:ref: cpotrs_ 14 9 13 4 4 8 4 8 4 4 124 */
/*:ref: cporfs_ 14 17 13 4 4 8 4 8 4 8 4 8 4 6 6 8 6 4 124 */
extern int cpotf2_(char *uplo, integer *n, complex *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
extern int cpotrf_(char *uplo, integer *n, complex *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: cpotf2_ 14 6 13 4 8 4 4 124 */
/*:ref: cherk_ 14 12 13 13 4 4 6 8 4 6 8 4 124 124 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
extern int cpotri_(char *uplo, integer *n, complex *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctrtri_ 14 8 13 13 4 8 4 4 124 124 */
/*:ref: clauum_ 14 6 13 4 8 4 4 124 */
extern int cpotrs_(char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
extern int cppcon_(char *uplo, integer *n, complex *ap, real *anorm, real *rcond, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: clatps_ 14 14 13 13 13 13 4 8 8 6 6 4 124 124 124 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csrscl_ 14 4 4 6 8 4 */
extern int cppequ_(char *uplo, integer *n, complex *ap, real *s, real *scond, real *amax, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cpprfs_(char *uplo, integer *n, integer *nrhs, complex *ap, complex *afp, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: chpmv_ 14 10 13 4 8 8 8 4 8 8 4 124 */
/*:ref: cpptrs_ 14 8 13 4 4 8 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int cppsv_(char *uplo, integer *n, integer *nrhs, complex *ap, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpptrf_ 14 5 13 4 8 4 124 */
/*:ref: cpptrs_ 14 8 13 4 4 8 8 4 4 124 */
extern int cppsvx_(char *fact, char *uplo, integer *n, integer *nrhs, complex *ap, complex *afp, char *equed, real *s, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cppequ_ 14 8 13 4 8 6 6 6 4 124 */
/*:ref: claqhp_ 14 9 13 4 8 6 6 6 13 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cpptrf_ 14 5 13 4 8 4 124 */
/*:ref: clanhp_ 6 7 13 13 4 8 6 124 124 */
/*:ref: cppcon_ 14 9 13 4 8 6 6 8 6 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cpptrs_ 14 8 13 4 4 8 8 4 4 124 */
/*:ref: cpprfs_ 14 15 13 4 4 8 8 8 4 8 4 6 6 8 6 4 124 */
extern int cpptrf_(char *uplo, integer *n, complex *ap, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctpsv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: chpr_ 14 7 13 4 6 8 4 8 124 */
extern int cpptri_(char *uplo, integer *n, complex *ap, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctptri_ 14 7 13 13 4 8 4 124 124 */
/*:ref: chpr_ 14 7 13 4 6 8 4 8 124 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: ctpmv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
extern int cpptrs_(char *uplo, integer *n, integer *nrhs, complex *ap, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctpsv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
extern int cptcon_(integer *n, real *d__, complex *e, real *anorm, real *rcond, real *rwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: isamax_ 4 3 4 6 4 */
extern int cpteqr_(char *compz, integer *n, real *d__, real *e, complex *z__, integer *ldz, real *work, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: spttrf_ 14 4 4 6 6 4 */
/*:ref: cbdsqr_ 14 16 13 4 4 4 4 6 6 8 4 8 4 8 4 6 4 124 */
extern int cptrfs_(char *uplo, integer *n, integer *nrhs, real *d__, complex *e, real *df, complex *ef, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: cpttrs_ 14 9 13 4 4 6 8 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: isamax_ 4 3 4 6 4 */
extern int cptsv_(integer *n, integer *nrhs, real *d__, complex *e, complex *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cpttrf_ 14 4 4 6 8 4 */
/*:ref: cpttrs_ 14 9 13 4 4 6 8 8 4 4 124 */
extern int cptsvx_(char *fact, integer *n, integer *nrhs, real *d__, complex *e, real *df, complex *ef, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen fact_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cpttrf_ 14 4 4 6 8 4 */
/*:ref: clanht_ 6 5 13 4 6 8 124 */
/*:ref: cptcon_ 14 7 4 6 8 6 6 6 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cpttrs_ 14 9 13 4 4 6 8 8 4 4 124 */
/*:ref: cptrfs_ 14 17 13 4 4 6 8 6 8 8 4 8 4 6 6 8 6 4 124 */
extern int cpttrf_(integer *n, real *d__, complex *e, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cpttrs_(char *uplo, integer *n, integer *nrhs, real *d__, complex *e, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: cptts2_ 14 7 4 4 4 6 8 8 4 */
extern int cptts2_(integer *iuplo, integer *n, integer *nrhs, real *d__, complex *e, complex *b, integer *ldb);
/*:ref: csscal_ 14 4 4 6 8 4 */
extern int crot_(integer *n, complex *cx, integer *incx, complex *cy, integer *incy, real *c__, complex *s);
extern int cspcon_(char *uplo, integer *n, complex *ap, integer *ipiv, real *anorm, real *rcond, complex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: csptrs_ 14 9 13 4 4 8 4 8 4 4 124 */
extern int cspmv_(char *uplo, integer *n, complex *alpha, complex *ap, complex *x, integer *incx, complex *beta, complex *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int cspr_(char *uplo, integer *n, complex *alpha, complex *x, integer *incx, complex *ap, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int csprfs_(char *uplo, integer *n, integer *nrhs, complex *ap, complex *afp, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cspmv_ 14 10 13 4 8 8 8 4 8 8 4 124 */
/*:ref: csptrs_ 14 9 13 4 4 8 4 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int cspsv_(char *uplo, integer *n, integer *nrhs, complex *ap, integer *ipiv, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: csptrf_ 14 6 13 4 8 4 4 124 */
/*:ref: csptrs_ 14 9 13 4 4 8 4 8 4 4 124 */
extern int cspsvx_(char *fact, char *uplo, integer *n, integer *nrhs, complex *ap, complex *afp, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: csptrf_ 14 6 13 4 8 4 4 124 */
/*:ref: clansp_ 6 7 13 13 4 8 6 124 124 */
/*:ref: cspcon_ 14 9 13 4 8 4 6 6 8 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: csptrs_ 14 9 13 4 4 8 4 8 4 4 124 */
/*:ref: csprfs_ 14 16 13 4 4 8 8 4 8 4 8 4 6 6 8 6 4 124 */
extern int csptrf_(char *uplo, integer *n, complex *ap, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cspr_ 14 7 13 4 8 8 4 8 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int csptri_(char *uplo, integer *n, complex *ap, integer *ipiv, complex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cspmv_ 14 10 13 4 8 8 8 4 8 8 4 124 */
/*:ref: cdotu_ 8 6 8 4 8 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int csptrs_(char *uplo, integer *n, integer *nrhs, complex *ap, integer *ipiv, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
extern int csrot_(integer *n, complex *cx, integer *incx, complex *cy, integer *incy, real *c__, real *s);
extern int csrscl_(integer *n, real *sa, complex *sx, integer *incx);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: csscal_ 14 4 4 6 8 4 */
extern int cstedc_(char *compz, integer *n, real *d__, real *e, complex *z__, integer *ldz, complex *work, integer *lwork, real *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: csteqr_ 14 9 13 4 6 6 8 4 6 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: sstedc_ 14 12 13 4 6 6 6 4 6 4 4 4 4 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: claed0_ 14 11 4 4 6 6 8 4 8 4 6 4 4 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: clacrm_ 14 9 4 4 8 4 6 4 8 4 6 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int cstegr_(char *jobz, char *range, integer *n, real *d__, real *e, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, complex *z__, integer *ldz, integer *isuppz, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen range_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: slarre_ 14 12 4 6 6 6 4 4 4 6 6 6 6 4 */
/*:ref: clarrv_ 14 15 4 6 6 4 4 6 4 6 6 8 4 4 6 4 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int cstein_(integer *n, real *d__, real *e, integer *m, real *w, integer *iblock, integer *isplit, complex *z__, integer *ldz, real *work, integer *iwork, integer *ifail, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slarnv_ 14 4 4 4 4 6 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slagtf_ 14 9 4 6 6 6 6 6 6 4 4 */
/*:ref: sasum_ 6 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slagts_ 14 10 4 4 6 6 6 6 4 6 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
extern int csteqr_(char *compz, integer *n, real *d__, real *e, complex *z__, integer *ldz, real *work, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaev2_ 14 7 6 6 6 6 6 6 6 */
/*:ref: clasr_ 14 12 13 13 13 4 4 6 6 8 4 124 124 124 */
/*:ref: slae2_ 14 5 6 6 6 6 6 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: slasrt_ 14 5 13 4 6 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int csycon_(char *uplo, integer *n, complex *a, integer *lda, integer *ipiv, real *anorm, real *rcond, complex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: csytrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
extern int csymv_(char *uplo, integer *n, complex *alpha, complex *a, integer *lda, complex *x, integer *incx, complex *beta, complex *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int csyr_(char *uplo, integer *n, complex *alpha, complex *x, integer *incx, complex *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int csyrfs_(char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, complex *af, integer *ldaf, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: csymv_ 14 11 13 4 8 8 4 8 4 8 8 4 124 */
/*:ref: csytrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int csysv_(char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, integer *ipiv, complex *b, integer *ldb, complex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: csytrf_ 14 9 13 4 8 4 4 8 4 4 124 */
/*:ref: csytrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
extern int csysvx_(char *fact, char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, complex *af, integer *ldaf, integer *ipiv, complex *b, integer *ldb, complex *x, integer *ldx, real *rcond, real *ferr, real *berr, complex *work, integer *lwork, real *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: csytrf_ 14 9 13 4 8 4 4 8 4 4 124 */
/*:ref: clansy_ 6 8 13 13 4 8 4 6 124 124 */
/*:ref: csycon_ 14 10 13 4 8 4 4 6 6 8 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: csytrs_ 14 10 13 4 4 8 4 4 8 4 4 124 */
/*:ref: csyrfs_ 14 18 13 4 4 8 4 8 4 4 8 4 8 4 6 6 8 6 4 124 */
extern int csytf2_(char *uplo, integer *n, complex *a, integer *lda, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: csyr_ 14 8 13 4 8 8 4 8 4 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int csytrf_(char *uplo, integer *n, complex *a, integer *lda, integer *ipiv, complex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clasyf_ 14 11 13 4 4 4 8 4 4 8 4 4 124 */
/*:ref: csytf2_ 14 7 13 4 8 4 4 4 124 */
extern int csytri_(char *uplo, integer *n, complex *a, integer *lda, integer *ipiv, complex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: csymv_ 14 11 13 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cdotu_ 8 6 8 4 8 4 8 4 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
extern int csytrs_(char *uplo, integer *n, integer *nrhs, complex *a, integer *lda, integer *ipiv, complex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cswap_ 14 5 4 8 4 8 4 */
/*:ref: cgeru_ 14 9 4 4 8 8 4 8 4 8 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
extern int ctbcon_(char *norm, char *uplo, char *diag, integer *n, integer *kd, complex *ab, integer *ldab, real *rcond, complex *work, real *rwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clantb_ 6 11 13 13 13 4 4 8 4 6 124 124 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: clatbs_ 14 16 13 13 13 13 4 4 8 4 8 6 6 4 124 124 124 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csrscl_ 14 4 4 6 8 4 */
extern int ctbrfs_(char *uplo, char *trans, char *diag, integer *n, integer *kd, integer *nrhs, complex *ab, integer *ldab, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: ctbmv_ 14 12 13 13 13 4 4 8 4 8 4 124 124 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: ctbsv_ 14 12 13 13 13 4 4 8 4 8 4 124 124 124 */
extern int ctbtrs_(char *uplo, char *trans, char *diag, integer *n, integer *kd, integer *nrhs, complex *ab, integer *ldab, complex *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctbsv_ 14 12 13 13 13 4 4 8 4 8 4 124 124 124 */
extern int ctgevc_(char *side, char *howmny, logical *select, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *vl, integer *ldvl, complex *vr, integer *ldvr, integer *mm, integer *m, complex *work, real *rwork, integer *info, ftnlen side_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: cladiv_ 8 3 8 8 8 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
extern int ctgex2_(logical *wantq, logical *wantz, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *q, integer *ldq, complex *z__, integer *ldz, integer *j1, integer *info);
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
/*:ref: clartg_ 14 5 8 8 6 8 8 */
/*:ref: crot_ 14 7 4 8 4 8 4 6 8 */
extern int ctgexc_(logical *wantq, logical *wantz, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *q, integer *ldq, complex *z__, integer *ldz, integer *ifst, integer *ilst, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctgex2_ 14 13 12 12 4 8 4 8 4 8 4 8 4 4 4 */
extern int ctgsen_(integer *ijob, logical *wantq, logical *wantz, logical *select, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *alpha, complex *beta, complex *q, integer *ldq, complex *z__, integer *ldz, integer *m, real *pl, real *pr, real *dif, complex *work, integer *lwork, integer *iwork, integer *liwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: classq_ 14 5 4 8 4 6 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ctgexc_ 14 14 12 12 4 8 4 8 4 8 4 8 4 4 4 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: ctgsyl_ 14 23 13 4 4 4 8 4 8 4 8 4 8 4 8 4 8 4 6 6 8 4 4 4 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int ctgsja_(char *jobu, char *jobv, char *jobq, integer *m, integer *p, integer *n, integer *k, integer *l, complex *a, integer *lda, complex *b, integer *ldb, real *tola, real *tolb, real *alpha, real *beta, complex *u, integer *ldu, complex *v, integer *ldv, complex *q, integer *ldq, complex *work, integer *ncycle, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: claset_ 14 8 13 4 4 8 8 8 4 124 */
/*:ref: clags2_ 14 13 12 6 8 6 6 8 6 6 8 6 8 6 8 */
/*:ref: crot_ 14 7 4 8 4 8 4 6 8 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: clapll_ 14 6 4 8 4 8 4 6 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
extern int ctgsna_(char *job, char *howmny, logical *select, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *vl, integer *ldvl, complex *vr, integer *ldvr, real *s, real *dif, integer *mm, integer *m, complex *work, integer *lwork, integer *iwork, integer *info, ftnlen job_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: ctgexc_ 14 14 12 12 4 8 4 8 4 8 4 8 4 4 4 4 */
/*:ref: ctgsyl_ 14 23 13 4 4 4 8 4 8 4 8 4 8 4 8 4 8 4 6 6 8 4 4 4 124 */
extern int ctgsy2_(char *trans, integer *ijob, integer *m, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *c__, integer *ldc, complex *d__, integer *ldd, complex *e, integer *lde, complex *f, integer *ldf, real *scale, real *rdsum, real *rdscal, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cgetc2_ 14 6 4 8 4 4 4 4 */
/*:ref: cgesc2_ 14 7 4 8 4 8 4 4 6 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: clatdf_ 14 9 4 4 8 4 8 6 6 4 4 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
extern int ctgsyl_(char *trans, integer *ijob, integer *m, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *c__, integer *ldc, complex *d__, integer *ldd, complex *e, integer *lde, complex *f, integer *ldf, real *scale, real *dif, complex *work, integer *lwork, integer *iwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: ctgsy2_ 14 21 13 4 4 4 8 4 8 4 8 4 8 4 8 4 8 4 6 6 6 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
/*:ref: cgemm_ 14 15 13 13 4 4 4 8 8 4 8 4 8 8 4 124 124 */
extern int ctpcon_(char *norm, char *uplo, char *diag, integer *n, complex *ap, real *rcond, complex *work, real *rwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clantp_ 6 9 13 13 13 4 8 6 124 124 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: clatps_ 14 14 13 13 13 13 4 8 8 6 6 4 124 124 124 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csrscl_ 14 4 4 6 8 4 */
extern int ctprfs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, complex *ap, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: ctpmv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: ctpsv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
extern int ctptri_(char *uplo, char *diag, integer *n, complex *ap, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctpmv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int ctptrs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, complex *ap, complex *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctpsv_ 14 10 13 13 13 4 8 8 4 124 124 124 */
extern int ctrcon_(char *norm, char *uplo, char *diag, integer *n, complex *a, integer *lda, real *rcond, complex *work, real *rwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: clantr_ 6 11 13 13 13 4 4 8 4 6 124 124 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: clatrs_ 14 15 13 13 13 13 4 8 4 8 6 6 4 124 124 124 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csrscl_ 14 4 4 6 8 4 */
extern int ctrevc_(char *side, char *howmny, logical *select, integer *n, complex *t, integer *ldt, complex *vl, integer *ldvl, complex *vr, integer *ldvr, integer *mm, integer *m, complex *work, real *rwork, integer *info, ftnlen side_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: scasum_ 6 3 4 8 4 */
/*:ref: clatrs_ 14 15 13 13 13 13 4 8 4 8 6 6 4 124 124 124 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
extern int ctrexc_(char *compq, integer *n, complex *t, integer *ldt, complex *q, integer *ldq, integer *ifst, integer *ilst, integer *info, ftnlen compq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clartg_ 14 5 8 8 6 8 8 */
/*:ref: crot_ 14 7 4 8 4 8 4 6 8 */
extern int ctrrfs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, complex *a, integer *lda, complex *b, integer *ldb, complex *x, integer *ldx, real *ferr, real *berr, complex *work, real *rwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: ctrmv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: ctrsv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
extern int ctrsen_(char *job, char *compq, logical *select, integer *n, complex *t, integer *ldt, complex *q, integer *ldq, complex *w, integer *m, real *s, real *sep, complex *work, integer *lwork, integer *info, ftnlen job_len, ftnlen compq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: ctrexc_ 14 10 13 4 8 4 8 4 4 4 4 124 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: ctrsyl_ 14 15 13 13 4 4 4 8 4 8 4 8 4 6 4 124 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
extern int ctrsna_(char *job, char *howmny, logical *select, integer *n, complex *t, integer *ldt, complex *vl, integer *ldvl, complex *vr, integer *ldvr, real *s, real *sep, integer *mm, integer *m, complex *work, integer *ldwork, real *rwork, integer *info, ftnlen job_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
/*:ref: scnrm2_ 6 3 4 8 4 */
/*:ref: clacpy_ 14 8 13 4 4 8 4 8 4 124 */
/*:ref: ctrexc_ 14 10 13 4 8 4 8 4 4 4 4 124 */
/*:ref: clacon_ 14 5 4 8 8 6 4 */
/*:ref: clatrs_ 14 15 13 13 13 13 4 8 4 8 6 6 4 124 124 124 124 */
/*:ref: icamax_ 4 3 4 8 4 */
/*:ref: csrscl_ 14 4 4 6 8 4 */
extern int ctrsyl_(char *trana, char *tranb, integer *isgn, integer *m, integer *n, complex *a, integer *lda, complex *b, integer *ldb, complex *c__, integer *ldc, real *scale, integer *info, ftnlen trana_len, ftnlen tranb_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: clange_ 6 7 13 4 4 8 4 6 124 */
/*:ref: cdotu_ 8 6 8 4 8 4 8 4 */
/*:ref: cladiv_ 8 3 8 8 8 */
/*:ref: csscal_ 14 4 4 6 8 4 */
/*:ref: cdotc_ 8 6 8 4 8 4 8 4 */
extern int ctrti2_(char *uplo, char *diag, integer *n, complex *a, integer *lda, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctrmv_ 14 11 13 13 13 4 8 4 8 4 124 124 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int ctrtri_(char *uplo, char *diag, integer *n, complex *a, integer *lda, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: ctrti2_ 14 8 13 13 4 8 4 4 124 124 */
/*:ref: ctrmm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
extern int ctrtrs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, complex *a, integer *lda, complex *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ctrsm_ 14 15 13 13 13 13 4 4 8 8 4 8 4 124 124 124 124 */
extern int ctzrqf_(integer *m, integer *n, complex *a, integer *lda, complex *tau, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: clarfg_ 14 5 4 8 8 4 8 */
/*:ref: ccopy_ 14 5 4 8 4 8 4 */
/*:ref: cgemv_ 14 12 13 4 4 8 8 4 8 4 8 8 4 124 */
/*:ref: caxpy_ 14 6 4 8 8 4 8 4 */
/*:ref: cgerc_ 14 9 4 4 8 8 4 8 4 8 4 */
extern int ctzrzf_(integer *m, integer *n, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clatrz_ 14 7 4 4 4 8 4 8 8 */
/*:ref: clarzt_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarzb_ 14 20 13 13 13 13 4 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cung2l_(integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int cung2r_(integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int cungbr_(char *vect, integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info, ftnlen vect_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: cunglq_ 14 9 4 4 4 8 4 8 8 4 4 */
extern int cunghr_(integer *n, integer *ilo, integer *ihi, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
extern int cungl2_(integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int cunglq_(integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cungl2_ 14 8 4 4 4 8 4 8 8 4 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cungql_(integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cung2l_ 14 8 4 4 4 8 4 8 8 4 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cungqr_(integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cung2r_ 14 8 4 4 4 8 4 8 8 4 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cungr2_(integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
/*:ref: cscal_ 14 4 4 8 8 4 */
extern int cungrq_(integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cungr2_ 14 8 4 4 4 8 4 8 8 4 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cungtr_(char *uplo, integer *n, complex *a, integer *lda, complex *tau, complex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cungql_ 14 9 4 4 4 8 4 8 8 4 4 */
/*:ref: cungqr_ 14 9 4 4 4 8 4 8 8 4 4 */
extern int cunm2l_(char *side, char *trans, integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int cunm2r_(char *side, char *trans, integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int cunmbr_(char *vect, char *side, char *trans, integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *lwork, integer *info, ftnlen vect_len, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: cunmlq_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
extern int cunmhr_(char *side, char *trans, integer *m, integer *n, integer *ilo, integer *ihi, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
extern int cunml2_(char *side, char *trans, integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int cunmlq_(char *side, char *trans, integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cunml2_ 14 14 13 13 4 4 4 8 4 8 8 4 8 4 124 124 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cunmql_(char *side, char *trans, integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cunm2l_ 14 14 13 13 4 4 4 8 4 8 8 4 8 4 124 124 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cunmqr_(char *side, char *trans, integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cunm2r_ 14 14 13 13 4 4 4 8 4 8 8 4 8 4 124 124 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cunmr2_(char *side, char *trans, integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clacgv_ 14 3 4 8 4 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int cunmr3_(char *side, char *trans, integer *m, integer *n, integer *k, integer *l, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarz_ 14 11 13 4 4 4 8 4 8 8 4 8 124 */
extern int cunmrq_(char *side, char *trans, integer *m, integer *n, integer *k, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cunmr2_ 14 14 13 13 4 4 4 8 4 8 8 4 8 4 124 124 */
/*:ref: clarft_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarfb_ 14 19 13 13 13 13 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cunmrz_(char *side, char *trans, integer *m, integer *n, integer *k, integer *l, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cunmr3_ 14 15 13 13 4 4 4 4 8 4 8 8 4 8 4 124 124 */
/*:ref: clarzt_ 14 11 13 13 4 4 8 4 8 8 4 124 124 */
/*:ref: clarzb_ 14 20 13 13 13 13 4 4 4 4 8 4 8 4 8 4 8 4 124 124 124 124 */
extern int cunmtr_(char *side, char *uplo, char *trans, integer *m, integer *n, complex *a, integer *lda, complex *tau, complex *c__, integer *ldc, complex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cunmql_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
/*:ref: cunmqr_ 14 15 13 13 4 4 4 8 4 8 8 4 8 4 4 124 124 */
extern int cupgtr_(char *uplo, integer *n, complex *ap, complex *tau, complex *q, integer *ldq, complex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: cung2l_ 14 8 4 4 4 8 4 8 8 4 */
/*:ref: cung2r_ 14 8 4 4 4 8 4 8 8 4 */
extern int cupmtr_(char *side, char *uplo, char *trans, integer *m, integer *n, complex *ap, complex *tau, complex *c__, integer *ldc, complex *work, integer *info, ftnlen side_len, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: clarf_ 14 10 13 4 4 8 4 8 8 4 8 124 */
extern int dbdsdc_(char *uplo, char *compq, integer *n, doublereal *d__, doublereal *e, doublereal *u, integer *ldu, doublereal *vt, integer *ldvt, doublereal *q, integer *iq, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len, ftnlen compq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: dlasdq_ 14 17 13 4 4 4 4 4 7 7 7 4 7 4 7 4 7 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlasd0_ 14 12 4 4 7 7 7 4 7 4 4 4 7 4 */
/*:ref: dlasda_ 14 24 4 4 4 4 7 7 7 4 7 4 7 7 7 7 4 4 4 4 7 7 7 7 4 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dlasr_ 14 12 13 13 13 4 4 7 7 7 4 124 124 124 */
extern int dbdsqr_(char *uplo, integer *n, integer *ncvt, integer *nru, integer *ncc, doublereal *d__, doublereal *e, doublereal *vt, integer *ldvt, doublereal *u, integer *ldu, doublereal *c__, integer *ldc, doublereal *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlasq1_ 14 5 4 7 7 7 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: dlasr_ 14 12 13 13 13 4 4 7 7 7 4 124 124 124 */
/*:ref: dlasv2_ 14 9 7 7 7 7 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dlas2_ 14 5 7 7 7 7 7 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int ddisna_(char *job, integer *m, integer *n, doublereal *d__, doublereal *sep, integer *info, ftnlen job_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
extern int dgbbrd_(char *vect, integer *m, integer *n, integer *ncc, integer *kl, integer *ku, doublereal *ab, integer *ldab, doublereal *d__, doublereal *e, doublereal *q, integer *ldq, doublereal *pt, integer *ldpt, doublereal *c__, integer *ldc, doublereal *work, integer *info, ftnlen vect_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlargv_ 14 7 4 7 4 7 4 7 4 */
/*:ref: dlartv_ 14 8 4 7 4 7 4 7 7 4 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
extern int dgbcon_(char *norm, integer *n, integer *kl, integer *ku, doublereal *ab, integer *ldab, integer *ipiv, doublereal *anorm, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlatbs_ 14 16 13 13 13 13 4 4 7 4 7 7 7 4 124 124 124 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: drscl_ 14 4 4 7 7 4 */
extern int dgbequ_(integer *m, integer *n, integer *kl, integer *ku, doublereal *ab, integer *ldab, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal *colcnd, doublereal *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
extern int dgbrfs_(char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, doublereal *ab, integer *ldab, doublereal *afb, integer *ldafb, integer *ipiv, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgbmv_ 14 14 13 4 4 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dgbtrs_ 14 12 13 4 4 4 4 7 4 4 7 4 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
extern int dgbsv_(integer *n, integer *kl, integer *ku, integer *nrhs, doublereal *ab, integer *ldab, integer *ipiv, doublereal *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgbtrf_ 14 8 4 4 4 4 7 4 4 4 */
/*:ref: dgbtrs_ 14 12 13 4 4 4 4 7 4 4 7 4 4 124 */
extern int dgbsvx_(char *fact, char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, doublereal *ab, integer *ldab, doublereal *afb, integer *ldafb, integer *ipiv, char *equed, doublereal *r__, doublereal *c__, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen trans_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgbequ_ 14 12 4 4 4 4 7 4 7 7 7 7 7 4 */
/*:ref: dlaqgb_ 14 13 4 4 4 4 7 4 7 7 7 7 7 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgbtrf_ 14 8 4 4 4 4 7 4 4 4 */
/*:ref: dlantb_ 7 11 13 13 13 4 4 7 4 7 124 124 124 */
/*:ref: dlangb_ 7 8 13 4 4 4 7 4 7 124 */
/*:ref: dgbcon_ 14 13 13 4 4 4 7 4 4 7 7 7 4 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dgbtrs_ 14 12 13 4 4 4 4 7 4 4 7 4 4 124 */
/*:ref: dgbrfs_ 14 20 13 4 4 4 4 7 4 7 4 4 7 4 7 4 7 7 7 4 4 124 */
extern int dgbtf2_(integer *m, integer *n, integer *kl, integer *ku, doublereal *ab, integer *ldab, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
extern int dgbtrf_(integer *m, integer *n, integer *kl, integer *ku, doublereal *ab, integer *ldab, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dgbtf2_ 14 8 4 4 4 4 7 4 4 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlaswp_ 14 7 4 7 4 4 4 4 4 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
extern int dgbtrs_(char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, doublereal *ab, integer *ldab, integer *ipiv, doublereal *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
/*:ref: dtbsv_ 14 12 13 13 13 4 4 7 4 7 4 124 124 124 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
extern int dgebak_(char *job, char *side, integer *n, integer *ilo, integer *ihi, doublereal *scale, integer *m, doublereal *v, integer *ldv, integer *info, ftnlen job_len, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dgebal_(char *job, integer *n, doublereal *a, integer *lda, integer *ilo, integer *ihi, doublereal *scale, integer *info, ftnlen job_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dgebd2_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *d__, doublereal *e, doublereal *tauq, doublereal *taup, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dgebrd_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *d__, doublereal *e, doublereal *tauq, doublereal *taup, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlabrd_ 14 13 4 4 4 7 4 7 7 7 7 7 4 7 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dgebd2_ 14 10 4 4 7 4 7 7 7 7 7 4 */
extern int dgecon_(char *norm, integer *n, doublereal *a, integer *lda, doublereal *anorm, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dlatrs_ 14 15 13 13 13 13 4 7 4 7 7 7 4 124 124 124 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: drscl_ 14 4 4 7 7 4 */
extern int dgeequ_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal *colcnd, doublereal *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
extern int dgees_(char *jobvs, char *sort, L_fp select, integer *n, doublereal *a, integer *lda, integer *sdim, doublereal *wr, doublereal *wi, doublereal *vs, integer *ldvs, doublereal *work, integer *lwork, logical *bwork, integer *info, ftnlen jobvs_len, ftnlen sort_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dgebal_ 14 9 13 4 7 4 4 4 7 4 124 */
/*:ref: dgehrd_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorghr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dhseqr_ 14 16 13 13 4 4 4 7 4 7 7 7 4 7 4 4 124 124 */
/*:ref: dtrsen_ 14 20 13 13 12 4 7 4 7 4 7 7 4 7 7 7 4 4 4 4 124 124 */
/*:ref: dgebak_ 14 12 13 13 4 4 4 7 4 7 4 4 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dgeesx_(char *jobvs, char *sort, L_fp select, char *sense, integer *n, doublereal *a, integer *lda, integer *sdim, doublereal *wr, doublereal *wi, doublereal *vs, integer *ldvs, doublereal *rconde, doublereal *rcondv, doublereal *work, integer *lwork, integer *iwork, integer *liwork, logical *bwork, integer *info, ftnlen jobvs_len, ftnlen sort_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dgebal_ 14 9 13 4 7 4 4 4 7 4 124 */
/*:ref: dgehrd_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorghr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dhseqr_ 14 16 13 13 4 4 4 7 4 7 7 7 4 7 4 4 124 124 */
/*:ref: dtrsen_ 14 20 13 13 12 4 7 4 7 4 7 7 4 7 7 7 4 4 4 4 124 124 */
/*:ref: dgebak_ 14 12 13 13 4 4 4 7 4 7 4 4 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dgeev_(char *jobvl, char *jobvr, integer *n, doublereal *a, integer *lda, doublereal *wr, doublereal *wi, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, doublereal *work, integer *lwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dgebal_ 14 9 13 4 7 4 4 4 7 4 124 */
/*:ref: dgehrd_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorghr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dhseqr_ 14 16 13 13 4 4 4 7 4 7 7 7 4 7 4 4 124 124 */
/*:ref: dtrevc_ 14 16 13 13 12 4 7 4 7 4 7 4 4 4 7 4 124 124 */
/*:ref: dgebak_ 14 12 13 13 4 4 4 7 4 7 4 4 124 124 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
extern int dgeevx_(char *balanc, char *jobvl, char *jobvr, char *sense, integer *n, doublereal *a, integer *lda, doublereal *wr, doublereal *wi, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, integer *ilo, integer *ihi, doublereal *scale, doublereal *abnrm, doublereal *rconde, doublereal *rcondv, doublereal *work, integer *lwork, integer *iwork, integer *info, ftnlen balanc_len, ftnlen jobvl_len, ftnlen jobvr_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dgebal_ 14 9 13 4 7 4 4 4 7 4 124 */
/*:ref: dgehrd_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorghr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dhseqr_ 14 16 13 13 4 4 4 7 4 7 7 7 4 7 4 4 124 124 */
/*:ref: dtrevc_ 14 16 13 13 12 4 7 4 7 4 7 4 4 4 7 4 124 124 */
/*:ref: dtrsna_ 14 20 13 13 12 4 7 4 7 4 7 4 7 7 4 4 7 4 4 4 124 124 */
/*:ref: dgebak_ 14 12 13 13 4 4 4 7 4 7 4 4 124 124 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
extern int dgegs_(char *jobvsl, char *jobvsr, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *alphar, doublereal *alphai, doublereal *beta, doublereal *vsl, integer *ldvsl, doublereal *vsr, integer *ldvsr, doublereal *work, integer *lwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dggbal_ 14 13 13 4 7 4 7 4 4 4 7 7 7 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dgghrd_ 14 16 13 13 4 4 4 7 4 7 4 7 4 7 4 4 124 124 */
/*:ref: dhgeqz_ 14 23 13 13 13 4 4 4 7 4 7 4 7 7 7 7 4 7 4 7 4 4 124 124 124 */
/*:ref: dggbak_ 14 13 13 13 4 4 4 7 7 4 7 4 4 124 124 */
extern int dgegv_(char *jobvl, char *jobvr, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *alphar, doublereal *alphai, doublereal *beta, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, doublereal *work, integer *lwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dggbal_ 14 13 13 4 7 4 7 4 4 4 7 7 7 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dgghrd_ 14 16 13 13 4 4 4 7 4 7 4 7 4 7 4 4 124 124 */
/*:ref: dhgeqz_ 14 23 13 13 13 4 4 4 7 4 7 4 7 7 7 7 4 7 4 7 4 4 124 124 124 */
/*:ref: dtgevc_ 14 18 13 13 12 4 7 4 7 4 7 4 7 4 4 4 7 4 124 124 */
/*:ref: dggbak_ 14 13 13 13 4 4 4 7 7 4 7 4 4 124 124 */
extern int dgehd2_(integer *n, integer *ilo, integer *ihi, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dgehrd_(integer *n, integer *ilo, integer *ihi, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlahrd_ 14 10 4 4 4 7 4 7 7 4 7 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
/*:ref: dgehd2_ 14 8 4 4 4 7 4 7 7 4 */
extern int dgelq2_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dgelqf_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgelq2_ 14 7 4 4 7 4 7 7 4 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dgels_(char *trans, integer *m, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *work, integer *lwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dgelqf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormlq_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
extern int dgelsd_(integer *m, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *s, doublereal *rcond, integer *rank, doublereal *work, integer *lwork, integer *iwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dgebrd_ 14 11 4 4 7 4 7 7 7 7 7 4 4 */
/*:ref: dormbr_ 14 17 13 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 124 */
/*:ref: dlalsd_ 14 14 13 4 4 4 7 7 7 4 7 4 7 4 4 124 */
/*:ref: dgelqf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dormlq_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
extern int dgelss_(integer *m, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *s, doublereal *rcond, integer *rank, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dgebrd_ 14 11 4 4 7 4 7 7 7 7 7 4 4 */
/*:ref: dormbr_ 14 17 13 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 124 */
/*:ref: dorgbr_ 14 11 13 4 4 4 7 4 7 7 4 4 124 */
/*:ref: dbdsqr_ 14 16 13 4 4 4 4 7 7 7 4 7 4 7 4 7 4 124 */
/*:ref: drscl_ 14 4 4 7 7 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgelqf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormlq_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
extern int dgelsx_(integer *m, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *jpvt, doublereal *rcond, integer *rank, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dgeqpf_ 14 8 4 4 7 4 4 7 7 4 */
/*:ref: dlaic1_ 14 9 4 4 7 7 7 7 7 7 7 */
/*:ref: dtzrqf_ 14 6 4 4 7 4 7 4 */
/*:ref: dorm2r_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dlatzm_ 14 11 13 4 4 7 4 7 7 7 4 7 124 */
extern int dgelsy_(integer *m, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *jpvt, doublereal *rcond, integer *rank, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dgeqp3_ 14 9 4 4 7 4 4 7 7 4 4 */
/*:ref: dlaic1_ 14 9 4 4 7 7 7 7 7 7 7 */
/*:ref: dtzrzf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dormrz_ 14 16 13 13 4 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
extern int dgeql2_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dgeqlf_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgeql2_ 14 7 4 4 7 4 7 7 4 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dgeqp3_(integer *m, integer *n, doublereal *a, integer *lda, integer *jpvt, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dlaqps_ 14 14 4 4 4 4 4 7 4 4 7 7 7 7 7 4 */
/*:ref: dlaqp2_ 14 10 4 4 4 7 4 4 7 7 7 7 */
extern int dgeqpf_(integer *m, integer *n, doublereal *a, integer *lda, integer *jpvt, doublereal *tau, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dgeqr2_ 14 7 4 4 7 4 7 7 4 */
/*:ref: dorm2r_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dgeqr2_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dgeqrf_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgeqr2_ 14 7 4 4 7 4 7 7 4 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dgerfs_(char *trans, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, integer *ipiv, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dgetrs_ 14 10 13 4 4 7 4 4 7 4 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
extern int dgerq2_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dgerqf_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgerq2_ 14 7 4 4 7 4 7 7 4 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dgesc2_(integer *n, doublereal *a, integer *lda, doublereal *rhs, integer *ipiv, integer *jpiv, doublereal *scale);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlaswp_ 14 7 4 7 4 4 4 4 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dgesdd_(char *jobz, integer *m, integer *n, doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, integer *iwork, integer *info, ftnlen jobz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dgebrd_ 14 11 4 4 7 4 7 7 7 7 7 4 4 */
/*:ref: dbdsdc_ 14 16 13 13 4 7 7 7 4 7 4 7 4 7 4 4 124 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dormbr_ 14 17 13 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dorgbr_ 14 11 13 4 4 4 7 4 7 7 4 4 124 */
/*:ref: dgelqf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dorglq_ 14 9 4 4 4 7 4 7 7 4 4 */
extern int dgesv_(integer *n, integer *nrhs, doublereal *a, integer *lda, integer *ipiv, doublereal *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgetrf_ 14 6 4 4 7 4 4 4 */
/*:ref: dgetrs_ 14 10 13 4 4 7 4 4 7 4 4 124 */
extern int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, integer *info, ftnlen jobu_len, ftnlen jobvt_len);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dgebrd_ 14 11 4 4 7 4 7 7 7 7 7 4 4 */
/*:ref: dorgbr_ 14 11 13 4 4 4 7 4 7 7 4 4 124 */
/*:ref: dbdsqr_ 14 16 13 4 4 4 4 7 7 7 4 7 4 7 4 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dormbr_ 14 17 13 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 124 */
/*:ref: dgelqf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dorglq_ 14 9 4 4 4 7 4 7 7 4 4 */
extern int dgesvx_(char *fact, char *trans, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, integer *ipiv, char *equed, doublereal *r__, doublereal *c__, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen trans_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgeequ_ 14 10 4 4 7 4 7 7 7 7 7 4 */
/*:ref: dlaqge_ 14 11 4 4 7 4 7 7 7 7 7 13 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dgetrf_ 14 6 4 4 7 4 4 4 */
/*:ref: dlantr_ 7 11 13 13 13 4 4 7 4 7 124 124 124 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dgecon_ 14 10 13 4 7 4 7 7 7 4 4 124 */
/*:ref: dgetrs_ 14 10 13 4 4 7 4 4 7 4 4 124 */
/*:ref: dgerfs_ 14 18 13 4 4 7 4 7 4 4 7 4 7 4 7 7 7 4 4 124 */
extern int dgetc2_(integer *n, doublereal *a, integer *lda, integer *ipiv, integer *jpiv, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
extern int dgetf2_(integer *m, integer *n, doublereal *a, integer *lda, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
extern int dgetrf_(integer *m, integer *n, doublereal *a, integer *lda, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dgetf2_ 14 6 4 4 7 4 4 4 */
/*:ref: dlaswp_ 14 7 4 7 4 4 4 4 4 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
extern int dgetri_(integer *n, doublereal *a, integer *lda, integer *ipiv, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtrtri_ 14 8 13 13 4 7 4 4 124 124 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dgetrs_(char *trans, integer *n, integer *nrhs, doublereal *a, integer *lda, integer *ipiv, doublereal *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaswp_ 14 7 4 7 4 4 4 4 4 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
extern int dggbak_(char *job, char *side, integer *n, integer *ilo, integer *ihi, doublereal *lscale, doublereal *rscale, integer *m, doublereal *v, integer *ldv, integer *info, ftnlen job_len, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dggbal_(char *job, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *ilo, integer *ihi, doublereal *lscale, doublereal *rscale, doublereal *work, integer *info, ftnlen job_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: idamax_ 4 3 4 7 4 */
extern int dgges_(char *jobvsl, char *jobvsr, char *sort, L_fp delctg, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *sdim, doublereal *alphar, doublereal *alphai, doublereal *beta, doublereal *vsl, integer *ldvsl, doublereal *vsr, integer *ldvsr, doublereal *work, integer *lwork, logical *bwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len, ftnlen sort_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dggbal_ 14 13 13 4 7 4 7 4 4 4 7 7 7 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dgghrd_ 14 16 13 13 4 4 4 7 4 7 4 7 4 7 4 4 124 124 */
/*:ref: dhgeqz_ 14 23 13 13 13 4 4 4 7 4 7 4 7 7 7 7 4 7 4 7 4 4 124 124 124 */
/*:ref: dtgsen_ 14 25 4 12 12 12 4 7 4 7 4 7 7 7 7 4 7 4 4 7 7 7 7 4 4 4 4 */
/*:ref: dggbak_ 14 13 13 13 4 4 4 7 7 4 7 4 4 124 124 */
extern int dggesx_(char *jobvsl, char *jobvsr, char *sort, L_fp delctg, char *sense, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *sdim, doublereal *alphar, doublereal *alphai, doublereal *beta, doublereal *vsl, integer *ldvsl, doublereal *vsr, integer *ldvsr, doublereal *rconde, doublereal *rcondv, doublereal *work, integer *lwork, integer *iwork, integer *liwork, logical *bwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len, ftnlen sort_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dggbal_ 14 13 13 4 7 4 7 4 4 4 7 7 7 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dgghrd_ 14 16 13 13 4 4 4 7 4 7 4 7 4 7 4 4 124 124 */
/*:ref: dhgeqz_ 14 23 13 13 13 4 4 4 7 4 7 4 7 7 7 7 4 7 4 7 4 4 124 124 124 */
/*:ref: dtgsen_ 14 25 4 12 12 12 4 7 4 7 4 7 7 7 7 4 7 4 4 7 7 7 7 4 4 4 4 */
/*:ref: dggbak_ 14 13 13 13 4 4 4 7 7 4 7 4 4 124 124 */
extern int dggev_(char *jobvl, char *jobvr, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *alphar, doublereal *alphai, doublereal *beta, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, doublereal *work, integer *lwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dggbal_ 14 13 13 4 7 4 7 4 4 4 7 7 7 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dgghrd_ 14 16 13 13 4 4 4 7 4 7 4 7 4 7 4 4 124 124 */
/*:ref: dhgeqz_ 14 23 13 13 13 4 4 4 7 4 7 4 7 7 7 7 4 7 4 7 4 4 124 124 124 */
/*:ref: dtgevc_ 14 18 13 13 12 4 7 4 7 4 7 4 7 4 4 4 7 4 124 124 */
/*:ref: dggbak_ 14 13 13 13 4 4 4 7 7 4 7 4 4 124 124 */
extern int dggevx_(char *balanc, char *jobvl, char *jobvr, char *sense, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *alphar, doublereal *alphai, doublereal *beta, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, integer *ilo, integer *ihi, doublereal *lscale, doublereal *rscale, doublereal *abnrm, doublereal *bbnrm, doublereal *rconde, doublereal *rcondv, doublereal *work, integer *lwork, integer *iwork, logical *bwork, integer *info, ftnlen balanc_len, ftnlen jobvl_len, ftnlen jobvr_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dggbal_ 14 13 13 4 7 4 7 4 4 4 7 7 7 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dgghrd_ 14 16 13 13 4 4 4 7 4 7 4 7 4 7 4 4 124 124 */
/*:ref: dhgeqz_ 14 23 13 13 13 4 4 4 7 4 7 4 7 7 7 7 4 7 4 7 4 4 124 124 124 */
/*:ref: dtgevc_ 14 18 13 13 12 4 7 4 7 4 7 4 7 4 4 4 7 4 124 124 */
/*:ref: dtgsna_ 14 22 13 13 12 4 7 4 7 4 7 4 7 4 7 7 4 4 7 4 4 4 124 124 */
/*:ref: dggbak_ 14 13 13 13 4 4 4 7 7 4 7 4 4 124 124 */
extern int dggglm_(integer *n, integer *m, integer *p, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *d__, doublereal *x, doublereal *y, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dggqrf_ 14 12 4 4 4 7 4 7 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dtrsv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dormrq_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
extern int dgghrd_(char *compq, char *compz, integer *n, integer *ilo, integer *ihi, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *q, integer *ldq, doublereal *z__, integer *ldz, integer *info, ftnlen compq_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
extern int dgglse_(integer *m, integer *n, integer *p, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *c__, doublereal *d__, doublereal *x, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dggrqf_ 14 12 4 4 4 7 4 7 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dtrsv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dtrmv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dormrq_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
extern int dggqrf_(integer *n, integer *m, integer *p, doublereal *a, integer *lda, doublereal *taua, doublereal *b, integer *ldb, doublereal *taub, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dgerqf_ 14 8 4 4 7 4 7 7 4 4 */
extern int dggrqf_(integer *m, integer *p, integer *n, doublereal *a, integer *lda, doublereal *taua, doublereal *b, integer *ldb, doublereal *taub, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgerqf_ 14 8 4 4 7 4 7 7 4 4 */
/*:ref: dormrq_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dgeqrf_ 14 8 4 4 7 4 7 7 4 4 */
extern int dggsvd_(char *jobu, char *jobv, char *jobq, integer *m, integer *n, integer *p, integer *k, integer *l, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *alpha, doublereal *beta, doublereal *u, integer *ldu, doublereal *v, integer *ldv, doublereal *q, integer *ldq, doublereal *work, integer *iwork, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dggsvp_ 14 27 13 13 13 4 4 4 7 4 7 4 7 7 4 4 7 4 7 4 7 4 4 7 7 4 124 124 124 */
/*:ref: dtgsja_ 14 28 13 13 13 4 4 4 4 4 7 4 7 4 7 7 7 7 7 4 7 4 7 4 7 4 4 124 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
extern int dggsvp_(char *jobu, char *jobv, char *jobq, integer *m, integer *p, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *tola, doublereal *tolb, integer *k, integer *l, doublereal *u, integer *ldu, doublereal *v, integer *ldv, doublereal *q, integer *ldq, integer *iwork, doublereal *tau, doublereal *work, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgeqpf_ 14 8 4 4 7 4 4 7 7 4 */
/*:ref: dlapmt_ 14 6 12 4 4 7 4 4 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorg2r_ 14 8 4 4 4 7 4 7 7 4 */
/*:ref: dgerq2_ 14 7 4 4 7 4 7 7 4 */
/*:ref: dormr2_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dorm2r_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dgeqr2_ 14 7 4 4 7 4 7 7 4 */
extern int dgtcon_(char *norm, integer *n, doublereal *dl, doublereal *d__, doublereal *du, doublereal *du2, integer *ipiv, doublereal *anorm, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dgttrs_ 14 12 13 4 4 7 7 7 7 4 7 4 4 124 */
extern int dgtrfs_(char *trans, integer *n, integer *nrhs, doublereal *dl, doublereal *d__, doublereal *du, doublereal *dlf, doublereal *df, doublereal *duf, doublereal *du2, integer *ipiv, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlagtm_ 14 13 13 4 4 7 7 7 7 7 4 7 7 4 124 */
/*:ref: dgttrs_ 14 12 13 4 4 7 7 7 7 4 7 4 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
extern int dgtsv_(integer *n, integer *nrhs, doublereal *dl, doublereal *d__, doublereal *du, doublereal *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dgtsvx_(char *fact, char *trans, integer *n, integer *nrhs, doublereal *dl, doublereal *d__, doublereal *du, doublereal *dlf, doublereal *df, doublereal *duf, doublereal *du2, integer *ipiv, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgttrf_ 14 7 4 7 7 7 7 4 4 */
/*:ref: dlangt_ 7 6 13 4 7 7 7 124 */
/*:ref: dgtcon_ 14 13 13 4 7 7 7 7 4 7 7 7 4 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dgttrs_ 14 12 13 4 4 7 7 7 7 4 7 4 4 124 */
/*:ref: dgtrfs_ 14 21 13 4 4 7 7 7 7 7 7 7 4 7 4 7 4 7 7 7 4 4 124 */
extern int dgttrf_(integer *n, doublereal *dl, doublereal *d__, doublereal *du, doublereal *du2, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dgttrs_(char *trans, integer *n, integer *nrhs, doublereal *dl, doublereal *d__, doublereal *du, doublereal *du2, integer *ipiv, doublereal *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dgtts2_ 14 10 4 4 4 7 7 7 7 4 7 4 */
extern int dgtts2_(integer *itrans, integer *n, integer *nrhs, doublereal *dl, doublereal *d__, doublereal *du, doublereal *du2, integer *ipiv, doublereal *b, integer *ldb);
extern int dhgeqz_(char *job, char *compq, char *compz, integer *n, integer *ilo, integer *ihi, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *alphar, doublereal *alphai, doublereal *beta, doublereal *q, integer *ldq, doublereal *z__, integer *ldz, doublereal *work, integer *lwork, integer *info, ftnlen job_len, ftnlen compq_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlanhs_ 7 6 13 4 7 4 7 124 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dlag2_ 14 10 7 4 7 4 7 7 7 7 7 7 */
/*:ref: dlasv2_ 14 9 7 7 7 7 7 7 7 7 7 */
/*:ref: dlapy3_ 7 3 7 7 7 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
extern int dhsein_(char *side, char *eigsrc, char *initv, logical *select, integer *n, doublereal *h__, integer *ldh, doublereal *wr, doublereal *wi, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, integer *mm, integer *m, doublereal *work, integer *ifaill, integer *ifailr, integer *info, ftnlen side_len, ftnlen eigsrc_len, ftnlen initv_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlanhs_ 7 6 13 4 7 4 7 124 */
/*:ref: dlaein_ 14 16 12 12 4 7 4 7 7 7 7 7 4 7 7 7 7 4 */
extern int dhseqr_(char *job, char *compz, integer *n, integer *ilo, integer *ihi, doublereal *h__, integer *ldh, doublereal *wr, doublereal *wi, doublereal *z__, integer *ldz, doublereal *work, integer *lwork, integer *info, ftnlen job_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dlahqr_ 14 14 12 12 4 4 4 7 4 7 7 4 4 7 4 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlanhs_ 7 6 13 4 7 4 7 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarfx_ 14 9 13 4 4 7 7 7 4 7 124 */
extern int dlabad_(doublereal *small, doublereal *large);
extern int dlabrd_(integer *m, integer *n, integer *nb, doublereal *a, integer *lda, doublereal *d__, doublereal *e, doublereal *tauq, doublereal *taup, doublereal *x, integer *ldx, doublereal *y, integer *ldy);
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dlacon_(integer *n, doublereal *v, doublereal *x, integer *isgn, doublereal *est, integer *kase);
/*:ref: dasum_ 7 3 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
extern int dlacpy_(char *uplo, integer *m, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int dladiv_(doublereal *a, doublereal *b, doublereal *c__, doublereal *d__, doublereal *p, doublereal *q);
extern int dlae2_(doublereal *a, doublereal *b, doublereal *c__, doublereal *rt1, doublereal *rt2);
extern int dlaebz_(integer *ijob, integer *nitmax, integer *n, integer *mmax, integer *minp, integer *nbmin, doublereal *abstol, doublereal *reltol, doublereal *pivmin, doublereal *d__, doublereal *e, doublereal *e2, integer *nval, doublereal *ab, doublereal *c__, integer *mout, integer *nab, doublereal *work, integer *iwork, integer *info);
extern int dlaed0_(integer *icompq, integer *qsiz, integer *n, doublereal *d__, doublereal *e, doublereal *q, integer *ldq, doublereal *qstore, integer *ldqs, doublereal *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dlaed1_ 14 10 4 7 7 4 4 7 4 7 4 4 */
/*:ref: dlaed7_ 14 22 4 4 4 4 4 4 7 7 4 4 7 4 7 4 4 4 4 4 7 7 4 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
extern int dlaed1_(integer *n, doublereal *d__, doublereal *q, integer *ldq, integer *indxq, doublereal *rho, integer *cutpnt, doublereal *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlaed2_ 14 17 4 4 4 7 7 4 4 7 7 7 7 7 4 4 4 4 4 */
/*:ref: dlaed3_ 14 14 4 4 4 7 7 4 7 7 7 4 4 7 7 4 */
/*:ref: dlamrg_ 14 6 4 4 7 4 4 4 */
extern int dlaed2_(integer *k, integer *n, integer *n1, doublereal *d__, doublereal *q, integer *ldq, integer *indxq, doublereal *rho, doublereal *z__, doublereal *dlamda, doublereal *w, doublereal *q2, integer *indx, integer *indxc, integer *indxp, integer *coltyp, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlamrg_ 14 6 4 4 7 4 4 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
extern int dlaed3_(integer *k, integer *n, integer *n1, doublereal *d__, doublereal *q, integer *ldq, doublereal *rho, doublereal *dlamda, doublereal *q2, integer *indx, integer *ctot, doublereal *w, doublereal *s, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamc3_ 7 2 7 7 */
/*:ref: dlaed4_ 14 8 4 4 7 7 7 7 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
extern int dlaed4_(integer *n, integer *i__, doublereal *d__, doublereal *z__, doublereal *delta, doublereal *rho, doublereal *dlam, integer *info);
/*:ref: dlaed5_ 14 6 4 7 7 7 7 7 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlaed6_ 14 8 4 12 7 7 7 7 7 4 */
extern int dlaed5_(integer *i__, doublereal *d__, doublereal *z__, doublereal *delta, doublereal *rho, doublereal *dlam);
extern int dlaed6_(integer *kniter, logical *orgati, doublereal *rho, doublereal *d__, doublereal *z__, doublereal *finit, doublereal *tau, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
extern int dlaed7_(integer *icompq, integer *n, integer *qsiz, integer *tlvls, integer *curlvl, integer *curpbm, doublereal *d__, doublereal *q, integer *ldq, integer *indxq, doublereal *rho, integer *cutpnt, doublereal *qstore, integer *qptr, integer *prmptr, integer *perm, integer *givptr, integer *givcol, doublereal *givnum, doublereal *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaeda_ 14 14 4 4 4 4 4 4 4 4 7 7 4 7 7 4 */
/*:ref: dlaed8_ 14 22 4 4 4 4 7 7 4 4 7 4 7 7 7 4 7 4 4 4 7 4 4 4 */
/*:ref: dlaed9_ 14 13 4 4 4 4 7 7 4 7 7 7 7 4 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dlamrg_ 14 6 4 4 7 4 4 4 */
extern int dlaed8_(integer *icompq, integer *k, integer *n, integer *qsiz, doublereal *d__, doublereal *q, integer *ldq, integer *indxq, doublereal *rho, integer *cutpnt, doublereal *z__, doublereal *dlamda, doublereal *q2, integer *ldq2, doublereal *w, integer *perm, integer *givptr, integer *givcol, doublereal *givnum, integer *indxp, integer *indx, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlamrg_ 14 6 4 4 7 4 4 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
extern int dlaed9_(integer *k, integer *kstart, integer *kstop, integer *n, doublereal *d__, doublereal *q, integer *ldq, doublereal *rho, doublereal *dlamda, doublereal *w, doublereal *s, integer *lds, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamc3_ 7 2 7 7 */
/*:ref: dlaed4_ 14 8 4 4 7 7 7 7 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
extern int dlaeda_(integer *n, integer *tlvls, integer *curlvl, integer *curpbm, integer *prmptr, integer *perm, integer *givptr, integer *givcol, doublereal *givnum, doublereal *q, integer *qptr, doublereal *z__, doublereal *ztemp, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
extern int dlaein_(logical *rightv, logical *noinit, integer *n, doublereal *h__, integer *ldh, doublereal *wr, doublereal *wi, doublereal *vr, doublereal *vi, doublereal *b, integer *ldb, doublereal *work, doublereal *eps3, doublereal *smlnum, doublereal *bignum, integer *info);
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlatrs_ 14 15 13 13 13 13 4 7 4 7 7 7 4 124 124 124 124 */
/*:ref: dasum_ 7 3 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dladiv_ 14 6 7 7 7 7 7 7 */
extern int dlaev2_(doublereal *a, doublereal *b, doublereal *c__, doublereal *rt1, doublereal *rt2, doublereal *cs1, doublereal *sn1);
extern int dlaexc_(logical *wantq, integer *n, doublereal *t, integer *ldt, doublereal *q, integer *ldq, integer *j1, integer *n1, integer *n2, doublereal *work, integer *info);
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlasy2_ 14 16 12 12 4 4 4 7 4 7 4 7 4 7 7 4 7 4 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarfx_ 14 9 13 4 4 7 7 7 4 7 124 */
/*:ref: dlanv2_ 14 10 7 7 7 7 7 7 7 7 7 7 */
extern int dlag2_(doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *safmin, doublereal *scale1, doublereal *scale2, doublereal *wr1, doublereal *wr2, doublereal *wi);
extern int dlags2_(logical *upper, doublereal *a1, doublereal *a2, doublereal *a3, doublereal *b1, doublereal *b2, doublereal *b3, doublereal *csu, doublereal *snu, doublereal *csv, doublereal *snv, doublereal *csq, doublereal *snq);
/*:ref: dlasv2_ 14 9 7 7 7 7 7 7 7 7 7 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
extern int dlagtf_(integer *n, doublereal *a, doublereal *lambda, doublereal *b, doublereal *c__, doublereal *tol, doublereal *d__, integer *in, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
extern int dlagtm_(char *trans, integer *n, integer *nrhs, doublereal *alpha, doublereal *dl, doublereal *d__, doublereal *du, doublereal *x, integer *ldx, doublereal *beta, doublereal *b, integer *ldb, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int dlagts_(integer *job, integer *n, doublereal *a, doublereal *b, doublereal *c__, doublereal *d__, integer *in, doublereal *y, doublereal *tol, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
extern int dlagv2_(doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *alphar, doublereal *alphai, doublereal *beta, doublereal *csl, doublereal *snl, doublereal *csr, doublereal *snr);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dlag2_ 14 10 7 4 7 4 7 7 7 7 7 7 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dlasv2_ 14 9 7 7 7 7 7 7 7 7 7 */
extern int dlahqr_(logical *wantt, logical *wantz, integer *n, integer *ilo, integer *ihi, doublereal *h__, integer *ldh, doublereal *wr, doublereal *wi, integer *iloz, integer *ihiz, doublereal *z__, integer *ldz, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlanhs_ 7 6 13 4 7 4 7 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlanv2_ 14 10 7 7 7 7 7 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
extern int dlahrd_(integer *n, integer *k, integer *nb, doublereal *a, integer *lda, doublereal *tau, doublereal *t, integer *ldt, doublereal *y, integer *ldy);
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dtrmv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dlaic1_(integer *job, integer *j, doublereal *x, doublereal *sest, doublereal *w, doublereal *gamma, doublereal *sestpr, doublereal *s, doublereal *c__);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
extern int dlaln2_(logical *ltrans, integer *na, integer *nw, doublereal *smin, doublereal *ca, doublereal *a, integer *lda, doublereal *d1, doublereal *d2, doublereal *b, integer *ldb, doublereal *wr, doublereal *wi, doublereal *x, integer *ldx, doublereal *scale, doublereal *xnorm, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dladiv_ 14 6 7 7 7 7 7 7 */
extern int dlals0_(integer *icompq, integer *nl, integer *nr, integer *sqre, integer *nrhs, doublereal *b, integer *ldb, doublereal *bx, integer *ldbx, integer *perm, integer *givptr, integer *givcol, integer *ldgcol, doublereal *givnum, integer *ldgnum, doublereal *poles, doublereal *difl, doublereal *difr, doublereal *z__, integer *k, doublereal *c__, doublereal *s, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlamc3_ 7 2 7 7 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
extern int dlalsa_(integer *icompq, integer *smlsiz, integer *n, integer *nrhs, doublereal *b, integer *ldb, doublereal *bx, integer *ldbx, doublereal *u, integer *ldu, doublereal *vt, integer *k, doublereal *difl, doublereal *difr, doublereal *z__, doublereal *poles, integer *givptr, integer *givcol, integer *ldgcol, integer *perm, doublereal *givnum, doublereal *c__, doublereal *s, doublereal *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlasdt_ 14 7 4 4 4 4 4 4 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlals0_ 14 24 4 4 4 4 4 7 4 7 4 4 4 4 4 7 4 7 7 7 7 4 7 7 7 4 */
extern int dlalsd_(char *uplo, integer *smlsiz, integer *n, integer *nrhs, doublereal *d__, doublereal *e, doublereal *b, integer *ldb, doublereal *rcond, integer *rank, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dlasdq_ 14 17 13 4 4 4 4 4 7 7 7 4 7 4 7 4 7 4 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dlasrt_ 14 5 13 4 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlasda_ 14 24 4 4 4 4 7 7 7 4 7 4 7 7 7 7 4 4 4 4 7 7 7 7 4 4 */
/*:ref: dlalsa_ 14 26 4 4 4 4 7 4 7 4 7 4 7 4 7 7 7 7 4 4 4 4 7 7 7 7 4 4 */
extern doublereal dlamch_(char *cmach, ftnlen cmach_len);
extern int dlamc1_(integer *beta, integer *t, logical *rnd, logical *ieee1);
extern int dlamc2_(integer *beta, integer *t, logical *rnd, doublereal *eps, integer *emin, doublereal *rmin, integer *emax, doublereal *rmax);
extern doublereal dlamc3_(doublereal *a, doublereal *b);
extern int dlamc4_(integer *emin, doublereal *start, integer *base);
extern int dlamc5_(integer *beta, integer *p, integer *emin, logical *ieee, integer *emax, doublereal *rmax);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int dlamrg_(integer *n1, integer *n2, doublereal *a, integer *dtrd1, integer *dtrd2, integer *index);
extern doublereal dlangb_(char *norm, integer *n, integer *kl, integer *ku, doublereal *ab, integer *ldab, doublereal *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal dlange_(char *norm, integer *m, integer *n, doublereal *a, integer *lda, doublereal *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal dlangt_(char *norm, integer *n, doublereal *dl, doublereal *d__, doublereal *du, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal dlanhs_(char *norm, integer *n, doublereal *a, integer *lda, doublereal *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal dlansb_(char *norm, char *uplo, integer *n, integer *k, doublereal *ab, integer *ldab, doublereal *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal dlansp_(char *norm, char *uplo, integer *n, doublereal *ap, doublereal *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal dlanst_(char *norm, integer *n, doublereal *d__, doublereal *e, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal dlansy_(char *norm, char *uplo, integer *n, doublereal *a, integer *lda, doublereal *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal dlantb_(char *norm, char *uplo, char *diag, integer *n, integer *k, doublereal *ab, integer *ldab, doublereal *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal dlantp_(char *norm, char *uplo, char *diag, integer *n, doublereal *ap, doublereal *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal dlantr_(char *norm, char *uplo, char *diag, integer *m, integer *n, doublereal *a, integer *lda, doublereal *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern int dlanv2_(doublereal *a, doublereal *b, doublereal *c__, doublereal *d__, doublereal *rt1r, doublereal *rt1i, doublereal *rt2r, doublereal *rt2i, doublereal *cs, doublereal *sn);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlapy2_ 7 2 7 7 */
extern int dlapll_(integer *n, doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *ssmin);
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlas2_ 14 5 7 7 7 7 7 */
extern int dlapmt_(logical *forwrd, integer *m, integer *n, doublereal *x, integer *ldx, integer *k);
extern doublereal dlapy2_(doublereal *x, doublereal *y);
extern doublereal dlapy3_(doublereal *x, doublereal *y, doublereal *z__);
extern int dlaqgb_(integer *m, integer *n, integer *kl, integer *ku, doublereal *ab, integer *ldab, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal *colcnd, doublereal *amax, char *equed, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
extern int dlaqge_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal *colcnd, doublereal *amax, char *equed, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
extern int dlaqp2_(integer *m, integer *n, integer *offset, doublereal *a, integer *lda, integer *jpvt, doublereal *tau, doublereal *vn1, doublereal *vn2, doublereal *work);
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
/*:ref: dnrm2_ 7 3 4 7 4 */
extern int dlaqps_(integer *m, integer *n, integer *offset, integer *nb, integer *kb, doublereal *a, integer *lda, integer *jpvt, doublereal *tau, doublereal *vn1, doublereal *vn2, doublereal *auxv, doublereal *f, integer *ldf);
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dnrm2_ 7 3 4 7 4 */
extern int dlaqsb_(char *uplo, integer *n, integer *kd, doublereal *ab, integer *ldab, doublereal *s, doublereal *scond, doublereal *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int dlaqsp_(char *uplo, integer *n, doublereal *ap, doublereal *s, doublereal *scond, doublereal *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int dlaqsy_(char *uplo, integer *n, doublereal *a, integer *lda, doublereal *s, doublereal *scond, doublereal *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int dlaqtr_(logical *ltran, logical *lreal, integer *n, doublereal *t, integer *ldt, doublereal *b, doublereal *w, doublereal *scale, doublereal *x, doublereal *work, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dasum_ 7 3 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlaln2_ 14 18 12 4 4 7 7 7 4 7 7 7 4 7 7 7 4 7 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dladiv_ 14 6 7 7 7 7 7 7 */
extern int dlar1v_(integer *n, integer *b1, integer *bn, doublereal *sigma, doublereal *d__, doublereal *l, doublereal *ld, doublereal *lld, doublereal *gersch, doublereal *z__, doublereal *ztz, doublereal *mingma, integer *r__, integer *isuppz, doublereal *work);
/*:ref: dlamch_ 7 2 13 124 */
extern int dlar2v_(integer *n, doublereal *x, doublereal *y, doublereal *z__, integer *incx, doublereal *c__, doublereal *s, integer *incc);
extern int dlarf_(char *side, integer *m, integer *n, doublereal *v, integer *incv, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
extern int dlarfb_(char *side, char *trans, char *direct, char *storev, integer *m, integer *n, integer *k, doublereal *v, integer *ldv, doublereal *t, integer *ldt, doublereal *c__, integer *ldc, doublereal *work, integer *ldwork, ftnlen side_len, ftnlen trans_len, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dtrmm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
extern int dlarfg_(integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *tau);
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dlarft_(char *direct, char *storev, integer *n, integer *k, doublereal *v, integer *ldv, doublereal *tau, doublereal *t, integer *ldt, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dtrmv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
extern int dlarfx_(char *side, integer *m, integer *n, doublereal *v, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
extern int dlargv_(integer *n, doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *c__, integer *incc);
extern int dlarnv_(integer *idist, integer *iseed, integer *n, doublereal *x);
/*:ref: dlaruv_ 14 3 4 4 7 */
extern int dlarrb_(integer *n, doublereal *d__, doublereal *l, doublereal *ld, doublereal *lld, integer *ifirst, integer *ilast, doublereal *sigma, doublereal *reltol, doublereal *w, doublereal *wgap, doublereal *werr, doublereal *work, integer *iwork, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
extern int dlarre_(integer *n, doublereal *d__, doublereal *e, doublereal *tol, integer *nsplit, integer *isplit, integer *m, doublereal *w, doublereal *woff, doublereal *gersch, doublereal *work, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlasq2_ 14 3 4 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
extern int dlarrf_(integer *n, doublereal *d__, doublereal *l, doublereal *ld, doublereal *lld, integer *ifirst, integer *ilast, doublereal *w, doublereal *dplus, doublereal *lplus, doublereal *work, integer *iwork, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
extern int dlarrv_(integer *n, doublereal *d__, doublereal *l, integer *isplit, integer *m, doublereal *w, integer *iblock, doublereal *gersch, doublereal *tol, doublereal *z__, integer *ldz, integer *isuppz, doublereal *work, integer *iwork, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlarrb_ 14 15 4 7 7 7 7 4 4 7 7 7 7 7 7 4 4 */
/*:ref: dlarrf_ 14 13 4 7 7 7 7 4 4 7 7 7 7 4 4 */
/*:ref: dstein_ 14 13 4 7 7 4 7 4 4 7 4 7 4 4 4 */
/*:ref: dlar1v_ 14 15 4 4 4 7 7 7 7 7 7 7 7 7 4 4 7 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
extern int dlartg_(doublereal *f, doublereal *g, doublereal *cs, doublereal *sn, doublereal *r__);
/*:ref: dlamch_ 7 2 13 124 */
extern int dlartv_(integer *n, doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *c__, doublereal *s, integer *incc);
extern int dlaruv_(integer *iseed, integer *n, doublereal *x);
extern int dlarz_(char *side, integer *m, integer *n, integer *l, doublereal *v, integer *incv, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
extern int dlarzb_(char *side, char *trans, char *direct, char *storev, integer *m, integer *n, integer *k, integer *l, doublereal *v, integer *ldv, doublereal *t, integer *ldt, doublereal *c__, integer *ldc, doublereal *work, integer *ldwork, ftnlen side_len, ftnlen trans_len, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dtrmm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
extern int dlarzt_(char *direct, char *storev, integer *n, integer *k, doublereal *v, integer *ldv, doublereal *tau, doublereal *t, integer *ldt, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dtrmv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
extern int dlas2_(doublereal *f, doublereal *g, doublereal *h__, doublereal *ssmin, doublereal *ssmax);
extern int dlascl_(char *type__, integer *kl, integer *ku, doublereal *cfrom, doublereal *cto, integer *m, integer *n, doublereal *a, integer *lda, integer *info, ftnlen type_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
extern int dlasd0_(integer *n, integer *sqre, doublereal *d__, doublereal *e, doublereal *u, integer *ldu, doublereal *vt, integer *ldvt, integer *smlsiz, integer *iwork, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlasdq_ 14 17 13 4 4 4 4 4 7 7 7 4 7 4 7 4 7 4 124 */
/*:ref: dlasdt_ 14 7 4 4 4 4 4 4 4 */
/*:ref: dlasd1_ 14 14 4 4 4 7 7 7 7 4 7 4 4 4 7 4 */
extern int dlasd1_(integer *nl, integer *nr, integer *sqre, doublereal *d__, doublereal *alpha, doublereal *beta, doublereal *u, integer *ldu, doublereal *vt, integer *ldvt, integer *idxq, integer *iwork, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlasd2_ 14 23 4 4 4 4 7 7 7 7 7 4 7 4 7 7 4 7 4 4 4 4 4 4 4 */
/*:ref: dlasd3_ 14 20 4 4 4 4 7 7 4 7 7 4 7 4 7 4 7 4 4 4 7 4 */
/*:ref: dlamrg_ 14 6 4 4 7 4 4 4 */
extern int dlasd2_(integer *nl, integer *nr, integer *sqre, integer *k, doublereal *d__, doublereal *z__, doublereal *alpha, doublereal *beta, doublereal *u, integer *ldu, doublereal *vt, integer *ldvt, doublereal *dsigma, doublereal *u2, integer *ldu2, doublereal *vt2, integer *ldvt2, integer *idxp, integer *idx, integer *idxc, integer *idxq, integer *coltyp, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamrg_ 14 6 4 4 7 4 4 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
extern int dlasd3_(integer *nl, integer *nr, integer *sqre, integer *k, doublereal *d__, doublereal *q, integer *ldq, doublereal *dsigma, doublereal *u, integer *ldu, doublereal *u2, integer *ldu2, doublereal *vt, integer *ldvt, doublereal *vt2, integer *ldvt2, integer *idxc, integer *ctot, doublereal *z__, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlamc3_ 7 2 7 7 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlasd4_ 14 9 4 4 7 7 7 7 7 7 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
extern int dlasd4_(integer *n, integer *i__, doublereal *d__, doublereal *z__, doublereal *delta, doublereal *rho, doublereal *sigma, doublereal *work, integer *info);
/*:ref: dlasd5_ 14 7 4 7 7 7 7 7 7 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlaed6_ 14 8 4 12 7 7 7 7 7 4 */
extern int dlasd5_(integer *i__, doublereal *d__, doublereal *z__, doublereal *delta, doublereal *rho, doublereal *dsigma, doublereal *work);
extern int dlasd6_(integer *icompq, integer *nl, integer *nr, integer *sqre, doublereal *d__, doublereal *vf, doublereal *vl, doublereal *alpha, doublereal *beta, integer *idxq, integer *perm, integer *givptr, integer *givcol, integer *ldgcol, doublereal *givnum, integer *ldgnum, doublereal *poles, doublereal *difl, doublereal *difr, doublereal *z__, integer *k, doublereal *c__, doublereal *s, doublereal *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlasd7_ 14 27 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 4 4 4 4 4 4 4 7 4 7 7 4 */
/*:ref: dlasd8_ 14 12 4 4 7 7 7 7 7 7 4 7 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlamrg_ 14 6 4 4 7 4 4 4 */
extern int dlasd7_(integer *icompq, integer *nl, integer *nr, integer *sqre, integer *k, doublereal *d__, doublereal *z__, doublereal *zw, doublereal *vf, doublereal *vfw, doublereal *vl, doublereal *vlw, doublereal *alpha, doublereal *beta, doublereal *dsigma, integer *idx, integer *idxp, integer *idxq, integer *perm, integer *givptr, integer *givcol, integer *ldgcol, doublereal *givnum, integer *ldgnum, doublereal *c__, doublereal *s, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamrg_ 14 6 4 4 7 4 4 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
extern int dlasd8_(integer *icompq, integer *k, doublereal *d__, doublereal *z__, doublereal *vf, doublereal *vl, doublereal *difl, doublereal *difr, integer *lddifr, doublereal *dsigma, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamc3_ 7 2 7 7 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlasd4_ 14 9 4 4 7 7 7 7 7 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
extern int dlasd9_(integer *icompq, integer *ldu, integer *k, doublereal *d__, doublereal *z__, doublereal *vf, doublereal *vl, doublereal *difl, doublereal *difr, doublereal *dsigma, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamc3_ 7 2 7 7 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlasd4_ 14 9 4 4 7 7 7 7 7 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
extern int dlasda_(integer *icompq, integer *smlsiz, integer *n, integer *sqre, doublereal *d__, doublereal *e, doublereal *u, integer *ldu, doublereal *vt, integer *k, doublereal *difl, doublereal *difr, doublereal *z__, doublereal *poles, integer *givptr, integer *givcol, integer *ldgcol, integer *perm, doublereal *givnum, doublereal *c__, doublereal *s, doublereal *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlasdq_ 14 17 13 4 4 4 4 4 7 7 7 4 7 4 7 4 7 4 124 */
/*:ref: dlasdt_ 14 7 4 4 4 4 4 4 4 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlasd6_ 14 26 4 4 4 4 7 7 7 7 7 4 4 4 4 4 7 4 7 7 7 7 4 7 7 7 4 4 */
extern int dlasdq_(char *uplo, integer *sqre, integer *n, integer *ncvt, integer *nru, integer *ncc, doublereal *d__, doublereal *e, doublereal *vt, integer *ldvt, doublereal *u, integer *ldu, doublereal *c__, integer *ldc, doublereal *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: dlasr_ 14 12 13 13 13 4 4 7 7 7 4 124 124 124 */
/*:ref: dbdsqr_ 14 16 13 4 4 4 4 7 7 7 4 7 4 7 4 7 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dlasdt_(integer *n, integer *lvl, integer *nd, integer *inode, integer *ndiml, integer *ndimr, integer *msub);
extern int dlaset_(char *uplo, integer *m, integer *n, doublereal *alpha, doublereal *beta, doublereal *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int dlasq1_(integer *n, doublereal *d__, doublereal *e, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlas2_ 14 5 7 7 7 7 7 */
/*:ref: dlasrt_ 14 5 13 4 7 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlasq2_ 14 3 4 7 4 */
extern int dlasq2_(integer *n, doublereal *z__, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlasrt_ 14 5 13 4 7 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dlasq3_ 14 12 4 4 7 4 7 7 7 7 4 4 4 12 */
extern int dlasq3_(integer *i0, integer *n0, doublereal *z__, integer *pp, doublereal *dmin__, doublereal *sigma, doublereal *desig, doublereal *qmax, integer *nfail, integer *iter, integer *ndiv, logical *ieee);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlasq4_ 14 13 4 4 7 4 4 7 7 7 7 7 7 7 4 */
/*:ref: dlasq5_ 14 12 4 4 7 4 7 7 7 7 7 7 7 12 */
/*:ref: dlasq6_ 14 10 4 4 7 4 7 7 7 7 7 7 */
extern int dlasq4_(integer *i0, integer *n0, doublereal *z__, integer *pp, integer *n0in, doublereal *dmin__, doublereal *dmin1, doublereal *dmin2, doublereal *dn, doublereal *dn1, doublereal *dn2, doublereal *tau, integer *ttype);
extern int dlasq5_(integer *i0, integer *n0, doublereal *z__, integer *pp, doublereal *tau, doublereal *dmin__, doublereal *dmin1, doublereal *dmin2, doublereal *dn, doublereal *dnm1, doublereal *dnm2, logical *ieee);
extern int dlasq6_(integer *i0, integer *n0, doublereal *z__, integer *pp, doublereal *dmin__, doublereal *dmin1, doublereal *dmin2, doublereal *dn, doublereal *dnm1, doublereal *dnm2);
/*:ref: dlamch_ 7 2 13 124 */
extern int dlasr_(char *side, char *pivot, char *direct, integer *m, integer *n, doublereal *c__, doublereal *s, doublereal *a, integer *lda, ftnlen side_len, ftnlen pivot_len, ftnlen direct_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dlasrt_(char *id, integer *n, doublereal *d__, integer *info, ftnlen id_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dlassq_(integer *n, doublereal *x, integer *incx, doublereal *scale, doublereal *sumsq);
extern int dlasv2_(doublereal *f, doublereal *g, doublereal *h__, doublereal *ssmin, doublereal *ssmax, doublereal *snr, doublereal *csr, doublereal *snl, doublereal *csl);
/*:ref: dlamch_ 7 2 13 124 */
extern int dlaswp_(integer *n, doublereal *a, integer *lda, integer *k1, integer *k2, integer *ipiv, integer *incx);
extern int dlasy2_(logical *ltranl, logical *ltranr, integer *isgn, integer *n1, integer *n2, doublereal *tl, integer *ldtl, doublereal *tr, integer *ldtr, doublereal *b, integer *ldb, doublereal *scale, doublereal *x, integer *ldx, doublereal *xnorm, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dlasyf_(char *uplo, integer *n, integer *nb, integer *kb, doublereal *a, integer *lda, integer *ipiv, doublereal *w, integer *ldw, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
extern int dlatbs_(char *uplo, char *trans, char *diag, char *normin, integer *n, integer *kd, doublereal *ab, integer *ldab, doublereal *x, doublereal *scale, doublereal *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dasum_ 7 3 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dtbsv_ 14 12 13 13 13 4 4 7 4 7 4 124 124 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
extern int dlatdf_(integer *ijob, integer *n, doublereal *z__, integer *ldz, doublereal *rhs, doublereal *rdsum, doublereal *rdscal, integer *ipiv, integer *jpiv);
/*:ref: dlaswp_ 14 7 4 7 4 4 4 4 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
/*:ref: dgecon_ 14 10 13 4 7 4 7 7 7 4 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dgesc2_ 14 7 4 7 4 7 4 4 7 */
/*:ref: dasum_ 7 3 4 7 4 */
extern int dlatps_(char *uplo, char *trans, char *diag, char *normin, integer *n, doublereal *ap, doublereal *x, doublereal *scale, doublereal *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dasum_ 7 3 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dtpsv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
extern int dlatrd_(char *uplo, integer *n, integer *nb, doublereal *a, integer *lda, doublereal *e, doublereal *tau, doublereal *w, integer *ldw, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dsymv_ 14 11 13 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
extern int dlatrs_(char *uplo, char *trans, char *diag, char *normin, integer *n, doublereal *a, integer *lda, doublereal *x, doublereal *scale, doublereal *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dasum_ 7 3 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dtrsv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
extern int dlatrz_(integer *m, integer *n, integer *l, doublereal *a, integer *lda, doublereal *tau, doublereal *work);
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dlarz_ 14 11 13 4 4 4 7 4 7 7 4 7 124 */
extern int dlatzm_(char *side, integer *m, integer *n, doublereal *v, integer *incv, doublereal *tau, doublereal *c1, doublereal *c2, integer *ldc, doublereal *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
extern int dlauu2_(char *uplo, integer *n, doublereal *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dlauum_(char *uplo, integer *n, doublereal *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dlauu2_ 14 6 13 4 7 4 4 124 */
/*:ref: dtrmm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dsyrk_ 14 12 13 13 4 4 7 7 4 7 7 4 124 124 */
extern int dopgtr_(char *uplo, integer *n, doublereal *ap, doublereal *tau, doublereal *q, integer *ldq, doublereal *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorg2l_ 14 8 4 4 4 7 4 7 7 4 */
/*:ref: dorg2r_ 14 8 4 4 4 7 4 7 7 4 */
extern int dopmtr_(char *side, char *uplo, char *trans, integer *m, integer *n, doublereal *ap, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *info, ftnlen side_len, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dorg2l_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dorg2r_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dorgbr_(char *vect, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info, ftnlen vect_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dorglq_ 14 9 4 4 4 7 4 7 7 4 4 */
extern int dorghr_(integer *n, integer *ilo, integer *ihi, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
extern int dorgl2_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dorglq_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorgl2_ 14 8 4 4 4 7 4 7 7 4 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dorgql_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorg2l_ 14 8 4 4 4 7 4 7 7 4 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dorgqr_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorg2r_ 14 8 4 4 4 7 4 7 7 4 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dorgr2_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dorgrq_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorgr2_ 14 8 4 4 4 7 4 7 7 4 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dorgtr_(char *uplo, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorgql_ 14 9 4 4 4 7 4 7 7 4 4 */
/*:ref: dorgqr_ 14 9 4 4 4 7 4 7 7 4 4 */
extern int dorm2l_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dorm2r_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dormbr_(char *vect, char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info, ftnlen vect_len, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dormlq_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
extern int dormhr_(char *side, char *trans, integer *m, integer *n, integer *ilo, integer *ihi, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
extern int dorml2_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dormlq_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorml2_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dormql_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorm2l_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dormqr_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dorm2r_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dormr2_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarf_ 14 10 13 4 4 7 4 7 7 4 7 124 */
extern int dormr3_(char *side, char *trans, integer *m, integer *n, integer *k, integer *l, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarz_ 14 11 13 4 4 4 7 4 7 7 4 7 124 */
extern int dormrq_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dormr2_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dlarft_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarfb_ 14 19 13 13 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dormrz_(char *side, char *trans, integer *m, integer *n, integer *k, integer *l, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dormr3_ 14 15 13 13 4 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dlarzt_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarzb_ 14 20 13 13 13 13 4 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern int dormtr_(char *side, char *uplo, char *trans, integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info, ftnlen side_len, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dormql_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
/*:ref: dormqr_ 14 15 13 13 4 4 4 7 4 7 7 4 7 4 4 124 124 */
extern int dpbcon_(char *uplo, integer *n, integer *kd, doublereal *ab, integer *ldab, doublereal *anorm, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dlatbs_ 14 16 13 13 13 13 4 4 7 4 7 7 7 4 124 124 124 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: drscl_ 14 4 4 7 7 4 */
extern int dpbequ_(char *uplo, integer *n, integer *kd, doublereal *ab, integer *ldab, doublereal *s, doublereal *scond, doublereal *amax, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dpbrfs_(char *uplo, integer *n, integer *kd, integer *nrhs, doublereal *ab, integer *ldab, doublereal *afb, integer *ldafb, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsbmv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dpbtrs_ 14 10 13 4 4 4 7 4 7 4 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
extern int dpbstf_(char *uplo, integer *n, integer *kd, doublereal *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dsyr_ 14 8 13 4 7 7 4 7 4 124 */
extern int dpbsv_(char *uplo, integer *n, integer *kd, integer *nrhs, doublereal *ab, integer *ldab, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpbtrf_ 14 7 13 4 4 7 4 4 124 */
/*:ref: dpbtrs_ 14 10 13 4 4 4 7 4 7 4 4 124 */
extern int dpbsvx_(char *fact, char *uplo, integer *n, integer *kd, integer *nrhs, doublereal *ab, integer *ldab, doublereal *afb, integer *ldafb, char *equed, doublereal *s, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpbequ_ 14 10 13 4 4 7 4 7 7 7 4 124 */
/*:ref: dlaqsb_ 14 11 13 4 4 7 4 7 7 7 13 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dpbtrf_ 14 7 13 4 4 7 4 4 124 */
/*:ref: dlansb_ 7 9 13 13 4 4 7 4 7 124 124 */
/*:ref: dpbcon_ 14 11 13 4 4 7 4 7 7 7 4 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dpbtrs_ 14 10 13 4 4 4 7 4 7 4 4 124 */
/*:ref: dpbrfs_ 14 18 13 4 4 4 7 4 7 4 7 4 7 4 7 7 7 4 4 124 */
extern int dpbtf2_(char *uplo, integer *n, integer *kd, doublereal *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dsyr_ 14 8 13 4 7 7 4 7 4 124 */
extern int dpbtrf_(char *uplo, integer *n, integer *kd, doublereal *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dpbtf2_ 14 7 13 4 4 7 4 4 124 */
/*:ref: dpotf2_ 14 6 13 4 7 4 4 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dsyrk_ 14 12 13 13 4 4 7 7 4 7 7 4 124 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
extern int dpbtrs_(char *uplo, integer *n, integer *kd, integer *nrhs, doublereal *ab, integer *ldab, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtbsv_ 14 12 13 13 13 4 4 7 4 7 4 124 124 124 */
extern int dpocon_(char *uplo, integer *n, doublereal *a, integer *lda, doublereal *anorm, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dlatrs_ 14 15 13 13 13 13 4 7 4 7 7 7 4 124 124 124 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: drscl_ 14 4 4 7 7 4 */
extern int dpoequ_(integer *n, doublereal *a, integer *lda, doublereal *s, doublereal *scond, doublereal *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dporfs_(char *uplo, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsymv_ 14 11 13 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dpotrs_ 14 9 13 4 4 7 4 7 4 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
extern int dposv_(char *uplo, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpotrf_ 14 6 13 4 7 4 4 124 */
/*:ref: dpotrs_ 14 9 13 4 4 7 4 7 4 4 124 */
extern int dposvx_(char *fact, char *uplo, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, char *equed, doublereal *s, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpoequ_ 14 7 4 7 4 7 7 7 4 */
/*:ref: dlaqsy_ 14 10 13 4 7 4 7 7 7 13 124 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dpotrf_ 14 6 13 4 7 4 4 124 */
/*:ref: dlansy_ 7 8 13 13 4 7 4 7 124 124 */
/*:ref: dpocon_ 14 10 13 4 7 4 7 7 7 4 4 124 */
/*:ref: dpotrs_ 14 9 13 4 4 7 4 7 4 4 124 */
/*:ref: dporfs_ 14 17 13 4 4 7 4 7 4 7 4 7 4 7 7 7 4 4 124 */
extern int dpotf2_(char *uplo, integer *n, doublereal *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dpotrf_(char *uplo, integer *n, doublereal *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dpotf2_ 14 6 13 4 7 4 4 124 */
/*:ref: dsyrk_ 14 12 13 13 4 4 7 7 4 7 7 4 124 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
extern int dpotri_(char *uplo, integer *n, doublereal *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtrtri_ 14 8 13 13 4 7 4 4 124 124 */
/*:ref: dlauum_ 14 6 13 4 7 4 4 124 */
extern int dpotrs_(char *uplo, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
extern int dppcon_(char *uplo, integer *n, doublereal *ap, doublereal *anorm, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dlatps_ 14 14 13 13 13 13 4 7 7 7 7 4 124 124 124 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: drscl_ 14 4 4 7 7 4 */
extern int dppequ_(char *uplo, integer *n, doublereal *ap, doublereal *s, doublereal *scond, doublereal *amax, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dpprfs_(char *uplo, integer *n, integer *nrhs, doublereal *ap, doublereal *afp, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dspmv_ 14 10 13 4 7 7 7 4 7 7 4 124 */
/*:ref: dpptrs_ 14 8 13 4 4 7 7 4 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
extern int dppsv_(char *uplo, integer *n, integer *nrhs, doublereal *ap, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpptrf_ 14 5 13 4 7 4 124 */
/*:ref: dpptrs_ 14 8 13 4 4 7 7 4 4 124 */
extern int dppsvx_(char *fact, char *uplo, integer *n, integer *nrhs, doublereal *ap, doublereal *afp, char *equed, doublereal *s, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dppequ_ 14 8 13 4 7 7 7 7 4 124 */
/*:ref: dlaqsp_ 14 9 13 4 7 7 7 7 13 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dpptrf_ 14 5 13 4 7 4 124 */
/*:ref: dlansp_ 7 7 13 13 4 7 7 124 124 */
/*:ref: dppcon_ 14 9 13 4 7 7 7 7 4 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dpptrs_ 14 8 13 4 4 7 7 4 4 124 */
/*:ref: dpprfs_ 14 15 13 4 4 7 7 7 4 7 4 7 7 7 4 4 124 */
extern int dpptrf_(char *uplo, integer *n, doublereal *ap, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtpsv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dspr_ 14 7 13 4 7 7 4 7 124 */
extern int dpptri_(char *uplo, integer *n, doublereal *ap, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtptri_ 14 7 13 13 4 7 4 124 124 */
/*:ref: dspr_ 14 7 13 4 7 7 4 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dtpmv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
extern int dpptrs_(char *uplo, integer *n, integer *nrhs, doublereal *ap, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtpsv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
extern int dptcon_(integer *n, doublereal *d__, doublereal *e, doublereal *anorm, doublereal *rcond, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: idamax_ 4 3 4 7 4 */
extern int dpteqr_(char *compz, integer *n, doublereal *d__, doublereal *e, doublereal *z__, integer *ldz, doublereal *work, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dpttrf_ 14 4 4 7 7 4 */
/*:ref: dbdsqr_ 14 16 13 4 4 4 4 7 7 7 4 7 4 7 4 7 4 124 */
extern int dptrfs_(integer *n, integer *nrhs, doublereal *d__, doublereal *e, doublereal *df, doublereal *ef, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dpttrs_ 14 7 4 4 7 7 7 4 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
extern int dptsv_(integer *n, integer *nrhs, doublereal *d__, doublereal *e, doublereal *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpttrf_ 14 4 4 7 7 4 */
/*:ref: dpttrs_ 14 7 4 4 7 7 7 4 4 */
extern int dptsvx_(char *fact, integer *n, integer *nrhs, doublereal *d__, doublereal *e, doublereal *df, doublereal *ef, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *info, ftnlen fact_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dpttrf_ 14 4 4 7 7 4 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dptcon_ 14 7 4 7 7 7 7 7 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dpttrs_ 14 7 4 4 7 7 7 4 4 */
/*:ref: dptrfs_ 14 14 4 4 7 7 7 7 7 4 7 4 7 7 7 4 */
extern int dpttrf_(integer *n, doublereal *d__, doublereal *e, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int dpttrs_(integer *n, integer *nrhs, doublereal *d__, doublereal *e, doublereal *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dptts2_ 14 6 4 4 7 7 7 4 */
extern int dptts2_(integer *n, integer *nrhs, doublereal *d__, doublereal *e, doublereal *b, integer *ldb);
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int drscl_(integer *n, doublereal *sa, doublereal *sx, integer *incx);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dsbev_(char *jobz, char *uplo, integer *n, integer *kd, doublereal *ab, integer *ldab, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlansb_ 7 9 13 13 4 4 7 4 7 124 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dsbtrd_ 14 14 13 13 4 4 7 4 7 7 7 4 7 4 124 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dsbevd_(char *jobz, char *uplo, integer *n, integer *kd, doublereal *ab, integer *ldab, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlansb_ 7 9 13 13 4 4 7 4 7 124 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dsbtrd_ 14 14 13 13 4 4 7 4 7 7 7 4 7 4 124 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dstedc_ 14 12 13 4 7 7 7 4 7 4 4 4 4 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dsbevx_(char *jobz, char *range, char *uplo, integer *n, integer *kd, doublereal *ab, integer *ldab, doublereal *q, integer *ldq, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlansb_ 7 9 13 13 4 4 7 4 7 124 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dsbtrd_ 14 14 13 13 4 4 7 4 7 7 7 4 7 4 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: dstein_ 14 13 4 7 7 4 7 4 4 7 4 7 4 4 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dsbgst_(char *vect, char *uplo, integer *n, integer *ka, integer *kb, doublereal *ab, integer *ldab, doublereal *bb, integer *ldbb, doublereal *x, integer *ldx, doublereal *work, integer *info, ftnlen vect_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: dlargv_ 14 7 4 7 4 7 4 7 4 */
/*:ref: dlartv_ 14 8 4 7 4 7 4 7 7 4 */
/*:ref: dlar2v_ 14 8 4 7 7 7 4 7 7 4 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
extern int dsbgv_(char *jobz, char *uplo, integer *n, integer *ka, integer *kb, doublereal *ab, integer *ldab, doublereal *bb, integer *ldbb, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpbstf_ 14 7 13 4 4 7 4 4 124 */
/*:ref: dsbgst_ 14 15 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 */
/*:ref: dsbtrd_ 14 14 13 13 4 4 7 4 7 7 7 4 7 4 124 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
extern int dsbgvd_(char *jobz, char *uplo, integer *n, integer *ka, integer *kb, doublereal *ab, integer *ldab, doublereal *bb, integer *ldbb, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpbstf_ 14 7 13 4 4 7 4 4 124 */
/*:ref: dsbgst_ 14 15 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 */
/*:ref: dsbtrd_ 14 14 13 13 4 4 7 4 7 7 7 4 7 4 124 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dstedc_ 14 12 13 4 7 7 7 4 7 4 4 4 4 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
extern int dsbgvx_(char *jobz, char *range, char *uplo, integer *n, integer *ka, integer *kb, doublereal *ab, integer *ldab, doublereal *bb, integer *ldbb, doublereal *q, integer *ldq, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpbstf_ 14 7 13 4 4 7 4 4 124 */
/*:ref: dsbgst_ 14 15 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 */
/*:ref: dsbtrd_ 14 14 13 13 4 4 7 4 7 7 7 4 7 4 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: dstein_ 14 13 4 7 7 4 7 4 4 7 4 7 4 4 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dsbtrd_(char *vect, char *uplo, integer *n, integer *kd, doublereal *ab, integer *ldab, doublereal *d__, doublereal *e, doublereal *q, integer *ldq, doublereal *work, integer *info, ftnlen vect_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlargv_ 14 7 4 7 4 7 4 7 4 */
/*:ref: dlartv_ 14 8 4 7 4 7 4 7 7 4 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: dlar2v_ 14 8 4 7 7 7 4 7 7 4 */
extern doublereal dsecnd_(void);
/*:ref: etime_ 6 1 6 */
extern int dspcon_(char *uplo, integer *n, doublereal *ap, integer *ipiv, doublereal *anorm, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dsptrs_ 14 9 13 4 4 7 4 7 4 4 124 */
extern int dspev_(char *jobz, char *uplo, integer *n, doublereal *ap, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlansp_ 7 7 13 13 4 7 7 124 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dsptrd_ 14 8 13 4 7 7 7 7 4 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dopgtr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
extern int dspevd_(char *jobz, char *uplo, integer *n, doublereal *ap, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlansp_ 7 7 13 13 4 7 7 124 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dsptrd_ 14 8 13 4 7 7 7 7 4 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dstedc_ 14 12 13 4 7 7 7 4 7 4 4 4 4 124 */
/*:ref: dopmtr_ 14 14 13 13 13 4 4 7 7 7 4 7 4 124 124 124 */
extern int dspevx_(char *jobz, char *range, char *uplo, integer *n, doublereal *ap, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlansp_ 7 7 13 13 4 7 7 124 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dsptrd_ 14 8 13 4 7 7 7 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dopgtr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: dstein_ 14 13 4 7 7 4 7 4 4 7 4 7 4 4 4 */
/*:ref: dopmtr_ 14 14 13 13 13 4 4 7 7 7 4 7 4 124 124 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dspgst_(integer *itype, char *uplo, integer *n, doublereal *ap, doublereal *bp, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtpsv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
/*:ref: dspmv_ 14 10 13 4 7 7 7 4 7 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dspr2_ 14 9 13 4 7 7 4 7 4 7 124 */
/*:ref: dtpmv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
extern int dspgv_(integer *itype, char *jobz, char *uplo, integer *n, doublereal *ap, doublereal *bp, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpptrf_ 14 5 13 4 7 4 124 */
/*:ref: dspgst_ 14 7 4 13 4 7 7 4 124 */
/*:ref: dspev_ 14 11 13 13 4 7 7 7 4 7 4 124 124 */
/*:ref: dtpsv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
/*:ref: dtpmv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
extern int dspgvd_(integer *itype, char *jobz, char *uplo, integer *n, doublereal *ap, doublereal *bp, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpptrf_ 14 5 13 4 7 4 124 */
/*:ref: dspgst_ 14 7 4 13 4 7 7 4 124 */
/*:ref: dspevd_ 14 14 13 13 4 7 7 7 4 7 4 4 4 4 124 124 */
/*:ref: dtpsv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
/*:ref: dtpmv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
extern int dspgvx_(integer *itype, char *jobz, char *range, char *uplo, integer *n, doublereal *ap, doublereal *bp, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpptrf_ 14 5 13 4 7 4 124 */
/*:ref: dspgst_ 14 7 4 13 4 7 7 4 124 */
/*:ref: dspevx_ 14 21 13 13 13 4 7 7 7 4 4 7 4 7 7 4 7 4 4 4 124 124 124 */
/*:ref: dtpsv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
/*:ref: dtpmv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
extern int dsprfs_(char *uplo, integer *n, integer *nrhs, doublereal *ap, doublereal *afp, integer *ipiv, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dspmv_ 14 10 13 4 7 7 7 4 7 7 4 124 */
/*:ref: dsptrs_ 14 9 13 4 4 7 4 7 4 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
extern int dspsv_(char *uplo, integer *n, integer *nrhs, doublereal *ap, integer *ipiv, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dsptrf_ 14 6 13 4 7 4 4 124 */
/*:ref: dsptrs_ 14 9 13 4 4 7 4 7 4 4 124 */
extern int dspsvx_(char *fact, char *uplo, integer *n, integer *nrhs, doublereal *ap, doublereal *afp, integer *ipiv, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsptrf_ 14 6 13 4 7 4 4 124 */
/*:ref: dlansp_ 7 7 13 13 4 7 7 124 124 */
/*:ref: dspcon_ 14 10 13 4 7 4 7 7 7 4 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dsptrs_ 14 9 13 4 4 7 4 7 4 4 124 */
/*:ref: dsprfs_ 14 16 13 4 4 7 7 4 7 4 7 4 7 7 7 4 4 124 */
extern int dsptrd_(char *uplo, integer *n, doublereal *ap, doublereal *d__, doublereal *e, doublereal *tau, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dspmv_ 14 10 13 4 7 7 7 4 7 7 4 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dspr2_ 14 9 13 4 7 7 4 7 4 7 124 */
extern int dsptrf_(char *uplo, integer *n, doublereal *ap, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dspr_ 14 7 13 4 7 7 4 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dsptri_(char *uplo, integer *n, doublereal *ap, integer *ipiv, doublereal *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dspmv_ 14 10 13 4 7 7 7 4 7 7 4 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dsptrs_(char *uplo, integer *n, integer *nrhs, doublereal *ap, integer *ipiv, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
extern int dstebz_(char *range, char *order, integer *n, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, doublereal *d__, doublereal *e, integer *m, integer *nsplit, doublereal *w, integer *iblock, integer *isplit, doublereal *work, integer *iwork, integer *info, ftnlen range_len, ftnlen order_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dlaebz_ 14 20 4 4 4 4 4 4 7 7 7 7 7 7 4 7 7 4 4 7 4 4 */
extern int dstedc_(char *compz, integer *n, doublereal *d__, doublereal *e, doublereal *z__, integer *ldz, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaed0_ 14 12 4 4 4 7 7 7 4 7 4 7 4 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dlasrt_ 14 5 13 4 7 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dstegr_(char *jobz, char *range, integer *n, doublereal *d__, doublereal *e, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, integer *ldz, integer *isuppz, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen range_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlarre_ 14 12 4 7 7 7 4 4 4 7 7 7 7 4 */
/*:ref: dlarrv_ 14 15 4 7 7 4 4 7 4 7 7 7 4 4 7 4 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dstein_(integer *n, doublereal *d__, doublereal *e, integer *m, doublereal *w, integer *iblock, integer *isplit, doublereal *z__, integer *ldz, doublereal *work, integer *iwork, integer *ifail, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlarnv_ 14 4 4 4 4 7 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlagtf_ 14 9 4 7 7 7 7 7 7 4 4 */
/*:ref: dasum_ 7 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlagts_ 14 10 4 4 7 7 7 7 4 7 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
extern int dsteqr_(char *compz, integer *n, doublereal *d__, doublereal *e, doublereal *z__, integer *ldz, doublereal *work, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaev2_ 14 7 7 7 7 7 7 7 7 */
/*:ref: dlasr_ 14 12 13 13 13 4 4 7 7 7 4 124 124 124 */
/*:ref: dlae2_ 14 5 7 7 7 7 7 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: dlasrt_ 14 5 13 4 7 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dsterf_(integer *n, doublereal *d__, doublereal *e, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlae2_ 14 5 7 7 7 7 7 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dlasrt_ 14 5 13 4 7 4 124 */
extern int dstev_(char *jobz, integer *n, doublereal *d__, doublereal *e, doublereal *z__, integer *ldz, doublereal *work, integer *info, ftnlen jobz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
extern int dstevd_(char *jobz, integer *n, doublereal *d__, doublereal *e, doublereal *z__, integer *ldz, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dstedc_ 14 12 13 4 7 7 7 4 7 4 4 4 4 124 */
extern int dstevr_(char *jobz, char *range, integer *n, doublereal *d__, doublereal *e, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, integer *ldz, integer *isuppz, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen range_len);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dstegr_ 14 22 13 13 4 7 7 7 7 4 4 7 4 7 7 4 4 7 4 4 4 4 124 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: dstein_ 14 13 4 7 7 4 7 4 4 7 4 7 4 4 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dstevx_(char *jobz, char *range, integer *n, doublereal *d__, doublereal *e, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: dstein_ 14 13 4 7 7 4 7 4 4 7 4 7 4 4 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dsycon_(char *uplo, integer *n, doublereal *a, integer *lda, integer *ipiv, doublereal *anorm, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dsytrs_ 14 10 13 4 4 7 4 4 7 4 4 124 */
extern int dsyev_(char *jobz, char *uplo, integer *n, doublereal *a, integer *lda, doublereal *w, doublereal *work, integer *lwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlansy_ 7 8 13 13 4 7 4 7 124 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dsytrd_ 14 11 13 4 7 4 7 7 7 7 4 4 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dorgtr_ 14 9 13 4 7 4 7 7 4 4 124 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dsyevd_(char *jobz, char *uplo, integer *n, doublereal *a, integer *lda, doublereal *w, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlansy_ 7 8 13 13 4 7 4 7 124 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dsytrd_ 14 11 13 4 7 4 7 7 7 7 4 4 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dstedc_ 14 12 13 4 7 7 7 4 7 4 4 4 4 124 */
/*:ref: dormtr_ 14 16 13 13 13 4 4 7 4 7 7 4 7 4 4 124 124 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dsyevr_(char *jobz, char *range, char *uplo, integer *n, doublereal *a, integer *lda, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, integer *ldz, integer *isuppz, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlansy_ 7 8 13 13 4 7 4 7 124 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dsytrd_ 14 11 13 4 7 4 7 7 7 7 4 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dstegr_ 14 22 13 13 4 7 7 7 7 4 4 7 4 7 7 4 4 7 4 4 4 4 124 124 */
/*:ref: dormtr_ 14 16 13 13 13 4 4 7 4 7 7 4 7 4 4 124 124 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: dstein_ 14 13 4 7 7 4 7 4 4 7 4 7 4 4 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dsyevx_(char *jobz, char *range, char *uplo, integer *n, doublereal *a, integer *lda, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *lwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlansy_ 7 8 13 13 4 7 4 7 124 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dsytrd_ 14 11 13 4 7 4 7 7 7 7 4 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dorgtr_ 14 9 13 4 7 4 7 7 4 4 124 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: dstein_ 14 13 4 7 7 4 7 4 4 7 4 7 4 4 4 */
/*:ref: dormtr_ 14 16 13 13 13 4 4 7 4 7 7 4 7 4 4 124 124 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dsygs2_(integer *itype, char *uplo, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dsyr2_ 14 10 13 4 7 7 4 7 4 7 4 124 */
/*:ref: dtrsv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
/*:ref: dtrmv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
extern int dsygst_(integer *itype, char *uplo, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dsygs2_ 14 9 4 13 4 7 4 7 4 4 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dsymm_ 14 14 13 13 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dsyr2k_ 14 14 13 13 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dtrmm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
extern int dsygv_(integer *itype, char *jobz, char *uplo, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *w, doublereal *work, integer *lwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpotrf_ 14 6 13 4 7 4 4 124 */
/*:ref: dsygst_ 14 9 4 13 4 7 4 7 4 4 124 */
/*:ref: dsyev_ 14 11 13 13 4 7 4 7 7 4 4 124 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dtrmm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
extern int dsygvd_(integer *itype, char *jobz, char *uplo, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *w, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpotrf_ 14 6 13 4 7 4 4 124 */
/*:ref: dsygst_ 14 9 4 13 4 7 4 7 4 4 124 */
/*:ref: dsyevd_ 14 13 13 13 4 7 4 7 7 4 4 4 4 124 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dtrmm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
extern int dsygvx_(integer *itype, char *jobz, char *range, char *uplo, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, integer *lwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dpotrf_ 14 6 13 4 7 4 4 124 */
/*:ref: dsygst_ 14 9 4 13 4 7 4 7 4 4 124 */
/*:ref: dsyevx_ 14 23 13 13 13 4 7 4 7 7 4 4 7 4 7 7 4 7 4 4 4 4 124 124 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dtrmm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
extern int dsyrfs_(char *uplo, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, integer *ipiv, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsymv_ 14 11 13 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dsytrs_ 14 10 13 4 4 7 4 4 7 4 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
extern int dsysv_(char *uplo, integer *n, integer *nrhs, doublereal *a, integer *lda, integer *ipiv, doublereal *b, integer *ldb, doublereal *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dsytrf_ 14 9 13 4 7 4 4 7 4 4 124 */
/*:ref: dsytrs_ 14 10 13 4 4 7 4 4 7 4 4 124 */
extern int dsysvx_(char *fact, char *uplo, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, integer *ipiv, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *lwork, integer *iwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dsytrf_ 14 9 13 4 7 4 4 7 4 4 124 */
/*:ref: dlansy_ 7 8 13 13 4 7 4 7 124 124 */
/*:ref: dsycon_ 14 11 13 4 7 4 4 7 7 7 4 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dsytrs_ 14 10 13 4 4 7 4 4 7 4 4 124 */
/*:ref: dsyrfs_ 14 18 13 4 4 7 4 7 4 4 7 4 7 4 7 7 7 4 4 124 */
extern int dsytd2_(char *uplo, integer *n, doublereal *a, integer *lda, doublereal *d__, doublereal *e, doublereal *tau, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dsymv_ 14 11 13 4 7 7 4 7 4 7 7 4 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dsyr2_ 14 10 13 4 7 7 4 7 4 7 4 124 */
extern int dsytf2_(char *uplo, integer *n, doublereal *a, integer *lda, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dsyr_ 14 8 13 4 7 7 4 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dsytrd_(char *uplo, integer *n, doublereal *a, integer *lda, doublereal *d__, doublereal *e, doublereal *tau, doublereal *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlatrd_ 14 10 13 4 4 7 4 7 7 7 4 124 */
/*:ref: dsyr2k_ 14 14 13 13 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dsytd2_ 14 9 13 4 7 4 7 7 7 4 124 */
extern int dsytrf_(char *uplo, integer *n, doublereal *a, integer *lda, integer *ipiv, doublereal *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlasyf_ 14 11 13 4 4 4 7 4 4 7 4 4 124 */
/*:ref: dsytf2_ 14 7 13 4 7 4 4 4 124 */
extern int dsytri_(char *uplo, integer *n, doublereal *a, integer *lda, integer *ipiv, doublereal *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsymv_ 14 11 13 4 7 7 4 7 4 7 7 4 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
extern int dsytrs_(char *uplo, integer *n, integer *nrhs, doublereal *a, integer *lda, integer *ipiv, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dswap_ 14 5 4 7 4 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
extern int dtbcon_(char *norm, char *uplo, char *diag, integer *n, integer *kd, doublereal *ab, integer *ldab, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlantb_ 7 11 13 13 13 4 4 7 4 7 124 124 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dlatbs_ 14 16 13 13 13 13 4 4 7 4 7 7 7 4 124 124 124 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: drscl_ 14 4 4 7 7 4 */
extern int dtbrfs_(char *uplo, char *trans, char *diag, integer *n, integer *kd, integer *nrhs, doublereal *ab, integer *ldab, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dtbmv_ 14 12 13 13 13 4 4 7 4 7 4 124 124 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dtbsv_ 14 12 13 13 13 4 4 7 4 7 4 124 124 124 */
extern int dtbtrs_(char *uplo, char *trans, char *diag, integer *n, integer *kd, integer *nrhs, doublereal *ab, integer *ldab, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtbsv_ 14 12 13 13 13 4 4 7 4 7 4 124 124 124 */
extern int dtgevc_(char *side, char *howmny, logical *select, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, integer *mm, integer *m, doublereal *work, integer *info, ftnlen side_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlag2_ 14 10 7 4 7 4 7 7 7 7 7 7 */
/*:ref: dlaln2_ 14 18 12 4 4 7 7 7 4 7 7 7 4 7 7 7 4 7 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
extern int dtgex2_(logical *wantq, logical *wantz, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *q, integer *ldq, doublereal *z__, integer *ldz, integer *j1, integer *n1, integer *n2, doublereal *work, integer *lwork, integer *info);
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: dtgsy2_ 14 23 13 4 4 4 7 4 7 4 7 4 7 4 7 4 7 4 7 7 7 4 4 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dgeqr2_ 14 7 4 4 7 4 7 7 4 */
/*:ref: dorg2r_ 14 8 4 4 4 7 4 7 7 4 */
/*:ref: dgerq2_ 14 7 4 4 7 4 7 7 4 */
/*:ref: dorgr2_ 14 8 4 4 4 7 4 7 7 4 */
/*:ref: dormr2_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dorm2r_ 14 14 13 13 4 4 4 7 4 7 7 4 7 4 124 124 */
/*:ref: dlagv2_ 14 11 7 4 7 4 7 7 7 7 7 7 7 */
extern int dtgexc_(logical *wantq, logical *wantz, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *q, integer *ldq, doublereal *z__, integer *ldz, integer *ifst, integer *ilst, doublereal *work, integer *lwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtgex2_ 14 17 12 12 4 7 4 7 4 7 4 7 4 4 4 4 7 4 4 */
extern int dtgsen_(integer *ijob, logical *wantq, logical *wantz, logical *select, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *alphar, doublereal *alphai, doublereal *beta, doublereal *q, integer *ldq, doublereal *z__, integer *ldz, integer *m, doublereal *pl, doublereal *pr, doublereal *dif, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
/*:ref: dtgexc_ 14 16 12 12 4 7 4 7 4 7 4 7 4 4 4 7 4 4 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dtgsyl_ 14 23 13 4 4 4 7 4 7 4 7 4 7 4 7 4 7 4 7 7 7 4 4 4 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dlag2_ 14 10 7 4 7 4 7 7 7 7 7 7 */
extern int dtgsja_(char *jobu, char *jobv, char *jobq, integer *m, integer *p, integer *n, integer *k, integer *l, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *tola, doublereal *tolb, doublereal *alpha, doublereal *beta, doublereal *u, integer *ldu, doublereal *v, integer *ldv, doublereal *q, integer *ldq, doublereal *work, integer *ncycle, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlags2_ 14 13 12 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: drot_ 14 7 4 7 4 7 4 7 7 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlapll_ 14 6 4 7 4 7 4 7 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
extern int dtgsna_(char *job, char *howmny, logical *select, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, doublereal *s, doublereal *dif, integer *mm, integer *m, doublereal *work, integer *lwork, integer *iwork, integer *info, ftnlen job_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dlag2_ 14 10 7 4 7 4 7 7 7 7 7 7 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dtgexc_ 14 16 12 12 4 7 4 7 4 7 4 7 4 4 4 7 4 4 */
/*:ref: dtgsyl_ 14 23 13 4 4 4 7 4 7 4 7 4 7 4 7 4 7 4 7 7 7 4 4 4 124 */
extern int dtgsy2_(char *trans, integer *ijob, integer *m, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *c__, integer *ldc, doublereal *d__, integer *ldd, doublereal *e, integer *lde, doublereal *f, integer *ldf, doublereal *scale, doublereal *rdsum, doublereal *rdscal, integer *iwork, integer *pq, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dgetc2_ 14 6 4 7 4 4 4 4 */
/*:ref: dgesc2_ 14 7 4 7 4 7 4 4 7 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlatdf_ 14 9 4 4 7 4 7 7 7 4 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
extern int dtgsyl_(char *trans, integer *ijob, integer *m, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *c__, integer *ldc, doublereal *d__, integer *ldd, doublereal *e, integer *lde, doublereal *f, integer *ldf, doublereal *scale, doublereal *dif, doublereal *work, integer *lwork, integer *iwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dtgsy2_ 14 23 13 4 4 4 7 4 7 4 7 4 7 4 7 4 7 4 7 7 7 4 4 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
extern int dtpcon_(char *norm, char *uplo, char *diag, integer *n, doublereal *ap, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlantp_ 7 9 13 13 13 4 7 7 124 124 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dlatps_ 14 14 13 13 13 13 4 7 7 7 7 4 124 124 124 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: drscl_ 14 4 4 7 7 4 */
extern int dtprfs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, doublereal *ap, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dtpmv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dtpsv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
extern int dtptri_(char *uplo, char *diag, integer *n, doublereal *ap, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtpmv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dtptrs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, doublereal *ap, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtpsv_ 14 10 13 13 13 4 7 7 4 124 124 124 */
extern int dtrcon_(char *norm, char *uplo, char *diag, integer *n, doublereal *a, integer *lda, doublereal *rcond, doublereal *work, integer *iwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlantr_ 7 11 13 13 13 4 4 7 4 7 124 124 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dlatrs_ 14 15 13 13 13 13 4 7 4 7 7 7 4 124 124 124 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: drscl_ 14 4 4 7 7 4 */
extern int dtrevc_(char *side, char *howmny, logical *select, integer *n, doublereal *t, integer *ldt, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, integer *mm, integer *m, doublereal *work, integer *info, ftnlen side_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlaln2_ 14 18 12 4 4 7 7 7 4 7 7 7 4 7 7 7 4 7 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
extern int dtrexc_(char *compq, integer *n, doublereal *t, integer *ldt, doublereal *q, integer *ldq, integer *ifst, integer *ilst, doublereal *work, integer *info, ftnlen compq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaexc_ 14 11 12 4 7 4 7 4 4 4 4 7 4 */
extern int dtrrfs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dtrmv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dtrsv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
extern int dtrsen_(char *job, char *compq, logical *select, integer *n, doublereal *t, integer *ldt, doublereal *q, integer *ldq, doublereal *wr, doublereal *wi, integer *m, doublereal *s, doublereal *sep, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen job_len, ftnlen compq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: dtrexc_ 14 11 13 4 7 4 7 4 4 4 7 4 124 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dtrsyl_ 14 15 13 13 4 4 4 7 4 7 4 7 4 7 4 124 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
extern int dtrsna_(char *job, char *howmny, logical *select, integer *n, doublereal *t, integer *ldt, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, doublereal *s, doublereal *sep, integer *mm, integer *m, doublereal *work, integer *ldwork, integer *iwork, integer *info, ftnlen job_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dlacpy_ 14 8 13 4 4 7 4 7 4 124 */
/*:ref: dtrexc_ 14 11 13 4 7 4 7 4 4 4 7 4 124 */
/*:ref: dlacon_ 14 6 4 7 7 4 7 4 */
/*:ref: dlaqtr_ 14 11 12 12 4 7 4 7 7 7 7 7 4 */
extern int dtrsyl_(char *trana, char *tranb, integer *isgn, integer *m, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *c__, integer *ldc, doublereal *scale, integer *info, ftnlen trana_len, ftnlen tranb_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dlange_ 7 7 13 4 4 7 4 7 124 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlaln2_ 14 18 12 4 4 7 7 7 4 7 7 7 4 7 7 7 4 7 7 4 */
/*:ref: dlasy2_ 14 16 12 12 4 4 4 7 4 7 4 7 4 7 7 4 7 4 */
extern int dtrti2_(char *uplo, char *diag, integer *n, doublereal *a, integer *lda, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtrmv_ 14 11 13 13 13 4 7 4 7 4 124 124 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int dtrtri_(char *uplo, char *diag, integer *n, doublereal *a, integer *lda, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dtrti2_ 14 8 13 13 4 7 4 4 124 124 */
/*:ref: dtrmm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
extern int dtrtrs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dtrsm_ 14 15 13 13 13 13 4 4 7 7 4 7 4 124 124 124 124 */
extern int dtzrqf_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlarfg_ 14 5 4 7 7 4 7 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dger_ 14 9 4 4 7 7 4 7 4 7 4 */
extern int dtzrzf_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlatrz_ 14 7 4 4 4 7 4 7 7 */
/*:ref: dlarzt_ 14 11 13 13 4 4 7 4 7 7 4 124 124 */
/*:ref: dlarzb_ 14 20 13 13 13 13 4 4 4 4 7 4 7 4 7 4 7 4 124 124 124 124 */
extern doublereal dzsum1_(integer *n, doublecomplex *cx, integer *incx);
extern integer icmax1_(integer *n, complex *cx, integer *incx);
extern integer ieeeck_(integer *ispec, real *zero, real *one);
extern integer ilaenv_(integer *ispec, char *name__, char *opts, integer *n1, integer *n2, integer *n3, integer *n4, ftnlen name_len, ftnlen opts_len);
/*:ref: ieeeck_ 4 3 4 6 6 */
extern integer izmax1_(integer *n, doublecomplex *cx, integer *incx);
extern logical lsame_(char *ca, char *cb, ftnlen ca_len, ftnlen cb_len);
extern logical lsamen_(integer *n, char *ca, char *cb, ftnlen ca_len, ftnlen cb_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int sbdsdc_(char *uplo, char *compq, integer *n, real *d__, real *e, real *u, integer *ldu, real *vt, integer *ldvt, real *q, integer *iq, real *work, integer *iwork, integer *info, ftnlen uplo_len, ftnlen compq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: slasdq_ 14 17 13 4 4 4 4 4 6 6 6 4 6 4 6 4 6 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slasd0_ 14 12 4 4 6 6 6 4 6 4 4 4 6 4 */
/*:ref: slasda_ 14 24 4 4 4 4 6 6 6 4 6 4 6 6 6 6 4 4 4 4 6 6 6 6 4 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: slasr_ 14 12 13 13 13 4 4 6 6 6 4 124 124 124 */
extern int sbdsqr_(char *uplo, integer *n, integer *ncvt, integer *nru, integer *ncc, real *d__, real *e, real *vt, integer *ldvt, real *u, integer *ldu, real *c__, integer *ldc, real *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slasq1_ 14 5 4 6 6 6 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: slasr_ 14 12 13 13 13 4 4 6 6 6 4 124 124 124 */
/*:ref: slasv2_ 14 9 6 6 6 6 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: slas2_ 14 5 6 6 6 6 6 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern E_f scsum1_(integer *n, complex *cx, integer *incx);
extern int sdisna_(char *job, integer *m, integer *n, real *d__, real *sep, integer *info, ftnlen job_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
extern E_f second_(void);
/*:ref: etime_ 6 1 6 */
extern int sgbbrd_(char *vect, integer *m, integer *n, integer *ncc, integer *kl, integer *ku, real *ab, integer *ldab, real *d__, real *e, real *q, integer *ldq, real *pt, integer *ldpt, real *c__, integer *ldc, real *work, integer *info, ftnlen vect_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slargv_ 14 7 4 6 4 6 4 6 4 */
/*:ref: slartv_ 14 8 4 6 4 6 4 6 6 4 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
extern int sgbcon_(char *norm, integer *n, integer *kl, integer *ku, real *ab, integer *ldab, integer *ipiv, real *anorm, real *rcond, real *work, integer *iwork, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slatbs_ 14 16 13 13 13 13 4 4 6 4 6 6 6 4 124 124 124 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: srscl_ 14 4 4 6 6 4 */
extern int sgbequ_(integer *m, integer *n, integer *kl, integer *ku, real *ab, integer *ldab, real *r__, real *c__, real *rowcnd, real *colcnd, real *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
extern int sgbrfs_(char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, real *ab, integer *ldab, real *afb, integer *ldafb, integer *ipiv, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgbmv_ 14 14 13 4 4 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sgbtrs_ 14 12 13 4 4 4 4 6 4 4 6 4 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
extern int sgbsv_(integer *n, integer *kl, integer *ku, integer *nrhs, real *ab, integer *ldab, integer *ipiv, real *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgbtrf_ 14 8 4 4 4 4 6 4 4 4 */
/*:ref: sgbtrs_ 14 12 13 4 4 4 4 6 4 4 6 4 4 124 */
extern int sgbsvx_(char *fact, char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, real *ab, integer *ldab, real *afb, integer *ldafb, integer *ipiv, char *equed, real *r__, real *c__, real *b, integer *ldb, real *x, integer *ldx, real *rcond, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen trans_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgbequ_ 14 12 4 4 4 4 6 4 6 6 6 6 6 4 */
/*:ref: slaqgb_ 14 13 4 4 4 4 6 4 6 6 6 6 6 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgbtrf_ 14 8 4 4 4 4 6 4 4 4 */
/*:ref: slantb_ 6 11 13 13 13 4 4 6 4 6 124 124 124 */
/*:ref: slangb_ 6 8 13 4 4 4 6 4 6 124 */
/*:ref: sgbcon_ 14 13 13 4 4 4 6 4 4 6 6 6 4 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sgbtrs_ 14 12 13 4 4 4 4 6 4 4 6 4 4 124 */
/*:ref: sgbrfs_ 14 20 13 4 4 4 4 6 4 6 4 4 6 4 6 4 6 6 6 4 4 124 */
extern int sgbtf2_(integer *m, integer *n, integer *kl, integer *ku, real *ab, integer *ldab, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
extern int sgbtrf_(integer *m, integer *n, integer *kl, integer *ku, real *ab, integer *ldab, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: sgbtf2_ 14 8 4 4 4 4 6 4 4 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slaswp_ 14 7 4 6 4 4 4 4 4 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
extern int sgbtrs_(char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, real *ab, integer *ldab, integer *ipiv, real *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
/*:ref: stbsv_ 14 12 13 13 13 4 4 6 4 6 4 124 124 124 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
extern int sgebak_(char *job, char *side, integer *n, integer *ilo, integer *ihi, real *scale, integer *m, real *v, integer *ldv, integer *info, ftnlen job_len, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int sgebal_(char *job, integer *n, real *a, integer *lda, integer *ilo, integer *ihi, real *scale, integer *info, ftnlen job_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int sgebd2_(integer *m, integer *n, real *a, integer *lda, real *d__, real *e, real *tauq, real *taup, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sgebrd_(integer *m, integer *n, real *a, integer *lda, real *d__, real *e, real *tauq, real *taup, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slabrd_ 14 13 4 4 4 6 4 6 6 6 6 6 4 6 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: sgebd2_ 14 10 4 4 6 4 6 6 6 6 6 4 */
extern int sgecon_(char *norm, integer *n, real *a, integer *lda, real *anorm, real *rcond, real *work, integer *iwork, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: slatrs_ 14 15 13 13 13 13 4 6 4 6 6 6 4 124 124 124 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: srscl_ 14 4 4 6 6 4 */
extern int sgeequ_(integer *m, integer *n, real *a, integer *lda, real *r__, real *c__, real *rowcnd, real *colcnd, real *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
extern int sgees_(char *jobvs, char *sort, L_fp select, integer *n, real *a, integer *lda, integer *sdim, real *wr, real *wi, real *vs, integer *ldvs, real *work, integer *lwork, logical *bwork, integer *info, ftnlen jobvs_len, ftnlen sort_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sgebal_ 14 9 13 4 6 4 4 4 6 4 124 */
/*:ref: sgehrd_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorghr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: shseqr_ 14 16 13 13 4 4 4 6 4 6 6 6 4 6 4 4 124 124 */
/*:ref: strsen_ 14 20 13 13 12 4 6 4 6 4 6 6 4 6 6 6 4 4 4 4 124 124 */
/*:ref: sgebak_ 14 12 13 13 4 4 4 6 4 6 4 4 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int sgeesx_(char *jobvs, char *sort, L_fp select, char *sense, integer *n, real *a, integer *lda, integer *sdim, real *wr, real *wi, real *vs, integer *ldvs, real *rconde, real *rcondv, real *work, integer *lwork, integer *iwork, integer *liwork, logical *bwork, integer *info, ftnlen jobvs_len, ftnlen sort_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sgebal_ 14 9 13 4 6 4 4 4 6 4 124 */
/*:ref: sgehrd_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorghr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: shseqr_ 14 16 13 13 4 4 4 6 4 6 6 6 4 6 4 4 124 124 */
/*:ref: strsen_ 14 20 13 13 12 4 6 4 6 4 6 6 4 6 6 6 4 4 4 4 124 124 */
/*:ref: sgebak_ 14 12 13 13 4 4 4 6 4 6 4 4 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int sgeev_(char *jobvl, char *jobvr, integer *n, real *a, integer *lda, real *wr, real *wi, real *vl, integer *ldvl, real *vr, integer *ldvr, real *work, integer *lwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sgebal_ 14 9 13 4 6 4 4 4 6 4 124 */
/*:ref: sgehrd_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorghr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: shseqr_ 14 16 13 13 4 4 4 6 4 6 6 6 4 6 4 4 124 124 */
/*:ref: strevc_ 14 16 13 13 12 4 6 4 6 4 6 4 4 4 6 4 124 124 */
/*:ref: sgebak_ 14 12 13 13 4 4 4 6 4 6 4 4 124 124 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
extern int sgeevx_(char *balanc, char *jobvl, char *jobvr, char *sense, integer *n, real *a, integer *lda, real *wr, real *wi, real *vl, integer *ldvl, real *vr, integer *ldvr, integer *ilo, integer *ihi, real *scale, real *abnrm, real *rconde, real *rcondv, real *work, integer *lwork, integer *iwork, integer *info, ftnlen balanc_len, ftnlen jobvl_len, ftnlen jobvr_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sgebal_ 14 9 13 4 6 4 4 4 6 4 124 */
/*:ref: sgehrd_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorghr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: shseqr_ 14 16 13 13 4 4 4 6 4 6 6 6 4 6 4 4 124 124 */
/*:ref: strevc_ 14 16 13 13 12 4 6 4 6 4 6 4 4 4 6 4 124 124 */
/*:ref: strsna_ 14 20 13 13 12 4 6 4 6 4 6 4 6 6 4 4 6 4 4 4 124 124 */
/*:ref: sgebak_ 14 12 13 13 4 4 4 6 4 6 4 4 124 124 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
extern int sgegs_(char *jobvsl, char *jobvsr, integer *n, real *a, integer *lda, real *b, integer *ldb, real *alphar, real *alphai, real *beta, real *vsl, integer *ldvsl, real *vsr, integer *ldvsr, real *work, integer *lwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sggbal_ 14 13 13 4 6 4 6 4 4 4 6 6 6 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: sgghrd_ 14 16 13 13 4 4 4 6 4 6 4 6 4 6 4 4 124 124 */
/*:ref: shgeqz_ 14 23 13 13 13 4 4 4 6 4 6 4 6 6 6 6 4 6 4 6 4 4 124 124 124 */
/*:ref: sggbak_ 14 13 13 13 4 4 4 6 6 4 6 4 4 124 124 */
extern int sgegv_(char *jobvl, char *jobvr, integer *n, real *a, integer *lda, real *b, integer *ldb, real *alphar, real *alphai, real *beta, real *vl, integer *ldvl, real *vr, integer *ldvr, real *work, integer *lwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sggbal_ 14 13 13 4 6 4 6 4 4 4 6 6 6 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: sgghrd_ 14 16 13 13 4 4 4 6 4 6 4 6 4 6 4 4 124 124 */
/*:ref: shgeqz_ 14 23 13 13 13 4 4 4 6 4 6 4 6 6 6 6 4 6 4 6 4 4 124 124 124 */
/*:ref: stgevc_ 14 18 13 13 12 4 6 4 6 4 6 4 6 4 4 4 6 4 124 124 */
/*:ref: sggbak_ 14 13 13 13 4 4 4 6 6 4 6 4 4 124 124 */
extern int sgehd2_(integer *n, integer *ilo, integer *ihi, real *a, integer *lda, real *tau, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sgehrd_(integer *n, integer *ilo, integer *ihi, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slahrd_ 14 10 4 4 4 6 4 6 6 4 6 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
/*:ref: sgehd2_ 14 8 4 4 4 6 4 6 6 4 */
extern int sgelq2_(integer *m, integer *n, real *a, integer *lda, real *tau, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sgelqf_(integer *m, integer *n, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgelq2_ 14 7 4 4 6 4 6 6 4 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sgels_(char *trans, integer *m, integer *n, integer *nrhs, real *a, integer *lda, real *b, integer *ldb, real *work, integer *lwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: sgelqf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormlq_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
extern int sgelsd_(integer *m, integer *n, integer *nrhs, real *a, integer *lda, real *b, integer *ldb, real *s, real *rcond, integer *rank, real *work, integer *lwork, integer *iwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: sgebrd_ 14 11 4 4 6 4 6 6 6 6 6 4 4 */
/*:ref: sormbr_ 14 17 13 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 124 */
/*:ref: slalsd_ 14 14 13 4 4 4 6 6 6 4 6 4 6 4 4 124 */
/*:ref: sgelqf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sormlq_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
extern int sgelss_(integer *m, integer *n, integer *nrhs, real *a, integer *lda, real *b, integer *ldb, real *s, real *rcond, integer *rank, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: sgebrd_ 14 11 4 4 6 4 6 6 6 6 6 4 4 */
/*:ref: sormbr_ 14 17 13 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 124 */
/*:ref: sorgbr_ 14 11 13 4 4 4 6 4 6 6 4 4 124 */
/*:ref: sbdsqr_ 14 16 13 4 4 4 4 6 6 6 4 6 4 6 4 6 4 124 */
/*:ref: srscl_ 14 4 4 6 6 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgelqf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormlq_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
extern int sgelsx_(integer *m, integer *n, integer *nrhs, real *a, integer *lda, real *b, integer *ldb, integer *jpvt, real *rcond, integer *rank, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: sgeqpf_ 14 8 4 4 6 4 4 6 6 4 */
/*:ref: slaic1_ 14 9 4 4 6 6 6 6 6 6 6 */
/*:ref: stzrqf_ 14 6 4 4 6 4 6 4 */
/*:ref: sorm2r_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: slatzm_ 14 11 13 4 4 6 4 6 6 6 4 6 124 */
extern int sgelsy_(integer *m, integer *n, integer *nrhs, real *a, integer *lda, real *b, integer *ldb, integer *jpvt, real *rcond, integer *rank, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: sgeqp3_ 14 9 4 4 6 4 4 6 6 4 4 */
/*:ref: slaic1_ 14 9 4 4 6 6 6 6 6 6 6 */
/*:ref: stzrzf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: sormrz_ 14 16 13 13 4 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
extern int sgeql2_(integer *m, integer *n, real *a, integer *lda, real *tau, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sgeqlf_(integer *m, integer *n, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgeql2_ 14 7 4 4 6 4 6 6 4 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sgeqp3_(integer *m, integer *n, real *a, integer *lda, integer *jpvt, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: slaqps_ 14 14 4 4 4 4 4 6 4 4 6 6 6 6 6 4 */
/*:ref: slaqp2_ 14 10 4 4 4 6 4 4 6 6 6 6 */
extern int sgeqpf_(integer *m, integer *n, real *a, integer *lda, integer *jpvt, real *tau, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sgeqr2_ 14 7 4 4 6 4 6 6 4 */
/*:ref: sorm2r_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sgeqr2_(integer *m, integer *n, real *a, integer *lda, real *tau, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sgeqrf_(integer *m, integer *n, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgeqr2_ 14 7 4 4 6 4 6 6 4 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sgerfs_(char *trans, integer *n, integer *nrhs, real *a, integer *lda, real *af, integer *ldaf, integer *ipiv, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sgetrs_ 14 10 13 4 4 6 4 4 6 4 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
extern int sgerq2_(integer *m, integer *n, real *a, integer *lda, real *tau, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sgerqf_(integer *m, integer *n, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgerq2_ 14 7 4 4 6 4 6 6 4 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sgesc2_(integer *n, real *a, integer *lda, real *rhs, integer *ipiv, integer *jpiv, real *scale);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slaswp_ 14 7 4 6 4 4 4 4 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int sgesdd_(char *jobz, integer *m, integer *n, real *a, integer *lda, real *s, real *u, integer *ldu, real *vt, integer *ldvt, real *work, integer *lwork, integer *iwork, integer *info, ftnlen jobz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: sgebrd_ 14 11 4 4 6 4 6 6 6 6 6 4 4 */
/*:ref: sbdsdc_ 14 16 13 13 4 6 6 6 4 6 4 6 4 6 4 4 124 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: sormbr_ 14 17 13 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: sorgbr_ 14 11 13 4 4 4 6 4 6 6 4 4 124 */
/*:ref: sgelqf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sorglq_ 14 9 4 4 4 6 4 6 6 4 4 */
extern int sgesv_(integer *n, integer *nrhs, real *a, integer *lda, integer *ipiv, real *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgetrf_ 14 6 4 4 6 4 4 4 */
/*:ref: sgetrs_ 14 10 13 4 4 6 4 4 6 4 4 124 */
extern int sgesvd_(char *jobu, char *jobvt, integer *m, integer *n, real *a, integer *lda, real *s, real *u, integer *ldu, real *vt, integer *ldvt, real *work, integer *lwork, integer *info, ftnlen jobu_len, ftnlen jobvt_len);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: sgebrd_ 14 11 4 4 6 4 6 6 6 6 6 4 4 */
/*:ref: sorgbr_ 14 11 13 4 4 4 6 4 6 6 4 4 124 */
/*:ref: sbdsqr_ 14 16 13 4 4 4 4 6 6 6 4 6 4 6 4 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: sormbr_ 14 17 13 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 124 */
/*:ref: sgelqf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sorglq_ 14 9 4 4 4 6 4 6 6 4 4 */
extern int sgesvx_(char *fact, char *trans, integer *n, integer *nrhs, real *a, integer *lda, real *af, integer *ldaf, integer *ipiv, char *equed, real *r__, real *c__, real *b, integer *ldb, real *x, integer *ldx, real *rcond, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen trans_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgeequ_ 14 10 4 4 6 4 6 6 6 6 6 4 */
/*:ref: slaqge_ 14 11 4 4 6 4 6 6 6 6 6 13 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sgetrf_ 14 6 4 4 6 4 4 4 */
/*:ref: slantr_ 6 11 13 13 13 4 4 6 4 6 124 124 124 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: sgecon_ 14 10 13 4 6 4 6 6 6 4 4 124 */
/*:ref: sgetrs_ 14 10 13 4 4 6 4 4 6 4 4 124 */
/*:ref: sgerfs_ 14 18 13 4 4 6 4 6 4 4 6 4 6 4 6 6 6 4 4 124 */
extern int sgetc2_(integer *n, real *a, integer *lda, integer *ipiv, integer *jpiv, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
extern int sgetf2_(integer *m, integer *n, real *a, integer *lda, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
extern int sgetrf_(integer *m, integer *n, real *a, integer *lda, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: sgetf2_ 14 6 4 4 6 4 4 4 */
/*:ref: slaswp_ 14 7 4 6 4 4 4 4 4 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
extern int sgetri_(integer *n, real *a, integer *lda, integer *ipiv, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: strtri_ 14 8 13 13 4 6 4 4 124 124 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int sgetrs_(char *trans, integer *n, integer *nrhs, real *a, integer *lda, integer *ipiv, real *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaswp_ 14 7 4 6 4 4 4 4 4 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
extern int sggbak_(char *job, char *side, integer *n, integer *ilo, integer *ihi, real *lscale, real *rscale, integer *m, real *v, integer *ldv, integer *info, ftnlen job_len, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int sggbal_(char *job, integer *n, real *a, integer *lda, real *b, integer *ldb, integer *ilo, integer *ihi, real *lscale, real *rscale, real *work, integer *info, ftnlen job_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: isamax_ 4 3 4 6 4 */
extern int sgges_(char *jobvsl, char *jobvsr, char *sort, L_fp selctg, integer *n, real *a, integer *lda, real *b, integer *ldb, integer *sdim, real *alphar, real *alphai, real *beta, real *vsl, integer *ldvsl, real *vsr, integer *ldvsr, real *work, integer *lwork, logical *bwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len, ftnlen sort_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sggbal_ 14 13 13 4 6 4 6 4 4 4 6 6 6 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: sgghrd_ 14 16 13 13 4 4 4 6 4 6 4 6 4 6 4 4 124 124 */
/*:ref: shgeqz_ 14 23 13 13 13 4 4 4 6 4 6 4 6 6 6 6 4 6 4 6 4 4 124 124 124 */
/*:ref: stgsen_ 14 25 4 12 12 12 4 6 4 6 4 6 6 6 6 4 6 4 4 6 6 6 6 4 4 4 4 */
/*:ref: sggbak_ 14 13 13 13 4 4 4 6 6 4 6 4 4 124 124 */
extern int sggesx_(char *jobvsl, char *jobvsr, char *sort, L_fp selctg, char *sense, integer *n, real *a, integer *lda, real *b, integer *ldb, integer *sdim, real *alphar, real *alphai, real *beta, real *vsl, integer *ldvsl, real *vsr, integer *ldvsr, real *rconde, real *rcondv, real *work, integer *lwork, integer *iwork, integer *liwork, logical *bwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len, ftnlen sort_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sggbal_ 14 13 13 4 6 4 6 4 4 4 6 6 6 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: sgghrd_ 14 16 13 13 4 4 4 6 4 6 4 6 4 6 4 4 124 124 */
/*:ref: shgeqz_ 14 23 13 13 13 4 4 4 6 4 6 4 6 6 6 6 4 6 4 6 4 4 124 124 124 */
/*:ref: stgsen_ 14 25 4 12 12 12 4 6 4 6 4 6 6 6 6 4 6 4 4 6 6 6 6 4 4 4 4 */
/*:ref: sggbak_ 14 13 13 13 4 4 4 6 6 4 6 4 4 124 124 */
extern int sggev_(char *jobvl, char *jobvr, integer *n, real *a, integer *lda, real *b, integer *ldb, real *alphar, real *alphai, real *beta, real *vl, integer *ldvl, real *vr, integer *ldvr, real *work, integer *lwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sggbal_ 14 13 13 4 6 4 6 4 4 4 6 6 6 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: sgghrd_ 14 16 13 13 4 4 4 6 4 6 4 6 4 6 4 4 124 124 */
/*:ref: shgeqz_ 14 23 13 13 13 4 4 4 6 4 6 4 6 6 6 6 4 6 4 6 4 4 124 124 124 */
/*:ref: stgevc_ 14 18 13 13 12 4 6 4 6 4 6 4 6 4 4 4 6 4 124 124 */
/*:ref: sggbak_ 14 13 13 13 4 4 4 6 6 4 6 4 4 124 124 */
extern int sggevx_(char *balanc, char *jobvl, char *jobvr, char *sense, integer *n, real *a, integer *lda, real *b, integer *ldb, real *alphar, real *alphai, real *beta, real *vl, integer *ldvl, real *vr, integer *ldvr, integer *ilo, integer *ihi, real *lscale, real *rscale, real *abnrm, real *bbnrm, real *rconde, real *rcondv, real *work, integer *lwork, integer *iwork, logical *bwork, integer *info, ftnlen balanc_len, ftnlen jobvl_len, ftnlen jobvr_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: sggbal_ 14 13 13 4 6 4 6 4 4 4 6 6 6 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: sgghrd_ 14 16 13 13 4 4 4 6 4 6 4 6 4 6 4 4 124 124 */
/*:ref: shgeqz_ 14 23 13 13 13 4 4 4 6 4 6 4 6 6 6 6 4 6 4 6 4 4 124 124 124 */
/*:ref: stgevc_ 14 18 13 13 12 4 6 4 6 4 6 4 6 4 4 4 6 4 124 124 */
/*:ref: stgsna_ 14 22 13 13 12 4 6 4 6 4 6 4 6 4 6 6 4 4 6 4 4 4 124 124 */
/*:ref: sggbak_ 14 13 13 13 4 4 4 6 6 4 6 4 4 124 124 */
extern int sggglm_(integer *n, integer *m, integer *p, real *a, integer *lda, real *b, integer *ldb, real *d__, real *x, real *y, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sggqrf_ 14 12 4 4 4 6 4 6 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: strsv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sormrq_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
extern int sgghrd_(char *compq, char *compz, integer *n, integer *ilo, integer *ihi, real *a, integer *lda, real *b, integer *ldb, real *q, integer *ldq, real *z__, integer *ldz, integer *info, ftnlen compq_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
extern int sgglse_(integer *m, integer *n, integer *p, real *a, integer *lda, real *b, integer *ldb, real *c__, real *d__, real *x, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sggrqf_ 14 12 4 4 4 6 4 6 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: strsv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: strmv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: sormrq_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
extern int sggqrf_(integer *n, integer *m, integer *p, real *a, integer *lda, real *taua, real *b, integer *ldb, real *taub, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: sgerqf_ 14 8 4 4 6 4 6 6 4 4 */
extern int sggrqf_(integer *m, integer *p, integer *n, real *a, integer *lda, real *taua, real *b, integer *ldb, real *taub, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgerqf_ 14 8 4 4 6 4 6 6 4 4 */
/*:ref: sormrq_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: sgeqrf_ 14 8 4 4 6 4 6 6 4 4 */
extern int sggsvd_(char *jobu, char *jobv, char *jobq, integer *m, integer *n, integer *p, integer *k, integer *l, real *a, integer *lda, real *b, integer *ldb, real *alpha, real *beta, real *u, integer *ldu, real *v, integer *ldv, real *q, integer *ldq, real *work, integer *iwork, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: sggsvp_ 14 27 13 13 13 4 4 4 6 4 6 4 6 6 4 4 6 4 6 4 6 4 4 6 6 4 124 124 124 */
/*:ref: stgsja_ 14 28 13 13 13 4 4 4 4 4 6 4 6 4 6 6 6 6 6 4 6 4 6 4 6 4 4 124 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
extern int sggsvp_(char *jobu, char *jobv, char *jobq, integer *m, integer *p, integer *n, real *a, integer *lda, real *b, integer *ldb, real *tola, real *tolb, integer *k, integer *l, real *u, integer *ldu, real *v, integer *ldv, real *q, integer *ldq, integer *iwork, real *tau, real *work, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgeqpf_ 14 8 4 4 6 4 4 6 6 4 */
/*:ref: slapmt_ 14 6 12 4 4 6 4 4 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorg2r_ 14 8 4 4 4 6 4 6 6 4 */
/*:ref: sgerq2_ 14 7 4 4 6 4 6 6 4 */
/*:ref: sormr2_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: sorm2r_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: sgeqr2_ 14 7 4 4 6 4 6 6 4 */
extern int sgtcon_(char *norm, integer *n, real *dl, real *d__, real *du, real *du2, integer *ipiv, real *anorm, real *rcond, real *work, integer *iwork, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: sgttrs_ 14 12 13 4 4 6 6 6 6 4 6 4 4 124 */
extern int sgtrfs_(char *trans, integer *n, integer *nrhs, real *dl, real *d__, real *du, real *dlf, real *df, real *duf, real *du2, integer *ipiv, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slagtm_ 14 13 13 4 4 6 6 6 6 6 4 6 6 4 124 */
/*:ref: sgttrs_ 14 12 13 4 4 6 6 6 6 4 6 4 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
extern int sgtsv_(integer *n, integer *nrhs, real *dl, real *d__, real *du, real *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int sgtsvx_(char *fact, char *trans, integer *n, integer *nrhs, real *dl, real *d__, real *du, real *dlf, real *df, real *duf, real *du2, integer *ipiv, real *b, integer *ldb, real *x, integer *ldx, real *rcond, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgttrf_ 14 7 4 6 6 6 6 4 4 */
/*:ref: slangt_ 6 6 13 4 6 6 6 124 */
/*:ref: sgtcon_ 14 13 13 4 6 6 6 6 4 6 6 6 4 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sgttrs_ 14 12 13 4 4 6 6 6 6 4 6 4 4 124 */
/*:ref: sgtrfs_ 14 21 13 4 4 6 6 6 6 6 6 6 4 6 4 6 4 6 6 6 4 4 124 */
extern int sgttrf_(integer *n, real *dl, real *d__, real *du, real *du2, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int sgttrs_(char *trans, integer *n, integer *nrhs, real *dl, real *d__, real *du, real *du2, integer *ipiv, real *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: sgtts2_ 14 10 4 4 4 6 6 6 6 4 6 4 */
extern int sgtts2_(integer *itrans, integer *n, integer *nrhs, real *dl, real *d__, real *du, real *du2, integer *ipiv, real *b, integer *ldb);
extern int shgeqz_(char *job, char *compq, char *compz, integer *n, integer *ilo, integer *ihi, real *a, integer *lda, real *b, integer *ldb, real *alphar, real *alphai, real *beta, real *q, integer *ldq, real *z__, integer *ldz, real *work, integer *lwork, integer *info, ftnlen job_len, ftnlen compq_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slanhs_ 6 6 13 4 6 4 6 124 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: slag2_ 14 10 6 4 6 4 6 6 6 6 6 6 */
/*:ref: slasv2_ 14 9 6 6 6 6 6 6 6 6 6 */
/*:ref: slapy3_ 6 3 6 6 6 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
extern int shsein_(char *side, char *eigsrc, char *initv, logical *select, integer *n, real *h__, integer *ldh, real *wr, real *wi, real *vl, integer *ldvl, real *vr, integer *ldvr, integer *mm, integer *m, real *work, integer *ifaill, integer *ifailr, integer *info, ftnlen side_len, ftnlen eigsrc_len, ftnlen initv_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slanhs_ 6 6 13 4 6 4 6 124 */
/*:ref: slaein_ 14 16 12 12 4 6 4 6 6 6 6 6 4 6 6 6 6 4 */
extern int shseqr_(char *job, char *compz, integer *n, integer *ilo, integer *ihi, real *h__, integer *ldh, real *wr, real *wi, real *z__, integer *ldz, real *work, integer *lwork, integer *info, ftnlen job_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: slahqr_ 14 14 12 12 4 4 4 6 4 6 6 4 4 6 4 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slanhs_ 6 6 13 4 6 4 6 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarfx_ 14 9 13 4 4 6 6 6 4 6 124 */
extern int slabad_(real *small, real *large);
extern int slabrd_(integer *m, integer *n, integer *nb, real *a, integer *lda, real *d__, real *e, real *tauq, real *taup, real *x, integer *ldx, real *y, integer *ldy);
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int slacon_(integer *n, real *v, real *x, integer *isgn, real *est, integer *kase);
/*:ref: sasum_ 6 3 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
extern int slacpy_(char *uplo, integer *m, integer *n, real *a, integer *lda, real *b, integer *ldb, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int sladiv_(real *a, real *b, real *c__, real *d__, real *p, real *q);
extern int slae2_(real *a, real *b, real *c__, real *rt1, real *rt2);
extern int slaebz_(integer *ijob, integer *nitmax, integer *n, integer *mmax, integer *minp, integer *nbmin, real *abstol, real *reltol, real *pivmin, real *d__, real *e, real *e2, integer *nval, real *ab, real *c__, integer *mout, integer *nab, real *work, integer *iwork, integer *info);
extern int slaed0_(integer *icompq, integer *qsiz, integer *n, real *d__, real *e, real *q, integer *ldq, real *qstore, integer *ldqs, real *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: slaed1_ 14 10 4 6 6 4 4 6 4 6 4 4 */
/*:ref: slaed7_ 14 22 4 4 4 4 4 4 6 6 4 4 6 4 6 4 4 4 4 4 6 6 4 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
extern int slaed1_(integer *n, real *d__, real *q, integer *ldq, integer *indxq, real *rho, integer *cutpnt, real *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slaed2_ 14 17 4 4 4 6 6 4 4 6 6 6 6 6 4 4 4 4 4 */
/*:ref: slaed3_ 14 14 4 4 4 6 6 4 6 6 6 4 4 6 6 4 */
/*:ref: slamrg_ 14 6 4 4 6 4 4 4 */
extern int slaed2_(integer *k, integer *n, integer *n1, real *d__, real *q, integer *ldq, integer *indxq, real *rho, real *z__, real *dlamda, real *w, real *q2, integer *indx, integer *indxc, integer *indxp, integer *coltyp, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slamrg_ 14 6 4 4 6 4 4 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
extern int slaed3_(integer *k, integer *n, integer *n1, real *d__, real *q, integer *ldq, real *rho, real *dlamda, real *q2, integer *indx, integer *ctot, real *w, real *s, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamc3_ 6 2 6 6 */
/*:ref: slaed4_ 14 8 4 4 6 6 6 6 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
extern int slaed4_(integer *n, integer *i__, real *d__, real *z__, real *delta, real *rho, real *dlam, integer *info);
/*:ref: slaed5_ 14 6 4 6 6 6 6 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slaed6_ 14 8 4 12 6 6 6 6 6 4 */
extern int slaed5_(integer *i__, real *d__, real *z__, real *delta, real *rho, real *dlam);
extern int slaed6_(integer *kniter, logical *orgati, real *rho, real *d__, real *z__, real *finit, real *tau, integer *info);
/*:ref: slamch_ 6 2 13 124 */
extern int slaed7_(integer *icompq, integer *n, integer *qsiz, integer *tlvls, integer *curlvl, integer *curpbm, real *d__, real *q, integer *ldq, integer *indxq, real *rho, integer *cutpnt, real *qstore, integer *qptr, integer *prmptr, integer *perm, integer *givptr, integer *givcol, real *givnum, real *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaeda_ 14 14 4 4 4 4 4 4 4 4 6 6 4 6 6 4 */
/*:ref: slaed8_ 14 22 4 4 4 4 6 6 4 4 6 4 6 6 6 4 6 4 4 4 6 4 4 4 */
/*:ref: slaed9_ 14 13 4 4 4 4 6 6 4 6 6 6 6 4 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: slamrg_ 14 6 4 4 6 4 4 4 */
extern int slaed8_(integer *icompq, integer *k, integer *n, integer *qsiz, real *d__, real *q, integer *ldq, integer *indxq, real *rho, integer *cutpnt, real *z__, real *dlamda, real *q2, integer *ldq2, real *w, integer *perm, integer *givptr, integer *givcol, real *givnum, integer *indxp, integer *indx, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slamrg_ 14 6 4 4 6 4 4 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
extern int slaed9_(integer *k, integer *kstart, integer *kstop, integer *n, real *d__, real *q, integer *ldq, real *rho, real *dlamda, real *w, real *s, integer *lds, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamc3_ 6 2 6 6 */
/*:ref: slaed4_ 14 8 4 4 6 6 6 6 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
extern int slaeda_(integer *n, integer *tlvls, integer *curlvl, integer *curpbm, integer *prmptr, integer *perm, integer *givptr, integer *givcol, real *givnum, real *q, integer *qptr, real *z__, real *ztemp, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
extern int slaein_(logical *rightv, logical *noinit, integer *n, real *h__, integer *ldh, real *wr, real *wi, real *vr, real *vi, real *b, integer *ldb, real *work, real *eps3, real *smlnum, real *bignum, integer *info);
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slatrs_ 14 15 13 13 13 13 4 6 4 6 6 6 4 124 124 124 124 */
/*:ref: sasum_ 6 3 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: sladiv_ 14 6 6 6 6 6 6 6 */
extern int slaev2_(real *a, real *b, real *c__, real *rt1, real *rt2, real *cs1, real *sn1);
extern int slaexc_(logical *wantq, integer *n, real *t, integer *ldt, real *q, integer *ldq, integer *j1, integer *n1, integer *n2, real *work, integer *info);
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slasy2_ 14 16 12 12 4 4 4 6 4 6 4 6 4 6 6 4 6 4 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarfx_ 14 9 13 4 4 6 6 6 4 6 124 */
/*:ref: slanv2_ 14 10 6 6 6 6 6 6 6 6 6 6 */
extern int slag2_(real *a, integer *lda, real *b, integer *ldb, real *safmin, real *scale1, real *scale2, real *wr1, real *wr2, real *wi);
extern int slags2_(logical *upper, real *a1, real *a2, real *a3, real *b1, real *b2, real *b3, real *csu, real *snu, real *csv, real *snv, real *csq, real *snq);
/*:ref: slasv2_ 14 9 6 6 6 6 6 6 6 6 6 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
extern int slagtf_(integer *n, real *a, real *lambda, real *b, real *c__, real *tol, real *d__, integer *in, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
extern int slagtm_(char *trans, integer *n, integer *nrhs, real *alpha, real *dl, real *d__, real *du, real *x, integer *ldx, real *beta, real *b, integer *ldb, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int slagts_(integer *job, integer *n, real *a, real *b, real *c__, real *d__, integer *in, real *y, real *tol, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
extern int slagv2_(real *a, integer *lda, real *b, integer *ldb, real *alphar, real *alphai, real *beta, real *csl, real *snl, real *csr, real *snr);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: slag2_ 14 10 6 4 6 4 6 6 6 6 6 6 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: slasv2_ 14 9 6 6 6 6 6 6 6 6 6 */
extern int slahqr_(logical *wantt, logical *wantz, integer *n, integer *ilo, integer *ihi, real *h__, integer *ldh, real *wr, real *wi, integer *iloz, integer *ihiz, real *z__, integer *ldz, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slanhs_ 6 6 13 4 6 4 6 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slanv2_ 14 10 6 6 6 6 6 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
extern int slahrd_(integer *n, integer *k, integer *nb, real *a, integer *lda, real *tau, real *t, integer *ldt, real *y, integer *ldy);
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: strmv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int slaic1_(integer *job, integer *j, real *x, real *sest, real *w, real *gamma, real *sestpr, real *s, real *c__);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
extern int slaln2_(logical *ltrans, integer *na, integer *nw, real *smin, real *ca, real *a, integer *lda, real *d1, real *d2, real *b, integer *ldb, real *wr, real *wi, real *x, integer *ldx, real *scale, real *xnorm, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: sladiv_ 14 6 6 6 6 6 6 6 */
extern int slals0_(integer *icompq, integer *nl, integer *nr, integer *sqre, integer *nrhs, real *b, integer *ldb, real *bx, integer *ldbx, integer *perm, integer *givptr, integer *givcol, integer *ldgcol, real *givnum, integer *ldgnum, real *poles, real *difl, real *difr, real *z__, integer *k, real *c__, real *s, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slamc3_ 6 2 6 6 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
extern int slalsa_(integer *icompq, integer *smlsiz, integer *n, integer *nrhs, real *b, integer *ldb, real *bx, integer *ldbx, real *u, integer *ldu, real *vt, integer *k, real *difl, real *difr, real *z__, real *poles, integer *givptr, integer *givcol, integer *ldgcol, integer *perm, real *givnum, real *c__, real *s, real *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slasdt_ 14 7 4 4 4 4 4 4 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slals0_ 14 24 4 4 4 4 4 6 4 6 4 4 4 4 4 6 4 6 6 6 6 4 6 6 6 4 */
extern int slalsd_(char *uplo, integer *smlsiz, integer *n, integer *nrhs, real *d__, real *e, real *b, integer *ldb, real *rcond, integer *rank, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: slasdq_ 14 17 13 4 4 4 4 4 6 6 6 4 6 4 6 4 6 4 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: slasrt_ 14 5 13 4 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slasda_ 14 24 4 4 4 4 6 6 6 4 6 4 6 6 6 6 4 4 4 4 6 6 6 6 4 4 */
/*:ref: slalsa_ 14 26 4 4 4 4 6 4 6 4 6 4 6 4 6 6 6 6 4 4 4 4 6 6 6 6 4 4 */
extern E_f slamch_(char *cmach, ftnlen cmach_len);
extern int slamc1_(integer *beta, integer *t, logical *rnd, logical *ieee1);
extern int slamc2_(integer *beta, integer *t, logical *rnd, real *eps, integer *emin, real *rmin, integer *emax, real *rmax);
extern E_f slamc3_(real *a, real *b);
extern int slamc4_(integer *emin, real *start, integer *base);
extern int slamc5_(integer *beta, integer *p, integer *emin, logical *ieee, integer *emax, real *rmax);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int slamrg_(integer *n1, integer *n2, real *a, integer *strd1, integer *strd2, integer *index);
extern E_f slangb_(char *norm, integer *n, integer *kl, integer *ku, real *ab, integer *ldab, real *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f slange_(char *norm, integer *m, integer *n, real *a, integer *lda, real *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f slangt_(char *norm, integer *n, real *dl, real *d__, real *du, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f slanhs_(char *norm, integer *n, real *a, integer *lda, real *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f slansb_(char *norm, char *uplo, integer *n, integer *k, real *ab, integer *ldab, real *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f slansp_(char *norm, char *uplo, integer *n, real *ap, real *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f slanst_(char *norm, integer *n, real *d__, real *e, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f slansy_(char *norm, char *uplo, integer *n, real *a, integer *lda, real *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f slantb_(char *norm, char *uplo, char *diag, integer *n, integer *k, real *ab, integer *ldab, real *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f slantp_(char *norm, char *uplo, char *diag, integer *n, real *ap, real *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern E_f slantr_(char *norm, char *uplo, char *diag, integer *m, integer *n, real *a, integer *lda, real *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
extern int slanv2_(real *a, real *b, real *c__, real *d__, real *rt1r, real *rt1i, real *rt2r, real *rt2i, real *cs, real *sn);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slapy2_ 6 2 6 6 */
extern int slapll_(integer *n, real *x, integer *incx, real *y, integer *incy, real *ssmin);
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slas2_ 14 5 6 6 6 6 6 */
extern int slapmt_(logical *forwrd, integer *m, integer *n, real *x, integer *ldx, integer *k);
extern E_f slapy2_(real *x, real *y);
extern E_f slapy3_(real *x, real *y, real *z__);
extern int slaqgb_(integer *m, integer *n, integer *kl, integer *ku, real *ab, integer *ldab, real *r__, real *c__, real *rowcnd, real *colcnd, real *amax, char *equed, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
extern int slaqge_(integer *m, integer *n, real *a, integer *lda, real *r__, real *c__, real *rowcnd, real *colcnd, real *amax, char *equed, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
extern int slaqp2_(integer *m, integer *n, integer *offset, real *a, integer *lda, integer *jpvt, real *tau, real *vn1, real *vn2, real *work);
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
/*:ref: snrm2_ 6 3 4 6 4 */
extern int slaqps_(integer *m, integer *n, integer *offset, integer *nb, integer *kb, real *a, integer *lda, integer *jpvt, real *tau, real *vn1, real *vn2, real *auxv, real *f, integer *ldf);
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: snrm2_ 6 3 4 6 4 */
extern int slaqsb_(char *uplo, integer *n, integer *kd, real *ab, integer *ldab, real *s, real *scond, real *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int slaqsp_(char *uplo, integer *n, real *ap, real *s, real *scond, real *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int slaqsy_(char *uplo, integer *n, real *a, integer *lda, real *s, real *scond, real *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int slaqtr_(logical *ltran, logical *lreal, integer *n, real *t, integer *ldt, real *b, real *w, real *scale, real *x, real *work, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: sasum_ 6 3 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slaln2_ 14 18 12 4 4 6 6 6 4 6 6 6 4 6 6 6 4 6 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: sladiv_ 14 6 6 6 6 6 6 6 */
extern int slar1v_(integer *n, integer *b1, integer *bn, real *sigma, real *d__, real *l, real *ld, real *lld, real *gersch, real *z__, real *ztz, real *mingma, integer *r__, integer *isuppz, real *work);
/*:ref: slamch_ 6 2 13 124 */
extern int slar2v_(integer *n, real *x, real *y, real *z__, integer *incx, real *c__, real *s, integer *incc);
extern int slarf_(char *side, integer *m, integer *n, real *v, integer *incv, real *tau, real *c__, integer *ldc, real *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
extern int slarfb_(char *side, char *trans, char *direct, char *storev, integer *m, integer *n, integer *k, real *v, integer *ldv, real *t, integer *ldt, real *c__, integer *ldc, real *work, integer *ldwork, ftnlen side_len, ftnlen trans_len, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: strmm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
extern int slarfg_(integer *n, real *alpha, real *x, integer *incx, real *tau);
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int slarft_(char *direct, char *storev, integer *n, integer *k, real *v, integer *ldv, real *tau, real *t, integer *ldt, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: strmv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
extern int slarfx_(char *side, integer *m, integer *n, real *v, real *tau, real *c__, integer *ldc, real *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
extern int slargv_(integer *n, real *x, integer *incx, real *y, integer *incy, real *c__, integer *incc);
extern int slarnv_(integer *idist, integer *iseed, integer *n, real *x);
/*:ref: slaruv_ 14 3 4 4 6 */
extern int slarrb_(integer *n, real *d__, real *l, real *ld, real *lld, integer *ifirst, integer *ilast, real *sigma, real *reltol, real *w, real *wgap, real *werr, real *work, integer *iwork, integer *info);
/*:ref: slamch_ 6 2 13 124 */
extern int slarre_(integer *n, real *d__, real *e, real *tol, integer *nsplit, integer *isplit, integer *m, real *w, real *woff, real *gersch, real *work, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slasq2_ 14 3 4 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
extern int slarrf_(integer *n, real *d__, real *l, real *ld, real *lld, integer *ifirst, integer *ilast, real *w, real *dplus, real *lplus, real *work, integer *iwork, integer *info);
/*:ref: slamch_ 6 2 13 124 */
extern int slarrv_(integer *n, real *d__, real *l, integer *isplit, integer *m, real *w, integer *iblock, real *gersch, real *tol, real *z__, integer *ldz, integer *isuppz, real *work, integer *iwork, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slarrb_ 14 15 4 6 6 6 6 4 4 6 6 6 6 6 6 4 4 */
/*:ref: slarrf_ 14 13 4 6 6 6 6 4 4 6 6 6 6 4 4 */
/*:ref: sstein_ 14 13 4 6 6 4 6 4 4 6 4 6 4 4 4 */
/*:ref: slar1v_ 14 15 4 4 4 6 6 6 6 6 6 6 6 6 4 4 6 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
extern int slartg_(real *f, real *g, real *cs, real *sn, real *r__);
/*:ref: slamch_ 6 2 13 124 */
extern int slartv_(integer *n, real *x, integer *incx, real *y, integer *incy, real *c__, real *s, integer *incc);
extern int slaruv_(integer *iseed, integer *n, real *x);
extern int slarz_(char *side, integer *m, integer *n, integer *l, real *v, integer *incv, real *tau, real *c__, integer *ldc, real *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
extern int slarzb_(char *side, char *trans, char *direct, char *storev, integer *m, integer *n, integer *k, integer *l, real *v, integer *ldv, real *t, integer *ldt, real *c__, integer *ldc, real *work, integer *ldwork, ftnlen side_len, ftnlen trans_len, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: strmm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
extern int slarzt_(char *direct, char *storev, integer *n, integer *k, real *v, integer *ldv, real *tau, real *t, integer *ldt, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: strmv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
extern int slas2_(real *f, real *g, real *h__, real *ssmin, real *ssmax);
extern int slascl_(char *type__, integer *kl, integer *ku, real *cfrom, real *cto, integer *m, integer *n, real *a, integer *lda, integer *info, ftnlen type_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
extern int slasd0_(integer *n, integer *sqre, real *d__, real *e, real *u, integer *ldu, real *vt, integer *ldvt, integer *smlsiz, integer *iwork, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slasdq_ 14 17 13 4 4 4 4 4 6 6 6 4 6 4 6 4 6 4 124 */
/*:ref: slasdt_ 14 7 4 4 4 4 4 4 4 */
/*:ref: slasd1_ 14 14 4 4 4 6 6 6 6 4 6 4 4 4 6 4 */
extern int slasd1_(integer *nl, integer *nr, integer *sqre, real *d__, real *alpha, real *beta, real *u, integer *ldu, real *vt, integer *ldvt, integer *idxq, integer *iwork, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slasd2_ 14 23 4 4 4 4 6 6 6 6 6 4 6 4 6 6 4 6 4 4 4 4 4 4 4 */
/*:ref: slasd3_ 14 20 4 4 4 4 6 6 4 6 6 4 6 4 6 4 6 4 4 4 6 4 */
/*:ref: slamrg_ 14 6 4 4 6 4 4 4 */
extern int slasd2_(integer *nl, integer *nr, integer *sqre, integer *k, real *d__, real *z__, real *alpha, real *beta, real *u, integer *ldu, real *vt, integer *ldvt, real *dsigma, real *u2, integer *ldu2, real *vt2, integer *ldvt2, integer *idxp, integer *idx, integer *idxc, integer *idxq, integer *coltyp, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamrg_ 14 6 4 4 6 4 4 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
extern int slasd3_(integer *nl, integer *nr, integer *sqre, integer *k, real *d__, real *q, integer *ldq, real *dsigma, real *u, integer *ldu, real *u2, integer *ldu2, real *vt, integer *ldvt, real *vt2, integer *ldvt2, integer *idxc, integer *ctot, real *z__, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slamc3_ 6 2 6 6 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slasd4_ 14 9 4 4 6 6 6 6 6 6 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
extern int slasd4_(integer *n, integer *i__, real *d__, real *z__, real *delta, real *rho, real *sigma, real *work, integer *info);
/*:ref: slasd5_ 14 7 4 6 6 6 6 6 6 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slaed6_ 14 8 4 12 6 6 6 6 6 4 */
extern int slasd5_(integer *i__, real *d__, real *z__, real *delta, real *rho, real *dsigma, real *work);
extern int slasd6_(integer *icompq, integer *nl, integer *nr, integer *sqre, real *d__, real *vf, real *vl, real *alpha, real *beta, integer *idxq, integer *perm, integer *givptr, integer *givcol, integer *ldgcol, real *givnum, integer *ldgnum, real *poles, real *difl, real *difr, real *z__, integer *k, real *c__, real *s, real *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slasd7_ 14 27 4 4 4 4 4 6 6 6 6 6 6 6 6 6 6 4 4 4 4 4 4 4 6 4 6 6 4 */
/*:ref: slasd8_ 14 12 4 4 6 6 6 6 6 6 4 6 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slamrg_ 14 6 4 4 6 4 4 4 */
extern int slasd7_(integer *icompq, integer *nl, integer *nr, integer *sqre, integer *k, real *d__, real *z__, real *zw, real *vf, real *vfw, real *vl, real *vlw, real *alpha, real *beta, real *dsigma, integer *idx, integer *idxp, integer *idxq, integer *perm, integer *givptr, integer *givcol, integer *ldgcol, real *givnum, integer *ldgnum, real *c__, real *s, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamrg_ 14 6 4 4 6 4 4 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
extern int slasd8_(integer *icompq, integer *k, real *d__, real *z__, real *vf, real *vl, real *difl, real *difr, integer *lddifr, real *dsigma, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamc3_ 6 2 6 6 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slasd4_ 14 9 4 4 6 6 6 6 6 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
extern int slasd9_(integer *icompq, integer *ldu, integer *k, real *d__, real *z__, real *vf, real *vl, real *difl, real *difr, real *dsigma, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamc3_ 6 2 6 6 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slasd4_ 14 9 4 4 6 6 6 6 6 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
extern int slasda_(integer *icompq, integer *smlsiz, integer *n, integer *sqre, real *d__, real *e, real *u, integer *ldu, real *vt, integer *k, real *difl, real *difr, real *z__, real *poles, integer *givptr, integer *givcol, integer *ldgcol, integer *perm, real *givnum, real *c__, real *s, real *work, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slasdq_ 14 17 13 4 4 4 4 4 6 6 6 4 6 4 6 4 6 4 124 */
/*:ref: slasdt_ 14 7 4 4 4 4 4 4 4 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slasd6_ 14 26 4 4 4 4 6 6 6 6 6 4 4 4 4 4 6 4 6 6 6 6 4 6 6 6 4 4 */
extern int slasdq_(char *uplo, integer *sqre, integer *n, integer *ncvt, integer *nru, integer *ncc, real *d__, real *e, real *vt, integer *ldvt, real *u, integer *ldu, real *c__, integer *ldc, real *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: slasr_ 14 12 13 13 13 4 4 6 6 6 4 124 124 124 */
/*:ref: sbdsqr_ 14 16 13 4 4 4 4 6 6 6 4 6 4 6 4 6 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int slasdt_(integer *n, integer *lvl, integer *nd, integer *inode, integer *ndiml, integer *ndimr, integer *msub);
extern int slaset_(char *uplo, integer *m, integer *n, real *alpha, real *beta, real *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int slasq1_(integer *n, real *d__, real *e, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slas2_ 14 5 6 6 6 6 6 */
/*:ref: slasrt_ 14 5 13 4 6 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slasq2_ 14 3 4 6 4 */
extern int slasq2_(integer *n, real *z__, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slasrt_ 14 5 13 4 6 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: slasq3_ 14 12 4 4 6 4 6 6 6 6 4 4 4 12 */
extern int slasq3_(integer *i0, integer *n0, real *z__, integer *pp, real *dmin__, real *sigma, real *desig, real *qmax, integer *nfail, integer *iter, integer *ndiv, logical *ieee);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slasq4_ 14 13 4 4 6 4 4 6 6 6 6 6 6 6 4 */
/*:ref: slasq5_ 14 12 4 4 6 4 6 6 6 6 6 6 6 12 */
/*:ref: slasq6_ 14 10 4 4 6 4 6 6 6 6 6 6 */
extern int slasq4_(integer *i0, integer *n0, real *z__, integer *pp, integer *n0in, real *dmin__, real *dmin1, real *dmin2, real *dn, real *dn1, real *dn2, real *tau, integer *ttype);
extern int slasq5_(integer *i0, integer *n0, real *z__, integer *pp, real *tau, real *dmin__, real *dmin1, real *dmin2, real *dn, real *dnm1, real *dnm2, logical *ieee);
extern int slasq6_(integer *i0, integer *n0, real *z__, integer *pp, real *dmin__, real *dmin1, real *dmin2, real *dn, real *dnm1, real *dnm2);
/*:ref: slamch_ 6 2 13 124 */
extern int slasr_(char *side, char *pivot, char *direct, integer *m, integer *n, real *c__, real *s, real *a, integer *lda, ftnlen side_len, ftnlen pivot_len, ftnlen direct_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int slasrt_(char *id, integer *n, real *d__, integer *info, ftnlen id_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int slassq_(integer *n, real *x, integer *incx, real *scale, real *sumsq);
extern int slasv2_(real *f, real *g, real *h__, real *ssmin, real *ssmax, real *snr, real *csr, real *snl, real *csl);
/*:ref: slamch_ 6 2 13 124 */
extern int slaswp_(integer *n, real *a, integer *lda, integer *k1, integer *k2, integer *ipiv, integer *incx);
extern int slasy2_(logical *ltranl, logical *ltranr, integer *isgn, integer *n1, integer *n2, real *tl, integer *ldtl, real *tr, integer *ldtr, real *b, integer *ldb, real *scale, real *x, integer *ldx, real *xnorm, integer *info);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int slasyf_(char *uplo, integer *n, integer *nb, integer *kb, real *a, integer *lda, integer *ipiv, real *w, integer *ldw, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
extern int slatbs_(char *uplo, char *trans, char *diag, char *normin, integer *n, integer *kd, real *ab, integer *ldab, real *x, real *scale, real *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: sasum_ 6 3 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: stbsv_ 14 12 13 13 13 4 4 6 4 6 4 124 124 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
extern int slatdf_(integer *ijob, integer *n, real *z__, integer *ldz, real *rhs, real *rdsum, real *rdscal, integer *ipiv, integer *jpiv);
/*:ref: slaswp_ 14 7 4 6 4 4 4 4 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
/*:ref: sgecon_ 14 10 13 4 6 4 6 6 6 4 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sgesc2_ 14 7 4 6 4 6 4 4 6 */
/*:ref: sasum_ 6 3 4 6 4 */
extern int slatps_(char *uplo, char *trans, char *diag, char *normin, integer *n, real *ap, real *x, real *scale, real *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: sasum_ 6 3 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: stpsv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
extern int slatrd_(char *uplo, integer *n, integer *nb, real *a, integer *lda, real *e, real *tau, real *w, integer *ldw, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: ssymv_ 14 11 13 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
extern int slatrs_(char *uplo, char *trans, char *diag, char *normin, integer *n, real *a, integer *lda, real *x, real *scale, real *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: sasum_ 6 3 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: strsv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
extern int slatrz_(integer *m, integer *n, integer *l, real *a, integer *lda, real *tau, real *work);
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: slarz_ 14 11 13 4 4 4 6 4 6 6 4 6 124 */
extern int slatzm_(char *side, integer *m, integer *n, real *v, integer *incv, real *tau, real *c1, real *c2, integer *ldc, real *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
extern int slauu2_(char *uplo, integer *n, real *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int slauum_(char *uplo, integer *n, real *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: slauu2_ 14 6 13 4 6 4 4 124 */
/*:ref: strmm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: ssyrk_ 14 12 13 13 4 4 6 6 4 6 6 4 124 124 */
extern int sopgtr_(char *uplo, integer *n, real *ap, real *tau, real *q, integer *ldq, real *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorg2l_ 14 8 4 4 4 6 4 6 6 4 */
/*:ref: sorg2r_ 14 8 4 4 4 6 4 6 6 4 */
extern int sopmtr_(char *side, char *uplo, char *trans, integer *m, integer *n, real *ap, real *tau, real *c__, integer *ldc, real *work, integer *info, ftnlen side_len, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sorg2l_(integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int sorg2r_(integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int sorgbr_(char *vect, integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info, ftnlen vect_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: sorglq_ 14 9 4 4 4 6 4 6 6 4 4 */
extern int sorghr_(integer *n, integer *ilo, integer *ihi, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
extern int sorgl2_(integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int sorglq_(integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorgl2_ 14 8 4 4 4 6 4 6 6 4 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sorgql_(integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorg2l_ 14 8 4 4 4 6 4 6 6 4 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sorgqr_(integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorg2r_ 14 8 4 4 4 6 4 6 6 4 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sorgr2_(integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int sorgrq_(integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorgr2_ 14 8 4 4 4 6 4 6 6 4 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sorgtr_(char *uplo, integer *n, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorgql_ 14 9 4 4 4 6 4 6 6 4 4 */
/*:ref: sorgqr_ 14 9 4 4 4 6 4 6 6 4 4 */
extern int sorm2l_(char *side, char *trans, integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sorm2r_(char *side, char *trans, integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sormbr_(char *vect, char *side, char *trans, integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *lwork, integer *info, ftnlen vect_len, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: sormlq_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
extern int sormhr_(char *side, char *trans, integer *m, integer *n, integer *ilo, integer *ihi, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
extern int sorml2_(char *side, char *trans, integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sormlq_(char *side, char *trans, integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorml2_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sormql_(char *side, char *trans, integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorm2l_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sormqr_(char *side, char *trans, integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sorm2r_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sormr2_(char *side, char *trans, integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarf_ 14 10 13 4 4 6 4 6 6 4 6 124 */
extern int sormr3_(char *side, char *trans, integer *m, integer *n, integer *k, integer *l, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarz_ 14 11 13 4 4 4 6 4 6 6 4 6 124 */
extern int sormrq_(char *side, char *trans, integer *m, integer *n, integer *k, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sormr2_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: slarft_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarfb_ 14 19 13 13 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sormrz_(char *side, char *trans, integer *m, integer *n, integer *k, integer *l, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sormr3_ 14 15 13 13 4 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: slarzt_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarzb_ 14 20 13 13 13 13 4 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int sormtr_(char *side, char *uplo, char *trans, integer *m, integer *n, real *a, integer *lda, real *tau, real *c__, integer *ldc, real *work, integer *lwork, integer *info, ftnlen side_len, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sormql_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
/*:ref: sormqr_ 14 15 13 13 4 4 4 6 4 6 6 4 6 4 4 124 124 */
extern int spbcon_(char *uplo, integer *n, integer *kd, real *ab, integer *ldab, real *anorm, real *rcond, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: slatbs_ 14 16 13 13 13 13 4 4 6 4 6 6 6 4 124 124 124 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: srscl_ 14 4 4 6 6 4 */
extern int spbequ_(char *uplo, integer *n, integer *kd, real *ab, integer *ldab, real *s, real *scond, real *amax, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int spbrfs_(char *uplo, integer *n, integer *kd, integer *nrhs, real *ab, integer *ldab, real *afb, integer *ldafb, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssbmv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: spbtrs_ 14 10 13 4 4 4 6 4 6 4 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
extern int spbstf_(char *uplo, integer *n, integer *kd, real *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ssyr_ 14 8 13 4 6 6 4 6 4 124 */
extern int spbsv_(char *uplo, integer *n, integer *kd, integer *nrhs, real *ab, integer *ldab, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spbtrf_ 14 7 13 4 4 6 4 4 124 */
/*:ref: spbtrs_ 14 10 13 4 4 4 6 4 6 4 4 124 */
extern int spbsvx_(char *fact, char *uplo, integer *n, integer *kd, integer *nrhs, real *ab, integer *ldab, real *afb, integer *ldafb, char *equed, real *s, real *b, integer *ldb, real *x, integer *ldx, real *rcond, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spbequ_ 14 10 13 4 4 6 4 6 6 6 4 124 */
/*:ref: slaqsb_ 14 11 13 4 4 6 4 6 6 6 13 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: spbtrf_ 14 7 13 4 4 6 4 4 124 */
/*:ref: slansb_ 6 9 13 13 4 4 6 4 6 124 124 */
/*:ref: spbcon_ 14 11 13 4 4 6 4 6 6 6 4 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: spbtrs_ 14 10 13 4 4 4 6 4 6 4 4 124 */
/*:ref: spbrfs_ 14 18 13 4 4 4 6 4 6 4 6 4 6 4 6 6 6 4 4 124 */
extern int spbtf2_(char *uplo, integer *n, integer *kd, real *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ssyr_ 14 8 13 4 6 6 4 6 4 124 */
extern int spbtrf_(char *uplo, integer *n, integer *kd, real *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: spbtf2_ 14 7 13 4 4 6 4 4 124 */
/*:ref: spotf2_ 14 6 13 4 6 4 4 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: ssyrk_ 14 12 13 13 4 4 6 6 4 6 6 4 124 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
extern int spbtrs_(char *uplo, integer *n, integer *kd, integer *nrhs, real *ab, integer *ldab, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: stbsv_ 14 12 13 13 13 4 4 6 4 6 4 124 124 124 */
extern int spocon_(char *uplo, integer *n, real *a, integer *lda, real *anorm, real *rcond, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: slatrs_ 14 15 13 13 13 13 4 6 4 6 6 6 4 124 124 124 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: srscl_ 14 4 4 6 6 4 */
extern int spoequ_(integer *n, real *a, integer *lda, real *s, real *scond, real *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int sporfs_(char *uplo, integer *n, integer *nrhs, real *a, integer *lda, real *af, integer *ldaf, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssymv_ 14 11 13 4 6 6 4 6 4 6 6 4 124 */
/*:ref: spotrs_ 14 9 13 4 4 6 4 6 4 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
extern int sposv_(char *uplo, integer *n, integer *nrhs, real *a, integer *lda, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spotrf_ 14 6 13 4 6 4 4 124 */
/*:ref: spotrs_ 14 9 13 4 4 6 4 6 4 4 124 */
extern int sposvx_(char *fact, char *uplo, integer *n, integer *nrhs, real *a, integer *lda, real *af, integer *ldaf, char *equed, real *s, real *b, integer *ldb, real *x, integer *ldx, real *rcond, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spoequ_ 14 7 4 6 4 6 6 6 4 */
/*:ref: slaqsy_ 14 10 13 4 6 4 6 6 6 13 124 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: spotrf_ 14 6 13 4 6 4 4 124 */
/*:ref: slansy_ 6 8 13 13 4 6 4 6 124 124 */
/*:ref: spocon_ 14 10 13 4 6 4 6 6 6 4 4 124 */
/*:ref: spotrs_ 14 9 13 4 4 6 4 6 4 4 124 */
/*:ref: sporfs_ 14 17 13 4 4 6 4 6 4 6 4 6 4 6 6 6 4 4 124 */
extern int spotf2_(char *uplo, integer *n, real *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int spotrf_(char *uplo, integer *n, real *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: spotf2_ 14 6 13 4 6 4 4 124 */
/*:ref: ssyrk_ 14 12 13 13 4 4 6 6 4 6 6 4 124 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
extern int spotri_(char *uplo, integer *n, real *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: strtri_ 14 8 13 13 4 6 4 4 124 124 */
/*:ref: slauum_ 14 6 13 4 6 4 4 124 */
extern int spotrs_(char *uplo, integer *n, integer *nrhs, real *a, integer *lda, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
extern int sppcon_(char *uplo, integer *n, real *ap, real *anorm, real *rcond, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: slatps_ 14 14 13 13 13 13 4 6 6 6 6 4 124 124 124 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: srscl_ 14 4 4 6 6 4 */
extern int sppequ_(char *uplo, integer *n, real *ap, real *s, real *scond, real *amax, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int spprfs_(char *uplo, integer *n, integer *nrhs, real *ap, real *afp, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sspmv_ 14 10 13 4 6 6 6 4 6 6 4 124 */
/*:ref: spptrs_ 14 8 13 4 4 6 6 4 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
extern int sppsv_(char *uplo, integer *n, integer *nrhs, real *ap, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spptrf_ 14 5 13 4 6 4 124 */
/*:ref: spptrs_ 14 8 13 4 4 6 6 4 4 124 */
extern int sppsvx_(char *fact, char *uplo, integer *n, integer *nrhs, real *ap, real *afp, char *equed, real *s, real *b, integer *ldb, real *x, integer *ldx, real *rcond, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sppequ_ 14 8 13 4 6 6 6 6 4 124 */
/*:ref: slaqsp_ 14 9 13 4 6 6 6 6 13 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: spptrf_ 14 5 13 4 6 4 124 */
/*:ref: slansp_ 6 7 13 13 4 6 6 124 124 */
/*:ref: sppcon_ 14 9 13 4 6 6 6 6 4 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: spptrs_ 14 8 13 4 4 6 6 4 4 124 */
/*:ref: spprfs_ 14 15 13 4 4 6 6 6 4 6 4 6 6 6 4 4 124 */
extern int spptrf_(char *uplo, integer *n, real *ap, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: stpsv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sspr_ 14 7 13 4 6 6 4 6 124 */
extern int spptri_(char *uplo, integer *n, real *ap, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: stptri_ 14 7 13 13 4 6 4 124 124 */
/*:ref: sspr_ 14 7 13 4 6 6 4 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: stpmv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
extern int spptrs_(char *uplo, integer *n, integer *nrhs, real *ap, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: stpsv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
extern int sptcon_(integer *n, real *d__, real *e, real *anorm, real *rcond, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: isamax_ 4 3 4 6 4 */
extern int spteqr_(char *compz, integer *n, real *d__, real *e, real *z__, integer *ldz, real *work, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: spttrf_ 14 4 4 6 6 4 */
/*:ref: sbdsqr_ 14 16 13 4 4 4 4 6 6 6 4 6 4 6 4 6 4 124 */
extern int sptrfs_(integer *n, integer *nrhs, real *d__, real *e, real *df, real *ef, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: spttrs_ 14 7 4 4 6 6 6 4 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
extern int sptsv_(integer *n, integer *nrhs, real *d__, real *e, real *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spttrf_ 14 4 4 6 6 4 */
/*:ref: spttrs_ 14 7 4 4 6 6 6 4 4 */
extern int sptsvx_(char *fact, integer *n, integer *nrhs, real *d__, real *e, real *df, real *ef, real *b, integer *ldb, real *x, integer *ldx, real *rcond, real *ferr, real *berr, real *work, integer *info, ftnlen fact_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: spttrf_ 14 4 4 6 6 4 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: sptcon_ 14 7 4 6 6 6 6 6 4 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: spttrs_ 14 7 4 4 6 6 6 4 4 */
/*:ref: sptrfs_ 14 14 4 4 6 6 6 6 6 4 6 4 6 6 6 4 */
extern int spttrf_(integer *n, real *d__, real *e, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int spttrs_(integer *n, integer *nrhs, real *d__, real *e, real *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: sptts2_ 14 6 4 4 6 6 6 4 */
extern int sptts2_(integer *n, integer *nrhs, real *d__, real *e, real *b, integer *ldb);
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int srscl_(integer *n, real *sa, real *sx, integer *incx);
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int ssbev_(char *jobz, char *uplo, integer *n, integer *kd, real *ab, integer *ldab, real *w, real *z__, integer *ldz, real *work, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slansb_ 6 9 13 13 4 4 6 4 6 124 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: ssbtrd_ 14 14 13 13 4 4 6 4 6 6 6 4 6 4 124 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int ssbevd_(char *jobz, char *uplo, integer *n, integer *kd, real *ab, integer *ldab, real *w, real *z__, integer *ldz, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slansb_ 6 9 13 13 4 4 6 4 6 124 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: ssbtrd_ 14 14 13 13 4 4 6 4 6 6 6 4 6 4 124 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: sstedc_ 14 12 13 4 6 6 6 4 6 4 4 4 4 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int ssbevx_(char *jobz, char *range, char *uplo, integer *n, integer *kd, real *ab, integer *ldab, real *q, integer *ldq, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, real *z__, integer *ldz, real *work, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slansb_ 6 9 13 13 4 4 6 4 6 124 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: ssbtrd_ 14 14 13 13 4 4 6 4 6 6 6 4 6 4 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: sstein_ 14 13 4 6 6 4 6 4 4 6 4 6 4 4 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int ssbgst_(char *vect, char *uplo, integer *n, integer *ka, integer *kb, real *ab, integer *ldab, real *bb, integer *ldbb, real *x, integer *ldx, real *work, integer *info, ftnlen vect_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: slargv_ 14 7 4 6 4 6 4 6 4 */
/*:ref: slartv_ 14 8 4 6 4 6 4 6 6 4 */
/*:ref: slar2v_ 14 8 4 6 6 6 4 6 6 4 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
extern int ssbgv_(char *jobz, char *uplo, integer *n, integer *ka, integer *kb, real *ab, integer *ldab, real *bb, integer *ldbb, real *w, real *z__, integer *ldz, real *work, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spbstf_ 14 7 13 4 4 6 4 4 124 */
/*:ref: ssbgst_ 14 15 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 */
/*:ref: ssbtrd_ 14 14 13 13 4 4 6 4 6 6 6 4 6 4 124 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
extern int ssbgvd_(char *jobz, char *uplo, integer *n, integer *ka, integer *kb, real *ab, integer *ldab, real *bb, integer *ldbb, real *w, real *z__, integer *ldz, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spbstf_ 14 7 13 4 4 6 4 4 124 */
/*:ref: ssbgst_ 14 15 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 */
/*:ref: ssbtrd_ 14 14 13 13 4 4 6 4 6 6 6 4 6 4 124 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: sstedc_ 14 12 13 4 6 6 6 4 6 4 4 4 4 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
extern int ssbgvx_(char *jobz, char *range, char *uplo, integer *n, integer *ka, integer *kb, real *ab, integer *ldab, real *bb, integer *ldbb, real *q, integer *ldq, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, real *z__, integer *ldz, real *work, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spbstf_ 14 7 13 4 4 6 4 4 124 */
/*:ref: ssbgst_ 14 15 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 */
/*:ref: ssbtrd_ 14 14 13 13 4 4 6 4 6 6 6 4 6 4 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: sstein_ 14 13 4 6 6 4 6 4 4 6 4 6 4 4 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int ssbtrd_(char *vect, char *uplo, integer *n, integer *kd, real *ab, integer *ldab, real *d__, real *e, real *q, integer *ldq, real *work, integer *info, ftnlen vect_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slargv_ 14 7 4 6 4 6 4 6 4 */
/*:ref: slartv_ 14 8 4 6 4 6 4 6 6 4 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: slar2v_ 14 8 4 6 6 6 4 6 6 4 */
extern int sspcon_(char *uplo, integer *n, real *ap, integer *ipiv, real *anorm, real *rcond, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: ssptrs_ 14 9 13 4 4 6 4 6 4 4 124 */
extern int sspev_(char *jobz, char *uplo, integer *n, real *ap, real *w, real *z__, integer *ldz, real *work, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slansp_ 6 7 13 13 4 6 6 124 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ssptrd_ 14 8 13 4 6 6 6 6 4 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: sopgtr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
extern int sspevd_(char *jobz, char *uplo, integer *n, real *ap, real *w, real *z__, integer *ldz, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slansp_ 6 7 13 13 4 6 6 124 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ssptrd_ 14 8 13 4 6 6 6 6 4 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: sstedc_ 14 12 13 4 6 6 6 4 6 4 4 4 4 124 */
/*:ref: sopmtr_ 14 14 13 13 13 4 4 6 6 6 4 6 4 124 124 124 */
extern int sspevx_(char *jobz, char *range, char *uplo, integer *n, real *ap, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, real *z__, integer *ldz, real *work, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slansp_ 6 7 13 13 4 6 6 124 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ssptrd_ 14 8 13 4 6 6 6 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: sopgtr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: sstein_ 14 13 4 6 6 4 6 4 4 6 4 6 4 4 4 */
/*:ref: sopmtr_ 14 14 13 13 13 4 4 6 6 6 4 6 4 124 124 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int sspgst_(integer *itype, char *uplo, integer *n, real *ap, real *bp, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: stpsv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
/*:ref: sspmv_ 14 10 13 4 6 6 6 4 6 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: sspr2_ 14 9 13 4 6 6 4 6 4 6 124 */
/*:ref: stpmv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
extern int sspgv_(integer *itype, char *jobz, char *uplo, integer *n, real *ap, real *bp, real *w, real *z__, integer *ldz, real *work, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spptrf_ 14 5 13 4 6 4 124 */
/*:ref: sspgst_ 14 7 4 13 4 6 6 4 124 */
/*:ref: sspev_ 14 11 13 13 4 6 6 6 4 6 4 124 124 */
/*:ref: stpsv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
/*:ref: stpmv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
extern int sspgvd_(integer *itype, char *jobz, char *uplo, integer *n, real *ap, real *bp, real *w, real *z__, integer *ldz, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spptrf_ 14 5 13 4 6 4 124 */
/*:ref: sspgst_ 14 7 4 13 4 6 6 4 124 */
/*:ref: sspevd_ 14 14 13 13 4 6 6 6 4 6 4 4 4 4 124 124 */
/*:ref: stpsv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
/*:ref: stpmv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
extern int sspgvx_(integer *itype, char *jobz, char *range, char *uplo, integer *n, real *ap, real *bp, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, real *z__, integer *ldz, real *work, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spptrf_ 14 5 13 4 6 4 124 */
/*:ref: sspgst_ 14 7 4 13 4 6 6 4 124 */
/*:ref: sspevx_ 14 21 13 13 13 4 6 6 6 4 4 6 4 6 6 4 6 4 4 4 124 124 124 */
/*:ref: stpsv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
/*:ref: stpmv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
extern int ssprfs_(char *uplo, integer *n, integer *nrhs, real *ap, real *afp, integer *ipiv, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sspmv_ 14 10 13 4 6 6 6 4 6 6 4 124 */
/*:ref: ssptrs_ 14 9 13 4 4 6 4 6 4 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
extern int sspsv_(char *uplo, integer *n, integer *nrhs, real *ap, integer *ipiv, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ssptrf_ 14 6 13 4 6 4 4 124 */
/*:ref: ssptrs_ 14 9 13 4 4 6 4 6 4 4 124 */
extern int sspsvx_(char *fact, char *uplo, integer *n, integer *nrhs, real *ap, real *afp, integer *ipiv, real *b, integer *ldb, real *x, integer *ldx, real *rcond, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssptrf_ 14 6 13 4 6 4 4 124 */
/*:ref: slansp_ 6 7 13 13 4 6 6 124 124 */
/*:ref: sspcon_ 14 10 13 4 6 4 6 6 6 4 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: ssptrs_ 14 9 13 4 4 6 4 6 4 4 124 */
/*:ref: ssprfs_ 14 16 13 4 4 6 6 4 6 4 6 4 6 6 6 4 4 124 */
extern int ssptrd_(char *uplo, integer *n, real *ap, real *d__, real *e, real *tau, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: sspmv_ 14 10 13 4 6 6 6 4 6 6 4 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: sspr2_ 14 9 13 4 6 6 4 6 4 6 124 */
extern int ssptrf_(char *uplo, integer *n, real *ap, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sspr_ 14 7 13 4 6 6 4 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int ssptri_(char *uplo, integer *n, real *ap, integer *ipiv, real *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sspmv_ 14 10 13 4 6 6 6 4 6 6 4 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int ssptrs_(char *uplo, integer *n, integer *nrhs, real *ap, integer *ipiv, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
extern int sstebz_(char *range, char *order, integer *n, real *vl, real *vu, integer *il, integer *iu, real *abstol, real *d__, real *e, integer *m, integer *nsplit, real *w, integer *iblock, integer *isplit, real *work, integer *iwork, integer *info, ftnlen range_len, ftnlen order_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: slaebz_ 14 20 4 4 4 4 4 4 6 6 6 6 6 6 4 6 6 4 4 6 4 4 */
extern int sstedc_(char *compz, integer *n, real *d__, real *e, real *z__, integer *ldz, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaed0_ 14 12 4 4 4 6 6 6 4 6 4 6 4 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: slasrt_ 14 5 13 4 6 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int sstegr_(char *jobz, char *range, integer *n, real *d__, real *e, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, real *z__, integer *ldz, integer *isuppz, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen range_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slarre_ 14 12 4 6 6 6 4 4 4 6 6 6 6 4 */
/*:ref: slarrv_ 14 15 4 6 6 4 4 6 4 6 6 6 4 4 6 4 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int sstein_(integer *n, real *d__, real *e, integer *m, real *w, integer *iblock, integer *isplit, real *z__, integer *ldz, real *work, integer *iwork, integer *ifail, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slarnv_ 14 4 4 4 4 6 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slagtf_ 14 9 4 6 6 6 6 6 6 4 4 */
/*:ref: sasum_ 6 3 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slagts_ 14 10 4 4 6 6 6 6 4 6 6 4 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
extern int ssteqr_(char *compz, integer *n, real *d__, real *e, real *z__, integer *ldz, real *work, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slaev2_ 14 7 6 6 6 6 6 6 6 */
/*:ref: slasr_ 14 12 13 13 13 4 4 6 6 6 4 124 124 124 */
/*:ref: slae2_ 14 5 6 6 6 6 6 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: slasrt_ 14 5 13 4 6 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int ssterf_(integer *n, real *d__, real *e, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: slae2_ 14 5 6 6 6 6 6 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: slasrt_ 14 5 13 4 6 4 124 */
extern int sstev_(char *jobz, integer *n, real *d__, real *e, real *z__, integer *ldz, real *work, integer *info, ftnlen jobz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
extern int sstevd_(char *jobz, integer *n, real *d__, real *e, real *z__, integer *ldz, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: sstedc_ 14 12 13 4 6 6 6 4 6 4 4 4 4 124 */
extern int sstevr_(char *jobz, char *range, integer *n, real *d__, real *e, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, real *z__, integer *ldz, integer *isuppz, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen range_len);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: sstegr_ 14 22 13 13 4 6 6 6 6 4 4 6 4 6 6 4 4 6 4 4 4 4 124 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: sstein_ 14 13 4 6 6 4 6 4 4 6 4 6 4 4 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int sstevx_(char *jobz, char *range, integer *n, real *d__, real *e, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, real *z__, integer *ldz, real *work, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slanst_ 6 5 13 4 6 6 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: sstein_ 14 13 4 6 6 4 6 4 4 6 4 6 4 4 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int ssycon_(char *uplo, integer *n, real *a, integer *lda, integer *ipiv, real *anorm, real *rcond, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: ssytrs_ 14 10 13 4 4 6 4 4 6 4 4 124 */
extern int ssyev_(char *jobz, char *uplo, integer *n, real *a, integer *lda, real *w, real *work, integer *lwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slansy_ 6 8 13 13 4 6 4 6 124 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: ssytrd_ 14 11 13 4 6 4 6 6 6 6 4 4 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: sorgtr_ 14 9 13 4 6 4 6 6 4 4 124 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int ssyevd_(char *jobz, char *uplo, integer *n, real *a, integer *lda, real *w, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slansy_ 6 8 13 13 4 6 4 6 124 124 */
/*:ref: slascl_ 14 11 13 4 4 6 6 4 4 6 4 4 124 */
/*:ref: ssytrd_ 14 11 13 4 6 4 6 6 6 6 4 4 124 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: sstedc_ 14 12 13 4 6 6 6 4 6 4 4 4 4 124 */
/*:ref: sormtr_ 14 16 13 13 13 4 4 6 4 6 6 4 6 4 4 124 124 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int ssyevr_(char *jobz, char *range, char *uplo, integer *n, real *a, integer *lda, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, real *z__, integer *ldz, integer *isuppz, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slansy_ 6 8 13 13 4 6 4 6 124 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ssytrd_ 14 11 13 4 6 4 6 6 6 6 4 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: sstegr_ 14 22 13 13 4 6 6 6 6 4 4 6 4 6 6 4 4 6 4 4 4 4 124 124 */
/*:ref: sormtr_ 14 16 13 13 13 4 4 6 4 6 6 4 6 4 4 124 124 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: sstein_ 14 13 4 6 6 4 6 4 4 6 4 6 4 4 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int ssyevx_(char *jobz, char *range, char *uplo, integer *n, real *a, integer *lda, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, real *z__, integer *ldz, real *work, integer *lwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slansy_ 6 8 13 13 4 6 4 6 124 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: ssytrd_ 14 11 13 4 6 4 6 6 6 6 4 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssterf_ 14 4 4 6 6 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sorgtr_ 14 9 13 4 6 4 6 6 4 4 124 */
/*:ref: ssteqr_ 14 9 13 4 6 6 6 4 6 4 124 */
/*:ref: sstebz_ 14 20 13 13 4 6 6 4 4 6 6 6 4 4 6 4 4 6 4 4 124 124 */
/*:ref: sstein_ 14 13 4 6 6 4 6 4 4 6 4 6 4 4 4 */
/*:ref: sormtr_ 14 16 13 13 13 4 4 6 4 6 6 4 6 4 4 124 124 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int ssygs2_(integer *itype, char *uplo, integer *n, real *a, integer *lda, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: ssyr2_ 14 10 13 4 6 6 4 6 4 6 4 124 */
/*:ref: strsv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
/*:ref: strmv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
extern int ssygst_(integer *itype, char *uplo, integer *n, real *a, integer *lda, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: ssygs2_ 14 9 4 13 4 6 4 6 4 4 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: ssymm_ 14 14 13 13 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: ssyr2k_ 14 14 13 13 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: strmm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
extern int ssygv_(integer *itype, char *jobz, char *uplo, integer *n, real *a, integer *lda, real *b, integer *ldb, real *w, real *work, integer *lwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spotrf_ 14 6 13 4 6 4 4 124 */
/*:ref: ssygst_ 14 9 4 13 4 6 4 6 4 4 124 */
/*:ref: ssyev_ 14 11 13 13 4 6 4 6 6 4 4 124 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: strmm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
extern int ssygvd_(integer *itype, char *jobz, char *uplo, integer *n, real *a, integer *lda, real *b, integer *ldb, real *w, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spotrf_ 14 6 13 4 6 4 4 124 */
/*:ref: ssygst_ 14 9 4 13 4 6 4 6 4 4 124 */
/*:ref: ssyevd_ 14 13 13 13 4 6 4 6 6 4 4 4 4 124 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: strmm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
extern int ssygvx_(integer *itype, char *jobz, char *range, char *uplo, integer *n, real *a, integer *lda, real *b, integer *ldb, real *vl, real *vu, integer *il, integer *iu, real *abstol, integer *m, real *w, real *z__, integer *ldz, real *work, integer *lwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: spotrf_ 14 6 13 4 6 4 4 124 */
/*:ref: ssygst_ 14 9 4 13 4 6 4 6 4 4 124 */
/*:ref: ssyevx_ 14 23 13 13 13 4 6 4 6 6 4 4 6 4 6 6 4 6 4 4 4 4 124 124 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: strmm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
extern int ssyrfs_(char *uplo, integer *n, integer *nrhs, real *a, integer *lda, real *af, integer *ldaf, integer *ipiv, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssymv_ 14 11 13 4 6 6 4 6 4 6 6 4 124 */
/*:ref: ssytrs_ 14 10 13 4 4 6 4 4 6 4 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
extern int ssysv_(char *uplo, integer *n, integer *nrhs, real *a, integer *lda, integer *ipiv, real *b, integer *ldb, real *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ssytrf_ 14 9 13 4 6 4 4 6 4 4 124 */
/*:ref: ssytrs_ 14 10 13 4 4 6 4 4 6 4 4 124 */
extern int ssysvx_(char *fact, char *uplo, integer *n, integer *nrhs, real *a, integer *lda, real *af, integer *ldaf, integer *ipiv, real *b, integer *ldb, real *x, integer *ldx, real *rcond, real *ferr, real *berr, real *work, integer *lwork, integer *iwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: ssytrf_ 14 9 13 4 6 4 4 6 4 4 124 */
/*:ref: slansy_ 6 8 13 13 4 6 4 6 124 124 */
/*:ref: ssycon_ 14 11 13 4 6 4 4 6 6 6 4 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: ssytrs_ 14 10 13 4 4 6 4 4 6 4 4 124 */
/*:ref: ssyrfs_ 14 18 13 4 4 6 4 6 4 4 6 4 6 4 6 6 6 4 4 124 */
extern int ssytd2_(char *uplo, integer *n, real *a, integer *lda, real *d__, real *e, real *tau, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: ssymv_ 14 11 13 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: ssyr2_ 14 10 13 4 6 6 4 6 4 6 4 124 */
extern int ssytf2_(char *uplo, integer *n, real *a, integer *lda, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: ssyr_ 14 8 13 4 6 6 4 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int ssytrd_(char *uplo, integer *n, real *a, integer *lda, real *d__, real *e, real *tau, real *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slatrd_ 14 10 13 4 4 6 4 6 6 6 4 124 */
/*:ref: ssyr2k_ 14 14 13 13 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: ssytd2_ 14 9 13 4 6 4 6 6 6 4 124 */
extern int ssytrf_(char *uplo, integer *n, real *a, integer *lda, integer *ipiv, real *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slasyf_ 14 11 13 4 4 4 6 4 4 6 4 4 124 */
/*:ref: ssytf2_ 14 7 13 4 6 4 4 4 124 */
extern int ssytri_(char *uplo, integer *n, real *a, integer *lda, integer *ipiv, real *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: ssymv_ 14 11 13 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
extern int ssytrs_(char *uplo, integer *n, integer *nrhs, real *a, integer *lda, integer *ipiv, real *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sswap_ 14 5 4 6 4 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
extern int stbcon_(char *norm, char *uplo, char *diag, integer *n, integer *kd, real *ab, integer *ldab, real *rcond, real *work, integer *iwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slantb_ 6 11 13 13 13 4 4 6 4 6 124 124 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: slatbs_ 14 16 13 13 13 13 4 4 6 4 6 6 6 4 124 124 124 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: srscl_ 14 4 4 6 6 4 */
extern int stbrfs_(char *uplo, char *trans, char *diag, integer *n, integer *kd, integer *nrhs, real *ab, integer *ldab, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: stbmv_ 14 12 13 13 13 4 4 6 4 6 4 124 124 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: stbsv_ 14 12 13 13 13 4 4 6 4 6 4 124 124 124 */
extern int stbtrs_(char *uplo, char *trans, char *diag, integer *n, integer *kd, integer *nrhs, real *ab, integer *ldab, real *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: stbsv_ 14 12 13 13 13 4 4 6 4 6 4 124 124 124 */
extern int stgevc_(char *side, char *howmny, logical *select, integer *n, real *a, integer *lda, real *b, integer *ldb, real *vl, integer *ldvl, real *vr, integer *ldvr, integer *mm, integer *m, real *work, integer *info, ftnlen side_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slag2_ 14 10 6 4 6 4 6 6 6 6 6 6 */
/*:ref: slaln2_ 14 18 12 4 4 6 6 6 4 6 6 6 4 6 6 6 4 6 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
extern int stgex2_(logical *wantq, logical *wantz, integer *n, real *a, integer *lda, real *b, integer *ldb, real *q, integer *ldq, real *z__, integer *ldz, integer *j1, integer *n1, integer *n2, real *work, integer *lwork, integer *info);
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
/*:ref: stgsy2_ 14 23 13 4 4 4 6 4 6 4 6 4 6 4 6 4 6 4 6 6 6 4 4 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sgeqr2_ 14 7 4 4 6 4 6 6 4 */
/*:ref: sorg2r_ 14 8 4 4 4 6 4 6 6 4 */
/*:ref: sgerq2_ 14 7 4 4 6 4 6 6 4 */
/*:ref: sorgr2_ 14 8 4 4 4 6 4 6 6 4 */
/*:ref: sormr2_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: sorm2r_ 14 14 13 13 4 4 4 6 4 6 6 4 6 4 124 124 */
/*:ref: slagv2_ 14 11 6 4 6 4 6 6 6 6 6 6 6 */
extern int stgexc_(logical *wantq, logical *wantz, integer *n, real *a, integer *lda, real *b, integer *ldb, real *q, integer *ldq, real *z__, integer *ldz, integer *ifst, integer *ilst, real *work, integer *lwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: stgex2_ 14 17 12 12 4 6 4 6 4 6 4 6 4 4 4 4 6 4 4 */
extern int stgsen_(integer *ijob, logical *wantq, logical *wantz, logical *select, integer *n, real *a, integer *lda, real *b, integer *ldb, real *alphar, real *alphai, real *beta, real *q, integer *ldq, real *z__, integer *ldz, integer *m, real *pl, real *pr, real *dif, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slassq_ 14 5 4 6 4 6 6 */
/*:ref: stgexc_ 14 16 12 12 4 6 4 6 4 6 4 6 4 4 4 6 4 4 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: stgsyl_ 14 23 13 4 4 4 6 4 6 4 6 4 6 4 6 4 6 4 6 6 6 4 4 4 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: slag2_ 14 10 6 4 6 4 6 6 6 6 6 6 */
extern int stgsja_(char *jobu, char *jobv, char *jobq, integer *m, integer *p, integer *n, integer *k, integer *l, real *a, integer *lda, real *b, integer *ldb, real *tola, real *tolb, real *alpha, real *beta, real *u, integer *ldu, real *v, integer *ldv, real *q, integer *ldq, real *work, integer *ncycle, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaset_ 14 8 13 4 4 6 6 6 4 124 */
/*:ref: slags2_ 14 13 12 6 6 6 6 6 6 6 6 6 6 6 6 */
/*:ref: srot_ 14 7 4 6 4 6 4 6 6 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: slapll_ 14 6 4 6 4 6 4 6 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slartg_ 14 5 6 6 6 6 6 */
extern int stgsna_(char *job, char *howmny, logical *select, integer *n, real *a, integer *lda, real *b, integer *ldb, real *vl, integer *ldvl, real *vr, integer *ldvr, real *s, real *dif, integer *mm, integer *m, real *work, integer *lwork, integer *iwork, integer *info, ftnlen job_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: slag2_ 14 10 6 4 6 4 6 6 6 6 6 6 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: stgexc_ 14 16 12 12 4 6 4 6 4 6 4 6 4 4 4 6 4 4 */
/*:ref: stgsyl_ 14 23 13 4 4 4 6 4 6 4 6 4 6 4 6 4 6 4 6 6 6 4 4 4 124 */
extern int stgsy2_(char *trans, integer *ijob, integer *m, integer *n, real *a, integer *lda, real *b, integer *ldb, real *c__, integer *ldc, real *d__, integer *ldd, real *e, integer *lde, real *f, integer *ldf, real *scale, real *rdsum, real *rdscal, integer *iwork, integer *pq, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: sgetc2_ 14 6 4 6 4 4 4 4 */
/*:ref: sgesc2_ 14 7 4 6 4 6 4 4 6 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slatdf_ 14 9 4 4 6 4 6 6 6 4 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
extern int stgsyl_(char *trans, integer *ijob, integer *m, integer *n, real *a, integer *lda, real *b, integer *ldb, real *c__, integer *ldc, real *d__, integer *ldd, real *e, integer *lde, real *f, integer *ldf, real *scale, real *dif, real *work, integer *lwork, integer *iwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: stgsy2_ 14 23 13 4 4 4 6 4 6 4 6 4 6 4 6 4 6 4 6 6 6 4 4 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: sgemm_ 14 15 13 13 4 4 4 6 6 4 6 4 6 6 4 124 124 */
extern int stpcon_(char *norm, char *uplo, char *diag, integer *n, real *ap, real *rcond, real *work, integer *iwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slantp_ 6 9 13 13 13 4 6 6 124 124 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: slatps_ 14 14 13 13 13 13 4 6 6 6 6 4 124 124 124 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: srscl_ 14 4 4 6 6 4 */
extern int stprfs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, real *ap, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: stpmv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: stpsv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
extern int stptri_(char *uplo, char *diag, integer *n, real *ap, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: stpmv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int stptrs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, real *ap, real *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: stpsv_ 14 10 13 13 13 4 6 6 4 124 124 124 */
extern int strcon_(char *norm, char *uplo, char *diag, integer *n, real *a, integer *lda, real *rcond, real *work, integer *iwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slantr_ 6 11 13 13 13 4 4 6 4 6 124 124 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: slatrs_ 14 15 13 13 13 13 4 6 4 6 6 6 4 124 124 124 124 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: srscl_ 14 4 4 6 6 4 */
extern int strevc_(char *side, char *howmny, logical *select, integer *n, real *t, integer *ldt, real *vl, integer *ldvl, real *vr, integer *ldvr, integer *mm, integer *m, real *work, integer *info, ftnlen side_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slaln2_ 14 18 12 4 4 6 6 6 4 6 6 6 4 6 6 6 4 6 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: isamax_ 4 3 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
extern int strexc_(char *compq, integer *n, real *t, integer *ldt, real *q, integer *ldq, integer *ifst, integer *ilst, real *work, integer *info, ftnlen compq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slaexc_ 14 11 12 4 6 4 6 4 4 4 4 6 4 */
extern int strrfs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, real *a, integer *lda, real *b, integer *ldb, real *x, integer *ldx, real *ferr, real *berr, real *work, integer *iwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: strmv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: strsv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
extern int strsen_(char *job, char *compq, logical *select, integer *n, real *t, integer *ldt, real *q, integer *ldq, real *wr, real *wi, integer *m, real *s, real *sep, real *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen job_len, ftnlen compq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: strexc_ 14 11 13 4 6 4 6 4 4 4 6 4 124 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: strsyl_ 14 15 13 13 4 4 4 6 4 6 4 6 4 6 4 124 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
extern int strsna_(char *job, char *howmny, logical *select, integer *n, real *t, integer *ldt, real *vl, integer *ldvl, real *vr, integer *ldvr, real *s, real *sep, integer *mm, integer *m, real *work, integer *ldwork, integer *iwork, integer *info, ftnlen job_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: snrm2_ 6 3 4 6 4 */
/*:ref: slapy2_ 6 2 6 6 */
/*:ref: slacpy_ 14 8 13 4 4 6 4 6 4 124 */
/*:ref: strexc_ 14 11 13 4 6 4 6 4 4 4 6 4 124 */
/*:ref: slacon_ 14 6 4 6 6 4 6 4 */
/*:ref: slaqtr_ 14 11 12 12 4 6 4 6 6 6 6 6 4 */
extern int strsyl_(char *trana, char *tranb, integer *isgn, integer *m, integer *n, real *a, integer *lda, real *b, integer *ldb, real *c__, integer *ldc, real *scale, integer *info, ftnlen trana_len, ftnlen tranb_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slamch_ 6 2 13 124 */
/*:ref: slabad_ 14 2 6 6 */
/*:ref: slange_ 6 7 13 4 4 6 4 6 124 */
/*:ref: sdot_ 6 5 4 6 4 6 4 */
/*:ref: sscal_ 14 4 4 6 6 4 */
/*:ref: slaln2_ 14 18 12 4 4 6 6 6 4 6 6 6 4 6 6 6 4 6 6 4 */
/*:ref: slasy2_ 14 16 12 12 4 4 4 6 4 6 4 6 4 6 6 4 6 4 */
extern int strti2_(char *uplo, char *diag, integer *n, real *a, integer *lda, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: strmv_ 14 11 13 13 13 4 6 4 6 4 124 124 124 */
/*:ref: sscal_ 14 4 4 6 6 4 */
extern int strtri_(char *uplo, char *diag, integer *n, real *a, integer *lda, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: strti2_ 14 8 13 13 4 6 4 4 124 124 */
/*:ref: strmm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
extern int strtrs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, real *a, integer *lda, real *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: strsm_ 14 15 13 13 13 13 4 4 6 6 4 6 4 124 124 124 124 */
extern int stzrqf_(integer *m, integer *n, real *a, integer *lda, real *tau, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slarfg_ 14 5 4 6 6 4 6 */
/*:ref: scopy_ 14 5 4 6 4 6 4 */
/*:ref: sgemv_ 14 12 13 4 4 6 6 4 6 4 6 6 4 124 */
/*:ref: saxpy_ 14 6 4 6 6 4 6 4 */
/*:ref: sger_ 14 9 4 4 6 6 4 6 4 6 4 */
extern int stzrzf_(integer *m, integer *n, real *a, integer *lda, real *tau, real *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: slatrz_ 14 7 4 4 4 6 4 6 6 */
/*:ref: slarzt_ 14 11 13 13 4 4 6 4 6 6 4 124 124 */
/*:ref: slarzb_ 14 20 13 13 13 13 4 4 4 4 6 4 6 4 6 4 6 4 124 124 124 124 */
extern int xerbla_(char *srname, integer *info, ftnlen srname_len);
extern int zbdsqr_(char *uplo, integer *n, integer *ncvt, integer *nru, integer *ncc, doublereal *d__, doublereal *e, doublecomplex *vt, integer *ldvt, doublecomplex *u, integer *ldu, doublecomplex *c__, integer *ldc, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlasq1_ 14 5 4 7 7 7 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: zlasr_ 14 12 13 13 13 4 4 7 7 9 4 124 124 124 */
/*:ref: dlasv2_ 14 9 7 7 7 7 7 7 7 7 7 */
/*:ref: zdrot_ 14 7 4 9 4 9 4 7 7 */
/*:ref: dlas2_ 14 5 7 7 7 7 7 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zdrot_(integer *n, doublecomplex *cx, integer *incx, doublecomplex *cy, integer *incy, doublereal *c__, doublereal *s);
extern int zdrscl_(integer *n, doublereal *sa, doublecomplex *sx, integer *incx);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
extern int zgbbrd_(char *vect, integer *m, integer *n, integer *ncc, integer *kl, integer *ku, doublecomplex *ab, integer *ldab, doublereal *d__, doublereal *e, doublecomplex *q, integer *ldq, doublecomplex *pt, integer *ldpt, doublecomplex *c__, integer *ldc, doublecomplex *work, doublereal *rwork, integer *info, ftnlen vect_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlargv_ 14 7 4 9 4 9 4 7 4 */
/*:ref: zlartv_ 14 8 4 9 4 9 4 7 9 4 */
/*:ref: zlartg_ 14 5 9 9 7 9 9 */
/*:ref: zrot_ 14 7 4 9 4 9 4 7 9 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zgbcon_(char *norm, integer *n, integer *kl, integer *ku, doublecomplex *ab, integer *ldab, integer *ipiv, doublereal *anorm, doublereal *rcond, doublecomplex *work, doublereal *rwork, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlatbs_ 14 16 13 13 13 13 4 4 9 4 9 7 7 4 124 124 124 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdrscl_ 14 4 4 7 9 4 */
extern int zgbequ_(integer *m, integer *n, integer *kl, integer *ku, doublecomplex *ab, integer *ldab, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal *colcnd, doublereal *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
extern int zgbrfs_(char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, doublecomplex *ab, integer *ldab, doublecomplex *afb, integer *ldafb, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgbmv_ 14 14 13 4 4 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zgbtrs_ 14 12 13 4 4 4 4 9 4 4 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int zgbsv_(integer *n, integer *kl, integer *ku, integer *nrhs, doublecomplex *ab, integer *ldab, integer *ipiv, doublecomplex *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgbtrf_ 14 8 4 4 4 4 9 4 4 4 */
/*:ref: zgbtrs_ 14 12 13 4 4 4 4 9 4 4 9 4 4 124 */
extern int zgbsvx_(char *fact, char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, doublecomplex *ab, integer *ldab, doublecomplex *afb, integer *ldafb, integer *ipiv, char *equed, doublereal *r__, doublereal *c__, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen fact_len, ftnlen trans_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgbequ_ 14 12 4 4 4 4 9 4 7 7 7 7 7 4 */
/*:ref: zlaqgb_ 14 13 4 4 4 4 9 4 7 7 7 7 7 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgbtrf_ 14 8 4 4 4 4 9 4 4 4 */
/*:ref: zlantb_ 7 11 13 13 13 4 4 9 4 7 124 124 124 */
/*:ref: zlangb_ 7 8 13 4 4 4 9 4 7 124 */
/*:ref: zgbcon_ 14 13 13 4 4 4 9 4 4 7 7 9 7 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zgbtrs_ 14 12 13 4 4 4 4 9 4 4 9 4 4 124 */
/*:ref: zgbrfs_ 14 20 13 4 4 4 4 9 4 9 4 4 9 4 9 4 7 7 9 7 4 124 */
extern int zgbtf2_(integer *m, integer *n, integer *kl, integer *ku, doublecomplex *ab, integer *ldab, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
extern int zgbtrf_(integer *m, integer *n, integer *kl, integer *ku, doublecomplex *ab, integer *ldab, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: zgbtf2_ 14 8 4 4 4 4 9 4 4 4 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlaswp_ 14 7 4 9 4 4 4 4 4 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
extern int zgbtrs_(char *trans, integer *n, integer *kl, integer *ku, integer *nrhs, doublecomplex *ab, integer *ldab, integer *ipiv, doublecomplex *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
/*:ref: ztbsv_ 14 12 13 13 13 4 4 9 4 9 4 124 124 124 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
extern int zgebak_(char *job, char *side, integer *n, integer *ilo, integer *ihi, doublereal *scale, integer *m, doublecomplex *v, integer *ldv, integer *info, ftnlen job_len, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zgebal_(char *job, integer *n, doublecomplex *a, integer *lda, integer *ilo, integer *ihi, doublereal *scale, integer *info, ftnlen job_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
extern int zgebd2_(integer *m, integer *n, doublecomplex *a, integer *lda, doublereal *d__, doublereal *e, doublecomplex *tauq, doublecomplex *taup, doublecomplex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
extern int zgebrd_(integer *m, integer *n, doublecomplex *a, integer *lda, doublereal *d__, doublereal *e, doublecomplex *tauq, doublecomplex *taup, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlabrd_ 14 13 4 4 4 9 4 7 7 9 9 9 4 9 4 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: zgebd2_ 14 10 4 4 9 4 7 7 9 9 9 4 */
extern int zgecon_(char *norm, integer *n, doublecomplex *a, integer *lda, doublereal *anorm, doublereal *rcond, doublecomplex *work, doublereal *rwork, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zlatrs_ 14 15 13 13 13 13 4 9 4 9 7 7 4 124 124 124 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdrscl_ 14 4 4 7 9 4 */
extern int zgeequ_(integer *m, integer *n, doublecomplex *a, integer *lda, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal *colcnd, doublereal *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
extern int zgees_(char *jobvs, char *sort, L_fp select, integer *n, doublecomplex *a, integer *lda, integer *sdim, doublecomplex *w, doublecomplex *vs, integer *ldvs, doublecomplex *work, integer *lwork, doublereal *rwork, logical *bwork, integer *info, ftnlen jobvs_len, ftnlen sort_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zgebal_ 14 9 13 4 9 4 4 4 7 4 124 */
/*:ref: zgehrd_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zunghr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zhseqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: ztrsen_ 14 17 13 13 12 4 9 4 9 4 9 4 7 7 9 4 4 124 124 */
/*:ref: zgebak_ 14 12 13 13 4 4 4 7 4 9 4 4 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
extern int zgeesx_(char *jobvs, char *sort, L_fp select, char *sense, integer *n, doublecomplex *a, integer *lda, integer *sdim, doublecomplex *w, doublecomplex *vs, integer *ldvs, doublereal *rconde, doublereal *rcondv, doublecomplex *work, integer *lwork, doublereal *rwork, logical *bwork, integer *info, ftnlen jobvs_len, ftnlen sort_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zgebal_ 14 9 13 4 9 4 4 4 7 4 124 */
/*:ref: zgehrd_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zunghr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zhseqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: ztrsen_ 14 17 13 13 12 4 9 4 9 4 9 4 7 7 9 4 4 124 124 */
/*:ref: zgebak_ 14 12 13 13 4 4 4 7 4 9 4 4 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
extern int zgeev_(char *jobvl, char *jobvr, integer *n, doublecomplex *a, integer *lda, doublecomplex *w, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zgebal_ 14 9 13 4 9 4 4 4 7 4 124 */
/*:ref: zgehrd_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zunghr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zhseqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: ztrevc_ 14 17 13 13 12 4 9 4 9 4 9 4 4 4 9 7 4 124 124 */
/*:ref: zgebak_ 14 12 13 13 4 4 4 7 4 9 4 4 124 124 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zgeevx_(char *balanc, char *jobvl, char *jobvr, char *sense, integer *n, doublecomplex *a, integer *lda, doublecomplex *w, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, integer *ilo, integer *ihi, doublereal *scale, doublereal *abnrm, doublereal *rconde, doublereal *rcondv, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen balanc_len, ftnlen jobvl_len, ftnlen jobvr_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zgebal_ 14 9 13 4 9 4 4 4 7 4 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: zgehrd_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zunghr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zhseqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: ztrevc_ 14 17 13 13 12 4 9 4 9 4 9 4 4 4 9 7 4 124 124 */
/*:ref: ztrsna_ 14 20 13 13 12 4 9 4 9 4 9 4 7 7 4 4 9 4 7 4 124 124 */
/*:ref: zgebak_ 14 12 13 13 4 4 4 7 4 9 4 4 124 124 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zgegs_(char *jobvsl, char *jobvsr, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *alpha, doublecomplex *beta, doublecomplex *vsl, integer *ldvsl, doublecomplex *vsr, integer *ldvsr, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zggbal_ 14 13 13 4 9 4 9 4 4 4 7 7 7 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zgghrd_ 14 16 13 13 4 4 4 9 4 9 4 9 4 9 4 4 124 124 */
/*:ref: zhgeqz_ 14 23 13 13 13 4 4 4 9 4 9 4 9 9 9 4 9 4 9 4 7 4 124 124 124 */
/*:ref: zggbak_ 14 13 13 13 4 4 4 7 7 4 9 4 4 124 124 */
extern int zgegv_(char *jobvl, char *jobvr, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *alpha, doublecomplex *beta, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zggbal_ 14 13 13 4 9 4 9 4 4 4 7 7 7 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zgghrd_ 14 16 13 13 4 4 4 9 4 9 4 9 4 9 4 4 124 124 */
/*:ref: zhgeqz_ 14 23 13 13 13 4 4 4 9 4 9 4 9 9 9 4 9 4 9 4 7 4 124 124 124 */
/*:ref: ztgevc_ 14 19 13 13 12 4 9 4 9 4 9 4 9 4 4 4 9 7 4 124 124 */
/*:ref: zggbak_ 14 13 13 13 4 4 4 7 7 4 9 4 4 124 124 */
extern int zgehd2_(integer *n, integer *ilo, integer *ihi, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
extern int zgehrd_(integer *n, integer *ilo, integer *ihi, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlahrd_ 14 10 4 4 4 9 4 9 9 4 9 4 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
/*:ref: zgehd2_ 14 8 4 4 4 9 4 9 9 4 */
extern int zgelq2_(integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
extern int zgelqf_(integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgelq2_ 14 7 4 4 9 4 9 9 4 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zgels_(char *trans, integer *m, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *work, integer *lwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zgelqf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmlq_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
extern int zgelsd_(integer *m, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublereal *s, doublereal *rcond, integer *rank, doublecomplex *work, integer *lwork, doublereal *rwork, integer *iwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zgebrd_ 14 11 4 4 9 4 7 7 9 9 9 4 4 */
/*:ref: zunmbr_ 14 17 13 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 124 */
/*:ref: zlalsd_ 14 15 13 4 4 4 7 7 9 4 7 4 9 7 4 4 124 */
/*:ref: zgelqf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zunmlq_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
extern int zgelss_(integer *m, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublereal *s, doublereal *rcond, integer *rank, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zgebrd_ 14 11 4 4 9 4 7 7 9 9 9 4 4 */
/*:ref: zunmbr_ 14 17 13 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 124 */
/*:ref: zungbr_ 14 11 13 4 4 4 9 4 9 9 4 4 124 */
/*:ref: zbdsqr_ 14 16 13 4 4 4 4 7 7 9 4 9 4 9 4 7 4 124 */
/*:ref: zdrscl_ 14 4 4 7 9 4 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgelqf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmlq_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
extern int zgelsx_(integer *m, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, integer *jpvt, doublereal *rcond, integer *rank, doublecomplex *work, doublereal *rwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zgeqpf_ 14 9 4 4 9 4 4 9 9 7 4 */
/*:ref: zlaic1_ 14 9 4 4 9 7 9 9 7 9 9 */
/*:ref: ztzrqf_ 14 6 4 4 9 4 9 4 */
/*:ref: zunm2r_ 14 14 13 13 4 4 4 9 4 9 9 4 9 4 124 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zlatzm_ 14 11 13 4 4 9 4 9 9 9 4 9 124 */
extern int zgelsy_(integer *m, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, integer *jpvt, doublereal *rcond, integer *rank, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zgeqp3_ 14 10 4 4 9 4 4 9 9 4 7 4 */
/*:ref: zlaic1_ 14 9 4 4 9 7 9 9 7 9 9 */
/*:ref: ztzrzf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zunmrz_ 14 16 13 13 4 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
extern int zgeql2_(integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
extern int zgeqlf_(integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgeql2_ 14 7 4 4 9 4 9 9 4 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zgeqp3_(integer *m, integer *n, doublecomplex *a, integer *lda, integer *jpvt, doublecomplex *tau, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zlaqps_ 14 14 4 4 4 4 4 9 4 4 9 7 7 9 9 4 */
/*:ref: zlaqp2_ 14 10 4 4 4 9 4 4 9 7 7 9 */
extern int zgeqpf_(integer *m, integer *n, doublecomplex *a, integer *lda, integer *jpvt, doublecomplex *tau, doublecomplex *work, doublereal *rwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zgeqr2_ 14 7 4 4 9 4 9 9 4 */
/*:ref: zunm2r_ 14 14 13 13 4 4 4 9 4 9 9 4 9 4 124 124 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
extern int zgeqr2_(integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
extern int zgeqrf_(integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgeqr2_ 14 7 4 4 9 4 9 9 4 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zgerfs_(char *trans, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zgetrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int zgerq2_(integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
extern int zgerqf_(integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgerq2_ 14 7 4 4 9 4 9 9 4 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zgesc2_(integer *n, doublecomplex *a, integer *lda, doublecomplex *rhs, integer *ipiv, integer *jpiv, doublereal *scale);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlaswp_ 14 7 4 9 4 4 4 4 4 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zgesdd_(char *jobz, integer *m, integer *n, doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u, integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work, integer *lwork, doublereal *rwork, integer *iwork, integer *info, ftnlen jobz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zgebrd_ 14 11 4 4 9 4 7 7 9 9 9 4 4 */
/*:ref: dbdsdc_ 14 16 13 13 4 7 7 7 4 7 4 7 4 7 4 4 124 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zlacp2_ 14 8 13 4 4 7 4 9 4 124 */
/*:ref: zunmbr_ 14 17 13 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 124 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: zungbr_ 14 11 13 4 4 4 9 4 9 9 4 4 124 */
/*:ref: zlarcm_ 14 9 4 4 7 4 9 4 9 4 7 */
/*:ref: zlacrm_ 14 9 4 4 9 4 7 4 9 4 7 */
/*:ref: zgelqf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunglq_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
extern int zgesv_(integer *n, integer *nrhs, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgetrf_ 14 6 4 4 9 4 4 4 */
/*:ref: zgetrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
extern int zgesvd_(char *jobu, char *jobvt, integer *m, integer *n, doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u, integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen jobu_len, ftnlen jobvt_len);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zgebrd_ 14 11 4 4 9 4 7 7 9 9 9 4 4 */
/*:ref: zungbr_ 14 11 13 4 4 4 9 4 9 9 4 4 124 */
/*:ref: zbdsqr_ 14 16 13 4 4 4 4 7 7 9 4 9 4 9 4 7 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: zunmbr_ 14 17 13 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 124 */
/*:ref: zgelqf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunglq_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
extern int zgesvx_(char *fact, char *trans, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, integer *ipiv, char *equed, doublereal *r__, doublereal *c__, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen fact_len, ftnlen trans_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgeequ_ 14 10 4 4 9 4 7 7 7 7 7 4 */
/*:ref: zlaqge_ 14 11 4 4 9 4 7 7 7 7 7 13 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zgetrf_ 14 6 4 4 9 4 4 4 */
/*:ref: zlantr_ 7 11 13 13 13 4 4 9 4 7 124 124 124 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zgecon_ 14 10 13 4 9 4 7 7 9 7 4 124 */
/*:ref: zgetrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
/*:ref: zgerfs_ 14 18 13 4 4 9 4 9 4 4 9 4 9 4 7 7 9 7 4 124 */
extern int zgetc2_(integer *n, doublecomplex *a, integer *lda, integer *ipiv, integer *jpiv, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
extern int zgetf2_(integer *m, integer *n, doublecomplex *a, integer *lda, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
extern int zgetrf_(integer *m, integer *n, doublecomplex *a, integer *lda, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: zgetf2_ 14 6 4 4 9 4 4 4 */
/*:ref: zlaswp_ 14 7 4 9 4 4 4 4 4 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
extern int zgetri_(integer *n, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztrtri_ 14 8 13 13 4 9 4 4 124 124 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zgetrs_(char *trans, integer *n, integer *nrhs, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlaswp_ 14 7 4 9 4 4 4 4 4 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
extern int zggbak_(char *job, char *side, integer *n, integer *ilo, integer *ihi, doublereal *lscale, doublereal *rscale, integer *m, doublecomplex *v, integer *ldv, integer *info, ftnlen job_len, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zggbal_(char *job, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, integer *ilo, integer *ihi, doublereal *lscale, doublereal *rscale, doublereal *work, integer *info, ftnlen job_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
extern int zgges_(char *jobvsl, char *jobvsr, char *sort, L_fp delctg, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, integer *sdim, doublecomplex *alpha, doublecomplex *beta, doublecomplex *vsl, integer *ldvsl, doublecomplex *vsr, integer *ldvsr, doublecomplex *work, integer *lwork, doublereal *rwork, logical *bwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len, ftnlen sort_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zggbal_ 14 13 13 4 9 4 9 4 4 4 7 7 7 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zgghrd_ 14 16 13 13 4 4 4 9 4 9 4 9 4 9 4 4 124 124 */
/*:ref: zhgeqz_ 14 23 13 13 13 4 4 4 9 4 9 4 9 9 9 4 9 4 9 4 7 4 124 124 124 */
/*:ref: ztgsen_ 14 24 4 12 12 12 4 9 4 9 4 9 9 9 4 9 4 4 7 7 7 9 4 4 4 4 */
/*:ref: zggbak_ 14 13 13 13 4 4 4 7 7 4 9 4 4 124 124 */
extern int zggesx_(char *jobvsl, char *jobvsr, char *sort, L_fp delctg, char *sense, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, integer *sdim, doublecomplex *alpha, doublecomplex *beta, doublecomplex *vsl, integer *ldvsl, doublecomplex *vsr, integer *ldvsr, doublereal *rconde, doublereal *rcondv, doublecomplex *work, integer *lwork, doublereal *rwork, integer *iwork, integer *liwork, logical *bwork, integer *info, ftnlen jobvsl_len, ftnlen jobvsr_len, ftnlen sort_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zggbal_ 14 13 13 4 9 4 9 4 4 4 7 7 7 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zgghrd_ 14 16 13 13 4 4 4 9 4 9 4 9 4 9 4 4 124 124 */
/*:ref: zhgeqz_ 14 23 13 13 13 4 4 4 9 4 9 4 9 9 9 4 9 4 9 4 7 4 124 124 124 */
/*:ref: ztgsen_ 14 24 4 12 12 12 4 9 4 9 4 9 9 9 4 9 4 4 7 7 7 9 4 4 4 4 */
/*:ref: zggbak_ 14 13 13 13 4 4 4 7 7 4 9 4 4 124 124 */
extern int zggev_(char *jobvl, char *jobvr, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *alpha, doublecomplex *beta, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen jobvl_len, ftnlen jobvr_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zggbal_ 14 13 13 4 9 4 9 4 4 4 7 7 7 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zgghrd_ 14 16 13 13 4 4 4 9 4 9 4 9 4 9 4 4 124 124 */
/*:ref: zhgeqz_ 14 23 13 13 13 4 4 4 9 4 9 4 9 9 9 4 9 4 9 4 7 4 124 124 124 */
/*:ref: ztgevc_ 14 19 13 13 12 4 9 4 9 4 9 4 9 4 4 4 9 7 4 124 124 */
/*:ref: zggbak_ 14 13 13 13 4 4 4 7 7 4 9 4 4 124 124 */
extern int zggevx_(char *balanc, char *jobvl, char *jobvr, char *sense, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *alpha, doublecomplex *beta, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, integer *ilo, integer *ihi, doublereal *lscale, doublereal *rscale, doublereal *abnrm, doublereal *bbnrm, doublereal *rconde, doublereal *rcondv, doublecomplex *work, integer *lwork, doublereal *rwork, integer *iwork, logical *bwork, integer *info, ftnlen balanc_len, ftnlen jobvl_len, ftnlen jobvr_len, ftnlen sense_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zggbal_ 14 13 13 4 9 4 9 4 4 4 7 7 7 4 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zgghrd_ 14 16 13 13 4 4 4 9 4 9 4 9 4 9 4 4 124 124 */
/*:ref: zhgeqz_ 14 23 13 13 13 4 4 4 9 4 9 4 9 9 9 4 9 4 9 4 7 4 124 124 124 */
/*:ref: ztgevc_ 14 19 13 13 12 4 9 4 9 4 9 4 9 4 4 4 9 7 4 124 124 */
/*:ref: ztgsna_ 14 22 13 13 12 4 9 4 9 4 9 4 9 4 7 7 4 4 9 4 4 4 124 124 */
/*:ref: zggbak_ 14 13 13 13 4 4 4 7 7 4 9 4 4 124 124 */
extern int zggglm_(integer *n, integer *m, integer *p, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *d__, doublecomplex *x, doublecomplex *y, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zggqrf_ 14 12 4 4 4 9 4 9 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: ztrsv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zunmrq_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
extern int zgghrd_(char *compq, char *compz, integer *n, integer *ilo, integer *ihi, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *q, integer *ldq, doublecomplex *z__, integer *ldz, integer *info, ftnlen compq_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlartg_ 14 5 9 9 7 9 9 */
/*:ref: zrot_ 14 7 4 9 4 9 4 7 9 */
extern int zgglse_(integer *m, integer *n, integer *p, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *c__, doublecomplex *d__, doublecomplex *x, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zggrqf_ 14 12 4 4 4 9 4 9 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: ztrsv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: ztrmv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zunmrq_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
extern int zggqrf_(integer *n, integer *m, integer *p, doublecomplex *a, integer *lda, doublecomplex *taua, doublecomplex *b, integer *ldb, doublecomplex *taub, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zgerqf_ 14 8 4 4 9 4 9 9 4 4 */
extern int zggrqf_(integer *m, integer *p, integer *n, doublecomplex *a, integer *lda, doublecomplex *taua, doublecomplex *b, integer *ldb, doublecomplex *taub, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgerqf_ 14 8 4 4 9 4 9 9 4 4 */
/*:ref: zunmrq_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zgeqrf_ 14 8 4 4 9 4 9 9 4 4 */
extern int zggsvd_(char *jobu, char *jobv, char *jobq, integer *m, integer *n, integer *p, integer *k, integer *l, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublereal *alpha, doublereal *beta, doublecomplex *u, integer *ldu, doublecomplex *v, integer *ldv, doublecomplex *q, integer *ldq, doublecomplex *work, doublereal *rwork, integer *iwork, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zggsvp_ 14 28 13 13 13 4 4 4 9 4 9 4 7 7 4 4 9 4 9 4 9 4 4 7 9 9 4 124 124 124 */
/*:ref: ztgsja_ 14 28 13 13 13 4 4 4 4 4 9 4 9 4 7 7 7 7 9 4 9 4 9 4 9 4 4 124 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
extern int zggsvp_(char *jobu, char *jobv, char *jobq, integer *m, integer *p, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublereal *tola, doublereal *tolb, integer *k, integer *l, doublecomplex *u, integer *ldu, doublecomplex *v, integer *ldv, doublecomplex *q, integer *ldq, integer *iwork, doublereal *rwork, doublecomplex *tau, doublecomplex *work, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgeqpf_ 14 9 4 4 9 4 4 9 9 7 4 */
/*:ref: zlapmt_ 14 6 12 4 4 9 4 4 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zung2r_ 14 8 4 4 4 9 4 9 9 4 */
/*:ref: zgerq2_ 14 7 4 4 9 4 9 9 4 */
/*:ref: zunmr2_ 14 14 13 13 4 4 4 9 4 9 9 4 9 4 124 124 */
/*:ref: zunm2r_ 14 14 13 13 4 4 4 9 4 9 9 4 9 4 124 124 */
/*:ref: zgeqr2_ 14 7 4 4 9 4 9 9 4 */
extern int zgtcon_(char *norm, integer *n, doublecomplex *dl, doublecomplex *d__, doublecomplex *du, doublecomplex *du2, integer *ipiv, doublereal *anorm, doublereal *rcond, doublecomplex *work, integer *info, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zgttrs_ 14 12 13 4 4 9 9 9 9 4 9 4 4 124 */
extern int zgtrfs_(char *trans, integer *n, integer *nrhs, doublecomplex *dl, doublecomplex *d__, doublecomplex *du, doublecomplex *dlf, doublecomplex *df, doublecomplex *duf, doublecomplex *du2, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlagtm_ 14 13 13 4 4 7 9 9 9 9 4 7 9 4 124 */
/*:ref: zgttrs_ 14 12 13 4 4 9 9 9 9 4 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int zgtsv_(integer *n, integer *nrhs, doublecomplex *dl, doublecomplex *d__, doublecomplex *du, doublecomplex *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zgtsvx_(char *fact, char *trans, integer *n, integer *nrhs, doublecomplex *dl, doublecomplex *d__, doublecomplex *du, doublecomplex *dlf, doublecomplex *df, doublecomplex *duf, doublecomplex *du2, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen fact_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgttrf_ 14 7 4 9 9 9 9 4 4 */
/*:ref: zlangt_ 7 6 13 4 9 9 9 124 */
/*:ref: zgtcon_ 14 12 13 4 9 9 9 9 4 7 7 9 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zgttrs_ 14 12 13 4 4 9 9 9 9 4 9 4 4 124 */
/*:ref: zgtrfs_ 14 21 13 4 4 9 9 9 9 9 9 9 4 9 4 9 4 7 7 9 7 4 124 */
extern int zgttrf_(integer *n, doublecomplex *dl, doublecomplex *d__, doublecomplex *du, doublecomplex *du2, integer *ipiv, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zgttrs_(char *trans, integer *n, integer *nrhs, doublecomplex *dl, doublecomplex *d__, doublecomplex *du, doublecomplex *du2, integer *ipiv, doublecomplex *b, integer *ldb, integer *info, ftnlen trans_len);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: zgtts2_ 14 10 4 4 4 9 9 9 9 4 9 4 */
extern int zgtts2_(integer *itrans, integer *n, integer *nrhs, doublecomplex *dl, doublecomplex *d__, doublecomplex *du, doublecomplex *du2, integer *ipiv, doublecomplex *b, integer *ldb);
extern int zhbev_(char *jobz, char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, doublereal *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhb_ 7 9 13 13 4 4 9 4 7 124 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zhbtrd_ 14 14 13 13 4 4 9 4 7 7 9 4 9 4 124 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zsteqr_ 14 9 13 4 7 7 9 4 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int zhbevd_(char *jobz, char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork, doublereal *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhb_ 7 9 13 13 4 4 9 4 7 124 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zhbtrd_ 14 14 13 13 4 4 9 4 7 7 9 4 9 4 124 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zstedc_ 14 14 13 4 7 7 9 4 9 4 7 4 4 4 4 124 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int zhbevx_(char *jobz, char *range, char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, doublecomplex *q, integer *ldq, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, doublereal *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhb_ 7 9 13 13 4 4 9 4 7 124 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zhbtrd_ 14 14 13 13 4 4 9 4 7 7 9 4 9 4 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zsteqr_ 14 9 13 4 7 7 9 4 7 4 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: zstein_ 14 13 4 7 7 4 7 4 4 9 4 7 4 4 4 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zhbgst_(char *vect, char *uplo, integer *n, integer *ka, integer *kb, doublecomplex *ab, integer *ldab, doublecomplex *bb, integer *ldbb, doublecomplex *x, integer *ldx, doublecomplex *work, doublereal *rwork, integer *info, ftnlen vect_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zgerc_ 14 9 4 4 9 9 4 9 4 9 4 */
/*:ref: zlartg_ 14 5 9 9 7 9 9 */
/*:ref: zlargv_ 14 7 4 9 4 9 4 7 4 */
/*:ref: zlartv_ 14 8 4 9 4 9 4 7 9 4 */
/*:ref: zlar2v_ 14 8 4 9 9 9 4 7 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zrot_ 14 7 4 9 4 9 4 7 9 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
extern int zhbgv_(char *jobz, char *uplo, integer *n, integer *ka, integer *kb, doublecomplex *ab, integer *ldab, doublecomplex *bb, integer *ldbb, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, doublereal *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpbstf_ 14 7 13 4 4 9 4 4 124 */
/*:ref: zhbgst_ 14 16 13 13 4 4 4 9 4 9 4 9 4 9 7 4 124 124 */
/*:ref: zhbtrd_ 14 14 13 13 4 4 9 4 7 7 9 4 9 4 124 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zsteqr_ 14 9 13 4 7 7 9 4 7 4 124 */
extern int zhbgvd_(char *jobz, char *uplo, integer *n, integer *ka, integer *kb, doublecomplex *ab, integer *ldab, doublecomplex *bb, integer *ldbb, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork, doublereal *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpbstf_ 14 7 13 4 4 9 4 4 124 */
/*:ref: zhbgst_ 14 16 13 13 4 4 4 9 4 9 4 9 4 9 7 4 124 124 */
/*:ref: zhbtrd_ 14 14 13 13 4 4 9 4 7 7 9 4 9 4 124 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zstedc_ 14 14 13 4 7 7 9 4 9 4 7 4 4 4 4 124 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
extern int zhbgvx_(char *jobz, char *range, char *uplo, integer *n, integer *ka, integer *kb, doublecomplex *ab, integer *ldab, doublecomplex *bb, integer *ldbb, doublecomplex *q, integer *ldq, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, doublereal *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpbstf_ 14 7 13 4 4 9 4 4 124 */
/*:ref: zhbgst_ 14 16 13 13 4 4 4 9 4 9 4 9 4 9 7 4 124 124 */
/*:ref: zhbtrd_ 14 14 13 13 4 4 9 4 7 7 9 4 9 4 124 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zsteqr_ 14 9 13 4 7 7 9 4 7 4 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: zstein_ 14 13 4 7 7 4 7 4 4 9 4 7 4 4 4 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zhbtrd_(char *vect, char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, doublereal *d__, doublereal *e, doublecomplex *q, integer *ldq, doublecomplex *work, integer *info, ftnlen vect_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlargv_ 14 7 4 9 4 9 4 7 4 */
/*:ref: zlartv_ 14 8 4 9 4 9 4 7 9 4 */
/*:ref: zrot_ 14 7 4 9 4 9 4 7 9 */
/*:ref: zlartg_ 14 5 9 9 7 9 9 */
/*:ref: zlar2v_ 14 8 4 9 9 9 4 7 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zhecon_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *ipiv, doublereal *anorm, doublereal *rcond, doublecomplex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zhetrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
extern int zheev_(char *jobz, char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *w, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhe_ 7 8 13 13 4 9 4 7 124 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zhetrd_ 14 11 13 4 9 4 7 7 9 9 4 4 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zungtr_ 14 9 13 4 9 4 9 9 4 4 124 */
/*:ref: zsteqr_ 14 9 13 4 7 7 9 4 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int zheevd_(char *jobz, char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *w, doublecomplex *work, integer *lwork, doublereal *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhe_ 7 8 13 13 4 9 4 7 124 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zhetrd_ 14 11 13 4 9 4 7 7 9 9 4 4 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zstedc_ 14 14 13 4 7 7 9 4 9 4 7 4 4 4 4 124 */
/*:ref: zunmtr_ 14 16 13 13 13 4 4 9 4 9 9 4 9 4 4 124 124 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int zheevr_(char *jobz, char *range, char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublecomplex *z__, integer *ldz, integer *isuppz, doublecomplex *work, integer *lwork, doublereal *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlansy_ 7 8 13 13 4 9 4 7 124 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zhetrd_ 14 11 13 4 9 4 7 7 9 9 4 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zstegr_ 14 22 13 13 4 7 7 7 7 4 4 7 4 7 9 4 4 7 4 4 4 4 124 124 */
/*:ref: zunmtr_ 14 16 13 13 13 4 4 9 4 9 9 4 9 4 4 124 124 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: zstein_ 14 13 4 7 7 4 7 4 4 9 4 7 4 4 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zheevx_(char *jobz, char *range, char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork, doublereal *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhe_ 7 8 13 13 4 9 4 7 124 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zhetrd_ 14 11 13 4 9 4 7 7 9 9 4 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zungtr_ 14 9 13 4 9 4 9 9 4 4 124 */
/*:ref: zsteqr_ 14 9 13 4 7 7 9 4 7 4 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: zstein_ 14 13 4 7 7 4 7 4 4 9 4 7 4 4 4 */
/*:ref: zunmtr_ 14 16 13 13 13 4 4 9 4 9 9 4 9 4 4 124 124 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zhegs2_(integer *itype, char *uplo, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zher2_ 14 10 13 4 9 9 4 9 4 9 4 124 */
/*:ref: ztrsv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
/*:ref: ztrmv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
extern int zhegst_(integer *itype, char *uplo, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: zhegs2_ 14 9 4 13 4 9 4 9 4 4 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zhemm_ 14 14 13 13 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: zher2k_ 14 14 13 13 4 4 9 9 4 9 4 7 9 4 124 124 */
/*:ref: ztrmm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
extern int zhegv_(integer *itype, char *jobz, char *uplo, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublereal *w, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpotrf_ 14 6 13 4 9 4 4 124 */
/*:ref: zhegst_ 14 9 4 13 4 9 4 9 4 4 124 */
/*:ref: zheev_ 14 12 13 13 4 9 4 7 9 4 7 4 124 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: ztrmm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
extern int zhegvd_(integer *itype, char *jobz, char *uplo, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublereal *w, doublecomplex *work, integer *lwork, doublereal *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpotrf_ 14 6 13 4 9 4 4 124 */
/*:ref: zhegst_ 14 9 4 13 4 9 4 9 4 4 124 */
/*:ref: zheevd_ 14 15 13 13 4 9 4 7 9 4 7 4 4 4 4 124 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: ztrmm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
extern int zhegvx_(integer *itype, char *jobz, char *range, char *uplo, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork, doublereal *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpotrf_ 14 6 13 4 9 4 4 124 */
/*:ref: zhegst_ 14 9 4 13 4 9 4 9 4 4 124 */
/*:ref: zheevx_ 14 24 13 13 13 4 9 4 7 7 4 4 7 4 7 9 4 9 4 7 4 4 4 124 124 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: ztrmm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
extern int zherfs_(char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zhemv_ 14 11 13 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zhetrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int zhesv_(char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zhetrf_ 14 9 13 4 9 4 4 9 4 4 124 */
/*:ref: zhetrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
extern int zhesvx_(char *fact, char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zhetrf_ 14 9 13 4 9 4 4 9 4 4 124 */
/*:ref: zlanhe_ 7 8 13 13 4 9 4 7 124 124 */
/*:ref: zhecon_ 14 10 13 4 9 4 4 7 7 9 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zhetrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
/*:ref: zherfs_ 14 18 13 4 4 9 4 9 4 4 9 4 9 4 7 7 9 7 4 124 */
extern int zhetd2_(char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *d__, doublereal *e, doublecomplex *tau, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zhemv_ 14 11 13 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zher2_ 14 10 13 4 9 9 4 9 4 9 4 124 */
extern int zhetf2_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zher_ 14 8 13 4 7 9 4 9 4 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: dlapy2_ 7 2 7 7 */
extern int zhetrd_(char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *d__, doublereal *e, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlatrd_ 14 10 13 4 4 9 4 7 9 9 4 124 */
/*:ref: zher2k_ 14 14 13 13 4 4 9 9 4 9 4 7 9 4 124 124 */
/*:ref: zhetd2_ 14 9 13 4 9 4 7 7 9 4 124 */
extern int zhetrf_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlahef_ 14 11 13 4 4 4 9 4 4 9 4 4 124 */
/*:ref: zhetf2_ 14 7 13 4 9 4 4 4 124 */
extern int zhetri_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zhemv_ 14 11 13 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zhetrs_(char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
extern int zhgeqz_(char *job, char *compq, char *compz, integer *n, integer *ilo, integer *ihi, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *alpha, doublecomplex *beta, doublecomplex *q, integer *ldq, doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen job_len, ftnlen compq_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhs_ 7 6 13 4 9 4 7 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zlartg_ 14 5 9 9 7 9 9 */
/*:ref: zrot_ 14 7 4 9 4 9 4 7 9 */
extern int zhpcon_(char *uplo, integer *n, doublecomplex *ap, integer *ipiv, doublereal *anorm, doublereal *rcond, doublecomplex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zhptrs_ 14 9 13 4 4 9 4 9 4 4 124 */
extern int zhpev_(char *jobz, char *uplo, integer *n, doublecomplex *ap, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, doublereal *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhp_ 7 7 13 13 4 9 7 124 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zhptrd_ 14 8 13 4 9 7 7 9 4 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zupgtr_ 14 9 13 4 9 9 9 4 9 4 124 */
/*:ref: zsteqr_ 14 9 13 4 7 7 9 4 7 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int zhpevd_(char *jobz, char *uplo, integer *n, doublecomplex *ap, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork, doublereal *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhp_ 7 7 13 13 4 9 7 124 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zhptrd_ 14 8 13 4 9 7 7 9 4 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zstedc_ 14 14 13 4 7 7 9 4 9 4 7 4 4 4 4 124 */
/*:ref: zupmtr_ 14 14 13 13 13 4 4 9 9 9 4 9 4 124 124 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
extern int zhpevx_(char *jobz, char *range, char *uplo, integer *n, doublecomplex *ap, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, doublereal *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhp_ 7 7 13 13 4 9 7 124 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zhptrd_ 14 8 13 4 9 7 7 9 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zupgtr_ 14 9 13 4 9 9 9 4 9 4 124 */
/*:ref: zsteqr_ 14 9 13 4 7 7 9 4 7 4 124 */
/*:ref: dstebz_ 14 20 13 13 4 7 7 4 4 7 7 7 4 4 7 4 4 7 4 4 124 124 */
/*:ref: zstein_ 14 13 4 7 7 4 7 4 4 9 4 7 4 4 4 */
/*:ref: zupmtr_ 14 14 13 13 13 4 4 9 9 9 4 9 4 124 124 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zhpgst_(integer *itype, char *uplo, integer *n, doublecomplex *ap, doublecomplex *bp, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztpsv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
/*:ref: zhpmv_ 14 10 13 4 9 9 9 4 9 9 4 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zhpr2_ 14 9 13 4 9 9 4 9 4 9 124 */
/*:ref: ztpmv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
extern int zhpgv_(integer *itype, char *jobz, char *uplo, integer *n, doublecomplex *ap, doublecomplex *bp, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, doublereal *rwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpptrf_ 14 5 13 4 9 4 124 */
/*:ref: zhpgst_ 14 7 4 13 4 9 9 4 124 */
/*:ref: zhpev_ 14 12 13 13 4 9 7 9 4 9 7 4 124 124 */
/*:ref: ztpsv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
/*:ref: ztpmv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
extern int zhpgvd_(integer *itype, char *jobz, char *uplo, integer *n, doublecomplex *ap, doublecomplex *bp, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork, doublereal *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpptrf_ 14 5 13 4 9 4 124 */
/*:ref: zhpgst_ 14 7 4 13 4 9 9 4 124 */
/*:ref: zhpevd_ 14 16 13 13 4 9 7 9 4 9 4 7 4 4 4 4 124 124 */
/*:ref: ztpsv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
/*:ref: ztpmv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
extern int zhpgvx_(integer *itype, char *jobz, char *range, char *uplo, integer *n, doublecomplex *ap, doublecomplex *bp, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *work, doublereal *rwork, integer *iwork, integer *ifail, integer *info, ftnlen jobz_len, ftnlen range_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpptrf_ 14 5 13 4 9 4 124 */
/*:ref: zhpgst_ 14 7 4 13 4 9 9 4 124 */
/*:ref: zhpevx_ 14 22 13 13 13 4 9 7 7 4 4 7 4 7 9 4 9 7 4 4 4 124 124 124 */
/*:ref: ztpsv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
/*:ref: ztpmv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
extern int zhprfs_(char *uplo, integer *n, integer *nrhs, doublecomplex *ap, doublecomplex *afp, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zhpmv_ 14 10 13 4 9 9 9 4 9 9 4 124 */
/*:ref: zhptrs_ 14 9 13 4 4 9 4 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int zhpsv_(char *uplo, integer *n, integer *nrhs, doublecomplex *ap, integer *ipiv, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zhptrf_ 14 6 13 4 9 4 4 124 */
/*:ref: zhptrs_ 14 9 13 4 4 9 4 9 4 4 124 */
extern int zhpsvx_(char *fact, char *uplo, integer *n, integer *nrhs, doublecomplex *ap, doublecomplex *afp, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zhptrf_ 14 6 13 4 9 4 4 124 */
/*:ref: zlanhp_ 7 7 13 13 4 9 7 124 124 */
/*:ref: zhpcon_ 14 9 13 4 9 4 7 7 9 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zhptrs_ 14 9 13 4 4 9 4 9 4 4 124 */
/*:ref: zhprfs_ 14 16 13 4 4 9 9 4 9 4 9 4 7 7 9 7 4 124 */
extern int zhptrd_(char *uplo, integer *n, doublecomplex *ap, doublereal *d__, doublereal *e, doublecomplex *tau, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zhpmv_ 14 10 13 4 9 9 9 4 9 9 4 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zhpr2_ 14 9 13 4 9 9 4 9 4 9 124 */
extern int zhptrf_(char *uplo, integer *n, doublecomplex *ap, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zhpr_ 14 7 13 4 7 9 4 9 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: dlapy2_ 7 2 7 7 */
extern int zhptri_(char *uplo, integer *n, doublecomplex *ap, integer *ipiv, doublecomplex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zhpmv_ 14 10 13 4 9 9 9 4 9 9 4 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zhptrs_(char *uplo, integer *n, integer *nrhs, doublecomplex *ap, integer *ipiv, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
extern int zhsein_(char *side, char *eigsrc, char *initv, logical *select, integer *n, doublecomplex *h__, integer *ldh, doublecomplex *w, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, integer *mm, integer *m, doublecomplex *work, doublereal *rwork, integer *ifaill, integer *ifailr, integer *info, ftnlen side_len, ftnlen eigsrc_len, ftnlen initv_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhs_ 7 6 13 4 9 4 7 124 */
/*:ref: zlaein_ 14 13 12 12 4 9 4 9 9 9 4 7 7 7 4 */
extern int zhseqr_(char *job, char *compz, integer *n, integer *ilo, integer *ihi, doublecomplex *h__, integer *ldh, doublecomplex *w, doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork, integer *info, ftnlen job_len, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: zlahqr_ 14 13 12 12 4 4 4 9 4 9 4 4 9 4 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlanhs_ 7 6 13 4 9 4 7 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zlarfx_ 14 9 13 4 4 9 9 9 4 9 124 */
extern int zlabrd_(integer *m, integer *n, integer *nb, doublecomplex *a, integer *lda, doublereal *d__, doublereal *e, doublecomplex *tauq, doublecomplex *taup, doublecomplex *x, integer *ldx, doublecomplex *y, integer *ldy);
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zlacgv_(integer *n, doublecomplex *x, integer *incx);
extern int zlacon_(integer *n, doublecomplex *v, doublecomplex *x, doublereal *est, integer *kase);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dzsum1_ 7 3 4 9 4 */
/*:ref: izmax1_ 4 3 4 9 4 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
extern int zlacp2_(char *uplo, integer *m, integer *n, doublereal *a, integer *lda, doublecomplex *b, integer *ldb, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int zlacpy_(char *uplo, integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int zlacrm_(integer *m, integer *n, doublecomplex *a, integer *lda, doublereal *b, integer *ldb, doublecomplex *c__, integer *ldc, doublereal *rwork);
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
extern int zlacrt_(integer *n, doublecomplex *cx, integer *incx, doublecomplex *cy, integer *incy, doublecomplex *c__, doublecomplex *s);
extern Z_f zladiv_(doublecomplex * ret_val, doublecomplex *x, doublecomplex *y);
/*:ref: dladiv_ 14 6 7 7 7 7 7 7 */
extern int zlaed0_(integer *qsiz, integer *n, doublereal *d__, doublereal *e, doublecomplex *q, integer *ldq, doublecomplex *qstore, integer *ldqs, doublereal *rwork, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: zlacrm_ 14 9 4 4 9 4 7 4 9 4 7 */
/*:ref: zlaed7_ 14 22 4 4 4 4 4 4 7 9 4 7 4 7 4 4 4 4 4 7 9 7 4 4 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
extern int zlaed7_(integer *n, integer *cutpnt, integer *qsiz, integer *tlvls, integer *curlvl, integer *curpbm, doublereal *d__, doublecomplex *q, integer *ldq, doublereal *rho, integer *indxq, doublereal *qstore, integer *qptr, integer *prmptr, integer *perm, integer *givptr, integer *givcol, doublereal *givnum, doublecomplex *work, doublereal *rwork, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlaeda_ 14 14 4 4 4 4 4 4 4 4 7 7 4 7 7 4 */
/*:ref: zlaed8_ 14 21 4 4 4 9 4 7 7 4 7 7 9 4 7 4 4 4 4 4 4 7 4 */
/*:ref: dlaed9_ 14 13 4 4 4 4 7 7 4 7 7 7 7 4 4 */
/*:ref: zlacrm_ 14 9 4 4 9 4 7 4 9 4 7 */
/*:ref: dlamrg_ 14 6 4 4 7 4 4 4 */
extern int zlaed8_(integer *k, integer *n, integer *qsiz, doublecomplex *q, integer *ldq, doublereal *d__, doublereal *rho, integer *cutpnt, doublereal *z__, doublereal *dlamda, doublecomplex *q2, integer *ldq2, doublereal *w, integer *indxp, integer *indx, integer *indxq, integer *perm, integer *givptr, integer *givcol, doublereal *givnum, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlamrg_ 14 6 4 4 7 4 4 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: zdrot_ 14 7 4 9 4 9 4 7 7 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
extern int zlaein_(logical *rightv, logical *noinit, integer *n, doublecomplex *h__, integer *ldh, doublecomplex *w, doublecomplex *v, doublecomplex *b, integer *ldb, doublereal *rwork, doublereal *eps3, doublereal *smlnum, integer *info);
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zladiv_ 9 3 9 9 9 */
/*:ref: zlatrs_ 14 15 13 13 13 13 4 9 4 9 7 7 4 124 124 124 124 */
/*:ref: dzasum_ 7 3 4 9 4 */
/*:ref: izamax_ 4 3 4 9 4 */
extern int zlaesy_(doublecomplex *a, doublecomplex *b, doublecomplex *c__, doublecomplex *rt1, doublecomplex *rt2, doublecomplex *evscal, doublecomplex *cs1, doublecomplex *sn1);
extern int zlaev2_(doublecomplex *a, doublecomplex *b, doublecomplex *c__, doublereal *rt1, doublereal *rt2, doublereal *cs1, doublecomplex *sn1);
/*:ref: dlaev2_ 14 7 7 7 7 7 7 7 7 */
extern int zlags2_(logical *upper, doublereal *a1, doublecomplex *a2, doublereal *a3, doublereal *b1, doublecomplex *b2, doublereal *b3, doublereal *csu, doublecomplex *snu, doublereal *csv, doublecomplex *snv, doublereal *csq, doublecomplex *snq);
/*:ref: dlasv2_ 14 9 7 7 7 7 7 7 7 7 7 */
/*:ref: zlartg_ 14 5 9 9 7 9 9 */
extern int zlagtm_(char *trans, integer *n, integer *nrhs, doublereal *alpha, doublecomplex *dl, doublecomplex *d__, doublecomplex *du, doublecomplex *x, integer *ldx, doublereal *beta, doublecomplex *b, integer *ldb, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int zlahef_(char *uplo, integer *n, integer *nb, integer *kb, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *w, integer *ldw, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
extern int zlahqr_(logical *wantt, logical *wantz, integer *n, integer *ilo, integer *ihi, doublecomplex *h__, integer *ldh, doublecomplex *w, integer *iloz, integer *ihiz, doublecomplex *z__, integer *ldz, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlanhs_ 7 6 13 4 9 4 7 124 */
/*:ref: zladiv_ 9 3 9 9 9 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zlahrd_(integer *n, integer *k, integer *nb, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *t, integer *ldt, doublecomplex *y, integer *ldy);
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: ztrmv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zlaic1_(integer *job, integer *j, doublecomplex *x, doublereal *sest, doublecomplex *w, doublecomplex *gamma, doublereal *sestpr, doublecomplex *s, doublecomplex *c__);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
extern int zlals0_(integer *icompq, integer *nl, integer *nr, integer *sqre, integer *nrhs, doublecomplex *b, integer *ldb, doublecomplex *bx, integer *ldbx, integer *perm, integer *givptr, integer *givcol, integer *ldgcol, doublereal *givnum, integer *ldgnum, doublereal *poles, doublereal *difl, doublereal *difr, doublereal *z__, integer *k, doublereal *c__, doublereal *s, doublereal *rwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zdrot_ 14 7 4 9 4 9 4 7 7 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: dlamc3_ 7 2 7 7 */
/*:ref: dnrm2_ 7 3 4 7 4 */
/*:ref: dgemv_ 14 12 13 4 4 7 7 4 7 4 7 7 4 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
extern int zlalsa_(integer *icompq, integer *smlsiz, integer *n, integer *nrhs, doublecomplex *b, integer *ldb, doublecomplex *bx, integer *ldbx, doublereal *u, integer *ldu, doublereal *vt, integer *k, doublereal *difl, doublereal *difr, doublereal *z__, doublereal *poles, integer *givptr, integer *givcol, integer *ldgcol, integer *perm, doublereal *givnum, doublereal *c__, doublereal *s, doublereal *rwork, integer *iwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlasdt_ 14 7 4 4 4 4 4 4 4 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlals0_ 14 24 4 4 4 4 4 9 4 9 4 4 4 4 4 7 4 7 7 7 7 4 7 7 7 4 */
extern int zlalsd_(char *uplo, integer *smlsiz, integer *n, integer *nrhs, doublereal *d__, doublereal *e, doublecomplex *b, integer *ldb, doublereal *rcond, integer *rank, doublecomplex *work, doublereal *rwork, integer *iwork, integer *info, ftnlen uplo_len);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlascl_ 14 11 13 4 4 7 7 4 4 9 4 4 124 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: zdrot_ 14 7 4 9 4 9 4 7 7 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dlasdq_ 14 17 13 4 4 4 4 4 7 7 7 4 7 4 7 4 7 4 124 */
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dlasrt_ 14 5 13 4 7 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: dlasda_ 14 24 4 4 4 4 7 7 7 4 7 4 7 7 7 7 4 4 4 4 7 7 7 7 4 4 */
/*:ref: zlalsa_ 14 26 4 4 4 4 9 4 9 4 7 4 7 4 7 7 7 7 4 4 4 4 7 7 7 7 4 4 */
extern doublereal zlangb_(char *norm, integer *n, integer *kl, integer *ku, doublecomplex *ab, integer *ldab, doublereal *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlange_(char *norm, integer *m, integer *n, doublecomplex *a, integer *lda, doublereal *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlangt_(char *norm, integer *n, doublecomplex *dl, doublecomplex *d__, doublecomplex *du, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlanhb_(char *norm, char *uplo, integer *n, integer *k, doublecomplex *ab, integer *ldab, doublereal *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlanhe_(char *norm, char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlanhp_(char *norm, char *uplo, integer *n, doublecomplex *ap, doublereal *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlanhs_(char *norm, integer *n, doublecomplex *a, integer *lda, doublereal *work, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlanht_(char *norm, integer *n, doublereal *d__, doublecomplex *e, ftnlen norm_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
/*:ref: dlassq_ 14 5 4 7 4 7 7 */
extern doublereal zlansb_(char *norm, char *uplo, integer *n, integer *k, doublecomplex *ab, integer *ldab, doublereal *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlansp_(char *norm, char *uplo, integer *n, doublecomplex *ap, doublereal *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlansy_(char *norm, char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *work, ftnlen norm_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlantb_(char *norm, char *uplo, char *diag, integer *n, integer *k, doublecomplex *ab, integer *ldab, doublereal *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlantp_(char *norm, char *uplo, char *diag, integer *n, doublecomplex *ap, doublereal *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern doublereal zlantr_(char *norm, char *uplo, char *diag, integer *m, integer *n, doublecomplex *a, integer *lda, doublereal *work, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
extern int zlapll_(integer *n, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublereal *ssmin);
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: dlas2_ 14 5 7 7 7 7 7 */
extern int zlapmt_(logical *forwrd, integer *m, integer *n, doublecomplex *x, integer *ldx, integer *k);
extern int zlaqgb_(integer *m, integer *n, integer *kl, integer *ku, doublecomplex *ab, integer *ldab, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal *colcnd, doublereal *amax, char *equed, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
extern int zlaqge_(integer *m, integer *n, doublecomplex *a, integer *lda, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal *colcnd, doublereal *amax, char *equed, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
extern int zlaqhb_(char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, doublereal *s, doublereal *scond, doublereal *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int zlaqhe_(char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *s, doublereal *scond, doublereal *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int zlaqhp_(char *uplo, integer *n, doublecomplex *ap, doublereal *s, doublereal *scond, doublereal *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int zlaqp2_(integer *m, integer *n, integer *offset, doublecomplex *a, integer *lda, integer *jpvt, doublecomplex *tau, doublereal *vn1, doublereal *vn2, doublecomplex *work);
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
/*:ref: dznrm2_ 7 3 4 9 4 */
extern int zlaqps_(integer *m, integer *n, integer *offset, integer *nb, integer *kb, doublecomplex *a, integer *lda, integer *jpvt, doublecomplex *tau, doublereal *vn1, doublereal *vn2, doublecomplex *auxv, doublecomplex *f, integer *ldf);
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: dznrm2_ 7 3 4 9 4 */
extern int zlaqsb_(char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, doublereal *s, doublereal *scond, doublereal *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int zlaqsp_(char *uplo, integer *n, doublecomplex *ap, doublereal *s, doublereal *scond, doublereal *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int zlaqsy_(char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *s, doublereal *scond, doublereal *amax, char *equed, ftnlen uplo_len, ftnlen equed_len);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int zlar1v_(integer *n, integer *b1, integer *bn, doublereal *sigma, doublereal *d__, doublereal *l, doublereal *ld, doublereal *lld, doublereal *gersch, doublecomplex *z__, doublereal *ztz, doublereal *mingma, integer *r__, integer *isuppz, doublereal *work);
/*:ref: dlamch_ 7 2 13 124 */
extern int zlar2v_(integer *n, doublecomplex *x, doublecomplex *y, doublecomplex *z__, integer *incx, doublereal *c__, doublecomplex *s, integer *incc);
extern int zlarcm_(integer *m, integer *n, doublereal *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *c__, integer *ldc, doublereal *rwork);
/*:ref: dgemm_ 14 15 13 13 4 4 4 7 7 4 7 4 7 7 4 124 124 */
extern int zlarf_(char *side, integer *m, integer *n, doublecomplex *v, integer *incv, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zgerc_ 14 9 4 4 9 9 4 9 4 9 4 */
extern int zlarfb_(char *side, char *trans, char *direct, char *storev, integer *m, integer *n, integer *k, doublecomplex *v, integer *ldv, doublecomplex *t, integer *ldt, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *ldwork, ftnlen side_len, ftnlen trans_len, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: ztrmm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
extern int zlarfg_(integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *tau);
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: dlapy3_ 7 3 7 7 7 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zladiv_ 9 3 9 9 9 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zlarft_(char *direct, char *storev, integer *n, integer *k, doublecomplex *v, integer *ldv, doublecomplex *tau, doublecomplex *t, integer *ldt, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: ztrmv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
extern int zlarfx_(char *side, integer *m, integer *n, doublecomplex *v, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zgerc_ 14 9 4 4 9 9 4 9 4 9 4 */
extern int zlargv_(integer *n, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublereal *c__, integer *incc);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlapy2_ 7 2 7 7 */
extern int zlarnv_(integer *idist, integer *iseed, integer *n, doublecomplex *x);
/*:ref: dlaruv_ 14 3 4 4 7 */
extern int zlarrv_(integer *n, doublereal *d__, doublereal *l, integer *isplit, integer *m, doublereal *w, integer *iblock, doublereal *gersch, doublereal *tol, doublecomplex *z__, integer *ldz, integer *isuppz, doublereal *work, integer *iwork, integer *info);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlarrb_ 14 15 4 7 7 7 7 4 4 7 7 7 7 7 7 4 4 */
/*:ref: dlarrf_ 14 13 4 7 7 7 7 4 4 7 7 7 7 4 4 */
/*:ref: zstein_ 14 13 4 7 7 4 7 4 4 9 4 7 4 4 4 */
/*:ref: zlar1v_ 14 15 4 4 4 7 7 7 7 7 7 9 7 7 4 4 7 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zdotu_ 9 6 9 4 9 4 9 4 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: dznrm2_ 7 3 4 9 4 */
extern int zlartg_(doublecomplex *f, doublecomplex *g, doublereal *cs, doublecomplex *sn, doublecomplex *r__);
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlapy2_ 7 2 7 7 */
extern int zlartv_(integer *n, doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, doublereal *c__, doublecomplex *s, integer *incc);
extern int zlarz_(char *side, integer *m, integer *n, integer *l, doublecomplex *v, integer *incv, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
/*:ref: zgerc_ 14 9 4 4 9 9 4 9 4 9 4 */
extern int zlarzb_(char *side, char *trans, char *direct, char *storev, integer *m, integer *n, integer *k, integer *l, doublecomplex *v, integer *ldv, doublecomplex *t, integer *ldt, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *ldwork, ftnlen side_len, ftnlen trans_len, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: ztrmm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
extern int zlarzt_(char *direct, char *storev, integer *n, integer *k, doublecomplex *v, integer *ldv, doublecomplex *tau, doublecomplex *t, integer *ldt, ftnlen direct_len, ftnlen storev_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: ztrmv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
extern int zlascl_(char *type__, integer *kl, integer *ku, doublereal *cfrom, doublereal *cto, integer *m, integer *n, doublecomplex *a, integer *lda, integer *info, ftnlen type_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
extern int zlaset_(char *uplo, integer *m, integer *n, doublecomplex *alpha, doublecomplex *beta, doublecomplex *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
extern int zlasr_(char *side, char *pivot, char *direct, integer *m, integer *n, doublereal *c__, doublereal *s, doublecomplex *a, integer *lda, ftnlen side_len, ftnlen pivot_len, ftnlen direct_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zlassq_(integer *n, doublecomplex *x, integer *incx, doublereal *scale, doublereal *sumsq);
extern int zlaswp_(integer *n, doublecomplex *a, integer *lda, integer *k1, integer *k2, integer *ipiv, integer *incx);
extern int zlasyf_(char *uplo, integer *n, integer *nb, integer *kb, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *w, integer *ldw, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
extern int zlatbs_(char *uplo, char *trans, char *diag, char *normin, integer *n, integer *kd, doublecomplex *ab, integer *ldab, doublecomplex *x, doublereal *scale, doublereal *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dzasum_ 7 3 4 9 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: ztbsv_ 14 12 13 13 13 4 4 9 4 9 4 124 124 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zladiv_ 9 3 9 9 9 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdotu_ 9 6 9 4 9 4 9 4 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
extern int zlatdf_(integer *ijob, integer *n, doublecomplex *z__, integer *ldz, doublecomplex *rhs, doublereal *rdsum, doublereal *rdscal, integer *ipiv, integer *jpiv);
/*:ref: zlaswp_ 14 7 4 9 4 4 4 4 4 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
/*:ref: zgecon_ 14 10 13 4 9 4 7 7 9 7 4 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zgesc2_ 14 7 4 9 4 9 4 4 7 */
/*:ref: dzasum_ 7 3 4 9 4 */
extern int zlatps_(char *uplo, char *trans, char *diag, char *normin, integer *n, doublecomplex *ap, doublecomplex *x, doublereal *scale, doublereal *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dzasum_ 7 3 4 9 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: ztpsv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zladiv_ 9 3 9 9 9 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdotu_ 9 6 9 4 9 4 9 4 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
extern int zlatrd_(char *uplo, integer *n, integer *nb, doublecomplex *a, integer *lda, doublereal *e, doublecomplex *tau, doublecomplex *w, integer *ldw, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zhemv_ 14 11 13 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
extern int zlatrs_(char *uplo, char *trans, char *diag, char *normin, integer *n, doublecomplex *a, integer *lda, doublecomplex *x, doublereal *scale, doublereal *cnorm, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len, ftnlen normin_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dzasum_ 7 3 4 9 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: ztrsv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zladiv_ 9 3 9 9 9 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdotu_ 9 6 9 4 9 4 9 4 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
extern int zlatrz_(integer *m, integer *n, integer *l, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work);
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zlarz_ 14 11 13 4 4 4 9 4 9 9 4 9 124 */
extern int zlatzm_(char *side, integer *m, integer *n, doublecomplex *v, integer *incv, doublecomplex *tau, doublecomplex *c1, doublecomplex *c2, integer *ldc, doublecomplex *work, ftnlen side_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
/*:ref: zgerc_ 14 9 4 4 9 9 4 9 4 9 4 */
extern int zlauu2_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
extern int zlauum_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: zlauu2_ 14 6 13 4 9 4 4 124 */
/*:ref: ztrmm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: zherk_ 14 12 13 13 4 4 7 9 4 7 9 4 124 124 */
extern int zpbcon_(char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, doublereal *anorm, doublereal *rcond, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zlatbs_ 14 16 13 13 13 13 4 4 9 4 9 7 7 4 124 124 124 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdrscl_ 14 4 4 7 9 4 */
extern int zpbequ_(char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, doublereal *s, doublereal *scond, doublereal *amax, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zpbrfs_(char *uplo, integer *n, integer *kd, integer *nrhs, doublecomplex *ab, integer *ldab, doublecomplex *afb, integer *ldafb, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zhbmv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zpbtrs_ 14 10 13 4 4 4 9 4 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int zpbstf_(char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zher_ 14 8 13 4 7 9 4 9 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
extern int zpbsv_(char *uplo, integer *n, integer *kd, integer *nrhs, doublecomplex *ab, integer *ldab, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpbtrf_ 14 7 13 4 4 9 4 4 124 */
/*:ref: zpbtrs_ 14 10 13 4 4 4 9 4 9 4 4 124 */
extern int zpbsvx_(char *fact, char *uplo, integer *n, integer *kd, integer *nrhs, doublecomplex *ab, integer *ldab, doublecomplex *afb, integer *ldafb, char *equed, doublereal *s, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpbequ_ 14 10 13 4 4 9 4 7 7 7 4 124 */
/*:ref: zlaqhb_ 14 11 13 4 4 9 4 7 7 7 13 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zpbtrf_ 14 7 13 4 4 9 4 4 124 */
/*:ref: zlanhb_ 7 9 13 13 4 4 9 4 7 124 124 */
/*:ref: zpbcon_ 14 11 13 4 4 9 4 7 7 9 7 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zpbtrs_ 14 10 13 4 4 4 9 4 9 4 4 124 */
/*:ref: zpbrfs_ 14 18 13 4 4 4 9 4 9 4 9 4 9 4 7 7 9 7 4 124 */
extern int zpbtf2_(char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zher_ 14 8 13 4 7 9 4 9 4 124 */
extern int zpbtrf_(char *uplo, integer *n, integer *kd, doublecomplex *ab, integer *ldab, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: zpbtf2_ 14 7 13 4 4 9 4 4 124 */
/*:ref: zpotf2_ 14 6 13 4 9 4 4 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: zherk_ 14 12 13 13 4 4 7 9 4 7 9 4 124 124 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
extern int zpbtrs_(char *uplo, integer *n, integer *kd, integer *nrhs, doublecomplex *ab, integer *ldab, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztbsv_ 14 12 13 13 13 4 4 9 4 9 4 124 124 124 */
extern int zpocon_(char *uplo, integer *n, doublecomplex *a, integer *lda, doublereal *anorm, doublereal *rcond, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zlatrs_ 14 15 13 13 13 13 4 9 4 9 7 7 4 124 124 124 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdrscl_ 14 4 4 7 9 4 */
extern int zpoequ_(integer *n, doublecomplex *a, integer *lda, doublereal *s, doublereal *scond, doublereal *amax, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zporfs_(char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zhemv_ 14 11 13 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zpotrs_ 14 9 13 4 4 9 4 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int zposv_(char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpotrf_ 14 6 13 4 9 4 4 124 */
/*:ref: zpotrs_ 14 9 13 4 4 9 4 9 4 4 124 */
extern int zposvx_(char *fact, char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, char *equed, doublereal *s, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpoequ_ 14 7 4 9 4 7 7 7 4 */
/*:ref: zlaqhe_ 14 10 13 4 9 4 7 7 7 13 124 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zpotrf_ 14 6 13 4 9 4 4 124 */
/*:ref: zlanhe_ 7 8 13 13 4 9 4 7 124 124 */
/*:ref: zpocon_ 14 10 13 4 9 4 7 7 9 7 4 124 */
/*:ref: zpotrs_ 14 9 13 4 4 9 4 9 4 4 124 */
/*:ref: zporfs_ 14 17 13 4 4 9 4 9 4 9 4 9 4 7 7 9 7 4 124 */
extern int zpotf2_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
extern int zpotrf_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: zpotf2_ 14 6 13 4 9 4 4 124 */
/*:ref: zherk_ 14 12 13 13 4 4 7 9 4 7 9 4 124 124 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
extern int zpotri_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztrtri_ 14 8 13 13 4 9 4 4 124 124 */
/*:ref: zlauum_ 14 6 13 4 9 4 4 124 */
extern int zpotrs_(char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
extern int zppcon_(char *uplo, integer *n, doublecomplex *ap, doublereal *anorm, doublereal *rcond, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zlatps_ 14 14 13 13 13 13 4 9 9 7 7 4 124 124 124 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdrscl_ 14 4 4 7 9 4 */
extern int zppequ_(char *uplo, integer *n, doublecomplex *ap, doublereal *s, doublereal *scond, doublereal *amax, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zpprfs_(char *uplo, integer *n, integer *nrhs, doublecomplex *ap, doublecomplex *afp, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zhpmv_ 14 10 13 4 9 9 9 4 9 9 4 124 */
/*:ref: zpptrs_ 14 8 13 4 4 9 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int zppsv_(char *uplo, integer *n, integer *nrhs, doublecomplex *ap, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpptrf_ 14 5 13 4 9 4 124 */
/*:ref: zpptrs_ 14 8 13 4 4 9 9 4 4 124 */
extern int zppsvx_(char *fact, char *uplo, integer *n, integer *nrhs, doublecomplex *ap, doublecomplex *afp, char *equed, doublereal *s, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len, ftnlen equed_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zppequ_ 14 8 13 4 9 7 7 7 4 124 */
/*:ref: zlaqhp_ 14 9 13 4 9 7 7 7 13 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zpptrf_ 14 5 13 4 9 4 124 */
/*:ref: zlanhp_ 7 7 13 13 4 9 7 124 124 */
/*:ref: zppcon_ 14 9 13 4 9 7 7 9 7 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zpptrs_ 14 8 13 4 4 9 9 4 4 124 */
/*:ref: zpprfs_ 14 15 13 4 4 9 9 9 4 9 4 7 7 9 7 4 124 */
extern int zpptrf_(char *uplo, integer *n, doublecomplex *ap, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztpsv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zhpr_ 14 7 13 4 7 9 4 9 124 */
extern int zpptri_(char *uplo, integer *n, doublecomplex *ap, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztptri_ 14 7 13 13 4 9 4 124 124 */
/*:ref: zhpr_ 14 7 13 4 7 9 4 9 124 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: ztpmv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
extern int zpptrs_(char *uplo, integer *n, integer *nrhs, doublecomplex *ap, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztpsv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
extern int zptcon_(integer *n, doublereal *d__, doublecomplex *e, doublereal *anorm, doublereal *rcond, doublereal *rwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: idamax_ 4 3 4 7 4 */
extern int zpteqr_(char *compz, integer *n, doublereal *d__, doublereal *e, doublecomplex *z__, integer *ldz, doublereal *work, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: dpttrf_ 14 4 4 7 7 4 */
/*:ref: zbdsqr_ 14 16 13 4 4 4 4 7 7 9 4 9 4 9 4 7 4 124 */
extern int zptrfs_(char *uplo, integer *n, integer *nrhs, doublereal *d__, doublecomplex *e, doublereal *df, doublecomplex *ef, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zpttrs_ 14 9 13 4 4 7 9 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: idamax_ 4 3 4 7 4 */
extern int zptsv_(integer *n, integer *nrhs, doublereal *d__, doublecomplex *e, doublecomplex *b, integer *ldb, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zpttrf_ 14 4 4 7 9 4 */
/*:ref: zpttrs_ 14 9 13 4 4 7 9 9 4 4 124 */
extern int zptsvx_(char *fact, integer *n, integer *nrhs, doublereal *d__, doublecomplex *e, doublereal *df, doublecomplex *ef, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen fact_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zpttrf_ 14 4 4 7 9 4 */
/*:ref: zlanht_ 7 5 13 4 7 9 124 */
/*:ref: zptcon_ 14 7 4 7 9 7 7 7 4 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zpttrs_ 14 9 13 4 4 7 9 9 4 4 124 */
/*:ref: zptrfs_ 14 17 13 4 4 7 9 7 9 9 4 9 4 7 7 9 7 4 124 */
extern int zpttrf_(integer *n, doublereal *d__, doublecomplex *e, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zpttrs_(char *uplo, integer *n, integer *nrhs, doublereal *d__, doublecomplex *e, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: zptts2_ 14 7 4 4 4 7 9 9 4 */
extern int zptts2_(integer *iuplo, integer *n, integer *nrhs, doublereal *d__, doublecomplex *e, doublecomplex *b, integer *ldb);
/*:ref: zdscal_ 14 4 4 7 9 4 */
extern int zrot_(integer *n, doublecomplex *cx, integer *incx, doublecomplex *cy, integer *incy, doublereal *c__, doublecomplex *s);
extern int zspcon_(char *uplo, integer *n, doublecomplex *ap, integer *ipiv, doublereal *anorm, doublereal *rcond, doublecomplex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zsptrs_ 14 9 13 4 4 9 4 9 4 4 124 */
extern int zspmv_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *ap, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zspr_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *ap, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zsprfs_(char *uplo, integer *n, integer *nrhs, doublecomplex *ap, doublecomplex *afp, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zspmv_ 14 10 13 4 9 9 9 4 9 9 4 124 */
/*:ref: zsptrs_ 14 9 13 4 4 9 4 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int zspsv_(char *uplo, integer *n, integer *nrhs, doublecomplex *ap, integer *ipiv, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zsptrf_ 14 6 13 4 9 4 4 124 */
/*:ref: zsptrs_ 14 9 13 4 4 9 4 9 4 4 124 */
extern int zspsvx_(char *fact, char *uplo, integer *n, integer *nrhs, doublecomplex *ap, doublecomplex *afp, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zsptrf_ 14 6 13 4 9 4 4 124 */
/*:ref: zlansp_ 7 7 13 13 4 9 7 124 124 */
/*:ref: zspcon_ 14 9 13 4 9 4 7 7 9 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zsptrs_ 14 9 13 4 4 9 4 9 4 4 124 */
/*:ref: zsprfs_ 14 16 13 4 4 9 9 4 9 4 9 4 7 7 9 7 4 124 */
extern int zsptrf_(char *uplo, integer *n, doublecomplex *ap, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zspr_ 14 7 13 4 9 9 4 9 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zsptri_(char *uplo, integer *n, doublecomplex *ap, integer *ipiv, doublecomplex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zspmv_ 14 10 13 4 9 9 9 4 9 9 4 124 */
/*:ref: zdotu_ 9 6 9 4 9 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zsptrs_(char *uplo, integer *n, integer *nrhs, doublecomplex *ap, integer *ipiv, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
extern int zstedc_(char *compz, integer *n, doublereal *d__, doublereal *e, doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork, doublereal *rwork, integer *lrwork, integer *iwork, integer *liwork, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: dsterf_ 14 4 4 7 7 4 */
/*:ref: zsteqr_ 14 9 13 4 7 7 9 4 7 4 124 */
/*:ref: dlaset_ 14 8 13 4 4 7 7 7 4 124 */
/*:ref: dstedc_ 14 12 13 4 7 7 7 4 7 4 4 4 4 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: zlaed0_ 14 11 4 4 7 7 9 4 9 4 7 4 4 */
/*:ref: dsteqr_ 14 9 13 4 7 7 7 4 7 4 124 */
/*:ref: zlacrm_ 14 9 4 4 9 4 7 4 9 4 7 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zstegr_(char *jobz, char *range, integer *n, doublereal *d__, doublereal *e, doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *w, doublecomplex *z__, integer *ldz, integer *isuppz, doublereal *work, integer *lwork, integer *iwork, integer *liwork, integer *info, ftnlen jobz_len, ftnlen range_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: dlarre_ 14 12 4 7 7 7 4 4 4 7 7 7 7 4 */
/*:ref: zlarrv_ 14 15 4 7 7 4 4 7 4 7 7 9 4 4 7 4 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zstein_(integer *n, doublereal *d__, doublereal *e, integer *m, doublereal *w, integer *iblock, integer *isplit, doublecomplex *z__, integer *ldz, doublereal *work, integer *iwork, integer *ifail, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlarnv_ 14 4 4 4 4 7 */
/*:ref: dcopy_ 14 5 4 7 4 7 4 */
/*:ref: dlagtf_ 14 9 4 7 7 7 7 7 7 4 4 */
/*:ref: dasum_ 7 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: dlagts_ 14 10 4 4 7 7 7 7 4 7 7 4 */
/*:ref: idamax_ 4 3 4 7 4 */
/*:ref: dnrm2_ 7 3 4 7 4 */
extern int zsteqr_(char *compz, integer *n, doublereal *d__, doublereal *e, doublecomplex *z__, integer *ldz, doublereal *work, integer *info, ftnlen compz_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: dlanst_ 7 5 13 4 7 7 124 */
/*:ref: dlascl_ 14 11 13 4 4 7 7 4 4 7 4 4 124 */
/*:ref: dlaev2_ 14 7 7 7 7 7 7 7 7 */
/*:ref: zlasr_ 14 12 13 13 13 4 4 7 7 9 4 124 124 124 */
/*:ref: dlae2_ 14 5 7 7 7 7 7 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
/*:ref: dlasrt_ 14 5 13 4 7 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zsycon_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *ipiv, doublereal *anorm, doublereal *rcond, doublecomplex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zsytrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
extern int zsymv_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *incy, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zsyr_(char *uplo, integer *n, doublecomplex *alpha, doublecomplex *x, integer *incx, doublecomplex *a, integer *lda, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
extern int zsyrfs_(char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zsymv_ 14 11 13 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zsytrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int zsysv_(char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zsytrf_ 14 9 13 4 9 4 4 9 4 4 124 */
/*:ref: zsytrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
extern int zsysvx_(char *fact, char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *work, integer *lwork, doublereal *rwork, integer *info, ftnlen fact_len, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zsytrf_ 14 9 13 4 9 4 4 9 4 4 124 */
/*:ref: zlansy_ 7 8 13 13 4 9 4 7 124 124 */
/*:ref: zsycon_ 14 10 13 4 9 4 4 7 7 9 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zsytrs_ 14 10 13 4 4 9 4 4 9 4 4 124 */
/*:ref: zsyrfs_ 14 18 13 4 4 9 4 9 4 4 9 4 9 4 7 7 9 7 4 124 */
extern int zsytf2_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *ipiv, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zsyr_ 14 8 13 4 9 9 4 9 4 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zsytrf_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlasyf_ 14 11 13 4 4 4 9 4 4 9 4 4 124 */
/*:ref: zsytf2_ 14 7 13 4 9 4 4 4 124 */
extern int zsytri_(char *uplo, integer *n, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zsymv_ 14 11 13 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zdotu_ 9 6 9 4 9 4 9 4 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
extern int zsytrs_(char *uplo, integer *n, integer *nrhs, doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zswap_ 14 5 4 9 4 9 4 */
/*:ref: zgeru_ 14 9 4 4 9 9 4 9 4 9 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
extern int ztbcon_(char *norm, char *uplo, char *diag, integer *n, integer *kd, doublecomplex *ab, integer *ldab, doublereal *rcond, doublecomplex *work, doublereal *rwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlantb_ 7 11 13 13 13 4 4 9 4 7 124 124 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zlatbs_ 14 16 13 13 13 13 4 4 9 4 9 7 7 4 124 124 124 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdrscl_ 14 4 4 7 9 4 */
extern int ztbrfs_(char *uplo, char *trans, char *diag, integer *n, integer *kd, integer *nrhs, doublecomplex *ab, integer *ldab, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: ztbmv_ 14 12 13 13 13 4 4 9 4 9 4 124 124 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: ztbsv_ 14 12 13 13 13 4 4 9 4 9 4 124 124 124 */
extern int ztbtrs_(char *uplo, char *trans, char *diag, integer *n, integer *kd, integer *nrhs, doublecomplex *ab, integer *ldab, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztbsv_ 14 12 13 13 13 4 4 9 4 9 4 124 124 124 */
extern int ztgevc_(char *side, char *howmny, logical *select, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, integer *mm, integer *m, doublecomplex *work, doublereal *rwork, integer *info, ftnlen side_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zladiv_ 9 3 9 9 9 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
extern int ztgex2_(logical *wantq, logical *wantz, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *q, integer *ldq, doublecomplex *z__, integer *ldz, integer *j1, integer *info);
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
/*:ref: zlartg_ 14 5 9 9 7 9 9 */
/*:ref: zrot_ 14 7 4 9 4 9 4 7 9 */
extern int ztgexc_(logical *wantq, logical *wantz, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *q, integer *ldq, doublecomplex *z__, integer *ldz, integer *ifst, integer *ilst, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztgex2_ 14 13 12 12 4 9 4 9 4 9 4 9 4 4 4 */
extern int ztgsen_(integer *ijob, logical *wantq, logical *wantz, logical *select, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *alpha, doublecomplex *beta, doublecomplex *q, integer *ldq, doublecomplex *z__, integer *ldz, integer *m, doublereal *pl, doublereal *pr, doublereal *dif, doublecomplex *work, integer *lwork, integer *iwork, integer *liwork, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlassq_ 14 5 4 9 4 7 7 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: ztgexc_ 14 14 12 12 4 9 4 9 4 9 4 9 4 4 4 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: ztgsyl_ 14 23 13 4 4 4 9 4 9 4 9 4 9 4 9 4 9 4 7 7 9 4 4 4 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int ztgsja_(char *jobu, char *jobv, char *jobq, integer *m, integer *p, integer *n, integer *k, integer *l, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublereal *tola, doublereal *tolb, doublereal *alpha, doublereal *beta, doublecomplex *u, integer *ldu, doublecomplex *v, integer *ldv, doublecomplex *q, integer *ldq, doublecomplex *work, integer *ncycle, integer *info, ftnlen jobu_len, ftnlen jobv_len, ftnlen jobq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlaset_ 14 8 13 4 4 9 9 9 4 124 */
/*:ref: zlags2_ 14 13 12 7 9 7 7 9 7 7 9 7 9 7 9 */
/*:ref: zrot_ 14 7 4 9 4 9 4 7 9 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zlapll_ 14 6 4 9 4 9 4 7 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: dlartg_ 14 5 7 7 7 7 7 */
extern int ztgsna_(char *job, char *howmny, logical *select, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, doublereal *s, doublereal *dif, integer *mm, integer *m, doublecomplex *work, integer *lwork, integer *iwork, integer *info, ftnlen job_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: dlapy2_ 7 2 7 7 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: ztgexc_ 14 14 12 12 4 9 4 9 4 9 4 9 4 4 4 4 */
/*:ref: ztgsyl_ 14 23 13 4 4 4 9 4 9 4 9 4 9 4 9 4 9 4 7 7 9 4 4 4 124 */
extern int ztgsy2_(char *trans, integer *ijob, integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *c__, integer *ldc, doublecomplex *d__, integer *ldd, doublecomplex *e, integer *lde, doublecomplex *f, integer *ldf, doublereal *scale, doublereal *rdsum, doublereal *rdscal, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zgetc2_ 14 6 4 9 4 4 4 4 */
/*:ref: zgesc2_ 14 7 4 9 4 9 4 4 7 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zlatdf_ 14 9 4 4 9 4 9 7 7 4 4 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
extern int ztgsyl_(char *trans, integer *ijob, integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *c__, integer *ldc, doublecomplex *d__, integer *ldd, doublecomplex *e, integer *lde, doublecomplex *f, integer *ldf, doublereal *scale, doublereal *dif, doublecomplex *work, integer *lwork, integer *iwork, integer *info, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: ztgsy2_ 14 21 13 4 4 4 9 4 9 4 9 4 9 4 9 4 9 4 7 7 7 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
/*:ref: zgemm_ 14 15 13 13 4 4 4 9 9 4 9 4 9 9 4 124 124 */
extern int ztpcon_(char *norm, char *uplo, char *diag, integer *n, doublecomplex *ap, doublereal *rcond, doublecomplex *work, doublereal *rwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlantp_ 7 9 13 13 13 4 9 7 124 124 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zlatps_ 14 14 13 13 13 13 4 9 9 7 7 4 124 124 124 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdrscl_ 14 4 4 7 9 4 */
extern int ztprfs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, doublecomplex *ap, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: ztpmv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: ztpsv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
extern int ztptri_(char *uplo, char *diag, integer *n, doublecomplex *ap, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztpmv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int ztptrs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, doublecomplex *ap, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztpsv_ 14 10 13 13 13 4 9 9 4 124 124 124 */
extern int ztrcon_(char *norm, char *uplo, char *diag, integer *n, doublecomplex *a, integer *lda, doublereal *rcond, doublecomplex *work, doublereal *rwork, integer *info, ftnlen norm_len, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zlantr_ 7 11 13 13 13 4 4 9 4 7 124 124 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zlatrs_ 14 15 13 13 13 13 4 9 4 9 7 7 4 124 124 124 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdrscl_ 14 4 4 7 9 4 */
extern int ztrevc_(char *side, char *howmny, logical *select, integer *n, doublecomplex *t, integer *ldt, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, integer *mm, integer *m, doublecomplex *work, doublereal *rwork, integer *info, ftnlen side_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: dzasum_ 7 3 4 9 4 */
/*:ref: zlatrs_ 14 15 13 13 13 13 4 9 4 9 7 7 4 124 124 124 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
extern int ztrexc_(char *compq, integer *n, doublecomplex *t, integer *ldt, doublecomplex *q, integer *ldq, integer *ifst, integer *ilst, integer *info, ftnlen compq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlartg_ 14 5 9 9 7 9 9 */
/*:ref: zrot_ 14 7 4 9 4 9 4 7 9 */
extern int ztrrfs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: ztrmv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: ztrsv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
extern int ztrsen_(char *job, char *compq, logical *select, integer *n, doublecomplex *t, integer *ldt, doublecomplex *q, integer *ldq, doublecomplex *w, integer *m, doublereal *s, doublereal *sep, doublecomplex *work, integer *lwork, integer *info, ftnlen job_len, ftnlen compq_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: ztrexc_ 14 10 13 4 9 4 9 4 4 4 4 124 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: ztrsyl_ 14 15 13 13 4 4 4 9 4 9 4 9 4 7 4 124 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
extern int ztrsna_(char *job, char *howmny, logical *select, integer *n, doublecomplex *t, integer *ldt, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, doublereal *s, doublereal *sep, integer *mm, integer *m, doublecomplex *work, integer *ldwork, doublereal *rwork, integer *info, ftnlen job_len, ftnlen howmny_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
/*:ref: dznrm2_ 7 3 4 9 4 */
/*:ref: zlacpy_ 14 8 13 4 4 9 4 9 4 124 */
/*:ref: ztrexc_ 14 10 13 4 9 4 9 4 4 4 4 124 */
/*:ref: zlacon_ 14 5 4 9 9 7 4 */
/*:ref: zlatrs_ 14 15 13 13 13 13 4 9 4 9 7 7 4 124 124 124 124 */
/*:ref: izamax_ 4 3 4 9 4 */
/*:ref: zdrscl_ 14 4 4 7 9 4 */
extern int ztrsyl_(char *trana, char *tranb, integer *isgn, integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, doublecomplex *c__, integer *ldc, doublereal *scale, integer *info, ftnlen trana_len, ftnlen tranb_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: dlamch_ 7 2 13 124 */
/*:ref: dlabad_ 14 2 7 7 */
/*:ref: zlange_ 7 7 13 4 4 9 4 7 124 */
/*:ref: zdotu_ 9 6 9 4 9 4 9 4 */
/*:ref: zladiv_ 9 3 9 9 9 */
/*:ref: zdscal_ 14 4 4 7 9 4 */
/*:ref: zdotc_ 9 6 9 4 9 4 9 4 */
extern int ztrti2_(char *uplo, char *diag, integer *n, doublecomplex *a, integer *lda, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztrmv_ 14 11 13 13 13 4 9 4 9 4 124 124 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int ztrtri_(char *uplo, char *diag, integer *n, doublecomplex *a, integer *lda, integer *info, ftnlen uplo_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: ztrti2_ 14 8 13 13 4 9 4 4 124 124 */
/*:ref: ztrmm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
extern int ztrtrs_(char *uplo, char *trans, char *diag, integer *n, integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, integer *info, ftnlen uplo_len, ftnlen trans_len, ftnlen diag_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: ztrsm_ 14 15 13 13 13 13 4 4 9 9 4 9 4 124 124 124 124 */
extern int ztzrqf_(integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zlarfg_ 14 5 4 9 9 4 9 */
/*:ref: zcopy_ 14 5 4 9 4 9 4 */
/*:ref: zgemv_ 14 12 13 4 4 9 9 4 9 4 9 9 4 124 */
/*:ref: zaxpy_ 14 6 4 9 9 4 9 4 */
/*:ref: zgerc_ 14 9 4 4 9 9 4 9 4 9 4 */
extern int ztzrzf_(integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlatrz_ 14 7 4 4 4 9 4 9 9 */
/*:ref: zlarzt_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarzb_ 14 20 13 13 13 13 4 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zung2l_(integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zung2r_(integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zungbr_(char *vect, integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info, ftnlen vect_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zunglq_ 14 9 4 4 4 9 4 9 9 4 4 */
extern int zunghr_(integer *n, integer *ilo, integer *ihi, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
extern int zungl2_(integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zunglq_(integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zungl2_ 14 8 4 4 4 9 4 9 9 4 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zungql_(integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zung2l_ 14 8 4 4 4 9 4 9 9 4 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zungqr_(integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zung2r_ 14 8 4 4 4 9 4 9 9 4 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zungr2_(integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
/*:ref: zscal_ 14 4 4 9 9 4 */
extern int zungrq_(integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info);
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zungr2_ 14 8 4 4 4 9 4 9 9 4 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zungtr_(char *uplo, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zungql_ 14 9 4 4 4 9 4 9 9 4 4 */
/*:ref: zungqr_ 14 9 4 4 4 9 4 9 9 4 4 */
extern int zunm2l_(char *side, char *trans, integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
extern int zunm2r_(char *side, char *trans, integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
extern int zunmbr_(char *vect, char *side, char *trans, integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, integer *info, ftnlen vect_len, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zunmlq_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
extern int zunmhr_(char *side, char *trans, integer *m, integer *n, integer *ilo, integer *ihi, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
extern int zunml2_(char *side, char *trans, integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
extern int zunmlq_(char *side, char *trans, integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zunml2_ 14 14 13 13 4 4 4 9 4 9 9 4 9 4 124 124 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zunmql_(char *side, char *trans, integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zunm2l_ 14 14 13 13 4 4 4 9 4 9 9 4 9 4 124 124 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zunmqr_(char *side, char *trans, integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zunm2r_ 14 14 13 13 4 4 4 9 4 9 9 4 9 4 124 124 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zunmr2_(char *side, char *trans, integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlacgv_ 14 3 4 9 4 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
extern int zunmr3_(char *side, char *trans, integer *m, integer *n, integer *k, integer *l, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarz_ 14 11 13 4 4 4 9 4 9 9 4 9 124 */
extern int zunmrq_(char *side, char *trans, integer *m, integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zunmr2_ 14 14 13 13 4 4 4 9 4 9 9 4 9 4 124 124 */
/*:ref: zlarft_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarfb_ 14 19 13 13 13 13 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zunmrz_(char *side, char *trans, integer *m, integer *n, integer *k, integer *l, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zunmr3_ 14 15 13 13 4 4 4 4 9 4 9 9 4 9 4 124 124 */
/*:ref: zlarzt_ 14 11 13 13 4 4 9 4 9 9 4 124 124 */
/*:ref: zlarzb_ 14 20 13 13 13 13 4 4 4 4 9 4 9 4 9 4 9 4 124 124 124 124 */
extern int zunmtr_(char *side, char *uplo, char *trans, integer *m, integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, integer *info, ftnlen side_len, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: ilaenv_ 4 9 4 13 13 4 4 4 4 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zunmql_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
/*:ref: zunmqr_ 14 15 13 13 4 4 4 9 4 9 9 4 9 4 4 124 124 */
extern int zupgtr_(char *uplo, integer *n, doublecomplex *ap, doublecomplex *tau, doublecomplex *q, integer *ldq, doublecomplex *work, integer *info, ftnlen uplo_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zung2l_ 14 8 4 4 4 9 4 9 9 4 */
/*:ref: zung2r_ 14 8 4 4 4 9 4 9 9 4 */
extern int zupmtr_(char *side, char *uplo, char *trans, integer *m, integer *n, doublecomplex *ap, doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *info, ftnlen side_len, ftnlen uplo_len, ftnlen trans_len);
/*:ref: lsame_ 12 4 13 13 124 124 */
/*:ref: xerbla_ 14 3 13 4 124 */
/*:ref: zlarf_ 14 10 13 4 4 9 4 9 9 4 9 124 */
