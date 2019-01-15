PDF = main.pdf
TEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error
GS = gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/printer -dNOPAUSE -dBATCH -sOutputFile=
TEX_PATH = tex
VIEWER = zathura

CC=g++
CXXFLAGS=-O3 -Wall -Werror -pedantic -g -DEPIX_FMT_TIKZ $(shell sdl2-config --cflags)
LDFLAGS=-lSDL2 -lSDL2_ttf
LDLIBS=-I/usr/include -L/usr/lib/epix -lm -lepix
VPATH=src

GEN_TEX_FILES=simulated_annealing.eepic tabu.eepic
TEX_FILES=conclusion.tex glossaire.tex travail.tex docs.tex introduction.tex page_de_garde.tex annexes.tex $(GEN_TEX_FILES)
EXEC=simulated_annealing
OBJS=simulated_annealing.o meta.o SDLdraw.o

all: $(PDF)

view: $(PDF)
	$(VIEWER) $(PDF)

main.pdf: $(foreach file,$(TEX_FILES),$(TEX_PATH)/$(file))

%.eepic: $(EXEC)
	./$(EXEC) $% > $@

$(EXEC): $(OBJS)

%.pdf: $(TEX_PATH)/%.tex
	rubber -d $<

#%.pdf: tex/%.tex
#	$(TEX) $< -o $@

compress: $(PDF)
	$(GS)"compressed-$(PDF)" $(PDF)

clean:
	$(RM) *.log *.aux *.pdf *.toc *.out *.dvi *.ptc *.o $(EXEC) $(TEX_PATH)/generated.eepic
