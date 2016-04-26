#!/bin/bash
#source /afs/phas.gla.ac.uk/system/sl6x/x86_64/gcc/4.8.2/setup.sh

#export C=/afs/phas.gla.ac.uk/system/sl6x/x86_64/gcc/4.8.2/bin/g++
#and for CXX

#export ROOTSYS=/data/ppe01/sl6x/x86_64/root/5.34.00
#///////
#ls /afs/cern.ch/sw/lcg/external/gcc/4.8.1/i686-slc6-gcc48-opt/setup.sh

#source  /afs/cern.ch/sw/lcg/contrib/gcc/4.7.1/x86_64-slc6/setup.sh
#export CXX=/afs/cern.ch/sw/lcg/contrib/gcc/4.7.1/x86_64-slc6/bin/g++
#export C=/afs/cern.ch/sw/lcg/contrib/gcc/4.7.1/x86_64-slc6/bin/g++
#export CXX=/afs/cern.ch/sw/lcg/contrib/gcc/4.7.2/x86_64-slc6/bin/g++
#export C=/afs/cern.ch/sw/lcg/contrib/gcc/4.7.2/x86_64-slc6/bin/g++
source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.26/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh
export LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH
source /afs/cern.ch/sw/lcg/contrib/gcc/4.6.2/x86_64-slc6/setup.sh

#setupATLAS 
#lSetupROOT
