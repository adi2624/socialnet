OSPL_LIBS = -lpthread -lddskernel -ldcpssacpp
LIBS=-L${OSPL_HOME}/lib ${OSPL_LIBS} -lboost_system -lboost_thread
CFLAGS = -DDEBUG_PRINT -DDEBUG_STATES -Wall -O0 -g -I. -I./include -I${OSPL_HOME}/include/dcps/C++/SACPP -I${OSPL_HOME}/include/sys
CXXFLAGS = -std=c++11
DIR = /idl

all: UserInformationPublisher UserInformationSubscriber Response Request main


IDL_GENERATED_H= \
                 ccpp_tsn.h \
                 tsnDcps.h \
                 tsnDcps_impl.h \
                 tsn.h \
                 tsnSplDcps.h 

IDL_GENERATED_CPP=\
                 tsn.cpp \
                 tsnDcps.cpp \
                 tsnDcps_impl.cpp \
                 tsnSplDcps.cpp

IDL_GENERATED= ${IDL_GENERATED_H} ${IDL_GENERATED_CPP}

${IDL_GENERATED}: idl/tsn.idl
	${OSPL_HOME}/bin/idlpp -l cpp idl/tsn.idl

COMMON_CPP= cpp/src/CheckStatus.cpp cpp/src/DDSEntityManager.cpp cpp/src/User.cpp cpp/src/Post.cpp

COMMON_H=   cpp/src/CheckStatus.h cpp/src/DDSEntityManager.h 

#src/io.h was removed from COMMON_H
REQUEST_FILES = cpp/src/Request.cpp
REQUEST_H_FILES = cpp/src/Request.h
POST_H = cpp/src/Post.h
RESPONSE_FILES = cpp/src/Response.cpp
RESPONSE_H_FILES = cpp/src/Response.h

UserInformationPublisher:  ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} cpp/src/UserInformationPublisher.cpp
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS} ${COMMON_CPP}

UserInformationSubscriber: ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} cpp/src/UserInformationSubscriber.cpp
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS} ${COMMON_CPP}

Response: ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} cpp/src/Response.cpp ${RESPONSE_FILES} ${RESPONSE_H_FILES}  ${COMMON_H} ${COMMON_CPP}
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS}

Request: ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} cpp/src/Request.cpp ${REQUEST_FILES} ${REQUEST_H_FILES} ${COMMON_H} ${COMMON_CPP}
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS}

main:   ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} cpp/src/main.cpp
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS} ${COMMON_CPP}

clean:
	-rm -f UserInformation Response Request
	-rm -f ${IDL_GENERATED_H} ${IDL_GENERATED_CPP}
	-rm -f ospl-error.log ospl-info.log
	-rm UserInformationPublisher UserInformationSubscriber main hello.tsn

