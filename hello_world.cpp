#include <iostream>
#include <thread>
 /*
  * Compilation instructions
  * $ g++ hello_world.cpp -std=c++0x -lpthread -o hello
  * $ ./hello
  */

/*
 * every thread has initial function 
 * where new thread execution begins
 * for the main application-- this is main()
 */
void hello()
{
	std::cout<<"Hello concurrency world\n";
}

int main()
{
	// initializing thread object t
	std::thread t(hello);
	std::cout<< "Completed excution of main()\n";
	// causes main() thread to wait for thread t
	t.join();
}