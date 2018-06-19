#ifndef Client_h
#define Client_h


#include "cocos2d.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <fstream>
#include "OrderMessage.h"
#include <vector>
#include <string>

/*�첽�ͻ��ˣ��������ݽ��պͷ���*/

using boost::asio::ip::tcp;
typedef std::deque<Order_Msg> message_queue;

/*�������ݵĽ���/����/����*/
class deal_order
{
public:
	/*����������ӵĿͻ���
	  service   ���ڴ���socket
	  endpoint  ����λ�õĶ˿ں�
	*/
	deal_order(boost::asio::io_service& service, tcp::resolver::iterator endpoint)
		:service_(service), socket_(service)
	{
		boost::asio::async_connect(socket_, endpoint,
			boost::bind(&deal_order::handle_connect, this, boost::asio::placeholders::error));
	}

	/*����ָ���server*/
	void write(const Order_Msg& msg)
	{
		service_.post(boost::bind(&deal_order::do_write, this, msg));
	}

	/*��ֹ����*/
	void close()
	{
		service_.post(boost::bind(&deal_order::do_close, this));
	}

private:

	/*�ɹ�����ʱ���øú�������*/
	void handle_connect(const boost::system::error_code& error);

	/*�ݹ鷢�͵ȴ����͵����ݣ���û�����ݷ���ʱֹͣ�ݹ�*/
	void handle_write(const boost::system::error_code& error);

	/*do_write()�������Ȱ���Ϣ������������,�ȴ�����*/
	void do_write(Order_Msg msg);

	/*�ر�ʱ����*/
	void do_close()
	{
		socket_.close();
	}

	/*�ڽ��ܵ���Ϣ���������ַ���*/
	void handle_read_header(const boost::system::error_code& error);

	/*�����������ݲ��������ַ������Ⱥ���øú��������������*/
	void handle_read_body(const boost::system::error_code& error);

private:

	boost::asio::io_service&    service_;       // ���ڴ���socket
	tcp::socket                 socket_;        //tcp���׽���
	Order_Msg                read_msg_;      //ÿ��ѭ������ȡ�����ݶ���
	message_queue          write_msgs_;    //�ȴ������͵����ݶ���
};

//----------------------------------------------------------------------

/*���������ӷ������������Ŀͻ���*/
class Client :public cocos2d::Node
{
public:
	bool _is_searched;   //�Ƿ�����������ҽ���������
	bool _filter_mode;  //�Ƿ����˹���ģʽ
	bool _with_server;  //�Ƿ�ͬʱ�����˷����
	deal_order* _DOInstance; //�������ݽ����뷢��
	std::mutex  t_lock; //�߳���
	std::string order_type; //ʶ��ָ������
	std::deque<std::string> _orderlist; //��ȡ��ָ�������

	/*�����ͻ���*/
	static Client* create(int mode)
	{
		Client* sprite = new Client();
		if (sprite)
		{
			sprite->autorelease();
			sprite->runclient(mode);

			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	/*����client��
	1.ͬʱ��server����
	2.ֻ����client*/
	void runclient(int mode);

	/*ȡ����ȡ��ָ����ض�ȡ���Ĳ��������˵�ָ��*/
	std::string pullorder();

	/*���Ͳ���
	code ָ�����
	msg  ָ������*/
	void send_message(const std::string& code, const std::string &msg);

	/*����������/���ӷ����*/
	int client();


};

#endif/*Client_h*/
