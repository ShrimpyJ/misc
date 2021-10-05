#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

void print_depth(int depth)
{
	int i;

	for (i = 0; i < depth; i++){
		printf("_");
	}
}

void explore_dir(const char *d_name, int depth)
{
	DIR *dir;
	struct dirent *entry;
	struct stat st;

	if ((dir = opendir(d_name)) == NULL){
		fprintf(stderr, "error: could not open directory %s\n", d_name);
		exit(1);
	}

	while(entry = readdir(dir)){
		if (strcmp(entry->d_name, "." ) == 0) continue;
		if (strcmp(entry->d_name, "..") == 0) continue;
		stat(entry->d_name, &st);
		print_depth(depth);
		printf("%s\n", entry->d_name);
		if (S_ISDIR(st.st_mode)){
			printf("DIRECTORY '%s' FOUND\n", entry->d_name);
			explore_dir(entry->d_name, depth+1);
		}
	}

	closedir(dir);
}

int main(int argc, char **argv)
{
	int depth;

	explore_dir(".", 0);

	return 0;
}
