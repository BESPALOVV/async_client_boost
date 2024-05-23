#pragma once 
#ifndef HANDLECLIENTS_H
#define HANDLECLIENTS_H
#include"async_client.h"

class HandleClient
{
public:
	explicit HandleClient(io_context& context, std::vector<std::string>& names_for_clients) :context(context), clients_name_(names_for_clients) {}

	void start();

private:

	io_context& context;

	std::vector<boost::shared_ptr<a_client>> clients_;

	std::vector<std::string>& clients_name_;
};
#endif // !HANDLECLIENTS_H
