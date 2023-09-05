#include "String.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>



String::String()
{
	//inString = nullptr;
	cap = 15;

	cString = new char[cap];
	//cString = nullptr;
	csize = 0;

	Invariant();

}

String::String(const String& rhs)
{
	//inString = rhs.inString;
	cap = 15;
	while (rhs.size() > cap)
	{
		cap = cap * 2;
	}
	cString = new char[cap];
	csize = rhs.csize;
	//std::cout << cString << " \n" << rhs.csize << " my size: " << csize << " strlen " << strlen(rhs.cString) + 1 << " cap and my cap" << rhs.cap << cap << std::endl;
	for (int i = 0; i < rhs.size(); i++)
	{
		cString[i] = rhs.cString[i];
	}

	//std::cout << "string is now " << cString  << std::endl;
	Invariant();
}

String::String(const char* cstr)
{
	if (cstr == nullptr)
	{
		cap = 15;
		cString = new char[cap];
		cString[0] = '\0';
		csize = 0;
	}
	else
	{
		cap = 15;
		while (sizeof(cstr) > cap)
		{
			cap = cap * 2;
		}
		cString = new char[cap];
		csize = strlen(cstr);

		strcpy_s(cString, strlen(cstr)+1, cstr);

		//std::cout << "const char is now " << cString << std::endl;
	}
	Invariant();
}

void String::Print()
{
	//std::cout << "printing:: ";
	//std::cout << cString << "  :: " << &cString << std::endl;
}
void String::IncreaseCap(size_t size)
{
	if (size < cap) return;

	int newCap = cap * 2;
	char* newString = new char[newCap];

	for (int i = 0; i < cap; i++)
	{
		newString[i] = cString[i];
	}

	cap = newCap;
	//std::cout << cString;
	//del makes heap corrupt, no delete makes the old cString into memory leak -- it crashes at delete[]
	delete[] cString;

	cString = newString;
}

String& String:: operator=(const String& rhs)
{
	//std::cout << "operator= " << cString;
	if (this == &rhs)
	{
		return *this;
	}
	if (rhs.size() > cap)
	{
		delete[] cString;
		while (rhs.size() > cap)
		{
			cap = cap * 2;
		}
		cString = new char[cap];
	}
	for (int i = 0; i < rhs.size(); i++)
	{
		cString[i] = rhs.cString[i];
	}
	//std::cout << "--> " << cString << std::endl;

	return*this;
}
//
char& String::operator[](size_t i)
{
	return cString[i];
}
//
const char& String::operator[](size_t i) const
{
	return cString[i];
}


size_t String::size() const
{
	//need to find better way of checking the size
	/*int i = 0;

	if (cString != nullptr)
	{
		while (cString[i] != '\0')
		{
			if (cString == nullptr)
			{
				break;
			}
			i++;
		}
	}
	size_t size = csize;*/
	//std::cout << "size of " << cString << " is " << size << " " << cap << std::endl;

	return csize;
}
size_t String::capacity() const
{
	//std::cout << "cap of " << cString << " is " << cap << std::endl;
	return cap;
}
//
void String::push_back(char c)
{
	/*if (c == '\0')
	{
		csize = csize + 1;
	}*/

	int len = size();
	//std::cout << len << " || "<< cap;
	if (len + 1 > cap)
	{
		IncreaseCap(len);
	}
	cString[len] = c;

	csize = csize + 1;
	//cString[len+1] = '\0';

	//std::cout << " String is " << cString << "  cap: " << cap << "  size:  " << size() << "\n";
}

//
bool operator==(const String& lhs, const String& rhs)
{
	bool sameChar = true, sameSize = true;
	int i = 0;
	for (int i = 0; i < lhs.csize; i++)
	{
		if (lhs.cString[i] != rhs.cString[i])
		{
			sameChar = false;
		}
		i++;
	}
	if (lhs.size() != rhs.size() || lhs.capacity() != rhs.capacity())
	{
		sameSize = false;
	}
	if (sameChar && sameSize)
	{
		//std::cout << "true";
		return true;
	}
	else
	{
		//std::cout << "false";
		return false;
	}
}

bool operator!=(const String& lhs, const String& rhs)
{
	bool sameChar = true, sameSize = true;
	int i = 0;
	for (int i = 0; i < lhs.csize; i++)
	{
		if (lhs.cString[i] != rhs.cString[i])
		{
			sameChar = false;
		}
		i++;
	}
	if (lhs.size() != rhs.size() || lhs.capacity() != rhs.capacity())
	{
		sameSize = false;
	}
	if (sameChar && sameSize)
	{
		//std::cout << "true";
		return false;
	}
	else
	{
		//std::cout << "false";
		return true;
	}
}
//
const char* String::data() const
{
	//std::cout << "using data" << std::endl;
	return cString;
}

std::ostream& operator<< (std::ostream& out, const String& rhs)
{
	for (size_t i = 0; i < rhs.size(); ++i)
	{
		out << rhs.cString[i];
	}
	return out;
}

void String::Invariant()
{
	assert(size() <= cap);
	assert(cString != nullptr);
}

String::~String()
{
	Invariant();
	delete[]cString;
	cString = nullptr;
};
