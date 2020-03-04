#!/bin/bash

cat access_log.txt |
grep js |
cut -d"/" -f5 |
grep -v css |
sort -u
