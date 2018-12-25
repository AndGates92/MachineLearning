#!/bin/sh

# Shell script settings
memleak=0
tests=0
clean=0
debug=0
doc=0


# Make file settings
EXENAME=ml
EXEDIR=bin

LOGDIR=log
DEBUGLOG=debug.log
COMPLOG=compile.log
DOCLOG=doc.log
EXELOG=${EXENAME}.log
VALGRINDTESLOG=valgrind_tes.log
VALGRINDTELLOG=valgrind_tel.log
VALGRINDALLLOG=valgrind_all.log
EXEVALGRINDLOG=${EXENAME}_valgrind.log

DATASET_DIR=dataset/mnist
TRAIN_SET=train-images-idx3-ubyte
TRAIN_LABEL=train-labels-idx1-ubyte
TEST_SET=t10k-images-idx3-ubyte
TEST_LABEL=t10k-labels-idx1-ubyte

VERBOSITY=LOW

CEXTRAFLAGS=-DENABLE_ASSERTIONS

DATE_FORMAT="%a %d %b %Y"
TIME_FORMAT=%H:%M:%S

usage () {
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]  - Usage:"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]  - >$0 <options>"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --clean|-c:	delete generated files"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --doc|-d:	generate documentation"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --debug|-g:	dump makefile flags to ${LOGDIR}/${DEBUGLOG}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --memleak|-m:	compile and check memory leaks using valgrind" 
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --test|-t:	compile and run tests"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --help|-h:	print this help"
}

if [ $# -lt 1 ]; then
	usage
	exit 0
fi

for args
do
	case "$1" in
		--test|-t)
			tests=1
			shift 1
			;;
		--doc|-d)
			doc=1
			shift 1
			;;
		--memleak|-m)
			memleak=1
			shift 1
			;;
		--debug|-g)
			debug=1
			shift 1
			;;
		--clean|-c)
			clean=1
			shift 1
			;;
		--help|-h)
			usage
			exit 0
			;;
		?*)
			echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Illegal argument $1"
			usage
			exit 0
			;;
	esac
done

if [ ${tests} -eq 1 ] || [ ${doc} -eq 1 ] || [ ${memleak} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Run script variables"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] DATASET"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Dataset directory ${DATASET_DIR}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Training set filename ${TRAIN_SET}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Training label filename ${TRAIN_LABEL}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Test set filename ${TEST_SET}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Test label filename ${TEST_LABEL}"
	echo "\n"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] EXECUTABLE"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Directory of the executable: ${EXEDIR}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Executable filename: ${EXENAME}"
	echo "\n"
fi

echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] LOGS"
echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Logfile directory: ${LOGDIRR}"

if [ ${debug} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Debug logfile name: ${DEBUGLOG}"
fi

if [ ${tests} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Compile logfile name: ${COMPLOG}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Executable logfile name: ${EXELOG}"
fi

if [ ${doc} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Documentation logfile name: ${DOCLOG}"
fi

if [ ${memleak} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Valgrind test set logfile name: ${VALGRINDTESLOG}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Valgrind test label logfile name: ${VALGRINDTELLOG}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Valgrind all input files logfile name: ${VALGRINDALLLOG}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Valgrind executable logfile name: ${EXEVALGRINDLOG}"
fi

echo "\n"

if [ ${clean} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Clean workspace"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 make clean LOG_DIR=${LOGDIR} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR})
	echo "\n"
fi

if [ ${tests} -eq 1 ] || [ ${debug} -eq 1 ] || [ ${doc} -eq 1 ] || [ ${memleak} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Create log directory"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 mkdir -p ${LOGDIR})
	echo "\n"
fi

if [ ${debug} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Makefile variables"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 make debug LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} CEXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${DEBUGLOG})
	echo "\n"
fi

if [ ${tests} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Compile sources"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 make all LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VERBOSITY=${VERBOSITY} CEXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${COMPLOG})

	echo "\n"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Run program"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] START:Test parsing test label file ${DATASET_DIR}/${TEST_LABEL}"
	(set -x; \
	 ./${EXEDIR}/${EXENAME} -tel ${DATASET_DIR}/${TEST_LABEL})
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] COMPLETED:Test parsing test label file ${DATASET_DIR}/${TEST_LABEL}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] START:Test parsing test set file ${DATASET_DIR}/${TEST_SET}"
	(set -x; \
	 ./${EXEDIR}/${EXENAME} -tes ${DATASET_DIR}/${TEST_SET})
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] COMPLETED:Test parsing test set file ${DATASET_DIR}/${TEST_SET}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] START:Test parsing test label file ${DATASET_DIR}/${TEST_LABEL}, test set file ${DATASET_DIR}/${TEST_SET}, training label file ${DATASET_DIR}/${TRAIN_LABEL}, training set file ${DATASET_DIR}/${TRAIN_SET}"
	(set -x; \
	 ./${EXEDIR}/${EXENAME} -tel ${DATASET_DIR}/${TEST_LABEL} -tes ${DATASET_DIR}/${TEST_SET} -trl ${DATASET_DIR}/${TRAIN_LABEL} -trs ${DATASET_DIR}/${TRAIN_SET})
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] COMPLETED:Test parsing test label file ${DATASET_DIR}/${TEST_LABEL}, test set file ${DATASET_DIR}/${TEST_SET}, training label file ${DATASET_DIR}/${TRAIN_LABEL}, training set file ${DATASET_DIR}/${TRAIN_SET}"
	echo "\n"
fi

if [ ${doc} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Compile documetation"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 make doc LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} CEXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${DOCLOG})
	echo "\n"
fi

if [ ${memleak} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Check memory leaks"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] START:Valgrind with label input file ${DATASET_DIR}/${TEST_LABEL}"
	(set -x; \
	 make memleak LOG_DIR=${LOGDIR} LOGFILENAME=${EXEVALGRINDLOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VALGRINDLOGFILENAME=${VALGRINDTELLOG} VALGRINDEXEARGS="-tel ${DATASET_DIR}/${TEST_LABEL}")
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] COMPLETED:Valgrind with label input file ${DATASET_DIR}/${TEST_LABEL}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] START:Valgrind with test set input file ${DATASET_DIR}/${TEST_SET}"
	(set -x; \
	 make memleak LOG_DIR=${LOGDIR} LOGFILENAME=${EXEVALGRINDLOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VALGRINDLOGFILENAME=${VALGRINDTESLOG} VALGRINDEXEARGS="-tes ${DATASET_DIR}/${TEST_SET}")
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] COMPLETED:Valgrind with test set input file ${DATASET_DIR}/${TEST_SET}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] START:Valgrind with the following input files: test label file ${DATASET_DIR}/${TEST_LABEL}, test set file ${DATASET_DIR}/${TEST_SET}, training label file ${DATASET_DIR}/${TRAIN_LABEL}, training set file ${DATASET_DIR}/${TRAIN_SET}"
	(set -x; \
	 make memleak LOG_DIR=${LOGDIR} LOGFILENAME=${EXEVALGRINDLOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VALGRINDLOGFILENAME=${VALGRINDALLLOG} VALGRINDEXEARGS="-tel ${DATASET_DIR}/${TEST_LABEL} -tes ${DATASET_DIR}/${TEST_SET} -trl ${DATASET_DIR}/${TRAIN_LABEL} -trs ${DATASET_DIR}/${TRAIN_SET}")
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] COMPLETED:Valgrind with the following input files: test label file ${DATASET_DIR}/${TEST_LABEL}, test set file ${DATASET_DIR}/${TEST_SET}, training label file ${DATASET_DIR}/${TRAIN_LABEL}, training set file ${DATASET_DIR}/${TRAIN_SET}"
	echo "\n"

fi
