#ifndef QUEUE_H__
#define QUEUE_H__
#include <mqueue.h>
#include "sys_common.h"

typedef mqd_t MSG_Q;

/**
 * @brief 消息队列的初始化
 * 
 * @param id 消息队列的ID
 * @param maxNum 队列最大长度 
 * @param byteSize 队列的包长
 * @return INT32 创建成功还是失败  
 */
INT32 sys_queue_create(MSG_Q *id, char *name, UINT32 maxNum, UINT32 byteSize);

//消息队列的发送
/**
 * @brief 消息队列的发送
 * 
 * @param id 
 * @param data 发送数据指针
 * @param byteSize 数据大小
 * @param iWaitTime 延时多久发送 ms
 * @return INT32 发送成功还是失败
 */
INT32 sys_queue_send(MSG_Q *id, void *data, UINT32 byteSize, UINT32 iWaitTime);

/**
 * @brief 消息队列的发送
 * 
 * @param id 
 * @param data 接受数据的指针
 * @param byteSize 接受数据的大小
 * @return INT32 发送成功还是失败
 */
INT32 sys_queue_recv(MSG_Q *id, void *data, UINT32 byteSize);

//消息队列的销毁
/**
 * @brief 
 * 
 * @param id 
 * @return INT32 
 */
INT32 sys_queue_del(MSG_Q *id, char *name);

#endif