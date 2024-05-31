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

## Integer Overflow
