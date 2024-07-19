{-
Codigo elaborado por || Coding done by
Leonardo Pereira
Murilo R.
-}

-- The idea is extracting three insights from the dados.csv file, given 4 entries n1,n2,n3,n4
-- 1 - The sum of "Active" of all countries which confirmed is bigger than n1
-- 2 - Whithin n2 countries, the sum of "Deaths" in the n3 countries with the lowest number of "Confirmed"
-- 3 - A list of the n4 countries with the largest values for "Confirmed" 

import System.IO
import Data.Text (replace)
import Data.List

-- Function to replace commas from csv and dashes not to interfere with words
replaceCommaWithSpace :: String -> String
replaceCommaWithSpace [] = []
replaceCommaWithSpace (x:xs)
    | x == ' ' = '-' : replaceCommaWithSpace xs
    | x == ','  = ' ' : replaceCommaWithSpace xs
    | otherwise = x : replaceCommaWithSpace xs

-- Function removes dashes from replaceCommaWithSpace
removeDash :: String -> String
removeDash [] = []
removeDash (x:xs)
    | x == '-' = ' ' : removeDash xs
    | otherwise = x : removeDash xs
    
main :: IO ()
main = do
  h <- openFile "dados.csv" ReadMode 
  c <- hGetContents h

  line <- getLine
  let numbers = map read (words line) :: [Int]
  let n1 = head numbers
  let n2 = numbers !! 1
  let n3 = numbers !! 2
  let n4 = numbers !! 3

  
  let numbercountries = length $ lines c

  -- CSV preprocessing into a list (lines) of lists(columns) of strings(data)
  let preprocessing = map (words . replaceCommaWithSpace) (lines c)

  -- Each column broken into their own list and typecasted when necessary
  let countries = map (removeDash . head) preprocessing
  let chartdataConfirmed :: [Int] = map (read . (!! 1)) preprocessing
  let chartdataDeaths :: [Int] = map (read . (!! 2)) preprocessing
  let chartdataRecovery :: [Int] = map (read . (!! 3)) preprocessing
  let chartdataActive :: [Int] = map (read . (!! 4)) preprocessing

  
  let result1 = sum $                                -- Sum of Confirmed
                map snd $                            -- Maps to list of just Confirmed
                filter (\(x,y) -> x >= n1) $         -- Removes Confirmed lower than n1
                zip chartdataConfirmed chartdataActive  -- Tuple (Confirmed,Active)

  let result2 = sum $                                -- Sum of Deaths
                map snd $                            -- Maps to list of just Deaths
                take n3 $                            -- n3 Highest Confirmed Countries
                sort $                               -- Sorts (Lowest Confirmed First)
                map snd $                            -- Maps to Tuple (Confirmed,Deaths)
                drop (numbercountries-n2) $          -- n2 Lowest Confirmed Countries
                sort $                               -- Sorts (Lowest Active First)
                zip chartdataActive $                -- Tuple (Active,(Confirmed,Deaths))
                zip chartdataConfirmed chartdataDeaths  -- Tuple (Confirmed,Deaths)

  let result3 = sort $                               -- Sorts Countries alphabetically
                map snd $                            -- Maps to list of just Countries
                drop (numbercountries-n4) $          -- n4 Lowest Confirmed Countries
                sort $                               -- Sorts (Lowest Confirmed First)
                zip chartdataConfirmed countries     -- Tuple(Confirmed,Country)
  
  print result1
  print result2
  
  -- Receives a list of strings, apllies PutStrLn to each and returns a IO action
  -- printing each string with a new line in between
  mapM_ putStrLn result3   
  
  hClose h
  
