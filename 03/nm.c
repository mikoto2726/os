.globl sum
sum:
    pushq %rbp          
    movq %rsp, %rbp    

    movl $0, %eax       
    movl %edi, %ecx    
    movl %esi, %edx    

    start_loop:
    cmp %edx, %ecx      
    jnle end_loop      

    addl %ecx, %eax     
    incl %ecx        
    jmp start_loop     

    end_loop:
    popq %rbp           
    ret               
