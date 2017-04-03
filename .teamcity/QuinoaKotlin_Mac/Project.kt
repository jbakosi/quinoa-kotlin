package QuinoaKotlin_Mac

import QuinoaKotlin_Mac.buildTypes.*
import jetbrains.buildServer.configs.kotlin.v10.*
import jetbrains.buildServer.configs.kotlin.v10.Project

object Project : Project({
    uuid = "8cc19dec-56fe-4bfb-b42f-4e35f7e616de"
    extId = "QuinoaKotlin_Mac"
    parentId = "QuinoaKotlin"
    name = "Mac"
    description = "Mac builds"

    buildType(QuinoaKotlin_Mac_BuildFromTmp)

    template(QuinoaKotlin_Mac_Matrix)
})
