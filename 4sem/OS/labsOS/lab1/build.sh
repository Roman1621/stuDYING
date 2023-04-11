#!/bin/sh

# build COM module
nasm lab1.s -fbin -o lab1.com
nasm lab1.s -fbin -o lab1bad.obj
# build EXE module
nasm -fobj lab1EXE.s -o lab1.obj