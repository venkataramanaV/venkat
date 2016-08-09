For More information reffer the below link:
[http://www.delorie.com/gnu/docs/gdb/gdb_toc.html#SEC_Contents]
1. Create Debug file
   gcc -g src.c -o src
   
2. To start the debugging
   gdb src
   
3. How to set the breakpoint
    1. to set at function = b reverse_array.c:main
    2. to set at line no  = b reverse_array.c:13
    
4. How to run the command in GDB
    1. run the command = r
    2. run the command with aguments = r <arguments>
    
5. How to traverse to the next line.
    1. type "n" to move to next line.
    2. type "s" to move into the function

6. How to move to next break point
    type "c" to move to next break point
    
7. How to see the call stack
    type "where" gives the call stack
    
8. How to see the value of variable
    1. type the command "p/print" with the variable name
       p <variable>
    2. Address of the variable can be found by executing below cmd
       p &<variable>
    3. To find content of the address
       p *<variable>
       
9. How to display the history of values printed
    show value <number>
    
10. How to access register variables
    1. info register
    
    GDB's standard register names:
      1. $pc  : program counter register
      2. $sp  : the stack pointer
      3. $fp  : register that contains a pointer to the current stack frame
      4. $ps  : register that contains the processor status.
      
    For example, you could print the program counter in hex with
    p/x $pc
    or print the instruction to be executed next with
    x/i $pc
    
11. How to get the details of memory region attributes
    info mem  : Print a table of all defined memory regions, with the following columns for each region.
          
          Memory Region Number
          Enabled or Disabled. :  Enabled memory regions are marked with `y'. Disabled memory regions are marked with `n'.
          Lo Address           :  The address defining the inclusive lower bound of the memory region.
          Hi Address           :  The address defining the exclusive upper bound of the memory region.
          Attributes           :  The list of attributes set for this memory region.
          
12. How to expand Macro in GDB
    gcc -gdwarf-2 -g3 src.c -o src
    info macro ADD
      o/p : #define ADD(x) (M + x)
    macro expand ADD(20)
      o/p : expands to: (10+20)

13. How to modify the variable at runtime
    set var b=20;
    p b
      o/p : 20
      
14. How to back trace in GDB
    1. create a debugging load
    2. set the break point
    3. run the executable
    4. use command
       bt 1
       bt full
       




    
