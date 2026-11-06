#! /bin/bash
set -e
mkdir -p $HOME/.local/bin/rng
if ! command -v gcc &> /dev/null; then
    echo "install gcc"
    exit 1
fi
if ! command -v git &> /dev/null; then
    echo "install git"
    exit 1
fi
libst="$HOME/rngtmp"
mkdir -p $libst
cd $libst
git clone https://github.com/kitty057/rng.git
cd rng
gcc -O3 -static $libst/rng/rng.c -o $HOME/.local/bin/rng/rng
rm -rf $libst
if [[ -f "$HOME/.bashrc" ]]; then
    echo 'export PATH="$PATH:$HOME/.local/bin/rng/"' >> ~/.bashrc
elif [[ -f "$HOME/.zshrc" ]]; then
    echo 'export PATH="$PATH:$HOME/.local/bin/rng/"' >> ~/.zshrc
fi
