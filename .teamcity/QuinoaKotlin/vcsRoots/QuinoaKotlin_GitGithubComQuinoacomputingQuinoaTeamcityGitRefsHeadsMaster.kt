package QuinoaKotlin.vcsRoots

import jetbrains.buildServer.configs.kotlin.v10.*
import jetbrains.buildServer.configs.kotlin.v10.vcs.GitVcsRoot

object QuinoaKotlin_GitGithubComQuinoacomputingQuinoaTeamcityGitRefsHeadsMaster : GitVcsRoot({
    uuid = "39847b99-5323-4453-aa17-eaed879042a6"
    extId = "QuinoaKotlin_GitGithubComQuinoacomputingQuinoaTeamcityGitRefsHeadsMaster"
    name = "git@github.com:quinoacomputing/quinoa-teamcity.git#refs/heads/master"
    url = "git@github.com:quinoacomputing/quinoa-teamcity.git"
    authMethod = defaultPrivateKey {
        userName = "git"
    }
})
