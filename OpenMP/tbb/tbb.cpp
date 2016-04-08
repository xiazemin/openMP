// tbb.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "task_scheduler_init.h"
#include "blocked_range.h"
#include "parallel_for.h"
// ����tbb_debug.lib
//#pragma comment(lib, "tbb_debug.lib")
using namespace tbb;
// ��ÿ��Itemִ�иò���
void Foo(float value)
{
	printf("%.2f/n ", value);
}
class ApplyFoo
{
	float * const my_a;
public:
	void operator () (const blocked_range<size_t> & r) const
	{
		float * a = my_a;
		for (size_t i = r.begin(); i != r.end(); ++ i)
			printf("%.2f\n ",my_a[i]);//Foo(a[i]);
	}
	ApplyFoo(float a[]) : my_a(a) {}
};
void ApplyFun(float a[],int size)
{
	
	for (int i=0;i<size;i++)
	{
		printf("%f\n",a[i]);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	// ����task scheduler
	// task_scheduler_init֧��һ����������ָ��ʹ�õ��߳���
	task_scheduler_init init;
	float a[100];
	for (int i = 0; i < 100; i ++)
		a[i] = (float)i;
	// TBB�������ֳ����ɵ�block
	// ��block����ApplyFoo���functor
	parallel_for(blocked_range<size_t>(0, 100),ApplyFoo(a));

	//parallel_for(blocked_range<size_t>(0, 100),ApplyFun(a,100));
	return 0;
}
