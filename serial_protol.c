#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

unsigned short cal_checksum(char *indata, unsigned short len)
{
    unsigned short checksum = 0;
    for(int i = 0; i < len; i++)
    {
        checksum += indata[i];
        //printf("checksum:%d\n",checksum);
    }
    checksum += len;
//printf("checksum:%d\n",checksum);
    return checksum;
}

unsigned int serial_t(unsigned char *indata, unsigned short size, unsigned char *outdata)
{
    unsigned int iRet = -1;
    unsigned int iIndex = 0;
    unsigned short checksum = 0;
    unsigned short *Checksum = NULL;
    if(indata == NULL || outdata == NULL)
    {
       printf("输入序列化函数失败\n");
        return iRet;
    }
   
    /*字节顺序编码*/
    *outdata = 0x7D;
    iIndex += sizeof(unsigned char); 
   // printf("1:%d;outdata:%d\n", iIndex,outdata[0]);
  // memcpy(outdata + iIndex, &size , sizeof(size)); //拷贝数据长度2字节
    *(outdata + iIndex) = size;
    iIndex += 2;
     //printf("2:%d;outdata:%d\n", iIndex,outdata[1]);
    checksum = cal_checksum(indata, size);
    Checksum = &checksum ;
    memcpy(outdata + iIndex, (char*)Checksum, sizeof(Checksum));//校验和长度2个字节
    // *(outdata + iIndex) = checksum;
   // printf("checksum:%d outdata:%d\n",*Checksum, *(outdata + iIndex));
    iIndex += sizeof(checksum);
    // printf("3:%d;outdata:%d %d\n", iIndex,outdata[3],outdata[4]);
    memcpy(outdata + iIndex, indata , size); //将拷贝数据
    iIndex += size;
    // printf("4:%d;outdata:%d %d %d %d %d\n", iIndex,outdata[5],outdata[6],outdata[7],outdata[8],outdata[9]);
    *(outdata + iIndex) = 0x0D;
    printf("5:%d;outdata:%d\n", iIndex,outdata[10]);
    
    return iIndex;//整个帧的长度
}

int anti_serial(unsigned char *indata, unsigned short size, unsigned  char *outdata)
{
    unsigned short datalenght;
    unsigned short checksum = 0;
    unsigned short RcvChecksum;
    unsigned int dataStartIndex;
    unsigned int dataEndIndex;
    unsigned int iIndex = 0;
    int head = 0;
    int tail = 0;

    if(indata == NULL || outdata == NULL)
    {
        printf("反序列化函数输入失败\n");
    }

    /*检查是否存在头和尾*/
    for(iIndex = 0 ; iIndex <= size; iIndex++)
    {
        if(indata[iIndex] == 0x7D)
        {
            head++;
        }
        if(head != 1)
        {
            printf("两个头部，尾部丢失\n");
            break;
        }
        if(indata[iIndex] == 0x0D)
        {
            tail++;
        }
    }
    /*完整数据*/
    if(indata[0] == 0x7D && indata[size] == 0x0D)
    {
        //提取数据长度
        datalenght = indata[1] ; 
        dataStartIndex = 2*sizeof(unsigned short)+1;//校验和+数据长度
        dataEndIndex = dataStartIndex + datalenght;//数据内容索引结束
        printf("dataStartIndex:%d dataEndIndex:%d\n",dataStartIndex,dataEndIndex);
         /*提取数据内容*/
      
      
        /*计算校验和*/
        for(int i = dataStartIndex; i < dataEndIndex; i++ )
        {
            checksum += indata[i];
            printf("checksum:%d\n",checksum);
        }
        checksum += datalenght; 
        printf("checksum:%d\n",checksum);
       RcvChecksum = (indata[4] << 8) | indata[3];//小端存储
       //printf("indata[4]:%d indata[3]:%d rcvchecksum:%d\n",indata[4],indata[3],RcvChecksum);
        if(checksum != RcvChecksum)
        {
            printf("数据出错\n");
            return -1;
        }
        else
        {
            printf("数据正确\n");
            memcpy(outdata, indata + dataStartIndex, sizeof(unsigned short)*datalenght);
            printf("data:%d,%d,%d,%d,%d\n", outdata[0],outdata[1],outdata[2],outdata[3],outdata[4]);
            return 0;
        }
    }     
        
  
}



int main()
{
    char str[] = "1234567";
    char out[1024] = {0};
    char Out[1024] = {0};
    unsigned int ret = 0;
    unsigned int Ret = 0;
    ret = serial_t(str, sizeof(str), out);
    printf("ret: %d\n",ret);

   // len = sizeof(out)/sizeof(char);
    Ret = anti_serial(out, ret, Out);
    printf("data:%d,%d,%d,%d,%d\n", Out[0],Out[1],Out[2],Out[3],Out[4]);
    
}