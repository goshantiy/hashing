#pragma once
#include <iostream>
#include "list.h"
template<class X> class Hash
{
private:
	List<X>* HashTab;//������� �����������
	int(*HashFunc)(X& key, int size);//����� �����������
	int size;//������ �������
public:
	Hash(int(*function)(X& key, int Size), int Size)//�����������, �������� ����� ����������� � ������ �������
	{	
		HashFunc = function;
		size = Size;
		HashTab = new List<X>[size];
		if (!HashTab)
			throw "Memory problem";
	}
	Hash(Hash<X>& obj)//����������� �����������
	{
		size = obj.size;
		HashTab = new List<X>[size];
		for (int i = 0; i < size; HashTab[i] = obj.HashTab[i], i++);
	}

	~Hash()//����������
	{
		if (HashTab)
			delete[] HashTab;
		HashTab = nullptr;
	}

	Hash<X>& operator = (Hash<X>& obj)//���������� ������������
	{
		// ��������� ����������� ������, ���� ����������, �� ������ ������������ ������, ���� ������, �� �������� �����������
		if (size != obj.size)
		{
			delete[] HashTab;
			size = obj.size;
			HashTab = new List<X>[size];
		}
		for (int i = 0; i < size; HashTab[i] = obj.HashTab[i], i++);
	}

	void Add(X& key)
	{
		
		int ix = HashFunc(key, size);//������� ������
		HashTab[ix].AddToTail(key);	// ��������� key � ������ ��� ������� ix
	}

	int Find(X& key)
	{
		int i=HashFunc(key,size);		
		if(i<size && (HashTab[i]).Find(key) != -1);// ���� � ����� ������ ����� ����, ���� �� ����� ���������� -1
			return i;//���� ����� ���������� ����� ������
			return -1;
	}

	bool Delete(X& key)//������� ����
	{
		int i;
		for (i = 0; i < size && !HashTab[i].DelKey(key); i++);//��������� �� �������, � ������� ������ ������� �������(���� ����� true, �� ����� false) 
	
		if (i == size)//���� �� �����
			return false;
		else//���� �����
			return true;
	}

	void Clear()//�������
	{
		for (int i = 0; i < size; i++)
			HashTab[i].Clear();
	}
	friend std::ostream& operator << (std::ostream& out, Hash<X>& obj)// ���������� ���������� ������
	{
		for (int i = 0; i < obj.size; i++)
		{
			out << i << ": ";
			if (!obj.HashTab[i].IsEmpty())
				out << obj.HashTab[i] << '\n';
			else
				out << "null\n";
		}
		return out;
	}
};

