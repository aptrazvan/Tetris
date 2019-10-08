#Student: Apetroaie Razvan-Mihai
#Grupa: 313CB

# Declaratiile de variabile
CC = gcc
CFLAGS = -Wall -lm
SRC = tetris.c
EXE = tema1
 
# Regula de compilare
all:
	$(CC) -o $(EXE) $(SRC) $(CFLAGS)

build:
	$(CC) -o $(EXE) $(SRC) $(CFLAGS)

run:
	./$(EXE)
# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
.PHONY : clean
clean :
	rm -f $(EXE) *~
