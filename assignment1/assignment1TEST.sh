echo Making the executable files
gcc arraymaker.c -o arraymaker
gcc assignment1.c -o assignment1C

echo Testing for edge cases

echo =Empty Set=
echo "C: $(./assignment1C )"
echo "Haskell: $(runhaskell assignment1.hs )"

echo =Single Element=
echo "C: $(./assignment1C 1)"
echo "Haskell: $(runhaskell assignment1.hs [1])"

echo =Already Sorted=
echo "C: $(./assignment1C 1,2,3,4,5)"
echo "Haskell: $(runhaskell assignment1.hs [1,2,3,4,5])"

echo =Negatives=
echo "C: $(./assignment1C 10,0,-2,-1,-7,2)"
echo "Haskell: $(runhaskell assignment1.hs [10,0,-2,-1,-7,2])"

echo "=Other Types (Haskell only...)"
echo "Single string"
{
  echo ":add assignment1.hs"
  echo "isSorted(mergeSort [\"Hello\"])"
  echo "isSorted(quickSort [\"Hello\"])"
  echo ":quit"
} | ghci --interactive
echo "Multiple strings"
{
  echo ":add assignment1.hs"
  echo "isSorted(mergeSort [\"apple\", \"Banana\", \"cherry\", \"date\", \"Elderberry\", \"fig\", \"grape\", \"Honeydew\", \"kiwi\", \"Lemon\"])"
  echo "isSorted(quickSort [\"apple\", \"Banana\", \"cherry\", \"date\", \"Elderberry\", \"fig\", \"grape\", \"Honeydew\", \"kiwi\", \"Lemon\"])"
  echo
  echo ":quit"
} | ghci --interactive
echo "Floats"
{
  echo ":add assignment1.hs"
  echo "isSorted(mergeSort [3.14, 1.59, 2.65, 4.28, 0.99, 5.0, 3.0, 2.72, 6.63, 1.41])"
  echo "isSorted(quickSort [3.14, 1.59, 2.65, 4.28, 0.99, 5.0, 3.0, 2.72, 6.63, 1.41])"
  echo
  echo ":quit"
} | ghci --interactive

echo "LOOK AT SYSTEM MONITOR FOR MEM USAGE"
sleep 5

echo =Stress Test C Program=
CTIMESTART=$(date +"%s.%N")
CARRAYS=$(./arraymaker 1 c)
./assignment1C $CARRAYS
CARRAYS=$(./arraymaker 10 c)
./assignment1C $CARRAYS
CARRAYS=$(./arraymaker 100 c)
./assignment1C $CARRAYS
CARRAYS=$(./arraymaker 1000 c)
./assignment1C $CARRAYS
CARRAYS=$(./arraymaker 10000 c)
./assignment1C $CARRAYS
CARRAYS=$(./arraymaker 50000 c)
./assignment1C $CARRAYS
CTIMEEND=$(date +"%s.%N")
echo "Time Taken: $(echo "$CTIMEEND - $CTIMESTART" | bc)"

echo "LOOK AT SYSTEM MONITOR FOR MEM USAGE"
sleep 5

echo =Stress Test Haskell Program=
HTIMESTART=$(date +"%s.%N")
HARRAYS=$(./arraymaker 1 h)
runhaskell assignment1.hs $HARRAYS
HARRAYS=$(./arraymaker 10 h)
runhaskell assignment1.hs $HARRAYS
HARRAYS=$(./arraymaker 100 h)
runhaskell assignment1.hs $HARRAYS
HARRAYS=$(./arraymaker 1000 h)
runhaskell assignment1.hs $HARRAYS
HARRAYS=$(./arraymaker 10000 h)
runhaskell assignment1.hs $HARRAYS
HARRAYS=$(./arraymaker 50000 h)
runhaskell assignment1.hs $HARRAYS
HTIMEEND=$(date +"%s.%N")
echo "Time Taken: $(echo "$HTIMEEND - $HTIMESTART" | bc)"

echo Removing executables
rm arraymaker
rm assignment1C