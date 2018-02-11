/* 
 * File:   gsmErrorHandler.h
 * Author: Manu K Harshan
 *
 * Created on 7 March, 2017, 12:17 PM
 */

#ifndef GSMERRORHANDLER_H
#define	GSMERRORHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include<stdint.h>

typedef enum
{
    CMEEPHONEFAILURE = 0,
    CMEESIMNOTINSERTED = 10,
    CMEESIMPINREQUIRED = 11,
    CMEESIMPUKREQUIRED = 12,
    CMEESIMFAILURE = 13,
    CMEESIMBUSY = 14,
    CMEESIMWRONG = 15,
    CMEEINCORRECTPWD = 16,
    CMEESIMPIN2REQUIRED = 17,
    CMEESIMPUCK2REQUIRED = 18,
};

typedef enum
{
    CMSUNASSIGNEDNUMBER = 1,
    CMSSIMNOTINSERTED = 310,
    CMSSIMPINREQUIED = 311,
    CMSSIMFAILURE = 313,
    CMSSIMBUSY = 314,
    CMSSIMWRONG = 315,
    CMSSIMPUKREQ = 316,
    CMSSIMPIN2REQ = 317,
    CMSSIMPUK2REQ = 318,
    CMSSIMNOTREADY = 538,
};

void gsmCmeeErrorHandler(int cmeeerrorCode);
void gsmCmsErrorHandler(int cmserrorCode);

#ifdef	__cplusplus
}
#endif

#endif	/* GSMERRORHANDLER_H */

