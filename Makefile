CXX=g++
CXX_FLAGS= -ansi -Wall -std=c++11 -pedantic -g
SOURCE= Piece.cpp Tour.cpp Cavalier.cpp Fou.cpp Dame.cpp Roi.cpp Pion.cpp Cellule.cpp Position.cpp Point.cpp LectureFichier.cpp EcritureFichier.cpp Initialisation.cpp TraitementCoups.cpp GestionErreurs.cpp main.cpp
PROG=chess
MSG_OK = @ echo "\t\t\t........................OK"

.SUFFIXES : .cpp .h .o

all : $(PROG)

.cpp.o :
	$(CXX) -c $(CXX_FLAGS) $<
	$(MSG_OK)

$(PROG) : $(SOURCE:.cpp=.o)
	$(CXX) $^ $(CXX_FLAGS) -o $(PROG)
	$(MSG_OK)
clear :
	rm $(SOURCE:.cpp=.o)



