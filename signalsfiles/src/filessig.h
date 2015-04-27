#ifndef _filessig_
#define _filessig_

#define CLIENT_FILE_PATH "../tmp/ca/%ld"
#define SERVER_FILE_PATH "../tmp/sa/%ld"
#define CA_PATH "../tmp/ca"
#define SA_PATH "../tmp/sa"
#define CA_PATH_LENGTH  9
#define SERVER_PID_FILE "./server_pid"

void communicate_with_server();
void readClientMessage();
void dealWithClient();
void user1_handler();
void user2_handler();
void onSigInt(int s);

#endif
