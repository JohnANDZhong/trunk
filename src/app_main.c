#include <pthread.h>
#include "sys_common.h"
#include "sys_logger.h"
#include  "queue.h"
#define  QNAME "/myqueue"
#define  MAX_MSG_NUM  2
#define  MAX_MSG_SIZE 256
MSG_Q id  ;
//MSG_Q mq;

//thread1
//while(1)循环接收 50ms周期收

//thread2
//while(1) 循环发送 50ms周期发
VOID *rcv_thr1(VOID *)
{
    INT32 data_rv[MAX_MSG_SIZE];
    INT32 i;

    while(1)
    {   
        if(OK != sys_queue_recv(&id, data_rv,  sizeof(data_rv)))
        {
            LOG_MESSAGE(LOG_ERROR, "psys_queue_recv fail");
            break;
        }
        //printf rcv
        for(i = 0; i < MAX_MSG_SIZE; i++)
        {
            LOG_MESSAGE(LOG_INFO, "RCV : %d",data_rv[i]);
        }
    }
}

VOID *send_thr2(VOID *)
{
    INT32 Data[MAX_MSG_SIZE];
    INT32 i = 0;

    while(1)  //send massage
    {
        for(i = 0; i < MAX_MSG_SIZE; i++)
        {
             Data[i] = i;
        }
        if( OK != sys_queue_send(&id, Data, MAX_MSG_SIZE, 50))
        {
            LOG_MESSAGE(LOG_ERROR,"send_thr fail");
            break;
        }
    } 
}

INT32 app_component_init(VOID)
{
    LOG_MESSAGE(LOG_INFO, "component init start");

    pthread_t thread1 ,thread2;
    //sys_queue_create(&mq)
    if( OK != sys_queue_create(&id, QNAME, MAX_MSG_NUM, MAX_MSG_SIZE))
    {
        LOG_MESSAGE(LOG_ERROR, "sys_ queue_create fail");
    }

    //创建两个线程
    //pthread_create(thread1) 接收线程
    //phtered_create(thread2) 发送线程
    if(0 != pthread_create(&thread1, NULL, rcv_thr1, NULL))
    {
        LOG_MESSAGE(LOG_ERROR, "pthread 2 create fail");
        return ERROR;
    }

     if(0 != pthread_create(&thread2, NULL, send_thr2, NULL))
    {
        LOG_MESSAGE(LOG_ERROR, "pthread 1 create fail");
        return ERROR;
    }

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    LOG_MESSAGE(LOG_ERROR, "component init finish");
   
    return 0;
}

INT32 app_component_start(VOID)
{
   
    LOG_MESSAGE(LOG_INFO, "component start");
   
    sys_queue_del(&id, QNAME);
    
    LOG_MESSAGE(LOG_INFO, "component start finish");
   // LOG_MESSAGE(LOG_INFO, WANGQIANG);

    return 0;
}
