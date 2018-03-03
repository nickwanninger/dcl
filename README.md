# DCL
Print the english representation of (most) c declarations

example:

```
$ echo "char (*(x())[])()" | dcl
=> x:  function returning array[] of pointer to function returning char
```
