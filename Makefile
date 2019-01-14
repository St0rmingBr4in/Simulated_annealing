PDF = main.pdf
TEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error
GS = gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/printer -dNOPAUSE -dBATCH -sOutputFile=
TEX_PATH = tex
VIEWER = zathura

CC=g++
CXXFLAGS=-O3 -Wall -Werror -pedantic -g -fpermissive -DEPIX_FMT_TIKZ
LDLIBS=-I/usr/include -L/usr/lib/epix -lm -lepix
VPATH=src

TEX_FILES=conclusion.tex glossaire.tex presentation.tex travail.tex docs.tex introduction.tex page_de_garde.tex remerciements.tex annexes.tex generated.eepic
EXEC=simulated_annealing
OBJS=simulated_annealing.o meta.o

all: $(PDF)

view: $(PDF)
	$(VIEWER) $(PDF)

main.pdf: $(foreach file,$(TEX_FILES),$(TEX_PATH)/$(file))

$(TEX_PATH)/generated.eepic: $(EXEC)
	./$(EXEC) > $(TEX_PATH)/generated.eepic

$(EXEC): $(OBJS)

#%.pdf: $(TEX_PATH)/%.tex
#	rubber -d $<

%.pdf: tex/%.tex
	$(TEX) $< -o $@

compress: $(PDF)
	$(GS)"compressed-$(PDF)" $(PDF)

clean:
	$(RM) *.log *.aux *.pdf *.toc *.out *.dvi *.ptc *.o $(EXEC) $(TEX_PATH)/generated.eepic
