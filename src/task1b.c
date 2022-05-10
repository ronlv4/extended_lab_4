#include "util.h"

#include <fcntl.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5

int system_call();

void print_system_call(int call_id, int arg1, int return_code)
{
		system_call(SYS_WRITE, STDERR, "\nsystem call id: ", strlen("\nfirst argument: "));
		system_call(SYS_WRITE, STDERR, itoa(call_id), strlen(itoa(call_id)));
		system_call(SYS_WRITE, STDERR, "\nfirst argument: ", strlen("\nfirst argument: "));
		system_call(SYS_WRITE, STDERR, itoa(arg1), strlen(itoa(arg1)));
		system_call(SYS_WRITE, STDERR, "\nreturn code: ", strlen("\nreturn code: "));
		system_call(SYS_WRITE, STDERR, itoa(return_code), strlen(itoa(return_code)));
		system_call(SYS_WRITE, STDERR, "\n\n", strlen("\n\n"));
}

void print_if_debug_mode(int debug_mode, int call_id, int arg1, int return_code, int out_name)
{
	if (debug_mode)
	{
		print_system_call(call_id, arg1, return_code);
	}
}
int main(int argc, char **argv)
{
	int arg_index = 1;
	int debug_mode = 0;
	int output_fd = STDOUT;
	int input_fd = STDIN;
	int fp;
	int fout = 0;
	while (arg_index < argc)
	{
		if (!strcmp(argv[arg_index], "-D"))
		{
			debug_mode = 1;
		}
		else if (!strncmp(argv[arg_index], "-i", 2))
		{
			input_fd = system_call(SYS_OPEN, argv[arg_index] + 2, O_RDONLY, 0777);
            print_if_debug_mode(debug_mode, SYS_OPEN, argv[arg_index] + 2, input_fd)
		}
		else if (!strncmp(argv[arg_index], "-o", 2))
		{
			output_fd = system_call(SYS_OPEN, argv[arg_index] + 2, O_WRONLY | O_TEMPORARY, 0777);
			print_if_debug_mode(debug_mode, SYS_OPEN, output_fd, 1, fout);
		}
		arg_index++;
	}
	if (input_fd)
	{
		print_if_debug_mode(debug_mode, SYS_OPEN, output_fd, 1, fout);
	}
	print_if_debug_mode(debug_mode, SYS_WRITE, output_fd, 1, fout);
	int word_count = 0;
	char *new_line = "\n";
	char *buf[1];
	int bytes_read = 0;
	int return_code;
	if (input_fd == 1)
	{
		bytes_read = system_call(SYS_READ, fp, buf, 1);
		print_if_debug_mode(debug_mode, SYS_READ, input_fd, bytes_read, fout);
	}
	else
	{
		bytes_read = system_call(SYS_READ, input_fd, buf, 1);
		print_if_debug_mode(debug_mode, SYS_READ, input_fd, bytes_read, fout);
	}
	while (bytes_read != 0)
	{
		while (buf[0] == ' ' && strcmp(buf, new_line))
		{
			if (input_fd == 1)
			{
				bytes_read = system_call(SYS_READ, fp, buf, 1);
				print_if_debug_mode(debug_mode, SYS_READ, input_fd, bytes_read, fout);
			}
			else
			{
				bytes_read = system_call(SYS_READ, input_fd, buf, 1);
				print_if_debug_mode(debug_mode, SYS_READ, input_fd, bytes_read, fout);
			}
		}
		if (!strcmp(buf, new_line))
		{
			break;
		}
		while (buf[0] != ' ' && bytes_read != 0 && strcmp(buf, new_line))
		{
			if (input_fd == 1)
			{
				bytes_read = system_call(SYS_READ, fp, buf, 1);
				print_if_debug_mode(debug_mode, SYS_READ, input_fd, bytes_read, fout);
			}
			else
			{
				bytes_read = system_call(SYS_READ, input_fd, buf, 1);
				print_if_debug_mode(debug_mode, SYS_READ, input_fd, bytes_read, fout);
			}
		}
		word_count++;
	}
	if (fout == 0)
	{
		return_code = system_call(SYS_WRITE, output_fd, itoa(word_count), 1);
		print_if_debug_mode(debug_mode, SYS_WRITE, output_fd, return_code, fout);
		return_code = system_call(SYS_WRITE, output_fd, new_line, strlen(new_line));
		print_if_debug_mode(debug_mode, SYS_WRITE, output_fd, return_code, fout);
	}
	else
	{
		return_code = system_call(SYS_WRITE, fout, itoa(word_count), 1);
		print_if_debug_mode(debug_mode, SYS_WRITE, fout, return_code, fout);
		return_code = system_call(SYS_WRITE, fout, new_line, strlen(new_line));
		print_if_debug_mode(debug_mode, SYS_WRITE, fout, return_code, fout);
	}
}