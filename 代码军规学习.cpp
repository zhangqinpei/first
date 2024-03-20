#include <iostream>

//  一 类的成员变量在构造函数中进行初始化 
// 防止未定义行为 导致程序崩溃
class MyClass {
public:
    // 构造函数中初始化类的成员变量
    MyClass(int value) : memberVariable(value) {
        // 可以在构造函数中对成员变量进行初始化
    }

    void printMemberVariable() {
        std::cout << "Member variable: " << memberVariable << std::endl;
    }

private:
    int memberVariable;
};

int main() {
    // 创建 MyClass 对象时，调用构造函数进行初始化
    MyClass obj(10);
    obj.printMemberVariable();

    return 0;
}


// 二 禁止使用不安全的CRT函数
// CRT是C语言库 有缓冲区溢出的风险
// 建议使用_s后缀的安全函数 如，strcpy_s strcat_s（dest,缓冲区大小，src）
//例子
#include <iostream>
#include <cstring>

int main() {
    char dest[20] = "Hello, ";
    const char* src = "world!";
    errno_t err = strcat_s(dest, sizeof(dest), src);

    if (err == 0) {
        std::cout << "Concatenated string: " << dest << std::endl;
    }
    else {
        std::cout << "Error occurred while concatenating." << std::endl;
    }

    return 0;
}


//三 准则九函数参数中的结构体和对象只能传指针或引用类型
// 避免不必要的拷贝，占用内存，提供性能

struct Point {
    int x;
    int y;
};

void function1(Point& p)
{
    p.x = 10;
    p.y = 20;
}


void function2(Point* p)
{
    p->x = 30;
    p->y = 40;
}

int main()
{
    Point mypoint = { 0,0 };
    cout << mypoint.x << "," << mypoint.y << endl;
    function1(mypoint);
    cout << mypoint.x << "," << mypoint.y << endl;
    function2(mypoint);
    cout << mypoint.x << "," << mypoint.y << endl;
}


//四 有分配的内存、打开句柄资源等必须在不用的时候进行释放
// 避免影响其他程序使用
// 分配内存
int* pInt = new int(42);
// 打开文件
FILE* file = fopen("example.txt", "r");
// 在不使用时释放内存和关闭文件句柄
if (pInt != nullptr) {
    delete pInt;
    pInt = nullptr;
}

if (file != nullptr) {
    fclose(file);
    file = nullptr;
}


//五 对于多线程访问的数据必须用锁保护
// 保证数据安全
#include<thread>
#include<mutex>
mutex mtx;
int data = 1;
int add(int data)
{
    mtx.lock();
    data++;
    mtx.unlock();
}
int main()
{
    thread t1(add);

    t1.join();
    cout << "show " << endl;
    return 0;
}


// 六 所有的锁必须利用C++的对象特征封装使用
// 使用lock_guard 管理锁 避免手动释放锁

// 互斥锁用于保护共享数据
std::mutex mtx;
int sharedData = 0;

// 线程函数，用于增加共享数据
void incrementSharedData() {
    std::lock_guard<std::mutex> lock(mtx); // 使用std::lock_guard来管理互斥锁
    sharedData++; // 增加共享数据
}

int main() {
    // 创建两个线程，分别对共享数据进行增加操作
    std::thread t1(incrementSharedData);
    std::thread t2(incrementSharedData);

    t1.join(); // 等待t1线程执行完毕
    t2.join(); // 等待t2线程执行完毕
    // 输出最终的共享数据值
    std::cout << "Final value of sharedData: " << sharedData << std::endl;
    return 0;
}


// 七 必不可少的容错处理
//调用系统或者第 3 方提供接口 / API 必须对返回值进行判断处理
//输出相应的消息，以表示是否成功 进行必要的容错处理
#include <iostream>
// 模拟调用第三方API的函数
int CallThirdPartyAPI()
{
    // 模拟第三方API返回值
    return -1; // 假设返回-1表示调用失败
}

int main()
{
    // 调用第三方API
    int result = CallThirdPartyAPI();

    // 对返回值进行判断处理
    if (result == -1)
    {
        std::cerr << "Error: Failed to call the third party API." << std::endl;
        // 可以根据具体情况进行容错处理，比如重试、记录日志等
    }
    else
    {
        // 处理API返回的结果
        std::cout << "Third party API call succeeded. Result: " << result << std::endl;
    }

    return 0;
}