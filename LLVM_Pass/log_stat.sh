#!/bin/bash
file=$1
n=$2

awk -v n=$n '
{
    for (i=1; i<n; i++) lines[i] = lines[i+1]
    lines[n] = $0
    
    if (NR >= n) {
        ngram = lines[1]
        for (i=2; i<=n; i++) ngram = ngram " | " lines[i]
        print ngram
    }
}' "$file" | sort | uniq -c | sort -nr