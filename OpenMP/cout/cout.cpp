// cout.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <omp.h>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{   
	 int coreNum = omp_get_num_procs();//��ô���������
	 cout<<coreNum<<"cores"<<endl;
	int sum=0;
	 double t1 = omp_get_wtime( );
	#pragma omp parallel for // reduction(+:sum)
	for (int i=0;i<10;i++)
	{
		//#pragma omp critical
		{
			sum+=i;
			cout<<i<<"\t"<<sum<<endl;
		}
		
	}
	 double t2 = omp_get_wtime( );
	cout<<endl;
	cout<<sum<<endl<<t2-t1<<endl;
	return 0;
}

//#pragma omp parallel sections
//{
//#pragma omp section
//	{
//		function1();
//	}
//����#pragma omp section
//	{
//		function2();
//	}
// }