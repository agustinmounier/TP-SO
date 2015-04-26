#ifndef _filessig_
#define _filessig_

#define CLIENT_FILE_PATH "../tmp/client_%ld"
#define SERVER_PID_FILE "./server_pid"

void communicate_with_server();
void readClientMessage();
void dealWithClient();
void user1_handler();
void user2_handler();

#endif