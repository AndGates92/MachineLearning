#!/bin/sh

# Shell script settings
memleak=0
tests=0
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

if [$# -lt 1]; then
	usage
fi

for args
do
	case "$1" in
		--test|-t)
			tests=1
			shift 1
			;;
		--doc|-d)
			tests=1
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
		--help|-h)
			usage
			exit 0
			;;
		?*)
			echo "Illegal argument $1"
			usage
			exit 0
			;;
	esac
done

echo "Run script variables"
echo "\n========================================================================="
echo "DATASET"
echo "========================================================================="
echo "--> Dataset directory ${DATASET_DIR}"
echo "--> Training set filename ${TRAIN_SET}"
echo "--> Training label filename ${TRAIN_LABEL}"
echo "--> Test set filename ${TEST_SET}"
echo "--> Test label filename ${TEST_LABEL}"
echo "\n========================================================================="
echo "EXECUTABLE"
echo "========================================================================="
echo "--> Directory of the executable: ${EXEDIR}"
echo "--> Executable filename: ${EXENAME}"
echo "\n========================================================================="
echo "LOGS"
echo "========================================================================="
echo "--> Logfile directory: ${LOGDIRR}"
echo "--> Debug logfile name: ${DEBUGLOG}"
if [ ${tests} -eq 1 ]; then
	echo "--> Compile logfile name: ${COMPLOG}"
	echo "--> Executable logfile name: ${EXELOG}"
fi
if [ ${doc} -eq 1 ]; then
	echo "--> Documentation logfile name: ${DOCLOG}"
fi
if [ ${memleak} -eq 1 ]; then
	echo "--> Valgrind test set logfile name: ${VALGRINDTESLOG}"
	echo "--> Valgrind test label logfile name: ${VALGRINDTELLOG}"
	echo "--> Valgrind all input files logfile name: ${VALGRINDALLLOG}"
	echo "--> Valgrind executable logfile name: ${EXEVALGRINDLOG}"
fi

echo "\n========================================================================="
echo "Clean workspace"
echo "========================================================================="
(set -x; \
 make clean LOG_DIR=${LOGDIR} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR})

echo "\n========================================================================="
echo "Create log directory"
echo "========================================================================="
(set -x; \
 mkdir -p ${LOGDIR})

if [ ${debug} -eq 1]; then
	echo "\n========================================================================="
	echo "Makefile variables"
	echo "========================================================================="
	(set -x; \
	 make debug LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} EXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${DEBUGLOG})
fi

if [ ${tests} -eq 1 ]; then
	echo "\n========================================================================="
	echo "Compile sources"
	echo "========================================================================="
	(set -x; \
	 make all LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VERBOSITY=${VERBOSITY} EXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${COMPLOG})

	echo "\n========================================================================="
	echo "Run program"
	echo "========================================================================="
	echo "START:Test parsing test label file ${DATASET_DIR}/${TEST_LABEL}"
	(set -x; \
	 ./bin/ml -tel ${DATASET_DIR}/${TEST_LABEL})
	echo "COMPLETED:Test parsing test label file ${DATASET_DIR}/${TEST_LABEL}"
	echo "START:Test parsing test set file ${DATASET_DIR}/${TEST_SET}"
	(set -x; \
	 ./bin/ml -tes ${DATASET_DIR}/${TEST_SET})
	echo "COMPLETED:Test parsing test set file ${DATASET_DIR}/${TEST_SET}"
	echo "START:Test parsing test label file ${DATASET_DIR}/${TEST_LABEL}, test set file ${DATASET_DIR}/${TEST_SET}, training label file ${DATASET_DIR}/${TRAIN_LABEL}, training set file ${DATASET_DIR}/${TRAIN_SET}"
	(set -x; \
	 ./bin/ml -tel ${DATASET_DIR}/${TEST_LABEL} -tes ${DATASET_DIR}/${TEST_SET} -trl ${DATASET_DIR}/${TRAIN_LABEL} -trs ${DATASET_DIR}/${TRAIN_SET})
	echo "COMPLETED:Test parsing test label file ${DATASET_DIR}/${TEST_LABEL}, test set file ${DATASET_DIR}/${TEST_SET}, training label file ${DATASET_DIR}/${TRAIN_LABEL}, training set file ${DATASET_DIR}/${TRAIN_SET}"
fi

if [ ${doc} -eq 1 ]; then
	echo "\n========================================================================="
	echo "Compile documetation"
	echo "========================================================================="
	(set -x; \
	 make doc LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} EXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${DOCLOG})
fi

if [ ${memleak} -eq 1 ]; then
	echo "\n========================================================================="
	echo "Check memory leaks"
	echo "========================================================================="
	echo "START:Valgrind with label input file ${DATASET_DIR}/${TEST_LABEL}"
	(set -x; \
	 make memleak LOG_DIR=${LOGDIR} LOGFILENAME=${EXEVALGRINDLOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VALGRINDLOGFILENAME=${VALGRINDTELLOG} VALGRINDEXEARGS="-tel ${DATASET_DIR}/${TEST_LABEL}")
	echo "COMPLETED:Valgrind with label input file ${DATASET_DIR}/${TEST_LABEL}"
	echo "START:Valgrind with test set input file ${DATASET_DIR}/${TEST_SET}"
	(set -x; \
	 make memleak LOG_DIR=${LOGDIR} LOGFILENAME=${EXEVALGRINDLOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VALGRINDLOGFILENAME=${VALGRINDTESLOG} VALGRINDEXEARGS="-tes ${DATASET_DIR}/${TEST_SET}")
	echo "COMPLETED:Valgrind with test set input file ${DATASET_DIR}/${TEST_SET}"
	echo "START:Valgrind with the following input files: test label file ${DATASET_DIR}/${TEST_LABEL}, test set file ${DATASET_DIR}/${TEST_SET}, training label file ${DATASET_DIR}/${TRAIN_LABEL}, training set file ${DATASET_DIR}/${TRAIN_SET}"
	(set -x; \
	 make memleak LOG_DIR=${LOGDIR} LOGFILENAME=${EXEVALGRINDLOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VALGRINDLOGFILENAME=${VALGRINDALLLOG} VALGRINDEXEARGS="-tel ${DATASET_DIR}/${TEST_LABEL} -tes ${DATASET_DIR}/${TEST_SET} -trl ${DATASET_DIR}/${TRAIN_LABEL} -trs ${DATASET_DIR}/${TRAIN_SET}")
	echo "COMPLETED:Valgrind with the following input files: test label file ${DATASET_DIR}/${TEST_LABEL}, test set file ${DATASET_DIR}/${TEST_SET}, training label file ${DATASET_DIR}/${TRAIN_LABEL}, training set file ${DATASET_DIR}/${TRAIN_SET}"

fi

usage () {
	echo " - Usage:"
	echo " - >$0 <options>"
	echo ""
	echo "      --doc|-d:		generate documentation"
	echo "      --debug|-g:		dump makefile flags to ${LOGDIR}/${DEBUGLOG}"
	echo "      --memleak|-m:	compile and check memory leaks using valgrind" 
	echo "      --test|-t:		compile and run tests"
	echo "      --help|-h:		print this help"
}
