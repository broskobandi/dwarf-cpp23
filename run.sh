#!/bin/env sh

cmake -GNinja .. &&
ninja &&
./dwarf
