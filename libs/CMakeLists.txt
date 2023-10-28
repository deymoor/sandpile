add_library(argparser
        Parser/argparser.cpp Parser/argparser.h
        Classes/Arguments/Arguments.cpp Classes/Arguments/Arguments.h
        Parser/checker.cpp Parser/checker.h)
add_library(readtsv
        TsvReader/tsvreader.cpp TsvReader/tsvreader.h)
add_library(utils
        utils.cpp utils.h)
add_library(iter
        IterSandPile/itersandpile.cpp IterSandPile/itersandpile.h)
add_library(field
        Classes/Field/Field.cpp Classes/Field/Field.h)
add_library(stack
        Classes/Stack/Stack.cpp Classes/Stack/Stack.h)
add_library(bmp
        Classes/Bmp/Bmp.cpp Classes/Bmp/Bmp.h)