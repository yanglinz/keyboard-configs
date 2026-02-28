#!/usr/bin/env bash

git ls-files -z -- '*.c' '*.cpp' '*.h' '*.hpp' | xargs -0 clang-format -style=file -i
