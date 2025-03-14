find . -regextype egrep -regex ".*\.(c|cc|cpp|h|hh)$" \
  -not -path '*/install/*' \
  -not -path '*/build/*' \
  -not -path '*/log/*' \
  -not -path '*/dependencies/*' \
  -not -path '*/test/*/glad.c' \
  -not -path '*/test/*/config.h' \
  -not -path '*/*/glad.c' \
  -not -path '*/*/stb_image.h' \
  -not -path '*/*/material.cc' \
  -not -path '*/*/material.h' \
  | xargs clang-format-7 -i
 
