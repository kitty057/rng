#! /bin/bash
echo "you need wget for this to run so if you dont have that, download it\non arch based its \"sudo pacman -Syy wget\" on debian its \"sudo apt update && sudo apt install wget\" \n check what distro you have with \"uname -r\" and if that has a name in it like for me it has artix in it then google the package manager for that distro. so install wget."
libst="$HOME/libsodium-temp"
mkdir -p $libst
list=$(ls "$libst"|grep -i libsodium|grep -i .tar.gz)
cd $libst
if [[ "$list" == *".tar.gz"* ]]; then 
    cd $HOME
    rm -rf $libst/
    mkdir $libst
    cd $libst
fi
wget https://download.libsodium.org/libsodium/releases/libsodium-1.0.22-stable.tar.gz
tar -xzf $(ls $libst|grep -i libsodium|grep -i .tar.gz)
cd $(ls $libst|grep -i libsodium|grep -vi .tar.gz)
./configure
make
sudo make install
