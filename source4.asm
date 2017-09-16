.sample program for SIC/XE architecture
        . Here is an additional file for testing
        . This file is VALID
        
prog    start   1000    .start of sample program

ThisIsAValidLabelEvenThoughItIsVeryLong

        lds     #3
        ldt     #300
        ldx     #0
addlf   lda     alpha,x   .loop control 
        add     beta,x
        sta     gamma,x                       
        addr    s,x
        compr   x,t 
        jlt     addlf 
        +LDA    delta
        LDB     @beta  
        
. storage allocation section        
alpha   resw    100
beta    resw    100
gamma   resw    100  
delta   byte    c'Here is a valid string'
zeta    byte    x'FF'
eta     WORD    X'ABCD' 
        end     prog    .end of sample program     
