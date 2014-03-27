#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=a
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dspic_CanFestival.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=a
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dspic_CanFestival.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=CanFestival-3/src/dcf.c CanFestival-3/src/emcy.c CanFestival-3/src/lifegrd.c CanFestival-3/src/lss.c CanFestival-3/src/nmtMaster.c CanFestival-3/src/nmtSlave.c CanFestival-3/src/objacces.c CanFestival-3/src/pdo.c CanFestival-3/src/sdo.c CanFestival-3/src/states.c CanFestival-3/src/sync.c CanFestival-3/src/timer.c CanFestival-3/drivers/dspic33e/can_dspic33e.c CanFestival-3/drivers/dspic33e/timer_dspic.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/CanFestival-3/src/dcf.o ${OBJECTDIR}/CanFestival-3/src/emcy.o ${OBJECTDIR}/CanFestival-3/src/lifegrd.o ${OBJECTDIR}/CanFestival-3/src/lss.o ${OBJECTDIR}/CanFestival-3/src/nmtMaster.o ${OBJECTDIR}/CanFestival-3/src/nmtSlave.o ${OBJECTDIR}/CanFestival-3/src/objacces.o ${OBJECTDIR}/CanFestival-3/src/pdo.o ${OBJECTDIR}/CanFestival-3/src/sdo.o ${OBJECTDIR}/CanFestival-3/src/states.o ${OBJECTDIR}/CanFestival-3/src/sync.o ${OBJECTDIR}/CanFestival-3/src/timer.o ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o
POSSIBLE_DEPFILES=${OBJECTDIR}/CanFestival-3/src/dcf.o.d ${OBJECTDIR}/CanFestival-3/src/emcy.o.d ${OBJECTDIR}/CanFestival-3/src/lifegrd.o.d ${OBJECTDIR}/CanFestival-3/src/lss.o.d ${OBJECTDIR}/CanFestival-3/src/nmtMaster.o.d ${OBJECTDIR}/CanFestival-3/src/nmtSlave.o.d ${OBJECTDIR}/CanFestival-3/src/objacces.o.d ${OBJECTDIR}/CanFestival-3/src/pdo.o.d ${OBJECTDIR}/CanFestival-3/src/sdo.o.d ${OBJECTDIR}/CanFestival-3/src/states.o.d ${OBJECTDIR}/CanFestival-3/src/sync.o.d ${OBJECTDIR}/CanFestival-3/src/timer.o.d ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o.d ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/CanFestival-3/src/dcf.o ${OBJECTDIR}/CanFestival-3/src/emcy.o ${OBJECTDIR}/CanFestival-3/src/lifegrd.o ${OBJECTDIR}/CanFestival-3/src/lss.o ${OBJECTDIR}/CanFestival-3/src/nmtMaster.o ${OBJECTDIR}/CanFestival-3/src/nmtSlave.o ${OBJECTDIR}/CanFestival-3/src/objacces.o ${OBJECTDIR}/CanFestival-3/src/pdo.o ${OBJECTDIR}/CanFestival-3/src/sdo.o ${OBJECTDIR}/CanFestival-3/src/states.o ${OBJECTDIR}/CanFestival-3/src/sync.o ${OBJECTDIR}/CanFestival-3/src/timer.o ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o

# Source Files
SOURCEFILES=CanFestival-3/src/dcf.c CanFestival-3/src/emcy.c CanFestival-3/src/lifegrd.c CanFestival-3/src/lss.c CanFestival-3/src/nmtMaster.c CanFestival-3/src/nmtSlave.c CanFestival-3/src/objacces.c CanFestival-3/src/pdo.c CanFestival-3/src/sdo.c CanFestival-3/src/states.c CanFestival-3/src/sync.c CanFestival-3/src/timer.c CanFestival-3/drivers/dspic33e/can_dspic33e.c CanFestival-3/drivers/dspic33e/timer_dspic.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/dspic_CanFestival.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP128GP506
MP_LINKER_FILE_OPTION=,--script=p33EP128GP506.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/CanFestival-3/src/dcf.o: CanFestival-3/src/dcf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/dcf.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/dcf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/dcf.c  -o ${OBJECTDIR}/CanFestival-3/src/dcf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/dcf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/dcf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/emcy.o: CanFestival-3/src/emcy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/emcy.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/emcy.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/emcy.c  -o ${OBJECTDIR}/CanFestival-3/src/emcy.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/emcy.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/emcy.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/lifegrd.o: CanFestival-3/src/lifegrd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/lifegrd.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/lifegrd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/lifegrd.c  -o ${OBJECTDIR}/CanFestival-3/src/lifegrd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/lifegrd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/lifegrd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/lss.o: CanFestival-3/src/lss.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/lss.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/lss.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/lss.c  -o ${OBJECTDIR}/CanFestival-3/src/lss.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/lss.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/lss.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/nmtMaster.o: CanFestival-3/src/nmtMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/nmtMaster.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/nmtMaster.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/nmtMaster.c  -o ${OBJECTDIR}/CanFestival-3/src/nmtMaster.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/nmtMaster.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/nmtMaster.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/nmtSlave.o: CanFestival-3/src/nmtSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/nmtSlave.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/nmtSlave.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/nmtSlave.c  -o ${OBJECTDIR}/CanFestival-3/src/nmtSlave.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/nmtSlave.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/nmtSlave.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/objacces.o: CanFestival-3/src/objacces.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/objacces.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/objacces.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/objacces.c  -o ${OBJECTDIR}/CanFestival-3/src/objacces.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/objacces.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/objacces.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/pdo.o: CanFestival-3/src/pdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/pdo.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/pdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/pdo.c  -o ${OBJECTDIR}/CanFestival-3/src/pdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/pdo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/pdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/sdo.o: CanFestival-3/src/sdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/sdo.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/sdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/sdo.c  -o ${OBJECTDIR}/CanFestival-3/src/sdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/sdo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/sdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/states.o: CanFestival-3/src/states.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/states.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/states.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/states.c  -o ${OBJECTDIR}/CanFestival-3/src/states.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/states.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/states.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/sync.o: CanFestival-3/src/sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/sync.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/sync.c  -o ${OBJECTDIR}/CanFestival-3/src/sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/timer.o: CanFestival-3/src/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/timer.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/timer.c  -o ${OBJECTDIR}/CanFestival-3/src/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o: CanFestival-3/drivers/dspic33e/can_dspic33e.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e 
	@${RM} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/drivers/dspic33e/can_dspic33e.c  -o ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o: CanFestival-3/drivers/dspic33e/timer_dspic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e 
	@${RM} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/drivers/dspic33e/timer_dspic.c  -o ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/CanFestival-3/src/dcf.o: CanFestival-3/src/dcf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/dcf.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/dcf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/dcf.c  -o ${OBJECTDIR}/CanFestival-3/src/dcf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/dcf.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/dcf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/emcy.o: CanFestival-3/src/emcy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/emcy.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/emcy.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/emcy.c  -o ${OBJECTDIR}/CanFestival-3/src/emcy.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/emcy.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/emcy.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/lifegrd.o: CanFestival-3/src/lifegrd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/lifegrd.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/lifegrd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/lifegrd.c  -o ${OBJECTDIR}/CanFestival-3/src/lifegrd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/lifegrd.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/lifegrd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/lss.o: CanFestival-3/src/lss.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/lss.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/lss.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/lss.c  -o ${OBJECTDIR}/CanFestival-3/src/lss.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/lss.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/lss.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/nmtMaster.o: CanFestival-3/src/nmtMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/nmtMaster.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/nmtMaster.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/nmtMaster.c  -o ${OBJECTDIR}/CanFestival-3/src/nmtMaster.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/nmtMaster.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/nmtMaster.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/nmtSlave.o: CanFestival-3/src/nmtSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/nmtSlave.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/nmtSlave.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/nmtSlave.c  -o ${OBJECTDIR}/CanFestival-3/src/nmtSlave.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/nmtSlave.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/nmtSlave.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/objacces.o: CanFestival-3/src/objacces.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/objacces.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/objacces.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/objacces.c  -o ${OBJECTDIR}/CanFestival-3/src/objacces.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/objacces.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/objacces.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/pdo.o: CanFestival-3/src/pdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/pdo.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/pdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/pdo.c  -o ${OBJECTDIR}/CanFestival-3/src/pdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/pdo.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/pdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/sdo.o: CanFestival-3/src/sdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/sdo.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/sdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/sdo.c  -o ${OBJECTDIR}/CanFestival-3/src/sdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/sdo.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/sdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/states.o: CanFestival-3/src/states.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/states.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/states.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/states.c  -o ${OBJECTDIR}/CanFestival-3/src/states.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/states.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/states.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/sync.o: CanFestival-3/src/sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/sync.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/sync.c  -o ${OBJECTDIR}/CanFestival-3/src/sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/sync.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/src/timer.o: CanFestival-3/src/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/src 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/timer.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/src/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/src/timer.c  -o ${OBJECTDIR}/CanFestival-3/src/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/src/timer.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/src/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o: CanFestival-3/drivers/dspic33e/can_dspic33e.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e 
	@${RM} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/drivers/dspic33e/can_dspic33e.c  -o ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/drivers/dspic33e/can_dspic33e.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o: CanFestival-3/drivers/dspic33e/timer_dspic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e 
	@${RM} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o.d 
	@${RM} ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  CanFestival-3/drivers/dspic33e/timer_dspic.c  -o ${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o.d"      -mno-eds-warn  -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/CanFestival-3/drivers/dspic33e/timer_dspic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: archive
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/dspic_CanFestival.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/dspic_CanFestival.${OUTPUT_SUFFIX} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  -omf=elf -r dist/${CND_CONF}/${IMAGE_TYPE}/dspic_CanFestival.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/dspic_CanFestival.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/dspic_CanFestival.${OUTPUT_SUFFIX} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  -omf=elf -r dist/${CND_CONF}/${IMAGE_TYPE}/dspic_CanFestival.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
