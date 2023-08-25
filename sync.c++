#include <iostream>
#include <sstream>
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
		return std::string(reply->str, reply->str + reply->len);
	} else
		std::cerr << reply->type << std::endl;
	return "ERROR";
}
