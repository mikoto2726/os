        .text
        .globl  main
main:
        mov     $1, %rax        /* system call# */
        mov     $1, %rdi        /* argument #1 */
        mov     $message, %rsi  /* argument #2 */
        mov     $14, %rdx       /* argument #3 */
        syscall
        
        mov     $0, %rax        /* return 0; */
        ret

message:
        .asciz  "Hello, world!\n"
