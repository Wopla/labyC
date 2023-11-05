# ENSICAEN
# 6 Boulevard Marechal Juin
# F-14050 Caen Cedex
#
# This file is owned by ENSICAEN students.
# No portion of this document may be reproduced, copied
# or revised without written permission of the authors.
#
# @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
# @version 01.00
# @date 30/10/2022

EXEC=menu
ROOT=gameFolder/
BIN_DIR=$(ROOT)bin/
MENU_MAKE=$(ROOT)menu_src/
LABY_MAKE=$(ROOT)play_src/
GEN_MAKE=$(ROOT)generator_src/

.PHONY : main run clean distclean doc docclean

main : 
	cd $(MENU_MAKE) && make
	cd ..
	cd $(LABY_MAKE) && make
	cd ..
	cd $(GEN_MAKE) && make
	
run:
	make
	cd $(BIN_DIR) && ./$(EXEC)

clean:
	cd $(MENU_MAKE) && make clean
	cd ..
	cd $(LABY_MAKE) && make clean
	cd ..
	cd $(GEN_MAKE) && make clean

distclean: clean
	rm -rf $(BIN_DIR)*

doc:
	doxygen doc/Doxyfile

docclean:
	rm -rf doc/html