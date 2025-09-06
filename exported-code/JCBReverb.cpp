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
	t_sample m_q_ONOFFEQ_135;
	t_sample m_h_LOWGAIN_136;
	t_sample m_a_INPUT_134;
	t_sample m_l_HPF_132;
	t_sample m_k_LPF_133;
	t_sample m_w_MAKEUP_131;
	t_sample m_history_137;
	t_sample m_a_139;
	t_sample m_a_140;
	t_sample m_b_144;
	t_sample m_history_15;
	t_sample m_r_ONOFFCOMP_130;
	t_sample m_f_143;
	t_sample m_w_141;
	t_sample m_b_142;
	t_sample m_history_5;
	t_sample m_t_RATIO_129;
	t_sample m_z_BYPASS_127;
	t_sample m_s_THD_117;
	t_sample m_u_ATK_118;
	t_sample m_d_DAMP_119;
	t_sample m_x_PUMP_116;
	t_sample m_o_PEAKFREQ_114;
	t_sample m_m_OUTPUT_115;
	t_sample m_g_FREEZE_128;
	t_sample m_v_REL_120;
	t_sample m_p_HIFREQ_122;
	t_sample m_b_DRYWET_126;
	t_sample m_n_LOWFREQ_121;
	t_sample m_c_REFLECT_125;
	t_sample m_f_ST_123;
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
	t_sample m_e_SIZE_113;
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
	t_sample m_y_FILTERS_112;
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
	t_sample m_i_PEAKGAIN_111;
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
		m_delay_6.reset("m_delay_6", samplerate);
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
		m_i_PEAKGAIN_111 = 0;
		m_y_FILTERS_112 = 0;
		m_e_SIZE_113 = 1;
		m_o_PEAKFREQ_114 = 800;
		m_m_OUTPUT_115 = 0;
		m_x_PUMP_116 = 0;
		m_s_THD_117 = -18;
		m_u_ATK_118 = 5;
		m_d_DAMP_119 = 0.25;
		m_v_REL_120 = 250;
		m_n_LOWFREQ_121 = 100;
		m_p_HIFREQ_122 = 5000;
		m_f_ST_123 = 0.5;
		m_j_HIGAIN_124 = 0;
		m_c_REFLECT_125 = 0.85;
		m_b_DRYWET_126 = 0.33;
		m_z_BYPASS_127 = 0;
		m_g_FREEZE_128 = 0;
		m_t_RATIO_129 = 4;
		m_r_ONOFFCOMP_130 = 0;
		m_w_MAKEUP_131 = 0;
		m_l_HPF_132 = 20;
		m_k_LPF_133 = 20000;
		m_a_INPUT_134 = 0;
		m_q_ONOFFEQ_135 = 0;
		m_h_LOWGAIN_136 = 0;
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
		t_sample mul_9 = (m_z_BYPASS_127 * ((t_sample)0.001));
		t_sample dbtoa_36 = dbtoa(m_a_INPUT_134);
		t_sample mul_609 = (dbtoa_36 * ((t_sample)0.001));
		t_sample mul_487 = (m_b_DRYWET_126 * ((t_sample)0.001));
		int gte_632 = (m_g_FREEZE_128 >= ((t_sample)0.5));
		t_sample mul_79 = (m_r_ONOFFCOMP_130 * ((t_sample)0.001));
		t_sample mul_71 = (m_s_THD_117 * ((t_sample)0.001));
		t_sample mul_63 = (m_t_RATIO_129 * ((t_sample)0.001));
		t_sample mul_55 = (m_u_ATK_118 * ((t_sample)0.001));
		t_sample mul_47 = (m_v_REL_120 * ((t_sample)0.001));
		t_sample mul_37 = (m_w_MAKEUP_131 * ((t_sample)0.001));
		t_sample dbtoa_35 = dbtoa(m_m_OUTPUT_115);
		t_sample mul_495 = (dbtoa_35 * ((t_sample)0.001));
		t_sample mul_301 = (m_q_ONOFFEQ_135 * ((t_sample)0.001));
		t_sample mul_327 = (m_n_LOWFREQ_121 * ((t_sample)0.001));
		t_sample mul_319 = (m_o_PEAKFREQ_114 * ((t_sample)0.001));
		t_sample mul_311 = (m_p_HIFREQ_122 * ((t_sample)0.001));
		t_sample mul_521 = (m_h_LOWGAIN_136 * ((t_sample)0.001));
		t_sample mul_513 = (m_i_PEAKGAIN_111 * ((t_sample)0.001));
		t_sample mul_505 = (m_j_HIGAIN_124 * ((t_sample)0.001));
		t_sample mul_617 = (m_f_ST_123 * ((t_sample)0.001));
		t_sample mul_335 = (m_e_SIZE_113 * ((t_sample)0.001));
		t_sample mul_27 = (m_d_DAMP_119 * ((t_sample)0.001));
		t_sample mul_537 = (m_k_LPF_133 * ((t_sample)0.001));
		t_sample mul_529 = (m_l_HPF_132 * ((t_sample)0.001));
		t_sample mul_1 = (m_y_FILTERS_112 * ((t_sample)0.001));
		int rsub_631 = (((int)1) - gte_632);
		t_sample mul_579 = (rsub_631 * ((t_sample)0.001));
		t_sample rsub_628 = (((int)1) - m_c_REFLECT_125);
		int choice_138 = gte_632;
		t_sample gate_627 = ((choice_138 >= 1) ? rsub_628 : 0);
		t_sample add_629 = (m_c_REFLECT_125 + gate_627);
		t_sample mul_587 = (add_629 * ((t_sample)0.001));
		t_sample div_934 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_469 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_452 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_435 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_418 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_712 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_397 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_380 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_363 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_346 = (samplerate * ((t_sample)2.2675736961451e-05));
		int maxb_193 = (-96);
		int maxb_197 = (-96);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_10 = (m_history_137 * ((t_sample)0.999));
			t_sample add_12 = (mul_9 + mul_10);
			t_sample gen_16 = add_12;
			t_sample history_11_next_15 = fixdenorm(add_12);
			t_sample mul_610 = (m_history_110 * ((t_sample)0.999));
			t_sample add_612 = (mul_609 + mul_610);
			t_sample gen_616 = add_612;
			t_sample history_611_next_615 = fixdenorm(add_612);
			t_sample mul_574 = (in1 * gen_616);
			t_sample out3 = mul_574;
			t_sample mul_573 = (in2 * gen_616);
			t_sample out4 = mul_573;
			t_sample mul_488 = (m_history_109 * ((t_sample)0.999));
			t_sample add_490 = (mul_487 + mul_488);
			t_sample gen_494 = add_490;
			t_sample history_489_next_493 = fixdenorm(add_490);
			t_sample mix_9064 = (in1 + (gte_632 * (((int)0) - in1)));
			t_sample mix_9065 = (in2 + (gte_632 * (((int)0) - in2)));
			t_sample mul_80 = (m_history_108 * ((t_sample)0.999));
			t_sample add_82 = (mul_79 + mul_80);
			t_sample gen_86 = add_82;
			t_sample history_81_next_85 = fixdenorm(add_82);
			t_sample mul_72 = (m_history_107 * ((t_sample)0.999));
			t_sample add_74 = (mul_71 + mul_72);
			t_sample gen_78 = add_74;
			t_sample history_73_next_77 = fixdenorm(add_74);
			t_sample mul_64 = (m_history_106 * ((t_sample)0.999));
			t_sample add_66 = (mul_63 + mul_64);
			t_sample gen_70 = add_66;
			t_sample history_65_next_69 = fixdenorm(add_66);
			t_sample mul_56 = (m_history_105 * ((t_sample)0.999));
			t_sample add_58 = (mul_55 + mul_56);
			t_sample gen_62 = add_58;
			t_sample history_57_next_61 = fixdenorm(add_58);
			t_sample mul_48 = (m_history_104 * ((t_sample)0.999));
			t_sample add_50 = (mul_47 + mul_48);
			t_sample gen_54 = add_50;
			t_sample history_49_next_53 = fixdenorm(add_50);
			t_sample mul_38 = (m_history_103 * ((t_sample)0.999));
			t_sample add_40 = (mul_37 + mul_38);
			t_sample gen_44 = add_40;
			t_sample history_39_next_43 = fixdenorm(add_40);
			t_sample mul_496 = (m_history_102 * ((t_sample)0.999));
			t_sample add_498 = (mul_495 + mul_496);
			t_sample gen_502 = add_498;
			t_sample history_497_next_501 = fixdenorm(add_498);
			t_sample mul_302 = (m_history_101 * ((t_sample)0.999));
			t_sample add_304 = (mul_301 + mul_302);
			t_sample gen_308 = add_304;
			t_sample history_303_next_307 = fixdenorm(add_304);
			t_sample mul_328 = (m_history_100 * ((t_sample)0.999));
			t_sample add_330 = (mul_327 + mul_328);
			t_sample gen_334 = add_330;
			t_sample history_329_next_333 = fixdenorm(add_330);
			t_sample mul_320 = (m_history_99 * ((t_sample)0.999));
			t_sample add_322 = (mul_319 + mul_320);
			t_sample gen_326 = add_322;
			t_sample history_321_next_325 = fixdenorm(add_322);
			t_sample mul_312 = (m_history_98 * ((t_sample)0.999));
			t_sample add_314 = (mul_311 + mul_312);
			t_sample gen_318 = add_314;
			t_sample history_313_next_317 = fixdenorm(add_314);
			t_sample mul_522 = (m_history_97 * ((t_sample)0.999));
			t_sample add_524 = (mul_521 + mul_522);
			t_sample gen_528 = add_524;
			t_sample history_523_next_527 = fixdenorm(add_524);
			t_sample mul_514 = (m_history_96 * ((t_sample)0.999));
			t_sample add_516 = (mul_513 + mul_514);
			t_sample gen_520 = add_516;
			t_sample history_515_next_519 = fixdenorm(add_516);
			t_sample mul_506 = (m_history_95 * ((t_sample)0.999));
			t_sample add_508 = (mul_505 + mul_506);
			t_sample gen_512 = add_508;
			t_sample history_507_next_511 = fixdenorm(add_508);
			t_sample mul_618 = (m_history_94 * ((t_sample)0.999));
			t_sample add_620 = (mul_617 + mul_618);
			t_sample gen_624 = add_620;
			t_sample history_619_next_623 = fixdenorm(add_620);
			t_sample sub_9069 = (gen_624 - ((int)0));
			t_sample scale_9066 = ((safepow((sub_9069 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_597 = scale_9066;
			t_sample sqrt_602 = sqrt(gen_624);
			t_sample rsub_625 = (((int)1) - gen_624);
			t_sample sqrt_603 = sqrt(rsub_625);
			t_sample mul_336 = (m_history_93 * ((t_sample)0.999));
			t_sample add_338 = (mul_335 + mul_336);
			t_sample gen_342 = add_338;
			t_sample history_337_next_341 = fixdenorm(add_338);
			t_sample mul_28 = (m_history_92 * ((t_sample)0.999));
			t_sample add_30 = (mul_27 + mul_28);
			t_sample gen_34 = add_30;
			t_sample history_29_next_33 = fixdenorm(add_30);
			t_sample mul_538 = (m_history_91 * ((t_sample)0.999));
			t_sample add_540 = (mul_537 + mul_538);
			t_sample gen_544 = add_540;
			t_sample history_539_next_543 = fixdenorm(add_540);
			t_sample mul_530 = (m_history_90 * ((t_sample)0.999));
			t_sample add_532 = (mul_529 + mul_530);
			t_sample gen_536 = add_532;
			t_sample history_531_next_535 = fixdenorm(add_532);
			t_sample mul_2 = (m_history_89 * ((t_sample)0.999));
			t_sample add_4 = (mul_1 + mul_2);
			t_sample gen_8 = add_4;
			t_sample history_3_next_7 = fixdenorm(add_4);
			t_sample mul_343 = (((int)23) * gen_342);
			t_sample mul_580 = (m_history_88 * ((t_sample)0.999));
			t_sample add_582 = (mul_579 + mul_580);
			t_sample gen_586 = add_582;
			t_sample history_581_next_585 = fixdenorm(add_582);
			t_sample mul_630 = (mul_574 * gen_586);
			t_sample mul_608 = (mul_573 * gen_586);
			t_sample omega = safediv((gen_536 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) + cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((-(((int)1) + cs)) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_280 = a2;
			t_sample expr_281 = a1;
			t_sample expr_282 = a2;
			t_sample expr_283 = b1;
			t_sample expr_284 = b2;
			t_sample omega_291 = safediv((gen_544 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_290 = sin(omega_291);
			t_sample cs_297 = cos(omega_291);
			t_sample alpha_298 = ((sn_290 * ((t_sample)0.5)) * ((int)1));
			t_sample b_295 = safediv(((int)1), (((int)1) + alpha_298));
			t_sample a_296 = (((((int)1) - cs_297) * ((t_sample)0.5)) * b_295);
			t_sample a_294 = ((((int)1) - cs_297) * b_295);
			t_sample b_292 = ((((int)-2) * cs_297) * b_295);
			t_sample b_293 = ((((int)1) - alpha_298) * b_295);
			t_sample expr_285 = a_296;
			t_sample expr_286 = a_294;
			t_sample expr_287 = a_296;
			t_sample expr_288 = b_292;
			t_sample expr_289 = b_293;
			t_sample mul_238 = (mul_630 * expr_285);
			t_sample mul_228 = (mul_608 * expr_285);
			t_sample mul_235 = (m_history_82 * expr_286);
			t_sample mul_225 = (m_history_83 * expr_286);
			t_sample mul_233 = (m_history_84 * expr_287);
			t_sample mul_223 = (m_history_87 * expr_287);
			t_sample mul_229 = (m_history_86 * expr_289);
			t_sample mul_219 = (m_history_85 * expr_289);
			t_sample mul_231 = (m_history_81 * expr_288);
			t_sample sub_237 = (((mul_233 + mul_235) + mul_238) - (mul_231 + mul_229));
			t_sample gen_257 = sub_237;
			t_sample mul_221 = (m_history_80 * expr_288);
			t_sample sub_227 = (((mul_228 + mul_225) + mul_223) - (mul_221 + mul_219));
			t_sample gen_258 = sub_227;
			t_sample history_224_next_249 = fixdenorm(m_history_83);
			t_sample history_230_next_250 = fixdenorm(m_history_81);
			t_sample history_220_next_251 = fixdenorm(m_history_80);
			t_sample history_234_next_252 = fixdenorm(m_history_82);
			t_sample history_226_next_253 = fixdenorm(mul_608);
			t_sample history_236_next_254 = fixdenorm(mul_630);
			t_sample history_232_next_255 = fixdenorm(sub_237);
			t_sample history_222_next_256 = fixdenorm(sub_227);
			t_sample mul_178 = (m_history_79 * expr_282);
			t_sample mul_188 = (m_history_76 * expr_282);
			t_sample mul_180 = (m_history_75 * expr_281);
			t_sample mul_190 = (m_history_74 * expr_281);
			t_sample mul_183 = (gen_258 * expr_280);
			t_sample mul_193 = (gen_257 * expr_280);
			t_sample mul_174 = (m_history_77 * expr_284);
			t_sample mul_184 = (m_history_78 * expr_284);
			t_sample mul_176 = (m_history_73 * expr_283);
			t_sample sub_182 = (((mul_183 + mul_180) + mul_178) - (mul_176 + mul_174));
			t_sample gen_213 = sub_182;
			t_sample mul_186 = (m_history_72 * expr_283);
			t_sample sub_192 = (((mul_188 + mul_190) + mul_193) - (mul_186 + mul_184));
			t_sample gen_212 = sub_192;
			t_sample history_179_next_204 = fixdenorm(m_history_75);
			t_sample history_185_next_205 = fixdenorm(m_history_72);
			t_sample history_175_next_206 = fixdenorm(m_history_73);
			t_sample history_189_next_207 = fixdenorm(m_history_74);
			t_sample history_181_next_208 = fixdenorm(gen_258);
			t_sample history_191_next_209 = fixdenorm(gen_257);
			t_sample history_177_next_210 = fixdenorm(sub_182);
			t_sample history_187_next_211 = fixdenorm(sub_192);
			t_sample mix_9070 = (mul_630 + (gen_8 * (gen_212 - mul_630)));
			t_sample mix_168 = mix_9070;
			t_sample gen_299 = mix_168;
			t_sample mix_9071 = (mul_608 + (gen_8 * (gen_213 - mul_608)));
			t_sample mix_167 = mix_9071;
			t_sample gen_300 = mix_167;
			t_sample mul_588 = (m_history_71 * ((t_sample)0.999));
			t_sample add_590 = (mul_587 + mul_588);
			t_sample gen_594 = add_590;
			t_sample history_589_next_593 = fixdenorm(add_590);
			t_sample rsub_953 = (((int)1) - gen_34);
			t_sample mul_919 = (div_934 * gen_342);
			t_sample mul_928 = (((int)1422) * mul_919);
			t_sample mul_888 = (m_history_70 * ((t_sample)0.999));
			t_sample mul_887 = (mul_928 * ((t_sample)0.001));
			t_sample add_890 = (mul_887 + mul_888);
			t_sample gen_894 = add_890;
			t_sample history_889_next_893 = fixdenorm(add_890);
			t_sample gen_948 = gen_894;
			t_sample mul_935 = (((int)1557) * mul_919);
			t_sample mul_912 = (m_history_69 * ((t_sample)0.999));
			t_sample mul_911 = (mul_935 * ((t_sample)0.001));
			t_sample add_914 = (mul_911 + mul_912);
			t_sample gen_918 = add_914;
			t_sample history_913_next_917 = fixdenorm(add_914);
			t_sample gen_945 = gen_918;
			t_sample mul_932 = (((int)1617) * mul_919);
			t_sample mul_904 = (m_history_68 * ((t_sample)0.999));
			t_sample mul_903 = (mul_932 * ((t_sample)0.001));
			t_sample add_906 = (mul_903 + mul_904);
			t_sample gen_910 = add_906;
			t_sample history_905_next_909 = fixdenorm(add_906);
			t_sample gen_946 = gen_910;
			t_sample mul_924 = (((int)1356) * mul_919);
			t_sample mul_872 = (m_history_67 * ((t_sample)0.999));
			t_sample mul_871 = (mul_924 * ((t_sample)0.001));
			t_sample add_874 = (mul_871 + mul_872);
			t_sample gen_878 = add_874;
			t_sample history_873_next_877 = fixdenorm(add_874);
			t_sample gen_950 = gen_878;
			t_sample mul_920 = (((int)1116) * mul_919);
			t_sample mul_856 = (m_history_66 * ((t_sample)0.999));
			t_sample mul_855 = (mul_920 * ((t_sample)0.001));
			t_sample add_858 = (mul_855 + mul_856);
			t_sample gen_862 = add_858;
			t_sample history_857_next_861 = fixdenorm(add_858);
			t_sample gen_952 = gen_862;
			t_sample mul_930 = (((int)1491) * mul_919);
			t_sample mul_896 = (m_history_65 * ((t_sample)0.999));
			t_sample mul_895 = (mul_930 * ((t_sample)0.001));
			t_sample add_898 = (mul_895 + mul_896);
			t_sample gen_902 = add_898;
			t_sample history_897_next_901 = fixdenorm(add_898);
			t_sample gen_947 = gen_902;
			t_sample mul_922 = (((int)1188) * mul_919);
			t_sample mul_864 = (m_history_64 * ((t_sample)0.999));
			t_sample mul_863 = (mul_922 * ((t_sample)0.001));
			t_sample add_866 = (mul_863 + mul_864);
			t_sample gen_870 = add_866;
			t_sample history_865_next_869 = fixdenorm(add_866);
			t_sample gen_951 = gen_870;
			t_sample mul_926 = (((int)1277) * mul_919);
			t_sample mul_880 = (m_history_63 * ((t_sample)0.999));
			t_sample mul_879 = (mul_926 * ((t_sample)0.001));
			t_sample add_882 = (mul_879 + mul_880);
			t_sample gen_886 = add_882;
			t_sample history_881_next_885 = fixdenorm(add_882);
			t_sample gen_949 = gen_886;
			t_sample rsub_955 = (((int)1) - rsub_953);
			t_sample mul_957 = (m_history_61 * rsub_955);
			t_sample add_954 = (((int)0) + gen_952);
			t_sample tap_963 = m_delay_62.read_linear(add_954);
			t_sample mul_960 = (tap_963 * rsub_953);
			t_sample add_959 = (mul_960 + mul_957);
			t_sample mul_956 = (add_959 * gen_594);
			t_sample add_961 = (gen_299 + mul_956);
			t_sample gen_968 = add_961;
			t_sample history_958_next_967 = fixdenorm(add_959);
			t_sample rsub_970 = (((int)1) - rsub_953);
			t_sample mul_972 = (m_history_59 * rsub_970);
			t_sample add_969 = (((int)0) + gen_951);
			t_sample tap_978 = m_delay_60.read_linear(add_969);
			t_sample mul_975 = (tap_978 * rsub_953);
			t_sample add_974 = (mul_975 + mul_972);
			t_sample mul_971 = (add_974 * gen_594);
			t_sample add_976 = (gen_299 + mul_971);
			t_sample gen_983 = add_976;
			t_sample history_973_next_982 = fixdenorm(add_974);
			t_sample rsub_985 = (((int)1) - rsub_953);
			t_sample mul_987 = (m_history_57 * rsub_985);
			t_sample add_984 = (((int)0) + gen_950);
			t_sample tap_993 = m_delay_58.read_linear(add_984);
			t_sample mul_990 = (tap_993 * rsub_953);
			t_sample add_989 = (mul_990 + mul_987);
			t_sample mul_986 = (add_989 * gen_594);
			t_sample add_991 = (gen_299 + mul_986);
			t_sample gen_998 = add_991;
			t_sample history_988_next_997 = fixdenorm(add_989);
			t_sample rsub_1000 = (((int)1) - rsub_953);
			t_sample mul_1002 = (m_history_55 * rsub_1000);
			t_sample add_999 = (((int)0) + gen_949);
			t_sample tap_1008 = m_delay_56.read_linear(add_999);
			t_sample mul_1005 = (tap_1008 * rsub_953);
			t_sample add_1004 = (mul_1005 + mul_1002);
			t_sample mul_1001 = (add_1004 * gen_594);
			t_sample add_1006 = (gen_299 + mul_1001);
			t_sample gen_1013 = add_1006;
			t_sample history_1003_next_1012 = fixdenorm(add_1004);
			t_sample rsub_1015 = (((int)1) - rsub_953);
			t_sample mul_1017 = (m_history_53 * rsub_1015);
			t_sample add_1014 = (((int)0) + gen_948);
			t_sample tap_1023 = m_delay_54.read_linear(add_1014);
			t_sample mul_1020 = (tap_1023 * rsub_953);
			t_sample add_1019 = (mul_1020 + mul_1017);
			t_sample mul_1016 = (add_1019 * gen_594);
			t_sample add_1021 = (gen_299 + mul_1016);
			t_sample gen_1028 = add_1021;
			t_sample history_1018_next_1027 = fixdenorm(add_1019);
			t_sample rsub_1030 = (((int)1) - rsub_953);
			t_sample mul_1032 = (m_history_51 * rsub_1030);
			t_sample add_1029 = (((int)0) + gen_947);
			t_sample tap_1038 = m_delay_52.read_linear(add_1029);
			t_sample mul_1035 = (tap_1038 * rsub_953);
			t_sample add_1034 = (mul_1035 + mul_1032);
			t_sample mul_1031 = (add_1034 * gen_594);
			t_sample add_1036 = (gen_299 + mul_1031);
			t_sample gen_1043 = add_1036;
			t_sample history_1033_next_1042 = fixdenorm(add_1034);
			t_sample rsub_1045 = (((int)1) - rsub_953);
			t_sample mul_1047 = (m_history_49 * rsub_1045);
			t_sample add_1044 = (((int)0) + gen_946);
			t_sample tap_1053 = m_delay_50.read_linear(add_1044);
			t_sample mul_1050 = (tap_1053 * rsub_953);
			t_sample add_1049 = (mul_1050 + mul_1047);
			t_sample mul_1046 = (add_1049 * gen_594);
			t_sample add_1051 = (gen_299 + mul_1046);
			t_sample gen_1058 = add_1051;
			t_sample history_1048_next_1057 = fixdenorm(add_1049);
			t_sample rsub_1060 = (((int)1) - rsub_953);
			t_sample mul_1062 = (m_history_47 * rsub_1060);
			t_sample add_1059 = (((int)0) + gen_945);
			t_sample tap_1068 = m_delay_48.read_linear(add_1059);
			t_sample mul_1065 = (tap_1068 * rsub_953);
			t_sample add_1064 = (mul_1065 + mul_1062);
			t_sample mul_1061 = (add_1064 * gen_594);
			t_sample add_1066 = (gen_299 + mul_1061);
			t_sample gen_1073 = add_1066;
			t_sample history_1063_next_1072 = fixdenorm(add_1064);
			t_sample mul_1074 = ((((((((gen_1073 + gen_1058) + gen_1043) + gen_1028) + gen_1013) + gen_998) + gen_983) + gen_968) * ((t_sample)0.125));
			t_sample gen_1076 = mul_1074;
			t_sample mul_478 = (gen_1076 * ((t_sample)-0.5));
			t_sample mul_468 = (div_469 * gen_342);
			t_sample mul_470 = (((int)255) * mul_468);
			t_sample add_472 = (((int)0) + mul_470);
			t_sample tap_480 = m_delay_46.read_linear(add_472);
			t_sample tap_475 = m_delay_45.read_linear(add_472);
			t_sample mul_473 = (tap_475 * ((t_sample)0.5));
			t_sample add_476 = (mul_478 + (tap_480 + mul_473));
			t_sample gen_484 = add_476;
			t_sample mul_461 = (gen_484 * ((t_sample)-0.5));
			t_sample mul_451 = (div_452 * gen_342);
			t_sample mul_453 = (((int)556) * mul_451);
			t_sample add_455 = (((int)0) + mul_453);
			t_sample tap_463 = m_delay_44.read_linear(add_455);
			t_sample tap_458 = m_delay_43.read_linear(add_455);
			t_sample mul_456 = (tap_458 * ((t_sample)0.5));
			t_sample add_459 = (mul_461 + (tap_463 + mul_456));
			t_sample gen_467 = add_459;
			t_sample mul_444 = (gen_467 * ((t_sample)-0.5));
			t_sample mul_434 = (div_435 * gen_342);
			t_sample mul_436 = (((int)441) * mul_434);
			t_sample add_438 = (((int)0) + mul_436);
			t_sample tap_446 = m_delay_42.read_linear(add_438);
			t_sample tap_441 = m_delay_41.read_linear(add_438);
			t_sample mul_439 = (tap_441 * ((t_sample)0.5));
			t_sample add_442 = (mul_444 + (tap_446 + mul_439));
			t_sample gen_450 = add_442;
			t_sample mul_427 = (gen_450 * ((t_sample)-0.5));
			t_sample mul_417 = (div_418 * gen_342);
			t_sample mul_419 = (((int)341) * mul_417);
			t_sample add_421 = (((int)0) + mul_419);
			t_sample tap_429 = m_delay_40.read_linear(add_421);
			t_sample tap_424 = m_delay_39.read_linear(add_421);
			t_sample mul_422 = (tap_424 * ((t_sample)0.5));
			t_sample add_425 = (mul_427 + (tap_429 + mul_422));
			t_sample gen_433 = add_425;
			t_sample gen_486 = gen_433;
			t_sample rsub_731 = (((int)1) - gen_34);
			t_sample mul_697 = (div_712 * gen_342);
			t_sample mul_710 = (((int)1617) * mul_697);
			t_sample mul_682 = (m_history_38 * ((t_sample)0.999));
			t_sample mul_681 = (mul_710 * ((t_sample)0.001));
			t_sample add_684 = (mul_681 + mul_682);
			t_sample gen_688 = add_684;
			t_sample history_683_next_687 = fixdenorm(add_684);
			t_sample gen_724 = gen_688;
			t_sample mul_698 = (((int)1116) * mul_697);
			t_sample mul_634 = (m_history_37 * ((t_sample)0.999));
			t_sample mul_633 = (mul_698 * ((t_sample)0.001));
			t_sample add_636 = (mul_633 + mul_634);
			t_sample gen_640 = add_636;
			t_sample history_635_next_639 = fixdenorm(add_636);
			t_sample gen_730 = gen_640;
			t_sample mul_708 = (((int)1491) * mul_697);
			t_sample mul_674 = (m_history_36 * ((t_sample)0.999));
			t_sample mul_673 = (mul_708 * ((t_sample)0.001));
			t_sample add_676 = (mul_673 + mul_674);
			t_sample gen_680 = add_676;
			t_sample history_675_next_679 = fixdenorm(add_676);
			t_sample gen_725 = gen_680;
			t_sample mul_706 = (((int)1422) * mul_697);
			t_sample mul_666 = (m_history_35 * ((t_sample)0.999));
			t_sample mul_665 = (mul_706 * ((t_sample)0.001));
			t_sample add_668 = (mul_665 + mul_666);
			t_sample gen_672 = add_668;
			t_sample history_667_next_671 = fixdenorm(add_668);
			t_sample gen_726 = gen_672;
			t_sample mul_702 = (((int)1356) * mul_697);
			t_sample mul_650 = (m_history_34 * ((t_sample)0.999));
			t_sample mul_649 = (mul_702 * ((t_sample)0.001));
			t_sample add_652 = (mul_649 + mul_650);
			t_sample gen_656 = add_652;
			t_sample history_651_next_655 = fixdenorm(add_652);
			t_sample gen_728 = gen_656;
			t_sample mul_713 = (((int)1557) * mul_697);
			t_sample mul_690 = (m_history_33 * ((t_sample)0.999));
			t_sample mul_689 = (mul_713 * ((t_sample)0.001));
			t_sample add_692 = (mul_689 + mul_690);
			t_sample gen_696 = add_692;
			t_sample history_691_next_695 = fixdenorm(add_692);
			t_sample gen_723 = gen_696;
			t_sample mul_704 = (((int)1277) * mul_697);
			t_sample mul_658 = (m_history_32 * ((t_sample)0.999));
			t_sample mul_657 = (mul_704 * ((t_sample)0.001));
			t_sample add_660 = (mul_657 + mul_658);
			t_sample gen_664 = add_660;
			t_sample history_659_next_663 = fixdenorm(add_660);
			t_sample gen_727 = gen_664;
			t_sample mul_700 = (((int)1188) * mul_697);
			t_sample mul_642 = (m_history_31 * ((t_sample)0.999));
			t_sample mul_641 = (mul_700 * ((t_sample)0.001));
			t_sample add_644 = (mul_641 + mul_642);
			t_sample gen_648 = add_644;
			t_sample history_643_next_647 = fixdenorm(add_644);
			t_sample gen_729 = gen_648;
			t_sample rsub_733 = (((int)1) - rsub_731);
			t_sample mul_735 = (m_history_29 * rsub_733);
			t_sample add_732 = (mul_343 + gen_730);
			t_sample tap_741 = m_delay_30.read_linear(add_732);
			t_sample mul_738 = (tap_741 * rsub_731);
			t_sample add_737 = (mul_738 + mul_735);
			t_sample mul_734 = (add_737 * gen_594);
			t_sample add_739 = (gen_300 + mul_734);
			t_sample gen_746 = add_739;
			t_sample history_736_next_745 = fixdenorm(add_737);
			t_sample rsub_748 = (((int)1) - rsub_731);
			t_sample mul_750 = (m_history_27 * rsub_748);
			t_sample add_747 = (mul_343 + gen_729);
			t_sample tap_756 = m_delay_28.read_linear(add_747);
			t_sample mul_753 = (tap_756 * rsub_731);
			t_sample add_752 = (mul_753 + mul_750);
			t_sample mul_749 = (add_752 * gen_594);
			t_sample add_754 = (gen_300 + mul_749);
			t_sample gen_761 = add_754;
			t_sample history_751_next_760 = fixdenorm(add_752);
			t_sample rsub_763 = (((int)1) - rsub_731);
			t_sample mul_765 = (m_history_25 * rsub_763);
			t_sample add_762 = (mul_343 + gen_728);
			t_sample tap_771 = m_delay_26.read_linear(add_762);
			t_sample mul_768 = (tap_771 * rsub_731);
			t_sample add_767 = (mul_768 + mul_765);
			t_sample mul_764 = (add_767 * gen_594);
			t_sample add_769 = (gen_300 + mul_764);
			t_sample gen_776 = add_769;
			t_sample history_766_next_775 = fixdenorm(add_767);
			t_sample rsub_778 = (((int)1) - rsub_731);
			t_sample mul_780 = (m_history_23 * rsub_778);
			t_sample add_777 = (mul_343 + gen_727);
			t_sample tap_786 = m_delay_24.read_linear(add_777);
			t_sample mul_783 = (tap_786 * rsub_731);
			t_sample add_782 = (mul_783 + mul_780);
			t_sample mul_779 = (add_782 * gen_594);
			t_sample add_784 = (gen_300 + mul_779);
			t_sample gen_791 = add_784;
			t_sample history_781_next_790 = fixdenorm(add_782);
			t_sample rsub_793 = (((int)1) - rsub_731);
			t_sample mul_795 = (m_history_21 * rsub_793);
			t_sample add_792 = (mul_343 + gen_726);
			t_sample tap_801 = m_delay_22.read_linear(add_792);
			t_sample mul_798 = (tap_801 * rsub_731);
			t_sample add_797 = (mul_798 + mul_795);
			t_sample mul_794 = (add_797 * gen_594);
			t_sample add_799 = (gen_300 + mul_794);
			t_sample gen_806 = add_799;
			t_sample history_796_next_805 = fixdenorm(add_797);
			t_sample rsub_808 = (((int)1) - rsub_731);
			t_sample mul_810 = (m_history_19 * rsub_808);
			t_sample add_807 = (mul_343 + gen_725);
			t_sample tap_816 = m_delay_20.read_linear(add_807);
			t_sample mul_813 = (tap_816 * rsub_731);
			t_sample add_812 = (mul_813 + mul_810);
			t_sample mul_809 = (add_812 * gen_594);
			t_sample add_814 = (gen_300 + mul_809);
			t_sample gen_821 = add_814;
			t_sample history_811_next_820 = fixdenorm(add_812);
			t_sample rsub_823 = (((int)1) - rsub_731);
			t_sample mul_825 = (m_history_17 * rsub_823);
			t_sample add_822 = (mul_343 + gen_724);
			t_sample tap_831 = m_delay_18.read_linear(add_822);
			t_sample mul_828 = (tap_831 * rsub_731);
			t_sample add_827 = (mul_828 + mul_825);
			t_sample mul_824 = (add_827 * gen_594);
			t_sample add_829 = (gen_300 + mul_824);
			t_sample gen_836 = add_829;
			t_sample history_826_next_835 = fixdenorm(add_827);
			t_sample rsub_838 = (((int)1) - rsub_731);
			t_sample mul_840 = (m_history_15 * rsub_838);
			t_sample add_837 = (mul_343 + gen_723);
			t_sample tap_846 = m_delay_16.read_linear(add_837);
			t_sample mul_843 = (tap_846 * rsub_731);
			t_sample add_842 = (mul_843 + mul_840);
			t_sample mul_839 = (add_842 * gen_594);
			t_sample add_844 = (gen_300 + mul_839);
			t_sample gen_851 = add_844;
			t_sample history_841_next_850 = fixdenorm(add_842);
			t_sample mul_852 = ((((((((gen_851 + gen_836) + gen_821) + gen_806) + gen_791) + gen_776) + gen_761) + gen_746) * ((t_sample)0.125));
			t_sample gen_854 = mul_852;
			t_sample mul_406 = (gen_854 * ((t_sample)-0.5));
			t_sample mul_396 = (div_397 * gen_342);
			t_sample mul_398 = (((int)255) * mul_396);
			t_sample add_400 = (((int)0) + mul_398);
			t_sample tap_408 = m_delay_14.read_linear(add_400);
			t_sample tap_403 = m_delay_13.read_linear(add_400);
			t_sample mul_401 = (tap_403 * ((t_sample)0.5));
			t_sample add_404 = (mul_406 + (tap_408 + mul_401));
			t_sample gen_412 = add_404;
			t_sample mul_389 = (gen_412 * ((t_sample)-0.5));
			t_sample mul_379 = (div_380 * gen_342);
			t_sample mul_381 = (((int)556) * mul_379);
			t_sample add_383 = (((int)0) + mul_381);
			t_sample tap_391 = m_delay_12.read_linear(add_383);
			t_sample tap_386 = m_delay_11.read_linear(add_383);
			t_sample mul_384 = (tap_386 * ((t_sample)0.5));
			t_sample add_387 = (mul_389 + (tap_391 + mul_384));
			t_sample gen_395 = add_387;
			t_sample mul_372 = (gen_395 * ((t_sample)-0.5));
			t_sample mul_362 = (div_363 * gen_342);
			t_sample mul_364 = (((int)441) * mul_362);
			t_sample add_366 = (((int)0) + mul_364);
			t_sample tap_374 = m_delay_10.read_linear(add_366);
			t_sample tap_369 = m_delay_9.read_linear(add_366);
			t_sample mul_367 = (tap_369 * ((t_sample)0.5));
			t_sample add_370 = (mul_372 + (tap_374 + mul_367));
			t_sample gen_378 = add_370;
			t_sample mul_355 = (gen_378 * ((t_sample)-0.5));
			t_sample mul_345 = (div_346 * gen_342);
			t_sample mul_347 = (((int)341) * mul_345);
			t_sample add_349 = (((int)0) + mul_347);
			t_sample tap_357 = m_delay_8.read_linear(add_349);
			t_sample tap_352 = m_delay_7.read_linear(add_349);
			t_sample mul_350 = (tap_352 * ((t_sample)0.5));
			t_sample add_353 = (mul_355 + (tap_357 + mul_350));
			t_sample gen_361 = add_353;
			t_sample gen_414 = gen_361;
			t_sample add_607 = (gen_486 + gen_414);
			t_sample mul_605 = (add_607 * sqrt_603);
			t_sample sub_606 = (gen_486 - gen_414);
			t_sample mul_604 = (sub_606 * sqrt_602);
			t_sample add_601 = (mul_605 + mul_604);
			t_sample mul_596 = (add_601 * scale_597);
			t_sample sub_600 = (mul_605 - mul_604);
			t_sample mul_595 = (sub_600 * scale_597);
			t_sample return_191;
			t_sample return_192;
			eq3bandas_d_d_d_d_d_d_d_d_i(mul_596, mul_595, gen_334, gen_326, gen_318, gen_528, gen_520, gen_512, ((int)1), return_191, return_192);
			t_sample expr_569 = return_191;
			t_sample expr_570 = return_192;
			t_sample gen_571 = expr_569;
			t_sample gen_572 = expr_570;
			t_sample mix_9072 = (mul_596 + (gen_308 * (gen_571 - mul_596)));
			t_sample mix_310 = mix_9072;
			t_sample mix_9073 = (mul_595 + (gen_308 * (gen_572 - mul_595)));
			t_sample mix_309 = mix_9073;
			t_sample dbtoa_87 = dbtoa(gen_44);
			t_sample mstosamps_131 = (gen_54 * (samplerate * 0.001));
			t_sample mstosamps_130 = (gen_62 * (samplerate * 0.001));
			t_sample rdiv_137 = safediv(((int)1), gen_70);
			t_sample rsub_136 = (((int)1) - rdiv_137);
			t_sample mul_7974 = (mix_310 * ((t_sample)0.25));
			t_sample add_9075 = (mul_7974 + mul_574);
			t_sample mix_9074 = (mix_310 + (m_x_PUMP_116 * (add_9075 - mix_310)));
			t_sample mix_4257 = mix_9074;
			t_sample fixdenorm_2357 = fixdenorm(m_history_5);
			t_sample tap_2129 = m_delay_6.read_step(((int)300));
			t_sample mul_142 = (mix_4257 * mix_4257);
			t_sample add_146 = (fixdenorm_2357 + mul_142);
			t_sample sub_145 = (add_146 - tap_2129);
			t_sample div_143 = (sub_145 * ((t_sample)0.0033333333333333));
			t_sample max_2144 = ((div_143 < ((int)0)) ? ((int)0) : div_143);
			t_sample sqrt_141 = sqrt(max_2144);
			t_sample gen_2489 = sqrt_141;
			t_sample history_144_next_2488 = fixdenorm(sub_145);
			t_sample atodb_140 = atodb(gen_2489);
			t_sample max_91 = ((atodb_140 < maxb_193) ? maxb_193 : atodb_140);
			int gt_139 = (max_91 > gen_78);
			t_sample mul_101 = (m_history_4 * ((t_sample)0.999));
			t_sample mul_100 = (gt_139 * ((t_sample)0.001));
			t_sample add_103 = (mul_100 + mul_101);
			t_sample gen_107 = add_103;
			t_sample history_102_next_106 = fixdenorm(add_103);
			t_sample sub_138 = (gen_78 - max_91);
			t_sample mul_135 = (sub_138 * rsub_136);
			t_sample dbtoa_133 = dbtoa(mul_135);
			t_sample orange_9078 = (dbtoa_133 - ((int)1));
			t_sample sub_9079 = (gen_107 - ((int)0));
			t_sample scale_9076 = ((safepow((sub_9079 * ((t_sample)1)), ((int)1)) * orange_9078) + ((int)1));
			t_sample iup_195 = (1 / maximum(1, abs(mstosamps_131)));
			t_sample idown_196 = (1 / maximum(1, abs(mstosamps_130)));
			__m_slide_194 = fixdenorm((__m_slide_194 + (((scale_9076 > __m_slide_194) ? iup_195 : idown_196) * (scale_9076 - __m_slide_194))));
			t_sample slide_132 = __m_slide_194;
			t_sample mul_155 = (mix_310 * slide_132);
			t_sample mul_89 = (mul_155 * dbtoa_87);
			t_sample mul_8038 = (mix_309 * ((t_sample)0.25));
			t_sample add_9081 = (mul_8038 + mul_573);
			t_sample mix_9080 = (mix_309 + (m_x_PUMP_116 * (add_9081 - mix_309)));
			t_sample mix_4555 = mix_9080;
			t_sample tap_124 = m_delay_3.read_step(((int)300));
			t_sample mul_117 = (mix_4555 * mix_4555);
			t_sample add_121 = (m_history_2 + mul_117);
			t_sample sub_120 = (add_121 - tap_124);
			t_sample div_118 = (sub_120 * ((t_sample)0.0033333333333333));
			t_sample sqrt_116 = sqrt(div_118);
			t_sample gen_129 = sqrt_116;
			t_sample history_119_next_128 = fixdenorm(sub_120);
			t_sample atodb_115 = atodb(gen_129);
			t_sample max_90 = ((atodb_115 < maxb_197) ? maxb_197 : atodb_115);
			int gt_114 = (max_90 > gen_78);
			t_sample mul_93 = (m_history_1 * ((t_sample)0.999));
			t_sample mul_92 = (gt_114 * ((t_sample)0.001));
			t_sample add_95 = (mul_92 + mul_93);
			t_sample gen_99 = add_95;
			t_sample history_94_next_98 = fixdenorm(add_95);
			t_sample sub_113 = (gen_78 - max_90);
			t_sample mul_112 = (sub_113 * rsub_136);
			t_sample dbtoa_110 = dbtoa(mul_112);
			t_sample orange_9084 = (dbtoa_110 - ((int)1));
			t_sample sub_9085 = (gen_99 - ((int)0));
			t_sample scale_9082 = ((safepow((sub_9085 * ((t_sample)1)), ((int)1)) * orange_9084) + ((int)1));
			t_sample iup_199 = (1 / maximum(1, abs(mstosamps_131)));
			t_sample idown_200 = (1 / maximum(1, abs(mstosamps_130)));
			__m_slide_198 = fixdenorm((__m_slide_198 + (((scale_9082 > __m_slide_198) ? iup_199 : idown_200) * (scale_9082 - __m_slide_198))));
			t_sample slide_109 = __m_slide_198;
			t_sample mul_108 = (mix_309 * slide_109);
			t_sample mul_88 = (mul_108 * dbtoa_87);
			t_sample mix_9086 = (mix_310 + (gen_86 * (mul_89 - mix_310)));
			t_sample mix_9087 = (mix_309 + (gen_86 * (mul_88 - mix_309)));
			t_sample mul_504 = (mix_9086 * gen_502);
			t_sample mix_9088 = (mix_9064 + (gen_494 * (mul_504 - mix_9064)));
			t_sample mix_9089 = (mix_9088 + (gen_16 * (in1 - mix_9088)));
			t_sample dcblock_46 = __m_dcblock_201(mix_9089);
			t_sample out1 = dcblock_46;
			t_sample mul_503 = (mix_9087 * gen_502);
			t_sample mix_9090 = (mix_9065 + (gen_494 * (mul_503 - mix_9065)));
			t_sample mix_9091 = (mix_9090 + (gen_16 * (in2 - mix_9090)));
			t_sample dcblock_45 = __m_dcblock_202(mix_9091);
			t_sample out2 = dcblock_45;
			m_history_137 = history_11_next_15;
			m_history_110 = history_611_next_615;
			m_history_109 = history_489_next_493;
			m_history_108 = history_81_next_85;
			m_history_107 = history_73_next_77;
			m_history_106 = history_65_next_69;
			m_history_105 = history_57_next_61;
			m_history_104 = history_49_next_53;
			m_history_103 = history_39_next_43;
			m_history_102 = history_497_next_501;
			m_history_101 = history_303_next_307;
			m_history_100 = history_329_next_333;
			m_history_99 = history_321_next_325;
			m_history_98 = history_313_next_317;
			m_history_97 = history_523_next_527;
			m_history_96 = history_515_next_519;
			m_history_95 = history_507_next_511;
			m_history_94 = history_619_next_623;
			m_history_93 = history_337_next_341;
			m_history_92 = history_29_next_33;
			m_history_91 = history_539_next_543;
			m_history_90 = history_531_next_535;
			m_history_89 = history_3_next_7;
			m_history_88 = history_581_next_585;
			m_history_87 = history_224_next_249;
			m_history_78 = history_185_next_205;
			m_history_77 = history_175_next_206;
			m_history_76 = history_189_next_207;
			m_history_75 = history_181_next_208;
			m_history_74 = history_191_next_209;
			m_history_73 = history_177_next_210;
			m_history_72 = history_187_next_211;
			m_history_79 = history_179_next_204;
			m_history_86 = history_230_next_250;
			m_history_85 = history_220_next_251;
			m_history_84 = history_234_next_252;
			m_history_83 = history_226_next_253;
			m_history_82 = history_236_next_254;
			m_history_81 = history_232_next_255;
			m_history_80 = history_222_next_256;
			m_history_71 = history_589_next_593;
			m_history_70 = history_889_next_893;
			m_history_47 = history_1063_next_1072;
			m_delay_48.write(add_1066);
			m_history_49 = history_1048_next_1057;
			m_delay_50.write(add_1051);
			m_history_51 = history_1033_next_1042;
			m_delay_52.write(add_1036);
			m_history_53 = history_1018_next_1027;
			m_delay_54.write(add_1021);
			m_history_55 = history_1003_next_1012;
			m_delay_56.write(add_1006);
			m_history_57 = history_988_next_997;
			m_delay_58.write(add_991);
			m_history_59 = history_973_next_982;
			m_delay_60.write(add_976);
			m_history_61 = history_958_next_967;
			m_delay_62.write(add_961);
			m_history_69 = history_913_next_917;
			m_history_68 = history_905_next_909;
			m_history_67 = history_873_next_877;
			m_history_66 = history_857_next_861;
			m_history_65 = history_897_next_901;
			m_history_64 = history_865_next_869;
			m_history_63 = history_881_next_885;
			m_delay_46.write(gen_1076);
			m_delay_39.write(add_425);
			m_delay_40.write(gen_450);
			m_delay_41.write(add_442);
			m_delay_42.write(gen_467);
			m_delay_43.write(add_459);
			m_delay_44.write(gen_484);
			m_delay_45.write(add_476);
			m_history_38 = history_683_next_687;
			m_history_15 = history_841_next_850;
			m_delay_16.write(add_844);
			m_history_17 = history_826_next_835;
			m_delay_18.write(add_829);
			m_history_19 = history_811_next_820;
			m_delay_20.write(add_814);
			m_history_21 = history_796_next_805;
			m_delay_22.write(add_799);
			m_history_23 = history_781_next_790;
			m_delay_24.write(add_784);
			m_history_25 = history_766_next_775;
			m_delay_26.write(add_769);
			m_history_27 = history_751_next_760;
			m_delay_28.write(add_754);
			m_history_29 = history_736_next_745;
			m_delay_30.write(add_739);
			m_history_37 = history_635_next_639;
			m_history_36 = history_675_next_679;
			m_history_35 = history_667_next_671;
			m_history_34 = history_651_next_655;
			m_history_33 = history_691_next_695;
			m_history_32 = history_659_next_663;
			m_history_31 = history_643_next_647;
			m_delay_14.write(gen_854);
			m_delay_7.write(add_353);
			m_delay_8.write(gen_378);
			m_delay_9.write(add_370);
			m_delay_10.write(gen_395);
			m_delay_11.write(add_387);
			m_delay_12.write(gen_412);
			m_delay_13.write(add_404);
			m_delay_6.write(mul_142);
			m_history_5 = history_144_next_2488;
			m_history_4 = history_102_next_106;
			m_delay_3.write(mul_117);
			m_history_2 = history_119_next_128;
			m_history_1 = history_94_next_98;
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
	inline void set_i_PEAKGAIN(t_param _value) {
		m_i_PEAKGAIN_111 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_y_FILTERS(t_param _value) {
		m_y_FILTERS_112 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_e_SIZE(t_param _value) {
		m_e_SIZE_113 = (_value < 0.1 ? 0.1 : (_value > 4 ? 4 : _value));
	};
	inline void set_o_PEAKFREQ(t_param _value) {
		m_o_PEAKFREQ_114 = (_value < 500 ? 500 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_m_OUTPUT(t_param _value) {
		m_m_OUTPUT_115 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_x_PUMP(t_param _value) {
		m_x_PUMP_116 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_s_THD(t_param _value) {
		m_s_THD_117 = (_value < -60 ? -60 : (_value > 0 ? 0 : _value));
	};
	inline void set_u_ATK(t_param _value) {
		m_u_ATK_118 = (_value < 1 ? 1 : (_value > 750 ? 750 : _value));
	};
	inline void set_d_DAMP(t_param _value) {
		m_d_DAMP_119 = (_value < 0.1 ? 0.1 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_v_REL(t_param _value) {
		m_v_REL_120 = (_value < 15 ? 15 : (_value > 2000 ? 2000 : _value));
	};
	inline void set_n_LOWFREQ(t_param _value) {
		m_n_LOWFREQ_121 = (_value < 20 ? 20 : (_value > 500 ? 500 : _value));
	};
	inline void set_p_HIFREQ(t_param _value) {
		m_p_HIFREQ_122 = (_value < 2500 ? 2500 : (_value > 15000 ? 15000 : _value));
	};
	inline void set_f_ST(t_param _value) {
		m_f_ST_123 = (_value < 0 ? 0 : (_value > 0.9 ? 0.9 : _value));
	};
	inline void set_j_HIGAIN(t_param _value) {
		m_j_HIGAIN_124 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_c_REFLECT(t_param _value) {
		m_c_REFLECT_125 = (_value < 0.1 ? 0.1 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_b_DRYWET(t_param _value) {
		m_b_DRYWET_126 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_z_BYPASS(t_param _value) {
		m_z_BYPASS_127 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_g_FREEZE(t_param _value) {
		m_g_FREEZE_128 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_t_RATIO(t_param _value) {
		m_t_RATIO_129 = (_value < 1 ? 1 : (_value > 20 ? 20 : _value));
	};
	inline void set_r_ONOFFCOMP(t_param _value) {
		m_r_ONOFFCOMP_130 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_w_MAKEUP(t_param _value) {
		m_w_MAKEUP_131 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void set_l_HPF(t_param _value) {
		m_l_HPF_132 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_k_LPF(t_param _value) {
		m_k_LPF_133 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_a_INPUT(t_param _value) {
		m_a_INPUT_134 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_q_ONOFFEQ(t_param _value) {
		m_q_ONOFFEQ_135 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_h_LOWGAIN(t_param _value) {
		m_h_LOWGAIN_136 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_150;
		t_sample return_151;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_150, return_151);
		t_sample x_563 = return_150;
		sigR = return_151;
		t_sample return_175;
		t_sample return_176;
		peak_d_d_d_d_i(x_563, sigR, pf, pg, bw, return_175, return_176);
		t_sample x_566 = return_175;
		sigR = return_176;
		t_sample return_189;
		t_sample return_190;
		hishelf_d_d_d_d(x_566, sigR, hf, hg, return_189, return_190);
		t_sample x_568 = return_189;
		sigR = return_190;
		out1 = x_568;
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
		t_sample output_564 = (m_a_154 * ((output - (m_a_153 * m_z_167)) - (m_a_152 * m_z_166)));
		m_z_166 = m_z_167;
		m_z_167 = output_564;
		t_sample output_565 = (input + (output_564 * m_d_157));
		return output_565;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_170(t_sample input, t_sample m_w_161, t_sample m_d_157, t_sample m_a_154, t_sample m_a_153, t_sample m_a_152) {
		t_sample output = ((input - m_z_173) * m_w_161);
		m_z_173 = m_z_174;
		m_z_174 = input;
		t_sample output_564 = (m_a_154 * ((output - (m_a_153 * m_z_172)) - (m_a_152 * m_z_171)));
		m_z_171 = m_z_172;
		m_z_172 = output_564;
		t_sample output_565 = (input + (output_564 * m_d_157));
		return output_565;
		
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
		t_sample output_567 = ((output * m_b_180) + input);
		return output_567;
		
	};
	inline t_sample hishelfCore_d_d_d_d_187(t_sample input, t_sample m_a_178, t_sample m_a_177, t_sample m_b_180) {
		t_sample x = (m_a_178 * (input - (m_a_177 * m_z_188)));
		t_sample output = (x - m_z_188);
		m_z_188 = x;
		t_sample output_567 = ((output * m_b_180) + input);
		return output_567;
		
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
		case 0: *value = self->m_a_INPUT_134; break;
		case 1: *value = self->m_b_DRYWET_126; break;
		case 2: *value = self->m_c_REFLECT_125; break;
		case 3: *value = self->m_d_DAMP_119; break;
		case 4: *value = self->m_e_SIZE_113; break;
		case 5: *value = self->m_f_ST_123; break;
		case 6: *value = self->m_g_FREEZE_128; break;
		case 7: *value = self->m_h_LOWGAIN_136; break;
		case 8: *value = self->m_i_PEAKGAIN_111; break;
		case 9: *value = self->m_j_HIGAIN_124; break;
		case 10: *value = self->m_k_LPF_133; break;
		case 11: *value = self->m_l_HPF_132; break;
		case 12: *value = self->m_m_OUTPUT_115; break;
		case 13: *value = self->m_n_LOWFREQ_121; break;
		case 14: *value = self->m_o_PEAKFREQ_114; break;
		case 15: *value = self->m_p_HIFREQ_122; break;
		case 16: *value = self->m_q_ONOFFEQ_135; break;
		case 17: *value = self->m_r_ONOFFCOMP_130; break;
		case 18: *value = self->m_s_THD_117; break;
		case 19: *value = self->m_t_RATIO_129; break;
		case 20: *value = self->m_u_ATK_118; break;
		case 21: *value = self->m_v_REL_120; break;
		case 22: *value = self->m_w_MAKEUP_131; break;
		case 23: *value = self->m_x_PUMP_116; break;
		case 24: *value = self->m_y_FILTERS_112; break;
		case 25: *value = self->m_z_BYPASS_127; break;
		
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
	// initialize parameter 1 ("m_b_DRYWET_126")
	pi = self->__commonstate.params + 1;
	pi->name = "b_DRYWET";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_DRYWET_126;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_REFLECT_125")
	pi = self->__commonstate.params + 2;
	pi->name = "c_REFLECT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_REFLECT_125;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.95;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_DAMP_119")
	pi = self->__commonstate.params + 3;
	pi->name = "d_DAMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_DAMP_119;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.95;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_SIZE_113")
	pi = self->__commonstate.params + 4;
	pi->name = "e_SIZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_SIZE_113;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_ST_123")
	pi = self->__commonstate.params + 5;
	pi->name = "f_ST";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_ST_123;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.9;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_FREEZE_128")
	pi = self->__commonstate.params + 6;
	pi->name = "g_FREEZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_FREEZE_128;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_LOWGAIN_136")
	pi = self->__commonstate.params + 7;
	pi->name = "h_LOWGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_LOWGAIN_136;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_PEAKGAIN_111")
	pi = self->__commonstate.params + 8;
	pi->name = "i_PEAKGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_PEAKGAIN_111;
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
	// initialize parameter 12 ("m_m_OUTPUT_115")
	pi = self->__commonstate.params + 12;
	pi->name = "m_OUTPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_OUTPUT_115;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -12;
	pi->outputmax = 12;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_LOWFREQ_121")
	pi = self->__commonstate.params + 13;
	pi->name = "n_LOWFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_LOWFREQ_121;
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
	// initialize parameter 16 ("m_q_ONOFFEQ_135")
	pi = self->__commonstate.params + 16;
	pi->name = "q_ONOFFEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_ONOFFEQ_135;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 17 ("m_r_ONOFFCOMP_130")
	pi = self->__commonstate.params + 17;
	pi->name = "r_ONOFFCOMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_ONOFFCOMP_130;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 18 ("m_s_THD_117")
	pi = self->__commonstate.params + 18;
	pi->name = "s_THD";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_THD_117;
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
	// initialize parameter 20 ("m_u_ATK_118")
	pi = self->__commonstate.params + 20;
	pi->name = "u_ATK";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_ATK_118;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 750;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_REL_120")
	pi = self->__commonstate.params + 21;
	pi->name = "v_REL";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_REL_120;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 15;
	pi->outputmax = 2000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_MAKEUP_131")
	pi = self->__commonstate.params + 22;
	pi->name = "w_MAKEUP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_MAKEUP_131;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -6;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 23 ("m_x_PUMP_116")
	pi = self->__commonstate.params + 23;
	pi->name = "x_PUMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_x_PUMP_116;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 24 ("m_y_FILTERS_112")
	pi = self->__commonstate.params + 24;
	pi->name = "y_FILTERS";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_y_FILTERS_112;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 25 ("m_z_BYPASS_127")
	pi = self->__commonstate.params + 25;
	pi->name = "z_BYPASS";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_z_BYPASS_127;
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
