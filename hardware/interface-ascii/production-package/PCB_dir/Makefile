PROJECT_DESC="PCB"
NAME="PCB"
BOARDREV=1
BOARDREVMINOR=
LAYERS=2
SMT=no

#README_STYLE=rst
README_STYLE=pdf

PCBNAME=$(NAME)-Rev_$(BOARDREV)$(BOARDREVMINOR)

READMEFILEBASE=README-PCB-$(PCBNAME)
READMEFILETXT=$(READMEFILEBASE).rst
READMEFILEPDF=$(READMEFILEBASE).pdf
READMETARGET=readme$(README_STYLE)

TOP_SOLDER_EXT = gts
TOP_SOLDER_DSC = F_Mask
TOP_SOLDER_GBR = "$(PCBNAME)_$(TOP_SOLDER_DSC).$(TOP_SOLDER_EXT)"
TOP_COPPER_EXT = gtl
TOP_COPPER_DSC = F_Cu
TOP_COPPER_GBR = "$(PCBNAME)_$(TOP_COPPER_DSC).$(TOP_COPPER_EXT)"
TOP_SILK_EXT = gto
TOP_SILK_DSC = F_Silkscreen
TOP_SILK_GBR = "$(PCBNAME)_$(TOP_SILK_DSC).$(TOP_SILK_EXT)"
BOT_SOLDER_EXT = gbs
BOT_SOLDER_DSC = B_Mask
BOT_SOLDER_GBR = "$(PCBNAME)_$(BOT_SOLDER_DSC).$(BOT_SOLDER_EXT)"
BOT_COPPER_EXT = gbl
BOT_COPPER_DSC = B_Cu
BOT_COPPER_GBR = "$(PCBNAME)_$(BOT_COPPER_DSC).$(BOT_COPPER_EXT)"
BOT_SILK_EXT = gbo
BOT_SILK_DSC = B_Silkscreen
BOT_SILK_GBR = "$(PCBNAME)_$(BOT_SILK_DSC).$(BOT_SILK_EXT)"
OUTLN_EXT = gm1
OUTLN_DSC = Edge_Cuts
OUTLN_GBR = "$(PCBNAME)_$(OUTLN_DSC).$(OUTLN_EXT)"
DRILL_EXT = DRL
DRILL_PTH = "$(PCBNAME)-PTH.$(DRILL_EXT)"
DRILL_NPTH = "$(PCBNAME)-NPTH.$(DRILL_EXT)"
TOP_PASTE_EXT = gtp
TOP_PASTE_DSC = F_Paste
TOP_PASTE_GBR = "$(PCBNAME)_$(TOP_PASTE_DSC).$(TOP_PASTE_EXT)"
BOT_PASTE_EXT = gbp
BOT_PASTE_DSC = B_Paste
BOT_PASTE_GBR = "$(PCBNAME)_$(BOT_PASTE_DSC).$(BOT_PASTE_EXT)"

GND1_EXT = g2
GND1_DSC = In1_Cu
GND1_GBR = "$(PCBNAME)_$(GND1_DSC).$(GND1_EXT)"
GND2_EXT = g3
GND2_DSC = In2_Cu
GND2_GBR = "$(PCBNAME)_$(GND2_DSC).$(GND2_EXT)"

ifeq ($(SMT),yes)
PASTE_LAYERS= $(TOP_PASTE_GBR) $(BOT_PASTE_GBR)
endif

ifeq ($(LAYERS),4)
OUTPUT_EXTS = $(addprefix *., $(TOP_SOLDER_EXT) $(TOP_COPPER_EXT) $(TOP_SILK_EXT) \
               $(BOT_SOLDER_EXT) $(BOT_COPPER_EXT) $(BOT_SILK_EXT) \
			   $(OUTLN_EXT) $(DRILL_EXT)) \
			   $(TOP_PASTE_EXT) $(BOT_PASTE_EXT) \
			   $(GND1_EXT) $(GND2_EXT)

define STACKUP_DESC
|   * Stackup: All tolerances 10%\
|       1. Total thickness: 0.062 inch\
|       1. top layer    1oz copper\
|       1. prepreg      2x2116\
|       1. second layer 1oz copper\
|       1. core         0.039 inch core\
|       1. third layer  1oz copper\
|       1. prepreg      2x2116\
|       1. bottom layer 1oz copper
endef

define INNER_PLANE_DESC
|:INNER_PLANE 1: - :code:\`"$(GND1_GBR)"\`\
|:INNER_PLANE 2: - :code:\`"$(GND2_GBR)"\`
endef

INNER_PLANES = $(GND1_GBR) $(GND2_GBR)

define INNER_LAYERS
 * In1.Cu\
|  * In2.Cu
endef

endif

ifeq ($(LAYERS),2)
OUTPUT_EXTS = $(addprefix *., $(TOP_SOLDER_EXT) $(TOP_COPPER_EXT) $(TOP_SILK_EXT) \
               $(BOT_SOLDER_EXT) $(BOT_COPPER_EXT) $(BOT_SILK_EXT) \
			   $(OUTLN_EXT) $(DRILL_EXT)) \
			   $(TOP_PASTE_EXT) $(BOT_PASTE_EXT)

define STACKUP_DESC
|   * Stackup: All tolerances 10%\
|       1. Total thickness: 0.062 inch\
|       1. top layer    1oz copper\
|       1. core         0.059 inch\
|       1. bottom layer 1oz copper
endef


endif

DRILDIR = outputs
GERBDIR = outputs
FAB_TOP = $(PCBNAME)-render-top-view.jpg
FAB_BOTTOM = $(PCBNAME)-render-bottom-view.jpg
FAB_FILES = $(FAB_TOP) $(FAB_BOTTOM)
FAB_DUMMIES = $(FAB_TOP)_ $(FAB_BOTTOM)_

DUMMY_TARGETS = $(FAB_DUMMIES)

ZIPFILE = ../$(PCBNAME)-pcbfab.zip

define FAB_TOP_MSG
|------------------------------------------------------------------------\
|The assembly rendering \"$(FAB_TOP)\"\
|must be manually generated with the following steps:|\
|1) Bring up the 3D rendering from PCBNEW \(ALT-3\).|\
|2) Deselect the 3D model visibility for all components.|\
|3) Select the TOP view \(RightClick-"View Top"\).|\
|2) Perform a screen capture.  Save the capture to the\
|\"production-package/PCB_dir\" directory.  Select the dummy file name|\
|"    \"$(FAB_TOP)_\""|\
|and delete the trailing \"_\".  Then click Save.
endef

define FAB_BOTTOM_MSG
|------------------------------------------------------------------------\
|The assembly rendering \"$(FAB_BOTTOM)\"\
|must be manually generated with the following steps:|\
|1) Bring up the 3D rendering from PCBNEW \(ALT-3\).|\
|2) Deselect the 3D model visibility for all components.|\
|3) Select the BOTTOM view \(RightClick-"View Bottom"\).|\
|2) Perform a screen capture.  Save the capture to the\
|\"production-package/PCB_dir\" directory.  Select the dummy file name|\
|"    \"$(FAB_BOTTOM)_\""|\
|and delete the trailing \"_\".  Then click Save.
endef

define README_TEXT
"$(NAME) Rev $(BOARDREV) \($(PROJECT_DESC)\)"\
|------------------------------------------------------------------------------------|\
||:Board: "$(BASENAME)"\
||Service\
|=======|\
|   * Manufacturing and inspection to IPC class 3 standard.\
|   * PCB Material: FR4\
|   * Solder mask color: Green\
|   * Silk screen color: White\
|   * Layers: $(LAYERS)\
|   * Copper thickness: 1 oz all layers\
|   * Finish: HASL|\
$(STACKUP_DESC)\
|\
|Files\
|=====|\
|:BOARD OUTLINE: - :code:\`"$(OUTLN_GBR)"\`\
|:TOP LAYER: - :code:\`"$(TOP_COPPER_GBR)"\`\
$(INNER_PLANE_DESC)\
|:BOTTOM LAYER: - :code:\`"$(BOT_COPPER_GBR)"\`\
|:TOP SOLDER MASK: - :code:\`"$(TOP_PASTE_GBR)"\`\
|:BOTTOM SOLDER MASK: - :code:\`"$(BOT_PASTE_GBR)"\`\
|:TOP PASTE MASK: - :code:\`"$(TOP_PASTE_GBR)"\`\
|:BOTTOM PASTE MASK: - :code:\`"$(BOT_PASTE_GBR)"\`\
|:TOP SILK SCREEN: - :code:\`"$(TOP_SILK_GBR)"\`\
|:BOTTOM SILK SCREEN: - :code:\`"$(BOT_SILK_GBR)"\`\
|:EXCELLON DRILL (Plated): - :code:\`"$(DRILL_PTH)"\`\
|:EXCELLON DRILL (Non-plated): :code:\`"$(DRILL_NPTH)"\`\
||Fab Drawings\
|============|\
|:$(FAB_TOP): - :code:\`3D rendering of the top of the bare PCB\`\
|:$(FAB_BOTTOM): - :code:\`3D rendering of the bottom of the bare PCB\`\
|\
|.. figure:: ./$(FAB_TOP)||\
|   TOP side rendering of bare PCB||\
|.. figure:: ./$(FAB_BOTTOM)||\
|   BOTTOM side rendering of bare PCB||\
|General Info\
|============|\
|   * This board was developed with Kicad 6\
|   * The Gerber files are in 2.5 RS274X format.\
||Special Instructions\
|====================|\
|  * Please note there are TWO Excellon Drill files, one for plated through holes (PTH), and one for non-plated through holes (NPTH).\
|  * The board outline is delineated in the Gerber file "$(OUTLN_GBR)"|\
|Thanks.
endef

define DRL_FAIL
|Missing drill file.  To generate the drill files, within PCBNew:|\
|- Select File->Plot.  Click "Generate Drill Files" at the bottom right side of the dialog.\
|- Select the following options:\
|  * Excellon, \"Use route command\"\
|  * Drill origin: Absolute\
|  * Drill units: inches\
|  * Zeros Format: Decimal format\
|  * Precision: 2.4\
|- Select \"Generate Drill File\"|
endef

define GBR_FAIL
|Missing gerber file.  To generate the gerber files, within PCBNew:|\
|- Select File->Plot.  Click "Generate Drill Files" at the bottom right side of the dialog.\
|- Select the following layers:\
|  * F.Cu\
|  * B.Cu\
|  * F.Silkscreen\
|  * B.Silkscreen|\
$(INNER_LAYERS)\
|  * F.Paste\
|  * B.Paste\
|  * F.Mask\
|  * B.Mask\
|  * Edge.Cuts|
endef


all: dummies copy renderfiles $(READMETARGET)

readmetxt: $(READMEFILETXT)

readmepdf: $(READMEFILEPDF)

$(READMEFILETXT): Makefile
	@echo "Creating Readme File $(READMEFILETXT)."; \
	echo "$(README_TEXT)"|tr '|' '\n' | sed 's/+++/   /g'  > $(READMEFILETXT);

$(READMEFILEPDF): $(READMEFILETXT)
	@echo "Creating Readme File $(READMEFILEPDF)."; \
	pandoc -f rst -t pdf -o "$(READMEFILEPDF)" "$(READMEFILETXT)";


.Phony: renderfiles
renderfiles: renderfile_top renderfile_bottom

.Phony: renderfile_top
renderfile_top:
	@if [ ! -f "$(FAB_TOP)" ]; then\
		echo; \
		echo "XXX Didn't find top assembly rendering: $(FAB_TOP). See makefile.log"; \
		echo "|$(FAB_TOP_MSG)|"|tr '|' '\n' >> makefile.log; \
		echo; \
	else \
		echo "--> Found top assembly rendering: $(FAB_TOP)"; \
	fi

.Phony: renderfile_bottom
renderfile_bottom:
	@if [ ! -f "$(FAB_BOTTOM)" ]; then\
		echo; \
		echo "XXX Didnt' find assembly rendering $(FAB_BOTTOM).  See makefile.log";\
		echo "|$(FAB_TOP_MSG)|"|tr '|' '\n' >> makefile.log; \
		echo; \
	else \
		echo "--> Found bottom assembly rendering: $(FAB_BOTTOM)"; \
	fi

renderfiles: renderfile_top renderfile_bottom

clean:
	rm -f $(OUTPUT_EXTS) *rst *pdf *.zip $(DUMMY_TARGETS) *_
	rm -f makefile.log

veryclean:
	rm -rfv outputs $(PCBNAME)* $(NAME)*
	rm -rfv *.jpg *.JPG *.pdf *.pdf *.png *.PNG
	rm -f README* *rst *pdf *dvi

.PHONY: dummies
dummies:
	@echo "Making placeholder filenames:"
	@echo "$(DUMMY_TARGETS)" | xargs -n 1 echo +++
	@touch $(DUMMY_TARGETS)


gvp: gvp_template.gvp
	sed -e "s/@@NAME@@/$(PCBNAME)/" < $< > $(PCBNAME).gvp

copy:
	cp $(DRILDIR)/$(NAME)-PTH.$(DRILL_EXT) $(DRILL_PTH) || echo "$(DRILL_FAIL)"|tr '|' '\n'
	cp $(DRILDIR)/$(NAME)-NPTH.$(DRILL_EXT) $(DRILL_NPTH) || echo "$(DRILL_FAIL)"|tr '|' '\n'
	cp $(GERBDIR)/$(NAME)-$(TOP_SOLDER_DSC).$(TOP_SOLDER_EXT) $(TOP_SOLDER_GBR) || echo "$(GBR_FAIL)" | tr '|' '\n'
	cp $(GERBDIR)/$(NAME)-$(TOP_COPPER_DSC).$(TOP_COPPER_EXT) ./$(TOP_COPPER_GBR)
	cp $(GERBDIR)/$(NAME)-$(TOP_SILK_DSC).$(TOP_SILK_EXT) ./$(TOP_SILK_GBR)
	cp $(GERBDIR)/$(NAME)-$(BOT_SILK_DSC).$(BOT_SILK_EXT) ./$(BOT_SILK_GBR)
	cp $(GERBDIR)/$(NAME)-$(BOT_SOLDER_DSC).$(BOT_SOLDER_EXT) ./$(BOT_SOLDER_GBR)
	cp $(GERBDIR)/$(NAME)-$(BOT_COPPER_DSC).$(BOT_COPPER_EXT) ./$(BOT_COPPER_GBR)
ifeq ($(SMT),yes)
	cp $(GERBDIR)/$(NAME)-$(TOP_PASTE_DSC).$(TOP_PASTE_EXT) ./$(TOP_PASTE_GBR)
	cp $(GERBDIR)/$(NAME)-$(BOT_PASTE_DSC).$(BOT_PASTE_EXT) ./$(BOT_PASTE_GBR)
endif
ifeq ($(LAYERS),4)
	cp $(GERBDIR)/$(NAME)-$(GND1_DSC).$(GND1_EXT) ./$(GND1_GBR)
	cp $(GERBDIR)/$(NAME)-$(GND2_DSC).$(GND2_EXT) ./$(GND2_GBR)
endif
	cp $(GERBDIR)/$(NAME)-$(OUTLN_DSC).$(OUTLN_EXT) ./$(OUTLN_GBR)

gerbv:
	gerbv \
	$(OUTLN_GBR) \
	$(DRILL_PTH) \
	$(DRILL_NPTH) \
	$(TOP_SOLDER_GBR) \
	$(TOP_COPPER_GBR) \
	$(PASTE_LAYERS) \
	$(TOP_SILK_GBR) \
	$(BOT_SILK_GBR) \
	$(BOT_SOLDER_GBR) \
	$(BOT_COPPER_GBR) \
	$(INNER_PLANES) \
	$(BOT_SILK_GBR)


zip: all
	rm -f $(ZIPFILE)
	zip -9 $(ZIPFILE) \
	$(OUTLN_GBR) \
	$(DRILL_PTH) \
	$(DRILL_NPTH) \
	$(TOP_SOLDER_GBR) \
	$(TOP_COPPER_GBR) \
	$(PASTE_LAYERS) \
	$(TOP_SILK_GBR) \
	$(BOT_SOLDER_GBR) \
	$(BOT_COPPER_GBR) \
	$(BOT_SILK_GBR) \
	$(INNER_PLANES) \
	$(FAB_FILES) \
	$(READMEFILEPDF) \
	$(READMEFILETXT)
