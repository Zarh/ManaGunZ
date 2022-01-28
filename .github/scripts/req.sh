#!/bin/bash
apt-get update
apt-get -y upgrade
apt-get -y install autoconf automake bison build-essential bzip2 ccache curl \
flex git-core libelf-dev libgmp3-dev libncurses5-dev libssl-dev libtool \
libtool-bin libz-dev make patch pkg-config python python-dev subversion \
texinfo wget zip zlib1g-dev

