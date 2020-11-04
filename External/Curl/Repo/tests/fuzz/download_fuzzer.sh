#!/bin/bash

# If any commands fail, fail the script immediately.
set -ex

# Clone the curl-fuzzer repository to the specified directory.
git clone https://github.com/curl/curl-fuzzer $1
