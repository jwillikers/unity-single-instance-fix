#!/usr/bin/env bash

gcc unity-single-instance-fix.c -o libunity-single-instance-fix.so -ldl -shared -fPIC
