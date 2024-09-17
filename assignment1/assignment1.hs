module Assignment1 where

--Helpers
foldR f b [] = b
foldR f b (x:xs) = x `f` (foldR f b xs)

isSorted :: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [x] = True
isSorted (x:y:xs) = x <= y && isSorted(y:xs)


merge :: (Ord a) => [a] -> [a] -> [a]
merge [] [] = []
merge [] r = r
merge l [] = l
merge (l:ls) (r:rs)
    | l <= r    = l: merge ls (r:rs) --put l first then continue merge on the rest of l and r
    | otherwise = r: merge (l:ls) rs --put r first then continue merge on the rest of l and r

split :: (Ord a) => [a] -> ([a],[a])
split [] = ([], [])
split (x:xs) = foldR put ([],[]) (x:xs)


put x (l,r) = (x:r, l)

quickSort :: Ord a => [a] -> [a]
--from learn you a haskell
quickSort [] = []
quickSort (x:xs) = left ++ [x] ++ right
    where left = quickSort [a | a <- xs, a <= x]
          right = quickSort [a | a <- xs, a > x]

mergeSort :: Ord a => [a] -> [a]
mergeSort [] = []
mergeSort [x] = [x]
mergeSort list = merge l r
    where l = mergeSort tl
          r = mergeSort tr
          (tl,tr) = split list


