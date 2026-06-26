pipeline {
    agent any

    options {
        timestamps()
    }

    stages {
        stage('Setup Build Environment') {
            steps {
                sh '''#!/bin/sh
set -e

if command -v make >/dev/null 2>&1 && command -v g++ >/dev/null 2>&1; then
    echo "Build tools already installed"
else
    echo "Installing build tools on Linux agent..."
    if command -v apt-get >/dev/null 2>&1; then
        if command -v sudo >/dev/null 2>&1; then
            sudo apt-get update
            sudo DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential libgtest-dev
        elif [ "$(id -u)" -eq 0 ]; then
            apt-get update
            DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential libgtest-dev
        else
            echo "ERROR: apt-get is available but Jenkins user has no sudo/root access."
            exit 1
        fi
    elif command -v yum >/dev/null 2>&1; then
        if command -v sudo >/dev/null 2>&1; then
            sudo yum install -y gcc-c++ make gtest-devel
        elif [ "$(id -u)" -eq 0 ]; then
            yum install -y gcc-c++ make gtest-devel
        else
            echo "ERROR: yum is available but Jenkins user has no sudo/root access."
            exit 1
        fi
    elif command -v apk >/dev/null 2>&1; then
        if command -v sudo >/dev/null 2>&1; then
            sudo apk add --no-cache build-base gtest-dev
        elif [ "$(id -u)" -eq 0 ]; then
            apk add --no-cache build-base gtest-dev
        else
            echo "ERROR: apk is available but Jenkins user has no sudo/root access."
            exit 1
        fi
    else
        echo "ERROR: No supported package manager found to install make/g++."
        exit 1
    fi
fi

echo "Toolchain versions:"
make --version | head -n 1
g++ --version | head -n 1
'''
            }
        }

        stage('Build Application') {
            steps {
                sh 'make clean'
                sh 'make'
            }
        }

        stage('Build Unit Tests') {
            steps {
                sh 'make -f Makefile.UnitTest clean'
                sh 'make -f Makefile.UnitTest'
            }
        }

        stage('Run Unit Tests') {
            steps {
                sh 'chmod +x runUT.sh || true'
                sh './runUT.sh'
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
