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

     // Generate matrix with all possible combinations of build parameters,
     // defined in package buildParams.
     CmakeBuildType.values().forEach{ b ->
       Compiler.values().forEach{ c ->
         MathLib.values().forEach{ m ->
           StdLibC.values().forEach{ l ->
             for( r in listOf( true, false ) ) {
               for( t in listOf( true, false ) ) {
                 buildType( QuinoaKotlin_Linux_Build( BuildParams( b, c, m, l, r, t ) ) )
               }
             }
           }
         }
       }
     }

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
