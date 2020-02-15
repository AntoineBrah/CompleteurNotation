CXX=g++
CXX_FLAGS= -ansi -Wall -pedantic -g
SOURCE= Piece.cc Tour.cc Cavalier.cc Fou.cc Dame.cc Roi.cc Pion.cc Cellule.cc Position.cc LectureFichier.cc Initialisation.cc Main.cc
PROG=chess
MSG_OK = @ echo "\t\t\t........................OK"

.SUFFIXES : .cc .h .o

all : $(PROG)

.cc.o :
	$(CXX) -c $(CXX_FLAGS) $<
	$(MSG_OK)

$(PROG) : $(SOURCE:.cc=.o)
	$(CXX) $^ $(CXX_FLAGS) -o $(PROG) -lncurses
	$(MSG_OK)
clear :
	rm $(SOURCE:.cc=.o)



