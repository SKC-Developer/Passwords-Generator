# Passwords Generator
A simple program to generate passwords lists.

## Usage:
In the cmd or terminal, type *"passgen number_length letters output_path"*.

*number_length* is the length of all the passwords.  
*letters* are the letters that the program will use to generate the passwords.  
*output_path* is the path to the output file. **This file will be overwritten.**

**Usage examples:**  
~~~
passgen 10 0123456789 numbers.txt  
passgen 24 01 binary.txt  
passgen 5 abcdefghijklmnopqrstuvwxyz words.txt
~~~

You can download the Linux version (named *'passgen'*) or the Windows version (named *'PassGen.exe'*) from *'Releases'*.
Before compiling the code, make sure it's compitable with your system and compiler.

## Compiling:
You can compile this code on every x64 system (x86 dosen't support int128 so you will have to change it to another int).  
To compile it on Windows, you can download the source and open *PassGen.dev* with *Dev-C++* and then select *'compile'*.  
To compile it on Linux, type in the terminal:
~~~
g++ main.cpp -o passgen.o
link passgen.o passgen
~~~
