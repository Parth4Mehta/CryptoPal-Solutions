#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$REPO_ROOT"

if ! command -v g++ >/dev/null 2>&1; then
  echo "Error: g++ not found. Install g++ first."
  exit 1
fi

mapfile -t SET_DIRS < <(find . -maxdepth 1 -type d -name 'Set*' | sed 's#^\./##' | sort -V)
if [[ ${#SET_DIRS[@]} -eq 0 ]]; then
  echo "No set folders found (expected folders like Set1, Set2, ...)."
  exit 1
fi

echo "Available sets:"
for set_dir in "${SET_DIRS[@]}"; do
  set_num="${set_dir#Set}"
  echo "  - $set_num"
done

read -rp "Enter set number: " set_num
if [[ ! "$set_num" =~ ^[0-9]+$ ]]; then
  echo "Invalid set number."
  exit 1
fi

SET_PATH="Set${set_num}"
if [[ ! -d "$SET_PATH" ]]; then
  echo "Set '$SET_PATH' does not exist."
  exit 1
fi

mapfile -t CHAL_DIRS < <(find "$SET_PATH" -maxdepth 1 -type d -name 'Chal*' | sed "s#^$SET_PATH/##" | sort -V)
if [[ ${#CHAL_DIRS[@]} -eq 0 ]]; then
  echo "No challenge folders found in $SET_PATH (expected Chal1, Chal2, ...)."
  exit 1
fi

echo "Available challenges in $SET_PATH:"
for chal_dir in "${CHAL_DIRS[@]}"; do
  chal_num="${chal_dir#Chal}"
  echo "  - $chal_num"
done

read -rp "Enter challenge number: " chal_num
if [[ ! "$chal_num" =~ ^[0-9]+$ ]]; then
  echo "Invalid challenge number."
  exit 1
fi

CHAL_PATH="$SET_PATH/Chal${chal_num}"
SOURCE_FILE="$CHAL_PATH/main.cpp"

if [[ ! -f "$SOURCE_FILE" ]]; then
  echo "Source file not found: $SOURCE_FILE"
  exit 1
fi

BUILD_DIR=".build"
mkdir -p "$BUILD_DIR"
BINARY="$BUILD_DIR/${SET_PATH}_Chal${chal_num}"

echo "Compiling $SOURCE_FILE ..."
g++ -std=c++17 "$SOURCE_FILE" -o "$BINARY"

echo
echo "Running $BINARY ..."
echo "----------------------------------------"
"$BINARY"
echo "----------------------------------------"
