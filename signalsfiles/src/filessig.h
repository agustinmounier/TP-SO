#define CLIENT_FILE_PATH "../../signalsfiles/clients/client_%ld"
#define SERVER_PID_FILE "../../signalsfiles/server_pid"

void communicate_with_server();
void readClientMessage();
void dealWithClient();
void user1_handler();
void user2_handler();