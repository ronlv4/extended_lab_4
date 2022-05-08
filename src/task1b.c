#include "util.h"

#define STDIN 0
#define STDOUT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define NEW_LINE '\n'
int main(int argc, char **argv)
{
	int word_count = 0;
	char* new_line = "\n";
	int end_space = 0;
	char *buf[1];
	int bytes_read = 0;
	bytes_read = system_call(SYS_READ, STDIN, buf, 1);
	while (bytes_read != 0){
		while (buf[0] == ' ' && strcmp(buf, new_line))
		{
			bytes_read = system_call(SYS_READ, STDIN, buf, 1);
		}
		if (!strcmp(buf, new_line))
		{
			break;
		}
		
		while (buf[0] != ' ' && bytes_read != 0 && strcmp(buf, new_line))
		{
			bytes_read = system_call(SYS_READ, STDIN, buf, 1);
		}
		word_count++;
	}

	system_call(SYS_WRITE, STDOUT, itoa(word_count), 1);
	system_call(SYS_WRITE, STDOUT, new_line, strlen(new_line));

}
