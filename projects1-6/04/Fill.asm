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
@REW
D;JEQ

@i
D=M
@n
D=D-M
@WHITEEND
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
@REB
D;JEQ

@i
D=M
@n
D=D-M
@BLACKEND
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


(BLACKEND)
@24576
D=M
@WHITE
D;JEQ
@BLACKEND
0;JMP

(WHITEEND)

@24576
D=M
@BLACK
D;JNE
@WHITEEND
0;JMP

(REW)
@i
M=0
@SCREEN
D=A
@addr
M=D
@WHITE
0;JMP

(REB)
@i
M=0
@SCREEN
D=A
@addr
M=D
@BLACK
0;JMP
