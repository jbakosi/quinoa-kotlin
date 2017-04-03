package QuinoaKotlin_Linux

import QuinoaKotlin_Linux.buildTypes.*
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

    buildType(QuinoaKotlin_Linux_BuildFromTmp)

    template(QuinoaKotlin_Linux_Matrix)

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
