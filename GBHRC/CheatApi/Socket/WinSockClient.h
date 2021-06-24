#pragma once



namespace Network
{
	class WinClient
	{
	protected:
		long(*_receive_function)(unsigned long long socket,char**out_buffer);
		
	private:
		unsigned long long _socket = 0;
	public:
		bool connect_to(const char* ip, long port);
		void send_data(char* data, long size) const;
		long receive_from(char** out_data) const;

		WinClient();
		~WinClient();
	};
}

