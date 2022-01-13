import Data.List
import System.IO

fac :: (Integral a) => a -> a
fac 0 = 1
fac n = n * fac (n-1)

main :: IO ()
main = print $ fac 5
