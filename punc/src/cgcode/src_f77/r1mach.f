      FUNCTION R1MACH (IDUM)
      INTEGER IDUM
C-----------------------------------------------------------------------
C this routine computes the unit roundoff of the machine in double
C precision.  this is defined as the smallest positive machine number
C u such that  1.0e0 + u .ne. 1.0e0 (in single precision).
C-----------------------------------------------------------------------
      REAL U, COMP
      U = 1.0E0
 10   U = U*0.5E0
      COMP = 1.0E0 + U
      IF (COMP .NE. 1.0E0) GO TO 10
      R1MACH = U*2.0E0
      RETURN
C----------------------- end of function R1MACH ------------------------
      END
