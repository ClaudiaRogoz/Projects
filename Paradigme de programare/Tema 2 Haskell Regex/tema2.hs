import Data.List
import Debug.Trace

data Smth = NoMatch | Match 
	deriving (Show)




-- intoarce intreaga prima paranteza intalnita
getPara ::  [Char] -> Integer -> [Char]
getPara "" _ = ""

getPara str ok 
	| ((head str) == '(') && (ok == 0) = '(' : (getPara (tail str) 1) 
	| ((head str) == '(' ) && (ok > 0) = (head str ) : (getPara (tail str) (ok + 1)) 
	| ((head str) == ')' ) && ( ok == 1 ) = ')' : (getPara "" ok ) 
	| ((head str) == ')' ) && (ok /= 1 ) = (head str) : (getPara (tail str) (ok - 1)) 
	| ((head str) /= '(' ) && (ok == 0 ) = getPara (tail str) ok 
	| otherwise = (head str) : (getPara (tail str) ok  )
	
--intoarce prima paranteza patrata	
getParaP ::  [Char] -> Integer -> [Char]
getParaP "" _ = ""
getParaP str ok 
	| ((head str) == '[') && (ok == 0) = '[' : (getParaP (tail str) 1) 
	| ((head str) == '[' ) && (ok > 0) = (head str ) : (getParaP (tail str) (ok + 1)) 
	| ((head str) == ']' ) && ( ok == 1 ) = ']' : (getParaP "" ok ) 
	| ((head str) == ']' ) && (ok /= 1 ) = (head str) : (getParaP (tail str) (ok - 1)) 
	| ((head str) /= '[' ) && (ok == 0 ) = getParaP (tail str) ok 
	| otherwise = (head str) : (getParaP (tail str) ok  ) 

-- interiorul unei paranteze rotunde
getParaex ::  [Char] -> [Char]
getParaex "" = ""	
getParaex str = take ((length (tail (getPara str 0)) ) -1 ) (tail (getPara str 0))

-- intoarce interiorul unei paranteze patrate 
getParaPex ::  [Char] -> [Char]
getParaPex "" = ""	
getParaPex str = take ((length (tail (getParaP str 0)) ) -1 ) (tail (getParaP str 0))

-- ia prima chestie dupa prima paranteza 
getFA :: [Char] -> Char 

getFA str 
	|(drop  (length (getPara str 0 ) ) str ) /= "" =  (head (drop  (length (getPara str 0 ) ) str ) )
	| otherwise = '\0'

getFAP :: [Char] -> Char 

getFAP str 
	|(drop  (length (getParaP str 0 ) ) str ) /= "" =  (head (drop  (length (getParaP str 0 ) ) str ) )
	| otherwise = '\0'
--intoarce tot dupa paranteza curenta 
getAllA :: [Char] -> [Char] 
getAllA "" = ""
getAllA str = (drop  (length (getPara str 0 ) )  str )

--intoarce tot dupa paranteza curenta 
getAllAP :: [Char] -> [Char] 
getAllAP "" = ""
getAllAP str = (drop  (length (getParaP str 0 ) )  str )

-- verifica daca un String contine un |  or
hasOr :: [Char] -> Integer -> Bool 

hasOr "" _ = False 
hasOr str ok 
	| ( (head str) == '|' ) && ( ok == 1) = True
	| (ok == 0 ) && ( (head str) == '(') = hasOr (tail str) 1
	| ((head str) == ')') = False
	| ((head str) == '(') && (ok == 1) = False
	| otherwise = hasOr (tail str) ok
	
	
 
-- returneaza pozitia pe care se afla | 
getIndOr :: [Char] -> Int -> Int

getIndOr "" nr = nr
getIndOr str nr
	| (not (hasOr str 0 )) && (nr == 0) = -1 
	| ( (head str ) == '|' ) =  nr 
	| otherwise = (getIndOr (tail str) (nr +1))

-- returneaza prima pereche de OR adica pt a| b = (a , b) 
getPairOr :: [Char] -> ([Char],[Char])

getPairOr "" = ("","")

getPairOr str 
	| (hasOr str 0) =  ((tail ( take (getIndOr str 0) str) ),init ( tail (drop (getIndOr (getPara str 0) 0) (getPara str 0)))) 
 	| otherwise = ("","")
 



-- verifica daca un caracter este caracter special 
isSpecial :: Char -> Bool

isSpecial str = (str == '(')  || (str == ')')  ||(str == '*')  ||(str == '^')  || (str == '[')  ||(str == ']')  || (str == '|') || (str == '.')  


--verifica daca un String contine un caracter special 
hasSpecial :: [Char] -> Bool
hasSpecial "" = False
hasSpecial str = any isSpecial str


--gaseste nr de aparitii al caracterului c in sir 
getNrInt :: [Char] -> Char -> Int
getNrInt "" _  = 0
getNrInt str c = length (findIndices (\x -> x == c) str )




-- returneaza toate perechile de caractere unite prin -
getPairL :: [Char] -> Int -> [([Char],[Char])]
getPairL "" _ = [("","")]

getPairL str nr 
	| (nr >= 0 ) = ((take 1 str),(drop 2 (take 3 str ))) : (getPairL  (drop 3 str) (nr - 1 ) ) 
	| otherwise = getPairL "" nr

-- transforma un string [a-z] intr-o lista cu toate posibilitatile 
getInterval ::  [([Char],[Char])] -> [Char]
getInterval [] = ""
getInterval str =  [(head (fst (head str)))..(head (snd (head str)))] ++ (getInterval (tail str) )

getIndex :: Char -> String -> Int -> Int
getIndex c "" _  = -1
getIndex c str index 
	| (c == (head str) ) = index 
	| otherwise = getIndex c (tail str) (index + 1) 

-- distanta maxima
maxlength :: String -> Int

maxlength "" = 0
maxlength str = length (drop ( (getIndex '*' str 0 ) + 1)  str)  


--calculeaza distanta minima pana la sfarsitul unui sir sarind peste stelute
mindist :: String -> Int 
mindist "" = 0

mindist str 
	|  ( hasSA str) = mindist (tail (tail str)) 
	| otherwise = (1 + mindist (tail str))
	
	
--functie care calculeaza distanta minima pana la sfasitul sirului necesara pentru verificare in cazul stelutei daca este necesar sa continuam sau sa sarim peste * 
mindistP :: String -> Int 
mindistP "" = 0 
mindistP str 
	| ((getFA str) == '*') = (mindistP (tail (getAllA str)))
	| ((getFAP str) == '*') = (mindistP (tail (getAllAP str)))
	|  ( hasSA str) = mindistP (tail (tail str)) 
	| (hasOr ( getPara str 0) 0) =  (mindist (fst (getPairOr str ) )) + (mindist  (snd (getPairOr str ) ))
	| otherwise = ( 1 + mindistP (tail str)) 
	
	
--are steluta dupa 
hasSA :: String -> Bool
hasSA "" = False
hasSA (x:"") = False 
hasSA str = ((head (tail str) ) == '*' )

--functie care ne ajuta sa determinam daca este necesar sa mai dam append o data la continutul de sub steluta
promite :: String -> Char -> Bool
promite "" _ = False
promite str f
	| (( head str ) == '[') && ((head (getParaPex str)) /= '^') && (elem '-' (getParaPex str)) = elem f (getInterval (init (getPairL (getParaPex str) (getNrInt (getParaPex str) '-' )))) 
	| (( head str ) == '[') && ((head (getParaPex str)) == '^')  = (not (elem f (getParaPex str)))
	| (( head str ) == '[') && ((head (getParaPex str)) /= '^') && (not (elem '-' (getParaPex str))) = elem f (getParaPex str) 
	| (head (getParaex str )) == f = True
	| (head (getParaex str)) == '.' = True
	| (hasOr ( getPara str 0) 0) = (head (fst (getPairOr str ) ) == f) || (head (snd (getPairOr str ) ) == f)
	
	| otherwise = False



compileRegex :: String -> String  -> Bool

compileRegex "" "" = True
compileRegex _ "" = False
compileRegex "" _ = False	

compileRegex regex str
	--pentru un singura litera 
	| (not spec) &&  (not stel) && (hr == (head str) ) = compileRegex (tail regex) (tail str)
	--pentru litera cu steluta
	| (not spec) && stel && (mdreg < len) = compileRegex (hr : regex) str
	--pentru litera cu steluta dar care nu convine
	|  (not spec) && stel  && (mdreg == len) = compileRegex (drop ( (getIndex '*' regex 0 ) + 1)  regex) str
	-- pentru paranteza simpla cu steluta
	|spec && (hr == '(')  && (not special ) && (fsta == '*') && (mdP < len) && prom =  (compileRegex ((getParaex regex)++regex) str )  
	--pentru paranteza simpla cu steluta care nu convine
	|spec && (hr == '(')  && (not special ) && (fsta == '*') && (mdP < len) && (not prom) =  (compileRegex (tail (getAllA regex)) str )
	--pentru paranteza simpla care convine 
	|spec && (hr == '(')  && (not special ) && (fsta == '*') && (mdP == len) =  compileRegex (tail (getAllA regex)) str 

	--pentru paranteza simpla 
	|spec &&  (hr == '(')  && (not special ) = (compileRegex ((getParaex regex ) ++  (getAllA regex)) str)
	-- --pentru paranteza simpla care contine | cu steluta  
	| spec &&  (hr == '(') && (hasOr ( getPara regex 0) 0) && (fsta== '*' ) && prom && (mdP < len)  = compileRegex ((getPara  regex 0) ++ regex) str
	-- --pentru paranteza simpla care contine | cu steluta  
	| spec &&  (hr == '(') && (hasOr ( getPara regex 0) 0) && (fsta== '*' ) && prom && (mdP == len)  = compileRegex (tail (getAllA regex)) str
	--pentru paranteza simpla care contine |
	| spec &&  (hr == '(') && (hasOr ( getPara regex 0) 0) = (compileRegex ((fst (getPairOr regex ) ) ++ (getAllA regex) ) str) || (compileRegex ((snd (getPairOr regex ) ) ++ (getAllA regex) ) str)
	--paranteza patrata cu steluta 
	| spec && (hr == '[') && ((getFAP regex) == '*') && prom &&  (mdP < len) = compileRegex ((getParaP regex 0)++regex) str
	
	
	| spec && (hr == '[') && ((getFAP regex) == '*')  &&  (mdP == len) = compileRegex (tail (getAllAP regex)) str
	
	--pentru paranteza patrata care contine caret fara interval 
	|  (hr == '[') && ((head ppr) == '^') &&(not((getFAP regex) == '*') ) && (not (elem '-' ppr )) && (not (elem (head str) (tail ppr)))     = compileRegex (getAllAP regex) (tail str)
	--paranteza patrata fara interval 
	| spec && (hr == '[')&&(not((getFAP regex) == '*') )&& ((head ppr) /= '^') && ((getNrInt ppr '-' ) /=0) && (( getNrInt (getInterval (init (getPairL ppr (getNrInt ppr '-' )))) (head str)) /= 0 )  =  compileRegex (getAllAP regex) (tail str) 
	--paranteza patrata cu interval
	| spec && (hr == '[')&&(not((getFAP regex) == '*') ) && ((getNrInt ppr '-' ) ==0) && ((getNrInt ppr (head str) ) /=0) && ((head ppr) /= '^') = compileRegex (getAllAP regex) (tail str) 
	
	| spec && (hr == '[')&& (not((getFAP regex) == '*') ) && ((getNrInt ppr '-' ) /=0) && ((head ppr) == '^') && (( getNrInt (getInterval (init (getPairL (tail ppr) (getNrInt ppr '-' )))) (head str)) == 0 )   =  compileRegex (getAllAP regex) (tail str) 
	--punct cu steluta
	| spec && (hr == '.') && stel && (mdreg < length str) = compileRegex (hr: regex)  str 
	| spec && (hr == '.') && stel && (mdreg == length str) = compileRegex (drop 2 regex)  str 
	--pentru punct
	| spec && (hr == '.') && (not stel) = compileRegex (tail regex) (tail str)
	|  otherwise = False
		where
			spec = (isSpecial (head regex))  
			stel = (hasSA regex)
			special = (hasSpecial (getParaex regex ))
			mdreg = (mindist regex)
			fsta = (getFA regex)
			mdP = (mindistP regex)
			len = (length str)
			prom = (promite regex (head str))
			hr = (head regex)
			ppr = (getParaPex regex)
			
			
compileOne :: String -> String -> Smth
compileOne  regex str
	|(compileRegex regex str) == True = Match
	| otherwise = NoMatch

