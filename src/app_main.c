#include <pthread.h>
#include "sys_common.h"
#include "sys_logger.h"
#include  "queue.h"
#define  QNAME "/myqueue"
#define  MAX_MSG_NUM  2
#define  MAX_MSG_SIZE 256

INT32 app_component_init(VOID)
{
    return 0;
}

INT32 app_component_start(VOID)
{
   
    LOG_MESSAGE(LOG_INFO, "component start");
   
    LOG_MESSAGE(LOG_INFO, "component start finish");
   // LOG_MESSAGE(LOG_INFO, WANGQIANG);

    return 0;
}
