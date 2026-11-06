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
	MyString(const char* assignment, size_t assignedCapacity) : _length(assignment ? strlen(assignment) : 0), _capacity(assignedCapacity), _arrOfChars(new char[_capacity])
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
	MyString(const MyString& obj, size_t assignedCapacity) : _length(obj._length), _capacity(assignedCapacity), _arrOfChars(new char[_capacity])
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

	void swap(MyString& other) noexcept {
		std::swap(_length, other._length);
		std::swap(_capacity, other._capacity);
		std::swap(_arrOfChars, other._arrOfChars);
	}

	static size_t constexpr  npos = static_cast<size_t>(-1);  // explicit conversion 

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
	MyString&operator+= (char c) {
		this->push_back(c);
		return *this;
	}
	MyString& operator+=(const char* str) {
		if (str == nullptr) 
		{
			return *this;
		}
		size_t strLen = strlen(str);
		size_t newLength = _length + strLen;
		size_t newCapacity = newLength + 1;


		growBufferIfNeeded(newCapacity);



		for (size_t i = 0; i < strLen; i++) {


			*(_arrOfChars + (i + _length)) = *(str+ i);


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

	int compare(const MyString& obj) const {

		size_t smallerLength = (_length < obj._length) ? _length : obj._length;

		for (size_t i = 0; i < smallerLength; i++)
		{

			unsigned char a = static_cast<unsigned char>(*(_arrOfChars + i));
			unsigned char b = static_cast<unsigned char>(*(obj._arrOfChars+ i));

			if (a != b) 
			{
				return static_cast<int>(a) - static_cast<int>(b);
			}

		}

		if (_length < obj._length) 
		{
			return -1;
		}
		if (_length > obj._length) 
		{
			return 1;
		}

		return 0;
	}
	int compare(const char * str) const {

	
		if (str == nullptr)
		{
			return _length == 0 ? 0 : 1;
		}

		size_t paramLen = strlen(str);

		size_t smallerLength = (_length < paramLen) ? _length : paramLen;

		for (size_t i = 0; i < smallerLength; i++)
		{

			unsigned char a = static_cast<unsigned char>(*(_arrOfChars + i));
			unsigned char b = static_cast<unsigned char>(*(str + i));
			
			if (a != b)
			{
				return static_cast<int>(a) - static_cast<int>(b);
			}

		}

		if (_length < paramLen)
		{
			return -1;
		}
		if (_length > paramLen)
		{
			return 1;
		}

		return 0;
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
	void reserve(size_t userCapacity) {

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

	char& at(size_t index) {
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

	const char& at(size_t index) const {
		if (index >= _length)
			throw std::out_of_range("Index is out of bounds");

		return *(_arrOfChars + index);   //read only (return a copy)
	}

	char& operator[](size_t index) {
		
		return *(_arrOfChars + index); //return straight from the string
	}

	const char &operator[](size_t index) const {
	
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

	MyString& assign(const MyString& obj) {
		return *this = obj;
		
	}
	MyString& assign(MyString&& obj) {
		return *this = std::move(obj);
	
	}
	MyString& assign(const char* str) {
		return *this = str;
		
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

	MyString substr(size_t pos) const {
		
		if(pos > _length) 
		{ 
			throw std::out_of_range("Index is out of bounds"); 
		} 
		 
		size_t newCapacity = (_length - pos) + 1;
		MyString result(_arrOfChars + pos, newCapacity);

		return result;
	}
	MyString substr(size_t pos, size_t length) const  {

		if (pos > _length) 
		{
			throw std::out_of_range("Index is out of bounds");
		}

		if (pos + length > _length) 
		{ 
			return substr(pos); 
			
		}

		char* copyArr = _arrOfChars;
		MyString result("", length + 1);
		

		for (size_t i = pos; i < pos + length; i++) {
			result.push_back(copyArr[i]);
		}
		
		return result;

	}

	MyString& insert(size_t pos, const MyString& obj) {

		if (pos > _length) 
		{ 
			throw std::out_of_range("Index is out of bounds"); 
		}
		if (pos == _length) 
		{
			return *this += obj;
			
		}
		
		size_t newLength = _length + obj._length; 
		size_t newCapacity = newLength + 1; 
		

		MyString result(_arrOfChars,newCapacity);
		result._length = newLength;


		const char* remaining = _arrOfChars + pos;
		
		size_t remainingLength = strlen(remaining);

		for (size_t i = 0; i < obj._length; i++) {
			result[i + pos] = obj[i];
		}

		
		for (size_t i = 0; i < remainingLength; i++) 
		{
			result[ obj._length + pos + i  ] = remaining[i];
		}

		result[result._length] = '\0';
		
		swap(result);
		return *(this);
	}
	MyString& insert(size_t pos, const char* str) {

		if (str == nullptr)
		{
			throw std::invalid_argument("Cannot operate on a null pointer of type const char");
		}
		if (pos > _length)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (pos == _length)
		{
			this->append(str);
			return *this;
		}
		size_t parameterLength = strlen(str);
		size_t newLength = _length + parameterLength;
		size_t newCapacity = newLength + 1;


		MyString result(_arrOfChars, newCapacity);
		result._length = newLength;


		const char* remaining = _arrOfChars + pos;

		size_t remainingLength = strlen(remaining);

		for (size_t i = 0; i < parameterLength; i++) {
			result[i + pos] = str[i];
		}


		for (size_t i = 0; i < remainingLength; i++)
		{
			result[parameterLength + pos + i] = remaining[i]; // problem is here i think
		}

		result[result._length] = '\0';

	
		swap(result);
		return *(this);
	}

	MyString& insert(size_t pos, size_t copiesOfCharactar, char charactar) {

		if (pos > _length)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (pos == _length)
		{
			for(size_t i = 0; i<copiesOfCharactar; i++) 
			{ 
				this->push_back(charactar); 
			}
			

			 return *this;
		}

		size_t newLength = _length + copiesOfCharactar;
		size_t newCapacity = newLength + 1;


		MyString result(_arrOfChars, newCapacity);
		result._length = newLength;


		const char* remaining = _arrOfChars + pos;

		size_t remainingLength = strlen(remaining);

		for (size_t i = 0; i < copiesOfCharactar; i++) {
			result[i + pos] = charactar;
		}


		for (size_t i = 0; i < remainingLength; i++)
		{
			result[copiesOfCharactar + pos + i] = remaining[i];
		}

		result[result._length] = '\0';
		remaining = nullptr;

		swap(result);
		return *(this);
	}
	MyString& insert(size_t pos, const char* str, size_t endLimit) {
		if (str == nullptr)
		{
			throw std::invalid_argument("Cannot operate on a null pointer of type const char");
		}
		if (pos > _length)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (endLimit > strlen(str))
		{
			endLimit = strlen(str);
		}
		if (pos == _length)
		{
			
			
				for (size_t i = 0; i < endLimit; i++)
				{
					this->push_back(str[i]);
				}
		
			
			return *this;
		}
		

		size_t newLength = _length + endLimit;
		size_t newCapacity = newLength + 1;


		MyString result(_arrOfChars, newCapacity);
		result._length = newLength;

		
		const char* remaining = _arrOfChars + pos;

		size_t remainingLength = strlen(remaining);

		for (size_t i = 0; i < endLimit; i++) {
			result[i + pos] = str[i];
		}


		for (size_t i = 0; i < remainingLength; i++)
		{
			result[endLimit + pos + i] = remaining[i]; // problem is here i think
		}

		result[result._length] = '\0';
		

		swap(result);
		return *(this);
	};

	MyString& insert(size_t pos, const MyString& obj, size_t subpos, size_t sublen)
	{
		return this->insert(pos,obj.substr(subpos, sublen));
	}

	MyString& erase(size_t pos, size_t len) {

		if (pos > _length)
		{
			throw std::out_of_range("Index is out of bounds");
		}
		if (len == 0) 
		{
			return *this;
		}
		if (pos == _length)
		{
			return *this;
		}

		if (pos + len > _length)
		{
			len = _length - pos ;
		}
		 
		
	    size_t newLength = _length - len;
		

		char* copy = _arrOfChars;

	
		const char* remaining = _arrOfChars + pos + len;

		size_t remainingLength = strlen(remaining);

		for (size_t i = 0; i < remainingLength; i++) 
		{
			copy[i + pos] = remaining[i];
		}

		copy[remainingLength + pos] = '\0';
		
		
		_length = newLength;
		_arrOfChars = copy;


	
		return *this;

	} 
	MyString& erase(size_t pos = 0) {

		if (pos == 0) 
		{
			this->clear();
			return *this;
		}
	
		return erase(pos, _length - pos);
	}
	
	size_t find(const MyString& obj, size_t pos = 0) const {


		if (obj.empty()) 
		{
			return pos;
		}
		if (pos > _length) 
		{
			return npos;
		}
		

		for (size_t i = pos; i + obj._length <= _length; i++) 
		{                                                          //"ABCXYZ" vs "XYZ" and pos = 3
			bool isMatched = true;

			for (size_t j = 0; j < obj._length; j++) 
			{

				if (_arrOfChars[i + j] != obj._arrOfChars[j]) 
				{
					isMatched = false;
					break;
				}
				
			}

			if (isMatched)
			{
				return i;
		    }

		}

		return npos;
	}
	size_t find(const char *str, size_t pos = 0) const {

		if (str == nullptr || strlen(str) == 0)
		{
			return pos;
		}
		if (pos > _length)
		{
			return npos;
		}

		size_t strLen = strlen(str);

		for (size_t i = pos; i + strLen <= _length; i++)
		{                                                          //"ABCXYZ" vs "XYZ" and pos = 3
			bool isMatched = true;

			for (size_t j = 0; j < strLen; j++)
			{

				if (_arrOfChars[i + j] != str[j])
				{
					isMatched = false;
					break;
				}

			}

			if (isMatched)
			{
				return i;
			}

		}

		return npos;
	}
	size_t find(const char* str, size_t pos, size_t strLenParameter) const {

		if (str == nullptr || strLenParameter == 0)
		{
			return pos;
		}
		if (pos > _length)
		{
			return npos;
		}
		if (strLenParameter > strlen(str)) 
		{
			strLenParameter = strlen(str);
		}

		

		for (size_t i = pos; i + strLenParameter <= _length; i++)
		{                                                          //"ABCXYZ" vs "XYZ" and pos = 3
			bool isMatched = true;

			for (size_t j = 0; j < strLenParameter; j++)
			{

				if (_arrOfChars[i + j] != str[j])
				{
					isMatched = false;
					break;
				}

			}

			if (isMatched)
			{
				return i;
			}

		}

		return npos;
	}
	size_t find(char c, size_t pos = 0) const {

		if (_length == 0 || pos > _length)
		{
			return npos;
		}

		for (size_t i = pos; i < _length; i++)
		{
			if (_arrOfChars[i] == c)
			{
				return i;
			}
		}

		return npos;

	}

	size_t rfind(char c, size_t pos = npos) const {
		
	

		if (_length == 0)
		{
			return npos;
		}
		
		size_t start = (pos >= _length) ? _length - 1 : pos;

		for ( size_t i = start + 1; i-- > 0; )
		{
			
			if (_arrOfChars[i] == c)
			{
				return i;
			}
			
		}

		return npos;

	} 
	size_t rfind(const MyString& obj, size_t pos = npos) const {
		
		if (obj._length > _length)
		{
			return npos;
		}

		size_t start = _length - obj._length; 

		if (pos < start)
		{
			start = pos;
		}

		for (size_t i = start + 1; i-- > 0;) 
		{
			bool isMatch = true;


			for (size_t j = 0; j < obj._length; j++) { 

				if (_arrOfChars[i + j] != obj[j]) {
					isMatch = false;
					break;
				}


			}

			if (isMatch) {
				return i;
			}

		}

		return npos;

	}
	size_t rfind(const char* string, size_t pos, size_t charToUseForString) const {

		if (string == nullptr)
		{
			return (pos < _length) ? pos : _length;
		}
		size_t paramLen = strlen(string);
		size_t length = (charToUseForString >= paramLen) ? paramLen : charToUseForString;

		if (length > _length)
		{
			return npos;
		}

	
		size_t start = _length - length; 

		if (pos < start)
		{
			start = pos;
		}

		for (size_t i = start + 1; i-- > 0;) 
		{
			bool isMatch = true;


			for (size_t j = 0; j < length; j++) { 

				if (_arrOfChars[i + j] != string[j]) {
					isMatch = false;
					break;
				}


			}

			if (isMatch) {
				return i;
			}

		}

		return npos;
	}
	size_t rfind(const char* string, size_t pos = npos) const {



		if (string == nullptr)
		{
			return (pos < _length) ? pos : _length;
		}
		size_t paramLen = strlen(string);

		if (paramLen > _length)
		{
			return npos;
		}

		size_t start = _length - paramLen; // start searching at the rightmost possible index then go left 

		if (pos < start)
		{
			start = pos;
		}

		for (size_t i = start + 1; i-- > 0;) // for original (sliding from right to left)
		{
			bool isMatch = true;


			for (size_t j = 0; j < paramLen; j++) { // for param

				if (_arrOfChars[i + j] != string[j]) {
					isMatch = false;
					break;
				}


			}

			if (isMatch) {
				return i;
			}

		}

		return npos;

	}


	size_t  size() const noexcept {
		return _length;
	}

	size_t  length() const noexcept {
		return _length;
	}

	size_t  capacity() const noexcept {
		return _capacity;
	}

	bool empty() const noexcept {
		return _length == 0;
	}
	size_t find_first_of(const char* str, size_t pos = 0) const {



	

		if (_length == 0)
		{
			return npos;
		}

		if (str == nullptr)
		{
			return npos;
		}
		size_t strLen = strlen(str);

		if (pos > _length)
		{
			return npos;
		}

		

		for (size_t i = pos; i < _length; i++)
		{                                                          //"ABCXYZ" vs "ZYX" 
			for (size_t j = 0; j < strLen; j++)
			{

				if (_arrOfChars[i] == str[j])
				{
					return i;
				}
			}
		}

		return npos;
	}
	size_t find_first_of(const MyString& str, size_t pos = 0) const {

		

		if (_length == 0)
		{
			return npos;
		}

		if (str.empty())
		{
			return npos;
		}

		if (pos > _length)
		{
			return npos;
		}



		for (size_t i = pos; i < _length; i++)
		{                                                          //"ABCXYZ" vs "ZYX" 
			for (size_t j = 0; j < str._length; j++)
			{

				if (_arrOfChars[i] == str[j])
				{
					return i;
				}
			}
		}

		return npos;
	}
	size_t find_first_of(const char* str, size_t pos, size_t n) const {

		

		if (_length == 0)
		{
			return npos;
		}

		if (str == nullptr)
		{
			return npos;
		}

		if (pos > _length)
		{
			return npos;
		}

		size_t limit = strlen(str); 

		limit = (n > limit) ? limit : n;



		for (size_t i = pos; i < _length; i++)
		{                                                          // hello World vs xyzaeiou (1,0)
			for (size_t j = 0; j < limit; j++)
			{

				if (_arrOfChars[i] == str[j])
				{
					return i;
				}
			}
		}

		return npos;
	}
	size_t find_first_of(char c, size_t pos = 0) const {

		return find(c, pos);
	}

	size_t find_last_of(const char* str, size_t pos = npos) const {


		if (str == nullptr || _length == 0)
			return npos;

		size_t paramLen = strlen(str);

		size_t start = (pos > _length) ? _length : pos;

		for (size_t i = start + 1; i-- > 0;) // for original (sliding from right to left) hello world to "aeiou" 7
		{
			for (size_t j = 0; j < paramLen; j++) { // for param

				if (_arrOfChars[i] == str[j]) {
				
					return i;
				}


			}


		}

		return npos;

	}
	size_t find_last_of(const MyString& str, size_t pos = npos) const {


		if (str.empty())
			return npos;
	

		size_t start = (pos > _length) ? _length : pos;

		for (size_t i = start + 1; i-- > 0;) // for original (sliding from right to left) hello world to "aeiou" 5
		{
			for (size_t j = 0; j < str._length; j++) { // for param

				if (_arrOfChars[i] == str[j]) {

					return i;
				}


			}


		}

		return npos;

	}
	size_t find_last_of(const char* str, size_t pos, size_t n) const {


		if (str == nullptr || n == 0 || _length == 0)
			return npos;

		size_t start = (pos > _length) ? _length : pos;

		


		for (size_t i = start + 1; i-- > 0;) // for original (sliding from right to left) hello world to "aeiou" 5
		{
			for (size_t j = 0; j < n; j++) { // for param

				if (_arrOfChars[i] == str[j]) {

					return i;
				}


			}


		}

		return npos;
	}
	size_t find_last_of(char c, size_t pos = npos) const {

		return rfind(c, pos);
	}

	friend std::ostream& operator<<(std::ostream& o, const MyString& obj);
	friend std::istream& operator>>(std::istream& i, MyString& obj);

};

inline std::istream& operator>>(std::istream& i, MyString &obj) {

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
inline std::ostream& operator<<(std::ostream& o, const MyString& obj) {
	for (size_t i = 0; i < obj._length; i++) {
		o << *(obj._arrOfChars + i);
	}
	return o;
}