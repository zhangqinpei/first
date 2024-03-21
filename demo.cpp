#include <cstddef>
#include <memory>  
#include <mutex>   
#include <iostream>
#include <iostream>
#include <thread>

using namespace std;

template <typename T>
class myvector 
{
public:
	myvector(): size(0),data(nullptr),capacity(0){}    //构造函数                    //军规：类成员变量、局部变量必须初始化

	void reserve(size_t new_capacity) //扩容函数
	{
		lock_guard<mutex> lock(mtx);                                                // 军规：多线程数据访问必须保证读写安全

		if (new_capacity <= capacity) {  // 如果新容量小于等于当前容量，返回
			return;
		}
		T* new_data = new T[capacity];
		if(new_data)                                                                 // 军规：指针判空
		{
			for (size_t i = 0; i < capacity; i++)
			{
				new_data[i] = data[i];
			}
			delete[] data;
		}

		data = new_data;          //更新后把新地址复制给data
		capacity = new_capacity   //更新容量
	}
	
	void push_back(const T& value)   //尾插函数
	{ 
		
		lock_guard<mutex> lock(mtx); 
		if (size == capacity) {        //如果容器满了则扩容
			reserve(capacity ? capacity * 2 : 1); 
		}
		data[size] = value;  
		++size;  
	}

	void pop_back() // 尾删函数
	{  
		
		lock_guard<mutex> lock(mtx); 
		if (size > 0) { 
			--size;  
		}
		else cout << "没有元素可删除" << endl;
	}

	void insert(size_t pos, const T& value) {  //插入函数
		lock_guard<mutex> lock(mtx);  
		if (pos > size) {  // 如果位置超出范围返回
			return;
		}
		if (size == capacity) {  // 如果容器满了则扩容
			reserve(capacity ? capacity * 2 : 1);  
		}
		for (size_t i = size; i > pos; --i) {  // 将位置 pos 及之后的元素向右移动一位
			data[i] = data[i - 1];
		}
		data[pos] = value;  
		++size; 
	}
private:
	T* data;
	size_t size;
	size_t capacity;
	mutex mtx;
};



void pushElements(myvector<int>& vec, int start, int end) {
	for (int i = start; i < end; ++i) {
		vec.push_back(i);
	}
}

int main() {
	MyVector<int> vec;

	// 创建两个线程并发地向向量中添加元素
	std::thread t1(pushElements, std::ref(vec), 0, 5);
	std::thread t2(pushElements, std::ref(vec), 5, 10);

	// 将线程与主线程合并
	t1.join();
	t2.join();

	// 输出向量中的元素
	for (std::size_t i = 0; i < vec.size; ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}