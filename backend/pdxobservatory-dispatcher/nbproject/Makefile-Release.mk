#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/dbconn.o \
	${OBJECTDIR}/guides/cnc_context/temperature.o \
	${OBJECTDIR}/guides/guide.o \
	${OBJECTDIR}/guides/guide_mobility.o \
	${OBJECTDIR}/guides/guide_mobility_extended.o \
	${OBJECTDIR}/guides/guide_temperature.o \
	${OBJECTDIR}/guides/types.o \
	${OBJECTDIR}/pdxobservatory.o \
	${OBJECTDIR}/socketconnhandler.o \
	${OBJECTDIR}/threadlib.o \
	${OBJECTDIR}/utils.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dbtest

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dbtest: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dbtest ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/dbconn.o: dbconn.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dbconn.o dbconn.cpp

${OBJECTDIR}/guides/cnc_context/temperature.o: guides/cnc_context/temperature.cpp 
	${MKDIR} -p ${OBJECTDIR}/guides/cnc_context
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/guides/cnc_context/temperature.o guides/cnc_context/temperature.cpp

${OBJECTDIR}/guides/guide.o: guides/guide.cpp 
	${MKDIR} -p ${OBJECTDIR}/guides
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/guides/guide.o guides/guide.cpp

${OBJECTDIR}/guides/guide_mobility.o: guides/guide_mobility.cpp 
	${MKDIR} -p ${OBJECTDIR}/guides
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/guides/guide_mobility.o guides/guide_mobility.cpp

${OBJECTDIR}/guides/guide_mobility_extended.o: guides/guide_mobility_extended.cpp 
	${MKDIR} -p ${OBJECTDIR}/guides
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/guides/guide_mobility_extended.o guides/guide_mobility_extended.cpp

${OBJECTDIR}/guides/guide_temperature.o: guides/guide_temperature.cpp 
	${MKDIR} -p ${OBJECTDIR}/guides
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/guides/guide_temperature.o guides/guide_temperature.cpp

${OBJECTDIR}/guides/types.o: guides/types.cpp 
	${MKDIR} -p ${OBJECTDIR}/guides
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/guides/types.o guides/types.cpp

${OBJECTDIR}/pdxobservatory.o: pdxobservatory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pdxobservatory.o pdxobservatory.cpp

${OBJECTDIR}/socketconnhandler.o: socketconnhandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/socketconnhandler.o socketconnhandler.cpp

${OBJECTDIR}/threadlib.o: threadlib.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/threadlib.o threadlib.cpp

${OBJECTDIR}/utils.o: utils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils.o utils.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dbtest

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
