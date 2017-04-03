package QuinoaKotlin_Linux.buildTypes

import jetbrains.buildServer.configs.kotlin.v10.*

object QuinoaKotlin_Linux_BuildFromTmp : BuildType({
    template(QuinoaKotlin_Linux.buildTypes.QuinoaKotlin_Linux_Matrix)
    uuid = "74ab5531-8668-437b-b05c-184ef0d71f72"
    extId = "QuinoaKotlin_Linux_BuildFromTmp"
    name = "BuildFromTmp"
    description = "Example build description"

    params {
        param("buildtype", "Debug")
        param("compiler", "clang")
        param("disable_rngsse2", "no")
        param("disable_testu01", "no")
        param("mathlib", "mkl")
        param("stdlibcpp", "libc++")
    }
})
