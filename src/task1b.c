#include "util.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define SYS_EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define NEW_LINE '\n'

void print_if_debug_mode(int debug_mode, int call_id, int arg1, int return_code)
{
	if (debug_mode)
	{
		print_system_call(call_id, arg1, return_code);
	}
}

void print_system_call(int call_id, int arg1, int return_code){
	char* newline = "\n";
	char* buf[100];
	strcat(buf, "system call id: ");
	strcat(buf, itoa(call_id));
	strcat(buf, newline);
	strcat(buf, "first argument: ");
	strcat(buf, itoa(arg1));
	strcat(buf, newline);
	strcat(buf, "return code: ");
	strcat(buf, itoa(return_code));
	strcat(buf, newline);
	system_call(SYS_WRITE, STDERR, buf, strlen(buf));
}


int main(int argc, char **argv)
{
	int arg_index = 1;
	int debug_mode = 0;
	while (arg_index < argc)
	{
		if (!strcmp(argv[arg_index], "-D"))
		{
			debug_mode = 1;
			arg_index++;
		}
		else
		{
			arg_index++;
		}
		
	}
	
	
	int word_count = 0;
	char* new_line = "\n";
	int end_space = 0;
	char *buf[1];
	int bytes_read = 0;
	int return_code;
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

	return_code = system_call(SYS_WRITE, STDOUT, itoa(word_count), 1);
	return_code = system_call(SYS_WRITE, STDOUT, new_line, strlen(new_line));
	print_if_debug_mode(debug_mode, SYS_READ, STDIN, bytes_read);
}
