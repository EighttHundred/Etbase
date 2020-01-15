#ifndef ETBASE_LOG_H
#define ETBASE_LOG_H

#include <sys/syslog.h>
#include <stdio.h>
#include <errno.h>
#define MESSAGELEN 256
/*
format:
fd,error name,manual message,errno message
fd=-1 when no value is set
while the others is ""
*/
namespace Etbase
{
    class LogWriter {
    public:
        LogWriter()
        {
            openlog(nullptr,LOG_NOWAIT,LOG_USER);
        }
        ~LogWriter()
        {
            closelog();
        }
        static void writeDaily(const int &fd,const char *name,const char *manual_m,const char*errno_m)
        {
            snprintf(message,MESSAGELEN,"fd:%d,error:%s,manual:%s,errno:%s",name,manual_m,errno_m);
            syslog(LOG_USER|LOG_INFO,message);
        }
        static void writeWarning(const int &fd,const char *name,const char *manual_m,const char*errno_m)
        {
            snprintf(message,MESSAGELEN,"fd:%d,error:%s,manual:%s,errno:%s",name,manual_m,errno_m);
            syslog(LOG_USER|LOG_WARNING,message);
        }
        static void writeError(const int &fd,const char *name,const char *manual_m,const char*errno_m)
        {
            snprintf(message,MESSAGELEN,"fd:%d,error:%s,manual:%s,errno:%s",name,manual_m,errno_m);
            syslog(LOG_USER|LOG_ERR,message);
        }
    private:
        static char message[MESSAGELEN];
    };
}



#endif //ETBASE_LOG_H
