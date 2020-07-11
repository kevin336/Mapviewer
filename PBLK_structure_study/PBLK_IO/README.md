pblk I/O
=========
file의 OS level에서의 논리적 주소인 LBA의 경우에는 OS가 관리하는 주소이기 때문에 얻는 것이 크게 어렵지 않다. 하지만, 실제 SSD에 저장되는 주소인 PPA는 SSD의 FTL이 관리하기 때문에 FTL의 구조를 파악하고 있어야만 LBA2PPA table을 쉽게 가져올 수 있을 것이다. 
