package QuinoaKotlin_Linux.buildTypes

import QuinoaKotlin_Linux.buildParams.*
import jetbrains.buildServer.configs.kotlin.v10.*

class QuinoaKotlin_Linux_Build( bp: BuildParams ) : BuildType({

    template(QuinoaKotlin_Linux.buildTypes.QuinoaKotlin_Linux_Matrix)

    val paramToId = bp.buildtype.toExtId() +
                    bp.compiler.toExtId() +
                    bp.disable_rngsse2.toExtId() +
                    bp.disable_testu01.toExtId() +
                    bp.mathlib.toExtId() +
                    bp.stdlibcpp.toExtId();

    uuid = "74ab5531-8668-437b-b05c-184ef0d71f72-$paramToId"
    extId = "QuinoaKotlin_Linux_Build-$paramToId"
    name = "Build"
    description = "Build: ${bp.buildtype}, ${bp.compiler},
                   ${bp.disable_rngsse2}, ${bp.disable_testu01}, ${bp.mathlib},
                   ${bp.stdlibcpp}"

    params {
        param("buildtype", bp.buildtype)
        param("compiler", b.compiler)
        param("disable_rngsse2", bp.disable_rngsse2)
        param("disable_testu01", bp.disable_testu01)
        param("mathlib", bp.mathlib)
        param("stdlibcpp", bp.stdlibcpp)
    }
})
