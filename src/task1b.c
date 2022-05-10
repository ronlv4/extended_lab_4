#include "util.h"
#include <fcntl.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define SYS_EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5

int system_call();

void print_system_call_id(int call_id) {
    system_call(SYS_WRITE, STDERR, "\nsystem call id: ", strlen("\nfirst argument: "));
    system_call(SYS_WRITE, STDERR, itoa(call_id), strlen(itoa(call_id)));
}

void print_return_code(int return_code) {
    system_call(SYS_WRITE, STDERR, "\nreturn code: ", strlen("\nreturn code: "));
    system_call(SYS_WRITE, STDERR, itoa(return_code), strlen(itoa(return_code)));
    system_call(SYS_WRITE, STDERR, "\n\n", strlen("\n\n"));
}

void print_first_arg_char(char *arg1) {
    system_call(SYS_WRITE, STDERR, "\nfirst argument: ", strlen("\nfirst argument: "));
    system_call(SYS_WRITE, STDERR, arg1, strlen(arg1));
}

void print_first_arg_int(int arg1) {
    system_call(SYS_WRITE, STDERR, "\nfirst argument: ", strlen("\nfirst argument: "));
    system_call(SYS_WRITE, STDERR, itoa(arg1), strlen(itoa(arg1)));
}

void print_system_call_int(int call_id, int arg1, int return_code) {
    print_system_call_id(call_id);
    print_first_arg_int(arg1);
    print_return_code(return_code);
}

void print_system_call_char(int call_id, char *arg1, int return_code) {
    print_system_call_id(call_id);
    print_first_arg_char(arg1);
    print_return_code(return_code);
}

void print_if_debug_mode_int(int debug_mode, int call_id, int arg1, int return_code) {
    if (debug_mode) {
        print_system_call_int(call_id, arg1, return_code);
    }
}

void print_if_debug_mode_char(int debug_mode, int call_id, char *arg1, int return_code) {
    if (debug_mode) {
        print_system_call_char(call_id, arg1, return_code);
    }
}

int main(int argc, char **argv) {
    int arg_index = 1;
    int debug_mode = 0;
    int output_fd = STDOUT;
    int input_fd = STDIN;
    while (arg_index < argc) {
        if (!strcmp(argv[arg_index], "-D"))
            debug_mode = 1;
        arg_index++;
    }
    arg_index = 1;
    while (arg_index < argc) {
        if (!strncmp(argv[arg_index], "-i", 2)) {
            input_fd = system_call(SYS_OPEN, argv[arg_index] + 2, O_RDONLY, 0777);
            print_if_debug_mode_char(debug_mode, SYS_OPEN, argv[arg_index] + 2, input_fd);
            if (input_fd == -1)
            {
                system_call(SYS_WRITE, STDERR, "'open' system call returned an error\nexiting...", 48);
                system_call(SYS_EXIT, 1);
            }
        } else if (!strncmp(argv[arg_index], "-o", 2)) {
            output_fd = system_call(SYS_OPEN, argv[arg_index] + 2, O_WRONLY | O_CREAT, 0777);
            print_if_debug_mode_char(debug_mode, SYS_OPEN, argv[arg_index] + 2, output_fd);
        }
        arg_index++;
    }
    int word_count = 0;
    char *new_line = "\n";
    char buf[1];
    int bytes_read, return_code;
    bytes_read = system_call(SYS_READ, input_fd, buf, 1);
    print_if_debug_mode_int(debug_mode, SYS_READ, input_fd, bytes_read);
    while (bytes_read != 0) {
        while (buf[0] == ' ' && strcmp(buf, new_line) != 0) {
            bytes_read = system_call(SYS_READ, input_fd, buf, 1);
            print_if_debug_mode_int(debug_mode, SYS_READ, input_fd, bytes_read);
        }
        if (!strcmp(buf, new_line)) {
            break;
        }
        while (buf[0] != ' ' && bytes_read != 0 && strcmp(buf, new_line) != 0) {
            bytes_read = system_call(SYS_READ, input_fd, buf, 1);
            print_if_debug_mode_int(debug_mode, SYS_READ, input_fd, bytes_read);
        }
        word_count++;
    }
    return_code = system_call(SYS_WRITE, output_fd, itoa(word_count), 1);
    print_if_debug_mode_int(debug_mode, SYS_WRITE, output_fd, return_code);
    return_code = system_call(SYS_WRITE, output_fd, new_line, strlen(new_line));
    print_if_debug_mode_int(debug_mode, SYS_WRITE, output_fd, return_code);
    return 0;
}
