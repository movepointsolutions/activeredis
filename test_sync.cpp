#include <iostream>
#include <memory>
#include "sync.h++"
#include "algorithm.h++"
#include "model.h++"

class db : public ar::db
{
public:
	struct model_type
		: public teach::model<std::string_view, std::string_view>
		//, public std::enable_shared_from_this<model_type>
	{
		// we are emitting K/V pairs
		void emit(const std::string_view &k,
		          const std::string_view &v)
		{
			std::cout << v << " (" << k << ")" << std::endl;
		}
	};

	typedef std::shared_ptr<model_type> mptr_type;

	class algorithm_type : public teach::algorithm<mptr_type>
	{
	public:
		algorithm_type(mptr_type mdl)
			: teach::algorithm<mptr_type>(mdl)
		{ }

		void handle(std::string_view k, std::string_view v)
		{
			transport(k, v);
		}
	};

	mptr_type model;
	algorithm_type algorithm;

	//using seventh database at localhost
	//standard port
	db() : ar::db("redis://127.0.0.1:6379/7")
	     , model{new model_type()}
	     , algorithm(model)
	{ }

	void handle_world()
	{
		std::string_view k{"world"};
		std::string v = this->get(k);
		algorithm.handle(k, v);
	}
};

void
test1()
{
	db().handle_world();
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
