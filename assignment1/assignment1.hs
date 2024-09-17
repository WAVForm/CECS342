module Assignment1 where

quickSort :: Ord a => [a] -> [a]
--pivot is first element since using lists
quickSort [] = []
quickSort (x:xs) = 
    let left = quickSort [a | a <- xs, a <= x]
        right = quickSort [a | a <- xs, a > x]
    in left ++ [x] ++ right


mergeSort :: Ord a => [a] -> [a]