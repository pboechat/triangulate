#ifndef TRIANGULATE_COLLECTIONUTILS_H
#define TRIANGULATE_COLLECTIONUTILS_H

#include <algorithm>
#include <list>
#include <vector>

namespace triangulate
{
	template<typename T>
	class CollectionUtils
	{
	public:
		typedef typename std::vector<T> VectorType;
		typedef typename std::vector<T>::iterator VectorIteratorType;
		typedef typename std::vector<T>::const_iterator VectorConstIteratorType;
		typedef typename std::list<T> ListType;
		typedef typename std::list<T>::iterator ListIteratorType;
		typedef typename std::list<T>::const_iterator ListConstIteratorType;

		static ListConstIteratorType GetNext(ListConstIteratorType iterator, const ListType* pList = nullptr)
		{
			ListConstIteratorType newIterator = ++iterator;

			if (pList != nullptr)
			{
				if (newIterator == pList->end())
				{
					return pList->begin();
				}
			}

			return newIterator;
		}

		static ListIteratorType GetNext(ListIteratorType iterator, ListType* pList = nullptr)
		{
			ListIteratorType newIterator = ++iterator;

			if (pList != nullptr)
			{
				if (newIterator == pList->end())
				{
					return pList->begin();
				}
			}

			return newIterator;
		}

		static VectorConstIteratorType GetNext(VectorConstIteratorType iterator, const VectorType* pVector = nullptr)
		{
			VectorConstIteratorType newIterator = ++iterator;

			if (pVector != nullptr)
			{
				if (newIterator == pVector->end())
				{
					return pVector->begin();
				}
			}

			return newIterator;
		}

		static VectorIteratorType GetNext(VectorIteratorType iterator, VectorType* pVector = nullptr)
		{
			VectorIteratorType newIterator = ++iterator;

			if (pVector != nullptr)
			{
				if (newIterator == pVector->end())
				{
					return pVector->begin();
				}
			}

			return newIterator;
		}

		static ListConstIteratorType GetPrevious(ListConstIteratorType iterator, const ListType* pList = nullptr)
		{
			if (pList != nullptr)
			{
				if (iterator == pList->begin())
				{
					return --pList->end();
				}
			}

			return --iterator;
		}

		static ListIteratorType GetPrevious(ListIteratorType iterator, ListType* pList = nullptr)
		{
			if (pList != nullptr)
			{
				if (iterator == pList->begin())
				{
					return --pList->end();
				}
			}

			return --iterator;
		}

		static VectorConstIteratorType GetPrevious(VectorConstIteratorType iterator, const VectorType* pVector = nullptr)
		{
			if (pVector != nullptr)
			{
				if (iterator == pVector->begin())
				{
					return --pVector->end();
				}
			}

			return --iterator;
		}

		static VectorIteratorType GetPrevious(VectorIteratorType iterator, VectorType* pVector = nullptr)
		{
			if (pVector != nullptr)
			{
				if (iterator == pVector->begin())
				{
					return --pVector->end();
				}
			}

			return --iterator;
		}

		CollectionUtils() = delete;

	};

}

#endif