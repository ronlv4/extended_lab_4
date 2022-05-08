#include "util.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define SYS_EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_GETDENTS 0x8d

int system_call();

struct linux_dirent {
               unsigned long  d_ino;     /* Inode number */
               unsigned long  d_off;     /* Offset to next linux_dirent */
               unsigned short d_reclen;  /* Length of this linux_dirent */
               char           d_name[];  /* Filename (null-terminated) */
                                 /* length is actually (d_reclen - 2 -
                                    offsetof(struct linux_dirent, d_name)) */
               /*
               char           pad;       // Zero padding byte
               char           d_type;    // File type (only since Linux
                                         // 2.6.4); offset is (d_reclen - 1)
               */
           };
void print_if_debug_mode(int debug_mode, int sys_call, char* first_arg, int return_code)
{
    print_system_calls_char(sys_call, first_arg, return_code);


}
void print_system_calls_char(int sys_call, char* first_arg, int return_code)
{
    char* new_line = "\n";
    system_call(SYS_WRITE, STDERR, "system call: ", 13);
    system_call(SYS_WRITE, STDERR, itoa(sys_call), 1);
    system_call(SYS_WRITE, STDERR, new_line, 1);
    system_call(SYS_WRITE, STDERR, "first argument: ", 14);
    system_call(SYS_WRITE, STDERR, first_arg, strlen(first_arg));
    system_call(SYS_WRITE, STDERR, new_line, 1);
    system_call(SYS_WRITE, STDERR, "return code: ", 13);
    system_call(SYS_WRITE, STDERR, itoa(return_code), 13);
    system_call(SYS_WRITE, STDERR, new_line, 1);

}

void print_if_debug_mode(int debug_mode, int sys_call, int first_arg, int return_code)
{
    if (debug_mode)
    {
        print_system_calls_int(sys_call, first_arg, return_code);
    }
}

void print_system_calls_int(int sys_call, int first_arg, int return_code)
{
    char* new_line = "\n";
    system_call(SYS_WRITE, STDERR, "system call: ", 13);
    system_call(SYS_WRITE, STDERR, itoa(sys_call), 1);
    system_call(SYS_WRITE, STDERR, new_line, 1);
    system_call(SYS_WRITE, STDERR, "first argument: ", 14);
    system_call(SYS_WRITE, STDERR, itoa(first_arg), 1);
    system_call(SYS_WRITE, STDERR, new_line, 1);
    system_call(SYS_WRITE, STDERR, "return code: ", 13);
    system_call(SYS_WRITE, STDERR, itoa(return_code), 13);
    system_call(SYS_WRITE, STDERR, new_line, 1);
}


int main(int argc, char **argv)
{
    int nread, fd, bpos, tmp_ret_code;
    struct linux_dirent *d;

    int BUF_SIZE = 8192;
    int debug_mode = 0;
    int arg_index = 1;
    int output_fd = STDOUT;
    char buf[BUF_SIZE];

    char * ten_spaces = "            ";
    char* new_line = "\n";
    char *prefix = "";

    while (arg_index < argc)
	{
		if (*(argv[arg_index] + 1) == 'p')
		{
			prefix = argv[arg_index] + 2;
			arg_index++;
		}
        else if (*(argv[arg_index] + 1) == 'D')
        {
            debug_mode = 1;
            arg_index++;
        }
		else
		{
			arg_index++;
		}
		
	}

    fd = system_call(SYS_OPEN, ".", 0 , 0);
    print_if_debug_mode(debug_mode, SYS_OPEN, ".", fd);
    nread = system_call(SYS_GETDENTS, fd, buf, BUF_SIZE);
    print_if_debug_mode(debug_mode, SYS_GETDENTS, fd, nread);
    if (nread == -1)
    {
        tmp_ret_code = system_call(SYS_WRITE,STDOUT, "error-getdents",BUF_SIZE);
        print_if_debug_mode(debug_mode, SYS_WRITE, "error-getdents", tmp_ret_code);
        return 1;
    }
	system_call(SYS_WRITE, output_fd, new_line, strlen(new_line));
    system_call(SYS_WRITE,output_fd, "file type    offset    d_name\n",31);
    for (bpos = 0; bpos < nread;) {
        d = (struct linux_dirent *) (buf + bpos);
        if (strncmp(prefix, d->d_name, strlen(prefix)))
        {
            bpos += d->d_reclen;
            continue;
        }
        system_call(SYS_WRITE, output_fd, itoa(d->d_reclen), 1);
        system_call(SYS_WRITE, output_fd, ten_spaces, strlen(ten_spaces));
        system_call(SYS_WRITE, output_fd, itoa(d->d_off), 1);
        system_call(SYS_WRITE, output_fd, ten_spaces, strlen(ten_spaces));
        system_call(SYS_WRITE, output_fd, d->d_name, strlen(d->d_name));
        system_call(SYS_WRITE, output_fd, new_line, strlen(new_line));
        bpos += d->d_reclen;
    }
    return 0;
}