#!/bin/sh

TARGET=convert

#
# Ce placer dans le répertoire courant
#
TESTDIR="$(cd "$(dirname "$0}")" && pwd)"
cd "$TESTDIR"

#
# Conserver une trace de toutes les actions
#
LOG="test.log"
rm -f "$LOG"
touch "$LOG"

#
# Importer les fonctions communes à tous les tests
#
. ./fonctions.sh


#
# Compilation du programme.
#

annoncer "Compilation"
rm $TARGET
make $TARGET >> $LOG 2>&1 || fail
coloredEcho "OK" green

annoncer "Test Erreur 1"
$VALGRIND ./$TARGET test-0/in >> $LOG 2>&1
if [ $? -ne 1 ]; then
  fail
fi
coloredEcho "OK" green

annoncer "Test Erreur 2"
$VALGRIND ./$TARGET fichier_qui_n_existe_pas out1.txt >> $LOG 2>&1
if [ $? -ne 1 ]; then
  fail
fi
coloredEcho "OK" green


annoncer "Test 0"
$VALGRIND ./$TARGET test-0/in out1.txt >> $LOG 2>&1 || fail
diff test-0/out out1.txt >> $LOG 2>&1 || fail
coloredEcho "OK" green

exit 0
