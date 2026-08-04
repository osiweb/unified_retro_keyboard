NAME=interface-ascii
PROJECT_DESC=Unified retro keyboard ASCII interface, ATMega 328P version
VARIANTNAME=Production
BOARDREV=3
BOARDREVMINOR=
SCHEMATIC_REV=0
PROJECT_REV=0
LAYERS=2

PCBDIR="./PCB_dir"

PROGRAMMING_DIR=programming_files_dir
DIAGRAMS_DIR=diagrams_dir
WORK_INSTR_DIR=work_instructions_dir
LABELS_DIR=labels_dir

SUBDIRS=$(PROGRAMMING_DIR) $(DIAGRAMS_DIR) $(WORK_INSTR_DIR) $(LABELS_DIR)

PCBREV=$(BOARDREV)
SCHREV=$(BOARDREV).$(SCHEMATIC_REV)
PRJREV=$(BOARDREV).$(SCHEMATIC_REV).$(PROJECT_REV)
PCBNAME=$(NAME)-Rev_$(PCBREV)$(BOARDREVMINOR)
PCBFULLNAME=$(PCBNAME)-$(VARIANTNAME)
SCHNAME=$(NAME)-Rev_$(SCHREV)-$(VARIANTNAME)
PRJNAME=$(NAME)-Rev_$(PRJREV)$(BOARDREVMINOR)-$(VARIANTNAME)

SCHEMATIC_SRC=$(NAME).kicad_sch
BOARD_SRC=$(NAME).kicad_pcb

PCBZIPFILE=$(PCBNAME)-pcbfab.zip
PKGZIPFILE=$(PRJNAME)-package.zip
GENERATED_BOMFILE = ../$(NAME)_bom_$(SCHREV).csv
BOMFILE=BOM-$(SCHNAME).csv
BOMINITFILE=../bom.ini
BOMINITTEMPLATE=./templates/bom.ini
#README_STYLE=rst
README_STYLE=pdf

READMEFILEBASE=README-$(PRJNAME)
READMEFILETXT=$(READMEFILEBASE).rst
READMEFILEPDF=$(READMEFILEBASE).pdf
READMETARGET=readme$(README_STYLE)

RENDERFILE_TOP=Renderings-top-$(PCBFULLNAME).jpg
RENDERFILE_BOTTOM=Renderings-bottom-$(PCBFULLNAME).jpg
RENDERFILES=$(RENDERFILE_TOP) $(RENDERFILE_BOTTOM)
DUMMY_RENDERFILES=$(addsuffix _, $(RENDERFILES))
GENERATED_SCHEMFILE=../$(NAME).pdf
SCHEMFILE=Schematic-$(PRJNAME).pdf
STEPFILE=Model-3D-$(PCBNAME)-$(VARIANTNAME).STEP
DUMMY_STEPFILE="$(STEPFILE)_"
DUMMY_TARGETS=$(DUMMY_STEPFILE) $(DUMMY_RENDERFILES)

define MAKEFILE_SWITCHES
NAME="$(NAME)" PROJECT_DESC="$(PROJECT_DESC)" \
BOARDREV="$(BOARDREV)" BOARDREVMINOR="$(BOARDREVMINOR)" \
LAYERS="$(LAYERS)"
endef

define README_TEXT
"$(NAME) Rev $(PRJREV) \($(PROJECT_DESC)\)"\
|-----------------------------------------------------------------------------------------------|\
|This is the package for $(NAME) rev $(PRJREV).|\
|Service Requested\
|=================|\
|   * Manufacturing and inspection to IPC class 3 standard.\
|   * RoHS compliant\
|   * PCB Material: FR4\
|   * Solder mask color: Green\
|   * Silk screen color: White\
|   * Layers: $(LAYERS)\
|   * Copper thickness: 1 oz all layers\
|   * Finish: HASL|\
||Programming and labeling of microcontroller\
|===========================================|\
|None\
||Testing\
|=======\
|   * Test 100% testing of assemblies\
|   * Standard PCB QA (bed of nails, test for shorts and opens)\
|\
||Tracking\
|========|\
|None\
|\
||Packaging\
|=========|\
|Standard Packaging\
||Production Package\
|==================|\
|The  ZIP file contains the following files:\
|   $(PCBZIPFILE)\
|+++A ZIP file containing Gerbers; drill file;\
|+++readme.txt\
|++++++readme file containing PCB fabrication directions; fab renderings, etc.\
|\
|$(READMEFILE)\
|+++This letter.\
|\
|$(RENDERFILE_TOP)\
|+++A JPEG file containing a reference for PCB parts placement, and 3D renderings of the front of the populated board (with components).\
|\
|$(RENDERFILE_BOTTOM)\
|+++A JPEG file containing a reference for PCB parts placement, and 3D renderings of the back of the populated board (with components).\
|\
|$(STEPFILE):\
|+++An exported 3D STEP file of the PCB with all components fitted.\
|\
|$(SCHEMFILE)\
|+++A PDF file containing the schematics for this PCB.\
|\
|$(BOMFILE)\
|+++BOM file, csv format\
|\
|Subdirectory: labels_dir\
|+++:$(PROJNAME)_labels.doc: Labels for final packaging.\
|\
|Subdirectory: programming_files_dir\
|+++empty, not applicable.\
|\
|Subdirectory containing programming files\
|+++empty, not applicable\
|\
|Subdirectory: diagrams_dir\
|+++empty\
|\
|Subdirectory containing diagrams or pictures related to production\
|+++empty\
|\
|Subdirectory: work_instructions_dir\
|+++Subdirectory containing work instructions, test procedures, etc.|\
|.. figure:: ./$(RENDERFILE_TOP)|\
|   TOP side rendering of populated PCB\
|.. figure:: ./$(RENDERFILE_BOTTOM)|\
|   BOTTOM side rendering of populated PCB
endef


define RENDER_TOP_MSG
|------------------------------------------------------------------------\
|The assembly rendering \"$(RENDERFILE_TOP)\"\
|must be manually generated with the following steps:|\
|1) Bring up the 3D rendering from PCBNEW (ALT-3).  Select\
|the TOP view (RightClick-"View Top").|\
|2) Perform a screen capture.  Save the capture to the\
|production-package directory.  Select the dummy file name|\
|"    \"$(RENDERFILE_TOP)_\""|\
|and delete the trailing \"_\".  Then click Save.
endef

define RENDER_BOTTOM_MSG
|------------------------------------------------------------------------\
|The assembly rendering \"$(RENDERFILE_BOTTOM)\"\
|must be manually generated with the following steps:|\
|1) Bring up the 3D rendering from PCBNEW (ALT-3).  Select\
|the BOTTOM view (RightClick-"View Bottom").|\
|2) Perform a screen capture.  Save the capture to the\
|production-package directory.  Select the dummy file name|\
|"    \"$(RENDERFILE_BOTTOM)_\""|\
|and delete the trailing \"_\".  Then click Save.
endef

define BOM_MSG
|------------------------------------------------------------------------\
|The BOM file must be manually generated.  The BOM file requires the KiBOM plugin.\
|Please ensure that KiBOM is installed.  To generate the BOM file:\
|1) Copy the file 'bom.ini' in the templates directory to the main directory:\
|\"   cp templates_dir/bom.ini ..\"\
|2) In EESChema, select Tools->Generate BOM.|\
|3) Select KIBOM_CLI and click \"Generate\"|
endef

define SCHEM_MSG
|------------------------------------------------------------------------\
|The Schematic PDF file must be manually generated:\
|1) In EESChema, select File->Plot to bring up the Plot dialog\
|2) Select PDF output format.\
|3) Check "Plot Drawing Sheet"\
|4) Click "Plot All Pages"
endef

define STEPFILE_MSG
|------------------------------------------------------------------------\
|The STEP file must be manually generated.\
|1) From PCBNEW, select File->Export->STEP\
|2) Check the following boxes:\
|   - Board Center Origin\
|   - Substitute similarly named models\
|   - Overwrite old file\
|2) Save to the production package directory.  Select the placeholder filename:\
|"    $(STEPFILE)_"\
|3) Remove the trailing \"_\" and click "Save"
endef

# KiCad doesn't automate saving of rendering files, which must be
# screen-captured and saved as JPEG files. The STEP file must similarly be
# exported manually. the "dummies" target creates filename templates that can be
# selected and edited (by removing the trailing "_") to help ensure that the

all: dummies bomfile renderfiles schemfile $(READMETARGET) pkgzip subdirs

.phony: dummies
dummies:
	@echo "$(DUMMY_TARGETS)" | xargs -n 1 echo "+++ Creating placeholder: "
	@touch $(DUMMY_TARGETS)

.Phony: clean
clean:
	rm -fv  *.zip  $(DUMMY_TARGETS) *~ *_ makefile.log
	rm -fv  *pdf *rst *csv

	(cd PCB_dir; make $(MAKEFILE_SWITCHES) clean)

.phony: veryclean
veryclean: clean
	rm -fv $(SCHEMFILE) $(RENDERFILES) $(BOMFILE)
	rm -rfv *.jpg *.JPG *.pdf *.pdf *.png *.PNG
	rm -f README* *rst *pdf *dvi
	(cd PCB_dir; make $(MAKEFILE_SWITCHES) veryclean)

bominit: $(BOMINITFILE)

$(BOMINITFILE): $(BOMINITTEMPLATE)
	cp -i $(BOMINITTEMPLATE) $(BOMINITFILE)

$(BOMFILE):
	@if [ ! -f "$(GENERATED_BOMFILE)" ]; then \
		echo "XXX Didn't find BOM: $(GENERATED_BOMFILE).  See makefile.log. . .";\
		echo "|$(BOM_MSG)|"|tr '|' '\n' >> makefile.log;\
	else \
		echo "--> Found BOM: $(GENERATED_BOMFILE).  Copying. . .";\
		cp $(GENERATED_BOMFILE) $(BOMFILE);\
	fi

bomfile: $(BOMFILE)

$(SCHEMFILE):
	@if [ ! -f "$(GENERATED_SCHEMFILE)" ]; then \
		echo "XXX Didn't find Schematic PDF: $(GENERATED_SCHEMFILE). See makefile.log";\
		echo "$(SCHEM_MSG)"|tr '|' '\n'  >> makefile.log; \
	else \
		echo "--> Found Schematic PDF: $(GENERATED_SCHEMFILE)";\
		cp $(GENERATED_SCHEMFILE) $(SCHEMFILE);\
	fi

schemfile: $(SCHEMFILE)

$(STEPFILE):
	@if [ ! -f "$(STEPFILE)" ]; then\
		echo; \
		echo "XXX Didn't find assembly STEP file: $(STEPFILE). See makefile.log"; \
		echo "$(STEPFILE_MSG)"|tr '|' '\n' >> makefile.log; \
		echo; \
	else \
		echo "--> Found assembly STEP file: $(STEPFILE)"; \
	fi

.Phony: stepfile
stepfile: $(STEPFILE)

.Phony: renderfiles
renderfiles: renderfile_top renderfile_bottom

.Phony: renderfile_top
renderfile_top:
	@if [ ! -f "$(RENDERFILE_TOP)" ]; then\
		echo; \
		echo "XXX Didn't find assembly rendering: $(RENDERFILE_TOP) See makefile.log"; \
		echo "$(RENDER_BOTTOM_MSG)"|tr '|' '\n' >> makefile.log; \
		echo; \
	else \
		echo "--> Found top assembly rendering: $(RENDERFILE_TOP)"; \
	fi

.Phony: renderfile_bottom
renderfile_bottom:
	@if [ ! -f "$(RENDERFILE_BOTTOM)" ]; then\
		echo; \
		echo "XXX Didn't find bottom assembly rendering: $(RENDERFILE_BOTTOM) See makefile.log"; \
		echo "$(RENDER_TOP_MSG)"|tr '|' '\n' >> makefile.log; \
		echo; \
	else \
		echo "--> Found bottom assembly rendering: $(RENDERFILE_BOTTOM)"; \
	fi

pcbzip: $(PCBZIPFILE)

$(PCBZIPFILE):
	echo "Building PCB Zip file..."; (cd $(PCBDIR); make $(MAKEFILE_SWITCHES) zip)

renderfiles: renderfile_top renderfile_bottom

readmetxt: $(READMEFILETXT)

readmepdf: $(READMEFILEPDF)

$(READMEFILETXT): Makefile
	@echo "Creating Readme File $(READMEFILETXT)."; \
	echo "$(README_TEXT)"|tr '|' '\n' | sed 's/+++/   /g'  > $(READMEFILETXT);

$(READMEFILEPDF): $(READMEFILETXT)
	@echo "Creating Readme File $(READMEFILEPDF)."; \
	pandoc -f rst -t pdf -o "$(READMEFILEPDF)" "$(READMEFILETXT)";

.phony subdirs:
	@mkdir -p $(SUBDIRS)

pkgzip: $(PCBZIPFILE) $(BOMFILE) $(RENDERFILES) $(READMEFILE) $(STEPFILE)
	@echo removing old zip. . .; \
	rm -rf $(PKGZIPFILE); \
	echo creating zip. . .; \
	zip -9r $(PKGZIPFILE) \
	$(PCBZIPFILE) \
	$(READMEFILETXT) \
	$(READMEFILEPDF) \
	$(SCHEMFILE) \
	$(RENDERFILES) \
	$(BOMFILE) \
	$(STEPFILE) \
	$(SUBDIRS)
