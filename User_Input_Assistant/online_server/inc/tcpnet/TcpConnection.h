///
/// @file    TcpConnection.h
/// @author  lemon(haohb13@gmail.com)
/// @date    2018-09-03 14:01:23
///
//boost库中的：class A:public enable_share_from_this<A>	这种类型的类
//使用场合：当类A的成员函数里需要把当前对象作为参数传给其他函数时，就需要传递一个
//指向自身的:share_ptr,我们就使用类A继承enable_share_from_this,然后通过其成员函数
//share_from_this()返回指向自身的share_ptr
#ifndef __WD_TCPCONNECTION_H__
#define __WD_TCPCONNECTION_H__

#include "Noncopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"

#include <string>
#include <memory>
#include <functional>

namespace wd
{
	class EpollPoller;
	class TcpConnection;
	typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
	class TcpConnection:Noncopyable,public std::enable_shared_from_this<TcpConnection>
	{
		public:
			typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;
			TcpConnection(int sockfd,EpollPoller *loop);
			~TcpConnection();

			std::string receive();
			void send(const std::string &msg);
			void sendInLoop(const std::string &msg);
			void shutdown();

			std::string toString();//返回Ip地址和端口号信息

			void setConnectionCallback(TcpConnectionCallback cb);
			void setMessageCallback(TcpConnectionCallback cb);
			void setCloseCallback(TcpConnectionCallback cb);

			void handleConnectionCallback();
			void handleMessageCallback();
			void handleCloseCallback();

		private:
			Socket _sockfd;//文件描述符
			SocketIO _sockIO;//accept()产生的新的文件描述符
			const InetAddress _localAddr;//本地IP地址和端口
			const InetAddress _peerAddr;//服务器IP地址和端口
			bool _isShutdownWrite;
			EpollPoller * _loop;

			TcpConnectionCallback _onConnectionCb;
			TcpConnectionCallback _onMessageCb;
			TcpConnectionCallback _onCloseCb;
	};
}
#endif
