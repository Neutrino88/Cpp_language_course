#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>

const size_t MAX_BUFF_LEN = 100;

int main(int argc, char** argv) {
	/* create main socket */
	int master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (master_socket < 0) {
		std::cerr << "serv: Can't create main socket" << std::endl;
		return 1;
	}

	/* bind master_socket to port and address */
	struct sockaddr_in sock_addr;
	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(12345);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (0 > bind(master_socket, (struct sockaddr*)&sock_addr, sizeof(sock_addr))){
		std::cerr << "serv: Can't bind" << std::endl;
		return 2;
	}

	/* listen */
	if (0 > listen(master_socket, SOMAXCONN)) {
		std::cerr << "serv: Can't listen" << std::endl;
		return 3;
	}
	
	for (int count = 0; count < 10; ++count) {
		int slave_socket = accept(master_socket, 0, 0);

		if (0 > slave_socket) {
			std::cerr << "serv: Can't accept" << std::endl;
			continue;
		}

		char buff[MAX_BUFF_LEN];
		ssize_t size = recv(slave_socket, buff, MAX_BUFF_LEN, MSG_NOSIGNAL);

		if (0 < size) {
			std::cout << "serv: " << std::string(buff, size) << std::endl;

			if (0 > (size = send(slave_socket, buff, MAX_BUFF_LEN, MSG_NOSIGNAL))) {
				std::cerr << "serv: Can't send message" << std::endl;
			}
		}

		close(slave_socket);
	}

	close(master_socket);
	return 0;
}
