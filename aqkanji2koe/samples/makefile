#----------------------------------------------------------------#
#  Makefile for Kanji2KoeCmd (AqKanji2Kkoe-A sample program)     #
#         ビルドにはGCC 5.1以上の環境が必要                      #
#         チェックは $gcc --version                              #
#----------------------------------------------------------------#

LIBDIR  	= ../lib
AQK2KLIB	= libAqKanji2Koe.so.4.1
SONAMELIB   = libAqKanji2Koe.so.4
LINKNAME   	= libAqKanji2Koe.so
TARGET		= Kanji2KoeCmd

all :
#	ln -sf $(LIBDIR)/$(AQK2KLIB) ./$(SONAMELIB)
#	ln -sf $(LIBDIR)/$(AQK2KLIB) ./$(LINKNAME)
	cp $(LIBDIR)/$(AQK2KLIB) ./$(SONAMELIB)
	cp $(LIBDIR)/$(AQK2KLIB) ./$(LINKNAME)
	g++ -I$(LIBDIR) -o Kanji2KoeCmd Kanji2KoeCmd.cpp -L. -lAqKanji2Koe

run :
	echo 音声合成テスト | LD_LIBRARY_PATH=. ./Kanji2KoeCmd ../aq_dic
