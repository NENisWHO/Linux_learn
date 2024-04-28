#!/bin/bash 


echo "before shift"
echo '$0:'$0
echo '$1:'$1
echo '$2:'$2
echo '$3:'$3
echo '$4:'$4
echo '$5:'$5 
echo '$#:'$#
echo '$@:'$@
echo '$*:'$*
echo '$$:'$$


shift
echo "after shift"
echo '$0:'$0
echo '$1:'$1
echo '$2:'$2
echo '$3:'$3
echo '$4:'$4
echo '$5:'$5 
echo '$#:'$#
echo '$@:'$@
echo '$*:'$*
echo '$$:'$$


