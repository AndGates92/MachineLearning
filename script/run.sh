#!/bin/sh

LOGDIR=log
DEBUGLOG=debug.log
COMPLOG=compile.log
DOCLOG=doc.log
CLEANLOG=clean.log

EXENAME=ml
EXEDIR=bin

DATASET_DIR=dataset/mnist
TRAIN_SET=train-images-idx3-ubyte
TRAIN_LABEL=train-label-idx1-ubyte
TEST_SET=t10k-images-idx3-ubyte
TEST_LABEL=t10k-label-idx1-ubyte

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

echo "\n========================================================================="
echo "Clean workspace"
echo "========================================================================="
(set -x; \
 make clean LOG_DIR=${LOGDIR} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} > ${LOGDIR}/${CLEANLOG})

echo "\n========================================================================="
echo "Create log directory"
echo "========================================================================="
(set -x; \
 mkdir -p ${LOGDIR})

echo "\n========================================================================="
echo "Makefile variables"
echo "========================================================================="
(set -x; \
 make debug LOG_DIR=${LOGDIR} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} > ${LOGDIR}/${DEBUGLOG})

echo "\n========================================================================="
echo "Compile sources"
echo "========================================================================="
(set -x; \
 make all LOG_DIR=${LOGDIR} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} > ${LOGDIR}/${COMPLOG})

echo "\n========================================================================="
echo "Compile documetation"
echo "========================================================================="
(set -x; \
 make doc LOG_DIR=${LOGDIR} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} > ${LOGDIR}/${DOCLOG})

echo "\n========================================================================="
echo "Run program"
echo "========================================================================="
(set -x; \
 ./bin/ml -trs ${DATASET_DIR}/${TRAIN_SET})
