OSPL_LIBS = -lpthread -lddskernel -ldcpssacpp
LIBS=-L${OSPL_HOME}/lib ${OSPL_LIBS} -lboost_system -lboost_thread
CFLAGS = -DDEBUG_PRINT -DDEBUG_STATES -Wall -O0 -g -I. -I./include -I${OSPL_HOME}/include/dcps/C++/SACPP -I${OSPL_HOME}/include/sys
CXXFLAGS = -std=c++11
DIR = /idl
OS_H = ${OSPL_HOME}/include/sys/os.h

all: main 
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

${IDL_GENERATED}: src/idl/tsn.idl
	${OSPL_HOME}/bin/idlpp -l cpp src/idl/tsn.idl

COMMON_CPP= src/CheckStatus.cpp src/DDSEntityManager.cpp src/User.cpp src/Post.cpp

COMMON_H= $ include/CheckStatus.h include/DDSEntityManager.h include/dds_io.h

USER_H =
main:${IDL_GENERATED_H} ${IDL_GENERATED_CPP} src/main.cpp src/Request.cpp src/Response.cpp src/Message.cpp
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS} ${COMMON_CPP} -pthread

testPosts: ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} testing/testPosts.cpp
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS} ${COMMON_CPP} -lboost_unit_test_framework
testUsers:${IDL_GENERATED_H} ${IDL_GENERATED_CPP} testing/testUsers.cpp
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS} ${COMMON_CPP} -lboost_unit_test_framework
clean:
	-rm -f UserInformation Response Request
	-rm -f ${IDL_GENERATED_H} ${IDL_GENERATED_CPP}
	-rm -f ospl-error.log ospl-info.log
	-rm -f  main my_user.tsn
	-rm -f *.tsn
	-rm -f testPosts
	-rm -f testUsers
