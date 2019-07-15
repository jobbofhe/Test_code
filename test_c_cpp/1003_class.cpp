// #include <iostream>
// #include <string.h>
// #include <stdio.h>


// using namespace std;

// class Point
// {
//     public:

//         Point(int x, int y)
//         {
//             cout<<"带参数的构造函数...\n";

//             // xPos = a;         //利用构造函数对数据成员 xPos, yPos进行初始化
//             // yPos = b;
//         }
//         Point()     //声明并定义构造函数
//         {
//             cout<<"自定义的构造函数被调用...\n";
//             xPos = 100;         //利用构造函数对数据成员 xPos, yPos进行初始化
//             yPos = 100;
//             strcpy(buff, "learning c++");
//         }

//         // 不自定义 拷贝构造函数，则使用 会调用默认的复制构造函数，这个时候执行的浅拷贝
//         // 如果定义了 拷贝构造函数，则调用自定义的拷贝构造函数，执行的是深拷贝
//         // Point M2 = M;
//         // 
//         // 0x7ffc60ddbde8  0x7ffc60ddbe18
//         // 0x7ffd2a4caa08  0x7ffd2a4caa38
//         Point(Point &obj)
//         {
//             strcpy(buff, obj.getBuff()); 
//         }
//         void printPoint()
//         {
//             cout<<"xPos = " << xPos <<endl;
//             cout<<"yPos = " << yPos <<endl;
//         }

//         int getX()
//         {
//             return this->xPos;
//         }

//         char *getBuff()
//         {
//             return this->buff;
//         }

//         ~Point()
//         {
//             cout << "destory" << endl;
//         }

//     private:
//         int xPos;
//         int yPos;
//         char buff[32];
// };

// int main()
// {
//     Point M;    //创建对象M
//     cout << M.getBuff() << endl;
//     printf("%p\n", M.getBuff());

//     Point M2 = M;
//     cout << M2.getBuff() << endl;
//     printf("%p\n", M2.getBuff());

//     Point M3(M);
//     cout << M3.getBuff() << endl;
//     printf("%p\n", M3.getBuff());

//     // 0x7fff9721f6e8
//     // 0x7fff9721f718
//     // 0x7fff9721f748

//     // M.~Point();
//     // M2.~Point();
//     // M3.~Point();

//     return 0;
// }


// #include <iostream>
// #include <string.h>
// #include <stdio.h>


// using namespace std;

// class Point
// {
//     public:

//         // Point(int x, int y):xPos(2),yPos(4)
//         // {
//         //     cout<<"带参数的构造函数...\n";

//         //     xPos = x;         //利用构造函数对数据成员 xPos, yPos进行初始化
//         //     yPos = y;
//         // }

//         Point(int x=0, int y=0)
//         {
//             cout<<"带参数的构造函数...\n";

//             xPos = x;         //利用构造函数对数据成员 xPos, yPos进行初始化
//             yPos = y;
//         }
//         Point()     //声明并定义构造函数
//         {
//             cout<<"自定义的构造函数被调用...\n";
//             xPos = 100;         //利用构造函数对数据成员 xPos, yPos进行初始化
//             yPos = 100;
//             strcpy(buff, "learning c++");
//         }

//     private:
//         int xPos;
//         int yPos;
//         char buff[32];
// };

// int main()
// {
//     Point M;    //创建对象M


//     return 0;
// }








// ------------------------------------------------------

// #include <iostream> 
// using namespace std;
 
// class Shape 
// {
//    protected:
//       int width, height;
//    public:
//       Shape( int a=0, int b=0)
//       {
//          width = a;
//          height = b;
//       }

//       int area()
//       {
//          cout << "Parent class area :" <<endl;
//          return 0;
//       }
        
//       // 虚函数
//       // virtual int area()
//       // {
//       //    cout << "Parent class area :" <<endl;
//       //    return 0;
//       // }

//       virtual int area() = 0;
//       // = 0 告诉编译器，函数没有主体，上面的虚函数是纯虚函数。
// };

// class Rectangle: public Shape
// {
//    public:
//       Rectangle( int a=0, int b=0):Shape(a, b) { }
//        int area ()
//       { 
//          cout << "Rectangle class area :" <<endl;
//          return (width * height); 
//       }
// };
// class Triangle: public Shape
// {
//    public:
//       Triangle( int a=0, int b=0):Shape(a, b) { }
//       int area ()
//       { 
//          cout << "Triangle class area :" <<endl;
//          return (width * height / 2); 
//       }
// };
// // 程序的主函数
// int main( )
// {
//    Shape *shape;
//    Rectangle rec(10,7);
//    Triangle  tri(10,5);
 
//    // 存储矩形的地址
//    shape = &rec;
//    // 调用矩形的求面积函数 area
//    shape->area();
 
//    // 存储三角形的地址
//    shape = &tri;
//    // 调用三角形的求面积函数 area
//    shape->area();
   
//    return 0;
// }


// ListNode* ReverseList(ListNode* pHead) 
// {
//     ListNode *p,*q,*r;
//     if(pHead==NULL || pHead->next==NULL)
//     {
//         return pHead;
//     }else
//     {
//         p=pHead;
//         q=p->next;
//         pHead->next=NULL;
//         while(q!=NULL)
//         {
//             r=q->next;
//             q->next=p;
//             p=q;
//             q=r;
//         }
//         return p;
//     }
// }



// ------------------------------------------------------

// #include <iostream> 
// using namespace std;

// int func(int x) 
// { 

//     int countx = 0; 

//     while(x) 
//     { 

//         countx ++; 

//         x = x&(x-1); 
//     } 
//     return countx; 
// } 

// int main(int argc, char const *argv[])
// {
//     int ret = func(9999);
//     cout << ret << endl;
//     return 0;
// }
// 
//
//  
