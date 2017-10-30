SOURCE=*.cpp *.h
MYPROGRAM=benchmark_runner
#MYINCLUDES=/home/scale/g++Projects/gLib/

#MYLIBRARIES=fltk
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)
	g++ -c stdafx.h -o stdafx.h.gch
	$(CC) $(SOURCE) -o$(MYPROGRAM)

clean:

	rm -f $(MYPROGRAM)

