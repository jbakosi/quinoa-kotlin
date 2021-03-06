package QuinoaKotlin_Linux.buildParams

enum class CmakeBuildType { Debug, Release }
enum class Compiler { clang, gnu }
enum class MathLib { mkl, lapack }
enum class StdLibC { libc, libstdc }

data class BuildParams( val buildtype: CmakeBuildType,
                        val compiler: Compiler,
                        val mathlib: MathLib,
                        val stdlibc: StdLibC,
                        val rngsse2: Boolean,
                        val testu01: Boolean )
