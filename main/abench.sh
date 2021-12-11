#!/bin/zsh
# ajjouter des checksum au sortie standar pour etre sur que les data sont integre
# diff DATA/diff DATA/SerializedStruc.data  verrifie si la sortie decerialiser a partire de la base auriginal est la meme que la sortie serialiser d'elle meme
help(){
    echo "Help"
    echo "  calcule le temps moyen d'une fonction en prenant le temps cpu est temps user"
    echo "./bench TEST NUBERoftime"
    echo ' les diférant test disponible
    - readb
    - readsmaldb
    - serialized
    - deserialisedb
    - deserialisesmalldb
    - swap
    - swaprint
    - ALL'
}


moyenne(){
    rm -f /tmp/tmpIwI
    echo "$1"
    NUBMER=1
    if [ -n "$2" ]; then
        NUBMER=$2
    fi
    
    for nbtest in $(seq $NUBMER);
    do
        /bin/time -f "%S+%U" ./bench $1 2>&1 |bc|tee -a /tmp/tmpIwI
    done
    echo temps moyen:
    OP=$(echo -n \( ; tr '\n' '+' < /tmp/tmpIwI ; echo 0\)/${NUBMER})
    grep -E ".*\.[0-9]{2}" -o <(echo $(($OP)))
    # cat /dev/stderr
}

if [[  $# -eq 0 ]] ; then
    echo "./bench BENCHTYPE NUBLOOP"
    help
    exit
fi


# reply=$(seq 10)
# _describe './abench.sh' "('cmd1:description1' 'cmd2:description2')"

TIMEFMT=$'%E'
moyenne $1 $2