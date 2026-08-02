#pragma once
#include<cstring>
#include<utility>
#include<stdexcept>
#include<iostream>
#include <cstddef>

class MyString {

private:
	
	size_t _length = 0;
	size_t _capacity = 0;
	char* _arrOfChars = nullptr;

	
	 void swap(MyString& other) noexcept  { 
		std::swap(_length, other._length);
		std::swap(_capacity, other._capacity);
		std::swap(_arrOfChars, other._arrOfChars);
	}

	 static size_t constexpr GROW_FACTOR = 2;

	 void growBufferIfNeeded(size_t neededCapacity) {

		 if (_capacity < neededCapacity)
		 {


			 size_t newGrowSizeAmount = neededCapacity * GROW_FACTOR;
			 char* newBuff = new char[newGrowSizeAmount];

			

			 for (size_t i = 0; i < _length; i++)
			 {
				 *(newBuff + i) = *(_arrOfChars + i);
			 }

			 delete[] _arrOfChars;

			 _arrOfChars = newBuff;
			 _capacity = newGrowSizeAmount;

		 }
		

	 }

public : 

	MyString(const char* assignment = "") : _length(assignment ? strlen(assignment) : 0), _capacity(_length + 1), _arrOfChars(new char[_capacity])
	{ 
	
		
		for (size_t i = 0; i < _length; i++)
		{
			*(_arrOfChars + i) = *(assignment + i);
		}
		
		*(_arrOfChars + _length) = '\0';
	}; 
	MyString(const MyString &obj) : _length(obj._length), _capacity(obj._capacity), _arrOfChars(new char[_capacity]) 
	{
		
		for (size_t i = 0; i < _length; i++)
		{
			*(_arrOfChars + i) = *(obj._arrOfChars + i);
		}
		
		*(_arrOfChars + _length) = '\0';
	
	};
	MyString(MyString&& obj) noexcept : _length(obj._length), _capacity(obj._capacity),  _arrOfChars(obj._arrOfChars)
	{
		
		obj._length = 0;
		obj._capacity = 0;
		
		obj._arrOfChars = nullptr;
		
	}
	~MyString() noexcept
	{
		delete[] _arrOfChars;
	}

	MyString& operator=(const char* assignment) {
		MyString temp(assignment);     // calls your existing constructor
		swap(temp);                    // swap this object's data with temp's
		return *(this);                // return the object 
	}
	MyString& operator=(const MyString& obj) {
		if (this == &obj)
			return *(this);

		MyString temp(obj);
		swap(temp);
		return *(this);
	}
	MyString& operator=(MyString&& obj) noexcept {
		
		swap(obj);
		return *(this);

		/*manual implementation for reference :

		if (this == &obj)
			return *(this);

		delete[] _arrOfChars;
		_length = obj._length;
		_size = obj._size;
		_arrOfChars = obj._arrOfChars;
		obj._length = 0;
		obj._size = 0;
		obj._arrOfChars = nullptr;
		return *(this);
		*/
	}
	MyString &operator+=(const MyString &obj) {

		
		size_t newLength = _length + obj._length; 
		size_t newCapacity = newLength + 1;   
	

		growBufferIfNeeded(newCapacity);  
		
			

			for (size_t i = 0; i < obj._length; i++) {
				
				
			 *( _arrOfChars + (i + _length) ) = *(obj._arrOfChars + i);
					
				
			}

			*(_arrOfChars + newLength) = '\0'; 
		
	      
		_length = newLength;


		return *(this);

	}
	MyString operator+(const MyString& obj) const {
		MyString result(*this);
		result += obj;
		return result;

	}
	bool operator!=(const MyString& obj) const {
		return !(*this == obj);
	}
	bool operator==(const MyString& obj) const {

		if (this->_length != obj._length)
			return false;

		for (size_t i = 0; i < _length; i++)
		{                                                       //ABC, ABC
			if (*(_arrOfChars + i) != *(obj._arrOfChars + i))
				return false;
		}
		return true;
	}
	bool operator<(const MyString& obj) const {

		size_t smallerLength = (_length < obj._length) ? _length : obj._length;

		for (size_t i = 0; i < smallerLength; i++)
		{

			if (*(_arrOfChars + i) < *(obj._arrOfChars + i))
				return true;

			if (*(_arrOfChars + i) > *(obj._arrOfChars + i))
				return false;

		}

		return _length < obj._length;

	}
	bool operator>(const MyString& obj) const {
		return  obj < *this;
	}
	bool operator<=(const MyString& obj) const {
		return (*this < obj || *this == obj);
	}
	bool operator >=(const MyString& obj) const {
		return (*this > obj || *this == obj);
	}

	void shrink_to_fit() {

		if (_capacity == _length + 1)
			return;

		size_t shrinkedCapacity = _length + 1;

		char* newBuff = new char[shrinkedCapacity];

		for (size_t i = 0; i < _length; i++) 
		{
			*(newBuff + i) = *(_arrOfChars + i);
		}
		 
		*(newBuff + _length) = '\0';

		delete[] _arrOfChars;

		
		_arrOfChars = newBuff;
		_capacity = shrinkedCapacity;
	}
	void reserve(const size_t& userCapacity) {

		if (_capacity < userCapacity) // _arrOfChars == nullptr if and only if _capacity == 0
		{

			char* newBuff = new char[userCapacity];

			for (size_t i = 0; i < _length; i++)
			{
				*(newBuff + i) = *(_arrOfChars + i);
			}

			*(newBuff + _length) = '\0';

			delete[] _arrOfChars;

			_arrOfChars = newBuff;
			_capacity = userCapacity;
		}
		
	}
	void resize(size_t resizeBy, char charactar = '\0') {

		if (resizeBy == _length)
			return;

		if (resizeBy < _length)
		{
			*(_arrOfChars + resizeBy) = '\0';
		}
		else 
		{
			growBufferIfNeeded(resizeBy + 1);
			for (size_t i = _length; i < resizeBy; i++) 
			{
				*(_arrOfChars + i) = charactar;
			}
			*(_arrOfChars + resizeBy) = '\0';
		}

		_length = resizeBy;

    }

	char& at(const size_t& index) {
		if(index>=_length)
			throw std::out_of_range("Index is out of bounds");

		return *(_arrOfChars + index); //return straight from the string
	}

	char* begin() noexcept {
		return _arrOfChars; 
	}

	char* end() noexcept {
		return _arrOfChars + _length; 
	}

	const char* begin() const noexcept { 
		return _arrOfChars;
	}

	const char* end() const noexcept { 
		return _arrOfChars + _length; 
	}

	const char& at(const size_t& index) const {
		if (index >= _length)
			throw std::out_of_range("Index is out of bounds");

		return *(_arrOfChars + index);   //read only (return a copy)
	}

	char& operator[](const size_t &index) {
		
		return *(_arrOfChars + index); //return straight from the string
	}

	const char &operator[](const size_t &index) const {
	
		return *(_arrOfChars + index);   //read only (return a copy)
	}

	void push_back(char charactar) {
		
		growBufferIfNeeded(_length + 2);
		
		*(_arrOfChars + _length) = charactar;

		++_length;

		
		*(_arrOfChars + _length) = '\0';
	}
	void pop_back() {

		if (_length == 0) 
		{
			throw std::out_of_range("Out of bounds, MyString is empty"); 
		}
			

			--_length;
			*(_arrOfChars + _length ) = '\0';
		

	}


	char& front() {
		if (_length == 0)
			throw std::out_of_range("Out of bounds, MyString is empty");

		return *_arrOfChars;
	}	
	const char& front() const {
		if (_length == 0)
			throw std::out_of_range("Out of bounds, MyString is empty");

		return *_arrOfChars;
	}

	char& back() {
		if (_length == 0)
			throw std::out_of_range("Out of bounds, MyString is empty");

		return *( _arrOfChars + (_length - 1) );

	}
	const char& back() const  {
		if (_length == 0)
			throw std::out_of_range("Out of bounds, MyString is empty");

		return *( _arrOfChars + (_length - 1) );

	}


	 const char* c_str() const noexcept {
		 return _arrOfChars ? _arrOfChars : "";
	}
	 const char* data() const noexcept {
		 return _arrOfChars ? _arrOfChars : "";
	 }
	void clear() {
		_length = 0;

		if (_arrOfChars != nullptr) 
		{
			*_arrOfChars = '\0';
		}

	}



	size_t const& size() const noexcept {
		return _length;
	}

	size_t const& length() const noexcept {
		return _length;
	}

	size_t const& capacity() const noexcept {
		return _capacity;
	}

	bool empty() const noexcept {
		return _length == 0;
	}
	void append(const MyString& obj) {
		*this += obj;
	}
	void append(char c) {
		push_back(c);
	}
	void append(const char* string) {

		size_t paraemeterLength = strlen(string);
		size_t newLength = _length + paraemeterLength;

		growBufferIfNeeded(newLength + 1);

		for (size_t i = 0; i < paraemeterLength; i++) {
			*(_arrOfChars + (i + _length)) = *(string + i);
		}

		_length = newLength;
		*(_arrOfChars + _length) = '\0';

	}

	friend std::ostream& operator<<(std::ostream& o, const MyString& obj);
	friend std::istream& operator>>(std::istream& i, MyString& obj);

};
std::istream& operator>>(std::istream& i, MyString &obj) {

	obj.clear();
	char charactar = '\0';
	bool isChar = false;

	while (i.get(charactar)) {
		bool isSpace = (charactar == ' ' || charactar == '\t' || charactar == '\n');

		if (!isChar) 
		{
			if (isSpace)
				continue;

			isChar = true;
		}
		else if (isSpace) 
		{
			i.unget();
			break;
		}
		  
		obj.push_back(charactar);
	}


	return i;
}
std::ostream& operator<<(std::ostream& o, const MyString& obj) {
	for (size_t i = 0; i < obj._length; i++) {
		o << *(obj._arrOfChars + i);
	}
	return o;
}