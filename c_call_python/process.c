#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <signal.h>
#include <Python.h>  //必须加载的头文件
int g_exit = 0;

//定义python对象
PyObject* pModule;
PyObject* pTest;

void sig_process(int sig)  
{  
    g_exit = 1;
}  

void func(void* param_name)  
{ 
    //子线程执行之前，加锁
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();
	
	PyObject* pFun2;
    PyObject* pFun;
    PyObject* pFun3;
    while(!g_exit)
    {
        pFun3 = PyObject_GetAttrString(pModule, "test_hello");
        PyObject_CallFunction(pFun3, "s", "shuqiang");

        //
        //通过全局python模块对象 ，获取该模块中的方法
        pFun = PyObject_GetAttrString(pModule, "show");
        //pTest 是python方法的返回值 ，使用 PyArg_Parse 接口可以解析为C风格的字 符//串或者其他格式的数据
        pTest = PyObject_CallFunction(pFun, "s", param_name);

        //
        pFun2 = PyObject_GetAttrString(pModule, "objTest"); 
        //调用接口，有多种方式调用 
        //PyObject_CallFunctionObjArgs(pFun2, pTest);   
        PyObject_CallFunction(pFun2, "sO", "str_test", pTest);  


        char *cstr;
        PyArg_Parse(pTest, "s", &cstr);
        printf(">>> parse result: <%s>\n\n", cstr);

	    sleep(10);
    }
    //释放线程中的锁，释放python对象
    //注意，子线程中有循环的时候，加锁，和释放放在循环之外执行，不建议在子线程中频繁的创建和释放锁。
    Py_DECREF(pFun);
    Py_DECREF(pFun2);
    PyGILState_Release(gstate);
}  
int main()  
{  
    pthread_t pid1, pid2, pid3; 
    signal(SIGINT, sig_process); 

    //调用python之前必须初始化，以获取python解释器
    Py_Initialize();     
    if (!Py_IsInitialized())  return -1; 

    //导入当前路径，或者是需要调用的python脚本路径
    PyRun_SimpleString("import sys");  
    PyRun_SimpleString("sys.path.append('./')");

    //这里物品将要调用的python脚本是hello.py, 将C字符串转为python对象
    PyObject *pName;
    pName = PyString_FromString("hello");

    //导入要调用的python模块
    pModule = PyImport_Import(pName);  
    if ( !pModule ) {  
        getchar();  
        return -1;  
    } 
	printf("[------ [%d]\n", pModule);
    // 启动多线程之前，所有准备工作完成，这时候启用 线程支持接口
    //释放全局锁，作用是，使子线程可以获取解释器
    //之后就可以执行线程了
    PyEval_InitThreads(); 
    PyEval_ReleaseThread(PyThreadState_Get());   
/*if(pthread_create(&pid1, NULL, (void *(*)(void *))func, "output")) {  
        return -1;  }  */
    if(pthread_create(&pid2, NULL, (void *(*)(void *))func, "show")){  
        return -1;  } 
/*if(pthread_create(&pid3, NULL, (void *(*)(void *))func, "see")){  
        return -1;  }  */
    while(!g_exit){  
        sleep(3);  
    } 
    pthread_join(pid3, NULL);
    pthread_join(pid2, NULL);
    pthread_join(pid1, NULL);

    //所有线程执行完成之后，释放所有python对象
    PyGILState_Ensure(); 
    Py_DECREF(pModule);  
    //Release   
    Py_Finalize();     
    return 0;    
}  

