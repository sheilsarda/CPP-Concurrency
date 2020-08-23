#include <iostream>
#include <thread>
 /*
  * Compilation instructions
  * $ g++ hello_world.cpp -std=c++0x -lpthread -o hello
  * $ ./hello
  */

void add_2(int * temp)
{
	*temp += 2;
	return;
}
void divide_2(int * temp)
{
	*temp /= 2;
	return;
}

int main()
{
	/* 
	 * lambda expression:
	 * allows you to write local function,
	 * possibly capturing some local vars
	 * avoiding need to pass additional args
	 */
	std::thread my_thread([]{
		int temp_var = 2;
		add_2(&temp_var);
		divide_2(&temp_var);
		std::cout<< temp_var << "\n";
	});
	
	std::cout<< "Completed excution of main()\n";
	// causes main() thread to wait for thread t
	my_thread.join();
}