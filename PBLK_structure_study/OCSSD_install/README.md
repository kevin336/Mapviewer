OCSSD Install
====
## Environment

OS : Ubuntu Linux 18.04 LTS

## QEMU Installation

### 필수 패키지 설치

```
sudo apt install libglib2.0-dev libpixman-1-dev build-essential libncurses5 libncurses5-dev libssl-dev bc bison flex libelf-dev
```

### qemu 설치

```
cd ~
git clone https://github.com/OpenChannelSSD/qemu-nvme.git
cd qemu-nvme
./configure --target-list=x86_64-softmmu --prefix=$HOME/qemu-nvme
make -j '# of core'
make install
cd bin
sudo ln qemu-img /usr/bin
sudo ln qemu-system-x86_64 /usr/bin
```

### Open-Channel 2.0 SSD 설정

```
cd ~
mkdir ocssd
cd ocssd
//ocssd img
qemu-img create -f ocssd -o num_grp=2,num_pu=4,num_chk=60 ocssd.img
//ubuntu disk
qemu-img create -f qcow2 -o preallocation=full ubuntu.img 40G
```

### qemu linux 설정

```
wget https://releases.ubuntu.com/18.04/ubuntu-18.04.4-desktop-amd64.iso
sudo qemu-system-x86_64 -hda ubuntu.img -boot d -cdrom ubuntu-18.04.4-desktop-amd64.iso -m 'memory size(e.g. 8G)' -smp '# of core' -cpu host --enable-kvm -vnc :2
```

이후 리미너를 통해서 ubuntu linux 설치를 완료한다.

### Kernel 컴파일 및 설치

kernel 소스파일을 다운로드 합니다. linux에서 제공해주는 kernel을 사용하지 않고, 아래 주소에 있는 OpenChannelSSD에서 제공되는 커널을 사용해야 합니다.

```
git clone https://github.com/OpenChannelSSD/linux.git
```

qemu-nvme에서 제공되는 kernel config file을 다운받은 kernel폴더에 옮겨 줍니다.

```
cd linux
cp ~/qemu-nvme/kernel.config ./.config
```

파일을 복사한 뒤에 .config파일을 열어 다음의 내용을 확인합니다.

```
# For NVMe support
CONFIG_BLK_DEV_NVME=y
# For LightNVM support
CONFIG_NVM=y
# Expose the /sys/module/lnvm/parameters/configure_debug interface
CONFIG_NVM_DEBUG=y
# Target support (required to expose the open-channel SSD as a block device)
CONFIG_NVM_PBLK=y
```

이후 make로 컴파일을 진행합니.

```
make -j '# of core'
```

make를 하게 되면 여러가지 옵션을 선택하는 창이 나오는데 전부 enter를 눌러줍니다.

### qemu 실행

다음 명령어로 qemu를 실행시킵니다.

tcp설정을 하기 때문에, ```ssh 'username'@localhost -p 2222```를 통햇 접속 할 수 있습니다.

```
sudo qemu-system-x86_64 \
    -hda ubuntu.img \
    -m 8G -smp 4 -cpu host --enable-kvm \
    -vnc :2 \
    -blockdev ocssd,node-name=nvme01,file.driver=file,file.filename=ocssd.img \
    -device nvme,drive=nvme01,serial=deadbeef,id=lnvm \
    -net user,hostfwd=tcp::2222-:22 \
    -net nic \
    -kernel ./linux/arch/x86_64/boot/bzImage -append 'root=/dev/sda1 console=ttr0 nokaslr'
```

## QEMU 내부 설정
### OCSSD 디바이스 설정

다음 명령어를 통해 nvme-cli를 설치합니다.

```
sudo apt install git make gcc
git clone https://github.com/linux-nvme/nvme-cli
cd nvme-cli
make -j '# of core'
sudo make install
```

설치 후 아래 명령어를 수행합니다.

```
sudo nvme lnvm list
```

수행 시 다음과 같이 ocssd디바이슥 인식이 되어야 합니.

```
Number of devices: 1
Device      	Block manager	Version
nvme0n1     	gennvm      	(1,0,0)
```

다음 명령어를 실행하여 OCSSD를 OS에 mount합니다.

```
sudo nvme lnvm init -d nvme0n1
sudo nvme lnvm create -d nvme0n1 -n mydevice -t pblk -b 0 -e 3
sudo mkfs.ext4 /dev/mydevice
sudo mkdir /mnt/nvme
sudo mount /dev/mydevice /mnt/nvme
sudo chown username:username /mnt/nvme
```
