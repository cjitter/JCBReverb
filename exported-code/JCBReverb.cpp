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
	Change __m_change_145;
	Change __m_change_162;
	Change __m_change_144;
	Change __m_change_161;
	Change __m_change_163;
	Change __m_change_183;
	Change __m_change_182;
	DCBlock __m_dcblock_200;
	DCBlock __m_dcblock_201;
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
	t_sample m_a_INPUT_134;
	t_sample m_u_ATK_135;
	t_sample m_g_FREEZE_133;
	t_sample m_z_BYPASS_131;
	t_sample m_m_OUTPUT_132;
	t_sample m_d_DAMP_130;
	t_sample m_v_REL_136;
	t_sample m_a_138;
	t_sample m_a_139;
	t_sample m_b_143;
	t_sample m_history_15;
	t_sample m_c_REFLECT_129;
	t_sample m_f_142;
	t_sample m_w_140;
	t_sample m_b_141;
	t_sample m_history_5;
	t_sample m_r_ONOFFCOMP_128;
	t_sample m_l_HPF_126;
	t_sample m_s_THD_116;
	t_sample m_t_RATIO_117;
	t_sample m_w_MAKEUP_118;
	t_sample m_f_ST_115;
	t_sample m_o_PEAKFREQ_113;
	t_sample m_b_DRYWET_114;
	t_sample m_y_IOMODE_127;
	t_sample m_q_ONOFFEQ_119;
	t_sample m_p_HIFREQ_121;
	t_sample m_k_LPF_125;
	t_sample m_n_LOWFREQ_120;
	t_sample m_j_HIGAIN_124;
	t_sample m_h_LOWGAIN_122;
	t_sample m_i_PEAKGAIN_123;
	t_sample m_z_146;
	t_sample m_z_148;
	t_sample m_a_151;
	t_sample m_a_176;
	t_sample m_a_177;
	t_sample m_w_178;
	t_sample m_z_173;
	t_sample m_z_171;
	t_sample m_z_172;
	t_sample m_z_170;
	t_sample m_b_179;
	t_sample m_b_181;
	t_sample __m_slide_193;
	t_sample __m_slide_197;
	t_sample m_f_180;
	t_sample m_z_187;
	t_sample samplerate;
	t_sample m_z_185;
	t_sample m_e_SIZE_112;
	t_sample m_z_168;
	t_sample m_z_166;
	t_sample m_wq_155;
	t_sample m_d_156;
	t_sample m_d_157;
	t_sample m_w_154;
	t_sample m_a_152;
	t_sample m_a_153;
	t_sample m_z_167;
	t_sample m_d_158;
	t_sample m_w_160;
	t_sample m_z_165;
	t_sample m_b_159;
	t_sample m_history_1;
	t_sample m_history_4;
	t_sample m_history_2;
	t_sample m_history_38;
	t_sample m_history_111;
	t_sample m_history_109;
	t_sample m_history_63;
	t_sample m_history_64;
	t_sample m_history_65;
	t_sample m_history_19;
	t_sample m_history_21;
	t_sample m_history_61;
	t_sample m_history_59;
	t_sample m_history_66;
	t_sample m_history_68;
	t_sample m_history_72;
	t_sample m_history_73;
	t_sample m_history_67;
	t_sample m_history_71;
	t_sample m_history_69;
	t_sample m_history_70;
	t_sample m_history_74;
	t_sample m_history_23;
	t_sample m_history_25;
	t_sample m_history_33;
	t_sample m_history_47;
	t_sample m_history_32;
	t_sample m_history_34;
	t_sample m_history_36;
	t_sample m_history_35;
	t_sample m_history_57;
	t_sample m_history_49;
	t_sample m_history_51;
	t_sample m_history_55;
	t_sample m_history_31;
	t_sample m_history_27;
	t_sample m_history_29;
	t_sample m_history_53;
	t_sample m_history_110;
	t_sample m_history_75;
	t_sample m_history_77;
	t_sample m_history_98;
	t_sample m_history_99;
	t_sample m_history_100;
	t_sample m_history_97;
	t_sample m_history_95;
	t_sample m_history_96;
	t_sample m_history_94;
	t_sample m_history_101;
	t_sample m_history_103;
	t_sample m_history_107;
	t_sample m_history_108;
	t_sample m_history_102;
	t_sample m_history_106;
	t_sample m_history_104;
	t_sample m_history_105;
	t_sample m_history_76;
	t_sample m_history_93;
	t_sample m_history_91;
	t_sample m_history_81;
	t_sample m_history_82;
	t_sample m_history_83;
	t_sample m_history_80;
	t_sample m_history_78;
	t_sample m_history_79;
	t_sample m_history_92;
	t_sample m_history_84;
	t_sample m_history_86;
	t_sample m_history_90;
	t_sample m_history_85;
	t_sample m_history_17;
	t_sample m_history_87;
	t_sample m_history_88;
	t_sample m_history_89;
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
		m_e_SIZE_112 = 1;
		m_o_PEAKFREQ_113 = 800;
		m_b_DRYWET_114 = 0.33;
		m_f_ST_115 = 0.5;
		m_s_THD_116 = -12;
		m_t_RATIO_117 = 2;
		m_w_MAKEUP_118 = 0;
		m_q_ONOFFEQ_119 = 0;
		m_n_LOWFREQ_120 = 500;
		m_p_HIFREQ_121 = 2000;
		m_h_LOWGAIN_122 = 0;
		m_i_PEAKGAIN_123 = 0;
		m_j_HIGAIN_124 = 0;
		m_k_LPF_125 = 20000;
		m_l_HPF_126 = 20;
		m_y_IOMODE_127 = 3;
		m_r_ONOFFCOMP_128 = 0;
		m_c_REFLECT_129 = 0.85;
		m_d_DAMP_130 = 0.8;
		m_z_BYPASS_131 = 1;
		m_m_OUTPUT_132 = 0;
		m_g_FREEZE_133 = 0;
		m_a_INPUT_134 = 0;
		m_u_ATK_135 = 10;
		m_v_REL_136 = 100;
		m_a_138 = ((int)0);
		m_a_139 = ((int)0);
		m_w_140 = ((int)0);
		m_b_141 = ((int)0);
		m_f_142 = ((int)0);
		m_b_143 = ((int)0);
		__m_change_144.reset(0);
		__m_change_145.reset(0);
		m_z_146 = ((int)0);
		m_z_148 = ((int)0);
		m_a_151 = ((int)0);
		m_a_152 = ((int)0);
		m_a_153 = ((int)0);
		m_w_154 = ((int)0);
		m_wq_155 = ((int)0);
		m_d_156 = ((int)0);
		m_d_157 = ((int)0);
		m_d_158 = ((int)0);
		m_b_159 = ((int)0);
		m_w_160 = ((int)0);
		__m_change_161.reset(0);
		__m_change_162.reset(0);
		__m_change_163.reset(0);
		m_z_165 = ((int)0);
		m_z_166 = ((int)0);
		m_z_167 = ((int)0);
		m_z_168 = ((int)0);
		m_z_170 = ((int)0);
		m_z_171 = ((int)0);
		m_z_172 = ((int)0);
		m_z_173 = ((int)0);
		m_a_176 = ((int)0);
		m_a_177 = ((int)0);
		m_w_178 = ((int)0);
		m_b_179 = ((int)0);
		m_f_180 = ((int)0);
		m_b_181 = ((int)0);
		__m_change_182.reset(0);
		__m_change_183.reset(0);
		m_z_185 = ((int)0);
		m_z_187 = ((int)0);
		__m_slide_193 = 0;
		__m_slide_197 = 0;
		__m_dcblock_200.reset();
		__m_dcblock_201.reset();
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
		t_sample bP_17359 = m_z_BYPASS_131;
		t_sample rsub_13763 = (((int)1) - m_z_BYPASS_131);
		t_sample mul_13447 = (rsub_13763 * ((t_sample)0.001));
		t_sample mul_4697 = (m_b_DRYWET_114 * ((t_sample)0.001));
		int eq_4721 = (m_g_FREEZE_133 == ((int)1));
		int toSize_4640 = eq_4721;
		t_sample mul_4559 = (toSize_4640 * ((t_sample)0.001));
		t_sample mul_4565 = (m_m_OUTPUT_132 * ((t_sample)0.001));
		t_sample mul_4225 = (m_r_ONOFFCOMP_128 * ((t_sample)0.001));
		t_sample mul_4219 = (m_s_THD_116 * ((t_sample)0.001));
		t_sample mul_4213 = (m_t_RATIO_117 * ((t_sample)0.001));
		t_sample mul_4207 = (m_u_ATK_135 * ((t_sample)0.001));
		t_sample mul_4201 = (m_v_REL_136 * ((t_sample)0.001));
		t_sample mul_4193 = (m_w_MAKEUP_118 * ((t_sample)0.001));
		t_sample mul_4691 = (m_a_INPUT_134 * ((t_sample)0.001));
		t_sample mul_4393 = (m_q_ONOFFEQ_119 * ((t_sample)0.001));
		t_sample mul_4703 = (m_f_ST_115 * ((t_sample)0.001));
		t_sample mul_4413 = (m_n_LOWFREQ_120 * ((t_sample)0.001));
		t_sample mul_4407 = (m_o_PEAKFREQ_113 * ((t_sample)0.001));
		t_sample mul_4401 = (m_p_HIFREQ_121 * ((t_sample)0.001));
		t_sample mul_4585 = (m_h_LOWGAIN_122 * ((t_sample)0.001));
		t_sample mul_4579 = (m_i_PEAKGAIN_123 * ((t_sample)0.001));
		t_sample mul_4573 = (m_j_HIGAIN_124 * ((t_sample)0.001));
		t_sample damp_4710 = m_d_DAMP_130;
		t_sample damp_4711 = damp_4710;
		t_sample mul_4423 = (m_e_SIZE_112 * ((t_sample)0.001));
		t_sample mul_4597 = (m_k_LPF_125 * ((t_sample)0.001));
		t_sample mul_4591 = (m_l_HPF_126 * ((t_sample)0.001));
		int toSize_4714 = toSize_4640;
		t_sample rsub_4716 = (((int)1) - m_c_REFLECT_129);
		int choice_137 = toSize_4714;
		t_sample gate_4715 = ((choice_137 >= 1) ? rsub_4716 : 0);
		t_sample add_4717 = (m_c_REFLECT_129 + gate_4715);
		t_sample mul_4658 = (add_4717 * ((t_sample)0.001));
		int rsub_4720 = (((int)1) - eq_4721);
		t_sample mul_4652 = (rsub_4720 * ((t_sample)0.001));
		t_sample rsub_4969 = (((int)1) - damp_4711);
		t_sample div_4958 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_5055 = (((int)1) - rsub_4969);
		t_sample rsub_5043 = (((int)1) - rsub_4969);
		t_sample rsub_5031 = (((int)1) - rsub_4969);
		t_sample rsub_5019 = (((int)1) - rsub_4969);
		t_sample rsub_5007 = (((int)1) - rsub_4969);
		t_sample rsub_4995 = (((int)1) - rsub_4969);
		t_sample rsub_4983 = (((int)1) - rsub_4969);
		t_sample rsub_4971 = (((int)1) - rsub_4969);
		t_sample div_4536 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4522 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4508 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4494 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_4796 = (((int)1) - damp_4710);
		t_sample div_4785 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_4882 = (((int)1) - rsub_4796);
		t_sample rsub_4870 = (((int)1) - rsub_4796);
		t_sample rsub_4858 = (((int)1) - rsub_4796);
		t_sample rsub_4846 = (((int)1) - rsub_4796);
		t_sample rsub_4834 = (((int)1) - rsub_4796);
		t_sample rsub_4822 = (((int)1) - rsub_4796);
		t_sample rsub_4810 = (((int)1) - rsub_4796);
		t_sample rsub_4798 = (((int)1) - rsub_4796);
		t_sample div_4476 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4462 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4448 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4434 = (samplerate * ((t_sample)2.2675736961451e-05));
		int maxb_192 = (-96);
		int maxb_196 = (-96);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_13448 = (m_history_111 * ((t_sample)0.999));
			t_sample add_13450 = (mul_13447 + mul_13448);
			t_sample gen_13452 = add_13450;
			t_sample history_13449_next_13451 = fixdenorm(add_13450);
			t_sample dryR_13082 = in2;
			t_sample dryL_16421 = in1;
			t_sample mul_4698 = (m_history_110 * ((t_sample)0.999));
			t_sample add_4700 = (mul_4697 + mul_4698);
			t_sample gen_4702 = add_4700;
			t_sample history_4699_next_4701 = fixdenorm(add_4700);
			t_sample dry_wet_4679 = gen_4702;
			t_sample mul_4554 = (m_history_109 * ((t_sample)0.999));
			t_sample mul_4553 = (dry_wet_4679 * ((t_sample)0.001));
			t_sample add_4556 = (mul_4553 + mul_4554);
			t_sample gen_4558 = add_4556;
			t_sample history_4555_next_4557 = fixdenorm(add_4556);
			t_sample mul_4560 = (m_history_108 * ((t_sample)0.999));
			t_sample add_4562 = (mul_4559 + mul_4560);
			t_sample gen_4564 = add_4562;
			t_sample history_4561_next_4563 = fixdenorm(add_4562);
			t_sample mul_4566 = (m_history_107 * ((t_sample)0.999));
			t_sample add_4568 = (mul_4565 + mul_4566);
			t_sample gen_4570 = add_4568;
			t_sample history_4567_next_4569 = fixdenorm(add_4568);
			t_sample dbtoa_11818 = dbtoa(gen_4570);
			t_sample mul_4226 = (m_history_106 * ((t_sample)0.999));
			t_sample add_4228 = (mul_4225 + mul_4226);
			t_sample gen_4230 = add_4228;
			t_sample history_4227_next_4229 = fixdenorm(add_4228);
			t_sample mul_4220 = (m_history_105 * ((t_sample)0.999));
			t_sample add_4222 = (mul_4219 + mul_4220);
			t_sample gen_4224 = add_4222;
			t_sample history_4221_next_4223 = fixdenorm(add_4222);
			t_sample thdC_4191 = gen_4224;
			t_sample mul_4214 = (m_history_104 * ((t_sample)0.999));
			t_sample add_4216 = (mul_4213 + mul_4214);
			t_sample gen_4218 = add_4216;
			t_sample history_4215_next_4217 = fixdenorm(add_4216);
			t_sample mul_4208 = (m_history_103 * ((t_sample)0.999));
			t_sample add_4210 = (mul_4207 + mul_4208);
			t_sample gen_4212 = add_4210;
			t_sample history_4209_next_4211 = fixdenorm(add_4210);
			t_sample mul_4202 = (m_history_102 * ((t_sample)0.999));
			t_sample add_4204 = (mul_4201 + mul_4202);
			t_sample gen_4206 = add_4204;
			t_sample history_4203_next_4205 = fixdenorm(add_4204);
			t_sample mul_4194 = (m_history_101 * ((t_sample)0.999));
			t_sample add_4196 = (mul_4193 + mul_4194);
			t_sample gen_4198 = add_4196;
			t_sample history_4195_next_4197 = fixdenorm(add_4196);
			t_sample mul_4692 = (m_history_100 * ((t_sample)0.999));
			t_sample add_4694 = (mul_4691 + mul_4692);
			t_sample gen_4696 = add_4694;
			t_sample history_4693_next_4695 = fixdenorm(add_4694);
			t_sample dbtoa_5485 = dbtoa(gen_4696);
			t_sample input_4622 = dbtoa_5485;
			t_sample mul_4623 = (in1 * input_4622);
			t_sample left_4677 = mul_4623;
			t_sample left_15794 = left_4677;
			t_sample mix_17596 = (left_15794 + (bP_17359 * (dryL_16421 - left_15794)));
			t_sample fixdenorm_16024 = fixdenorm(mix_17596);
			t_sample out3 = fixdenorm_16024;
			t_sample mix_17597 = (left_4677 + (gen_4564 * (((int)0) - left_4677)));
			t_sample mul_4621 = (in2 * input_4622);
			t_sample right_4676 = mul_4621;
			t_sample right_15909 = right_4676;
			t_sample mix_17598 = (right_15909 + (bP_17359 * (dryR_13082 - right_15909)));
			t_sample fixdenorm_16139 = fixdenorm(mix_17598);
			t_sample out4 = fixdenorm_16139;
			t_sample mix_17599 = (right_4676 + (gen_4564 * (((int)0) - right_4676)));
			t_sample mul_4394 = (m_history_99 * ((t_sample)0.999));
			t_sample add_4396 = (mul_4393 + mul_4394);
			t_sample gen_4398 = add_4396;
			t_sample history_4395_next_4397 = fixdenorm(add_4396);
			t_sample onOffEQ_4392 = gen_4398;
			t_sample mul_4704 = (m_history_98 * ((t_sample)0.999));
			t_sample add_4706 = (mul_4703 + mul_4704);
			t_sample gen_4708 = add_4706;
			t_sample history_4705_next_4707 = fixdenorm(add_4706);
			t_sample sub_17603 = (gen_4708 - ((int)0));
			t_sample scale_17600 = ((safepow((sub_17603 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_4674 = scale_17600;
			t_sample mul_4414 = (m_history_97 * ((t_sample)0.999));
			t_sample add_4416 = (mul_4413 + mul_4414);
			t_sample gen_4418 = add_4416;
			t_sample history_4415_next_4417 = fixdenorm(add_4416);
			t_sample mul_4408 = (m_history_96 * ((t_sample)0.999));
			t_sample add_4410 = (mul_4407 + mul_4408);
			t_sample gen_4412 = add_4410;
			t_sample history_4409_next_4411 = fixdenorm(add_4410);
			t_sample mul_4402 = (m_history_95 * ((t_sample)0.999));
			t_sample add_4404 = (mul_4401 + mul_4402);
			t_sample gen_4406 = add_4404;
			t_sample history_4403_next_4405 = fixdenorm(add_4404);
			t_sample mul_4586 = (m_history_94 * ((t_sample)0.999));
			t_sample add_4588 = (mul_4585 + mul_4586);
			t_sample gen_4590 = add_4588;
			t_sample history_4587_next_4589 = fixdenorm(add_4588);
			t_sample mul_4580 = (m_history_93 * ((t_sample)0.999));
			t_sample add_4582 = (mul_4579 + mul_4580);
			t_sample gen_4584 = add_4582;
			t_sample history_4581_next_4583 = fixdenorm(add_4582);
			t_sample mul_4574 = (m_history_92 * ((t_sample)0.999));
			t_sample add_4576 = (mul_4573 + mul_4574);
			t_sample gen_4578 = add_4576;
			t_sample history_4575_next_4577 = fixdenorm(add_4576);
			t_sample sqrt_4683 = sqrt(gen_4708);
			t_sample rsub_4709 = (((int)1) - gen_4708);
			t_sample sqrt_4684 = sqrt(rsub_4709);
			t_sample mul_4424 = (m_history_91 * ((t_sample)0.999));
			t_sample add_4426 = (mul_4423 + mul_4424);
			t_sample gen_4428 = add_4426;
			t_sample history_4425_next_4427 = fixdenorm(add_4426);
			t_sample escala_Size_14015 = gen_4428;
			t_sample escala_Size_4550 = escala_Size_14015;
			t_sample escala_Size_4490 = escala_Size_14015;
			t_sample escala_Size_4552 = escala_Size_14015;
			t_sample escala_Size_4551 = escala_Size_14015;
			t_sample mul_14013 = (((int)23) * escala_Size_14015);
			t_sample mul_4598 = (m_history_90 * ((t_sample)0.999));
			t_sample add_4600 = (mul_4597 + mul_4598);
			t_sample gen_4602 = add_4600;
			t_sample history_4599_next_4601 = fixdenorm(add_4600);
			t_sample mul_4592 = (m_history_89 * ((t_sample)0.999));
			t_sample add_4594 = (mul_4591 + mul_4592);
			t_sample gen_4596 = add_4594;
			t_sample history_4593_next_4595 = fixdenorm(add_4594);
			t_sample mul_4659 = (m_history_88 * ((t_sample)0.999));
			t_sample add_4661 = (mul_4658 + mul_4659);
			t_sample gen_4663 = add_4661;
			t_sample history_4660_next_4662 = fixdenorm(add_4661);
			t_sample left_4671 = left_4677;
			t_sample right_4670 = right_4676;
			t_sample mul_4653 = (m_history_87 * ((t_sample)0.999));
			t_sample add_4655 = (mul_4652 + mul_4653);
			t_sample gen_4657 = add_4655;
			t_sample history_4654_next_4656 = fixdenorm(add_4655);
			t_sample freeze_4689 = gen_4657;
			t_sample mul_4690 = (right_4670 * freeze_4689);
			t_sample toFILTERS_c45R_4297 = mul_4690;
			t_sample freeze_4718 = freeze_4689;
			t_sample mul_4719 = (left_4671 * freeze_4718);
			t_sample toFILTERS_c45L_4298 = mul_4719;
			t_sample omega = safediv((gen_4602 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((int)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) - cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((((int)1) - cs) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_4376 = a2;
			t_sample expr_4377 = a1;
			t_sample expr_4378 = a2;
			t_sample expr_4379 = b1;
			t_sample expr_4380 = b2;
			t_sample omega_4384 = safediv((gen_4596 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_4381 = sin(omega_4384);
			t_sample cs_4389 = cos(omega_4384);
			t_sample alpha_4383 = ((sn_4381 * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b_4387 = safediv(((int)1), (((int)1) + alpha_4383));
			t_sample a_4388 = (((((int)1) + cs_4389) * ((t_sample)0.5)) * b_4387);
			t_sample a_4386 = ((-(((int)1) + cs_4389)) * b_4387);
			t_sample b_4385 = ((((int)-2) * cs_4389) * b_4387);
			t_sample b_4382 = ((((int)1) - alpha_4383) * b_4387);
			t_sample expr_4371 = a_4388;
			t_sample expr_4372 = a_4386;
			t_sample expr_4373 = a_4388;
			t_sample expr_4374 = b_4385;
			t_sample expr_4375 = b_4382;
			t_sample mul_4350 = (toFILTERS_c45R_4297 * expr_4376);
			t_sample mul_4360 = (toFILTERS_c45L_4298 * expr_4376);
			t_sample mul_4347 = (m_history_82 * expr_4377);
			t_sample mul_4357 = (m_history_81 * expr_4377);
			t_sample mul_4345 = (m_history_85 * expr_4378);
			t_sample mul_4355 = (m_history_84 * expr_4378);
			t_sample mul_4343 = (m_history_80 * expr_4379);
			t_sample mul_4353 = (m_history_79 * expr_4379);
			t_sample mul_4341 = (m_history_83 * expr_4380);
			t_sample sub_4349 = (((mul_4345 + mul_4347) + mul_4350) - (mul_4341 + mul_4343));
			t_sample gen_4370 = sub_4349;
			t_sample mul_4351 = (m_history_86 * expr_4380);
			t_sample sub_4359 = (((mul_4360 + mul_4357) + mul_4355) - (mul_4351 + mul_4353));
			t_sample gen_4369 = sub_4359;
			t_sample history_4352_next_4361 = fixdenorm(m_history_79);
			t_sample history_4346_next_4362 = fixdenorm(m_history_82);
			t_sample history_4356_next_4363 = fixdenorm(m_history_81);
			t_sample history_4342_next_4364 = fixdenorm(m_history_80);
			t_sample history_4348_next_4365 = fixdenorm(toFILTERS_c45R_4297);
			t_sample history_4358_next_4366 = fixdenorm(toFILTERS_c45L_4298);
			t_sample history_4344_next_4367 = fixdenorm(sub_4349);
			t_sample history_4354_next_4368 = fixdenorm(sub_4359);
			t_sample mul_4315 = (gen_4370 * expr_4371);
			t_sample mul_4325 = (gen_4369 * expr_4371);
			t_sample mul_4312 = (m_history_73 * expr_4372);
			t_sample mul_4322 = (m_history_74 * expr_4372);
			t_sample mul_4310 = (m_history_77 * expr_4373);
			t_sample mul_4320 = (m_history_75 * expr_4373);
			t_sample mul_4308 = (m_history_72 * expr_4374);
			t_sample mul_4318 = (m_history_71 * expr_4374);
			t_sample mul_4306 = (m_history_76 * expr_4375);
			t_sample sub_4314 = (((mul_4310 + mul_4312) + mul_4315) - (mul_4306 + mul_4308));
			t_sample gen_4335 = sub_4314;
			t_sample mul_4316 = (m_history_78 * expr_4375);
			t_sample sub_4324 = (((mul_4325 + mul_4322) + mul_4320) - (mul_4316 + mul_4318));
			t_sample gen_4334 = sub_4324;
			t_sample history_4317_next_4326 = fixdenorm(m_history_71);
			t_sample history_4311_next_4327 = fixdenorm(m_history_73);
			t_sample history_4307_next_4328 = fixdenorm(m_history_72);
			t_sample history_4321_next_4329 = fixdenorm(m_history_74);
			t_sample history_4323_next_4330 = fixdenorm(gen_4369);
			t_sample history_4313_next_4331 = fixdenorm(gen_4370);
			t_sample history_4309_next_4332 = fixdenorm(sub_4314);
			t_sample history_4319_next_4333 = fixdenorm(sub_4324);
			t_sample gen_4391 = gen_4335;
			t_sample gen_4390 = gen_4334;
			t_sample fromFILTERS_c45L_4300 = gen_4390;
			t_sample mul_4943 = (div_4958 * escala_Size_4552);
			t_sample mul_4954 = (((int)1491) * mul_4943);
			t_sample mul_4926 = (m_history_70 * ((t_sample)0.999));
			t_sample mul_4925 = (mul_4954 * ((t_sample)0.001));
			t_sample add_4928 = (mul_4925 + mul_4926);
			t_sample gen_4930 = add_4928;
			t_sample history_4927_next_4929 = fixdenorm(add_4928);
			t_sample gen_4963 = gen_4930;
			t_sample mul_4946 = (((int)1188) * mul_4943);
			t_sample mul_4902 = (m_history_69 * ((t_sample)0.999));
			t_sample mul_4901 = (mul_4946 * ((t_sample)0.001));
			t_sample add_4904 = (mul_4901 + mul_4902);
			t_sample gen_4906 = add_4904;
			t_sample history_4903_next_4905 = fixdenorm(add_4904);
			t_sample gen_4967 = gen_4906;
			t_sample mul_4950 = (((int)1277) * mul_4943);
			t_sample mul_4914 = (m_history_68 * ((t_sample)0.999));
			t_sample mul_4913 = (mul_4950 * ((t_sample)0.001));
			t_sample add_4916 = (mul_4913 + mul_4914);
			t_sample gen_4918 = add_4916;
			t_sample history_4915_next_4917 = fixdenorm(add_4916);
			t_sample gen_4965 = gen_4918;
			t_sample mul_4948 = (((int)1356) * mul_4943);
			t_sample mul_4908 = (m_history_67 * ((t_sample)0.999));
			t_sample mul_4907 = (mul_4948 * ((t_sample)0.001));
			t_sample add_4910 = (mul_4907 + mul_4908);
			t_sample gen_4912 = add_4910;
			t_sample history_4909_next_4911 = fixdenorm(add_4910);
			t_sample gen_4966 = gen_4912;
			t_sample mul_4952 = (((int)1422) * mul_4943);
			t_sample mul_4920 = (m_history_66 * ((t_sample)0.999));
			t_sample mul_4919 = (mul_4952 * ((t_sample)0.001));
			t_sample add_4922 = (mul_4919 + mul_4920);
			t_sample gen_4924 = add_4922;
			t_sample history_4921_next_4923 = fixdenorm(add_4922);
			t_sample gen_4964 = gen_4924;
			t_sample mul_4944 = (((int)1116) * mul_4943);
			t_sample mul_4896 = (m_history_65 * ((t_sample)0.999));
			t_sample mul_4895 = (mul_4944 * ((t_sample)0.001));
			t_sample add_4898 = (mul_4895 + mul_4896);
			t_sample gen_4900 = add_4898;
			t_sample history_4897_next_4899 = fixdenorm(add_4898);
			t_sample gen_4968 = gen_4900;
			t_sample mul_4959 = (((int)1557) * mul_4943);
			t_sample mul_4938 = (m_history_64 * ((t_sample)0.999));
			t_sample mul_4937 = (mul_4959 * ((t_sample)0.001));
			t_sample add_4940 = (mul_4937 + mul_4938);
			t_sample gen_4942 = add_4940;
			t_sample history_4939_next_4941 = fixdenorm(add_4940);
			t_sample gen_4961 = gen_4942;
			t_sample mul_4956 = (((int)1617) * mul_4943);
			t_sample mul_4932 = (m_history_63 * ((t_sample)0.999));
			t_sample mul_4931 = (mul_4956 * ((t_sample)0.001));
			t_sample add_4934 = (mul_4931 + mul_4932);
			t_sample gen_4936 = add_4934;
			t_sample history_4933_next_4935 = fixdenorm(add_4934);
			t_sample gen_4962 = gen_4936;
			t_sample mul_5057 = (m_history_61 * rsub_5055);
			t_sample add_5054 = (((int)0) + gen_4961);
			t_sample tap_5063 = m_delay_62.read_linear(add_5054);
			t_sample mul_5060 = (tap_5063 * rsub_4969);
			t_sample add_5059 = (mul_5060 + mul_5057);
			t_sample mul_5056 = (add_5059 * gen_4663);
			t_sample add_5061 = (fromFILTERS_c45L_4300 + mul_5056);
			t_sample gen_5065 = add_5061;
			t_sample history_5058_next_5064 = fixdenorm(add_5059);
			t_sample mul_5045 = (m_history_59 * rsub_5043);
			t_sample add_5042 = (((int)0) + gen_4962);
			t_sample tap_5051 = m_delay_60.read_linear(add_5042);
			t_sample mul_5048 = (tap_5051 * rsub_4969);
			t_sample add_5047 = (mul_5048 + mul_5045);
			t_sample mul_5044 = (add_5047 * gen_4663);
			t_sample add_5049 = (fromFILTERS_c45L_4300 + mul_5044);
			t_sample gen_5053 = add_5049;
			t_sample history_5046_next_5052 = fixdenorm(add_5047);
			t_sample mul_5033 = (m_history_57 * rsub_5031);
			t_sample add_5030 = (((int)0) + gen_4963);
			t_sample tap_5039 = m_delay_58.read_linear(add_5030);
			t_sample mul_5036 = (tap_5039 * rsub_4969);
			t_sample add_5035 = (mul_5036 + mul_5033);
			t_sample mul_5032 = (add_5035 * gen_4663);
			t_sample add_5037 = (fromFILTERS_c45L_4300 + mul_5032);
			t_sample gen_5041 = add_5037;
			t_sample history_5034_next_5040 = fixdenorm(add_5035);
			t_sample mul_5021 = (m_history_55 * rsub_5019);
			t_sample add_5018 = (((int)0) + gen_4964);
			t_sample tap_5027 = m_delay_56.read_linear(add_5018);
			t_sample mul_5024 = (tap_5027 * rsub_4969);
			t_sample add_5023 = (mul_5024 + mul_5021);
			t_sample mul_5020 = (add_5023 * gen_4663);
			t_sample add_5025 = (fromFILTERS_c45L_4300 + mul_5020);
			t_sample gen_5029 = add_5025;
			t_sample history_5022_next_5028 = fixdenorm(add_5023);
			t_sample mul_5009 = (m_history_53 * rsub_5007);
			t_sample add_5006 = (((int)0) + gen_4965);
			t_sample tap_5015 = m_delay_54.read_linear(add_5006);
			t_sample mul_5012 = (tap_5015 * rsub_4969);
			t_sample add_5011 = (mul_5012 + mul_5009);
			t_sample mul_5008 = (add_5011 * gen_4663);
			t_sample add_5013 = (fromFILTERS_c45L_4300 + mul_5008);
			t_sample gen_5017 = add_5013;
			t_sample history_5010_next_5016 = fixdenorm(add_5011);
			t_sample mul_4997 = (m_history_51 * rsub_4995);
			t_sample add_4994 = (((int)0) + gen_4966);
			t_sample tap_5003 = m_delay_52.read_linear(add_4994);
			t_sample mul_5000 = (tap_5003 * rsub_4969);
			t_sample add_4999 = (mul_5000 + mul_4997);
			t_sample mul_4996 = (add_4999 * gen_4663);
			t_sample add_5001 = (fromFILTERS_c45L_4300 + mul_4996);
			t_sample gen_5005 = add_5001;
			t_sample history_4998_next_5004 = fixdenorm(add_4999);
			t_sample mul_4985 = (m_history_49 * rsub_4983);
			t_sample add_4982 = (((int)0) + gen_4967);
			t_sample tap_4991 = m_delay_50.read_linear(add_4982);
			t_sample mul_4988 = (tap_4991 * rsub_4969);
			t_sample add_4987 = (mul_4988 + mul_4985);
			t_sample mul_4984 = (add_4987 * gen_4663);
			t_sample add_4989 = (fromFILTERS_c45L_4300 + mul_4984);
			t_sample gen_4993 = add_4989;
			t_sample history_4986_next_4992 = fixdenorm(add_4987);
			t_sample mul_4973 = (m_history_47 * rsub_4971);
			t_sample add_4970 = (((int)0) + gen_4968);
			t_sample tap_4979 = m_delay_48.read_linear(add_4970);
			t_sample mul_4976 = (tap_4979 * rsub_4969);
			t_sample add_4975 = (mul_4976 + mul_4973);
			t_sample mul_4972 = (add_4975 * gen_4663);
			t_sample add_4977 = (fromFILTERS_c45L_4300 + mul_4972);
			t_sample gen_4981 = add_4977;
			t_sample history_4974_next_4980 = fixdenorm(add_4975);
			t_sample mul_5066 = ((((((((gen_4981 + gen_4993) + gen_5005) + gen_5017) + gen_5029) + gen_5041) + gen_5053) + gen_5065) * ((t_sample)0.125));
			t_sample gen_5067 = mul_5066;
			t_sample mul_4545 = (gen_5067 * ((t_sample)-0.5));
			t_sample mul_4535 = (div_4536 * escala_Size_4550);
			t_sample mul_4537 = (((int)255) * mul_4535);
			t_sample add_4539 = (((int)0) + mul_4537);
			t_sample tap_4547 = m_delay_46.read_linear(add_4539);
			t_sample tap_4542 = m_delay_45.read_linear(add_4539);
			t_sample mul_4540 = (tap_4542 * ((t_sample)0.5));
			t_sample add_4543 = (mul_4545 + (mul_4540 + tap_4547));
			t_sample gen_4548 = add_4543;
			t_sample mul_4531 = (gen_4548 * ((t_sample)-0.5));
			t_sample mul_4521 = (div_4522 * escala_Size_4550);
			t_sample mul_4523 = (((int)556) * mul_4521);
			t_sample add_4525 = (((int)0) + mul_4523);
			t_sample tap_4533 = m_delay_44.read_linear(add_4525);
			t_sample tap_4528 = m_delay_43.read_linear(add_4525);
			t_sample mul_4526 = (tap_4528 * ((t_sample)0.5));
			t_sample add_4529 = (mul_4531 + (mul_4526 + tap_4533));
			t_sample gen_4534 = add_4529;
			t_sample mul_4517 = (gen_4534 * ((t_sample)-0.5));
			t_sample mul_4507 = (div_4508 * escala_Size_4550);
			t_sample mul_4509 = (((int)441) * mul_4507);
			t_sample add_4511 = (((int)0) + mul_4509);
			t_sample tap_4519 = m_delay_42.read_linear(add_4511);
			t_sample tap_4514 = m_delay_41.read_linear(add_4511);
			t_sample mul_4512 = (tap_4514 * ((t_sample)0.5));
			t_sample add_4515 = (mul_4517 + (mul_4512 + tap_4519));
			t_sample gen_4520 = add_4515;
			t_sample mul_4503 = (gen_4520 * ((t_sample)-0.5));
			t_sample mul_4493 = (div_4494 * escala_Size_4550);
			t_sample mul_4495 = (((int)341) * mul_4493);
			t_sample add_4497 = (((int)0) + mul_4495);
			t_sample tap_4505 = m_delay_40.read_linear(add_4497);
			t_sample tap_4500 = m_delay_39.read_linear(add_4497);
			t_sample mul_4498 = (tap_4500 * ((t_sample)0.5));
			t_sample add_4501 = (mul_4503 + (mul_4498 + tap_4505));
			t_sample gen_4506 = add_4501;
			t_sample gen_4549 = gen_4506;
			t_sample matrizMS_c45L_4669 = gen_4549;
			t_sample fromFILTERS_c45R_4299 = gen_4391;
			t_sample mul_4770 = (div_4785 * escala_Size_4551);
			t_sample mul_4773 = (((int)1188) * mul_4770);
			t_sample mul_4729 = (m_history_38 * ((t_sample)0.999));
			t_sample mul_4728 = (mul_4773 * ((t_sample)0.001));
			t_sample add_4731 = (mul_4728 + mul_4729);
			t_sample gen_4733 = add_4731;
			t_sample history_4730_next_4732 = fixdenorm(add_4731);
			t_sample gen_4794 = gen_4733;
			t_sample mul_4786 = (((int)1557) * mul_4770);
			t_sample mul_4765 = (m_history_37 * ((t_sample)0.999));
			t_sample mul_4764 = (mul_4786 * ((t_sample)0.001));
			t_sample add_4767 = (mul_4764 + mul_4765);
			t_sample gen_4769 = add_4767;
			t_sample history_4766_next_4768 = fixdenorm(add_4767);
			t_sample gen_4788 = gen_4769;
			t_sample mul_4781 = (((int)1491) * mul_4770);
			t_sample mul_4753 = (m_history_36 * ((t_sample)0.999));
			t_sample mul_4752 = (mul_4781 * ((t_sample)0.001));
			t_sample add_4755 = (mul_4752 + mul_4753);
			t_sample gen_4757 = add_4755;
			t_sample history_4754_next_4756 = fixdenorm(add_4755);
			t_sample gen_4790 = gen_4757;
			t_sample mul_4783 = (((int)1617) * mul_4770);
			t_sample mul_4759 = (m_history_35 * ((t_sample)0.999));
			t_sample mul_4758 = (mul_4783 * ((t_sample)0.001));
			t_sample add_4761 = (mul_4758 + mul_4759);
			t_sample gen_4763 = add_4761;
			t_sample history_4760_next_4762 = fixdenorm(add_4761);
			t_sample gen_4789 = gen_4763;
			t_sample mul_4775 = (((int)1356) * mul_4770);
			t_sample mul_4735 = (m_history_34 * ((t_sample)0.999));
			t_sample mul_4734 = (mul_4775 * ((t_sample)0.001));
			t_sample add_4737 = (mul_4734 + mul_4735);
			t_sample gen_4739 = add_4737;
			t_sample history_4736_next_4738 = fixdenorm(add_4737);
			t_sample gen_4793 = gen_4739;
			t_sample mul_4771 = (((int)1116) * mul_4770);
			t_sample mul_4723 = (m_history_33 * ((t_sample)0.999));
			t_sample mul_4722 = (mul_4771 * ((t_sample)0.001));
			t_sample add_4725 = (mul_4722 + mul_4723);
			t_sample gen_4727 = add_4725;
			t_sample history_4724_next_4726 = fixdenorm(add_4725);
			t_sample gen_4795 = gen_4727;
			t_sample mul_4777 = (((int)1277) * mul_4770);
			t_sample mul_4741 = (m_history_32 * ((t_sample)0.999));
			t_sample mul_4740 = (mul_4777 * ((t_sample)0.001));
			t_sample add_4743 = (mul_4740 + mul_4741);
			t_sample gen_4745 = add_4743;
			t_sample history_4742_next_4744 = fixdenorm(add_4743);
			t_sample gen_4792 = gen_4745;
			t_sample mul_4779 = (((int)1422) * mul_4770);
			t_sample mul_4747 = (m_history_31 * ((t_sample)0.999));
			t_sample mul_4746 = (mul_4779 * ((t_sample)0.001));
			t_sample add_4749 = (mul_4746 + mul_4747);
			t_sample gen_4751 = add_4749;
			t_sample history_4748_next_4750 = fixdenorm(add_4749);
			t_sample gen_4791 = gen_4751;
			t_sample mul_4884 = (m_history_29 * rsub_4882);
			t_sample add_4881 = (mul_14013 + gen_4788);
			t_sample tap_4890 = m_delay_30.read_linear(add_4881);
			t_sample mul_4887 = (tap_4890 * rsub_4796);
			t_sample add_4886 = (mul_4887 + mul_4884);
			t_sample mul_4883 = (add_4886 * gen_4663);
			t_sample add_4888 = (fromFILTERS_c45R_4299 + mul_4883);
			t_sample gen_4892 = add_4888;
			t_sample history_4885_next_4891 = fixdenorm(add_4886);
			t_sample mul_4872 = (m_history_27 * rsub_4870);
			t_sample add_4869 = (mul_14013 + gen_4789);
			t_sample tap_4878 = m_delay_28.read_linear(add_4869);
			t_sample mul_4875 = (tap_4878 * rsub_4796);
			t_sample add_4874 = (mul_4875 + mul_4872);
			t_sample mul_4871 = (add_4874 * gen_4663);
			t_sample add_4876 = (fromFILTERS_c45R_4299 + mul_4871);
			t_sample gen_4880 = add_4876;
			t_sample history_4873_next_4879 = fixdenorm(add_4874);
			t_sample mul_4860 = (m_history_25 * rsub_4858);
			t_sample add_4857 = (mul_14013 + gen_4790);
			t_sample tap_4866 = m_delay_26.read_linear(add_4857);
			t_sample mul_4863 = (tap_4866 * rsub_4796);
			t_sample add_4862 = (mul_4863 + mul_4860);
			t_sample mul_4859 = (add_4862 * gen_4663);
			t_sample add_4864 = (fromFILTERS_c45R_4299 + mul_4859);
			t_sample gen_4868 = add_4864;
			t_sample history_4861_next_4867 = fixdenorm(add_4862);
			t_sample mul_4848 = (m_history_23 * rsub_4846);
			t_sample add_4845 = (mul_14013 + gen_4791);
			t_sample tap_4854 = m_delay_24.read_linear(add_4845);
			t_sample mul_4851 = (tap_4854 * rsub_4796);
			t_sample add_4850 = (mul_4851 + mul_4848);
			t_sample mul_4847 = (add_4850 * gen_4663);
			t_sample add_4852 = (fromFILTERS_c45R_4299 + mul_4847);
			t_sample gen_4856 = add_4852;
			t_sample history_4849_next_4855 = fixdenorm(add_4850);
			t_sample mul_4836 = (m_history_21 * rsub_4834);
			t_sample add_4833 = (mul_14013 + gen_4792);
			t_sample tap_4842 = m_delay_22.read_linear(add_4833);
			t_sample mul_4839 = (tap_4842 * rsub_4796);
			t_sample add_4838 = (mul_4839 + mul_4836);
			t_sample mul_4835 = (add_4838 * gen_4663);
			t_sample add_4840 = (fromFILTERS_c45R_4299 + mul_4835);
			t_sample gen_4844 = add_4840;
			t_sample history_4837_next_4843 = fixdenorm(add_4838);
			t_sample mul_4824 = (m_history_19 * rsub_4822);
			t_sample add_4821 = (mul_14013 + gen_4793);
			t_sample tap_4830 = m_delay_20.read_linear(add_4821);
			t_sample mul_4827 = (tap_4830 * rsub_4796);
			t_sample add_4826 = (mul_4827 + mul_4824);
			t_sample mul_4823 = (add_4826 * gen_4663);
			t_sample add_4828 = (fromFILTERS_c45R_4299 + mul_4823);
			t_sample gen_4832 = add_4828;
			t_sample history_4825_next_4831 = fixdenorm(add_4826);
			t_sample mul_4812 = (m_history_17 * rsub_4810);
			t_sample add_4809 = (mul_14013 + gen_4794);
			t_sample tap_4818 = m_delay_18.read_linear(add_4809);
			t_sample mul_4815 = (tap_4818 * rsub_4796);
			t_sample add_4814 = (mul_4815 + mul_4812);
			t_sample mul_4811 = (add_4814 * gen_4663);
			t_sample add_4816 = (fromFILTERS_c45R_4299 + mul_4811);
			t_sample gen_4820 = add_4816;
			t_sample history_4813_next_4819 = fixdenorm(add_4814);
			t_sample mul_4800 = (m_history_15 * rsub_4798);
			t_sample add_4797 = (mul_14013 + gen_4795);
			t_sample tap_4806 = m_delay_16.read_linear(add_4797);
			t_sample mul_4803 = (tap_4806 * rsub_4796);
			t_sample add_4802 = (mul_4803 + mul_4800);
			t_sample mul_4799 = (add_4802 * gen_4663);
			t_sample add_4804 = (fromFILTERS_c45R_4299 + mul_4799);
			t_sample gen_4808 = add_4804;
			t_sample history_4801_next_4807 = fixdenorm(add_4802);
			t_sample mul_4893 = ((((((((gen_4808 + gen_4820) + gen_4832) + gen_4844) + gen_4856) + gen_4868) + gen_4880) + gen_4892) * ((t_sample)0.125));
			t_sample gen_4894 = mul_4893;
			t_sample mul_4485 = (gen_4894 * ((t_sample)-0.5));
			t_sample mul_4475 = (div_4476 * escala_Size_4490);
			t_sample mul_4477 = (((int)255) * mul_4475);
			t_sample add_4479 = (((int)0) + mul_4477);
			t_sample tap_4487 = m_delay_14.read_linear(add_4479);
			t_sample tap_4482 = m_delay_13.read_linear(add_4479);
			t_sample mul_4480 = (tap_4482 * ((t_sample)0.5));
			t_sample add_4483 = (mul_4485 + (mul_4480 + tap_4487));
			t_sample gen_4488 = add_4483;
			t_sample mul_4471 = (gen_4488 * ((t_sample)-0.5));
			t_sample mul_4461 = (div_4462 * escala_Size_4490);
			t_sample mul_4463 = (((int)556) * mul_4461);
			t_sample add_4465 = (((int)0) + mul_4463);
			t_sample tap_4473 = m_delay_12.read_linear(add_4465);
			t_sample tap_4468 = m_delay_11.read_linear(add_4465);
			t_sample mul_4466 = (tap_4468 * ((t_sample)0.5));
			t_sample add_4469 = (mul_4471 + (mul_4466 + tap_4473));
			t_sample gen_4474 = add_4469;
			t_sample mul_4457 = (gen_4474 * ((t_sample)-0.5));
			t_sample mul_4447 = (div_4448 * escala_Size_4490);
			t_sample mul_4449 = (((int)441) * mul_4447);
			t_sample add_4451 = (((int)0) + mul_4449);
			t_sample tap_4459 = m_delay_10.read_linear(add_4451);
			t_sample tap_4454 = m_delay_9.read_linear(add_4451);
			t_sample mul_4452 = (tap_4454 * ((t_sample)0.5));
			t_sample add_4455 = (mul_4457 + (mul_4452 + tap_4459));
			t_sample gen_4460 = add_4455;
			t_sample mul_4443 = (gen_4460 * ((t_sample)-0.5));
			t_sample mul_4433 = (div_4434 * escala_Size_4490);
			t_sample mul_4435 = (((int)341) * mul_4433);
			t_sample add_4437 = (((int)0) + mul_4435);
			t_sample tap_4445 = m_delay_8.read_linear(add_4437);
			t_sample tap_4440 = m_delay_7.read_linear(add_4437);
			t_sample mul_4438 = (tap_4440 * ((t_sample)0.5));
			t_sample add_4441 = (mul_4443 + (mul_4438 + tap_4445));
			t_sample gen_4446 = add_4441;
			t_sample gen_4489 = gen_4446;
			t_sample matrizMS_c45R_4668 = gen_4489;
			t_sample add_4688 = (matrizMS_c45L_4669 + matrizMS_c45R_4668);
			t_sample mul_4686 = (add_4688 * sqrt_4684);
			t_sample sub_4687 = (matrizMS_c45L_4669 - matrizMS_c45R_4668);
			t_sample mul_4685 = (sub_4687 * sqrt_4683);
			t_sample add_4682 = (mul_4686 + mul_4685);
			t_sample mul_4673 = (add_4682 * scale_4674);
			t_sample filterL_4420 = mul_4673;
			t_sample sub_4681 = (mul_4686 - mul_4685);
			t_sample mul_4672 = (sub_4681 * scale_4674);
			t_sample filterR_4419 = mul_4672;
			t_sample return_190;
			t_sample return_191;
			eq3bandas_d_d_d_d_d_d_d_d_i(filterL_4420, filterR_4419, gen_4418, gen_4412, gen_4406, gen_4590, gen_4584, gen_4578, ((int)1), return_190, return_191);
			t_sample expr_4617 = return_190;
			t_sample expr_4618 = return_191;
			t_sample gen_4620 = expr_4618;
			t_sample gen_4619 = expr_4617;
			t_sample fromFilterL_4422 = gen_4619;
			t_sample mix_17604 = (mul_4673 + (onOffEQ_4392 * (fromFilterL_4422 - mul_4673)));
			t_sample mix_4400 = mix_17604;
			t_sample fromFilterR_4421 = gen_4620;
			t_sample mix_17605 = (mul_4672 + (onOffEQ_4392 * (fromFilterR_4421 - mul_4672)));
			t_sample mix_4399 = mix_17605;
			t_sample dbtoa_4231 = dbtoa(gen_4198);
			t_sample mstosamps_4268 = (gen_4206 * (samplerate * 0.001));
			t_sample mstosamps_4267 = (gen_4212 * (samplerate * 0.001));
			t_sample tap_4286 = m_delay_6.read_step(((int)300));
			t_sample mul_4279 = (mix_4400 * mix_4400);
			t_sample add_4283 = (m_history_5 + mul_4279);
			t_sample sub_4282 = (add_4283 - tap_4286);
			t_sample div_4280 = (sub_4282 * ((t_sample)0.0033333333333333));
			t_sample sqrt_4278 = sqrt(div_4280);
			t_sample gen_4288 = sqrt_4278;
			t_sample history_4281_next_4287 = fixdenorm(sub_4282);
			t_sample atodb_4277 = atodb(gen_4288);
			t_sample max_4235 = ((atodb_4277 < maxb_192) ? maxb_192 : atodb_4277);
			int gt_4276 = (max_4235 > thdC_4191);
			t_sample mul_4243 = (m_history_4 * ((t_sample)0.999));
			t_sample mul_4242 = (gt_4276 * ((t_sample)0.001));
			t_sample add_4245 = (mul_4242 + mul_4243);
			t_sample gen_4247 = add_4245;
			t_sample history_4244_next_4246 = fixdenorm(add_4245);
			t_sample sub_4275 = (thdC_4191 - max_4235);
			t_sample rdiv_4274 = safediv(((int)1), gen_4218);
			t_sample rsub_4273 = (((int)1) - rdiv_4274);
			t_sample mul_4272 = (sub_4275 * rsub_4273);
			t_sample dbtoa_4270 = dbtoa(mul_4272);
			t_sample orange_17608 = (dbtoa_4270 - ((int)1));
			t_sample sub_17609 = (gen_4247 - ((int)0));
			t_sample scale_17606 = ((safepow((sub_17609 * ((t_sample)1)), ((int)1)) * orange_17608) + ((int)1));
			t_sample iup_194 = (1 / maximum(1, abs(mstosamps_4268)));
			t_sample idown_195 = (1 / maximum(1, abs(mstosamps_4267)));
			__m_slide_193 = fixdenorm((__m_slide_193 + (((scale_17606 > __m_slide_193) ? iup_194 : idown_195) * (scale_17606 - __m_slide_193))));
			t_sample slide_4269 = __m_slide_193;
			t_sample mul_4289 = (mix_4400 * slide_4269);
			t_sample mul_4233 = (mul_4289 * dbtoa_4231);
			t_sample tap_4264 = m_delay_3.read_step(((int)300));
			t_sample mul_4257 = (mix_4399 * mix_4399);
			t_sample add_4261 = (m_history_2 + mul_4257);
			t_sample sub_4260 = (add_4261 - tap_4264);
			t_sample div_4258 = (sub_4260 * ((t_sample)0.0033333333333333));
			t_sample sqrt_4256 = sqrt(div_4258);
			t_sample gen_4266 = sqrt_4256;
			t_sample history_4259_next_4265 = fixdenorm(sub_4260);
			t_sample atodb_4255 = atodb(gen_4266);
			t_sample max_4234 = ((atodb_4255 < maxb_196) ? maxb_196 : atodb_4255);
			int gt_4254 = (max_4234 > thdC_4191);
			t_sample mul_4237 = (m_history_1 * ((t_sample)0.999));
			t_sample mul_4236 = (gt_4254 * ((t_sample)0.001));
			t_sample add_4239 = (mul_4236 + mul_4237);
			t_sample gen_4241 = add_4239;
			t_sample history_4238_next_4240 = fixdenorm(add_4239);
			t_sample sub_4253 = (thdC_4191 - max_4234);
			t_sample mul_4252 = (sub_4253 * rsub_4273);
			t_sample dbtoa_4250 = dbtoa(mul_4252);
			t_sample orange_17612 = (dbtoa_4250 - ((int)1));
			t_sample sub_17613 = (gen_4241 - ((int)0));
			t_sample scale_17610 = ((safepow((sub_17613 * ((t_sample)1)), ((int)1)) * orange_17612) + ((int)1));
			t_sample iup_198 = (1 / maximum(1, abs(mstosamps_4268)));
			t_sample idown_199 = (1 / maximum(1, abs(mstosamps_4267)));
			__m_slide_197 = fixdenorm((__m_slide_197 + (((scale_17610 > __m_slide_197) ? iup_198 : idown_199) * (scale_17610 - __m_slide_197))));
			t_sample slide_4249 = __m_slide_197;
			t_sample mul_4248 = (mix_4399 * slide_4249);
			t_sample mul_4232 = (mul_4248 * dbtoa_4231);
			t_sample mix_17614 = (mix_4400 + (gen_4230 * (mul_4233 - mix_4400)));
			t_sample mix_17615 = (mix_4399 + (gen_4230 * (mul_4232 - mix_4399)));
			t_sample mul_5787 = (mix_17614 * dbtoa_11818);
			t_sample dcblock_6333 = __m_dcblock_200(mul_5787);
			t_sample mix_17616 = (mix_17597 + (gen_4558 * (dcblock_6333 - mix_17597)));
			t_sample mix_17617 = (dryL_16421 + (gen_13452 * (mix_17616 - dryL_16421)));
			t_sample fixdenorm_15286 = fixdenorm(mix_17617);
			t_sample out1 = fixdenorm_15286;
			t_sample mul_5981 = (mix_17615 * dbtoa_11818);
			t_sample dcblock_6570 = __m_dcblock_201(mul_5981);
			t_sample mix_17618 = (mix_17599 + (gen_4558 * (dcblock_6570 - mix_17599)));
			t_sample mix_17619 = (dryR_13082 + (gen_13452 * (mix_17618 - dryR_13082)));
			t_sample fixdenorm_15171 = fixdenorm(mix_17619);
			t_sample out2 = fixdenorm_15171;
			m_history_111 = history_13449_next_13451;
			m_history_110 = history_4699_next_4701;
			m_history_109 = history_4555_next_4557;
			m_history_108 = history_4561_next_4563;
			m_history_107 = history_4567_next_4569;
			m_history_106 = history_4227_next_4229;
			m_history_105 = history_4221_next_4223;
			m_history_104 = history_4215_next_4217;
			m_history_103 = history_4209_next_4211;
			m_history_102 = history_4203_next_4205;
			m_history_101 = history_4195_next_4197;
			m_history_100 = history_4693_next_4695;
			m_history_99 = history_4395_next_4397;
			m_history_98 = history_4705_next_4707;
			m_history_97 = history_4415_next_4417;
			m_history_96 = history_4409_next_4411;
			m_history_95 = history_4403_next_4405;
			m_history_94 = history_4587_next_4589;
			m_history_93 = history_4581_next_4583;
			m_history_92 = history_4575_next_4577;
			m_history_91 = history_4425_next_4427;
			m_history_90 = history_4599_next_4601;
			m_history_89 = history_4593_next_4595;
			m_history_88 = history_4660_next_4662;
			m_history_87 = history_4654_next_4656;
			m_history_86 = history_4352_next_4361;
			m_history_77 = history_4311_next_4327;
			m_history_76 = history_4307_next_4328;
			m_history_75 = history_4321_next_4329;
			m_history_74 = history_4323_next_4330;
			m_history_73 = history_4313_next_4331;
			m_history_72 = history_4309_next_4332;
			m_history_71 = history_4319_next_4333;
			m_history_78 = history_4317_next_4326;
			m_history_85 = history_4346_next_4362;
			m_history_84 = history_4356_next_4363;
			m_history_83 = history_4342_next_4364;
			m_history_82 = history_4348_next_4365;
			m_history_81 = history_4358_next_4366;
			m_history_80 = history_4344_next_4367;
			m_history_79 = history_4354_next_4368;
			m_history_70 = history_4927_next_4929;
			m_history_47 = history_4974_next_4980;
			m_delay_48.write(add_4977);
			m_history_49 = history_4986_next_4992;
			m_delay_50.write(add_4989);
			m_history_51 = history_4998_next_5004;
			m_delay_52.write(add_5001);
			m_history_53 = history_5010_next_5016;
			m_delay_54.write(add_5013);
			m_history_55 = history_5022_next_5028;
			m_delay_56.write(add_5025);
			m_history_57 = history_5034_next_5040;
			m_delay_58.write(add_5037);
			m_history_59 = history_5046_next_5052;
			m_delay_60.write(add_5049);
			m_history_61 = history_5058_next_5064;
			m_delay_62.write(add_5061);
			m_history_69 = history_4903_next_4905;
			m_history_68 = history_4915_next_4917;
			m_history_67 = history_4909_next_4911;
			m_history_66 = history_4921_next_4923;
			m_history_65 = history_4897_next_4899;
			m_history_64 = history_4939_next_4941;
			m_history_63 = history_4933_next_4935;
			m_delay_46.write(gen_5067);
			m_delay_39.write(add_4501);
			m_delay_40.write(gen_4520);
			m_delay_41.write(add_4515);
			m_delay_42.write(gen_4534);
			m_delay_43.write(add_4529);
			m_delay_44.write(gen_4548);
			m_delay_45.write(add_4543);
			m_history_38 = history_4730_next_4732;
			m_history_15 = history_4801_next_4807;
			m_delay_16.write(add_4804);
			m_history_17 = history_4813_next_4819;
			m_delay_18.write(add_4816);
			m_history_19 = history_4825_next_4831;
			m_delay_20.write(add_4828);
			m_history_21 = history_4837_next_4843;
			m_delay_22.write(add_4840);
			m_history_23 = history_4849_next_4855;
			m_delay_24.write(add_4852);
			m_history_25 = history_4861_next_4867;
			m_delay_26.write(add_4864);
			m_history_27 = history_4873_next_4879;
			m_delay_28.write(add_4876);
			m_history_29 = history_4885_next_4891;
			m_delay_30.write(add_4888);
			m_history_37 = history_4766_next_4768;
			m_history_36 = history_4754_next_4756;
			m_history_35 = history_4760_next_4762;
			m_history_34 = history_4736_next_4738;
			m_history_33 = history_4724_next_4726;
			m_history_32 = history_4742_next_4744;
			m_history_31 = history_4748_next_4750;
			m_delay_14.write(gen_4894);
			m_delay_7.write(add_4441);
			m_delay_8.write(gen_4460);
			m_delay_9.write(add_4455);
			m_delay_10.write(gen_4474);
			m_delay_11.write(add_4469);
			m_delay_12.write(gen_4488);
			m_delay_13.write(add_4483);
			m_delay_6.write(mul_4279);
			m_history_5 = history_4281_next_4287;
			m_history_4 = history_4244_next_4246;
			m_delay_3.write(mul_4257);
			m_history_2 = history_4259_next_4265;
			m_history_1 = history_4238_next_4240;
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
	inline void set_e_SIZE(t_param _value) {
		m_e_SIZE_112 = (_value < 0.125 ? 0.125 : (_value > 4 ? 4 : _value));
	};
	inline void set_o_PEAKFREQ(t_param _value) {
		m_o_PEAKFREQ_113 = (_value < 100 ? 100 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_b_DRYWET(t_param _value) {
		m_b_DRYWET_114 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_f_ST(t_param _value) {
		m_f_ST_115 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_s_THD(t_param _value) {
		m_s_THD_116 = (_value < -36 ? -36 : (_value > 0 ? 0 : _value));
	};
	inline void set_t_RATIO(t_param _value) {
		m_t_RATIO_117 = (_value < 1 ? 1 : (_value > 20 ? 20 : _value));
	};
	inline void set_w_MAKEUP(t_param _value) {
		m_w_MAKEUP_118 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void set_q_ONOFFEQ(t_param _value) {
		m_q_ONOFFEQ_119 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_n_LOWFREQ(t_param _value) {
		m_n_LOWFREQ_120 = (_value < 20 ? 20 : (_value > 800 ? 800 : _value));
	};
	inline void set_p_HIFREQ(t_param _value) {
		m_p_HIFREQ_121 = (_value < 800 ? 800 : (_value > 15000 ? 15000 : _value));
	};
	inline void set_h_LOWGAIN(t_param _value) {
		m_h_LOWGAIN_122 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_i_PEAKGAIN(t_param _value) {
		m_i_PEAKGAIN_123 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_j_HIGAIN(t_param _value) {
		m_j_HIGAIN_124 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_k_LPF(t_param _value) {
		m_k_LPF_125 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_l_HPF(t_param _value) {
		m_l_HPF_126 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_y_IOMODE(t_param _value) {
		m_y_IOMODE_127 = (_value < 1 ? 1 : (_value > 3 ? 3 : _value));
	};
	inline void set_r_ONOFFCOMP(t_param _value) {
		m_r_ONOFFCOMP_128 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_c_REFLECT(t_param _value) {
		m_c_REFLECT_129 = (_value < 0.1 ? 0.1 : (_value > 0.99 ? 0.99 : _value));
	};
	inline void set_d_DAMP(t_param _value) {
		m_d_DAMP_130 = (_value < 0.001 ? 0.001 : (_value > 1 ? 1 : _value));
	};
	inline void set_z_BYPASS(t_param _value) {
		m_z_BYPASS_131 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_m_OUTPUT(t_param _value) {
		m_m_OUTPUT_132 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_g_FREEZE(t_param _value) {
		m_g_FREEZE_133 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_a_INPUT(t_param _value) {
		m_a_INPUT_134 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_u_ATK(t_param _value) {
		m_u_ATK_135 = (_value < 5 ? 5 : (_value > 250 ? 250 : _value));
	};
	inline void set_v_REL(t_param _value) {
		m_v_REL_136 = (_value < 5 ? 5 : (_value > 500 ? 500 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_149;
		t_sample return_150;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_149, return_150);
		t_sample x_4611 = return_149;
		sigR = return_150;
		t_sample return_174;
		t_sample return_175;
		peak_d_d_d_d_i(x_4611, sigR, pf, pg, bw, return_174, return_175);
		t_sample x_4614 = return_174;
		sigR = return_175;
		t_sample return_188;
		t_sample return_189;
		hishelf_d_d_d_d(x_4614, sigR, hf, hg, return_188, return_189);
		t_sample x_4616 = return_188;
		sigR = return_189;
		out1 = x_4616;
		out2 = sigR;
		
	};
	inline void lowshelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_144(freq) != ((int)0)) || (__m_change_145(db) != ((int)0)))) {
			m_b_143 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_f_142 = safediv(freq, m_b_143);
			m_b_141 = ((m_b_143 * m_b_143) - ((int)1));
			m_w_140 = tan(safediv((m_f_142 * ((t_sample)3.1415926535898)), samplerate));
			m_a_139 = safediv(((int)1), (m_w_140 + ((int)1)));
			m_a_138 = (m_w_140 - ((int)1));
			
		};
		t_sample outputLowShelfL = lowshelfCore_d_d_d_d_d(sigL, m_a_139, m_a_138, m_b_141, m_w_140);
		t_sample outputLowShelfR = lowshelfCore_d_d_d_d_d_147(sigR, m_a_139, m_a_138, m_b_141, m_w_140);
		out1 = outputLowShelfL;
		out2 = outputLowShelfR;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_139, t_sample m_a_138, t_sample m_b_141, t_sample m_w_140) {
		t_sample x = (m_a_139 * (input - (m_a_138 * m_z_146)));
		t_sample output = (m_w_140 * (x + m_z_146));
		m_z_146 = x;
		return ((output * m_b_141) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_147(t_sample input, t_sample m_a_139, t_sample m_a_138, t_sample m_b_141, t_sample m_w_140) {
		t_sample x = (m_a_139 * (input - (m_a_138 * m_z_148)));
		t_sample output = (m_w_140 * (x + m_z_148));
		m_z_148 = x;
		return ((output * m_b_141) + input);
		
	};
	inline void peak_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_161(freq) != ((int)0)) || (__m_change_162(db) != ((int)0))) || (__m_change_163(bw) != ((int)0)))) {
			m_w_160 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_159 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_159 * m_b_159) - ((int)1));
			m_d_158 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_164 = safediv(((m_d_158 * m_d_158) - ((int)1)), (m_d_158 * m_b_159));
			m_d_157 = ((v_164 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_164 >= ((int)100)) ? ((int)100) : v_164));
			m_d_156 = (m_d_157 * b);
			m_wq_155 = (m_d_157 * m_w_160);
			m_w_154 = (m_w_160 * m_w_160);
			m_a_153 = safediv(((int)1), ((((int)1) + m_w_154) + m_wq_155));
			m_a_152 = ((m_w_154 - ((int)1)) * ((int)2));
			m_a_151 = ((((int)1) + m_w_154) - m_wq_155);
			
		};
		t_sample outputPeakL = peakCore_d_d_d_d_d_d(sigL, m_w_160, m_d_156, m_a_153, m_a_152, m_a_151);
		t_sample outputPeakR = peakCore_d_d_d_d_d_d_169(sigR, m_w_160, m_d_156, m_a_153, m_a_152, m_a_151);
		out1 = outputPeakL;
		out2 = outputPeakR;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_160, t_sample m_d_156, t_sample m_a_153, t_sample m_a_152, t_sample m_a_151) {
		t_sample output = ((input - m_z_167) * m_w_160);
		m_z_167 = m_z_168;
		m_z_168 = input;
		t_sample output_4612 = (m_a_153 * ((output - (m_a_152 * m_z_166)) - (m_a_151 * m_z_165)));
		m_z_165 = m_z_166;
		m_z_166 = output_4612;
		t_sample output_4613 = (input + (output_4612 * m_d_156));
		return output_4613;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_169(t_sample input, t_sample m_w_160, t_sample m_d_156, t_sample m_a_153, t_sample m_a_152, t_sample m_a_151) {
		t_sample output = ((input - m_z_172) * m_w_160);
		m_z_172 = m_z_173;
		m_z_173 = input;
		t_sample output_4612 = (m_a_153 * ((output - (m_a_152 * m_z_171)) - (m_a_151 * m_z_170)));
		m_z_170 = m_z_171;
		m_z_171 = output_4612;
		t_sample output_4613 = (input + (output_4612 * m_d_156));
		return output_4613;
		
	};
	inline void hishelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_182(freq) != ((int)0)) || (__m_change_183(db) != ((int)0)))) {
			m_b_181 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_184 = (freq * m_b_181);
			m_f_180 = ((samplerate < mina_184) ? samplerate : mina_184);
			m_b_179 = ((m_b_181 * m_b_181) - ((int)1));
			m_w_178 = tan(safediv((((m_f_180 < ((int)0)) ? ((int)0) : m_f_180) * ((t_sample)3.1415926535898)), samplerate));
			m_a_177 = safediv(((int)1), (m_w_178 + ((int)1)));
			m_a_176 = (m_w_178 - ((int)1));
			
		};
		t_sample outputHighShelfL = hishelfCore_d_d_d_d(sigL, m_a_177, m_a_176, m_b_179);
		t_sample outputHighShelfR = hishelfCore_d_d_d_d_186(sigR, m_a_177, m_a_176, m_b_179);
		out1 = outputHighShelfL;
		out2 = outputHighShelfR;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_177, t_sample m_a_176, t_sample m_b_179) {
		t_sample x = (m_a_177 * (input - (m_a_176 * m_z_185)));
		t_sample output = (x - m_z_185);
		m_z_185 = x;
		t_sample output_4615 = ((output * m_b_179) + input);
		return output_4615;
		
	};
	inline t_sample hishelfCore_d_d_d_d_186(t_sample input, t_sample m_a_177, t_sample m_a_176, t_sample m_b_179) {
		t_sample x = (m_a_177 * (input - (m_a_176 * m_z_187)));
		t_sample output = (x - m_z_187);
		m_z_187 = x;
		t_sample output_4615 = ((output * m_b_179) + input);
		return output_4615;
		
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
		case 23: self->set_y_IOMODE(value); break;
		case 24: self->set_z_BYPASS(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_a_INPUT_134; break;
		case 1: *value = self->m_b_DRYWET_114; break;
		case 2: *value = self->m_c_REFLECT_129; break;
		case 3: *value = self->m_d_DAMP_130; break;
		case 4: *value = self->m_e_SIZE_112; break;
		case 5: *value = self->m_f_ST_115; break;
		case 6: *value = self->m_g_FREEZE_133; break;
		case 7: *value = self->m_h_LOWGAIN_122; break;
		case 8: *value = self->m_i_PEAKGAIN_123; break;
		case 9: *value = self->m_j_HIGAIN_124; break;
		case 10: *value = self->m_k_LPF_125; break;
		case 11: *value = self->m_l_HPF_126; break;
		case 12: *value = self->m_m_OUTPUT_132; break;
		case 13: *value = self->m_n_LOWFREQ_120; break;
		case 14: *value = self->m_o_PEAKFREQ_113; break;
		case 15: *value = self->m_p_HIFREQ_121; break;
		case 16: *value = self->m_q_ONOFFEQ_119; break;
		case 17: *value = self->m_r_ONOFFCOMP_128; break;
		case 18: *value = self->m_s_THD_116; break;
		case 19: *value = self->m_t_RATIO_117; break;
		case 20: *value = self->m_u_ATK_135; break;
		case 21: *value = self->m_v_REL_136; break;
		case 22: *value = self->m_w_MAKEUP_118; break;
		case 23: *value = self->m_y_IOMODE_127; break;
		case 24: *value = self->m_z_BYPASS_131; break;
		
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
	// initialize parameter 0 ("m_a_INPUT_134")
	pi = self->__commonstate.params + 0;
	pi->name = "a_INPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_INPUT_134;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -12;
	pi->outputmax = 12;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_DRYWET_114")
	pi = self->__commonstate.params + 1;
	pi->name = "b_DRYWET";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_DRYWET_114;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_REFLECT_129")
	pi = self->__commonstate.params + 2;
	pi->name = "c_REFLECT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_REFLECT_129;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.99;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_DAMP_130")
	pi = self->__commonstate.params + 3;
	pi->name = "d_DAMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_DAMP_130;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_SIZE_112")
	pi = self->__commonstate.params + 4;
	pi->name = "e_SIZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_SIZE_112;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.125;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_ST_115")
	pi = self->__commonstate.params + 5;
	pi->name = "f_ST";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_ST_115;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_FREEZE_133")
	pi = self->__commonstate.params + 6;
	pi->name = "g_FREEZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_FREEZE_133;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_LOWGAIN_122")
	pi = self->__commonstate.params + 7;
	pi->name = "h_LOWGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_LOWGAIN_122;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_PEAKGAIN_123")
	pi = self->__commonstate.params + 8;
	pi->name = "i_PEAKGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_PEAKGAIN_123;
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
	// initialize parameter 10 ("m_k_LPF_125")
	pi = self->__commonstate.params + 10;
	pi->name = "k_LPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_LPF_125;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_HPF_126")
	pi = self->__commonstate.params + 11;
	pi->name = "l_HPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_HPF_126;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_OUTPUT_132")
	pi = self->__commonstate.params + 12;
	pi->name = "m_OUTPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_OUTPUT_132;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -12;
	pi->outputmax = 12;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_LOWFREQ_120")
	pi = self->__commonstate.params + 13;
	pi->name = "n_LOWFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_LOWFREQ_120;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 800;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_PEAKFREQ_113")
	pi = self->__commonstate.params + 14;
	pi->name = "o_PEAKFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_PEAKFREQ_113;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 2500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_HIFREQ_121")
	pi = self->__commonstate.params + 15;
	pi->name = "p_HIFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_HIFREQ_121;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 800;
	pi->outputmax = 15000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_ONOFFEQ_119")
	pi = self->__commonstate.params + 16;
	pi->name = "q_ONOFFEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_ONOFFEQ_119;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 17 ("m_r_ONOFFCOMP_128")
	pi = self->__commonstate.params + 17;
	pi->name = "r_ONOFFCOMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_ONOFFCOMP_128;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 18 ("m_s_THD_116")
	pi = self->__commonstate.params + 18;
	pi->name = "s_THD";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_THD_116;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -36;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_RATIO_117")
	pi = self->__commonstate.params + 19;
	pi->name = "t_RATIO";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_RATIO_117;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_ATK_135")
	pi = self->__commonstate.params + 20;
	pi->name = "u_ATK";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_ATK_135;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 5;
	pi->outputmax = 250;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_REL_136")
	pi = self->__commonstate.params + 21;
	pi->name = "v_REL";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_REL_136;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 5;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_MAKEUP_118")
	pi = self->__commonstate.params + 22;
	pi->name = "w_MAKEUP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_MAKEUP_118;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -6;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 23 ("m_y_IOMODE_127")
	pi = self->__commonstate.params + 23;
	pi->name = "y_IOMODE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_y_IOMODE_127;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 3;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 24 ("m_z_BYPASS_131")
	pi = self->__commonstate.params + 24;
	pi->name = "z_BYPASS";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_z_BYPASS_131;
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
