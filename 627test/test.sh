#!/bin/bash
time ./run < a1.in > a.out && diff -b a.out a1.out
time ./run < a2.in > a.out && diff -b a.out a2.out
time ./run < a3.in > a.out && diff -b a.out a3.out
time ./run < a4.in > a.out && diff -b a.out a4.out
time ./run < a5.in > a.out && diff -b a.out a5.out
time ./run < a6.in > a.out && diff -b a.out a6.out
time ./run < a7.in > a.out && diff -b a.out a7.out
time ./run < a8.in > a.out && diff -b a.out a8.out
time ./run < a9.in > a.out && diff -b a.out a9.out
time ./run < a10.in > a.out && diff -b a.out a10.out
