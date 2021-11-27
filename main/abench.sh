help(){
    echo "Help"
    echo "./bench TEST NUBERoftime"
    echo ' les diférant test disponible
    - readb
    - readbCOPY
    - serialized
    - deserialisedb
    - readsmaldb
    - deserialisesmalldb'
}

lunch(){
    \time -f "%E;%U;%S;%P" ./bench $1
}

moyenne(){
    echo "$1"
    NUBMER=1
    if [ -n "$2" ]; then
        NUBMER=$2
    fi

    for nbtest in $(seq $NUBMER);
    do
        echo "lunch number $nbtest:"
        lunch $1
    done
}

if [[ ! $# -eq 2 ]] ; then
    echo "./bench BENCHTYPE NUBLOOP"
fi
# reply=$(seq 10)
# _describe './abench.sh' "('cmd1:description1' 'cmd2:description2')"

moyenne $1 $2