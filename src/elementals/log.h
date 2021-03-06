/*
   This file is part of elementals (http://hoesterholt.github.com/elementals/).
   Copyright 2013, Hans Oesterholt <debian@oesterholt.net>

   Elementals are free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Elementals are distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with elementals.  If not, see <http://www.gnu.org/licenses/>.

   ********************************************************************
*/

#ifndef __LOG__H
#define __LOG__H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define LOG_DEBUG 1
#define LOG_INFO  2
#define LOG_ERROR 3
#define LOG_FCALL 4
#define LOG_FATAL 10
#define LOG_WARN  5

#define log_severity(s) ((s==LOG_DEBUG) ? "debug" : \
              ((s==LOG_INFO) ? "info  " : \
                ((s==LOG_ERROR) ? "error" : \
                  ((s==LOG_FATAL) ? "fatal" : \
                    ((s==LOG_FCALL) ? "fcall" : \
                      ((s==LOG_WARN) ? "warning" : "unknown") \
                      ) \
                        ) \
                          ) \
                            ) \
                             )


FILE * log_handle();
void reset_log_handle_to_space(const char *space);
int log_this_severity(int severity);

#define log_flush() fseek(log_handle(),0,SEEK_END)

#define log_imsg(severity,code) \
    ((log_this_severity(severity)) ? \
      (fprintf(log_handle(),"%s:%s[%d]:%s: ",log_severity(severity),__FILE__,__LINE__,__FUNCTION__), \
       code, \
       fprintf(log_handle(),"\n"), \
       log_flush()) : 0)

#define log_msg(severity,msg)  log_imsg(severity,fprintf(log_handle(),"%s",msg))
#define log_msg2(severity,template,m1) log_imsg(severity,fprintf(log_handle(),template,m1))
#define log_msg3(severity,template,m1,m2) log_imsg(severity,fprintf(log_handle(),template,m1,m2))
#define log_msg4(severity,template,m1,m2,m3) log_imsg(severity,fprintf(log_handle(),template,m1,m2,m3))
#define log_msg5(severity,template,m1,m2,m3,m4) log_imsg(severity,fprintf(log_handle(),template,m1,m2,m3,m4))
#define log_msg6(severity,template,m1,m2,m3,m4,m5) log_imsg(severity,fprintf(log_handle(),template,m1,m2,m3,m4,m5))

#define log_fcall(msg)  log_msg(LOG_FCALL,msg)

#define log_fcall_enter() log_fcall("enter");
#define log_fcall_leave() log_fcall("leave");

#define log_debug(msg)  log_msg(LOG_DEBUG,msg)
#define log_fatal(msg)  (log_msg(LOG_FATAL,msg),abort())
#define log_fatal_errno(msg) (log_msg(LOG_FATAL,msg),log_msg(LOG_ERROR,(strerror(errno))),abort())
#define log_info(msg)   log_msg(LOG_INFO,msg)
#define log_warning(msg)   log_msg(LOG_WARN,msg)
#define log_error(msg)  log_msg(LOG_ERROR,msg)
#define log_errno(msg)  (log_msg(LOG_ERROR,msg),log_msg(LOG_ERROR,strerror(errno)))

#define cond_log_error(cond,msg) if (cond) { log_error(msg); }
#define cond_log_fatal(cond,msg) if (cond) { log_fatal(msg); }
#define cond_log_warning(cond,msg) if (cond) { log_warning(msg); }
#define cond_log_errno(cond,msg) if (cond) { log_errno(msg); }
#define cond_log_fatal_errno(cond,msg) if (cond) { log_fatal_errno(msg); }

#define log_assert(cond) cond_log_fatal(!(cond), "Assertion failed: " #cond )

#define log_debug2(template,msg) log_msg2(LOG_DEBUG,template,msg)
#define log_fatal2(template,msg) (log_msg2(LOG_FATAL,template,msg),abort())
#define log_info2(template,msg) log_msg2(LOG_INFO,template,msg)
#define log_warning2(template,msg) log_msg2(LOG_WARN,template,msg)
#define log_error2(template,msg) log_msg2(LOG_ERROR,template,msg)

#define log_debug3(template,msg,m2) log_msg3(LOG_DEBUG,template,msg,m2)
#define log_fatal3(template,msg,m2) (log_msg3(LOG_FATAL,template,msg,m2),abort())
#define log_info3(template,msg,m2) log_msg3(LOG_INFO,template,msg,m2)
#define log_warning3(template,msg,m2) log_msg3(LOG_WARN,template,msg,m2)
#define log_error3(template,msg,m2) log_msg3(LOG_ERROR,template,msg,m2)

#define log_debug4(template,msg,m2,m3) log_msg4(LOG_DEBUG,template,msg,m2,m3)
#define log_fatal4(template,msg,m2,m3) (log_msg4(LOG_FATAL,template,msg,m2,m3),abort())
#define log_info4(template,msg,m2,m3) log_msg4(LOG_INFO,template,msg,m2,m3)
#define log_warning4(template,msg,m2,m3) log_msg4(LOG_WARN,template,msg,m2,m3)
#define log_error4(template,msg,m2,m3) log_msg4(LOG_ERROR,template,msg,m2,m3)

#define log_debug5(template,msg,m2,m3,m4) log_msg5(LOG_DEBUG,template,msg,m2,m3,m4)
#define log_fatal5(template,msg,m2,m3,m4) (log_msg5(LOG_FATAL,template,msg,m2,m3,m4),abort())
#define log_info5(template,msg,m2,m3,m4) log_msg5(LOG_INFO,template,msg,m2,m3,m4)
#define log_warning5(template,msg,m2,m3,m4) log_msg5(LOG_WARN,template,msg,m2,m3,m4)
#define log_error5(template,msg,m2,m3,m4) log_msg5(LOG_ERROR,template,msg,m2,m3,m4)

#define log_debug6(template,msg,m2,m3,m4,m5) log_msg6(LOG_DEBUG,template,msg,m2,m3,m4,m5)
#define log_fatal6(template,msg,m2,m3,m4,m5) (log_msg6(LOG_FATAL,template,msg,m2,m3,m4,m5),abort())
#define log_info6(template,msg,m2,m3,m4,m5) log_msg6(LOG_INFO,template,msg,m2,m3,m4,m5)
#define log_warning6(template,msg,m2,m3,m4,m5) log_msg6(LOG_WARN,template,msg,m2,m3,m4,m5)
#define log_error6(template,msg,m2,m3,m4,m5) log_msg6(LOG_ERROR,template,msg,m2,m3,m4,m5)


#define cond_log_error2(cond,template,msg) if (cond) { log_error2(template,msg); }

#define log_return(v)   return (log_debug2("return value=%d",v),v)
#define log_return_st(v)  return (log_debug2("return value=%ld",v),v)

#ifdef __cplusplus
}
#endif


#endif
