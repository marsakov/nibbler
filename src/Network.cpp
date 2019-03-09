#include "../inc/Network.hpp"

Network::Network(bool serv) {
	serverBool = serv;
	init();
}

Network::Network(std::string ip) {
	serverBool = false;
	server_ipv_str = ip;
	init();
}

Network::Network() {
	serverBool = false;
	init();
}

Network::~Network() {
	printf("descriptor\n");
	shutdown_properly(EXIT_FAILURE);
}


int Network::connect_server(peer_t *server) {
	// create socket
	server->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server->socket < 0) {
		perror("socket()");
		return (-1);
	}
	
	// set up addres
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(server_ipv_str.c_str());
	server_addr.sin_port = htons(SERVER_LISTEN_PORT);
	
	server->addres = server_addr;
	
	if (connect(server->socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) != 0) {
		perror("connect()");
		return (-1);
	}
	
	printf("Connected to %s:%d.\n", server_ipv_str.c_str(), SERVER_LISTEN_PORT);
	
	return (0);
}

/* Start listening socket listen_sock. */
int Network::start_listen_socket(int *listen_sock) {
	// Obtain a file descriptor for our "listening" socket.
	*listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (*listen_sock < 0) {
		perror("socket");
		return (-1);
	}
 
	int reuse = 1;
	if (setsockopt(*listen_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) != 0) {
		perror("setsockopt");
		return (-1);
	}
	
	struct sockaddr_in my_addr;
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr =  htonl(INADDR_ANY);//inet_addr(INADDR_ANY);
	my_addr.sin_port = htons(SERVER_LISTEN_PORT);
 
	if (bind(*listen_sock, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) != 0) {
		perror("bind");
		return (-1);
	}
 
	// start accept client connections
	if (listen(*listen_sock, 10) != 0) {
		perror("listen");
		return (-1);
	}
	printf("Accepting connections on port %d.\n", (int)SERVER_LISTEN_PORT);
 
	return (0);
}

void Network::shutdown_properly(int code) {
	if (serverBool) {
		close(listen_sock);
		if (connection.socket != NO_SOCKET)
			close(connection.socket);
			
		printf("Shutdown server properly.\n");
		exit(code);
	}
	else
	{
		close(server.socket);
		printf("Shutdown client properly.\ncode = % d", code);
		exit(code);
	}
}

int Network::build_fd_setsCl(peer_t *server, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds) {
	FD_ZERO(read_fds);
	FD_SET(STDIN_FILENO, read_fds);
	FD_SET(server->socket, read_fds);
	
	FD_ZERO(write_fds);
	FD_SET(server->socket, write_fds);
	
	FD_ZERO(except_fds);
	FD_SET(STDIN_FILENO, except_fds);
	FD_SET(server->socket, except_fds);
	
	return (0);
}

int Network::build_fd_sets(fd_set *read_fds, fd_set *write_fds, fd_set *except_fds) {

	FD_ZERO(read_fds);
	FD_SET(STDIN_FILENO, read_fds);
	FD_SET(listen_sock, read_fds);

	if (connection.socket != NO_SOCKET)
		FD_SET(connection.socket, read_fds);

	FD_ZERO(write_fds);

	if (connection.socket != NO_SOCKET)
		FD_SET(connection.socket, write_fds);

	FD_ZERO(except_fds);
	FD_SET(STDIN_FILENO, except_fds);
	FD_SET(listen_sock, except_fds);

	if (connection.socket != NO_SOCKET)
		FD_SET(connection.socket, except_fds);
	return (0);
}  

int Network::handle_new_connection() {
	struct sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	socklen_t client_len = sizeof(client_addr);
	int new_client_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &client_len);
	if (new_client_sock < 0) {
		perror("accept()");
		return (-1);
	}
	
	char client_ipv4_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client_addr.sin_addr, client_ipv4_str, INET_ADDRSTRLEN);
	
	printf("Incoming connection from %s:%d.\n", client_ipv4_str, client_addr.sin_port);
	
	if (connection.socket == NO_SOCKET) {
		connection.socket = new_client_sock;
		connection.addres = client_addr;
		return (0);
	}
	printf("There is too much connections. Close new connection %s:%d.\n", client_ipv4_str, client_addr.sin_port);
	close(new_client_sock);
	return (-1);
}

int Network::close_client_connection(peer_t *client) {
	printf("Close client socket for %s.\n", peer_get_addres_str(client));
	
	close(client->socket);
	client->socket = NO_SOCKET;
	return ((1));
}

void  Network::init() { 
	
	if (serverBool && start_listen_socket(&listen_sock) != 0)
		exit(EXIT_FAILURE);
	
	if (!serverBool) {
		// create_peer(&server);
		if (connect_server(&server) != 0)
			shutdown_properly(EXIT_FAILURE);
	}

	/* Set nonblock for stdin. */
	int flag = fcntl(STDIN_FILENO, F_GETFL, 0);
	flag |= O_NONBLOCK;
	fcntl(STDIN_FILENO, F_SETFL, flag);
	
	if (serverBool) {
		connection.socket = NO_SOCKET;
		// create_peer(&connection);
	}
	
	high_sock = (serverBool) ? listen_sock : server.socket;
	
	if (serverBool) {
		printf("Waiting for incoming connections.\n");
		handle_new_connection();
	}
	
}

int Network::cycle(eKeyType *key) {

	std::cout << "START key = " << *key << std::endl;
	struct timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = 0;
	// //int key;
	// std::cout << "24546546" << std::endl;
	// std::cout << "serverBool = " << serverBool << std::endl;
	if (serverBool)
		build_fd_sets(&read_fds, &write_fds, &except_fds);
	else
		build_fd_setsCl(&server, &read_fds, &write_fds, &except_fds);
	// std::cout << serverBool << std::endl;

	if (serverBool && connection.socket > high_sock)
		high_sock = connection.socket;
	
	int activity = select(high_sock + 1, &read_fds, &write_fds, &except_fds, &tv);
	switch (activity) {
		case -1:
			perror("select()");
			shutdown_properly(EXIT_FAILURE);

		case 0:
			std::cout << "RETURN 0" << std::endl;
			return (0);
		
		default: {

			/* All set fds should be checked. */
			if (FD_ISSET(STDIN_FILENO, &read_fds)) {
				printf("HERE\n");
				shutdown_properly(EXIT_FAILURE);
			}

			if (serverBool && FD_ISSET(listen_sock, &read_fds)) {
				handle_new_connection();
			}
			
			if (FD_ISSET(STDIN_FILENO, &except_fds)) {
				printf("except_fds for stdin.\n");
				shutdown_properly(EXIT_FAILURE);
			}

			if (serverBool && FD_ISSET(listen_sock, &except_fds)) {
				printf("Exception listen socket fd.\n");
				shutdown_properly(EXIT_FAILURE);
			}
			
			if (serverBool) {

				if (connection.socket != NO_SOCKET && FD_ISSET(connection.socket, &write_fds) && *key != none)
					send(connection.socket, key, sizeof(key), 0);

				if (connection.socket != NO_SOCKET && FD_ISSET(connection.socket, &read_fds))
					recv(connection.socket, key, sizeof(key), MSG_DONTWAIT);

				if (connection.socket != NO_SOCKET && FD_ISSET(connection.socket, &except_fds)) {
					printf("Exception client fd.\n");
					close_client_connection(&connection);
				}
			}
			else
			{

				if (FD_ISSET(server.socket, &write_fds) && *key != none)
					send(server.socket, key, sizeof(key), 0);

				if (FD_ISSET(server.socket, &read_fds))
					recv(server.socket, key, sizeof(key), MSG_DONTWAIT);

				if (FD_ISSET(server.socket, &except_fds)) {
					printf("except_fds for server.\n");
					shutdown_properly(EXIT_FAILURE);
				}
			}
		}
	}
	
	std::cout << "FINISH key = " << *key << std::endl;

	return (0);
}

char *Network::peer_get_addres_str(peer_t *peer)
{
	static char ret[INET_ADDRSTRLEN + 10];
	char peer_ipv4_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &peer->addres.sin_addr, peer_ipv4_str, INET_ADDRSTRLEN);
	sprintf(ret, "%s:%d", peer_ipv4_str, peer->addres.sin_port);
	
	return (ret);
}

