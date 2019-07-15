#if 0

/**
 * ******************************************************************************
 */
// test code1
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
#include <iostream>

#include<sys/wait.h>

using namespace std;

// 进程退出函数
void print_exit()  
{  
       printf("the exit pid:[%d] \n",getpid() );  
} 

int main()
{
    string sMatch;
    pid_t pid, child_pid;
    vector<string> provList;
    provList.push_back("taskFace");
    provList.push_back("taskObj");
    provList.push_back("taskAction");
    provList.push_back("taskHat");
    provList.push_back("taskOther");

    cout << "Main process,id=" << getpid() << endl;

    // 循环处理"100,200,300,400,500"
    for (vector<string>::iterator it = provList.begin(); it != provList.end(); ++it)
    {
        sMatch = *it;
        atexit( print_exit );
        pid = fork();
        // (*hsq*)子进程退出循环，不再创建子进程，全部由主进程创建子进程，这里是关键所在
        if(pid == 0 || pid == -1)
        {
            break;
        }
    }

    if(pid == -1)
    {
        cout<<"Fail to fork!"<<endl;
        exit(1);
    }
    else if(pid == 0)
    {
        // 这里写子进程处理逻辑
        cout <<"This is children process,id=" << getpid() << ",start to process " << sMatch << endl;
        sleep(10);
        exit(0);
    }
    else
    {
        // 这里主进程处理逻辑
        cout << "This is main process,id=" << getpid() <<",end to process "<< sMatch << endl;



        // do 
        // {   
        //     // WNOHANG 非阻塞 轮询 等待带子进程结束
        //     child_pid = waitpid(pid, NULL, WNOHANG);  
        //     if(child_pid != pid)
        //     {
        //         printf("---- watpid error!\n");
        //     }
        //     printf("I am main progress.The pid progress has not exited!\n");
        //     sleep(2);

        // }while(child_pid == 0);
        exit(0);
    }

    return 0;
}
#endif 


#if 0

/**
 * ******************************************************************************
 */
// test code  2 进程间通信
// 
#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include<vector>
#include <iostream>
#include<sys/wait.h>

#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

typedef struct TASK_LIST_
{
    int taskId;
    const char *taskInfo;
}TASK_LIST;


void print_exit()  
{  
       printf("the exit pid:[%d] \n",getpid() );  
} 


TASK_LIST taskList[5];

#define     SIZE 1024
const   long id = 1;

int main(int argc, char const *argv[])
{
    key_t unique_key;
    int msgid;
    int status;
    char str[SIZE];
       
    struct msgbuf 
    {
        long msgtype;
        char msgtext[SIZE];

    }sndmsg, rcvmsg;

    TASK_LIST sMatch;
    pid_t pid, child_pid;
    //int status;
    
    vector<TASK_LIST> provList;
    taskList[0].taskInfo = "1001";
    taskList[1].taskInfo = "2002";
    taskList[2].taskInfo = "3003";
    taskList[3].taskInfo = "4004";
    taskList[4].taskInfo = "5005";
    for (int i = 0; i < 5; i++)
    {
        cout << i << " " << taskList[i].taskInfo << endl;
        taskList[i].taskId = i;

        provList.push_back(taskList[i]);
    }
    cout<<"main process,id="<<getpid()<<endl;

    // 创建一个消息队列 
    // IPC_CREAT :创建一个消息队列  IPC_EXCL :如果已经存在则报错
    msgid = msgget(unique_key,IPC_CREAT | IPC_EXCL);

    for (int i = 0; i < provList.size(); i++)
    {
        atexit( print_exit );
        pid = fork();

        // (*hsq*)子进程退出循环，不再创建子进程，全部由主进程创建子进程，这里是关键所在
        if (pid == 0 || pid == -1)
        {
            break;
        }
    }

    if(pid == -1)
    {
        cout<<"fail to fork!"<<endl;
        msgctl(msgid, IPC_RMID, 0);
        exit(1);
    }
    else if(pid == 0)
    {
        sleep(2);
        if((status = msgrcv(msgid, (struct msgbuf *)&rcvmsg, sizeof(str) + 1, id, IPC_NOWAIT)) == -1) 
        {
            fprintf(stderr, "msgrcv error!\n");
            exit(4);
        }
        int taskId = atoi(rcvmsg.msgtext);

        if(taskId == 1)
        {
            cout << "start task [" << taskList[1].taskId <<"] :" << taskList[1].taskInfo << endl; 
        }
        printf("The received message is:%s\n", rcvmsg.msgtext);
        // msgctl(msgid, IPC_RMID, 0);   // delete the message queue
        
        //这里写子进程处理逻辑
        cout << "this is children process,id=" << getpid() << endl;

        sleep(2);
        exit(0);
    }
    else
    {   
        cout << "this is main process,pid=" << getpid() << endl;

        // sleep(3);

        for (int i = 0; i < 5; ++i)
        {
            sndmsg.msgtype = id;
            char id[4];
            sprintf(id, "%d", i);
            strcpy(str, id);
            sprintf(sndmsg.msgtext, str);
            if(msgsnd(msgid, (struct msgbuf *)&sndmsg, sizeof(str) + 1, 0) == -1) 
            {
                fprintf(stderr, "msgsnd error! \n");
                exit(2);
            }
        }
      
        // 这里主进程处理逻辑
       
        // do 
        // {   
        //     // WNOHANG 非阻塞 轮询 等你带子进程结束
        //     child_pid = waitpid(pid, NULL, WNOHANG);  
        //     if(child_pid != pid)
        //     {
        //         printf("---- watpid error!\n");
        //     }
        //     printf("I am main progress.The pid progress has not exited!\n");
        //     sleep(2);

        // }while(child_pid == 0);

        // exit(0);
    }
    
    return 0;
}

#endif





#if 0


#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include<vector>
#include <iostream>
#include<sys/wait.h>

using namespace std;

typedef struct TASK_LIST_
{
    int taskId;
    const char *taskInfo;
}TASK_LIST;


void print_exit()  
{  
       printf("the exit pid:[%d] \n",getpid() );  
} 


TASK_LIST taskList[5];

int main(int argc, char const *argv[])
{
    TASK_LIST sMatch;
    pid_t pid, child_pid;
    int status;
    
    vector<TASK_LIST> provList;
    taskList[0].taskInfo = "1001";
    taskList[1].taskInfo = "2002";
    taskList[2].taskInfo = "3003";
    taskList[3].taskInfo = "4004";
    taskList[4].taskInfo = "5005";
    for (int i = 0; i < 5; i++)
    {
        //cout << i << " " << taskList[i].taskInfo << endl;
        taskList[i].taskId = 0;
        provList.push_back(taskList[i]);
    }
    cout<<"main process,id="<<getpid()<<endl;

    for (int i = 0; i < provList.size(); i++)
    {
        // atexit( print_exit );
        pid = fork();

        // (*hsq*)子进程退出循环，不再创建子进程，全部由主进程创建子进程，这里是关键所在
        if (pid == 0 || pid == -1)
        {
            break;
        }
        else
        {
            cout<<"main process pid: "<< getpid ()<< ", child process pid: " << pid << endl;
            for (int i = 0; i < 5; i++)
            {
                if(taskList[i].taskId == 0)
                {   
                    // 主进程修改任务状态信息 
                    // 主进程将每一个子进程的pid赋值给 每一个任务， 子进程在继续执行的过程中，根据pid 执行相应的任务
                    taskList[i].taskId = pid;
                    cout << "main process taskList[i].taskId " << i << " " <<   taskList[i].taskId << endl;
                    break;
                }
            }
        }

    }

    if(pid == -1)
    {
        cout<<"fail to fork!"<<endl;
        exit(1);
    }
    else if(pid == 0)
    {
        //这里写子进程处理逻辑
        cout<<"this is children process,id=" << getpid() << ", start to process " << endl;

         for (int i = 0; i < 5; i++)
        {
            cout << i << " " << taskList[i].taskId << " " << taskList[i].taskInfo << endl;
            //taskList[i].taskId = 0;
            //provList.push_back(taskList[i]);
        }
        
        for (int i = 0; i < 5; i++)
        {
            if(taskList[i].taskId == 0)
            {
                cout << "exec task :" << taskList[i].taskInfo << endl;
                break;
            }
        }
        //sleep(2);
        cout<<"this is children process,id=" << getpid() << ", end to process " << endl << endl;
        exit(0);
    }
    
    return 0;
}

#endif 















/////////////////////////////////////////////////////////////////////////


#if 0
#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include<vector>
#include <iostream>
#include<sys/wait.h>

using namespace std;

typedef struct TASK_LIST_
{
    int taskId;
    const char *taskInfo;
}TASK_LIST;


void print_exit()  
{  
       printf("the exit pid:[%d] \n",getpid() );  
} 


TASK_LIST taskList[5];

int main(int argc, char const *argv[])
{
    TASK_LIST sMatch;
    pid_t pid, child_pid;
    int status;
    
    vector<TASK_LIST> provList;
    taskList[0].taskInfo = "1001";
    taskList[1].taskInfo = "2002";
    taskList[2].taskInfo = "3003";
    taskList[3].taskInfo = "4004";
    taskList[4].taskInfo = "5005";
    for (int i = 0; i < 5; i++)
    {
        cout << i << " " << taskList[i].taskInfo << endl;
        taskList[i].taskId = i;

        provList.push_back(taskList[i]);
    }
    cout<<"main process,id="<<getpid()<<endl;


    // 循环处理"100,200,300,400,500"
    // 迭代器
    // for (vector<string>::iterator it = provList.begin(); it != provList.end(); ++it)
    // {
    //     sMatch = *it;
    //     // 注册进程退出函数
    //     atexit( print_exit );
    //     pid = fork();
    //     cout << "child process " << pid << " " << getpid() <<  endl;  // 此时pid 是父进程中 fork() 返回的子进程ID

    //     // (*hsq*)子进程退出循环，不再创建子进程，全部由主进程创建子进程，这里是关键所在
    //     if(pid == 0 || pid == -1)
    //     {
    //         cout << "chid  process break for()" <<endl;
    //         break;
    //     }
    // }
    // 
    
    for (int i = 0; i < provList.size(); i++)
    {
        atexit( print_exit );
        pid = fork();

        // (*hsq*)子进程退出循环，不再创建子进程，全部由主进程创建子进程，这里是关键所在
        if (pid == 0 || pid == -1)
        {
            break;
        }
    }

    if(pid == -1)
    {
        cout<<"fail to fork!"<<endl;
        exit(1);
    }
    else if(pid == 0)
    {
        //这里写子进程处理逻辑
        cout<<"this is children process,id="<<getpid()<<", start to process "<< endl;

        sleep(2);
        exit(0);
    }
    else
    {
        // 这里主进程处理逻辑
        cout<<"this is main process,id="<<getpid()<<",end to process "<< endl;
        do 
        {   
            // WNOHANG 非阻塞 轮询 等你带子进程结束
            child_pid = waitpid(pid, NULL, WNOHANG);  
            if(child_pid != pid)
            {
                printf("---- watpid error!\n");
            }
            printf("I am main progress.The pid progress has not exited!\n");
            sleep(2);

        }while(child_pid == 0);

        exit(0);
    }
    
    return 0;
}

#endif 














#include<iostream>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
 
class CMyString
{
public:
    CMyString(char *pData=NULL);//构造函数
    CMyString(const CMyString& str);//拷贝构造函数
    ~CMyString();//析构函数
    CMyString& operator=(const CMyString& str);//重载运算符
    void Print();//打印字符串
private:
    char* m_pData;//数据域，字符指针
};
 
void CMyString::Print()
{
    cout<<m_pData<<endl;
}
//构造函数
CMyString::CMyString(char *pData)
{
    if(pData==NULL)//如果构造函数的参数为空
    {
        m_pData=new char[1];
        m_pData[0]='\0';//初始化字符串，内容为'\0'
    }
    else//如果构造函数的参数不为NULL，那么首先求出字符串长度，然后new一个长度为len+1的字符数组
    {
        int len=strlen(pData);
        m_pData=new char[len+1];
        strcpy(m_pData,pData);//字符串拷贝
    }
}
 
//析构函数
CMyString::~CMyString()
{
    delete[] m_pData;
}
 
//拷贝构造函数，拷贝构造函数与构造函数的思路非常类似。
CMyString::CMyString(const CMyString& str)
{
    int len=strlen(str.m_pData);
    m_pData=new char[len+1];
    strcpy(m_pData,str.m_pData);
}
 
//重载运算符
CMyString& CMyString::operator=(const CMyString& str)
{
    // //如果传入的参数与当前的实例是同一个实例，则直接返回自身
    // if(this==&str)
    //     return *this;
 
    // //释放实例自身已有内存
    // delete[] m_pData;
    // m_pData=NULL;
 
    // //在删除自身内存以后在重新new一个长度为len+1的字符数组，类似拷贝构造函数
    // int len=strlen(str.m_pData);
    // m_pData=new char[len+1];
    // strcpy(m_pData,str.m_pData);

    if(this!=&str)//
    {
        CMyString strTemp(str);//使用构造函数创建一个临时对象
        //交换临时对象与当前对象的m_pData值
        char* pTemp=strTemp.m_pData;
        strTemp.m_pData=m_pData;
        m_pData=*pTemp;
    }
    return *this;
}
 
int  main()
{
    char* strs="hello xuxing";
    CMyString str1(strs);
    CMyString str2;
    str2=str1;
    str1.Print();
    str2.Print();
 
    return 0;
}




















