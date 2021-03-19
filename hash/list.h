#pragma once
#include <iostream>
template<class T> class List//����� ������ ������
{
public:
	class Node
	{
	public:
		Node* nx;//��������� �� ���������
		Node* prev;//��������� �� ����������
		T data;//��������
	};
	List()//����������� �� ���������
	{

		Head = Tail = Current = NULL;//������ ������
		size = 0;
	}
	List(int sz)//����������� ������� size
	{
		Node* ptr = NULL;
		Node FictHead;//������� ��������� ������
		FictHead.nx = NULL;
		FictHead.prev = NULL;
		ptr = &FictHead;
		if (sz <= 0)
		{
			List();
			return;
		}
		for (int i = 0; i < sz && ptr; i++, ptr = ptr->nx, sz++, i++)
		{
			ptr->nx = NULL;
			ptr->nx = new Node;//������� ����� �������
			if (ptr->nx)
			{
				ptr->nx->prev = ptr;//������������� �����
				ptr->nx->data = 0;//�� ��������� data 0
				ptr->nx->nx = NULL;//��������� �� ����������� null
			}
		}
		Head = FictHead.nx;//������������� ������
		if (Head)
			Head->prev = NULL;//���������� ��� ������ ������� null
		if (ptr)
			Tail = ptr;//��������� ������� �����
		Current = FictHead.nx;//������� �������(������)
	}
	List(T* arr, int sz)//����������� �� �������
	{
		Node* ptr = NULL;
		Node FictHead;
		FictHead.nx = NULL;
		FictHead.prev = NULL;
		ptr = &FictHead;
		Tail = Current = NULL;
		size = 0;
		for (int i = 0; (i < sz) && ptr; i++, ptr = ptr->nx)
		{
			ptr->nx = NULL;
			ptr->nx = new Node;//������� �������
			if (ptr->nx)
			{
				ptr->nx->prev = ptr;
				ptr->nx->data = arr[i];//��������� ���������� �������
				ptr->nx->nx = NULL;
				Tail = ptr->nx;//������������� �����
			}
			size++;
		}
		Head = FictHead.nx;//������������� ������
		if (Head)
			Head->prev = NULL;//���������� ��� ������ null
		Current = FictHead.nx;//������� �������(������)
	}

	List(List<T>& obj)//�����������
	{
		Node FictHead;//��������� ������
		FictHead.nx = NULL;
		FictHead.prev = NULL;
		Node* ptr = NULL;
		Node* ptr1 = obj.Head;//��������� �� ������
		if (obj.size)//��������� ������
		{
			ptr = &FictHead;
			while (ptr1)//��������� �� �������
			{
				ptr->nx = NULL;
				ptr->nx = new Node;//������� �������
				if (ptr)
				{
					ptr->nx->prev = ptr;//������������� �����
					ptr->nx->nx = NULL;
					ptr->nx->data = ptr1->data;//�������� ��������
					size++;

					if (ptr1 == obj.Current)//������������� ������� 
						Current = ptr->nx;
					if (ptr1 == obj.Tail)//������������� �����
						Tail = ptr->nx;
					ptr1 = ptr1->nx;//������� ��������� �� ��������� �������
					ptr = ptr->nx;
				}
			}
			Head = FictHead.nx;//������������� ������
			if (Head)
				Head->prev = NULL;//���������� ��� ������ null
		}
		else
		{
			Head = Tail = Current = NULL;//������ ������
			size = 0;
		}

	}

	int Find(T& key)//����� �� �����, ���������� �����
	{
		Node* ptr = Head;
		int k = 0;

		while (ptr)
		{
			if (ptr->data == key)
				return k;
			k++;
			ptr = ptr->nx;
		}
		return -1;
		//int res = 0;
		//Node* ptr = Head;
		//while (ptr && ptr->data != key)//��������� �� ������ ���� �� ������ ����
		//{
		//	ptr = ptr->nx;
		//	res++;
		//}
		//if (ptr)
		//	return res;//���� �����
		//return -1;//���� �� �����
	}

	friend std::ostream& operator<<(std::ostream& out, const List<T>& obj)//�����
	{

		Node* ptr = obj.Head;//��������� �� ������
		while (ptr)
		{
			
			std::cout << ptr->data << " ";//��������� �� ������ ������ ��������
			ptr = ptr->nx;
		}
		return out;
	}
	friend std::istream& operator>>(std::istream& in, List<T>& obj)//����
	{
		std::cout << "enter size ";//������ ������
		int sz;
		std::cin >> sz;
		Node* ptr;
		ptr = obj.Tail;
		Node FictHead;
		FictHead.prev = NULL;
		FictHead.nx = obj.Head;
		if (obj.Head)
			obj.Head->prev = &FictHead;
		while (ptr != &FictHead && ptr)
		{
			ptr = ptr->prev;
			delete ptr->nx;
		}
		ptr = &FictHead;
		ptr->nx = NULL;
		std::cout << "\n enter data ";
		for (int i = 0; i < sz && ptr; i++, obj.size++)//������ ��������
		{
			ptr->nx = new Node;
			if (ptr->nx)
			{
				ptr->nx->prev = ptr;//������������� �����
				std::cin >> ptr->nx->data;//������ ��������
				ptr->nx->nx = NULL;
			}
			ptr = ptr->nx;//������� ��������� �� ��������� �������
		}
		obj.Tail = ptr;//������������� �����
		obj.Head = FictHead.nx;//������������� ������
		obj.Head->prev = NULL;//���������� ��� ������ null
		obj.Current = obj.Head;//������� ������
		if (sz != obj.size)
			throw 1;
		return in;
	}

	int getSize()
	{
		return size;
	}

	int CurrentPos()
	{
		Node* ptr = NULL;
		int pos = 0;
		ptr = Head;
		if (ptr)
			for (; ptr != Current && ptr; pos++, ptr = ptr->nx);
		else
			return -1;
		return pos;
	}

	T& GetCurrent()
	{
		if (Current)
			return Current->data;
		throw 1;
		//	return NULL;
	}


	bool DelCurrent()//������� �������
	{
		if (Current)//��������� ���������
		{
			Node* ptr = Current;
			if (Current != Head)//���� �� ������
				ptr->prev->nx = ptr->nx;//������������ ����� 
			else
			{
				Head = Head->nx;//���� ������, �������� ��������� �� ������
				if (Head)
					Head->prev = NULL;//���������� ��� ������ null
			}
			if (Current != Tail)//���� �� �����
				ptr->nx->prev = ptr->prev;//������������ ����� 
			else
			{
				Tail = Tail->prev;//���� �����, �������� ��������� �� �����
				if (Tail)
					Tail->nx = NULL;//��������� ��� ������ null
			}
			if (ptr->nx)//���� ���� ��������� ������� ������������� ��� �������
				Current = ptr->nx;
			else//���� ���� ������������� ���������� ������� �������
				Current = ptr->prev;
			delete ptr;//�������
			size--;//��������� ������ �� 1
			return true;
		}
		return false;
	}
	void ResetCurrent()//������� ������� ������
	{
		Current = Head;
	}
	bool NextCurrent()//������� ������ ������� �������
	{
		if (Current && Current->nx)//���� ���� ������� � ���������
		{
			Current = Current->nx;//��������� ���������� �������
			return true;
		}
		return false;
	}

	bool MoveCurrent(int step)//������� ������� �� step 
	{
		Node* ptr = Current;//��������� �� �������
		if (step >= 0)//���� ��� �������������
		{
			//Node * ptr = Current;
			for (int i = 0; i < step && ptr; i++, ptr = ptr->nx);
			if (ptr)
				Current = ptr;//������� ������� ������ ���� �� ������ �� +step ��� �� ����� ������
			return true;
		}
		else
		{
			for (int i = 0; i < -step && ptr; i++, ptr = ptr->prev);
			if (ptr)
				Current = ptr;//������� ������� ����� ���� �� ������ �� -step ��� �� ������ ������
			return true;
		}
		return false;
	}
	bool PrevCurrent()//������� ����� ������� �������
	{
		if (Current && Current->prev)//���� ���� ������� � ����������
		{
			Current = Current->prev;//���������� ���������� �������
			return true;
		}
		return false;
	}
	bool ResetCurrentTail()//������������� ������� �����
	{
		if (Tail)//���� ����� �� null
		{
			Current = Tail;//������� �����
			return true;
		}
		return false;
	}
	bool AddToCurrent(T key)//�������� ������� � ������ key
	{
		Node* Elem = NULL;
		Elem = new Node;//�������
		if (Elem)
		{
			Elem->data = key;//������������� ����
			Elem->prev = NULL;
			Elem->nx = NULL;
			if (Current)
			{
				if (Current->prev)//���� ���� ����������
					Current->prev->nx = Elem;//��� ����������� �������� ���������  -����� �������
				Elem->nx = Current;//��� ������ �������� ��������� - �������
				Elem->prev = Current->prev;//������������� ���������� ��� ������ ��������
				Current->prev = Elem;//���������� ��� �������� - ����� �������
				if (Head == Current)//���� ������� ��� �������
					Head = Elem;//������������� ����� ������� ��� ������
				Current = Elem;//����� ���������� �������
			}
			else
			{
				Head = Tail = Elem;//����� ������ � ������� - ����� �������
				Current = Elem;
			}
			size++;//����������� ������
			return true;
		}
		return false;
	}

	bool AddToHead(T key)//�������� � ������ ������� � ������ 
	{
		Node* Elem = NULL;
		Elem = new Node;//�������
		if (Elem)
		{
			Elem->data = key;//������������� ����
			Elem->prev = NULL;//������������� ���������� - null
			Elem->nx = Head;//������������� ��������� - head
			if (Head)//���� �� null
			{
				Head->prev = Elem;//���������� ��� ������ - ����� �������
			}
			else
			{
				Tail = Elem;//�����
				Current = Elem;//�������
			}
			Head = Elem;//������������� ������
			if (size)//������������� ������� ���� ������ ��� �� ����
				Current = Current->prev;
			size++;
			return true;
		}
		return false;
	}
	operator bool()
	{
		if (Head)
			return true;
		return false;
	}
	bool AddToTail(T key)//�������� � ����� ������� � ������
	{
		Node* Elem = NULL;
		Elem = new Node;//�������
		if (Elem)
		{
			Elem->data = key;//������������� ����
			Elem->prev = Tail;//������������� ���������� - �����
			Elem->nx = NULL;
			if (Tail)//���� ����� �� null
			{
				Tail->nx = Elem;//��������� ��� ������ - ����� �������
			}
			else//�����
			{
				Head = Elem;//������
				Current = Elem;//�����
			}
			Tail = Elem;//������������� �������
			size++;
			return true;
		}
		return false;
	}

	bool AddToPos(int pos, T key)//�������� �� ������ ������� ������� � ������ 
	{
		Node* ptr = NULL;
		ptr = Head;
		if (pos <= size)
		{
			if (pos == size)//���� ������� - �����
				return AddToTail(key);
			if (pos == 0)//���� ������� - ������
				return AddToHead(key);
			for (int i = 0; i < pos; i++, ptr = ptr->nx);//��������� �� �������
			Node* Elem = NULL;
			Elem = new Node;//�������
			if (Elem)
			{
				Elem->prev = ptr->prev;//������������� �����
				Elem->nx = ptr;
				Elem->data = key;//������������� ����
				if (ptr == Current)//���� ������� �� ������� ��� �������
					Current = Elem;//����� ���������� �������
				ptr->prev->nx = Elem;//������������ �����
				ptr->prev = Elem;
				size++;
				return true;
			}
			else
				return false;
		}
		return false;
	}
	bool AddAfterKey(T datakey, T key)//�������� ����� ����� ������� � ������
	{
		Node* ptr = NULL;
		ptr = Head;
		for (ptr = Head; ptr && ptr->data != key; ptr = ptr->nx);//��������� ���� �� ������ ���� ��� �� ����� ������
		if (ptr)
		{
			Node* Elem = NULL;
			Elem = new Node;//�������
			if (Elem)
			{
				Elem->prev = ptr;//������������� �����
				Elem->nx = ptr->nx;
				Elem->data = datakey;//������������� ����
				if (ptr->nx == Current)//���� ������� � ������ ��� �������, ����� ������� - �������
					Current = Elem;
				if (ptr == Tail)//���� ������� � ������ ��� �����, ����� ������� - �����
					Tail = Elem;
				if (ptr->nx)//���� ���� ���������
					ptr->nx->prev = Elem;//���������� ��� ���������� - ����� �������
				ptr->nx = Elem;//��������� - ����� �������
				size++;
				return true;
			}
			return false;
		}
		else
			return false;
	}
	bool DelFromHead()//������� � ������
	{
		if (Head)//���� �� null
		{
			Node* ptr = Head;
			Head = Head->nx;//�������� ������
			if (Head)//���� �� null
				Head->prev = NULL;//���������� ��� ����� ������ - null
			else
			{
				Current = Tail = NULL;//������ ������
			}
			if (ptr == Current)//���� ��� �������, �������� �������
				Current = Current->nx;
			size--;//��������� ������
			delete ptr;//�������
			return true;
		}
		return false;
	}
	bool DelFromTail()//������� � ������
	{
		if (Tail)//���� �� null
		{
			if (Head == Tail)//���� ������ �� ������
			{
				delete Tail;//�������
				Head = Current = Tail = NULL;//��������� �� null
				size--;//��������� ������
				return true;
			}
			if (Current == Tail)//���� ������� �����
				Current = Current->prev;//�������� �������
			Tail = Tail->prev;//�������� �����
			delete Tail->nx;//�������
			Tail->nx = NULL;//��������� ��� ������ ������ - null
			size--; //��������� ������
			return true;
		}
		return false;
	}
	bool DelFromPos(int pos)//������� �� �������
	{
		Node* ptr;
		ptr = Head;
		if (pos <= size && size > -1)//���� ���� �����
		{
			if (pos == size - 1)//���� � ������
				return DelFromTail();
			if (pos == 0)//���� � ������
				return DelFromHead();
			for (int i = 0; i < pos; i++, ptr = ptr->nx);//��������� �� �������
			ptr->prev->nx = ptr->nx;//������������ �����
			ptr->nx->prev = ptr->prev;
			if (ptr == Current)//���� �������
				Current = Current->nx;//��������
			delete ptr;//�������
			size--;//��������� ������
			return true;
		}
		else
			return false;
	}
	bool DelKey(T key)//������� �� �����
	{
		Node* ptr = Head;
		for (; ptr && ptr->data != key; ptr = ptr->nx);//��������� ���� �� ������ �� ����� ��� �� �����
		if (ptr)
		{
			if (ptr == Head)
				return DelFromHead();//���� ������
			if (ptr == Tail)
				return DelFromTail();//���� �����
			ptr->prev->nx = ptr->nx;//������������ �����
			ptr->nx->prev = ptr->prev;
			if (ptr == Current)//���� �������
				Current = Current->nx;//�������� �������
			delete ptr;//�������
			size--;//��������� ������
			return true;
		}
		return false;
	}

	bool IsEmpty()//�������� �� �������
	{
		if (Head)//���� ��������� �� ������ �� ����
			return false;
		else
			return true;
	}
	void Clear()//�������
	{
		bool a = true;
		while (a)//��������� ������ ���������� � ������ �������� ���� �� ������ �� �����
			a = DelFromTail();
	}


	List<T>& operator=(const List<T>& obj)//������������
	{
		Clear();//�������
		Node* ptr = obj.Head;//��������� �� ������
		for (; ptr; ptr = ptr->nx)//��������� �� ������
		{
			AddToTail(ptr->data);//��������� � ����� 
			if (ptr == obj.Current)
				ResetCurrentTail();
		}
		return *this;
	}
	List<T> operator +(List<T>& obj)
	{
		bool a = true;
		List res(*this);//�������������� ������, � ��������� ������ ����� ������
		Node* ptr = obj.Head;//��������� �� ������
		while (ptr && a)
		{
			a = res.AddToTail(ptr->data);//��������� � ����� �������� �������
			ptr = ptr->nx;//��������� �� ������
			res.size++;//����������� ������
		}
		return res;//����������
	}

	bool operator==(List<T>& obj)//��������� �� ���������
	{
		Node* ptr1;
		Node* ptr2;
		if (size == obj.size)//���� ������ ������
		{
			for (ptr1 = Head, ptr2 = obj.Head; ptr1 && ptr2 && (ptr1->data == ptr2->data); ptr1 = ptr1->nx, ptr2 = ptr2->nx);//���������� �����
			if (ptr1 == NULL && ptr2 == NULL)
				return true;
			return false;
		}
		return false;
	}
	bool operator!=(List<T>& obj)//��������� �� �����������
	{
		Node* ptr1;
		Node* ptr2;
		if (size == obj.size)
		{
			for (ptr1 = Head, ptr2 = obj.Head; ptr1 && ptr2 && (ptr1->data == ptr2->data); ptr1 = ptr1->nx, ptr2 = ptr2->nx);
			if (ptr1 == NULL && ptr2 == NULL)
				return false;
			return true;
		}
		return true;
	}
	~List()//����������
	{
		bool a = true;
		while (a)
			a = DelFromTail();
	}
protected:
	Node* Head;//��������� �� ������
	Node* Tail;//��������� �� �����
	Node* Current;//��������� �� �������
	int size;//������
};

