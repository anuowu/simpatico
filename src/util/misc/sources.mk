
util_misc_=\
    util/misc/Bit.cpp \
    util/misc/Exception.cpp \
    util/misc/FileMaster.cpp \
    util/misc/initStatic.cpp \
    util/misc/Log.cpp \
    util/misc/Memory.cpp \
    util/misc/ioUtil.cpp \
    util/misc/XmlBase.cpp \
    util/misc/XmlXmlTag.cpp \
    util/misc/XmlAttribute.cpp \
    util/misc/XmlStartTag.cpp \
    util/misc/XmlEndTag.cpp \


util_misc_SRCS=$(addprefix $(SRC_DIR)/, $(util_misc_))
util_misc_OBJS=$(addprefix $(BLD_DIR)/, $(util_misc_:.cpp=.o))

