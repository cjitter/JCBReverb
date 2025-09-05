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
	Change __m_change_141;
	Change __m_change_158;
	Change __m_change_140;
	Change __m_change_157;
	Change __m_change_159;
	Change __m_change_179;
	Change __m_change_178;
	DCBlock __m_dcblock_196;
	DCBlock __m_dcblock_197;
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
	t_sample m_p_HIFREQ_132;
	t_sample m_a_134;
	t_sample m_s_THD_131;
	t_sample m_h_LOWGAIN_129;
	t_sample m_j_HIGAIN_130;
	t_sample m_o_PEAKFREQ_128;
	t_sample m_w_MAKEUP_127;
	t_sample m_a_135;
	t_sample m_b_137;
	t_sample m_history_5;
	t_sample m_w_136;
	t_sample m_history_15;
	t_sample m_f_138;
	t_sample m_b_139;
	t_sample m_u_ATK_126;
	t_sample m_k_LPF_125;
	t_sample m_e_SIZE_124;
	t_sample m_b_DRYWET_114;
	t_sample m_r_ONOFFCOMP_115;
	t_sample m_v_REL_116;
	t_sample m_n_LOWFREQ_113;
	t_sample m_i_PEAKGAIN_111;
	t_sample m_t_RATIO_112;
	t_sample m_z_142;
	t_sample m_m_OUTPUT_117;
	t_sample m_a_INPUT_119;
	t_sample m_l_HPF_123;
	t_sample m_d_DAMP_118;
	t_sample m_g_FREEZE_122;
	t_sample m_c_REFLECT_120;
	t_sample m_f_ST_121;
	t_sample m_z_144;
	t_sample m_a_147;
	t_sample m_a_148;
	t_sample m_a_173;
	t_sample m_w_174;
	t_sample m_b_175;
	t_sample m_a_172;
	t_sample m_z_168;
	t_sample m_z_169;
	t_sample m_z_167;
	t_sample m_f_176;
	t_sample samplerate;
	t_sample __m_slide_193;
	t_sample m_b_177;
	t_sample __m_slide_189;
	t_sample m_z_181;
	t_sample m_z_183;
	t_sample m_q_ONOFFEQ_110;
	t_sample m_z_166;
	t_sample m_z_163;
	t_sample m_d_152;
	t_sample m_d_153;
	t_sample m_d_154;
	t_sample m_wq_151;
	t_sample m_a_149;
	t_sample m_w_150;
	t_sample m_z_164;
	t_sample m_b_155;
	t_sample m_history_4;
	t_sample m_z_162;
	t_sample m_w_156;
	t_sample m_z_161;
	t_sample m_history_2;
	t_sample m_history_1;
	t_sample m_history_38;
	t_sample m_history_109;
	t_sample m_history_107;
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
	t_sample m_history_67;
	t_sample m_history_71;
	t_sample m_history_69;
	t_sample m_history_70;
	t_sample m_history_73;
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
	t_sample m_history_108;
	t_sample m_history_74;
	t_sample m_history_76;
	t_sample m_history_97;
	t_sample m_history_98;
	t_sample m_history_99;
	t_sample m_history_96;
	t_sample m_history_94;
	t_sample m_history_95;
	t_sample m_history_93;
	t_sample m_history_100;
	t_sample m_history_102;
	t_sample m_history_106;
	t_sample m_history_101;
	t_sample m_history_105;
	t_sample m_history_103;
	t_sample m_history_104;
	t_sample m_history_75;
	t_sample m_history_92;
	t_sample m_history_90;
	t_sample m_history_80;
	t_sample m_history_81;
	t_sample m_history_82;
	t_sample m_history_79;
	t_sample m_history_77;
	t_sample m_history_78;
	t_sample m_history_91;
	t_sample m_history_83;
	t_sample m_history_85;
	t_sample m_history_89;
	t_sample m_history_84;
	t_sample m_history_88;
	t_sample m_history_86;
	t_sample m_history_17;
	t_sample m_history_87;
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
		m_q_ONOFFEQ_110 = 0;
		m_i_PEAKGAIN_111 = 0;
		m_t_RATIO_112 = 2;
		m_n_LOWFREQ_113 = 500;
		m_b_DRYWET_114 = 0.33;
		m_r_ONOFFCOMP_115 = 0;
		m_v_REL_116 = 100;
		m_m_OUTPUT_117 = 0;
		m_d_DAMP_118 = 0.8;
		m_a_INPUT_119 = 0;
		m_c_REFLECT_120 = 0.86;
		m_f_ST_121 = 0.5;
		m_g_FREEZE_122 = 0;
		m_l_HPF_123 = 20;
		m_e_SIZE_124 = 1;
		m_k_LPF_125 = 20000;
		m_u_ATK_126 = 10;
		m_w_MAKEUP_127 = 0;
		m_o_PEAKFREQ_128 = 800;
		m_h_LOWGAIN_129 = 0;
		m_j_HIGAIN_130 = 0;
		m_s_THD_131 = -12;
		m_p_HIFREQ_132 = 2000;
		m_a_134 = ((int)0);
		m_a_135 = ((int)0);
		m_w_136 = ((int)0);
		m_b_137 = ((int)0);
		m_f_138 = ((int)0);
		m_b_139 = ((int)0);
		__m_change_140.reset(0);
		__m_change_141.reset(0);
		m_z_142 = ((int)0);
		m_z_144 = ((int)0);
		m_a_147 = ((int)0);
		m_a_148 = ((int)0);
		m_a_149 = ((int)0);
		m_w_150 = ((int)0);
		m_wq_151 = ((int)0);
		m_d_152 = ((int)0);
		m_d_153 = ((int)0);
		m_d_154 = ((int)0);
		m_b_155 = ((int)0);
		m_w_156 = ((int)0);
		__m_change_157.reset(0);
		__m_change_158.reset(0);
		__m_change_159.reset(0);
		m_z_161 = ((int)0);
		m_z_162 = ((int)0);
		m_z_163 = ((int)0);
		m_z_164 = ((int)0);
		m_z_166 = ((int)0);
		m_z_167 = ((int)0);
		m_z_168 = ((int)0);
		m_z_169 = ((int)0);
		m_a_172 = ((int)0);
		m_a_173 = ((int)0);
		m_w_174 = ((int)0);
		m_b_175 = ((int)0);
		m_f_176 = ((int)0);
		m_b_177 = ((int)0);
		__m_change_178.reset(0);
		__m_change_179.reset(0);
		m_z_181 = ((int)0);
		m_z_183 = ((int)0);
		__m_slide_189 = 0;
		__m_slide_193 = 0;
		__m_dcblock_196.reset();
		__m_dcblock_197.reset();
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
		t_sample dbtoa_4065 = dbtoa(m_a_INPUT_119);
		t_sample mul_3484 = (dbtoa_4065 * ((t_sample)0.001));
		t_sample mul_3384 = (m_b_DRYWET_114 * ((t_sample)0.001));
		t_sample dbtoa_4066 = dbtoa(m_m_OUTPUT_117);
		t_sample mul_3396 = (dbtoa_4066 * ((t_sample)0.001));
		t_sample mul_3071 = (m_r_ONOFFCOMP_115 * ((t_sample)0.001));
		t_sample mul_3065 = (m_s_THD_131 * ((t_sample)0.001));
		t_sample mul_3059 = (m_t_RATIO_112 * ((t_sample)0.001));
		t_sample mul_3053 = (m_u_ATK_126 * ((t_sample)0.001));
		t_sample mul_3047 = (m_v_REL_116 * ((t_sample)0.001));
		t_sample mul_3039 = (m_w_MAKEUP_127 * ((t_sample)0.001));
		int gte_3503 = (m_g_FREEZE_122 >= ((t_sample)0.5));
		t_sample mul_3390 = (gte_3503 * ((t_sample)0.001));
		t_sample mul_3234 = (m_q_ONOFFEQ_110 * ((t_sample)0.001));
		t_sample mul_3254 = (m_n_LOWFREQ_113 * ((t_sample)0.001));
		t_sample mul_3248 = (m_o_PEAKFREQ_128 * ((t_sample)0.001));
		t_sample mul_3242 = (m_p_HIFREQ_132 * ((t_sample)0.001));
		t_sample mul_3416 = (m_h_LOWGAIN_129 * ((t_sample)0.001));
		t_sample mul_3410 = (m_i_PEAKGAIN_111 * ((t_sample)0.001));
		t_sample mul_3404 = (m_j_HIGAIN_130 * ((t_sample)0.001));
		t_sample mul_3490 = (m_f_ST_121 * ((t_sample)0.001));
		t_sample mul_3260 = (m_e_SIZE_124 * ((t_sample)0.001));
		t_sample rsub_3852 = (((int)1) - m_d_DAMP_118);
		t_sample mul_3428 = (m_k_LPF_125 * ((t_sample)0.001));
		t_sample mul_3422 = (m_l_HPF_123 * ((t_sample)0.001));
		int rsub_3502 = (((int)1) - gte_3503);
		t_sample mul_3458 = (rsub_3502 * ((t_sample)0.001));
		t_sample rsub_3499 = (((int)1) - m_c_REFLECT_120);
		int choice_133 = gte_3503;
		t_sample gate_3498 = ((choice_133 >= 1) ? rsub_3499 : 0);
		t_sample add_3500 = (m_c_REFLECT_120 + gate_3498);
		t_sample mul_3464 = (add_3500 * ((t_sample)0.001));
		t_sample rsub_3751 = (((int)1) - rsub_3852);
		t_sample div_3740 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_3837 = (((int)1) - rsub_3751);
		t_sample rsub_3825 = (((int)1) - rsub_3751);
		t_sample rsub_3813 = (((int)1) - rsub_3751);
		t_sample rsub_3801 = (((int)1) - rsub_3751);
		t_sample rsub_3789 = (((int)1) - rsub_3751);
		t_sample rsub_3777 = (((int)1) - rsub_3751);
		t_sample rsub_3765 = (((int)1) - rsub_3751);
		t_sample rsub_3753 = (((int)1) - rsub_3751);
		t_sample div_3370 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_3356 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_3342 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_3328 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_3578 = (((int)1) - rsub_3852);
		t_sample div_3567 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_3664 = (((int)1) - rsub_3578);
		t_sample rsub_3652 = (((int)1) - rsub_3578);
		t_sample rsub_3640 = (((int)1) - rsub_3578);
		t_sample rsub_3628 = (((int)1) - rsub_3578);
		t_sample rsub_3616 = (((int)1) - rsub_3578);
		t_sample rsub_3604 = (((int)1) - rsub_3578);
		t_sample rsub_3592 = (((int)1) - rsub_3578);
		t_sample rsub_3580 = (((int)1) - rsub_3578);
		t_sample div_3311 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_3297 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_3283 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_3269 = (samplerate * ((t_sample)2.2675736961451e-05));
		int maxb_188 = (-96);
		int maxb_192 = (-96);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_3485 = (m_history_109 * ((t_sample)0.999));
			t_sample add_3487 = (mul_3484 + mul_3485);
			t_sample gen_3489 = add_3487;
			t_sample history_3486_next_3488 = fixdenorm(add_3487);
			t_sample mul_3452 = (in2 * gen_3489);
			t_sample out4 = mul_3452;
			t_sample mul_3453 = (in1 * gen_3489);
			t_sample out3 = mul_3453;
			t_sample mul_3385 = (m_history_108 * ((t_sample)0.999));
			t_sample add_3387 = (mul_3384 + mul_3385);
			t_sample gen_3389 = add_3387;
			t_sample history_3386_next_3388 = fixdenorm(add_3387);
			t_sample mul_3397 = (m_history_107 * ((t_sample)0.999));
			t_sample add_3399 = (mul_3396 + mul_3397);
			t_sample gen_3401 = add_3399;
			t_sample history_3398_next_3400 = fixdenorm(add_3399);
			t_sample mul_3072 = (m_history_106 * ((t_sample)0.999));
			t_sample add_3074 = (mul_3071 + mul_3072);
			t_sample gen_3076 = add_3074;
			t_sample history_3073_next_3075 = fixdenorm(add_3074);
			t_sample mul_3066 = (m_history_105 * ((t_sample)0.999));
			t_sample add_3068 = (mul_3065 + mul_3066);
			t_sample gen_3070 = add_3068;
			t_sample history_3067_next_3069 = fixdenorm(add_3068);
			t_sample mul_3060 = (m_history_104 * ((t_sample)0.999));
			t_sample add_3062 = (mul_3059 + mul_3060);
			t_sample gen_3064 = add_3062;
			t_sample history_3061_next_3063 = fixdenorm(add_3062);
			t_sample mul_3054 = (m_history_103 * ((t_sample)0.999));
			t_sample add_3056 = (mul_3053 + mul_3054);
			t_sample gen_3058 = add_3056;
			t_sample history_3055_next_3057 = fixdenorm(add_3056);
			t_sample mul_3048 = (m_history_102 * ((t_sample)0.999));
			t_sample add_3050 = (mul_3047 + mul_3048);
			t_sample gen_3052 = add_3050;
			t_sample history_3049_next_3051 = fixdenorm(add_3050);
			t_sample mul_3040 = (m_history_101 * ((t_sample)0.999));
			t_sample add_3042 = (mul_3039 + mul_3040);
			t_sample gen_3044 = add_3042;
			t_sample history_3041_next_3043 = fixdenorm(add_3042);
			t_sample mul_3391 = (m_history_100 * ((t_sample)0.999));
			t_sample add_3393 = (mul_3390 + mul_3391);
			t_sample gen_3395 = add_3393;
			t_sample history_3392_next_3394 = fixdenorm(add_3393);
			t_sample mix_4067 = (mul_3453 + (gen_3395 * (((int)0) - mul_3453)));
			t_sample mix_4068 = (mul_3452 + (gen_3395 * (((int)0) - mul_3452)));
			t_sample mul_3235 = (m_history_99 * ((t_sample)0.999));
			t_sample add_3237 = (mul_3234 + mul_3235);
			t_sample gen_3239 = add_3237;
			t_sample history_3236_next_3238 = fixdenorm(add_3237);
			t_sample mul_3255 = (m_history_98 * ((t_sample)0.999));
			t_sample add_3257 = (mul_3254 + mul_3255);
			t_sample gen_3259 = add_3257;
			t_sample history_3256_next_3258 = fixdenorm(add_3257);
			t_sample mul_3249 = (m_history_97 * ((t_sample)0.999));
			t_sample add_3251 = (mul_3248 + mul_3249);
			t_sample gen_3253 = add_3251;
			t_sample history_3250_next_3252 = fixdenorm(add_3251);
			t_sample mul_3243 = (m_history_96 * ((t_sample)0.999));
			t_sample add_3245 = (mul_3242 + mul_3243);
			t_sample gen_3247 = add_3245;
			t_sample history_3244_next_3246 = fixdenorm(add_3245);
			t_sample mul_3417 = (m_history_95 * ((t_sample)0.999));
			t_sample add_3419 = (mul_3416 + mul_3417);
			t_sample gen_3421 = add_3419;
			t_sample history_3418_next_3420 = fixdenorm(add_3419);
			t_sample mul_3411 = (m_history_94 * ((t_sample)0.999));
			t_sample add_3413 = (mul_3410 + mul_3411);
			t_sample gen_3415 = add_3413;
			t_sample history_3412_next_3414 = fixdenorm(add_3413);
			t_sample mul_3405 = (m_history_93 * ((t_sample)0.999));
			t_sample add_3407 = (mul_3404 + mul_3405);
			t_sample gen_3409 = add_3407;
			t_sample history_3406_next_3408 = fixdenorm(add_3407);
			t_sample mul_3491 = (m_history_92 * ((t_sample)0.999));
			t_sample add_3493 = (mul_3490 + mul_3491);
			t_sample gen_3495 = add_3493;
			t_sample history_3492_next_3494 = fixdenorm(add_3493);
			t_sample sub_4072 = (gen_3495 - ((int)0));
			t_sample scale_4069 = ((safepow((sub_4072 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_3472 = scale_4069;
			t_sample sqrt_3477 = sqrt(gen_3495);
			t_sample rsub_3496 = (((int)1) - gen_3495);
			t_sample sqrt_3478 = sqrt(rsub_3496);
			t_sample mul_3261 = (m_history_91 * ((t_sample)0.999));
			t_sample add_3263 = (mul_3260 + mul_3261);
			t_sample gen_3265 = add_3263;
			t_sample history_3262_next_3264 = fixdenorm(add_3263);
			t_sample mul_3429 = (m_history_90 * ((t_sample)0.999));
			t_sample add_3431 = (mul_3428 + mul_3429);
			t_sample gen_3433 = add_3431;
			t_sample history_3430_next_3432 = fixdenorm(add_3431);
			t_sample mul_3423 = (m_history_89 * ((t_sample)0.999));
			t_sample add_3425 = (mul_3422 + mul_3423);
			t_sample gen_3427 = add_3425;
			t_sample history_3424_next_3426 = fixdenorm(add_3425);
			t_sample mul_3266 = (((int)23) * gen_3265);
			t_sample mul_3459 = (m_history_88 * ((t_sample)0.999));
			t_sample add_3461 = (mul_3458 + mul_3459);
			t_sample gen_3463 = add_3461;
			t_sample history_3460_next_3462 = fixdenorm(add_3461);
			t_sample mul_3501 = (mul_3453 * gen_3463);
			t_sample mul_3483 = (mul_3452 * gen_3463);
			t_sample omega = safediv((gen_3427 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) + cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((-(((int)1) + cs)) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_3213 = a2;
			t_sample expr_3214 = a1;
			t_sample expr_3215 = a2;
			t_sample expr_3216 = b1;
			t_sample expr_3217 = b2;
			t_sample omega_3225 = safediv((gen_3433 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_3223 = sin(omega_3225);
			t_sample cs_3230 = cos(omega_3225);
			t_sample alpha_3231 = ((sn_3223 * ((t_sample)0.5)) * ((int)1));
			t_sample b_3228 = safediv(((int)1), (((int)1) + alpha_3231));
			t_sample a_3229 = (((((int)1) - cs_3230) * ((t_sample)0.5)) * b_3228);
			t_sample a_3226 = ((((int)1) - cs_3230) * b_3228);
			t_sample b_3224 = ((((int)-2) * cs_3230) * b_3228);
			t_sample b_3227 = ((((int)1) - alpha_3231) * b_3228);
			t_sample expr_3218 = a_3229;
			t_sample expr_3219 = a_3226;
			t_sample expr_3220 = a_3229;
			t_sample expr_3221 = b_3224;
			t_sample expr_3222 = b_3227;
			t_sample mul_3192 = (mul_3483 * expr_3218);
			t_sample mul_3202 = (mul_3501 * expr_3218);
			t_sample mul_3189 = (m_history_83 * expr_3219);
			t_sample mul_3199 = (m_history_82 * expr_3219);
			t_sample mul_3187 = (m_history_85 * expr_3220);
			t_sample mul_3197 = (m_history_87 * expr_3220);
			t_sample mul_3185 = (m_history_81 * expr_3221);
			t_sample mul_3195 = (m_history_80 * expr_3221);
			t_sample mul_3183 = (m_history_84 * expr_3222);
			t_sample sub_3191 = (((mul_3187 + mul_3189) + mul_3192) - (mul_3183 + mul_3185));
			t_sample gen_3212 = sub_3191;
			t_sample mul_3193 = (m_history_86 * expr_3222);
			t_sample sub_3201 = (((mul_3202 + mul_3199) + mul_3197) - (mul_3193 + mul_3195));
			t_sample gen_3211 = sub_3201;
			t_sample history_3198_next_3203 = fixdenorm(m_history_82);
			t_sample history_3194_next_3204 = fixdenorm(m_history_80);
			t_sample history_3188_next_3205 = fixdenorm(m_history_83);
			t_sample history_3184_next_3206 = fixdenorm(m_history_81);
			t_sample history_3190_next_3207 = fixdenorm(mul_3483);
			t_sample history_3200_next_3208 = fixdenorm(mul_3501);
			t_sample history_3186_next_3209 = fixdenorm(sub_3191);
			t_sample history_3196_next_3210 = fixdenorm(sub_3201);
			t_sample mul_3157 = (gen_3212 * expr_3213);
			t_sample mul_3167 = (gen_3211 * expr_3213);
			t_sample mul_3154 = (m_history_75 * expr_3214);
			t_sample mul_3164 = (m_history_74 * expr_3214);
			t_sample mul_3152 = (m_history_79 * expr_3215);
			t_sample mul_3162 = (m_history_76 * expr_3215);
			t_sample mul_3150 = (m_history_73 * expr_3216);
			t_sample mul_3160 = (m_history_72 * expr_3216);
			t_sample mul_3148 = (m_history_78 * expr_3217);
			t_sample sub_3156 = (((mul_3152 + mul_3154) + mul_3157) - (mul_3148 + mul_3150));
			t_sample gen_3177 = sub_3156;
			t_sample mul_3158 = (m_history_77 * expr_3217);
			t_sample sub_3166 = (((mul_3167 + mul_3164) + mul_3162) - (mul_3158 + mul_3160));
			t_sample gen_3176 = sub_3166;
			t_sample history_3153_next_3168 = fixdenorm(m_history_75);
			t_sample history_3149_next_3169 = fixdenorm(m_history_73);
			t_sample history_3159_next_3170 = fixdenorm(m_history_72);
			t_sample history_3163_next_3171 = fixdenorm(m_history_74);
			t_sample history_3155_next_3172 = fixdenorm(gen_3212);
			t_sample history_3165_next_3173 = fixdenorm(gen_3211);
			t_sample history_3151_next_3174 = fixdenorm(sub_3156);
			t_sample history_3161_next_3175 = fixdenorm(sub_3166);
			t_sample gen_3233 = gen_3177;
			t_sample gen_3232 = gen_3176;
			t_sample mul_3465 = (m_history_71 * ((t_sample)0.999));
			t_sample add_3467 = (mul_3464 + mul_3465);
			t_sample gen_3469 = add_3467;
			t_sample history_3466_next_3468 = fixdenorm(add_3467);
			t_sample mul_3725 = (div_3740 * gen_3265);
			t_sample mul_3728 = (((int)1188) * mul_3725);
			t_sample mul_3684 = (m_history_70 * ((t_sample)0.999));
			t_sample mul_3683 = (mul_3728 * ((t_sample)0.001));
			t_sample add_3686 = (mul_3683 + mul_3684);
			t_sample gen_3688 = add_3686;
			t_sample history_3685_next_3687 = fixdenorm(add_3686);
			t_sample gen_3749 = gen_3688;
			t_sample mul_3726 = (((int)1116) * mul_3725);
			t_sample mul_3678 = (m_history_69 * ((t_sample)0.999));
			t_sample mul_3677 = (mul_3726 * ((t_sample)0.001));
			t_sample add_3680 = (mul_3677 + mul_3678);
			t_sample gen_3682 = add_3680;
			t_sample history_3679_next_3681 = fixdenorm(add_3680);
			t_sample gen_3750 = gen_3682;
			t_sample mul_3734 = (((int)1422) * mul_3725);
			t_sample mul_3702 = (m_history_68 * ((t_sample)0.999));
			t_sample mul_3701 = (mul_3734 * ((t_sample)0.001));
			t_sample add_3704 = (mul_3701 + mul_3702);
			t_sample gen_3706 = add_3704;
			t_sample history_3703_next_3705 = fixdenorm(add_3704);
			t_sample gen_3746 = gen_3706;
			t_sample mul_3738 = (((int)1617) * mul_3725);
			t_sample mul_3714 = (m_history_67 * ((t_sample)0.999));
			t_sample mul_3713 = (mul_3738 * ((t_sample)0.001));
			t_sample add_3716 = (mul_3713 + mul_3714);
			t_sample gen_3718 = add_3716;
			t_sample history_3715_next_3717 = fixdenorm(add_3716);
			t_sample gen_3744 = gen_3718;
			t_sample mul_3741 = (((int)1557) * mul_3725);
			t_sample mul_3720 = (m_history_66 * ((t_sample)0.999));
			t_sample mul_3719 = (mul_3741 * ((t_sample)0.001));
			t_sample add_3722 = (mul_3719 + mul_3720);
			t_sample gen_3724 = add_3722;
			t_sample history_3721_next_3723 = fixdenorm(add_3722);
			t_sample gen_3743 = gen_3724;
			t_sample mul_3736 = (((int)1491) * mul_3725);
			t_sample mul_3708 = (m_history_65 * ((t_sample)0.999));
			t_sample mul_3707 = (mul_3736 * ((t_sample)0.001));
			t_sample add_3710 = (mul_3707 + mul_3708);
			t_sample gen_3712 = add_3710;
			t_sample history_3709_next_3711 = fixdenorm(add_3710);
			t_sample gen_3745 = gen_3712;
			t_sample mul_3730 = (((int)1356) * mul_3725);
			t_sample mul_3690 = (m_history_64 * ((t_sample)0.999));
			t_sample mul_3689 = (mul_3730 * ((t_sample)0.001));
			t_sample add_3692 = (mul_3689 + mul_3690);
			t_sample gen_3694 = add_3692;
			t_sample history_3691_next_3693 = fixdenorm(add_3692);
			t_sample gen_3748 = gen_3694;
			t_sample mul_3732 = (((int)1277) * mul_3725);
			t_sample mul_3696 = (m_history_63 * ((t_sample)0.999));
			t_sample mul_3695 = (mul_3732 * ((t_sample)0.001));
			t_sample add_3698 = (mul_3695 + mul_3696);
			t_sample gen_3700 = add_3698;
			t_sample history_3697_next_3699 = fixdenorm(add_3698);
			t_sample gen_3747 = gen_3700;
			t_sample mul_3839 = (m_history_61 * rsub_3837);
			t_sample add_3836 = (((int)0) + gen_3743);
			t_sample tap_3845 = m_delay_62.read_linear(add_3836);
			t_sample mul_3842 = (tap_3845 * rsub_3751);
			t_sample add_3841 = (mul_3842 + mul_3839);
			t_sample mul_3838 = (add_3841 * gen_3469);
			t_sample add_3843 = (gen_3232 + mul_3838);
			t_sample gen_3847 = add_3843;
			t_sample history_3840_next_3846 = fixdenorm(add_3841);
			t_sample mul_3827 = (m_history_59 * rsub_3825);
			t_sample add_3824 = (((int)0) + gen_3744);
			t_sample tap_3833 = m_delay_60.read_linear(add_3824);
			t_sample mul_3830 = (tap_3833 * rsub_3751);
			t_sample add_3829 = (mul_3830 + mul_3827);
			t_sample mul_3826 = (add_3829 * gen_3469);
			t_sample add_3831 = (gen_3232 + mul_3826);
			t_sample gen_3835 = add_3831;
			t_sample history_3828_next_3834 = fixdenorm(add_3829);
			t_sample mul_3815 = (m_history_57 * rsub_3813);
			t_sample add_3812 = (((int)0) + gen_3745);
			t_sample tap_3821 = m_delay_58.read_linear(add_3812);
			t_sample mul_3818 = (tap_3821 * rsub_3751);
			t_sample add_3817 = (mul_3818 + mul_3815);
			t_sample mul_3814 = (add_3817 * gen_3469);
			t_sample add_3819 = (gen_3232 + mul_3814);
			t_sample gen_3823 = add_3819;
			t_sample history_3816_next_3822 = fixdenorm(add_3817);
			t_sample mul_3803 = (m_history_55 * rsub_3801);
			t_sample add_3800 = (((int)0) + gen_3746);
			t_sample tap_3809 = m_delay_56.read_linear(add_3800);
			t_sample mul_3806 = (tap_3809 * rsub_3751);
			t_sample add_3805 = (mul_3806 + mul_3803);
			t_sample mul_3802 = (add_3805 * gen_3469);
			t_sample add_3807 = (gen_3232 + mul_3802);
			t_sample gen_3811 = add_3807;
			t_sample history_3804_next_3810 = fixdenorm(add_3805);
			t_sample mul_3791 = (m_history_53 * rsub_3789);
			t_sample add_3788 = (((int)0) + gen_3747);
			t_sample tap_3797 = m_delay_54.read_linear(add_3788);
			t_sample mul_3794 = (tap_3797 * rsub_3751);
			t_sample add_3793 = (mul_3794 + mul_3791);
			t_sample mul_3790 = (add_3793 * gen_3469);
			t_sample add_3795 = (gen_3232 + mul_3790);
			t_sample gen_3799 = add_3795;
			t_sample history_3792_next_3798 = fixdenorm(add_3793);
			t_sample mul_3779 = (m_history_51 * rsub_3777);
			t_sample add_3776 = (((int)0) + gen_3748);
			t_sample tap_3785 = m_delay_52.read_linear(add_3776);
			t_sample mul_3782 = (tap_3785 * rsub_3751);
			t_sample add_3781 = (mul_3782 + mul_3779);
			t_sample mul_3778 = (add_3781 * gen_3469);
			t_sample add_3783 = (gen_3232 + mul_3778);
			t_sample gen_3787 = add_3783;
			t_sample history_3780_next_3786 = fixdenorm(add_3781);
			t_sample mul_3767 = (m_history_49 * rsub_3765);
			t_sample add_3764 = (((int)0) + gen_3749);
			t_sample tap_3773 = m_delay_50.read_linear(add_3764);
			t_sample mul_3770 = (tap_3773 * rsub_3751);
			t_sample add_3769 = (mul_3770 + mul_3767);
			t_sample mul_3766 = (add_3769 * gen_3469);
			t_sample add_3771 = (gen_3232 + mul_3766);
			t_sample gen_3775 = add_3771;
			t_sample history_3768_next_3774 = fixdenorm(add_3769);
			t_sample mul_3755 = (m_history_47 * rsub_3753);
			t_sample add_3752 = (((int)0) + gen_3750);
			t_sample tap_3761 = m_delay_48.read_linear(add_3752);
			t_sample mul_3758 = (tap_3761 * rsub_3751);
			t_sample add_3757 = (mul_3758 + mul_3755);
			t_sample mul_3754 = (add_3757 * gen_3469);
			t_sample add_3759 = (gen_3232 + mul_3754);
			t_sample gen_3763 = add_3759;
			t_sample history_3756_next_3762 = fixdenorm(add_3757);
			t_sample mul_3848 = ((((((((gen_3763 + gen_3775) + gen_3787) + gen_3799) + gen_3811) + gen_3823) + gen_3835) + gen_3847) * ((t_sample)0.125));
			t_sample gen_3849 = mul_3848;
			t_sample mul_3379 = (gen_3849 * ((t_sample)-0.5));
			t_sample mul_3369 = (div_3370 * gen_3265);
			t_sample mul_3371 = (((int)255) * mul_3369);
			t_sample add_3373 = (((int)0) + mul_3371);
			t_sample tap_3381 = m_delay_46.read_linear(add_3373);
			t_sample tap_3376 = m_delay_45.read_linear(add_3373);
			t_sample mul_3374 = (tap_3376 * ((t_sample)0.5));
			t_sample add_3377 = (mul_3379 + (mul_3374 + tap_3381));
			t_sample gen_3382 = add_3377;
			t_sample mul_3365 = (gen_3382 * ((t_sample)-0.5));
			t_sample mul_3355 = (div_3356 * gen_3265);
			t_sample mul_3357 = (((int)556) * mul_3355);
			t_sample add_3359 = (((int)0) + mul_3357);
			t_sample tap_3367 = m_delay_44.read_linear(add_3359);
			t_sample tap_3362 = m_delay_43.read_linear(add_3359);
			t_sample mul_3360 = (tap_3362 * ((t_sample)0.5));
			t_sample add_3363 = (mul_3365 + (mul_3360 + tap_3367));
			t_sample gen_3368 = add_3363;
			t_sample mul_3351 = (gen_3368 * ((t_sample)-0.5));
			t_sample mul_3341 = (div_3342 * gen_3265);
			t_sample mul_3343 = (((int)441) * mul_3341);
			t_sample add_3345 = (((int)0) + mul_3343);
			t_sample tap_3353 = m_delay_42.read_linear(add_3345);
			t_sample tap_3348 = m_delay_41.read_linear(add_3345);
			t_sample mul_3346 = (tap_3348 * ((t_sample)0.5));
			t_sample add_3349 = (mul_3351 + (mul_3346 + tap_3353));
			t_sample gen_3354 = add_3349;
			t_sample mul_3337 = (gen_3354 * ((t_sample)-0.5));
			t_sample mul_3327 = (div_3328 * gen_3265);
			t_sample mul_3329 = (((int)341) * mul_3327);
			t_sample add_3331 = (((int)0) + mul_3329);
			t_sample tap_3339 = m_delay_40.read_linear(add_3331);
			t_sample tap_3334 = m_delay_39.read_linear(add_3331);
			t_sample mul_3332 = (tap_3334 * ((t_sample)0.5));
			t_sample add_3335 = (mul_3337 + (mul_3332 + tap_3339));
			t_sample gen_3340 = add_3335;
			t_sample gen_3383 = gen_3340;
			t_sample mul_3552 = (div_3567 * gen_3265);
			t_sample mul_3565 = (((int)1617) * mul_3552);
			t_sample mul_3541 = (m_history_38 * ((t_sample)0.999));
			t_sample mul_3540 = (mul_3565 * ((t_sample)0.001));
			t_sample add_3543 = (mul_3540 + mul_3541);
			t_sample gen_3545 = add_3543;
			t_sample history_3542_next_3544 = fixdenorm(add_3543);
			t_sample gen_3571 = gen_3545;
			t_sample mul_3568 = (((int)1557) * mul_3552);
			t_sample mul_3547 = (m_history_37 * ((t_sample)0.999));
			t_sample mul_3546 = (mul_3568 * ((t_sample)0.001));
			t_sample add_3549 = (mul_3546 + mul_3547);
			t_sample gen_3551 = add_3549;
			t_sample history_3548_next_3550 = fixdenorm(add_3549);
			t_sample gen_3570 = gen_3551;
			t_sample mul_3561 = (((int)1422) * mul_3552);
			t_sample mul_3529 = (m_history_36 * ((t_sample)0.999));
			t_sample mul_3528 = (mul_3561 * ((t_sample)0.001));
			t_sample add_3531 = (mul_3528 + mul_3529);
			t_sample gen_3533 = add_3531;
			t_sample history_3530_next_3532 = fixdenorm(add_3531);
			t_sample gen_3573 = gen_3533;
			t_sample mul_3553 = (((int)1116) * mul_3552);
			t_sample mul_3505 = (m_history_35 * ((t_sample)0.999));
			t_sample mul_3504 = (mul_3553 * ((t_sample)0.001));
			t_sample add_3507 = (mul_3504 + mul_3505);
			t_sample gen_3509 = add_3507;
			t_sample history_3506_next_3508 = fixdenorm(add_3507);
			t_sample gen_3577 = gen_3509;
			t_sample mul_3559 = (((int)1277) * mul_3552);
			t_sample mul_3523 = (m_history_34 * ((t_sample)0.999));
			t_sample mul_3522 = (mul_3559 * ((t_sample)0.001));
			t_sample add_3525 = (mul_3522 + mul_3523);
			t_sample gen_3527 = add_3525;
			t_sample history_3524_next_3526 = fixdenorm(add_3525);
			t_sample gen_3574 = gen_3527;
			t_sample mul_3555 = (((int)1188) * mul_3552);
			t_sample mul_3511 = (m_history_33 * ((t_sample)0.999));
			t_sample mul_3510 = (mul_3555 * ((t_sample)0.001));
			t_sample add_3513 = (mul_3510 + mul_3511);
			t_sample gen_3515 = add_3513;
			t_sample history_3512_next_3514 = fixdenorm(add_3513);
			t_sample gen_3576 = gen_3515;
			t_sample mul_3557 = (((int)1356) * mul_3552);
			t_sample mul_3517 = (m_history_32 * ((t_sample)0.999));
			t_sample mul_3516 = (mul_3557 * ((t_sample)0.001));
			t_sample add_3519 = (mul_3516 + mul_3517);
			t_sample gen_3521 = add_3519;
			t_sample history_3518_next_3520 = fixdenorm(add_3519);
			t_sample gen_3575 = gen_3521;
			t_sample mul_3563 = (((int)1491) * mul_3552);
			t_sample mul_3535 = (m_history_31 * ((t_sample)0.999));
			t_sample mul_3534 = (mul_3563 * ((t_sample)0.001));
			t_sample add_3537 = (mul_3534 + mul_3535);
			t_sample gen_3539 = add_3537;
			t_sample history_3536_next_3538 = fixdenorm(add_3537);
			t_sample gen_3572 = gen_3539;
			t_sample mul_3666 = (m_history_29 * rsub_3664);
			t_sample add_3663 = (mul_3266 + gen_3570);
			t_sample tap_3672 = m_delay_30.read_linear(add_3663);
			t_sample mul_3669 = (tap_3672 * rsub_3578);
			t_sample add_3668 = (mul_3669 + mul_3666);
			t_sample mul_3665 = (add_3668 * gen_3469);
			t_sample add_3670 = (gen_3233 + mul_3665);
			t_sample gen_3674 = add_3670;
			t_sample history_3667_next_3673 = fixdenorm(add_3668);
			t_sample mul_3654 = (m_history_27 * rsub_3652);
			t_sample add_3651 = (mul_3266 + gen_3571);
			t_sample tap_3660 = m_delay_28.read_linear(add_3651);
			t_sample mul_3657 = (tap_3660 * rsub_3578);
			t_sample add_3656 = (mul_3657 + mul_3654);
			t_sample mul_3653 = (add_3656 * gen_3469);
			t_sample add_3658 = (gen_3233 + mul_3653);
			t_sample gen_3662 = add_3658;
			t_sample history_3655_next_3661 = fixdenorm(add_3656);
			t_sample mul_3642 = (m_history_25 * rsub_3640);
			t_sample add_3639 = (mul_3266 + gen_3572);
			t_sample tap_3648 = m_delay_26.read_linear(add_3639);
			t_sample mul_3645 = (tap_3648 * rsub_3578);
			t_sample add_3644 = (mul_3645 + mul_3642);
			t_sample mul_3641 = (add_3644 * gen_3469);
			t_sample add_3646 = (gen_3233 + mul_3641);
			t_sample gen_3650 = add_3646;
			t_sample history_3643_next_3649 = fixdenorm(add_3644);
			t_sample mul_3630 = (m_history_23 * rsub_3628);
			t_sample add_3627 = (mul_3266 + gen_3573);
			t_sample tap_3636 = m_delay_24.read_linear(add_3627);
			t_sample mul_3633 = (tap_3636 * rsub_3578);
			t_sample add_3632 = (mul_3633 + mul_3630);
			t_sample mul_3629 = (add_3632 * gen_3469);
			t_sample add_3634 = (gen_3233 + mul_3629);
			t_sample gen_3638 = add_3634;
			t_sample history_3631_next_3637 = fixdenorm(add_3632);
			t_sample mul_3618 = (m_history_21 * rsub_3616);
			t_sample add_3615 = (mul_3266 + gen_3574);
			t_sample tap_3624 = m_delay_22.read_linear(add_3615);
			t_sample mul_3621 = (tap_3624 * rsub_3578);
			t_sample add_3620 = (mul_3621 + mul_3618);
			t_sample mul_3617 = (add_3620 * gen_3469);
			t_sample add_3622 = (gen_3233 + mul_3617);
			t_sample gen_3626 = add_3622;
			t_sample history_3619_next_3625 = fixdenorm(add_3620);
			t_sample mul_3606 = (m_history_19 * rsub_3604);
			t_sample add_3603 = (mul_3266 + gen_3575);
			t_sample tap_3612 = m_delay_20.read_linear(add_3603);
			t_sample mul_3609 = (tap_3612 * rsub_3578);
			t_sample add_3608 = (mul_3609 + mul_3606);
			t_sample mul_3605 = (add_3608 * gen_3469);
			t_sample add_3610 = (gen_3233 + mul_3605);
			t_sample gen_3614 = add_3610;
			t_sample history_3607_next_3613 = fixdenorm(add_3608);
			t_sample mul_3594 = (m_history_17 * rsub_3592);
			t_sample add_3591 = (mul_3266 + gen_3576);
			t_sample tap_3600 = m_delay_18.read_linear(add_3591);
			t_sample mul_3597 = (tap_3600 * rsub_3578);
			t_sample add_3596 = (mul_3597 + mul_3594);
			t_sample mul_3593 = (add_3596 * gen_3469);
			t_sample add_3598 = (gen_3233 + mul_3593);
			t_sample gen_3602 = add_3598;
			t_sample history_3595_next_3601 = fixdenorm(add_3596);
			t_sample mul_3582 = (m_history_15 * rsub_3580);
			t_sample add_3579 = (mul_3266 + gen_3577);
			t_sample tap_3588 = m_delay_16.read_linear(add_3579);
			t_sample mul_3585 = (tap_3588 * rsub_3578);
			t_sample add_3584 = (mul_3585 + mul_3582);
			t_sample mul_3581 = (add_3584 * gen_3469);
			t_sample add_3586 = (gen_3233 + mul_3581);
			t_sample gen_3590 = add_3586;
			t_sample history_3583_next_3589 = fixdenorm(add_3584);
			t_sample mul_3675 = ((((((((gen_3590 + gen_3602) + gen_3614) + gen_3626) + gen_3638) + gen_3650) + gen_3662) + gen_3674) * ((t_sample)0.125));
			t_sample gen_3676 = mul_3675;
			t_sample mul_3320 = (gen_3676 * ((t_sample)-0.5));
			t_sample mul_3310 = (div_3311 * gen_3265);
			t_sample mul_3312 = (((int)255) * mul_3310);
			t_sample add_3314 = (((int)0) + mul_3312);
			t_sample tap_3322 = m_delay_14.read_linear(add_3314);
			t_sample tap_3317 = m_delay_13.read_linear(add_3314);
			t_sample mul_3315 = (tap_3317 * ((t_sample)0.5));
			t_sample add_3318 = (mul_3320 + (mul_3315 + tap_3322));
			t_sample gen_3323 = add_3318;
			t_sample mul_3306 = (gen_3323 * ((t_sample)-0.5));
			t_sample mul_3296 = (div_3297 * gen_3265);
			t_sample mul_3298 = (((int)556) * mul_3296);
			t_sample add_3300 = (((int)0) + mul_3298);
			t_sample tap_3308 = m_delay_12.read_linear(add_3300);
			t_sample tap_3303 = m_delay_11.read_linear(add_3300);
			t_sample mul_3301 = (tap_3303 * ((t_sample)0.5));
			t_sample add_3304 = (mul_3306 + (mul_3301 + tap_3308));
			t_sample gen_3309 = add_3304;
			t_sample mul_3292 = (gen_3309 * ((t_sample)-0.5));
			t_sample mul_3282 = (div_3283 * gen_3265);
			t_sample mul_3284 = (((int)441) * mul_3282);
			t_sample add_3286 = (((int)0) + mul_3284);
			t_sample tap_3294 = m_delay_10.read_linear(add_3286);
			t_sample tap_3289 = m_delay_9.read_linear(add_3286);
			t_sample mul_3287 = (tap_3289 * ((t_sample)0.5));
			t_sample add_3290 = (mul_3292 + (mul_3287 + tap_3294));
			t_sample gen_3295 = add_3290;
			t_sample mul_3278 = (gen_3295 * ((t_sample)-0.5));
			t_sample mul_3268 = (div_3269 * gen_3265);
			t_sample mul_3270 = (((int)341) * mul_3268);
			t_sample add_3272 = (((int)0) + mul_3270);
			t_sample tap_3280 = m_delay_8.read_linear(add_3272);
			t_sample tap_3275 = m_delay_7.read_linear(add_3272);
			t_sample mul_3273 = (tap_3275 * ((t_sample)0.5));
			t_sample add_3276 = (mul_3278 + (mul_3273 + tap_3280));
			t_sample gen_3281 = add_3276;
			t_sample gen_3324 = gen_3281;
			t_sample add_3482 = (gen_3383 + gen_3324);
			t_sample mul_3480 = (add_3482 * sqrt_3478);
			t_sample sub_3481 = (gen_3383 - gen_3324);
			t_sample mul_3479 = (sub_3481 * sqrt_3477);
			t_sample add_3476 = (mul_3480 + mul_3479);
			t_sample mul_3471 = (add_3476 * scale_3472);
			t_sample sub_3475 = (mul_3480 - mul_3479);
			t_sample mul_3470 = (sub_3475 * scale_3472);
			t_sample return_186;
			t_sample return_187;
			eq3bandas_d_d_d_d_d_d_d_d_i(mul_3471, mul_3470, gen_3259, gen_3253, gen_3247, gen_3421, gen_3415, gen_3409, ((int)1), return_186, return_187);
			t_sample expr_3448 = return_186;
			t_sample expr_3449 = return_187;
			t_sample gen_3451 = expr_3449;
			t_sample gen_3450 = expr_3448;
			t_sample mix_4073 = (mul_3471 + (gen_3239 * (gen_3450 - mul_3471)));
			t_sample mix_3241 = mix_4073;
			t_sample mix_4074 = (mul_3470 + (gen_3239 * (gen_3451 - mul_3470)));
			t_sample mix_3240 = mix_4074;
			t_sample dbtoa_3077 = dbtoa(gen_3044);
			t_sample mstosamps_3114 = (gen_3052 * (samplerate * 0.001));
			t_sample mstosamps_3113 = (gen_3058 * (samplerate * 0.001));
			t_sample tap_3110 = m_delay_6.read_step(((int)300));
			t_sample mul_3103 = (mix_3240 * mix_3240);
			t_sample add_3107 = (m_history_5 + mul_3103);
			t_sample sub_3106 = (add_3107 - tap_3110);
			t_sample div_3104 = (sub_3106 * ((t_sample)0.0033333333333333));
			t_sample sqrt_3102 = sqrt(div_3104);
			t_sample gen_3112 = sqrt_3102;
			t_sample history_3105_next_3111 = fixdenorm(sub_3106);
			t_sample atodb_3101 = atodb(gen_3112);
			t_sample max_3080 = ((atodb_3101 < maxb_188) ? maxb_188 : atodb_3101);
			int gt_3100 = (max_3080 > gen_3070);
			t_sample mul_3083 = (m_history_4 * ((t_sample)0.999));
			t_sample mul_3082 = (gt_3100 * ((t_sample)0.001));
			t_sample add_3085 = (mul_3082 + mul_3083);
			t_sample gen_3087 = add_3085;
			t_sample history_3084_next_3086 = fixdenorm(add_3085);
			t_sample sub_3099 = (gen_3070 - max_3080);
			t_sample rdiv_3120 = safediv(((int)1), gen_3064);
			t_sample rsub_3119 = (((int)1) - rdiv_3120);
			t_sample mul_3098 = (sub_3099 * rsub_3119);
			t_sample dbtoa_3096 = dbtoa(mul_3098);
			t_sample orange_4077 = (dbtoa_3096 - ((int)1));
			t_sample sub_4078 = (gen_3087 - ((int)0));
			t_sample scale_4075 = ((safepow((sub_4078 * ((t_sample)1)), ((int)1)) * orange_4077) + ((int)1));
			t_sample iup_190 = (1 / maximum(1, abs(mstosamps_3114)));
			t_sample idown_191 = (1 / maximum(1, abs(mstosamps_3113)));
			__m_slide_189 = fixdenorm((__m_slide_189 + (((scale_4075 > __m_slide_189) ? iup_190 : idown_191) * (scale_4075 - __m_slide_189))));
			t_sample slide_3095 = __m_slide_189;
			t_sample mul_3094 = (mix_3240 * slide_3095);
			t_sample mul_3078 = (mul_3094 * dbtoa_3077);
			t_sample tap_3132 = m_delay_3.read_step(((int)300));
			t_sample mul_3125 = (mix_3241 * mix_3241);
			t_sample add_3129 = (m_history_2 + mul_3125);
			t_sample sub_3128 = (add_3129 - tap_3132);
			t_sample div_3126 = (sub_3128 * ((t_sample)0.0033333333333333));
			t_sample sqrt_3124 = sqrt(div_3126);
			t_sample gen_3134 = sqrt_3124;
			t_sample history_3127_next_3133 = fixdenorm(sub_3128);
			t_sample atodb_3123 = atodb(gen_3134);
			t_sample max_3081 = ((atodb_3123 < maxb_192) ? maxb_192 : atodb_3123);
			int gt_3122 = (max_3081 > gen_3070);
			t_sample mul_3089 = (m_history_1 * ((t_sample)0.999));
			t_sample mul_3088 = (gt_3122 * ((t_sample)0.001));
			t_sample add_3091 = (mul_3088 + mul_3089);
			t_sample gen_3093 = add_3091;
			t_sample history_3090_next_3092 = fixdenorm(add_3091);
			t_sample sub_3121 = (gen_3070 - max_3081);
			t_sample mul_3118 = (sub_3121 * rsub_3119);
			t_sample dbtoa_3116 = dbtoa(mul_3118);
			t_sample orange_4081 = (dbtoa_3116 - ((int)1));
			t_sample sub_4082 = (gen_3093 - ((int)0));
			t_sample scale_4079 = ((safepow((sub_4082 * ((t_sample)1)), ((int)1)) * orange_4081) + ((int)1));
			t_sample iup_194 = (1 / maximum(1, abs(mstosamps_3114)));
			t_sample idown_195 = (1 / maximum(1, abs(mstosamps_3113)));
			__m_slide_193 = fixdenorm((__m_slide_193 + (((scale_4079 > __m_slide_193) ? iup_194 : idown_195) * (scale_4079 - __m_slide_193))));
			t_sample slide_3115 = __m_slide_193;
			t_sample mul_3135 = (mix_3241 * slide_3115);
			t_sample mul_3079 = (mul_3135 * dbtoa_3077);
			t_sample mix_4083 = (mix_3241 + (gen_3076 * (mul_3079 - mix_3241)));
			t_sample mix_4084 = (mix_3240 + (gen_3076 * (mul_3078 - mix_3240)));
			t_sample mix_4085 = (mix_4067 + (gen_3389 * (mix_4083 - mix_4067)));
			t_sample mul_3403 = (mix_4085 * gen_3401);
			t_sample dcblock_3046 = __m_dcblock_196(mul_3403);
			t_sample out1 = dcblock_3046;
			t_sample mix_4086 = (mix_4068 + (gen_3389 * (mix_4084 - mix_4068)));
			t_sample mul_3402 = (mix_4086 * gen_3401);
			t_sample dcblock_3045 = __m_dcblock_197(mul_3402);
			t_sample out2 = dcblock_3045;
			m_history_109 = history_3486_next_3488;
			m_history_108 = history_3386_next_3388;
			m_history_107 = history_3398_next_3400;
			m_history_106 = history_3073_next_3075;
			m_history_105 = history_3067_next_3069;
			m_history_104 = history_3061_next_3063;
			m_history_103 = history_3055_next_3057;
			m_history_102 = history_3049_next_3051;
			m_history_101 = history_3041_next_3043;
			m_history_100 = history_3392_next_3394;
			m_history_99 = history_3236_next_3238;
			m_history_98 = history_3256_next_3258;
			m_history_97 = history_3250_next_3252;
			m_history_96 = history_3244_next_3246;
			m_history_95 = history_3418_next_3420;
			m_history_94 = history_3412_next_3414;
			m_history_93 = history_3406_next_3408;
			m_history_92 = history_3492_next_3494;
			m_history_91 = history_3262_next_3264;
			m_history_90 = history_3430_next_3432;
			m_history_89 = history_3424_next_3426;
			m_history_88 = history_3460_next_3462;
			m_history_87 = history_3198_next_3203;
			m_history_78 = history_3149_next_3169;
			m_history_77 = history_3159_next_3170;
			m_history_76 = history_3163_next_3171;
			m_history_75 = history_3155_next_3172;
			m_history_74 = history_3165_next_3173;
			m_history_73 = history_3151_next_3174;
			m_history_72 = history_3161_next_3175;
			m_history_79 = history_3153_next_3168;
			m_history_86 = history_3194_next_3204;
			m_history_85 = history_3188_next_3205;
			m_history_84 = history_3184_next_3206;
			m_history_83 = history_3190_next_3207;
			m_history_82 = history_3200_next_3208;
			m_history_81 = history_3186_next_3209;
			m_history_80 = history_3196_next_3210;
			m_history_71 = history_3466_next_3468;
			m_history_70 = history_3685_next_3687;
			m_history_47 = history_3756_next_3762;
			m_delay_48.write(add_3759);
			m_history_49 = history_3768_next_3774;
			m_delay_50.write(add_3771);
			m_history_51 = history_3780_next_3786;
			m_delay_52.write(add_3783);
			m_history_53 = history_3792_next_3798;
			m_delay_54.write(add_3795);
			m_history_55 = history_3804_next_3810;
			m_delay_56.write(add_3807);
			m_history_57 = history_3816_next_3822;
			m_delay_58.write(add_3819);
			m_history_59 = history_3828_next_3834;
			m_delay_60.write(add_3831);
			m_history_61 = history_3840_next_3846;
			m_delay_62.write(add_3843);
			m_history_69 = history_3679_next_3681;
			m_history_68 = history_3703_next_3705;
			m_history_67 = history_3715_next_3717;
			m_history_66 = history_3721_next_3723;
			m_history_65 = history_3709_next_3711;
			m_history_64 = history_3691_next_3693;
			m_history_63 = history_3697_next_3699;
			m_delay_46.write(gen_3849);
			m_delay_39.write(add_3335);
			m_delay_40.write(gen_3354);
			m_delay_41.write(add_3349);
			m_delay_42.write(gen_3368);
			m_delay_43.write(add_3363);
			m_delay_44.write(gen_3382);
			m_delay_45.write(add_3377);
			m_history_38 = history_3542_next_3544;
			m_history_15 = history_3583_next_3589;
			m_delay_16.write(add_3586);
			m_history_17 = history_3595_next_3601;
			m_delay_18.write(add_3598);
			m_history_19 = history_3607_next_3613;
			m_delay_20.write(add_3610);
			m_history_21 = history_3619_next_3625;
			m_delay_22.write(add_3622);
			m_history_23 = history_3631_next_3637;
			m_delay_24.write(add_3634);
			m_history_25 = history_3643_next_3649;
			m_delay_26.write(add_3646);
			m_history_27 = history_3655_next_3661;
			m_delay_28.write(add_3658);
			m_history_29 = history_3667_next_3673;
			m_delay_30.write(add_3670);
			m_history_37 = history_3548_next_3550;
			m_history_36 = history_3530_next_3532;
			m_history_35 = history_3506_next_3508;
			m_history_34 = history_3524_next_3526;
			m_history_33 = history_3512_next_3514;
			m_history_32 = history_3518_next_3520;
			m_history_31 = history_3536_next_3538;
			m_delay_14.write(gen_3676);
			m_delay_7.write(add_3276);
			m_delay_8.write(gen_3295);
			m_delay_9.write(add_3290);
			m_delay_10.write(gen_3309);
			m_delay_11.write(add_3304);
			m_delay_12.write(gen_3323);
			m_delay_13.write(add_3318);
			m_delay_6.write(mul_3103);
			m_history_5 = history_3105_next_3111;
			m_history_4 = history_3084_next_3086;
			m_delay_3.write(mul_3125);
			m_history_2 = history_3127_next_3133;
			m_history_1 = history_3090_next_3092;
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
	inline void set_q_ONOFFEQ(t_param _value) {
		m_q_ONOFFEQ_110 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_i_PEAKGAIN(t_param _value) {
		m_i_PEAKGAIN_111 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_t_RATIO(t_param _value) {
		m_t_RATIO_112 = (_value < 1 ? 1 : (_value > 20 ? 20 : _value));
	};
	inline void set_n_LOWFREQ(t_param _value) {
		m_n_LOWFREQ_113 = (_value < 20 ? 20 : (_value > 800 ? 800 : _value));
	};
	inline void set_b_DRYWET(t_param _value) {
		m_b_DRYWET_114 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_r_ONOFFCOMP(t_param _value) {
		m_r_ONOFFCOMP_115 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_v_REL(t_param _value) {
		m_v_REL_116 = (_value < 5 ? 5 : (_value > 500 ? 500 : _value));
	};
	inline void set_m_OUTPUT(t_param _value) {
		m_m_OUTPUT_117 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_d_DAMP(t_param _value) {
		m_d_DAMP_118 = (_value < 0.1 ? 0.1 : (_value > 0.9 ? 0.9 : _value));
	};
	inline void set_a_INPUT(t_param _value) {
		m_a_INPUT_119 = (_value < -12 ? -12 : (_value > 12 ? 12 : _value));
	};
	inline void set_c_REFLECT(t_param _value) {
		m_c_REFLECT_120 = (_value < 0.1 ? 0.1 : (_value > 0.98 ? 0.98 : _value));
	};
	inline void set_f_ST(t_param _value) {
		m_f_ST_121 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_g_FREEZE(t_param _value) {
		m_g_FREEZE_122 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_l_HPF(t_param _value) {
		m_l_HPF_123 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_e_SIZE(t_param _value) {
		m_e_SIZE_124 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_k_LPF(t_param _value) {
		m_k_LPF_125 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_u_ATK(t_param _value) {
		m_u_ATK_126 = (_value < 5 ? 5 : (_value > 250 ? 250 : _value));
	};
	inline void set_w_MAKEUP(t_param _value) {
		m_w_MAKEUP_127 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void set_o_PEAKFREQ(t_param _value) {
		m_o_PEAKFREQ_128 = (_value < 100 ? 100 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_h_LOWGAIN(t_param _value) {
		m_h_LOWGAIN_129 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_j_HIGAIN(t_param _value) {
		m_j_HIGAIN_130 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_s_THD(t_param _value) {
		m_s_THD_131 = (_value < -36 ? -36 : (_value > 0 ? 0 : _value));
	};
	inline void set_p_HIFREQ(t_param _value) {
		m_p_HIFREQ_132 = (_value < 800 ? 800 : (_value > 15000 ? 15000 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_145;
		t_sample return_146;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_145, return_146);
		t_sample x_3442 = return_145;
		sigR = return_146;
		t_sample return_170;
		t_sample return_171;
		peak_d_d_d_d_i(x_3442, sigR, pf, pg, bw, return_170, return_171);
		t_sample x_3445 = return_170;
		sigR = return_171;
		t_sample return_184;
		t_sample return_185;
		hishelf_d_d_d_d(x_3445, sigR, hf, hg, return_184, return_185);
		t_sample x_3447 = return_184;
		sigR = return_185;
		out1 = x_3447;
		out2 = sigR;
		
	};
	inline void lowshelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_140(freq) != ((int)0)) || (__m_change_141(db) != ((int)0)))) {
			m_b_139 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_f_138 = safediv(freq, m_b_139);
			m_b_137 = ((m_b_139 * m_b_139) - ((int)1));
			m_w_136 = tan(safediv((m_f_138 * ((t_sample)3.1415926535898)), samplerate));
			m_a_135 = safediv(((int)1), (m_w_136 + ((int)1)));
			m_a_134 = (m_w_136 - ((int)1));
			
		};
		t_sample outputLowShelfL = lowshelfCore_d_d_d_d_d(sigL, m_a_135, m_a_134, m_b_137, m_w_136);
		t_sample outputLowShelfR = lowshelfCore_d_d_d_d_d_143(sigR, m_a_135, m_a_134, m_b_137, m_w_136);
		out1 = outputLowShelfL;
		out2 = outputLowShelfR;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_135, t_sample m_a_134, t_sample m_b_137, t_sample m_w_136) {
		t_sample x = (m_a_135 * (input - (m_a_134 * m_z_142)));
		t_sample output = (m_w_136 * (x + m_z_142));
		m_z_142 = x;
		return ((output * m_b_137) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_143(t_sample input, t_sample m_a_135, t_sample m_a_134, t_sample m_b_137, t_sample m_w_136) {
		t_sample x = (m_a_135 * (input - (m_a_134 * m_z_144)));
		t_sample output = (m_w_136 * (x + m_z_144));
		m_z_144 = x;
		return ((output * m_b_137) + input);
		
	};
	inline void peak_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_157(freq) != ((int)0)) || (__m_change_158(db) != ((int)0))) || (__m_change_159(bw) != ((int)0)))) {
			m_w_156 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_155 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_155 * m_b_155) - ((int)1));
			m_d_154 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_160 = safediv(((m_d_154 * m_d_154) - ((int)1)), (m_d_154 * m_b_155));
			m_d_153 = ((v_160 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_160 >= ((int)100)) ? ((int)100) : v_160));
			m_d_152 = (m_d_153 * b);
			m_wq_151 = (m_d_153 * m_w_156);
			m_w_150 = (m_w_156 * m_w_156);
			m_a_149 = safediv(((int)1), ((((int)1) + m_w_150) + m_wq_151));
			m_a_148 = ((m_w_150 - ((int)1)) * ((int)2));
			m_a_147 = ((((int)1) + m_w_150) - m_wq_151);
			
		};
		t_sample outputPeakL = peakCore_d_d_d_d_d_d(sigL, m_w_156, m_d_152, m_a_149, m_a_148, m_a_147);
		t_sample outputPeakR = peakCore_d_d_d_d_d_d_165(sigR, m_w_156, m_d_152, m_a_149, m_a_148, m_a_147);
		out1 = outputPeakL;
		out2 = outputPeakR;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_156, t_sample m_d_152, t_sample m_a_149, t_sample m_a_148, t_sample m_a_147) {
		t_sample output = ((input - m_z_163) * m_w_156);
		m_z_163 = m_z_164;
		m_z_164 = input;
		t_sample output_3443 = (m_a_149 * ((output - (m_a_148 * m_z_162)) - (m_a_147 * m_z_161)));
		m_z_161 = m_z_162;
		m_z_162 = output_3443;
		t_sample output_3444 = (input + (output_3443 * m_d_152));
		return output_3444;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_165(t_sample input, t_sample m_w_156, t_sample m_d_152, t_sample m_a_149, t_sample m_a_148, t_sample m_a_147) {
		t_sample output = ((input - m_z_168) * m_w_156);
		m_z_168 = m_z_169;
		m_z_169 = input;
		t_sample output_3443 = (m_a_149 * ((output - (m_a_148 * m_z_167)) - (m_a_147 * m_z_166)));
		m_z_166 = m_z_167;
		m_z_167 = output_3443;
		t_sample output_3444 = (input + (output_3443 * m_d_152));
		return output_3444;
		
	};
	inline void hishelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_178(freq) != ((int)0)) || (__m_change_179(db) != ((int)0)))) {
			m_b_177 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_180 = (freq * m_b_177);
			m_f_176 = ((samplerate < mina_180) ? samplerate : mina_180);
			m_b_175 = ((m_b_177 * m_b_177) - ((int)1));
			m_w_174 = tan(safediv((((m_f_176 < ((int)0)) ? ((int)0) : m_f_176) * ((t_sample)3.1415926535898)), samplerate));
			m_a_173 = safediv(((int)1), (m_w_174 + ((int)1)));
			m_a_172 = (m_w_174 - ((int)1));
			
		};
		t_sample outputHighShelfL = hishelfCore_d_d_d_d(sigL, m_a_173, m_a_172, m_b_175);
		t_sample outputHighShelfR = hishelfCore_d_d_d_d_182(sigR, m_a_173, m_a_172, m_b_175);
		out1 = outputHighShelfL;
		out2 = outputHighShelfR;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_173, t_sample m_a_172, t_sample m_b_175) {
		t_sample x = (m_a_173 * (input - (m_a_172 * m_z_181)));
		t_sample output = (x - m_z_181);
		m_z_181 = x;
		t_sample output_3446 = ((output * m_b_175) + input);
		return output_3446;
		
	};
	inline t_sample hishelfCore_d_d_d_d_182(t_sample input, t_sample m_a_173, t_sample m_a_172, t_sample m_b_175) {
		t_sample x = (m_a_173 * (input - (m_a_172 * m_z_183)));
		t_sample output = (x - m_z_183);
		m_z_183 = x;
		t_sample output_3446 = ((output * m_b_175) + input);
		return output_3446;
		
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
int num_params() { return 23; }

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
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_a_INPUT_119; break;
		case 1: *value = self->m_b_DRYWET_114; break;
		case 2: *value = self->m_c_REFLECT_120; break;
		case 3: *value = self->m_d_DAMP_118; break;
		case 4: *value = self->m_e_SIZE_124; break;
		case 5: *value = self->m_f_ST_121; break;
		case 6: *value = self->m_g_FREEZE_122; break;
		case 7: *value = self->m_h_LOWGAIN_129; break;
		case 8: *value = self->m_i_PEAKGAIN_111; break;
		case 9: *value = self->m_j_HIGAIN_130; break;
		case 10: *value = self->m_k_LPF_125; break;
		case 11: *value = self->m_l_HPF_123; break;
		case 12: *value = self->m_m_OUTPUT_117; break;
		case 13: *value = self->m_n_LOWFREQ_113; break;
		case 14: *value = self->m_o_PEAKFREQ_128; break;
		case 15: *value = self->m_p_HIFREQ_132; break;
		case 16: *value = self->m_q_ONOFFEQ_110; break;
		case 17: *value = self->m_r_ONOFFCOMP_115; break;
		case 18: *value = self->m_s_THD_131; break;
		case 19: *value = self->m_t_RATIO_112; break;
		case 20: *value = self->m_u_ATK_126; break;
		case 21: *value = self->m_v_REL_116; break;
		case 22: *value = self->m_w_MAKEUP_127; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(23 * sizeof(ParamInfo));
	self->__commonstate.numparams = 23;
	// initialize parameter 0 ("m_a_INPUT_119")
	pi = self->__commonstate.params + 0;
	pi->name = "a_INPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_INPUT_119;
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
	// initialize parameter 2 ("m_c_REFLECT_120")
	pi = self->__commonstate.params + 2;
	pi->name = "c_REFLECT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_REFLECT_120;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.98;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_DAMP_118")
	pi = self->__commonstate.params + 3;
	pi->name = "d_DAMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_DAMP_118;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.9;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_SIZE_124")
	pi = self->__commonstate.params + 4;
	pi->name = "e_SIZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_SIZE_124;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_ST_121")
	pi = self->__commonstate.params + 5;
	pi->name = "f_ST";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_ST_121;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_FREEZE_122")
	pi = self->__commonstate.params + 6;
	pi->name = "g_FREEZE";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_FREEZE_122;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_LOWGAIN_129")
	pi = self->__commonstate.params + 7;
	pi->name = "h_LOWGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_LOWGAIN_129;
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
	// initialize parameter 9 ("m_j_HIGAIN_130")
	pi = self->__commonstate.params + 9;
	pi->name = "j_HIGAIN";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_HIGAIN_130;
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
	// initialize parameter 11 ("m_l_HPF_123")
	pi = self->__commonstate.params + 11;
	pi->name = "l_HPF";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_HPF_123;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_OUTPUT_117")
	pi = self->__commonstate.params + 12;
	pi->name = "m_OUTPUT";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_OUTPUT_117;
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
	// initialize parameter 14 ("m_o_PEAKFREQ_128")
	pi = self->__commonstate.params + 14;
	pi->name = "o_PEAKFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_PEAKFREQ_128;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 2500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_HIFREQ_132")
	pi = self->__commonstate.params + 15;
	pi->name = "p_HIFREQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_HIFREQ_132;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 800;
	pi->outputmax = 15000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_ONOFFEQ_110")
	pi = self->__commonstate.params + 16;
	pi->name = "q_ONOFFEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_ONOFFEQ_110;
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
	// initialize parameter 18 ("m_s_THD_131")
	pi = self->__commonstate.params + 18;
	pi->name = "s_THD";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_THD_131;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -36;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_RATIO_112")
	pi = self->__commonstate.params + 19;
	pi->name = "t_RATIO";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_RATIO_112;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_ATK_126")
	pi = self->__commonstate.params + 20;
	pi->name = "u_ATK";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_ATK_126;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 5;
	pi->outputmax = 250;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_REL_116")
	pi = self->__commonstate.params + 21;
	pi->name = "v_REL";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_REL_116;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 5;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_MAKEUP_127")
	pi = self->__commonstate.params + 22;
	pi->name = "w_MAKEUP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_MAKEUP_127;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -6;
	pi->outputmax = 6;
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
