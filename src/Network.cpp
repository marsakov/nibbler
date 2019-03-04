#include "../inc/Network.hpp"

Network::Network(bool serv) {
	serverBool = serv;
	init();
}

Network::Network() {
	serverBool = false;
	init();
}

Network::~Network() {
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
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IPV4_ADDR);
	server_addr.sin_port = htons(SERVER_LISTEN_PORT);
	
	server->addres = server_addr;
	
	if (connect(server->socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) != 0) {
		perror("connect()");
		return (-1);
	}
	
	printf("Connected to %s:%d.\n", SERVER_IPV4_ADDR, SERVER_LISTEN_PORT);
	
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
	my_addr.sin_addr.s_addr = inet_addr(SERVER_IPV4_ADDR);
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
		delete_peer(&server);
		printf("Shutdown client properly.\n");
		exit(code);
	}
}

int Network::build_fd_setsCl(peer_t *server, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds) {
	FD_ZERO(read_fds);
	FD_SET(STDIN_FILENO, read_fds);
	FD_SET(server->socket, read_fds);
	
	FD_ZERO(write_fds);
	// there is smth to send, set up write_fd for server socket
	if (server->send_buffer.current > 0)
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
	if (connection.socket != NO_SOCKET && connection.send_buffer.current > 0)
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
		connection.current_sending_byte   = -1;
		connection.current_receiving_byte = 0;
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
	// dequeue_all(&client->send_buffer);
	client->current_sending_byte   = -1;
	client->current_receiving_byte = 0;
	return ((1));
}

/* Reads from stdin and create new message. This message enqueues to send queueu. */

// int Network::handle_read_from_stdin() {
// 	char read_buffer[DATA_MAXSIZE]; // buffer for stdin
// 	if (read_from_stdin(read_buffer, DATA_MAXSIZE) != 0)
// 		return (-1);
	
// 	// Create new message and enqueue it.
// 	message_t new_message;
// 	prepare_message(SERVER_NAME, read_buffer, &new_message);
// 	print_message(&new_message);
	
// 	/* enqueue message for all clients */
// 	if (serverBool && connection.socket != NO_SOCKET) {
// 		if (peer_add_to_send(&connection, &new_message) != 0) {
// 			printf("Send buffer was overflowed, we lost this message!\n");
// 			// continue;
// 		}
// 		printf("New message to send was enqueued right now.\n");
// 	}
// 	else if (!serverBool) {
// 		if (peer_add_to_send(&server, &new_message) != 0) {
// 			printf("Send buffer is overflowed, we lost this message!\n");
// 			return (0);
// 		}
// 		printf("New message to send was enqueued right now.\n");
// 	}
	
// 	return (0);
// }

// int Network::handle_read_from_stdinCl(peer_t *server, char *client_name)
// {
// 	char read_buffer[DATA_MAXSIZE]; // buffer for stdin
// 	if (read_from_stdin(read_buffer, DATA_MAXSIZE) != 0)
// 	return (-1);
	
// 	// Create new message and enqueue it.
// 	message_t new_message;
// 	prepare_message(client_name, read_buffer, &new_message);
// 	print_message(&new_message);
	
// 	if (peer_add_to_send(server, &new_message) != 0) {
// 	printf("Send buffer is overflowed, we lost this message!\n");
// 	return (0);
// 	}
// 	printf("New message to send was enqueued right now.\n");
	
// 	return (0);
// }

// int Network::handle_received_message(message_t *message) {
// 	printf("Received message\n");
// 	print_message(message);
// 	return (0);
// }

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

int Network::cycle() {

	struct timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = 0;
	//int key;

	if (serverBool)
		build_fd_sets(&read_fds, &write_fds, &except_fds);
	else
		build_fd_setsCl(&server, &read_fds, &write_fds, &except_fds);

	if (serverBool && connection.socket > high_sock)
		high_sock = connection.socket;
	int activity = select(high_sock + 1, &read_fds, &write_fds, &except_fds, &tv);
	switch (activity) {
		case -1:
			perror("select()");
			shutdown_properly(EXIT_FAILURE);

		case 0:
			return (0);
			// you should never get here
			// printf("select() returns( 0).\n");
			// shutdown_properly(EXIT_FAILURE);
		
		default:
			/* All set fds should be checked. */
			if (FD_ISSET(STDIN_FILENO, &read_fds)) {
				// if ((serverBool && handle_read_from_stdin() != 0) || (!serverBool && handle_read_from_stdinCl(&server, "") != 0))
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
				if (connection.socket != NO_SOCKET && FD_ISSET(connection.socket, &read_fds)) {
					recv(connection.socket, &key, sizeof(key), MSG_DONTWAIT);
					// if (receive_from_peer(&connection) != 0) {
					// 	close_client_connection(&connection);
					// }
				}
	
				if (connection.socket != NO_SOCKET && FD_ISSET(connection.socket, &write_fds)) {
					send(connection.socket, &key, sizeof(key), 0);
					
					// if (send_to_peer(&connection) != 0) {
					// 	close_client_connection(&connection);

					// }
				}

				if (connection.socket != NO_SOCKET && FD_ISSET(connection.socket, &except_fds)) {
					printf("Exception client fd.\n");
					close_client_connection(&connection);
				}
			}
			else
			{
				if (FD_ISSET(server.socket, &read_fds))
					recv(server.socket, &key, sizeof(key), MSG_DONTWAIT);

				// if (FD_ISSET(server.socket, &read_fds)) && receive_from_peer(&server))
				// 	shutdown_properly(EXIT_FAILURE);

				if (FD_ISSET(server.socket, &write_fds)) {
					send(server.socket, &key, sizeof(key), 0);

					// if (send_to_peer(&server) != 0)
					// 	shutdown_properly(EXIT_FAILURE);
				}

				if (FD_ISSET(server.socket, &except_fds)) {
					printf("except_fds for server.\n");
					shutdown_properly(EXIT_FAILURE);
				}
			}
	}
	
	printf("And we are still waiting for clients' or stdin activity. You can type something to send:\n");

return (0);
}
 
// int Network::prepare_message(char *sender, char *data, message_t *message)
// {
// 	sprintf(message->sender, "%s", sender);
// 	sprintf(message->data, "%s", data);
// 	return (0);
// }
 
// int Network::print_message(message_t *message)
// {
// 	printf("Message: \"%s: %s\"\n", message->sender, message->data);
// 	return (0);
// }

// int Network::create_message_queue(int queue_size, message_queue_t *queue)
// {
// 	queue->data = (message_t *)calloc(queue_size, sizeof(message_t));
// 	queue->size = queue_size;
// 	queue->current = 0;
	
// 	return (0);
// }

// void Network::delete_message_queue(message_queue_t *queue)
// {
// 	free(queue->data);
// 	queue->data = NULL;
// }

// int Network::enqueue(message_queue_t *queue, message_t *message)
// {
// 	if (queue->current == queue->size)
// 	return (-1);
	
// 	memcpy(&queue->data[queue->current], message, sizeof(message_t));
// 	queue->current++;
	
// 	return (0);
// }

// int Network::dequeue(message_queue_t *queue, message_t *message)
// {
// 	if (queue->current == 0)
// 	return (-1);
	
// 	memcpy(message, &queue->data[queue->current - 1], sizeof(message_t));
// 	queue->current--;
	
// 	return (0);
// }

// int Network::dequeue_all(message_queue_t *queue)
// {
// 	queue->current = 0;
	
// 	return (0);
// }


int Network::delete_peer(peer_t *peer)
{
	close(peer->socket);
	// delete_message_queue(&peer->send_buffer);
	return (1);
}

// int Network::create_peer(peer_t *peer)
// {
// 	create_message_queue(MAX_MESSAGES_BUFFER_SIZE, &peer->send_buffer);
	
// 	peer->current_sending_byte   = -1;
// 	peer->current_receiving_byte = 0;
	
// 	return (0);
// }

char *Network::peer_get_addres_str(peer_t *peer)
{
	static char ret[INET_ADDRSTRLEN + 10];
	char peer_ipv4_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &peer->addres.sin_addr, peer_ipv4_str, INET_ADDRSTRLEN);
	sprintf(ret, "%s:%d", peer_ipv4_str, peer->addres.sin_port);
	
	return (ret);
}

// int Network::peer_add_to_send(peer_t *peer, message_t *message)
// {
// 	return (enqueue)(&peer->send_buffer, message);
// }

/* Receive message from peer and handle it with message_handler(). */
// int Network::receive_from_peer(peer_t *peer)
// {
	// printf("Ready for recv() from %s.\n", peer_get_addres_str(peer));
	
	// size_t len_to_receive;
	// ssize_t received_count;
	//size_t received_total = 0;
	// do {
	// Is completely received?
	// if (peer->current_receiving_byte >= sizeof(peer->receiving_buffer)) {
	// 	handle_received_message(&peer->receiving_buffer);
	// 	peer->current_receiving_byte = 0;
	// }
	
		// Count bytes to send.
		// len_to_receive = sizeof(peer->receiving_buffer) - peer->current_receiving_byte;
		// if (len_to_receive > MAX_SEND_SIZE)
		// 	len_to_receive = MAX_SEND_SIZE;
		
		// printf("Let's try to recv() %zd bytes... ", len_to_receive);
		// received_count = recv(peer->socket, (char *)&peer->receiving_buffer + peer->current_receiving_byte, len_to_receive, MSG_DONTWAIT);
		
		// recv(peer->socket, key, len_to_receive, MSG_DONTWAIT);
		
	// 	if (received_count < 0) {
	// 		if (errno == EAGAIN || errno == EWOULDBLOCK)
	// 			printf("peer is not ready right now, try again later.\n");
	// 		else {
	// 			perror("recv() from peer error");
	// 			return (-1);
	// 		}
	// 	} 
	// 	else if (received_count < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
	// 		break;
	// 	}
	// 	// If recv() returns( 0), it means that peer gracefully shutdown. Shutdown client.
	// 	else if (received_count == 0) {
	// 		printf("recv() 0 bytes. Peer gracefully shutdown.\n");
	// 		return (-1);
	// 	}
	// 	else if (received_count > 0) {
	// 		peer->current_receiving_byte += received_count;
	// 		//received_total += received_count;
	// 		//printf("recv() %zd bytes\n", received_count);
	// 	}
	// } while (received_count > 0);
	
	//printf("Total recv()'ed %zu bytes.\n", received_total);
// 	return (0);
// }

// int Network::send_to_peer(peer_t *peer)
// {
// 	printf("Ready for send() to %s.\n", peer_get_addres_str(peer));
	
// 	size_t len_to_send;
// 	ssize_t send_count;
// 	size_t send_total = 0;
// 	do {
// 	// If sending message has completely sent and there are messages in queue, why not send them?
// 	if (peer->current_sending_byte < 0 || peer->current_sending_byte >= sizeof(peer->sending_buffer)) {
// 		printf("There is no pending to send() message, maybe we can find one in queue... ");
// 		if (dequeue(&peer->send_buffer, &peer->sending_buffer) != 0) {
// 		peer->current_sending_byte = -1;
// 		printf("No, there is nothing to send() anymore.\n");
// 		break;
// 		}
// 		printf("Yes, pop and send() one of them.\n");
// 		peer->current_sending_byte = 0;
// 	}
	
// 	// Count bytes to send.
// 	len_to_send = sizeof(peer->sending_buffer) - peer->current_sending_byte;
// 	if (len_to_send > MAX_SEND_SIZE)
// 		len_to_send = MAX_SEND_SIZE;
	
// 	printf("Let's try to send() %zd bytes... ", len_to_send);
// 	send_count = send(peer->socket, (char *)&peer->sending_buffer + peer->current_sending_byte, len_to_send, 0);
// 	if (send_count < 0) {
// 		if (errno == EAGAIN || errno == EWOULDBLOCK) {
// 		printf("peer is not ready right now, try again later.\n");
// 		}
// 		else {
// 		perror("send() from peer error");
// 		return (-1);
// 		}
// 	}
// 	// we have read as many as possible
// 	else if (send_count < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
// 		break;
// 	}
// 	else if (send_count == 0) {
// 		printf("send()'ed 0 bytes. It seems that peer can't accept data right now. Try again later.\n");
// 		break;
// 	}
// 	else if (send_count > 0) {
// 		peer->current_sending_byte += send_count;
// 		send_total += send_count;
// 		printf("send()'ed %zd bytes.\n", send_count);
// 	}
// 	} while (send_count > 0);

// 	printf("Total send()'ed %zu bytes.\n", send_total);
// 	return (0);
// }

// common ---------------------------------------------------------------------

/* Reads from stdin and create new message. This message enqueues to send queueu. */
// int Network::read_from_stdin(char *read_buffer, size_t max_len)
// {
// 	memset(read_buffer, 0, max_len);
	
// 	ssize_t read_count = 0;
// 	ssize_t total_read = 0;
	
// 	do {
// 	read_count = read(STDIN_FILENO, read_buffer, max_len);
// 	if (read_count < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
// 		perror("read()");
// 		return (-1);
// 	}
// 	else if (read_count < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
// 		break;
// 	}
// 	else if (read_count > 0) {
// 		total_read += read_count;
// 		if (total_read > max_len) {
// 		printf("Message too large and will be chopped. Please try to be shorter next time.\n");
// 		fflush(STDIN_FILENO);
// 		break;
// 		}
// 	}
// 	} while (read_count > 0);
	
// 	size_t len = strlen(read_buffer);
// 	if (len > 0 && read_buffer[len - 1] == '\n')
// 	read_buffer[len - 1] = '\0';
	
// 	printf("Read from stdin %zu bytes. Let's prepare message to send.\n", strlen(read_buffer));

// 	return (0);
// }
 