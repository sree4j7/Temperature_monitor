pipeline {
    agent any

    options {
        timestamps()
    }

    environment {
        BUILD_MODE = 'host'
        BUILD_IMAGE = 'gcc:13'
        GTEST_DIR = '.ci/googletest'
        PORTABLE_TC_DIR = '.ci/toolchain'
        CXX_BIN = 'g++'
        CXX_EXTRA_FLAGS = ''
        CXX_LINK_FLAGS = ''
    }

    stages {
        stage('Setup Build Environment') {
            steps {
                script {
                    def resolvedBuildMode = 'host_make'
                    def resolvedCxx = 'g++'
                    def resolvedExtraFlags = ''
                    def resolvedLinkFlags = ''

                    def compilerBin = sh(script: '''#!/bin/sh
if command -v g++ >/dev/null 2>&1; then
    echo g++
elif command -v c++ >/dev/null 2>&1; then
    echo c++
elif command -v clang++ >/dev/null 2>&1; then
    echo clang++
elif command -v gcc >/dev/null 2>&1; then
    echo gcc
else
    echo none
fi
''', returnStdout: true).trim()

                    def hostMakeReady = (compilerBin != 'none' && compilerBin != 'gcc' && sh(script: "command -v make >/dev/null 2>&1 && command -v ${compilerBin} >/dev/null 2>&1", returnStatus: true) == 0)
                    def hostGppReady = (compilerBin != 'none')

                    if (hostMakeReady) {
                        resolvedCxx = compilerBin
                        resolvedExtraFlags = ''
                        resolvedLinkFlags = ''
                        resolvedBuildMode = 'host_make'
                        sh 'make --version | head -n 1'
                        sh "${resolvedCxx} --version | head -n 1"
                    } else if (hostGppReady) {
                        resolvedCxx = compilerBin
                        resolvedExtraFlags = ''
                        resolvedLinkFlags = (compilerBin == 'gcc') ? '-lstdc++' : ''
                        resolvedBuildMode = 'host_gpp'
                        sh "${resolvedCxx} --version | head -n 1"
                    } else {
                        def installed = sh(script: '''#!/bin/sh
set -e

SUDO_OK=0
if command -v sudo >/dev/null 2>&1; then
    if sudo -n true >/dev/null 2>&1; then
        SUDO_OK=1
    fi
fi

if command -v apt-get >/dev/null 2>&1; then
    if [ "$SUDO_OK" -eq 1 ]; then
        sudo apt-get update
        sudo DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential libgtest-dev
    elif [ "$(id -u)" -eq 0 ]; then
        apt-get update
        DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential libgtest-dev
    else
        exit 2
    fi
elif command -v yum >/dev/null 2>&1; then
    if [ "$SUDO_OK" -eq 1 ]; then
        sudo yum install -y gcc-c++ make gtest-devel
    elif [ "$(id -u)" -eq 0 ]; then
        yum install -y gcc-c++ make gtest-devel
    else
        exit 2
    fi
elif command -v apk >/dev/null 2>&1; then
    if [ "$SUDO_OK" -eq 1 ]; then
        sudo apk add --no-cache build-base gtest-dev
    elif [ "$(id -u)" -eq 0 ]; then
        apk add --no-cache build-base gtest-dev
    else
        exit 2
    fi
else
    exit 3
fi

command -v make >/dev/null 2>&1 && command -v g++ >/dev/null 2>&1
''', returnStatus: true)

                        if (installed == 0) {
                            resolvedCxx = 'g++'
                            resolvedExtraFlags = ''
                            resolvedLinkFlags = ''
                            resolvedBuildMode = 'host_make'
                            sh 'make --version | head -n 1; g++ --version | head -n 1'
                        } else {
                            def dockerReady = (sh(script: 'command -v docker >/dev/null 2>&1 && docker info >/dev/null 2>&1', returnStatus: true) == 0)
                            if (dockerReady) {
                                resolvedBuildMode = 'docker'
                                sh 'docker pull ${BUILD_IMAGE}'
                                echo 'Host toolchain unavailable and no install privileges; using Docker build mode.'
                            } else {
                                def portableReady = sh(script: '''#!/bin/sh
set -e

TC_DIR="${PORTABLE_TC_DIR}"
ARCHIVE=".ci/x86_64-linux-musl-native.tgz"
URL="https://musl.cc/x86_64-linux-musl-native.tgz"

mkdir -p .ci

if [ -x "${TC_DIR}/bin/g++" ]; then
    exit 0
fi

if command -v curl >/dev/null 2>&1; then
    curl -L --fail -o "${ARCHIVE}" "${URL}"
elif command -v wget >/dev/null 2>&1; then
    wget -O "${ARCHIVE}" "${URL}"
elif command -v python3 >/dev/null 2>&1; then
    python3 - <<'PY'
import urllib.request
urllib.request.urlretrieve('https://musl.cc/x86_64-linux-musl-native.tgz', '.ci/x86_64-linux-musl-native.tgz')
PY
else
    exit 4
fi

rm -rf "${TC_DIR}" .ci/x86_64-linux-musl-native
tar -xzf "${ARCHIVE}" -C .ci
mv .ci/x86_64-linux-musl-native "${TC_DIR}"
test -x "${TC_DIR}/bin/g++"
''', returnStatus: true)

                                if (portableReady == 0) {
                                    def ws = pwd()
                                    def portableCxx = "${ws}/${env.PORTABLE_TC_DIR}/bin/g++"
                                    resolvedBuildMode = 'portable_gpp'
                                    resolvedCxx = portableCxx
                                    resolvedExtraFlags = '-fno-pie'
                                    resolvedLinkFlags = '-static -no-pie'
                                    sh "\"${portableCxx}\" --version | head -n 1"
                                    echo 'Using portable user-space C++ toolchain.'
                                } else {
                                    error('No usable C++ toolchain found. Jenkins user cannot install packages, Docker is unavailable, and portable toolchain bootstrap failed. Preinstall make/g++/gtest on the agent, or enable Docker/sudo/network access for Jenkins.')
                                }
                            }
                        }
                    }

                    env.BUILD_MODE = resolvedBuildMode
                    env.CXX_BIN = resolvedCxx
                    env.CXX_EXTRA_FLAGS = resolvedExtraFlags
                    env.CXX_LINK_FLAGS = resolvedLinkFlags

                    sh 'mkdir -p .ci'
                    writeFile file: '.ci/jenkins_build_mode', text: "${resolvedBuildMode}\n"
                    writeFile file: '.ci/jenkins_cxx_bin', text: "${resolvedCxx}\n"
                    writeFile file: '.ci/jenkins_extra_flags', text: "${resolvedExtraFlags}\n"
                    writeFile file: '.ci/jenkins_link_flags', text: "${resolvedLinkFlags}\n"
                }
            }
        }

        stage('Build Application') {
            steps {
                script {
                    def buildMode = fileExists('.ci/jenkins_build_mode') ? readFile('.ci/jenkins_build_mode').trim() : env.BUILD_MODE
                    def cxx = fileExists('.ci/jenkins_cxx_bin') ? readFile('.ci/jenkins_cxx_bin').trim() : (env.CXX_BIN?.trim() ? env.CXX_BIN.trim() : 'g++')
                    def extraFlags = fileExists('.ci/jenkins_extra_flags') ? readFile('.ci/jenkins_extra_flags').trim() : (env.CXX_EXTRA_FLAGS?.trim() ? env.CXX_EXTRA_FLAGS.trim() : '')
                    def linkFlags = fileExists('.ci/jenkins_link_flags') ? readFile('.ci/jenkins_link_flags').trim() : (env.CXX_LINK_FLAGS?.trim() ? env.CXX_LINK_FLAGS.trim() : '')
                    echo "BuildApplication mode=${buildMode}, cxx=${cxx}"

                    if (buildMode == 'docker') {
                        sh '''docker run --rm \
  -v "$PWD":/workspace \
  -w /workspace \
  ${BUILD_IMAGE} \
  bash -lc "apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y make libgtest-dev && make clean && make"'''
                    } else if (buildMode == 'host_make') {
                        sh 'make clean'
                        sh 'make'
                    } else {
                        sh """#!/bin/sh
set -e
mkdir -p obj
"${cxx}" -g -std=c++17 -Wall -Wextra -W -O0 ${extraFlags} -I/usr/include -c main.cpp -o obj/main.o
"${cxx}" -g -std=c++17 -Wall -Wextra -W -O0 ${extraFlags} -I/usr/include -c ac_monitor.cpp -o obj/ac_monitor.o
"${cxx}" -g -std=c++17 -Wall -Wextra -W -O0 ${extraFlags} -I/usr/include -c temperature_monitor.cpp -o obj/temperature_monitor.o
"${cxx}" -g -std=c++17 -Wall -Wextra -W -O0 ${extraFlags} -I/usr/include -c temperature_sensor.cpp -o obj/temperature_sensor.o
"${cxx}" -g -std=c++17 -Wall -Wextra -W -O0 ${extraFlags} -I/usr/include -c main_controller.cpp -o obj/main_controller.o
"${cxx}" -I/usr/include -L/usr/lib -o Binary obj/main.o obj/ac_monitor.o obj/temperature_monitor.o obj/temperature_sensor.o obj/main_controller.o -pthread ${linkFlags}
"""
                    }
                }
            }
        }

        stage('Build Unit Tests') {
            steps {
                script {
                    def buildMode = fileExists('.ci/jenkins_build_mode') ? readFile('.ci/jenkins_build_mode').trim() : env.BUILD_MODE
                    def cxx = fileExists('.ci/jenkins_cxx_bin') ? readFile('.ci/jenkins_cxx_bin').trim() : (env.CXX_BIN?.trim() ? env.CXX_BIN.trim() : 'g++')
                    def extraFlags = fileExists('.ci/jenkins_extra_flags') ? readFile('.ci/jenkins_extra_flags').trim() : (env.CXX_EXTRA_FLAGS?.trim() ? env.CXX_EXTRA_FLAGS.trim() : '')
                    def linkFlags = fileExists('.ci/jenkins_link_flags') ? readFile('.ci/jenkins_link_flags').trim() : (env.CXX_LINK_FLAGS?.trim() ? env.CXX_LINK_FLAGS.trim() : '')
                    echo "BuildUnitTests mode=${buildMode}, cxx=${cxx}"

                    if (buildMode == 'docker') {
                        sh '''docker run --rm \
  -v "$PWD":/workspace \
  -w /workspace \
  ${BUILD_IMAGE} \
  bash -lc "apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y make libgtest-dev && make -f Makefile.UnitTest clean && make -f Makefile.UnitTest"'''
                    } else if (buildMode == 'host_make') {
                        sh 'make -f Makefile.UnitTest clean'
                        sh 'make -f Makefile.UnitTest'
                    } else {
                        def gtestDir = env.GTEST_DIR?.trim() ? env.GTEST_DIR.trim() : '.ci/googletest'
                        sh """#!/bin/sh
set -e

mkdir -p objunit
mkdir -p .ci

if [ ! -d "${gtestDir}" ]; then
    if command -v git >/dev/null 2>&1; then
        git clone --depth 1 https://github.com/google/googletest.git "${gtestDir}"
    else
        echo "ERROR: git is required to fetch GoogleTest source in host_gpp mode."
        exit 1
    fi
fi

GTEST_INC="-I${gtestDir}/googletest/include -I${gtestDir}/googletest"
COMMON_FLAGS="-g -std=c++17 -Wall -Wextra -W -O0 ${extraFlags} -I/usr/include \$GTEST_INC"

"${cxx}" \$COMMON_FLAGS -c test_main.cpp -o objunit/test_main.o
"${cxx}" \$COMMON_FLAGS -c main_controller.cpp -o objunit/main_controller.o
"${cxx}" \$COMMON_FLAGS -c main_controller_test.cpp -o objunit/main_controller_test.o
"${cxx}" \$COMMON_FLAGS -c temperature_monitor.cpp -o objunit/temperature_monitor.o
"${cxx}" \$COMMON_FLAGS -c temp_monitor_test.cpp -o objunit/temp_monitor_test.o
"${cxx}" \$COMMON_FLAGS -c temperature_sensor.cpp -o objunit/temperature_sensor.o
"${cxx}" \$COMMON_FLAGS -c temp_sensor_test.cpp -o objunit/temp_sensor_test.o
"${cxx}" \$COMMON_FLAGS -c ac_monitor.cpp -o objunit/ac_monitor.o
"${cxx}" \$COMMON_FLAGS -c ac_monitor_test.cpp -o objunit/ac_monitor_test.o
"${cxx}" \$COMMON_FLAGS -c ${gtestDir}/googletest/src/gtest-all.cc -o objunit/gtest-all.o

"${cxx}" -I/usr/include \$GTEST_INC -L/usr/lib -o UT.Binary \
  objunit/test_main.o \
  objunit/main_controller.o \
  objunit/main_controller_test.o \
  objunit/temperature_monitor.o \
  objunit/temp_monitor_test.o \
  objunit/temperature_sensor.o \
  objunit/temp_sensor_test.o \
  objunit/ac_monitor.o \
  objunit/ac_monitor_test.o \
  objunit/gtest-all.o \
    -pthread ${linkFlags}
"""
                    }
                }
            }
        }

        stage('Run Unit Tests') {
            steps {
                script {
                    def buildMode = fileExists('.ci/jenkins_build_mode') ? readFile('.ci/jenkins_build_mode').trim() : env.BUILD_MODE
                    if (buildMode == 'docker') {
                        sh '''docker run --rm \
  -v "$PWD":/workspace \
  -w /workspace \
  ${BUILD_IMAGE} \
  bash -lc "chmod +x runUT.sh || true; ./runUT.sh"'''
                    } else if (buildMode == 'portable_gpp') {
                        sh '''#!/bin/sh
set -e

chmod +x runUT.sh || true

if [ ! -f ./UT.Binary ]; then
    echo "ERROR: UT.Binary was not generated by Build Unit Tests stage."
    exit 1
fi

export GTEST_OUTPUT="xml:${PWD}/UTReport.xml"

set +e
./UT.Binary
rc=$?
set -e

if [ "$rc" -eq 126 ] || [ "$rc" -eq 127 ]; then
    echo "Direct execution failed with code $rc, retrying from /tmp..."
    TMP_BIN="/tmp/UT.Binary.$$.bin"
    cp ./UT.Binary "$TMP_BIN"
    chmod +x "$TMP_BIN"

    set +e
    "$TMP_BIN"
    rc=$?
    set -e

    if [ "$rc" -ne 0 ] && [ -x "./.ci/toolchain/lib/ld-musl-x86_64.so.1" ]; then
        set +e
        ./.ci/toolchain/lib/ld-musl-x86_64.so.1 "$TMP_BIN"
        rc=$?
        set -e
    fi

    if [ "$rc" -ne 0 ] && [ -x "./.ci/toolchain/x86_64-linux-musl/lib/ld-musl-x86_64.so.1" ]; then
        set +e
        ./.ci/toolchain/x86_64-linux-musl/lib/ld-musl-x86_64.so.1 "$TMP_BIN"
        rc=$?
        set -e
    fi

    rm -f "$TMP_BIN" || true
fi

if [ "$rc" -ne 0 ]; then
    if [ "$rc" -eq 126 ] || [ "$rc" -eq 127 ]; then
        echo "ERROR: UT.Binary exists but could not be executed (exit code $rc)."
        echo "Host architecture:"
        uname -m || true
        echo "Binary metadata:"
        file ./UT.Binary || true
    else
        echo "Unit tests failed with exit code $rc."
    fi
    exit $rc
fi
'''
                    } else {
                        sh 'chmod +x runUT.sh || true'
                        sh './runUT.sh'
                    }
                }
            }
        }
    }

    post {
        always {
            junit allowEmptyResults: true, testResults: 'UTReport.xml'
            archiveArtifacts artifacts: 'Binary,UT.Binary,UTReport.xml,UTestReport.html', allowEmptyArchive: true
        }
    }
}
