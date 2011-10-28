#!/bin/sh
for i in apg bpg ig ug; do
  wget -nc http://clipsrules.sourceforge.net/documentation/v630/${i}.pdf
done
