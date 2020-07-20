FTL(Flash Translation Layer)
========
SSD(Solid State Drive) vs. HDD(Hard Disk Drive)
-----
SSD는 HDD를 대체하는 새로운 기억장치로, 2020년 현재에는 대부분의 기억장치로써 SSD를 사용하고 있다. HDD보다 용량 대비 가격이 비싸지만, SSD를 사용하게 된 가장 큰 이유는 바로 read/write의 속도에 있다. 통상적으로 HDD의 sequential read/write의 속도는 200mb/s정도이나, NVMe interface를 사용하는 SSD의 경우에는 12GB/s에 달하는 속도가 나오기도 한다. 이처럼 SSD는 HDD에 비해 굉장히 빠른 read/write의 속도를 가지기 때문에 대부분 HDD대신 SSD를 사용한다.

이렇게 HDD에 비해서 SSD의 속도가 빠른 이유는 바로 데이터를 저장하는 방식에 있다. 먼저, HDD의 경우에 아래의 그림과 같이 cylinder와 arm으로 이루어져 있어서 cylinder가 회전을 하면 arm이 platter의 데이터를 read하는 방식이다. 이처럼 물리적으로 데이터를 저장하는 방식이기 때문에 만약 데이터가 sequential하게 read/write할 경우에는 그나마 빠른 속도로 read/write를 할 수 있지만, random read/write처럼 물리적으로 떨어져있을 경우에는 그만큼 arm과 cylinder가 이동해야하는 양이 많이지기 때문에 read/write 성능이 대폭 떨어지게 된다.

SSD의 구조는 다음과 같다. SSD는 논리적으로 데이터를 저장하는 저장장치로, 크게 컨트롤러와 플래시 메모리 두부분으로 구성된다. 플래시 메모리는 전원이 끊겨도 데이터를 보존하는 특성을 가진 반도체로, 일반적으로 전원이 꺼지면 기억된 정보를 모두 잃어버리는 반도체인 DRAM, SRAM과 달리 비휘발성 메모리이다. 플래시 메모리는 전기적인 방법으로 데이터를 저장한다. SSD는 HDD와는 다른 특징들이 몇가지 있다. 먼저, SSD의 경우에는 최대 쓰기제한 횟수가 존재한다. 두 번째, overwrite가 되지 않는다. 세 번째, page단위로 write하고, block단위로 erase 한다.

FTL(Flash Translation layer)
-----

