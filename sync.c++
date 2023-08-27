#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <hiredis.h>
#include "sync.h++"

using namespace ar;

ar::db::db(std::string_view url)
{
	const char *ip = "127.0.0.1";
	int port = 6379;
	unsigned int dbn = 7;
	context = redisConnect(ip, port);
	select(dbn);
}

ar::db::error_type db::error() const
{
	error_type ret;
	if (ret.code = ctx()->err)
		ret.desc = ctx()->errstr;
	return ret;
}

ar::db::check_and_throw() const
{
	if (!ctx())
		throw std::runtime_error("NULL Redis context");
	else {
		auto err = error();
		if (err.code)
			throw std::runtime_error(err.desc);
	}
}

void
ar::db::select(unsigned int ndb)
{
	redisCommand(ctx(), "SELECT %i", ndb);
}

std::string
ar::db::get(std::string_view key)
{
	std::ostringstream cmd;
	cmd << "GET " << key;
	std::string cmd_str = cmd.str();
	redisReply *reply = static_cast<redisReply *>(
		redisCommand(ctx(), cmd_str.c_str())
	);
	if (reply->type == REDIS_REPLY_STRING) {
		const char *str = reply->str;
		size_t len = reply->len;
		return std::string(str, str + len);
	} else
		std::cerr << reply->type << std::endl;
	return "ERROR";
}
