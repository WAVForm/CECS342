echo Making the executable files
gcc arraymaker.c -o arraymaker
gcc assignment1.c -o assignment1C

echo Testing C Program
CARRAYS=$(./arraymaker 100 c)
./assignment1C $CARRAYS


echo Testing Haskell Program
echo note: I couldn\'t figure out how to do command line arguments, so I ran the file in interpreted mode
HARRAYS=$(./arraymaker 100 h)
IFS=' '
read -ra arr <<< "$HARRAYS"
for val in "${arr[@]}";
do
  ghci -v0 <<EOF
  :add assignment1.hs
  isSorted(mergeSort $val)
  isSorted(quickSort $val)
  :quit
EOF
done

echo Removing executables
echo Haskell is so slow because we open and close ghci each time
rm arraymaker
rm assignment1C