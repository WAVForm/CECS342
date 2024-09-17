-- FunctionsProducingLists.hs
--
-- CECS 342
-- Haskell vs C
--
-- Functions producing lists


module FunctionsProducingLists where

import Prelude hiding (map, filter, foldl, flip, reverse)
import Data.Char (toUpper)


-- Apply a function to each element in a list
map f [] = []
map f (x:xs) = f x : map f xs


-- Filter out all elements that have property p
filter p [] = []
filter p (x:xs) = if p x
  then x : filter p xs
  else     filter p xs


-- Tail recursive fold with an accumulating parameter
foldl f z [] = z
foldl f z (x:xs) = foldl f (f z x) xs
-- Intuitively foldl combines the elements from the left:
--  foldl (+) 0 [1, 2, 3] == ((0 + 1) + 2) + 3


-- Flip the arguments of any 2-argument-function
flip f a b = f b a

-- Reverse a list
reverse :: [a] -> [a]
reverse = foldl (flip (:)) []
