module Assignment1 where

--HELPERS
foldR f b [] = b
foldR f b (x:xs) = x `f` (foldR f b xs)

isSorted :: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [x] = True
isSorted (x:y:xs) = x <= y && isSorted(y:xs)
--        ^^^ cool!
--HELPERS

--QUICK SORT
quickSort :: Ord a => [a] -> [a]
--from learn you a haskell
quickSort [] = []
quickSort (x:xs) = left ++ [x] ++ right --combine left, x, and right
    where left = quickSort [a | a <- xs, a <= x] --sort a, whose elements come from xs and must be <= x
          right = quickSort [a | a <- xs, a > x] -- same as above ^ except where elements of a must be > x
--QUICK SORT

--MERGE SORT
mergeSort :: Ord a => [a] -> [a]
mergeSort [] = []
mergeSort [x] = [x]
mergeSort list = merge l r --merge left and right
    where (tl,tr) = split list --split left and right
          l = mergeSort tl --sort left
          r = mergeSort tr -- sort right

merge :: (Ord a) => [a] -> [a] -> [a]
merge [] [] = []
merge [] r = r
merge l [] = l
merge (l:ls) (r:rs)
    | l <= r    = l: merge ls (r:rs) --put l first then continue merge on the rest of l and r
    | otherwise = r: merge (l:ls) rs --put r first then continue merge on the rest of l and r

split :: (Ord a) => [a] -> ([a],[a])
split [] = ([], [])
split (x:xs) = foldR put ([],[]) (x:xs) --apply put to all elements

put x (l,r) = (x:r, l) --put x at the front of r and swap l and r so they are treated as the other
--MERGE SORT