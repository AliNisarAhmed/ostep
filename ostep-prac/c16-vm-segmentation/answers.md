## 1

`./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0`

AS size = 128 = 7 bits
PM size = 512 = 9 bits

SEGMENT 0:
- 0x00 (0)
- limit: 20 (32)

SEGMENT 1:
- 0x200 (512)
- limit: 20 (32)

0. `0x6c` (108) - 110_1100
  - Segment 1
  - Offset = 108 - 128 = -20
  - Address = 512 - 20 = 492 = `0x1EC`
1. `0x61` (97) - 110_0001
  - Segment 1
  - Offset = 97 - 128 = -31
  - OUT OF BOUNDS
2. `0x35` (53) - 011_0101
  - Segment 0
  - Offset = 53
  - OUT OF BOUNDS
3. `0x21` (33) - 010_0001
  - Segment 0
  - Offset = 33
  - OUT OF BOUNDS
4. `0x41` (65) - 110_0101
  - Segment 1
  - Offset = 65 - 128 = -63
  - OUT OF BOUNDS


`./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1`

AS size = 128 = 7 bits
PM size = 512 = 9 bits

SEGMENT 0:
- 0x00 (0)
- limit: 20 (32)

SEGMENT 1:
- 0x200 (512)
- limit: 20 (32)

0. `0x11` (17) - 001_0001
  - Segment 0
  - Offset = 17
  - Address: `0x11`
1. `0x6C` (108) - 110_1100
  - Segment 1
  - Offset = 108 - 128 = -20
  - Address = `0x1EC` (492)
2. `0x61` (97) - 110_0001
  - Segment 1
  - Offset = 97 - 128 =  -31
  - OUT OF BOUNDS (31 > 20)
3. `0x20` (32) - 010_0000
  - Segment 0
  - Offset = 32
  - OUT OF BOUNDS
4. `0x3f` (63) - 011_1111
  - Segment 0
  - OUT OF BOUNDS



`./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1`

AS size = 128 = 7 bits
PM size = 512 = 9 bits

SEGMENT 0:
- 0x00 (0)
- limit: 20

SEGMENT 1:
- 0x200 (512)
- limit: 20 

0. `0x7a` (122) - 111_1010
  - Segment 1
  - Offset = 122 - 128 = -6
  - Address = 512 - 6 = `0x1FA` (506)
1. `0x79` (121) - 111_1001
  - Segment 1
  - Offset = 121 - 128 = -7
  - Address = 512 - 7 = `0x1F9` (505)
2. `0x7` (7) - 000_0111
  - Segment 0
  - Address: `0x7` (7)
3. `0xa` (10) - 000_1010
  - Segment 0
  - Address: `0xa` (10)
4. `0x6a` (106) - 110_1010
  - Segment 1
  - Offset = 106 - 128 = -22
  - OUT OF BOUNDS (22 > 20)

---


## 2

Q: Highest legal virtual address in Segment 0
A: `0x13` (19)

Q: Lowest legal VA in Segment 1
A: 128 - 20 = `0x6c` (108)

Q: Lowest and Highest *illegal* address in the entire Address Space
A: lowest illegal: `0x14` (20) ; highest illegal `0x7f` (107)


check with `./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -A 0,19,20,107,108,127 -c`

---


## 3

AS = 16 bytes
PS = 128 Bytes

`./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 <> --l0 <> --b1 <> --l1 <>`

Out of the address above, we need top 2 and bottom 2 to be valid

--b0 = 0
--l0 = 2 (so addresses allowed will be <2 i.e. 0, 1)
--b1 = 16
--l1 = 2 (so addresses allowed will be 14 and 15)


--- 

## 4

Calc 90% of total addresses and divide segments into half of that space

e.g.
- in the above example, total addresses: 16
- 90% of 16 = 14
- so give segment 1 limit of 14 /2 , and same with segment 2


---

## 5

yes, make both segments 0?

e.g.: 
./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 0 --b1 16 --l1 0 -c

