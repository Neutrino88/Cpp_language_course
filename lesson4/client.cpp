#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>

const size_t MAX_BUFF_LEN = 100;

int main(int argc, char** argv) {
	/* create client socket */
	int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (client_socket < 0) {
		std::cerr << "cl: Can't create client_socket" << std::endl;
		return 1;
	}

	/* connect client_socket to server */
	struct sockaddr_in sock_addr;
	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(12345);
	inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr);

	if (0 > connect(client_socket, (struct sockaddr*)&sock_addr, sizeof(sock_addr))) {
		std::cerr << "cl: Can't connect" << std::endl;
		return 2;
	}

	/* send message */
	char buff[MAX_BUFF_LEN];
	ssize_t size = send(client_socket, buff, MAX_BUFF_LEN, MSG_NOSIGNAL);

	if (0 < size) {
		if (0 > (size = recv(client_socket, buff, MAX_BUFF_LEN, MSG_NOSIGNAL))) {
			std::cerr << "cl: Can't send message" << std::endl;
		}
		else {
			std::cout << "cl:" << std::string(buff, size) << std::endl;
		}
	}
	else{
		std::cerr << "cl: Can't send message" << std::endl;
	}

	close(client_socket);
	return 0;
}
