add_library(argparser
        parser/argparser.cpp parser/argparser.h
        Classes/Arguments/Arguments.cpp Classes/Arguments/Arguments.h
        parser/checker.cpp parser/checker.h)
add_library(readtsv
        tsv_reader/tsvreader.cpp tsv_reader/tsvreader.h)
add_library(utils
        utils/utils.cpp utils/utils.h)
add_library(iter
        iter_sand_pile/itersandpile.cpp iter_sand_pile/itersandpile.h)
add_library(field
        Classes/Field/Field.cpp Classes/Field/Field.h)
add_library(stack
        Classes/Stack/Stack.cpp Classes/Stack/Stack.h)
add_library(bmp
        Classes/Bmp/Bmp.cpp Classes/Bmp/Bmp.h)