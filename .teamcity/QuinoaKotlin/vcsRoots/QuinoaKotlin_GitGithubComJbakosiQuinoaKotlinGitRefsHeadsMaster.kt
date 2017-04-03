package QuinoaKotlin.vcsRoots

import jetbrains.buildServer.configs.kotlin.v10.*
import jetbrains.buildServer.configs.kotlin.v10.vcs.GitVcsRoot

object QuinoaKotlin_GitGithubComJbakosiQuinoaKotlinGitRefsHeadsMaster : GitVcsRoot({
    uuid = "70c1ccdf-8610-4bfb-8b50-97c93b3b6058"
    extId = "QuinoaKotlin_GitGithubComJbakosiQuinoaKotlinGitRefsHeadsMaster"
    name = "git@github.com:jbakosi/quinoa-kotlin.git#refs/heads/master"
    url = "git@github.com:jbakosi/quinoa-kotlin.git"
    checkoutSubmodules = GitVcsRoot.CheckoutSubmodules.IGNORE
    authMethod = defaultPrivateKey {
        userName = "git"
    }
})
