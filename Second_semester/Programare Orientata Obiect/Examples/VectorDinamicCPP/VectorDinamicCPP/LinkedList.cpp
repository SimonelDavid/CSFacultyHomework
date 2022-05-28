#include "VectorDinamicTemplate.h"

template <class TElem>
Lista<TElem>::Lista()
{
	first = NULL;
	last = NULL;
}

template <class TElem>
Lista<TElem>::~Lista()
{
	Node<TElem>* temp = first;
	while (temp != NULL)
	{
		temp = temp->next;
		delete(first);
		first = temp;
	}
}

template <class TElem>
void Lista<TElem>::add(TElem valueToInsert)
{
	Node<TElem>* newNode;
	newNode->val = valueToInsert;
	newNode->next = NULL;

	Node<TElem>* temp = first;

	if (temp != NULL)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = newNode;
	}
	else
	{
		first = newNode;
	}
}

template <class TElem>
bool Lista<TElem>::removeFromBack()
{
	if (first == NULL && last == NULL) { return false; }

	if (first == last)
	{
		cout << "First is equal to Last." << endl;
		delete(first);
		first = last = NULL;
		return true;
	}

	else
	{
		Node<TElem>* temp = first;
		int nodeCount = 0;

		while (temp != NULL)
		{
			nodeCount = nodeCount + 1;
			temp = temp->next;
		}

		Node<TElem>* temp2 = first;

		for (int i = 1; i < (nodeCount - 1); i++)
		{
			temp2 = temp2->next;
		}

		cout << temp2->val << endl;
		delete(temp2->next);

		last = temp2;
		last->next = NULL;

		return true;
	}
}

template <class TElem>
void Lista<TElem>::print()
{
	Node<TElem>* temp = first;

	if (temp == NULL)
	{
		cout << "";
	}

	if (temp->next == NULL)
	{
		cout << temp->val;
	}
	else
	{
		while (temp != NULL)
		{
			cout << temp->val;
			temp = temp->next;
			cout << ",";
		}
	}
}

template <class TElem>
bool Lista<TElem>::isEmpty()
{
	if (first == NULL && last == NULL) { return true; }
	else { return false; }
}

template <class TElem>
int Lista<TElem>::size()
{
	if (first == NULL && last == NULL) { return 0; }

	Node<TElem>* temp = first;
	int nodeCounter = 0;

	while (temp != NULL)
	{
		nodeCounter = nodeCounter + 1;
		temp = temp->next;
	}
	return nodeCounter;
}

template <class TElem>
void Lista<TElem>::clear()
{
	Node<TElem>* temp = first;
	while (temp != NULL)
	{
		temp = temp->next;
		first = temp;
		delete(temp);
	}
}

template <class TElem>
void Lista<TElem>::insertAtFront(TElem valueToInsert)
{
	Node<TElem>* newNode;

	newNode->val = valueToInsert;

	if (first == NULL)
	{
		first = newNode;
	}
	else
	{
		newNode->next = first;
		first = newNode;
	}

}

template <class TElem>
bool Lista<TElem>::removeFromFront()
{
	if (first == NULL && last == NULL) { return false; }

	else
	{
		Node<TElem>* temp;

		temp = first;
		first = first->next;

		delete(temp);

		return true;
	}
}

template <class TElem>
TElem& Lista<TElem>::firstNum()
{
	return first->val;
}

template <class TElem>
TElem& Lista<TElem>::get(int index)
{
	if (first == NULL) {
		cout << "linked list is empty !" << endl;
		return -9999;
	}
	if (index >= size() || index < 0) {
		cout << "index out of bound !" << endl;
		return -9999;
	}
	if (index == 0) {
		return first->data;
	}
	int count = 0;
	TElem res;
	Node<TElem>* temp = first;
	while (temp != NULL) {
		if (count++ == index) {
			res = temp->data;
			break;
		}
		temp = temp->next;
	}
	return res;
}