#!/bin/bash

set -e

WORKDIR="$(dirname "$0")"
JQ_EXEC="$1"

function jq_expect()
{
  CMD="$JQ_EXEC -f '$1' '$2'"
  echo "--> Execute: $CMD"
  result="$(eval "$CMD")"
  echo "$result"
  echo "<--> Expect"
  echo "$3"
  if [ "$result" != "$3" ]; then
    echo "<-- Result mismatch"
    exit 1
  else
    echo "<-- Result match"
  fi;
  echo ""
}

source "$WORKDIR/simple/run.sh"
source "$WORKDIR/dynamic/run.sh"