package QuinoaKotlin

import QuinoaKotlin.vcsRoots.*
import QuinoaKotlin.vcsRoots.QuinoaKotlin_GitGithubComJbakosiQuinoaKotlinGitRefsHeadsMaster
import jetbrains.buildServer.configs.kotlin.v10.*
import jetbrains.buildServer.configs.kotlin.v10.Project
import jetbrains.buildServer.configs.kotlin.v10.projectFeatures.VersionedSettings
import jetbrains.buildServer.configs.kotlin.v10.projectFeatures.VersionedSettings.*
import jetbrains.buildServer.configs.kotlin.v10.projectFeatures.versionedSettings

object Project : Project({
    uuid = "836f6694-574f-448a-ad1d-4732464fbc2a"
    extId = "QuinoaKotlin"
    parentId = "_Root"
    name = "Quinoa Kotlin"

    vcsRoot(QuinoaKotlin_GitGithubComJbakosiQuinoaKotlinGitRefsHeadsMaster)

    features {
        versionedSettings {
            id = "PROJECT_EXT_2"
            mode = VersionedSettings.Mode.ENABLED
            buildSettingsMode = VersionedSettings.BuildSettingsMode.PREFER_SETTINGS_FROM_VCS
            rootExtId = QuinoaKotlin_GitGithubComJbakosiQuinoaKotlinGitRefsHeadsMaster.extId
            showChanges = false
            settingsFormat = VersionedSettings.Format.KOTLIN
        }
    }
})
