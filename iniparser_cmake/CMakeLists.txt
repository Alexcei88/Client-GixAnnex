cmake_minimum_required (VERSION 2.6)

set (PROJECT iniparser)
project (${PROJECT})

set (HEADERS 
	src/dictionary.h
	src/iniparser.h
	)
 
set (SOURCES 
	src/dictionary.c
	src/iniparser.c
	test/parse.c) 
 
add_library (${PROJECT} ${HEADERS} ${SOURCES})
