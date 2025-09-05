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
	Change __m_change_146;
	Change __m_change_163;
	Change __m_change_145;
	Change __m_change_162;
	Change __m_change_164;
	Change __m_change_184;
	Change __m_change_183;
	DCBlock __m_dcblock_201;
	DCBlock __m_dcblock_202;
	Delay m_delay_54;
	Delay m_delay_56;
	Delay m_delay_26;
	Delay m_delay_28;
	Delay m_delay_52;
	Delay m_delay_30;
	Delay m_delay_46;
	Delay m_delay_48;
	Delay m_delay_42;
	Delay m_delay_41;
	Delay m_delay_50;
	Delay m_delay_43;
	Delay m_delay_45;
	Delay m_delay_44;
	Delay m_delay_24;
	Delay m_delay_58;
	Delay m_delay_62;
	Delay m_delay_60;
	Delay m_delay_8;
	Delay m_delay_9;
	Delay m_delay_10;
	Delay m_delay_7;
	Delay m_delay_3;
	Delay m_delay_6;
	Delay m_delay_22;
	Delay m_delay_11;
	Delay m_delay_13;
	Delay m_delay_39;
	Delay m_delay_20;
	Delay m_delay_12;
	Delay m_delay_18;
	Delay m_delay_14;
	Delay m_delay_16;
	Delay m_delay_40;
	int __exception;
	int vectorsize;
	t_sample m_history_37;
	t_sample m_w_MAKEUP_135;
	t_sample m_a_INPUT_136;
	t_sample m_l_HPF_134;
	t_sample m_r_ONOFFCOMP_132;
	t_sample m_i_PEAKGAIN_133;
	t_sample m_g_FREEZE_131;
	t_sample m_history_137;
	t_sample m_a_139;
	t_sample m_a_140;
	t_sample m_b_144;
	t_sample m_history_15;
	t_sample m_p_HIFREQ_130;
	t_sample m_f_143;
	t_sample m_w_141;
	t_sample m_b_142;
	t_sample m_history_5;
	t_sample m_t_RATIO_129;
	t_sample m_k_LPF_127;
	t_sample m_u_ATK_117;
	t_sample m_v_REL_118;
	t_sample m_s_THD_119;
	t_sample m_d_DAMP_116;
	t_sample m_m_OUTPUT_114;
	t_sample m_y_FILTERS_115;
	t_sample m_h_LOWGAIN_128;
	t_sample m_q_ONOFFEQ_120;
	t_sample m_f_ST_122;
	t_sample m_e_SIZE_126;
	t_sample m_c_REFLECT_121;
	t_sample m_b_DRYWET_125;
	t_sample m_z_BYPASS_123;
	t_sample m_j_HIGAIN_124;
	t_sample m_z_147;
	t_sample m_z_149;
	t_sample m_a_152;
	t_sample m_a_177;
	t_sample m_a_178;
	t_sample m_w_179;
	t_sample m_z_174;
	t_sample m_z_172;
	t_sample m_z_173;
	t_sample m_z_171;
	t_sample m_b_180;
	t_sample m_b_182;
	t_sample __m_slide_194;
	t_sample __m_slide_198;
	t_sample m_f_181;
	t_sample m_z_188;
	t_sample samplerate;
	t_sample m_z_186;
	t_sample m_n_LOWFREQ_113;
	t_sample m_z_169;
	t_sample m_z_167;
	t_sample m_wq_156;
	t_sample m_d_157;
	t_sample m_d_158;
	t_sample m_w_155;
	t_sample m_a_153;
	t_sample m_a_154;
	t_sample m_z_168;
	t_sample m_d_159;
	t_sample m_w_161;
	t_sample m_z_166;
	t_sample m_b_160;
	t_sample m_history_1;
	t_sample m_history_4;
	t_sample m_history_2;
	t_sample m_history_38;
	t_sample m_o_PEAKFREQ_112;
	t_sample m_history_110;
	t_sample m_history_64;
	t_sample m_history_65;
	t_sample m_history_66;
	t_sample m_history_63;
	t_sample m_history_61;
	t_sample m_history_19;
	t_sample m_history_21;
	t_sample m_history_67;
	t_sample m_history_69;
	t_sample m_history_73;
	t_sample m_history_74;
	t_sample m_history_68;
	t_sample m_history_72;
	t_sample m_history_70;
	t_sample m_history_71;
	t_sample m_history_75;
	t_sample m_history_59;
	t_sample m_history_57;
	t_sample m_history_33;
	t_sample m_history_47;
	t_sample m_history_32;
	t_sample m_history_34;
	t_sample m_history_36;
	t_sample m_history_35;
	t_sample m_history_23;
	t_sample m_history_49;
	t_sample m_history_51;
	t_sample m_history_55;
	t_sample m_history_25;
	t_sample m_history_31;
	t_sample m_history_27;
	t_sample m_history_29;
	t_sample m_history_53;
	t_sample m_history_111;
	t_sample m_history_76;
	t_sample m_history_78;
	t_sample m_history_99;
	t_sample m_history_100;
	t_sample m_history_101;
	t_sample m_history_98;
	t_sample m_history_96;
	t_sample m_history_97;
	t_sample m_history_95;
	t_sample m_history_102;
	t_sample m_history_104;
	t_sample m_history_108;
	t_sample m_history_109;
	t_sample m_history_103;
	t_sample m_history_107;
	t_sample m_history_105;
	t_sample m_history_106;
	t_sample m_history_77;
	t_sample m_history_94;
	t_sample m_history_92;
	t_sample m_history_82;
	t_sample m_history_83;
	t_sample m_history_84;
	t_sample m_history_81;
	t_sample m_history_79;
	t_sample m_history_80;
	t_sample m_history_93;
	t_sample m_history_85;
	t_sample m_history_87;
	t_sample m_history_91;
	t_sample m_history_86;
	t_sample m_history_17;
	t_sample m_history_88;
	t_sample m_history_89;
	t_sample m_history_90;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_delay_3.reset("m_delay_3", ((int)44100));
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_delay_6.reset("m_delay_6", ((int)44100));
		m_delay_7.reset("m_delay_7", samplerate);
		m_delay_8.reset("m_delay_8", samplerate);
		m_delay_9.reset("m_delay_9", samplerate);
		m_delay_10.reset("m_delay_10", samplerate);
		m_delay_11.reset("m_delay_11", samplerate);
		m_delay_12.reset("m_delay_12", samplerate);
		m_delay_13.reset("m_delay_13", samplerate);
		m_delay_14.reset("m_delay_14", samplerate);
		m_history_15 = ((int)0);
		m_delay_16.reset("m_delay_16", samplerate);
		m_history_17 = ((int)0);
		m_delay_18.reset("m_delay_18", samplerate);
		m_history_19 = ((int)0);
		m_delay_20.reset("m_delay_20", samplerate);
		m_history_21 = ((int)0);
		m_delay_22.reset("m_delay_22", samplerate);
		m_history_23 = ((int)0);
		m_delay_24.reset("m_delay_24", samplerate);
		m_history_25 = ((int)0);
		m_delay_26.reset("m_delay_26", samplerate);
		m_history_27 = ((int)0);
		m_delay_28.reset("m_delay_28", samplerate);
		m_history_29 = ((int)0);
		m_delay_30.reset("m_delay_30", samplerate);
		m_history_31 = ((int)0);
		m_history_32 = ((int)0);
		m_history_33 = ((int)0);
		m_history_34 = ((int)0);
		m_history_35 = ((int)0);
		m_history_36 = ((int)0);
		m_history_37 = ((int)0);
		m_history_38 = ((int)0);
		m_delay_39.reset("m_delay_39", samplerate);
		m_delay_40.reset("m_delay_40", samplerate);
		m_delay_41.reset("m_delay_41", samplerate);
		m_delay_42.reset("m_delay_42", samplerate);
		m_delay_43.reset("m_delay_43", samplerate);
		m_delay_44.reset("m_delay_44", samplerate);
		m_delay_45.reset("m_delay_45", samplerate);
		m_delay_46.reset("m_delay_46", samplerate);
		m_history_47 = ((int)0);
		m_delay_48.reset("m_delay_48", samplerate);
		m_history_49 = ((int)0);
		m_delay_50.reset("m_delay_50", samplerate);
		m_history_51 = ((int)0);
		m_delay_52.reset("m_delay_52", samplerate);
		m_history_53 = ((int)0);
		m_delay_54.reset("m_delay_54", samplerate);
		m_history_55 = ((int)0);
		m_delay_56.reset("m_delay_56", samplerate);
		m_history_57 = ((int)0);
		m_delay_58.reset("m_delay_58", samplerate);
		m_history_59 = ((int)0);
		m_delay_60.reset("m_delay_60", samplerate);
		m_history_61 = ((int)0);
		m_delay_62.reset("m_delay_62", samplerate);
		m_history_63 = ((int)0);
		m_history_64 = ((int)0);
		m_history_65 = ((int)0);
		m_history_66 = ((int)0);
		m_history_67 = ((int)0);
		m_history_68 = ((int)0);
		m_history_69 = ((int)0);
		m_history_70 = ((int)0);
		m_history_71 = ((int)0);
		m_history_72 = ((int)0);
		m_history_73 = ((int)0);
		m_history_74 = ((int)0);
		m_history_75 = ((int)0);
		m_history_76 = ((int)0);
		m_history_77 = ((int)0);
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
		m_history_94 = ((int)0);
		m_history_95 = ((int)0);
		m_history_96 = ((int)0);
		m_history_97 = ((int)0);
		m_history_98 = ((int)0);
		m_history_99 = ((int)0);
		m_history_100 = ((int)0);
		m_history_101 = ((int)0);
		m_history_102 = ((int)0);
		m_history_103 = ((int)0);
		m_history_104 = ((int)0);
		m_history_105 = ((int)0);
		m_history_106 = ((int)0);
		m_history_107 = ((int)0);
		m_history_108 = ((int)0);
		m_history_109 = ((int)0);
		m_history_110 = ((int)0);
		m_history_111 = ((int)0);
		m_o_PEAKFREQ_112 = 800;
		m_n_LOWFREQ_113 = 500;
		m_m_OUTPUT_114 = 0;
		m_y_FILTERS_115 = 0;
		m_d_DAMP_116 = 0.25;
		m_u_ATK_117 = 10;
		m_v_REL_118 = 100;
		m_s_THD_119 = -12;
		m_q_ONOFFEQ_120 = 0;
		m_c_REFLECT_121 = 0.85;
		m_f_ST_122 = 0.5;
		m_z_BYPASS_123 = 0;
		m_j_HIGAIN_124 = 0;
		m_b_DRYWET_125 = 0.33;
		m_e_SIZE_126 = 1;
		m_k_LPF_127 = 20000;
		m_h_LOWGAIN_128 = 0;
		m_t_RATIO_129 = 2;
		m_p_HIFREQ_130 = 2000;
		m_g_FREEZE_131 = 0;
		m_r_ONOFFCOMP_132 = 0;
		m_i_PEAKGAIN_133 = 0;
		m_l_HPF_134 = 20;
		m_w_MAKEUP_135 = 0;
		m_a_INPUT_136 = 0;
		m_history_137 = ((int)0);
		m_a_139 = ((int)0);
		m_a_140 = ((int)0);
		m_w_141 = ((int)0);
		m_b_142 = ((int)0);
		m_f_143 = ((int)0);
		m_b_144 = ((int)0);
		__m_change_145.reset(0);
		__m_change_146.reset(0);
		m_z_147 = ((int)0);
		m_z_149 = ((int)0);
		m_a_152 = ((int)0);
		m_a_153 = ((int)0);
		m_a_154 = ((int)0);
		m_w_155 = ((int)0);
		m_wq_156 = ((int)0);
		m_d_157 = ((int)0);
		m_d_158 = ((int)0);
		m_d_159 = ((int)0);
		m_b_160 = ((int)0);
		m_w_161 = ((int)0);
		__m_change_162.reset(0);
		__m_change_163.reset(0);
		__m_change_164.reset(0);
		m_z_166 = ((int)0);
		m_z_167 = ((int)0);
		m_z_168 = ((int)0);
		m_z_169 = ((int)0);
		m_z_171 = ((int)0);
		m_z_172 = ((int)0);
		m_z_173 = ((int)0);
		m_z_174 = ((int)0);
		m_a_177 = ((int)0);
		m_a_178 = ((int)0);
		m_w_179 = ((int)0);
		m_b_180 = ((int)0);
		m_f_181 = ((int)0);
		m_b_182 = ((int)0);
		__m_change_183.reset(0);
		__m_change_184.reset(0);
		m_z_186 = ((int)0);
		m_z_188 = ((int)0);
		__m_slide_194 = 0;
		__m_slide_198 = 0;
		__m_dcblock_201.reset();
		__m_dcblock_202.reset();
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
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample mul_1645 = (m_z_BYPASS_123 * ((t_sample)0.001));
		t_sample dbtoa_2 = dbtoa(m_a_INPUT_136);
		t_sample mul_448 = (dbtoa_2 * ((t_sample)0.001));
		t_sample mul_348 = (m_b_DRYWET_125 * ((t_sample)0.001));
		t_sample dbtoa_1 = dbtoa(m_m_OUTPUT_114);
		t_sample mul_360 = (dbtoa_1 * ((t_sample)0.001));
		t_sample mul_35 = (m_r_ONOFFCOMP_132 * ((t_sample)0.001));
		t_sample mul_29 = (m_s_THD_119 * ((t_sample)0.001));
		t_sample mul_23 = (m_t_RATIO_129 * ((t_sample)0.001));
		t_sample mul_17 = (m_u_ATK_117 * ((t_sample)0.001));
		t_sample mul_11 = (m_v_REL_118 * ((t_sample)0.001));
		t_sample mul_3 = (m_w_MAKEUP_135 * ((t_sample)0.001));
		int gte_467 = (m_g_FREEZE_131 >= ((t_sample)0.5));
		t_sample mul_1637 = (gte_467 * ((t_sample)0.001));
		t_sample mul_198 = (m_q_ONOFFEQ_120 * ((t_sample)0.001));
		t_sample mul_218 = (m_n_LOWFREQ_113 * ((t_sample)0.001));
		t_sample mul_212 = (m_o_PEAKFREQ_112 * ((t_sample)0.001));
		t_sample mul_206 = (m_p_HIFREQ_130 * ((t_sample)0.001));
		t_sample mul_380 = (m_h_LOWGAIN_128 * ((t_sample)0.001));
		t_sample mul_374 = (m_i_PEAKGAIN_133 * ((t_sample)0.001));
		t_sample mul_368 = (m_j_HIGAIN_124 * ((t_sample)0.001));
		t_sample mul_454 = (m_f_ST_122 * ((t_sample)0.001));
		t_sample mul_224 = (m_e_SIZE_126 * ((t_sample)0.001));
		t_sample mul_1631 = (m_d_DAMP_116 * ((t_sample)0.001));
		t_sample mul_392 = (m_k_LPF_127 * ((t_sample)0.001));
		t_sample mul_386 = (m_l_HPF_134 * ((t_sample)0.001));
		t_sample mul_2696 = (m_y_FILTERS_115 * ((t_sample)0.001));
		int rsub_466 = (((int)1) - gte_467);
		t_sample mul_422 = (rsub_466 * ((t_sample)0.001));
		t_sample rsub_463 = (((int)1) - m_c_REFLECT_121);
		int choice_138 = gte_467;
		t_sample gate_462 = ((choice_138 >= 1) ? rsub_463 : 0);
		t_sample add_464 = (m_c_REFLECT_121 + gate_462);
		t_sample mul_428 = (add_464 * ((t_sample)0.001));
		t_sample div_704 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_334 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_320 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_306 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_292 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_531 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_275 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_261 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_247 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_233 = (samplerate * ((t_sample)2.2675736961451e-05));
		int maxb_193 = (-96);
		int maxb_197 = (-96);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_1646 = (m_history_137 * ((t_sample)0.999));
			t_sample add_1648 = (mul_1645 + mul_1646);
			t_sample gen_1650 = add_1648;
			t_sample history_1647_next_1649 = fixdenorm(add_1648);
			t_sample mul_449 = (m_history_111 * ((t_sample)0.999));
			t_sample add_451 = (mul_448 + mul_449);
			t_sample gen_453 = add_451;
			t_sample history_450_next_452 = fixdenorm(add_451);
			t_sample mul_416 = (in2 * gen_453);
			t_sample out4 = mul_416;
			t_sample mul_417 = (in1 * gen_453);
			t_sample out3 = mul_417;
			t_sample mul_349 = (m_history_110 * ((t_sample)0.999));
			t_sample add_351 = (mul_348 + mul_349);
			t_sample gen_353 = add_351;
			t_sample history_350_next_352 = fixdenorm(add_351);
			t_sample mul_361 = (m_history_109 * ((t_sample)0.999));
			t_sample add_363 = (mul_360 + mul_361);
			t_sample gen_365 = add_363;
			t_sample history_362_next_364 = fixdenorm(add_363);
			t_sample mul_36 = (m_history_108 * ((t_sample)0.999));
			t_sample add_38 = (mul_35 + mul_36);
			t_sample gen_40 = add_38;
			t_sample history_37_next_39 = fixdenorm(add_38);
			t_sample mul_30 = (m_history_107 * ((t_sample)0.999));
			t_sample add_32 = (mul_29 + mul_30);
			t_sample gen_34 = add_32;
			t_sample history_31_next_33 = fixdenorm(add_32);
			t_sample mul_24 = (m_history_106 * ((t_sample)0.999));
			t_sample add_26 = (mul_23 + mul_24);
			t_sample gen_28 = add_26;
			t_sample history_25_next_27 = fixdenorm(add_26);
			t_sample mul_18 = (m_history_105 * ((t_sample)0.999));
			t_sample add_20 = (mul_17 + mul_18);
			t_sample gen_22 = add_20;
			t_sample history_19_next_21 = fixdenorm(add_20);
			t_sample mul_12 = (m_history_104 * ((t_sample)0.999));
			t_sample add_14 = (mul_11 + mul_12);
			t_sample gen_16 = add_14;
			t_sample history_13_next_15 = fixdenorm(add_14);
			t_sample mul_4 = (m_history_103 * ((t_sample)0.999));
			t_sample add_6 = (mul_3 + mul_4);
			t_sample gen_8 = add_6;
			t_sample history_5_next_7 = fixdenorm(add_6);
			t_sample mul_1638 = (m_history_102 * ((t_sample)0.999));
			t_sample add_1640 = (mul_1637 + mul_1638);
			t_sample gen_1642 = add_1640;
			t_sample history_1639_next_1641 = fixdenorm(add_1640);
			t_sample mix_2816 = (mul_416 + (gen_1642 * (((int)0) - mul_416)));
			t_sample mix_2817 = (mul_417 + (gen_1642 * (((int)0) - mul_417)));
			t_sample mul_199 = (m_history_101 * ((t_sample)0.999));
			t_sample add_201 = (mul_198 + mul_199);
			t_sample gen_203 = add_201;
			t_sample history_200_next_202 = fixdenorm(add_201);
			t_sample mul_219 = (m_history_100 * ((t_sample)0.999));
			t_sample add_221 = (mul_218 + mul_219);
			t_sample gen_223 = add_221;
			t_sample history_220_next_222 = fixdenorm(add_221);
			t_sample mul_213 = (m_history_99 * ((t_sample)0.999));
			t_sample add_215 = (mul_212 + mul_213);
			t_sample gen_217 = add_215;
			t_sample history_214_next_216 = fixdenorm(add_215);
			t_sample mul_207 = (m_history_98 * ((t_sample)0.999));
			t_sample add_209 = (mul_206 + mul_207);
			t_sample gen_211 = add_209;
			t_sample history_208_next_210 = fixdenorm(add_209);
			t_sample mul_381 = (m_history_97 * ((t_sample)0.999));
			t_sample add_383 = (mul_380 + mul_381);
			t_sample gen_385 = add_383;
			t_sample history_382_next_384 = fixdenorm(add_383);
			t_sample mul_375 = (m_history_96 * ((t_sample)0.999));
			t_sample add_377 = (mul_374 + mul_375);
			t_sample gen_379 = add_377;
			t_sample history_376_next_378 = fixdenorm(add_377);
			t_sample mul_369 = (m_history_95 * ((t_sample)0.999));
			t_sample add_371 = (mul_368 + mul_369);
			t_sample gen_373 = add_371;
			t_sample history_370_next_372 = fixdenorm(add_371);
			t_sample mul_455 = (m_history_94 * ((t_sample)0.999));
			t_sample add_457 = (mul_454 + mul_455);
			t_sample gen_459 = add_457;
			t_sample history_456_next_458 = fixdenorm(add_457);
			t_sample sub_2821 = (gen_459 - ((int)0));
			t_sample scale_2818 = ((safepow((sub_2821 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_436 = scale_2818;
			t_sample sqrt_441 = sqrt(gen_459);
			t_sample rsub_460 = (((int)1) - gen_459);
			t_sample sqrt_442 = sqrt(rsub_460);
			t_sample mul_225 = (m_history_93 * ((t_sample)0.999));
			t_sample add_227 = (mul_224 + mul_225);
			t_sample gen_229 = add_227;
			t_sample history_226_next_228 = fixdenorm(add_227);
			t_sample mul_1632 = (m_history_92 * ((t_sample)0.999));
			t_sample add_1634 = (mul_1631 + mul_1632);
			t_sample gen_1636 = add_1634;
			t_sample history_1633_next_1635 = fixdenorm(add_1634);
			t_sample mul_393 = (m_history_91 * ((t_sample)0.999));
			t_sample add_395 = (mul_392 + mul_393);
			t_sample gen_397 = add_395;
			t_sample history_394_next_396 = fixdenorm(add_395);
			t_sample mul_387 = (m_history_90 * ((t_sample)0.999));
			t_sample add_389 = (mul_386 + mul_387);
			t_sample gen_391 = add_389;
			t_sample history_388_next_390 = fixdenorm(add_389);
			t_sample mul_2697 = (m_history_89 * ((t_sample)0.999));
			t_sample add_2699 = (mul_2696 + mul_2697);
			t_sample gen_2701 = add_2699;
			t_sample history_2698_next_2700 = fixdenorm(add_2699);
			t_sample mul_230 = (((int)23) * gen_229);
			t_sample mul_423 = (m_history_88 * ((t_sample)0.999));
			t_sample add_425 = (mul_422 + mul_423);
			t_sample gen_427 = add_425;
			t_sample history_424_next_426 = fixdenorm(add_425);
			t_sample mul_465 = (mul_417 * gen_427);
			t_sample mul_447 = (mul_416 * gen_427);
			t_sample omega = safediv((gen_397 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((int)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) - cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((((int)1) - cs) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_2623 = a2;
			t_sample expr_2624 = a1;
			t_sample expr_2625 = a2;
			t_sample expr_2626 = b1;
			t_sample expr_2627 = b2;
			t_sample omega_2633 = safediv((gen_391 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_2629 = sin(omega_2633);
			t_sample cs_2636 = cos(omega_2633);
			t_sample alpha_2631 = ((sn_2629 * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b_2634 = safediv(((int)1), (((int)1) + alpha_2631));
			t_sample a_2635 = (((((int)1) + cs_2636) * ((t_sample)0.5)) * b_2634);
			t_sample a_2630 = ((-(((int)1) + cs_2636)) * b_2634);
			t_sample b_2628 = ((((int)-2) * cs_2636) * b_2634);
			t_sample b_2632 = ((((int)1) - alpha_2631) * b_2634);
			t_sample expr_2618 = a_2635;
			t_sample expr_2619 = a_2630;
			t_sample expr_2620 = a_2635;
			t_sample expr_2621 = b_2628;
			t_sample expr_2622 = b_2632;
			t_sample mul_166 = (mul_465 * expr_2623);
			t_sample mul_156 = (mul_447 * expr_2623);
			t_sample mul_163 = (m_history_83 * expr_2624);
			t_sample mul_153 = (m_history_82 * expr_2624);
			t_sample mul_161 = (m_history_86 * expr_2625);
			t_sample mul_151 = (m_history_87 * expr_2625);
			t_sample mul_157 = (m_history_85 * expr_2627);
			t_sample mul_147 = (m_history_84 * expr_2627);
			t_sample mul_159 = (m_history_81 * expr_2626);
			t_sample sub_165 = (((mul_161 + mul_163) + mul_166) - (mul_159 + mul_157));
			t_sample gen_175 = sub_165;
			t_sample mul_149 = (m_history_80 * expr_2626);
			t_sample sub_155 = (((mul_156 + mul_153) + mul_151) - (mul_149 + mul_147));
			t_sample gen_176 = sub_155;
			t_sample history_152_next_167 = fixdenorm(m_history_82);
			t_sample history_162_next_168 = fixdenorm(m_history_83);
			t_sample history_158_next_169 = fixdenorm(m_history_81);
			t_sample history_148_next_170 = fixdenorm(m_history_80);
			t_sample history_164_next_171 = fixdenorm(mul_465);
			t_sample history_154_next_172 = fixdenorm(mul_447);
			t_sample history_160_next_173 = fixdenorm(sub_165);
			t_sample history_150_next_174 = fixdenorm(sub_155);
			t_sample mul_131 = (gen_175 * expr_2618);
			t_sample mul_121 = (gen_176 * expr_2618);
			t_sample mul_128 = (m_history_75 * expr_2619);
			t_sample mul_118 = (m_history_74 * expr_2619);
			t_sample mul_126 = (m_history_77 * expr_2620);
			t_sample mul_116 = (m_history_76 * expr_2620);
			t_sample mul_122 = (m_history_79 * expr_2622);
			t_sample mul_112 = (m_history_78 * expr_2622);
			t_sample mul_124 = (m_history_73 * expr_2621);
			t_sample sub_130 = (((mul_126 + mul_128) + mul_131) - (mul_124 + mul_122));
			t_sample gen_140 = sub_130;
			t_sample mul_114 = (m_history_72 * expr_2621);
			t_sample sub_120 = (((mul_121 + mul_118) + mul_116) - (mul_114 + mul_112));
			t_sample gen_141 = sub_120;
			t_sample history_123_next_132 = fixdenorm(m_history_73);
			t_sample history_113_next_133 = fixdenorm(m_history_72);
			t_sample history_127_next_134 = fixdenorm(m_history_75);
			t_sample history_117_next_135 = fixdenorm(m_history_74);
			t_sample history_129_next_136 = fixdenorm(gen_175);
			t_sample history_119_next_137 = fixdenorm(gen_176);
			t_sample history_125_next_138 = fixdenorm(sub_130);
			t_sample history_115_next_139 = fixdenorm(sub_120);
			t_sample mix_2822 = (mul_465 + (gen_2701 * (gen_140 - mul_465)));
			t_sample mix_2364 = mix_2822;
			t_sample gen_2637 = mix_2364;
			t_sample mix_2823 = (mul_447 + (gen_2701 * (gen_141 - mul_447)));
			t_sample mix_2407 = mix_2823;
			t_sample gen_2638 = mix_2407;
			t_sample mul_429 = (m_history_71 * ((t_sample)0.999));
			t_sample add_431 = (mul_428 + mul_429);
			t_sample gen_433 = add_431;
			t_sample history_430_next_432 = fixdenorm(add_431);
			t_sample rsub_715 = (((int)1) - gen_1636);
			t_sample mul_689 = (div_704 * gen_229);
			t_sample mul_692 = (((int)1188) * mul_689);
			t_sample mul_648 = (m_history_70 * ((t_sample)0.999));
			t_sample mul_647 = (mul_692 * ((t_sample)0.001));
			t_sample add_650 = (mul_647 + mul_648);
			t_sample gen_652 = add_650;
			t_sample history_649_next_651 = fixdenorm(add_650);
			t_sample gen_713 = gen_652;
			t_sample mul_700 = (((int)1491) * mul_689);
			t_sample mul_672 = (m_history_69 * ((t_sample)0.999));
			t_sample mul_671 = (mul_700 * ((t_sample)0.001));
			t_sample add_674 = (mul_671 + mul_672);
			t_sample gen_676 = add_674;
			t_sample history_673_next_675 = fixdenorm(add_674);
			t_sample gen_709 = gen_676;
			t_sample mul_698 = (((int)1422) * mul_689);
			t_sample mul_666 = (m_history_68 * ((t_sample)0.999));
			t_sample mul_665 = (mul_698 * ((t_sample)0.001));
			t_sample add_668 = (mul_665 + mul_666);
			t_sample gen_670 = add_668;
			t_sample history_667_next_669 = fixdenorm(add_668);
			t_sample gen_710 = gen_670;
			t_sample mul_705 = (((int)1557) * mul_689);
			t_sample mul_684 = (m_history_67 * ((t_sample)0.999));
			t_sample mul_683 = (mul_705 * ((t_sample)0.001));
			t_sample add_686 = (mul_683 + mul_684);
			t_sample gen_688 = add_686;
			t_sample history_685_next_687 = fixdenorm(add_686);
			t_sample gen_707 = gen_688;
			t_sample mul_694 = (((int)1356) * mul_689);
			t_sample mul_654 = (m_history_66 * ((t_sample)0.999));
			t_sample mul_653 = (mul_694 * ((t_sample)0.001));
			t_sample add_656 = (mul_653 + mul_654);
			t_sample gen_658 = add_656;
			t_sample history_655_next_657 = fixdenorm(add_656);
			t_sample gen_712 = gen_658;
			t_sample mul_696 = (((int)1277) * mul_689);
			t_sample mul_660 = (m_history_65 * ((t_sample)0.999));
			t_sample mul_659 = (mul_696 * ((t_sample)0.001));
			t_sample add_662 = (mul_659 + mul_660);
			t_sample gen_664 = add_662;
			t_sample history_661_next_663 = fixdenorm(add_662);
			t_sample gen_711 = gen_664;
			t_sample mul_690 = (((int)1116) * mul_689);
			t_sample mul_642 = (m_history_64 * ((t_sample)0.999));
			t_sample mul_641 = (mul_690 * ((t_sample)0.001));
			t_sample add_644 = (mul_641 + mul_642);
			t_sample gen_646 = add_644;
			t_sample history_643_next_645 = fixdenorm(add_644);
			t_sample gen_714 = gen_646;
			t_sample mul_702 = (((int)1617) * mul_689);
			t_sample mul_678 = (m_history_63 * ((t_sample)0.999));
			t_sample mul_677 = (mul_702 * ((t_sample)0.001));
			t_sample add_680 = (mul_677 + mul_678);
			t_sample gen_682 = add_680;
			t_sample history_679_next_681 = fixdenorm(add_680);
			t_sample gen_708 = gen_682;
			t_sample rsub_717 = (((int)1) - rsub_715);
			t_sample mul_719 = (m_history_61 * rsub_717);
			t_sample add_716 = (((int)0) + gen_714);
			t_sample tap_725 = m_delay_62.read_linear(add_716);
			t_sample mul_722 = (tap_725 * rsub_715);
			t_sample add_721 = (mul_722 + mul_719);
			t_sample mul_718 = (add_721 * gen_433);
			t_sample add_723 = (gen_2637 + mul_718);
			t_sample gen_727 = add_723;
			t_sample history_720_next_726 = fixdenorm(add_721);
			t_sample rsub_729 = (((int)1) - rsub_715);
			t_sample mul_731 = (m_history_59 * rsub_729);
			t_sample add_728 = (((int)0) + gen_713);
			t_sample tap_737 = m_delay_60.read_linear(add_728);
			t_sample mul_734 = (tap_737 * rsub_715);
			t_sample add_733 = (mul_734 + mul_731);
			t_sample mul_730 = (add_733 * gen_433);
			t_sample add_735 = (gen_2637 + mul_730);
			t_sample gen_739 = add_735;
			t_sample history_732_next_738 = fixdenorm(add_733);
			t_sample rsub_741 = (((int)1) - rsub_715);
			t_sample mul_743 = (m_history_57 * rsub_741);
			t_sample add_740 = (((int)0) + gen_712);
			t_sample tap_749 = m_delay_58.read_linear(add_740);
			t_sample mul_746 = (tap_749 * rsub_715);
			t_sample add_745 = (mul_746 + mul_743);
			t_sample mul_742 = (add_745 * gen_433);
			t_sample add_747 = (gen_2637 + mul_742);
			t_sample gen_751 = add_747;
			t_sample history_744_next_750 = fixdenorm(add_745);
			t_sample rsub_753 = (((int)1) - rsub_715);
			t_sample mul_755 = (m_history_55 * rsub_753);
			t_sample add_752 = (((int)0) + gen_711);
			t_sample tap_761 = m_delay_56.read_linear(add_752);
			t_sample mul_758 = (tap_761 * rsub_715);
			t_sample add_757 = (mul_758 + mul_755);
			t_sample mul_754 = (add_757 * gen_433);
			t_sample add_759 = (gen_2637 + mul_754);
			t_sample gen_763 = add_759;
			t_sample history_756_next_762 = fixdenorm(add_757);
			t_sample rsub_765 = (((int)1) - rsub_715);
			t_sample mul_767 = (m_history_53 * rsub_765);
			t_sample add_764 = (((int)0) + gen_710);
			t_sample tap_773 = m_delay_54.read_linear(add_764);
			t_sample mul_770 = (tap_773 * rsub_715);
			t_sample add_769 = (mul_770 + mul_767);
			t_sample mul_766 = (add_769 * gen_433);
			t_sample add_771 = (gen_2637 + mul_766);
			t_sample gen_775 = add_771;
			t_sample history_768_next_774 = fixdenorm(add_769);
			t_sample rsub_777 = (((int)1) - rsub_715);
			t_sample mul_779 = (m_history_51 * rsub_777);
			t_sample add_776 = (((int)0) + gen_709);
			t_sample tap_785 = m_delay_52.read_linear(add_776);
			t_sample mul_782 = (tap_785 * rsub_715);
			t_sample add_781 = (mul_782 + mul_779);
			t_sample mul_778 = (add_781 * gen_433);
			t_sample add_783 = (gen_2637 + mul_778);
			t_sample gen_787 = add_783;
			t_sample history_780_next_786 = fixdenorm(add_781);
			t_sample rsub_789 = (((int)1) - rsub_715);
			t_sample mul_791 = (m_history_49 * rsub_789);
			t_sample add_788 = (((int)0) + gen_708);
			t_sample tap_797 = m_delay_50.read_linear(add_788);
			t_sample mul_794 = (tap_797 * rsub_715);
			t_sample add_793 = (mul_794 + mul_791);
			t_sample mul_790 = (add_793 * gen_433);
			t_sample add_795 = (gen_2637 + mul_790);
			t_sample gen_799 = add_795;
			t_sample history_792_next_798 = fixdenorm(add_793);
			t_sample rsub_801 = (((int)1) - rsub_715);
			t_sample mul_803 = (m_history_47 * rsub_801);
			t_sample add_800 = (((int)0) + gen_707);
			t_sample tap_809 = m_delay_48.read_linear(add_800);
			t_sample mul_806 = (tap_809 * rsub_715);
			t_sample add_805 = (mul_806 + mul_803);
			t_sample mul_802 = (add_805 * gen_433);
			t_sample add_807 = (gen_2637 + mul_802);
			t_sample gen_811 = add_807;
			t_sample history_804_next_810 = fixdenorm(add_805);
			t_sample mul_812 = ((((((((gen_811 + gen_799) + gen_787) + gen_775) + gen_763) + gen_751) + gen_739) + gen_727) * ((t_sample)0.125));
			t_sample gen_813 = mul_812;
			t_sample mul_343 = (gen_813 * ((t_sample)-0.5));
			t_sample mul_333 = (div_334 * gen_229);
			t_sample mul_335 = (((int)255) * mul_333);
			t_sample add_337 = (((int)0) + mul_335);
			t_sample tap_345 = m_delay_46.read_linear(add_337);
			t_sample tap_340 = m_delay_45.read_linear(add_337);
			t_sample mul_338 = (tap_340 * ((t_sample)0.5));
			t_sample add_341 = (mul_343 + (tap_345 + mul_338));
			t_sample gen_346 = add_341;
			t_sample mul_329 = (gen_346 * ((t_sample)-0.5));
			t_sample mul_319 = (div_320 * gen_229);
			t_sample mul_321 = (((int)556) * mul_319);
			t_sample add_323 = (((int)0) + mul_321);
			t_sample tap_331 = m_delay_44.read_linear(add_323);
			t_sample tap_326 = m_delay_43.read_linear(add_323);
			t_sample mul_324 = (tap_326 * ((t_sample)0.5));
			t_sample add_327 = (mul_329 + (tap_331 + mul_324));
			t_sample gen_332 = add_327;
			t_sample mul_315 = (gen_332 * ((t_sample)-0.5));
			t_sample mul_305 = (div_306 * gen_229);
			t_sample mul_307 = (((int)441) * mul_305);
			t_sample add_309 = (((int)0) + mul_307);
			t_sample tap_317 = m_delay_42.read_linear(add_309);
			t_sample tap_312 = m_delay_41.read_linear(add_309);
			t_sample mul_310 = (tap_312 * ((t_sample)0.5));
			t_sample add_313 = (mul_315 + (tap_317 + mul_310));
			t_sample gen_318 = add_313;
			t_sample mul_301 = (gen_318 * ((t_sample)-0.5));
			t_sample mul_291 = (div_292 * gen_229);
			t_sample mul_293 = (((int)341) * mul_291);
			t_sample add_295 = (((int)0) + mul_293);
			t_sample tap_303 = m_delay_40.read_linear(add_295);
			t_sample tap_298 = m_delay_39.read_linear(add_295);
			t_sample mul_296 = (tap_298 * ((t_sample)0.5));
			t_sample add_299 = (mul_301 + (tap_303 + mul_296));
			t_sample gen_304 = add_299;
			t_sample gen_347 = gen_304;
			t_sample rsub_542 = (((int)1) - gen_1636);
			t_sample mul_516 = (div_531 * gen_229);
			t_sample mul_525 = (((int)1422) * mul_516);
			t_sample mul_493 = (m_history_38 * ((t_sample)0.999));
			t_sample mul_492 = (mul_525 * ((t_sample)0.001));
			t_sample add_495 = (mul_492 + mul_493);
			t_sample gen_497 = add_495;
			t_sample history_494_next_496 = fixdenorm(add_495);
			t_sample gen_537 = gen_497;
			t_sample mul_521 = (((int)1356) * mul_516);
			t_sample mul_481 = (m_history_37 * ((t_sample)0.999));
			t_sample mul_480 = (mul_521 * ((t_sample)0.001));
			t_sample add_483 = (mul_480 + mul_481);
			t_sample gen_485 = add_483;
			t_sample history_482_next_484 = fixdenorm(add_483);
			t_sample gen_539 = gen_485;
			t_sample mul_529 = (((int)1617) * mul_516);
			t_sample mul_505 = (m_history_36 * ((t_sample)0.999));
			t_sample mul_504 = (mul_529 * ((t_sample)0.001));
			t_sample add_507 = (mul_504 + mul_505);
			t_sample gen_509 = add_507;
			t_sample history_506_next_508 = fixdenorm(add_507);
			t_sample gen_535 = gen_509;
			t_sample mul_517 = (((int)1116) * mul_516);
			t_sample mul_469 = (m_history_35 * ((t_sample)0.999));
			t_sample mul_468 = (mul_517 * ((t_sample)0.001));
			t_sample add_471 = (mul_468 + mul_469);
			t_sample gen_473 = add_471;
			t_sample history_470_next_472 = fixdenorm(add_471);
			t_sample gen_541 = gen_473;
			t_sample mul_523 = (((int)1277) * mul_516);
			t_sample mul_487 = (m_history_34 * ((t_sample)0.999));
			t_sample mul_486 = (mul_523 * ((t_sample)0.001));
			t_sample add_489 = (mul_486 + mul_487);
			t_sample gen_491 = add_489;
			t_sample history_488_next_490 = fixdenorm(add_489);
			t_sample gen_538 = gen_491;
			t_sample mul_527 = (((int)1491) * mul_516);
			t_sample mul_499 = (m_history_33 * ((t_sample)0.999));
			t_sample mul_498 = (mul_527 * ((t_sample)0.001));
			t_sample add_501 = (mul_498 + mul_499);
			t_sample gen_503 = add_501;
			t_sample history_500_next_502 = fixdenorm(add_501);
			t_sample gen_536 = gen_503;
			t_sample mul_519 = (((int)1188) * mul_516);
			t_sample mul_475 = (m_history_32 * ((t_sample)0.999));
			t_sample mul_474 = (mul_519 * ((t_sample)0.001));
			t_sample add_477 = (mul_474 + mul_475);
			t_sample gen_479 = add_477;
			t_sample history_476_next_478 = fixdenorm(add_477);
			t_sample gen_540 = gen_479;
			t_sample mul_532 = (((int)1557) * mul_516);
			t_sample mul_511 = (m_history_31 * ((t_sample)0.999));
			t_sample mul_510 = (mul_532 * ((t_sample)0.001));
			t_sample add_513 = (mul_510 + mul_511);
			t_sample gen_515 = add_513;
			t_sample history_512_next_514 = fixdenorm(add_513);
			t_sample gen_534 = gen_515;
			t_sample rsub_544 = (((int)1) - rsub_542);
			t_sample mul_546 = (m_history_29 * rsub_544);
			t_sample add_543 = (mul_230 + gen_541);
			t_sample tap_552 = m_delay_30.read_linear(add_543);
			t_sample mul_549 = (tap_552 * rsub_542);
			t_sample add_548 = (mul_549 + mul_546);
			t_sample mul_545 = (add_548 * gen_433);
			t_sample add_550 = (gen_2638 + mul_545);
			t_sample gen_554 = add_550;
			t_sample history_547_next_553 = fixdenorm(add_548);
			t_sample rsub_556 = (((int)1) - rsub_542);
			t_sample mul_558 = (m_history_27 * rsub_556);
			t_sample add_555 = (mul_230 + gen_540);
			t_sample tap_564 = m_delay_28.read_linear(add_555);
			t_sample mul_561 = (tap_564 * rsub_542);
			t_sample add_560 = (mul_561 + mul_558);
			t_sample mul_557 = (add_560 * gen_433);
			t_sample add_562 = (gen_2638 + mul_557);
			t_sample gen_566 = add_562;
			t_sample history_559_next_565 = fixdenorm(add_560);
			t_sample rsub_568 = (((int)1) - rsub_542);
			t_sample mul_570 = (m_history_25 * rsub_568);
			t_sample add_567 = (mul_230 + gen_539);
			t_sample tap_576 = m_delay_26.read_linear(add_567);
			t_sample mul_573 = (tap_576 * rsub_542);
			t_sample add_572 = (mul_573 + mul_570);
			t_sample mul_569 = (add_572 * gen_433);
			t_sample add_574 = (gen_2638 + mul_569);
			t_sample gen_578 = add_574;
			t_sample history_571_next_577 = fixdenorm(add_572);
			t_sample rsub_580 = (((int)1) - rsub_542);
			t_sample mul_582 = (m_history_23 * rsub_580);
			t_sample add_579 = (mul_230 + gen_538);
			t_sample tap_588 = m_delay_24.read_linear(add_579);
			t_sample mul_585 = (tap_588 * rsub_542);
			t_sample add_584 = (mul_585 + mul_582);
			t_sample mul_581 = (add_584 * gen_433);
			t_sample add_586 = (gen_2638 + mul_581);
			t_sample gen_590 = add_586;
			t_sample history_583_next_589 = fixdenorm(add_584);
			t_sample rsub_592 = (((int)1) - rsub_542);
			t_sample mul_594 = (m_history_21 * rsub_592);
			t_sample add_591 = (mul_230 + gen_537);
			t_sample tap_600 = m_delay_22.read_linear(add_591);
			t_sample mul_597 = (tap_600 * rsub_542);
			t_sample add_596 = (mul_597 + mul_594);
			t_sample mul_593 = (add_596 * gen_433);
			t_sample add_598 = (gen_2638 + mul_593);
			t_sample gen_602 = add_598;
			t_sample history_595_next_601 = fixdenorm(add_596);
			t_sample rsub_604 = (((int)1) - rsub_542);
			t_sample mul_606 = (m_history_19 * rsub_604);
			t_sample add_603 = (mul_230 + gen_536);
			t_sample tap_612 = m_delay_20.read_linear(add_603);
			t_sample mul_609 = (tap_612 * rsub_542);
			t_sample add_608 = (mul_609 + mul_606);
			t_sample mul_605 = (add_608 * gen_433);
			t_sample add_610 = (gen_2638 + mul_605);
			t_sample gen_614 = add_610;
			t_sample history_607_next_613 = fixdenorm(add_608);
			t_sample rsub_616 = (((int)1) - rsub_542);
			t_sample mul_618 = (m_history_17 * rsub_616);
			t_sample add_615 = (mul_230 + gen_535);
			t_sample tap_624 = m_delay_18.read_linear(add_615);
			t_sample mul_621 = (tap_624 * rsub_542);
			t_sample add_620 = (mul_621 + mul_618);
			t_sample mul_617 = (add_620 * gen_433);
			t_sample add_622 = (gen_2638 + mul_617);
			t_sample gen_626 = add_622;
			t_sample history_619_next_625 = fixdenorm(add_620);
			t_sample rsub_628 = (((int)1) - rsub_542);
			t_sample mul_630 = (m_history_15 * rsub_628);
			t_sample add_627 = (mul_230 + gen_534);
			t_sample tap_636 = m_delay_16.read_linear(add_627);
			t_sample mul_633 = (tap_636 * rsub_542);
			t_sample add_632 = (mul_633 + mul_630);
			t_sample mul_629 = (add_632 * gen_433);
			t_sample add_634 = (gen_2638 + mul_629);
			t_sample gen_638 = add_634;
			t_sample history_631_next_637 = fixdenorm(add_632);
			t_sample mul_639 = ((((((((gen_638 + gen_626) + gen_614) + gen_602) + gen_590) + gen_578) + gen_566) + gen_554) * ((t_sample)0.125));
			t_sample gen_640 = mul_639;
			t_sample mul_284 = (gen_640 * ((t_sample)-0.5));
			t_sample mul_274 = (div_275 * gen_229);
			t_sample mul_276 = (((int)255) * mul_274);
			t_sample add_278 = (((int)0) + mul_276);
			t_sample tap_286 = m_delay_14.read_linear(add_278);
			t_sample tap_281 = m_delay_13.read_linear(add_278);
			t_sample mul_279 = (tap_281 * ((t_sample)0.5));
			t_sample add_282 = (mul_284 + (tap_286 + mul_279));
			t_sample gen_287 = add_282;
			t_sample mul_270 = (gen_287 * ((t_sample)-0.5));
			t_sample mul_260 = (div_261 * gen_229);
			t_sample mul_262 = (((int)556) * mul_260);
			t_sample add_264 = (((int)0) + mul_262);
			t_sample tap_272 = m_delay_12.read_linear(add_264);
			t_sample tap_267 = m_delay_11.read_linear(add_264);
			t_sample mul_265 = (tap_267 * ((t_sample)0.5));
			t_sample add_268 = (mul_270 + (tap_272 + mul_265));
			t_sample gen_273 = add_268;
			t_sample mul_256 = (gen_273 * ((t_sample)-0.5));
			t_sample mul_246 = (div_247 * gen_229);
			t_sample mul_248 = (((int)441) * mul_246);
			t_sample add_250 = (((int)0) + mul_248);
			t_sample tap_258 = m_delay_10.read_linear(add_250);
			t_sample tap_253 = m_delay_9.read_linear(add_250);
			t_sample mul_251 = (tap_253 * ((t_sample)0.5));
			t_sample add_254 = (mul_256 + (tap_258 + mul_251));
			t_sample gen_259 = add_254;
			t_sample mul_242 = (gen_259 * ((t_sample)-0.5));
			t_sample mul_232 = (div_233 * gen_229);
			t_sample mul_234 = (((int)341) * mul_232);
			t_sample add_236 = (((int)0) + mul_234);
			t_sample tap_244 = m_delay_8.read_linear(add_236);
			t_sample tap_239 = m_delay_7.read_linear(add_236);
			t_sample mul_237 = (tap_239 * ((t_sample)0.5));
			t_sample add_240 = (mul_242 + (tap_244 + mul_237));
			t_sample gen_245 = add_240;
			t_sample gen_288 = gen_245;
			t_sample add_446 = (gen_347 + gen_288);
			t_sample mul_444 = (add_446 * sqrt_442);
			t_sample sub_445 = (gen_347 - gen_288);
			t_sample mul_443 = (sub_445 * sqrt_441);
			t_sample add_440 = (mul_444 + mul_443);
			t_sample mul_435 = (add_440 * scale_436);
			t_sample sub_439 = (mul_444 - mul_443);
			t_sample mul_434 = (sub_439 * scale_436);
			t_sample return_191;
			t_sample return_192;
			eq3bandas_d_d_d_d_d_d_d_d_i(mul_435, mul_434, gen_223, gen_217, gen_211, gen_385, gen_379, gen_373, ((int)1), return_191, return_192);
			t_sample expr_412 = return_191;
			t_sample expr_413 = return_192;
			t_sample gen_415 = expr_413;
			t_sample gen_414 = expr_412;
			t_sample mix_2824 = (mul_435 + (gen_203 * (gen_414 - mul_435)));
			t_sample mix_205 = mix_2824;
			t_sample mix_2825 = (mul_434 + (gen_203 * (gen_415 - mul_434)));
			t_sample mix_204 = mix_2825;
			t_sample dbtoa_41 = dbtoa(gen_8);
			t_sample mstosamps_78 = (gen_16 * (samplerate * 0.001));
			t_sample mstosamps_77 = (gen_22 * (samplerate * 0.001));
			t_sample tap_74 = m_delay_6.read_step(((int)300));
			t_sample mul_67 = (mix_204 * mix_204);
			t_sample add_71 = (m_history_5 + mul_67);
			t_sample sub_70 = (add_71 - tap_74);
			t_sample div_68 = (sub_70 * ((t_sample)0.0033333333333333));
			t_sample sqrt_66 = sqrt(div_68);
			t_sample gen_76 = sqrt_66;
			t_sample history_69_next_75 = fixdenorm(sub_70);
			t_sample atodb_65 = atodb(gen_76);
			t_sample max_44 = ((atodb_65 < maxb_193) ? maxb_193 : atodb_65);
			int gt_64 = (max_44 > gen_34);
			t_sample mul_47 = (m_history_4 * ((t_sample)0.999));
			t_sample mul_46 = (gt_64 * ((t_sample)0.001));
			t_sample add_49 = (mul_46 + mul_47);
			t_sample gen_51 = add_49;
			t_sample history_48_next_50 = fixdenorm(add_49);
			t_sample sub_63 = (gen_34 - max_44);
			t_sample rdiv_84 = safediv(((int)1), gen_28);
			t_sample rsub_83 = (((int)1) - rdiv_84);
			t_sample mul_62 = (sub_63 * rsub_83);
			t_sample dbtoa_60 = dbtoa(mul_62);
			t_sample orange_2828 = (dbtoa_60 - ((int)1));
			t_sample sub_2829 = (gen_51 - ((int)0));
			t_sample scale_2826 = ((safepow((sub_2829 * ((t_sample)1)), ((int)1)) * orange_2828) + ((int)1));
			t_sample iup_195 = (1 / maximum(1, abs(mstosamps_78)));
			t_sample idown_196 = (1 / maximum(1, abs(mstosamps_77)));
			__m_slide_194 = fixdenorm((__m_slide_194 + (((scale_2826 > __m_slide_194) ? iup_195 : idown_196) * (scale_2826 - __m_slide_194))));
			t_sample slide_59 = __m_slide_194;
			t_sample mul_58 = (mix_204 * slide_59);
			t_sample mul_42 = (mul_58 * dbtoa_41);
			t_sample tap_96 = m_delay_3.read_step(((int)300));
			t_sample mul_89 = (mix_205 * mix_205);
			t_sample add_93 = (m_history_2 + mul_89);
			t_sample sub_92 = (add_93 - tap_96);
			t_sample div_90 = (sub_92 * ((t_sample)0.0033333333333333));
			t_sample sqrt_88 = sqrt(div_90);
			t_sample gen_98 = sqrt_88;
			t_sample history_91_next_97 = fixdenorm(sub_92);
			t_sample atodb_87 = atodb(gen_98);
			t_sample max_45 = ((atodb_87 < maxb_197) ? maxb_197 : atodb_87);
			int gt_86 = (max_45 > gen_34);
			t_sample mul_53 = (m_history_1 * ((t_sample)0.999));
			t_sample mul_52 = (gt_86 * ((t_sample)0.001));
			t_sample add_55 = (mul_52 + mul_53);
			t_sample gen_57 = add_55;
			t_sample history_54_next_56 = fixdenorm(add_55);
			t_sample sub_85 = (gen_34 - max_45);
			t_sample mul_82 = (sub_85 * rsub_83);
			t_sample dbtoa_80 = dbtoa(mul_82);
			t_sample orange_2832 = (dbtoa_80 - ((int)1));
			t_sample sub_2833 = (gen_57 - ((int)0));
			t_sample scale_2830 = ((safepow((sub_2833 * ((t_sample)1)), ((int)1)) * orange_2832) + ((int)1));
			t_sample iup_199 = (1 / maximum(1, abs(mstosamps_78)));
			t_sample idown_200 = (1 / maximum(1, abs(mstosamps_77)));
			__m_slide_198 = fixdenorm((__m_slide_198 + (((scale_2830 > __m_slide_198) ? iup_199 : idown_200) * (scale_2830 - __m_slide_198))));
			t_sample slide_79 = __m_slide_198;
			t_sample mul_99 = (mix_205 * slide_79);
			t_sample mul_43 = (mul_99 * dbtoa_41);
			t_sample mix_2834 = (mix_204 + (gen_40 * (mul_42 - mix_204)));
			t_sample mix_2835 = (mix_205 + (gen_40 * (mul_43 - mix_205)));
			t_sample mix_2836 = (mix_2816 + (gen_353 * (mix_2834 - mix_2816)));
			t_sample mul_366 = (mix_2836 * gen_365);
			t_sample mix_2837 = (mul_366 + (gen_1650 * (in2 - mul_366)));
			t_sample dcblock_9 = __m_dcblock_201(mix_2837);
			t_sample out2 = dcblock_9;
			t_sample mix_2838 = (mix_2817 + (gen_353 * (mix_2835 - mix_2817)));
			t_sample mul_367 = (mix_2838 * gen_365);
			t_sample mix_2839 = (mul_367 + (gen_1650 * (in1 - mul_367)));
			t_sample dcblock_10 = __m_dcblock_202(mix_2839);
			t_sample out1 = dcblock_10;
			m_history_137 = history_1647_next_1649;
			m_history_111 = history_450_next_452;
			m_history_110 = history_350_next_352;
			m_history_109 = history_362_next_364;
			m_history_108 = history_37_next_39;
			m_history_107 = history_31_next_33;
			m_history_106 = history_25_next_27;
			m_history_105 = history_19_next_21;
			m_history_104 = history_13_next_15;
			m_history_103 = history_5_next_7;
			m_history_102 = history_1639_next_1641;
			m_history_101 = history_200_next_202;
			m_history_100 = history_220_next_222;
			m_history_99 = history_214_next_216;
			m_history_98 = history_208_next_210;
			m_history_97 = history_382_next_384;
			m_history_96 = history_376_next_378;
			m_history_95 = history_370_next_372;
			m_history_94 = history_456_next_458;
			m_history_93 = history_226_next_228;
			m_history_92 = history_1633_next_1635;
			m_history_91 = history_394_next_396;
			m_history_90 = history_388_next_390;
			m_history_89 = history_2698_next_2700;
			m_history_88 = history_424_next_426;
			m_history_87 = history_152_next_167;
			m_history_78 = history_113_next_133;
			m_history_77 = history_127_next_134;
			m_history_76 = history_117_next_135;
			m_history_75 = history_129_next_136;
			m_history_74 = history_119_next_137;
			m_history_73 = history_125_next_138;
			m_history_72 = history_115_next_139;
			m_history_79 = history_123_next_132;
			m_history_86 = history_162_next_168;
			m_history_85 = history_158_next_169;
			m_history_84 = history_148_next_170;
			m_history_83 = history_164_next_171;
			m_history_82 = history_154_next_172;
			m_history_81 = history_160_next_173;
			m_history_80 = history_150_next_174;
			m_history_71 = history_430_next_432;
			m_history_70 = history_649_next_651;
			m_history_47 = history_804_next_810;
			m_delay_48.write(add_807);
			m_history_49 = history_792_next_798;
			m_delay_50.write(add_795);
			m_history_51 = history_780_next_786;
			m_delay_52.write(add_783);
			m_history_53 = history_768_next_774;
			m_delay_54.write(add_771);
			m_history_55 = history_756_next_762;
			m_delay_56.write(add_759);
			m_history_57 = history_744_next_750;
			m_delay_58.write(add_747);
			m_history_59 = history_732_next_738;
			m_delay_60.write(add_735);
			m_history_61 = history_720_next_726;
			m_delay_62.write(add_723);
			m_history_69 = history_673_next_675;
			m_history_68 = history_667_next_669;
			m_history_67 = history_685_next_687;
			m_history_66 = history_655_next_657;
			m_history_65 = history_661_next_663;
			m_history_64 = history_643_next_645;
			m_history_63 = history_679_next_681;
			m_delay_46.write(gen_813);
			m_delay_39.write(add_299);
			m_delay_40.write(gen_318);
			m_delay_41.write(add_313);
			m_delay_42.write(gen_332);
			m_delay_43.write(add_327);
			m_delay_44.write(gen_346);
			m_delay_45.write(add_341);
			m_history_38 = history_494_next_496;
			m_history_15 = history_631_next_637;
			m_delay_16.write(add_634);
			m_history_17 = history_619_next_625;
			m_delay_18.write(add_622);
			m_history_19 = history_607_next_613;
			m_delay_20.write(add_610);
			m_history_21 = history_595_next_601;
			m_delay_22.write(add_598);
			m_history_23 = history_583_next_589;
			m_delay_24.write(add_586);
			m_history_25 = history_571_next_577;
			m_delay_26.write(add_574);
			m_history_27 = history_559_next_565;
			m_delay_28.write(add_562);
			m_history_29 = history_547_next_553;
			m_delay_30.write(add_550);
			m_history_37 = history_482_next_484;
			m_history_36 = history_506_next_508;
			m_history_35 = history_470_next_472;
			m_history_34 = history_488_next_490;
			m_history_33 = history_500_next_502;
			m_history_32 = history_476_next_478;
			m_history_31 = history_512_next_514;
			m_delay_14.write(gen_640);
			m_delay_7.write(add_240);
			m_delay_8.write(gen_259);
			m_delay_9.write(add_254);
			m_delay_10.write(gen_273);
			m_delay_11.write(add_268);
			m_delay_12.write(gen_287);
			m_delay_13.write(add_282);
			m_delay_6.write(mul_67);
			m_history_5 = history_69_next_75;
			m_history_4 = history_48_next_50;
			m_delay_3.write(mul_89);
			m_history_2 = history_91_next_97;
			m_history_1 = history_54_next_56;
			m_delay_3.step();
			m_delay_6.step();
			m_delay_7.step();
			m_delay_8.step();
			m_delay_9.step();
			m_delay_10.step();
			m_delay_11.step();
			m_delay_12.step();
			m_delay_13.step();
			m_delay_14.step();
			m_delay_16.step();
			m_delay_18.step();
			m_delay_20.step();
			m_delay_22.step();
			m_delay_24.step();
			m_delay_26.step();
			m_delay_28.step();
			m_delay_30.step();
			m_delay_39.step();
			m_delay_40.step();
			m_delay_41.step();
			m_delay_42.step();
			m_delay_43.step();
			m_delay_44.step();
			m_delay_45.step();
			m_delay_46.step();
			m_delay_48.step();
			m_delay_50.step();
			m_delay_52.step();
			m_delay_54.step();
			m_delay_56.step();
			m_delay_58.step();
			m_delay_60.step();
			m_delay_62.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			
		};
		return __exception;
		
	};
	inline void set_o_PEAKFREQ(t_param _value) {
		m_o_PEAKFREQ_112 = (_value < 100 ? 100 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_n_LOWFREQ(t_param _value) {
		m_n_LOWFREQ_113 = (_value < 20 ? 20 : (_value > 800 ? 800 : _value));
	};
	inline void set_m_OUTPUT(t_param _value) {
		m_m_OUTPUT_114 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_y_FILTERS(t_param _value) {
		m_y_FILTERS_115 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_d_DAMP(t_param _value) {
		m_d_DAMP_116 = (_value < 0.1 ? 0.1 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_u_ATK(t_param _value) {
		m_u_ATK_117 = (_value < 1 ? 1 : (_value > 500 ? 500 : _value));
	};
	inline void set_v_REL(t_param _value) {
		m_v_REL_118 = (_value < 5 ? 5 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_s_THD(t_param _value) {
		m_s_THD_119 = (_value < -60 ? -60 : (_value > 0 ? 0 : _value));
	};
	inline void set_q_ONOFFEQ(t_param _value) {
		m_q_ONOFFEQ_120 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_c_REFLECT(t_param _value) {
		m_c_REFLECT_121 = (_value < 0.1 ? 0.1 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_f_ST(t_param _value) {
		m_f_ST_122 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_z_BYPASS(t_param _value) {
		m_z_BYPASS_123 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_j_HIGAIN(t_param _value) {
		m_j_HIGAIN_124 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_b_DRYWET(t_param _value) {
		m_b_DRYWET_125 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_e_SIZE(t_param _value) {
		m_e_SIZE_126 = (_value < 0.1 ? 0.1 : (_value > 4 ? 4 : _value));
	};
	inline void set_k_LPF(t_param _value) {
		m_k_LPF_127 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_h_LOWGAIN(t_param _value) {
		m_h_LOWGAIN_128 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_t_RATIO(t_param _value) {
		m_t_RATIO_129 = (_value < 1 ? 1 : (_value > 20 ? 20 : _value));
	};
	inline void set_p_HIFREQ(t_param _value) {
		m_p_HIFREQ_130 = (_value < 800 ? 800 : (_value > 15000 ? 15000 : _value));
	};
	inline void set_g_FREEZE(t_param _value) {
		m_g_FREEZE_131 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_r_ONOFFCOMP(t_param _value) {
		m_r_ONOFFCOMP_132 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_i_PEAKGAIN(t_param _value) {
		m_i_PEAKGAIN_133 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_l_HPF(t_param _value) {
		m_l_HPF_134 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_w_MAKEUP(t_param _value) {
		m_w_MAKEUP_135 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void set_a_INPUT(t_param _value) {
		m_a_INPUT_136 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_150;
		t_sample return_151;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_150, return_151);
		t_sample x_406 = return_150;
		sigR = return_151;
		t_sample return_175;
		t_sample return_176;
		peak_d_d_d_d_i(x_406, sigR, pf, pg, bw, return_175, return_176);
		t_sample x_409 = return_175;
		sigR = return_176;
		t_sample return_189;
		t_sample return_190;
		hishelf_d_d_d_d(x_409, sigR, hf, hg, return_189, return_190);
		t_sample x_411 = return_189;
		sigR = return_190;
		out1 = x_411;
		out2 = sigR;
		
	};
	inline void lowshelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_145(freq) != ((int)0)) || (__m_change_146(db) != ((int)0)))) {
			m_b_144 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_f_143 = safediv(freq, m_b_144);
			m_b_142 = ((m_b_144 * m_b_144) - ((int)1));
			m_w_141 = tan(safediv((m_f_143 * ((t_sample)3.1415926535898)), samplerate));
			m_a_140 = safediv(((int)1), (m_w_141 + ((int)1)));
			m_a_139 = (m_w_141 - ((int)1));
			
		};
		t_sample outputLowShelfL = lowshelfCore_d_d_d_d_d(sigL, m_a_140, m_a_139, m_b_142, m_w_141);
		t_sample outputLowShelfR = lowshelfCore_d_d_d_d_d_148(sigR, m_a_140, m_a_139, m_b_142, m_w_141);
		out1 = outputLowShelfL;
		out2 = outputLowShelfR;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_140, t_sample m_a_139, t_sample m_b_142, t_sample m_w_141) {
		t_sample x = (m_a_140 * (input - (m_a_139 * m_z_147)));
		t_sample output = (m_w_141 * (x + m_z_147));
		m_z_147 = x;
		return ((output * m_b_142) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_148(t_sample input, t_sample m_a_140, t_sample m_a_139, t_sample m_b_142, t_sample m_w_141) {
		t_sample x = (m_a_140 * (input - (m_a_139 * m_z_149)));
		t_sample output = (m_w_141 * (x + m_z_149));
		m_z_149 = x;
		return ((output * m_b_142) + input);
		
	};
	inline void peak_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_162(freq) != ((int)0)) || (__m_change_163(db) != ((int)0))) || (__m_change_164(bw) != ((int)0)))) {
			m_w_161 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_160 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_160 * m_b_160) - ((int)1));
			m_d_159 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_165 = safediv(((m_d_159 * m_d_159) - ((int)1)), (m_d_159 * m_b_160));
			m_d_158 = ((v_165 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_165 >= ((int)100)) ? ((int)100) : v_165));
			m_d_157 = (m_d_158 * b);
			m_wq_156 = (m_d_158 * m_w_161);
			m_w_155 = (m_w_161 * m_w_161);
			m_a_154 = safediv(((int)1), ((((int)1) + m_w_155) + m_wq_156));
			m_a_153 = ((m_w_155 - ((int)1)) * ((int)2));
			m_a_152 = ((((int)1) + m_w_155) - m_wq_156);
			
		};
		t_sample outputPeakL = peakCore_d_d_d_d_d_d(sigL, m_w_161, m_d_157, m_a_154, m_a_153, m_a_152);
		t_sample outputPeakR = peakCore_d_d_d_d_d_d_170(sigR, m_w_161, m_d_157, m_a_154, m_a_153, m_a_152);
		out1 = outputPeakL;
		out2 = outputPeakR;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_161, t_sample m_d_157, t_sample m_a_154, t_sample m_a_153, t_sample m_a_152) {
		t_sample output = ((input - m_z_168) * m_w_161);
		m_z_168 = m_z_169;
		m_z_169 = input;
		t_sample output_407 = (m_a_154 * ((output - (m_a_153 * m_z_167)) - (m_a_152 * m_z_166)));
		m_z_166 = m_z_167;
		m_z_167 = output_407;
		t_sample output_408 = (input + (output_407 * m_d_157));
		return output_408;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_170(t_sample input, t_sample m_w_161, t_sample m_d_157, t_sample m_a_154, t_sample m_a_153, t_sample m_a_152) {
		t_sample output = ((input - m_z_173) * m_w_161);
		m_z_173 = m_z_174;
		m_z_174 = input;
		t_sample output_407 = (m_a_154 * ((output - (m_a_153 * m_z_172)) - (m_a_152 * m_z_171)));
		m_z_171 = m_z_172;
		m_z_172 = output_407;
		t_sample output_408 = (input + (output_407 * m_d_157));
		return output_408;
		
	};
	inline void hishelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_183(freq) != ((int)0)) || (__m_change_184(db) != ((int)0)))) {
			m_b_182 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_185 = (freq * m_b_182);
			m_f_181 = ((samplerate < mina_185) ? samplerate : mina_185);
			m_b_180 = ((m_b_182 * m_b_182) - ((int)1));
			m_w_179 = tan(safediv((((m_f_181 < ((int)0)) ? ((int)0) : m_f_181) * ((t_sample)3.1415926535898)), samplerate));
			m_a_178 = safediv(((int)1), (m_w_179 + ((int)1)));
			m_a_177 = (m_w_179 - ((int)1));
			
		};
		t_sample outputHighShelfL = hishelfCore_d_d_d_d(sigL, m_a_178, m_a_177, m_b_180);
		t_sample outputHighShelfR = hishelfCore_d_d_d_d_187(sigR, m_a_178, m_a_177, m_b_180);
		out1 = outputHighShelfL;
		out2 = outputHighShelfR;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_178, t_sample m_a_177, t_sample m_b_180) {
		t_sample x = (m_a_178 * (input - (m_a_177 * m_z_186)));
		t_sample output = (x - m_z_186);
		m_z_186 = x;
		t_sample output_410 = ((output * m_b_180) + input);
		return output_410;
		
	};
	inline t_sample hishelfCore_d_d_d_d_187(t_sample input, t_sample m_a_178, t_sample m_a_177, t_sample m_b_180) {
		t_sample x = (m_a_178 * (input - (m_a_177 * m_z_188)));
		t_sample output = (x - m_z_188);
		m_z_188 = x;
		t_sample output_410 = ((output * m_b_180) + input);
		return output_410;
		
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 4;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 25; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "out4" };

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
		case 23: self->set_y_FILTERS(value); break;
		case 24: self->set_z_BYPASS(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_a_INPUT_136; break;
		case 1: *value = self->m_b_DRYWET_125; break;
		case 2: *value = self->m_c_REFLECT_121; break;
		case 3: *value = self->m_d_DAMP_116; break;
		case 4: *value = self->m_e_SIZE_126; break;
		case 5: *value = self->m_f_ST_122; break;
		case 6: *value = self->m_g_FREEZE_131; break;
		case 7: *value = self->m_h_LOWGAIN_128; break;
		case 8: *value = self->m_i_PEAKGAIN_133; break;
		case 9: *value = self->m_j_HIGAIN_124; break;
		case 10: *value = self->m_k_LPF_127; break;
		case 11: *value = self->m_l_HPF_134; break;
		case 12: *value = self->m_m_OUTPUT_114; break;
		case 13: *value = self->m_n_LOWFREQ_113; break;
		case 14: *value = self->m_o_PEAKFREQ_112; break;
		case 15: *value = self->m_p_HIFREQ_130; break;
		case 16: *value = self->m_q_ONOFFEQ_120; break;
		case 17: *value = self->m_r_ONOFFCOMP_132; break;
		case 18: *value = self->m_s_THD_119; break;
		case 19: *value = self->m_t_RATIO_129; break;
		case 20: *value = self->m_u_ATK_117; break;
		case 21: *value = self->m_v_REL_118; break;
		case 22: *value = self->m_w_MAKEUP_135; break;
		case 23: *value = self->m_y_FILTERS_115; break;
		case 24: *value = self->m_z_BYPASS_123; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(25 * sizeof(ParamInfo));
	self->__commonstate.numparams = 25;
	// initialize parameter 0 ("m_a_INPUT_136")
	pi = self->__commonstate.params + 0;
	pi->name = "a_INPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_INPUT_136;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -12;
	pi->outputmax = 12;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_DRYWET_125")
	pi = self->__commonstate.params + 1;
	pi->name = "b_DRYWET";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_DRYWET_125;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_REFLECT_121")
	pi = self->__commonstate.params + 2;
	pi->name = "c_REFLECT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_REFLECT_121;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.95;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_DAMP_116")
	pi = self->__commonstate.params + 3;
	pi->name = "d_DAMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_DAMP_116;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.95;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_SIZE_126")
	pi = self->__commonstate.params + 4;
	pi->name = "e_SIZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_SIZE_126;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_ST_122")
	pi = self->__commonstate.params + 5;
	pi->name = "f_ST";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_ST_122;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_FREEZE_131")
	pi = self->__commonstate.params + 6;
	pi->name = "g_FREEZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_FREEZE_131;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_LOWGAIN_128")
	pi = self->__commonstate.params + 7;
	pi->name = "h_LOWGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_LOWGAIN_128;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_PEAKGAIN_133")
	pi = self->__commonstate.params + 8;
	pi->name = "i_PEAKGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_PEAKGAIN_133;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_HIGAIN_124")
	pi = self->__commonstate.params + 9;
	pi->name = "j_HIGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_HIGAIN_124;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_LPF_127")
	pi = self->__commonstate.params + 10;
	pi->name = "k_LPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_LPF_127;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_HPF_134")
	pi = self->__commonstate.params + 11;
	pi->name = "l_HPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_HPF_134;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_OUTPUT_114")
	pi = self->__commonstate.params + 12;
	pi->name = "m_OUTPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_OUTPUT_114;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -12;
	pi->outputmax = 12;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_LOWFREQ_113")
	pi = self->__commonstate.params + 13;
	pi->name = "n_LOWFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_LOWFREQ_113;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 800;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_PEAKFREQ_112")
	pi = self->__commonstate.params + 14;
	pi->name = "o_PEAKFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_PEAKFREQ_112;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 2500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_HIFREQ_130")
	pi = self->__commonstate.params + 15;
	pi->name = "p_HIFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_HIFREQ_130;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 800;
	pi->outputmax = 15000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_ONOFFEQ_120")
	pi = self->__commonstate.params + 16;
	pi->name = "q_ONOFFEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_ONOFFEQ_120;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 17 ("m_r_ONOFFCOMP_132")
	pi = self->__commonstate.params + 17;
	pi->name = "r_ONOFFCOMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_ONOFFCOMP_132;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 18 ("m_s_THD_119")
	pi = self->__commonstate.params + 18;
	pi->name = "s_THD";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_THD_119;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -60;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_RATIO_129")
	pi = self->__commonstate.params + 19;
	pi->name = "t_RATIO";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_RATIO_129;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_ATK_117")
	pi = self->__commonstate.params + 20;
	pi->name = "u_ATK";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_ATK_117;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_REL_118")
	pi = self->__commonstate.params + 21;
	pi->name = "v_REL";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_REL_118;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 5;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_MAKEUP_135")
	pi = self->__commonstate.params + 22;
	pi->name = "w_MAKEUP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_MAKEUP_135;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -6;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 23 ("m_y_FILTERS_115")
	pi = self->__commonstate.params + 23;
	pi->name = "y_FILTERS";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_y_FILTERS_115;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 24 ("m_z_BYPASS_123")
	pi = self->__commonstate.params + 24;
	pi->name = "z_BYPASS";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_z_BYPASS_123;
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
