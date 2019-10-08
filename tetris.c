/*
Student: Apetroaie Razvan-Mihai
Grupa: 313CB
*/


#include <stdio.h>
#include <stdint.h>
#include <math.h>

//functie utilizata pentru calcularea scorului final
void gameOver(uint64_t map, int linePoints) 
{
	uint64_t mask = 1ul << 63;
	double score, zeroCount = 0.0;

	while(mask)
	{
		//prin deplasarea bitului "1" al mastii se numara aparitia bitului "0" in harta finala
		if((mask & map) == 0) 
		{
			zeroCount = zeroCount + 1.00f;
		}

		mask >>= 1;
	}

	score = sqrt(zeroCount) + pow(1.25, linePoints);

	printf("GAME OVER!\n");
	printf("Score:%.2f\n", score);
}

//functie utilizata pentru a verifica daca piesa introdusa se afla pe prima linie a hartii
int checkFirstLine(uint64_t piece) 
{
	//verificarea se face prin crearea unei masti ca are nuami bitul "1" pe prima linie
	uint64_t mask = ((1 << 8) -1);

	if(mask & piece)
	{
		return 1;
	}
	return 0;
}

//functie ce returneaza pozitia extremei din stinga piesei
int getPositionLeft(uint64_t piece)
{
	int pos = 64;
	uint64_t mask = 1ul << 63;

	//se afla pozitia prin deplasarea bitului "1" al mastii
	while((mask & piece) == 0)
	{
		mask >>= 1;
		pos--;
	}

	//pentru cazul in care piesa e de tip "L" si extrema e pe urmatoarea linie
	if(((mask >> 7) & piece) != 0)
	{
		pos -= 7;
	}

	return pos;
}

//functie ce returneaza pozitia extremei din stinga piesei
int getPositionRight(uint64_t piece)
{
	int pos = 1;
	uint64_t mask = 1;

	//se afla pozitia prin deplasarea bitului "1" al mastii
	while((mask & piece) == 0)
	{
		mask <<= 1;
		pos++;
	}

	//pentru cazul in care piesa e de tip "L" si extrema e pe urmatoarea linie
	if(((mask << 7) & piece) != 0)
	{
		pos += 7;
	}

	return pos;
}

//functie ce salveaza partea inferioara a hartii in cazul completarii unei linii
uint64_t buildDownMap(uint64_t map,  int i)
{
	uint64_t dwnMap;
	int line = i / 8;

	//daca prima linie este cea completa, nu exista parte inferioara
	if(line == 1)
	{
		dwnMap = 0;
	}
	//se creeaza o masca ce cuprinde numai bitul "1" in partea inferioara
	else
	{
		dwnMap = (1ul << (line - 1) * 8) - 1;
		dwnMap = map & dwnMap;
	}

	return dwnMap;
}

//functie ce salveaza partea superioara a hartii in cazul completarii unei linii
uint64_t buildUpperMap(uint64_t map,  int i)
{
	uint64_t upMap;
	int line = i / 8;

	//daca ultima linie este cea completa, nu exista parte superioara
	if(line == 8)
	{
		upMap = 0;
	}
	//se creeaza o masca ce cuprinde numai bitul "1" in partea superioara
	else
	{
		upMap = (1ul << ((8 - line) * 8)) - 1;
		upMap <<= (line * 8);
		upMap = map & upMap;
		upMap >>= 8;
	}

	return upMap;
}

//functie ce numara liniile complete cu scopul adaugarii acestora la scorul final
int countLines(uint64_t map)
{
	uint64_t mask = 1;
	int i = 0, count = 0, lines = 0;

	/*numararea se face prin deplasarea bitului "1" al mastii si incrementarea counter-ului
	pana la sfarsitul liniei*/
	while(mask < 1ul << 63)
	{
		i++;

		if(map & mask)
		{
			count++;
		}
	
		if(i % 8 == 0)
		{
			if(count == 8)
			{
				lines++;
			}

			count = 0;


		}

		mask <<= 1;
	}

	return lines;
}

//functie ce verifica aparitia unei linii complete si returneaza harta dupa eliminarea acesteia
uint64_t checkFullLine(uint64_t map)
{
	uint64_t mask = 1;
	int i = 0, count = 0;

	/*numararea se face prin deplasarea bitului "1" al mastii si incrementarea counter-ului
	pana la sfarsitul liniei*/
	while(mask < 1ul << 63)
	{
		i++;

		if(map & mask)
		{
			count++;
		}
		
		if(i % 8 == 0)
		{
			//in cazul unei linii complete, se reconstruieste harta in absenta liniei respective
			if(count == 8)
			{
				map = buildDownMap(map, i) | buildUpperMap(map, i);
				i -= 8;
				mask >>= 8;
			}

			count = 0;


		}
		
		/*daca prima linie este cea completa, este necesara o reinitializare
		pentru ca deplasarea sa poata continua*/
		if(mask == 0)
		{
			mask = 1;
		}
		else
		{
			mask <<= 1;
		}

	}

	return map;
}

//functie ce afiseaza harta sub forma dorita
void printMap(uint64_t map)
{
	uint64_t mask = 1ul << 63;
	int i = 0;

	//afisarea se face prin deplasarea bitului "1" al mastii
	while(mask)
	{
		i++;

		if(map & mask)
		{
			printf("#");
		}
		else printf(".");

		mask = mask >> 1;

		if(i % 8 == 0)
		{
			printf("\n");
		}
	}

printf("\n");

}

/*functie ce salveaza partea superioara a piesei ce se pierde in urma deplasarii
acesteia pe ultima linie a hartii*/
uint64_t upperPiece(uint64_t piece)
{
	/*salvare se face prin crearea unei masti ce cuprinde bitul "1"
	peste tot mai putin pe prima linie*/
	uint64_t upPiece, mask = (1ul << 56) -1;
	mask <<= 8;
	upPiece = mask & piece;
	return upPiece;
}

//functie ce deplaseaza piesa orizontal
uint64_t movePiece(uint64_t piece, int move)
{
	if(move < 0)
	{
		while(move)
		{
			piece <<= 1;
			move++;
		}
	}

	if(move > 0)
	{
		while(move)
		{
			piece >>= 1;
			move--;
		}
	}

	return piece;
}

//functie ce verifica coliziunea piesei cu harta, utilizata preponderent la coborarea acesteia
int checkCollisionDown(uint64_t map, uint64_t piece)
{

	if(map & piece)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*functie ce testeaza coliziunea piesei cu harta in urma unei deplasari
orizontale si retuneaza spatiul posibil deplasarii dorite*/
int checkCollisionMove(uint64_t map, uint64_t piece, int move)
{
	int left = getPositionLeft(piece);
	int right = getPositionRight(piece);
	int space = 0;
	int leftSpace, rightSpace;

	if(move < 0)
	{
		//se calculeaza mai intai spatiul ramas pana la marginea liniei
		if(left % 8 == 0)
		{
			return 0;
		}
		leftSpace = -(8 - left % 8);

		//daca mutarea depaseste spatiul ramas, aceasta va lua valoarea disponibila
		if(move < leftSpace)
		{
			move = leftSpace;
		}

		while(move)
		{
			piece <<= 1;

			/*in cazul unei coliziuni, functia va returna spatiul disponibil
			pana la intalnirea obstacolului*/
			if(checkCollisionDown(map, piece) == 1)
			{
				return space;
			}
			
			space--;
			move++;

		}

	}

	if(move > 0)
	{
		//se calculeaza mai intai spatiul ramas pana la marginea liniei
		if(right % 8 == 0)
		{
			rightSpace = 7;
		}
		
		else
		{
			rightSpace = right % 8 -1;
		}

		//daca mutarea depaseste spatiul ramas, aceasta va lua valoarea disponibila
		if(move > rightSpace)
		{
			move = rightSpace;
		}

		while(move)
		{
			piece >>= 1;

			/*in cazul unei coliziuni, functia va returna spatiul disponibil
			pana la intalnirea obstacolului*/
			if(checkCollisionDown(map, piece) == 1)
			{
				return space;
			}

			space++;
			move--;
		}
	}

	if(move == 0)
	{
		return space;
	}
	return 0;
}

int main()
{
	uint64_t map, piece, upPiece;
	int move[8], upMove, i, j, turns, linePoints = 0;


	scanf("%lu", &map);
	scanf("%d", &turns);

	map = checkFullLine(map);

	printMap(map);

	while(turns)
	{
		scanf("%lu", &piece);

		//se utilizeaza un vector cu scopul memorarii si parcurgerii mutarilor introduse
		for(i = 0; i < 8;i++)
		{
			scanf("%d", &move[i]);
		}
		turns--;

		/*se salveaza partea superioara a piesei ce se pierde in urma
		deplasarii acesteia pe ultima linie*/
		upPiece = upperPiece(piece);
		piece <<= 56;

		//in cazul in care piesa intlneste un obstacol la prima intrare, jocul se va incheia
		if(checkCollisionDown(map, piece) != 0)
		{
			printMap(map);
			gameOver(map, linePoints);
			return 0;
		}

		/*se realizeaza prima mutare, si aceasta se salveaza pentru a fi
		utilizata mai tarziu de partea superioara a piesei*/
		move[0] = checkCollisionMove(map, piece, move[0]);
		upMove = move[0];
		piece = movePiece(piece, move[0]);
		printMap(map | piece);

		for(j = 1; j < 8; j++)
		{

			/*in cazul unei coliziuni la coborare, piesa se adauga hartii
			si se verifica formarea unei linii complete*/
			if(checkCollisionDown(map, piece >> 8) != 0 )
			{

				map = map | piece;
		
				if(map != checkFullLine(map))
				{
					linePoints += countLines(map);
					map = checkFullLine(map);
					printMap(map);
				}

				/*in cazul in care piesa are o parte superioara si se afla la prima mutare, aceasta
				va fi pe prima linie iar jocul se va sfarsi in urma lipsei de spatiu*/
				if(j == 1 && upPiece != 0)
				{
					printMap(map);
					gameOver(map, linePoints);
					return 0;
				}
				
				break;
			}
			
			piece >>= 8;

			//se adauga partea superioara pierduta in urma deplasarii piesei pe ultima linie
			if(j == 1)
			{
				
				upPiece = movePiece(upPiece, upMove);

				upPiece <<= 48;
				piece = piece | upPiece;			
			}			

			//se deplaseaza piesa si se afiseaza harta in urma mutarii
			move[j] = checkCollisionMove(map, piece, move[j]);
			piece = movePiece(piece, move[j]);
			printMap(map | piece);

			/*daca piesa se afla pe prima linie, aceasta se va adauga hartii si se va testa
			linia completa*/
			if(checkFirstLine(piece) == 1)
			{
				map = map | piece;

				if(map != checkFullLine(map))
				{
					linePoints += countLines(map);
					map = checkFullLine(map);
					printMap(map);
				}

				break;
			}
		}


	}

	//jocul se va sfarsi in urma epuizarii mutarilor
	gameOver(map, linePoints);
	return 0;


}
