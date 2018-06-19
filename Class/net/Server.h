#ifndef _Server_h_
#define _Server_h_

#include "cocos2d.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <stdio.h>
#include<ostream>
#include"OrderMessage.h"

using namespace boost::asio;
using boost::asio::ip::tcp;
typedef std::deque<Order_Msg> message_queue;
//-----------------------------����----------------------------------
/*�Ự��ĳ�����࣬��Ҫÿ����������deliver����
ÿ���ͻ��˸�����˼��γɻỰ*/
class chat_base
{
public:
	virtual ~chat_base() {}
	virtual void deliver(const Order_Msg &msg);
};

typedef boost:: shared_ptr<chat_base> chat_base_ptr;

//-----------------------------�Ự������----------------------------------

/*�Ự����Ļ���*/
class chat_room
{
public:

	/*�򷿼������лỰ��������*/
	void deliver(const Order_Msg& msg)
	{
		temp_msg_.push_back(msg);
		while (temp_msg_.size() > max_temp_msg)
		{
			temp_msg_.pop_front();
		}
		std::for_each(pars_.begin(), pars_.end(),
			boost::bind(&chat_base::deliver, _1, boost::ref(msg)));
	}

	/*���¼���ĻỰ���뷿�䲢�Թ㲥��ʽ��������*/
	void join(chat_base_ptr par)
	{
		pars_.insert(par);
		std::for_each(temp_msg_.begin(), temp_msg_.end(),
			boost::bind(&chat_base::deliver, par, _1));
	}

	/*�˳��ĻỰ���˳����䣬�������䴫������*/
	void leave(chat_base_ptr par)
	{
		pars_.erase(par);
	}


private:
	std::set<chat_base_ptr>  pars_; //���淿�������в���ĻỰ
	message_queue temp_msg_; //���淿������Ҫ���͵���Ϣ

	enum {max_temp_msg=0}; //��ǰ������ڵ����δ���ͻỰ��
};
//------------------------------�Ự��---------------------------------

/*�̳���chat_base*/

class session :public chat_base,public boost::enable_shared_from_this<session>
{
public:

	/*����Ự����ʱ��δ���Ӻͼ��뷿��*/
	session(boost::asio::io_service& service,chat_room room)
		:socket_(service),room_(room)
	{}

	/*�����׽���*/
	tcp::socket& socket()
	{
		return socket_;
	}

	/*�����Ự�����뷿��*/
	void start()
	{
		room_.join(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), Order_Msg::header_length),
			boost::bind(
				&session::handle_read_header, shared_from_this(),
				boost::asio::placeholders::error));
	}

	/*��ĳ���ͻ����յ�����Ϣ���͸��˻Ự��Ӧ�Ŀͻ���*/
	void deliver(const Order_Msg& msg)
	{
		bool write_in_progress = !write_msg_.empty();
		write_msg_.push_back(msg);
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_, boost::asio::buffer(write_msg_.front().data(), write_msg_.front().length()),
				boost::bind(&session::handle_write, shared_from_this(), boost::asio::placeholders::error));
		}
	}

	/*���տͻ�����Ϣ�����ַ�������*/
	void handle_read_header(const boost::system::error_code& error)
	{
		if (!error&&read_msg_.decode_header())
		{
			boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&session::handle_read_body, shared_from_this(), boost::asio::placeholders::error));

		}
		else {
			room_.leave(shared_from_this());
		}
	}

	/*�����괦���ַ������ȵĺ����󣬵��ñ�������������Ҫ����*/
	void handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			room_.deliver(read_msg_);
			boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), Order_Msg::header_length),
				boost::bind(&session::handle_read_header, shared_from_this(), boost::asio::placeholders::error));
		}
		else {
			room_.leave(shared_from_this());
		}
	}

	/*�������ݣ�������Ϣδ����ݹ���ø÷��ͺ���*/
	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msg_.pop_front();
			if (!write_msg_.empty())
			{
				boost::asio::async_write(socket_, boost::asio::buffer(write_msg_.front().data(), write_msg_.front().length()),
					boost::bind(&session::handle_write, shared_from_this(), boost::asio::placeholders::error));
			}
		}
		else {
			room_.leave(shared_from_this());
		}
	}


private:
	tcp::socket socket_; //�ûỰ�׽���
	chat_room& room_; //���ڷ���
	Order_Msg read_msg_; //����ȡ����Ϣ
	message_queue  write_msg_; //��Ҫ���͵����ݶ���
};

	typedef boost::shared_ptr<session> session_ptr;

//------------------------------server��---------------------------------
	
class server
{
public:

	/*���������������������˵���Ϣ�󶨣���ʼ�����ͻ��˵����ӣ������ú�����������*/
	server(boost::asio::io_service& service, const tcp::endpoint& ep)
		:service_(service), acceptor_(service, ep)
	{
		start_accept();
	}

	/*�����첽�������������ӣ������Ự*/
	void start_accept()
	{
		session_ptr new_(new session(service_, room_));
		acceptor_.async_accept(new_->socket(),
			boost::bind(&server::handle_accept, this, new_, boost::asio::placeholders::error));
	}

	/*������ܣ����µĻỰ����room����ʼ��ȡ�����첽�ͻ��˵���Ϣ*/
	void handle_accept(session_ptr session, const boost::system::error_code& error)
	{
		if (!error)
		{
			session->start();
		}
		start_accept();
	}

private:
	boost::asio::io_service& service_; //ִ���첽�����Ķ���ȫ��ֻ����һ����
	tcp::acceptor  acceptor_;  //���������յ����ӵļ�����
	chat_room  room_;  //���䣬ÿ�����յ��µ��������󲢵����������Ӵ���ʱ���µĻỰ���뷿��

};

typedef boost::shared_ptr<server> server_ptr;
typedef std::list<server_ptr> server_list;

//==================================LocalServer===============================

/*�����ı��ط���������Cocos�ڴ����ϵͳ����*/

class LocalServer : public cocos2d::Node
{
public:

	/*���챾�ط�������������server*/
	static LocalServer* create()
	{
		LocalServer *ls = new LocalServer();
		if (ls)
		{
			ls->autorelease();
			ls->runserver();

			return ls;

		}
		return nullptr;
	}

	/*�½�һ���̣߳�����server*/
	void runserver()
	{
		std::thread new_t(&LocalServer::newserver, this);
		new_t.detach();
	}

	/*�ڶ����߳�������server*/
	int newserver()
	{
		try 
		{
			boost::asio::io_service service;
			server_list servers;
			using namespace std;
			tcp::endpoint ep(tcp::v4(), 8001);
			server_ptr  new_server(new server(service, ep));
			servers.push_back(new_server);

			service.run();

		}
		catch (std::exception& e)
		{
			std:: cerr << "Exception:" << e.what() << "\n";
		}
		return 0;
	}
};



#endif /*_Server_h_*/
