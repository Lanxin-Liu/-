#ifndef OrderMessage_H
#define OrderMessage_H

#include <cstdio>
#include <cstdlib>
#include <cstring>


 /*��Ϊ��Ϣ��������ʽ*/
/*һ�����ݷ�Ϊ�����֣�\n
* 1���ַ���ͷ��4���ֽڱ�ʾ���ݲ��ֵĳ��ȣ����Ϊ9999�����㲹0
* 2���ַ���������ַ���ʾ��������
* 3���ַ�������Ϊ��������*/

class Order_Msg
{
public:
	enum { header_length = 4 };
	enum { max_body_length = 512 };

	Order_Msg()
		:body_length_(0){}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	size_t length() const
	{
		return header_length + body_length_;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	void body_length(size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}
	/*����ʾ����ȵ��ַ���������Σ�������󳤶ȱȽ�*/
	bool decode_header()
	{
		using namespace std;
		char header[header_length + 1] = "";
		strncat(header, data_, header_length);
		body_length_ = atoi(header);
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}

	/*�������������ַ�����������ͷ��*/
	void encode_header()
	{
		using namespace std;
		char header[header_length + 1] = "";
		sprintf(header, "%4d", body_length_);
		memcpy(data_, header, header_length);
	}


private:
	char data_[header_length + max_body_length];
	size_t body_length_;

};




#endif /*OrderMessage_H*/