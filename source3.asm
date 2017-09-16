.sample program for SIC/XE architecture
.test program for prog1
.This file should assemble without errors

prog    start   1000    .start of sample program
bsrch   EQU     14
OFFB    EQU     8 
        BASE    delta
        LDB     #delta
        lds     #3
        +ldx     @foo
        +lda     beta,x
        add     gamma
        ldx     @zeta   
first   NORM  
        SVC     13  
        HIO
        ldt     #alpha
        +ldt     #foo
        lda     @alpha
        lda     @foo
        addr    S,T
        shiftr  T,2
        shiftl  S,1
        tixr    T
        j       first
        +j      first
        Clear   T
        +ldt    #50000	
        ldx     #0
        jsub    first
addl    lda     alpha,x   .loop control     
        add     beta,x
        sta     gamma,x     . extra space for testing                                
        addr    s,t
        compr   x,t
        +jlt     addl
        jlt     addl
        rsub  
        
. storage allocation section 
test    byte    C'12345' 
test2   byte    x'007b'      
alpha   resw    100
beta    RESW    100
gamma   resw    100  
delta   WORD    20 
zeta    BYTE    C'EOF' 
eta     byte    X'FFFFFE'
theta	byte	c'eof'
buffer  RESB    3000
foo     word    1
        end     prog    .end of sample program    
