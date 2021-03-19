#pragma once
#include <iostream>
#include "list.h"
template<class X> class Hash
{
private:
	List<X>* HashTab;//таблица хэширования
	int(*HashFunc)(X& key, int size);//метод хэширования
	int size;//размер таблицы
public:
	Hash(int(*function)(X& key, int Size), int Size)//конструктор, передаем метод хэширования и размер таблицы
	{	
		HashFunc = function;
		size = Size;
		HashTab = new List<X>[size];
		if (!HashTab)
			throw "Memory problem";
	}
	Hash(Hash<X>& obj)//конструктор копирования
	{
		size = obj.size;
		HashTab = new List<X>[size];
		for (int i = 0; i < size; HashTab[i] = obj.HashTab[i], i++);
	}

	~Hash()//деструктор
	{
		if (HashTab)
			delete[] HashTab;
		HashTab = nullptr;
	}

	Hash<X>& operator = (Hash<X>& obj)//перегрузка присваивания
	{
		// проверяем размерности таблиц, если одинаковые, то просто переписываем списки, если разные, то изменяем размерность
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
		
		int ix = HashFunc(key, size);//находим индекс
		HashTab[ix].AddToTail(key);	// добавляем key в список под номером ix
	}

	int Find(X& key)
	{
		int i=HashFunc(key,size);		
		if(i<size && (HashTab[i]).Find(key) != -1);// ищем в каком списке лежит ключ, если не нашли возвращаем -1
			return i;//если нашли возвращаем номер списка
			return -1;
	}

	bool Delete(X& key)//удалить ключ
	{
		int i;
		for (i = 0; i < size && !HashTab[i].DelKey(key); i++);//Двигаемся по спискам, с помощью метода удаляем элемент(если нашло true, не нашло false) 
	
		if (i == size)//если не нашли
			return false;
		else//если нашли
			return true;
	}

	void Clear()//очистка
	{
		for (int i = 0; i < size; i++)
			HashTab[i].Clear();
	}
	friend std::ostream& operator << (std::ostream& out, Hash<X>& obj)// перегрузка потокового вывода
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

