find . -iname *.h -o -iname *.cpp -o -iname *.hpp -print | xargs clang-format -style=file
