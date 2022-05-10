#include "util.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define SYS_EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6

void check_free_mem()
{
	char* buf[500];
	system_call(SYS_WRITE, STDERR, itoa(1),1);
	system_call(0x5b, buf, 500);
	system_call(SYS_WRITE, STDERR, itoa(2), 1);
}


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
	system_call(0x5b, buf, 100);
}


int main(int argc, char **argv)
{
	int arg_index = 1;
	int debug_mode = 0;
	char * inputFileName;
	int inputFd = STDIN;
	int outputFd = STDOUT;
	char * outputFileName;
	while (arg_index < argc)
	{
		if (!strcmp(argv[arg_index], "-D"))
		{
			debug_mode = 1;
			arg_index++;
		}
		else if(argv[arg_index][1] == 'i')
		{
			inputFileName = argv[arg_index] + 2;
			inputFd = system_call(SYS_OPEN, inputFileName, O_RDONLY);
			arg_index++;
		}
		else if(argv[arg_index][1] == 'o')
		{
			outputFileName = argv[arg_index] + 2;
			outputFd = system_call(SYS_OPEN, inputFileName, O_RDWR | O_CREAT);
			arg_index++;
		}
		else
		{
			arg_index++;
		}
		
	}

	system_call(SYS_WRITE, STDOUT, itoa(debug_mode), 1);

	int word_count = 0;
	char* new_line = "\n";
	int end_space = 0;
	char *buf[1];
	int bytes_read = 0;
	int return_code;
	bytes_read = system_call(SYS_READ, inputFd, buf, 1);
	while (bytes_read != 0){
		while (buf[0] == ' ' && strcmp(buf, new_line))
		{
			bytes_read = system_call(SYS_READ, inputFd, buf, 1);
			
		}
		if (!strcmp(buf, new_line))
		{
			break;
		}
		
		while (buf[0] != ' ' && bytes_read != 0 && strcmp(buf, new_line))
		{
			bytes_read = system_call(SYS_READ, STDIN, buf, 1);
			print_if_debug_mode(debug_mode, SYS_READ, inputFd, bytes_read);


		}
		word_count++;
	}

	return_code = system_call(SYS_WRITE, outputFd, itoa(word_count), 1);
	return_code = system_call(SYS_WRITE, outputFd, new_line, strlen(new_line));

}
