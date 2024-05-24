#include"async_client.h"
#include"HandleClient.h"
#include"ctime"

using namespace boost::asio;

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	io_context context;

	std::vector<std::string> names{ "Alex","Den","Mark","Bob","Liza","glasha","mark","ben","conan","socket"};

	HandleClient clients(context,names);

	clients.start();

	context.run();

}