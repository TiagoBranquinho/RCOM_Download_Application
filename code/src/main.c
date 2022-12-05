#include <stdio.h>
#include "auxiliar.h"

// TO DO
/* - unique use case: connect, login host, passive, get path, success (file saved in CWD) or un-success (indicating failing phase)
- challenging programming aspects: gethostbyname, sockets, control connection, passive, data connection */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s %s\n", argv[0], "ftp://[<user>:<password>@]<host>/<url-path>");
        return -1;
    }

    // parse command line arguments
    struct arguments args;
    if (parseArguments(&args, argv[1]) != 0) {
        return -1;
    }
    printf("User: %s\n", args.user);
    printf("Password: %s\n", args.password);
    printf("Host name: %s\n", args.host_name);
    printf("File path: %s\n", args.file_path);
    printf("File name: %s\n", args.file_name);

    struct ftp ftp;
    char command[MAX_IP_LENGTH];           // buffer to send commands
    char response[MAX_IP_LENGTH];    // buffer to read commands

    // get IP Address
    char ipAddress[MAX_IP_LENGTH];
    if (getIPAddress(ipAddress, args.host_name) < 0) {
        return -1;
    }
    // create and connect socket to server
    if ((ftp.control_socket_fd = createAndConnectSocket(ipAddress, FTP_PORT_NUMBER)) < 0) {
        printf("Error creating new socket\n");
        return -1;
    }

    // receive confirmation from server
    receiveFromControlSocket(&ftp, response, MAX_IP_LENGTH);

    // checking confirmation from server
    if (responseBuffer[0] == '2') {
        printf("Expecting username...\n\n");
    }
    else
    {
        printf("Error in conection...\n\n");
        return -1;
    }
}