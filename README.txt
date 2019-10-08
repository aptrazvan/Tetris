Student: Apetroaie Razvan-Mihai
Grupa: 313CB

	In scopul unei intelegeri mai usoare a codului, reducerii numarului de linii de cod si usurarii modului de lucru, am utilizat
diverse functii prezente anterior functiei "main". In cadrul programului am utilizat un singur vector, utilizat la memorarea
si parcurgerea mutarilor introduse.

	Functia "gameover" are ca rol calcularea si afisarea scorului final. Prima parte a subprogramului numara prin deplasarea
bitului "1" a mastii("mask") aparitia bitului "0" in cadrul hartii finale, dupa care se aplica formula ceruta.
	Functia "checkFirstLine" verifica daca piesa introdusa se afla pe prima linie a hartii, pentru a impiedica mai departe iesirea
acesteia din harta. Verificarea se face prin crearea unei masti ca are nuami bitul "1" pe prima linie.
	Functiile "getPositionLeft" si "getPositionRight" au ca scop determinarea extremelor piesei, pentru a se gasi mai departe
spatiul disponibil mutarii piesei. Extremele se afla prin deplasarea bitului "1" al mastii, iar subprogramul are in vedere
si cazul utilizarii pieselor de tip "L".
	Functiile "buldDownMap" si "buildUpperMap" au ca rol salvare partii inferioare, respectiv superioare a hartii in urma completarii
unei linii de joc, pentru a se reconstrui pe urma harta in lipsa liniei respective. Pentru aceasta, se creeaza o masca ce cuprinde numai
bitul "1" in partea inferioara/superioara. In cazul in care prima/ultima linie este cea completata, partea inferioara/superioara este
nula.
	Functia "countLines" numara liniile complete cu scopul adaugarii acestora la scorul final. Numararea se face prin deplasarea bitului
"1" al mastii si incrementarea counter-ului pana la sfarsitul liniei.
	Functia "checkFullLine" functioneaza similar functiei anterioare, numai ca la gasirea unei linii complete subprogramul reconstruieste
harta in absenta liniei respective si returneaza harta rezultata.
	Functia "printMap" realizeaza afisarea hartii sub forma dorita, folosindu-se de o masca auxiliara cu un singur bit de 1 care este
deplasat pe parcursul hartii.
	Functia "upperPiece" foloseste o masca ce cuprinde bitul "1" peste tot mai putin pe prima linie, in scopul salvarii partii
superioare a piesei ce se pierde in urma deplasarii acesteia pe ultima linie a hartii.
	Functia "movePiece" deplaseaza orizontal piesa data. Piesa se deplaseaza un numar de spatii calculat in afara subprogramului, conform
coliziunilor si spatiului ramas pana la marginea liniei.
	Functia "checkCollisionDown" verifica coliziunea piesei cu harta, utilizandu-se preponderent la coborarea acesteia.
	Functia "checkCollisionMove" este cea care calculeaza spatiul posibil deplasarii piesei pe orizontala, in conformitate cu mutarea
introdusa. Se calculeaza mai intai spatiul ramas pana la marginea liniei, iar daca mutarea depaseste spatiul ramas, aceasta va lua
valoarea disponibila. In cazul unei coliziuni, functia va returna spatiul disponibil pana la intalnirea obstacolului, altfel va fi
returnat spatiul disponibil. Numarul returnat este preluat apoi(in main) de subprogramul "movePiece".

	In cadrul functiei "main" gasim declarate variabilele upPiece - partea superioara a piesei si upMove - numarul de spatii ce va trebui
deplasata partea superioara(= move[0]). Vectorul move[8] reprezinta mutarile ce urmeaza a fi citite si efectuate pe piesa.
	Se testeaza liniile complete in urma introducerii hartii initiale(desi probabil nu e cazul) dupa care aceasta se afiseaza.
Urmatoarele linii de cod se executa atat timp cat mai exista mutari de efectuat.
	Dupa citirea piesei, se salveaza partea superioara a acesteia folosind functia "upperPiece". Structura va fi mutata asemenea piesei
dupa prima deplasare("move[0]") si va fi adusa la nivelul acesteia("upPiece <<= 48"), urmand a fi contopite pentru a forma din nou piesa
initiala, dar in pozitia dorita("piece = piece | upPiece"). Prima mutare a piesei am ales s-o execut in afara for-ului, din moment ce in
cadrul instructiunii se realizeaza mai intai o coborare, urmata de mutare. Folosind functia "checkCollisionDown" testez existenta unei
coliziuni la introducerea piesei, caz in care jocul se incheie.
	In cadrul instructiunii for(ce realizeaza trecerea prin mutarile introduse), se testeaza mai intai coliziunea la coborare. In acest
caz, piesa se adauga hartii si se testeaza formarea liniilor complete, fiind apoi numarate si eliminate in cazul in care exista.
	Ajungandu-se la "break", se trece la urmatoarea piesa, fara sa se mai tina cont de restul mutarilor. Daca este a doua mutare
move[1]) piesa este pe prima linie, iar in cazul in care aceasta are o parte superioara, piesa nu incape complet pe harta si jocul se
incheie.
	Daca nu s-a ajuns la coliziune, piesa poate fi coborata o linie("piece >>= 8") si apoi mutata folosindu-se functiile
"checkCollisionMove" si "movePiece", dupa care se afiseaza harta actuala. Instructiunea "if" ce urmeaza testeaza daca piesa se afla pe
prima linie, caz in care actioneaza asemenea coliziunii la coborare.
	Instructiunile se reiau pana la indeplinirea conditiei de incheiere a jocului, sau pana la epuizarea mutarilor. In ambele cazuri, se
calculeaza si afiseaza scorul final folosind functia "gameOver", dupa care se incheie programul prin returnarea valorii "0".

