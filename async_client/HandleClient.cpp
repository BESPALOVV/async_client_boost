#include"HandleClient.h"

void HandleClient::start()
{
	for (auto client : clients_name_)
	{
		boost::shared_ptr<a_client> new_(new a_client(context, client));

		new_->Start(ip::tcp::endpoint(ip::make_address_v4("127.0.0.1"), 1313));

		clients_.push_back(new_);
	}
}

