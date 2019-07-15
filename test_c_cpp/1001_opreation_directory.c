 #include <fcntl.h>             // 提供open()函数  
#include <unistd.h>  
#include <stdio.h>  
#include <dirent.h>            // 提供目录流操作函数  
#include <string.h>  
#include <sys/stat.h>        // 提供属性操作函数  
#include <sys/types.h>         // 提供mode_t 类型  
#include <stdlib.h> 
  
void scan_dir(char *dir, int depth)   // 定义目录扫描函数  
{  
    DIR *dp;                      // 定义子目录流指针  
    struct dirent *entry;         // 定义dirent结构指针保存后续目录  
    struct stat statbuf;          // 定义statbuf结构保存文件属性  
    if((dp = opendir(dir)) == NULL) // 打开目录，获取子目录流指针，判断操作是否成功  
    {  
        puts("can't open dir.");  
        return;  
    }  
    chdir (dir);                     // 切换到当前目录  

    while((entry = readdir(dp)) != NULL)  // 获取下一级目录信息，如果未否则循环  
    {  
        lstat(entry->d_name, &statbuf); // 获取下一级成员属性  
        if(S_IFDIR &statbuf.st_mode)    // 判断下一级成员是否是目录  
        {  
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)  
              continue;  
  
            printf("%*s%s/\n", depth, "", entry->d_name);  // 输出目录名称  
            scan_dir(entry->d_name, depth+4);              // 递归调用自身，扫描下一级目录的内容  
        }  
        else
        {   
            printf("%*s%s\n", depth, "", entry->d_name);  // 输出属性不是目录的成员  
        } 
            
    }  
    chdir("..");                                                  // 回到上级目录  
    closedir(dp);                                                 // 关闭子目录流  
}  
  
  
int main()  
{  
    puts("scan /icooper/vision_dev/shuqiang/image/face_lib:");  
    scan_dir("/icooper/vision_dev/shuqiang/image/face_lib", 0);  
    puts("scan over.");  
    return 0;  
}  























// #include<stdio.h>    //标准输入输出
// #include<unistd.h>   //各种系统调用
// #include<dirent.h>   //与目录有关的操作
// #include<string.h>   //与字符串处理有关的函数
// #include<sys/stat.h> //与文件状态有关
// #include<sys/types.h>//linux系统自定义的类型



// void show_directory(char * dir_name,int level);
// int main(int argc, char * argv[])
// {
//     if(argc != 2)
//     {
//         fprintf(stdout,"%s\n","参数输入有问题!");
//         return 1;
//     }
//     show_directory(argv[1],0);
//     return 0;
    
// }

// /*用于显示目录
//  * 第一个参数为目录的名称
//  * 第二个参数为目录为几及目录
//  * */

// void show_directory(char * dir_name,int level)
// {
//     DIR * dir; //目录流指针
//     struct dirent * entry; //目录项结构体指针
//     struct stat statbuf;
    


//     if( (  dir =  opendir(dir_name) ) ==  NULL    )
//         return ; 
    
//     chdir(dir_name);

//     char cwd[100];
//     getcwd(cwd,100);

//     int dir_name_len;
//     dir_name_len = strlen(dir_name);
//     fprintf(stdout,"%*s文件夹中：\n",level + dir_name_len,dir_name);
//     while( ( entry = readdir(dir) ) !=  NULL )
//     {
        
//         lstat(entry->d_name,&statbuf);
//         //如果是目录，就第归调用    
//         if( S_ISDIR (statbuf.st_mode)  )
//         {
//             if(   strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
//             {
//                 continue;
//             }
//             int level2;
//             level2 = level + dir_name_len + 10;  //计算出空格数
//             show_directory(entry->d_name,level2);
//         }
//         else if(  S_ISREG(statbuf.st_mode)  )  //如果是文件，输出
//         {
//             int length = level + (int)strlen(entry->d_name) + dir_name_len + 10; //子段应有占的长度
//             fprintf(stdout,"%*s\n",level + (int)strlen(entry->d_name) + dir_name_len + 10,entry->d_name);
//         }
//     }
//     chdir("..");
//     closedir(dir);

// }