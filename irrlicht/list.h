
//ÒÑÍê³É
#pragma once

#include "irrtypes.h"

namespace irr
{
	namespace core
	{
		template <class T>
		class list
		{
			
		private:
			struct  SKListNode
			{
				SKListNode * next;
				SKListNode * prev;
				T element;
				SKListNode() : next(0), prev(0) {}
			};

		public:
			class  Iterator
			{
			private:
				friend class list<T>;
				SKListNode * current;
			public:
				Iterator() : current(0) {};
				Iterator(SKListNode * begin) : current(begin){};

				bool operator ++()	{ current = current->next; };
				bool operator --()	{ current = current->prev; };
				bool operator ==(const Iterator& other) const { return current == other.current; };
				bool operator != (const Iterator& other) const { return current != other.current; };
				T& operator *() { return current->element; };

			private:

			};

			 Iterator:: Iterator()
			{
			}

			 Iterator::~ Iterator()
			{
			}
		private:
			SKListNode * root;
			SKListNode * last;
			u32 size;
		public:
			list() : root(0), last(0) {}
			~list() { clear(); }

			u32 getSize() const
			{
				return size;
			}

			void clear()
			{
				SKListNode * node = root;
				while (node)
				{
					SKListNode * next = node->next;
					delete node;
					node = next;
				}
				root = 0;
				last = 0;
				size = 0;
			}

			bool empty() const
			{
				return root == 0;
			}

			void push_back(const T& element)
			{
				SKListNode * node = new SKListNode;
				node->element = element;
				++size;

				if ( root == 0 )
				{
					root = node;
				}

				node->prev = last;

				if ( last != 0 )
				{
					last->next = node;
				}
				last = node;
			}
			void push_front(const T& element)
			{
				SKListNode * node = new SKListNode;
				node->elment = element;
				++size;
				if ( root == 0 )
				{
					last = node;
					root = node;
				}
				else
				{
					node->next = root;
					root->prev = node;
					root = node;
				}

			}

			Iterator begin() const
			{
				return Iterator(root);
			}
			Iterator end() const
			{
				return Iterator(0);
			}
			Iterator getLast() const
			{
				return Iterator(last);
			}

			void insert_after(Iterator& it, const T& element)
			{
				SKListNode * node = new SKListNode;
				node->element = element;
				node->next = it.current->next;
				if (it.current->next)
				{
					it.current->next->prev = node;
				}
				node->prev = it.current;
				it.current->next = node;
			}
			void insert_before(Iterator& it, const T& element)
			{
				SKListNode * node = new SKListNode;
				node->element = element;
				node->prev = it.current->prev;
				if (it.current->prev)
				{
					it.current->prev->next = node;
				}
				node->next = it.current;
				it.current->prev = node;
			}
			Iterator erase(Iterator& it)
			{
				Iterator returnIterator(it);
				returnIterator++;
				if (it.current == root)
				{
					root = it.current->next;
				}
				if (it.current == last)
				{
					last = it.current->prev;
				}
				if (it.current->next)
				{
					it.current->next->prev = it.current->prev;
				}
				if (it.current->prev)
				{
					it.current->prev->next = it.current->next;
				}
				delete it.current;
				it.current = 0;
				--size;

				return returnIterator;
			}
		};

		
	}
}