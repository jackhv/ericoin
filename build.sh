#!/bin/bash

set -e

date
ps axjf

#################################################################
# Update Ubuntu and install prerequisites for running ERI   #
#################################################################
sudo apt-get update
#################################################################
# Build ERI from source                                     #
#################################################################
NPROC=$(nproc)
echo "nproc: $NPROC"
#################################################################
# Install all necessary packages for building ERI           #
#################################################################
sudo apt-get install -y qt4-qmake libqt4-dev libminiupnpc-dev libdb++-dev libdb-dev libcrypto++-dev libqrencode-dev libboost-all-dev build-essential libboost-system-dev libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libssl-dev libdb++-dev libssl-dev ufw git
sudo add-apt-repository -y ppa:bitcoin/bitcoin
sudo apt-get update
sudo apt-get install -y libdb4.8-dev libdb4.8++-dev

cd /usr/local
file=/usr/local/ERI
if [ ! -e "$file" ]
then
        sudo git clone https://github.com/BPbpBpb/ERIcoin
fi

cd /usr/local/ERI/src
file=/usr/local/ERI/src/ERId
if [ ! -e "$file" ]
then
        sudo make -j$NPROC -f makefile.unix
fi

sudo cp /usr/local/ERI/src/ERId /usr/bin/ERId

################################################################
# Configure to auto start at boot                                      #
################################################################
file=$HOME/.ERI
if [ ! -e "$file" ]
then
        sudo mkdir $HOME/.ERI
fi
printf '%s\n%s\n%s\n%s\n' 'daemon=1' 'server=1' 'rpcuser=u' 'rpcpassword=p' | sudo tee $HOME/.ERI/ERI.conf
file=/etc/init.d/ERI
if [ ! -e "$file" ]
then
        printf '%s\n%s\n' '#!/bin/sh' 'sudo ERId' | sudo tee /etc/init.d/ERI
        sudo chmod +x /etc/init.d/ERI
        sudo update-rc.d ERI defaults
fi

/usr/bin/ERId
echo "ERI has been setup successfully and is running..."
exit 0

