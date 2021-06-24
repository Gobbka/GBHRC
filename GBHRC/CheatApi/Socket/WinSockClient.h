#pragma once



namespace Network
{
	class WinClient
	{
	protected:
		long(*_receive_function)(unsigned long long socket,char**out_buffer);
		void(*_send_function)(unsigned long long socket,char*in_buffer,long size);
		
	private:
		unsigned long long _socket = 0;
	public:
		bool connect_to(const char* ip, long port);
		void send_data(char* data, long size) const;
		long receive_to(char** out_data) const;

		WinClient();
		~WinClient();
	};
}

