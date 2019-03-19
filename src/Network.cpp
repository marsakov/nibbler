#include "../inc/Network.hpp"
#include <pthread.h>

static int check_accept;

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
	printf("destructor\n");
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

	struct timeval timeout;
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;

	if (setsockopt (server->socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		perror("setsockopt failed\n");

	if (setsockopt (server->socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		perror("setsockopt failed\n");

	// fcntl(server->socket, F_SETFL, O_NONBLOCK);

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

	struct timeval timeout;
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;

	if (setsockopt (*listen_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		perror("setsockopt failed\n");

	if (setsockopt (*listen_sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		perror("setsockopt failed\n");
	
	struct sockaddr_in my_addr;
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr =  htonl(INADDR_ANY);
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

int Network::handle_new_connection() {
	struct sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	socklen_t client_len = sizeof(client_addr);

	std::cout << "check_accept1 " << check_accept << std::endl;
	int new_client_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &client_len);
	check_accept = new_client_sock;
	std::cout << "check_accept2 " << check_accept << std::endl;

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
	check_accept = 0;
	if (serverBool && start_listen_socket(&listen_sock) != 0)
		exit(EXIT_FAILURE);
	
	if (!serverBool && connect_server(&server) != 0)
		shutdown_properly(EXIT_FAILURE);

	/* Set nonblock for stdin. */
	// int flag = fcntl(STDIN_FILENO, F_GETFL, 0);
	// flag |= O_NONBLOCK;
	// fcntl(STDIN_FILENO, F_SETFL, flag);
	
	if (serverBool)
		connection.socket = NO_SOCKET;

	high_sock = (serverBool) ? listen_sock : server.socket;
	
	if (serverBool) {
		printf("Waiting for incoming connections.\n");
		waiting();
		//handle_new_connection();
	}
}

int Network::cycle(eKeyType *key, int *x, int *y) {
	int arr[3];

	arr[0] = *key;
	if (serverBool) {
		arr[1] = *x;
		arr[2] = *y;

		std::cout << "APPLE x = " << *x << " y = " << *y << std::endl;
	}

	send( (serverBool) ? connection.socket : server.socket, arr, sizeof(arr), 0);
	arr[0] = none;
	recv((serverBool) ? connection.socket : server.socket, arr, sizeof(arr), 0);
	*key = (eKeyType)arr[0];

	if (!serverBool) {
		*x = arr[1];
		*y = arr[2];

		std::cout << "APPLE x = " << *x << " y = " << *y << std::endl;
	}

	return (0);
}

// --------------------------      send/recv snake coord            ------------------------------

// int Network::cycle(std::vector<rect> *snakeRect1, std::vector<rect> *snakeRect2, eKeyType *k) {
// 	int siz = (*snakeRect1).size();

// 	rect snake[siz];
// 	for (int i = 0; i < siz; i++)
// 	{
// 		snake[i].x = (*snakeRect1)[i].x;
// 		snake[i].y = (*snakeRect1)[i].y;
// 	}

// 	snake[1].s = (int)*k;

// 	std::cout << "snakeRect1 = " << snake[1].s << std::endl;

// 	send( (serverBool) ? connection.socket : server.socket, snake, sizeof(snake), 0);
// 	printf("1\n");
// 	snake[1].s = (int)none;
// 	recv((serverBool) ? connection.socket : server.socket, snake, sizeof(snake), 0);
// 	printf("2\n");

// 	for (int i = 0; i < siz; i++)
// 	{
// 		(*snakeRect2)[i].x = snake[i].x;
// 		(*snakeRect2)[i].y = snake[i].y;
// 	}


// 	*k = (eKeyType)snake[1].s;
// 	std::cout << "FROM  = " << snake[1].s << std::endl;


// 	return 0;
// }


char *Network::peer_get_addres_str(peer_t *peer)
{
	static char ret[INET_ADDRSTRLEN + 10];
	char peer_ipv4_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &peer->addres.sin_addr, peer_ipv4_str, INET_ADDRSTRLEN);
	sprintf(ret, "%s:%d", peer_ipv4_str, peer->addres.sin_port);
	
	return (ret);
}

void* Network::one(void *args) {
	char	sec;

	sec = 10;
	printf("waiting for connection \n");
	while (sec >= 0)
	{
		sleep(1);
		printf("%d\n", sec);
		if (check_accept)
			return 0;
		sec--;
	}
	exit(0);
    return args;
}

void	Network::waiting()
{
	pthread_t	thread;

	pthread_create(&thread, NULL, one, NULL);
	handle_new_connection();
}