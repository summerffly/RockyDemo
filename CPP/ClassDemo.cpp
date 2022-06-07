
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//


#include <unistd.h>   // POSIX SysCall (Unix,Linux,masOS)
#include <stdlib.h>   // standard library of C
#include <stdio.h>
#include <iostream>

using namespace std;


class A
{
public:
	A()
    {
        cout << "A Constructor() Called" << endl;
    }

	~A()
    {
        cout << "A Destructor() Called" << endl;
    }
};

class AA: public A
{
public:
	AA()
    {
        cout << "AA Constructor() Called" << endl;
    }

	~AA()
    {
        cout << "AA Destructor() Called" << endl;
    }
};

class AAA: public AA
{
public:
	AAA()
    {
        cout << "AAA Constructor() Called" << endl;
    }

	~AAA()
    {
        cout << "AAA Destructor() Called" << endl;
    }
};


class B
{
public:
	B()
    {
        cout << "B Constructor() Called" << endl;
    }

	virtual ~B()
    {
        cout << "B Destructor() Called" << endl;
    }
};

class BB: public B
{
public:
	BB()
    {
        cout << "BB Constructor() Called" << endl;
    }

	~BB()
    {
        cout << "BB Destructor() Called" << endl;
    }
};

class BBB: public BB
{
public:
	BBB()
    {
        cout << "BBB Constructor() Called" << endl;
    }

	~BBB()
    {
        cout << "BBB Destructor() Called" << endl;
    }
};


int main(int argc, char **argv, char *env[])
{
    {
        A *pa = new AAA;
        delete pa;

        cout << "------------" << endl;

        B *pb = new BBB;
        delete pb;

        cout << "------------" << endl;
    }

    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
