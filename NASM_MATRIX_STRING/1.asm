section .data
msg1 :db 'Enter your name :',10
l1 : equ $-msg1
msg2 :db 'Palindrome',10
l2 : equ $-msg2
msg3 :db 'Not palindrome',10
l3 : equ $-msg3

section .bss
Matrix : resw 400
Matrix1 : resw 400
Matrix2 : resw 400
n : resw 1
m : resw 1
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

print_str:
    pusha
    
    mov cx,word[lenstr]
    forprint_str:
        cmp cx,0
        je endforstr
        dec cx
        mov bl,byte[eax]
        mov byte[scan],bl
        inc eax
        call print_char
        jmp forprint_str
    endforstr:
    popa
    ret

readnum:
    pusha
    mov word[scanint],0
    forreadnum:
        call read_char
        cmp byte[scan],10
        je endforreadnum
        sub byte[scan],48
        mov ax,word[scanint]
        mov bx,10
        mov dx,0
        mul bx
        add al,byte[scan]
        mov word[scanint],ax
        jmp forreadnum
    endforreadnum:
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
    call readnum
    mov ax,word[scanint]
    mov word[n],ax
    
    call print_num
    mov byte[scan],32
    call print_char
    
    call readnum
    mov ax,word[scanint]
    mov word[m],ax
    
    call print_num
    mov byte[scan],10
    call print_char

    mov ecx, Matrix
    mov ax,0
    foriiii:
        cmp word[n],ax
        je endforiiii
        inc ax
        mov bx,0
        gorjjjj:
            cmp word[m],bx
            je endforjjjj
            inc bx
            call readnum
            mov dx,word[scanint]
            mov word[ecx],dx
            inc ecx
            inc ecx
            jmp gorjjjj
        endforjjjj:
        jmp foriiii
    endforiiii:
    
    mov ecx, Matrix1
    mov ax,0
    fori:
        cmp word[n],ax
        je endfori
        inc ax
        mov bx,0
        gorj:
            cmp word[m],bx
            je endforj
            inc bx
            call readnum
            mov dx,word[scanint]
            mov word[ecx],dx
            inc ecx
            inc ecx
            jmp gorj
        endforj:
        jmp fori
    endfori:

    mov ecx,Matrix2
    mov edi,Matrix1
    mov esi,Matrix
    mov ax,0
    foriii:
        cmp word[n],ax
        je endforiii
        inc ax
        mov bx,0
        gorjjj:
            cmp word[m],bx
            je endforjjj
            inc bx
            mov dx,word[edi]
            add dx,word[esi]
            mov word[ecx],dx
            inc esi
            inc esi
            inc edi
            inc edi
            inc ecx
            inc ecx
            jmp gorjjj
        endforjjj:
        jmp foriii
    endforiii:


    mov ecx,Matrix2
    mov ax,0
    forii:
        cmp word[n],ax
        je endforii
        inc ax
        mov bx,0
        gorjj:
            cmp word[m],bx
            je endforjj
            inc bx
            mov dx,word[ecx]
            mov word[scanint],dx
            call print_num
            mov byte[scan],32
            call print_char
            inc ecx
            inc ecx
            jmp gorjj
        endforjj:
        mov byte[scan],10
        call print_char
        jmp forii
    endforii:

	mov eax,1
	mov ebx, 0
	int 80h