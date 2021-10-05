#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define START_CHECK     5
#define SONG_CHECK      5
#define ARTIST_CHECK    7
#define ALBUM_CHECK     6
#define YEAR_CHECK      5
#define TUNING_CHECK    7
#define SML_BAR        36
#define MED_BAR        72
#define LRG_BAR       108
#define NOTE_SEP      ","
#define W_L            31
#define H_L            15
#define Q_L             7
#define E_L             4
#define S_L             1
#define T_L             1
#define X_L             1

typedef struct header
{
	char *song;
	char *artist;
	char *album;
	char *year;
	char *tuning;
	int isong, iartist, ialbum, iyear, ituning; /* Bools to check if info exists */
	int num_strings;
	char strings[8][3];
	int start_line;
} Header;

typedef struct note
{
	char fret[5];
	int duration;
	int string;
} Note;

typedef struct measure
{
	int wc, hc, qc, ec, sc, tc, xc;
	char *w, *h, *q, *e, *s, *t, *x;
	int num_strings;
	int start_line;
	int num_notes;
	int total_duration;
	Note **notes;
	char tunings[8][3];
	char **strings;
} Measure;

char **read_file(FILE *f, int *f_items)
{
	char buffer[2];
	char *str;
	char *token;
	char **ret;
	int num_lines;
	int size;
	int i;
	int len;

	/* Get size of file first */
	size = 0;
	while ((fread(&buffer, 1, 1, f)) != 0) size++;

	/* Create string of entire file to be delimited later */
	str = malloc(sizeof(char) * size + 4);
	i = num_lines = 0;
	fseek(f, 0, SEEK_SET);
	while ((fread(&buffer, 1, 1, f)) != 0){
		str[i] = buffer[0];
		if (str[i] == '\n') num_lines++;
		i++;
	}

	/* Delimit file by newline */
	ret = (char **) calloc(num_lines+1, sizeof(char*));
	i = 0;
	token = strtok(str, "\n");
	len = strlen(token);
	while (token != NULL){
		len = strlen(token);
		ret[i] = (char *) calloc(len, sizeof(char));
		memcpy(ret[i], token, len);
		token = strtok(NULL, "\n");
		i++;
	}
	free(str);
	free(token);

	*f_items = i;

	return ret;
}

char *copy_info(char *info, int start)
{
	int len;
	char *ret;
	int i;

	i = 0;
	while (info[start+i] == ' ') i++;   /* Strip out any beginning whitespace */
	len = strlen(info);
	ret = calloc(1, len+1);
	memcpy(ret, info+start+i, len-start-i);

	return ret;
}

int parse_header(char **arr, int items, Header *h)
{
	int i, j;
	char *str;

	h->isong = h->iartist = h->ialbum = h->iyear = h->ituning = 0;
	for (i = 0; i < items; i++){
		/* Make info label lowercase for case insensitivity */
		for (j = 0; j < strlen(arr[i]); j++){
			if (arr[i][j] >= 'A' && arr[i][j] <= 'Z') arr[i][j] = arr[i][j] + ' ';
			if (arr[i][j] == ':') break;
		}

		/* Check for info labels and add label to header if exists */
		if (strncmp("start", arr[i], START_CHECK) == 0){
			h->start_line = i+1;
			break;
		}
		else if (strncmp("song:", arr[i], SONG_CHECK) == 0){
			h->song = copy_info(arr[i], SONG_CHECK);
			h->isong = 1;
		}
		else if (strncmp("artist:", arr[i], ARTIST_CHECK) == 0){
			h->artist = copy_info(arr[i], ARTIST_CHECK);
			h->iartist = 1;
		}
		else if (strncmp("album:", arr[i], ALBUM_CHECK) == 0){
			h->album = copy_info(arr[i], ALBUM_CHECK);
			h->ialbum = 1;
		}
		else if (strncmp("year:", arr[i], YEAR_CHECK) == 0){
			h->year = copy_info(arr[i], YEAR_CHECK);
			h->iyear = 1;
		}
		else if (strncmp("tuning:", arr[i], TUNING_CHECK) == 0){
			h->tuning = copy_info(arr[i], TUNING_CHECK);
			h->ituning = 1;
		}
	}
}

void parse_tuning(Header *h)
{
	int i, j;
	int num_strings;
	char string[3];
	int length;

	memset(h->strings, '.', sizeof(h->strings));
	num_strings = length = 0;
	for (i = 0; i < strlen(h->tuning); i++){
		if (h->tuning[i] >= 'a' && h->tuning[i] <= 'g'){
			length = 0;
			h->tuning[i] = h->tuning[i] - ' ';
			h->strings[num_strings][length] = h->tuning[i];
			num_strings++;
			length++;
		}
		else if (h->tuning[i] >= 'A' && h->tuning[i] <= 'G'){
			length = 0;
			h->strings[num_strings][length] = h->tuning[i];
			num_strings++;
			length++;
		}
		else if (h->tuning[i] == '#'){
			if (length == 0){
				fprintf(stderr, "error: tuning '%s' contains bad character '%c'\n", h->tuning, h->tuning[i]);
				exit(1);
			}
			num_strings--;
			h->strings[num_strings][length] = h->tuning[i];
			num_strings++;
			length++;
		}
		else if (h->tuning[i] == '_'){
			if (length == 0){
				fprintf(stderr, "error: tuning '%s' contains bad character '%c'\n", h->tuning, h->tuning[i]);
				exit(1);
			}
			h->tuning[i] = 'b';
			num_strings--;
			h->strings[num_strings][length] = h->tuning[i];
			num_strings++;
			length++;
		}
		else{
			fprintf(stderr, "error: tuning '%s' contains bad character '%c'\n", h->tuning, h->tuning[i]);
			exit(1);
		}

		if (length > 2){
			fprintf(stderr, "error: tuning '%s' contains bad character '%c'\n", h->tuning, h->tuning[i]);
			exit(1);
		}
	}

	for (i = 0; i < num_strings; i++){
		for (j = 0; j < strlen(h->strings[i]); j++){
			if (h->strings[i][j] == '.'){
				h->strings[i][j] = '\0';
				break;
			}
		}
	}

	h->num_strings = num_strings;
}

void print_header(Header *h)
{
	if (h->isong) printf("Song: %s\n", h->song);
	if (h->iartist) printf("Artist: %s\n", h->artist);
	if (h->ialbum) printf("Album: %s\n", h->album);
	if (h->iyear) printf("Year: %s\n", h->year);
	if (h->ituning) printf("Tuning: %s\n", h->tuning);
	printf("\n\n\n");
}

int note_duration(char *input, int index, int fret_l)
{
	int i;
	int len;

	i = index;
	len = strlen(input);
	switch (input[i]){
		case 'w':
			return (len == 1) ? W_L : W_L-1;
		case 'h':
			return (len == 1) ? H_L : H_L-1;
		case 'q':
			return (len == 1) ? Q_L : Q_L-1;
		case 'e':
			return (len == 1) ? E_L : E_L-1;
		case 's':
			return S_L;
		case 't':
			return T_L;
		case 'x':
			return X_L;
		default:
			fprintf(stderr, "error: invalid note duration '%c'\n", input[i]);
			exit(1);
	}
}

int note_fret(char *input, Note *n)
{
	int i, j;
	char fret[5];

	i = 2;
	j = 0;
	n->fret[0] = '\0';
	while (input[i] >= '0' && input[i] <= '9'){
		n->fret[j] = input[i];
		i++;
		j++;
	}
	n->fret[j] = '\0';
	
	if (n->fret[0] == '\0'){
		fprintf(stderr, "error: no fret given\n");
		exit(1);
	}
	return i;
}

Note *note_analyze(char *input, int num_strings)
{
	Note *n;
	int i, j;
	int len;
	int duration;

	/* Get string and check that it's valid or a rest */
	n = malloc(sizeof(Note *)+5);
	if (input[0] == 'r'){
		n->fret[0] = '-';
		n->fret[1] = '\0';
		n->duration = note_duration(input, 1, strlen(n->fret));
		return n;
	}
	else if (input[0]-'0' < 0 || input[0]-'0' > num_strings){
		fprintf(stderr, "error: invalid string '%c'\n", input[0]);
		exit(1);
	}
	else{
		n->string = input[0] - '0';
	}

	if (input[1] != '.' && input[0] != 'r'){
		fprintf(stderr, "error: missing '.' after string\n");
		exit(1);
	}

	/* Get fret */
	i = note_fret(input, n);

	/* Get duration */
	n->duration = note_duration(input, i, strlen(n->fret));

	return n;
}

void measure_print(Measure *m)
{
	int i;
	int space;

	for (i = 0; i < m->num_strings; i++){
		if (strlen(m->tunings[i]) == 2){ space = 1; break; }
	}
	for (i = m->num_strings-1; i >= 0; i--){
		if (space) printf("%-2s", m->tunings[i]);
		else printf("%s", m->tunings[i]);
		printf("%s\n", m->strings[i]);
	}
	printf("\n\n");
}

void measure_build(Measure *m)
{
	int i, j, k;
	Note *n;

	m->strings = calloc(m->num_strings, sizeof(char *));
	for (i = 0; i < m->num_strings; i++){
		m->strings[i] = calloc(m->total_duration, sizeof(char));
		strcat(m->strings[i], "|-");
	}

	for (i = 0; i < m->num_notes; i++){
		n = m->notes[i];
		strcat(m->strings[n->string-1], n->fret);
		for (j = 0; j < m->num_strings; j++){
			if (j == n->string-1) continue;
			for (k = 0; k < strlen(n->fret); k++){
				strcat(m->strings[j], "-");
			}
		}
		for (j = 0; j < n->duration; j++){
			for (k = 0; k < m->num_strings; k++){
				strcat(m->strings[k], "-");
			}
		}
	}

	for (i = 0; i < m->num_strings; i++) strcat(m->strings[i], "|");
}

void measure_free(Measure *m)
{
	int i;

	for (i = 0; i < m->num_strings; i++){
		free(m->strings[i]);
	}
	free(m->strings);
	for (i = 0; i < m->num_notes; i++){
		free(m->notes[i]);
	}
	free(m->notes);
}

void measure_analyze(Measure *m, char **arr)
{
	int i, j;
	Note *n;
	char *token;

	i = m->start_line;
	while (strncmp(arr[i], "end", 3) != 0){
		while(strlen(arr[i]) < 2) i++;
		if (arr[i][0] == '#'){ i++; continue; }
	
		m->num_notes = 0;
		m->total_duration = 0;
		token = strtok(arr[i], NOTE_SEP);
		m->notes= calloc(1, sizeof(Note *));
		while (token != NULL){
			n = note_analyze(token, m->num_strings);
			m->num_notes++;
			m->notes = realloc(m->notes, sizeof(Note *)*m->num_notes);
			m->notes[m->num_notes-1] = n;
			token = strtok(NULL, NOTE_SEP);
		}
		for (j = 0; j < m->num_notes; j++){
			m->total_duration += m->notes[j]->duration;
		}
		m->total_duration *= 5;
		measure_build(m);
		measure_print(m);
		measure_free(m);
		free(token);
		i++;
	}
}

void measure_construct(Measure *m, Header *h)
{
	int i;

	m->wc = m->hc = m->qc = m->ec = m->sc = m->tc = m->xc = 0;
	m->num_strings = h->num_strings;
	m->start_line = h->start_line;
	m->total_duration = 0;
	for (i = 0; i < m->num_strings; i++){
		memcpy(m->tunings[i], h->strings[i], strlen(h->strings[i]));
	}
}

int main(int argc, char **argv)
{
	FILE *fp;
	char **arr;
	int f_items;
	char *file;
	int len;
	Header *h;
	Measure *m;
	int i;
	int is_file;

	/* Error check */
	if (argc == 1){
		is_file = 0;
	}
	else if (argc == 2){
		is_file = 1;

	}
	else{
		fprintf(stderr, "usage: tabr [tabr_file]\n");
		exit(1);
	}

	if (is_file){    /* Handle input file if given as arg */
		file = argv[1];
		len = strlen(file);
		if (file[len-1] != 'r' && file[len-2] != 'b' && file[len-3] != 'a' &&
		    file[len-4] != 't' && file[len-5] != '.'){
			fprintf(stderr, "error: file must be of type .tabr\n");
			exit(1);
		}

		/* Read file into array of lines */
		if ((fp = fopen(file, "r")) == 0){
			perror(file);
			exit(1);
		}
		arr = read_file(fp, &f_items);
		fclose(fp);
	}
	else{
	}

	h = malloc(sizeof(struct header)+5);

	parse_header(arr, f_items, h);

	if (!h->ituning){    /* Exit if no tuning */
		fprintf(stderr, "error: tuning must be specified in file header\n");
		exit(1);
	}

	parse_tuning(h);
	print_header(h);

	m = malloc(sizeof(struct measure)+5);
	measure_construct(m, h);

	measure_analyze(m, arr);

	/* Free */
	if (h->isong) free(h->song);
	if (h->iartist) free(h->artist);
	if (h->ialbum) free(h->album);
	if (h->iyear) free(h->year);
	if (h->ituning) free(h->tuning);
	free(h);
	for (i = 0; i < f_items+1; i++) free(arr[i]);
	free(arr);
	free(m);

	return 0;
}
