#ifndef SNAKETABELEMENT_H
#define SNAKETABELEMENT_H

template<class T>
class SnakeTabElement
{
	template<class T> friend class SnakeTab;

	SnakeTabElement<T> *m_previous;
	SnakeTabElement<T> *m_next;

	T m_content;

	//const Weapon *m_weapon;
public:
	SnakeTabElement()
	{
		m_previous = nullptr;
		m_next = nullptr;

		m_content = nullptr;
	}
	SnakeTabElement(T content)
	{
		m_previous = nullptr;
		m_next = nullptr;

		m_content = content;
	}
	~SnakeTabElement()
	{
		;
	}
	SnakeTabElement<T>* getPrevious() const
	{
		return m_previous;
	}
	SnakeTabElement<T>* getNext() const
	{
		return m_next;
	}
	T getContent() const
	{
		return m_content;
	}
	void removeFromTab()
	{
		if (m_previous != nullptr && m_next != nullptr)
		{
			m_previous->m_next = m_next;
			m_next->m_previous = m_previous;

			m_previous = nullptr;
			m_next = nullptr;
		}
		else if (m_previous != nullptr)
		{
			m_previous->m_next = nullptr;

			m_previous = nullptr;
		}
		else if (m_next != nullptr)
		{
			m_next->m_previous = nullptr;

			m_next = nullptr;
		}
	}
};

#endif