// tbb.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "task_scheduler_init.h"
#include "blocked_range.h"
#include "parallel_for.h"
// 链接tbb_debug.lib
//#pragma comment(lib, "tbb_debug.lib")
using namespace tbb;
// 对每个Item执行该操作
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
	// 创建task scheduler
	// task_scheduler_init支持一个参数，以指定使用的线程数
	task_scheduler_init init;
	float a[100];
	for (int i = 0; i < 100; i ++)
		a[i] = (float)i;
	// TBB会把数组分成若干的block
	// 对block调用ApplyFoo这个functor
	parallel_for(blocked_range<size_t>(0, 100),ApplyFoo(a));

	//parallel_for(blocked_range<size_t>(0, 100),ApplyFun(a,100));
	return 0;
}
