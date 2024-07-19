-- Código desenvolvido por / Coding done by
-- Leonardo Pereira
-- Murilo R.
import Data.List (intercalate)

-- A função calcularPontuacao recebe uma lista de inteiros representando as pontuações em uma partida de boliche
-- Retorna uma tupla contendo uma lista de strings representando os frames e o total da pontuação
calcularPontuacao :: [Int] -> ([String], Int)
calcularPontuacao jogadas = calcular jogadas 1 0 [] 0
  where
    -- A função interna calcular é responsável por calcular a pontuação e os frames do jogo
    calcular :: [Int] -> Int -> Int -> [String] -> Int -> ([String], Int)
    calcular _ frame total pontos _ | frame > 10 = (pontos, total)  -- Se todos os frames já foram calculados, retorna os pontos e o total
    calcular jogadas frame total pontos i
      | jogadas !! i == 10 =  -- Strike
        if frame < 10 then
          calcular jogadas (frame + 1) (total + 10 + jogadas !! (i + 1) + jogadas !! (i + 2)) (pontos ++ ["X _ |"]) (i + 1)
        else
          calcular jogadas (frame + 1) (total + 10 + jogadas !! (i + 1) + jogadas !! (i + 2)) (pontos ++ [formatarUltimoFrame jogadas i]) (i + 3)  -- Para o último frame, formata de maneira diferente
      | jogadas !! i + jogadas !! (i + 1) == 10 =  -- Spare
        if frame < 10 then
          calcular jogadas (frame + 1) (total + 10 + jogadas !! (i + 2)) (pontos ++ [show (jogadas !! i) ++ " / |"]) (i + 2)
        else
          calcular jogadas (frame + 1) (total + 10 + jogadas !! (i + 2)) (pontos ++ [formatarUltimoFrame jogadas i]) (i + 2)  -- Para o último frame, formata de maneira diferente
      | otherwise =  -- Normal
        if frame < 10 then
          calcular jogadas (frame + 1) (total + jogadas !! i + jogadas !! (i + 1)) (pontos ++ [show (jogadas !! i) ++ " " ++ show (jogadas !! (i + 1)) ++ " |"]) (i + 2)
        else
          calcular jogadas (frame + 1) (total + jogadas !! i + jogadas !! (i + 1)) (pontos ++ [show (jogadas !! i) ++ " " ++ show (jogadas !! (i + 1))]) (i + 2)  -- Para o último frame, formata de maneira diferente

    formatarUltimoFrame :: [Int] -> Int -> String
    formatarUltimoFrame jogadas i = unwords (map formatarJogada [ (-1,jogadas !! i) , (jogadas !! i, jogadas !! (i+1)) , (jogadas !! (i+1), jogadas !! (i+2)) ])


formatarJogada :: (Int, Int) -> String
formatarJogada (-1, 10) = "X"     --frame 10, strike na abertura
formatarJogada (-1, y) = show y   --frame 10, sem strike na abertura
formatarJogada (x, y)
  | x+y == 10 && x /= 10 = "/"    --frame 10, spare no meio
  | y == 10 && x >= 0 = "X"       --frame 10, strikes consecutivos ou strike apos spare
  | otherwise = show y

main :: IO ()
main = do
    input <- getLine
    let score = map read (words input) :: [Int]
    let (pontos, total) = calcularPontuacao score
    putStrLn $ unwords pontos ++ " | " ++ show total
