#ifndef __ACDS_ERRORS_H
  #define __ACDS_ERRORS_H
  #include <commandLib.h>
  //error sources for BUS test program
  enum{ACDS_ERR_SRC_SUBSYSTEM=ERR_SRC_CMD+1};
  
  #define ACDS_MIN_ERR                    (ERR_SRC_CMD)
  #define ACDS_MAX_ERR                    (ACDS_ERR_SRC_SUBSYSTEM)

  const char *ACDS_err_decode(char buf[150], unsigned short source,int err, unsigned short argument);

#endif
  