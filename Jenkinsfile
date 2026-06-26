pipeline {
    agent any

    options {
        timestamps()
    }

    environment {
        BUILD_MODE = 'host'
        BUILD_IMAGE = 'gcc:13'
    }

    stages {
        stage('Setup Build Environment') {
            steps {
                script {
                    def hostReady = (sh(script: 'command -v make >/dev/null 2>&1 && command -v g++ >/dev/null 2>&1', returnStatus: true) == 0)
                    if (hostReady) {
                        env.BUILD_MODE = 'host'
                        sh 'make --version | head -n 1; g++ --version | head -n 1'
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
                            env.BUILD_MODE = 'host'
                            sh 'make --version | head -n 1; g++ --version | head -n 1'
                        } else {
                            def dockerReady = (sh(script: 'command -v docker >/dev/null 2>&1 && docker info >/dev/null 2>&1', returnStatus: true) == 0)
                            if (dockerReady) {
                                env.BUILD_MODE = 'docker'
                                sh 'docker pull ${BUILD_IMAGE}'
                                echo 'Host toolchain unavailable and no install privileges; using Docker build mode.'
                            } else {
                                error('No usable C++ toolchain found. Jenkins user cannot install packages and Docker is unavailable. Preinstall make/g++/gtest on the agent, or enable Docker access for Jenkins.')
                            }
                        }
                    }
                }
            }
        }

        stage('Build Application') {
            steps {
                script {
                    if (env.BUILD_MODE == 'docker') {
                        sh '''docker run --rm \
  -v "$PWD":/workspace \
  -w /workspace \
  ${BUILD_IMAGE} \
  bash -lc "apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y make libgtest-dev && make clean && make"'''
                    } else {
                        sh 'make clean'
                        sh 'make'
                    }
                }
            }
        }

        stage('Build Unit Tests') {
            steps {
                script {
                    if (env.BUILD_MODE == 'docker') {
                        sh '''docker run --rm \
  -v "$PWD":/workspace \
  -w /workspace \
  ${BUILD_IMAGE} \
  bash -lc "apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y make libgtest-dev && make -f Makefile.UnitTest clean && make -f Makefile.UnitTest"'''
                    } else {
                        sh 'make -f Makefile.UnitTest clean'
                        sh 'make -f Makefile.UnitTest'
                    }
                }
            }
        }

        stage('Run Unit Tests') {
            steps {
                script {
                    if (env.BUILD_MODE == 'docker') {
                        sh '''docker run --rm \
  -v "$PWD":/workspace \
  -w /workspace \
  ${BUILD_IMAGE} \
  bash -lc "chmod +x runUT.sh || true; ./runUT.sh"'''
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
