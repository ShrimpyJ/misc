--------------------------------------------------------------------------------
import Data.List
import System.IO

-- Int
doubleMe x = x + x
doubleUs x y = doubleMe x + doubleMe y
doubleSmallNumber x = if x > 100 then x else x*2

--Set Comprehension
boomBangs xs = [if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]
allMultiples xs ys = [x*y | x <- xs, y <- ys]
length' xs = sum [1 | _ <- xs]
removeLowercase st = [c | c <- st, c `elem` ['A'..'Z']]
removeUppercase st = [c | c <- st, c `elem` ['a'..'z']]
removeOdds xxs = [ [ x | x <- xs, even x ] | xs <- xxs]

--Tuples
triangles = [ (a,b,c) | c <- [1..10], b <- [1..10], a <- [1..10] ]
rightTriangles = [ (a,b,c) |
                    c <- [1..10], b <- [1..c], a <- [1..b],
                    a^2 + b^2 == c^2 ]
rightTriangles' = [ (a,b,c) |
                     c <- [1..10], b <- [1..c], a <- [1..b],
                     a^2 + b^2 == c^2, a+b+c == 24 ]

--Graph
adj = [ [2,4,5], [1,3,4,5,6], [2,5,6],
        [1,2,5,7,8], [1,2,3,4,6,7,8,9, [2,3,5,8,9]
        [4,5,8], [4,5,6,7,9], [5,6,8] ]

visited = [0,0,0,0,0,0,0,0,0]

traverseDF :: Tree a -> [a]
traverseDF Empty        = []
traverseDF (Node a l r) = a : (traverseDF 1) ++ (traverseDF r)

dfs as, vs = 
main :: IO ()
main = return ()
