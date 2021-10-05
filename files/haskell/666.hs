import Data.List
import System.IO
import qualified Data.Text    as Text
import qualified Data.Text.IO as Text
import Text.Printf

add :: Integer -> Integer -> Integer
add a b = a + b

fac :: Integer -> Integer
fac n = if n < 2 then 1 else n * fac (n-1)

it :: String -> Integer -> Integer
it str n =
  if length str == 0
    then 0
    else
      it (drop 1 str) (lookup (take 1 str) table)

base = 6
baselist = map (*base) [1 .. 26]
alpha = ['a' .. 'z']
table = zip alpha baselist
str = "hello"

main :: IO ()
main = do
  lines <- fmap Text.lines (Text.readFile "/home/pete/words.txt")
  print(add 2 5)
  print(fac 5)
  print(it str 0)
