#include "util.h"

#include <fcntl.h>



#define STDIN 0

#define STDOUT 1

#define STDERR 2

#define SYS_EXIT 1

#define SYS_READ 3

#define SYS_WRITE 4

#define NEW_LINE '\n'



void check_free_mem()

{

	char* buf[500];

	system_call(SYS_WRITE, STDERR, itoa(1),1);

	system_call(0x5b, buf, 500);

	system_call(SYS_WRITE, STDERR, itoa(2), 1);

}





void print_if_debug_mode(int debug_mode, int call_id, int arg1, int return_code,int out_name)

{

	if (debug_mode)

	{

		print_system_call(call_id, arg1, return_code,out_name);

	}

}



void print_system_call(int call_id, int arg1, int return_code,int out_name){

	char* newline = "\n";

	char* buf[100];

	if(out_name==0)

	{

	system_call(SYS_WRITE, STDOUT,"\nsystem call id: ", strlen("\nfirst argument: "));

	system_call(SYS_WRITE, STDOUT,itoa(call_id), strlen(itoa(call_id)));

	system_call(SYS_WRITE, STDOUT,"\nfirst argument: ", strlen("\nfirst argument: "));

	system_call(SYS_WRITE, STDOUT,itoa(arg1), strlen(itoa(arg1)));



	system_call(SYS_WRITE, STDOUT,"\nreturn code: ", strlen("\nreturn code: "));

	system_call(SYS_WRITE, STDOUT,itoa(return_code), strlen(itoa(return_code)));

	system_call(SYS_WRITE, STDOUT,"\n\n", strlen("\n\n"));

	}

	else

	{

	system_call(SYS_WRITE, out_name,"\nsystem call id: ", strlen("\nfirst argument: "));

	system_call(SYS_WRITE, out_name,itoa(call_id), strlen(itoa(call_id)));

	system_call(SYS_WRITE, out_name,"\nfirst argument: ", strlen("\nfirst argument: "));

	system_call(SYS_WRITE, out_name,itoa(arg1), strlen(itoa(arg1)));



	system_call(SYS_WRITE, out_name,"\nreturn code: ", strlen("\nreturn code: "));

	system_call(SYS_WRITE, out_name,itoa(return_code), strlen(itoa(return_code)));

	system_call(SYS_WRITE, out_name,"\n\n", strlen("\n\n"));

	}



}





int main(int argc, char **argv)

{

	int arg_index = 1;

	int debug_mode = 0;

	int outfile = 0;

	int infile = 0;

	char *file_in;

	char *out_file;

	int fp;

	int fout=0;

	file_in = argv[arg_index]+2;

	while (arg_index < argc)

	{

		if (!strcmp(argv[arg_index], "-D"))

		{

			debug_mode = 1;

		}

		else if (!strncmp(argv[arg_index],"-i",2))

		{

			infile=1;

			file_in = argv[arg_index]+2;

			fp = system_call(5,file_in,0,0777);



		}



		else if (!strncmp(argv[arg_index],"-o",2))

		{

			outfile=1;

			out_file = argv[arg_index]+2;

			fout = system_call(5,out_file,1|64,0777);

			print_if_debug_mode(debug_mode, 5, STDOUT,1,fout);





		}

			arg_index++;

		

	}

	if(infile)

	{

		print_if_debug_mode(debug_mode, 5, STDOUT,1,fout);



	}



	print_if_debug_mode(debug_mode, SYS_WRITE, STDOUT,1,fout);



	int word_count = 0;

	char* new_line = "\n";

	int end_space = 0;

	char *buf[1];

	int bytes_read = 0;

	int return_code;

	int out = 0;

	int in = 0;

	if(infile=1)

	{

		bytes_read = system_call(SYS_READ, fp, buf, 1);

		print_if_debug_mode(debug_mode, SYS_READ, STDIN, bytes_read,fout);

	}

	else

	{

		bytes_read = system_call(SYS_READ, STDIN, buf, 1);

		print_if_debug_mode(debug_mode, SYS_READ, STDIN, bytes_read,fout);

	}



	while (bytes_read != 0){

		while (buf[0] == ' ' && strcmp(buf, new_line))

		{

			if(infile=1)

			{

				bytes_read = system_call(SYS_READ, fp, buf, 1);

				print_if_debug_mode(debug_mode, SYS_READ, STDIN, bytes_read,fout);



			}

			else

			{

				bytes_read = system_call(SYS_READ, STDIN, buf, 1);

				print_if_debug_mode(debug_mode, SYS_READ, STDIN, bytes_read,fout);

			}



			

		}

		if (!strcmp(buf, new_line))

		{

			break;

		}

		while (buf[0] != ' ' && bytes_read != 0 && strcmp(buf, new_line))

		{

			

			if(infile=1)

			{

				bytes_read = system_call(SYS_READ, fp, buf, 1);

				print_if_debug_mode(debug_mode, SYS_READ, STDIN, bytes_read,fout);



			}

			else

			{

				bytes_read = system_call(SYS_READ, STDIN, buf, 1);

				print_if_debug_mode(debug_mode, SYS_READ, STDIN, bytes_read,fout);

			}





		}

		word_count++;



	}

	if(fout==0)

	{

	return_code = system_call(SYS_WRITE, STDOUT, itoa(word_count), 1);

	print_if_debug_mode(debug_mode, SYS_WRITE, STDOUT, return_code,fout);



	return_code = system_call(SYS_WRITE, STDOUT, new_line, strlen(new_line));

	print_if_debug_mode(debug_mode, SYS_WRITE, STDOUT, return_code,fout);

	}

	else

	{

		return_code = system_call(SYS_WRITE, fout, itoa(word_count), 1);

		print_if_debug_mode(debug_mode, SYS_WRITE, fout, return_code,fout);



		return_code = system_call(SYS_WRITE, fout, new_line, strlen(new_line));

		print_if_debug_mode(debug_mode, SYS_WRITE, fout, return_code,fout);



	}

}