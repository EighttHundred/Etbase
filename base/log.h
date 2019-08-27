
#ifndef ETBASE_LOG_H
#define ETBASE_LOG_H

#include <sys/syslog.h>
#include <string>
#include <cstring>
#define ERRORLEN 256

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
        static void writeDaily(const std::string& info)
        {
            syslog(LOG_USER|LOG_INFO,info.c_str());
        }
        static void writeWarning(const std::string& info)
        {
            syslog(LOG_USER|LOG_WARNING,info.c_str());
        }
        static void writeError(const std::string& info)
        {
            syslog(LOG_USER|LOG_ERR,info.c_str());
        }
    };
}



#endif //ETBASE_LOG_H
