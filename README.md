# buffer Overflow
## Application Vulnerability
In french  `dépassement de tampon ou débordement de tampon`

copy data without checking size.
A bug whereby a process, when writing to a buffer, writes outside the space allocated to the buffer, thus overwriting information necessary for the process.
<hr>

## Most common exploitation
1. stack overflow
2. Injection of a shellcode on the stack and calculation of its address
3. Overflow of a variable on the stack
4. Overwriting SEIP with the shellcode address
<img src="Buffer1.png" width="70%">

## A C program to demonstrate buffer overflow
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
 
       // Reserve 5 byte of buffer plus the terminating NULL.
       // should allocate 8 bytes = 2 double words,
       // To overflow, need more than 8 bytes...
       char buffer[5];  // If more than 8 characters input
                        // by user, there will be access 
                        // violation, segmentation fault
 
       // a prompt how to execute the program...
       if (argc < 2)
       {
              printf("strcpy() NOT executed....\n");
              printf("Syntax: %s <characters>\n", argv[0]);
              exit(0);
       }
 
       // copy the user input to mybuffer, without any
       // bound checking a secure version is strcpy_s()
       strcpy(buffer, argv[1]);
       printf("buffer content= %s\n", buffer);
 
       // you may want to try strcpy_s()
       printf("strcpy() executed...\n");
 
       return 0;
}
```
## Test
Open terminal
1. compile the program
```terminal
gcc -g -o BOF testoverflow.c
```
2. execute
```terminal
./BOF sam
```
3. output

```
buffer content= sam
strcpy() executed...
```

### now enter more than 8 characters.
```
./BOF beididinasamuel
```
output

```
buffer content= beididinasamuel
strcpy() executed...
Erreur de segmentation
```
### exploit, use GDB in terminal
```
$gdb -q ./BOF 
```
output
```
Reading symbols from ./BOF...
(gdb) 
```
1. list the program
```
(gdb) list 1
```
output

```
1	// A C program to demonstrate buffer overflow
2	#include <stdio.h>
3	#include <string.h>
4	#include <stdlib.h>
5	 
6	int main(int argc, char *argv[])
7	{
8	 
9	       // Reserve 5 byte of buffer plus the terminating NULL.
10	       // should allocate 8 bytes = 2 double words,
(gdb) 
11	       // To overflow, need more than 8 bytes...
12	       char buffer[5];  // If more than 8 characters input
13	                        // by user, there will be access 
14	                        // violation, segmentation fault
15	 
16	       // a prompt how to execute the program...
17	       if (argc < 2)
18	       {
19	              printf("strcpy() NOT executed....\n");
20	              printf("Syntax: %s <characters>\n", argv[0]);
(gdb) 
21	              exit(0);
22	       }
23	 
24	       // copy the user input to mybuffer, without any
25	       // bound checking a secure version is strcpy_s()
26	       strcpy(buffer, argv[1]);
27	       printf("buffer content= %s\n", buffer);
28	 
29	       // you may want to try strcpy_s()
30	       printf("strcpy() executed...\n");
```
2. breakpoint ( gdb will stop your program just before that function is called)

``` 
(gdb) break 26
```
output

```
(gdb) break 26
Breakpoint 1 at 0x11ab: file overflow.c, line 26.
```
3. run the program
```
(gdb) run AAAAAAAAAAAAAAAA
```
output

```
Starting program: Directory/BOF AAAAAAAAAAAAAAAA

Breakpoint 1, main (argc=2, argv=0x7fffffffe038) at overflow.c:26
26	       strcpy(buffer, argv[1]);
(gdb) 

```
the program stopped at line 26

### let's analyze the data of the variable

```
(gdb) x/s buffer
```
output
```
0x7fffffffdf3b:	""
(gdb) 
```