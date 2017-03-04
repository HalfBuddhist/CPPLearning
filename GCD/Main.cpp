//============================================================================
// Name        : Euclid.cpp
// Author      : LQW
// Version     :
// Copyright   : All copyleft reserved!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "GCD.h"

using namespace std;

int main()
{
    //test for modular inverse - 费马小定理
    cout<<"test for modular inverse - 费马小定理:"<<endl;
    cout << modular_inverse_rec(3, long(1E9+7))<<endl;
    cout << modular_inverse_iter(3, long(1E9+7))<<endl;
    cout << modular_inverse_rec(long(1E9+7),3)<<endl;
    cout << modular_inverse_iter(long(1E9+7), 3)<<endl;

	//test for euclid and stein
	cout<<"test for euclid and stein:"<<endl;
	unsigned int a=12, b=8;
//	cin>>a>>b;
	cout<<"eculid for ("<<a<<", "<<b<<") is " << euclid(a,b)<<endl;
    cout<<"stein for ("<<a<<", "<<b<<") is " << stein(a,b)<<endl;
//	printf("eculid for (%ld, %ld) is %ld\n", a, b, euclid(a,b));
//	printf("stein for (%ld, %ld) is %ld\n", a, b, stein(a,b));
    
	//test for extended_euclid_recursive
	cout<<"test for extended_euclid_recursive:"<<endl;
    long i, x, y;
    const long P = 13;
    for (i = 1; i < P; ++i)
    {
        int comm = extended_euclid_recursive(i, P, x, y);
        while (x < 0) x += P;
        while (y < 0)
        {
            y += i;
        }
        printf("(%ld, %ld)-%d-%ld-%ld\n", i, P, comm, x, y);

        comm = extended_euclid_recursive(P, i, x, y);
        while (x < 0) x += i;
        while (y < 0)
        {
            y += P;
        }
        printf("(%ld, %ld)-%d-%ld-%ld\n", P, i, comm, x, y);
        printf("************************\n");
    }
    
    int comm  = extended_euclid_recursive(8, 12, x, y);
    printf("%d %d, %d %ld %ld\n", 8, 12, comm, x, y);
    
    //test for extended_euclid
	cout<<"test for extended_euclid:"<<endl;
	for (i = 1; i < P; ++i) {
       int comm = extended_euclid(i, P, x, y);
       while (x < 0) x += P;
       while (y < 0)
       {
           y += i;
       }
       printf("(%ld, %ld)-%d-%ld-%ld\n", i, P, comm, x, y);

		comm = extended_euclid(P, i, x, y);
		while (x < 0)
			x += i;
		while (y < 0) {
			y += P;
		}
		printf("(%ld, %ld)-%d-%ld-%ld\n", P, i, comm, x, y);
		printf("************************\n");
	}

    comm  = extended_euclid_recursive(2, 11, x, y);
    printf("%ld %ld, %d %ld %ld\n", 2, 11, comm, x, y);

    comm  = extended_euclid(3, long(1E9+7), x, y);
    printf("%ld %ld, %d %ld %ld\n", 3, long(1E9+7), comm, x, y);

    //test for extended_euclid_weired
	cout<<"test for ExtendedEuclid:"<<endl;
    long x1, y1, z = 0;

    //    printf("输入两个数：\n");
//    scanf("%d%d", &x1, &y1);
    for (long i=1; i<P; i++)
    {
        if (extended_euclid_weired(i, P, &z))
            printf("%ld和%ld互素, 模逆元是：%ld\n", i, P, z);
        else
            printf("%ld和%ld不互素，最大公约数为：%ld\n", i, P, z);

        if (extended_euclid_weired(P, i, &z))
            printf("%ld和%ld互素, 模逆元是：%ld\n", P, i,z);
        else
            printf("%ld和%ld不互素，最大公约数为：%ld\n", P, i, z);
		printf("************************\n");
    }
    comm  = extended_euclid_weired(8, 12, &y);
    printf("%d %d, %d %ld\n", 8, 12, comm, y);
    comm  = extended_euclid_weired(8, 0, &y);
    printf("%d %d, %d %ld\n", 8, 0, comm, y);

	return 0;
}



