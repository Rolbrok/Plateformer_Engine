#!/bin/sh

bspc rule -a output floating=true
build/output
bspc rule -r output floating=true
