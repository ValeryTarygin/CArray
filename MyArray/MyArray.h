#pragma once
template <typename TData>
class CArray
{
	TData* first_;
	TData* last_;
	TData* end_;

public:
	CArray ();

	CArray (
		const CArray& _array
	);

	~CArray ();

	void push_back (
		const TData& _value
	);

	void insert (
		unsigned int _index,
		const TData& _value
	);

	void erase (
		unsigned int _index
	);

	void clear ();

	unsigned int size () const;

	unsigned int capacity () const;

	void resize (
		unsigned int _size
	);

	void reserve (
		unsigned int _capacity
	);

	TData* data ();

	TData& operator[](
		unsigned int _index
		);
};

template <typename TData>
CArray<TData>::CArray ()
	: first_ ( nullptr )
	, last_ ( nullptr )
	, end_ ( nullptr )
{
}

template <typename TData>
CArray<TData>::CArray (
		const CArray& _array
	)
{
	if (this == &_array)
		return;

	TData* tempFirst = new TData[ _array.capacity () ];
	std::copy ( _array.first_, _array.last_ - 1, tempFirst );

	first_ = tempFirst;
	last_ = first_ + _array.size ();
	end_ = first_ + _array.capacity ();
}

template <typename TData>
CArray<TData>::~CArray ()
{
	delete[ ] first_;
}

template <typename TData>
unsigned int CArray<TData>::size () const
{
	return last_ - first_;
}

template <typename TData>
unsigned int CArray<TData>::capacity () const
{
	return end_ - first_;
}

template <typename TData>
void CArray<TData>::reserve (
		unsigned int _capacity
	)
{
	if (!first_)
	{
		first_ = new TData[ _capacity ];
		last_ = first_;
		end_ = first_ + _capacity;
	}
	else
	{
		if (_capacity <= capacity ())
			return;

		TData* tempFirst = new TData[ _capacity ];
		std::copy ( first_, last_, tempFirst );

		auto size ( size () );

		delete[ ] first_;

		first_ = tempFirst;
		last_ = first_ + size;
		end_ = first_ + _capacity;
	}
}

template <typename TData>
void CArray<TData>::resize (
		unsigned int _size
	)
{
	if (_size == size ())
		return;
	else if (_size > capacity ())
		reserve ( _size );

	last_ = first_ + _size;
}

template <typename TData>
void CArray<TData>::clear ()
{
	last_ = first_;
}

template <typename TData>
void CArray<TData>::erase (
		unsigned int _index
	)
{
	if (_index >= size ())
		throw std::out_of_range ( "Out of range. Method erase" );

	auto elemForErase = first_ + _index;
	std::copy ( elemForErase + 1, last_, elemForErase );
	--last_;
}

template <typename TData>
void CArray<TData>::insert (
		unsigned int _index,
		const TData& _value
	)
{
	if (_index >= size ())
		throw std::out_of_range ( "Out of range. Method insert" );

	resize ( size () + 1 );

	auto insertElem = first_ + _index;
	std::copy_backward ( insertElem, ( last_ - 1 ), last_ );
	*insertElem = _value;
}

template <typename TData>
void CArray<TData>::push_back (
		const TData& _value
	)
{
	resize ( size () + 1 );
	*( last_ - 1 ) = _value;
}

template <typename TData>
TData* CArray<TData>::data ()
{
	return first_;
}

template <typename TData>
TData& CArray<TData>::operator[](
		unsigned int _index
	)
{
	return *( first_ + _index );
}