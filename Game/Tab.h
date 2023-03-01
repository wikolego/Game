#ifndef TAB_H
#define TAB_H

#define Temp template<class T>

template<class T>
class Tab
{
	friend class UnitsGroup;
protected:
	size_t m_size;
	T *m_tab;

public:
	Tab()
	{
		m_size = 0;
	}
	Tab(size_t size)
	{
		m_size = size;
		m_tab = new T[m_size];
	}
	~Tab()
	{
		delete[] m_tab;
	}
	void init(size_t size)
	{
		if (m_size > 0)
			delete[] m_tab;

		m_size = size;
		m_tab = new T[m_size];
	}
	void clear()
	{
		delete[] m_tab;
		m_size = 0;
	}
	void setElement(T element, size_t indeks)
	{
		m_tab[indeks] = element;
	}
	void addElement(T element)
	{
		T *newTab = new T[m_size + 1];

		for (int i = 0; i < m_size; i++)
			newTab[i] = m_tab[i];
		newTab[m_size++] = element;

		delete[] m_tab;
		m_tab = newTab;
	}
	void addElement(T element, size_t indeks)
	{
		T *newTab = new T[m_size + 1];

		int i = 0;
		while (i < indeks)
		{
			newTab[i] = m_tab[i];
			i++;
		}

		newTab[i++] = element;

		m_size++;
		while (i < m_size)
		{
			newTab[i] = m_tab[i - 1];
			i++;
		}
		delete[] m_tab;
		m_tab = newTab;
	}
	void removeElement(size_t indeks)
	{
		T *newTab = new T[m_size - 1];

		int i = 0;
		while (i < indeks)
		{
			newTab[i] = m_tab[i];
			i++;
		}
		i++;
		while (i < m_size)
		{
			newTab[i - 1] = m_tab[i];
			i++;
		}

		delete[] m_tab;
		m_tab = newTab;
		m_size--;
	}
	T operator[](size_t indeks)
	{
		return m_tab[indeks];
	}
	T getElement(size_t indeks) const
	{
		return m_tab[indeks];
	}
	T* getElementPointer(size_t indeks) const
	{
		return &(m_tab[indeks]);
	}
	size_t getSize() const
	{
		return m_size;
	}
};

#endif