package QuinoaKotlin_Linux.buildParams

enum class CmakeBuildType { Debug, Release }
enum class Compiler { clang, gnu }
enum class MathLib { mkl, lapack }
enum class StdLibCpp { libc, libstdc }

data class BuildParams( val buildtype: CmakeBuildType,
                        val compiler: Compiler,
                        val mathlib: MathLib,
                        val stdlibcpp: StdLibCpp,
                        val rngsse2: Boolean,
                        val testu01: Boolean )
