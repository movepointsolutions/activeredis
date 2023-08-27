#include <iostream>
#include "sync.h++"

void
test1()
{
	//using seventh database at localhost
	//standard port
	ar::db db("redis://127.0.0.1:6379/7");
	std::string world = db.get("hello");
	std::cout << "Hello, " << world << std::endl;
}

int
main()
{
	try {
		test1();
	} catch (const std::exception &e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
}
