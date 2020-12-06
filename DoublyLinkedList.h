#ifndef CPSC_350_DLL_H
#define CPSC_350_DLL_H

#include "ListBase.h"
#include "ListNode.h"

template <typename T>
class DoublyLinkedList : public ListBase<T>
{
private:

	ListNode<T>* front;
	ListNode<T>* back;

public:

	DoublyLinkedList();
	~DoublyLinkedList();

	DoublyLinkedList(const DoublyLinkedList&);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList&);

	void insertFront(const T& d);
	void insertBack(const T& d);
	T removeFront();
	T removeBack();
	T& getFront();
	T& getBack();
	void deleteElem(const T& d);
	T deletePos(size_t pos);
	void clear();

	class iterator
	{
		friend class DoublyLinkedList<T>;

	public:

		void operator++() { cur = cur->next; }
		bool operator==(const iterator& it) { return cur == it.cur; }
		bool operator!=(const iterator& it) { return !(*this == it); }
		T& operator*() { return cur->data; }
		T* operator->() { return &cur->data; }

	private:

		ListNode<T>* cur;

		iterator(ListNode<T>* cur) : cur(cur) {}
	};

	iterator begin() const { return iterator(front); }
	iterator end() const { return iterator(nullptr); }

private:

	void copy(const DoublyLinkedList<T>&);
};

#include "DoublyLinkedList.cpp"

#endif
