#include <iostream>
#include <random>
#include "MyArray.h"

namespace common_const
{
	constexpr int kLeftBorderOfTheRange { 0 };
	constexpr int kRightBorderOfTheRange { 100 };
	constexpr int kNumberDigitsForAdd { 20 };
	constexpr int kNUmberDigitsForInsert { 10 };

	constexpr int kNumberWordsForAdd { 15 };
	constexpr int kNumberWordsForInsert { 3 };
	constexpr int kMinLength { 1 };
	constexpr int kMaxLength { 10 };
}

template<typename T>
void out(
		CArray<T>& _arr
	)
{
	for (unsigned int i = 0; i < _arr.size(); ++i)
		std::cout << _arr[i] << " ";
	std::cout << "\n";
}

template<typename T>
void addTwentyRandomNumbers ( 
		CArray<T>& _arr
	)
{
	std::random_device rd;
	std::mt19937 gen( rd () );
	std::uniform_int_distribution<> disNumbers( common_const::kLeftBorderOfTheRange, common_const::kRightBorderOfTheRange );

 	for (int i = 0; i < common_const::kNumberDigitsForAdd; ++i)
		_arr.push_back ( disNumbers( gen ) );
}

template<typename T>
void sortArray (
		CArray<T>& _arr
	)
{
	std::sort ( _arr.data (), _arr.data () + _arr.size () );
}

template<typename T>
void deleteEverySecondElement ( 
		CArray<T>& _arr
	)
{
	for(unsigned int i = 1; i < _arr.size(); ++i)
		_arr.erase ( i );
}

template<typename T>
void insertRandomNumbersInRandomPosition (
		CArray<T>& _arr
	)
{
	using param_t = std::uniform_int_distribution<>::param_type;

	std::random_device rd;
	std::mt19937 gen ( rd () );
	std::uniform_int_distribution<>  disNumbers ( common_const::kLeftBorderOfTheRange, common_const::kRightBorderOfTheRange );
	std::uniform_int_distribution<>  disPosition;

	for (int i = 0; i < common_const::kNUmberDigitsForInsert; ++i)
		_arr.insert ( disPosition ( gen, param_t ( 0, _arr.size () - 1 ) ), disNumbers ( gen ) );
}

void testForDigits ()
{
	CArray<int> arrayInt;
	addTwentyRandomNumbers ( arrayInt );
	out ( arrayInt );

	sortArray ( arrayInt );
	out ( arrayInt );

	deleteEverySecondElement ( arrayInt );
	out ( arrayInt );

	insertRandomNumbersInRandomPosition ( arrayInt );
	out ( arrayInt );

	arrayInt.clear ();
	out ( arrayInt );
}

std::string getRandomWord ()
{
	std::random_device rd; 
	std::mt19937 gen ( rd () );
	std::uniform_int_distribution<>  disLenString ( common_const::kMinLength, common_const::kMaxLength );
	std::uniform_int_distribution<>  disSymbol ( 'a', 'z' );

	std::string str;
	for (int i = 0, lenString = disLenString ( gen ); i < lenString; ++i)
		str.push_back ( disSymbol ( gen ) );

	return str;
}

template<typename T>
void addRandomWords ( 
		CArray<T>& _arr 
	)
{
	for (int i = 0; i < common_const::kNumberWordsForAdd; ++i)
		_arr.push_back ( getRandomWord () );
}

template<typename T>
void sortWords ( 
		CArray<T>& _arr
	)
{
	sort ( _arr.data(), _arr.data() + _arr.size () );
}

template<typename T>
void sortWordsByLength ( 
		CArray<T>& _arr 
	)
{
	auto compareForSort = [] ( 
			const std::string& _s1, 
			const std::string& _s2 
		) 
	{
		return _s1.length () < _s2.length ();
	};

	sort ( _arr.data (), _arr.data () + _arr.size (), compareForSort );
}

template<typename T>
void deleteWordsWithIndicatedSymbols ( 
		CArray<T>& _arr 
	)
{
	for (unsigned int i = 0; i < _arr.size (); ++i)
		if (_arr[ i ].find_first_of ( "abcde" ) != std::string::npos)
			_arr.erase ( i-- );
}

template<typename T>
void insertRandomWordsInRandomPosition ( 
		CArray<T>& _arr 
	)
{
	using param_t = std::uniform_int_distribution<>::param_type;

	std::random_device rd;
	std::mt19937 gen ( rd () );
	std::uniform_int_distribution<>  disPosition;

	for (int i = 0; i < common_const::kNumberWordsForInsert; ++i)
		_arr.insert ( disPosition ( gen, param_t ( 0, _arr.size () - 1 ) ), getRandomWord () );
}

void testForStrings()
{
	CArray<std::string> arrayString;
	addRandomWords ( arrayString );
	out ( arrayString );

	sortWords ( arrayString );
	out ( arrayString );

	sortWordsByLength ( arrayString );
	out ( arrayString );

	deleteWordsWithIndicatedSymbols ( arrayString );
	out ( arrayString );

	insertRandomWordsInRandomPosition ( arrayString );
	out ( arrayString );
}

int main()
{	
	testForDigits ();
	testForStrings ();
}

