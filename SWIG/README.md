## Ref: http://books.gigatux.nl/mirror/pythonprogramming/0596000855_python2-CHP-19-SECT-8.html

## C++ with Python coupling
```
swig -c++ -python number.i
g++ -g -std=c++14 -fPIC -c number.cxx number_wrap.cxx  -I/usr/include/python3.6
g++ -shared number.o number_wrap.o _number.so
g++ -shared number.o number_wrap.o -o _number.so
python3
>>> import number
>>> abc = number.Number(1)
Number: 1
>>> abc.display()
Number = 1
>>> abc.add_v([1,2,3])
add 6
>>> abc.display()
Number = 7
>>> x = number.vectori([4,5,6])
>>> abc.add_v(x)
add 15
>>> abc.display()
Number = 22
>>> abc.timedata(123)
time data = 123
```
