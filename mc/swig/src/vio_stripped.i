#define VPORTNUMBER 14916   
#define VIO_MAXBUF 10       

typedef enum VIOtype {
    VIO_NO_TYPE, 
    VIO_SDIO,
    VIO_BUFF,
    VIO_FILE,
    VIO_UNIX,
    VIO_INET
} VIOtype;

typedef enum VIOfrmt {
    VIO_NO_FRMT,
    VIO_XDR,
    VIO_ASC
} VIOfrmt;

typedef enum VIOrwkey {
    VIO_NO_RW,
    VIO_R,
    VIO_W
} VIOrwkey;

typedef struct Vio {

    VIOtype type;       /**< file (or device) type.                          
                         *   VIO_NO_TYPE = not initialized.
                         *   VIO_SDIO    = standard I/O.
                         *   VIO_FILE    = file I/O.                   
                         *   VIO_BUFF    = buffer I/O.                      
                         *   VIO_UNIX    = UNIX (domain) socket I/O.
                         *   VIO_INET    = INET (network) socket I/O.        */

    VIOfrmt frmt;       /**< data format.
                         *   VIO_NO_FRMT = not initialized.                
                         *   VIO_ASC     = ASCII (FILE,BUFF,UNIX,INET).
                         *   VIO_XDR     = BINARY (FILE,BUFF,UNIX,INET).     */

    VIOrwkey rwkey;     /**< r/w key.
                         *   VIO_NO_R = not initialized.
                         *   VIO_R    = read (FILE,BUFF,UNIX,INET)
                         *   VIO_W    = write (FILE,BUFF,UNIX,INET)          */

    char file[VMAX_ARGLEN];   /**< file or device name (FILE,BUFF,UNIX,INET) */
    char lhost[VMAX_ARGLEN];  /**< local hostname (me) (UNIX,INET)           */
    char rhost[VMAX_ARGLEN];  /**< remote hostname (other guy) (UNIX,INET)   */

    int error;        /**< note if any error has occurred on this vio device */
    int dirty;        /**< dirty read bit -- have we read file yet (FILE)    */

    FILE *fp;         /**< file pointer (SDIO,FILE)                          */
    int so;           /**< primary unix domain or inet socket (UNIX,INET)    */
    int soc;          /**< subsocket created for socket reading (UNIX,INET)  */
    void *name;       /**< &sockaddr_un or &sockaddr_in (UNIX,INET)          */
    void *axdr;       /**< ASC/XDR structure pointer (ASC,XDR)               */

    char whiteChars[VMAX_ARGNUM]; /**< white space character set (ASC)       */
    char commChars[VMAX_ARGNUM];  /**< comment character set (ASC,XDR)       */

    char ioBuffer[VMAX_BUFSIZE];  /**< I/O buffer (ASC,XDR)                  */
    int ioBufferLen;              /**< I/O buffer length (ASC,XDR)           */

    char putBuffer[VMAX_BUFSIZE]; /**< final write buffer (ASC,XDR)          */
    int putBufferLen;             /**< final write buffer length (ASC,XDR)   */

    char *VIObuffer;    /**< (BUFF) */
    int VIObufferLen;   /**< (BUFF) */
    int VIObufferPtr;   /**< (BUFF) */

  %extend{
    
    
    //VEXTERNC void start();
 
    //VEXTERNC void stop();

    Vio(const char *socktype, const char *datafrmt, 
	const char *hostname, const char *filename, const char *rwkey){
      return Vio_ctor(socktype, datafrmt, hostname, filename, rwkey);
	}

    ~Vio(){Vio_dtor(&$self);}

    VEXTERNC void setWhiteChars(char *whiteChars);

    VEXTERNC void setCommChars(char *commChars);

    VEXTERNC int accept(int nonblock);

    VEXTERNC void acceptFree();

    VEXTERNC int connect(int nonblock);

    VEXTERNC void connectFree();

    VEXTERNC int scanf(char *parms, ...);

    VEXTERNC int printf(char *parms, ...);

    VEXTERNC int read(char *buf, int bufsize);

    VEXTERNC int write(char *buf, int bufsize);

    VEXTERNC void bufTake(char *buf, int bufsize);

    VEXTERNC char* bufGive();

    VEXTERNC int bufSize();

    //VEXTERNC Vio *socketOpen(char *key,
    //			     const char *iodev, const char *iofmt,
    //			     const char *iohost, const char *iofile);
    //
    //VEXTERNC void socketClose(Vio **sock);

  }

} Vio;
