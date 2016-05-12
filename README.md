# ENGN3213 Assignment 2

### Report:

[overleaf](https://www.overleaf.com/5154243hxzfnh)

### Multiple functions how-to:
Do not throw all the functions in the main file, keep them separate. For each function file, create a header file and `#include` it in both the main file and your function file as shown below:

`main.c` main file:
``` c
#include <stdio.h>
#include "other.h"
 
int main (void)
{
    \\ use the function
    top = kek();
    return 0;
}
```
`other.h` header file:
``` c
#ifndef _OTHER_H_
#define _OTHER_H_

// declare the function
int kek(void);
 
#endif
```
`other.c` with your function:
``` c
#include "other.h"
 
int kek(void)
{
    return 42;
}
```
### Lab times:

* TUE 17MAY 1500--1700
* THU 19MAY 1100--1300
* FRI 20MAY 1100--1300
* MON 23MAY 1100--1300
* TUE 24MAY 1300--1700
* THU 26MAY 1100--1300
