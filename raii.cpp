#include <iostream>
#include <thread>
/**
 * @brief      Resource Acquisition Is Initialization (RAII)
 */

class thread_guard
{
	std::thread & t;
public:
	explicit thread_guard(std::thread& t_):
		t(t_)
	{}

	/*
	 * Destructor of thread_guard first tests to see if std::thread
	 * is joinable() before calling join(). Prevents making multiple
	 * calls to join(), which can be called only once.
	 */
	~thread_guard()
	{
		if(t.joinable())
		{
			t.join();
		}
	}

	/*
	 * Copy constructor and copy-assignment operators marked =delete
	 * to ensure they are not automatically provided by compiler.
	 * By declaring them deleted, any attempt to copy a thread_guard 
	 * object will generate compilation error.
	 */
	thread_guard(thread_guard const&)=delete;
	thread_guard& operator= (thread_guard const&)=delete;
};

void do_something(int temp)
{
    std::cout<<"doing something\n";
    return;
}

struct func
{
	int & i;
	func(int& i_):i{i_}{}
	
	/*
	 * The first part operator() is the way to declare the function 
	 * that is called when an instance of the class is invoked as a 
	 * function. The second pair of parentheses would contain the 
	 * actual arguments.
	 */
	void operator()()
	{
		for(unsigned j=0; j<1000000;++j)
		{
			do_something(i);
		}
	}
};

void do_something_in_current_thread()
{
	std::cout<<"In current thread\n";
	return;
}

/*
 * When execution of current thread reaches end of f, 
 * local objects destroyed in reverse order of construction.
 * 
 * thread_guard g destroyed first, and the thread is joined in
 * the destructor.
 */
int main()
{
	int some_local_state = 0;
    func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	do_something_in_current_thread();
}
