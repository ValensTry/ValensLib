#include <iostream>
#include <memory>


//shared_ptr, weak_ptr, unique_ptr

/*shared_ptr
shared_ptr多个指针指向相同的对象。shared_ptr使用引用计数，每一个shared_ptr的拷贝都指向相同的内存。每使用他一次，内部的引用计数加1，每析构一次，内部的引用计数减1，减为0时，自动删除所指向的堆内存。shared_ptr内部的引用计数是线程安全的，但是对象的读取需要加锁。

初始化。智能指针是个模板类，可以指定类型，传入指针通过构造函数初始化。也可以使用make_shared函数初始化。不能将指针直接赋值给一个智能指针，一个是类，一个是指针。例如std::shared_ptr<int> p4 = new int(1);的写法是错误的
拷贝和赋值。拷贝使得对象的引用计数增加1，赋值使得原对象引用计数减1，当计数为0时，自动释放内存。后来指向的对象引用计数加1，指向后来的对象。
get函数获取原始指针
注意不要用一个原始指针初始化多个shared_ptr，否则会造成二次释放同一内存
注意避免循环引用，shared_ptr的一个最大的陷阱是循环引用，循环，循环引用会导致堆内存无法正确释放，导致内存泄漏。循环引用在weak_ptr中介绍。
*/

/*
 unique_ptr“唯一”拥有其所指对象，同一时刻只能有一个unique_ptr指向给定对象（通过禁止拷贝语义、只有移动语义来实现）。
 相比与原始指针unique_ptr用于其RAII的特性，使得在出现异常的情况下，动态资源能得到释放。
 unique_ptr指针本身的生命周期：从unique_ptr指针创建时开始，直到离开作用域。离开作用域时，若其指向对象，则将其所指对象销毁(默认使用delete操作符，用户可指定其他操作)。
 unique_ptr指针与其所指对象的关系：
 在智能指针生命周期内，可以改变智能指针所指对象，如创建智能指针时通过构造函数指定、通过reset方法重新指定、通过release方法释放所有权、通过移动语义转移所有权。
*/

/*
weak_ptr是为了配合shared_ptr而引入的一种智能指针，因为它不具有普通指针的行为，没有重载operator*和->,它的最大作用在于协助shared_ptr工作，像旁观者那样观测资源的使用情况。
weak_ptr可以从一个shared_ptr或者另一个weak_ptr对象构造，获得资源的观测权。但weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加。
使用weak_ptr的成员函数use_count()可以观测资源的引用计数，另一个成员函数expired()的功能等价于use_count()==0,但更快，表示被观测的资源(也就是shared_ptr的管理的资源)已经不复存在。
weak_ptr可以使用一个非常重要的成员函数lock()从被观测的shared_ptr获得一个可用的shared_ptr对象， 从而操作资源。
但当expired()==true的时候，lock()函数将返回一个存储空指针的shared_ptr。
*/

void sharedPointer() {
	int a = 10;
	std::shared_ptr<int>ptra = std::make_shared<int>(a);
	std::shared_ptr<int>ptra2(ptra); //copy
	std::cout << ptra.use_count() << std::endl;

	int b = 20;
	int *pb = &a;
	std::shared_ptr<int>ptrb = std::make_shared<int>(b);
	ptra2 = ptrb; //assign
	pb = ptrb.get(); //get the original pointer

	std::cout << ptra.use_count() << std::endl;
	std::cout << ptrb.use_count() << std::endl;
}

void uniquePointer() {
	std::unique_ptr<int>uptr(new int(10)); //绑定动态对象
	std::unique_ptr<int>uptr2 = std::move(uptr); //转换所有权
	uptr2.release(); //释放所有权
}

void weakPointer() {
	std::shared_ptr<int>sh_ptr = std::make_shared<int>(10);
	std::cout << sh_ptr.use_count() << std::endl;

	std::weak_ptr<int>wp(sh_ptr);
	std::cout << wp.use_count() << std::endl;

	if (!wp.expired()) {
		std::shared_ptr<int>sh_ptr2 = wp.lock();
		*sh_ptr = 100;
		std::cout << wp.use_count() << std::endl;
	}
}