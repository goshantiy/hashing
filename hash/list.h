#pragma once
#include <iostream>
template<class T> class List//класс шаблон список
{
public:
	class Node
	{
	public:
		Node* nx;//указатель на следующий
		Node* prev;//указатель на предыдущий
		T data;//значение
	};
	List()//конструктор по умолчанию
	{

		Head = Tail = Current = NULL;//пустой список
		size = 0;
	}
	List(int sz)//конструктор размера size
	{
		Node* ptr = NULL;
		Node FictHead;//создаем фиктивную голову
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
			ptr->nx = new Node;//создаем новый элемент
			if (ptr->nx)
			{
				ptr->nx->prev = ptr;//устанавливаем связи
				ptr->nx->data = 0;//по умолчанию data 0
				ptr->nx->nx = NULL;//указатель на последующий null
			}
		}
		Head = FictHead.nx;//устанавливаем голову
		if (Head)
			Head->prev = NULL;//предыдущий для головы элемент null
		if (ptr)
			Tail = ptr;//последний элемент хвост
		Current = FictHead.nx;//текущий элемент(первый)
	}
	List(T* arr, int sz)//конструктор из массива
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
			ptr->nx = new Node;//создаем элемент
			if (ptr->nx)
			{
				ptr->nx->prev = ptr;
				ptr->nx->data = arr[i];//заполняем элементами массива
				ptr->nx->nx = NULL;
				Tail = ptr->nx;//устанавливаем хвост
			}
			size++;
		}
		Head = FictHead.nx;//устанавливаем голову
		if (Head)
			Head->prev = NULL;//предыдущий для головы null
		Current = FictHead.nx;//текущий элемент(первый)
	}

	List(List<T>& obj)//копирование
	{
		Node FictHead;//фиктивная голова
		FictHead.nx = NULL;
		FictHead.prev = NULL;
		Node* ptr = NULL;
		Node* ptr1 = obj.Head;//указатель на обьект
		if (obj.size)//проверяем размер
		{
			ptr = &FictHead;
			while (ptr1)//двигаемся по обьекту
			{
				ptr->nx = NULL;
				ptr->nx = new Node;//создаем элемент
				if (ptr)
				{
					ptr->nx->prev = ptr;//устанавливаем связи
					ptr->nx->nx = NULL;
					ptr->nx->data = ptr1->data;//копируем значения
					size++;

					if (ptr1 == obj.Current)//устанавливаем текущий 
						Current = ptr->nx;
					if (ptr1 == obj.Tail)//устанавливаем хвост
						Tail = ptr->nx;
					ptr1 = ptr1->nx;//двигаем указатели на следующий элемент
					ptr = ptr->nx;
				}
			}
			Head = FictHead.nx;//устанавливаем голову
			if (Head)
				Head->prev = NULL;//предыдущий для головы null
		}
		else
		{
			Head = Tail = Current = NULL;//пустой список
			size = 0;
		}

	}

	int Find(T& key)//поиск по ключу, возвращаем номер
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
		//while (ptr && ptr->data != key)//двигаемся по списку пока не найдем ключ
		//{
		//	ptr = ptr->nx;
		//	res++;
		//}
		//if (ptr)
		//	return res;//если нашли
		//return -1;//если не нашли
	}

	friend std::ostream& operator<<(std::ostream& out, const List<T>& obj)//вывод
	{

		Node* ptr = obj.Head;//указатель на голову
		while (ptr)
		{
			
			std::cout << ptr->data << " ";//двигаемся по списку выводя значения
			ptr = ptr->nx;
		}
		return out;
	}
	friend std::istream& operator>>(std::istream& in, List<T>& obj)//ввод
	{
		std::cout << "enter size ";//вводим размер
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
		for (int i = 0; i < sz && ptr; i++, obj.size++)//вводим значения
		{
			ptr->nx = new Node;
			if (ptr->nx)
			{
				ptr->nx->prev = ptr;//устанавливаем связи
				std::cin >> ptr->nx->data;//вводим значение
				ptr->nx->nx = NULL;
			}
			ptr = ptr->nx;//двигаем указатель на следующий элемент
		}
		obj.Tail = ptr;//устанавливаем хвост
		obj.Head = FictHead.nx;//устанавливаем голову
		obj.Head->prev = NULL;//предыдущий для головы null
		obj.Current = obj.Head;//текущий голова
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


	bool DelCurrent()//удаляем текущий
	{
		if (Current)//проверяем указатель
		{
			Node* ptr = Current;
			if (Current != Head)//если не голова
				ptr->prev->nx = ptr->nx;//перекидываем связи 
			else
			{
				Head = Head->nx;//если голова, сдвигаем указатель на голову
				if (Head)
					Head->prev = NULL;//предыдущий для головы null
			}
			if (Current != Tail)//если не хвост
				ptr->nx->prev = ptr->prev;//перекидываем связи 
			else
			{
				Tail = Tail->prev;//если хвост, сдвигаем указатель на хвост
				if (Tail)
					Tail->nx = NULL;//следующий для хвоста null
			}
			if (ptr->nx)//если есть следующий элемент устанавливаем его текущим
				Current = ptr->nx;
			else//если нету устанавливаем предыдущий элемент текущим
				Current = ptr->prev;
			delete ptr;//удаляем
			size--;//уменьшаем размер на 1
			return true;
		}
		return false;
	}
	void ResetCurrent()//текущий элемент голова
	{
		Current = Head;
	}
	bool NextCurrent()//двигаем вперед текущий элемент
	{
		if (Current && Current->nx)//если есть текущий и следующий
		{
			Current = Current->nx;//следующий становится текущим
			return true;
		}
		return false;
	}

	bool MoveCurrent(int step)//двигаем текущий на step 
	{
		Node* ptr = Current;//указатель на текущий
		if (step >= 0)//если шаг положиткльный
		{
			//Node * ptr = Current;
			for (int i = 0; i < step && ptr; i++, ptr = ptr->nx);
			if (ptr)
				Current = ptr;//двигаем текущий вперед пока не дойдем до +step или до конца списка
			return true;
		}
		else
		{
			for (int i = 0; i < -step && ptr; i++, ptr = ptr->prev);
			if (ptr)
				Current = ptr;//двигаем текущий назад пока не дойдем до -step или до начала списка
			return true;
		}
		return false;
	}
	bool PrevCurrent()//двигаем назад текущий элемент
	{
		if (Current && Current->prev)//если есть текущий и предыдущий
		{
			Current = Current->prev;//предыдущий становится текущим
			return true;
		}
		return false;
	}
	bool ResetCurrentTail()//устанавливаем текущим хвост
	{
		if (Tail)//если хвост не null
		{
			Current = Tail;//текущий хвост
			return true;
		}
		return false;
	}
	bool AddToCurrent(T key)//добавить элемент с ключом key
	{
		Node* Elem = NULL;
		Elem = new Node;//создаем
		if (Elem)
		{
			Elem->data = key;//устанавливаем ключ
			Elem->prev = NULL;
			Elem->nx = NULL;
			if (Current)
			{
				if (Current->prev)//если есть предыдущий
					Current->prev->nx = Elem;//для предыдущего текущему следующий  -новый элемент
				Elem->nx = Current;//для нового элемента следующий - текущий
				Elem->prev = Current->prev;//устанавливаем предыдущий для нового элемента
				Current->prev = Elem;//предыдущий для текущего - новый элемент
				if (Head == Current)//если текущий был головой
					Head = Elem;//устанавливаем новый элемент как голову
				Current = Elem;//новый становится текущим
			}
			else
			{
				Head = Tail = Elem;//хвост голова и текущий - новый элемент
				Current = Elem;
			}
			size++;//увеличиваем размер
			return true;
		}
		return false;
	}

	bool AddToHead(T key)//добавить в голову элемент с ключом 
	{
		Node* Elem = NULL;
		Elem = new Node;//создаем
		if (Elem)
		{
			Elem->data = key;//устанавливаем ключ
			Elem->prev = NULL;//устанавливаем предыдущий - null
			Elem->nx = Head;//устанавливаем следующий - head
			if (Head)//если не null
			{
				Head->prev = Elem;//предыдущий для головы - новый элемент
			}
			else
			{
				Tail = Elem;//хвост
				Current = Elem;//текущий
			}
			Head = Elem;//устанавливаем голову
			if (size)//устанавливаем текущий если список был не пуст
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
	bool AddToTail(T key)//добавить в хвост элемент с ключом
	{
		Node* Elem = NULL;
		Elem = new Node;//создаем
		if (Elem)
		{
			Elem->data = key;//устанавливаем ключ
			Elem->prev = Tail;//устанавливаем предыдущий - хвост
			Elem->nx = NULL;
			if (Tail)//если хвост не null
			{
				Tail->nx = Elem;//следующий для хвоста - новый элемент
			}
			else//иначе
			{
				Head = Elem;//голова
				Current = Elem;//хвост
			}
			Tail = Elem;//устанавливаем хвостом
			size++;
			return true;
		}
		return false;
	}

	bool AddToPos(int pos, T key)//добавить по номеру позиции элемент с ключом 
	{
		Node* ptr = NULL;
		ptr = Head;
		if (pos <= size)
		{
			if (pos == size)//если позиция - хвост
				return AddToTail(key);
			if (pos == 0)//если позиция - голова
				return AddToHead(key);
			for (int i = 0; i < pos; i++, ptr = ptr->nx);//двигаемся до позиции
			Node* Elem = NULL;
			Elem = new Node;//создаем
			if (Elem)
			{
				Elem->prev = ptr->prev;//устанавливаем связи
				Elem->nx = ptr;
				Elem->data = key;//устанавливаем ключ
				if (ptr == Current)//если элемент на позиции был текущим
					Current = Elem;//новый становится текущим
				ptr->prev->nx = Elem;//перекидываем связи
				ptr->prev = Elem;
				size++;
				return true;
			}
			else
				return false;
		}
		return false;
	}
	bool AddAfterKey(T datakey, T key)//добавить после ключа элемент с ключом
	{
		Node* ptr = NULL;
		ptr = Head;
		for (ptr = Head; ptr && ptr->data != key; ptr = ptr->nx);//двигаемся пока не найдем ключ или до конца списка
		if (ptr)
		{
			Node* Elem = NULL;
			Elem = new Node;//создаем
			if (Elem)
			{
				Elem->prev = ptr;//устанавливаем связи
				Elem->nx = ptr->nx;
				Elem->data = datakey;//устанавливаем ключ
				if (ptr->nx == Current)//если элемент с ключом был текущим, новый элемент - текущий
					Current = Elem;
				if (ptr == Tail)//если элемент с ключом был хвост, новый элемент - хвост
					Tail = Elem;
				if (ptr->nx)//если есть следующий
					ptr->nx->prev = Elem;//предыдущий для следующего - новый элемент
				ptr->nx = Elem;//следующий - новый элемент
				size++;
				return true;
			}
			return false;
		}
		else
			return false;
	}
	bool DelFromHead()//удалить с головы
	{
		if (Head)//если не null
		{
			Node* ptr = Head;
			Head = Head->nx;//сдвигаем голову
			if (Head)//если не null
				Head->prev = NULL;//предыдущий для новой головы - null
			else
			{
				Current = Tail = NULL;//пустой список
			}
			if (ptr == Current)//если был текущим, сдвигаем текущий
				Current = Current->nx;
			size--;//уменьшаем размер
			delete ptr;//удаляем
			return true;
		}
		return false;
	}
	bool DelFromTail()//удалить с хвоста
	{
		if (Tail)//если не null
		{
			if (Head == Tail)//если список из одного
			{
				delete Tail;//удаляем
				Head = Current = Tail = NULL;//указатели на null
				size--;//уменьшаем размер
				return true;
			}
			if (Current == Tail)//если текущий хвост
				Current = Current->prev;//сдвигаем текущий
			Tail = Tail->prev;//сдвигаем хвост
			delete Tail->nx;//удаляем
			Tail->nx = NULL;//следующий для нового хвоста - null
			size--; //уменьшаем размер
			return true;
		}
		return false;
	}
	bool DelFromPos(int pos)//удалить по позиции
	{
		Node* ptr;
		ptr = Head;
		if (pos <= size && size > -1)//если есть такая
		{
			if (pos == size - 1)//если в хвосте
				return DelFromTail();
			if (pos == 0)//если в голове
				return DelFromHead();
			for (int i = 0; i < pos; i++, ptr = ptr->nx);//двигаемся до позиции
			ptr->prev->nx = ptr->nx;//перекдиываем связи
			ptr->nx->prev = ptr->prev;
			if (ptr == Current)//если текущий
				Current = Current->nx;//сдвигаем
			delete ptr;//удаляем
			size--;//уменьшаем размер
			return true;
		}
		else
			return false;
	}
	bool DelKey(T key)//удалить по ключу
	{
		Node* ptr = Head;
		for (; ptr && ptr->data != key; ptr = ptr->nx);//двигаемся пока не дойдем до ключа или до конца
		if (ptr)
		{
			if (ptr == Head)
				return DelFromHead();//если голова
			if (ptr == Tail)
				return DelFromTail();//если хвост
			ptr->prev->nx = ptr->nx;//перекидываем связи
			ptr->nx->prev = ptr->prev;
			if (ptr == Current)//если текущий
				Current = Current->nx;//сдвигаем текущий
			delete ptr;//удаляем
			size--;//уменьшаем размер
			return true;
		}
		return false;
	}

	bool IsEmpty()//проверка на пустоту
	{
		if (Head)//если указатель на голову не пуст
			return false;
		else
			return true;
	}
	void Clear()//очистка
	{
		bool a = true;
		while (a)//двигаемся удаляя поочередно с хвоста элементы пока не дойдем до конца
			a = DelFromTail();
	}


	List<T>& operator=(const List<T>& obj)//присваивание
	{
		Clear();//очищаем
		Node* ptr = obj.Head;//указатель на обьект
		for (; ptr; ptr = ptr->nx)//двигаемся по списку
		{
			AddToTail(ptr->data);//добавляем в хвост 
			if (ptr == obj.Current)
				ResetCurrentTail();
		}
		return *this;
	}
	List<T> operator +(List<T>& obj)
	{
		bool a = true;
		List res(*this);//результирующий список, в начальный момент копия левого
		Node* ptr = obj.Head;//указатель на список
		while (ptr && a)
		{
			a = res.AddToTail(ptr->data);//добавляем в хвост элементы правого
			ptr = ptr->nx;//двигаемся по списку
			res.size++;//увеличиваем размер
		}
		return res;//возвращаем
	}

	bool operator==(List<T>& obj)//сравнение на равенство
	{
		Node* ptr1;
		Node* ptr2;
		if (size == obj.size)//если равный размер
		{
			for (ptr1 = Head, ptr2 = obj.Head; ptr1 && ptr2 && (ptr1->data == ptr2->data); ptr1 = ptr1->nx, ptr2 = ptr2->nx);//сравниваем ключи
			if (ptr1 == NULL && ptr2 == NULL)
				return true;
			return false;
		}
		return false;
	}
	bool operator!=(List<T>& obj)//сравнение на неравенство
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
	~List()//деструктор
	{
		bool a = true;
		while (a)
			a = DelFromTail();
	}
protected:
	Node* Head;//указатель на голову
	Node* Tail;//указатель на хвост
	Node* Current;//указатель на текущий
	int size;//размер
};

