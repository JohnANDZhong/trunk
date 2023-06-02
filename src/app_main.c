#include "sys_common.h"
#include "sys_logger.h"
#include  "queue.h"


//MSG_Q mq;

//thread1
//while(1)循环接收 50ms周期收

//thread2
//while(1)循环发送 50ms周期发

INT32 app_component_init(VOID)
{
    LOG_MESSAGE(LOG_INFO, "component init start");

    LOG_MESSAGE(LOG_ERROR, "component init finish");
    //sys_queue_create(&mq)
    //创建两个线程
    //pthread_create(thread1) 接收线程
    //phtered_create(thread2) 发送线程
    return 0;
}


INT32 app_component_start(VOID)
{
    LOG_MESSAGE(LOG_INFO, "component start");

    LOG_MESSAGE(LOG_INFO, "component start finish");
    LOG_MESSAGE(LOG_INFO, WANGQIANG);

    return 0;
}
