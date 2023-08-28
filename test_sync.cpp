#include <iostream>
#include <memory>
#include "sync.h++"
#include "algorithm.h++"
#include "model.h++"

struct model_type : public teach::model<std::string, std::string>
{
	void emit(const std::string &k, const std::string &v)
	{
		std::cout << k << ", " << v << "!" << std::endl;
	}
};

typedef teach::algorithm<std::unique_ptr<model_type>> algorithm_type;
algorithm_type algorithm(std::unique_ptr<model_type>(new model_type()));

void
test1()
{
	//using seventh database at localhost
	//standard port
	ar::db db("redis://127.0.0.1:6379/7");
	auto key = "hello";
	auto value = db.get(key);
	algorithm.transport(key, value);
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
