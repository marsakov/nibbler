#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "../inc/Snake.hpp"

#define SERVER_LISTEN_PORT 33235

// peer -----------------------------------------------------------------------

typedef struct {
  int socket;
  struct sockaddr_in addres;
} peer_t;

#define NO_SOCKET -1

class Network
{

	bool serverBool;
	int listen_sock;

	peer_t connection;
	peer_t server;

	int high_sock;

	fd_set read_fds;
	fd_set write_fds;
	fd_set except_fds;
	std::string server_ipv_str;

	void shutdown_properly(int code);

	int connect_server(peer_t *server);
	int start_listen_socket(int *listen_sock);
	int handle_new_connection();
	int close_client_connection(peer_t *client);
	
	void init();

	char *peer_get_addres_str(peer_t *peer);



public:

	int cycle(eKeyType *key, int *x, int *y);
	
	Network();
	Network(bool serv);
	Network(std::string ip);
	~Network();
	
};