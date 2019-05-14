/**
 * Code developed and maintained by Sharded-Games.
 * Licensed under the GPLv3
 *
 * @author Dave Cotterill
 *
 * (c)2018 ShardedGames.com, https://github.com/sharded-gaming/opengl-cross-platform-example
 *
 * Please keep this notice here AS IS going forward.
 * ShardedGames and the author provide no warranty and liability for the code provided AS IS.
 */

#ifndef __LIST_H__
#define __LIST_H__

/**
 * \class List 
 * TEMPLATE CLASS.
 * Used to create an array of any type of object
 * Designed to be the same size as the number of elements in-side
 * Other Useful lists.
 *  * Pre-allocated (resizable) array use @class AllocList
 *  * Rolling window list (FIFO) use @class RollingList
 */
template<class T>
class List {
private:	
	T*		mList;
	U32		mLength;

	void	resize(U32 dif);

public:
	List();
	List(T t);
	List(T t, T t2);
	List(const List<T>&);
	~List();

	void	add		(T t);
	void	add		(List<T>* t);
	void	remove	(T t);
	T		get		(U32 idx) const;
	inline U32		length	() const			{	return mLength;	}

	void	deleteArray();
};

/** 
 * Constructor 
 */
template <class T>
List<T>::List()
{
	mLength = 0;
	mList = NULL;
}

/**
 * Constructor
 */
template <class T>
List<T>::List(T t)
{
	mLength = 0;
	mList = NULL;
	add(t);
}

/**
 * Constructor
 */
template <class T>
List<T>::List(T t, T t2)
{
	mLength = 0;
	mList = NULL;
	add(t);
	add(t2);
}

template <class T>
List<T>::List(const List<T>& v)
{
	mLength = 0;
	mList = NULL;
	for (U32 i = 0; i < v.length(); i++)
	{
		add(v.get(i));
	}
	//add(&v);
}

/** 
 * Destructor
 */
template <class T>
List<T>::~List<T>()
{
	mLength = 0;
	SAFEDELETE(mList);
}

/**
 * Internally used to resize the list array
 * @param dif size to increase the array by
 */
template <class T>
void List<T>::resize(U32 dif)
{
	if(!mList && dif > 0)
	{
		mList = DBG_NEW T[dif];
		mLength = dif;
	}
	else if(mList)
	{
		T* list = mList;
		U32 oLen = mLength;
		mLength += dif;
		mList = DBG_NEW T[mLength];

		// Copy 
		memcpy(mList, list, sizeof(T) * oLen);

		// Remove
		SAFEDELETE(list);
	}
}

/**
 * add's an element to the end of the array 
 * @param t Element to add
 */
template <class T>
void List<T>::add(T t)
{
	U32 p = mLength;
	resize(1);
	mList[p] = t;
}

/** 
 * Combines a list into this list
 * @param t List to append (Must be same type)
 */
template <class T>
void List<T>::add(List<T>* t)
{
	U32 p = mLength;
	resize(t->length());
	for (U32 i = 0; i < t->length(); i++)
	{
		mList[p + i] = t->get(i);
	}
}

/**
 * Gets an element 
 * @param idx Index of element in array
 * @returns Element or NULL if failed
 */
template <class T>
T List<T>::get(U32 idx) const
{
	if(idx >= 0 && idx < mLength)
	{
		return mList[idx];
	}
	return static_cast <T> (NULL);
}

/**
 * Deletes all the elements in the array
 */
template <class T>
void List<T>::deleteArray()
{
	for(U32 i = 0 ; i < mLength ; i++)
	{
		SAFEDELETE(mList[i]);
	}
	SAFEDELETE(mList);
	mLength = 0;
}

/**
 * Removes an element from the array
 * @param t Element to find/remove
 */
template <class T>
void List<T>::remove(T t)
{
	bool found = false;
	for(U32 i = 0 ; i < mLength ; i++)
	{
		if(found)
		{
			mList[i-1] = mList[i];
		}
		else if(mList[i] == t)
		{
			found = true;
		}
	}
	mLength--;
}


#endif //__LIST_H__
