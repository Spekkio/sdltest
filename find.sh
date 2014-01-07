#!/bin/bash
echo $(find src/ -regex "^.*\.c$") $(find src/ -regex "^.*\.h$")
