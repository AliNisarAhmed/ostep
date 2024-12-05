## 1

#### INPUT 

seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList
compute False

#### END INPUT

ptr[0] = Alloc(3) returned 1000
List [Size 1]: [ addr:1003, size:97 ]

Free(ptr[0])
returned 0
List [Size 2]: [ addr:1000, size:3 ] [ addr:1003, size:97 ]

ptr[1] = Alloc(5) returned 1003
List [Size 2]: [ addr:1000, size:3 ] [ addr:1008, size:92 ]

Free(ptr[1])
returned 0
List [Size 3]: [ addr:1000, size:3 ] [ addr:1003, size:5 ] [ addr:1008, size: 92 ]

ptr[2] = Alloc(8) returned 1008
List [Size 3]: [ addr:1000, size:3 ] [ addr:1003, size:5 ] [ addr:1016, size:84 ]

Free(ptr[2])
returned 0
List [Size 4]: [ addr:1000, size:3 ] [ addr:1003, size:5 ] [ addr:1008, size:8 ] [ addr:1016, size:84 ]

ptr[3] = Alloc(8) returned 1008
List [Size 3]: [ addr:1000, size:3 ] [ addr:1003, size:5 ] [ addr:1016, size:84 ]

Free(ptr[3])
returned 0
List [Size 4]: [ addr:1000, size:3 ] [ addr:1003, size:5 ] [ addr:1008, size:8 ] [ addr:1016, size:84 ]

ptr[4] = Alloc(2) returned 1000
List [Size 4]: [ addr:1002, size:1 ] [ addr:1003, size:5 ] [ addr:1008, size:8 ] [ addr:1016, size:84 ]

ptr[5] = Alloc(7) returned 1008
List [Size 4]: [ addr:1002, size: 1] [ addr:1003, size:5 ] [ addr:1015, size: 1] [ addr: 1016, size:84 ]


---

## 2

#### INPUT 
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList
compute False
#### END INPUT

seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy WORST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList
compute False

ptr[0] = Alloc(3) returned 1000
List [ size 1 ]: [ addr:1003, size:97 ]

Free(ptr[0])
returned 0
List [ size 2 ]: [ addr:1000, size:3 ] [ addr:1003, size:97 ]

ptr[1] = Alloc(5) returned 1003
List [ size 2 ]: [ addr:1000, size:3 ] [ addr:1008, size:92 ]

Free(ptr[1])
returned 0
List [ size 3 ]: [ addr:1000, size:3 ] [ addr:1003, size:5 ] [ addr:1008, size:92 ]

ptr[2] = Alloc(8) returned 1008
List [ size 3 ]: [ addr:1000, size:3 ] [ addr:1003, size:5 ] [ addr:1016, size: 84 ]

Free(ptr[2])
returned 0
List [ size 4 ]: [ addr:1000, size:3 ] [ addr:1003, size: 5 ] [ addr:1008, size:8 ] [ addr:1016, size: 84 ]

ptr[3] = Alloc(8) returned 1016
List [ size 5 ]: [ addr:1000, size: 3 ] [ addr:1003, size: 5] [ addr:1008, size:8 ] [ addr:1024, size: 76 ]

Free(ptr[3])
returned 0
List [ size 5 ]: [ addr:1000, size: 3 ] [ addr:1003, size:5 ] [ addr:1008, size:8 ] [ addr:1016, size:8 ], [ addr:1024, size: 76 ]

ptr[4] = Alloc(2) returned 1024
List [ size 5 ]: [ addr:1000, size: 3] [ addr:1003, size:5 ] [ addr:1008, size:8 ] [ addr:1016, size:8 ] [ addr:1026, size:74 ]

ptr[5] = Alloc(7) returned 1026
List [ size 5 ]: [ addr:1000, size: 3] [ addr:1003, size:5 ] [ addr:1008, size: 8] [ addr:1016, size: 8] [ addr: 1033, size: 67 ]


---


## 3 

When using `FIRST` fit (-p FIRST), Number of fragments in the final list stays `4` (same as `BEST` fit), however
the number of searches through the list decreases

- `BEST` : 1 + 2 + 3 + 4 + 4 + 4 = 18
- `FIRST`: 1 + 2 + 3 + 3 + 1 + 3 = 13


---


## 4


#### BEST fit

1. ADDRSORT
   - end size = 4
   - max size = 4
   - `Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]`
   - accesses = 1 + 2 + 3 + 4 + 4 + 4 = 18
2. SIZESORT+
   - end size = 4
   - max size = 4
   - `Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]`
   - accesses = 1 + 2 + 3 + 4 + 4 + 4 = 18
3. SIZESORT-
   - end size = 4
   - max size = 4
   - `Free List [ Size 4 ]: [ addr:1016 sz:84 ][ addr:1015 sz:1 ][ addr:1003 sz:5 ][ addr:1002 sz:1 ]`
   - accesses = 1 + 2 + 3 + 4 + 4 + 4 = 18
4. INSERT-FRONT
   - end size = 4
   - max size = 4
   - `Free List [ Size 4 ]: [ addr:1015 sz:1 ][ addr:1003 sz:5 ][ addr:1002 sz:1 ][ addr:1016 sz:84 ]`
   - accesses = 1 + 2 + 3 + 4 + 4 + 4 = 18
5. INSERT-BACK
   - end size = 4
   - max size = 4
   - `Free List [ Size 4 ]: [ addr:1016 sz:84 ][ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ]`
   - accesses = 1 + 2 + 3 + 4 + 4 + 4 = 18


#### WORST fit

1. ADDRSORT
   - end size = 5
   - max size = 5
   - `Free List [ Size 5 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ][ addr:1033 sz:67 ]`
   - accesses = 1 + 2 + 3 + 4 + 5 + 5 = 20
2. SIZESORT+
   - end size = 5
   - max size = 5
   - `Free List [ Size 5 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ][ addr:1033 sz:67 ]`
   - accesses = 20
3. SIZESORT-
   - end size = 5
   - max size = 5
   - `Free List [ Size 5 ]: [ addr:1033 sz:67 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ][ addr:1003 sz:5 ][ addr:1000 sz:3 ]`
   - accesses = 20
4. INSERT-FRONT
   - end size = 5
   - max size = 5
   - `Free List [ Size 5 ]: [ addr:1016 sz:8 ][ addr:1008 sz:8 ][ addr:1003 sz:5 ][ addr:1000 sz:3 ][ addr:1033 sz:67 ]`
   - accesses = 20
5. INSERT-BACK
   - end size = 5
   - max size = 5
   - `Free List [ Size 5 ]: [ addr:1033 sz:67 ][ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ]`
   - accesses = 20


#### FIRST fit

1. ADDRSORT
   - end size = 4
   - max size = 4
   - `Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]`
   - accesses = 1 + 2 + 3 + 3 + 1 + 3 = 13
2. SIZESORT+ (asc)
   - end size = 4
   - max size = 4
   - `Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]`
   - accesses = 13
3. SIZESORT- (desc)
   - end size = 5
   - max size = 5
   - `Free List [ Size 5 ]: [ addr:1033 sz:67 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ][ addr:1003 sz:5 ][ addr:1000 sz:3 ]`
   - accesses = 6 (each 1)
4. INSERT-FRONT
   - end size = 4
   - max size = 4
   - `Free List [ Size 4 ]: [ addr:1010 sz:6 ][ addr:1003 sz:5 ][ addr:1000 sz:3 ][ addr:1023 sz:77 ]`
   - accesses = 1 + 2 + 3 + 1 + 1 + 4 = 12
5. INSERT-BACK
   - end size = 5
   - max size = 5
   - `Free List [ Size 5 ]: [ addr:1033 sz:67 ][ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ]`
   - accesses = 6 (1 each)



SUMMARY
- FIRST fit with SIZESORT- (desc) seems the best for accesses 
  - only 6 accesses with list size 5
- FIRST fit with INSERT-FRONT seems best for list size
  - 12 accesses with list size 4 (the least with size 4)


---

## 5

running `./malloc.py -n 1000 -H 0 -c` (defauls to ADDRSORT)
 - Without coalescing, the max List size reached 35, with ending size at 31
 - With coalescing, the max List size was 5, with ending size at 1


Same config with
- ADDRSORT
  - W/o coal: max size 35, end size 31
  - W coal  :  max size 5, end size 1
- SIZESORT+
  - w/o coal: max size 34, end size 31
  - w coal  : max size 33, end size 28
- SIZESORT-
  - w/o coal: max size 35, end size 31
  - w coal  : max size 41, end size 33
- INSERT-FRONT
  - w/o coal: max size 35, end size 31
  - w coal  : max size 37, end size 37
- INSERT-BACK
  - w/o coal: max size 35, end size 31
  - w coal  : max size 47, end size 46 (by far the worst overall performance)
