-- Codigo elaborado por / Coding done by
-- Leonardo Pereira

import Data.List -- tail,map,zip
import System.IO -- getLine

--recebe um numero e retorna um bool caso for verdadeiro
--n será primo (True) se e somente se:
--n maior que 1
--o mod da divisao de n por x for 0, sendo x qualquer numero entre 2 e o arredondamento para baixo da conversao para Int da raiz quadrada de n
checkPrime :: Int -> Bool
checkPrime n = n > 1 && all (\x -> n `mod` x /= 0) [2..floor(sqrt(fromIntegral n))]


-- recebe 2 numeros e retorna uma lista de numeros primos filtrada por checkPrime
primesBetween :: Int -> Int -> [Int]
primesBetween a b = filter checkPrime [a..b]


-- recebe uma lista de tuplas (tamanho 2) de numeros e retorna uma lista de numeros
-- faz uma transformacao de tupla (x,y) para numero y-x
subtractTuples :: Num a => [(a, a)] -> [a]
subtractTuples tuples = map (\(x, y) -> y - x) tuples


-- funcao main que recebe IO
main :: IO ()
main = do
    --recebe input do terminal e converte IO string em Ints
    a <- getLine
    b <- getLine
    let aInt = read a :: Int
        bInt = read b :: Int

        primeNumbers = primesBetween aInt bInt

        -- pega a lista de numeros primos e a lista de numeros primos exceto a cabeça (cauda) e as junta para criar uma lista de tuplas (ultimo do numero da cauda nao forma uma tupla pois a primeira lista ja acabou)
        tuplesList = zip primeNumbers (tail primeNumbers)

        distances = subtractTuples tuplesList
        result = maximum distances
    print result