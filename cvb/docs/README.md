# Genrating docs
## Installing Doxygen:
in your home folder execute the following commands, command 3 will show the missing dependencies install them and execute again.
1. git clone git@github.com:doxygen/doxygen.git
2. cd doxygen
3. ./configure
4. make
5. make install

## Genrating Documentation:
in docs folder of cvb execute the following commands
2. doxygen cvb.cfg
3. ln -s html/annotated.html index.html

double click the index.html to see documentation in browser