#ifndef SNAKETAB_H
#define SNAKETAB_H

//#define Temp template<class T>

#include"SnakeTabElement.h"

template<class T>
class SnakeTab
{
protected:
	SnakeTabElement<T> *m_first;
	SnakeTabElement<T> *m_last;

	size_t m_count;
public:
	SnakeTab()
	{
		m_first = nullptr;
		m_last = nullptr;

		m_count = 0;
	}
	~SnakeTab()
	{
		while (m_count > 1)
		{
			m_last = m_last->m_previous;
			delete m_last->m_next;

			m_count--;
		}
		delete m_last;
	}
	void add(T content)
	{
		SnakeTabElement<T> *element = new SnakeTabElement<T>(content);

		if (m_first != nullptr)
		{
			m_last->m_next = element;
			element->m_previous = m_last;
			m_last = element;
		}
		else
		{
			m_first = element;
			m_last = element;
		}
		m_count++;
	}
	bool remove(SnakeTabElement<T> *element)
	{
		if (m_count == 0)
		{
			printf("WUT HAPENT???\nIDK, IDK... (WTF???)\n");
			return false;
		}

		if (element->m_previous != nullptr && element->m_next != nullptr)
		{
			element->m_previous->m_next = element->m_next;
			element->m_next->m_previous = element->m_previous;

			element->m_previous = nullptr;
			element->m_next = nullptr;
		}
		else if (element->m_previous != nullptr)
		{
			m_last = element->m_previous;

			element->m_previous->m_next = nullptr;

			element->m_previous = nullptr;
		}
		else if (element->m_next != nullptr)
		{
			m_first = element->m_next;

			element->m_next->m_previous = nullptr;

			element->m_next = nullptr;
		}
		else
		{
			m_first = nullptr;
			m_last = nullptr;
		}

		m_count--;

		return true;
	}
	bool remove(size_t indeks)
	{
		if (m_count == 0)
			return false;

		SnakeTabElement<T> *element = m_first;

		for (size_t i = 0; i <= indeks; i++)
		{
			if (i == indeks)
				return remove(element);
			element = element->m_next;
		}

		return false;
	}
	SnakeTabElement<T>* getFirst() const
	{
		return m_first;
	}
	SnakeTabElement<T>* getLast() const
	{
		return m_first;
	}
	size_t getCount()
	{
		return m_count;
	}
};

#endif