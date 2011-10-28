#!/bin/sh
mkdir html
cd html
for i in apg bpg ig ug; do
  wget -nc -p -nH --cut-dirs=2 --convert-links http://clipsrules.sourceforge.net/documentation/v630/${i}.htm
  dos2unix ${i}.htm
done
cd ..

