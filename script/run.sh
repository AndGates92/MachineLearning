#!/bin/sh

EXENAME=ml
EXEDIR=bin

LOGDIR=log
DEBUGLOG=debug.log
COMPLOG=compile.log
DOCLOG=doc.log
CLEANLOG=clean.log
VALGRINDLOG=valgrind.log
EXEVALGRINDLOG=${EXENAME}_valgrind.log

DATASET_DIR=dataset/mnist
TRAIN_SET=train-images-idx3-ubyte
TRAIN_LABEL=train-labels-idx1-ubyte
TEST_SET=t10k-images-idx3-ubyte
TEST_LABEL=t10k-labels-idx1-ubyte

VERBOSITY=LOW

CEXTRAFLAGS=-DENABLE_ASSERTIONS

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
echo "--> Compile logfile name: ${COMPLOG}"
echo "--> Documentation logfile name: ${DOCLOG}"
echo "--> Clean logfile name: ${CLEANLOG}"
echo "--> Valgrind logfile name: ${VALGRINDLOG}"
echo "--> Valgrind executable logfile name: ${EXEVALGRINDLOG}"

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

echo "\n========================================================================="
echo "Makefile variables"
echo "========================================================================="
(set -x; \
 make debug LOG_DIR=${LOGDIR} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} EXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${DEBUGLOG})

echo "\n========================================================================="
echo "Compile sources"
echo "========================================================================="
(set -x; \
 make all LOG_DIR=${LOGDIR} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VERBOSITY=${VERBOSITY} EXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${COMPLOG})

echo "\n========================================================================="
echo "Compile documetation"
echo "========================================================================="
(set -x; \
 make doc LOG_DIR=${LOGDIR} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} EXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${DOCLOG})

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

echo "\n========================================================================="
echo "Run valgrind"
echo "========================================================================="
(set -x; \
 make valgrind LOG_DIR=${LOGDIR} LOGFILENAME=${EXEVALGRINDLOG} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VALGRINDLOGFILENAME=${VALGRINDLOG} VALGRINDEXEARGS="-tes ${DATASET_DIR}/${TEST_SET} -trl ${DATASET_DIR}/${TRAIN_LABEL} -trs ${DATASET_DIR}/${TRAIN_SET}")
