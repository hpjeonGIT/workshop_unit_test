# Python Regex sample code
`import re`
- Padding spaces around array or number
```
>>> txt = 'Kx=Kx+1.3515e-3'
>>> re.sub(r'(\=|\+|\-)',r' \1 ', txt)
'Kx = Kx + 1.3515e - 3'
```
- This will add space inside of floating number, which we don't want
```
>>> re.sub(r'([0-9]*\.?[0-9]+([eE][-+]?[0-9]+)|\=|\+|\-|\*|\/)',r' \1 ', txt)
'Kx = Kx +  1.3515e-3 '
```
- Adding floating number search will avoid the issues
- When == is necessary
```
>>> cond = 'Kx = (Ky == Kz)'
>>> re.sub(r'([0-9]*\.?[0-9]+([eE][-+]?[0-9]+)|\=|\+|\-|\*|\/)',r' \1 ', cond)
'Kx  =  (Ky  =  =  Kz)'
>>> re.sub(r'([0-9]*\.?[0-9]+([eE][-+]?[0-9]+)|\=\=|\=|\+|\-|\*|\/)',r' \1 ', cond)
'Kx  =  (Ky  ==  Kz)'
```
- Adding `\=\=` resolves the issue
