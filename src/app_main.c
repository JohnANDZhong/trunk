#include <pthread.h>
#include "sys_common.h"
#include "sys_logger.h"
#include  "queue.h"
#define  QNAME "/home/lzj/git/trunk/build/q_test"
#define  MAX_MSG_NUM  10
#define  MAX_MSG_SIZE 1024
MSG_Q *id =NULL ;
//MSG_Q mq;

//thread1
//while(1)循环接收 50ms周期收

//thread2
//while(1) 循环发送 50ms周期发
VOID *send_thr1(VOID *)
{
    INT32 Data[10];
    INT32 i;
    for(i = 0; i < 10; i++)     //send massage
    {
        Data[i] = rand()%100;
    }
    while(1)
    {
        if( OK != sys_queue_send(id, Data, sizeof(Data), 50))
        {
            LOG_MESSAGE(LOG_ERROR,"send_thr fail");
            break;
        }
       return NULL;
    }

}
VOID *rcv_thr2(VOID *)
{
    INT32 data_rv[10];
    while(1)
    {
        if(OK != sys_queue_recv(id, data_rv,  sizeof(data_rv)))
        {
            LOG_MESSAGE(LOG_ERROR, "psys_queue_recv fail");
            break;
        }
    }
    
}
INT32 app_component_init(VOID)
{
    LOG_MESSAGE(LOG_INFO, "component init start");

    pthread_t id1, id2;
/* if(mq_unlink(QNAME) != 0)
    {
        perror("mq_ulink");
        return ERROR;
    }
  */  
   if( OK != sys_queue_create(id, QNAME, MAX_MSG_NUM, MAX_MSG_SIZE))
   {
     LOG_MESSAGE(LOG_ERROR, "sys_ queue_create fail");
   }

   
    if(0 != pthread_create(&id1, NULL, send_thr1, NULL))
    {
        LOG_MESSAGE(LOG_ERROR, "pthread 1 create fail");
        return ERROR;
    }
    


    if(0 != pthread_create(&id2, NULL, rcv_thr2, NULL))
    {
        LOG_MESSAGE(LOG_ERROR, "pthread 2 create fail");
        return ERROR;
    }

    LOG_MESSAGE(LOG_ERROR, "component init finish");
   
    pthread_join(id1,NULL);
     pthread_join(id2,NULL);
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
   // LOG_MESSAGE(LOG_INFO, WANGQIANG);

    return 0;
}
