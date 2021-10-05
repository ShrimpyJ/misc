/* Simple http server taken from github.com/blghns/Simple-Web-Server-in-C/ */
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <netinet/in.h>

#define ERROR_FILE     0
#define REG_FILE       1
#define DIRECTORY      2

int get_file_type(char *path)
{
	struct stat buf;

	if (stat(path, &buf) != 0){
		perror("Failed to identify file");
		fprintf(stderr, "[ERROR] stat() on file: |%s|\n", path);
		fflush(stderr);
		return ERROR_FILE;
	}

	printf("Path: %s\nBytes: %li\n", path, buf.st_size);

	if (S_ISREG(buf.st_mode)) return REG_FILE;
	if (S_ISDIR(buf.st_mode)) return DIRECTORY;

	return ERROR_FILE;
}

void extract_request(char *req, char *buf)
{
	int i, j;

	i = 0;
	j = 5;
	while(buf[j] != 32){
		req[i] = buf[j];
		i++;
		j++;
	}
	req[i] = '\0';
}

void send_data(char *file, int sock, char *webdir)
{
	int handle;
	char path[256];
	char header[1024];
	ssize_t s;
	char buffer[1024];
	int file_size;
	char *file_type;
	char *extension;
	int send_len;
	int send_buf;

	/* Build full path to file */
	sprintf(path, "%s/%s", webdir, file);

	/* If file is directory, append 'index.html' file to end of path */
	file_type = get_file_type(path);
	if (file_type == DIRECTORY) sprintf(path, "%s%s", path, "index.html");

	send_len = strlen(file);
	if (send_len > 3) extension = &file[send_len-3];
	else extension = "html";

	if ((handle = open(path, O_RDONLY)) == -1){
		perror(file);
		exit(1);
	}
	file_size = lseek(handle, (off_t)0, SEEK_END);
	lseek(handle, (off_t)0, SEEK_SET);

	if (file_type == DIRECTORY || file_type == REG_FILE){
		if (!strncmp(extension, "pdf", 3)){
			sprintf(header, "HTTP/1.1 200 OK "
                      "Content-length: %d "
                      "Content-type: application/pdf\n\n", file_size);
		}
		else{
			sprintf(header, "HTTP/1.0 200 OK\r\n"
                      "Content-type: text/html\r\n"
                      "Content-length: %d\r\n\r\n", file_size);
		}
	}
	else{
		sprintf(header, "HTTP/1.1 400 Bad Request\r\n"
                    "Content-length: %d\r\n"
                    "Content-type: text/html\r\n\r\n", file_size);
	}

	if (write(sock, header, strlen(header)) == -1){
		perror("Error writing header");
		exit(1);
	}

	send_buf = 0;
	do{
		send_buf = send_buf + 1024;
		if ((s = read(handle, buffer, 1024)) == -1){
			perror("Error reading buffer");
			exit(1);
		}
		if ((write(sock, buffer, s)) == -1){
			perror("Error writing file");
			exit(1);
		}
	} while(send_buf <= file_size);

	close (handle);
}

int main(int argc, char **argv)
{
	pid_t pid;
	int sockFD;
	int newsockFD;
	int port;
	char web_dir[128];
	socklen_t client_addr_len;
	struct sockaddr_in server_addr, client_addr;
	char request[256];
	char t[128];
	int backlog;

	if (argc != 3){
		fprintf(stderr, "USAGE: %s <port> <website directory>\n", argv[0]);
		exit(1);
	}

	port = atoi(argv[1]);
	strcpy(web_dir, argv[2]);

	if ((pid = fork()) < 0){
		perror("Cannot fork for daemon");
		exit(1);
	}

	else if (pid != 0){
		sprintf(t, "echo %d > %s.pid\n", pid, argv[0]);
		system(t);
		exit(1);
	}

	/* Create socket, bind it, listen. Used to communicate between client/server */
	if ((sockFD = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Error creating socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;   /* Internet domain */
	server_addr.sin_addr.s_addr = INADDR_ANY;   /* Local machine IP */
	server_addr.sin_port = htons(port);
	if ((bind(sockFD, (struct sockaddr*) &server_addr, sizeof(server_addr))) == -1){
		perror("Error binding socket");
		exit(1);
	}

	backlog = 5;
	if((listen(sockFD, backlog)) == -1){
		perror("Error listening");
		exit(1);
	}

	signal(SIGCHLD, SIG_IGN);   /* Prevent zombie processes */

	/* Get size of client_addr */
	client_addr_len = sizeof(client_addr);

	/* Accept new connection and fork.
	   If child, process request and exit.
		 If parent, close socket and come back to accept another connection. */
	while(1){
		if((newsockFD = accept(sockFD, (struct sockaddr *) &client_addr, &client_addr_len)) == -1){
			perror("Error accepting connection");
			exit(1);
		}

		if ((pid = fork()) < 0){
			perror("Error forking child process");
			exit(1);
		}
		else if (pid == 0){
			int bytes;
			char buf[1024];
			char ref[1024];

			close(sockFD);
			memset(buf, 0, 1024);
			memset(ref, 0, 1024);

			if ((read(newsockFD, ref, 1024)) == -1){
				perror("Error reading client request");
			}
			bytes = 0;
			while(ref[bytes] != '\0'){
				buf[bytes] = ref[bytes];
				bytes++;
			}

			printf("Client request: \n%s\n", buf);
			extract_request(request, buf);
			printf("File requested: |%s|\n", request);
			fflush(stdout);

			/* Read file and send to client */
			send_data(request, newsockFD, web_dir);
			shutdown(newsockFD, 1);
			close(newsockFD);
			exit(0);
		}
		else{
			close(newsockFD);
		}
	}
}
