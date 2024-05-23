#include"async_client.h"
#include"HandleClient.h"

using namespace boost::asio;

int main()
{
	io_context context;

	std::vector<std::string> names{ "Alex","Den","Mark","Bob","Liza" };

	HandleClient clients(context,names);

	clients.start();

	context.run();

}