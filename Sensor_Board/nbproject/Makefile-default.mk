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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=ObjDict.c clock.c main.c sensor_can.c sensor_hallsensors.c sensor_http.c sensor_imu.c sensor_iptest.c sensor_led.c sensor_loadcell.c sensor_memdebug.c sensor_pindefs.c sensor_pmsm.c sensor_rf.c sensor_state.c sensor_timers.c sensor_uart.c superball_circularbuffer.c traps.c xbee_API.c ../libs/dspic_CanFestival/CanFestival-3/src/dcf.c ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c ../libs/dspic_CanFestival/CanFestival-3/src/lss.c ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c ../libs/dspic_CanFestival/CanFestival-3/src/states.c ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c ../libs/dspic_CanFestival/CanFestival-3/src/sync.c ../libs/dspic_CanFestival/CanFestival-3/src/timer.c ../libs/dspic_http-parser/http_parser.c ../libs/dspic_jsmn/jsmn.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ObjDict.o ${OBJECTDIR}/clock.o ${OBJECTDIR}/main.o ${OBJECTDIR}/sensor_can.o ${OBJECTDIR}/sensor_hallsensors.o ${OBJECTDIR}/sensor_http.o ${OBJECTDIR}/sensor_imu.o ${OBJECTDIR}/sensor_iptest.o ${OBJECTDIR}/sensor_led.o ${OBJECTDIR}/sensor_loadcell.o ${OBJECTDIR}/sensor_memdebug.o ${OBJECTDIR}/sensor_pindefs.o ${OBJECTDIR}/sensor_pmsm.o ${OBJECTDIR}/sensor_rf.o ${OBJECTDIR}/sensor_state.o ${OBJECTDIR}/sensor_timers.o ${OBJECTDIR}/sensor_uart.o ${OBJECTDIR}/superball_circularbuffer.o ${OBJECTDIR}/traps.o ${OBJECTDIR}/xbee_API.o ${OBJECTDIR}/_ext/532265478/dcf.o ${OBJECTDIR}/_ext/532265478/emcy.o ${OBJECTDIR}/_ext/532265478/lifegrd.o ${OBJECTDIR}/_ext/532265478/lss.o ${OBJECTDIR}/_ext/532265478/nmtMaster.o ${OBJECTDIR}/_ext/532265478/nmtSlave.o ${OBJECTDIR}/_ext/532265478/objacces.o ${OBJECTDIR}/_ext/532265478/pdo.o ${OBJECTDIR}/_ext/532265478/sdo.o ${OBJECTDIR}/_ext/532265478/states.o ${OBJECTDIR}/_ext/532265478/symbols.o ${OBJECTDIR}/_ext/532265478/sync.o ${OBJECTDIR}/_ext/532265478/timer.o ${OBJECTDIR}/_ext/2093447502/http_parser.o ${OBJECTDIR}/_ext/1162098784/jsmn.o
POSSIBLE_DEPFILES=${OBJECTDIR}/ObjDict.o.d ${OBJECTDIR}/clock.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/sensor_can.o.d ${OBJECTDIR}/sensor_hallsensors.o.d ${OBJECTDIR}/sensor_http.o.d ${OBJECTDIR}/sensor_imu.o.d ${OBJECTDIR}/sensor_iptest.o.d ${OBJECTDIR}/sensor_led.o.d ${OBJECTDIR}/sensor_loadcell.o.d ${OBJECTDIR}/sensor_memdebug.o.d ${OBJECTDIR}/sensor_pindefs.o.d ${OBJECTDIR}/sensor_pmsm.o.d ${OBJECTDIR}/sensor_rf.o.d ${OBJECTDIR}/sensor_state.o.d ${OBJECTDIR}/sensor_timers.o.d ${OBJECTDIR}/sensor_uart.o.d ${OBJECTDIR}/superball_circularbuffer.o.d ${OBJECTDIR}/traps.o.d ${OBJECTDIR}/xbee_API.o.d ${OBJECTDIR}/_ext/532265478/dcf.o.d ${OBJECTDIR}/_ext/532265478/emcy.o.d ${OBJECTDIR}/_ext/532265478/lifegrd.o.d ${OBJECTDIR}/_ext/532265478/lss.o.d ${OBJECTDIR}/_ext/532265478/nmtMaster.o.d ${OBJECTDIR}/_ext/532265478/nmtSlave.o.d ${OBJECTDIR}/_ext/532265478/objacces.o.d ${OBJECTDIR}/_ext/532265478/pdo.o.d ${OBJECTDIR}/_ext/532265478/sdo.o.d ${OBJECTDIR}/_ext/532265478/states.o.d ${OBJECTDIR}/_ext/532265478/symbols.o.d ${OBJECTDIR}/_ext/532265478/sync.o.d ${OBJECTDIR}/_ext/532265478/timer.o.d ${OBJECTDIR}/_ext/2093447502/http_parser.o.d ${OBJECTDIR}/_ext/1162098784/jsmn.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ObjDict.o ${OBJECTDIR}/clock.o ${OBJECTDIR}/main.o ${OBJECTDIR}/sensor_can.o ${OBJECTDIR}/sensor_hallsensors.o ${OBJECTDIR}/sensor_http.o ${OBJECTDIR}/sensor_imu.o ${OBJECTDIR}/sensor_iptest.o ${OBJECTDIR}/sensor_led.o ${OBJECTDIR}/sensor_loadcell.o ${OBJECTDIR}/sensor_memdebug.o ${OBJECTDIR}/sensor_pindefs.o ${OBJECTDIR}/sensor_pmsm.o ${OBJECTDIR}/sensor_rf.o ${OBJECTDIR}/sensor_state.o ${OBJECTDIR}/sensor_timers.o ${OBJECTDIR}/sensor_uart.o ${OBJECTDIR}/superball_circularbuffer.o ${OBJECTDIR}/traps.o ${OBJECTDIR}/xbee_API.o ${OBJECTDIR}/_ext/532265478/dcf.o ${OBJECTDIR}/_ext/532265478/emcy.o ${OBJECTDIR}/_ext/532265478/lifegrd.o ${OBJECTDIR}/_ext/532265478/lss.o ${OBJECTDIR}/_ext/532265478/nmtMaster.o ${OBJECTDIR}/_ext/532265478/nmtSlave.o ${OBJECTDIR}/_ext/532265478/objacces.o ${OBJECTDIR}/_ext/532265478/pdo.o ${OBJECTDIR}/_ext/532265478/sdo.o ${OBJECTDIR}/_ext/532265478/states.o ${OBJECTDIR}/_ext/532265478/symbols.o ${OBJECTDIR}/_ext/532265478/sync.o ${OBJECTDIR}/_ext/532265478/timer.o ${OBJECTDIR}/_ext/2093447502/http_parser.o ${OBJECTDIR}/_ext/1162098784/jsmn.o

# Source Files
SOURCEFILES=ObjDict.c clock.c main.c sensor_can.c sensor_hallsensors.c sensor_http.c sensor_imu.c sensor_iptest.c sensor_led.c sensor_loadcell.c sensor_memdebug.c sensor_pindefs.c sensor_pmsm.c sensor_rf.c sensor_state.c sensor_timers.c sensor_uart.c superball_circularbuffer.c traps.c xbee_API.c ../libs/dspic_CanFestival/CanFestival-3/src/dcf.c ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c ../libs/dspic_CanFestival/CanFestival-3/src/lss.c ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c ../libs/dspic_CanFestival/CanFestival-3/src/states.c ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c ../libs/dspic_CanFestival/CanFestival-3/src/sync.c ../libs/dspic_CanFestival/CanFestival-3/src/timer.c ../libs/dspic_http-parser/http_parser.c ../libs/dspic_jsmn/jsmn.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP128MC506
MP_LINKER_FILE_OPTION=,--script=p33EP128MC506.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ObjDict.o: ObjDict.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ObjDict.o.d 
	@${RM} ${OBJECTDIR}/ObjDict.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ObjDict.c  -o ${OBJECTDIR}/ObjDict.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ObjDict.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ObjDict.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/clock.o: clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/clock.o.d 
	@${RM} ${OBJECTDIR}/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clock.c  -o ${OBJECTDIR}/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_can.o: sensor_can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_can.o.d 
	@${RM} ${OBJECTDIR}/sensor_can.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_can.c  -o ${OBJECTDIR}/sensor_can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_can.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_hallsensors.o: sensor_hallsensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_hallsensors.o.d 
	@${RM} ${OBJECTDIR}/sensor_hallsensors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_hallsensors.c  -o ${OBJECTDIR}/sensor_hallsensors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_hallsensors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_hallsensors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_http.o: sensor_http.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_http.o.d 
	@${RM} ${OBJECTDIR}/sensor_http.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_http.c  -o ${OBJECTDIR}/sensor_http.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_http.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_http.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_imu.o: sensor_imu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_imu.o.d 
	@${RM} ${OBJECTDIR}/sensor_imu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_imu.c  -o ${OBJECTDIR}/sensor_imu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_imu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_imu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_iptest.o: sensor_iptest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_iptest.o.d 
	@${RM} ${OBJECTDIR}/sensor_iptest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_iptest.c  -o ${OBJECTDIR}/sensor_iptest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_iptest.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_iptest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_led.o: sensor_led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_led.o.d 
	@${RM} ${OBJECTDIR}/sensor_led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_led.c  -o ${OBJECTDIR}/sensor_led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_led.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_led.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_loadcell.o: sensor_loadcell.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_loadcell.o.d 
	@${RM} ${OBJECTDIR}/sensor_loadcell.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_loadcell.c  -o ${OBJECTDIR}/sensor_loadcell.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_loadcell.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_loadcell.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_memdebug.o: sensor_memdebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_memdebug.o.d 
	@${RM} ${OBJECTDIR}/sensor_memdebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_memdebug.c  -o ${OBJECTDIR}/sensor_memdebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_memdebug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_memdebug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_pindefs.o: sensor_pindefs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_pindefs.o.d 
	@${RM} ${OBJECTDIR}/sensor_pindefs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_pindefs.c  -o ${OBJECTDIR}/sensor_pindefs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_pindefs.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_pindefs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_pmsm.o: sensor_pmsm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_pmsm.o.d 
	@${RM} ${OBJECTDIR}/sensor_pmsm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_pmsm.c  -o ${OBJECTDIR}/sensor_pmsm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_pmsm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_pmsm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_rf.o: sensor_rf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_rf.o.d 
	@${RM} ${OBJECTDIR}/sensor_rf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_rf.c  -o ${OBJECTDIR}/sensor_rf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_rf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_rf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_state.o: sensor_state.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_state.o.d 
	@${RM} ${OBJECTDIR}/sensor_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_state.c  -o ${OBJECTDIR}/sensor_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_state.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_timers.o: sensor_timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_timers.o.d 
	@${RM} ${OBJECTDIR}/sensor_timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_timers.c  -o ${OBJECTDIR}/sensor_timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_uart.o: sensor_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_uart.o.d 
	@${RM} ${OBJECTDIR}/sensor_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_uart.c  -o ${OBJECTDIR}/sensor_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/superball_circularbuffer.o: superball_circularbuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/superball_circularbuffer.o.d 
	@${RM} ${OBJECTDIR}/superball_circularbuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  superball_circularbuffer.c  -o ${OBJECTDIR}/superball_circularbuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/superball_circularbuffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/superball_circularbuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/traps.o: traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/traps.o.d 
	@${RM} ${OBJECTDIR}/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  traps.c  -o ${OBJECTDIR}/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/xbee_API.o: xbee_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/xbee_API.o.d 
	@${RM} ${OBJECTDIR}/xbee_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  xbee_API.c  -o ${OBJECTDIR}/xbee_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/xbee_API.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/xbee_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/dcf.o: ../libs/dspic_CanFestival/CanFestival-3/src/dcf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/dcf.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/dcf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/dcf.c  -o ${OBJECTDIR}/_ext/532265478/dcf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/dcf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/dcf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/emcy.o: ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/emcy.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/emcy.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c  -o ${OBJECTDIR}/_ext/532265478/emcy.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/emcy.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/emcy.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/lifegrd.o: ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/lifegrd.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/lifegrd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c  -o ${OBJECTDIR}/_ext/532265478/lifegrd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/lifegrd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/lifegrd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/lss.o: ../libs/dspic_CanFestival/CanFestival-3/src/lss.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/lss.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/lss.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/lss.c  -o ${OBJECTDIR}/_ext/532265478/lss.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/lss.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/lss.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/nmtMaster.o: ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtMaster.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c  -o ${OBJECTDIR}/_ext/532265478/nmtMaster.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/nmtMaster.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/nmtMaster.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/nmtSlave.o: ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtSlave.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtSlave.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c  -o ${OBJECTDIR}/_ext/532265478/nmtSlave.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/nmtSlave.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/nmtSlave.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/objacces.o: ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/objacces.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/objacces.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c  -o ${OBJECTDIR}/_ext/532265478/objacces.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/objacces.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/objacces.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/pdo.o: ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/pdo.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/pdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c  -o ${OBJECTDIR}/_ext/532265478/pdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/pdo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/pdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/sdo.o: ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/sdo.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/sdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c  -o ${OBJECTDIR}/_ext/532265478/sdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/sdo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/sdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/states.o: ../libs/dspic_CanFestival/CanFestival-3/src/states.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/states.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/states.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/states.c  -o ${OBJECTDIR}/_ext/532265478/states.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/states.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/states.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/symbols.o: ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/symbols.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/symbols.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c  -o ${OBJECTDIR}/_ext/532265478/symbols.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/symbols.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/symbols.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/sync.o: ../libs/dspic_CanFestival/CanFestival-3/src/sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/sync.c  -o ${OBJECTDIR}/_ext/532265478/sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/timer.o: ../libs/dspic_CanFestival/CanFestival-3/src/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/timer.c  -o ${OBJECTDIR}/_ext/532265478/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2093447502/http_parser.o: ../libs/dspic_http-parser/http_parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2093447502 
	@${RM} ${OBJECTDIR}/_ext/2093447502/http_parser.o.d 
	@${RM} ${OBJECTDIR}/_ext/2093447502/http_parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_http-parser/http_parser.c  -o ${OBJECTDIR}/_ext/2093447502/http_parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2093447502/http_parser.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2093447502/http_parser.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1162098784/jsmn.o: ../libs/dspic_jsmn/jsmn.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1162098784 
	@${RM} ${OBJECTDIR}/_ext/1162098784/jsmn.o.d 
	@${RM} ${OBJECTDIR}/_ext/1162098784/jsmn.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_jsmn/jsmn.c  -o ${OBJECTDIR}/_ext/1162098784/jsmn.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1162098784/jsmn.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1162098784/jsmn.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/ObjDict.o: ObjDict.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ObjDict.o.d 
	@${RM} ${OBJECTDIR}/ObjDict.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ObjDict.c  -o ${OBJECTDIR}/ObjDict.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ObjDict.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ObjDict.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/clock.o: clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/clock.o.d 
	@${RM} ${OBJECTDIR}/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  clock.c  -o ${OBJECTDIR}/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/clock.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_can.o: sensor_can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_can.o.d 
	@${RM} ${OBJECTDIR}/sensor_can.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_can.c  -o ${OBJECTDIR}/sensor_can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_can.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_hallsensors.o: sensor_hallsensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_hallsensors.o.d 
	@${RM} ${OBJECTDIR}/sensor_hallsensors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_hallsensors.c  -o ${OBJECTDIR}/sensor_hallsensors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_hallsensors.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_hallsensors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_http.o: sensor_http.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_http.o.d 
	@${RM} ${OBJECTDIR}/sensor_http.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_http.c  -o ${OBJECTDIR}/sensor_http.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_http.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_http.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_imu.o: sensor_imu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_imu.o.d 
	@${RM} ${OBJECTDIR}/sensor_imu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_imu.c  -o ${OBJECTDIR}/sensor_imu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_imu.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_imu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_iptest.o: sensor_iptest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_iptest.o.d 
	@${RM} ${OBJECTDIR}/sensor_iptest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_iptest.c  -o ${OBJECTDIR}/sensor_iptest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_iptest.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_iptest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_led.o: sensor_led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_led.o.d 
	@${RM} ${OBJECTDIR}/sensor_led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_led.c  -o ${OBJECTDIR}/sensor_led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_led.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_led.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_loadcell.o: sensor_loadcell.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_loadcell.o.d 
	@${RM} ${OBJECTDIR}/sensor_loadcell.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_loadcell.c  -o ${OBJECTDIR}/sensor_loadcell.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_loadcell.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_loadcell.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_memdebug.o: sensor_memdebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_memdebug.o.d 
	@${RM} ${OBJECTDIR}/sensor_memdebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_memdebug.c  -o ${OBJECTDIR}/sensor_memdebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_memdebug.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_memdebug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_pindefs.o: sensor_pindefs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_pindefs.o.d 
	@${RM} ${OBJECTDIR}/sensor_pindefs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_pindefs.c  -o ${OBJECTDIR}/sensor_pindefs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_pindefs.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_pindefs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_pmsm.o: sensor_pmsm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_pmsm.o.d 
	@${RM} ${OBJECTDIR}/sensor_pmsm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_pmsm.c  -o ${OBJECTDIR}/sensor_pmsm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_pmsm.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_pmsm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_rf.o: sensor_rf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_rf.o.d 
	@${RM} ${OBJECTDIR}/sensor_rf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_rf.c  -o ${OBJECTDIR}/sensor_rf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_rf.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_rf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_state.o: sensor_state.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_state.o.d 
	@${RM} ${OBJECTDIR}/sensor_state.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_state.c  -o ${OBJECTDIR}/sensor_state.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_state.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_state.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_timers.o: sensor_timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_timers.o.d 
	@${RM} ${OBJECTDIR}/sensor_timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_timers.c  -o ${OBJECTDIR}/sensor_timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_timers.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sensor_uart.o: sensor_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensor_uart.o.d 
	@${RM} ${OBJECTDIR}/sensor_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sensor_uart.c  -o ${OBJECTDIR}/sensor_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensor_uart.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sensor_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/superball_circularbuffer.o: superball_circularbuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/superball_circularbuffer.o.d 
	@${RM} ${OBJECTDIR}/superball_circularbuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  superball_circularbuffer.c  -o ${OBJECTDIR}/superball_circularbuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/superball_circularbuffer.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/superball_circularbuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/traps.o: traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/traps.o.d 
	@${RM} ${OBJECTDIR}/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  traps.c  -o ${OBJECTDIR}/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/traps.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/xbee_API.o: xbee_API.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/xbee_API.o.d 
	@${RM} ${OBJECTDIR}/xbee_API.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  xbee_API.c  -o ${OBJECTDIR}/xbee_API.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/xbee_API.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/xbee_API.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/dcf.o: ../libs/dspic_CanFestival/CanFestival-3/src/dcf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/dcf.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/dcf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/dcf.c  -o ${OBJECTDIR}/_ext/532265478/dcf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/dcf.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/dcf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/emcy.o: ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/emcy.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/emcy.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c  -o ${OBJECTDIR}/_ext/532265478/emcy.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/emcy.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/emcy.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/lifegrd.o: ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/lifegrd.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/lifegrd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c  -o ${OBJECTDIR}/_ext/532265478/lifegrd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/lifegrd.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/lifegrd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/lss.o: ../libs/dspic_CanFestival/CanFestival-3/src/lss.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/lss.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/lss.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/lss.c  -o ${OBJECTDIR}/_ext/532265478/lss.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/lss.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/lss.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/nmtMaster.o: ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtMaster.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c  -o ${OBJECTDIR}/_ext/532265478/nmtMaster.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/nmtMaster.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/nmtMaster.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/nmtSlave.o: ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtSlave.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtSlave.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c  -o ${OBJECTDIR}/_ext/532265478/nmtSlave.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/nmtSlave.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/nmtSlave.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/objacces.o: ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/objacces.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/objacces.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c  -o ${OBJECTDIR}/_ext/532265478/objacces.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/objacces.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/objacces.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/pdo.o: ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/pdo.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/pdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c  -o ${OBJECTDIR}/_ext/532265478/pdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/pdo.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/pdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/sdo.o: ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/sdo.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/sdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c  -o ${OBJECTDIR}/_ext/532265478/sdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/sdo.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/sdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/states.o: ../libs/dspic_CanFestival/CanFestival-3/src/states.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/states.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/states.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/states.c  -o ${OBJECTDIR}/_ext/532265478/states.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/states.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/states.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/symbols.o: ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/symbols.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/symbols.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c  -o ${OBJECTDIR}/_ext/532265478/symbols.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/symbols.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/symbols.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/sync.o: ../libs/dspic_CanFestival/CanFestival-3/src/sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/sync.c  -o ${OBJECTDIR}/_ext/532265478/sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/sync.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/timer.o: ../libs/dspic_CanFestival/CanFestival-3/src/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/532265478 
	@${RM} ${OBJECTDIR}/_ext/532265478/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/timer.c  -o ${OBJECTDIR}/_ext/532265478/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/timer.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2093447502/http_parser.o: ../libs/dspic_http-parser/http_parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2093447502 
	@${RM} ${OBJECTDIR}/_ext/2093447502/http_parser.o.d 
	@${RM} ${OBJECTDIR}/_ext/2093447502/http_parser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_http-parser/http_parser.c  -o ${OBJECTDIR}/_ext/2093447502/http_parser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2093447502/http_parser.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2093447502/http_parser.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1162098784/jsmn.o: ../libs/dspic_jsmn/jsmn.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1162098784 
	@${RM} ${OBJECTDIR}/_ext/1162098784/jsmn.o.d 
	@${RM} ${OBJECTDIR}/_ext/1162098784/jsmn.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_jsmn/jsmn.c  -o ${OBJECTDIR}/_ext/1162098784/jsmn.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1162098784/jsmn.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1162098784/jsmn.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../libs/dspic_CanFestival/dist/default/debug/dspic_CanFestival.a ../libs/dspic_http-parser/dist/default/debug/dspic_http-parser.a ../libs/dspic_jsmn/dist/default/debug/dspic_jsmn.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    ../libs/dspic_CanFestival/dist/default/debug/dspic_CanFestival.a ../libs/dspic_http-parser/dist/default/debug/dspic_http-parser.a ../libs/dspic_jsmn/dist/default/debug/dspic_jsmn.a  -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=5000,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../libs/dspic_CanFestival/dist/default/production/dspic_CanFestival.a ../libs/dspic_http-parser/dist/default/production/dspic_http-parser.a ../libs/dspic_jsmn/dist/default/production/dspic_jsmn.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Board.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    ../libs/dspic_CanFestival/dist/default/production/dspic_CanFestival.a ../libs/dspic_http-parser/dist/default/production/dspic_http-parser.a ../libs/dspic_jsmn/dist/default/production/dspic_jsmn.a  -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=5000,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Board.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:
	cd ../libs/dspic_CanFestival && ${MAKE}  -f Makefile CONF=default
	cd ../libs/dspic_http-parser && ${MAKE}  -f Makefile CONF=default
	cd ../libs/dspic_jsmn && ${MAKE}  -f Makefile CONF=default


# Subprojects
.clean-subprojects:
	cd ../libs/dspic_CanFestival && rm -rf "build/default" "dist/default"
	cd ../libs/dspic_http-parser && rm -rf "build/default" "dist/default"
	cd ../libs/dspic_jsmn && rm -rf "build/default" "dist/default"

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
