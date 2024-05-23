
#pragma once
#ifndef ASYNC_CLNT_H
#define ASYNC_CLNT_H
#include"iostream"
#include"boost/asio.hpp"
#include"boost/bind.hpp"
#include"boost/chrono.hpp"
#include"boost/enable_shared_from_this.hpp"
#include"boost/noncopyable.hpp"

using namespace boost::asio;

class HandleClient;

class a_client:public boost::enable_shared_from_this<a_client>, boost::noncopyable
{
public:
	explicit a_client(io_context& context,const std::string username):sock_(context),username_(username),timer_(context){}

	void Start(ip::tcp::endpoint& ep);
	
private:

	void stop();

	void on_connect(const boost::system::error_code& ec);

	void on_write(const boost::system::error_code& ec, size_t bytes);

	void on_read(const boost::system::error_code& ec, std::size_t bytes);

	void do_write(const std::string& msg);

	void do_read();

	void postpone_ping();

	void on_ping(const std::string& msg);

	void on_login();

	void on_client(const std::string& msg);

	void do_ask_clients();

	inline void ErrorHandle(const boost::system::error_code& ec);

	


	ip::tcp::socket sock_;

	std::string username_;

	bool started_ = false;

	char read_buff[1024];

	char write_buff[1024];

	deadline_timer timer_;

    boost::asio::streambuf buffer_;


};
#endif // !ASYNC_CLNT_H


