#!/bin/bash

FILE="$WORKDIR/simple/values.json"

jq_expect "$FILE" '$.a' '0'
jq_expect "$FILE" '$.e["e.1"]' '"a"'
jq_expect "$FILE" '$.f.g' '"de f"'