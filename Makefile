PDF = main.pdf
TEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error
GS = gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/printer -dNOPAUSE -dBATCH -sOutputFile=
TEX_PATH = tex


CXXFLAGS=-O3 -Wall -Werror -pedantic -g $(shell sdl2-config --cflags) -fpermissive
LDFLAGS=-lSDL2 -lSDL2_ttf -lm
VPATH=src

TEX_FILES := conclusion.tex glossaire.tex presentation.tex travail.tex docs.tex introduction.tex page_de_garde.tex remerciements.tex annexes.tex generated.tex
main.pdf = $(foreach file,$(TEX_FILES),${TEX_PATH}/$(file))

EXEC=simulated_annealing
OBJS=meta.o simulated_annealing.o draw.o

all: ${PDF}

tex/generated.tex: ${EXEC}
	./${EXEC}

${EXEC}: ${OBJS}

%.pdf: tex/%.tex
	rubber -d $<

compress: $(PDF)
	$(GS)"compressed-$(PDF)" $(PDF)

clean:
	$(RM) *.log *.aux *.pdf *.toc *.out *.dvi *.ptc *.o ${EXEC}
