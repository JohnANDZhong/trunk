#include "sys_common.h"
#include "sys_logger.h"
#include  "queue.h"
INT32 app_component_init(VOID)
{
    LOG_MESSAGE(LOG_INFO, "component init start");

    LOG_MESSAGE(LOG_ERROR, "component init finish");

    return 0;
}


INT32 app_component_start(VOID)
{
    LOG_MESSAGE(LOG_INFO, "component start");

    LOG_MESSAGE(LOG_INFO, "component start finish");
    LOG_MESSAGE(LOG_INFO, WANGQIANG);

    return 0;
}