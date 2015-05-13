#!/bin/bash

for f in *.so.2.4.9
do
	f=${f#'.so.2.4.9'}
	f=${f%'.so.2.4.9'}
	ln -s $f.so.2.4.9 $f.so.2.4
	ln -s $f.so.2.4 $f.so 
done
