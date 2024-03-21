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
	myvector(): size(0),data(nullptr),capacity(0){}    //���캯��                    //���棺���Ա�������ֲ����������ʼ��

	void reserve(size_t new_capacity) //���ݺ���
	{
		lock_guard<mutex> lock(mtx);                                                // ���棺���߳����ݷ��ʱ��뱣֤��д��ȫ

		if (new_capacity <= capacity) {  // ���������С�ڵ��ڵ�ǰ����������
			return;
		}
		T* new_data = new T[capacity];
		if(new_data)                                                                 // ���棺ָ���п�
		{
			for (size_t i = 0; i < capacity; i++)
			{
				new_data[i] = data[i];
			}
			delete[] data;
		}

		data = new_data;          //���º���µ�ַ���Ƹ�data
		capacity = new_capacity   //��������
	}
	
	void push_back(const T& value)   //β�庯��
	{ 
		
		lock_guard<mutex> lock(mtx); 
		if (size == capacity) {        //�����������������
			reserve(capacity ? capacity * 2 : 1); 
		}
		data[size] = value;  
		++size;  
	}

	void pop_back() // βɾ����
	{  
		
		lock_guard<mutex> lock(mtx); 
		if (size > 0) { 
			--size;  
		}
		else cout << "û��Ԫ�ؿ�ɾ��" << endl;
	}

	void insert(size_t pos, const T& value) {  //���뺯��
		lock_guard<mutex> lock(mtx);  
		if (pos > size) {  // ���λ�ó�����Χ����
			return;
		}
		if (size == capacity) {  // �����������������
			reserve(capacity ? capacity * 2 : 1);  
		}
		for (size_t i = size; i > pos; --i) {  // ��λ�� pos ��֮���Ԫ�������ƶ�һλ
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

	// ���������̲߳����������������Ԫ��
	std::thread t1(pushElements, std::ref(vec), 0, 5);
	std::thread t2(pushElements, std::ref(vec), 5, 10);

	// ���߳������̺߳ϲ�
	t1.join();
	t2.join();

	// ��������е�Ԫ��
	for (std::size_t i = 0; i < vec.size; ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}