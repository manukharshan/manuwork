#include "gsmErrorHandler.h"

void gsmCmeeErrorHandler(int cmeeerrorCode)
{
    switch(cmeeerrorCode)
    {
        case CMEEPHONEFAILURE:
        {  
            break;
        }
        case CMEESIMNOTINSERTED:
        { 
            break;
        }
        case CMEESIMPINREQUIRED:
        {
            break;
        }
        case CMEESIMPUKREQUIRED:
        {
            break;
        }
        case CMEESIMFAILURE:
        {
            break;
        }
        case CMEESIMBUSY:
        {
            break;
        }
        case CMEESIMWRONG:
        {
            break;
        }
        case CMEEINCORRECTPWD:
        {
            break;
        }
        case CMEESIMPIN2REQUIRED:
        {
            break;
        }
        case CMEESIMPUCK2REQUIRED:
        {
            break;
        }
    }  
}

void gsmCmsErrorHandler(int cmserrorCode)
{
    switch(cmserrorCode)
    {
        case CMSUNASSIGNEDNUMBER:
        {
            break;
        }
        case CMSSIMNOTINSERTED:
        {
            break;
        }
        case CMSSIMPINREQUIED:
        {
           break; 
        }
        case CMSSIMFAILURE:
        {
            break;
        }
        case CMSSIMBUSY:
        {
            break;
        }
        case CMSSIMWRONG:
        {
            break;
        }
        case CMSSIMPUKREQ:
        { 
            break;
        }
        case CMSSIMPIN2REQ:
        {
            break;
        }
        case CMSSIMPUK2REQ:
        {
            break;
        }
        case CMSSIMNOTREADY:
        {
            break;
        } 
        default:
        {
            break;
        }
    }
}
