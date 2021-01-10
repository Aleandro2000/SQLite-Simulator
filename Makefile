build:
	(mkdir Linux&&g++ "sqlite".cpp -o ./Linux/"sqlite")||g++ "sqlite".cpp -o ./Linux/"sqlite"
	(mkdir Windows-32&&i686-w64-mingw32-g++ -o ./Windows-32/"sqlite".exe "sqlite".cpp)||i686-w64-mingw32-g++ -o ./Windows-32/"sqlite".exe "sqlite".cpp
	(mkdir Windows-64&&x86_64-w64-mingw32-g++ -o ./Windows-64/"sqlite".exe "sqlite".cpp)||x86_64-w64-mingw32-g++ -o ./Windows-64/"sqlite".exe "sqlite".cpp
linux-run:
	./Linux/"sqlite"