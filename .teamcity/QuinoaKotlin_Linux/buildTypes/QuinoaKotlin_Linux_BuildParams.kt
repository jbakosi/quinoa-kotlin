package QuinoaKotlin_Linux.buildParams

data class BuildParams(val buildtype: String,
                       val compiler: String,
                       val disable_rngsse2: Boolean,
                       val disable_testu01: Boolean,
                       val mathlib: String,
                       val stdlibcpp: String)
