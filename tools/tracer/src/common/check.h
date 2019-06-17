/*
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
*/
#pragma once

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "log.h"

namespace cxtrace {

void backtrace();

template <typename... Args>
void fail(const char *fmt, Args... args) {
    log::error(fmt, args...);
    log::error("(errno: %d) %s", errno, strerror(errno));
    if (getenv("CXTRACE_DEBUG")) backtrace();
    exit(EXIT_FAILURE);
}

template <typename... Args>
void failx(const char *fmt, Args... args) {
    log::error(fmt, args...);
    if (getenv("CXTRACE_DEBUG")) backtrace();
    exit(EXIT_FAILURE);
}

template <typename... Args>
void check(bool cond, const char *fmt, Args... args) {
    if (!cond) {
        log::error(fmt, args...);
        log::error("(errno: %d) %s", errno, strerror(errno));
        if (getenv("CXTRACE_DEBUG")) backtrace();
        exit(EXIT_FAILURE);
    }
}

template <typename... Args>
void checkx(bool cond, const char *fmt, Args... args) {
    if (!cond) {
        log::error(fmt, args...);
        if (getenv("CXTRACE_DEBUG")) backtrace();
        exit(EXIT_FAILURE);
    }
}

}
