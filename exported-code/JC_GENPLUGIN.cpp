#include "JC_GENPLUGIN.h"

namespace JC_GENPLUGIN {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Change __m_change_173;
	Change __m_change_153;
	Change __m_change_174;
	Change __m_change_154;
	Change __m_change_152;
	Change __m_change_136;
	Change __m_change_135;
	Delay m_delay_36;
	Delay m_delay_37;
	Delay m_delay_35;
	Delay m_delay_54;
	Delay m_delay_56;
	Delay m_delay_52;
	Delay m_delay_58;
	Delay m_delay_50;
	Delay m_delay_39;
	Delay m_delay_26;
	Delay m_delay_46;
	Delay m_delay_48;
	Delay m_delay_38;
	Delay m_delay_44;
	Delay m_delay_41;
	Delay m_delay_42;
	Delay m_delay_40;
	Delay m_delay_22;
	Delay m_delay_24;
	Delay m_delay_14;
	Delay m_delay_7;
	Delay m_delay_18;
	Delay m_delay_8;
	Delay m_delay_9;
	Delay m_delay_16;
	Delay m_delay_10;
	Delay m_delay_6;
	Delay m_delay_4;
	Delay m_delay_5;
	Delay m_delay_3;
	Delay m_delay_2;
	Delay m_delay_12;
	Delay m_delay_20;
	int vectorsize;
	int __exception;
	t_sample m_w_131;
	t_sample m_m_output_124;
	t_sample m_w_makeup_127;
	t_sample m_j_hiGain_125;
	t_sample m_s_thd_126;
	t_sample m_n_lowFreq_123;
	t_sample m_q_onoffEQ_122;
	t_sample m_a_129;
	t_sample m_a_130;
	t_sample m_h_lowGain_121;
	t_sample m_e_size_120;
	t_sample m_f_st_117;
	t_sample m_o_peakFreq_118;
	t_sample m_r_onoffCOMP_107;
	t_sample m_k_lpf_108;
	t_sample m_t_ratio_109;
	t_sample m_g_freeze_106;
	t_sample m_history_104;
	t_sample m_p_hiFreq_105;
	t_sample m_history_103;
	t_sample m_l_hpf_119;
	t_sample m_v_rel_110;
	t_sample m_c_reflect_112;
	t_sample m_a_input_116;
	t_sample m_b_132;
	t_sample m_i_peakGain_111;
	t_sample m_u_atk_115;
	t_sample m_d_damp_113;
	t_sample m_b_drywet_114;
	t_sample m_f_133;
	t_sample m_w_151;
	t_sample m_z_137;
	t_sample m_z_164;
	t_sample m_a_167;
	t_sample m_z_163;
	t_sample m_z_161;
	t_sample m_z_162;
	t_sample m_z_159;
	t_sample m_a_168;
	t_sample m_b_170;
	t_sample m_z_178;
	t_sample m_w_169;
	t_sample m_z_176;
	t_sample m_f_171;
	t_sample m_b_172;
	t_sample m_b_134;
	t_sample m_z_158;
	t_sample m_z_156;
	t_sample m_a_144;
	t_sample m_w_145;
	t_sample m_a_143;
	t_sample m_z_139;
	t_sample m_a_142;
	t_sample m_z_157;
	t_sample m_wq_146;
	t_sample m_d_148;
	t_sample m_history_102;
	t_sample m_d_147;
	t_sample m_b_150;
	t_sample m_d_149;
	t_sample m_history_101;
	t_sample m_history_84;
	t_sample m_history_99;
	t_sample m_history_47;
	t_sample m_history_49;
	t_sample m_history_51;
	t_sample m_history_45;
	t_sample m_history_34;
	t_sample m_history_43;
	t_sample m_history_33;
	t_sample m_history_53;
	t_sample m_history_57;
	t_sample m_history_62;
	t_sample m_history_63;
	t_sample m_history_55;
	t_sample m_history_61;
	t_sample m_history_59;
	t_sample m_history_60;
	t_sample m_history_64;
	t_sample m_history_32;
	t_sample m_history_30;
	t_sample m_history_13;
	t_sample m_history_15;
	t_sample m_history_17;
	t_sample m_history_11;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample m_history_31;
	t_sample m_history_19;
	t_sample m_history_23;
	t_sample m_history_29;
	t_sample m_history_21;
	t_sample m_history_28;
	t_sample m_history_25;
	t_sample m_history_27;
	t_sample m_history_100;
	t_sample m_history_65;
	t_sample m_history_67;
	t_sample m_history_88;
	t_sample m_history_89;
	t_sample m_history_90;
	t_sample m_history_87;
	t_sample m_history_85;
	t_sample m_history_86;
	t_sample __m_slide_184;
	t_sample m_history_91;
	t_sample m_history_93;
	t_sample m_history_97;
	t_sample m_history_98;
	t_sample m_history_92;
	t_sample m_history_96;
	t_sample m_history_94;
	t_sample m_history_95;
	t_sample m_history_66;
	t_sample m_history_83;
	t_sample m_history_81;
	t_sample m_history_71;
	t_sample m_history_72;
	t_sample m_history_73;
	t_sample m_history_70;
	t_sample m_history_68;
	t_sample m_history_69;
	t_sample m_history_82;
	t_sample m_history_74;
	t_sample m_history_76;
	t_sample m_history_80;
	t_sample m_history_75;
	t_sample m_history_79;
	t_sample m_history_77;
	t_sample m_history_78;
	t_sample __m_slide_187;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_delay_2.reset("m_delay_2", ((int)44100));
		m_delay_3.reset("m_delay_3", samplerate);
		m_delay_4.reset("m_delay_4", samplerate);
		m_delay_5.reset("m_delay_5", samplerate);
		m_delay_6.reset("m_delay_6", samplerate);
		m_delay_7.reset("m_delay_7", samplerate);
		m_delay_8.reset("m_delay_8", samplerate);
		m_delay_9.reset("m_delay_9", samplerate);
		m_delay_10.reset("m_delay_10", samplerate);
		m_history_11 = ((int)0);
		m_delay_12.reset("m_delay_12", samplerate);
		m_history_13 = ((int)0);
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
		m_history_28 = ((int)0);
		m_history_29 = ((int)0);
		m_history_30 = ((int)0);
		m_history_31 = ((int)0);
		m_history_32 = ((int)0);
		m_history_33 = ((int)0);
		m_history_34 = ((int)0);
		m_delay_35.reset("m_delay_35", samplerate);
		m_delay_36.reset("m_delay_36", samplerate);
		m_delay_37.reset("m_delay_37", samplerate);
		m_delay_38.reset("m_delay_38", samplerate);
		m_delay_39.reset("m_delay_39", samplerate);
		m_delay_40.reset("m_delay_40", samplerate);
		m_delay_41.reset("m_delay_41", samplerate);
		m_delay_42.reset("m_delay_42", samplerate);
		m_history_43 = ((int)0);
		m_delay_44.reset("m_delay_44", samplerate);
		m_history_45 = ((int)0);
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
		m_history_60 = ((int)0);
		m_history_61 = ((int)0);
		m_history_62 = ((int)0);
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
		m_p_hiFreq_105 = 2000;
		m_g_freeze_106 = 0;
		m_r_onoffCOMP_107 = 0;
		m_k_lpf_108 = 20000;
		m_t_ratio_109 = 2;
		m_v_rel_110 = 100;
		m_i_peakGain_111 = 0;
		m_c_reflect_112 = 0.86;
		m_d_damp_113 = 0.8;
		m_b_drywet_114 = 0.33;
		m_u_atk_115 = 25;
		m_a_input_116 = 0;
		m_f_st_117 = 0.5;
		m_o_peakFreq_118 = 800;
		m_l_hpf_119 = 20;
		m_e_size_120 = 1;
		m_h_lowGain_121 = 0;
		m_q_onoffEQ_122 = 0;
		m_n_lowFreq_123 = 500;
		m_m_output_124 = 0;
		m_j_hiGain_125 = 0;
		m_s_thd_126 = -12;
		m_w_makeup_127 = 0;
		m_a_129 = ((int)0);
		m_a_130 = ((int)0);
		m_w_131 = ((int)0);
		m_b_132 = ((int)0);
		m_f_133 = ((int)0);
		m_b_134 = ((int)0);
		__m_change_135.reset(0);
		__m_change_136.reset(0);
		m_z_137 = ((int)0);
		m_z_139 = ((int)0);
		m_a_142 = ((int)0);
		m_a_143 = ((int)0);
		m_a_144 = ((int)0);
		m_w_145 = ((int)0);
		m_wq_146 = ((int)0);
		m_d_147 = ((int)0);
		m_d_148 = ((int)0);
		m_d_149 = ((int)0);
		m_b_150 = ((int)0);
		m_w_151 = ((int)0);
		__m_change_152.reset(0);
		__m_change_153.reset(0);
		__m_change_154.reset(0);
		m_z_156 = ((int)0);
		m_z_157 = ((int)0);
		m_z_158 = ((int)0);
		m_z_159 = ((int)0);
		m_z_161 = ((int)0);
		m_z_162 = ((int)0);
		m_z_163 = ((int)0);
		m_z_164 = ((int)0);
		m_a_167 = ((int)0);
		m_a_168 = ((int)0);
		m_w_169 = ((int)0);
		m_b_170 = ((int)0);
		m_f_171 = ((int)0);
		m_b_172 = ((int)0);
		__m_change_173.reset(0);
		__m_change_174.reset(0);
		m_z_176 = ((int)0);
		m_z_178 = ((int)0);
		__m_slide_184 = 0;
		__m_slide_187 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample dbtoa_1069 = dbtoa(m_m_output_124);
		t_sample mul_429 = (dbtoa_1069 * ((t_sample)0.001));
		t_sample rsub_9 = (((int)1) - m_r_onoffCOMP_107);
		t_sample mul_1 = (rsub_9 * ((t_sample)0.001));
		t_sample dbtoa_18 = dbtoa(m_w_makeup_127);
		t_sample mul_10 = (dbtoa_18 * ((t_sample)0.001));
		t_sample mul_593 = (m_b_drywet_114 * ((t_sample)0.001));
		int eq_621 = (m_g_freeze_106 == ((int)1));
		int toSize_530 = eq_621;
		t_sample mul_421 = (toSize_530 * ((t_sample)0.001));
		t_sample mul_217 = (m_q_onoffEQ_122 * ((t_sample)0.001));
		t_sample dbtoa_1302 = dbtoa(m_a_input_116);
		t_sample mul_585 = (dbtoa_1302 * ((t_sample)0.001));
		t_sample mul_601 = (m_f_st_117 * ((t_sample)0.001));
		t_sample mul_243 = (m_n_lowFreq_123 * ((t_sample)0.001));
		t_sample mul_235 = (m_o_peakFreq_118 * ((t_sample)0.001));
		t_sample mul_227 = (m_p_hiFreq_105 * ((t_sample)0.001));
		t_sample mul_455 = (m_h_lowGain_121 * ((t_sample)0.001));
		t_sample mul_447 = (m_i_peakGain_111 * ((t_sample)0.001));
		t_sample mul_439 = (m_j_hiGain_125 * ((t_sample)0.001));
		t_sample mul_255 = (m_e_size_120 * ((t_sample)0.001));
		t_sample rsub_1068 = (((int)1) - m_d_damp_113);
		t_sample damp_610 = rsub_1068;
		t_sample damp_611 = damp_610;
		t_sample mul_471 = (m_k_lpf_108 * ((t_sample)0.001));
		t_sample mul_463 = (m_l_hpf_119 * ((t_sample)0.001));
		int toSize_614 = toSize_530;
		t_sample rsub_616 = (((t_sample)0.999) - m_c_reflect_112);
		int choice_128 = toSize_614;
		t_sample gate_615 = ((choice_128 >= 1) ? rsub_616 : 0);
		t_sample add_617 = (m_c_reflect_112 + gate_615);
		t_sample mul_550 = (add_617 * ((t_sample)0.001));
		int rsub_620 = (((int)1) - eq_621);
		t_sample mul_542 = (rsub_620 * ((t_sample)0.001));
		t_sample rsub_942 = (((int)1) - damp_611);
		t_sample div_923 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_944 = (((int)1) - rsub_942);
		t_sample rsub_959 = (((int)1) - rsub_942);
		t_sample rsub_974 = (((int)1) - rsub_942);
		t_sample rsub_989 = (((int)1) - rsub_942);
		t_sample rsub_1004 = (((int)1) - rsub_942);
		t_sample rsub_1019 = (((int)1) - rsub_942);
		t_sample rsub_1034 = (((int)1) - rsub_942);
		t_sample rsub_1049 = (((int)1) - rsub_942);
		t_sample div_392 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_375 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_358 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_341 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_720 = (((int)1) - damp_610);
		t_sample div_701 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_722 = (((int)1) - rsub_720);
		t_sample rsub_737 = (((int)1) - rsub_720);
		t_sample rsub_752 = (((int)1) - rsub_720);
		t_sample rsub_767 = (((int)1) - rsub_720);
		t_sample rsub_782 = (((int)1) - rsub_720);
		t_sample rsub_797 = (((int)1) - rsub_720);
		t_sample rsub_812 = (((int)1) - rsub_720);
		t_sample rsub_827 = (((int)1) - rsub_720);
		t_sample div_319 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_302 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_285 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_268 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample mstosamps_52 = (m_v_rel_110 * (samplerate * 0.001));
		t_sample mstosamps_51 = (m_u_atk_115 * (samplerate * 0.001));
		int min_183 = (-70);
		t_sample rdiv_58 = safediv(((int)1), m_t_ratio_109);
		t_sample rsub_57 = (((int)1) - rdiv_58);
		t_sample iup_185 = (1 / maximum(1, abs(mstosamps_52)));
		t_sample idown_186 = (1 / maximum(1, abs(mstosamps_51)));
		t_sample mstosamps_22 = (m_v_rel_110 * (samplerate * 0.001));
		t_sample mstosamps_21 = (m_u_atk_115 * (samplerate * 0.001));
		t_sample rdiv_28 = safediv(((int)1), m_t_ratio_109);
		t_sample rsub_27 = (((int)1) - rdiv_28);
		t_sample iup_188 = (1 / maximum(1, abs(mstosamps_22)));
		t_sample idown_189 = (1 / maximum(1, abs(mstosamps_21)));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_430 = (m_history_104 * ((t_sample)0.999));
			t_sample add_432 = (mul_429 + mul_430);
			t_sample gen_436 = add_432;
			t_sample history_431_next_435 = fixdenorm(add_432);
			t_sample mul_2 = (m_history_103 * ((t_sample)0.999));
			t_sample add_4 = (mul_1 + mul_2);
			t_sample gen_8 = add_4;
			t_sample history_3_next_7 = fixdenorm(add_4);
			t_sample mul_11 = (m_history_102 * ((t_sample)0.999));
			t_sample add_13 = (mul_10 + mul_11);
			t_sample gen_17 = add_13;
			t_sample history_12_next_16 = fixdenorm(add_13);
			t_sample mul_594 = (m_history_101 * ((t_sample)0.999));
			t_sample add_596 = (mul_593 + mul_594);
			t_sample gen_600 = add_596;
			t_sample history_595_next_599 = fixdenorm(add_596);
			t_sample dry_wet_573 = gen_600;
			t_sample mul_414 = (m_history_100 * ((t_sample)0.999));
			t_sample mul_413 = (dry_wet_573 * ((t_sample)0.001));
			t_sample add_416 = (mul_413 + mul_414);
			t_sample gen_420 = add_416;
			t_sample history_415_next_419 = fixdenorm(add_416);
			t_sample mul_422 = (m_history_99 * ((t_sample)0.999));
			t_sample add_424 = (mul_421 + mul_422);
			t_sample gen_428 = add_424;
			t_sample history_423_next_427 = fixdenorm(add_424);
			t_sample mul_218 = (m_history_98 * ((t_sample)0.999));
			t_sample add_220 = (mul_217 + mul_218);
			t_sample gen_224 = add_220;
			t_sample history_219_next_223 = fixdenorm(add_220);
			t_sample onOffEQ_216 = gen_224;
			t_sample mul_586 = (m_history_97 * ((t_sample)0.999));
			t_sample add_588 = (mul_585 + mul_586);
			t_sample gen_592 = add_588;
			t_sample history_587_next_591 = fixdenorm(add_588);
			t_sample mul_509 = (in1 * gen_592);
			t_sample left_571 = mul_509;
			t_sample mix_1419 = (left_571 + (gen_428 * (((int)0) - left_571)));
			t_sample left_537 = left_571;
			t_sample mul_602 = (m_history_96 * ((t_sample)0.999));
			t_sample add_604 = (mul_601 + mul_602);
			t_sample gen_608 = add_604;
			t_sample history_603_next_607 = fixdenorm(add_604);
			t_sample sub_1423 = (gen_608 - ((int)0));
			t_sample scale_1420 = ((safepow((sub_1423 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_568 = scale_1420;
			t_sample mul_244 = (m_history_95 * ((t_sample)0.999));
			t_sample add_246 = (mul_243 + mul_244);
			t_sample gen_250 = add_246;
			t_sample history_245_next_249 = fixdenorm(add_246);
			t_sample mul_236 = (m_history_94 * ((t_sample)0.999));
			t_sample add_238 = (mul_235 + mul_236);
			t_sample gen_242 = add_238;
			t_sample history_237_next_241 = fixdenorm(add_238);
			t_sample mul_228 = (m_history_93 * ((t_sample)0.999));
			t_sample add_230 = (mul_227 + mul_228);
			t_sample gen_234 = add_230;
			t_sample history_229_next_233 = fixdenorm(add_230);
			t_sample mul_456 = (m_history_92 * ((t_sample)0.999));
			t_sample add_458 = (mul_455 + mul_456);
			t_sample gen_462 = add_458;
			t_sample history_457_next_461 = fixdenorm(add_458);
			t_sample mul_448 = (m_history_91 * ((t_sample)0.999));
			t_sample add_450 = (mul_447 + mul_448);
			t_sample gen_454 = add_450;
			t_sample history_449_next_453 = fixdenorm(add_450);
			t_sample mul_440 = (m_history_90 * ((t_sample)0.999));
			t_sample add_442 = (mul_439 + mul_440);
			t_sample gen_446 = add_442;
			t_sample history_441_next_445 = fixdenorm(add_442);
			t_sample mul_507 = (in2 * gen_592);
			t_sample right_531 = mul_507;
			t_sample right_570 = right_531;
			t_sample right_533 = right_531;
			int eq_540 = (right_533 == ((int)0));
			t_sample mul_519 = (m_history_89 * ((t_sample)0.999));
			t_sample mul_518 = (eq_540 * ((t_sample)0.001));
			t_sample add_521 = (mul_518 + mul_519);
			t_sample gen_525 = add_521;
			t_sample history_520_next_524 = fixdenorm(add_521);
			t_sample mix_1424 = (((int)0) + (gen_525 * (left_537 - ((int)0))));
			t_sample mix_536 = mix_1424;
			t_sample add_1426 = (mix_536 + right_570);
			t_sample mix_1425 = (add_1426 + (gen_428 * (((int)0) - add_1426)));
			t_sample sqrt_577 = sqrt(gen_608);
			t_sample rsub_609 = (((int)1) - gen_608);
			t_sample sqrt_578 = sqrt(rsub_609);
			t_sample mul_256 = (m_history_88 * ((t_sample)0.999));
			t_sample add_258 = (mul_255 + mul_256);
			t_sample gen_262 = add_258;
			t_sample history_257_next_261 = fixdenorm(add_258);
			t_sample escala_Size_337 = gen_262;
			t_sample escala_Size_410 = escala_Size_337;
			t_sample escala_Size_412 = escala_Size_337;
			t_sample escala_Size_411 = escala_Size_337;
			t_sample mul_472 = (m_history_87 * ((t_sample)0.999));
			t_sample add_474 = (mul_471 + mul_472);
			t_sample gen_478 = add_474;
			t_sample history_473_next_477 = fixdenorm(add_474);
			t_sample mul_464 = (m_history_86 * ((t_sample)0.999));
			t_sample add_466 = (mul_463 + mul_464);
			t_sample gen_470 = add_466;
			t_sample history_465_next_469 = fixdenorm(add_466);
			t_sample toMoud_541 = gen_608;
			t_sample mul_551 = (m_history_85 * ((t_sample)0.999));
			t_sample add_553 = (mul_550 + mul_551);
			t_sample gen_557 = add_553;
			t_sample history_552_next_556 = fixdenorm(add_553);
			t_sample escala_Size_265 = escala_Size_337;
			t_sample mul_263 = (((int)12) * escala_Size_265);
			t_sample left_565 = left_571;
			t_sample right_564 = right_531;
			t_sample left_532 = left_571;
			int eq_534 = (left_532 == right_531);
			t_sample mul_511 = (m_history_84 * ((t_sample)0.999));
			t_sample mul_510 = (eq_534 * ((t_sample)0.001));
			t_sample add_513 = (mul_510 + mul_511);
			t_sample gen_517 = add_513;
			t_sample history_512_next_516 = fixdenorm(add_513);
			t_sample add_1428 = (gen_517 + gen_525);
			t_sample mix_1427 = (((int)0) + (add_1428 * (toMoud_541 - ((int)0))));
			t_sample mix_539 = mix_1427;
			t_sample mix_1429 = (((int)0) + (mix_539 * ((int)0)));
			t_sample mix_561 = mix_1429;
			t_sample zeroL_612 = mix_561;
			t_sample mix_1430 = (((int)0) + (mix_539 * (mul_263 - ((int)0))));
			t_sample mix_559 = mix_1430;
			t_sample zeroR_613 = mix_559;
			t_sample mul_543 = (m_history_83 * ((t_sample)0.999));
			t_sample add_545 = (mul_542 + mul_543);
			t_sample gen_549 = add_545;
			t_sample history_544_next_548 = fixdenorm(add_545);
			t_sample freeze_583 = gen_549;
			t_sample mul_584 = ((mix_536 + right_564) * freeze_583);
			t_sample toFILTERS_c45R_80 = mul_584;
			t_sample freeze_618 = freeze_583;
			t_sample mul_619 = (left_565 * freeze_618);
			t_sample toFILTERS_c45L_81 = mul_619;
			t_sample omega = safediv((gen_478 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((int)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) - cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((((int)1) - cs) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_200 = a2;
			t_sample expr_201 = a1;
			t_sample expr_202 = a2;
			t_sample expr_203 = b1;
			t_sample expr_204 = b2;
			t_sample omega_207 = safediv((gen_470 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_205 = sin(omega_207);
			t_sample cs_212 = cos(omega_207);
			t_sample alpha_213 = ((sn_205 * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b_210 = safediv(((int)1), (((int)1) + alpha_213));
			t_sample a_211 = (((((int)1) + cs_212) * ((t_sample)0.5)) * b_210);
			t_sample a_209 = ((-(((int)1) + cs_212)) * b_210);
			t_sample b_208 = ((((int)-2) * cs_212) * b_210);
			t_sample b_206 = ((((int)1) - alpha_213) * b_210);
			t_sample expr_195 = a_211;
			t_sample expr_196 = a_209;
			t_sample expr_197 = a_211;
			t_sample expr_198 = b_208;
			t_sample expr_199 = b_206;
			t_sample mul_138 = (m_history_80 * expr_202);
			t_sample mul_148 = (m_history_82 * expr_202);
			t_sample mul_140 = (m_history_77 * expr_201);
			t_sample mul_150 = (m_history_78 * expr_201);
			t_sample mul_143 = (toFILTERS_c45R_80 * expr_200);
			t_sample mul_153 = (toFILTERS_c45L_81 * expr_200);
			t_sample mul_134 = (m_history_81 * expr_204);
			t_sample mul_144 = (m_history_79 * expr_204);
			t_sample mul_136 = (m_history_76 * expr_203);
			t_sample sub_142 = (((mul_143 + mul_140) + mul_138) - (mul_136 + mul_134));
			t_sample gen_173 = sub_142;
			t_sample mul_146 = (m_history_75 * expr_203);
			t_sample sub_152 = (((mul_148 + mul_150) + mul_153) - (mul_146 + mul_144));
			t_sample gen_172 = sub_152;
			t_sample history_149_next_164 = fixdenorm(m_history_78);
			t_sample history_135_next_165 = fixdenorm(m_history_76);
			t_sample history_139_next_166 = fixdenorm(m_history_77);
			t_sample history_145_next_167 = fixdenorm(m_history_75);
			t_sample history_151_next_168 = fixdenorm(toFILTERS_c45L_81);
			t_sample history_141_next_169 = fixdenorm(toFILTERS_c45R_80);
			t_sample history_137_next_170 = fixdenorm(sub_142);
			t_sample history_147_next_171 = fixdenorm(sub_152);
			t_sample mul_93 = (m_history_72 * expr_197);
			t_sample mul_103 = (m_history_74 * expr_197);
			t_sample mul_95 = (m_history_70 * expr_196);
			t_sample mul_105 = (m_history_69 * expr_196);
			t_sample mul_98 = (gen_173 * expr_195);
			t_sample mul_108 = (gen_172 * expr_195);
			t_sample mul_89 = (m_history_71 * expr_199);
			t_sample mul_99 = (m_history_73 * expr_199);
			t_sample mul_91 = (m_history_68 * expr_198);
			t_sample sub_97 = (((mul_98 + mul_95) + mul_93) - (mul_91 + mul_89));
			t_sample gen_128 = sub_97;
			t_sample mul_101 = (m_history_67 * expr_198);
			t_sample sub_107 = (((mul_103 + mul_105) + mul_108) - (mul_101 + mul_99));
			t_sample gen_127 = sub_107;
			t_sample history_104_next_119 = fixdenorm(m_history_69);
			t_sample history_100_next_120 = fixdenorm(m_history_67);
			t_sample history_94_next_121 = fixdenorm(m_history_70);
			t_sample history_90_next_122 = fixdenorm(m_history_68);
			t_sample history_96_next_123 = fixdenorm(gen_173);
			t_sample history_106_next_124 = fixdenorm(gen_172);
			t_sample history_92_next_125 = fixdenorm(sub_97);
			t_sample history_102_next_126 = fixdenorm(sub_107);
			t_sample gen_214 = gen_127;
			t_sample gen_215 = gen_128;
			t_sample fromFILTERS_c45L_83 = gen_214;
			t_sample mul_908 = (div_923 * escala_Size_412);
			t_sample mul_913 = (((int)1356) * mul_908);
			t_sample mul_861 = (m_history_66 * ((t_sample)0.999));
			t_sample mul_860 = (mul_913 * ((t_sample)0.001));
			t_sample add_863 = (mul_860 + mul_861);
			t_sample gen_867 = add_863;
			t_sample history_862_next_866 = fixdenorm(add_863);
			t_sample gen_939 = gen_867;
			t_sample mul_919 = (((int)1491) * mul_908);
			t_sample mul_885 = (m_history_65 * ((t_sample)0.999));
			t_sample mul_884 = (mul_919 * ((t_sample)0.001));
			t_sample add_887 = (mul_884 + mul_885);
			t_sample gen_891 = add_887;
			t_sample history_886_next_890 = fixdenorm(add_887);
			t_sample gen_936 = gen_891;
			t_sample mul_917 = (((int)1422) * mul_908);
			t_sample mul_877 = (m_history_64 * ((t_sample)0.999));
			t_sample mul_876 = (mul_917 * ((t_sample)0.001));
			t_sample add_879 = (mul_876 + mul_877);
			t_sample gen_883 = add_879;
			t_sample history_878_next_882 = fixdenorm(add_879);
			t_sample gen_937 = gen_883;
			t_sample mul_924 = (((int)1557) * mul_908);
			t_sample mul_901 = (m_history_63 * ((t_sample)0.999));
			t_sample mul_900 = (mul_924 * ((t_sample)0.001));
			t_sample add_903 = (mul_900 + mul_901);
			t_sample gen_907 = add_903;
			t_sample history_902_next_906 = fixdenorm(add_903);
			t_sample gen_934 = gen_907;
			t_sample mul_911 = (((int)1188) * mul_908);
			t_sample mul_853 = (m_history_62 * ((t_sample)0.999));
			t_sample mul_852 = (mul_911 * ((t_sample)0.001));
			t_sample add_855 = (mul_852 + mul_853);
			t_sample gen_859 = add_855;
			t_sample history_854_next_858 = fixdenorm(add_855);
			t_sample gen_940 = gen_859;
			t_sample mul_909 = (((int)1116) * mul_908);
			t_sample mul_845 = (m_history_61 * ((t_sample)0.999));
			t_sample mul_844 = (mul_909 * ((t_sample)0.001));
			t_sample add_847 = (mul_844 + mul_845);
			t_sample gen_851 = add_847;
			t_sample history_846_next_850 = fixdenorm(add_847);
			t_sample gen_941 = gen_851;
			t_sample mul_915 = (((int)1277) * mul_908);
			t_sample mul_869 = (m_history_60 * ((t_sample)0.999));
			t_sample mul_868 = (mul_915 * ((t_sample)0.001));
			t_sample add_871 = (mul_868 + mul_869);
			t_sample gen_875 = add_871;
			t_sample history_870_next_874 = fixdenorm(add_871);
			t_sample gen_938 = gen_875;
			t_sample mul_921 = (((int)1617) * mul_908);
			t_sample mul_893 = (m_history_59 * ((t_sample)0.999));
			t_sample mul_892 = (mul_921 * ((t_sample)0.001));
			t_sample add_895 = (mul_892 + mul_893);
			t_sample gen_899 = add_895;
			t_sample history_894_next_898 = fixdenorm(add_895);
			t_sample gen_935 = gen_899;
			t_sample mul_946 = (m_history_57 * rsub_944);
			t_sample add_943 = (zeroL_612 + gen_941);
			t_sample tap_952 = m_delay_58.read_linear(add_943);
			t_sample mul_949 = (tap_952 * rsub_942);
			t_sample add_948 = (mul_949 + mul_946);
			t_sample mul_945 = (add_948 * gen_557);
			t_sample add_950 = (fromFILTERS_c45L_83 + mul_945);
			t_sample gen_957 = add_950;
			t_sample history_947_next_956 = fixdenorm(add_948);
			t_sample mul_961 = (m_history_55 * rsub_959);
			t_sample add_958 = (zeroL_612 + gen_940);
			t_sample tap_967 = m_delay_56.read_linear(add_958);
			t_sample mul_964 = (tap_967 * rsub_942);
			t_sample add_963 = (mul_964 + mul_961);
			t_sample mul_960 = (add_963 * gen_557);
			t_sample add_965 = (fromFILTERS_c45L_83 + mul_960);
			t_sample gen_972 = add_965;
			t_sample history_962_next_971 = fixdenorm(add_963);
			t_sample mul_976 = (m_history_53 * rsub_974);
			t_sample add_973 = (zeroL_612 + gen_939);
			t_sample tap_982 = m_delay_54.read_linear(add_973);
			t_sample mul_979 = (tap_982 * rsub_942);
			t_sample add_978 = (mul_979 + mul_976);
			t_sample mul_975 = (add_978 * gen_557);
			t_sample add_980 = (fromFILTERS_c45L_83 + mul_975);
			t_sample gen_987 = add_980;
			t_sample history_977_next_986 = fixdenorm(add_978);
			t_sample mul_991 = (m_history_51 * rsub_989);
			t_sample add_988 = (zeroL_612 + gen_938);
			t_sample tap_997 = m_delay_52.read_linear(add_988);
			t_sample mul_994 = (tap_997 * rsub_942);
			t_sample add_993 = (mul_994 + mul_991);
			t_sample mul_990 = (add_993 * gen_557);
			t_sample add_995 = (fromFILTERS_c45L_83 + mul_990);
			t_sample gen_1002 = add_995;
			t_sample history_992_next_1001 = fixdenorm(add_993);
			t_sample mul_1006 = (m_history_49 * rsub_1004);
			t_sample add_1003 = (zeroL_612 + gen_937);
			t_sample tap_1012 = m_delay_50.read_linear(add_1003);
			t_sample mul_1009 = (tap_1012 * rsub_942);
			t_sample add_1008 = (mul_1009 + mul_1006);
			t_sample mul_1005 = (add_1008 * gen_557);
			t_sample add_1010 = (fromFILTERS_c45L_83 + mul_1005);
			t_sample gen_1017 = add_1010;
			t_sample history_1007_next_1016 = fixdenorm(add_1008);
			t_sample mul_1021 = (m_history_47 * rsub_1019);
			t_sample add_1018 = (zeroL_612 + gen_936);
			t_sample tap_1027 = m_delay_48.read_linear(add_1018);
			t_sample mul_1024 = (tap_1027 * rsub_942);
			t_sample add_1023 = (mul_1024 + mul_1021);
			t_sample mul_1020 = (add_1023 * gen_557);
			t_sample add_1025 = (fromFILTERS_c45L_83 + mul_1020);
			t_sample gen_1032 = add_1025;
			t_sample history_1022_next_1031 = fixdenorm(add_1023);
			t_sample mul_1036 = (m_history_45 * rsub_1034);
			t_sample add_1033 = (zeroL_612 + gen_935);
			t_sample tap_1042 = m_delay_46.read_linear(add_1033);
			t_sample mul_1039 = (tap_1042 * rsub_942);
			t_sample add_1038 = (mul_1039 + mul_1036);
			t_sample mul_1035 = (add_1038 * gen_557);
			t_sample add_1040 = (fromFILTERS_c45L_83 + mul_1035);
			t_sample gen_1047 = add_1040;
			t_sample history_1037_next_1046 = fixdenorm(add_1038);
			t_sample mul_1051 = (m_history_43 * rsub_1049);
			t_sample add_1048 = (zeroL_612 + gen_934);
			t_sample tap_1057 = m_delay_44.read_linear(add_1048);
			t_sample mul_1054 = (tap_1057 * rsub_942);
			t_sample add_1053 = (mul_1054 + mul_1051);
			t_sample mul_1050 = (add_1053 * gen_557);
			t_sample add_1055 = (fromFILTERS_c45L_83 + mul_1050);
			t_sample gen_1062 = add_1055;
			t_sample history_1052_next_1061 = fixdenorm(add_1053);
			t_sample mul_1063 = ((((((((gen_1062 + gen_1047) + gen_1032) + gen_1017) + gen_1002) + gen_987) + gen_972) + gen_957) * ((t_sample)0.125));
			t_sample gen_1065 = mul_1063;
			t_sample mul_401 = (gen_1065 * ((t_sample)-0.5));
			t_sample mul_391 = (div_392 * escala_Size_410);
			t_sample mul_393 = (((int)255) * mul_391);
			t_sample add_395 = (((int)0) + mul_393);
			t_sample tap_403 = m_delay_42.read_linear(add_395);
			t_sample tap_398 = m_delay_41.read_linear(add_395);
			t_sample mul_396 = (tap_398 * ((t_sample)0.5));
			t_sample add_399 = (mul_401 + (tap_403 + mul_396));
			t_sample gen_407 = add_399;
			t_sample mul_384 = (gen_407 * ((t_sample)-0.5));
			t_sample mul_374 = (div_375 * escala_Size_410);
			t_sample mul_376 = (((int)556) * mul_374);
			t_sample add_378 = (((int)0) + mul_376);
			t_sample tap_386 = m_delay_40.read_linear(add_378);
			t_sample tap_381 = m_delay_39.read_linear(add_378);
			t_sample mul_379 = (tap_381 * ((t_sample)0.5));
			t_sample add_382 = (mul_384 + (tap_386 + mul_379));
			t_sample gen_390 = add_382;
			t_sample mul_367 = (gen_390 * ((t_sample)-0.5));
			t_sample mul_357 = (div_358 * escala_Size_410);
			t_sample mul_359 = (((int)441) * mul_357);
			t_sample add_361 = (((int)0) + mul_359);
			t_sample tap_369 = m_delay_38.read_linear(add_361);
			t_sample tap_364 = m_delay_37.read_linear(add_361);
			t_sample mul_362 = (tap_364 * ((t_sample)0.5));
			t_sample add_365 = (mul_367 + (tap_369 + mul_362));
			t_sample gen_373 = add_365;
			t_sample mul_350 = (gen_373 * ((t_sample)-0.5));
			t_sample mul_340 = (div_341 * escala_Size_410);
			t_sample mul_342 = (((int)341) * mul_340);
			t_sample add_344 = (((int)0) + mul_342);
			t_sample tap_352 = m_delay_36.read_linear(add_344);
			t_sample tap_347 = m_delay_35.read_linear(add_344);
			t_sample mul_345 = (tap_347 * ((t_sample)0.5));
			t_sample add_348 = (mul_350 + (tap_352 + mul_345));
			t_sample gen_356 = add_348;
			t_sample gen_409 = gen_356;
			t_sample matrizMS_c45L_563 = gen_409;
			t_sample fromFILTERS_c45R_82 = gen_215;
			t_sample mul_686 = (div_701 * escala_Size_411);
			t_sample mul_689 = (((int)1188) * mul_686);
			t_sample mul_631 = (m_history_34 * ((t_sample)0.999));
			t_sample mul_630 = (mul_689 * ((t_sample)0.001));
			t_sample add_633 = (mul_630 + mul_631);
			t_sample gen_637 = add_633;
			t_sample history_632_next_636 = fixdenorm(add_633);
			t_sample gen_718 = gen_637;
			t_sample mul_691 = (((int)1356) * mul_686);
			t_sample mul_639 = (m_history_33 * ((t_sample)0.999));
			t_sample mul_638 = (mul_691 * ((t_sample)0.001));
			t_sample add_641 = (mul_638 + mul_639);
			t_sample gen_645 = add_641;
			t_sample history_640_next_644 = fixdenorm(add_641);
			t_sample gen_717 = gen_645;
			t_sample mul_693 = (((int)1277) * mul_686);
			t_sample mul_647 = (m_history_32 * ((t_sample)0.999));
			t_sample mul_646 = (mul_693 * ((t_sample)0.001));
			t_sample add_649 = (mul_646 + mul_647);
			t_sample gen_653 = add_649;
			t_sample history_648_next_652 = fixdenorm(add_649);
			t_sample gen_716 = gen_653;
			t_sample mul_702 = (((int)1557) * mul_686);
			t_sample mul_679 = (m_history_31 * ((t_sample)0.999));
			t_sample mul_678 = (mul_702 * ((t_sample)0.001));
			t_sample add_681 = (mul_678 + mul_679);
			t_sample gen_685 = add_681;
			t_sample history_680_next_684 = fixdenorm(add_681);
			t_sample gen_712 = gen_685;
			t_sample mul_697 = (((int)1491) * mul_686);
			t_sample mul_663 = (m_history_30 * ((t_sample)0.999));
			t_sample mul_662 = (mul_697 * ((t_sample)0.001));
			t_sample add_665 = (mul_662 + mul_663);
			t_sample gen_669 = add_665;
			t_sample history_664_next_668 = fixdenorm(add_665);
			t_sample gen_714 = gen_669;
			t_sample mul_699 = (((int)1617) * mul_686);
			t_sample mul_671 = (m_history_29 * ((t_sample)0.999));
			t_sample mul_670 = (mul_699 * ((t_sample)0.001));
			t_sample add_673 = (mul_670 + mul_671);
			t_sample gen_677 = add_673;
			t_sample history_672_next_676 = fixdenorm(add_673);
			t_sample gen_713 = gen_677;
			t_sample mul_695 = (((int)1422) * mul_686);
			t_sample mul_655 = (m_history_28 * ((t_sample)0.999));
			t_sample mul_654 = (mul_695 * ((t_sample)0.001));
			t_sample add_657 = (mul_654 + mul_655);
			t_sample gen_661 = add_657;
			t_sample history_656_next_660 = fixdenorm(add_657);
			t_sample gen_715 = gen_661;
			t_sample mul_687 = (((int)1116) * mul_686);
			t_sample mul_623 = (m_history_27 * ((t_sample)0.999));
			t_sample mul_622 = (mul_687 * ((t_sample)0.001));
			t_sample add_625 = (mul_622 + mul_623);
			t_sample gen_629 = add_625;
			t_sample history_624_next_628 = fixdenorm(add_625);
			t_sample gen_719 = gen_629;
			t_sample mul_724 = (m_history_25 * rsub_722);
			t_sample add_721 = (zeroR_613 + gen_719);
			t_sample tap_730 = m_delay_26.read_linear(add_721);
			t_sample mul_727 = (tap_730 * rsub_720);
			t_sample add_726 = (mul_727 + mul_724);
			t_sample mul_723 = (add_726 * gen_557);
			t_sample add_728 = (fromFILTERS_c45R_82 + mul_723);
			t_sample gen_735 = add_728;
			t_sample history_725_next_734 = fixdenorm(add_726);
			t_sample mul_739 = (m_history_23 * rsub_737);
			t_sample add_736 = (zeroR_613 + gen_718);
			t_sample tap_745 = m_delay_24.read_linear(add_736);
			t_sample mul_742 = (tap_745 * rsub_720);
			t_sample add_741 = (mul_742 + mul_739);
			t_sample mul_738 = (add_741 * gen_557);
			t_sample add_743 = (fromFILTERS_c45R_82 + mul_738);
			t_sample gen_750 = add_743;
			t_sample history_740_next_749 = fixdenorm(add_741);
			t_sample mul_754 = (m_history_21 * rsub_752);
			t_sample add_751 = (zeroR_613 + gen_717);
			t_sample tap_760 = m_delay_22.read_linear(add_751);
			t_sample mul_757 = (tap_760 * rsub_720);
			t_sample add_756 = (mul_757 + mul_754);
			t_sample mul_753 = (add_756 * gen_557);
			t_sample add_758 = (fromFILTERS_c45R_82 + mul_753);
			t_sample gen_765 = add_758;
			t_sample history_755_next_764 = fixdenorm(add_756);
			t_sample mul_769 = (m_history_19 * rsub_767);
			t_sample add_766 = (zeroR_613 + gen_716);
			t_sample tap_775 = m_delay_20.read_linear(add_766);
			t_sample mul_772 = (tap_775 * rsub_720);
			t_sample add_771 = (mul_772 + mul_769);
			t_sample mul_768 = (add_771 * gen_557);
			t_sample add_773 = (fromFILTERS_c45R_82 + mul_768);
			t_sample gen_780 = add_773;
			t_sample history_770_next_779 = fixdenorm(add_771);
			t_sample mul_784 = (m_history_17 * rsub_782);
			t_sample add_781 = (zeroR_613 + gen_715);
			t_sample tap_790 = m_delay_18.read_linear(add_781);
			t_sample mul_787 = (tap_790 * rsub_720);
			t_sample add_786 = (mul_787 + mul_784);
			t_sample mul_783 = (add_786 * gen_557);
			t_sample add_788 = (fromFILTERS_c45R_82 + mul_783);
			t_sample gen_795 = add_788;
			t_sample history_785_next_794 = fixdenorm(add_786);
			t_sample mul_799 = (m_history_15 * rsub_797);
			t_sample add_796 = (zeroR_613 + gen_714);
			t_sample tap_805 = m_delay_16.read_linear(add_796);
			t_sample mul_802 = (tap_805 * rsub_720);
			t_sample add_801 = (mul_802 + mul_799);
			t_sample mul_798 = (add_801 * gen_557);
			t_sample add_803 = (fromFILTERS_c45R_82 + mul_798);
			t_sample gen_810 = add_803;
			t_sample history_800_next_809 = fixdenorm(add_801);
			t_sample mul_814 = (m_history_13 * rsub_812);
			t_sample add_811 = (zeroR_613 + gen_713);
			t_sample tap_820 = m_delay_14.read_linear(add_811);
			t_sample mul_817 = (tap_820 * rsub_720);
			t_sample add_816 = (mul_817 + mul_814);
			t_sample mul_813 = (add_816 * gen_557);
			t_sample add_818 = (fromFILTERS_c45R_82 + mul_813);
			t_sample gen_825 = add_818;
			t_sample history_815_next_824 = fixdenorm(add_816);
			t_sample mul_829 = (m_history_11 * rsub_827);
			t_sample add_826 = (zeroR_613 + gen_712);
			t_sample tap_835 = m_delay_12.read_linear(add_826);
			t_sample mul_832 = (tap_835 * rsub_720);
			t_sample add_831 = (mul_832 + mul_829);
			t_sample mul_828 = (add_831 * gen_557);
			t_sample add_833 = (fromFILTERS_c45R_82 + mul_828);
			t_sample gen_840 = add_833;
			t_sample history_830_next_839 = fixdenorm(add_831);
			t_sample mul_841 = ((((((((gen_840 + gen_825) + gen_810) + gen_795) + gen_780) + gen_765) + gen_750) + gen_735) * ((t_sample)0.125));
			t_sample gen_843 = mul_841;
			t_sample mul_328 = (gen_843 * ((t_sample)-0.5));
			t_sample mul_318 = (div_319 * escala_Size_337);
			t_sample mul_320 = (((int)255) * mul_318);
			t_sample add_322 = (((int)0) + mul_320);
			t_sample tap_330 = m_delay_10.read_linear(add_322);
			t_sample tap_325 = m_delay_9.read_linear(add_322);
			t_sample mul_323 = (tap_325 * ((t_sample)0.5));
			t_sample add_326 = (mul_328 + (tap_330 + mul_323));
			t_sample gen_334 = add_326;
			t_sample mul_311 = (gen_334 * ((t_sample)-0.5));
			t_sample mul_301 = (div_302 * escala_Size_337);
			t_sample mul_303 = (((int)556) * mul_301);
			t_sample add_305 = (((int)0) + mul_303);
			t_sample tap_313 = m_delay_8.read_linear(add_305);
			t_sample tap_308 = m_delay_7.read_linear(add_305);
			t_sample mul_306 = (tap_308 * ((t_sample)0.5));
			t_sample add_309 = (mul_311 + (tap_313 + mul_306));
			t_sample gen_317 = add_309;
			t_sample mul_294 = (gen_317 * ((t_sample)-0.5));
			t_sample mul_284 = (div_285 * escala_Size_337);
			t_sample mul_286 = (((int)441) * mul_284);
			t_sample add_288 = (((int)0) + mul_286);
			t_sample tap_296 = m_delay_6.read_linear(add_288);
			t_sample tap_291 = m_delay_5.read_linear(add_288);
			t_sample mul_289 = (tap_291 * ((t_sample)0.5));
			t_sample add_292 = (mul_294 + (tap_296 + mul_289));
			t_sample gen_300 = add_292;
			t_sample mul_277 = (gen_300 * ((t_sample)-0.5));
			t_sample mul_267 = (div_268 * escala_Size_337);
			t_sample mul_269 = (((int)341) * mul_267);
			t_sample add_271 = (((int)0) + mul_269);
			t_sample tap_279 = m_delay_4.read_linear(add_271);
			t_sample tap_274 = m_delay_3.read_linear(add_271);
			t_sample mul_272 = (tap_274 * ((t_sample)0.5));
			t_sample add_275 = (mul_277 + (tap_279 + mul_272));
			t_sample gen_283 = add_275;
			t_sample gen_336 = gen_283;
			t_sample matrizMS_c45R_562 = gen_336;
			t_sample add_582 = (matrizMS_c45L_563 + matrizMS_c45R_562);
			t_sample mul_580 = (add_582 * sqrt_578);
			t_sample sub_581 = (matrizMS_c45L_563 - matrizMS_c45R_562);
			t_sample mul_579 = (sub_581 * sqrt_577);
			t_sample add_576 = (mul_580 + mul_579);
			t_sample mul_567 = (add_576 * scale_568);
			t_sample filterL_252 = mul_567;
			t_sample sub_575 = (mul_580 - mul_579);
			t_sample mul_566 = (sub_575 * scale_568);
			t_sample filterR_251 = mul_566;
			t_sample return_181;
			t_sample return_182;
			eq3bandas_d_d_d_d_d_d_d_d_i(filterL_252, filterR_251, gen_250, gen_242, gen_234, gen_462, gen_454, gen_446, ((int)1), return_181, return_182);
			t_sample expr_503 = return_181;
			t_sample expr_504 = return_182;
			t_sample gen_505 = expr_503;
			t_sample fromFilterL_254 = gen_505;
			t_sample mix_1431 = (mul_567 + (onOffEQ_216 * (fromFilterL_254 - mul_567)));
			t_sample mix_226 = mix_1431;
			t_sample mix_1432 = (mul_566 + (onOffEQ_216 * (expr_504 - mul_566)));
			t_sample tap_45 = m_delay_2.read_step(((int)300));
			t_sample mul_38 = (mix_226 * mix_226);
			t_sample add_42 = (m_history_1 + mul_38);
			t_sample sub_41 = (add_42 - tap_45);
			t_sample div_39 = (sub_41 * ((t_sample)0.0033333333333333));
			t_sample sqrt_37 = sqrt(div_39);
			t_sample history_40_next_49 = fixdenorm(sub_41);
			t_sample atodb_61 = atodb(sqrt_37);
			t_sample clamp_36 = ((atodb_61 <= min_183) ? min_183 : ((atodb_61 >= ((int)0)) ? ((int)0) : atodb_61));
			int gt_60 = (clamp_36 > m_s_thd_126);
			t_sample sub_59 = (m_s_thd_126 - clamp_36);
			t_sample mul_56 = (sub_59 * rsub_57);
			t_sample dbtoa_54 = dbtoa(mul_56);
			t_sample orange_1435 = (dbtoa_54 - ((int)1));
			int sub_1436 = (gt_60 - ((int)0));
			t_sample scale_1433 = ((safepow((sub_1436 * ((t_sample)1)), ((int)1)) * orange_1435) + ((int)1));
			__m_slide_184 = fixdenorm((__m_slide_184 + (((scale_1433 > __m_slide_184) ? iup_185 : idown_186) * (scale_1433 - __m_slide_184))));
			t_sample slide_53 = __m_slide_184;
			t_sample mul_62 = (mix_226 * slide_53);
			t_sample mul_20 = (mul_62 * gen_17);
			t_sample mix_1437 = (mix_226 + (gen_8 * (mul_20 - mix_226)));
			int gt_30 = (clamp_36 > m_s_thd_126);
			t_sample sub_29 = (m_s_thd_126 - clamp_36);
			t_sample mul_26 = (sub_29 * rsub_27);
			t_sample dbtoa_24 = dbtoa(mul_26);
			t_sample orange_1440 = (dbtoa_24 - ((int)1));
			int sub_1441 = (gt_30 - ((int)0));
			t_sample scale_1438 = ((safepow((sub_1441 * ((t_sample)1)), ((int)1)) * orange_1440) + ((int)1));
			__m_slide_187 = fixdenorm((__m_slide_187 + (((scale_1438 > __m_slide_187) ? iup_188 : idown_189) * (scale_1438 - __m_slide_187))));
			t_sample slide_23 = __m_slide_187;
			t_sample mul_31 = (mix_1432 * slide_23);
			t_sample mul_19 = (mul_31 * gen_17);
			t_sample mix_1442 = (mix_1432 + (gen_8 * (mul_19 - mix_1432)));
			t_sample mix_1443 = (mix_1419 + (gen_420 * (mix_1437 - mix_1419)));
			t_sample mul_438 = (mix_1443 * gen_436);
			t_sample out1 = mul_438;
			t_sample mix_1444 = (mix_1425 + (gen_420 * (mix_1442 - mix_1425)));
			t_sample mul_437 = (mix_1444 * gen_436);
			t_sample out2 = mul_437;
			m_history_104 = history_431_next_435;
			m_history_103 = history_3_next_7;
			m_history_102 = history_12_next_16;
			m_history_101 = history_595_next_599;
			m_history_100 = history_415_next_419;
			m_history_99 = history_423_next_427;
			m_history_98 = history_219_next_223;
			m_history_97 = history_587_next_591;
			m_history_96 = history_603_next_607;
			m_history_95 = history_245_next_249;
			m_history_94 = history_237_next_241;
			m_history_93 = history_229_next_233;
			m_history_92 = history_457_next_461;
			m_history_91 = history_449_next_453;
			m_history_90 = history_441_next_445;
			m_history_89 = history_520_next_524;
			m_history_88 = history_257_next_261;
			m_history_87 = history_473_next_477;
			m_history_86 = history_465_next_469;
			m_history_85 = history_552_next_556;
			m_history_84 = history_512_next_516;
			m_history_83 = history_544_next_548;
			m_history_82 = history_149_next_164;
			m_history_73 = history_100_next_120;
			m_history_72 = history_94_next_121;
			m_history_71 = history_90_next_122;
			m_history_70 = history_96_next_123;
			m_history_69 = history_106_next_124;
			m_history_68 = history_92_next_125;
			m_history_67 = history_102_next_126;
			m_history_74 = history_104_next_119;
			m_history_81 = history_135_next_165;
			m_history_80 = history_139_next_166;
			m_history_79 = history_145_next_167;
			m_history_78 = history_151_next_168;
			m_history_77 = history_141_next_169;
			m_history_76 = history_137_next_170;
			m_history_75 = history_147_next_171;
			m_history_66 = history_862_next_866;
			m_history_43 = history_1052_next_1061;
			m_delay_44.write(add_1055);
			m_history_45 = history_1037_next_1046;
			m_delay_46.write(add_1040);
			m_history_47 = history_1022_next_1031;
			m_delay_48.write(add_1025);
			m_history_49 = history_1007_next_1016;
			m_delay_50.write(add_1010);
			m_history_51 = history_992_next_1001;
			m_delay_52.write(add_995);
			m_history_53 = history_977_next_986;
			m_delay_54.write(add_980);
			m_history_55 = history_962_next_971;
			m_delay_56.write(add_965);
			m_history_57 = history_947_next_956;
			m_delay_58.write(add_950);
			m_history_65 = history_886_next_890;
			m_history_64 = history_878_next_882;
			m_history_63 = history_902_next_906;
			m_history_62 = history_854_next_858;
			m_history_61 = history_846_next_850;
			m_history_60 = history_870_next_874;
			m_history_59 = history_894_next_898;
			m_delay_42.write(gen_1065);
			m_delay_35.write(add_348);
			m_delay_36.write(gen_373);
			m_delay_37.write(add_365);
			m_delay_38.write(gen_390);
			m_delay_39.write(add_382);
			m_delay_40.write(gen_407);
			m_delay_41.write(add_399);
			m_history_34 = history_632_next_636;
			m_history_11 = history_830_next_839;
			m_delay_12.write(add_833);
			m_history_13 = history_815_next_824;
			m_delay_14.write(add_818);
			m_history_15 = history_800_next_809;
			m_delay_16.write(add_803);
			m_history_17 = history_785_next_794;
			m_delay_18.write(add_788);
			m_history_19 = history_770_next_779;
			m_delay_20.write(add_773);
			m_history_21 = history_755_next_764;
			m_delay_22.write(add_758);
			m_history_23 = history_740_next_749;
			m_delay_24.write(add_743);
			m_history_25 = history_725_next_734;
			m_delay_26.write(add_728);
			m_history_33 = history_640_next_644;
			m_history_32 = history_648_next_652;
			m_history_31 = history_680_next_684;
			m_history_30 = history_664_next_668;
			m_history_29 = history_672_next_676;
			m_history_28 = history_656_next_660;
			m_history_27 = history_624_next_628;
			m_delay_10.write(gen_843);
			m_delay_3.write(add_275);
			m_delay_4.write(gen_300);
			m_delay_5.write(add_292);
			m_delay_6.write(gen_317);
			m_delay_7.write(add_309);
			m_delay_8.write(gen_334);
			m_delay_9.write(add_326);
			m_delay_2.write(mul_38);
			m_history_1 = history_40_next_49;
			m_delay_2.step();
			m_delay_3.step();
			m_delay_4.step();
			m_delay_5.step();
			m_delay_6.step();
			m_delay_7.step();
			m_delay_8.step();
			m_delay_9.step();
			m_delay_10.step();
			m_delay_12.step();
			m_delay_14.step();
			m_delay_16.step();
			m_delay_18.step();
			m_delay_20.step();
			m_delay_22.step();
			m_delay_24.step();
			m_delay_26.step();
			m_delay_35.step();
			m_delay_36.step();
			m_delay_37.step();
			m_delay_38.step();
			m_delay_39.step();
			m_delay_40.step();
			m_delay_41.step();
			m_delay_42.step();
			m_delay_44.step();
			m_delay_46.step();
			m_delay_48.step();
			m_delay_50.step();
			m_delay_52.step();
			m_delay_54.step();
			m_delay_56.step();
			m_delay_58.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_p_hiFreq(t_param _value) {
		m_p_hiFreq_105 = (_value < 800 ? 800 : (_value > 15000 ? 15000 : _value));
	};
	inline void set_g_freeze(t_param _value) {
		m_g_freeze_106 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_r_onoffCOMP(t_param _value) {
		m_r_onoffCOMP_107 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_k_lpf(t_param _value) {
		m_k_lpf_108 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_t_ratio(t_param _value) {
		m_t_ratio_109 = (_value < 1 ? 1 : (_value > 10 ? 10 : _value));
	};
	inline void set_v_rel(t_param _value) {
		m_v_rel_110 = (_value < 10 ? 10 : (_value > 500 ? 500 : _value));
	};
	inline void set_i_peakGain(t_param _value) {
		m_i_peakGain_111 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_c_reflect(t_param _value) {
		m_c_reflect_112 = (_value < 0.001 ? 0.001 : (_value > 0.985 ? 0.985 : _value));
	};
	inline void set_d_damp(t_param _value) {
		m_d_damp_113 = (_value < 0.001 ? 0.001 : (_value > 1 ? 1 : _value));
	};
	inline void set_b_drywet(t_param _value) {
		m_b_drywet_114 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_u_atk(t_param _value) {
		m_u_atk_115 = (_value < 10 ? 10 : (_value > 250 ? 250 : _value));
	};
	inline void set_a_input(t_param _value) {
		m_a_input_116 = (_value < -72 ? -72 : (_value > 0 ? 0 : _value));
	};
	inline void set_f_st(t_param _value) {
		m_f_st_117 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_o_peakFreq(t_param _value) {
		m_o_peakFreq_118 = (_value < 100 ? 100 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_l_hpf(t_param _value) {
		m_l_hpf_119 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_e_size(t_param _value) {
		m_e_size_120 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_h_lowGain(t_param _value) {
		m_h_lowGain_121 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_q_onoffEQ(t_param _value) {
		m_q_onoffEQ_122 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_n_lowFreq(t_param _value) {
		m_n_lowFreq_123 = (_value < 20 ? 20 : (_value > 800 ? 800 : _value));
	};
	inline void set_m_output(t_param _value) {
		m_m_output_124 = (_value < -72 ? -72 : (_value > 0 ? 0 : _value));
	};
	inline void set_j_hiGain(t_param _value) {
		m_j_hiGain_125 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_s_thd(t_param _value) {
		m_s_thd_126 = (_value < -50 ? -50 : (_value > 0 ? 0 : _value));
	};
	inline void set_w_makeup(t_param _value) {
		m_w_makeup_127 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_140;
		t_sample return_141;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_140, return_141);
		t_sample x_497 = return_140;
		sigR = return_141;
		t_sample return_165;
		t_sample return_166;
		peak_d_d_d_d_i(x_497, sigR, pf, pg, bw, return_165, return_166);
		t_sample x_500 = return_165;
		sigR = return_166;
		t_sample return_179;
		t_sample return_180;
		hishelf_d_d_d_d(x_500, sigR, hf, hg, return_179, return_180);
		t_sample x_502 = return_179;
		sigR = return_180;
		out1 = x_502;
		out2 = sigR;
		
	};
	inline void lowshelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_135(freq) != ((int)0)) || (__m_change_136(db) != ((int)0)))) {
			m_b_134 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_f_133 = safediv(freq, m_b_134);
			m_b_132 = ((m_b_134 * m_b_134) - ((int)1));
			m_w_131 = tan(safediv((m_f_133 * ((t_sample)3.1415926535898)), samplerate));
			m_a_130 = safediv(((int)1), (m_w_131 + ((int)1)));
			m_a_129 = (m_w_131 - ((int)1));
			
		};
		t_sample outputLowShelfL = lowshelfCore_d_d_d_d_d(sigL, m_a_130, m_a_129, m_b_132, m_w_131);
		t_sample outputLowShelfR = lowshelfCore_d_d_d_d_d_138(sigR, m_a_130, m_a_129, m_b_132, m_w_131);
		out1 = outputLowShelfL;
		out2 = outputLowShelfR;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_130, t_sample m_a_129, t_sample m_b_132, t_sample m_w_131) {
		t_sample x = (m_a_130 * (input - (m_a_129 * m_z_137)));
		t_sample output = (m_w_131 * (x + m_z_137));
		m_z_137 = x;
		return ((output * m_b_132) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_138(t_sample input, t_sample m_a_130, t_sample m_a_129, t_sample m_b_132, t_sample m_w_131) {
		t_sample x = (m_a_130 * (input - (m_a_129 * m_z_139)));
		t_sample output = (m_w_131 * (x + m_z_139));
		m_z_139 = x;
		return ((output * m_b_132) + input);
		
	};
	inline void peak_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_152(freq) != ((int)0)) || (__m_change_153(db) != ((int)0))) || (__m_change_154(bw) != ((int)0)))) {
			m_w_151 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_150 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_150 * m_b_150) - ((int)1));
			m_d_149 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_155 = safediv(((m_d_149 * m_d_149) - ((int)1)), (m_d_149 * m_b_150));
			m_d_148 = ((v_155 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_155 >= ((int)100)) ? ((int)100) : v_155));
			m_d_147 = (m_d_148 * b);
			m_wq_146 = (m_d_148 * m_w_151);
			m_w_145 = (m_w_151 * m_w_151);
			m_a_144 = safediv(((int)1), ((((int)1) + m_w_145) + m_wq_146));
			m_a_143 = ((m_w_145 - ((int)1)) * ((int)2));
			m_a_142 = ((((int)1) + m_w_145) - m_wq_146);
			
		};
		t_sample outputPeakL = peakCore_d_d_d_d_d_d(sigL, m_w_151, m_d_147, m_a_144, m_a_143, m_a_142);
		t_sample outputPeakR = peakCore_d_d_d_d_d_d_160(sigR, m_w_151, m_d_147, m_a_144, m_a_143, m_a_142);
		out1 = outputPeakL;
		out2 = outputPeakR;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_151, t_sample m_d_147, t_sample m_a_144, t_sample m_a_143, t_sample m_a_142) {
		t_sample output = ((input - m_z_158) * m_w_151);
		m_z_158 = m_z_159;
		m_z_159 = input;
		t_sample output_498 = (m_a_144 * ((output - (m_a_143 * m_z_157)) - (m_a_142 * m_z_156)));
		m_z_156 = m_z_157;
		m_z_157 = output_498;
		t_sample output_499 = (input + (output_498 * m_d_147));
		return output_499;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_160(t_sample input, t_sample m_w_151, t_sample m_d_147, t_sample m_a_144, t_sample m_a_143, t_sample m_a_142) {
		t_sample output = ((input - m_z_163) * m_w_151);
		m_z_163 = m_z_164;
		m_z_164 = input;
		t_sample output_498 = (m_a_144 * ((output - (m_a_143 * m_z_162)) - (m_a_142 * m_z_161)));
		m_z_161 = m_z_162;
		m_z_162 = output_498;
		t_sample output_499 = (input + (output_498 * m_d_147));
		return output_499;
		
	};
	inline void hishelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_173(freq) != ((int)0)) || (__m_change_174(db) != ((int)0)))) {
			m_b_172 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_175 = (freq * m_b_172);
			m_f_171 = ((samplerate < mina_175) ? samplerate : mina_175);
			m_b_170 = ((m_b_172 * m_b_172) - ((int)1));
			m_w_169 = tan(safediv((((m_f_171 < ((int)0)) ? ((int)0) : m_f_171) * ((t_sample)3.1415926535898)), samplerate));
			m_a_168 = safediv(((int)1), (m_w_169 + ((int)1)));
			m_a_167 = (m_w_169 - ((int)1));
			
		};
		t_sample outputHighShelfL = hishelfCore_d_d_d_d(sigL, m_a_168, m_a_167, m_b_170);
		t_sample outputHighShelfR = hishelfCore_d_d_d_d_177(sigR, m_a_168, m_a_167, m_b_170);
		out1 = outputHighShelfL;
		out2 = outputHighShelfR;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_168, t_sample m_a_167, t_sample m_b_170) {
		t_sample x = (m_a_168 * (input - (m_a_167 * m_z_176)));
		t_sample output = (x - m_z_176);
		m_z_176 = x;
		t_sample output_501 = ((output * m_b_170) + input);
		return output_501;
		
	};
	inline t_sample hishelfCore_d_d_d_d_177(t_sample input, t_sample m_a_168, t_sample m_a_167, t_sample m_b_170) {
		t_sample x = (m_a_168 * (input - (m_a_167 * m_z_178)));
		t_sample output = (x - m_z_178);
		m_z_178 = x;
		t_sample output_501 = ((output * m_b_170) + input);
		return output_501;
		
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 23; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

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
		case 0: self->set_a_input(value); break;
		case 1: self->set_b_drywet(value); break;
		case 2: self->set_c_reflect(value); break;
		case 3: self->set_d_damp(value); break;
		case 4: self->set_e_size(value); break;
		case 5: self->set_f_st(value); break;
		case 6: self->set_g_freeze(value); break;
		case 7: self->set_h_lowGain(value); break;
		case 8: self->set_i_peakGain(value); break;
		case 9: self->set_j_hiGain(value); break;
		case 10: self->set_k_lpf(value); break;
		case 11: self->set_l_hpf(value); break;
		case 12: self->set_m_output(value); break;
		case 13: self->set_n_lowFreq(value); break;
		case 14: self->set_o_peakFreq(value); break;
		case 15: self->set_p_hiFreq(value); break;
		case 16: self->set_q_onoffEQ(value); break;
		case 17: self->set_r_onoffCOMP(value); break;
		case 18: self->set_s_thd(value); break;
		case 19: self->set_t_ratio(value); break;
		case 20: self->set_u_atk(value); break;
		case 21: self->set_v_rel(value); break;
		case 22: self->set_w_makeup(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_a_input_116; break;
		case 1: *value = self->m_b_drywet_114; break;
		case 2: *value = self->m_c_reflect_112; break;
		case 3: *value = self->m_d_damp_113; break;
		case 4: *value = self->m_e_size_120; break;
		case 5: *value = self->m_f_st_117; break;
		case 6: *value = self->m_g_freeze_106; break;
		case 7: *value = self->m_h_lowGain_121; break;
		case 8: *value = self->m_i_peakGain_111; break;
		case 9: *value = self->m_j_hiGain_125; break;
		case 10: *value = self->m_k_lpf_108; break;
		case 11: *value = self->m_l_hpf_119; break;
		case 12: *value = self->m_m_output_124; break;
		case 13: *value = self->m_n_lowFreq_123; break;
		case 14: *value = self->m_o_peakFreq_118; break;
		case 15: *value = self->m_p_hiFreq_105; break;
		case 16: *value = self->m_q_onoffEQ_122; break;
		case 17: *value = self->m_r_onoffCOMP_107; break;
		case 18: *value = self->m_s_thd_126; break;
		case 19: *value = self->m_t_ratio_109; break;
		case 20: *value = self->m_u_atk_115; break;
		case 21: *value = self->m_v_rel_110; break;
		case 22: *value = self->m_w_makeup_127; break;
		
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
	// initialize parameter 0 ("m_a_input_116")
	pi = self->__commonstate.params + 0;
	pi->name = "a_input";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_input_116;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -72;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_drywet_114")
	pi = self->__commonstate.params + 1;
	pi->name = "b_drywet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_drywet_114;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_reflect_112")
	pi = self->__commonstate.params + 2;
	pi->name = "c_reflect";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_reflect_112;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 0.985;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_damp_113")
	pi = self->__commonstate.params + 3;
	pi->name = "d_damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_damp_113;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_size_120")
	pi = self->__commonstate.params + 4;
	pi->name = "e_size";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_size_120;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_st_117")
	pi = self->__commonstate.params + 5;
	pi->name = "f_st";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_st_117;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_freeze_106")
	pi = self->__commonstate.params + 6;
	pi->name = "g_freeze";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_freeze_106;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_lowGain_121")
	pi = self->__commonstate.params + 7;
	pi->name = "h_lowGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_lowGain_121;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_peakGain_111")
	pi = self->__commonstate.params + 8;
	pi->name = "i_peakGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_peakGain_111;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_hiGain_125")
	pi = self->__commonstate.params + 9;
	pi->name = "j_hiGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_hiGain_125;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_lpf_108")
	pi = self->__commonstate.params + 10;
	pi->name = "k_lpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_lpf_108;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_hpf_119")
	pi = self->__commonstate.params + 11;
	pi->name = "l_hpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_hpf_119;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_output_124")
	pi = self->__commonstate.params + 12;
	pi->name = "m_output";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_output_124;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -72;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_lowFreq_123")
	pi = self->__commonstate.params + 13;
	pi->name = "n_lowFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_lowFreq_123;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 800;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_peakFreq_118")
	pi = self->__commonstate.params + 14;
	pi->name = "o_peakFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_peakFreq_118;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 2500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_hiFreq_105")
	pi = self->__commonstate.params + 15;
	pi->name = "p_hiFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_hiFreq_105;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 800;
	pi->outputmax = 15000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_onoffEQ_122")
	pi = self->__commonstate.params + 16;
	pi->name = "q_onoffEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_onoffEQ_122;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 17 ("m_r_onoffCOMP_107")
	pi = self->__commonstate.params + 17;
	pi->name = "r_onoffCOMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_onoffCOMP_107;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 18 ("m_s_thd_126")
	pi = self->__commonstate.params + 18;
	pi->name = "s_thd";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_thd_126;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -50;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_ratio_109")
	pi = self->__commonstate.params + 19;
	pi->name = "t_ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_ratio_109;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_atk_115")
	pi = self->__commonstate.params + 20;
	pi->name = "u_atk";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_atk_115;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 10;
	pi->outputmax = 250;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_rel_110")
	pi = self->__commonstate.params + 21;
	pi->name = "v_rel";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_rel_110;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 10;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_makeup_127")
	pi = self->__commonstate.params + 22;
	pi->name = "w_makeup";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_makeup_127;
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


} // JC_GENPLUGIN::
