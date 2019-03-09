section .data
msg1 :db 'Enter your name :',10
l1 : equ $-msg1
msg2 :db 'Palindrome',10
l2 : equ $-msg2
msg3 :db 'Not palindrome',10
l3 : equ $-msg3

section .bss
name : resb 100
l : resb 1
temp : resb 1
scanint : resw 1
scan : resb 1
lenstr : resw 1

section .text

global _start:

print_char:
    pusha
    mov eax,4
    mov ebx,1
    mov ecx,scan
    mov edx,1
    int 0x80
    popa
    ret

read_char:
    pusha
    mov eax,3
    mov ebx,0
    mov ecx,scan
    mov edx,1
    int 0x80
    popa
    ret

read_str:
    pusha
    mov word[lenstr],0
    forread_str:
        call read_char
        cmp byte[scan],10
        je endforread
        mov bl,byte[scan]
        mov byte[eax],bl
        inc eax
        inc word[lenstr]
        jmp forread_str
    endforread:
    popa
    ret

print_num:
    pusha
    mov esi,0
    forprint:
        cmp word[scanint],0
        je endforprint
        mov eax,0
        mov ax,word[scanint]
        mov ebx,10
        mov edx,0
        div ebx
        add edx,48
        push edx
        mov word[scanint],ax
        inc esi
        jmp forprint
    endforprint:
    printfor:
        cmp esi,0
        je endprintfor
        dec esi
        pop edx
        mov byte[scan],dl
        call print_char
        jmp printfor
    endprintfor:    
    popa
    ret
    
_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, l1
	int 80h

    mov eax,name
    call read_str
    
    mov cx,0
    mov eax,name
    fori :
        cmp cx,word[lenstr]
        je endfori
        mov edx,0
        mov dl,byte[eax]
        push edx
        inc cx
        inc eax
        jmp fori
    endfori:
    
    mov cx,0
    mov eax,name
    forcheck:
        cmp cx,word[lenstr]
        je endforcheck
        pop edx
        cmp byte[eax],dl
        je skip
        mov eax,4
        mov ebx,1
        mov ecx,msg3
        mov edx,l3
        int 0x80
        jmp endpro
        skip:
        inc eax
        inc cx
        jmp forcheck
    endforcheck:
    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,l2
    int 0x80
    endpro:
	mov eax,1
	mov ebx, 0
	int 80h