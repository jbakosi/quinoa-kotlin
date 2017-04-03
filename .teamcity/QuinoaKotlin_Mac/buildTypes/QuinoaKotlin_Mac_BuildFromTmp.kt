package QuinoaKotlin_Mac.buildTypes

import jetbrains.buildServer.configs.kotlin.v10.*

object QuinoaKotlin_Mac_BuildFromTmp : BuildType({
    template(QuinoaKotlin_Mac.buildTypes.QuinoaKotlin_Mac_Matrix)
    uuid = "c70a908a-3451-47dc-96e9-da6a8f48637e"
    extId = "QuinoaKotlin_Mac_BuildFromTmp"
    name = "BuildFromTmp"
    description = "Example build from Mac Template"

    params {
        param("buildtype", "Debug")
        param("compiler", "clang")
    }
})
