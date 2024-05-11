#include"async_client.h"

using namespace boost::asio;

int main()
{
	io_context context;

	boost::shared_ptr<a_client> client( new a_client(context, "Alex"));
	try
	{
		client->Start(ip::tcp::endpoint(ip::make_address_v4("127.0.0.1"), 1313));
	}
	catch (boost::system::error_code& ec)
	{
		std::cout << ec.what() << std::endl;
	}
	context.run();

}