File LBA Extraction
===================
ssd의 file fragmentation을 시각화 하기 위해서 가장 먼저 해야하는 일은 시각화할 파일들의 LBA(OS level에서 파일을 저장하기 위해서 사용하는 논리적 주소)를 추출해야한다.

ioctl
-----
입출력제어(I/OControl)의 약자로 보통 사용자 공간의 코드가 하드웨어 장치, 커널 구성 요소와 통신할 수 있게 도와 주는 역할을 한다.

운영체제는 기본적으로 User mode와 kernel mode 두가지 형태가 존재한다. 이는 OS에서 User가 마음대로 system에 접근하는 것을 방지함으로써, kernel resource를 보호하는 역할을 수행한다. user mode와 kernel mode는 mode bit(0:kernel mode, 1:user mode)를 사용해서 구별한다.

User application은 기본적으로는 user mode에서 필요한 작업들을 수행하다가 file I/O와 같이 system call을 하게 되면 interrupt가 된 후에 kernel mode로 mode를 바꾸고 kernel mode 에서 수행할 작업이 모두 끝났다면, 다시 user mode로 돌아가게 된다.

SSD Mapviewer의 경우 user application이기 때문에 File LBA와 같은 kernel level 정보를 얻기 위해서는 kernel mode에서 수행 되어야한다. 일반적인 read, write와 같은 system call은 OS의 system call table에 등록되어 있는 명령어로 이 것을 사용하게 되면 장치 driver를 막아버린다. ioctl인터페이스는 모든 장치 드라이버가 공유하는 하나의 시스템 콜을 할당함으로써 이 문제를 피할 수 있게 도와 준다. 이러한 시스템 콜을 통해 다양한 장치의 특정한 요청의 방향을 바꿀 수 있다. 그러므로 커널은 관리가 불가능한 시스템 콜 테이블을 만들지 않고도 유동적으로 장치에 대한 콜을 처리할 수 있다.


fibmap
-----
fibmap은 ioctl 함수로써 file의 kernel level 논리적 주소를 얻을 수 있다. 사용법은 terminal에서 사용할 경우
  ```
  sudo hdparm --fibmap [파일]
  ```
api로 사용할 경우
  ```
  //file의 blocksize를 얻는다.
  //fd : LBA를 얻을 파일의 file descriptor
  //FIGETBSZ : get file block size
  //blocksize : blocksize를 받을 변수
  ioctl(fd, FIGETBSZ, &blocksize)
  //각 block에 대한 주소값을 얻는다.
  //FIBMAP : 해당 file의 lba를 block_p에 넣어줌
  ioctl(fd, FIBMAP, &block_p)
  ```
  
