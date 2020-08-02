OCSSD Install
====
Environment
-----
OS : Ubuntu Linux 18.04 LTS

Installation
-----
필수 패키지 설치

```
sudo apt install libglib2.0-dev libpixman-1-dev 
```

qemu 설치

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

Open-Channel 2.0 SSD 설정

```
cd ~
mkdir ocssd
cd ocssd
//ocssd img
qemu-img create -f ocssd -o num_grp=2,num_pu=4,num_chk=60 ocssd.img
//ubuntu disk
qemu-img create -f qcow2 -o preallocation=full ubuntu.img 40G
```

qemu linux 설정

```
wget https://releases.ubuntu.com/18.04/ubuntu-18.04.4-desktop-amd64.iso
sudo qemu-system-x86_64 -hda ubuntu.img -boot d -cdrom ubuntu-18.04.4-desktop-amd64.iso -m 'memory size(e.g. 8G)' -smp '# of core' -cpu host --enable-kvm -vnc :2
```

이후 리미너를 통해서 ubuntu linux 설치를 완료한다.
