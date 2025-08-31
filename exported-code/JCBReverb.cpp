#include "JCBReverb.h"

namespace JCBReverb {

/****************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER 200k USD in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below 200k USD annual revenue or funding.

For entities with OVER 200k USD in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing (at) cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
****************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Change __m_change_172;
	Change __m_change_209;
	Change __m_change_155;
	Change __m_change_265;
	Change __m_change_194;
	Change __m_change_193;
	Change __m_change_156;
	Change __m_change_174;
	Change __m_change_266;
	Change __m_change_284;
	Change __m_change_308;
	Change __m_change_286;
	Change __m_change_307;
	Change __m_change_285;
	Change __m_change_173;
	DCBlock __m_dcblock_324;
	DCBlock __m_dcblock_325;
	Delay m_delay_15;
	Delay m_delay_63;
	Delay m_delay_61;
	Delay m_delay_59;
	Delay m_delay_37;
	Delay m_delay_35;
	Delay m_delay_65;
	Delay m_delay_67;
	Delay m_delay_33;
	Delay m_delay_57;
	Delay m_delay_53;
	Delay m_delay_47;
	Delay m_delay_48;
	Delay m_delay_55;
	Delay m_delay_46;
	Delay m_delay_52;
	Delay m_delay_51;
	Delay m_delay_14;
	Delay m_delay_69;
	Delay m_delay_preL_4;
	Delay m_delay_19;
	Delay m_delay_20;
	Delay m_delay_21;
	Delay m_delay_18;
	Delay m_delay_16;
	Delay m_delay_17;
	Delay m_delay_31;
	Delay m_delay_13;
	Delay m_delay_49;
	Delay m_delay_preR_7;
	Delay m_delay_29;
	Delay m_delay_23;
	Delay m_delay_27;
	Delay m_delay_25;
	Delay m_delay_10;
	Delay m_delay_50;
	int __exception;
	int vectorsize;
	t_sample m_z_179;
	t_sample m_z_178;
	t_sample m_z_181;
	t_sample m_z_182;
	t_sample m_z_183;
	t_sample m_h_combDelayR_44;
	t_sample m_z_176;
	t_sample m_z_177;
	t_sample m_h_combStateR_22;
	t_sample m_h_postRightAccum_12;
	t_sample m_h_combStateR_24;
	t_sample m_z_184;
	t_sample m_a_188;
	t_sample m_h_postRightOverFlag_11;
	t_sample m_h_postLeftAccum_9;
	t_sample m_z_196;
	t_sample m_a_187;
	t_sample m_shelfGain_192;
	t_sample m_shelfTerm_190;
	t_sample m_cutoff_191;
	t_sample m_w_189;
	t_sample m_w_171;
	t_sample m_b_170;
	t_sample m_d_169;
	t_sample m_shelfTerm_152;
	t_sample m_cutoff_153;
	t_sample m_shelfGain_154;
	t_sample m_h_combStateR_28;
	t_sample m_w_151;
	t_sample m_a_149;
	t_sample m_a_150;
	t_sample m_q_ONOFFEQ_146;
	t_sample m_e_SIZE_147;
	t_sample m_z_198;
	t_sample m_h_combStateR_26;
	t_sample m_z_159;
	t_sample m_wq_166;
	t_sample m_d_167;
	t_sample m_d_168;
	t_sample m_z_157;
	t_sample m_w_165;
	t_sample m_a_163;
	t_sample m_a_164;
	t_sample m_a_162;
	t_sample __m_slide_203;
	t_sample __m_slide_206;
	t_sample m_h_postLeftOverFlag_8;
	t_sample m_z_295;
	t_sample m_z_296;
	t_sample m_z_297;
	t_sample m_a_301;
	t_sample m_z_294;
	t_sample m_z_291;
	t_sample m_z_292;
	t_sample m_z_289;
	t_sample m_z_290;
	t_sample m_prePost_s_1;
	t_sample m_a_302;
	t_sample m_shelfTerm_304;
	t_sample m_z_313;
	t_sample __m_slide_318;
	t_sample __m_slide_321;
	t_sample m_w_303;
	t_sample m_z_311;
	t_sample m_shelfGain_306;
	t_sample samplerate;
	t_sample m_cutoff_305;
	t_sample m_u_ATK_145;
	t_sample m_preL_flag_2;
	t_sample m_w_283;
	t_sample m_shelfGain_264;
	t_sample m_preR_accum_6;
	t_sample m_preR_flag_5;
	t_sample m_z_268;
	t_sample m_cutoff_263;
	t_sample m_w_261;
	t_sample m_shelfTerm_262;
	t_sample m_a_259;
	t_sample m_a_260;
	t_sample m_preL_accum_3;
	t_sample m_z_270;
	t_sample m_a_275;
	t_sample m_d_280;
	t_sample m_d_281;
	t_sample m_b_282;
	t_sample m_a_274;
	t_sample m_d_279;
	t_sample m_w_277;
	t_sample m_wq_278;
	t_sample m_a_276;
	t_sample m_h_combDelayR_45;
	t_sample m_i_PEAKGAIN_144;
	t_sample m_k_LPF_142;
	t_sample m_history_81;
	t_sample m_history_82;
	t_sample m_history_83;
	t_sample m_history_84;
	t_sample m_history_80;
	t_sample m_history_78;
	t_sample m_history_79;
	t_sample m_h_combDelayL_76;
	t_sample m_h_combDelayL_77;
	t_sample m_h_combDelayL_75;
	t_sample m_history_85;
	t_sample m_history_87;
	t_sample m_history_93;
	t_sample m_h_freezeGate_94;
	t_sample m_h_reflectCoef_95;
	t_sample m_history_86;
	t_sample m_history_92;
	t_sample m_history_90;
	t_sample m_history_91;
	t_sample m_history_88;
	t_sample m_history_89;
	t_sample m_h_hpfHz_96;
	t_sample m_h_combDelayL_74;
	t_sample m_h_combDelayL_72;
	t_sample m_h_combStateL_58;
	t_sample m_h_combDelayR_40;
	t_sample m_h_combStateL_60;
	t_sample m_h_combDelayR_39;
	t_sample m_h_combDelayR_41;
	t_sample m_h_combDelayR_42;
	t_sample m_h_combStateL_56;
	t_sample m_h_combDelayR_43;
	t_sample m_h_combStateL_54;
	t_sample m_h_combDelayL_73;
	t_sample m_h_combStateL_62;
	t_sample m_h_combStateL_64;
	t_sample m_h_combStateR_32;
	t_sample m_h_combDelayL_70;
	t_sample m_h_combDelayL_71;
	t_sample m_h_combDelayR_38;
	t_sample m_h_combStateL_68;
	t_sample m_h_combStateL_66;
	t_sample m_h_combStateR_34;
	t_sample m_h_combStateR_36;
	t_sample m_r_ONOFFCOMP_143;
	t_sample m_h_lpfHz_97;
	t_sample m_h_inputTrim_99;
	t_sample m_v_REL_128;
	t_sample m_l_HPF_129;
	t_sample m_w_MAKEUP_130;
	t_sample m_p_HIFREQ_131;
	t_sample m_m_OUTPUT_127;
	t_sample m_h_LOWGAIN_125;
	t_sample m_s_THD_126;
	t_sample m_y_IOMODE_123;
	t_sample m_x_PREPOST_124;
	t_sample m_z_BYPASSS_122;
	t_sample m_o_PEAKFREQ_132;
	t_sample m_b_DRYWET_134;
	t_sample m_g_FREEZE_139;
	t_sample m_n_LOWFREQ_140;
	t_sample m_t_RATIO_141;
	t_sample m_j_HIGAIN_133;
	t_sample m_d_DAMP_138;
	t_sample m_c_REFLECT_136;
	t_sample m_f_ST_137;
	t_sample m_a_INPUT_135;
	t_sample m_h_sizeScale_98;
	t_sample m_z_SOFTCLIP_121;
	t_sample m_h_prepostGap_119;
	t_sample m_h_lowFreqHz_105;
	t_sample m_h_stereoWidth_106;
	t_sample m_h_freezeBlend_107;
	t_sample m_h_eqEnabled_108;
	t_sample m_h_peakFreqHz_104;
	t_sample m_h_lowGainDb_102;
	t_sample m_h_hiFreqHz_103;
	t_sample m_h_hiGainDb_100;
	t_sample m_h_peakGainDb_101;
	t_sample m_h_outputTrim_120;
	t_sample m_h_dryWetStage_109;
	t_sample m_h_makeupDb_111;
	t_sample m_h_compEnable_116;
	t_sample m_h_combStateR_30;
	t_sample m_h_softclipEnable_118;
	t_sample m_h_dryWetStage_110;
	t_sample m_h_thresholdDb_115;
	t_sample m_h_attackMs_113;
	t_sample m_h_ratio_114;
	t_sample m_h_releaseMs_112;
	t_sample m_h_bypass_117;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_prePost_s_1 = ((int)0);
		m_preL_flag_2 = ((int)0);
		m_preL_accum_3 = ((int)0);
		m_delay_preL_4.reset("m_delay_preL_4", ((int)44100));
		m_preR_flag_5 = ((int)0);
		m_preR_accum_6 = ((int)0);
		m_delay_preR_7.reset("m_delay_preR_7", ((int)44100));
		m_h_postLeftOverFlag_8 = ((int)0);
		m_h_postLeftAccum_9 = ((int)0);
		m_delay_10.reset("m_delay_10", ((int)44100));
		m_h_postRightOverFlag_11 = ((int)0);
		m_h_postRightAccum_12 = ((int)0);
		m_delay_13.reset("m_delay_13", ((int)44100));
		m_delay_14.reset("m_delay_14", samplerate);
		m_delay_15.reset("m_delay_15", samplerate);
		m_delay_16.reset("m_delay_16", samplerate);
		m_delay_17.reset("m_delay_17", samplerate);
		m_delay_18.reset("m_delay_18", samplerate);
		m_delay_19.reset("m_delay_19", samplerate);
		m_delay_20.reset("m_delay_20", samplerate);
		m_delay_21.reset("m_delay_21", samplerate);
		m_h_combStateR_22 = ((int)0);
		m_delay_23.reset("m_delay_23", samplerate);
		m_h_combStateR_24 = ((int)0);
		m_delay_25.reset("m_delay_25", samplerate);
		m_h_combStateR_26 = ((int)0);
		m_delay_27.reset("m_delay_27", samplerate);
		m_h_combStateR_28 = ((int)0);
		m_delay_29.reset("m_delay_29", samplerate);
		m_h_combStateR_30 = ((int)0);
		m_delay_31.reset("m_delay_31", samplerate);
		m_h_combStateR_32 = ((int)0);
		m_delay_33.reset("m_delay_33", samplerate);
		m_h_combStateR_34 = ((int)0);
		m_delay_35.reset("m_delay_35", samplerate);
		m_h_combStateR_36 = ((int)0);
		m_delay_37.reset("m_delay_37", samplerate);
		m_h_combDelayR_38 = ((int)0);
		m_h_combDelayR_39 = ((int)0);
		m_h_combDelayR_40 = ((int)0);
		m_h_combDelayR_41 = ((int)0);
		m_h_combDelayR_42 = ((int)0);
		m_h_combDelayR_43 = ((int)0);
		m_h_combDelayR_44 = ((int)0);
		m_h_combDelayR_45 = ((int)0);
		m_delay_46.reset("m_delay_46", samplerate);
		m_delay_47.reset("m_delay_47", samplerate);
		m_delay_48.reset("m_delay_48", samplerate);
		m_delay_49.reset("m_delay_49", samplerate);
		m_delay_50.reset("m_delay_50", samplerate);
		m_delay_51.reset("m_delay_51", samplerate);
		m_delay_52.reset("m_delay_52", samplerate);
		m_delay_53.reset("m_delay_53", samplerate);
		m_h_combStateL_54 = ((int)0);
		m_delay_55.reset("m_delay_55", samplerate);
		m_h_combStateL_56 = ((int)0);
		m_delay_57.reset("m_delay_57", samplerate);
		m_h_combStateL_58 = ((int)0);
		m_delay_59.reset("m_delay_59", samplerate);
		m_h_combStateL_60 = ((int)0);
		m_delay_61.reset("m_delay_61", samplerate);
		m_h_combStateL_62 = ((int)0);
		m_delay_63.reset("m_delay_63", samplerate);
		m_h_combStateL_64 = ((int)0);
		m_delay_65.reset("m_delay_65", samplerate);
		m_h_combStateL_66 = ((int)0);
		m_delay_67.reset("m_delay_67", samplerate);
		m_h_combStateL_68 = ((int)0);
		m_delay_69.reset("m_delay_69", samplerate);
		m_h_combDelayL_70 = ((int)0);
		m_h_combDelayL_71 = ((int)0);
		m_h_combDelayL_72 = ((int)0);
		m_h_combDelayL_73 = ((int)0);
		m_h_combDelayL_74 = ((int)0);
		m_h_combDelayL_75 = ((int)0);
		m_h_combDelayL_76 = ((int)0);
		m_h_combDelayL_77 = ((int)0);
		m_history_78 = ((int)0);
		m_history_79 = ((int)0);
		m_history_80 = ((int)0);
		m_history_81 = ((int)0);
		m_history_82 = ((int)0);
		m_history_83 = ((int)0);
		m_history_84 = ((int)0);
		m_history_85 = ((int)0);
		m_history_86 = ((int)0);
		m_history_87 = ((int)0);
		m_history_88 = ((int)0);
		m_history_89 = ((int)0);
		m_history_90 = ((int)0);
		m_history_91 = ((int)0);
		m_history_92 = ((int)0);
		m_history_93 = ((int)0);
		m_h_freezeGate_94 = ((int)0);
		m_h_reflectCoef_95 = ((int)0);
		m_h_hpfHz_96 = ((int)0);
		m_h_lpfHz_97 = ((int)0);
		m_h_sizeScale_98 = ((int)0);
		m_h_inputTrim_99 = ((int)0);
		m_h_hiGainDb_100 = ((int)0);
		m_h_peakGainDb_101 = ((int)0);
		m_h_lowGainDb_102 = ((int)0);
		m_h_hiFreqHz_103 = ((int)0);
		m_h_peakFreqHz_104 = ((int)0);
		m_h_lowFreqHz_105 = ((int)0);
		m_h_stereoWidth_106 = ((int)0);
		m_h_freezeBlend_107 = ((int)0);
		m_h_eqEnabled_108 = ((int)0);
		m_h_dryWetStage_109 = ((int)0);
		m_h_dryWetStage_110 = ((int)0);
		m_h_makeupDb_111 = ((int)0);
		m_h_releaseMs_112 = ((int)0);
		m_h_attackMs_113 = ((int)0);
		m_h_ratio_114 = ((int)0);
		m_h_thresholdDb_115 = ((int)0);
		m_h_compEnable_116 = ((int)0);
		m_h_bypass_117 = ((int)0);
		m_h_softclipEnable_118 = ((int)0);
		m_h_prepostGap_119 = ((int)0);
		m_h_outputTrim_120 = ((int)0);
		m_z_SOFTCLIP_121 = 0;
		m_z_BYPASSS_122 = 0;
		m_y_IOMODE_123 = 3;
		m_x_PREPOST_124 = 0;
		m_h_LOWGAIN_125 = 0;
		m_s_THD_126 = -12;
		m_m_OUTPUT_127 = 0;
		m_v_REL_128 = 100;
		m_l_HPF_129 = 20;
		m_w_MAKEUP_130 = 0;
		m_p_HIFREQ_131 = 2000;
		m_o_PEAKFREQ_132 = 800;
		m_j_HIGAIN_133 = 0;
		m_b_DRYWET_134 = 0.33;
		m_a_INPUT_135 = 0;
		m_c_REFLECT_136 = 0.86;
		m_f_ST_137 = 0.5;
		m_d_DAMP_138 = 0.8;
		m_g_FREEZE_139 = 0;
		m_n_LOWFREQ_140 = 500;
		m_t_RATIO_141 = 2;
		m_k_LPF_142 = 20000;
		m_r_ONOFFCOMP_143 = 0;
		m_i_PEAKGAIN_144 = 0;
		m_u_ATK_145 = 10;
		m_q_ONOFFEQ_146 = 0;
		m_e_SIZE_147 = 1;
		m_a_149 = ((int)0);
		m_a_150 = ((int)0);
		m_w_151 = ((int)0);
		m_shelfTerm_152 = ((int)0);
		m_cutoff_153 = ((int)0);
		m_shelfGain_154 = ((int)0);
		__m_change_155.reset(0);
		__m_change_156.reset(0);
		m_z_157 = ((int)0);
		m_z_159 = ((int)0);
		m_a_162 = ((int)0);
		m_a_163 = ((int)0);
		m_a_164 = ((int)0);
		m_w_165 = ((int)0);
		m_wq_166 = ((int)0);
		m_d_167 = ((int)0);
		m_d_168 = ((int)0);
		m_d_169 = ((int)0);
		m_b_170 = ((int)0);
		m_w_171 = ((int)0);
		__m_change_172.reset(0);
		__m_change_173.reset(0);
		__m_change_174.reset(0);
		m_z_176 = ((int)0);
		m_z_177 = ((int)0);
		m_z_178 = ((int)0);
		m_z_179 = ((int)0);
		m_z_181 = ((int)0);
		m_z_182 = ((int)0);
		m_z_183 = ((int)0);
		m_z_184 = ((int)0);
		m_a_187 = ((int)0);
		m_a_188 = ((int)0);
		m_w_189 = ((int)0);
		m_shelfTerm_190 = ((int)0);
		m_cutoff_191 = ((int)0);
		m_shelfGain_192 = ((int)0);
		__m_change_193.reset(0);
		__m_change_194.reset(0);
		m_z_196 = ((int)0);
		m_z_198 = ((int)0);
		__m_slide_203 = 0;
		__m_slide_206 = 0;
		__m_change_209.reset(0);
		m_a_259 = ((int)0);
		m_a_260 = ((int)0);
		m_w_261 = ((int)0);
		m_shelfTerm_262 = ((int)0);
		m_cutoff_263 = ((int)0);
		m_shelfGain_264 = ((int)0);
		__m_change_265.reset(0);
		__m_change_266.reset(0);
		m_z_268 = ((int)0);
		m_z_270 = ((int)0);
		m_a_274 = ((int)0);
		m_a_275 = ((int)0);
		m_a_276 = ((int)0);
		m_w_277 = ((int)0);
		m_wq_278 = ((int)0);
		m_d_279 = ((int)0);
		m_d_280 = ((int)0);
		m_d_281 = ((int)0);
		m_b_282 = ((int)0);
		m_w_283 = ((int)0);
		__m_change_284.reset(0);
		__m_change_285.reset(0);
		__m_change_286.reset(0);
		m_z_289 = ((int)0);
		m_z_290 = ((int)0);
		m_z_291 = ((int)0);
		m_z_292 = ((int)0);
		m_z_294 = ((int)0);
		m_z_295 = ((int)0);
		m_z_296 = ((int)0);
		m_z_297 = ((int)0);
		m_a_301 = ((int)0);
		m_a_302 = ((int)0);
		m_w_303 = ((int)0);
		m_shelfTerm_304 = ((int)0);
		m_cutoff_305 = ((int)0);
		m_shelfGain_306 = ((int)0);
		__m_change_307.reset(0);
		__m_change_308.reset(0);
		m_z_311 = ((int)0);
		m_z_313 = ((int)0);
		__m_slide_318 = 0;
		__m_slide_321 = 0;
		__m_dcblock_324.reset();
		__m_dcblock_325.reset();
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		t_sample * __out4 = __outs[3];
		t_sample * __out5 = __outs[4];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int freezeOn = (m_g_FREEZE_139 == ((int)1));
		t_sample ioMode = m_y_IOMODE_123;
		int isMonoIn = ((ioMode == ((int)1)) || (ioMode == ((int)2)));
		int isMonoOut = (ioMode == ((int)1));
		t_sample dampPass = (((int)1) - m_d_DAMP_138);
		t_sample dampLeak = m_d_DAMP_138;
		t_sample sizeInputScaled = (m_e_SIZE_147 * ((t_sample)0.001));
		t_sample lpfInputScaled = (m_k_LPF_142 * ((t_sample)0.001));
		t_sample hpfInputScaled = (m_l_HPF_129 * ((t_sample)0.001));
		t_sample reflectComplement = (((int)1) - m_c_REFLECT_136);
		int choice_148 = freezeOn;
		t_sample reflectGate = ((choice_148 >= 1) ? reflectComplement : 0);
		t_sample reflectBase = (m_c_REFLECT_136 + reflectGate);
		t_sample reflectInputScaled = (reflectBase * ((t_sample)0.001));
		int freezeComplement = (((int)1) - (m_g_FREEZE_139 == ((int)1)));
		t_sample freezeInputScaled = (freezeComplement * ((t_sample)0.001));
		int prePostBinary = (m_x_PREPOST_124 > ((t_sample)0.5));
		t_sample leftCombLeak = dampLeak;
		t_sample leftCombPass = dampPass;
		t_sample sampleRateScaleL = (samplerate * ((t_sample)2.2675736961451e-05));
		int max_212 = (samplerate - ((int)1));
		int max_214 = (samplerate - ((int)1));
		int max_216 = (samplerate - ((int)1));
		int max_218 = (samplerate - ((int)1));
		int max_220 = (samplerate - ((int)1));
		int max_222 = (samplerate - ((int)1));
		int max_224 = (samplerate - ((int)1));
		int max_226 = (samplerate - ((int)1));
		t_sample sampleRateScaleAP_L = (samplerate * ((t_sample)2.2675736961451e-05));
		int max_228 = (samplerate - ((int)1));
		int max_230 = (samplerate - ((int)1));
		int max_232 = (samplerate - ((int)1));
		int max_234 = (samplerate - ((int)1));
		t_sample rightCombLeak = dampLeak;
		t_sample rightCombPass = dampPass;
		t_sample sampleRateScaleR = (samplerate * ((t_sample)2.2675736961451e-05));
		int max_236 = (samplerate - ((int)1));
		int max_238 = (samplerate - ((int)1));
		int max_240 = (samplerate - ((int)1));
		int max_242 = (samplerate - ((int)1));
		int max_244 = (samplerate - ((int)1));
		int max_246 = (samplerate - ((int)1));
		int max_248 = (samplerate - ((int)1));
		int max_250 = (samplerate - ((int)1));
		t_sample sampleRateScaleAP_R = (samplerate * ((t_sample)2.2675736961451e-05));
		int max_252 = (samplerate - ((int)1));
		int max_254 = (samplerate - ((int)1));
		int max_256 = (samplerate - ((int)1));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample prePostBlend = ((m_prePost_s_1 * ((t_sample)0.999)) + (m_x_PREPOST_124 * ((t_sample)0.001)));
			t_sample outputTrimLin = ((m_h_outputTrim_120 * ((t_sample)0.999)) + (dbtoa(m_m_OUTPUT_127) * ((t_sample)0.001)));
			t_sample next_outputTrim = fixdenorm(outputTrimLin);
			t_sample compEnableSmoothed = ((m_h_compEnable_116 * ((t_sample)0.999)) + (m_r_ONOFFCOMP_143 * ((t_sample)0.001)));
			t_sample next_compEnable = fixdenorm(compEnableSmoothed);
			t_sample softclipEnabled = ((m_h_softclipEnable_118 * ((t_sample)0.999)) + (m_z_SOFTCLIP_121 * ((t_sample)0.001)));
			t_sample next_softclipEnable = fixdenorm(softclipEnabled);
			t_sample bypassSmoothed = ((m_h_bypass_117 * ((t_sample)0.999)) + (m_z_BYPASSS_122 * ((t_sample)0.001)));
			t_sample next_bypass = fixdenorm(bypassSmoothed);
			t_sample thresholdDb = ((m_h_thresholdDb_115 * ((t_sample)0.999)) + (m_s_THD_126 * ((t_sample)0.001)));
			t_sample next_thresholdDb = fixdenorm(thresholdDb);
			t_sample ratio = ((m_h_ratio_114 * ((t_sample)0.999)) + (m_t_RATIO_141 * ((t_sample)0.001)));
			t_sample next_ratio = fixdenorm(ratio);
			t_sample attackMs = ((m_h_attackMs_113 * ((t_sample)0.999)) + (m_u_ATK_145 * ((t_sample)0.001)));
			t_sample next_attackMs = fixdenorm(attackMs);
			t_sample releaseMs = ((m_h_releaseMs_112 * ((t_sample)0.999)) + (m_v_REL_128 * ((t_sample)0.001)));
			t_sample next_releaseMs = fixdenorm(releaseMs);
			t_sample makeupDb = ((m_h_makeupDb_111 * ((t_sample)0.999)) + (m_w_MAKEUP_130 * ((t_sample)0.001)));
			t_sample next_makeupDb = fixdenorm(makeupDb);
			t_sample dryWet = ((m_h_dryWetStage_110 * ((t_sample)0.999)) + (m_b_DRYWET_134 * ((t_sample)0.001)));
			t_sample next_dryWetStage1 = fixdenorm(dryWet);
			t_sample dryWet_25661 = ((m_h_dryWetStage_109 * ((t_sample)0.999)) + (dryWet * ((t_sample)0.001)));
			t_sample next_dryWetStage2 = fixdenorm(dryWet_25661);
			t_sample eqEnabled = ((m_h_eqEnabled_108 * ((t_sample)0.999)) + (m_q_ONOFFEQ_146 * ((t_sample)0.001)));
			t_sample next_eqEnabled = fixdenorm(eqEnabled);
			t_sample freezeBlend = ((m_h_freezeBlend_107 * ((t_sample)0.999)) + (freezeOn * ((t_sample)0.001)));
			t_sample next_freezeBlend = fixdenorm(freezeBlend);
			t_sample stereoWidthParam = ((m_h_stereoWidth_106 * ((t_sample)0.999)) + (m_f_ST_137 * ((t_sample)0.001)));
			t_sample next_stereoWidth = fixdenorm(stereoWidthParam);
			t_sample sub_25783 = (stereoWidthParam - ((int)0));
			t_sample scale_25780 = ((safepow((sub_25783 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample widthScale = scale_25780;
			t_sample lowFreqHz = ((m_h_lowFreqHz_105 * ((t_sample)0.999)) + (m_n_LOWFREQ_140 * ((t_sample)0.001)));
			t_sample next_lowFreqHz = fixdenorm(lowFreqHz);
			t_sample peakFreqHz = ((m_h_peakFreqHz_104 * ((t_sample)0.999)) + (m_o_PEAKFREQ_132 * ((t_sample)0.001)));
			t_sample next_peakFreqHz = fixdenorm(peakFreqHz);
			t_sample hiFreqHz = ((m_h_hiFreqHz_103 * ((t_sample)0.999)) + (m_p_HIFREQ_131 * ((t_sample)0.001)));
			t_sample next_hiFreqHz = fixdenorm(hiFreqHz);
			t_sample lowGainDb = ((m_h_lowGainDb_102 * ((t_sample)0.999)) + (m_h_LOWGAIN_125 * ((t_sample)0.001)));
			t_sample next_lowGainDb = fixdenorm(lowGainDb);
			t_sample peakGainDb = ((m_h_peakGainDb_101 * ((t_sample)0.999)) + (m_i_PEAKGAIN_144 * ((t_sample)0.001)));
			t_sample next_peakGainDb = fixdenorm(peakGainDb);
			t_sample hiGainDb = ((m_h_hiGainDb_100 * ((t_sample)0.999)) + (m_j_HIGAIN_133 * ((t_sample)0.001)));
			t_sample next_hiGainDb = fixdenorm(hiGainDb);
			t_sample inputTrimLin = ((m_h_inputTrim_99 * ((t_sample)0.999)) + (dbtoa(m_a_INPUT_135) * ((t_sample)0.001)));
			t_sample next_inputTrim = fixdenorm(inputTrimLin);
			t_sample leftRaw = in1;
			t_sample rightRaw = in2;
			t_sample leftTrimmed = (in1 * inputTrimLin);
			t_sample rightTrimmed = (in2 * inputTrimLin);
			t_sample inMonoRoute = ((leftTrimmed + rightTrimmed) * ((t_sample)0.5));
			t_sample mix_25784 = (leftTrimmed + (isMonoIn * (inMonoRoute - leftTrimmed)));
			t_sample ioL = mix_25784;
			t_sample mix_25785 = (rightTrimmed + (isMonoIn * (inMonoRoute - rightTrimmed)));
			t_sample ioR = mix_25785;
			t_sample inMonoRouteRaw = ((leftRaw + rightRaw) * ((t_sample)0.5));
			t_sample mix_25786 = (leftRaw + (isMonoIn * (inMonoRouteRaw - leftRaw)));
			t_sample mix_25787 = (rightRaw + (isMonoIn * (inMonoRouteRaw - rightRaw)));
			t_sample mix_25788 = (mix_25786 + (freezeBlend * (((int)0) - mix_25786)));
			t_sample mix_25789 = (mix_25787 + (freezeBlend * (((int)0) - mix_25787)));
			t_sample widthComplement = (((int)1) - stereoWidthParam);
			t_sample stereoSpreadMid = sqrt(widthComplement);
			t_sample stereoSpreadSide = sqrt(stereoWidthParam);
			t_sample sizeScalePrev = (m_h_sizeScale_98 * ((t_sample)0.999));
			t_sample sizeScaleSmoothed = (sizeInputScaled + sizeScalePrev);
			t_sample nextSizeScale = fixdenorm(sizeScaleSmoothed);
			t_sample mix_25790 = (sizeScaleSmoothed + (freezeOn * (((t_sample)0.999) - sizeScaleSmoothed)));
			t_sample sizeScaleEff = mix_25790;
			t_sample sizeScaleEff_25662 = ((((t_sample)0.999) < sizeScaleEff) ? ((t_sample)0.999) : sizeScaleEff);
			t_sample sizeScaleL = sizeScaleEff_25662;
			t_sample sizeScaleR = sizeScaleEff_25662;
			t_sample lpfPrev = (m_h_lpfHz_97 * ((t_sample)0.999));
			t_sample lpfHzSmoothed = (lpfInputScaled + lpfPrev);
			t_sample lpfHz = lpfHzSmoothed;
			t_sample nextLpfHz = fixdenorm(lpfHzSmoothed);
			t_sample hpfPrev = (m_h_hpfHz_96 * ((t_sample)0.999));
			t_sample hpfHzSmoothed = (hpfInputScaled + hpfPrev);
			t_sample hpfHz = hpfHzSmoothed;
			t_sample nextHpfHz = fixdenorm(hpfHzSmoothed);
			t_sample reflectPrev = (m_h_reflectCoef_95 * ((t_sample)0.999));
			t_sample reflectCoefSmoothed = (reflectInputScaled + reflectPrev);
			t_sample nextReflectCoef = fixdenorm(reflectCoefSmoothed);
			t_sample reflectCoef = reflectCoefSmoothed;
			t_sample offsetSamplesR = (((int)23) * sizeScaleR);
			t_sample mix_25791 = (stereoWidthParam + (isMonoOut * (((int)0) - stereoWidthParam)));
			t_sample widthControl = mix_25791;
			t_sample mix_25792 = (((int)0) + (widthControl * ((int)0)));
			t_sample baseOffsetL = mix_25792;
			t_sample mix_25793 = (((int)0) + (widthControl * (offsetSamplesR - ((int)0))));
			t_sample baseOffsetR = mix_25793;
			t_sample freezePrev = (m_h_freezeGate_94 * ((t_sample)0.999));
			t_sample freezeGateSmoothed = (freezeInputScaled + freezePrev);
			t_sample nextFreezeGate = fixdenorm(freezeGateSmoothed);
			t_sample preInputR = (ioR * (((int)1) - freezeOn));
			t_sample preInputL = (ioL * (((int)1) - freezeOn));
			t_sample return_201;
			t_sample return_202;
			eq3bandas_d_d_d_d_d_d_d_d_i(preInputL, preInputR, lowFreqHz, peakFreqHz, hiFreqHz, lowGainDb, peakGainDb, hiGainDb, ((int)1), return_201, return_202);
			t_sample preEQ_L_raw = return_201;
			t_sample preEQ_R_raw = return_202;
			t_sample mix_25794 = (preInputL + (eqEnabled * (preEQ_L_raw - preInputL)));
			t_sample preEQ_L = mix_25794;
			t_sample mix_25795 = (preInputR + (eqEnabled * (preEQ_R_raw - preInputR)));
			t_sample preEQ_R = mix_25795;
			t_sample pre_relSamps = (releaseMs * (samplerate * 0.001));
			t_sample pre_atkSamps = (attackMs * (samplerate * 0.001));
			t_sample preLeftTap = m_delay_preL_4.read_step(((int)300));
			t_sample preLeftEnergy = (preEQ_L * preEQ_L);
			t_sample preLeftAccum = (m_preL_accum_3 + preLeftEnergy);
			t_sample preLeftDiff = (preLeftAccum - preLeftTap);
			t_sample preLeftAvg = (preLeftDiff * ((t_sample)0.0033333333333333));
			t_sample preLeftRms = sqrt(preLeftAvg);
			t_sample preL_accum_next = fixdenorm(preLeftDiff);
			t_sample preLeftDb = atodb(preLeftRms);
			t_sample preLeftLvlDb = ((preLeftDb < ((int)-96)) ? ((int)-96) : preLeftDb);
			int preLeftOver = (preLeftLvlDb > thresholdDb);
			t_sample preLeftFlagSmoothed = ((m_preL_flag_2 * ((t_sample)0.999)) + (preLeftOver * ((t_sample)0.001)));
			t_sample preL_flag_s = preLeftFlagSmoothed;
			t_sample preLeftGainDb = ((thresholdDb - preLeftLvlDb) * (((int)1) - safediv(((int)1), ratio)));
			t_sample preLeftGainLin = dbtoa(preLeftGainDb);
			t_sample mix_25796 = (((int)1) + (preLeftOver * (preLeftGainLin - ((int)1))));
			t_sample preLeftEnvTarget = mix_25796;
			t_sample iup_204 = (1 / maximum(1, abs(pre_relSamps)));
			t_sample idown_205 = (1 / maximum(1, abs(pre_atkSamps)));
			__m_slide_203 = fixdenorm((__m_slide_203 + (((preLeftEnvTarget > __m_slide_203) ? iup_204 : idown_205) * (preLeftEnvTarget - __m_slide_203))));
			t_sample preLeftEnv = __m_slide_203;
			t_sample preL_out = ((preEQ_L * preLeftEnv) * dbtoa(makeupDb));
			t_sample preRightTap = m_delay_preR_7.read_step(((int)300));
			t_sample preRightEnergy = (preEQ_R * preEQ_R);
			t_sample preRightAccum = (m_preR_accum_6 + preRightEnergy);
			t_sample preRightDiff = (preRightAccum - preRightTap);
			t_sample preRightAvg = (preRightDiff * ((t_sample)0.0033333333333333));
			t_sample preRightRms = sqrt(preRightAvg);
			t_sample preR_accum_next = fixdenorm(preRightDiff);
			t_sample preRightDb = atodb(preRightRms);
			t_sample preRightLvlDb = ((preRightDb < ((int)-96)) ? ((int)-96) : preRightDb);
			int preRightOver = (preRightLvlDb > thresholdDb);
			t_sample preRightFlagSmoothed = ((m_preR_flag_5 * ((t_sample)0.999)) + (preRightOver * ((t_sample)0.001)));
			t_sample preR_flag_s = preRightFlagSmoothed;
			t_sample preRightGainDb = ((thresholdDb - preRightLvlDb) * (((int)1) - safediv(((int)1), ratio)));
			t_sample preRightGainLin = dbtoa(preRightGainDb);
			t_sample mix_25797 = (((int)1) + (preRightOver * (preRightGainLin - ((int)1))));
			t_sample preRightEnvTarget = mix_25797;
			t_sample iup_207 = (1 / maximum(1, abs(pre_relSamps)));
			t_sample idown_208 = (1 / maximum(1, abs(pre_atkSamps)));
			__m_slide_206 = fixdenorm((__m_slide_206 + (((preRightEnvTarget > __m_slide_206) ? iup_207 : idown_208) * (preRightEnvTarget - __m_slide_206))));
			t_sample preRightEnv = __m_slide_206;
			t_sample preR_out = ((preEQ_R * preRightEnv) * dbtoa(makeupDb));
			t_sample mix_25798 = (preEQ_R + (compEnableSmoothed * (preR_out - preEQ_R)));
			t_sample preR_proc = mix_25798;
			t_sample mix_25799 = (preEQ_L + (compEnableSmoothed * (preL_out - preEQ_L)));
			t_sample preL_proc = mix_25799;
			int prePostSwitch = (__m_change_209(m_x_PREPOST_124) != ((int)0));
			t_sample maxa_210 = (m_h_prepostGap_119 * ((t_sample)0.98));
			t_sample gapEnv = ((maxa_210 < prePostSwitch) ? prePostSwitch : maxa_210);
			t_sample next_prepostGap = fixdenorm(gapEnv);
			t_sample feedGate = (((int)1) - gapEnv);
			t_sample mix_25800 = (preInputR + (prePostBinary * (preR_proc - preInputR)));
			t_sample preInputR_sel = (mix_25800 * feedGate);
			t_sample mix_25801 = (preInputL + (prePostBinary * (preL_proc - preInputL)));
			t_sample preInputL_sel = (mix_25801 * feedGate);
			t_sample preFilterInR = preInputR_sel;
			t_sample preFilterInL = preInputL_sel;
			t_sample omega = safediv((lpfHz * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((int)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) - cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((((int)1) - cs) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample lpfA2 = a2;
			t_sample lpfA1 = a1;
			t_sample lpfA2_b = a2;
			t_sample lpfB1 = b1;
			t_sample lpfB2 = b2;
			t_sample omega_324 = safediv((hpfHz * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_325 = sin(omega_324);
			t_sample cs_326 = cos(omega_324);
			t_sample alpha_327 = ((sn_325 * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b_328 = safediv(((int)1), (((int)1) + alpha_327));
			t_sample a_329 = (((((int)1) + cs_326) * ((t_sample)0.5)) * b_328);
			t_sample a_330 = ((-(((int)1) + cs_326)) * b_328);
			t_sample b_331 = ((((int)-2) * cs_326) * b_328);
			t_sample b_332 = ((((int)1) - alpha_327) * b_328);
			t_sample hpfA2 = a_329;
			t_sample hpfA1 = a_330;
			t_sample hpfA2_b = a_329;
			t_sample hpfB1 = b_331;
			t_sample hpfB2 = b_332;
			t_sample lpfOutL = ((((preFilterInL * lpfA2) + (m_history_89 * lpfA1)) + (m_history_92 * lpfA2_b)) - ((m_history_86 * lpfB1) + (m_history_90 * lpfB2)));
			t_sample lpfOutR = ((((preFilterInR * lpfA2) + (m_history_88 * lpfA1)) + (m_history_93 * lpfA2_b)) - ((m_history_87 * lpfB1) + (m_history_91 * lpfB2)));
			t_sample history_33_next_352 = fixdenorm(m_history_88);
			t_sample history_34_next_353 = fixdenorm(m_history_89);
			t_sample history_35_next_354 = fixdenorm(m_history_87);
			t_sample history_36_next_355 = fixdenorm(m_history_86);
			t_sample nextPreInputL = fixdenorm(preInputL_sel);
			t_sample nextPreInputR = fixdenorm(preInputR_sel);
			t_sample nextLpfOutR = fixdenorm(lpfOutR);
			t_sample nextLpfOutL = fixdenorm(lpfOutL);
			t_sample hpfOutR = ((((lpfOutR * hpfA2) + (m_history_81 * hpfA1)) + (m_history_82 * hpfA2_b)) - ((m_history_79 * hpfB1) + (m_history_85 * hpfB2)));
			t_sample hpfOutL = ((((lpfOutL * hpfA2) + (m_history_80 * hpfA1)) + (m_history_84 * hpfA2_b)) - ((m_history_78 * hpfB1) + (m_history_83 * hpfB2)));
			t_sample history_41_next_374 = fixdenorm(m_history_79);
			t_sample history_42_next_375 = fixdenorm(m_history_80);
			t_sample history_43_next_376 = fixdenorm(m_history_78);
			t_sample history_44_next_377 = fixdenorm(m_history_81);
			t_sample history_45_next_378 = fixdenorm(lpfOutR);
			t_sample history_46_next_379 = fixdenorm(lpfOutL);
			t_sample history_47_next_380 = fixdenorm(hpfOutR);
			t_sample history_48_next_381 = fixdenorm(hpfOutL);
			t_sample combScaleL = (sampleRateScaleL * sizeScaleL);
			t_sample combDelayL1Scaled = (((int)1491) * combScaleL);
			t_sample combDelayL1Smoothed = ((m_h_combDelayL_77 * ((t_sample)0.999)) + (combDelayL1Scaled * ((t_sample)0.001)));
			t_sample next_combDelayL1 = fixdenorm(combDelayL1Smoothed);
			t_sample combDelayL2Scaled = (((int)1617) * combScaleL);
			t_sample combDelayL2Smoothed = ((m_h_combDelayL_76 * ((t_sample)0.999)) + (combDelayL2Scaled * ((t_sample)0.001)));
			t_sample next_combDelayL2 = fixdenorm(combDelayL2Smoothed);
			t_sample combDelayL3Scaled = (((int)1188) * combScaleL);
			t_sample combDelayL3Smoothed = ((m_h_combDelayL_75 * ((t_sample)0.999)) + (combDelayL3Scaled * ((t_sample)0.001)));
			t_sample next_combDelayL3 = fixdenorm(combDelayL3Smoothed);
			t_sample combDelayL4Scaled = (((int)1116) * combScaleL);
			t_sample combDelayL4Smoothed = ((m_h_combDelayL_74 * ((t_sample)0.999)) + (combDelayL4Scaled * ((t_sample)0.001)));
			t_sample next_combDelayL4 = fixdenorm(combDelayL4Smoothed);
			t_sample combDelayL5Scaled = (((int)1557) * combScaleL);
			t_sample combDelayL5Smoothed = ((m_h_combDelayL_73 * ((t_sample)0.999)) + (combDelayL5Scaled * ((t_sample)0.001)));
			t_sample next_combDelayL5 = fixdenorm(combDelayL5Smoothed);
			t_sample combDelayL6Scaled = (((int)1356) * combScaleL);
			t_sample combDelayL6Smoothed = ((m_h_combDelayL_72 * ((t_sample)0.999)) + (combDelayL6Scaled * ((t_sample)0.001)));
			t_sample next_combDelayL6 = fixdenorm(combDelayL6Smoothed);
			t_sample combDelayL7Scaled = (((int)1422) * combScaleL);
			t_sample combDelayL7Smoothed = ((m_h_combDelayL_71 * ((t_sample)0.999)) + (combDelayL7Scaled * ((t_sample)0.001)));
			t_sample next_combDelayL7 = fixdenorm(combDelayL7Smoothed);
			t_sample combDelayL8Scaled = (((int)1277) * combScaleL);
			t_sample combDelayL8Smoothed = ((m_h_combDelayL_70 * ((t_sample)0.999)) + (combDelayL8Scaled * ((t_sample)0.001)));
			t_sample next_combDelayL8 = fixdenorm(combDelayL8Smoothed);
			t_sample combL1FeedbackScaled = (m_h_combStateL_68 * leftCombPass);
			t_sample delayOffsetL1Samples = combDelayL4Smoothed;
			t_sample v_211 = (baseOffsetL + delayOffsetL1Samples);
			t_sample combL1DelayOffset = ((v_211 <= ((int)0)) ? ((int)0) : ((v_211 >= max_212) ? max_212 : v_211));
			t_sample combL1Tap = m_delay_69.read_linear(combL1DelayOffset);
			t_sample combL1TapScaled = (combL1Tap * leftCombLeak);
			t_sample combL1Mix = (combL1TapScaled + combL1FeedbackScaled);
			t_sample combL1Feedforward = (combL1Mix * reflectCoef);
			t_sample combL1Sum = (hpfOutL + combL1Feedforward);
			t_sample combL1Out = combL1Sum;
			t_sample next_combStateL1 = fixdenorm(combL1Mix);
			t_sample combL2FeedbackScaled = (m_h_combStateL_66 * leftCombPass);
			t_sample delayOffsetL2Samples = combDelayL3Smoothed;
			t_sample v_213 = (baseOffsetL + delayOffsetL2Samples);
			t_sample combL2DelayOffset = ((v_213 <= ((int)0)) ? ((int)0) : ((v_213 >= max_214) ? max_214 : v_213));
			t_sample combL2Tap = m_delay_67.read_linear(combL2DelayOffset);
			t_sample combL2TapScaled = (combL2Tap * leftCombLeak);
			t_sample combL2Mix = (combL2TapScaled + combL2FeedbackScaled);
			t_sample combL2Feedforward = (combL2Mix * reflectCoef);
			t_sample combL2Sum = (hpfOutL + combL2Feedforward);
			t_sample combL2Out = combL2Sum;
			t_sample next_combStateL2 = fixdenorm(combL2Mix);
			t_sample combL3FeedbackScaled = (m_h_combStateL_64 * leftCombPass);
			t_sample delayOffsetL3Samples = combDelayL6Smoothed;
			t_sample v_215 = (baseOffsetL + delayOffsetL3Samples);
			t_sample combL3DelayOffset = ((v_215 <= ((int)0)) ? ((int)0) : ((v_215 >= max_216) ? max_216 : v_215));
			t_sample combL3Tap = m_delay_65.read_linear(combL3DelayOffset);
			t_sample combL3TapScaled = (combL3Tap * leftCombLeak);
			t_sample combL3Mix = (combL3TapScaled + combL3FeedbackScaled);
			t_sample combL3Feedforward = (combL3Mix * reflectCoef);
			t_sample combL3Sum = (hpfOutL + combL3Feedforward);
			t_sample combL3Out = combL3Sum;
			t_sample next_combStateL3 = fixdenorm(combL3Mix);
			t_sample combL4FeedbackScaled = (m_h_combStateL_62 * leftCombPass);
			t_sample delayOffsetL4Samples = combDelayL8Smoothed;
			t_sample v_217 = (baseOffsetL + delayOffsetL4Samples);
			t_sample combL4DelayOffset = ((v_217 <= ((int)0)) ? ((int)0) : ((v_217 >= max_218) ? max_218 : v_217));
			t_sample combL4Tap = m_delay_63.read_linear(combL4DelayOffset);
			t_sample combL4TapScaled = (combL4Tap * leftCombLeak);
			t_sample combL4Mix = (combL4TapScaled + combL4FeedbackScaled);
			t_sample combL4Feedforward = (combL4Mix * reflectCoef);
			t_sample combL4Sum = (hpfOutL + combL4Feedforward);
			t_sample combL4Out = combL4Sum;
			t_sample next_combStateL4 = fixdenorm(combL4Mix);
			t_sample combL5FeedbackScaled = (m_h_combStateL_60 * leftCombPass);
			t_sample delayOffsetL5Samples = combDelayL7Smoothed;
			t_sample v_219 = (baseOffsetL + delayOffsetL5Samples);
			t_sample combL5DelayOffset = ((v_219 <= ((int)0)) ? ((int)0) : ((v_219 >= max_220) ? max_220 : v_219));
			t_sample combL5Tap = m_delay_61.read_linear(combL5DelayOffset);
			t_sample combL5TapScaled = (combL5Tap * leftCombLeak);
			t_sample combL5Mix = (combL5TapScaled + combL5FeedbackScaled);
			t_sample combL5Feedforward = (combL5Mix * reflectCoef);
			t_sample combL5Sum = (hpfOutL + combL5Feedforward);
			t_sample combL5Out = combL5Sum;
			t_sample next_combStateL5 = fixdenorm(combL5Mix);
			t_sample combL6FeedbackScaled = (m_h_combStateL_58 * leftCombPass);
			t_sample delayOffsetL6Samples = combDelayL1Smoothed;
			t_sample v_221 = (baseOffsetL + delayOffsetL6Samples);
			t_sample combL6DelayOffset = ((v_221 <= ((int)0)) ? ((int)0) : ((v_221 >= max_222) ? max_222 : v_221));
			t_sample combL6Tap = m_delay_59.read_linear(combL6DelayOffset);
			t_sample combL6TapScaled = (combL6Tap * leftCombLeak);
			t_sample combL6Mix = (combL6TapScaled + combL6FeedbackScaled);
			t_sample combL6Feedforward = (combL6Mix * reflectCoef);
			t_sample combL6Sum = (hpfOutL + combL6Feedforward);
			t_sample combL6Out = combL6Sum;
			t_sample next_combStateL6 = fixdenorm(combL6Mix);
			t_sample combL7FeedbackScaled = (m_h_combStateL_56 * leftCombPass);
			t_sample delayOffsetL7Samples = combDelayL2Smoothed;
			t_sample v_223 = (baseOffsetL + delayOffsetL7Samples);
			t_sample combL7DelayOffset = ((v_223 <= ((int)0)) ? ((int)0) : ((v_223 >= max_224) ? max_224 : v_223));
			t_sample combL7Tap = m_delay_57.read_linear(combL7DelayOffset);
			t_sample combL7TapScaled = (combL7Tap * leftCombLeak);
			t_sample combL7Mix = (combL7TapScaled + combL7FeedbackScaled);
			t_sample combL7Feedforward = (combL7Mix * reflectCoef);
			t_sample combL7Sum = (hpfOutL + combL7Feedforward);
			t_sample combL7Out = combL7Sum;
			t_sample next_combStateL7 = fixdenorm(combL7Mix);
			t_sample combL8FeedbackScaled = (m_h_combStateL_54 * leftCombPass);
			t_sample delayOffsetL8Samples = combDelayL5Smoothed;
			t_sample v_225 = (baseOffsetL + delayOffsetL8Samples);
			t_sample combL8DelayOffset = ((v_225 <= ((int)0)) ? ((int)0) : ((v_225 >= max_226) ? max_226 : v_225));
			t_sample combL8Tap = m_delay_55.read_linear(combL8DelayOffset);
			t_sample combL8TapScaled = (combL8Tap * leftCombLeak);
			t_sample combL8Mix = (combL8TapScaled + combL8FeedbackScaled);
			t_sample combL8Feedforward = (combL8Mix * reflectCoef);
			t_sample combL8Sum = (hpfOutL + combL8Feedforward);
			t_sample combL8Out = combL8Sum;
			t_sample next_combStateL8 = fixdenorm(combL8Mix);
			t_sample combMixLeft = ((((((((combL8Out + combL7Out) + combL6Out) + combL5Out) + combL4Out) + combL3Out) + combL2Out) + combL1Out) * ((t_sample)0.125));
			t_sample earlyLeft = combMixLeft;
			t_sample apScaleL = (sampleRateScaleAP_L * sizeScaleEff_25662);
			t_sample apL1DelaySamples = (((int)255) * apScaleL);
			t_sample v_227 = (((int)0) + apL1DelaySamples);
			t_sample apL1DelayOffset = ((v_227 <= ((int)0)) ? ((int)0) : ((v_227 >= max_228) ? max_228 : v_227));
			t_sample apL1TapA = m_delay_53.read_linear(apL1DelayOffset);
			t_sample apL1TapB = m_delay_52.read_linear(apL1DelayOffset);
			t_sample apL1Sum = ((earlyLeft * ((t_sample)-0.5)) + (apL1TapA + (apL1TapB * ((t_sample)0.5))));
			t_sample apL1 = apL1Sum;
			t_sample apL2DelaySamples = (((int)556) * apScaleL);
			t_sample v_229 = (((int)0) + apL2DelaySamples);
			t_sample apL2DelayOffset = ((v_229 <= ((int)0)) ? ((int)0) : ((v_229 >= max_230) ? max_230 : v_229));
			t_sample apL2TapA = m_delay_51.read_linear(apL2DelayOffset);
			t_sample apL2TapB = m_delay_50.read_linear(apL2DelayOffset);
			t_sample apL2Sum = ((apL1 * ((t_sample)-0.5)) + (apL2TapA + (apL2TapB * ((t_sample)0.5))));
			t_sample apL2 = apL2Sum;
			t_sample apL3DelaySamples = (((int)441) * apScaleL);
			t_sample v_231 = (((int)0) + apL3DelaySamples);
			t_sample apL3DelayOffset = ((v_231 <= ((int)0)) ? ((int)0) : ((v_231 >= max_232) ? max_232 : v_231));
			t_sample apL3TapA = m_delay_49.read_linear(apL3DelayOffset);
			t_sample apL3TapB = m_delay_48.read_linear(apL3DelayOffset);
			t_sample apL3Sum = ((apL2 * ((t_sample)-0.5)) + (apL3TapA + (apL3TapB * ((t_sample)0.5))));
			t_sample apL3 = apL3Sum;
			t_sample apL4DelaySamples = (((int)341) * apScaleL);
			t_sample v_233 = (((int)0) + apL4DelaySamples);
			t_sample apL4DelayOffset = ((v_233 <= ((int)0)) ? ((int)0) : ((v_233 >= max_234) ? max_234 : v_233));
			t_sample apL4TapA = m_delay_47.read_linear(apL4DelayOffset);
			t_sample apL4TapB = m_delay_46.read_linear(apL4DelayOffset);
			t_sample apL4Sum = ((apL3 * ((t_sample)-0.5)) + (apL4TapA + (apL4TapB * ((t_sample)0.5))));
			t_sample apL4 = apL4Sum;
			t_sample msInLeft = apL4;
			t_sample combScaleR = (sampleRateScaleR * sizeScaleR);
			t_sample combDelayR1Scaled = (((int)1422) * combScaleR);
			t_sample combDelayR1Smoothed = ((m_h_combDelayR_45 * ((t_sample)0.999)) + (combDelayR1Scaled * ((t_sample)0.001)));
			t_sample next_combDelayR1 = fixdenorm(combDelayR1Smoothed);
			t_sample combDelayR2Scaled = (((int)1491) * combScaleR);
			t_sample combDelayR2Smoothed = ((m_h_combDelayR_44 * ((t_sample)0.999)) + (combDelayR2Scaled * ((t_sample)0.001)));
			t_sample next_combDelayR2 = fixdenorm(combDelayR2Smoothed);
			t_sample combDelayR3Scaled = (((int)1116) * combScaleR);
			t_sample combDelayR3Smoothed = ((m_h_combDelayR_43 * ((t_sample)0.999)) + (combDelayR3Scaled * ((t_sample)0.001)));
			t_sample next_combDelayR3 = fixdenorm(combDelayR3Smoothed);
			t_sample combDelayR4Scaled = (((int)1188) * combScaleR);
			t_sample combDelayR4Smoothed = ((m_h_combDelayR_42 * ((t_sample)0.999)) + (combDelayR4Scaled * ((t_sample)0.001)));
			t_sample next_combDelayR4 = fixdenorm(combDelayR4Smoothed);
			t_sample combDelayR5Scaled = (((int)1617) * combScaleR);
			t_sample combDelayR5Smoothed = ((m_h_combDelayR_41 * ((t_sample)0.999)) + (combDelayR5Scaled * ((t_sample)0.001)));
			t_sample next_combDelayR5 = fixdenorm(combDelayR5Smoothed);
			t_sample combDelayR6Scaled = (((int)1356) * combScaleR);
			t_sample combDelayR6Smoothed = ((m_h_combDelayR_40 * ((t_sample)0.999)) + (combDelayR6Scaled * ((t_sample)0.001)));
			t_sample next_combDelayR6 = fixdenorm(combDelayR6Smoothed);
			t_sample combDelayR7Scaled = (((int)1277) * combScaleR);
			t_sample combDelayR7Smoothed = ((m_h_combDelayR_39 * ((t_sample)0.999)) + (combDelayR7Scaled * ((t_sample)0.001)));
			t_sample next_combDelayR7 = fixdenorm(combDelayR7Smoothed);
			t_sample combDelayR8Scaled = (((int)1557) * combScaleR);
			t_sample combDelayR8Smoothed = ((m_h_combDelayR_38 * ((t_sample)0.999)) + (combDelayR8Scaled * ((t_sample)0.001)));
			t_sample next_combDelayR8 = fixdenorm(combDelayR8Smoothed);
			t_sample combR1FeedbackScaled = (m_h_combStateR_36 * rightCombPass);
			t_sample delayOffsetR1Samples = combDelayR3Smoothed;
			t_sample v_235 = (baseOffsetR + delayOffsetR1Samples);
			t_sample combR1DelayOffset = ((v_235 <= ((int)0)) ? ((int)0) : ((v_235 >= max_236) ? max_236 : v_235));
			t_sample combR1Tap = m_delay_37.read_linear(combR1DelayOffset);
			t_sample combR1TapScaled = (combR1Tap * rightCombLeak);
			t_sample combR1Mix = (combR1TapScaled + combR1FeedbackScaled);
			t_sample combR1Feedforward = (combR1Mix * reflectCoef);
			t_sample combR1Sum = (hpfOutR + combR1Feedforward);
			t_sample combR1Out = combR1Sum;
			t_sample next_combStateR1 = fixdenorm(combR1Mix);
			t_sample combR2FeedbackScaled = (m_h_combStateR_34 * rightCombPass);
			t_sample delayOffsetR2Samples = combDelayR4Smoothed;
			t_sample v_237 = (baseOffsetR + delayOffsetR2Samples);
			t_sample combR2DelayOffset = ((v_237 <= ((int)0)) ? ((int)0) : ((v_237 >= max_238) ? max_238 : v_237));
			t_sample combR2Tap = m_delay_35.read_linear(combR2DelayOffset);
			t_sample combR2TapScaled = (combR2Tap * rightCombLeak);
			t_sample combR2Mix = (combR2TapScaled + combR2FeedbackScaled);
			t_sample combR2Feedforward = (combR2Mix * reflectCoef);
			t_sample combR2Sum = (hpfOutR + combR2Feedforward);
			t_sample combR2Out = combR2Sum;
			t_sample next_combStateR2 = fixdenorm(combR2Mix);
			t_sample combR3FeedbackScaled = (m_h_combStateR_32 * rightCombPass);
			t_sample delayOffsetR3Samples = combDelayR6Smoothed;
			t_sample v_239 = (baseOffsetR + delayOffsetR3Samples);
			t_sample combR3DelayOffset = ((v_239 <= ((int)0)) ? ((int)0) : ((v_239 >= max_240) ? max_240 : v_239));
			t_sample combR3Tap = m_delay_33.read_linear(combR3DelayOffset);
			t_sample combR3TapScaled = (combR3Tap * rightCombLeak);
			t_sample combR3Mix = (combR3TapScaled + combR3FeedbackScaled);
			t_sample combR3Feedforward = (combR3Mix * reflectCoef);
			t_sample combR3Sum = (hpfOutR + combR3Feedforward);
			t_sample combR3Out = combR3Sum;
			t_sample next_combStateR3 = fixdenorm(combR3Mix);
			t_sample combR4FeedbackScaled = (m_h_combStateR_30 * rightCombPass);
			t_sample delayOffsetR4Samples = combDelayR7Smoothed;
			t_sample v_241 = (baseOffsetR + delayOffsetR4Samples);
			t_sample combR4DelayOffset = ((v_241 <= ((int)0)) ? ((int)0) : ((v_241 >= max_242) ? max_242 : v_241));
			t_sample combR4Tap = m_delay_31.read_linear(combR4DelayOffset);
			t_sample combR4TapScaled = (combR4Tap * rightCombLeak);
			t_sample combR4Mix = (combR4TapScaled + combR4FeedbackScaled);
			t_sample combR4Feedforward = (combR4Mix * reflectCoef);
			t_sample combR4Sum = (hpfOutR + combR4Feedforward);
			t_sample combR4Out = combR4Sum;
			t_sample next_combStateR4 = fixdenorm(combR4Mix);
			t_sample combR5FeedbackScaled = (m_h_combStateR_28 * rightCombPass);
			t_sample delayOffsetR5Samples = combDelayR1Smoothed;
			t_sample v_243 = (baseOffsetR + delayOffsetR5Samples);
			t_sample combR5DelayOffset = ((v_243 <= ((int)0)) ? ((int)0) : ((v_243 >= max_244) ? max_244 : v_243));
			t_sample combR5Tap = m_delay_29.read_linear(combR5DelayOffset);
			t_sample combR5TapScaled = (combR5Tap * rightCombLeak);
			t_sample combR5Mix = (combR5TapScaled + combR5FeedbackScaled);
			t_sample combR5Feedforward = (combR5Mix * reflectCoef);
			t_sample combR5Sum = (hpfOutR + combR5Feedforward);
			t_sample combR5Out = combR5Sum;
			t_sample next_combStateR5 = fixdenorm(combR5Mix);
			t_sample combR6FeedbackScaled = (m_h_combStateR_26 * rightCombPass);
			t_sample delayOffsetR6Samples = combDelayR2Smoothed;
			t_sample v_245 = (baseOffsetR + delayOffsetR6Samples);
			t_sample combR6DelayOffset = ((v_245 <= ((int)0)) ? ((int)0) : ((v_245 >= max_246) ? max_246 : v_245));
			t_sample combR6Tap = m_delay_27.read_linear(combR6DelayOffset);
			t_sample combR6TapScaled = (combR6Tap * rightCombLeak);
			t_sample combR6Mix = (combR6TapScaled + combR6FeedbackScaled);
			t_sample combR6Feedforward = (combR6Mix * reflectCoef);
			t_sample combR6Sum = (hpfOutR + combR6Feedforward);
			t_sample combR6Out = combR6Sum;
			t_sample next_combStateR6 = fixdenorm(combR6Mix);
			t_sample combR7FeedbackScaled = (m_h_combStateR_24 * rightCombPass);
			t_sample delayOffsetR7Samples = combDelayR5Smoothed;
			t_sample v_247 = (baseOffsetR + delayOffsetR7Samples);
			t_sample combR7DelayOffset = ((v_247 <= ((int)0)) ? ((int)0) : ((v_247 >= max_248) ? max_248 : v_247));
			t_sample combR7Tap = m_delay_25.read_linear(combR7DelayOffset);
			t_sample combR7TapScaled = (combR7Tap * rightCombLeak);
			t_sample combR7Mix = (combR7TapScaled + combR7FeedbackScaled);
			t_sample combR7Feedforward = (combR7Mix * reflectCoef);
			t_sample combR7Sum = (hpfOutR + combR7Feedforward);
			t_sample combR7Out = combR7Sum;
			t_sample next_combStateR7 = fixdenorm(combR7Mix);
			t_sample combR8FeedbackScaled = (m_h_combStateR_22 * rightCombPass);
			t_sample delayOffsetR8Samples = combDelayR8Smoothed;
			t_sample v_249 = (baseOffsetR + delayOffsetR8Samples);
			t_sample combR8DelayOffset = ((v_249 <= ((int)0)) ? ((int)0) : ((v_249 >= max_250) ? max_250 : v_249));
			t_sample combR8Tap = m_delay_23.read_linear(combR8DelayOffset);
			t_sample combR8TapScaled = (combR8Tap * rightCombLeak);
			t_sample combR8Mix = (combR8TapScaled + combR8FeedbackScaled);
			t_sample combR8Feedforward = (combR8Mix * reflectCoef);
			t_sample combR8Sum = (hpfOutR + combR8Feedforward);
			t_sample combR8Out = combR8Sum;
			t_sample next_combStateR8 = fixdenorm(combR8Mix);
			t_sample combMixRight = ((((((((combR8Out + combR7Out) + combR6Out) + combR5Out) + combR4Out) + combR3Out) + combR2Out) + combR1Out) * ((t_sample)0.125));
			t_sample earlyRight = combMixRight;
			t_sample apScaleR = (sampleRateScaleAP_R * sizeScaleEff_25662);
			t_sample apR1DelaySamples = (((int)255) * apScaleR);
			t_sample apR1DelayOffset = (((int)0) + apR1DelaySamples);
			t_sample apR1TapA = m_delay_21.read_linear(apR1DelayOffset);
			t_sample apR1TapB = m_delay_20.read_linear(apR1DelayOffset);
			t_sample apR1Sum = ((earlyRight * ((t_sample)-0.5)) + (apR1TapA + (apR1TapB * ((t_sample)0.5))));
			t_sample apR1 = apR1Sum;
			t_sample apR2DelaySamples = (((int)556) * apScaleR);
			t_sample v_251 = (((int)0) + apR2DelaySamples);
			t_sample apR2DelayOffset = ((v_251 <= ((int)0)) ? ((int)0) : ((v_251 >= max_252) ? max_252 : v_251));
			t_sample apR2TapA = m_delay_19.read_linear(apR2DelayOffset);
			t_sample apR2TapB = m_delay_18.read_linear(apR2DelayOffset);
			t_sample apR2Sum = ((apR1 * ((t_sample)-0.5)) + (apR2TapA + (apR2TapB * ((t_sample)0.5))));
			t_sample apR2 = apR2Sum;
			t_sample apR3DelaySamples = (((int)441) * apScaleR);
			t_sample v_253 = (((int)0) + apR3DelaySamples);
			t_sample apR3DelayOffset = ((v_253 <= ((int)0)) ? ((int)0) : ((v_253 >= max_254) ? max_254 : v_253));
			t_sample apR3TapA = m_delay_17.read_linear(apR3DelayOffset);
			t_sample apR3TapB = m_delay_16.read_linear(apR3DelayOffset);
			t_sample apR3Sum = ((apR2 * ((t_sample)-0.5)) + (apR3TapA + (apR3TapB * ((t_sample)0.5))));
			t_sample apR3 = apR3Sum;
			t_sample apR4DelaySamples = (((int)341) * apScaleR);
			t_sample v_255 = (((int)0) + apR4DelaySamples);
			t_sample apR4DelayOffset = ((v_255 <= ((int)0)) ? ((int)0) : ((v_255 >= max_256) ? max_256 : v_255));
			t_sample apR4TapA = m_delay_15.read_linear(apR4DelayOffset);
			t_sample apR4TapB = m_delay_14.read_linear(apR4DelayOffset);
			t_sample apR4Sum = ((apR3 * ((t_sample)-0.5)) + (apR4TapA + (apR4TapB * ((t_sample)0.5))));
			t_sample apR4 = apR4Sum;
			t_sample msInRight = apR4;
			t_sample msMidRaw = (msInLeft + msInRight);
			t_sample msMid = (msMidRaw * stereoSpreadMid);
			t_sample msSideRaw = (msInLeft - msInRight);
			t_sample msSide = (msSideRaw * stereoSpreadSide);
			t_sample msLeftPreWidth = (msMid + msSide);
			t_sample msLeft = (msLeftPreWidth * widthScale);
			t_sample msRightPreWidth = (msMid - msSide);
			t_sample msRight = (msRightPreWidth * widthScale);
			t_sample wetPreLeft = msLeft;
			t_sample wetPreRight = msRight;
			t_sample return_316;
			t_sample return_317;
			eq3bandas_d_d_d_d_d_d_d_d_i_257(wetPreLeft, wetPreRight, lowFreqHz, peakFreqHz, hiFreqHz, lowGainDb, peakGainDb, hiGainDb, ((int)1), return_316, return_317);
			t_sample eqPostLeftRaw = return_316;
			t_sample eqPostRightRaw = return_317;
			t_sample mul_25803 = (eqEnabled * (((int)1) - prePostBinary));
			t_sample mix_25802 = (msLeft + (mul_25803 * (eqPostLeftRaw - msLeft)));
			t_sample postEqLeft = mix_25802;
			t_sample mul_25805 = (eqEnabled * (((int)1) - prePostBinary));
			t_sample mix_25804 = (msRight + (mul_25805 * (eqPostRightRaw - msRight)));
			t_sample postEqRight = mix_25804;
			t_sample makeupGainLin = dbtoa(makeupDb);
			t_sample releaseSamps = (releaseMs * (samplerate * 0.001));
			t_sample attackSamps = (attackMs * (samplerate * 0.001));
			t_sample rightTap = m_delay_13.read_step(((int)300));
			t_sample rightEnergy = (postEqRight * postEqRight);
			t_sample rightAccumPrev = m_h_postRightAccum_12;
			t_sample rightAccum = (rightAccumPrev + rightEnergy);
			t_sample rightDiff = (rightAccum - rightTap);
			t_sample rightAvg = (rightDiff * ((t_sample)0.0033333333333333));
			t_sample rightRms = sqrt(rightAvg);
			t_sample next_postRightAccum = fixdenorm(rightDiff);
			t_sample rightDb = atodb(rightRms);
			t_sample rightLvlDb = ((rightDb < ((int)-96)) ? ((int)-96) : rightDb);
			int rightOver = (rightLvlDb > thresholdDb);
			t_sample rightOverFlagPrev = m_h_postRightOverFlag_11;
			t_sample rightOverSmoothed = ((rightOverFlagPrev * ((t_sample)0.999)) + (rightOver * ((t_sample)0.001)));
			t_sample next_postRightOverFlag = fixdenorm(rightOverSmoothed);
			t_sample rightGainDb = ((thresholdDb - rightLvlDb) * (((int)1) - safediv(((int)1), ratio)));
			t_sample rightGainLin = dbtoa(rightGainDb);
			t_sample mix_25806 = (((int)1) + (rightOver * (rightGainLin - ((int)1))));
			t_sample iup_319 = (1 / maximum(1, abs(releaseSamps)));
			t_sample idown_320 = (1 / maximum(1, abs(attackSamps)));
			__m_slide_318 = fixdenorm((__m_slide_318 + (((mix_25806 > __m_slide_318) ? iup_319 : idown_320) * (mix_25806 - __m_slide_318))));
			t_sample rightEnv = __m_slide_318;
			t_sample compRight = ((postEqRight * rightEnv) * makeupGainLin);
			t_sample leftTap = m_delay_10.read_step(((int)300));
			t_sample leftEnergy = (postEqLeft * postEqLeft);
			t_sample leftAccumPrev = m_h_postLeftAccum_9;
			t_sample leftAccum = (leftAccumPrev + leftEnergy);
			t_sample leftDiff = (leftAccum - leftTap);
			t_sample leftAvg = (leftDiff * ((t_sample)0.0033333333333333));
			t_sample leftRms = sqrt(leftAvg);
			t_sample next_postLeftAccum = fixdenorm(leftDiff);
			t_sample leftDb = atodb(leftRms);
			t_sample leftLvlDb = ((leftDb < ((int)-96)) ? ((int)-96) : leftDb);
			int leftOver = (leftLvlDb > thresholdDb);
			t_sample leftOverFlagPrev = m_h_postLeftOverFlag_8;
			t_sample leftOverSmoothed = ((leftOverFlagPrev * ((t_sample)0.999)) + (leftOver * ((t_sample)0.001)));
			t_sample next_postLeftOverFlag = fixdenorm(leftOverSmoothed);
			t_sample leftGainDb = ((thresholdDb - leftLvlDb) * (((int)1) - safediv(((int)1), ratio)));
			t_sample leftGainLin = dbtoa(leftGainDb);
			t_sample mix_25807 = (((int)1) + (leftOver * (leftGainLin - ((int)1))));
			t_sample iup_322 = (1 / maximum(1, abs(releaseSamps)));
			t_sample idown_323 = (1 / maximum(1, abs(attackSamps)));
			__m_slide_321 = fixdenorm((__m_slide_321 + (((mix_25807 > __m_slide_321) ? iup_322 : idown_323) * (mix_25807 - __m_slide_321))));
			t_sample leftEnv = __m_slide_321;
			t_sample compLeft = ((postEqLeft * leftEnv) * makeupGainLin);
			t_sample mul_25809 = (compEnableSmoothed * (((int)1) - prePostBinary));
			t_sample mix_25808 = (postEqLeft + (mul_25809 * (compLeft - postEqLeft)));
			t_sample mul_25811 = (compEnableSmoothed * (((int)1) - prePostBinary));
			t_sample mix_25810 = (postEqRight + (mul_25811 * (compRight - postEqRight)));
			t_sample wetOutL = (mix_25808 * outputTrimLin);
			t_sample wetOutR = (mix_25810 * outputTrimLin);
			t_sample wetClipL = (((t_sample)0.63661977236758) * tanh(wetOutL));
			t_sample wetClipR = (((t_sample)0.63661977236758) * tanh(wetOutR));
			t_sample mix_25812 = (wetOutL + (softclipEnabled * (wetClipL - wetOutL)));
			t_sample mix_25813 = (wetOutR + (softclipEnabled * (wetClipR - wetOutR)));
			t_sample mix_25814 = (mix_25788 + (dryWet_25661 * (mix_25812 - mix_25788)));
			t_sample mix_25815 = (mix_25789 + (dryWet_25661 * (mix_25813 - mix_25789)));
			t_sample mix_25816 = (mix_25814 + (bypassSmoothed * (mix_25788 - mix_25814)));
			t_sample dcblockLeft = __m_dcblock_324(mix_25816);
			t_sample mix_25817 = (mix_25815 + (bypassSmoothed * (mix_25789 - mix_25815)));
			t_sample dcblockRight = __m_dcblock_325(mix_25817);
			t_sample outMono = ((dcblockLeft + dcblockRight) * ((t_sample)0.5));
			t_sample mix_25818 = (dcblockLeft + (isMonoOut * (outMono - dcblockLeft)));
			t_sample mix_25819 = (dcblockRight + (isMonoOut * (outMono - dcblockRight)));
			m_delay_preR_7.write(preRightEnergy);
			m_preR_accum_6 = preR_accum_next;
			m_preR_flag_5 = fixdenorm(preR_flag_s);
			m_delay_preL_4.write(preLeftEnergy);
			m_preL_accum_3 = preL_accum_next;
			m_preL_flag_2 = fixdenorm(preL_flag_s);
			m_h_outputTrim_120 = next_outputTrim;
			m_h_postLeftOverFlag_8 = next_postLeftOverFlag;
			m_h_postLeftAccum_9 = next_postLeftAccum;
			m_delay_10.write(leftEnergy);
			m_h_postRightOverFlag_11 = next_postRightOverFlag;
			m_h_postRightAccum_12 = next_postRightAccum;
			m_delay_13.write(rightEnergy);
			m_delay_20.write(apR1Sum);
			m_delay_19.write(apR1);
			m_delay_18.write(apR2Sum);
			m_delay_17.write(apR2);
			m_delay_16.write(apR3Sum);
			m_delay_15.write(apR3);
			m_delay_14.write(apR4Sum);
			m_delay_21.write(earlyRight);
			m_h_combDelayR_38 = next_combDelayR8;
			m_h_combDelayR_39 = next_combDelayR7;
			m_h_combDelayR_40 = next_combDelayR6;
			m_h_combDelayR_41 = next_combDelayR5;
			m_h_combDelayR_42 = next_combDelayR4;
			m_h_combDelayR_43 = next_combDelayR3;
			m_h_combDelayR_44 = next_combDelayR2;
			m_delay_37.write(combR1Sum);
			m_h_combStateR_36 = next_combStateR1;
			m_delay_35.write(combR2Sum);
			m_h_combStateR_34 = next_combStateR2;
			m_delay_33.write(combR3Sum);
			m_h_combStateR_32 = next_combStateR3;
			m_delay_31.write(combR4Sum);
			m_h_combStateR_30 = next_combStateR4;
			m_delay_29.write(combR5Sum);
			m_h_combStateR_28 = next_combStateR5;
			m_delay_27.write(combR6Sum);
			m_h_combStateR_26 = next_combStateR6;
			m_delay_25.write(combR7Sum);
			m_h_combStateR_24 = next_combStateR7;
			m_delay_23.write(combR8Sum);
			m_h_combStateR_22 = next_combStateR8;
			m_h_combDelayR_45 = next_combDelayR1;
			m_delay_52.write(apL1Sum);
			m_delay_51.write(apL1);
			m_delay_50.write(apL2Sum);
			m_delay_49.write(apL2);
			m_delay_48.write(apL3Sum);
			m_delay_47.write(apL3);
			m_delay_46.write(apL4Sum);
			m_delay_53.write(earlyLeft);
			m_h_combDelayL_70 = next_combDelayL8;
			m_h_combDelayL_71 = next_combDelayL7;
			m_h_combDelayL_72 = next_combDelayL6;
			m_h_combDelayL_73 = next_combDelayL5;
			m_h_combDelayL_74 = next_combDelayL4;
			m_h_combDelayL_75 = next_combDelayL3;
			m_h_combDelayL_76 = next_combDelayL2;
			m_delay_69.write(combL1Sum);
			m_h_combStateL_68 = next_combStateL1;
			m_delay_67.write(combL2Sum);
			m_h_combStateL_66 = next_combStateL2;
			m_delay_65.write(combL3Sum);
			m_h_combStateL_64 = next_combStateL3;
			m_delay_63.write(combL4Sum);
			m_h_combStateL_62 = next_combStateL4;
			m_delay_61.write(combL5Sum);
			m_h_combStateL_60 = next_combStateL5;
			m_delay_59.write(combL6Sum);
			m_h_combStateL_58 = next_combStateL6;
			m_delay_57.write(combL7Sum);
			m_h_combStateL_56 = next_combStateL7;
			m_delay_55.write(combL8Sum);
			m_h_combStateL_54 = next_combStateL8;
			m_h_combDelayL_77 = next_combDelayL1;
			m_history_86 = nextLpfOutL;
			m_history_87 = nextLpfOutR;
			m_history_88 = nextPreInputR;
			m_history_89 = nextPreInputL;
			m_history_90 = history_36_next_355;
			m_history_91 = history_35_next_354;
			m_history_92 = history_34_next_353;
			m_history_85 = history_41_next_374;
			m_history_78 = history_48_next_381;
			m_history_79 = history_47_next_380;
			m_history_80 = history_46_next_379;
			m_history_81 = history_45_next_378;
			m_history_82 = history_44_next_377;
			m_history_83 = history_43_next_376;
			m_history_84 = history_42_next_375;
			m_history_93 = history_33_next_352;
			m_h_freezeGate_94 = nextFreezeGate;
			m_h_reflectCoef_95 = nextReflectCoef;
			m_h_hpfHz_96 = nextHpfHz;
			m_h_lpfHz_97 = nextLpfHz;
			m_h_sizeScale_98 = nextSizeScale;
			m_h_inputTrim_99 = next_inputTrim;
			m_h_hiGainDb_100 = next_hiGainDb;
			m_h_peakGainDb_101 = next_peakGainDb;
			m_h_lowGainDb_102 = next_lowGainDb;
			m_h_hiFreqHz_103 = next_hiFreqHz;
			m_h_peakFreqHz_104 = next_peakFreqHz;
			m_h_lowFreqHz_105 = next_lowFreqHz;
			m_h_stereoWidth_106 = next_stereoWidth;
			m_h_freezeBlend_107 = next_freezeBlend;
			m_h_eqEnabled_108 = next_eqEnabled;
			m_h_dryWetStage_109 = next_dryWetStage2;
			m_h_dryWetStage_110 = next_dryWetStage1;
			m_h_makeupDb_111 = next_makeupDb;
			m_h_releaseMs_112 = next_releaseMs;
			m_h_attackMs_113 = next_attackMs;
			m_h_ratio_114 = next_ratio;
			m_h_thresholdDb_115 = next_thresholdDb;
			m_h_compEnable_116 = next_compEnable;
			m_h_outputTrim_120 = next_outputTrim;
			m_h_softclipEnable_118 = next_softclipEnable;
			m_h_bypass_117 = next_bypass;
			m_h_prepostGap_119 = next_prepostGap;
			m_prePost_s_1 = fixdenorm(prePostBlend);
			t_sample out4 = leftTrimmed;
			t_sample out1 = mix_25818;
			t_sample out2 = mix_25819;
			t_sample out5 = rightTrimmed;
			m_delay_preL_4.step();
			m_delay_preR_7.step();
			m_delay_10.step();
			m_delay_13.step();
			m_delay_14.step();
			m_delay_15.step();
			m_delay_16.step();
			m_delay_17.step();
			m_delay_18.step();
			m_delay_19.step();
			m_delay_20.step();
			m_delay_21.step();
			m_delay_23.step();
			m_delay_25.step();
			m_delay_27.step();
			m_delay_29.step();
			m_delay_31.step();
			m_delay_33.step();
			m_delay_35.step();
			m_delay_37.step();
			m_delay_46.step();
			m_delay_47.step();
			m_delay_48.step();
			m_delay_49.step();
			m_delay_50.step();
			m_delay_51.step();
			m_delay_52.step();
			m_delay_53.step();
			m_delay_55.step();
			m_delay_57.step();
			m_delay_59.step();
			m_delay_61.step();
			m_delay_63.step();
			m_delay_65.step();
			m_delay_67.step();
			m_delay_69.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = 0;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			
		};
		return __exception;
		
	};
	inline void set_z_SOFTCLIP(t_param _value) {
		m_z_SOFTCLIP_121 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_z_BYPASSS(t_param _value) {
		m_z_BYPASSS_122 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_y_IOMODE(t_param _value) {
		m_y_IOMODE_123 = (_value < 1 ? 1 : (_value > 3 ? 3 : _value));
	};
	inline void set_x_PREPOST(t_param _value) {
		m_x_PREPOST_124 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_h_LOWGAIN(t_param _value) {
		m_h_LOWGAIN_125 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_s_THD(t_param _value) {
		m_s_THD_126 = (_value < -36 ? -36 : (_value > 0 ? 0 : _value));
	};
	inline void set_m_OUTPUT(t_param _value) {
		m_m_OUTPUT_127 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_v_REL(t_param _value) {
		m_v_REL_128 = (_value < 5 ? 5 : (_value > 500 ? 500 : _value));
	};
	inline void set_l_HPF(t_param _value) {
		m_l_HPF_129 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_w_MAKEUP(t_param _value) {
		m_w_MAKEUP_130 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void set_p_HIFREQ(t_param _value) {
		m_p_HIFREQ_131 = (_value < 800 ? 800 : (_value > 15000 ? 15000 : _value));
	};
	inline void set_o_PEAKFREQ(t_param _value) {
		m_o_PEAKFREQ_132 = (_value < 100 ? 100 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_j_HIGAIN(t_param _value) {
		m_j_HIGAIN_133 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_b_DRYWET(t_param _value) {
		m_b_DRYWET_134 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_a_INPUT(t_param _value) {
		m_a_INPUT_135 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_c_REFLECT(t_param _value) {
		m_c_REFLECT_136 = (_value < 0.1 ? 0.1 : (_value > 0.98 ? 0.98 : _value));
	};
	inline void set_f_ST(t_param _value) {
		m_f_ST_137 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_d_DAMP(t_param _value) {
		m_d_DAMP_138 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_g_FREEZE(t_param _value) {
		m_g_FREEZE_139 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_n_LOWFREQ(t_param _value) {
		m_n_LOWFREQ_140 = (_value < 20 ? 20 : (_value > 800 ? 800 : _value));
	};
	inline void set_t_RATIO(t_param _value) {
		m_t_RATIO_141 = (_value < 1 ? 1 : (_value > 20 ? 20 : _value));
	};
	inline void set_k_LPF(t_param _value) {
		m_k_LPF_142 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_r_ONOFFCOMP(t_param _value) {
		m_r_ONOFFCOMP_143 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_i_PEAKGAIN(t_param _value) {
		m_i_PEAKGAIN_144 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_u_ATK(t_param _value) {
		m_u_ATK_145 = (_value < 5 ? 5 : (_value > 250 ? 250 : _value));
	};
	inline void set_q_ONOFFEQ(t_param _value) {
		m_q_ONOFFEQ_146 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_e_SIZE(t_param _value) {
		m_e_SIZE_147 = (_value < 0.1 ? 0.1 : (_value > 4 ? 4 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_160;
		t_sample return_161;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_160, return_161);
		t_sample lowL = return_160;
		t_sample lowR = return_161;
		t_sample return_185;
		t_sample return_186;
		peak_d_d_d_d_i(lowL, lowR, pf, pg, bw, return_185, return_186);
		t_sample peakL = return_185;
		t_sample peakR = return_186;
		t_sample return_199;
		t_sample return_200;
		hishelf_d_d_d_d(peakL, peakR, hf, hg, return_199, return_200);
		t_sample highL = return_199;
		t_sample highR = return_200;
		out1 = highL;
		out2 = highR;
		
	};
	inline void lowshelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_155(freq) != ((int)0)) || (__m_change_156(db) != ((int)0)))) {
			m_shelfGain_154 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_cutoff_153 = safediv(freq, m_shelfGain_154);
			m_shelfTerm_152 = ((m_shelfGain_154 * m_shelfGain_154) - ((int)1));
			m_w_151 = tan(safediv((m_cutoff_153 * ((t_sample)3.1415926535898)), samplerate));
			m_a_150 = safediv(((int)1), (m_w_151 + ((int)1)));
			m_a_149 = (m_w_151 - ((int)1));
			
		};
		t_sample leftOut = lowshelfCore_d_d_d_d_d(sigL, m_a_150, m_a_149, m_shelfTerm_152, m_w_151);
		t_sample rightOut = lowshelfCore_d_d_d_d_d_158(sigR, m_a_150, m_a_149, m_shelfTerm_152, m_w_151);
		out1 = leftOut;
		out2 = rightOut;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_150, t_sample m_a_149, t_sample b1, t_sample m_w_151) {
		t_sample x = (m_a_150 * (input - (m_a_149 * m_z_157)));
		t_sample y = (m_w_151 * (x + m_z_157));
		m_z_157 = x;
		return ((y * b1) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_158(t_sample input, t_sample m_a_150, t_sample m_a_149, t_sample b1, t_sample m_w_151) {
		t_sample x = (m_a_150 * (input - (m_a_149 * m_z_159)));
		t_sample y = (m_w_151 * (x + m_z_159));
		m_z_159 = x;
		return ((y * b1) + input);
		
	};
	inline void peak_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_172(freq) != ((int)0)) || (__m_change_173(db) != ((int)0))) || (__m_change_174(bw) != ((int)0)))) {
			m_w_171 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_170 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_170 * m_b_170) - ((int)1));
			m_d_169 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_175 = safediv(((m_d_169 * m_d_169) - ((int)1)), (m_d_169 * m_b_170));
			m_d_168 = ((v_175 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_175 >= ((int)100)) ? ((int)100) : v_175));
			m_d_167 = (m_d_168 * b);
			m_wq_166 = (m_d_168 * m_w_171);
			m_w_165 = (m_w_171 * m_w_171);
			m_a_164 = safediv(((int)1), ((((int)1) + m_w_165) + m_wq_166));
			m_a_163 = ((m_w_165 - ((int)1)) * ((int)2));
			m_a_162 = ((((int)1) + m_w_165) - m_wq_166);
			
		};
		t_sample leftOut = peakCore_d_d_d_d_d_d(sigL, m_w_171, m_d_167, m_a_164, m_a_163, m_a_162);
		t_sample rightOut = peakCore_d_d_d_d_d_d_180(sigR, m_w_171, m_d_167, m_a_164, m_a_163, m_a_162);
		out1 = leftOut;
		out2 = rightOut;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_171, t_sample m_d_167, t_sample m_a_164, t_sample m_a_163, t_sample m_a_162) {
		t_sample stage = ((input - m_z_178) * m_w_171);
		m_z_178 = m_z_179;
		m_z_179 = input;
		t_sample biquadOut = (m_a_164 * ((stage - (m_a_163 * m_z_177)) - (m_a_162 * m_z_176)));
		m_z_176 = m_z_177;
		m_z_177 = biquadOut;
		t_sample out1 = (input + (biquadOut * m_d_167));
		return out1;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_180(t_sample input, t_sample m_w_171, t_sample m_d_167, t_sample m_a_164, t_sample m_a_163, t_sample m_a_162) {
		t_sample stage = ((input - m_z_183) * m_w_171);
		m_z_183 = m_z_184;
		m_z_184 = input;
		t_sample biquadOut = (m_a_164 * ((stage - (m_a_163 * m_z_182)) - (m_a_162 * m_z_181)));
		m_z_181 = m_z_182;
		m_z_182 = biquadOut;
		t_sample out1 = (input + (biquadOut * m_d_167));
		return out1;
		
	};
	inline void hishelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_193(freq) != ((int)0)) || (__m_change_194(db) != ((int)0)))) {
			m_shelfGain_192 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_195 = (freq * m_shelfGain_192);
			m_cutoff_191 = ((samplerate < mina_195) ? samplerate : mina_195);
			m_shelfTerm_190 = ((m_shelfGain_192 * m_shelfGain_192) - ((int)1));
			m_w_189 = tan(safediv((((m_cutoff_191 < ((int)0)) ? ((int)0) : m_cutoff_191) * ((t_sample)3.1415926535898)), samplerate));
			m_a_188 = safediv(((int)1), (m_w_189 + ((int)1)));
			m_a_187 = (m_w_189 - ((int)1));
			
		};
		t_sample leftOut = hishelfCore_d_d_d_d(sigL, m_a_188, m_a_187, m_shelfTerm_190);
		t_sample rightOut = hishelfCore_d_d_d_d_197(sigR, m_a_188, m_a_187, m_shelfTerm_190);
		out1 = leftOut;
		out2 = rightOut;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_188, t_sample m_a_187, t_sample b1) {
		t_sample x = (m_a_188 * (input - (m_a_187 * m_z_196)));
		t_sample y = (x - m_z_196);
		m_z_196 = x;
		t_sample out1 = ((y * b1) + input);
		return out1;
		
	};
	inline t_sample hishelfCore_d_d_d_d_197(t_sample input, t_sample m_a_188, t_sample m_a_187, t_sample b1) {
		t_sample x = (m_a_188 * (input - (m_a_187 * m_z_198)));
		t_sample y = (x - m_z_198);
		m_z_198 = x;
		t_sample out1 = ((y * b1) + input);
		return out1;
		
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i_257(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_271;
		t_sample return_272;
		lowshelf_d_d_d_d_258(sigL, sigR, lf, lg, return_271, return_272);
		t_sample lowL = return_271;
		t_sample lowR = return_272;
		t_sample return_298;
		t_sample return_299;
		peak_d_d_d_d_i_273(lowL, lowR, pf, pg, bw, return_298, return_299);
		t_sample peakL = return_298;
		t_sample peakR = return_299;
		t_sample return_314;
		t_sample return_315;
		hishelf_d_d_d_d_300(peakL, peakR, hf, hg, return_314, return_315);
		t_sample highL = return_314;
		t_sample highR = return_315;
		out1 = highL;
		out2 = highR;
		
	};
	inline void lowshelf_d_d_d_d_258(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_265(freq) != ((int)0)) || (__m_change_266(db) != ((int)0)))) {
			m_shelfGain_264 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_cutoff_263 = safediv(freq, m_shelfGain_264);
			m_shelfTerm_262 = ((m_shelfGain_264 * m_shelfGain_264) - ((int)1));
			m_w_261 = tan(safediv((m_cutoff_263 * ((t_sample)3.1415926535898)), samplerate));
			m_a_260 = safediv(((int)1), (m_w_261 + ((int)1)));
			m_a_259 = (m_w_261 - ((int)1));
			
		};
		t_sample leftOut = lowshelfCore_d_d_d_d_d_267(sigL, m_a_260, m_a_259, m_shelfTerm_262, m_w_261);
		t_sample rightOut = lowshelfCore_d_d_d_d_d_269(sigR, m_a_260, m_a_259, m_shelfTerm_262, m_w_261);
		out1 = leftOut;
		out2 = rightOut;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_267(t_sample input, t_sample m_a_260, t_sample m_a_259, t_sample b1, t_sample m_w_261) {
		t_sample x = (m_a_260 * (input - (m_a_259 * m_z_268)));
		t_sample y = (m_w_261 * (x + m_z_268));
		m_z_268 = x;
		return ((y * b1) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_269(t_sample input, t_sample m_a_260, t_sample m_a_259, t_sample b1, t_sample m_w_261) {
		t_sample x = (m_a_260 * (input - (m_a_259 * m_z_270)));
		t_sample y = (m_w_261 * (x + m_z_270));
		m_z_270 = x;
		return ((y * b1) + input);
		
	};
	inline void peak_d_d_d_d_i_273(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_284(freq) != ((int)0)) || (__m_change_285(db) != ((int)0))) || (__m_change_286(bw) != ((int)0)))) {
			m_w_283 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_282 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_282 * m_b_282) - ((int)1));
			m_d_281 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_287 = safediv(((m_d_281 * m_d_281) - ((int)1)), (m_d_281 * m_b_282));
			m_d_280 = ((v_287 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_287 >= ((int)100)) ? ((int)100) : v_287));
			m_d_279 = (m_d_280 * b);
			m_wq_278 = (m_d_280 * m_w_283);
			m_w_277 = (m_w_283 * m_w_283);
			m_a_276 = safediv(((int)1), ((((int)1) + m_w_277) + m_wq_278));
			m_a_275 = ((m_w_277 - ((int)1)) * ((int)2));
			m_a_274 = ((((int)1) + m_w_277) - m_wq_278);
			
		};
		t_sample leftOut = peakCore_d_d_d_d_d_d_288(sigL, m_w_283, m_d_279, m_a_276, m_a_275, m_a_274);
		t_sample rightOut = peakCore_d_d_d_d_d_d_293(sigR, m_w_283, m_d_279, m_a_276, m_a_275, m_a_274);
		out1 = leftOut;
		out2 = rightOut;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_288(t_sample input, t_sample m_w_283, t_sample m_d_279, t_sample m_a_276, t_sample m_a_275, t_sample m_a_274) {
		t_sample stage = ((input - m_z_291) * m_w_283);
		m_z_291 = m_z_292;
		m_z_292 = input;
		t_sample biquadOut = (m_a_276 * ((stage - (m_a_275 * m_z_290)) - (m_a_274 * m_z_289)));
		m_z_289 = m_z_290;
		m_z_290 = biquadOut;
		t_sample out1 = (input + (biquadOut * m_d_279));
		return out1;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_293(t_sample input, t_sample m_w_283, t_sample m_d_279, t_sample m_a_276, t_sample m_a_275, t_sample m_a_274) {
		t_sample stage = ((input - m_z_296) * m_w_283);
		m_z_296 = m_z_297;
		m_z_297 = input;
		t_sample biquadOut = (m_a_276 * ((stage - (m_a_275 * m_z_295)) - (m_a_274 * m_z_294)));
		m_z_294 = m_z_295;
		m_z_295 = biquadOut;
		t_sample out1 = (input + (biquadOut * m_d_279));
		return out1;
		
	};
	inline void hishelf_d_d_d_d_300(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_307(freq) != ((int)0)) || (__m_change_308(db) != ((int)0)))) {
			m_shelfGain_306 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_309 = (freq * m_shelfGain_306);
			m_cutoff_305 = ((samplerate < mina_309) ? samplerate : mina_309);
			m_shelfTerm_304 = ((m_shelfGain_306 * m_shelfGain_306) - ((int)1));
			m_w_303 = tan(safediv((((m_cutoff_305 < ((int)0)) ? ((int)0) : m_cutoff_305) * ((t_sample)3.1415926535898)), samplerate));
			m_a_302 = safediv(((int)1), (m_w_303 + ((int)1)));
			m_a_301 = (m_w_303 - ((int)1));
			
		};
		t_sample leftOut = hishelfCore_d_d_d_d_310(sigL, m_a_302, m_a_301, m_shelfTerm_304);
		t_sample rightOut = hishelfCore_d_d_d_d_312(sigR, m_a_302, m_a_301, m_shelfTerm_304);
		out1 = leftOut;
		out2 = rightOut;
		
	};
	inline t_sample hishelfCore_d_d_d_d_310(t_sample input, t_sample m_a_302, t_sample m_a_301, t_sample b1) {
		t_sample x = (m_a_302 * (input - (m_a_301 * m_z_311)));
		t_sample y = (x - m_z_311);
		m_z_311 = x;
		t_sample out1 = ((y * b1) + input);
		return out1;
		
	};
	inline t_sample hishelfCore_d_d_d_d_312(t_sample input, t_sample m_a_302, t_sample m_a_301, t_sample b1) {
		t_sample x = (m_a_302 * (input - (m_a_301 * m_z_313)));
		t_sample y = (x - m_z_313);
		m_z_313 = x;
		t_sample out1 = ((y * b1) + input);
		return out1;
		
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 5;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 27; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "out4", "out5" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_a_INPUT(value); break;
		case 1: self->set_b_DRYWET(value); break;
		case 2: self->set_c_REFLECT(value); break;
		case 3: self->set_d_DAMP(value); break;
		case 4: self->set_e_SIZE(value); break;
		case 5: self->set_f_ST(value); break;
		case 6: self->set_g_FREEZE(value); break;
		case 7: self->set_h_LOWGAIN(value); break;
		case 8: self->set_i_PEAKGAIN(value); break;
		case 9: self->set_j_HIGAIN(value); break;
		case 10: self->set_k_LPF(value); break;
		case 11: self->set_l_HPF(value); break;
		case 12: self->set_m_OUTPUT(value); break;
		case 13: self->set_n_LOWFREQ(value); break;
		case 14: self->set_o_PEAKFREQ(value); break;
		case 15: self->set_p_HIFREQ(value); break;
		case 16: self->set_q_ONOFFEQ(value); break;
		case 17: self->set_r_ONOFFCOMP(value); break;
		case 18: self->set_s_THD(value); break;
		case 19: self->set_t_RATIO(value); break;
		case 20: self->set_u_ATK(value); break;
		case 21: self->set_v_REL(value); break;
		case 22: self->set_w_MAKEUP(value); break;
		case 23: self->set_x_PREPOST(value); break;
		case 24: self->set_y_IOMODE(value); break;
		case 25: self->set_z_BYPASSS(value); break;
		case 26: self->set_z_SOFTCLIP(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_a_INPUT_135; break;
		case 1: *value = self->m_b_DRYWET_134; break;
		case 2: *value = self->m_c_REFLECT_136; break;
		case 3: *value = self->m_d_DAMP_138; break;
		case 4: *value = self->m_e_SIZE_147; break;
		case 5: *value = self->m_f_ST_137; break;
		case 6: *value = self->m_g_FREEZE_139; break;
		case 7: *value = self->m_h_LOWGAIN_125; break;
		case 8: *value = self->m_i_PEAKGAIN_144; break;
		case 9: *value = self->m_j_HIGAIN_133; break;
		case 10: *value = self->m_k_LPF_142; break;
		case 11: *value = self->m_l_HPF_129; break;
		case 12: *value = self->m_m_OUTPUT_127; break;
		case 13: *value = self->m_n_LOWFREQ_140; break;
		case 14: *value = self->m_o_PEAKFREQ_132; break;
		case 15: *value = self->m_p_HIFREQ_131; break;
		case 16: *value = self->m_q_ONOFFEQ_146; break;
		case 17: *value = self->m_r_ONOFFCOMP_143; break;
		case 18: *value = self->m_s_THD_126; break;
		case 19: *value = self->m_t_RATIO_141; break;
		case 20: *value = self->m_u_ATK_145; break;
		case 21: *value = self->m_v_REL_128; break;
		case 22: *value = self->m_w_MAKEUP_130; break;
		case 23: *value = self->m_x_PREPOST_124; break;
		case 24: *value = self->m_y_IOMODE_123; break;
		case 25: *value = self->m_z_BYPASSS_122; break;
		case 26: *value = self->m_z_SOFTCLIP_121; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(27 * sizeof(ParamInfo));
	self->__commonstate.numparams = 27;
	// initialize parameter 0 ("m_a_INPUT_135")
	pi = self->__commonstate.params + 0;
	pi->name = "a_INPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_INPUT_135;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -12;
	pi->outputmax = 12;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_DRYWET_134")
	pi = self->__commonstate.params + 1;
	pi->name = "b_DRYWET";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_DRYWET_134;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_REFLECT_136")
	pi = self->__commonstate.params + 2;
	pi->name = "c_REFLECT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_REFLECT_136;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.98;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_DAMP_138")
	pi = self->__commonstate.params + 3;
	pi->name = "d_DAMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_DAMP_138;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_SIZE_147")
	pi = self->__commonstate.params + 4;
	pi->name = "e_SIZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_SIZE_147;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_ST_137")
	pi = self->__commonstate.params + 5;
	pi->name = "f_ST";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_ST_137;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_FREEZE_139")
	pi = self->__commonstate.params + 6;
	pi->name = "g_FREEZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_FREEZE_139;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_LOWGAIN_125")
	pi = self->__commonstate.params + 7;
	pi->name = "h_LOWGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_LOWGAIN_125;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_PEAKGAIN_144")
	pi = self->__commonstate.params + 8;
	pi->name = "i_PEAKGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_PEAKGAIN_144;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_HIGAIN_133")
	pi = self->__commonstate.params + 9;
	pi->name = "j_HIGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_HIGAIN_133;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_LPF_142")
	pi = self->__commonstate.params + 10;
	pi->name = "k_LPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_LPF_142;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_HPF_129")
	pi = self->__commonstate.params + 11;
	pi->name = "l_HPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_HPF_129;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_OUTPUT_127")
	pi = self->__commonstate.params + 12;
	pi->name = "m_OUTPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_OUTPUT_127;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -12;
	pi->outputmax = 12;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_LOWFREQ_140")
	pi = self->__commonstate.params + 13;
	pi->name = "n_LOWFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_LOWFREQ_140;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 800;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_PEAKFREQ_132")
	pi = self->__commonstate.params + 14;
	pi->name = "o_PEAKFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_PEAKFREQ_132;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 2500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_HIFREQ_131")
	pi = self->__commonstate.params + 15;
	pi->name = "p_HIFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_HIFREQ_131;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 800;
	pi->outputmax = 15000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_ONOFFEQ_146")
	pi = self->__commonstate.params + 16;
	pi->name = "q_ONOFFEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_ONOFFEQ_146;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 17 ("m_r_ONOFFCOMP_143")
	pi = self->__commonstate.params + 17;
	pi->name = "r_ONOFFCOMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_ONOFFCOMP_143;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 18 ("m_s_THD_126")
	pi = self->__commonstate.params + 18;
	pi->name = "s_THD";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_THD_126;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -36;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_RATIO_141")
	pi = self->__commonstate.params + 19;
	pi->name = "t_RATIO";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_RATIO_141;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_ATK_145")
	pi = self->__commonstate.params + 20;
	pi->name = "u_ATK";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_ATK_145;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 5;
	pi->outputmax = 250;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_REL_128")
	pi = self->__commonstate.params + 21;
	pi->name = "v_REL";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_REL_128;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 5;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_MAKEUP_130")
	pi = self->__commonstate.params + 22;
	pi->name = "w_MAKEUP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_MAKEUP_130;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -6;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 23 ("m_x_PREPOST_124")
	pi = self->__commonstate.params + 23;
	pi->name = "x_PREPOST";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_x_PREPOST_124;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 24 ("m_y_IOMODE_123")
	pi = self->__commonstate.params + 24;
	pi->name = "y_IOMODE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_y_IOMODE_123;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 3;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 25 ("m_z_BYPASSS_122")
	pi = self->__commonstate.params + 25;
	pi->name = "z_BYPASSS";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_z_BYPASSS_122;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 26 ("m_z_SOFTCLIP_121")
	pi = self->__commonstate.params + 26;
	pi->name = "z_SOFTCLIP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_z_SOFTCLIP_121;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // JCBReverb::
