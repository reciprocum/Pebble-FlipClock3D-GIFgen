/*
   File  : RadialDial2D.c
   Author: Afonso Santos, Portugal

   Last revision: 11h50 August 06 2016
*/

#include "Config.h"
#include "Edge.h"


const EdgeInfo RADIAL_DIAL_24_EDGEINFO
= { .edgesNum = 72
  , .edges    = (Edge[])
                { {  0,  24 }      // e0
                , {  1,  25 }      // e1
                , {  2,  26 }      // e2
                , {  3,  27 }      // e3
                , {  4,  28 }      // e4
                , {  5,  29 }      // e5
                , {  6,  30 }      // e6
                , {  7,  31 }      // e7
                , {  8,  32 }      // e8
                , {  9,  33 }      // e9
                , { 10,  34 }      // e10
                , { 11,  35 }      // e11
                , { 12,  36 }      // e12
                , { 13,  37 }      // e13
                , { 14,  38 }      // e14
                , { 15,  39 }      // e15
                , { 16,  40 }      // e16
                , { 17,  41 }      // e17
                , { 18,  42 }      // e18
                , { 19,  43 }      // e19
                , { 20,  44 }      // e20
                , { 21,  45 }      // e21
                , { 22,  46 }      // e22
                , { 23,  47 }      // e23

                , {  0,   0 }      // e24
                , {  0,   1 }      // e25
                , {  1,   2 }      // e26
                , {  2,   3 }      // e27
                , {  3,   4 }      // e28
                , {  4,   5 }      // e29
                , {  5,   6 }      // e30
                , {  6,   7 }      // e31
                , {  7,   8 }      // e32
                , {  8,   9 }      // e33
                , {  9,  10 }      // e34
                , { 10,  11 }      // e35
                , { 11,  12 }      // e36
                , { 12,  13 }      // e37
                , { 13,  14 }      // e38
                , { 14,  15 }      // e39
                , { 15,  16 }      // e40
                , { 16,  17 }      // e41
                , { 17,  18 }      // e42
                , { 18,  19 }      // e43
                , { 19,  20 }      // e44
                , { 20,  21 }      // e45
                , { 21,  22 }      // e46
                , { 22,  23 }      // e47

                , { 24,  24 }      // e48
                , { 24,  25 }      // e49
                , { 25,  26 }      // e50
                , { 26,  27 }      // e51
                , { 27,  28 }      // e52
                , { 28,  29 }      // e53
                , { 29,  30 }      // e54
                , { 30,  31 }      // e55
                , { 31,  32 }      // e56
                , { 32,  33 }      // e57
                , { 33,  34 }      // e58
                , { 34,  35 }      // e59
                , { 35,  36 }      // e60
                , { 36,  37 }      // e61
                , { 37,  38 }      // e62
                , { 38,  39 }      // e63
                , { 39,  40 }      // e64
                , { 40,  41 }      // e65
                , { 41,  42 }      // e66
                , { 42,  43 }      // e67
                , { 43,  44 }      // e68
                , { 44,  45 }      // e69
                , { 45,  46 }      // e70
                , { 46,  47 }      // e71
                }
  }
;

const unsigned char *RADIAL_DIAL_24_EVERY6ALTERNATEEDGEMASK_L2R
= (unsigned char[])
  { 0b10000010    //   0..  7
  , 0b00001000    //   8.. 15
  , 0b00100000    //  16.. 23
  , 0b00000000    //  24.. 31
  , 0b00000000    //  32.. 39
  , 0b00000000    //  40.. 47
  , 0b00000000    //  48.. 55
  , 0b00000000    //  56.. 63
  , 0b00000000    //  64.. 71
  }
;


const EdgeInfo RADIAL_DIAL_60_EDGEINFO
= { .edgesNum = 180
  , .edges    = (Edge[])
                { {   0,  60 }      // e0
                , {   1,  61 }      // e1
                , {   2,  62 }      // e2
                , {   3,  63 }      // e3
                , {   4,  64 }      // e4
                , {   5,  65 }      // e5
                , {   6,  66 }      // e6
                , {   7,  67 }      // e7
                , {   8,  68 }      // e8
                , {   9,  69 }      // e9
                , {  10,  70 }      // e10
                , {  11,  71 }      // e11
                , {  12,  72 }      // e12
                , {  13,  73 }      // e13
                , {  14,  74 }      // e14
                , {  15,  75 }      // e15
                , {  16,  76 }      // e16
                , {  17,  77 }      // e17
                , {  18,  78 }      // e18
                , {  19,  79 }      // e19
                , {  20,  80 }      // e20
                , {  21,  81 }      // e21
                , {  22,  82 }      // e22
                , {  23,  83 }      // e23
                , {  24,  84 }      // e24
                , {  25,  85 }      // e25
                , {  26,  86 }      // e26
                , {  27,  87 }      // e27
                , {  28,  88 }      // e28
                , {  29,  89 }      // e29
                , {  30,  90 }      // e30
                , {  31,  91 }      // e31
                , {  32,  92 }      // e32
                , {  33,  93 }      // e33
                , {  34,  94 }      // e34
                , {  35,  95 }      // e35
                , {  36,  96 }      // e36
                , {  37,  97 }      // e37
                , {  38,  98 }      // e38
                , {  39,  99 }      // e39
                , {  40, 100 }      // e40
                , {  41, 101 }      // e41
                , {  42, 102 }      // e42
                , {  43, 103 }      // e43
                , {  44, 104 }      // e44
                , {  45, 105 }      // e45
                , {  46, 106 }      // e46
                , {  47, 107 }      // e47
                , {  48, 108 }      // e48
                , {  49, 109 }      // e49
                , {  50, 110 }      // e50
                , {  51, 111 }      // e51
                , {  52, 112 }      // e52
                , {  53, 113 }      // e53
                , {  54, 114 }      // e54
                , {  55, 115 }      // e55
                , {  56, 116 }      // e56
                , {  57, 117 }      // e57
                , {  58, 118 }      // e58
                , {  59, 119 }      // e59

                , {   0,   0 }      // e60
                , {   0,   1 }      // e61
                , {   1,   2 }      // e62
                , {   2,   3 }      // e63
                , {   3,   4 }      // e64
                , {   4,   5 }      // e65
                , {   5,   6 }      // e66
                , {   6,   7 }      // e67
                , {   7,   8 }      // e68
                , {   8,   9 }      // e69
                , {   9,  10 }      // e70
                , {  10,  11 }      // e71
                , {  11,  12 }      // e72
                , {  12,  13 }      // e73
                , {  13,  14 }      // e74
                , {  14,  15 }      // e75
                , {  15,  16 }      // e76
                , {  16,  17 }      // e77
                , {  17,  18 }      // e78
                , {  18,  19 }      // e79
                , {  19,  20 }      // e80
                , {  20,  21 }      // e81
                , {  21,  22 }      // e82
                , {  22,  23 }      // e83
                , {  23,  24 }      // e84
                , {  24,  25 }      // e85
                , {  25,  26 }      // e86
                , {  26,  27 }      // e87
                , {  27,  28 }      // e88
                , {  28,  29 }      // e89
                , {  29,  30 }      // e90
                , {  30,  31 }      // e91
                , {  31,  32 }      // e92
                , {  32,  33 }      // e93
                , {  33,  34 }      // e94
                , {  34,  35 }      // e95
                , {  35,  36 }      // e96
                , {  36,  37 }      // e97
                , {  37,  38 }      // e98
                , {  38,  39 }      // e99
                , {  39,  40 }      // e100
                , {  40,  41 }      // e101
                , {  41,  42 }      // e102
                , {  42,  43 }      // e103
                , {  43,  44 }      // e104
                , {  44,  45 }      // e105
                , {  45,  46 }      // e106
                , {  46,  47 }      // e107
                , {  47,  48 }      // e108
                , {  48,  49 }      // e109
                , {  49,  50 }      // e110
                , {  50,  51 }      // e111
                , {  51,  52 }      // e112
                , {  52,  53 }      // e113
                , {  53,  54 }      // e114
                , {  54,  55 }      // e115
                , {  55,  56 }      // e116
                , {  56,  57 }      // e117
                , {  57,  58 }      // e118
                , {  58,  59 }      // e119

                , {  60,  60 }      // e120
                , {  60,  61 }      // e121
                , {  61,  62 }      // e122
                , {  62,  63 }      // e123
                , {  63,  64 }      // e124
                , {  64,  65 }      // e125
                , {  65,  66 }      // e126
                , {  66,  67 }      // e127
                , {  67,  68 }      // e128
                , {  68,  69 }      // e129
                , {  69,  70 }      // e130
                , {  70,  71 }      // e131
                , {  71,  72 }      // e132
                , {  72,  73 }      // e133
                , {  73,  74 }      // e134
                , {  74,  75 }      // e135
                , {  75,  76 }      // e136
                , {  76,  77 }      // e137
                , {  77,  78 }      // e138
                , {  78,  79 }      // e139
                , {  79,  80 }      // e140
                , {  80,  81 }      // e141
                , {  81,  82 }      // e142
                , {  82,  83 }      // e143
                , {  83,  84 }      // e144
                , {  84,  85 }      // e145
                , {  85,  86 }      // e146
                , {  86,  87 }      // e147
                , {  87,  88 }      // e148
                , {  88,  89 }      // e149
                , {  89,  90 }      // e150
                , {  90,  91 }      // e151
                , {  91,  92 }      // e152
                , {  92,  93 }      // e153
                , {  93,  94 }      // e154
                , {  94,  95 }      // e155
                , {  95,  96 }      // e156
                , {  96,  97 }      // e157
                , {  97,  98 }      // e158
                , {  98,  99 }      // e159
                , {  99, 100 }      // e160
                , { 100, 101 }      // e161
                , { 101, 102 }      // e162
                , { 102, 103 }      // e163
                , { 103, 104 }      // e164
                , { 104, 105 }      // e165
                , { 105, 106 }      // e166
                , { 106, 107 }      // e167
                , { 107, 108 }      // e168
                , { 108, 109 }      // e169
                , { 109, 110 }      // e170
                , { 110, 111 }      // e171
                , { 111, 112 }      // e172
                , { 112, 113 }      // e173
                , { 113, 114 }      // e174
                , { 114, 115 }      // e175
                , { 115, 116 }      // e176
                , { 116, 117 }      // e177
                , { 117, 118 }      // e178
                , { 118, 119 }      // e179
                }
  }
;

const unsigned char *RADIAL_DIAL_60_EVERY5ALTERNATEEDGEMASK_L2R
= (unsigned char[])
  { 0b10000100    //   0..  7
  , 0b00100001    //   8.. 15
  , 0b00001000    //  16.. 23
  , 0b01000010    //  24.. 31
  , 0b00010000    //  32.. 39
  , 0b10000100    //  40.. 47
  , 0b00100001    //  48.. 55
  , 0b00000000    //  56.. 63
  , 0b00000000    //  64.. 71
  , 0b00000000    //  72.. 79
  , 0b00000000    //  80.. 87
  , 0b00000000    //  88.. 95
  , 0b00000000    //  96..103
  , 0b00000000    // 104..111
  , 0b00000000    // 112..119
  , 0b00000000    // 120..127
  , 0b00000000    // 128..135
  , 0b00000000    // 136..143
  , 0b00000000    // 144..151
  , 0b00000000    // 152..159
  , 0b00000000    // 160..167
  , 0b00000000    // 168..175
  , 0b00000000    // 176..183
  }
;


const EdgeInfo RADIAL_DIAL_100_EDGEINFO
= { .edgesNum = 300
  , .edges    = (Edge[])
                { {  0, 100 }      // e0
                , {  1, 101 }      // e1
                , {  2, 102 }      // e2
                , {  3, 103 }      // e3
                , {  4, 104 }      // e4
                , {  5, 105 }      // e5
                , {  6, 106 }      // e6
                , {  7, 107 }      // e7
                , {  8, 108 }      // e8
                , {  9, 109 }      // e9
                , { 10, 110 }      // e10
                , { 11, 111 }      // e11
                , { 12, 112 }      // e12
                , { 13, 113 }      // e13
                , { 14, 114 }      // e14
                , { 15, 115 }      // e15
                , { 16, 116 }      // e16
                , { 17, 117 }      // e17
                , { 18, 118 }      // e18
                , { 19, 119 }      // e19
                , { 20, 120 }      // e20
                , { 21, 121 }      // e21
                , { 22, 122 }      // e22
                , { 23, 123 }      // e23
                , { 24, 124 }      // e24
                , { 25, 125 }      // e25
                , { 26, 126 }      // e26
                , { 27, 127 }      // e27
                , { 28, 128 }      // e28
                , { 29, 129 }      // e29
                , { 30, 130 }      // e30
                , { 31, 131 }      // e31
                , { 32, 132 }      // e32
                , { 33, 133 }      // e33
                , { 34, 134 }      // e34
                , { 35, 135 }      // e35
                , { 36, 136 }      // e36
                , { 37, 137 }      // e37
                , { 38, 138 }      // e38
                , { 39, 139 }      // e39
                , { 40, 140 }      // e40
                , { 41, 141 }      // e41
                , { 42, 142 }      // e42
                , { 43, 143 }      // e43
                , { 44, 144 }      // e44
                , { 45, 145 }      // e45
                , { 46, 146 }      // e46
                , { 47, 147 }      // e47
                , { 48, 148 }      // e48
                , { 49, 149 }      // e49
                , { 50, 150 }      // e50
                , { 51, 151 }      // e51
                , { 52, 152 }      // e52
                , { 53, 153 }      // e53
                , { 54, 154 }      // e54
                , { 55, 155 }      // e55
                , { 56, 156 }      // e56
                , { 57, 157 }      // e57
                , { 58, 158 }      // e58
                , { 59, 159 }      // e59
                , { 60, 160 }      // e60
                , { 61, 161 }      // e61
                , { 62, 162 }      // e62
                , { 63, 163 }      // e63
                , { 64, 164 }      // e64
                , { 65, 165 }      // e65
                , { 66, 166 }      // e66
                , { 67, 167 }      // e67
                , { 68, 168 }      // e68
                , { 69, 169 }      // e69
                , { 70, 170 }      // e70
                , { 71, 171 }      // e71
                , { 72, 172 }      // e72
                , { 73, 173 }      // e73
                , { 74, 174 }      // e74
                , { 75, 175 }      // e75
                , { 76, 176 }      // e76
                , { 77, 177 }      // e77
                , { 78, 178 }      // e78
                , { 79, 179 }      // e79
                , { 80, 180 }      // e80
                , { 81, 181 }      // e81
                , { 82, 182 }      // e82
                , { 83, 183 }      // e83
                , { 84, 184 }      // e84
                , { 85, 185 }      // e85
                , { 86, 186 }      // e86
                , { 87, 187 }      // e87
                , { 88, 188 }      // e88
                , { 89, 189 }      // e89
                , { 90, 190 }      // e90
                , { 91, 191 }      // e91
                , { 92, 192 }      // e92
                , { 93, 193 }      // e93
                , { 94, 194 }      // e94
                , { 95, 195 }      // e95
                , { 96, 196 }      // e96
                , { 97, 197 }      // e97
                , { 98, 198 }      // e98
                , { 99, 199 }      // e99

                , {  0,  0 }       // e100
                , {  0,  1 }       // e101
                , {  1,  2 }       // e102
                , {  2,  3 }       // e103
                , {  3,  4 }       // e104
                , {  4,  5 }       // e105
                , {  5,  6 }       // e106
                , {  6,  7 }       // e107
                , {  7,  8 }       // e108
                , {  8,  9 }       // e109
                , {  9, 10 }       // e110
                , { 10, 11 }       // e111
                , { 11, 12 }       // e112
                , { 12, 13 }       // e113
                , { 13, 14 }       // e114
                , { 14, 15 }       // e115
                , { 15, 16 }       // e116
                , { 16, 17 }       // e117
                , { 17, 18 }       // e118
                , { 18, 19 }       // e119
                , { 19, 20 }       // e120
                , { 20, 21 }       // e121
                , { 21, 22 }       // e122
                , { 22, 23 }       // e123
                , { 23, 24 }       // e124
                , { 24, 25 }       // e125
                , { 25, 26 }       // e126
                , { 26, 27 }       // e127
                , { 27, 28 }       // e128
                , { 28, 29 }       // e129
                , { 29, 30 }       // e130
                , { 30, 31 }       // e131
                , { 31, 32 }       // e132
                , { 32, 33 }       // e133
                , { 33, 34 }       // e134
                , { 34, 35 }       // e135
                , { 35, 36 }       // e136
                , { 36, 37 }       // e137
                , { 37, 38 }       // e138
                , { 38, 39 }       // e139
                , { 39, 40 }       // e140
                , { 40, 41 }       // e141
                , { 41, 42 }       // e142
                , { 42, 43 }       // e143
                , { 43, 44 }       // e144
                , { 44, 45 }       // e145
                , { 45, 46 }       // e146
                , { 46, 47 }       // e147
                , { 47, 48 }       // e148
                , { 48, 49 }       // e149
                , { 49, 50 }       // e150
                , { 50, 51 }       // e151
                , { 51, 52 }       // e152
                , { 52, 53 }       // e153
                , { 53, 54 }       // e154
                , { 54, 55 }       // e155
                , { 55, 56 }       // e156
                , { 56, 57 }       // e157
                , { 57, 58 }       // e158
                , { 58, 59 }       // e159
                , { 59, 60 }       // e160
                , { 60, 61 }       // e161
                , { 61, 62 }       // e162
                , { 62, 63 }       // e163
                , { 63, 64 }       // e164
                , { 64, 65 }       // e165
                , { 65, 66 }       // e166
                , { 66, 67 }       // e167
                , { 67, 68 }       // e168
                , { 68, 69 }       // e169
                , { 69, 70 }       // e170
                , { 70, 71 }       // e171
                , { 71, 72 }       // e172
                , { 72, 73 }       // e173
                , { 73, 74 }       // e174
                , { 74, 75 }       // e175
                , { 75, 76 }       // e176
                , { 76, 77 }       // e177
                , { 77, 78 }       // e178
                , { 78, 79 }       // e179
                , { 79, 80 }       // e180
                , { 80, 81 }       // e181
                , { 81, 82 }       // e182
                , { 82, 83 }       // e183
                , { 83, 84 }       // e184
                , { 84, 85 }       // e185
                , { 85, 86 }       // e186
                , { 86, 87 }       // e187
                , { 87, 88 }       // e188
                , { 88, 89 }       // e189
                , { 89, 90 }       // e190
                , { 90, 91 }       // e191
                , { 91, 92 }       // e192
                , { 92, 93 }       // e193
                , { 93, 94 }       // e194
                , { 94, 95 }       // e195
                , { 95, 96 }       // e196
                , { 96, 97 }       // e197
                , { 97, 98 }       // e198
                , { 98, 99 }       // e199

                , { 100, 100 }     // e200
                , { 100, 101 }     // e201
                , { 101, 102 }     // e202
                , { 102, 103 }     // e203
                , { 103, 104 }     // e204
                , { 104, 105 }     // e205
                , { 105, 106 }     // e206
                , { 106, 107 }     // e207
                , { 107, 108 }     // e208
                , { 108, 109 }     // e209
                , { 109, 110 }     // e210
                , { 110, 111 }     // e211
                , { 111, 112 }     // e212
                , { 112, 113 }     // e213
                , { 113, 114 }     // e214
                , { 114, 115 }     // e215
                , { 115, 116 }     // e216
                , { 116, 117 }     // e217
                , { 117, 118 }     // e218
                , { 118, 119 }     // e219
                , { 119, 120 }     // e220
                , { 120, 121 }     // e221
                , { 121, 122 }     // e222
                , { 122, 123 }     // e223
                , { 123, 124 }     // e224
                , { 124, 125 }     // e225
                , { 125, 126 }     // e226
                , { 126, 127 }     // e227
                , { 127, 128 }     // e228
                , { 128, 129 }     // e229
                , { 129, 130 }     // e230
                , { 130, 131 }     // e231
                , { 131, 132 }     // e232
                , { 132, 133 }     // e233
                , { 133, 134 }     // e234
                , { 134, 135 }     // e235
                , { 135, 136 }     // e236
                , { 136, 137 }     // e237
                , { 137, 138 }     // e238
                , { 138, 139 }     // e239
                , { 139, 140 }     // e240
                , { 140, 141 }     // e241
                , { 141, 142 }     // e242
                , { 142, 143 }     // e243
                , { 143, 144 }     // e244
                , { 144, 145 }     // e245
                , { 145, 146 }     // e246
                , { 146, 147 }     // e247
                , { 147, 148 }     // e248
                , { 148, 149 }     // e249
                , { 149, 150 }     // e250
                , { 150, 151 }     // e251
                , { 151, 152 }     // e252
                , { 152, 153 }     // e253
                , { 153, 154 }     // e254
                , { 154, 155 }     // e255
                , { 155, 156 }     // e256
                , { 156, 157 }     // e257
                , { 157, 158 }     // e258
                , { 158, 159 }     // e259
                , { 159, 160 }     // e260
                , { 160, 161 }     // e261
                , { 161, 162 }     // e262
                , { 162, 163 }     // e263
                , { 163, 164 }     // e264
                , { 164, 165 }     // e265
                , { 165, 166 }     // e266
                , { 166, 167 }     // e267
                , { 167, 168 }     // e268
                , { 168, 169 }     // e269
                , { 169, 170 }     // e270
                , { 170, 171 }     // e271
                , { 171, 172 }     // e272
                , { 172, 173 }     // e273
                , { 173, 174 }     // e274
                , { 174, 175 }     // e275
                , { 175, 176 }     // e276
                , { 176, 177 }     // e277
                , { 177, 178 }     // e278
                , { 178, 179 }     // e279
                , { 179, 180 }     // e280
                , { 180, 181 }     // e281
                , { 181, 182 }     // e282
                , { 182, 183 }     // e283
                , { 183, 184 }     // e284
                , { 184, 185 }     // e285
                , { 185, 186 }     // e286
                , { 186, 187 }     // e287
                , { 187, 188 }     // e288
                , { 188, 189 }     // e289
                , { 189, 190 }     // e290
                , { 190, 191 }     // e291
                , { 191, 192 }     // e292
                , { 192, 193 }     // e293
                , { 193, 194 }     // e294
                , { 194, 195 }     // e295
                , { 195, 196 }     // e296
                , { 196, 197 }     // e297
                , { 197, 198 }     // e298
                , { 198, 199 }     // e299
                }
  }
;

const unsigned char *RADIAL_DIAL_100_EVERY10ALTERNATEEDGEMASK_L2R
= (unsigned char[])
  { 0b10000000    //   0..  7
  , 0b00100000    //   8.. 15
  , 0b00001000    //  16.. 23
  , 0b00000010    //  24.. 31
  , 0b00000000    //  32.. 39
  , 0b10000000    //  40.. 47
  , 0b00100000    //  48.. 55
  , 0b00001000    //  56.. 63
  , 0b00000010    //  64.. 71
  , 0b00000000    //  72.. 79
  , 0b10000000    //  80.. 87
  , 0b00100000    //  88.. 95
  , 0b00000000    //  96..103
  , 0b00000000    // 104..111
  , 0b00000000    // 112..119
  , 0b00000000    // 120..127
  , 0b00000000    // 128..135
  , 0b00000000    // 136..143
  , 0b00000000    // 144..151
  , 0b00000000    // 152..159
  , 0b00000000    // 160..167
  , 0b00000000    // 168..175
  , 0b00000000    // 176..183
  , 0b00000000    // 184..191
  , 0b00000000    // 192..199
  , 0b00000000    // 200..207
  , 0b00000000    // 208..215
  , 0b00000000    // 216..223
  , 0b00000000    // 224..231
  , 0b00000000    // 232..239
  , 0b00000000    // 240..247
  , 0b00000000    // 248..255
  , 0b00000000    // 256..263
  , 0b00000000    // 264..271
  , 0b00000000    // 272..279
  , 0b00000000    // 280..287
  , 0b00000000    // 288..295
  , 0b00000000    // 296..303
  }
;