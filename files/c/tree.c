#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>

void print_depth(int depth)
{
	int i;


	for (i = 0; i < depth*4; i++){
    if (i % 4 == 0) printf("│");
		else printf(" ");
	}
  printf("├── ");
}

void explore_dir(const char *d_name, int depth)
{
	DIR *dir;
	struct dirent *entry;
	struct stat st;
  char *path;
  char *name;
  int len;

  /* Construct relative path name */
  path = calloc(strlen(d_name)+80, sizeof(char));
  strcat(path, d_name);
  len = strlen(path);

	if ((dir = opendir(path)) == NULL){
		fprintf(stderr, "error: could not open directory %s\n", d_name);
		exit(1);
	}

	while(entry = readdir(dir)){
    if (entry->d_name[0] == '.') continue;
    name = calloc(len+strlen(entry->d_name)+3, sizeof(char));
    //strcat(name, path);
    strncpy(name, path, len);
    //strcat(name, "/");
    strncpy(name+len, "/", 1);
    //strcat(name, entry->d_name);
    strncpy(name+len+1, entry->d_name, strlen(entry->d_name));
		if (lstat(name, &st) != 0){
      perror(name);
      exit(1);
    }
		print_depth(depth);
		printf("%s\n", entry->d_name);
		if (S_ISDIR(st.st_mode)){
			explore_dir(name, depth+1);
		}
    free(name);
	}

  free(path);
	closedir(dir);
}

int main(int argc, char **argv)
{
	int depth;

  printf(".\n");
	explore_dir(".", 0);

	return 0;
}
