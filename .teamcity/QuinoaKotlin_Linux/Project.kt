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

    template( QuinoaKotlin_Linux_Matrix )

    val allBuilds = mutableListOf< BuildParams >()

    // Generate matrix with all possible combinations of build parameters,
    // defined in package buildParams.
    Compiler.values().forEach{ c ->
      StdLibC.values().forEach{ l ->
        MathLib.values().forEach{ m ->
          CmakeBuildType.values().forEach{ b ->
            for( r in listOf( true, false ) ) {
              for( t in listOf( true, false ) ) {
                allBuilds.add( BuildParams(b,c,m,l,r,t) )
              }
            }
          }
        }
      }
    }

    val builds = mutableListOf< BuildParams >()

    // Exclude some builds
    allBuilds.forEach{ b ->
      if ( !(b.compiler == Compiler.gnu && b.stdlibc == StdLibC.libc)) {
        builds.add( b );
      }
    }

    // Generate TeamCity builds
    builds.forEach{ buildType( QuinoaKotlin_Linux_Build(it) ) }

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
