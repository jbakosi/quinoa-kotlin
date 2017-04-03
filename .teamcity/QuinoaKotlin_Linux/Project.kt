package QuinoaKotlin_Linux

import QuinoaKotlin_Linux.buildTypes.*
import QuinoaKotlin_Linux.buildParams.*
import jetbrains.buildServer.configs.kotlin.v10.*
import jetbrains.buildServer.configs.kotlin.v10.Project
import jetbrains.buildServer.configs.kotlin.v10.projectFeatures.VersionedSettings
import jetbrains.buildServer.configs.kotlin.v10.projectFeatures.VersionedSettings.*
import jetbrains.buildServer.configs.kotlin.v10.projectFeatures.versionedSettings

object Project : Project({
    uuid = "e00a2acd-1e09-4352-ab15-cf32e7838238"
    extId = "QuinoaKotlin_Linux"
    parentId = "QuinoaKotlin"
    name = "Linux"
    description = "Linux builds"

    template(QuinoaKotlin_Linux_Matrix)

    data class BuildParams(val buildtype: String,
                           val compiler: String,
                           val disable_rngsse2: Boolean,
                           val disable_testu01: Boolean,
                           val mathlib: String,
                           val stdlibcpp: String)

     val builds = listOf(
        BuildParams("Debug", "clang", false, false, "mkl", "libc++"),
        BuildParams("Debug", "clang", false, false, "mkl", "libstdc++")
     )

     builds.forEach{ buildType( QuinoaKotlin_Linux_Build( it ) ) }

    //buildType(QuinoaKotlin_Linux_BuildFromTmp)

    features {
        versionedSettings {
            id = "PROJECT_EXT_3"
            mode = VersionedSettings.Mode.ENABLED
            buildSettingsMode = VersionedSettings.BuildSettingsMode.PREFER_SETTINGS_FROM_VCS
            rootExtId = "QuinoaKotlin_GitGithubComJbakosiQuinoaKotlinGitRefsHeadsMaster"
            showChanges = true
            settingsFormat = VersionedSettings.Format.KOTLIN
        }
    }
})
