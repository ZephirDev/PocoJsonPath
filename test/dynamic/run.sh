#!/bin/bash

FILE="$WORKDIR/dynamic/values.json"

jq_expect "$FILE" '$[?((@.key >= 1) && (@.key <= 3))]' ''