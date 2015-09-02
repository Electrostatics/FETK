extern int builda_(integer *nx, integer *ny, integer *nz, integer *ipkey, integer *mgdisc, integer *numdia, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf);
extern int builda_fv__(integer *nx, integer *ny, integer *nz, integer *ipkey, integer *numdia, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf);
extern int builda_fe__(integer *nx, integer *ny, integer *nz, integer *ipkey, integer *numdia, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf);
extern int buildband_(integer *key, integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, integer *ipcb, doublereal *rpcb, doublereal *acb);
extern int buildband1_7__(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, integer *ipcb, doublereal *rpcb, doublereal *acb, integer *n, integer *m, integer *lda);
extern int buildband1_27__(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, integer *ipcb, doublereal *rpcb, doublereal *acb, integer *n, integer *m, integer *lda);
/*:ref: dpbfa_ 14 5 7 4 4 4 4 */
extern int buildg_(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *numdia, doublereal *pcff, doublereal *acff, doublereal *ac);
extern int buildg_1__(integer *nxf, integer *nyf, integer *nzf, integer *nx, integer *ny, integer *nz, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw, doublereal *oc, doublereal *xoc, doublereal *xoe, doublereal *xon, doublereal *xuc, doublereal *xone, doublereal *xonw, doublereal *xue, doublereal *xuw, doublereal *xun, doublereal *xus, doublereal *xune, doublereal *xunw, doublereal *xuse, doublereal *xusw);
extern int buildg_7__(integer *nxf, integer *nyf, integer *nzf, integer *nx, integer *ny, integer *nz, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *xoc, doublereal *xoe, doublereal *xon, doublereal *xuc, doublereal *xone, doublereal *xonw, doublereal *xue, doublereal *xuw, doublereal *xun, doublereal *xus, doublereal *xune, doublereal *xunw, doublereal *xuse, doublereal *xusw);
extern int buildg_27__(integer *nxf, integer *nyf, integer *nzf, integer *nx, integer *ny, integer *nz, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *xoc, doublereal *xoe, doublereal *xon, doublereal *xuc, doublereal *xone, doublereal *xonw, doublereal *xue, doublereal *xuw, doublereal *xun, doublereal *xus, doublereal *xune, doublereal *xunw, doublereal *xuse, doublereal *xusw);
extern int buildp_(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *mgprol, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *xf, doublereal *yf, doublereal *zf);
extern int buildp_trilin__(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, doublereal *pc, doublereal *xf, doublereal *yf, doublereal *zf);
extern int buildpb_trilin__(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw, doublereal *xf, doublereal *yf, doublereal *zf);
extern int buildp_op7__(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *pc);
extern int buildpb_op7__(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw);
extern int buildp_op27__(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *pc);
extern int buildpb_op27__(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw);
extern int buildp_modop7__(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *pc);
extern int buildpb_modop7__(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw);
extern int buildp_modop27__(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *pc);
extern int buildpb_modop27__(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw);
extern int cghs_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *p, doublereal *ap, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
/*:ref: mresid_ 14 10 4 4 4 4 7 7 7 7 7 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: xscal_ 14 5 4 4 4 7 7 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
extern int fcgmg_(integer *nx, integer *ny, integer *nz, doublereal *x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, doublereal *w3, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *nlev, integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, integer *mgsmoo, doublereal *w4, doublereal *w5, doublereal *w6, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int cgmg_(integer *nx, integer *ny, integer *nz, doublereal *x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, doublereal *w3, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *nlev, integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, integer *mgsmoo, doublereal *rr, doublereal *zz, doublereal *pp, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int getpre_(integer *nx, integer *ny, integer *nz, integer *iz, integer *lev, integer *nlev_real__, doublereal *r__, doublereal *pc);
/*:ref: mkcors_ 14 7 4 4 4 4 4 4 4 */
/*:ref: mkfine_ 14 7 4 4 4 4 4 4 4 */
/*:ref: interp_ 14 9 4 4 4 4 4 4 7 7 7 */
/*:ref: prtini_ 14 1 4 */
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: xnrm1_ 7 4 4 4 4 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: mresid_ 14 10 4 4 4 4 7 7 7 7 7 7 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: mvcs_ 14 32 4 4 4 7 4 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 4 7 7 7 7 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: xscal_ 14 5 4 4 4 7 7 */
/*:ref: restrc_ 14 9 4 4 4 4 4 4 7 7 7 */
extern int cgmgdriv_(integer *iparm, doublereal *rparm, integer *iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int cgmgdriv2_(integer *iparm, doublereal *rparm, integer *nx, integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *w1, doublereal *w2, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
/*:ref: maxlev_ 4 3 4 4 4 */
/*:ref: mgsz_ 14 19 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 */
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: buildstr_ 14 5 4 4 4 4 4 */
/*:ref: tstart_ 14 2 7 7 */
/*:ref: buildops_ 14 30 4 4 4 4 4 4 4 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: tstop_ 14 3 7 7 7 */
/*:ref: buildalg_ 14 14 4 4 4 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: epsmac_ 7 1 4 */
/*:ref: fbound00_ 14 4 4 4 4 7 */
/*:ref: cgmg_ 14 35 4 4 4 7 4 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 7 7 7 4 7 7 7 7 7 7 */
/*:ref: fcgmg_ 14 35 4 4 4 7 4 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 7 7 7 4 7 7 7 7 7 7 */
/*:ref: fbound_ 14 8 4 4 4 4 7 7 7 7 */
extern int gsrb_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int gsrb7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int gsrb27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int gsrb7x_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
/*:ref: mresid7_1s__ 14 13 4 4 4 4 7 7 7 7 7 7 7 7 7 */
/*:ref: mresid27_1s__ 14 23 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
extern int matvec_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, doublereal *y);
extern int matvec7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, doublereal *y);
extern int matvec7_1s__(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *y);
extern int matvec27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, doublereal *y);
extern int matvec27_1s__(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *y);
extern int mresid_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *r__);
extern int mresid7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *r__);
extern int mresid7_1s__(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *r__);
extern int mresid27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *r__);
extern int mresid27_1s__(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *r__);
extern int nmatvec_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, doublereal *y, doublereal *w1);
extern int nmatvec7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, doublereal *y, doublereal *w1);
extern int nmatvecd7_1s__(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *y, doublereal *w1);
extern int nmatvec27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *x, doublereal *y, doublereal *w1);
extern int nmatvecd27_1s__(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *y, doublereal *w1);
extern int nmresid_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *r__, doublereal *w1);
extern int nmresid7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *r__, doublereal *w1);
extern int nmresid7_1s__(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *r__, doublereal *w1);
extern int nmresid27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *r__, doublereal *w1);
extern int nmresid27_1s__(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *r__, doublereal *w1);
extern int interp_(integer *nxc, integer *nyc, integer *nzc, integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal *xout, doublereal *pc);
extern int interp2_(integer *nxc, integer *nyc, integer *nzc, integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal *xout, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw);
extern int restrc_(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, doublereal *xin, doublereal *xout, doublereal *pc);
extern int restrc2_(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, doublereal *xin, doublereal *xout, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw);
extern int extrac_(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, doublereal *xin, doublereal *xout);
extern int interpz_(integer *nxc, integer *nyc, integer *nzc, integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal *xout);
extern int restrcz_(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, doublereal *xin, doublereal *xout);
/*:ref: c_vec__ 14 7 7 7 7 4 4 4 4 */
/*:ref: fbound00_ 14 4 4 4 4 7 */
extern int daxpy_(integer *n, doublereal *alpha, doublereal *x, integer *istep, doublereal *y, integer *jstep);
extern int dcopy_(integer *n, doublereal *x, integer *istep, doublereal *y, integer *jstep);
extern doublereal dasum_(integer *n, doublereal *x, integer *istep);
extern doublereal dnrm1_(integer *n, doublereal *x, integer *istep);
extern doublereal dnrm2_(integer *n, doublereal *x, integer *istep);
extern doublereal dnrm8_(integer *n, doublereal *x, integer *istep);
extern int dscal_(integer *n, doublereal *fac, doublereal *x, integer *istep);
extern doublereal ddot_(integer *n, doublereal *x, integer *istep, doublereal *y, integer *jstep);
extern integer idamax_(integer *n, doublereal *sx, integer *incx);
extern int fmvcs_(integer *nx, integer *ny, integer *nz, doublereal *x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, doublereal *w3, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *nlev, integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, integer *mgsmoo, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int mvcs_(integer *nx, integer *ny, integer *nz, doublereal *x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, doublereal *w3, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *nlev, integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, integer *mgsmoo, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
/*:ref: mkcors_ 14 7 4 4 4 4 4 4 4 */
/*:ref: mkfine_ 14 7 4 4 4 4 4 4 4 */
/*:ref: interp_ 14 9 4 4 4 4 4 4 7 7 7 */
/*:ref: prtini_ 14 1 4 */
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: xnrm1_ 7 4 4 4 4 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: smooth_ 14 19 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 4 */
/*:ref: xcopy_small__ 14 5 4 4 4 7 7 */
/*:ref: dpbsl_ 14 5 7 4 4 4 7 */
/*:ref: xcopy_large__ 14 5 4 4 4 7 7 */
/*:ref: fbound00_ 14 4 4 4 4 7 */
/*:ref: mresid_ 14 10 4 4 4 4 7 7 7 7 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: ivariv_ 4 2 4 4 */
/*:ref: restrc_ 14 9 4 4 4 4 4 4 7 7 7 */
extern int mgdriv_(integer *iparm, doublereal *rparm, integer *iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int mgdriv2_(integer *iparm, doublereal *rparm, integer *nx, integer *ny, integer *nz, doublereal *u, integer *iz, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int mgsz_(integer *mgcoar, integer *mgdisc, integer *mgsolv, integer *nx, integer *ny, integer *nz, integer *nlev, integer *nxc, integer *nyc, integer *nzc, integer *nf, integer *nc, integer *narr, integer *narrc, integer *n_rpc__, integer *n_iz__, integer *n_ipc__, integer *iretot, integer *iintot);
extern int mgsize_(integer *mgcoar, integer *mgdisc, integer *mgsolv, integer *nx, integer *ny, integer *nz, integer *nlev);
/*:ref: maxlev_ 4 3 4 4 4 */
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: buildstr_ 14 5 4 4 4 4 4 */
/*:ref: tstart_ 14 2 7 7 */
/*:ref: buildops_ 14 30 4 4 4 4 4 4 4 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: tstop_ 14 3 7 7 7 */
/*:ref: epsmac_ 7 1 4 */
/*:ref: mkcors_ 14 7 4 4 4 4 4 4 4 */
/*:ref: power_ 14 19 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 4 4 4 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: ipower_ 14 33 4 4 4 7 4 7 7 7 7 7 7 7 7 4 4 4 4 4 4 4 4 7 7 7 4 4 4 4 7 7 7 7 7 */
/*:ref: mpower_ 14 33 4 4 4 7 4 7 7 7 7 7 7 7 4 4 4 4 4 4 4 4 7 7 7 4 4 4 4 7 7 7 7 7 7 */
/*:ref: buildalg_ 14 14 4 4 4 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: fbound00_ 14 4 4 4 4 7 */
/*:ref: mvcs_ 14 32 4 4 4 7 4 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 4 7 7 7 7 7 7 */
/*:ref: fmvcs_ 14 32 4 4 4 7 4 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 4 7 7 7 7 7 7 */
/*:ref: mvfas_ 14 33 4 4 4 7 4 7 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 4 7 7 7 7 7 7 */
/*:ref: fmvfas_ 14 33 4 4 4 7 4 7 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 4 7 7 7 7 7 7 */
/*:ref: fbound_ 14 8 4 4 4 4 7 7 7 7 */
extern int fmvfas_(integer *nx, integer *ny, integer *nz, doublereal *x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, doublereal *w3, doublereal *w4, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *nlev, integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, integer *mgsmoo, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int mvfas_(integer *nx, integer *ny, integer *nz, doublereal *x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, doublereal *w3, doublereal *w4, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *nlev, integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, integer *mgsmoo, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
/*:ref: mkcors_ 14 7 4 4 4 4 4 4 4 */
/*:ref: mkfine_ 14 7 4 4 4 4 4 4 4 */
/*:ref: interp_ 14 9 4 4 4 4 4 4 7 7 7 */
/*:ref: prtini_ 14 1 4 */
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: nmresid_ 14 11 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: xnrm1_ 7 4 4 4 4 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: nmatvec_ 14 10 4 4 4 4 7 7 7 7 7 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: nsmooth_ 14 19 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 4 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: ivariv_ 4 2 4 4 */
/*:ref: restrc_ 14 9 4 4 4 4 4 4 7 7 7 */
/*:ref: extrac_ 14 8 4 4 4 4 4 4 7 7 */
/*:ref: linesearch_ 14 15 4 4 4 7 4 7 7 7 7 7 7 7 7 7 7 */
extern integer maxlev_(integer *n1, integer *n2, integer *n3);
extern int mkcors_(integer *numlev, integer *nxold, integer *nyold, integer *nzold, integer *nxnew, integer *nynew, integer *nznew);
extern int corsr_(integer *nold, integer *nnew);
extern int mkfine_(integer *numlev, integer *nxold, integer *nyold, integer *nzold, integer *nxnew, integer *nynew, integer *nznew);
extern int finer_(integer *nold, integer *nnew);
extern integer ivariv_(integer *nu, integer *level);
extern int prtini_(integer *istop);
extern int prtstp_(integer *iok, integer *iters, doublereal *rsnrm, doublereal *rsden, doublereal *orsnrm);
extern int buildstr_(integer *nx, integer *ny, integer *nz, integer *nlev, integer *iz);
extern int buildops_(integer *nx, integer *ny, integer *nz, integer *nlev, integer *ipkey, integer *iinfo, integer *ido, integer *iz, integer *mgprol, integer *mgcoar, integer *mgsolv, integer *mgdisc, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int buildcopy0_(integer *nx, integer *ny, integer *nz, integer *nxf, integer *nyf, integer *nzf, doublereal *xc, doublereal *yc, doublereal *zc, doublereal *gxc, doublereal *gyc, doublereal *gzc, doublereal *a1c, doublereal *a2c, doublereal *a3c, doublereal *cc, doublereal *fc, doublereal *tc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int buildharm0_(integer *nx, integer *ny, integer *nz, integer *nxf, integer *nyf, integer *nzf, doublereal *xc, doublereal *yc, doublereal *zc, doublereal *gxc, doublereal *gyc, doublereal *gzc, doublereal *a1c, doublereal *a2c, doublereal *a3c, doublereal *cc, doublereal *fc, doublereal *tc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int buildgaler0_(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *ipkey, integer *numdia, doublereal *pcff, integer *ipcff, doublereal *rpcff, doublereal *acff, doublereal *ccff, doublereal *fcff, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc);
extern int buildgaler1_(integer *nxf, integer *nyf, integer *nzf, integer *nxc, integer *nyc, integer *nzc, integer *numdia, doublereal *pcff, integer *ipcff, doublereal *rpcff, doublereal *ccff, integer *ipc, doublereal *rpc, doublereal *cc);
extern int buildalg_(integer *nx, integer *ny, integer *nz, integer *mode, integer *nlev, integer *iz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *y, doublereal *tmp);
/*:ref: tstart_ 14 2 7 7 */
/*:ref: tstop_ 14 3 7 7 7 */
/*:ref: builda_ 14 22 4 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: prtmatd_ 14 6 4 4 4 4 7 7 */
/*:ref: buildp_ 14 14 4 4 4 4 4 4 4 4 7 7 7 7 7 7 */
/*:ref: extrac_ 14 8 4 4 4 4 4 4 7 7 */
/*:ref: buildband_ 14 10 4 4 4 4 4 7 7 4 7 7 */
/*:ref: buildg_ 14 10 4 4 4 4 4 4 4 7 7 7 */
/*:ref: restrc_ 14 9 4 4 4 4 4 4 7 7 7 */
/*:ref: nmatvec_ 14 11 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
extern doublereal epsmac_(integer *idum);
extern int tstart_(doublereal *before, doublereal *overhd);
extern int tstop_(doublereal *before, doublereal *overhd, doublereal *cputme);
extern int xaxpy_(integer *nx, integer *ny, integer *nz, doublereal *alpha, doublereal *x, doublereal *y);
extern int xcopy_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *y);
extern doublereal xnrm1_(integer *nx, integer *ny, integer *nz, doublereal *x);
extern doublereal xnrm2_(integer *nx, integer *ny, integer *nz, doublereal *x);
extern doublereal xnrm8_(integer *nx, integer *ny, integer *nz, doublereal *x);
extern int xscal_(integer *nx, integer *ny, integer *nz, doublereal *fac, doublereal *x);
extern doublereal xdot_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *y);
extern doublereal xdot3_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *y);
extern int zeros_(integer *nx, integer *ny, integer *nz, doublereal *x);
extern int xrand_(integer *nx, integer *ny, integer *nz, doublereal *x);
extern int cinit_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *value);
extern int azeros_(integer *nx, integer *ny, integer *nz, doublereal *x);
extern int axrand_(integer *nx, integer *ny, integer *nz, doublereal *x);
extern int xcopy_small__(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *y);
extern int xcopy_large__(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *y);
extern int fbound_(integer *ibound, integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *gxc, doublereal *gyc, doublereal *gzc);
extern int fbound00_(integer *nx, integer *ny, integer *nz, doublereal *x);
extern int xprint_(integer *nx, integer *ny, integer *nz, doublereal *x);
extern int prtmatd_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac);
extern int prtmatd7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc);
extern int prtmatd27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw);
extern int prtmatb_(doublereal *a, integer *n, integer *m, integer *lda);
extern int linesearch_(integer *nx, integer *ny, integer *nz, doublereal *alpha, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *p, doublereal *x, doublereal *r__, doublereal *ap, doublereal *zk, doublereal *zkp1);
/*:ref: tsecnd_ 7 0 */
/*:ref: rand_ 6 1 4 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
/*:ref: c_vec__ 14 7 7 7 7 4 4 4 4 */
/*:ref: dc_vec__ 14 7 7 7 7 4 4 4 4 */
extern int dpbco_(doublereal *abd, integer *lda, integer *n, integer *m, doublereal *rcond, doublereal *z__, integer *info);
extern int dpbfa_(doublereal *abd, integer *lda, integer *n, integer *m, integer *info);
extern int dpbsl_(doublereal *abd, integer *lda, integer *n, integer *m, doublereal *b);
/*:ref: dasum_ 7 3 4 7 4 */
/*:ref: dscal_ 14 4 4 7 7 4 */
/*:ref: daxpy_ 14 6 4 7 7 4 7 4 */
/*:ref: ddot_ 7 5 4 7 4 7 4 */
extern int ncghs_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *p, doublereal *ap, doublereal *r__, doublereal *zk, doublereal *zkp1, doublereal *tmp, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
/*:ref: nmresid_ 14 11 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: xscal_ 14 5 4 4 4 7 7 */
/*:ref: linesearch_ 14 15 4 4 4 7 4 7 7 7 7 7 7 7 7 7 7 */
extern int ncghsdriv_(integer *iparm, doublereal *rparm, integer *iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int ncghsdriv2_(integer *iparm, doublereal *rparm, integer *nx, integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *w0, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int ncghsgo_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *r__, doublereal *p, doublereal *ap, doublereal *zk, doublereal *zkp1, doublereal *tmp, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int cghsgo_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *r__, doublereal *p, doublereal *ap, doublereal *zk, doublereal *zkp1, doublereal *tmp, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: buildstr_ 14 5 4 4 4 4 4 */
/*:ref: tstart_ 14 2 7 7 */
/*:ref: buildops_ 14 30 4 4 4 4 4 4 4 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: tstop_ 14 3 7 7 7 */
/*:ref: nmatvec_ 14 10 4 4 4 4 7 7 7 7 7 7 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
/*:ref: epsmac_ 7 1 4 */
/*:ref: fbound00_ 14 4 4 4 4 7 */
/*:ref: fbound_ 14 8 4 4 4 4 7 7 7 7 */
/*:ref: prtini_ 14 1 4 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: nmresid_ 14 11 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: xnrm1_ 7 4 4 4 4 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: xscal_ 14 5 4 4 4 7 7 */
/*:ref: linesearch_ 14 15 4 4 4 7 4 7 7 7 7 7 7 7 7 7 7 */
/*:ref: mresid_ 14 10 4 4 4 4 7 7 7 7 7 7 */
extern int newdriv_(integer *iparm, doublereal *rparm, integer *iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int newdriv2_(integer *iparm, doublereal *rparm, integer *nx, integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *w1, doublereal *w2, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
/*:ref: maxlev_ 4 3 4 4 4 */
/*:ref: mgsz_ 14 19 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 */
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: buildstr_ 14 5 4 4 4 4 4 */
/*:ref: tstart_ 14 2 7 7 */
/*:ref: buildops_ 14 30 4 4 4 4 4 4 4 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: tstop_ 14 3 7 7 7 */
/*:ref: buildalg_ 14 14 4 4 4 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: epsmac_ 7 1 4 */
/*:ref: fbound00_ 14 4 4 4 4 7 */
/*:ref: newton_ 14 35 4 4 4 7 4 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 7 7 7 4 7 7 7 7 7 7 */
/*:ref: fnewton_ 14 35 4 4 4 7 4 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 7 7 7 4 7 7 7 7 7 7 */
/*:ref: fbound_ 14 8 4 4 4 4 7 7 7 7 */
extern int fnewton_(integer *nx, integer *ny, integer *nz, doublereal *x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, doublereal *w3, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *nlev, integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, integer *mgsmoo, doublereal *cprime, doublereal *rhs, doublereal *xtmp, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int newton_(integer *nx, integer *ny, integer *nz, doublereal *x, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, doublereal *w3, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *nlev, integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, integer *mgsmoo, doublereal *cprime, doublereal *rhs, doublereal *xtmp, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int getjac_(integer *nx, integer *ny, integer *nz, integer *nlev_real__, integer *iz, integer *lev, integer *ipkey, doublereal *x, doublereal *r__, doublereal *cprime, doublereal *rhs, doublereal *cc, doublereal *pc);
/*:ref: mkcors_ 14 7 4 4 4 4 4 4 4 */
/*:ref: mkfine_ 14 7 4 4 4 4 4 4 4 */
/*:ref: interp_ 14 9 4 4 4 4 4 4 7 7 7 */
/*:ref: prtini_ 14 1 4 */
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: nmresid_ 14 11 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: xnrm1_ 7 4 4 4 4 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: nmatvec_ 14 10 4 4 4 4 7 7 7 7 7 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: mvcs_ 14 32 4 4 4 7 4 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 4 7 7 7 7 7 7 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: power_ 14 19 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 4 4 4 */
/*:ref: ipower_ 14 33 4 4 4 7 4 7 7 7 7 7 7 7 7 4 4 4 4 4 4 4 4 7 7 7 4 4 4 4 7 7 7 7 7 */
/*:ref: dc_vec__ 14 7 7 7 7 4 4 4 4 */
/*:ref: restrc_ 14 9 4 4 4 4 4 4 7 7 7 */
extern int ngsrb_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int ngsrb7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int ngsrb27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int ngsrb7x_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
/*:ref: c_scal__ 7 3 7 7 4 */
/*:ref: dc_scal__ 7 3 7 7 4 */
/*:ref: nmresid7_1s__ 14 14 4 4 4 4 7 7 7 7 7 7 7 7 7 7 */
/*:ref: nmresid27_1s__ 14 24 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
extern int ngsrbdriv_(integer *iparm, doublereal *rparm, integer *iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int ngsrbdriv2_(integer *iparm, doublereal *rparm, integer *nx, integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *w0, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int ngsrbgo_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *r__, doublereal *w1, doublereal *w2, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int gsrbgo_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *r__, doublereal *w1, doublereal *w2, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: buildstr_ 14 5 4 4 4 4 4 */
/*:ref: tstart_ 14 2 7 7 */
/*:ref: buildops_ 14 30 4 4 4 4 4 4 4 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: tstop_ 14 3 7 7 7 */
/*:ref: nmatvec_ 14 10 4 4 4 4 7 7 7 7 7 7 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
/*:ref: epsmac_ 7 1 4 */
/*:ref: fbound00_ 14 4 4 4 4 7 */
/*:ref: fbound_ 14 8 4 4 4 4 7 7 7 7 */
/*:ref: prtini_ 14 1 4 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: nmresid_ 14 11 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: xnrm1_ 7 4 4 4 4 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: ngsrb_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: gsrb_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
extern int ninterp_(integer *nxc, integer *nyc, integer *nzc, integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal *xout, doublereal *pc, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc);
extern int ninterp7_(integer *nxc, integer *nyc, integer *nzc, integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal *xout, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *cc, doublereal *fc);
extern int ninterp27_(integer *nxc, integer *nyc, integer *nzc, integer *nxf, integer *nyf, integer *nzf, doublereal *xin, doublereal *xout, doublereal *opc, doublereal *opn, doublereal *ops, doublereal *ope, doublereal *opw, doublereal *opne, doublereal *opnw, doublereal *opse, doublereal *opsw, doublereal *upc, doublereal *upn, doublereal *ups, doublereal *upe, doublereal *upw, doublereal *upne, doublereal *upnw, doublereal *upse, doublereal *upsw, doublereal *dpc, doublereal *dpn, doublereal *dps, doublereal *dpe, doublereal *dpw, doublereal *dpne, doublereal *dpnw, doublereal *dpse, doublereal *dpsw, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *cc, doublereal *fc);
/*:ref: fbound00_ 14 4 4 4 4 7 */
/*:ref: c_scal__ 7 3 7 7 4 */
/*:ref: dc_scal__ 7 3 7 7 4 */
extern int nrich_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int nrich7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int nrich27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
/*:ref: nmresid7_1s__ 14 14 4 4 4 4 7 7 7 7 7 7 7 7 7 7 */
/*:ref: mresid27_1s__ 14 23 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: nmresid27_1s__ 14 24 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
extern int nrichdriv_(integer *iparm, doublereal *rparm, integer *iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int nrichdriv2_(integer *iparm, doublereal *rparm, integer *nx, integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *w0, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int nrichgo_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *r__, doublereal *w1, doublereal *w2, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int richgo_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *r__, doublereal *w1, doublereal *w2, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: buildstr_ 14 5 4 4 4 4 4 */
/*:ref: tstart_ 14 2 7 7 */
/*:ref: buildops_ 14 30 4 4 4 4 4 4 4 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: tstop_ 14 3 7 7 7 */
/*:ref: nmatvec_ 14 10 4 4 4 4 7 7 7 7 7 7 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
/*:ref: epsmac_ 7 1 4 */
/*:ref: fbound00_ 14 4 4 4 4 7 */
/*:ref: fbound_ 14 8 4 4 4 4 7 7 7 7 */
/*:ref: prtini_ 14 1 4 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: nmresid_ 14 11 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: xnrm1_ 7 4 4 4 4 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: nrich_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: rich_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
extern int nsmooth_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint, integer *meth);
/*:ref: nwjac_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: ngsrb_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: nsor_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: nrich_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
extern int nsor_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int nsor7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int nsor27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
/*:ref: c_scal__ 7 3 7 7 4 */
/*:ref: dc_scal__ 7 3 7 7 4 */
/*:ref: nmresid7_1s__ 14 14 4 4 4 4 7 7 7 7 7 7 7 7 7 7 */
/*:ref: nmresid27_1s__ 14 24 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
extern int nsordriv_(integer *iparm, doublereal *rparm, integer *iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int nsordriv2_(integer *iparm, doublereal *rparm, integer *nx, integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *w0, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int nsorgo_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *r__, doublereal *w1, doublereal *w2, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int sorgo_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *r__, doublereal *w1, doublereal *w2, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: buildstr_ 14 5 4 4 4 4 4 */
/*:ref: tstart_ 14 2 7 7 */
/*:ref: buildops_ 14 30 4 4 4 4 4 4 4 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: tstop_ 14 3 7 7 7 */
/*:ref: nmatvec_ 14 10 4 4 4 4 7 7 7 7 7 7 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
/*:ref: epsmac_ 7 1 4 */
/*:ref: fbound00_ 14 4 4 4 4 7 */
/*:ref: fbound_ 14 8 4 4 4 4 7 7 7 7 */
/*:ref: prtini_ 14 1 4 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: nmresid_ 14 11 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: xnrm1_ 7 4 4 4 4 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: nsor_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: sor_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
extern int nwjac_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int nwjac7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int nwjac27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
/*:ref: c_scal__ 7 3 7 7 4 */
/*:ref: dc_scal__ 7 3 7 7 4 */
/*:ref: nmresid7_1s__ 14 14 4 4 4 4 7 7 7 7 7 7 7 7 7 7 */
/*:ref: nmresid27_1s__ 14 24 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
extern int nwjacdriv_(integer *iparm, doublereal *rparm, integer *iwork, doublereal *rwork, doublereal *u, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int nwjacdriv2_(integer *iparm, doublereal *rparm, integer *nx, integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *w0, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *xf, doublereal *yf, doublereal *zf, doublereal *gxcf, doublereal *gycf, doublereal *gzcf, doublereal *a1cf, doublereal *a2cf, doublereal *a3cf, doublereal *ccf, doublereal *fcf, doublereal *tcf);
extern int nwjacgo_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *r__, doublereal *w1, doublereal *w2, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
extern int wjacgo_(integer *nx, integer *ny, integer *nz, doublereal *x, doublereal *r__, doublereal *w1, doublereal *w2, integer *istop, integer *itmax, integer *iters, integer *ierror, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
/*:ref: prtstp_ 14 5 4 4 7 7 7 */
/*:ref: buildstr_ 14 5 4 4 4 4 4 */
/*:ref: tstart_ 14 2 7 7 */
/*:ref: buildops_ 14 30 4 4 4 4 4 4 4 4 4 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
/*:ref: tstop_ 14 3 7 7 7 */
/*:ref: nmatvec_ 14 10 4 4 4 4 7 7 7 7 7 7 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
/*:ref: epsmac_ 7 1 4 */
/*:ref: fbound00_ 14 4 4 4 4 7 */
/*:ref: fbound_ 14 8 4 4 4 4 7 7 7 7 */
/*:ref: prtini_ 14 1 4 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: nmresid_ 14 11 4 4 4 4 7 7 7 7 7 7 7 */
/*:ref: xnrm1_ 7 4 4 4 4 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: nwjac_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: wjac_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
extern int power_(integer *nx, integer *ny, integer *nz, integer *iz, integer *ilev, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *w1, doublereal *w2, doublereal *w3, doublereal *w4, doublereal *eigmax, doublereal *eigmax_model__, doublereal *tol, integer *itmax, integer *iters, integer *iinfo);
extern int ipower_(integer *nx, integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, doublereal *w3, doublereal *w4, doublereal *eigmin, doublereal *eigmin_model__, doublereal *tol, integer *itmax, integer *iters, integer *nlev, integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, integer *mgsmoo, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *tru);
extern int mpower_(integer *nx, integer *ny, integer *nz, doublereal *u, integer *iz, doublereal *w0, doublereal *w1, doublereal *w2, doublereal *w3, doublereal *w4, doublereal *eigmax, doublereal *tol, integer *itmax, integer *iters, integer *nlev, integer *ilev, integer *nlev_real__, integer *mgsolv, integer *iok, integer *iinfo, doublereal *epsiln, doublereal *errtol, doublereal *omega, integer *nu1, integer *nu2, integer *mgsmoo, integer *ipc, doublereal *rpc, doublereal *pc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *tru);
/*:ref: axrand_ 14 4 4 4 4 7 */
/*:ref: azeros_ 14 4 4 4 4 7 */
/*:ref: xnrm2_ 7 4 4 4 4 7 */
/*:ref: xscal_ 14 5 4 4 4 7 7 */
/*:ref: matvec_ 14 9 4 4 4 4 7 7 7 7 7 */
/*:ref: xdot_ 7 5 4 4 4 7 7 */
/*:ref: xcopy_ 14 5 4 4 4 7 7 */
/*:ref: xaxpy_ 14 6 4 4 4 7 7 7 */
/*:ref: mvcs_ 14 32 4 4 4 7 4 7 7 7 7 4 4 4 4 4 4 4 4 4 4 7 7 7 4 4 4 4 7 7 7 7 7 7 */
extern int rich_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int rich7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int rich27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
/*:ref: mresid7_1s__ 14 13 4 4 4 4 7 7 7 7 7 7 7 7 7 */
/*:ref: mresid27_1s__ 14 23 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
extern int smooth_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint, integer *meth);
/*:ref: wjac_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: gsrb_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: sor_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: rich_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
/*:ref: cghs_ 14 18 4 4 4 4 7 7 7 7 7 7 7 7 4 4 7 7 4 4 */
extern int sor_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int sor7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int sor27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
/*:ref: mresid7_1s__ 14 13 4 4 4 4 7 7 7 7 7 7 7 7 7 */
/*:ref: mresid27_1s__ 14 23 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
extern int wjac_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *ac, doublereal *cc, doublereal *fc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int wjac7_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
extern int wjac27_(integer *nx, integer *ny, integer *nz, integer *ipc, doublereal *rpc, doublereal *oc, doublereal *cc, doublereal *fc, doublereal *oe, doublereal *on, doublereal *uc, doublereal *one, doublereal *onw, doublereal *ue, doublereal *uw, doublereal *un, doublereal *us, doublereal *une, doublereal *unw, doublereal *use, doublereal *usw, doublereal *x, doublereal *w1, doublereal *w2, doublereal *r__, integer *itmax, integer *iters, doublereal *errtol, doublereal *omega, integer *iresid, integer *iadjoint);
/*:ref: mresid7_1s__ 14 13 4 4 4 4 7 7 7 7 7 7 7 7 7 */
/*:ref: mresid27_1s__ 14 23 4 4 4 4 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 */
