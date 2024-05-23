
#include "async_client.h"


using namespace std;

class HandleClient;

void a_client::Start(ip::tcp::endpoint& ep)
{
	sock_.async_connect(ep, bind(&a_client::on_connect, shared_from_this(), _1));
}

void a_client::stop()
{
	sock_.close();

	sock_.cancel();
}

void a_client::on_connect(const boost::system::error_code& ec)
{
	if (ec) {
		std::cout << "Connected error" << std::endl;

		std::cout << ec.what() << std::endl;
		
		return;
	}
	started_ = true;

	do_write("login " + username_ + '\n');

}

void a_client::do_write(const std::string& msg)
{
	if (!started_) { return; }

	std::copy(msg.begin(), msg.end(), write_buff);

	sock_.async_write_some(buffer(write_buff,msg.size()), bind(&a_client::on_write,shared_from_this(), _1, _2));
}

void a_client::on_write(const boost::system::error_code& ec, size_t bytes)
{
	ErrorHandle(ec);

	buffer_.consume(bytes);

	do_read();
}

void a_client::do_read()
{
	boost::asio::async_read_until(sock_, buffer_, '\n', boost::bind(&a_client::on_read,this, _1, _2));
}

void a_client::on_read(const boost::system::error_code& ec, std::size_t bytes)
{
	ErrorHandle(ec);

	std::istream in(&buffer_);

	std::string message;

	std::getline(in, message);


	if (message.find("ping") == 0) { on_ping(message); }

	else if (message.find("clients") == 0) { on_client(message); }

	else if (message.find("login") == 0) { on_login(); }

}

void a_client::on_ping(const std::string& msg)
{
	std::istringstream in(msg);

	std::string answ;

	in >> answ >> answ;

	if (answ == "client_list_changed")
	{
		do_ask_clients();
	}
	else
	{
		postpone_ping();
	}
}

void a_client::do_ask_clients()
{
	do_write("ask_clients\n");
}

void a_client::postpone_ping()
{
	timer_.expires_from_now(boost::posix_time::milliseconds(rand() % 7000));

	timer_.async_wait(bind(&a_client::do_write, shared_from_this(), "ping\n"));

}

void a_client::on_client(const std::string& msg)
{
	std::string clients = msg.substr(8);

	std::cout << username_ + ", new clients list : " + clients << std::endl;

	postpone_ping();
}

void a_client::on_login()
{
	do_ask_clients();
}


inline void a_client::ErrorHandle(const boost::system::error_code& ec)
{
	if (!ec)
	{
		return;
	}
	else if (ec.value() == 10054||ec.value()==10053)
	{
		std::cout<<username_<<"::" << "Connection Closed(Error10054/53)" << std::endl;

		stop();
	}
	else
	{
		std::cout << "Unknown error: " << ec.what() << endl << ec.message() << endl;

		stop();
	}
}

