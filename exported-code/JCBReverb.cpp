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
	t_sample m_z_BYPASS_137;
	t_sample m_x_PUMP_138;
	t_sample m_w_MAKEUP_136;
	t_sample m_u_ATK_134;
	t_sample m_k_LPF_135;
	t_sample m_l_HPF_133;
	t_sample m_v_REL_139;
	t_sample m_a_141;
	t_sample m_a_142;
	t_sample m_b_146;
	t_sample m_history_6;
	t_sample m_q_ONOFFEQ_132;
	t_sample m_f_145;
	t_sample m_w_143;
	t_sample m_b_144;
	t_sample m_c_REFLECT_131;
	t_sample m_n_LOWFREQ_130;
	t_sample m_s_THD_129;
	t_sample m_r_ONOFFCOMP_118;
	t_sample m_t_RATIO_119;
	t_sample m_o_PEAKFREQ_120;
	t_sample m_f_ST_117;
	t_sample m_a_INPUT_115;
	t_sample m_e_SIZE_116;
	t_sample m_history_5;
	t_sample m_m_OUTPUT_121;
	t_sample m_b_DRYWET_123;
	t_sample m_y_FILTERS_127;
	t_sample m_d_DAMP_128;
	t_sample m_p_HIFREQ_122;
	t_sample m_h_LOWGAIN_126;
	t_sample m_g_FREEZE_124;
	t_sample m_i_PEAKGAIN_125;
	t_sample m_j_HIGAIN_114;
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
		m_delay_4.reset("m_delay_4", ((int)44100));
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_delay_7.reset("m_delay_7", samplerate);
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
		m_j_HIGAIN_114 = 0;
		m_a_INPUT_115 = 0;
		m_e_SIZE_116 = 1;
		m_f_ST_117 = 0.5;
		m_r_ONOFFCOMP_118 = 0;
		m_t_RATIO_119 = 4;
		m_o_PEAKFREQ_120 = 1500;
		m_m_OUTPUT_121 = 0;
		m_p_HIFREQ_122 = 8600;
		m_b_DRYWET_123 = 0.33;
		m_g_FREEZE_124 = 0;
		m_i_PEAKGAIN_125 = 0;
		m_h_LOWGAIN_126 = 0;
		m_y_FILTERS_127 = 0;
		m_d_DAMP_128 = 0.25;
		m_s_THD_129 = -18;
		m_n_LOWFREQ_130 = 250;
		m_c_REFLECT_131 = 0.85;
		m_q_ONOFFEQ_132 = 0;
		m_l_HPF_133 = 20;
		m_u_ATK_134 = 5;
		m_k_LPF_135 = 20000;
		m_w_MAKEUP_136 = 0;
		m_z_BYPASS_137 = 0;
		m_x_PUMP_138 = 0;
		m_v_REL_139 = 250;
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
		t_sample dbtoa_7712 = dbtoa(m_a_INPUT_115);
		t_sample mul_8145 = (dbtoa_7712 * ((t_sample)0.001));
		t_sample mul_7697 = (m_z_BYPASS_137 * ((t_sample)0.001));
		t_sample mul_8067 = (m_b_DRYWET_123 * ((t_sample)0.001));
		int gte_8164 = (m_g_FREEZE_124 >= ((t_sample)0.5));
		t_sample mul_10015 = (gte_8164 * ((t_sample)0.001));
		t_sample mul_7745 = (m_r_ONOFFCOMP_118 * ((t_sample)0.001));
		t_sample mul_7739 = (m_s_THD_129 * ((t_sample)0.001));
		t_sample mul_7733 = (m_t_RATIO_119 * ((t_sample)0.001));
		t_sample mul_7727 = (m_u_ATK_134 * ((t_sample)0.001));
		t_sample mul_7721 = (m_v_REL_139 * ((t_sample)0.001));
		t_sample mul_7713 = (m_w_MAKEUP_136 * ((t_sample)0.001));
		t_sample dbtoa_7711 = dbtoa(m_m_OUTPUT_121);
		t_sample mul_8073 = (dbtoa_7711 * ((t_sample)0.001));
		t_sample mul_7917 = (m_q_ONOFFEQ_132 * ((t_sample)0.001));
		t_sample mul_7937 = (m_n_LOWFREQ_130 * ((t_sample)0.001));
		t_sample mul_7931 = (m_o_PEAKFREQ_120 * ((t_sample)0.001));
		t_sample mul_7925 = (m_p_HIFREQ_122 * ((t_sample)0.001));
		t_sample mul_8093 = (m_h_LOWGAIN_126 * ((t_sample)0.001));
		t_sample mul_8087 = (m_i_PEAKGAIN_125 * ((t_sample)0.001));
		t_sample mul_8081 = (m_j_HIGAIN_114 * ((t_sample)0.001));
		t_sample mul_8151 = (m_f_ST_117 * ((t_sample)0.001));
		t_sample mul_7943 = (m_e_SIZE_116 * ((t_sample)0.001));
		t_sample mul_7705 = (m_d_DAMP_128 * ((t_sample)0.001));
		t_sample mul_8105 = (m_k_LPF_135 * ((t_sample)0.001));
		t_sample mul_8099 = (m_l_HPF_133 * ((t_sample)0.001));
		t_sample mul_7691 = (m_y_FILTERS_127 * ((t_sample)0.001));
		int rsub_8163 = (((int)1) - gte_8164);
		t_sample mul_9757 = (rsub_8163 * ((t_sample)0.001));
		t_sample rsub_8160 = (((int)1) - m_c_REFLECT_131);
		int choice_140 = gte_8164;
		t_sample gate_8159 = ((choice_140 >= 1) ? rsub_8160 : 0);
		t_sample add_8161 = (m_c_REFLECT_131 + gate_8159);
		t_sample mul_10336 = (add_8161 * ((t_sample)0.001));
		t_sample div_8401 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_8053 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_8039 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_8025 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_8011 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_8228 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_7994 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_7980 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_7966 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_7952 = (samplerate * ((t_sample)2.2675736961451e-05));
		int maxb_195 = (-96);
		int maxb_199 = (-96);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mix_10594 = (((int)0) + (((t_sample)0.05) * (m_history_1 - ((int)0))));
			t_sample mix_9504 = mix_10594;
			t_sample mul_8146 = (m_history_113 * ((t_sample)0.999));
			t_sample add_8148 = (mul_8145 + mul_8146);
			t_sample gen_8150 = add_8148;
			t_sample history_8147_next_8149 = fixdenorm(add_8148);
			t_sample mul_8130 = (in1 * gen_8150);
			t_sample out3 = mul_8130;
			t_sample mul_8129 = (in2 * gen_8150);
			t_sample out4 = mul_8129;
			t_sample mul_7698 = (m_history_112 * ((t_sample)0.999));
			t_sample add_7700 = (mul_7697 + mul_7698);
			t_sample gen_7702 = add_7700;
			t_sample history_7699_next_7701 = fixdenorm(add_7700);
			t_sample mul_8068 = (m_history_111 * ((t_sample)0.999));
			t_sample add_8070 = (mul_8067 + mul_8068);
			t_sample gen_8072 = add_8070;
			t_sample history_8069_next_8071 = fixdenorm(add_8070);
			t_sample mul_10016 = (m_history_110 * ((t_sample)0.999));
			t_sample add_10018 = (mul_10015 + mul_10016);
			t_sample gen_10020 = add_10018;
			t_sample history_10017_next_10019 = fixdenorm(add_10018);
			t_sample mix_10595 = (in1 + (gen_10020 * (((int)0) - in1)));
			t_sample mix_10596 = (in2 + (gen_10020 * (((int)0) - in2)));
			t_sample mul_7746 = (m_history_109 * ((t_sample)0.999));
			t_sample add_7748 = (mul_7745 + mul_7746);
			t_sample gen_7750 = add_7748;
			t_sample history_7747_next_7749 = fixdenorm(add_7748);
			t_sample mul_7740 = (m_history_108 * ((t_sample)0.999));
			t_sample add_7742 = (mul_7739 + mul_7740);
			t_sample gen_7744 = add_7742;
			t_sample history_7741_next_7743 = fixdenorm(add_7742);
			t_sample mul_7734 = (m_history_107 * ((t_sample)0.999));
			t_sample add_7736 = (mul_7733 + mul_7734);
			t_sample gen_7738 = add_7736;
			t_sample history_7735_next_7737 = fixdenorm(add_7736);
			t_sample mul_7728 = (m_history_106 * ((t_sample)0.999));
			t_sample add_7730 = (mul_7727 + mul_7728);
			t_sample gen_7732 = add_7730;
			t_sample history_7729_next_7731 = fixdenorm(add_7730);
			t_sample mul_7722 = (m_history_105 * ((t_sample)0.999));
			t_sample add_7724 = (mul_7721 + mul_7722);
			t_sample gen_7726 = add_7724;
			t_sample history_7723_next_7725 = fixdenorm(add_7724);
			t_sample mul_7714 = (m_history_104 * ((t_sample)0.999));
			t_sample add_7716 = (mul_7713 + mul_7714);
			t_sample gen_7718 = add_7716;
			t_sample history_7715_next_7717 = fixdenorm(add_7716);
			t_sample mul_8074 = (m_history_103 * ((t_sample)0.999));
			t_sample add_8076 = (mul_8073 + mul_8074);
			t_sample gen_8078 = add_8076;
			t_sample history_8075_next_8077 = fixdenorm(add_8076);
			t_sample mul_7918 = (m_history_102 * ((t_sample)0.999));
			t_sample add_7920 = (mul_7917 + mul_7918);
			t_sample gen_7922 = add_7920;
			t_sample history_7919_next_7921 = fixdenorm(add_7920);
			t_sample mul_7938 = (m_history_101 * ((t_sample)0.999));
			t_sample add_7940 = (mul_7937 + mul_7938);
			t_sample gen_7942 = add_7940;
			t_sample history_7939_next_7941 = fixdenorm(add_7940);
			t_sample mul_7932 = (m_history_100 * ((t_sample)0.999));
			t_sample add_7934 = (mul_7931 + mul_7932);
			t_sample gen_7936 = add_7934;
			t_sample history_7933_next_7935 = fixdenorm(add_7934);
			t_sample mul_7926 = (m_history_99 * ((t_sample)0.999));
			t_sample add_7928 = (mul_7925 + mul_7926);
			t_sample gen_7930 = add_7928;
			t_sample history_7927_next_7929 = fixdenorm(add_7928);
			t_sample mul_8094 = (m_history_98 * ((t_sample)0.999));
			t_sample add_8096 = (mul_8093 + mul_8094);
			t_sample gen_8098 = add_8096;
			t_sample history_8095_next_8097 = fixdenorm(add_8096);
			t_sample mul_8088 = (m_history_97 * ((t_sample)0.999));
			t_sample add_8090 = (mul_8087 + mul_8088);
			t_sample gen_8092 = add_8090;
			t_sample history_8089_next_8091 = fixdenorm(add_8090);
			t_sample mul_8082 = (m_history_96 * ((t_sample)0.999));
			t_sample add_8084 = (mul_8081 + mul_8082);
			t_sample gen_8086 = add_8084;
			t_sample history_8083_next_8085 = fixdenorm(add_8084);
			t_sample mul_8152 = (m_history_95 * ((t_sample)0.999));
			t_sample add_8154 = (mul_8151 + mul_8152);
			t_sample gen_8156 = add_8154;
			t_sample history_8153_next_8155 = fixdenorm(add_8154);
			t_sample sub_10600 = (gen_8156 - ((int)0));
			t_sample scale_10597 = ((safepow((sub_10600 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_8133 = scale_10597;
			t_sample sqrt_8138 = sqrt(gen_8156);
			t_sample rsub_8157 = (((int)1) - gen_8156);
			t_sample sqrt_8139 = sqrt(rsub_8157);
			t_sample mul_7944 = (m_history_94 * ((t_sample)0.999));
			t_sample add_7946 = (mul_7943 + mul_7944);
			t_sample gen_7948 = add_7946;
			t_sample history_7945_next_7947 = fixdenorm(add_7946);
			t_sample mul_7706 = (m_history_93 * ((t_sample)0.999));
			t_sample add_7708 = (mul_7705 + mul_7706);
			t_sample gen_7710 = add_7708;
			t_sample history_7707_next_7709 = fixdenorm(add_7708);
			t_sample mul_8106 = (m_history_92 * ((t_sample)0.999));
			t_sample add_8108 = (mul_8105 + mul_8106);
			t_sample gen_8110 = add_8108;
			t_sample history_8107_next_8109 = fixdenorm(add_8108);
			t_sample mul_8100 = (m_history_91 * ((t_sample)0.999));
			t_sample add_8102 = (mul_8099 + mul_8100);
			t_sample gen_8104 = add_8102;
			t_sample history_8101_next_8103 = fixdenorm(add_8102);
			t_sample mul_7692 = (m_history_90 * ((t_sample)0.999));
			t_sample add_7694 = (mul_7691 + mul_7692);
			t_sample gen_7696 = add_7694;
			t_sample history_7693_next_7695 = fixdenorm(add_7694);
			t_sample mul_7949 = (((int)23) * gen_7948);
			t_sample mul_9758 = (m_history_89 * ((t_sample)0.999));
			t_sample add_9760 = (mul_9757 + mul_9758);
			t_sample gen_9762 = add_9760;
			t_sample history_9759_next_9761 = fixdenorm(add_9760);
			t_sample mul_8162 = (mul_8130 * gen_9762);
			t_sample mul_8144 = (mul_8129 * gen_9762);
			t_sample omega = safediv((gen_8110 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((int)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) - cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((((int)1) - cs) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_7901 = a2;
			t_sample expr_7902 = a1;
			t_sample expr_7903 = a2;
			t_sample expr_7904 = b1;
			t_sample expr_7905 = b2;
			t_sample omega_7907 = safediv((gen_8104 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_7906 = sin(omega_7907);
			t_sample cs_7913 = cos(omega_7907);
			t_sample alpha_7914 = ((sn_7906 * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b_7911 = safediv(((int)1), (((int)1) + alpha_7914));
			t_sample a_7912 = (((((int)1) + cs_7913) * ((t_sample)0.5)) * b_7911);
			t_sample a_7910 = ((-(((int)1) + cs_7913)) * b_7911);
			t_sample b_7908 = ((((int)-2) * cs_7913) * b_7911);
			t_sample b_7909 = ((((int)1) - alpha_7914) * b_7911);
			t_sample expr_7896 = a_7912;
			t_sample expr_7897 = a_7910;
			t_sample expr_7898 = a_7912;
			t_sample expr_7899 = b_7908;
			t_sample expr_7900 = b_7909;
			t_sample mul_7870 = (m_history_88 * expr_7903);
			t_sample mul_7880 = (m_history_85 * expr_7903);
			t_sample mul_7872 = (m_history_84 * expr_7902);
			t_sample mul_7882 = (m_history_83 * expr_7902);
			t_sample mul_7875 = (mul_8144 * expr_7901);
			t_sample mul_7885 = (mul_8162 * expr_7901);
			t_sample mul_7866 = (m_history_87 * expr_7905);
			t_sample mul_7876 = (m_history_86 * expr_7905);
			t_sample mul_7868 = (m_history_82 * expr_7904);
			t_sample sub_7874 = (((mul_7875 + mul_7872) + mul_7870) - (mul_7868 + mul_7866));
			t_sample gen_7895 = sub_7874;
			t_sample mul_7878 = (m_history_81 * expr_7904);
			t_sample sub_7884 = (((mul_7880 + mul_7882) + mul_7885) - (mul_7878 + mul_7876));
			t_sample gen_7894 = sub_7884;
			t_sample history_7871_next_7886 = fixdenorm(m_history_84);
			t_sample history_7867_next_7887 = fixdenorm(m_history_82);
			t_sample history_7877_next_7888 = fixdenorm(m_history_81);
			t_sample history_7881_next_7889 = fixdenorm(m_history_83);
			t_sample history_7873_next_7890 = fixdenorm(mul_8144);
			t_sample history_7883_next_7891 = fixdenorm(mul_8162);
			t_sample history_7869_next_7892 = fixdenorm(sub_7874);
			t_sample history_7879_next_7893 = fixdenorm(sub_7884);
			t_sample mul_7835 = (m_history_78 * expr_7898);
			t_sample mul_7845 = (m_history_79 * expr_7898);
			t_sample mul_7837 = (m_history_75 * expr_7897);
			t_sample mul_7847 = (m_history_76 * expr_7897);
			t_sample mul_7840 = (gen_7895 * expr_7896);
			t_sample mul_7850 = (gen_7894 * expr_7896);
			t_sample mul_7831 = (m_history_77 * expr_7900);
			t_sample mul_7841 = (m_history_80 * expr_7900);
			t_sample mul_7833 = (m_history_74 * expr_7899);
			t_sample sub_7839 = (((mul_7840 + mul_7837) + mul_7835) - (mul_7833 + mul_7831));
			t_sample gen_7860 = sub_7839;
			t_sample mul_7843 = (m_history_73 * expr_7899);
			t_sample sub_7849 = (((mul_7845 + mul_7847) + mul_7850) - (mul_7843 + mul_7841));
			t_sample gen_7859 = sub_7849;
			t_sample history_7842_next_7851 = fixdenorm(m_history_73);
			t_sample history_7846_next_7852 = fixdenorm(m_history_76);
			t_sample history_7836_next_7853 = fixdenorm(m_history_75);
			t_sample history_7832_next_7854 = fixdenorm(m_history_74);
			t_sample history_7848_next_7855 = fixdenorm(gen_7894);
			t_sample history_7838_next_7856 = fixdenorm(gen_7895);
			t_sample history_7834_next_7857 = fixdenorm(sub_7839);
			t_sample history_7844_next_7858 = fixdenorm(sub_7849);
			t_sample mix_10601 = (mul_8162 + (gen_7696 * (gen_7859 - mul_8162)));
			t_sample mix_7825 = mix_10601;
			t_sample gen_7915 = mix_7825;
			t_sample mix_10602 = (mul_8144 + (gen_7696 * (gen_7860 - mul_8144)));
			t_sample mix_7824 = mix_10602;
			t_sample gen_7916 = mix_7824;
			t_sample mul_10337 = (m_history_72 * ((t_sample)0.999));
			t_sample add_10339 = (mul_10336 + mul_10337);
			t_sample gen_10341 = add_10339;
			t_sample history_10338_next_10340 = fixdenorm(add_10339);
			t_sample rsub_8412 = (((int)1) - gen_7710);
			t_sample mul_8386 = (div_8401 * gen_7948);
			t_sample mul_8393 = (((int)1277) * mul_8386);
			t_sample mul_8357 = (m_history_71 * ((t_sample)0.999));
			t_sample mul_8356 = (mul_8393 * ((t_sample)0.001));
			t_sample add_8359 = (mul_8356 + mul_8357);
			t_sample gen_8361 = add_8359;
			t_sample history_8358_next_8360 = fixdenorm(add_8359);
			t_sample gen_8408 = gen_8361;
			t_sample mul_8387 = (((int)1116) * mul_8386);
			t_sample mul_8339 = (m_history_70 * ((t_sample)0.999));
			t_sample mul_8338 = (mul_8387 * ((t_sample)0.001));
			t_sample add_8341 = (mul_8338 + mul_8339);
			t_sample gen_8343 = add_8341;
			t_sample history_8340_next_8342 = fixdenorm(add_8341);
			t_sample gen_8411 = gen_8343;
			t_sample mul_8399 = (((int)1617) * mul_8386);
			t_sample mul_8375 = (m_history_69 * ((t_sample)0.999));
			t_sample mul_8374 = (mul_8399 * ((t_sample)0.001));
			t_sample add_8377 = (mul_8374 + mul_8375);
			t_sample gen_8379 = add_8377;
			t_sample history_8376_next_8378 = fixdenorm(add_8377);
			t_sample gen_8405 = gen_8379;
			t_sample mul_8397 = (((int)1491) * mul_8386);
			t_sample mul_8369 = (m_history_68 * ((t_sample)0.999));
			t_sample mul_8368 = (mul_8397 * ((t_sample)0.001));
			t_sample add_8371 = (mul_8368 + mul_8369);
			t_sample gen_8373 = add_8371;
			t_sample history_8370_next_8372 = fixdenorm(add_8371);
			t_sample gen_8406 = gen_8373;
			t_sample mul_8391 = (((int)1356) * mul_8386);
			t_sample mul_8351 = (m_history_67 * ((t_sample)0.999));
			t_sample mul_8350 = (mul_8391 * ((t_sample)0.001));
			t_sample add_8353 = (mul_8350 + mul_8351);
			t_sample gen_8355 = add_8353;
			t_sample history_8352_next_8354 = fixdenorm(add_8353);
			t_sample gen_8409 = gen_8355;
			t_sample mul_8389 = (((int)1188) * mul_8386);
			t_sample mul_8345 = (m_history_66 * ((t_sample)0.999));
			t_sample mul_8344 = (mul_8389 * ((t_sample)0.001));
			t_sample add_8347 = (mul_8344 + mul_8345);
			t_sample gen_8349 = add_8347;
			t_sample history_8346_next_8348 = fixdenorm(add_8347);
			t_sample gen_8410 = gen_8349;
			t_sample mul_8402 = (((int)1557) * mul_8386);
			t_sample mul_8381 = (m_history_65 * ((t_sample)0.999));
			t_sample mul_8380 = (mul_8402 * ((t_sample)0.001));
			t_sample add_8383 = (mul_8380 + mul_8381);
			t_sample gen_8385 = add_8383;
			t_sample history_8382_next_8384 = fixdenorm(add_8383);
			t_sample gen_8404 = gen_8385;
			t_sample mul_8395 = (((int)1422) * mul_8386);
			t_sample mul_8363 = (m_history_64 * ((t_sample)0.999));
			t_sample mul_8362 = (mul_8395 * ((t_sample)0.001));
			t_sample add_8365 = (mul_8362 + mul_8363);
			t_sample gen_8367 = add_8365;
			t_sample history_8364_next_8366 = fixdenorm(add_8365);
			t_sample gen_8407 = gen_8367;
			t_sample rsub_8414 = (((int)1) - rsub_8412);
			t_sample mul_8416 = (m_history_62 * rsub_8414);
			t_sample add_8413 = (((int)0) + gen_8411);
			t_sample tap_8422 = m_delay_63.read_linear(add_8413);
			t_sample mul_8419 = (tap_8422 * rsub_8412);
			t_sample add_8418 = (mul_8419 + mul_8416);
			t_sample mul_8415 = (add_8418 * gen_10341);
			t_sample add_8420 = (gen_7915 + mul_8415);
			t_sample gen_8424 = add_8420;
			t_sample history_8417_next_8423 = fixdenorm(add_8418);
			t_sample rsub_8426 = (((int)1) - rsub_8412);
			t_sample mul_8428 = (m_history_60 * rsub_8426);
			t_sample add_8425 = (((int)0) + gen_8410);
			t_sample tap_8434 = m_delay_61.read_linear(add_8425);
			t_sample mul_8431 = (tap_8434 * rsub_8412);
			t_sample add_8430 = (mul_8431 + mul_8428);
			t_sample mul_8427 = (add_8430 * gen_10341);
			t_sample add_8432 = (gen_7915 + mul_8427);
			t_sample gen_8436 = add_8432;
			t_sample history_8429_next_8435 = fixdenorm(add_8430);
			t_sample rsub_8438 = (((int)1) - rsub_8412);
			t_sample mul_8440 = (m_history_58 * rsub_8438);
			t_sample add_8437 = (((int)0) + gen_8409);
			t_sample tap_8446 = m_delay_59.read_linear(add_8437);
			t_sample mul_8443 = (tap_8446 * rsub_8412);
			t_sample add_8442 = (mul_8443 + mul_8440);
			t_sample mul_8439 = (add_8442 * gen_10341);
			t_sample add_8444 = (gen_7915 + mul_8439);
			t_sample gen_8448 = add_8444;
			t_sample history_8441_next_8447 = fixdenorm(add_8442);
			t_sample rsub_8450 = (((int)1) - rsub_8412);
			t_sample mul_8452 = (m_history_56 * rsub_8450);
			t_sample add_8449 = (((int)0) + gen_8408);
			t_sample tap_8458 = m_delay_57.read_linear(add_8449);
			t_sample mul_8455 = (tap_8458 * rsub_8412);
			t_sample add_8454 = (mul_8455 + mul_8452);
			t_sample mul_8451 = (add_8454 * gen_10341);
			t_sample add_8456 = (gen_7915 + mul_8451);
			t_sample gen_8460 = add_8456;
			t_sample history_8453_next_8459 = fixdenorm(add_8454);
			t_sample rsub_8462 = (((int)1) - rsub_8412);
			t_sample mul_8464 = (m_history_54 * rsub_8462);
			t_sample add_8461 = (((int)0) + gen_8407);
			t_sample tap_8470 = m_delay_55.read_linear(add_8461);
			t_sample mul_8467 = (tap_8470 * rsub_8412);
			t_sample add_8466 = (mul_8467 + mul_8464);
			t_sample mul_8463 = (add_8466 * gen_10341);
			t_sample add_8468 = (gen_7915 + mul_8463);
			t_sample gen_8472 = add_8468;
			t_sample history_8465_next_8471 = fixdenorm(add_8466);
			t_sample rsub_8474 = (((int)1) - rsub_8412);
			t_sample mul_8476 = (m_history_52 * rsub_8474);
			t_sample add_8473 = (((int)0) + gen_8406);
			t_sample tap_8482 = m_delay_53.read_linear(add_8473);
			t_sample mul_8479 = (tap_8482 * rsub_8412);
			t_sample add_8478 = (mul_8479 + mul_8476);
			t_sample mul_8475 = (add_8478 * gen_10341);
			t_sample add_8480 = (gen_7915 + mul_8475);
			t_sample gen_8484 = add_8480;
			t_sample history_8477_next_8483 = fixdenorm(add_8478);
			t_sample rsub_8486 = (((int)1) - rsub_8412);
			t_sample mul_8488 = (m_history_50 * rsub_8486);
			t_sample add_8485 = (((int)0) + gen_8405);
			t_sample tap_8494 = m_delay_51.read_linear(add_8485);
			t_sample mul_8491 = (tap_8494 * rsub_8412);
			t_sample add_8490 = (mul_8491 + mul_8488);
			t_sample mul_8487 = (add_8490 * gen_10341);
			t_sample add_8492 = (gen_7915 + mul_8487);
			t_sample gen_8496 = add_8492;
			t_sample history_8489_next_8495 = fixdenorm(add_8490);
			t_sample rsub_8498 = (((int)1) - rsub_8412);
			t_sample mul_8500 = (m_history_48 * rsub_8498);
			t_sample add_8497 = (((int)0) + gen_8404);
			t_sample tap_8506 = m_delay_49.read_linear(add_8497);
			t_sample mul_8503 = (tap_8506 * rsub_8412);
			t_sample add_8502 = (mul_8503 + mul_8500);
			t_sample mul_8499 = (add_8502 * gen_10341);
			t_sample add_8504 = (gen_7915 + mul_8499);
			t_sample gen_8508 = add_8504;
			t_sample history_8501_next_8507 = fixdenorm(add_8502);
			t_sample mul_8509 = ((((((((gen_8508 + gen_8496) + gen_8484) + gen_8472) + gen_8460) + gen_8448) + gen_8436) + gen_8424) * ((t_sample)0.125));
			t_sample gen_8510 = mul_8509;
			t_sample mul_8062 = (gen_8510 * ((t_sample)-0.5));
			t_sample mul_8052 = (div_8053 * gen_7948);
			t_sample mul_8054 = (((int)255) * mul_8052);
			t_sample add_8056 = (((int)0) + mul_8054);
			t_sample tap_8064 = m_delay_47.read_linear(add_8056);
			t_sample tap_8059 = m_delay_46.read_linear(add_8056);
			t_sample mul_8057 = (tap_8059 * ((t_sample)0.5));
			t_sample add_8060 = (mul_8062 + (tap_8064 + mul_8057));
			t_sample gen_8065 = add_8060;
			t_sample mul_8048 = (gen_8065 * ((t_sample)-0.5));
			t_sample mul_8038 = (div_8039 * gen_7948);
			t_sample mul_8040 = (((int)556) * mul_8038);
			t_sample add_8042 = (((int)0) + mul_8040);
			t_sample tap_8050 = m_delay_45.read_linear(add_8042);
			t_sample tap_8045 = m_delay_44.read_linear(add_8042);
			t_sample mul_8043 = (tap_8045 * ((t_sample)0.5));
			t_sample add_8046 = (mul_8048 + (tap_8050 + mul_8043));
			t_sample gen_8051 = add_8046;
			t_sample mul_8034 = (gen_8051 * ((t_sample)-0.5));
			t_sample mul_8024 = (div_8025 * gen_7948);
			t_sample mul_8026 = (((int)441) * mul_8024);
			t_sample add_8028 = (((int)0) + mul_8026);
			t_sample tap_8036 = m_delay_43.read_linear(add_8028);
			t_sample tap_8031 = m_delay_42.read_linear(add_8028);
			t_sample mul_8029 = (tap_8031 * ((t_sample)0.5));
			t_sample add_8032 = (mul_8034 + (tap_8036 + mul_8029));
			t_sample gen_8037 = add_8032;
			t_sample mul_8020 = (gen_8037 * ((t_sample)-0.5));
			t_sample mul_8010 = (div_8011 * gen_7948);
			t_sample mul_8012 = (((int)341) * mul_8010);
			t_sample add_8014 = (((int)0) + mul_8012);
			t_sample tap_8022 = m_delay_41.read_linear(add_8014);
			t_sample tap_8017 = m_delay_40.read_linear(add_8014);
			t_sample mul_8015 = (tap_8017 * ((t_sample)0.5));
			t_sample add_8018 = (mul_8020 + (tap_8022 + mul_8015));
			t_sample gen_8023 = add_8018;
			t_sample gen_8066 = gen_8023;
			t_sample rsub_8239 = (((int)1) - gen_7710);
			t_sample mul_8213 = (div_8228 * gen_7948);
			t_sample mul_8218 = (((int)1356) * mul_8213);
			t_sample mul_8178 = (m_history_39 * ((t_sample)0.999));
			t_sample mul_8177 = (mul_8218 * ((t_sample)0.001));
			t_sample add_8180 = (mul_8177 + mul_8178);
			t_sample gen_8182 = add_8180;
			t_sample history_8179_next_8181 = fixdenorm(add_8180);
			t_sample gen_8236 = gen_8182;
			t_sample mul_8229 = (((int)1557) * mul_8213);
			t_sample mul_8208 = (m_history_38 * ((t_sample)0.999));
			t_sample mul_8207 = (mul_8229 * ((t_sample)0.001));
			t_sample add_8210 = (mul_8207 + mul_8208);
			t_sample gen_8212 = add_8210;
			t_sample history_8209_next_8211 = fixdenorm(add_8210);
			t_sample gen_8231 = gen_8212;
			t_sample mul_8222 = (((int)1422) * mul_8213);
			t_sample mul_8190 = (m_history_37 * ((t_sample)0.999));
			t_sample mul_8189 = (mul_8222 * ((t_sample)0.001));
			t_sample add_8192 = (mul_8189 + mul_8190);
			t_sample gen_8194 = add_8192;
			t_sample history_8191_next_8193 = fixdenorm(add_8192);
			t_sample gen_8234 = gen_8194;
			t_sample mul_8220 = (((int)1277) * mul_8213);
			t_sample mul_8184 = (m_history_36 * ((t_sample)0.999));
			t_sample mul_8183 = (mul_8220 * ((t_sample)0.001));
			t_sample add_8186 = (mul_8183 + mul_8184);
			t_sample gen_8188 = add_8186;
			t_sample history_8185_next_8187 = fixdenorm(add_8186);
			t_sample gen_8235 = gen_8188;
			t_sample mul_8224 = (((int)1491) * mul_8213);
			t_sample mul_8196 = (m_history_35 * ((t_sample)0.999));
			t_sample mul_8195 = (mul_8224 * ((t_sample)0.001));
			t_sample add_8198 = (mul_8195 + mul_8196);
			t_sample gen_8200 = add_8198;
			t_sample history_8197_next_8199 = fixdenorm(add_8198);
			t_sample gen_8233 = gen_8200;
			t_sample mul_8214 = (((int)1116) * mul_8213);
			t_sample mul_8166 = (m_history_34 * ((t_sample)0.999));
			t_sample mul_8165 = (mul_8214 * ((t_sample)0.001));
			t_sample add_8168 = (mul_8165 + mul_8166);
			t_sample gen_8170 = add_8168;
			t_sample history_8167_next_8169 = fixdenorm(add_8168);
			t_sample gen_8238 = gen_8170;
			t_sample mul_8226 = (((int)1617) * mul_8213);
			t_sample mul_8202 = (m_history_33 * ((t_sample)0.999));
			t_sample mul_8201 = (mul_8226 * ((t_sample)0.001));
			t_sample add_8204 = (mul_8201 + mul_8202);
			t_sample gen_8206 = add_8204;
			t_sample history_8203_next_8205 = fixdenorm(add_8204);
			t_sample gen_8232 = gen_8206;
			t_sample mul_8216 = (((int)1188) * mul_8213);
			t_sample mul_8172 = (m_history_32 * ((t_sample)0.999));
			t_sample mul_8171 = (mul_8216 * ((t_sample)0.001));
			t_sample add_8174 = (mul_8171 + mul_8172);
			t_sample gen_8176 = add_8174;
			t_sample history_8173_next_8175 = fixdenorm(add_8174);
			t_sample gen_8237 = gen_8176;
			t_sample rsub_8241 = (((int)1) - rsub_8239);
			t_sample mul_8243 = (m_history_30 * rsub_8241);
			t_sample add_8240 = (mul_7949 + gen_8238);
			t_sample tap_8249 = m_delay_31.read_linear(add_8240);
			t_sample mul_8246 = (tap_8249 * rsub_8239);
			t_sample add_8245 = (mul_8246 + mul_8243);
			t_sample mul_8242 = (add_8245 * gen_10341);
			t_sample add_8247 = (gen_7916 + mul_8242);
			t_sample gen_8251 = add_8247;
			t_sample history_8244_next_8250 = fixdenorm(add_8245);
			t_sample rsub_8253 = (((int)1) - rsub_8239);
			t_sample mul_8255 = (m_history_28 * rsub_8253);
			t_sample add_8252 = (mul_7949 + gen_8237);
			t_sample tap_8261 = m_delay_29.read_linear(add_8252);
			t_sample mul_8258 = (tap_8261 * rsub_8239);
			t_sample add_8257 = (mul_8258 + mul_8255);
			t_sample mul_8254 = (add_8257 * gen_10341);
			t_sample add_8259 = (gen_7916 + mul_8254);
			t_sample gen_8263 = add_8259;
			t_sample history_8256_next_8262 = fixdenorm(add_8257);
			t_sample rsub_8265 = (((int)1) - rsub_8239);
			t_sample mul_8267 = (m_history_26 * rsub_8265);
			t_sample add_8264 = (mul_7949 + gen_8236);
			t_sample tap_8273 = m_delay_27.read_linear(add_8264);
			t_sample mul_8270 = (tap_8273 * rsub_8239);
			t_sample add_8269 = (mul_8270 + mul_8267);
			t_sample mul_8266 = (add_8269 * gen_10341);
			t_sample add_8271 = (gen_7916 + mul_8266);
			t_sample gen_8275 = add_8271;
			t_sample history_8268_next_8274 = fixdenorm(add_8269);
			t_sample rsub_8277 = (((int)1) - rsub_8239);
			t_sample mul_8279 = (m_history_24 * rsub_8277);
			t_sample add_8276 = (mul_7949 + gen_8235);
			t_sample tap_8285 = m_delay_25.read_linear(add_8276);
			t_sample mul_8282 = (tap_8285 * rsub_8239);
			t_sample add_8281 = (mul_8282 + mul_8279);
			t_sample mul_8278 = (add_8281 * gen_10341);
			t_sample add_8283 = (gen_7916 + mul_8278);
			t_sample gen_8287 = add_8283;
			t_sample history_8280_next_8286 = fixdenorm(add_8281);
			t_sample rsub_8289 = (((int)1) - rsub_8239);
			t_sample mul_8291 = (m_history_22 * rsub_8289);
			t_sample add_8288 = (mul_7949 + gen_8234);
			t_sample tap_8297 = m_delay_23.read_linear(add_8288);
			t_sample mul_8294 = (tap_8297 * rsub_8239);
			t_sample add_8293 = (mul_8294 + mul_8291);
			t_sample mul_8290 = (add_8293 * gen_10341);
			t_sample add_8295 = (gen_7916 + mul_8290);
			t_sample gen_8299 = add_8295;
			t_sample history_8292_next_8298 = fixdenorm(add_8293);
			t_sample rsub_8301 = (((int)1) - rsub_8239);
			t_sample mul_8303 = (m_history_20 * rsub_8301);
			t_sample add_8300 = (mul_7949 + gen_8233);
			t_sample tap_8309 = m_delay_21.read_linear(add_8300);
			t_sample mul_8306 = (tap_8309 * rsub_8239);
			t_sample add_8305 = (mul_8306 + mul_8303);
			t_sample mul_8302 = (add_8305 * gen_10341);
			t_sample add_8307 = (gen_7916 + mul_8302);
			t_sample gen_8311 = add_8307;
			t_sample history_8304_next_8310 = fixdenorm(add_8305);
			t_sample rsub_8313 = (((int)1) - rsub_8239);
			t_sample mul_8315 = (m_history_18 * rsub_8313);
			t_sample add_8312 = (mul_7949 + gen_8232);
			t_sample tap_8321 = m_delay_19.read_linear(add_8312);
			t_sample mul_8318 = (tap_8321 * rsub_8239);
			t_sample add_8317 = (mul_8318 + mul_8315);
			t_sample mul_8314 = (add_8317 * gen_10341);
			t_sample add_8319 = (gen_7916 + mul_8314);
			t_sample gen_8323 = add_8319;
			t_sample history_8316_next_8322 = fixdenorm(add_8317);
			t_sample rsub_8325 = (((int)1) - rsub_8239);
			t_sample mul_8327 = (m_history_16 * rsub_8325);
			t_sample add_8324 = (mul_7949 + gen_8231);
			t_sample tap_8333 = m_delay_17.read_linear(add_8324);
			t_sample mul_8330 = (tap_8333 * rsub_8239);
			t_sample add_8329 = (mul_8330 + mul_8327);
			t_sample mul_8326 = (add_8329 * gen_10341);
			t_sample add_8331 = (gen_7916 + mul_8326);
			t_sample gen_8335 = add_8331;
			t_sample history_8328_next_8334 = fixdenorm(add_8329);
			t_sample mul_8336 = ((((((((gen_8335 + gen_8323) + gen_8311) + gen_8299) + gen_8287) + gen_8275) + gen_8263) + gen_8251) * ((t_sample)0.125));
			t_sample gen_8337 = mul_8336;
			t_sample mul_8003 = (gen_8337 * ((t_sample)-0.5));
			t_sample mul_7993 = (div_7994 * gen_7948);
			t_sample mul_7995 = (((int)255) * mul_7993);
			t_sample add_7997 = (((int)0) + mul_7995);
			t_sample tap_8005 = m_delay_15.read_linear(add_7997);
			t_sample tap_8000 = m_delay_14.read_linear(add_7997);
			t_sample mul_7998 = (tap_8000 * ((t_sample)0.5));
			t_sample add_8001 = (mul_8003 + (tap_8005 + mul_7998));
			t_sample gen_8006 = add_8001;
			t_sample mul_7989 = (gen_8006 * ((t_sample)-0.5));
			t_sample mul_7979 = (div_7980 * gen_7948);
			t_sample mul_7981 = (((int)556) * mul_7979);
			t_sample add_7983 = (((int)0) + mul_7981);
			t_sample tap_7991 = m_delay_13.read_linear(add_7983);
			t_sample tap_7986 = m_delay_12.read_linear(add_7983);
			t_sample mul_7984 = (tap_7986 * ((t_sample)0.5));
			t_sample add_7987 = (mul_7989 + (tap_7991 + mul_7984));
			t_sample gen_7992 = add_7987;
			t_sample mul_7975 = (gen_7992 * ((t_sample)-0.5));
			t_sample mul_7965 = (div_7966 * gen_7948);
			t_sample mul_7967 = (((int)441) * mul_7965);
			t_sample add_7969 = (((int)0) + mul_7967);
			t_sample tap_7977 = m_delay_11.read_linear(add_7969);
			t_sample tap_7972 = m_delay_10.read_linear(add_7969);
			t_sample mul_7970 = (tap_7972 * ((t_sample)0.5));
			t_sample add_7973 = (mul_7975 + (tap_7977 + mul_7970));
			t_sample gen_7978 = add_7973;
			t_sample mul_7961 = (gen_7978 * ((t_sample)-0.5));
			t_sample mul_7951 = (div_7952 * gen_7948);
			t_sample mul_7953 = (((int)341) * mul_7951);
			t_sample add_7955 = (((int)0) + mul_7953);
			t_sample tap_7963 = m_delay_9.read_linear(add_7955);
			t_sample tap_7958 = m_delay_8.read_linear(add_7955);
			t_sample mul_7956 = (tap_7958 * ((t_sample)0.5));
			t_sample add_7959 = (mul_7961 + (tap_7963 + mul_7956));
			t_sample gen_7964 = add_7959;
			t_sample gen_8007 = gen_7964;
			t_sample add_8143 = (gen_8066 + gen_8007);
			t_sample mul_8141 = (add_8143 * sqrt_8139);
			t_sample sub_8142 = (gen_8066 - gen_8007);
			t_sample mul_8140 = (sub_8142 * sqrt_8138);
			t_sample add_8137 = (mul_8141 + mul_8140);
			t_sample mul_8132 = (add_8137 * scale_8133);
			t_sample sub_8136 = (mul_8141 - mul_8140);
			t_sample mul_8131 = (sub_8136 * scale_8133);
			t_sample return_193;
			t_sample return_194;
			eq3bandas_d_d_d_d_d_d_d_d_i(mul_8132, mul_8131, gen_7942, gen_7936, gen_7930, gen_8098, gen_8092, gen_8086, ((int)1), return_193, return_194);
			t_sample expr_8125 = return_193;
			t_sample expr_8126 = return_194;
			t_sample gen_8128 = expr_8126;
			t_sample gen_8127 = expr_8125;
			t_sample mix_10603 = (mul_8132 + (gen_7922 * (gen_8127 - mul_8132)));
			t_sample mix_7924 = mix_10603;
			t_sample mix_10604 = (mul_8131 + (gen_7922 * (gen_8128 - mul_8131)));
			t_sample mix_7923 = mix_10604;
			t_sample dbtoa_7751 = dbtoa(gen_7718);
			t_sample mstosamps_7792 = (gen_7726 * (samplerate * 0.001));
			t_sample mstosamps_7791 = (gen_7732 * (samplerate * 0.001));
			t_sample rdiv_7798 = safediv(((int)1), gen_7738);
			t_sample rsub_7797 = (((int)1) - rdiv_7798);
			t_sample mul_7753 = (mix_7924 * ((t_sample)0.25));
			t_sample add_10606 = (mul_8130 + mul_7753);
			t_sample mix_10605 = (mix_7924 + (m_x_PUMP_138 * (add_10606 - mix_7924)));
			t_sample mix_7755 = mix_10605;
			t_sample fixdenorm_7802 = fixdenorm(m_history_6);
			t_sample tap_7813 = m_delay_7.read_step(((int)300));
			t_sample mul_7806 = (mix_7755 * mix_7755);
			t_sample add_7810 = (fixdenorm_7802 + mul_7806);
			t_sample sub_7809 = (add_7810 - tap_7813);
			t_sample div_7807 = (sub_7809 * ((t_sample)0.0033333333333333));
			t_sample max_7804 = ((div_7807 < ((int)0)) ? ((int)0) : div_7807);
			t_sample sqrt_7805 = sqrt(max_7804);
			t_sample gen_7815 = sqrt_7805;
			t_sample history_7808_next_7814 = fixdenorm(sub_7809);
			t_sample atodb_7801 = atodb(gen_7815);
			t_sample max_7759 = ((atodb_7801 < maxb_195) ? maxb_195 : atodb_7801);
			int gt_7800 = (max_7759 > gen_7744);
			t_sample mul_7767 = (m_history_5 * ((t_sample)0.999));
			t_sample mul_7766 = (gt_7800 * ((t_sample)0.001));
			t_sample add_7769 = (mul_7766 + mul_7767);
			t_sample gen_7771 = add_7769;
			t_sample history_7768_next_7770 = fixdenorm(add_7769);
			t_sample sub_7799 = (gen_7744 - max_7759);
			t_sample mul_7796 = (sub_7799 * rsub_7797);
			t_sample dbtoa_7794 = dbtoa(mul_7796);
			t_sample orange_10609 = (dbtoa_7794 - ((int)1));
			t_sample sub_10610 = (gen_7771 - ((int)0));
			t_sample scale_10607 = ((safepow((sub_10610 * ((t_sample)1)), ((int)1)) * orange_10609) + ((int)1));
			t_sample iup_197 = (1 / maximum(1, abs(mstosamps_7792)));
			t_sample idown_198 = (1 / maximum(1, abs(mstosamps_7791)));
			__m_slide_196 = fixdenorm((__m_slide_196 + (((scale_10607 > __m_slide_196) ? iup_197 : idown_198) * (scale_10607 - __m_slide_196))));
			t_sample slide_7793 = __m_slide_196;
			t_sample mul_7816 = (mix_7924 * slide_7793);
			t_sample mul_7757 = (mul_7816 * dbtoa_7751);
			t_sample mul_7752 = (mix_7923 * ((t_sample)0.25));
			t_sample add_10612 = (mul_8129 + mul_7752);
			t_sample mix_10611 = (mix_7923 + (m_x_PUMP_138 * (add_10612 - mix_7923)));
			t_sample mix_7754 = mix_10611;
			t_sample tap_7788 = m_delay_4.read_step(((int)300));
			t_sample mul_7781 = (mix_7754 * mix_7754);
			t_sample add_7785 = (m_history_3 + mul_7781);
			t_sample sub_7784 = (add_7785 - tap_7788);
			t_sample div_7782 = (sub_7784 * ((t_sample)0.0033333333333333));
			t_sample sqrt_7780 = sqrt(div_7782);
			t_sample gen_7790 = sqrt_7780;
			t_sample history_7783_next_7789 = fixdenorm(sub_7784);
			t_sample atodb_7779 = atodb(gen_7790);
			t_sample max_7758 = ((atodb_7779 < maxb_199) ? maxb_199 : atodb_7779);
			int gt_7778 = (max_7758 > gen_7744);
			t_sample mul_7761 = (m_history_2 * ((t_sample)0.999));
			t_sample mul_7760 = (gt_7778 * ((t_sample)0.001));
			t_sample add_7763 = (mul_7760 + mul_7761);
			t_sample gen_7765 = add_7763;
			t_sample history_7762_next_7764 = fixdenorm(add_7763);
			t_sample sub_7777 = (gen_7744 - max_7758);
			t_sample mul_7776 = (sub_7777 * rsub_7797);
			t_sample dbtoa_7774 = dbtoa(mul_7776);
			t_sample orange_10615 = (dbtoa_7774 - ((int)1));
			t_sample sub_10616 = (gen_7765 - ((int)0));
			t_sample scale_10613 = ((safepow((sub_10616 * ((t_sample)1)), ((int)1)) * orange_10615) + ((int)1));
			t_sample iup_201 = (1 / maximum(1, abs(mstosamps_7792)));
			t_sample idown_202 = (1 / maximum(1, abs(mstosamps_7791)));
			__m_slide_200 = fixdenorm((__m_slide_200 + (((scale_10613 > __m_slide_200) ? iup_201 : idown_202) * (scale_10613 - __m_slide_200))));
			t_sample slide_7773 = __m_slide_200;
			t_sample mul_7772 = (mix_7923 * slide_7773);
			t_sample mul_7756 = (mul_7772 * dbtoa_7751);
			t_sample mix_10617 = (mix_7924 + (gen_7750 * (mul_7757 - mix_7924)));
			t_sample mix_10618 = (mix_7923 + (gen_7750 * (mul_7756 - mix_7923)));
			t_sample mul_8080 = (mix_10617 * gen_8078);
			t_sample mix_10619 = (mix_10595 + (gen_8072 * (mul_8080 - mix_10595)));
			t_sample mix_10620 = (mix_10619 + (gen_7702 * (in1 - mix_10619)));
			t_sample dcblock_7720 = __m_dcblock_203(mix_10620);
			t_sample out1 = dcblock_7720;
			t_sample mul_8079 = (mix_10618 * gen_8078);
			t_sample mix_10621 = (mix_10596 + (gen_8072 * (mul_8079 - mix_10596)));
			t_sample mix_10622 = (mix_10621 + (gen_7702 * (in2 - mix_10621)));
			t_sample dcblock_7719 = __m_dcblock_204(mix_10622);
			t_sample out2 = dcblock_7719;
			t_sample history_7685_next_10531 = fixdenorm(mix_9504);
			m_history_113 = history_8147_next_8149;
			m_history_112 = history_7699_next_7701;
			m_history_111 = history_8069_next_8071;
			m_history_110 = history_10017_next_10019;
			m_history_109 = history_7747_next_7749;
			m_history_108 = history_7741_next_7743;
			m_history_107 = history_7735_next_7737;
			m_history_106 = history_7729_next_7731;
			m_history_105 = history_7723_next_7725;
			m_history_104 = history_7715_next_7717;
			m_history_103 = history_8075_next_8077;
			m_history_102 = history_7919_next_7921;
			m_history_101 = history_7939_next_7941;
			m_history_100 = history_7933_next_7935;
			m_history_99 = history_7927_next_7929;
			m_history_98 = history_8095_next_8097;
			m_history_97 = history_8089_next_8091;
			m_history_96 = history_8083_next_8085;
			m_history_95 = history_8153_next_8155;
			m_history_94 = history_7945_next_7947;
			m_history_93 = history_7707_next_7709;
			m_history_92 = history_8107_next_8109;
			m_history_91 = history_8101_next_8103;
			m_history_90 = history_7693_next_7695;
			m_history_89 = history_9759_next_9761;
			m_history_88 = history_7871_next_7886;
			m_history_79 = history_7846_next_7852;
			m_history_78 = history_7836_next_7853;
			m_history_77 = history_7832_next_7854;
			m_history_76 = history_7848_next_7855;
			m_history_75 = history_7838_next_7856;
			m_history_74 = history_7834_next_7857;
			m_history_73 = history_7844_next_7858;
			m_history_80 = history_7842_next_7851;
			m_history_87 = history_7867_next_7887;
			m_history_86 = history_7877_next_7888;
			m_history_85 = history_7881_next_7889;
			m_history_84 = history_7873_next_7890;
			m_history_83 = history_7883_next_7891;
			m_history_82 = history_7869_next_7892;
			m_history_81 = history_7879_next_7893;
			m_history_72 = history_10338_next_10340;
			m_history_71 = history_8358_next_8360;
			m_history_48 = history_8501_next_8507;
			m_delay_49.write(add_8504);
			m_history_50 = history_8489_next_8495;
			m_delay_51.write(add_8492);
			m_history_52 = history_8477_next_8483;
			m_delay_53.write(add_8480);
			m_history_54 = history_8465_next_8471;
			m_delay_55.write(add_8468);
			m_history_56 = history_8453_next_8459;
			m_delay_57.write(add_8456);
			m_history_58 = history_8441_next_8447;
			m_delay_59.write(add_8444);
			m_history_60 = history_8429_next_8435;
			m_delay_61.write(add_8432);
			m_history_62 = history_8417_next_8423;
			m_delay_63.write(add_8420);
			m_history_70 = history_8340_next_8342;
			m_history_69 = history_8376_next_8378;
			m_history_68 = history_8370_next_8372;
			m_history_67 = history_8352_next_8354;
			m_history_66 = history_8346_next_8348;
			m_history_65 = history_8382_next_8384;
			m_history_64 = history_8364_next_8366;
			m_delay_47.write(gen_8510);
			m_delay_40.write(add_8018);
			m_delay_41.write(gen_8037);
			m_delay_42.write(add_8032);
			m_delay_43.write(gen_8051);
			m_delay_44.write(add_8046);
			m_delay_45.write(gen_8065);
			m_delay_46.write(add_8060);
			m_history_39 = history_8179_next_8181;
			m_history_16 = history_8328_next_8334;
			m_delay_17.write(add_8331);
			m_history_18 = history_8316_next_8322;
			m_delay_19.write(add_8319);
			m_history_20 = history_8304_next_8310;
			m_delay_21.write(add_8307);
			m_history_22 = history_8292_next_8298;
			m_delay_23.write(add_8295);
			m_history_24 = history_8280_next_8286;
			m_delay_25.write(add_8283);
			m_history_26 = history_8268_next_8274;
			m_delay_27.write(add_8271);
			m_history_28 = history_8256_next_8262;
			m_delay_29.write(add_8259);
			m_history_30 = history_8244_next_8250;
			m_delay_31.write(add_8247);
			m_history_38 = history_8209_next_8211;
			m_history_37 = history_8191_next_8193;
			m_history_36 = history_8185_next_8187;
			m_history_35 = history_8197_next_8199;
			m_history_34 = history_8167_next_8169;
			m_history_33 = history_8203_next_8205;
			m_history_32 = history_8173_next_8175;
			m_delay_15.write(gen_8337);
			m_delay_8.write(add_7959);
			m_delay_9.write(gen_7978);
			m_delay_10.write(add_7973);
			m_delay_11.write(gen_7992);
			m_delay_12.write(add_7987);
			m_delay_13.write(gen_8006);
			m_delay_14.write(add_8001);
			m_delay_7.write(mul_7806);
			m_history_6 = history_7808_next_7814;
			m_history_5 = history_7768_next_7770;
			m_delay_4.write(mul_7781);
			m_history_3 = history_7783_next_7789;
			m_history_2 = history_7762_next_7764;
			m_history_1 = history_7685_next_10531;
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
	inline void set_j_HIGAIN(t_param _value) {
		m_j_HIGAIN_114 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_a_INPUT(t_param _value) {
		m_a_INPUT_115 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_e_SIZE(t_param _value) {
		m_e_SIZE_116 = (_value < 0.1 ? 0.1 : (_value > 4 ? 4 : _value));
	};
	inline void set_f_ST(t_param _value) {
		m_f_ST_117 = (_value < 0 ? 0 : (_value > 0.9 ? 0.9 : _value));
	};
	inline void set_r_ONOFFCOMP(t_param _value) {
		m_r_ONOFFCOMP_118 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_t_RATIO(t_param _value) {
		m_t_RATIO_119 = (_value < 1 ? 1 : (_value > 20 ? 20 : _value));
	};
	inline void set_o_PEAKFREQ(t_param _value) {
		m_o_PEAKFREQ_120 = (_value < 500 ? 500 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_m_OUTPUT(t_param _value) {
		m_m_OUTPUT_121 = (_value < -24 ? -24 : (_value > 12 ? 12 : _value));
	};
	inline void set_p_HIFREQ(t_param _value) {
		m_p_HIFREQ_122 = (_value < 2500 ? 2500 : (_value > 15000 ? 15000 : _value));
	};
	inline void set_b_DRYWET(t_param _value) {
		m_b_DRYWET_123 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_g_FREEZE(t_param _value) {
		m_g_FREEZE_124 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_i_PEAKGAIN(t_param _value) {
		m_i_PEAKGAIN_125 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_h_LOWGAIN(t_param _value) {
		m_h_LOWGAIN_126 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_y_FILTERS(t_param _value) {
		m_y_FILTERS_127 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_d_DAMP(t_param _value) {
		m_d_DAMP_128 = (_value < 0.1 ? 0.1 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_s_THD(t_param _value) {
		m_s_THD_129 = (_value < -60 ? -60 : (_value > 0 ? 0 : _value));
	};
	inline void set_n_LOWFREQ(t_param _value) {
		m_n_LOWFREQ_130 = (_value < 20 ? 20 : (_value > 500 ? 500 : _value));
	};
	inline void set_c_REFLECT(t_param _value) {
		m_c_REFLECT_131 = (_value < 0.1 ? 0.1 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_q_ONOFFEQ(t_param _value) {
		m_q_ONOFFEQ_132 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_l_HPF(t_param _value) {
		m_l_HPF_133 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_u_ATK(t_param _value) {
		m_u_ATK_134 = (_value < 1 ? 1 : (_value > 750 ? 750 : _value));
	};
	inline void set_k_LPF(t_param _value) {
		m_k_LPF_135 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_w_MAKEUP(t_param _value) {
		m_w_MAKEUP_136 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void set_z_BYPASS(t_param _value) {
		m_z_BYPASS_137 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_x_PUMP(t_param _value) {
		m_x_PUMP_138 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_v_REL(t_param _value) {
		m_v_REL_139 = (_value < 15 ? 15 : (_value > 2000 ? 2000 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_152;
		t_sample return_153;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_152, return_153);
		t_sample x_8119 = return_152;
		sigR = return_153;
		t_sample return_177;
		t_sample return_178;
		peak_d_d_d_d_i(x_8119, sigR, pf, pg, bw, return_177, return_178);
		t_sample x_8122 = return_177;
		sigR = return_178;
		t_sample return_191;
		t_sample return_192;
		hishelf_d_d_d_d(x_8122, sigR, hf, hg, return_191, return_192);
		t_sample x_8124 = return_191;
		sigR = return_192;
		out1 = x_8124;
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
		t_sample output_8120 = (m_a_156 * ((output - (m_a_155 * m_z_169)) - (m_a_154 * m_z_168)));
		m_z_168 = m_z_169;
		m_z_169 = output_8120;
		t_sample output_8121 = (input + (output_8120 * m_d_159));
		return output_8121;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_172(t_sample input, t_sample m_w_163, t_sample m_d_159, t_sample m_a_156, t_sample m_a_155, t_sample m_a_154) {
		t_sample output = ((input - m_z_175) * m_w_163);
		m_z_175 = m_z_176;
		m_z_176 = input;
		t_sample output_8120 = (m_a_156 * ((output - (m_a_155 * m_z_174)) - (m_a_154 * m_z_173)));
		m_z_173 = m_z_174;
		m_z_174 = output_8120;
		t_sample output_8121 = (input + (output_8120 * m_d_159));
		return output_8121;
		
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
		t_sample output_8123 = ((output * m_b_182) + input);
		return output_8123;
		
	};
	inline t_sample hishelfCore_d_d_d_d_189(t_sample input, t_sample m_a_180, t_sample m_a_179, t_sample m_b_182) {
		t_sample x = (m_a_180 * (input - (m_a_179 * m_z_190)));
		t_sample output = (x - m_z_190);
		m_z_190 = x;
		t_sample output_8123 = ((output * m_b_182) + input);
		return output_8123;
		
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
		case 0: *value = self->m_a_INPUT_115; break;
		case 1: *value = self->m_b_DRYWET_123; break;
		case 2: *value = self->m_c_REFLECT_131; break;
		case 3: *value = self->m_d_DAMP_128; break;
		case 4: *value = self->m_e_SIZE_116; break;
		case 5: *value = self->m_f_ST_117; break;
		case 6: *value = self->m_g_FREEZE_124; break;
		case 7: *value = self->m_h_LOWGAIN_126; break;
		case 8: *value = self->m_i_PEAKGAIN_125; break;
		case 9: *value = self->m_j_HIGAIN_114; break;
		case 10: *value = self->m_k_LPF_135; break;
		case 11: *value = self->m_l_HPF_133; break;
		case 12: *value = self->m_m_OUTPUT_121; break;
		case 13: *value = self->m_n_LOWFREQ_130; break;
		case 14: *value = self->m_o_PEAKFREQ_120; break;
		case 15: *value = self->m_p_HIFREQ_122; break;
		case 16: *value = self->m_q_ONOFFEQ_132; break;
		case 17: *value = self->m_r_ONOFFCOMP_118; break;
		case 18: *value = self->m_s_THD_129; break;
		case 19: *value = self->m_t_RATIO_119; break;
		case 20: *value = self->m_u_ATK_134; break;
		case 21: *value = self->m_v_REL_139; break;
		case 22: *value = self->m_w_MAKEUP_136; break;
		case 23: *value = self->m_x_PUMP_138; break;
		case 24: *value = self->m_y_FILTERS_127; break;
		case 25: *value = self->m_z_BYPASS_137; break;
		
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
	// initialize parameter 0 ("m_a_INPUT_115")
	pi = self->__commonstate.params + 0;
	pi->name = "a_INPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_INPUT_115;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -12;
	pi->outputmax = 12;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_DRYWET_123")
	pi = self->__commonstate.params + 1;
	pi->name = "b_DRYWET";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_DRYWET_123;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_REFLECT_131")
	pi = self->__commonstate.params + 2;
	pi->name = "c_REFLECT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_REFLECT_131;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.95;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_DAMP_128")
	pi = self->__commonstate.params + 3;
	pi->name = "d_DAMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_DAMP_128;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.95;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_SIZE_116")
	pi = self->__commonstate.params + 4;
	pi->name = "e_SIZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_SIZE_116;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_ST_117")
	pi = self->__commonstate.params + 5;
	pi->name = "f_ST";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_ST_117;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.9;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_FREEZE_124")
	pi = self->__commonstate.params + 6;
	pi->name = "g_FREEZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_FREEZE_124;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_LOWGAIN_126")
	pi = self->__commonstate.params + 7;
	pi->name = "h_LOWGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_LOWGAIN_126;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_PEAKGAIN_125")
	pi = self->__commonstate.params + 8;
	pi->name = "i_PEAKGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_PEAKGAIN_125;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_HIGAIN_114")
	pi = self->__commonstate.params + 9;
	pi->name = "j_HIGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_HIGAIN_114;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_LPF_135")
	pi = self->__commonstate.params + 10;
	pi->name = "k_LPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_LPF_135;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_HPF_133")
	pi = self->__commonstate.params + 11;
	pi->name = "l_HPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_HPF_133;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_OUTPUT_121")
	pi = self->__commonstate.params + 12;
	pi->name = "m_OUTPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_OUTPUT_121;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 12;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_LOWFREQ_130")
	pi = self->__commonstate.params + 13;
	pi->name = "n_LOWFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_LOWFREQ_130;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_PEAKFREQ_120")
	pi = self->__commonstate.params + 14;
	pi->name = "o_PEAKFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_PEAKFREQ_120;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 500;
	pi->outputmax = 2500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_HIFREQ_122")
	pi = self->__commonstate.params + 15;
	pi->name = "p_HIFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_HIFREQ_122;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 2500;
	pi->outputmax = 15000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_ONOFFEQ_132")
	pi = self->__commonstate.params + 16;
	pi->name = "q_ONOFFEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_ONOFFEQ_132;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 17 ("m_r_ONOFFCOMP_118")
	pi = self->__commonstate.params + 17;
	pi->name = "r_ONOFFCOMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_ONOFFCOMP_118;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 18 ("m_s_THD_129")
	pi = self->__commonstate.params + 18;
	pi->name = "s_THD";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_THD_129;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -60;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_RATIO_119")
	pi = self->__commonstate.params + 19;
	pi->name = "t_RATIO";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_RATIO_119;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_ATK_134")
	pi = self->__commonstate.params + 20;
	pi->name = "u_ATK";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_ATK_134;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 750;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_REL_139")
	pi = self->__commonstate.params + 21;
	pi->name = "v_REL";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_REL_139;
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
	// initialize parameter 23 ("m_x_PUMP_138")
	pi = self->__commonstate.params + 23;
	pi->name = "x_PUMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_x_PUMP_138;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 24 ("m_y_FILTERS_127")
	pi = self->__commonstate.params + 24;
	pi->name = "y_FILTERS";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_y_FILTERS_127;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 25 ("m_z_BYPASS_137")
	pi = self->__commonstate.params + 25;
	pi->name = "z_BYPASS";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_z_BYPASS_137;
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
