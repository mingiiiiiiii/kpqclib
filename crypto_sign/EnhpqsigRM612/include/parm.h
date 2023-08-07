// parm.h 
// 
// This header includes parameters for pqsigRM-6-12
// 
#ifndef __PARM_H
#define __PARM_H



#if pqsigRM_MODE == 1
#define RM_R 6
#define RM_M 12

#define CODE_K 2510
#define CODE_N 4096

#define PARM_P 385

#define WEIGHT_PUB 471 
#define HASHSIZEBYTES 64

#define SIGN_FAILURE -1
#define VERIF_REJECT -1

#define ERROR_NO_FILE -1
#endif


#if pqsigRM_MODE == 5
#define RM_R 6U
#define RM_M 13U

#define K_REP 2U

#define CODE_K 4096U
#define CODE_N 8192U

#define PARM_P 561U

#define WEIGHT_PUB 1370U    ///
#define HASHSIZEBYTES 64U  /// 64U

#define SIGN_FAILURE -1
#define VERIF_REJECT -1

#define ERROR_NO_FILE -1
#endif



#endif
