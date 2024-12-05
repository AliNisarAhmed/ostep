## 1

`-P 1k -a 1m -p 512m -v -n 0`
- page table size: 1k
- 1k pages of 1k each = 1m

`-P 1k -a 2m -p 512m -v -n 0`
- page table size: 2k
- 2k pages of 1k each = 2m


`-P 1k -a 4m -p 512m -v -n 0`
- page table size: 4k
- 4k pages with 1k each = 4m

Summary: page table size is proportional to address space size, when page size and Phys space size are same


`-P 1k -a 1m -p 512m -v -n 0`
- page table size: 1k


`-P 2k -a 1m -p 512m -v -n 0`
- page table size: 512 bytes


`-P 4k -a 1m -p 512m -v -n 0`
- page table size: 256 bytes

Summary: page table size is inversely proportional to Page size, given address space & phys space sizes are same


**We should not use big pages because it wastes a lot of spaces (process do not need that much memory)**


## 2

address space size: 16384 bytes requires 14 bits
Since page size is 1k, offset = 10 bits
VPN = first 4 bits

`-P 1k -a 16k -p 32k -v -u 0`
  - `-u` flag means 0% Address space utilized
  - Also, all page table Entries start with 0
  - which means they are all INVALID

`-P 1k -a 16k -p 32k -v -u 25`
- `0x3986` (1110 01_1000_0110)
  - VPN = 1110 = 14 = INVALID
- `0x2bc6` (1010 11_1100_0110)
  - VPN = 10 = `0x80000013` = VALID
  - offset = 11_1100_0110 = 966 = `0x3c6`
  - address = `base address x page size + offset`
  - address = `0x13 x 0x400 + 0x3c6` = `0x45c6` (13 * 1024 + 966 = 20422 dec)
- `0x1e37` (0111 10_0011_0111)
  - VPN = 0111 = 7 = INVALID
- `0x671` (0001 10_0111_0001)
  - VPN = 0001 = 1 = INVALID
- `0x1bc9` (0110 11_1100_1001)
  - VPN = 0110 = 6 = INVALID


`-P 1k -a 16k -p 32k -v -u 50`
- `0x3385` (1100 11_1000_0101)
  - VPN = 1100 = 12 = VALID
  - offset = 11_1000_0101 = `0x385` (901)
  - address = `0x0f x 0x400 + 0x385` = `0x3f85` (15360 + 901 = 16261)
- `0x231d` (1000 11_0001_1101)
  - VPN = 1000 = 8 = INVALID
- `0xe6` (0000 00_1110_0110)
  - VPN = 0 = VALID
  - offset = 00_1110_0110 = `0xe6` (230)
  - address = `0x18 * 0x400 + 0xe6` = `0x60e6` (24576 + 230 = 24806)
- `0x2e0f` (1011 10_0000_1111)
  - VPN = 1011 = 11 = INVALID
- `0x1986` (0110 01_1000_0110)
  - VPN = 0110 = 6 = VALID
  - offset = 01_1000_0110 = `0x186` (390)
  - address = `0x1d x 0x400 + 0x186` = `0x7586` (29696 + 390 = 30086)


`-P 1k -a 16k -p 32k -v -u 75`
- `0x2e0f` (1011 10_0000_1111)
  - VPN = 1011 = 11 = VALID = PFN = `0x13`
  - offset = 10_0000_1111 = `0x20f` (527)
  - address = `0x13 x 0x400 + 0x20f` = `0x4e0f` (19456 + 527 = 19983)
- `0x1986` (0110 01_1000_0110)
  - VPN = 0110 = 6 = VALID = `0x1f`
  - offset = `0x186` (390)
  - address = `0x1f x 0x400 + 0x186` = `0x7d86` (32134)
- `0x34ca` (1101 00_1100_1010)
  - VPN = 1101 = 13 = VALID = `0x1b`
  - offset = 00_1100_1010 = `0xCA`
  - address = `0x1b x 0xc400 + 0xCA` = `0x6cca` = (27648 + 202 = 27850)
- `0x2ac3` (1010 10_1100_0011)
  - VPN = 1010 = 10 = VALID = `0x3`
  - offset = 10_1100_0011 = `0x2c3`
  - address = `0x3 x 0x400 + 0x2c3` = 3779
- `0x12` = 0000 00_0001_0010
  - VPN = 0 = VALID = `0x18` (24)
  - offset = `0x12` (18)
  - address = `24 x 1024 + 18` = 24594


`-P 1k -a 16k -p 32k -v -u 100`
- `0x2e0f` (1011 10_0000_1111)
  - VPN = 1011 = 11 = VALID = `0x13` = 19
  - offset = `0x20f` (527)
  - address = `19 x 1024 + 527` = 19983
- `0x1986`
  - VPN = 0110 = 6 = VALID = `0x1f` (31)
  - offset = `0x186` (390)
  - address = `31 x 1024 + 390` = 32134
- `0x34ca`
  - VPN = 1101 = 13 = VALID = `0x1b` (27)
  - offset = `0xca` (202)
  - address = `27 x 1024 + 202` = 27850
- `0x2ac3`
  - VPN = 1010 = 10 = VALID = `0x3` (3)
  - offset = `0x2c3` = 707
  - address = `3 * 1024 + 707` = 3779
- `0x12`
  - address = 24594


**As we increase the % of pages allocated in each address space, the number of**
**VALID page table entries increases as more pages are in use**


## 3

`-P 8 -a 32 -p 1024 -v -s 1`
AS size = 32 = requires 5 bits
PM size = 1024 = 10 bits
Page size = 8 = 4 pages per AS = 2 bits for VPN
which means offset = 3 bits
- `0xe` (14) 01 110
  - VPN = 01 = VALID = `0x61` (97)
  - offset = 110 = 6
  - address = `97 * 8 + 6` = 782
- `0x14` (20) 10 100
  - VPN = 10 = 2 = INVALID
- `0x19` 11 001
  - VPN = 11 = 3 = INVALID
- `0x3` (00 011)
  - VPN = 0 = INVALID
- `0x0` = 00 000
  - VPN = 0 = INVALID


`-P 8k -a 32k -p 1m -v -s 2`
AS size = 32k = 32768 = requires 15 bits
PM size = 1M = 1048576 = 20 bits
Page size = 8k = 4 pages per AS = 2 bits for VPN
which means offset = 13 bits
- `0x55b9` (10 1_0101_1011_1001)
  - VPN = 10 = 2 = INVALID
- `0x2771` (01 0_0111_0111_0001)
  - VPN = 01 = 1 = INVALID
- `0x4d8f` (10 0_1101_1000_1111)
  - VPN = 10 = 2 = INVALID
- `0x4dab` (10 0_1101_1010_1011)
  - VPN = 10 = 2 = INVALID
- `0x4a64` (10 0_1010_0110_0100)
  - VPN = 2 = INVALID

`-P 1m -a 256m -p 512m -v -s 3`
AS size = 256m = 28 bits
PM size = 512m
Page size = 1M = 20 bits = 256 pages per AS = 8 bit VPN
which means 20 bits offset
- `0x308b24d` 
  - VPN = 0011 0000 = 48 = `0x1f6` = 502
  - offset = 1000 1011 0010 0100 1101 = 569933
  - address = 502 x 1048576 + 569933 = 562955085
- `0x42351e6`
  - VPN = 0100 0010 = 66 = INVALID
- `2feb67b` 
  - VPN = 0010 1111 = 47 = `0xa9` = 169
  - offset = 964219
  - address = 169 x 1m + 964219 = 178.173.563
- `0b46977d`
  - VPN = 1011 0100 = 180 = INVALID
- `0dbcceb4`
  - VPN = 1101 1011 = 219 = 498
  - offset = 839348
  - address = 523.030.196

these parameter combinations allow very few processes
e.g. combo 1 & 2 only allow 32 address spaces to exist, hence 32 processes
while combo 3 allows only 2


## 4


