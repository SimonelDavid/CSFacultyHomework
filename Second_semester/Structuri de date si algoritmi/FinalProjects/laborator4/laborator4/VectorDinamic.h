#pragma once
#include <iostream>
#define INITIAL_CAPACITY 5

template<typename ElemType>
class IteratorVector;

template<typename ElemType>
class myVector
{

private:
	ElemType* elems; // elemente
	int length; // numr  elemente
	int capacity; // capacitate

	void ensureCapacity();

public:

	/*
	RULE OF FIVE :
		- Constructor
		- Destructor
		- Copy constructor
		-> Move constructor
		-> Move assignment
	*/


	// Constructor default. Alocam loc pentru 5 elemente
	myVector();

	// Constructor de copiere
	myVector(const myVector& other);

	// Destructor ce elibereaza memoria
	~myVector();

	/// <summary>
	/// Operator assignment 
	/// Elibereaza ce era in obiectul curent
	/// Aloca spatiu pt. elemente
	/// Copiaza elementelle din other in this
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	myVector& operator=(const myVector& other);


	/// <summary>
	/// Move constructor
	/// Apelat daca construim un nou vector dintr-un r-value (ex temporary, expresie de la return)
	/// Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
	/// </summary>
	/// <param name="other"></param>
	myVector(myVector&& other); // rule of 5


	/// <summary>
	/// Move assignment
	/// Similar cu move constructor, folosit doar la assignment
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	myVector& operator=(myVector&& other); // rule of 5

	void add(const ElemType& el);

	void remove(int poz);



	ElemType& get(int position) const;

	void set(int position, const ElemType& el);

	int size() const noexcept;

	friend class IteratorVector<ElemType>;

	// functii care creeaza iteratori
	IteratorVector<ElemType> begin();
	IteratorVector<ElemType> end();


	void resize();

};

// Constructor default
template <typename ElemType>
myVector<ElemType>::myVector() : elems{ new ElemType[INITIAL_CAPACITY] }, capacity{ INITIAL_CAPACITY }, length{ 0 } {}


// Constructor de copiere
template <typename ElemType>
myVector<ElemType>::myVector(const myVector<ElemType>& other)
{
	// aloc spatiu pt. toate elementele
	elems = new ElemType[other.capacity];
	// copiez toate elementele
	for (int i = 0; i < other.length; i++)
	{
		elems[i] = other.elems[i];
	}
	length = other.length;
	capacity = other.capacity;

}

/// <summary>
/// Operator assignment
/// Elibereaza memoria ocupata anterior si aloca mem. noua pentru a copia toate elementele din other
/// </summary>
/// <typeparam name="ElemType"></typeparam>
/// <param name="other"></param>
/// <returns></returns>
template <typename ElemType>
myVector<ElemType>& myVector<ElemType>::operator=(const myVector<ElemType>& other)
{
	if (this == &other)
	{
		return *this;  // In cazul a = a
	}
	delete[] elems;
	elems = new ElemType[other.capacity];

	// copiez elementele 
	for (int i = 0; i < other.length; i++)
	{
		elems[i] = other.elems[i];
	}
	length = other.length;
	capacity = other.capacity;
	return *this;
}


// Destructor / elibereaza memoria
template <typename ElemType>
myVector<ElemType>::~myVector()
{
	delete[] elems;
}


// Move constructor
// Apelat daca construim un nou vector dintr - un r - value(ex temporary)
// Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
template <typename ElemType>
myVector<ElemType>::myVector(myVector&& other)
{
	elems = other.elems;
	length = other.length;
	capacity = other.capacity;

	// Eliberez pointer-ul din obiectul de copiat ( il fac nullptr ) 
	// pentru ca destructor-ul sa nu incerce sa elibereze de 2 ori memoria
	other.elems = nullptr;
	other.length = 0;
	other.capacity = 0;

	return *this;

}

// Move assignment
// Similar cu move constructor
// Folosit la assignment
// Elibereaza ce continea obiectul curent(this)
// "fura" interiorul lui other
// pregateste other pentru distrugere
template<typename ElemType>
myVector<ElemType>& myVector<ElemType>::operator=(myVector<ElemType>&& other)
{
	if (this == &other)
	{
		return *this;
	}
	delete[] elems;

	elems = other.elems;
	length = other.length;
	capacity = other.capacity;

	// Eliberez pointer-ul din obiectul de copiat ( il fac nullptr ) 
	// pentru ca destructor-ul sa nu incerce sa elibereze de 2 ori memoria
	other.elems = nullptr;
	other.length = 0;
	other.capacity = 0;

	return *this;

}


template<typename ElemType>
void myVector<ElemType>::ensureCapacity()
{
	if (length < capacity)
		return; // mai este loc

	capacity *= 2;

	ElemType* aux = new ElemType[capacity];
	for (int i = 0; i < length; i++)
	{
		aux[i] = elems[i];
	}

	delete[] elems;
	elems = aux;

}

template<typename ElemType>
void myVector<ElemType>::resize()
{
	capacity *= 2;

	ElemType* aux = new ElemType[capacity];
	for (int i = 0; i < length; i++)
	{
		aux[i] = elems[i];
	}

	delete[] elems;
	elems = aux;
}

template<typename ElemType>
void myVector<ElemType>::add(const ElemType& elem)
{
	ensureCapacity();
	elems[length++] = elem;
}

template<typename ElemType>
void myVector<ElemType>::remove(int poz)
{
	int i;
	for (i = poz; i < length - 1; i++)
	{
		elems[i] = elems[i + 1];
	}
	length--;
}

template<typename ElemType>
ElemType& myVector<ElemType>::get(int position) const {
	return elems[position];
}

template<typename ElemType>
void myVector<ElemType>::set(int position, const ElemType& el) {
	elems[position] = el;
}

template<typename ElemType>
int myVector<ElemType>::size() const noexcept
{
	return length;
}


template<typename ElemType>
IteratorVector<ElemType> myVector<ElemType>::begin()
{
	return IteratorVector<ElemType>(*this);
}

template<typename ElemType>
IteratorVector<ElemType> myVector<ElemType>::end()
{
	return IteratorVector<ElemType>(*this, length - 1);
}


// Clasa pentru iterator

template<typename ElemType>
class IteratorVector {

private:
	const myVector<ElemType>& v;
	int position = 0;

public:

	// 2 variante de constructori ( cu referinta la vector si cu pozitia de pointat sau doar cu referinta la vector )
	IteratorVector(const myVector<ElemType>& v) noexcept;
	IteratorVector(const myVector<ElemType>& v, int position) noexcept;

	// Verifica validitatea iteratorului ( nu incearca sa acceseze o pozitie care nu exista in vector )
	bool valid() const;

	// Returneaza elementul la care pointeaza iteratorul
	ElemType& element() const;

	// Trece a urmatorul element daca poate ( intervine valid() )
	void next();

	ElemType& operator*();

	IteratorVector& operator++();

	void operator=(int poz);

	IteratorVector& operator=(const IteratorVector& other) noexcept;


	// operatori logici
	bool operator<(int poz) noexcept;

	bool operator>(int poz) noexcept;

	bool operator<=(int poz) noexcept;

	bool operator>=(int poz) noexcept;

	bool operator==(const IteratorVector& other) noexcept;

	bool operator!=(const IteratorVector& other) noexcept;



};


template<typename ElemType>
IteratorVector<ElemType>::IteratorVector(const myVector<ElemType>& v) noexcept : v{ v } {}

template<typename ElemType>
IteratorVector<ElemType>::IteratorVector(const myVector<ElemType>& v, int position) noexcept : v{ v }, position{ position } {}

template<typename ElemType>
bool IteratorVector<ElemType>::valid() const
{
	return position < v.length;
}

template<typename ElemType>
ElemType& IteratorVector< ElemType>::element() const {
	return v.elems[position];
}

template<typename ElemType>
void IteratorVector<ElemType>::next()
{
	position++;
}

template<typename ElemType>
ElemType& IteratorVector<ElemType>::operator*()
{
	return element();
}

template<typename ElemType>
IteratorVector<ElemType>& IteratorVector<ElemType>::operator++()
{
	next();
	return *this;
}


template<typename ElemType>
void IteratorVector<ElemType>::operator=(int poz)
{
	position = poz;
}

template<typename ElemType>
IteratorVector<ElemType>& IteratorVector<ElemType>::operator=(const IteratorVector& other) noexcept
{
	position = other.position;
	return *this;
}


template<typename ElemType>
bool IteratorVector<ElemType>::operator<(int poz) noexcept
{
	return position < poz;
}

template<typename ElemType>
bool IteratorVector<ElemType>::operator>(int poz) noexcept
{
	return position > poz;
}

template<typename ElemType>
bool IteratorVector<ElemType>::operator<=(int poz) noexcept
{
	return position <= poz;
}

template<typename ElemType>
bool IteratorVector<ElemType>::operator>=(int poz) noexcept
{
	return position >= poz;
}

template<typename ElemType>
bool IteratorVector<ElemType>::operator==(const IteratorVector<ElemType>& other) noexcept
{
	return position == other.position;
}

template<typename ElemType>
bool IteratorVector<ElemType>::operator!=(const IteratorVector<ElemType>& other)noexcept {

	return !(*this == other);
}


