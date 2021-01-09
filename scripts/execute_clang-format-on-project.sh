echo $PWD
find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\|h\)' -print -exec clang-format -style=file -i {} \;

