@SCREEN
D=A
@addr
M=D

@8192
D=A
@n
M=D

@i
M=0

(WHITE)
@8193
D=A
@i
D=D-M
@RE
D;JEQ

@i
D=M
@n
D=D-M
@END
D;JGT
@addr
A=M
M=0

@i
M=M+1
@addr
M=M+1

@24576
D=M

@BLACK
D;JNE
@WHITE
D;JEQ

(BLACK)
@8193
D=A
@i
D=D-M
@RE
D;JEQ

@i
D=M
@n
D=D-M
@END
D;JGT
@addr
A=M
M=-1

@i
M=M+1
@addr
M=M+1

@24576
D=M

@BLACK
D;JNE
@WHITE
D;JEQ

(END)
@24576
D=M
@WHITE
D;JEQ
@BLACK
D;JNE
0;JMP

(RE)
@i
M=0
@SCREEN
D=A
@addr
M=D
@24576
D=M
@WHITE
D;JEQ
@BLACK
D;JNE
0;JMP