#include <iostream>
#include <memory>
#include "sync.h++"
#include "algorithm.h++"
#include "model.h++"

struct model_type
	: public teach::model<std::string_view, std::string_view>
{
	void emit(const std::string_view &k, const std::string_view &v)
	{
		std::cout << v << " (" << k << ")" << std::endl;
	}
};

typedef teach::algorithm<std::unique_ptr<model_type>> algorithm_type;
algorithm_type algorithm(std::unique_ptr<model_type>(new model_type()));

class db : public ar::db
{
public:
	//using seventh database at localhost
	//standard port
	db() : ar::db("redis://127.0.0.1:6379/7") { }

	void handle_key(std::string_view key)
	{
		std::string_view k{key};
		std::string v = this->get(k);
		algorithm.transport(k, v);
	}
};

void
test1()
{
	db().handle_key("world");
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
