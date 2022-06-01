
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//


#include <unistd.h>   // POSIX SysCall (Unix,Linux,masOS)
#include <stdlib.h>   // standard library of C
#include <stdio.h>
#include <iostream>
#include <memory>

using namespace std;


class Girl;

class Boy
{
public:
	Boy()
    {
        cout << "Boy Constructor() Called" << endl;
    }

	Boy(int index)
    {
        cout << "Boy_#" << index  << ":" << endl;
        cout << "Constructor() Called" << endl;
        b_index = index;
    }

	~Boy()
    {
        cout << "Boy_#" << b_index  << ":" << endl;
        cout << "Destructor() Called" << endl;
    }

	void setGirlFriend(shared_ptr<Girl> _girlFriend)
    {
		this->girlFriend = _girlFriend;
	}

	void setWeakGirlFriend(shared_ptr<Girl> _girlFriend)
    {
		this->girlFriendw = _girlFriend;
	}

	int getIndex()
    {
        return b_index;
    }

private:
	int b_index;
    shared_ptr<Girl> girlFriend;
    weak_ptr<Girl> girlFriendw;
};

class Girl
{
public:
	Girl()
    {
        cout << "Girl Constructor() Called" << endl;
    }

	Girl(int index)
    {
        cout << "Girl_#" << index  << ":" << endl;
        cout << "Constructor() Called" << endl;
        g_index = index;
    }

	~Girl()
    {
        cout << "Girl_#" << g_index  << ":" << endl;
        cout << "Destructor() Called" << endl;
    }

	void setBoyFriend(shared_ptr<Boy> _boyFriend)
    {
		this->boyFriend = _boyFriend;
	}

	void setWeakBoyFriend(shared_ptr<Boy> _boyFriend)
    {
		this->boyFriendw = _boyFriend;
	}

	int getIndex()
    {
        return g_index;
    }

private:
	int g_index;
    shared_ptr<Boy> boyFriend;
    weak_ptr<Boy> boyFriendw;
};

void SmartPointerTest()
{
    Boy *ptest_1 = new Boy(1);

    Boy *ptest_2 = new Boy(2);
    delete ptest_2;

    unique_ptr<Boy> sptest_3(new Boy(3));
    cout << "sptest_3: " << sptest_3.get() << endl;

    // 编译错误，禁止左值赋值
    //unique_ptr<Boy> sptest_4 = sptest_3;
    unique_ptr<Boy> sptest_4;
    cout << "sptest_4: " << sptest_4.get() << endl;

    sptest_4 = move(sptest_3);
    cout << "sptest_3: " << sptest_3.get() << endl;
    cout << "sptest_4: " << sptest_4.get() << endl;

    shared_ptr<Boy> sptest_5(new Boy(5));
    cout << "sptest_5: " << sptest_5.use_count() << endl;
    shared_ptr<Boy> sptest_6 = sptest_5;
    cout << "sptest_5: " << sptest_5.use_count() << endl;
}

void SharedPointerTest()
{
    shared_ptr<Boy> sptest_boy(new Boy(1));
    shared_ptr<Girl> sptest_girl(new Girl(2));

    sptest_boy->setGirlFriend(sptest_girl);
	sptest_girl->setBoyFriend(sptest_boy);

    cout << "sptest_boy: " << sptest_boy.use_count() << endl;
    cout << "sptest_girl: " << sptest_girl.use_count() << endl;
}

void WeakPointerTest()
{
    shared_ptr<Boy> sptest_boy(new Boy(3));
    shared_ptr<Girl> sptest_girl(new Girl(4));

    sptest_boy->setWeakGirlFriend(sptest_girl);
	sptest_girl->setWeakBoyFriend(sptest_boy);

    cout << "sptest_boy: " << sptest_boy.use_count() << endl;
    cout << "sptest_girl: " << sptest_girl.use_count() << endl;
}

int main(int argc, char **argv, char *env[])
{
    //SmartPointerTest();
    SharedPointerTest();
    WeakPointerTest();

    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
