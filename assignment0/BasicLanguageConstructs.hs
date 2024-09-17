module BasicLanguageConstructs where

--Variables
seven = 7

sq123 = let x = 123 in x * x

sq321 = x * x where x = 321

--Functions
twice1 n = 2 * n --regular

twice2 = \n -> 2 * n --lambda

twice3 = (2*) --section

average1 :: Float -> Float -> Float
average1 a b = (a+b)/2
average2 a = \b -> (a+b)/2
average3 = \a -> \b -> (a+b)/2
average4 = \a b -> (a+b)/2

h = average1 2

average5 :: (Float, Float) -> Float
average5(a, b) = (a+b)/2

--Conditionals
signum1 n = if n<0 then      -1
            else if n>0 then 1
            else             0

--Piece-wise functions with guards
signum2 n | n < 0     = -1
          | n > 0     = 1
          | otherwise = 0

--Recursion

--Factorial with if-then-else
factorial1 n = if n==0 then 1 else n * (factorial1(n-1))

--Factorial with pattern matching
factorial2 0 = 1
factorial2 n = n * (factorial2(n-1))

--Factorial with accumulating parameter
factorial3 n = fact_acc n 1
               where
                   fact_acc 0 f = f
                   fact_acc n f = fact_acc(n-1) (n*f)

--Factorial with a list of range of numbers
factorial4 n = product[1..n]

--Naive fibonacci numbers
fib1 0 = 0
fib1 1 = 1
fib1 n = fib1(n-2) + fib1(n-1)

--Fibonacci numbers with two accumulating parameters
fib2 n = fib_acc n 0 1
         where
             fib_acc 0 a _ = a
             fib_acc n a b = fib_acc (n-1) b (a+b)

