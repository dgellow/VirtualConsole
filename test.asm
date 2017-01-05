// Implementation
  @R2
  M=0 // reset product

  @R0
  D=M
  @x
  M=D // x = R0

  @R1
  D=M
  @y
  M=D // y = R1

  D=M
  @i
  M=D // i = y

  @0
  D=A
  @sum
  M=D // sum = 0

(LOOP)
  @i
  D=M
  @STOP
  D;JEQ // if i == 0 goto STOP

  @x
  D=M
  @sum
  M=D+M;JEQ // sum = sum + x

  @i
  D=M
  M=D-1 // i--

  @LOOP
  0;JMP

(STOP)
  @sum
  D=M
  @R2
  M=D // R2 = sum

(END)
  0;JMP
