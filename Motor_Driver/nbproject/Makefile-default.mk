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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Motor_Driver.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Motor_Driver.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../libs/dspic_CanFestival/CanFestival-3/src/dcf.c ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c ../libs/dspic_CanFestival/CanFestival-3/src/lss.c ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c ../libs/dspic_CanFestival/CanFestival-3/src/states.c ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c ../libs/dspic_CanFestival/CanFestival-3/src/sync.c ../libs/dspic_CanFestival/CanFestival-3/src/timer.c ../libs/dspic_CanFestival/CanFestival-3/drivers/dspic33e/timer_dspic.c "PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.c" "PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.c" "PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.c" "PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.c" "PMSM/Motor Driver Code/CAN Testing/canFiles/traps.c" "PMSM/Motor Driver Code/PMSMx/CircularBuffer.c" "PMSM/Motor Driver Code/PMSMx/DMA_Transfer.c" "PMSM/Motor Driver Code/PMSMx/DRV8301.c" "PMSM/Motor Driver Code/PMSMx/PMSMBoard.c" "PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.c" "PMSM/Motor Driver Code/PMSMx/PMSM_Position.c" "PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.c" "PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.c" "PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.c" "PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.c" "PMSM/Motor Driver Code/PMSMx/SPIdsPIC.c" "PMSM/Motor Driver Code/PMSMx/Uart2.c" "PMSM/Motor Driver Code/PMSMx/cordic.c" "PMSM/Motor Driver Code/PMSMx/main.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/532265478/dcf.o ${OBJECTDIR}/_ext/532265478/emcy.o ${OBJECTDIR}/_ext/532265478/lifegrd.o ${OBJECTDIR}/_ext/532265478/lss.o ${OBJECTDIR}/_ext/532265478/nmtMaster.o ${OBJECTDIR}/_ext/532265478/nmtSlave.o ${OBJECTDIR}/_ext/532265478/objacces.o ${OBJECTDIR}/_ext/532265478/pdo.o ${OBJECTDIR}/_ext/532265478/sdo.o ${OBJECTDIR}/_ext/532265478/states.o ${OBJECTDIR}/_ext/532265478/symbols.o ${OBJECTDIR}/_ext/532265478/sync.o ${OBJECTDIR}/_ext/532265478/timer.o ${OBJECTDIR}/_ext/778741524/timer_dspic.o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o" "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o" "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o" "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o" "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o"
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/532265478/dcf.o.d ${OBJECTDIR}/_ext/532265478/emcy.o.d ${OBJECTDIR}/_ext/532265478/lifegrd.o.d ${OBJECTDIR}/_ext/532265478/lss.o.d ${OBJECTDIR}/_ext/532265478/nmtMaster.o.d ${OBJECTDIR}/_ext/532265478/nmtSlave.o.d ${OBJECTDIR}/_ext/532265478/objacces.o.d ${OBJECTDIR}/_ext/532265478/pdo.o.d ${OBJECTDIR}/_ext/532265478/sdo.o.d ${OBJECTDIR}/_ext/532265478/states.o.d ${OBJECTDIR}/_ext/532265478/symbols.o.d ${OBJECTDIR}/_ext/532265478/sync.o.d ${OBJECTDIR}/_ext/532265478/timer.o.d ${OBJECTDIR}/_ext/778741524/timer_dspic.o.d "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o.d" "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o.d"

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/532265478/dcf.o ${OBJECTDIR}/_ext/532265478/emcy.o ${OBJECTDIR}/_ext/532265478/lifegrd.o ${OBJECTDIR}/_ext/532265478/lss.o ${OBJECTDIR}/_ext/532265478/nmtMaster.o ${OBJECTDIR}/_ext/532265478/nmtSlave.o ${OBJECTDIR}/_ext/532265478/objacces.o ${OBJECTDIR}/_ext/532265478/pdo.o ${OBJECTDIR}/_ext/532265478/sdo.o ${OBJECTDIR}/_ext/532265478/states.o ${OBJECTDIR}/_ext/532265478/symbols.o ${OBJECTDIR}/_ext/532265478/sync.o ${OBJECTDIR}/_ext/532265478/timer.o ${OBJECTDIR}/_ext/778741524/timer_dspic.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/can_dspic33e_motor.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_can.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_can_state.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_objdict.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/traps.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/CircularBuffer.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/DMA_Transfer.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/DRV8301.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSMBoard.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Characterize.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Position.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Sinusoidal_Drive.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Sinusoidal_Drive_data.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Velocity.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PRBSCharacterization.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/SPIdsPIC.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/Uart2.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/cordic.o ${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/main.o

# Source Files
SOURCEFILES=../libs/dspic_CanFestival/CanFestival-3/src/dcf.c ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c ../libs/dspic_CanFestival/CanFestival-3/src/lss.c ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c ../libs/dspic_CanFestival/CanFestival-3/src/states.c ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c ../libs/dspic_CanFestival/CanFestival-3/src/sync.c ../libs/dspic_CanFestival/CanFestival-3/src/timer.c ../libs/dspic_CanFestival/CanFestival-3/drivers/dspic33e/timer_dspic.c PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.c PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.c PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.c PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.c PMSM/Motor Driver Code/CAN Testing/canFiles/traps.c PMSM/Motor Driver Code/PMSMx/CircularBuffer.c PMSM/Motor Driver Code/PMSMx/DMA_Transfer.c PMSM/Motor Driver Code/PMSMx/DRV8301.c PMSM/Motor Driver Code/PMSMx/PMSMBoard.c PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.c PMSM/Motor Driver Code/PMSMx/PMSM_Position.c PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.c PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.c PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.c PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.c PMSM/Motor Driver Code/PMSMx/SPIdsPIC.c PMSM/Motor Driver Code/PMSMx/Uart2.c PMSM/Motor Driver Code/PMSMx/cordic.c PMSM/Motor Driver Code/PMSMx/main.c


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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Motor_Driver.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP256MU806
MP_LINKER_FILE_OPTION=,--script="../../dspic33e-bootloader/dspic_bootloader/linker_motorboard_application.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/532265478/dcf.o: ../libs/dspic_CanFestival/CanFestival-3/src/dcf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/dcf.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/dcf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/dcf.c  -o ${OBJECTDIR}/_ext/532265478/dcf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/dcf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/dcf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/emcy.o: ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/emcy.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/emcy.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c  -o ${OBJECTDIR}/_ext/532265478/emcy.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/emcy.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/emcy.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/lifegrd.o: ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/lifegrd.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/lifegrd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c  -o ${OBJECTDIR}/_ext/532265478/lifegrd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/lifegrd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/lifegrd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/lss.o: ../libs/dspic_CanFestival/CanFestival-3/src/lss.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/lss.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/lss.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/lss.c  -o ${OBJECTDIR}/_ext/532265478/lss.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/lss.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/lss.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/nmtMaster.o: ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtMaster.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c  -o ${OBJECTDIR}/_ext/532265478/nmtMaster.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/nmtMaster.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/nmtMaster.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/nmtSlave.o: ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtSlave.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtSlave.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c  -o ${OBJECTDIR}/_ext/532265478/nmtSlave.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/nmtSlave.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/nmtSlave.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/objacces.o: ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/objacces.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/objacces.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c  -o ${OBJECTDIR}/_ext/532265478/objacces.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/objacces.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/objacces.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/pdo.o: ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/pdo.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/pdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c  -o ${OBJECTDIR}/_ext/532265478/pdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/pdo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/pdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/sdo.o: ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/sdo.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/sdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c  -o ${OBJECTDIR}/_ext/532265478/sdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/sdo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/sdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/states.o: ../libs/dspic_CanFestival/CanFestival-3/src/states.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/states.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/states.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/states.c  -o ${OBJECTDIR}/_ext/532265478/states.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/states.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/states.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/symbols.o: ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/symbols.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/symbols.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c  -o ${OBJECTDIR}/_ext/532265478/symbols.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/symbols.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/symbols.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/sync.o: ../libs/dspic_CanFestival/CanFestival-3/src/sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/sync.c  -o ${OBJECTDIR}/_ext/532265478/sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/sync.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/timer.o: ../libs/dspic_CanFestival/CanFestival-3/src/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/timer.c  -o ${OBJECTDIR}/_ext/532265478/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/778741524/timer_dspic.o: ../libs/dspic_CanFestival/CanFestival-3/drivers/dspic33e/timer_dspic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/778741524" 
	@${RM} ${OBJECTDIR}/_ext/778741524/timer_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/778741524/timer_dspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/drivers/dspic33e/timer_dspic.c  -o ${OBJECTDIR}/_ext/778741524/timer_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/778741524/timer_dspic.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/778741524/timer_dspic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/can_dspic33e_motor.o: PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/can_dspic33e_motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_can.o: PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_can_state.o: PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_can_state.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_objdict.o: PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_objdict.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/traps.o: PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/CAN Testing/canFiles/traps.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/CircularBuffer.o: PMSM/Motor\ Driver\ Code/PMSMx/CircularBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/CircularBuffer.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/DMA_Transfer.o: PMSM/Motor\ Driver\ Code/PMSMx/DMA_Transfer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/DMA_Transfer.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/DRV8301.o: PMSM/Motor\ Driver\ Code/PMSMx/DRV8301.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/DRV8301.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSMBoard.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSMBoard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSMBoard.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Characterize.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Characterize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Position.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Position.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSM_Position.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Sinusoidal_Drive.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Sinusoidal_Drive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Sinusoidal_Drive_data.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Sinusoidal_Drive_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Velocity.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Velocity.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PRBSCharacterization.o: PMSM/Motor\ Driver\ Code/PMSMx/PRBSCharacterization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/SPIdsPIC.o: PMSM/Motor\ Driver\ Code/PMSMx/SPIdsPIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/SPIdsPIC.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/Uart2.o: PMSM/Motor\ Driver\ Code/PMSMx/Uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/Uart2.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/cordic.o: PMSM/Motor\ Driver\ Code/PMSMx/cordic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/cordic.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/main.o: PMSM/Motor\ Driver\ Code/PMSMx/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/main.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/532265478/dcf.o: ../libs/dspic_CanFestival/CanFestival-3/src/dcf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/dcf.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/dcf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/dcf.c  -o ${OBJECTDIR}/_ext/532265478/dcf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/dcf.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/dcf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/emcy.o: ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/emcy.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/emcy.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/emcy.c  -o ${OBJECTDIR}/_ext/532265478/emcy.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/emcy.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/emcy.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/lifegrd.o: ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/lifegrd.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/lifegrd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/lifegrd.c  -o ${OBJECTDIR}/_ext/532265478/lifegrd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/lifegrd.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/lifegrd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/lss.o: ../libs/dspic_CanFestival/CanFestival-3/src/lss.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/lss.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/lss.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/lss.c  -o ${OBJECTDIR}/_ext/532265478/lss.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/lss.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/lss.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/nmtMaster.o: ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtMaster.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtMaster.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/nmtMaster.c  -o ${OBJECTDIR}/_ext/532265478/nmtMaster.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/nmtMaster.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/nmtMaster.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/nmtSlave.o: ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtSlave.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/nmtSlave.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/nmtSlave.c  -o ${OBJECTDIR}/_ext/532265478/nmtSlave.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/nmtSlave.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/nmtSlave.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/objacces.o: ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/objacces.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/objacces.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/objacces.c  -o ${OBJECTDIR}/_ext/532265478/objacces.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/objacces.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/objacces.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/pdo.o: ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/pdo.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/pdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/pdo.c  -o ${OBJECTDIR}/_ext/532265478/pdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/pdo.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/pdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/sdo.o: ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/sdo.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/sdo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/sdo.c  -o ${OBJECTDIR}/_ext/532265478/sdo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/sdo.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/sdo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/states.o: ../libs/dspic_CanFestival/CanFestival-3/src/states.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/states.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/states.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/states.c  -o ${OBJECTDIR}/_ext/532265478/states.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/states.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/states.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/symbols.o: ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/symbols.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/symbols.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/symbols.c  -o ${OBJECTDIR}/_ext/532265478/symbols.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/symbols.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/symbols.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/sync.o: ../libs/dspic_CanFestival/CanFestival-3/src/sync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/sync.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/sync.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/sync.c  -o ${OBJECTDIR}/_ext/532265478/sync.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/sync.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/sync.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/532265478/timer.o: ../libs/dspic_CanFestival/CanFestival-3/src/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/532265478" 
	@${RM} ${OBJECTDIR}/_ext/532265478/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/532265478/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/src/timer.c  -o ${OBJECTDIR}/_ext/532265478/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/532265478/timer.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/532265478/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/778741524/timer_dspic.o: ../libs/dspic_CanFestival/CanFestival-3/drivers/dspic33e/timer_dspic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/778741524" 
	@${RM} ${OBJECTDIR}/_ext/778741524/timer_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/778741524/timer_dspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../libs/dspic_CanFestival/CanFestival-3/drivers/dspic33e/timer_dspic.c  -o ${OBJECTDIR}/_ext/778741524/timer_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/778741524/timer_dspic.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/778741524/timer_dspic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/can_dspic33e_motor.o: PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/can_dspic33e_motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/can_dspic33e_motor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_can.o: PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_can_state.o: PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_can_state.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_can_state.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_objdict.o: PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/motor_objdict.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/motor_objdict.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/traps.o: PMSM/Motor\ Driver\ Code/CAN\ Testing/canFiles/traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/CAN Testing/canFiles/traps.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/CAN Testing/canFiles/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/CircularBuffer.o: PMSM/Motor\ Driver\ Code/PMSMx/CircularBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/CircularBuffer.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/CircularBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/DMA_Transfer.o: PMSM/Motor\ Driver\ Code/PMSMx/DMA_Transfer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/DMA_Transfer.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DMA_Transfer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/DRV8301.o: PMSM/Motor\ Driver\ Code/PMSMx/DRV8301.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/DRV8301.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/DRV8301.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSMBoard.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSMBoard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSMBoard.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSMBoard.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Characterize.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Characterize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Characterize.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Position.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Position.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSM_Position.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Position.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Sinusoidal_Drive.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Sinusoidal_Drive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Sinusoidal_Drive_data.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Sinusoidal_Drive_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Sinusoidal_Drive_data.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Velocity.o: PMSM/Motor\ Driver\ Code/PMSMx/PMSM_Velocity.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PMSM_Velocity.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/PRBSCharacterization.o: PMSM/Motor\ Driver\ Code/PMSMx/PRBSCharacterization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/PRBSCharacterization.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/SPIdsPIC.o: PMSM/Motor\ Driver\ Code/PMSMx/SPIdsPIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/SPIdsPIC.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/SPIdsPIC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/Uart2.o: PMSM/Motor\ Driver\ Code/PMSMx/Uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/Uart2.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/Uart2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/cordic.o: PMSM/Motor\ Driver\ Code/PMSMx/cordic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/cordic.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/cordic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/PMSM/Motor\ Driver\ Code/PMSMx/main.o: PMSM/Motor\ Driver\ Code/PMSMx/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx" 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o".d 
	@${RM} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "PMSM/Motor Driver Code/PMSMx/main.c"  -o "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/PMSM/Motor Driver Code/PMSMx/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/Motor_Driver.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../dspic33e-bootloader/dspic_bootloader/linker_motorboard_application.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Motor_Driver.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--no-local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=0,--stack=512,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Motor_Driver.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../dspic33e-bootloader/dspic_bootloader/linker_motorboard_application.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Motor_Driver.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--no-local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=0,--stack=512,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Motor_Driver.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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
