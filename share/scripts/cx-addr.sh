#!/usr/bin/env sh
#
# ----------------------------------------------------------------------------
#
# Copyright 2019 IBM Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ----------------------------------------------------------------------------
#

set -e # Finish right after a non-zero return command
set -u # Finish right after a undefined expression is used
set -a # All following variables are exported

die() {
    echo "$@" >&2
    exit 1
}

[ $# -eq 2 ] || die "Usage: cx-addr.sh <binary> <symbol>"

bin="$1"
sym="$2"

address=0x$(readelf -s /bin/ls | grep " $sym$" | tr -s " "  | cut -d " " -f 3)

[ "$address" != "0x" ] || die "'$sym' not found in '$bin'"

echo "$address"

# vim: set tabstop=4 softtabstop=4 shiftwidth=4 expandtab
