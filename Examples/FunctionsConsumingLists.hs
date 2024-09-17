-- FunctionsConsumingLists.hs
--
-- CECS 342
-- Haskell vs C
--
-- Functions consuming lists


module FunctionsConsumingLists where

import Prelude hiding (head, tail, sum, product, length, foldr)


-- List syntax in Haskell:
list1 = [1, 2, 3]           -- syntactic sugar
list2 = 1 : 2 : 3 : []
list3 = 1 : (2 : (3 : []))  -- list construction

-- Strings are just lists of charcters:
list4 = "This is a list of characters."


-- Some simple functions on lists
--   using pattern matching to deconstruct lists:
head (x:xs) = x   -- get the first element
tail (x:xs) = xs  -- drop the first element


-- Some recursive functions on lists:
sum     []     = 0
sum     (x:xs) = x + sum     xs

product []     = 1
product (x:xs) = x * product xs

length  []     = 0
length  (x:xs) = 1 + length  xs


-- The above functions share the same recursion pattern:
foldr f z [] = z
foldr f z (x:xs) = x `f` (foldr f z xs)
-- Intuitively foldr combines elements from the right:
--   foldr (+) 0 [1, 2, 3]
--     == foldr (+) 0 (1 : (2 : (3 : [])))
--     ==              1 + (2 + (3 +  0))


-- Thus we can define them in terms of foldr:
sum'     = foldr (+)             0
product' = foldr (*)             1
length'  = foldr (\a b -> 1 + b) 0
