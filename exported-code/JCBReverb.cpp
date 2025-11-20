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
[[maybe_unused]] static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Change __m_change_148;
	Change __m_change_164;
	Change __m_change_165;
	Change __m_change_166;
	Change __m_change_185;
	Change __m_change_186;
	Change __m_change_147;
	DCBlock __m_dcblock_203;
	DCBlock __m_dcblock_204;
	Delay m_delay_55;
	Delay m_delay_29;
	Delay m_delay_51;
	Delay m_delay_25;
	Delay m_delay_27;
	Delay m_delay_53;
	Delay m_delay_31;
	Delay m_delay_46;
	Delay m_delay_47;
	Delay m_delay_43;
	Delay m_delay_42;
	Delay m_delay_49;
	Delay m_delay_44;
	Delay m_delay_57;
	Delay m_delay_45;
	Delay m_delay_23;
	Delay m_delay_19;
	Delay m_delay_21;
	Delay m_delay_9;
	Delay m_delay_10;
	Delay m_delay_11;
	Delay m_delay_8;
	Delay m_delay_4;
	Delay m_delay_7;
	Delay m_delay_59;
	Delay m_delay_12;
	Delay m_delay_14;
	Delay m_delay_41;
	Delay m_delay_61;
	Delay m_delay_13;
	Delay m_delay_63;
	Delay m_delay_15;
	Delay m_delay_17;
	Delay m_delay_40;
	int __exception;
	int vectorsize;
	t_sample m_history_38;
	t_sample m_y_FILTERS_137;
	t_sample m_e_SIZE_138;
	t_sample m_w_MAKEUP_136;
	t_sample m_q_ONOFFEQ_134;
	t_sample m_m_OUTPUT_135;
	t_sample m_k_LPF_133;
	t_sample m_h_LOWGAIN_139;
	t_sample m_a_141;
	t_sample m_a_142;
	t_sample m_b_146;
	t_sample m_history_6;
	t_sample m_l_HPF_132;
	t_sample m_f_145;
	t_sample m_w_143;
	t_sample m_b_144;
	t_sample m_i_PEAKGAIN_131;
	t_sample m_z_BYPASS_130;
	t_sample m_n_LOWFREQ_129;
	t_sample m_x_PUMP_118;
	t_sample m_f_ST_119;
	t_sample m_g_FREEZE_120;
	t_sample m_p_HIFREQ_117;
	t_sample m_r_ONOFFCOMP_115;
	t_sample m_u_ATK_116;
	t_sample m_history_5;
	t_sample m_d_DAMP_121;
	t_sample m_a_INPUT_123;
	t_sample m_s_THD_127;
	t_sample m_j_HIGAIN_128;
	t_sample m_c_REFLECT_122;
	t_sample m_v_REL_126;
	t_sample m_t_RATIO_124;
	t_sample m_b_DRYWET_125;
	t_sample m_o_PEAKFREQ_114;
	t_sample m_z_149;
	t_sample m_a_154;
	t_sample m_a_179;
	t_sample m_a_180;
	t_sample m_w_181;
	t_sample m_z_176;
	t_sample m_z_174;
	t_sample m_z_175;
	t_sample m_z_173;
	t_sample m_b_182;
	t_sample m_b_184;
	t_sample __m_slide_196;
	t_sample __m_slide_200;
	t_sample m_f_183;
	t_sample m_z_190;
	t_sample samplerate;
	t_sample m_z_188;
	t_sample m_z_151;
	t_sample m_z_171;
	t_sample m_z_169;
	t_sample m_wq_158;
	t_sample m_d_159;
	t_sample m_d_160;
	t_sample m_w_157;
	t_sample m_a_155;
	t_sample m_a_156;
	t_sample m_z_170;
	t_sample m_d_161;
	t_sample m_w_163;
	t_sample m_z_168;
	t_sample m_b_162;
	t_sample m_history_1;
	t_sample m_history_3;
	t_sample m_history_2;
	t_sample m_history_39;
	t_sample m_history_113;
	t_sample m_history_111;
	t_sample m_history_64;
	t_sample m_history_65;
	t_sample m_history_66;
	t_sample m_history_18;
	t_sample m_history_20;
	t_sample m_history_62;
	t_sample m_history_60;
	t_sample m_history_67;
	t_sample m_history_69;
	t_sample m_history_73;
	t_sample m_history_74;
	t_sample m_history_68;
	t_sample m_history_72;
	t_sample m_history_70;
	t_sample m_history_71;
	t_sample m_history_75;
	t_sample m_history_22;
	t_sample m_history_24;
	t_sample m_history_34;
	t_sample m_history_33;
	t_sample m_history_48;
	t_sample m_history_35;
	t_sample m_history_37;
	t_sample m_history_36;
	t_sample m_history_58;
	t_sample m_history_32;
	t_sample m_history_30;
	t_sample m_history_26;
	t_sample m_history_56;
	t_sample m_history_50;
	t_sample m_history_54;
	t_sample m_history_52;
	t_sample m_history_28;
	t_sample m_history_112;
	t_sample m_history_76;
	t_sample m_history_78;
	t_sample m_history_100;
	t_sample m_history_101;
	t_sample m_history_102;
	t_sample m_history_99;
	t_sample m_history_97;
	t_sample m_history_98;
	t_sample m_history_96;
	t_sample m_history_103;
	t_sample m_history_105;
	t_sample m_history_109;
	t_sample m_history_110;
	t_sample m_history_104;
	t_sample m_history_108;
	t_sample m_history_106;
	t_sample m_history_107;
	t_sample m_history_77;
	t_sample m_history_95;
	t_sample m_history_93;
	t_sample m_history_82;
	t_sample m_history_83;
	t_sample m_history_84;
	t_sample m_history_81;
	t_sample m_history_79;
	t_sample m_history_80;
	t_sample m_history_94;
	t_sample m_history_85;
	t_sample m_history_87;
	t_sample m_history_16;
	t_sample m_history_92;
	t_sample m_history_86;
	t_sample m_history_90;
	t_sample m_history_88;
	t_sample m_history_89;
	t_sample m_history_91;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_delay_4.reset("m_delay_4", samplerate);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_delay_7.reset("m_delay_7", ((int)44100));
		m_delay_8.reset("m_delay_8", samplerate);
		m_delay_9.reset("m_delay_9", samplerate);
		m_delay_10.reset("m_delay_10", samplerate);
		m_delay_11.reset("m_delay_11", samplerate);
		m_delay_12.reset("m_delay_12", samplerate);
		m_delay_13.reset("m_delay_13", samplerate);
		m_delay_14.reset("m_delay_14", samplerate);
		m_delay_15.reset("m_delay_15", samplerate);
		m_history_16 = ((int)0);
		m_delay_17.reset("m_delay_17", samplerate);
		m_history_18 = ((int)0);
		m_delay_19.reset("m_delay_19", samplerate);
		m_history_20 = ((int)0);
		m_delay_21.reset("m_delay_21", samplerate);
		m_history_22 = ((int)0);
		m_delay_23.reset("m_delay_23", samplerate);
		m_history_24 = ((int)0);
		m_delay_25.reset("m_delay_25", samplerate);
		m_history_26 = ((int)0);
		m_delay_27.reset("m_delay_27", samplerate);
		m_history_28 = ((int)0);
		m_delay_29.reset("m_delay_29", samplerate);
		m_history_30 = ((int)0);
		m_delay_31.reset("m_delay_31", samplerate);
		m_history_32 = ((int)0);
		m_history_33 = ((int)0);
		m_history_34 = ((int)0);
		m_history_35 = ((int)0);
		m_history_36 = ((int)0);
		m_history_37 = ((int)0);
		m_history_38 = ((int)0);
		m_history_39 = ((int)0);
		m_delay_40.reset("m_delay_40", samplerate);
		m_delay_41.reset("m_delay_41", samplerate);
		m_delay_42.reset("m_delay_42", samplerate);
		m_delay_43.reset("m_delay_43", samplerate);
		m_delay_44.reset("m_delay_44", samplerate);
		m_delay_45.reset("m_delay_45", samplerate);
		m_delay_46.reset("m_delay_46", samplerate);
		m_delay_47.reset("m_delay_47", samplerate);
		m_history_48 = ((int)0);
		m_delay_49.reset("m_delay_49", samplerate);
		m_history_50 = ((int)0);
		m_delay_51.reset("m_delay_51", samplerate);
		m_history_52 = ((int)0);
		m_delay_53.reset("m_delay_53", samplerate);
		m_history_54 = ((int)0);
		m_delay_55.reset("m_delay_55", samplerate);
		m_history_56 = ((int)0);
		m_delay_57.reset("m_delay_57", samplerate);
		m_history_58 = ((int)0);
		m_delay_59.reset("m_delay_59", samplerate);
		m_history_60 = ((int)0);
		m_delay_61.reset("m_delay_61", samplerate);
		m_history_62 = ((int)0);
		m_delay_63.reset("m_delay_63", samplerate);
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
		m_history_112 = ((int)0);
		m_history_113 = ((int)0);
		m_o_PEAKFREQ_114 = 1500;
		m_r_ONOFFCOMP_115 = 0;
		m_u_ATK_116 = 5;
		m_p_HIFREQ_117 = 8600;
		m_x_PUMP_118 = 0;
		m_f_ST_119 = 0;
		m_g_FREEZE_120 = 0;
		m_d_DAMP_121 = 0.25;
		m_c_REFLECT_122 = 0.85;
		m_a_INPUT_123 = 0;
		m_t_RATIO_124 = 4;
		m_b_DRYWET_125 = 0.33;
		m_v_REL_126 = 250;
		m_s_THD_127 = -18;
		m_j_HIGAIN_128 = 0;
		m_n_LOWFREQ_129 = 250;
		m_z_BYPASS_130 = 0;
		m_i_PEAKGAIN_131 = 0;
		m_l_HPF_132 = 20;
		m_k_LPF_133 = 20000;
		m_q_ONOFFEQ_134 = 0;
		m_m_OUTPUT_135 = 0;
		m_w_MAKEUP_136 = 0;
		m_y_FILTERS_137 = 0;
		m_e_SIZE_138 = 1;
		m_h_LOWGAIN_139 = 0;
		m_a_141 = ((int)0);
		m_a_142 = ((int)0);
		m_w_143 = ((int)0);
		m_b_144 = ((int)0);
		m_f_145 = ((int)0);
		m_b_146 = ((int)0);
		__m_change_147.reset(0);
		__m_change_148.reset(0);
		m_z_149 = ((int)0);
		m_z_151 = ((int)0);
		m_a_154 = ((int)0);
		m_a_155 = ((int)0);
		m_a_156 = ((int)0);
		m_w_157 = ((int)0);
		m_wq_158 = ((int)0);
		m_d_159 = ((int)0);
		m_d_160 = ((int)0);
		m_d_161 = ((int)0);
		m_b_162 = ((int)0);
		m_w_163 = ((int)0);
		__m_change_164.reset(0);
		__m_change_165.reset(0);
		__m_change_166.reset(0);
		m_z_168 = ((int)0);
		m_z_169 = ((int)0);
		m_z_170 = ((int)0);
		m_z_171 = ((int)0);
		m_z_173 = ((int)0);
		m_z_174 = ((int)0);
		m_z_175 = ((int)0);
		m_z_176 = ((int)0);
		m_a_179 = ((int)0);
		m_a_180 = ((int)0);
		m_w_181 = ((int)0);
		m_b_182 = ((int)0);
		m_f_183 = ((int)0);
		m_b_184 = ((int)0);
		__m_change_185.reset(0);
		__m_change_186.reset(0);
		m_z_188 = ((int)0);
		m_z_190 = ((int)0);
		__m_slide_196 = 0;
		__m_slide_200 = 0;
		__m_dcblock_203.reset();
		__m_dcblock_204.reset();
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
		t_sample mul_39 = (m_z_BYPASS_130 * ((t_sample)0.001));
		t_sample dbtoa_58 = dbtoa(m_a_INPUT_123);
		t_sample mul_618 = (dbtoa_58 * ((t_sample)0.001));
		t_sample mul_516 = (m_b_DRYWET_125 * ((t_sample)0.001));
		int gte_641 = (m_g_FREEZE_120 >= ((t_sample)0.5));
		t_sample mul_9 = (gte_641 * ((t_sample)0.001));
		t_sample mul_101 = (m_r_ONOFFCOMP_115 * ((t_sample)0.001));
		t_sample mul_93 = (m_s_THD_127 * ((t_sample)0.001));
		t_sample mul_85 = (m_t_RATIO_124 * ((t_sample)0.001));
		t_sample mul_77 = (m_u_ATK_116 * ((t_sample)0.001));
		t_sample mul_69 = (m_v_REL_126 * ((t_sample)0.001));
		t_sample mul_59 = (m_w_MAKEUP_136 * ((t_sample)0.001));
		t_sample dbtoa_57 = dbtoa(m_m_OUTPUT_135);
		t_sample mul_524 = (dbtoa_57 * ((t_sample)0.001));
		t_sample mul_330 = (m_q_ONOFFEQ_134 * ((t_sample)0.001));
		t_sample mul_356 = (m_n_LOWFREQ_129 * ((t_sample)0.001));
		t_sample mul_348 = (m_o_PEAKFREQ_114 * ((t_sample)0.001));
		t_sample mul_340 = (m_p_HIFREQ_117 * ((t_sample)0.001));
		t_sample mul_550 = (m_h_LOWGAIN_139 * ((t_sample)0.001));
		t_sample mul_542 = (m_i_PEAKGAIN_131 * ((t_sample)0.001));
		t_sample mul_534 = (m_j_HIGAIN_128 * ((t_sample)0.001));
		t_sample mul_626 = (m_f_ST_119 * ((t_sample)0.001));
		t_sample mul_364 = (m_e_SIZE_138 * ((t_sample)0.001));
		t_sample mul_49 = (m_d_DAMP_121 * ((t_sample)0.001));
		t_sample mul_566 = (m_k_LPF_133 * ((t_sample)0.001));
		t_sample mul_558 = (m_l_HPF_132 * ((t_sample)0.001));
		t_sample mul_31 = (m_y_FILTERS_137 * ((t_sample)0.001));
		int rsub_640 = (((int)1) - gte_641);
		t_sample mul_17 = (rsub_640 * ((t_sample)0.001));
		t_sample rsub_637 = (((int)1) - m_c_REFLECT_122);
		int choice_140 = gte_641;
		t_sample gate_636 = ((choice_140 >= 1) ? rsub_637 : 0);
		t_sample add_638 = (m_c_REFLECT_122 + gate_636);
		t_sample mul_1 = (add_638 * ((t_sample)0.001));
		t_sample div_943 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_498 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_481 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_464 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_447 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_721 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_426 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_409 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_392 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_375 = (samplerate * ((t_sample)2.2675736961451e-05));
		int maxb_195 = (-96);
		int maxb_199 = (-96);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mix_2141 = (((int)0) + (((t_sample)0.05) * (m_history_1 - ((int)0))));
			t_sample mix_26 = mix_2141;
			t_sample mul_40 = (m_history_113 * ((t_sample)0.999));
			t_sample add_42 = (mul_39 + mul_40);
			t_sample gen_46 = add_42;
			t_sample history_41_next_45 = fixdenorm(add_42);
			t_sample mul_619 = (m_history_112 * ((t_sample)0.999));
			t_sample add_621 = (mul_618 + mul_619);
			t_sample gen_625 = add_621;
			t_sample history_620_next_624 = fixdenorm(add_621);
			t_sample mul_603 = (in1 * gen_625);
			t_sample out3 = mul_603;
			t_sample mul_602 = (in2 * gen_625);
			t_sample out4 = mul_602;
			t_sample mul_517 = (m_history_111 * ((t_sample)0.999));
			t_sample add_519 = (mul_516 + mul_517);
			t_sample gen_523 = add_519;
			t_sample history_518_next_522 = fixdenorm(add_519);
			t_sample mul_10 = (m_history_110 * ((t_sample)0.999));
			t_sample add_12 = (mul_9 + mul_10);
			t_sample gen_16 = add_12;
			t_sample history_11_next_15 = fixdenorm(add_12);
			t_sample mix_2142 = (in1 + (gen_16 * (((int)0) - in1)));
			t_sample mix_2143 = (in2 + (gen_16 * (((int)0) - in2)));
			t_sample mul_102 = (m_history_109 * ((t_sample)0.999));
			t_sample add_104 = (mul_101 + mul_102);
			t_sample gen_108 = add_104;
			t_sample history_103_next_107 = fixdenorm(add_104);
			t_sample mul_94 = (m_history_108 * ((t_sample)0.999));
			t_sample add_96 = (mul_93 + mul_94);
			t_sample gen_100 = add_96;
			t_sample history_95_next_99 = fixdenorm(add_96);
			t_sample mul_86 = (m_history_107 * ((t_sample)0.999));
			t_sample add_88 = (mul_85 + mul_86);
			t_sample gen_92 = add_88;
			t_sample history_87_next_91 = fixdenorm(add_88);
			t_sample mul_78 = (m_history_106 * ((t_sample)0.999));
			t_sample add_80 = (mul_77 + mul_78);
			t_sample gen_84 = add_80;
			t_sample history_79_next_83 = fixdenorm(add_80);
			t_sample mul_70 = (m_history_105 * ((t_sample)0.999));
			t_sample add_72 = (mul_69 + mul_70);
			t_sample gen_76 = add_72;
			t_sample history_71_next_75 = fixdenorm(add_72);
			t_sample mul_60 = (m_history_104 * ((t_sample)0.999));
			t_sample add_62 = (mul_59 + mul_60);
			t_sample gen_66 = add_62;
			t_sample history_61_next_65 = fixdenorm(add_62);
			t_sample mul_525 = (m_history_103 * ((t_sample)0.999));
			t_sample add_527 = (mul_524 + mul_525);
			t_sample gen_531 = add_527;
			t_sample history_526_next_530 = fixdenorm(add_527);
			t_sample mul_331 = (m_history_102 * ((t_sample)0.999));
			t_sample add_333 = (mul_330 + mul_331);
			t_sample gen_337 = add_333;
			t_sample history_332_next_336 = fixdenorm(add_333);
			t_sample mul_357 = (m_history_101 * ((t_sample)0.999));
			t_sample add_359 = (mul_356 + mul_357);
			t_sample gen_363 = add_359;
			t_sample history_358_next_362 = fixdenorm(add_359);
			t_sample mul_349 = (m_history_100 * ((t_sample)0.999));
			t_sample add_351 = (mul_348 + mul_349);
			t_sample gen_355 = add_351;
			t_sample history_350_next_354 = fixdenorm(add_351);
			t_sample mul_341 = (m_history_99 * ((t_sample)0.999));
			t_sample add_343 = (mul_340 + mul_341);
			t_sample gen_347 = add_343;
			t_sample history_342_next_346 = fixdenorm(add_343);
			t_sample mul_551 = (m_history_98 * ((t_sample)0.999));
			t_sample add_553 = (mul_550 + mul_551);
			t_sample gen_557 = add_553;
			t_sample history_552_next_556 = fixdenorm(add_553);
			t_sample mul_543 = (m_history_97 * ((t_sample)0.999));
			t_sample add_545 = (mul_542 + mul_543);
			t_sample gen_549 = add_545;
			t_sample history_544_next_548 = fixdenorm(add_545);
			t_sample mul_535 = (m_history_96 * ((t_sample)0.999));
			t_sample add_537 = (mul_534 + mul_535);
			t_sample gen_541 = add_537;
			t_sample history_536_next_540 = fixdenorm(add_537);
			t_sample mul_627 = (m_history_95 * ((t_sample)0.999));
			t_sample add_629 = (mul_626 + mul_627);
			t_sample gen_633 = add_629;
			t_sample history_628_next_632 = fixdenorm(add_629);
			t_sample sub_2147 = (gen_633 - ((int)0));
			t_sample scale_2144 = ((safepow((sub_2147 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_606 = scale_2144;
			t_sample sqrt_611 = sqrt(gen_633);
			t_sample rsub_634 = (((int)1) - gen_633);
			t_sample sqrt_612 = sqrt(rsub_634);
			t_sample mul_365 = (m_history_94 * ((t_sample)0.999));
			t_sample add_367 = (mul_364 + mul_365);
			t_sample gen_371 = add_367;
			t_sample history_366_next_370 = fixdenorm(add_367);
			t_sample mul_50 = (m_history_93 * ((t_sample)0.999));
			t_sample add_52 = (mul_49 + mul_50);
			t_sample gen_56 = add_52;
			t_sample history_51_next_55 = fixdenorm(add_52);
			t_sample mul_567 = (m_history_92 * ((t_sample)0.999));
			t_sample add_569 = (mul_566 + mul_567);
			t_sample gen_573 = add_569;
			t_sample history_568_next_572 = fixdenorm(add_569);
			t_sample mul_559 = (m_history_91 * ((t_sample)0.999));
			t_sample add_561 = (mul_558 + mul_559);
			t_sample gen_565 = add_561;
			t_sample history_560_next_564 = fixdenorm(add_561);
			t_sample mul_32 = (m_history_90 * ((t_sample)0.999));
			t_sample add_34 = (mul_31 + mul_32);
			t_sample gen_38 = add_34;
			t_sample history_33_next_37 = fixdenorm(add_34);
			t_sample mul_372 = (((int)23) * gen_371);
			t_sample mul_18 = (m_history_89 * ((t_sample)0.999));
			t_sample add_20 = (mul_17 + mul_18);
			t_sample gen_24 = add_20;
			t_sample history_19_next_23 = fixdenorm(add_20);
			t_sample mul_639 = (mul_603 * gen_24);
			t_sample mul_617 = (mul_602 * gen_24);
			t_sample omega = safediv((gen_565 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) + cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((-(((int)1) + cs)) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_309 = a2;
			t_sample expr_310 = a1;
			t_sample expr_311 = a2;
			t_sample expr_312 = b1;
			t_sample expr_313 = b2;
			t_sample omega_320 = safediv((gen_573 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_319 = sin(omega_320);
			t_sample cs_326 = cos(omega_320);
			t_sample alpha_327 = ((sn_319 * ((t_sample)0.5)) * ((int)1));
			t_sample b_324 = safediv(((int)1), (((int)1) + alpha_327));
			t_sample a_325 = (((((int)1) - cs_326) * ((t_sample)0.5)) * b_324);
			t_sample a_323 = ((((int)1) - cs_326) * b_324);
			t_sample b_322 = ((((int)-2) * cs_326) * b_324);
			t_sample b_321 = ((((int)1) - alpha_327) * b_324);
			t_sample expr_314 = a_325;
			t_sample expr_315 = a_323;
			t_sample expr_316 = a_325;
			t_sample expr_317 = b_322;
			t_sample expr_318 = b_321;
			t_sample mul_267 = (mul_639 * expr_314);
			t_sample mul_257 = (mul_617 * expr_314);
			t_sample mul_264 = (m_history_83 * expr_315);
			t_sample mul_254 = (m_history_84 * expr_315);
			t_sample mul_262 = (m_history_87 * expr_316);
			t_sample mul_252 = (m_history_85 * expr_316);
			t_sample mul_258 = (m_history_86 * expr_318);
			t_sample mul_248 = (m_history_88 * expr_318);
			t_sample mul_260 = (m_history_82 * expr_317);
			t_sample sub_266 = (((mul_262 + mul_264) + mul_267) - (mul_260 + mul_258));
			t_sample gen_286 = sub_266;
			t_sample mul_250 = (m_history_81 * expr_317);
			t_sample sub_256 = (((mul_257 + mul_254) + mul_252) - (mul_250 + mul_248));
			t_sample gen_287 = sub_256;
			t_sample history_249_next_278 = fixdenorm(m_history_81);
			t_sample history_263_next_279 = fixdenorm(m_history_83);
			t_sample history_259_next_280 = fixdenorm(m_history_82);
			t_sample history_253_next_281 = fixdenorm(m_history_84);
			t_sample history_255_next_282 = fixdenorm(mul_617);
			t_sample history_265_next_283 = fixdenorm(mul_639);
			t_sample history_261_next_284 = fixdenorm(sub_266);
			t_sample history_251_next_285 = fixdenorm(sub_256);
			t_sample mul_207 = (m_history_79 * expr_311);
			t_sample mul_217 = (m_history_80 * expr_311);
			t_sample mul_209 = (m_history_76 * expr_310);
			t_sample mul_219 = (m_history_75 * expr_310);
			t_sample mul_212 = (gen_287 * expr_309);
			t_sample mul_222 = (gen_286 * expr_309);
			t_sample mul_203 = (m_history_77 * expr_313);
			t_sample mul_213 = (m_history_78 * expr_313);
			t_sample mul_205 = (m_history_74 * expr_312);
			t_sample sub_211 = (((mul_212 + mul_209) + mul_207) - (mul_205 + mul_203));
			t_sample gen_242 = sub_211;
			t_sample mul_215 = (m_history_73 * expr_312);
			t_sample sub_221 = (((mul_217 + mul_219) + mul_222) - (mul_215 + mul_213));
			t_sample gen_241 = sub_221;
			t_sample history_218_next_233 = fixdenorm(m_history_75);
			t_sample history_208_next_234 = fixdenorm(m_history_76);
			t_sample history_214_next_235 = fixdenorm(m_history_73);
			t_sample history_204_next_236 = fixdenorm(m_history_74);
			t_sample history_210_next_237 = fixdenorm(gen_287);
			t_sample history_220_next_238 = fixdenorm(gen_286);
			t_sample history_206_next_239 = fixdenorm(sub_211);
			t_sample history_216_next_240 = fixdenorm(sub_221);
			t_sample mix_2148 = (mul_639 + (gen_38 * (gen_241 - mul_639)));
			t_sample mix_197 = mix_2148;
			t_sample gen_328 = mix_197;
			t_sample mix_2149 = (mul_617 + (gen_38 * (gen_242 - mul_617)));
			t_sample mix_196 = mix_2149;
			t_sample gen_329 = mix_196;
			t_sample mul_2 = (m_history_72 * ((t_sample)0.999));
			t_sample add_4 = (mul_1 + mul_2);
			t_sample gen_8 = add_4;
			t_sample history_3_next_7 = fixdenorm(add_4);
			t_sample rsub_962 = (((int)1) - gen_56);
			t_sample mul_928 = (div_943 * gen_371);
			t_sample mul_937 = (((int)1422) * mul_928);
			t_sample mul_897 = (m_history_71 * ((t_sample)0.999));
			t_sample mul_896 = (mul_937 * ((t_sample)0.001));
			t_sample add_899 = (mul_896 + mul_897);
			t_sample gen_903 = add_899;
			t_sample history_898_next_902 = fixdenorm(add_899);
			t_sample gen_957 = gen_903;
			t_sample mul_941 = (((int)1617) * mul_928);
			t_sample mul_913 = (m_history_70 * ((t_sample)0.999));
			t_sample mul_912 = (mul_941 * ((t_sample)0.001));
			t_sample add_915 = (mul_912 + mul_913);
			t_sample gen_919 = add_915;
			t_sample history_914_next_918 = fixdenorm(add_915);
			t_sample gen_955 = gen_919;
			t_sample mul_944 = (((int)1557) * mul_928);
			t_sample mul_921 = (m_history_69 * ((t_sample)0.999));
			t_sample mul_920 = (mul_944 * ((t_sample)0.001));
			t_sample add_923 = (mul_920 + mul_921);
			t_sample gen_927 = add_923;
			t_sample history_922_next_926 = fixdenorm(add_923);
			t_sample gen_954 = gen_927;
			t_sample mul_931 = (((int)1188) * mul_928);
			t_sample mul_873 = (m_history_68 * ((t_sample)0.999));
			t_sample mul_872 = (mul_931 * ((t_sample)0.001));
			t_sample add_875 = (mul_872 + mul_873);
			t_sample gen_879 = add_875;
			t_sample history_874_next_878 = fixdenorm(add_875);
			t_sample gen_960 = gen_879;
			t_sample mul_939 = (((int)1491) * mul_928);
			t_sample mul_905 = (m_history_67 * ((t_sample)0.999));
			t_sample mul_904 = (mul_939 * ((t_sample)0.001));
			t_sample add_907 = (mul_904 + mul_905);
			t_sample gen_911 = add_907;
			t_sample history_906_next_910 = fixdenorm(add_907);
			t_sample gen_956 = gen_911;
			t_sample mul_933 = (((int)1356) * mul_928);
			t_sample mul_881 = (m_history_66 * ((t_sample)0.999));
			t_sample mul_880 = (mul_933 * ((t_sample)0.001));
			t_sample add_883 = (mul_880 + mul_881);
			t_sample gen_887 = add_883;
			t_sample history_882_next_886 = fixdenorm(add_883);
			t_sample gen_959 = gen_887;
			t_sample mul_929 = (((int)1116) * mul_928);
			t_sample mul_865 = (m_history_65 * ((t_sample)0.999));
			t_sample mul_864 = (mul_929 * ((t_sample)0.001));
			t_sample add_867 = (mul_864 + mul_865);
			t_sample gen_871 = add_867;
			t_sample history_866_next_870 = fixdenorm(add_867);
			t_sample gen_961 = gen_871;
			t_sample mul_935 = (((int)1277) * mul_928);
			t_sample mul_889 = (m_history_64 * ((t_sample)0.999));
			t_sample mul_888 = (mul_935 * ((t_sample)0.001));
			t_sample add_891 = (mul_888 + mul_889);
			t_sample gen_895 = add_891;
			t_sample history_890_next_894 = fixdenorm(add_891);
			t_sample gen_958 = gen_895;
			t_sample rsub_964 = (((int)1) - rsub_962);
			t_sample mul_966 = (m_history_62 * rsub_964);
			t_sample add_963 = (((int)0) + gen_961);
			t_sample tap_972 = m_delay_63.read_linear(add_963);
			t_sample mul_969 = (tap_972 * rsub_962);
			t_sample add_968 = (mul_969 + mul_966);
			t_sample mul_965 = (add_968 * gen_8);
			t_sample add_970 = (gen_328 + mul_965);
			t_sample gen_977 = add_970;
			t_sample history_967_next_976 = fixdenorm(add_968);
			t_sample rsub_979 = (((int)1) - rsub_962);
			t_sample mul_981 = (m_history_60 * rsub_979);
			t_sample add_978 = (((int)0) + gen_960);
			t_sample tap_987 = m_delay_61.read_linear(add_978);
			t_sample mul_984 = (tap_987 * rsub_962);
			t_sample add_983 = (mul_984 + mul_981);
			t_sample mul_980 = (add_983 * gen_8);
			t_sample add_985 = (gen_328 + mul_980);
			t_sample gen_992 = add_985;
			t_sample history_982_next_991 = fixdenorm(add_983);
			t_sample rsub_994 = (((int)1) - rsub_962);
			t_sample mul_996 = (m_history_58 * rsub_994);
			t_sample add_993 = (((int)0) + gen_959);
			t_sample tap_1002 = m_delay_59.read_linear(add_993);
			t_sample mul_999 = (tap_1002 * rsub_962);
			t_sample add_998 = (mul_999 + mul_996);
			t_sample mul_995 = (add_998 * gen_8);
			t_sample add_1000 = (gen_328 + mul_995);
			t_sample gen_1007 = add_1000;
			t_sample history_997_next_1006 = fixdenorm(add_998);
			t_sample rsub_1009 = (((int)1) - rsub_962);
			t_sample mul_1011 = (m_history_56 * rsub_1009);
			t_sample add_1008 = (((int)0) + gen_958);
			t_sample tap_1017 = m_delay_57.read_linear(add_1008);
			t_sample mul_1014 = (tap_1017 * rsub_962);
			t_sample add_1013 = (mul_1014 + mul_1011);
			t_sample mul_1010 = (add_1013 * gen_8);
			t_sample add_1015 = (gen_328 + mul_1010);
			t_sample gen_1022 = add_1015;
			t_sample history_1012_next_1021 = fixdenorm(add_1013);
			t_sample rsub_1024 = (((int)1) - rsub_962);
			t_sample mul_1026 = (m_history_54 * rsub_1024);
			t_sample add_1023 = (((int)0) + gen_957);
			t_sample tap_1032 = m_delay_55.read_linear(add_1023);
			t_sample mul_1029 = (tap_1032 * rsub_962);
			t_sample add_1028 = (mul_1029 + mul_1026);
			t_sample mul_1025 = (add_1028 * gen_8);
			t_sample add_1030 = (gen_328 + mul_1025);
			t_sample gen_1037 = add_1030;
			t_sample history_1027_next_1036 = fixdenorm(add_1028);
			t_sample rsub_1039 = (((int)1) - rsub_962);
			t_sample mul_1041 = (m_history_52 * rsub_1039);
			t_sample add_1038 = (((int)0) + gen_956);
			t_sample tap_1047 = m_delay_53.read_linear(add_1038);
			t_sample mul_1044 = (tap_1047 * rsub_962);
			t_sample add_1043 = (mul_1044 + mul_1041);
			t_sample mul_1040 = (add_1043 * gen_8);
			t_sample add_1045 = (gen_328 + mul_1040);
			t_sample gen_1052 = add_1045;
			t_sample history_1042_next_1051 = fixdenorm(add_1043);
			t_sample rsub_1054 = (((int)1) - rsub_962);
			t_sample mul_1056 = (m_history_50 * rsub_1054);
			t_sample add_1053 = (((int)0) + gen_955);
			t_sample tap_1062 = m_delay_51.read_linear(add_1053);
			t_sample mul_1059 = (tap_1062 * rsub_962);
			t_sample add_1058 = (mul_1059 + mul_1056);
			t_sample mul_1055 = (add_1058 * gen_8);
			t_sample add_1060 = (gen_328 + mul_1055);
			t_sample gen_1067 = add_1060;
			t_sample history_1057_next_1066 = fixdenorm(add_1058);
			t_sample rsub_1069 = (((int)1) - rsub_962);
			t_sample mul_1071 = (m_history_48 * rsub_1069);
			t_sample add_1068 = (((int)0) + gen_954);
			t_sample tap_1077 = m_delay_49.read_linear(add_1068);
			t_sample mul_1074 = (tap_1077 * rsub_962);
			t_sample add_1073 = (mul_1074 + mul_1071);
			t_sample mul_1070 = (add_1073 * gen_8);
			t_sample add_1075 = (gen_328 + mul_1070);
			t_sample gen_1082 = add_1075;
			t_sample history_1072_next_1081 = fixdenorm(add_1073);
			t_sample mul_1083 = ((((((((gen_1082 + gen_1067) + gen_1052) + gen_1037) + gen_1022) + gen_1007) + gen_992) + gen_977) * ((t_sample)0.125));
			t_sample gen_1085 = mul_1083;
			t_sample mul_507 = (gen_1085 * ((t_sample)-0.5));
			t_sample mul_497 = (div_498 * gen_371);
			t_sample mul_499 = (((int)255) * mul_497);
			t_sample add_501 = (((int)0) + mul_499);
			t_sample tap_509 = m_delay_47.read_linear(add_501);
			t_sample tap_504 = m_delay_46.read_linear(add_501);
			t_sample mul_502 = (tap_504 * ((t_sample)0.5));
			t_sample add_505 = (mul_507 + (tap_509 + mul_502));
			t_sample gen_513 = add_505;
			t_sample mul_490 = (gen_513 * ((t_sample)-0.5));
			t_sample mul_480 = (div_481 * gen_371);
			t_sample mul_482 = (((int)556) * mul_480);
			t_sample add_484 = (((int)0) + mul_482);
			t_sample tap_492 = m_delay_45.read_linear(add_484);
			t_sample tap_487 = m_delay_44.read_linear(add_484);
			t_sample mul_485 = (tap_487 * ((t_sample)0.5));
			t_sample add_488 = (mul_490 + (tap_492 + mul_485));
			t_sample gen_496 = add_488;
			t_sample mul_473 = (gen_496 * ((t_sample)-0.5));
			t_sample mul_463 = (div_464 * gen_371);
			t_sample mul_465 = (((int)441) * mul_463);
			t_sample add_467 = (((int)0) + mul_465);
			t_sample tap_475 = m_delay_43.read_linear(add_467);
			t_sample tap_470 = m_delay_42.read_linear(add_467);
			t_sample mul_468 = (tap_470 * ((t_sample)0.5));
			t_sample add_471 = (mul_473 + (tap_475 + mul_468));
			t_sample gen_479 = add_471;
			t_sample mul_456 = (gen_479 * ((t_sample)-0.5));
			t_sample mul_446 = (div_447 * gen_371);
			t_sample mul_448 = (((int)341) * mul_446);
			t_sample add_450 = (((int)0) + mul_448);
			t_sample tap_458 = m_delay_41.read_linear(add_450);
			t_sample tap_453 = m_delay_40.read_linear(add_450);
			t_sample mul_451 = (tap_453 * ((t_sample)0.5));
			t_sample add_454 = (mul_456 + (tap_458 + mul_451));
			t_sample gen_462 = add_454;
			t_sample gen_515 = gen_462;
			t_sample rsub_740 = (((int)1) - gen_56);
			t_sample mul_706 = (div_721 * gen_371);
			t_sample mul_711 = (((int)1356) * mul_706);
			t_sample mul_659 = (m_history_39 * ((t_sample)0.999));
			t_sample mul_658 = (mul_711 * ((t_sample)0.001));
			t_sample add_661 = (mul_658 + mul_659);
			t_sample gen_665 = add_661;
			t_sample history_660_next_664 = fixdenorm(add_661);
			t_sample gen_737 = gen_665;
			t_sample mul_722 = (((int)1557) * mul_706);
			t_sample mul_699 = (m_history_38 * ((t_sample)0.999));
			t_sample mul_698 = (mul_722 * ((t_sample)0.001));
			t_sample add_701 = (mul_698 + mul_699);
			t_sample gen_705 = add_701;
			t_sample history_700_next_704 = fixdenorm(add_701);
			t_sample gen_732 = gen_705;
			t_sample mul_719 = (((int)1617) * mul_706);
			t_sample mul_691 = (m_history_37 * ((t_sample)0.999));
			t_sample mul_690 = (mul_719 * ((t_sample)0.001));
			t_sample add_693 = (mul_690 + mul_691);
			t_sample gen_697 = add_693;
			t_sample history_692_next_696 = fixdenorm(add_693);
			t_sample gen_733 = gen_697;
			t_sample mul_715 = (((int)1422) * mul_706);
			t_sample mul_675 = (m_history_36 * ((t_sample)0.999));
			t_sample mul_674 = (mul_715 * ((t_sample)0.001));
			t_sample add_677 = (mul_674 + mul_675);
			t_sample gen_681 = add_677;
			t_sample history_676_next_680 = fixdenorm(add_677);
			t_sample gen_735 = gen_681;
			t_sample mul_709 = (((int)1188) * mul_706);
			t_sample mul_651 = (m_history_35 * ((t_sample)0.999));
			t_sample mul_650 = (mul_709 * ((t_sample)0.001));
			t_sample add_653 = (mul_650 + mul_651);
			t_sample gen_657 = add_653;
			t_sample history_652_next_656 = fixdenorm(add_653);
			t_sample gen_738 = gen_657;
			t_sample mul_713 = (((int)1277) * mul_706);
			t_sample mul_667 = (m_history_34 * ((t_sample)0.999));
			t_sample mul_666 = (mul_713 * ((t_sample)0.001));
			t_sample add_669 = (mul_666 + mul_667);
			t_sample gen_673 = add_669;
			t_sample history_668_next_672 = fixdenorm(add_669);
			t_sample gen_736 = gen_673;
			t_sample mul_717 = (((int)1491) * mul_706);
			t_sample mul_683 = (m_history_33 * ((t_sample)0.999));
			t_sample mul_682 = (mul_717 * ((t_sample)0.001));
			t_sample add_685 = (mul_682 + mul_683);
			t_sample gen_689 = add_685;
			t_sample history_684_next_688 = fixdenorm(add_685);
			t_sample gen_734 = gen_689;
			t_sample mul_707 = (((int)1116) * mul_706);
			t_sample mul_643 = (m_history_32 * ((t_sample)0.999));
			t_sample mul_642 = (mul_707 * ((t_sample)0.001));
			t_sample add_645 = (mul_642 + mul_643);
			t_sample gen_649 = add_645;
			t_sample history_644_next_648 = fixdenorm(add_645);
			t_sample gen_739 = gen_649;
			t_sample rsub_742 = (((int)1) - rsub_740);
			t_sample mul_744 = (m_history_30 * rsub_742);
			t_sample add_741 = (mul_372 + gen_739);
			t_sample tap_750 = m_delay_31.read_linear(add_741);
			t_sample mul_747 = (tap_750 * rsub_740);
			t_sample add_746 = (mul_747 + mul_744);
			t_sample mul_743 = (add_746 * gen_8);
			t_sample add_748 = (gen_329 + mul_743);
			t_sample gen_755 = add_748;
			t_sample history_745_next_754 = fixdenorm(add_746);
			t_sample rsub_757 = (((int)1) - rsub_740);
			t_sample mul_759 = (m_history_28 * rsub_757);
			t_sample add_756 = (mul_372 + gen_738);
			t_sample tap_765 = m_delay_29.read_linear(add_756);
			t_sample mul_762 = (tap_765 * rsub_740);
			t_sample add_761 = (mul_762 + mul_759);
			t_sample mul_758 = (add_761 * gen_8);
			t_sample add_763 = (gen_329 + mul_758);
			t_sample gen_770 = add_763;
			t_sample history_760_next_769 = fixdenorm(add_761);
			t_sample rsub_772 = (((int)1) - rsub_740);
			t_sample mul_774 = (m_history_26 * rsub_772);
			t_sample add_771 = (mul_372 + gen_737);
			t_sample tap_780 = m_delay_27.read_linear(add_771);
			t_sample mul_777 = (tap_780 * rsub_740);
			t_sample add_776 = (mul_777 + mul_774);
			t_sample mul_773 = (add_776 * gen_8);
			t_sample add_778 = (gen_329 + mul_773);
			t_sample gen_785 = add_778;
			t_sample history_775_next_784 = fixdenorm(add_776);
			t_sample rsub_787 = (((int)1) - rsub_740);
			t_sample mul_789 = (m_history_24 * rsub_787);
			t_sample add_786 = (mul_372 + gen_736);
			t_sample tap_795 = m_delay_25.read_linear(add_786);
			t_sample mul_792 = (tap_795 * rsub_740);
			t_sample add_791 = (mul_792 + mul_789);
			t_sample mul_788 = (add_791 * gen_8);
			t_sample add_793 = (gen_329 + mul_788);
			t_sample gen_800 = add_793;
			t_sample history_790_next_799 = fixdenorm(add_791);
			t_sample rsub_802 = (((int)1) - rsub_740);
			t_sample mul_804 = (m_history_22 * rsub_802);
			t_sample add_801 = (mul_372 + gen_735);
			t_sample tap_810 = m_delay_23.read_linear(add_801);
			t_sample mul_807 = (tap_810 * rsub_740);
			t_sample add_806 = (mul_807 + mul_804);
			t_sample mul_803 = (add_806 * gen_8);
			t_sample add_808 = (gen_329 + mul_803);
			t_sample gen_815 = add_808;
			t_sample history_805_next_814 = fixdenorm(add_806);
			t_sample rsub_817 = (((int)1) - rsub_740);
			t_sample mul_819 = (m_history_20 * rsub_817);
			t_sample add_816 = (mul_372 + gen_734);
			t_sample tap_825 = m_delay_21.read_linear(add_816);
			t_sample mul_822 = (tap_825 * rsub_740);
			t_sample add_821 = (mul_822 + mul_819);
			t_sample mul_818 = (add_821 * gen_8);
			t_sample add_823 = (gen_329 + mul_818);
			t_sample gen_830 = add_823;
			t_sample history_820_next_829 = fixdenorm(add_821);
			t_sample rsub_832 = (((int)1) - rsub_740);
			t_sample mul_834 = (m_history_18 * rsub_832);
			t_sample add_831 = (mul_372 + gen_733);
			t_sample tap_840 = m_delay_19.read_linear(add_831);
			t_sample mul_837 = (tap_840 * rsub_740);
			t_sample add_836 = (mul_837 + mul_834);
			t_sample mul_833 = (add_836 * gen_8);
			t_sample add_838 = (gen_329 + mul_833);
			t_sample gen_845 = add_838;
			t_sample history_835_next_844 = fixdenorm(add_836);
			t_sample rsub_847 = (((int)1) - rsub_740);
			t_sample mul_849 = (m_history_16 * rsub_847);
			t_sample add_846 = (mul_372 + gen_732);
			t_sample tap_855 = m_delay_17.read_linear(add_846);
			t_sample mul_852 = (tap_855 * rsub_740);
			t_sample add_851 = (mul_852 + mul_849);
			t_sample mul_848 = (add_851 * gen_8);
			t_sample add_853 = (gen_329 + mul_848);
			t_sample gen_860 = add_853;
			t_sample history_850_next_859 = fixdenorm(add_851);
			t_sample mul_861 = ((((((((gen_860 + gen_845) + gen_830) + gen_815) + gen_800) + gen_785) + gen_770) + gen_755) * ((t_sample)0.125));
			t_sample gen_863 = mul_861;
			t_sample mul_435 = (gen_863 * ((t_sample)-0.5));
			t_sample mul_425 = (div_426 * gen_371);
			t_sample mul_427 = (((int)255) * mul_425);
			t_sample add_429 = (((int)0) + mul_427);
			t_sample tap_437 = m_delay_15.read_linear(add_429);
			t_sample tap_432 = m_delay_14.read_linear(add_429);
			t_sample mul_430 = (tap_432 * ((t_sample)0.5));
			t_sample add_433 = (mul_435 + (tap_437 + mul_430));
			t_sample gen_441 = add_433;
			t_sample mul_418 = (gen_441 * ((t_sample)-0.5));
			t_sample mul_408 = (div_409 * gen_371);
			t_sample mul_410 = (((int)556) * mul_408);
			t_sample add_412 = (((int)0) + mul_410);
			t_sample tap_420 = m_delay_13.read_linear(add_412);
			t_sample tap_415 = m_delay_12.read_linear(add_412);
			t_sample mul_413 = (tap_415 * ((t_sample)0.5));
			t_sample add_416 = (mul_418 + (tap_420 + mul_413));
			t_sample gen_424 = add_416;
			t_sample mul_401 = (gen_424 * ((t_sample)-0.5));
			t_sample mul_391 = (div_392 * gen_371);
			t_sample mul_393 = (((int)441) * mul_391);
			t_sample add_395 = (((int)0) + mul_393);
			t_sample tap_403 = m_delay_11.read_linear(add_395);
			t_sample tap_398 = m_delay_10.read_linear(add_395);
			t_sample mul_396 = (tap_398 * ((t_sample)0.5));
			t_sample add_399 = (mul_401 + (tap_403 + mul_396));
			t_sample gen_407 = add_399;
			t_sample mul_384 = (gen_407 * ((t_sample)-0.5));
			t_sample mul_374 = (div_375 * gen_371);
			t_sample mul_376 = (((int)341) * mul_374);
			t_sample add_378 = (((int)0) + mul_376);
			t_sample tap_386 = m_delay_9.read_linear(add_378);
			t_sample tap_381 = m_delay_8.read_linear(add_378);
			t_sample mul_379 = (tap_381 * ((t_sample)0.5));
			t_sample add_382 = (mul_384 + (tap_386 + mul_379));
			t_sample gen_390 = add_382;
			t_sample gen_443 = gen_390;
			t_sample add_616 = (gen_515 + gen_443);
			t_sample mul_614 = (add_616 * sqrt_612);
			t_sample sub_615 = (gen_515 - gen_443);
			t_sample mul_613 = (sub_615 * sqrt_611);
			t_sample add_610 = (mul_614 + mul_613);
			t_sample mul_605 = (add_610 * scale_606);
			t_sample sub_609 = (mul_614 - mul_613);
			t_sample mul_604 = (sub_609 * scale_606);
			t_sample return_193;
			t_sample return_194;
			eq3bandas_d_d_d_d_d_d_d_d_i(mul_605, mul_604, gen_363, gen_355, gen_347, gen_557, gen_549, gen_541, ((int)1), return_193, return_194);
			t_sample expr_598 = return_193;
			t_sample expr_599 = return_194;
			t_sample gen_600 = expr_598;
			t_sample gen_601 = expr_599;
			t_sample mix_2150 = (mul_605 + (gen_337 * (gen_600 - mul_605)));
			t_sample mix_339 = mix_2150;
			t_sample mix_2151 = (mul_604 + (gen_337 * (gen_601 - mul_604)));
			t_sample mix_338 = mix_2151;
			t_sample dbtoa_109 = dbtoa(gen_66);
			t_sample mstosamps_157 = (gen_76 * (samplerate * 0.001));
			t_sample mstosamps_156 = (gen_84 * (samplerate * 0.001));
			t_sample rdiv_163 = safediv(((int)1), gen_92);
			t_sample rsub_162 = (((int)1) - rdiv_163);
			t_sample mul_110 = (mix_338 * ((t_sample)0.25));
			t_sample add_2153 = (mul_602 + mul_110);
			t_sample mix_2152 = (mix_338 + (m_x_PUMP_118 * (add_2153 - mix_338)));
			t_sample mix_112 = mix_2152;
			t_sample tap_150 = m_delay_7.read_step(((int)300));
			t_sample mul_143 = (mix_112 * mix_112);
			t_sample add_147 = (m_history_6 + mul_143);
			t_sample sub_146 = (add_147 - tap_150);
			t_sample div_144 = (sub_146 * ((t_sample)0.0033333333333333));
			t_sample sqrt_142 = sqrt(div_144);
			t_sample gen_155 = sqrt_142;
			t_sample history_145_next_154 = fixdenorm(sub_146);
			t_sample atodb_141 = atodb(gen_155);
			t_sample max_116 = ((atodb_141 < maxb_195) ? maxb_195 : atodb_141);
			int gt_140 = (max_116 > gen_100);
			t_sample mul_119 = (m_history_5 * ((t_sample)0.999));
			t_sample mul_118 = (gt_140 * ((t_sample)0.001));
			t_sample add_121 = (mul_118 + mul_119);
			t_sample gen_125 = add_121;
			t_sample history_120_next_124 = fixdenorm(add_121);
			t_sample sub_139 = (gen_100 - max_116);
			t_sample mul_138 = (sub_139 * rsub_162);
			t_sample dbtoa_136 = dbtoa(mul_138);
			t_sample orange_2156 = (dbtoa_136 - ((int)1));
			t_sample sub_2157 = (gen_125 - ((int)0));
			t_sample scale_2154 = ((safepow((sub_2157 * ((t_sample)1)), ((int)1)) * orange_2156) + ((int)1));
			t_sample iup_197 = (1 / maximum(1, abs(mstosamps_157)));
			t_sample idown_198 = (1 / maximum(1, abs(mstosamps_156)));
			__m_slide_196 = fixdenorm((__m_slide_196 + (((scale_2154 > __m_slide_196) ? iup_197 : idown_198) * (scale_2154 - __m_slide_196))));
			t_sample slide_135 = __m_slide_196;
			t_sample mul_134 = (mix_338 * slide_135);
			t_sample mul_114 = (mul_134 * dbtoa_109);
			t_sample mul_111 = (mix_339 * ((t_sample)0.25));
			t_sample add_2159 = (mul_603 + mul_111);
			t_sample mix_2158 = (mix_339 + (m_x_PUMP_118 * (add_2159 - mix_339)));
			t_sample mix_113 = mix_2158;
			t_sample fixdenorm_167 = fixdenorm(m_history_3);
			t_sample tap_178 = m_delay_4.read_step(((int)300));
			t_sample mul_171 = (mix_113 * mix_113);
			t_sample add_175 = (fixdenorm_167 + mul_171);
			t_sample sub_174 = (add_175 - tap_178);
			t_sample div_172 = (sub_174 * ((t_sample)0.0033333333333333));
			t_sample max_169 = ((div_172 < ((int)0)) ? ((int)0) : div_172);
			t_sample sqrt_170 = sqrt(max_169);
			t_sample gen_183 = sqrt_170;
			t_sample history_173_next_182 = fixdenorm(sub_174);
			t_sample atodb_166 = atodb(gen_183);
			t_sample max_117 = ((atodb_166 < maxb_199) ? maxb_199 : atodb_166);
			int gt_165 = (max_117 > gen_100);
			t_sample mul_127 = (m_history_2 * ((t_sample)0.999));
			t_sample mul_126 = (gt_165 * ((t_sample)0.001));
			t_sample add_129 = (mul_126 + mul_127);
			t_sample gen_133 = add_129;
			t_sample history_128_next_132 = fixdenorm(add_129);
			t_sample sub_164 = (gen_100 - max_117);
			t_sample mul_161 = (sub_164 * rsub_162);
			t_sample dbtoa_159 = dbtoa(mul_161);
			t_sample orange_2162 = (dbtoa_159 - ((int)1));
			t_sample sub_2163 = (gen_133 - ((int)0));
			t_sample scale_2160 = ((safepow((sub_2163 * ((t_sample)1)), ((int)1)) * orange_2162) + ((int)1));
			t_sample iup_201 = (1 / maximum(1, abs(mstosamps_157)));
			t_sample idown_202 = (1 / maximum(1, abs(mstosamps_156)));
			__m_slide_200 = fixdenorm((__m_slide_200 + (((scale_2160 > __m_slide_200) ? iup_201 : idown_202) * (scale_2160 - __m_slide_200))));
			t_sample slide_158 = __m_slide_200;
			t_sample mul_184 = (mix_339 * slide_158);
			t_sample mul_115 = (mul_184 * dbtoa_109);
			t_sample mix_2164 = (mix_338 + (gen_108 * (mul_114 - mix_338)));
			t_sample mix_2165 = (mix_339 + (gen_108 * (mul_115 - mix_339)));
			t_sample mul_533 = (mix_2165 * gen_531);
			t_sample mix_2166 = (mix_2142 + (gen_523 * (mul_533 - mix_2142)));
			t_sample mix_2167 = (mix_2166 + (gen_46 * (in1 - mix_2166)));
			t_sample dcblock_68 = __m_dcblock_203(mix_2167);
			t_sample out1 = dcblock_68;
			t_sample mul_532 = (mix_2164 * gen_531);
			t_sample mix_2168 = (mix_2143 + (gen_523 * (mul_532 - mix_2143)));
			t_sample mix_2169 = (mix_2168 + (gen_46 * (in2 - mix_2168)));
			t_sample dcblock_67 = __m_dcblock_204(mix_2169);
			t_sample out2 = dcblock_67;
			t_sample history_25_next_2140 = fixdenorm(mix_26);
			m_history_113 = history_41_next_45;
			m_history_112 = history_620_next_624;
			m_history_111 = history_518_next_522;
			m_history_110 = history_11_next_15;
			m_history_109 = history_103_next_107;
			m_history_108 = history_95_next_99;
			m_history_107 = history_87_next_91;
			m_history_106 = history_79_next_83;
			m_history_105 = history_71_next_75;
			m_history_104 = history_61_next_65;
			m_history_103 = history_526_next_530;
			m_history_102 = history_332_next_336;
			m_history_101 = history_358_next_362;
			m_history_100 = history_350_next_354;
			m_history_99 = history_342_next_346;
			m_history_98 = history_552_next_556;
			m_history_97 = history_544_next_548;
			m_history_96 = history_536_next_540;
			m_history_95 = history_628_next_632;
			m_history_94 = history_366_next_370;
			m_history_93 = history_51_next_55;
			m_history_92 = history_568_next_572;
			m_history_91 = history_560_next_564;
			m_history_90 = history_33_next_37;
			m_history_89 = history_19_next_23;
			m_history_88 = history_249_next_278;
			m_history_79 = history_208_next_234;
			m_history_78 = history_214_next_235;
			m_history_77 = history_204_next_236;
			m_history_76 = history_210_next_237;
			m_history_75 = history_220_next_238;
			m_history_74 = history_206_next_239;
			m_history_73 = history_216_next_240;
			m_history_80 = history_218_next_233;
			m_history_87 = history_263_next_279;
			m_history_86 = history_259_next_280;
			m_history_85 = history_253_next_281;
			m_history_84 = history_255_next_282;
			m_history_83 = history_265_next_283;
			m_history_82 = history_261_next_284;
			m_history_81 = history_251_next_285;
			m_history_72 = history_3_next_7;
			m_history_71 = history_898_next_902;
			m_history_48 = history_1072_next_1081;
			m_delay_49.write(add_1075);
			m_history_50 = history_1057_next_1066;
			m_delay_51.write(add_1060);
			m_history_52 = history_1042_next_1051;
			m_delay_53.write(add_1045);
			m_history_54 = history_1027_next_1036;
			m_delay_55.write(add_1030);
			m_history_56 = history_1012_next_1021;
			m_delay_57.write(add_1015);
			m_history_58 = history_997_next_1006;
			m_delay_59.write(add_1000);
			m_history_60 = history_982_next_991;
			m_delay_61.write(add_985);
			m_history_62 = history_967_next_976;
			m_delay_63.write(add_970);
			m_history_70 = history_914_next_918;
			m_history_69 = history_922_next_926;
			m_history_68 = history_874_next_878;
			m_history_67 = history_906_next_910;
			m_history_66 = history_882_next_886;
			m_history_65 = history_866_next_870;
			m_history_64 = history_890_next_894;
			m_delay_47.write(gen_1085);
			m_delay_40.write(add_454);
			m_delay_41.write(gen_479);
			m_delay_42.write(add_471);
			m_delay_43.write(gen_496);
			m_delay_44.write(add_488);
			m_delay_45.write(gen_513);
			m_delay_46.write(add_505);
			m_history_39 = history_660_next_664;
			m_history_16 = history_850_next_859;
			m_delay_17.write(add_853);
			m_history_18 = history_835_next_844;
			m_delay_19.write(add_838);
			m_history_20 = history_820_next_829;
			m_delay_21.write(add_823);
			m_history_22 = history_805_next_814;
			m_delay_23.write(add_808);
			m_history_24 = history_790_next_799;
			m_delay_25.write(add_793);
			m_history_26 = history_775_next_784;
			m_delay_27.write(add_778);
			m_history_28 = history_760_next_769;
			m_delay_29.write(add_763);
			m_history_30 = history_745_next_754;
			m_delay_31.write(add_748);
			m_history_38 = history_700_next_704;
			m_history_37 = history_692_next_696;
			m_history_36 = history_676_next_680;
			m_history_35 = history_652_next_656;
			m_history_34 = history_668_next_672;
			m_history_33 = history_684_next_688;
			m_history_32 = history_644_next_648;
			m_delay_15.write(gen_863);
			m_delay_8.write(add_382);
			m_delay_9.write(gen_407);
			m_delay_10.write(add_399);
			m_delay_11.write(gen_424);
			m_delay_12.write(add_416);
			m_delay_13.write(gen_441);
			m_delay_14.write(add_433);
			m_delay_7.write(mul_143);
			m_history_6 = history_145_next_154;
			m_history_5 = history_120_next_124;
			m_delay_4.write(mul_171);
			m_history_3 = history_173_next_182;
			m_history_2 = history_128_next_132;
			m_history_1 = history_25_next_2140;
			m_delay_4.step();
			m_delay_7.step();
			m_delay_8.step();
			m_delay_9.step();
			m_delay_10.step();
			m_delay_11.step();
			m_delay_12.step();
			m_delay_13.step();
			m_delay_14.step();
			m_delay_15.step();
			m_delay_17.step();
			m_delay_19.step();
			m_delay_21.step();
			m_delay_23.step();
			m_delay_25.step();
			m_delay_27.step();
			m_delay_29.step();
			m_delay_31.step();
			m_delay_40.step();
			m_delay_41.step();
			m_delay_42.step();
			m_delay_43.step();
			m_delay_44.step();
			m_delay_45.step();
			m_delay_46.step();
			m_delay_47.step();
			m_delay_49.step();
			m_delay_51.step();
			m_delay_53.step();
			m_delay_55.step();
			m_delay_57.step();
			m_delay_59.step();
			m_delay_61.step();
			m_delay_63.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			
		};
		return __exception;
		
	};
	inline void set_o_PEAKFREQ(t_param _value) {
		m_o_PEAKFREQ_114 = (_value < 500 ? 500 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_r_ONOFFCOMP(t_param _value) {
		m_r_ONOFFCOMP_115 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_u_ATK(t_param _value) {
		m_u_ATK_116 = (_value < 1 ? 1 : (_value > 750 ? 750 : _value));
	};
	inline void set_p_HIFREQ(t_param _value) {
		m_p_HIFREQ_117 = (_value < 2500 ? 2500 : (_value > 15000 ? 15000 : _value));
	};
	inline void set_x_PUMP(t_param _value) {
		m_x_PUMP_118 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_f_ST(t_param _value) {
		m_f_ST_119 = (_value < 0 ? 0 : (_value > 0.85 ? 0.85 : _value));
	};
	inline void set_g_FREEZE(t_param _value) {
		m_g_FREEZE_120 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_d_DAMP(t_param _value) {
		m_d_DAMP_121 = (_value < 0.1 ? 0.1 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_c_REFLECT(t_param _value) {
		m_c_REFLECT_122 = (_value < 0.1 ? 0.1 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_a_INPUT(t_param _value) {
		m_a_INPUT_123 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_t_RATIO(t_param _value) {
		m_t_RATIO_124 = (_value < 1 ? 1 : (_value > 20 ? 20 : _value));
	};
	inline void set_b_DRYWET(t_param _value) {
		m_b_DRYWET_125 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_v_REL(t_param _value) {
		m_v_REL_126 = (_value < 15 ? 15 : (_value > 2000 ? 2000 : _value));
	};
	inline void set_s_THD(t_param _value) {
		m_s_THD_127 = (_value < -60 ? -60 : (_value > 0 ? 0 : _value));
	};
	inline void set_j_HIGAIN(t_param _value) {
		m_j_HIGAIN_128 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_n_LOWFREQ(t_param _value) {
		m_n_LOWFREQ_129 = (_value < 20 ? 20 : (_value > 500 ? 500 : _value));
	};
	inline void set_z_BYPASS(t_param _value) {
		m_z_BYPASS_130 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_i_PEAKGAIN(t_param _value) {
		m_i_PEAKGAIN_131 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_l_HPF(t_param _value) {
		m_l_HPF_132 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_k_LPF(t_param _value) {
		m_k_LPF_133 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_q_ONOFFEQ(t_param _value) {
		m_q_ONOFFEQ_134 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_m_OUTPUT(t_param _value) {
		m_m_OUTPUT_135 = (_value < -24 ? -24 : (_value > 12 ? 12 : _value));
	};
	inline void set_w_MAKEUP(t_param _value) {
		m_w_MAKEUP_136 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void set_y_FILTERS(t_param _value) {
		m_y_FILTERS_137 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_e_SIZE(t_param _value) {
		m_e_SIZE_138 = (_value < 0.1 ? 0.1 : (_value > 4 ? 4 : _value));
	};
	inline void set_h_LOWGAIN(t_param _value) {
		m_h_LOWGAIN_139 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_152;
		t_sample return_153;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_152, return_153);
		t_sample x_592 = return_152;
		sigR = return_153;
		t_sample return_177;
		t_sample return_178;
		peak_d_d_d_d_i(x_592, sigR, pf, pg, bw, return_177, return_178);
		t_sample x_595 = return_177;
		sigR = return_178;
		t_sample return_191;
		t_sample return_192;
		hishelf_d_d_d_d(x_595, sigR, hf, hg, return_191, return_192);
		t_sample x_597 = return_191;
		sigR = return_192;
		out1 = x_597;
		out2 = sigR;
		
	};
	inline void lowshelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_147(freq) != ((int)0)) || (__m_change_148(db) != ((int)0)))) {
			m_b_146 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_f_145 = safediv(freq, m_b_146);
			m_b_144 = ((m_b_146 * m_b_146) - ((int)1));
			m_w_143 = tan(safediv((m_f_145 * ((t_sample)3.1415926535898)), samplerate));
			m_a_142 = safediv(((int)1), (m_w_143 + ((int)1)));
			m_a_141 = (m_w_143 - ((int)1));
			
		};
		t_sample outputLowShelfL = lowshelfCore_d_d_d_d_d(sigL, m_a_142, m_a_141, m_b_144, m_w_143);
		t_sample outputLowShelfR = lowshelfCore_d_d_d_d_d_150(sigR, m_a_142, m_a_141, m_b_144, m_w_143);
		out1 = outputLowShelfL;
		out2 = outputLowShelfR;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_142, t_sample m_a_141, t_sample m_b_144, t_sample m_w_143) {
		t_sample x = (m_a_142 * (input - (m_a_141 * m_z_149)));
		t_sample output = (m_w_143 * (x + m_z_149));
		m_z_149 = x;
		return ((output * m_b_144) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_150(t_sample input, t_sample m_a_142, t_sample m_a_141, t_sample m_b_144, t_sample m_w_143) {
		t_sample x = (m_a_142 * (input - (m_a_141 * m_z_151)));
		t_sample output = (m_w_143 * (x + m_z_151));
		m_z_151 = x;
		return ((output * m_b_144) + input);
		
	};
	inline void peak_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_164(freq) != ((int)0)) || (__m_change_165(db) != ((int)0))) || (__m_change_166(bw) != ((int)0)))) {
			m_w_163 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_162 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_162 * m_b_162) - ((int)1));
			m_d_161 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_167 = safediv(((m_d_161 * m_d_161) - ((int)1)), (m_d_161 * m_b_162));
			m_d_160 = ((v_167 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_167 >= ((int)100)) ? ((int)100) : v_167));
			m_d_159 = (m_d_160 * b);
			m_wq_158 = (m_d_160 * m_w_163);
			m_w_157 = (m_w_163 * m_w_163);
			m_a_156 = safediv(((int)1), ((((int)1) + m_w_157) + m_wq_158));
			m_a_155 = ((m_w_157 - ((int)1)) * ((int)2));
			m_a_154 = ((((int)1) + m_w_157) - m_wq_158);
			
		};
		t_sample outputPeakL = peakCore_d_d_d_d_d_d(sigL, m_w_163, m_d_159, m_a_156, m_a_155, m_a_154);
		t_sample outputPeakR = peakCore_d_d_d_d_d_d_172(sigR, m_w_163, m_d_159, m_a_156, m_a_155, m_a_154);
		out1 = outputPeakL;
		out2 = outputPeakR;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_163, t_sample m_d_159, t_sample m_a_156, t_sample m_a_155, t_sample m_a_154) {
		t_sample output = ((input - m_z_170) * m_w_163);
		m_z_170 = m_z_171;
		m_z_171 = input;
		t_sample output_593 = (m_a_156 * ((output - (m_a_155 * m_z_169)) - (m_a_154 * m_z_168)));
		m_z_168 = m_z_169;
		m_z_169 = output_593;
		t_sample output_594 = (input + (output_593 * m_d_159));
		return output_594;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_172(t_sample input, t_sample m_w_163, t_sample m_d_159, t_sample m_a_156, t_sample m_a_155, t_sample m_a_154) {
		t_sample output = ((input - m_z_175) * m_w_163);
		m_z_175 = m_z_176;
		m_z_176 = input;
		t_sample output_593 = (m_a_156 * ((output - (m_a_155 * m_z_174)) - (m_a_154 * m_z_173)));
		m_z_173 = m_z_174;
		m_z_174 = output_593;
		t_sample output_594 = (input + (output_593 * m_d_159));
		return output_594;
		
	};
	inline void hishelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_185(freq) != ((int)0)) || (__m_change_186(db) != ((int)0)))) {
			m_b_184 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_187 = (freq * m_b_184);
			m_f_183 = ((samplerate < mina_187) ? samplerate : mina_187);
			m_b_182 = ((m_b_184 * m_b_184) - ((int)1));
			m_w_181 = tan(safediv((((m_f_183 < ((int)0)) ? ((int)0) : m_f_183) * ((t_sample)3.1415926535898)), samplerate));
			m_a_180 = safediv(((int)1), (m_w_181 + ((int)1)));
			m_a_179 = (m_w_181 - ((int)1));
			
		};
		t_sample outputHighShelfL = hishelfCore_d_d_d_d(sigL, m_a_180, m_a_179, m_b_182);
		t_sample outputHighShelfR = hishelfCore_d_d_d_d_189(sigR, m_a_180, m_a_179, m_b_182);
		out1 = outputHighShelfL;
		out2 = outputHighShelfR;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_180, t_sample m_a_179, t_sample m_b_182) {
		t_sample x = (m_a_180 * (input - (m_a_179 * m_z_188)));
		t_sample output = (x - m_z_188);
		m_z_188 = x;
		t_sample output_596 = ((output * m_b_182) + input);
		return output_596;
		
	};
	inline t_sample hishelfCore_d_d_d_d_189(t_sample input, t_sample m_a_180, t_sample m_a_179, t_sample m_b_182) {
		t_sample x = (m_a_180 * (input - (m_a_179 * m_z_190)));
		t_sample output = (x - m_z_190);
		m_z_190 = x;
		t_sample output_596 = ((output * m_b_182) + input);
		return output_596;
		
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
int num_params() { return 26; }

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
		case 23: self->set_x_PUMP(value); break;
		case 24: self->set_y_FILTERS(value); break;
		case 25: self->set_z_BYPASS(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_a_INPUT_123; break;
		case 1: *value = self->m_b_DRYWET_125; break;
		case 2: *value = self->m_c_REFLECT_122; break;
		case 3: *value = self->m_d_DAMP_121; break;
		case 4: *value = self->m_e_SIZE_138; break;
		case 5: *value = self->m_f_ST_119; break;
		case 6: *value = self->m_g_FREEZE_120; break;
		case 7: *value = self->m_h_LOWGAIN_139; break;
		case 8: *value = self->m_i_PEAKGAIN_131; break;
		case 9: *value = self->m_j_HIGAIN_128; break;
		case 10: *value = self->m_k_LPF_133; break;
		case 11: *value = self->m_l_HPF_132; break;
		case 12: *value = self->m_m_OUTPUT_135; break;
		case 13: *value = self->m_n_LOWFREQ_129; break;
		case 14: *value = self->m_o_PEAKFREQ_114; break;
		case 15: *value = self->m_p_HIFREQ_117; break;
		case 16: *value = self->m_q_ONOFFEQ_134; break;
		case 17: *value = self->m_r_ONOFFCOMP_115; break;
		case 18: *value = self->m_s_THD_127; break;
		case 19: *value = self->m_t_RATIO_124; break;
		case 20: *value = self->m_u_ATK_116; break;
		case 21: *value = self->m_v_REL_126; break;
		case 22: *value = self->m_w_MAKEUP_136; break;
		case 23: *value = self->m_x_PUMP_118; break;
		case 24: *value = self->m_y_FILTERS_137; break;
		case 25: *value = self->m_z_BYPASS_130; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(26 * sizeof(ParamInfo));
	self->__commonstate.numparams = 26;
	// initialize parameter 0 ("m_a_INPUT_123")
	pi = self->__commonstate.params + 0;
	pi->name = "a_INPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_INPUT_123;
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
	// initialize parameter 2 ("m_c_REFLECT_122")
	pi = self->__commonstate.params + 2;
	pi->name = "c_REFLECT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_REFLECT_122;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.95;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_DAMP_121")
	pi = self->__commonstate.params + 3;
	pi->name = "d_DAMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_DAMP_121;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.95;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_SIZE_138")
	pi = self->__commonstate.params + 4;
	pi->name = "e_SIZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_SIZE_138;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_ST_119")
	pi = self->__commonstate.params + 5;
	pi->name = "f_ST";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_ST_119;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.85;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_FREEZE_120")
	pi = self->__commonstate.params + 6;
	pi->name = "g_FREEZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_FREEZE_120;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_LOWGAIN_139")
	pi = self->__commonstate.params + 7;
	pi->name = "h_LOWGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_LOWGAIN_139;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_PEAKGAIN_131")
	pi = self->__commonstate.params + 8;
	pi->name = "i_PEAKGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_PEAKGAIN_131;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_HIGAIN_128")
	pi = self->__commonstate.params + 9;
	pi->name = "j_HIGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_HIGAIN_128;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_LPF_133")
	pi = self->__commonstate.params + 10;
	pi->name = "k_LPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_LPF_133;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_HPF_132")
	pi = self->__commonstate.params + 11;
	pi->name = "l_HPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_HPF_132;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_OUTPUT_135")
	pi = self->__commonstate.params + 12;
	pi->name = "m_OUTPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_OUTPUT_135;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 12;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_LOWFREQ_129")
	pi = self->__commonstate.params + 13;
	pi->name = "n_LOWFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_LOWFREQ_129;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_PEAKFREQ_114")
	pi = self->__commonstate.params + 14;
	pi->name = "o_PEAKFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_PEAKFREQ_114;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 500;
	pi->outputmax = 2500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_HIFREQ_117")
	pi = self->__commonstate.params + 15;
	pi->name = "p_HIFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_HIFREQ_117;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 2500;
	pi->outputmax = 15000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_ONOFFEQ_134")
	pi = self->__commonstate.params + 16;
	pi->name = "q_ONOFFEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_ONOFFEQ_134;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 17 ("m_r_ONOFFCOMP_115")
	pi = self->__commonstate.params + 17;
	pi->name = "r_ONOFFCOMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_ONOFFCOMP_115;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 18 ("m_s_THD_127")
	pi = self->__commonstate.params + 18;
	pi->name = "s_THD";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_THD_127;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -60;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_RATIO_124")
	pi = self->__commonstate.params + 19;
	pi->name = "t_RATIO";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_RATIO_124;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_ATK_116")
	pi = self->__commonstate.params + 20;
	pi->name = "u_ATK";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_ATK_116;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 750;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_REL_126")
	pi = self->__commonstate.params + 21;
	pi->name = "v_REL";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_REL_126;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 15;
	pi->outputmax = 2000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_MAKEUP_136")
	pi = self->__commonstate.params + 22;
	pi->name = "w_MAKEUP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_MAKEUP_136;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -6;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 23 ("m_x_PUMP_118")
	pi = self->__commonstate.params + 23;
	pi->name = "x_PUMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_x_PUMP_118;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 24 ("m_y_FILTERS_137")
	pi = self->__commonstate.params + 24;
	pi->name = "y_FILTERS";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_y_FILTERS_137;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 25 ("m_z_BYPASS_130")
	pi = self->__commonstate.params + 25;
	pi->name = "z_BYPASS";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_z_BYPASS_130;
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
