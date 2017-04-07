package QuinoaKotlin_Mac.buildTypes

import jetbrains.buildServer.configs.kotlin.v10.*
import jetbrains.buildServer.configs.kotlin.v10.buildSteps.ScriptBuildStep
import jetbrains.buildServer.configs.kotlin.v10.buildSteps.ScriptBuildStep.*
import jetbrains.buildServer.configs.kotlin.v10.buildSteps.script
import jetbrains.buildServer.configs.kotlin.v10.triggers.VcsTrigger
import jetbrains.buildServer.configs.kotlin.v10.triggers.VcsTrigger.*
import jetbrains.buildServer.configs.kotlin.v10.triggers.vcs

object QuinoaKotlin_Mac_Matrix : Template({
    uuid = "bfc71567-af5a-4a29-abe4-54c2481c06bf"
    extId = "QuinoaKotlin_Mac_Matrix"
    name = "Matrix"

    vcs {
        root(QuinoaKotlin.vcsRoots.QuinoaKotlin_GitGithubComJbakosiQuinoaKotlinGitRefsHeadsMaster)

    }

    steps {
        script {
            name = "Verify commit"
            id = "RUNNER_12"
            scriptContent = """git verify-commit %build.vcs.number% 2>&1 | grep "Good signature""""
        }
        script {
            name = "Build code"
            id = "RUNNER_14"
            scriptContent = """
                [ %compiler% == clang ] && port select clang mp-clang-3.8 && port select mpi openmpi-clang38-fortran
                [ %compiler% == gnu ] && port select gcc mp-gcc5 && port select mpi openmpi-gcc5-fortran
                rm -rf build && mkdir build && cd build
                cmake -DCMAKE_CXX_COMPILER=mpicxx -DCMAKE_C_COMPILER=mpicc -DCMAKE_BUILD_TYPE=%buildtype% -DCMAKE_CXX_FLAGS=-Werror -DTPL_DIR=/Volumes/Storage/jbakosi/code/quinoa-tpl/install/%compiler%-x86_64 ../src
                #make -j%teamcity.agent.hardware.cpuCount%
            """.trimIndent()
        }
        script {
            name = "Run tests"
            id = "RUNNER_16"
            workingDir = "build"
            scriptContent = """
                #[ %compiler% == clang ] && port select clang mp-clang-3.8 && port select mpi openmpi-clang38-fortran
                #[ %compiler% == gnu ] && port select gcc mp-gcc5 && port select mpi openmpi-gcc5-fortran
                #../script/run_tests.sh
            """.trimIndent()
        }
    }

    triggers {
        vcs {
            id = "vcsTrigger"
            triggerRules = """
                +:.
                -:comment="[ci skip]":**
                -:comment="[skip ci]":**
            """.trimIndent()
            perCheckinTriggering = true
            groupCheckinsByCommitter = true
        }
    }

    requirements {
        equals("teamcity.agent.jvm.os.name", "Mac OS X", "RQ_12")
        contains("teamcity.agent.name", "euler", "RQ_13")
    }
})
