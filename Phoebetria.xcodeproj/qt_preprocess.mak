#############################################################################
# Makefile for building: Phoebetria.app/Contents/MacOS/Phoebetria
# Generated by qmake (2.01a) (Qt 4.8.2) on: Thu Aug 9 08:37:52 2012
# Project:  Phoebetria.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/local/Qt4.8/mkspecs/macx-xcode -o Phoebetria.xcodeproj/project.pbxproj Phoebetria.pro
#############################################################################

MOC       = /Developer/Tools/Qt/moc
UIC       = /Developer/Tools/Qt/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/local/Qt4.8/mkspecs/macx-xcode -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/usr/include -Ihidapi-0.7.0/hidapi -I. -I. -I/usr/local/include -I/System/Library/Frameworks/CarbonCore.framework/Headers -F/Library/Frameworks
DEL_FILE  = rm -f
MOVE      = mv -f

IMAGES = 
PARSERS =
preprocess: $(PARSERS) compilers
clean preprocess_clean: parser_clean compiler_clean

parser_clean:
check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compilers: ./moc_gui_mainwindow.cpp ./moc_fancontroller.cpp ./moc_device-io.cpp\
	 ./moc_temperaturemonitor.cpp ./ui_gui_mainwindow.h
compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_gui_mainwindow.cpp moc_fancontroller.cpp moc_device-io.cpp moc_temperaturemonitor.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_gui_mainwindow.cpp moc_fancontroller.cpp moc_device-io.cpp moc_temperaturemonitor.cpp
moc_gui_mainwindow.cpp: gui_mainwindow.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ gui_mainwindow.h -o moc_gui_mainwindow.cpp

moc_fancontroller.cpp: device-io.h \
		bfx-recon/fancontroller.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ bfx-recon/fancontroller.h -o moc_fancontroller.cpp

moc_device-io.cpp: device-io.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ device-io.h -o moc_device-io.cpp

moc_temperaturemonitor.cpp: temperaturemonitor.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ temperaturemonitor.h -o moc_temperaturemonitor.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all: ui_gui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_gui_mainwindow.h
ui_gui_mainwindow.h: gui_mainwindow.ui
	/Developer/Tools/Qt/uic gui_mainwindow.ui -o ui_gui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 
