pipeline {
    agent any

    options {
        timestamps()
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
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
