#!/bin/zsh
# ajjouter des checksum au sortie standar pour etre sur que les data sont integre
# diff DATA/diff DATA/SerializedStruc.data  verrifie si la sortie decerialiser a partire de la base auriginal est la meme que la sortie serialiser d'elle meme
help(){
    echo "Help"
    echo "./bench TEST NUBERoftime"
    echo ' les diférant test disponible
    - readb
    - readbCOPY
    - readsmaldb
    - serialized
    - deserialisedb
    - deserialisesmalldb'
}


moyenne(){
    echo "$1"
    NUBMER=1
    if [ -n "$2" ]; then
        NUBMER=$2
    fi
    
    for nbtest in $(seq $NUBMER);
    do
        time ./bench $1
    done
    echo temps total:
}

if [[  $# -eq 0 ]] ; then
    echo "./bench BENCHTYPE NUBLOOP"
    help
    exit
fi
# reply=$(seq 10)
# _describe './abench.sh' "('cmd1:description1' 'cmd2:description2')"

TIMEFMT=$'%E'
time moyenne $1 $2