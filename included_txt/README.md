# Sample code to read multiple txt files into a single string stream
- Sample input files are shown below.
```
$ more first.txt 
1 123 3.13
2 apple banana
include 'second.txt'
3 computer vga
4 cpu

$ more second.txt 
11 ubuntu os
12 windows Linux
include
 'third.txt'
13 centos rhel
14 nextstep
$ more third.txt 
21 Miku Hatsune
22 LAT
23 Eletric love
```
- first.txt includes second.txt while second.txt includes third.txt
- We want the data of each txt file is concatenated into a single stream while the order matters
- When "include" token is detected, it reads the file of next token and read the file data as string stream. This could be recursive to handle nested include statements
- When executed:
```
$ ./a.out 
include found 
include file ='second.txt'
include found 
include file ='third.txt'
1 123 3.13
2 apple banana
11 ubuntu os
12 windows Linux
21 Miku Hatsune
22 LAT
23 Eletric love
13 centos rhel
14 nextstep
3 computer vga
4 cpu
```
- Compiling: gcc -std=c++14 main.cpp

