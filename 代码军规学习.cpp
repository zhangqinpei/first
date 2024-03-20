#include <iostream>

//  һ ��ĳ�Ա�����ڹ��캯���н��г�ʼ�� 
// ��ֹδ������Ϊ ���³������
class MyClass {
public:
    // ���캯���г�ʼ����ĳ�Ա����
    MyClass(int value) : memberVariable(value) {
        // �����ڹ��캯���жԳ�Ա�������г�ʼ��
    }

    void printMemberVariable() {
        std::cout << "Member variable: " << memberVariable << std::endl;
    }

private:
    int memberVariable;
};

int main() {
    // ���� MyClass ����ʱ�����ù��캯�����г�ʼ��
    MyClass obj(10);
    obj.printMemberVariable();

    return 0;
}


// �� ��ֹʹ�ò���ȫ��CRT����
// CRT��C���Կ� �л���������ķ���
// ����ʹ��_s��׺�İ�ȫ���� �磬strcpy_s strcat_s��dest,��������С��src��
//����
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


//�� ׼��ź��������еĽṹ��Ͷ���ֻ�ܴ�ָ�����������
// ���ⲻ��Ҫ�Ŀ�����ռ���ڴ棬�ṩ����

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


//�� �з�����ڴ桢�򿪾����Դ�ȱ����ڲ��õ�ʱ������ͷ�
// ����Ӱ����������ʹ��
// �����ڴ�
int* pInt = new int(42);
// ���ļ�
FILE* file = fopen("example.txt", "r");
// �ڲ�ʹ��ʱ�ͷ��ڴ�͹ر��ļ����
if (pInt != nullptr) {
    delete pInt;
    pInt = nullptr;
}

if (file != nullptr) {
    fclose(file);
    file = nullptr;
}


//�� ���ڶ��̷߳��ʵ����ݱ�����������
// ��֤���ݰ�ȫ
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


// �� ���е�����������C++�Ķ���������װʹ��
// ʹ��lock_guard ������ �����ֶ��ͷ���

// ���������ڱ�����������
std::mutex mtx;
int sharedData = 0;

// �̺߳������������ӹ�������
void incrementSharedData() {
    std::lock_guard<std::mutex> lock(mtx); // ʹ��std::lock_guard����������
    sharedData++; // ���ӹ�������
}

int main() {
    // ���������̣߳��ֱ�Թ������ݽ������Ӳ���
    std::thread t1(incrementSharedData);
    std::thread t2(incrementSharedData);

    t1.join(); // �ȴ�t1�߳�ִ�����
    t2.join(); // �ȴ�t2�߳�ִ�����
    // ������յĹ�������ֵ
    std::cout << "Final value of sharedData: " << sharedData << std::endl;
    return 0;
}


// �� �ز����ٵ��ݴ���
//����ϵͳ���ߵ� 3 ���ṩ�ӿ� / API ����Է���ֵ�����жϴ���
//�����Ӧ����Ϣ���Ա�ʾ�Ƿ�ɹ� ���б�Ҫ���ݴ���
#include <iostream>
// ģ����õ�����API�ĺ���
int CallThirdPartyAPI()
{
    // ģ�������API����ֵ
    return -1; // ���践��-1��ʾ����ʧ��
}

int main()
{
    // ���õ�����API
    int result = CallThirdPartyAPI();

    // �Է���ֵ�����жϴ���
    if (result == -1)
    {
        std::cerr << "Error: Failed to call the third party API." << std::endl;
        // ���Ը��ݾ�����������ݴ����������ԡ���¼��־��
    }
    else
    {
        // ����API���صĽ��
        std::cout << "Third party API call succeeded. Result: " << result << std::endl;
    }

    return 0;
}