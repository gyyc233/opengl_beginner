find . -regextype egrep -regex ".*\.(c|cc|cpp|h|hh)$" -not -path '*/install/*' \
  -not -path '*/build/*' -not -path '*/log/*' -not -path '*/dependencies/*' -not -path '*/test/*/glad.c' -not -path '*/test/*/config.h'| xargs clang-format-7 -i
 
