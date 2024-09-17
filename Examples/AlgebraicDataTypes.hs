-- AlgebraicDataTypes.hs
--
-- CECS 342
-- Haskell vs C
-- 
-- Algebraic Data Types


module AlgebraicDataTypes where

import Data.Foldable

-----------------
-- (1) Co-Product (disjunction, enumeration)
-----------------
data Gender = Female | Male deriving (Show, Eq)

isMale :: Gender -> Bool
isMale Male = True
isMale _    = False

isFemale g = case g of
                Female     -> True
                otherwise  -> False

--------------
-- (2) Product (conjunction, tuple, struct)
--------------
data Person = Person String Int Gender deriving (Show, Eq)

name :: Person -> String
name   (Person n a g) = n

age :: Person -> Int
age    (Person n a g) = a 

gender :: Person -> Gender
gender (Person n a g) = g


-- Declare an order on persons (by name)
instance Ord Person where
  p <= q = name p <= name q

-- A list of some people
somePeople = [Person "Alice" 19 Female, Person "Bob" 20 Male, Person "Carol" 17 Female, Person "Dave" 30 Male]


-- Haskel can help to define the projections
data Person' = Person' {
                 name'   :: String,
                 age'    :: Int,
                 gender' :: Gender }
                   deriving (Show, Eq)

---------------------
-- (3) Type Recursion
---------------------
--   Refer to the type we're defining inside its own definition.

-- Make our own list type (to understand how lists work)
data List a = Nil | Cons a (List a) deriving Show

-- Make our own lists foldable
instance Foldable List where
  foldr f z Nil = z
  foldr f z (Cons a as) = f a (foldr f z as)


-- A binary tree data structure
data Tree a = Tip | Branch (Tree a) a (Tree a) deriving Show


-- Tree traversal

-- Traverse in order
inOrder :: Tree a -> [a]
inOrder Tip = []
inOrder (Branch l a r) = inOrder l ++ [a] ++ inOrder r

-- Traverse in order with an accumulating parameter
inOrder' :: Tree a -> [a] -> [a]
inOrder' Tip = \x -> x
inOrder' (Branch l a r) = inOrder' l . (a:) . inOrder' r


-- Traverse in order by making our trees foldable
instance Foldable Tree where
  foldr f z Tip            = z
  foldr f z (Branch l m r) = foldr f (f m (foldr f z r)) l

-- toList = foldr (:) []


-- Traverse pre order
preOrder' :: Tree a -> [a] -> [a]
preOrder' Tip = \x -> x
preOrder' (Branch l a r) = (a:) . preOrder' l . preOrder' r 

-- Traverse post order
postOrder' :: Tree a -> [a] -> [a]
postOrder' Tip = \x -> x
postOrder' (Branch l a r) = postOrder' l . postOrder' r . (a:)


-- Traverse in level order
levels :: Tree a -> [[a]]
levels Tip = [[]]
levels (Branch l m r) = [m] : combine (levels l) (levels r)
  where
    combine [] ys = ys
    combine xs [] = xs
    combine (x:xs) (y:ys) = (x++y) : combine xs ys


-- Insert an element into a sorted tree
insert :: Ord a => a -> Tree a -> Tree a
insert a Tip = Branch Tip a Tip
insert a (Branch l p r) | a <= p    = Branch (insert a l) p r
                        | otherwise = Branch l p (insert a r)

-- Convert a list to a sorted tree
toTree :: Ord a => [a] -> Tree a
toTree = foldr insert Tip

-- Use our tree data structure for sorting
sort :: Ord a => [a] -> [a]
sort = toList . toTree