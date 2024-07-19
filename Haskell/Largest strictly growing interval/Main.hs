{-
Codigo elaborado por || Coding done by
Leonardo Pereira
-}

import Data.List -- map,tails,inits,length,concatMap,maximum


{- 
Function that receives a list of Integers and returns whether
it's a strictly growing list or not
Compares the head (x) to the head of the tail (y) similarly to
bubble sort and recursively does the same to the tail (y:xs)
-}
isGrowing :: [Int] -> Bool
isGrowing [] = True
isGrowing [_] = True
isGrowing (x:y:xs) = x < y && isGrowing (y:xs)


{- 
Function that receives a list of Integers and returns a list of
list of integers compromising of strictly of its strictly growing
subvectors
Concatenates the maps of each possible list starting from the
head (inits) with the each possible list ending in the last
element of the tail (tails)
Firstly filters out the cases of empty lists
Secondly filters out the cases where the list is not strictly
growing
-}
growingIntSubvectors :: [Int] -> [[Int]]
growingIntSubvectors x = filter isGrowing $ filter (not . null) $ concatMap inits (tails x)


{-
Function that receives a list of Integers and returns the
largest Subvector within it that is strictly growing
Given the list of all strictly growing subvectors maps each
to its length and then takes the max of said map
-}
largestGrowingIntSubvectorSize :: [Int] -> Int
largestGrowingIntSubvectorSize a = maximum $ map length $ growingIntSubvectors a

{-
Function that receives a string and returns the list of Integers
contained within it
Breaks up the string in a list of words separated by space
Maps it to a new list where each word is mapped to its Integer 
-}
readIntVector :: String -> [Int]
readIntVector input = map read (words input)


main :: IO ()
main = do
    input <- getLine
    let vectInt = readIntVector input
    let result = largestGrowingIntSubvectorSize vectInt
    putStr $ show result