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

// #include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "../inc/Snake.hpp"

/* Maximum bytes that can be send() or recv() via net by one call.
 * It's a good idea to test sending one byte by one.
 */
#define MAX_SEND_SIZE 100

/* Size of send queue (messages). */
#define MAX_MESSAGES_BUFFER_SIZE 10

#define SENDER_MAXSIZE 128
#define DATA_MAXSIZE 512

#define SERVER_IPV4_ADDR "127.0.0.1"
#define SERVER_LISTEN_PORT 33235

// peer -----------------------------------------------------------------------
typedef struct {
  char sender[SENDER_MAXSIZE];
  char data[DATA_MAXSIZE];
}  message_t;

typedef struct {
  int size;
  message_t *data;
  int current;
} message_queue_t;

typedef struct {
  int socket;
  struct sockaddr_in addres;
  
  /* Messages that waiting for send. */
  message_queue_t send_buffer;
  
  /* Buffered sending message.
   * 
   * In case we doesn't send whole message per one call send().
   * And current_sending_byte is a pointer to the part of data that will be send next call.
   */
  message_t sending_buffer;
  size_t current_sending_byte;
  
  /* The same for the receiving message. */
  message_t receiving_buffer;
  size_t current_receiving_byte;
} peer_t;

// message queue --------------------------------------------------------------


#define MAX_CLIENTS 10

#define NO_SOCKET -1

#define SERVER_NAME "server"

class Network
{

	bool serverBool;
	int listen_sock;

	peer_t connection;
	peer_t server;

	// char read_buffer[1024];
	int high_sock;

	fd_set read_fds;
	fd_set write_fds;
	fd_set except_fds;
	std::string server_ipv_str;

	void shutdown_properly(int code);

	int connect_server(peer_t *server);
	int start_listen_socket(int *listen_sock);
	int build_fd_setsCl(peer_t *server, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds);
	int build_fd_sets(fd_set *read_fds, fd_set *write_fds, fd_set *except_fds);
	int handle_new_connection();
	int close_client_connection(peer_t *client);
	
	void init();

	char *peer_get_addres_str(peer_t *peer);



public:

	int cycle(eKeyType *key);
	
	Network();
	Network(bool serv);
	Network(std::string ip);
	~Network();
	
};