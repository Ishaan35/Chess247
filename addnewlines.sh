find . -type f \( -name "*.in" -o -name "*.txt" \) -exec sed -i -e '$a\' {} \;

find . -type f \( -name "*.h" -o -name "*.cc" \) -exec sed -i -e '$a\' {} \;

find . -type f -name "makefile" -exec sed -i -e '$a\' {} \;
