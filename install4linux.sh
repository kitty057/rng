#! /bin/bash
echo "you need wget for this to run so if you dont have that, download it"
echo "on arch based its \"sudo pacman -Syy wget\" on debian its \"sudo apt update && sudo apt install wget\""
echo "check what distro you have with \"uname -r\" and if that has a name in it"
echo "like for me it has artix in it then google the package manager for that distro. so install wget."
mkdir -p $HOME/.local/bin/rng
if ! command -v wget &> /dev/null; then
    echo "install wget"
    exit 1
fi
if ! command -v gcc &> /dev/null; then 
    echo "install gcc"
    exit 1
fi
libst="$HOME/libsodium-temp"
mkdir -p $libst
cd $libst
if  compgen -G "$libst/*.tar.gz" > /dev/null; then 
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
cd $libst
git clone https://github.com/kitty057/rng.git
cd rng
gcc -O3 rng.c -o $HOME/.local/bin/rng/rng -static -L/usr/local/lib -lsodium
if [[ -f "$HOME/.bashrc" ]]; then 
    echo "export PATH=\"\$PATH:\$HOME/.local/bin/rng/\"" >> ~/.bashrc
elif [[ -f "$HOME/.zshrc" ]]; then 
    echo "export PATH=\"\$PATH:\$HOME/.local/bin/rng/\"" >> ~/.zshrc
fi
