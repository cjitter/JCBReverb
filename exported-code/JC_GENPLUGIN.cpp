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
	Change __m_change_144;
	Change __m_change_161;
	Change __m_change_143;
	Change __m_change_160;
	Change __m_change_162;
	Change __m_change_182;
	Change __m_change_181;
	DCBlock __m_dcblock_199;
	DCBlock __m_dcblock_200;
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
	t_sample m_l_hpf_134;
	t_sample m_history_135;
	t_sample m_i_peakGain_133;
	t_sample m_k_lpf_131;
	t_sample m_p_hiFreq_132;
	t_sample m_q_onoffEQ_130;
	t_sample m_a_137;
	t_sample m_a_138;
	t_sample m_w_139;
	t_sample m_history_15;
	t_sample m_history_5;
	t_sample m_g_freeze_129;
	t_sample m_b_142;
	t_sample m_b_140;
	t_sample m_f_141;
	t_sample m_z_145;
	t_sample m_d_damp_128;
	t_sample m_s_thd_126;
	t_sample m_m_output_116;
	t_sample m_f_st_117;
	t_sample m_o_peakFreq_118;
	t_sample m_r_onoffCOMP_115;
	t_sample m_n_lowFreq_113;
	t_sample m_e_size_114;
	t_sample m_b_drywet_127;
	t_sample m_w_makeup_119;
	t_sample m_j_hiGain_121;
	t_sample m_a_input_125;
	t_sample m_c_reflect_120;
	t_sample m_u_atk_124;
	t_sample m_v_rel_122;
	t_sample m_h_lowGain_123;
	t_sample m_t_ratio_112;
	t_sample m_z_147;
	t_sample m_a_151;
	t_sample m_a_176;
	t_sample m_w_177;
	t_sample m_b_178;
	t_sample m_a_175;
	t_sample m_z_171;
	t_sample m_z_172;
	t_sample m_z_170;
	t_sample m_f_179;
	t_sample samplerate;
	t_sample __m_slide_196;
	t_sample m_b_180;
	t_sample __m_slide_192;
	t_sample m_z_184;
	t_sample m_z_186;
	t_sample m_a_150;
	t_sample m_z_169;
	t_sample m_z_166;
	t_sample m_d_155;
	t_sample m_d_156;
	t_sample m_d_157;
	t_sample m_wq_154;
	t_sample m_a_152;
	t_sample m_w_153;
	t_sample m_z_167;
	t_sample m_b_158;
	t_sample m_history_4;
	t_sample m_z_165;
	t_sample m_w_159;
	t_sample m_z_164;
	t_sample m_history_2;
	t_sample m_history_1;
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
		m_t_ratio_112 = 2;
		m_n_lowFreq_113 = 500;
		m_e_size_114 = 1;
		m_r_onoffCOMP_115 = 0;
		m_m_output_116 = 1;
		m_f_st_117 = 0.5;
		m_o_peakFreq_118 = 800;
		m_w_makeup_119 = 0;
		m_c_reflect_120 = 0.86;
		m_j_hiGain_121 = 0;
		m_v_rel_122 = 100;
		m_h_lowGain_123 = 0;
		m_u_atk_124 = 10;
		m_a_input_125 = 1;
		m_s_thd_126 = -12;
		m_b_drywet_127 = 0.33;
		m_d_damp_128 = 0.8;
		m_g_freeze_129 = 0;
		m_q_onoffEQ_130 = 0;
		m_k_lpf_131 = 20000;
		m_p_hiFreq_132 = 2000;
		m_i_peakGain_133 = 0;
		m_l_hpf_134 = 20;
		m_history_135 = ((int)0);
		m_a_137 = ((int)0);
		m_a_138 = ((int)0);
		m_w_139 = ((int)0);
		m_b_140 = ((int)0);
		m_f_141 = ((int)0);
		m_b_142 = ((int)0);
		__m_change_143.reset(0);
		__m_change_144.reset(0);
		m_z_145 = ((int)0);
		m_z_147 = ((int)0);
		m_a_150 = ((int)0);
		m_a_151 = ((int)0);
		m_a_152 = ((int)0);
		m_w_153 = ((int)0);
		m_wq_154 = ((int)0);
		m_d_155 = ((int)0);
		m_d_156 = ((int)0);
		m_d_157 = ((int)0);
		m_b_158 = ((int)0);
		m_w_159 = ((int)0);
		__m_change_160.reset(0);
		__m_change_161.reset(0);
		__m_change_162.reset(0);
		m_z_164 = ((int)0);
		m_z_165 = ((int)0);
		m_z_166 = ((int)0);
		m_z_167 = ((int)0);
		m_z_169 = ((int)0);
		m_z_170 = ((int)0);
		m_z_171 = ((int)0);
		m_z_172 = ((int)0);
		m_a_175 = ((int)0);
		m_a_176 = ((int)0);
		m_w_177 = ((int)0);
		m_b_178 = ((int)0);
		m_f_179 = ((int)0);
		m_b_180 = ((int)0);
		__m_change_181.reset(0);
		__m_change_182.reset(0);
		m_z_184 = ((int)0);
		m_z_186 = ((int)0);
		__m_slide_192 = 0;
		__m_slide_196 = 0;
		__m_dcblock_199.reset();
		__m_dcblock_200.reset();
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
		t_sample mul_492 = (m_m_output_116 * ((t_sample)0.001));
		t_sample mul_55 = (m_r_onoffCOMP_115 * ((t_sample)0.001));
		t_sample mul_47 = (m_s_thd_126 * ((t_sample)0.001));
		t_sample mul_39 = (m_t_ratio_112 * ((t_sample)0.001));
		t_sample mul_31 = (m_u_atk_124 * ((t_sample)0.001));
		t_sample mul_23 = (m_v_rel_122 * ((t_sample)0.001));
		t_sample mul_13 = (m_w_makeup_119 * ((t_sample)0.001));
		t_sample mul_656 = (m_b_drywet_127 * ((t_sample)0.001));
		int eq_684 = (m_g_freeze_129 == ((int)1));
		int toSize_593 = eq_684;
		t_sample mul_484 = (toSize_593 * ((t_sample)0.001));
		t_sample mul_280 = (m_q_onoffEQ_130 * ((t_sample)0.001));
		t_sample mul_648 = (m_a_input_125 * ((t_sample)0.001));
		t_sample mul_664 = (m_f_st_117 * ((t_sample)0.001));
		t_sample mul_306 = (m_n_lowFreq_113 * ((t_sample)0.001));
		t_sample mul_298 = (m_o_peakFreq_118 * ((t_sample)0.001));
		t_sample mul_290 = (m_p_hiFreq_132 * ((t_sample)0.001));
		t_sample mul_518 = (m_h_lowGain_123 * ((t_sample)0.001));
		t_sample mul_510 = (m_i_peakGain_133 * ((t_sample)0.001));
		t_sample mul_502 = (m_j_hiGain_121 * ((t_sample)0.001));
		t_sample mul_318 = (m_e_size_114 * ((t_sample)0.001));
		t_sample rsub_1131 = (((int)1) - m_d_damp_128);
		t_sample damp_673 = rsub_1131;
		t_sample damp_674 = damp_673;
		t_sample mul_534 = (m_k_lpf_131 * ((t_sample)0.001));
		t_sample mul_526 = (m_l_hpf_134 * ((t_sample)0.001));
		int toSize_677 = toSize_593;
		t_sample rsub_679 = (((int)1) - m_c_reflect_120);
		int choice_136 = toSize_677;
		t_sample gate_678 = ((choice_136 >= 1) ? rsub_679 : 0);
		t_sample add_680 = (m_c_reflect_120 + gate_678);
		t_sample mul_613 = (add_680 * ((t_sample)0.001));
		int rsub_683 = (((int)1) - eq_684);
		t_sample mul_605 = (rsub_683 * ((t_sample)0.001));
		t_sample rsub_1005 = (((int)1) - damp_674);
		t_sample div_986 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_1007 = (((int)1) - rsub_1005);
		t_sample rsub_1022 = (((int)1) - rsub_1005);
		t_sample rsub_1037 = (((int)1) - rsub_1005);
		t_sample rsub_1052 = (((int)1) - rsub_1005);
		t_sample rsub_1067 = (((int)1) - rsub_1005);
		t_sample rsub_1082 = (((int)1) - rsub_1005);
		t_sample rsub_1097 = (((int)1) - rsub_1005);
		t_sample rsub_1112 = (((int)1) - rsub_1005);
		t_sample div_455 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_438 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_421 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_404 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_783 = (((int)1) - damp_673);
		t_sample div_764 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_785 = (((int)1) - rsub_783);
		t_sample rsub_800 = (((int)1) - rsub_783);
		t_sample rsub_815 = (((int)1) - rsub_783);
		t_sample rsub_830 = (((int)1) - rsub_783);
		t_sample rsub_845 = (((int)1) - rsub_783);
		t_sample rsub_860 = (((int)1) - rsub_783);
		t_sample rsub_875 = (((int)1) - rsub_783);
		t_sample rsub_890 = (((int)1) - rsub_783);
		t_sample div_382 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_365 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_348 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_331 = (samplerate * ((t_sample)2.2675736961451e-05));
		int maxb_191 = (-96);
		int maxb_195 = (-96);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_493 = (m_history_135 * ((t_sample)0.999));
			t_sample add_495 = (mul_492 + mul_493);
			t_sample gen_499 = add_495;
			t_sample history_494_next_498 = fixdenorm(add_495);
			t_sample mul_56 = (m_history_111 * ((t_sample)0.999));
			t_sample add_58 = (mul_55 + mul_56);
			t_sample gen_62 = add_58;
			t_sample history_57_next_61 = fixdenorm(add_58);
			t_sample mul_48 = (m_history_110 * ((t_sample)0.999));
			t_sample add_50 = (mul_47 + mul_48);
			t_sample gen_54 = add_50;
			t_sample history_49_next_53 = fixdenorm(add_50);
			t_sample thdC_11 = gen_54;
			t_sample mul_40 = (m_history_109 * ((t_sample)0.999));
			t_sample add_42 = (mul_39 + mul_40);
			t_sample gen_46 = add_42;
			t_sample history_41_next_45 = fixdenorm(add_42);
			t_sample mul_32 = (m_history_108 * ((t_sample)0.999));
			t_sample add_34 = (mul_31 + mul_32);
			t_sample gen_38 = add_34;
			t_sample history_33_next_37 = fixdenorm(add_34);
			t_sample mul_24 = (m_history_107 * ((t_sample)0.999));
			t_sample add_26 = (mul_23 + mul_24);
			t_sample gen_30 = add_26;
			t_sample history_25_next_29 = fixdenorm(add_26);
			t_sample mul_14 = (m_history_106 * ((t_sample)0.999));
			t_sample add_16 = (mul_13 + mul_14);
			t_sample gen_20 = add_16;
			t_sample history_15_next_19 = fixdenorm(add_16);
			t_sample mul_657 = (m_history_105 * ((t_sample)0.999));
			t_sample add_659 = (mul_656 + mul_657);
			t_sample gen_663 = add_659;
			t_sample history_658_next_662 = fixdenorm(add_659);
			t_sample dry_wet_636 = gen_663;
			t_sample mul_477 = (m_history_104 * ((t_sample)0.999));
			t_sample mul_476 = (dry_wet_636 * ((t_sample)0.001));
			t_sample add_479 = (mul_476 + mul_477);
			t_sample gen_483 = add_479;
			t_sample history_478_next_482 = fixdenorm(add_479);
			t_sample mul_485 = (m_history_103 * ((t_sample)0.999));
			t_sample add_487 = (mul_484 + mul_485);
			t_sample gen_491 = add_487;
			t_sample history_486_next_490 = fixdenorm(add_487);
			t_sample mul_281 = (m_history_102 * ((t_sample)0.999));
			t_sample add_283 = (mul_280 + mul_281);
			t_sample gen_287 = add_283;
			t_sample history_282_next_286 = fixdenorm(add_283);
			t_sample onOffEQ_279 = gen_287;
			t_sample mul_649 = (m_history_101 * ((t_sample)0.999));
			t_sample add_651 = (mul_648 + mul_649);
			t_sample gen_655 = add_651;
			t_sample history_650_next_654 = fixdenorm(add_651);
			t_sample input_571 = gen_655;
			t_sample mul_570 = (in2 * input_571);
			t_sample right_633 = mul_570;
			t_sample mul_572 = (in1 * input_571);
			t_sample left_600 = mul_572;
			t_sample left_634 = left_600;
			t_sample mix_1132 = (left_634 + (gen_491 * (((int)0) - left_634)));
			t_sample right_596 = right_633;
			int eq_603 = (right_596 == ((int)0));
			t_sample mul_582 = (m_history_100 * ((t_sample)0.999));
			t_sample mul_581 = (eq_603 * ((t_sample)0.001));
			t_sample add_584 = (mul_581 + mul_582);
			t_sample gen_588 = add_584;
			t_sample history_583_next_587 = fixdenorm(add_584);
			t_sample mix_1133 = (((int)0) + (gen_588 * (left_600 - ((int)0))));
			t_sample mix_599 = mix_1133;
			t_sample add_1135 = (mix_599 + right_633);
			t_sample mix_1134 = (add_1135 + (gen_491 * (((int)0) - add_1135)));
			t_sample mul_665 = (m_history_99 * ((t_sample)0.999));
			t_sample add_667 = (mul_664 + mul_665);
			t_sample gen_671 = add_667;
			t_sample history_666_next_670 = fixdenorm(add_667);
			t_sample sub_1139 = (gen_671 - ((int)0));
			t_sample scale_1136 = ((safepow((sub_1139 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_631 = scale_1136;
			t_sample mul_307 = (m_history_98 * ((t_sample)0.999));
			t_sample add_309 = (mul_306 + mul_307);
			t_sample gen_313 = add_309;
			t_sample history_308_next_312 = fixdenorm(add_309);
			t_sample mul_299 = (m_history_97 * ((t_sample)0.999));
			t_sample add_301 = (mul_298 + mul_299);
			t_sample gen_305 = add_301;
			t_sample history_300_next_304 = fixdenorm(add_301);
			t_sample mul_291 = (m_history_96 * ((t_sample)0.999));
			t_sample add_293 = (mul_290 + mul_291);
			t_sample gen_297 = add_293;
			t_sample history_292_next_296 = fixdenorm(add_293);
			t_sample mul_519 = (m_history_95 * ((t_sample)0.999));
			t_sample add_521 = (mul_518 + mul_519);
			t_sample gen_525 = add_521;
			t_sample history_520_next_524 = fixdenorm(add_521);
			t_sample mul_511 = (m_history_94 * ((t_sample)0.999));
			t_sample add_513 = (mul_510 + mul_511);
			t_sample gen_517 = add_513;
			t_sample history_512_next_516 = fixdenorm(add_513);
			t_sample mul_503 = (m_history_93 * ((t_sample)0.999));
			t_sample add_505 = (mul_502 + mul_503);
			t_sample gen_509 = add_505;
			t_sample history_504_next_508 = fixdenorm(add_505);
			t_sample sqrt_640 = sqrt(gen_671);
			t_sample rsub_672 = (((int)1) - gen_671);
			t_sample sqrt_641 = sqrt(rsub_672);
			t_sample mul_319 = (m_history_92 * ((t_sample)0.999));
			t_sample add_321 = (mul_318 + mul_319);
			t_sample gen_325 = add_321;
			t_sample history_320_next_324 = fixdenorm(add_321);
			t_sample escala_Size_475 = gen_325;
			t_sample escala_Size_473 = escala_Size_475;
			t_sample escala_Size_400 = escala_Size_475;
			t_sample escala_Size_474 = escala_Size_475;
			t_sample mul_535 = (m_history_91 * ((t_sample)0.999));
			t_sample add_537 = (mul_534 + mul_535);
			t_sample gen_541 = add_537;
			t_sample history_536_next_540 = fixdenorm(add_537);
			t_sample mul_527 = (m_history_90 * ((t_sample)0.999));
			t_sample add_529 = (mul_526 + mul_527);
			t_sample gen_533 = add_529;
			t_sample history_528_next_532 = fixdenorm(add_529);
			t_sample toMoud_604 = gen_671;
			t_sample mul_614 = (m_history_89 * ((t_sample)0.999));
			t_sample add_616 = (mul_613 + mul_614);
			t_sample gen_620 = add_616;
			t_sample history_615_next_619 = fixdenorm(add_616);
			t_sample escala_Size_328 = escala_Size_475;
			t_sample mul_326 = (((int)23) * escala_Size_328);
			t_sample left_628 = left_600;
			t_sample right_627 = right_633;
			t_sample left_595 = left_600;
			t_sample right_594 = right_633;
			int eq_597 = (left_595 == right_594);
			t_sample mul_574 = (m_history_88 * ((t_sample)0.999));
			t_sample mul_573 = (eq_597 * ((t_sample)0.001));
			t_sample add_576 = (mul_573 + mul_574);
			t_sample gen_580 = add_576;
			t_sample history_575_next_579 = fixdenorm(add_576);
			t_sample add_1141 = (gen_580 + gen_588);
			t_sample mix_1140 = (((int)0) + (add_1141 * (toMoud_604 - ((int)0))));
			t_sample mix_602 = mix_1140;
			t_sample mix_1142 = (((int)0) + (mix_602 * ((int)0)));
			t_sample mix_624 = mix_1142;
			t_sample zeroL_675 = mix_624;
			t_sample mix_1143 = (((int)0) + (mix_602 * (mul_326 - ((int)0))));
			t_sample mix_622 = mix_1143;
			t_sample zeroR_676 = mix_622;
			t_sample mul_606 = (m_history_87 * ((t_sample)0.999));
			t_sample add_608 = (mul_605 + mul_606);
			t_sample gen_612 = add_608;
			t_sample history_607_next_611 = fixdenorm(add_608);
			t_sample freeze_646 = gen_612;
			t_sample mul_647 = ((mix_599 + right_627) * freeze_646);
			t_sample toFILTERS_c45R_143 = mul_647;
			t_sample freeze_681 = freeze_646;
			t_sample mul_682 = (left_628 * freeze_681);
			t_sample toFILTERS_c45L_144 = mul_682;
			t_sample omega = safediv((gen_541 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((int)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) - cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((((int)1) - cs) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_263 = a2;
			t_sample expr_264 = a1;
			t_sample expr_265 = a2;
			t_sample expr_266 = b1;
			t_sample expr_267 = b2;
			t_sample omega_269 = safediv((gen_533 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_268 = sin(omega_269);
			t_sample cs_275 = cos(omega_269);
			t_sample alpha_276 = ((sn_268 * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b_273 = safediv(((int)1), (((int)1) + alpha_276));
			t_sample a_274 = (((((int)1) + cs_275) * ((t_sample)0.5)) * b_273);
			t_sample a_272 = ((-(((int)1) + cs_275)) * b_273);
			t_sample b_271 = ((((int)-2) * cs_275) * b_273);
			t_sample b_270 = ((((int)1) - alpha_276) * b_273);
			t_sample expr_258 = a_274;
			t_sample expr_259 = a_272;
			t_sample expr_260 = a_274;
			t_sample expr_261 = b_271;
			t_sample expr_262 = b_270;
			t_sample mul_216 = (toFILTERS_c45L_144 * expr_263);
			t_sample mul_206 = (toFILTERS_c45R_143 * expr_263);
			t_sample mul_213 = (m_history_82 * expr_264);
			t_sample mul_203 = (m_history_81 * expr_264);
			t_sample mul_211 = (m_history_86 * expr_265);
			t_sample mul_201 = (m_history_83 * expr_265);
			t_sample mul_207 = (m_history_84 * expr_267);
			t_sample mul_197 = (m_history_85 * expr_267);
			t_sample mul_209 = (m_history_80 * expr_266);
			t_sample sub_215 = (((mul_211 + mul_213) + mul_216) - (mul_209 + mul_207));
			t_sample gen_235 = sub_215;
			t_sample mul_199 = (m_history_79 * expr_266);
			t_sample sub_205 = (((mul_206 + mul_203) + mul_201) - (mul_199 + mul_197));
			t_sample gen_236 = sub_205;
			t_sample history_212_next_227 = fixdenorm(m_history_82);
			t_sample history_198_next_228 = fixdenorm(m_history_79);
			t_sample history_208_next_229 = fixdenorm(m_history_80);
			t_sample history_202_next_230 = fixdenorm(m_history_81);
			t_sample history_214_next_231 = fixdenorm(toFILTERS_c45L_144);
			t_sample history_204_next_232 = fixdenorm(toFILTERS_c45R_143);
			t_sample history_210_next_233 = fixdenorm(sub_215);
			t_sample history_200_next_234 = fixdenorm(sub_205);
			t_sample mul_156 = (m_history_75 * expr_260);
			t_sample mul_166 = (m_history_76 * expr_260);
			t_sample mul_158 = (m_history_73 * expr_259);
			t_sample mul_168 = (m_history_74 * expr_259);
			t_sample mul_161 = (gen_236 * expr_258);
			t_sample mul_171 = (gen_235 * expr_258);
			t_sample mul_152 = (m_history_78 * expr_262);
			t_sample mul_162 = (m_history_77 * expr_262);
			t_sample mul_154 = (m_history_72 * expr_261);
			t_sample sub_160 = (((mul_161 + mul_158) + mul_156) - (mul_154 + mul_152));
			t_sample gen_191 = sub_160;
			t_sample mul_164 = (m_history_71 * expr_261);
			t_sample sub_170 = (((mul_166 + mul_168) + mul_171) - (mul_164 + mul_162));
			t_sample gen_190 = sub_170;
			t_sample history_153_next_182 = fixdenorm(m_history_72);
			t_sample history_163_next_183 = fixdenorm(m_history_71);
			t_sample history_167_next_184 = fixdenorm(m_history_74);
			t_sample history_157_next_185 = fixdenorm(m_history_73);
			t_sample history_169_next_186 = fixdenorm(gen_235);
			t_sample history_159_next_187 = fixdenorm(gen_236);
			t_sample history_155_next_188 = fixdenorm(sub_160);
			t_sample history_165_next_189 = fixdenorm(sub_170);
			t_sample gen_277 = gen_190;
			t_sample gen_278 = gen_191;
			t_sample fromFILTERS_c45L_146 = gen_277;
			t_sample mul_971 = (div_986 * escala_Size_475);
			t_sample mul_982 = (((int)1491) * mul_971);
			t_sample mul_948 = (m_history_70 * ((t_sample)0.999));
			t_sample mul_947 = (mul_982 * ((t_sample)0.001));
			t_sample add_950 = (mul_947 + mul_948);
			t_sample gen_954 = add_950;
			t_sample history_949_next_953 = fixdenorm(add_950);
			t_sample gen_999 = gen_954;
			t_sample mul_972 = (((int)1116) * mul_971);
			t_sample mul_908 = (m_history_69 * ((t_sample)0.999));
			t_sample mul_907 = (mul_972 * ((t_sample)0.001));
			t_sample add_910 = (mul_907 + mul_908);
			t_sample gen_914 = add_910;
			t_sample history_909_next_913 = fixdenorm(add_910);
			t_sample gen_1004 = gen_914;
			t_sample mul_978 = (((int)1277) * mul_971);
			t_sample mul_932 = (m_history_68 * ((t_sample)0.999));
			t_sample mul_931 = (mul_978 * ((t_sample)0.001));
			t_sample add_934 = (mul_931 + mul_932);
			t_sample gen_938 = add_934;
			t_sample history_933_next_937 = fixdenorm(add_934);
			t_sample gen_1001 = gen_938;
			t_sample mul_976 = (((int)1356) * mul_971);
			t_sample mul_924 = (m_history_67 * ((t_sample)0.999));
			t_sample mul_923 = (mul_976 * ((t_sample)0.001));
			t_sample add_926 = (mul_923 + mul_924);
			t_sample gen_930 = add_926;
			t_sample history_925_next_929 = fixdenorm(add_926);
			t_sample gen_1002 = gen_930;
			t_sample mul_974 = (((int)1188) * mul_971);
			t_sample mul_916 = (m_history_66 * ((t_sample)0.999));
			t_sample mul_915 = (mul_974 * ((t_sample)0.001));
			t_sample add_918 = (mul_915 + mul_916);
			t_sample gen_922 = add_918;
			t_sample history_917_next_921 = fixdenorm(add_918);
			t_sample gen_1003 = gen_922;
			t_sample mul_980 = (((int)1422) * mul_971);
			t_sample mul_940 = (m_history_65 * ((t_sample)0.999));
			t_sample mul_939 = (mul_980 * ((t_sample)0.001));
			t_sample add_942 = (mul_939 + mul_940);
			t_sample gen_946 = add_942;
			t_sample history_941_next_945 = fixdenorm(add_942);
			t_sample gen_1000 = gen_946;
			t_sample mul_984 = (((int)1617) * mul_971);
			t_sample mul_956 = (m_history_64 * ((t_sample)0.999));
			t_sample mul_955 = (mul_984 * ((t_sample)0.001));
			t_sample add_958 = (mul_955 + mul_956);
			t_sample gen_962 = add_958;
			t_sample history_957_next_961 = fixdenorm(add_958);
			t_sample gen_998 = gen_962;
			t_sample mul_987 = (((int)1557) * mul_971);
			t_sample mul_964 = (m_history_63 * ((t_sample)0.999));
			t_sample mul_963 = (mul_987 * ((t_sample)0.001));
			t_sample add_966 = (mul_963 + mul_964);
			t_sample gen_970 = add_966;
			t_sample history_965_next_969 = fixdenorm(add_966);
			t_sample gen_997 = gen_970;
			t_sample mul_1009 = (m_history_61 * rsub_1007);
			t_sample add_1006 = (zeroL_675 + gen_1004);
			t_sample tap_1015 = m_delay_62.read_linear(add_1006);
			t_sample mul_1012 = (tap_1015 * rsub_1005);
			t_sample add_1011 = (mul_1012 + mul_1009);
			t_sample mul_1008 = (add_1011 * gen_620);
			t_sample add_1013 = (fromFILTERS_c45L_146 + mul_1008);
			t_sample gen_1020 = add_1013;
			t_sample history_1010_next_1019 = fixdenorm(add_1011);
			t_sample mul_1024 = (m_history_59 * rsub_1022);
			t_sample add_1021 = (zeroL_675 + gen_1003);
			t_sample tap_1030 = m_delay_60.read_linear(add_1021);
			t_sample mul_1027 = (tap_1030 * rsub_1005);
			t_sample add_1026 = (mul_1027 + mul_1024);
			t_sample mul_1023 = (add_1026 * gen_620);
			t_sample add_1028 = (fromFILTERS_c45L_146 + mul_1023);
			t_sample gen_1035 = add_1028;
			t_sample history_1025_next_1034 = fixdenorm(add_1026);
			t_sample mul_1039 = (m_history_57 * rsub_1037);
			t_sample add_1036 = (zeroL_675 + gen_1002);
			t_sample tap_1045 = m_delay_58.read_linear(add_1036);
			t_sample mul_1042 = (tap_1045 * rsub_1005);
			t_sample add_1041 = (mul_1042 + mul_1039);
			t_sample mul_1038 = (add_1041 * gen_620);
			t_sample add_1043 = (fromFILTERS_c45L_146 + mul_1038);
			t_sample gen_1050 = add_1043;
			t_sample history_1040_next_1049 = fixdenorm(add_1041);
			t_sample mul_1054 = (m_history_55 * rsub_1052);
			t_sample add_1051 = (zeroL_675 + gen_1001);
			t_sample tap_1060 = m_delay_56.read_linear(add_1051);
			t_sample mul_1057 = (tap_1060 * rsub_1005);
			t_sample add_1056 = (mul_1057 + mul_1054);
			t_sample mul_1053 = (add_1056 * gen_620);
			t_sample add_1058 = (fromFILTERS_c45L_146 + mul_1053);
			t_sample gen_1065 = add_1058;
			t_sample history_1055_next_1064 = fixdenorm(add_1056);
			t_sample mul_1069 = (m_history_53 * rsub_1067);
			t_sample add_1066 = (zeroL_675 + gen_1000);
			t_sample tap_1075 = m_delay_54.read_linear(add_1066);
			t_sample mul_1072 = (tap_1075 * rsub_1005);
			t_sample add_1071 = (mul_1072 + mul_1069);
			t_sample mul_1068 = (add_1071 * gen_620);
			t_sample add_1073 = (fromFILTERS_c45L_146 + mul_1068);
			t_sample gen_1080 = add_1073;
			t_sample history_1070_next_1079 = fixdenorm(add_1071);
			t_sample mul_1084 = (m_history_51 * rsub_1082);
			t_sample add_1081 = (zeroL_675 + gen_999);
			t_sample tap_1090 = m_delay_52.read_linear(add_1081);
			t_sample mul_1087 = (tap_1090 * rsub_1005);
			t_sample add_1086 = (mul_1087 + mul_1084);
			t_sample mul_1083 = (add_1086 * gen_620);
			t_sample add_1088 = (fromFILTERS_c45L_146 + mul_1083);
			t_sample gen_1095 = add_1088;
			t_sample history_1085_next_1094 = fixdenorm(add_1086);
			t_sample mul_1099 = (m_history_49 * rsub_1097);
			t_sample add_1096 = (zeroL_675 + gen_998);
			t_sample tap_1105 = m_delay_50.read_linear(add_1096);
			t_sample mul_1102 = (tap_1105 * rsub_1005);
			t_sample add_1101 = (mul_1102 + mul_1099);
			t_sample mul_1098 = (add_1101 * gen_620);
			t_sample add_1103 = (fromFILTERS_c45L_146 + mul_1098);
			t_sample gen_1110 = add_1103;
			t_sample history_1100_next_1109 = fixdenorm(add_1101);
			t_sample mul_1114 = (m_history_47 * rsub_1112);
			t_sample add_1111 = (zeroL_675 + gen_997);
			t_sample tap_1120 = m_delay_48.read_linear(add_1111);
			t_sample mul_1117 = (tap_1120 * rsub_1005);
			t_sample add_1116 = (mul_1117 + mul_1114);
			t_sample mul_1113 = (add_1116 * gen_620);
			t_sample add_1118 = (fromFILTERS_c45L_146 + mul_1113);
			t_sample gen_1125 = add_1118;
			t_sample history_1115_next_1124 = fixdenorm(add_1116);
			t_sample mul_1126 = ((((((((gen_1125 + gen_1110) + gen_1095) + gen_1080) + gen_1065) + gen_1050) + gen_1035) + gen_1020) * ((t_sample)0.125));
			t_sample gen_1128 = mul_1126;
			t_sample mul_464 = (gen_1128 * ((t_sample)-0.5));
			t_sample mul_454 = (div_455 * escala_Size_473);
			t_sample mul_456 = (((int)255) * mul_454);
			t_sample add_458 = (((int)0) + mul_456);
			t_sample tap_466 = m_delay_46.read_linear(add_458);
			t_sample tap_461 = m_delay_45.read_linear(add_458);
			t_sample mul_459 = (tap_461 * ((t_sample)0.5));
			t_sample add_462 = (mul_464 + (tap_466 + mul_459));
			t_sample gen_470 = add_462;
			t_sample mul_447 = (gen_470 * ((t_sample)-0.5));
			t_sample mul_437 = (div_438 * escala_Size_473);
			t_sample mul_439 = (((int)556) * mul_437);
			t_sample add_441 = (((int)0) + mul_439);
			t_sample tap_449 = m_delay_44.read_linear(add_441);
			t_sample tap_444 = m_delay_43.read_linear(add_441);
			t_sample mul_442 = (tap_444 * ((t_sample)0.5));
			t_sample add_445 = (mul_447 + (tap_449 + mul_442));
			t_sample gen_453 = add_445;
			t_sample mul_430 = (gen_453 * ((t_sample)-0.5));
			t_sample mul_420 = (div_421 * escala_Size_473);
			t_sample mul_422 = (((int)441) * mul_420);
			t_sample add_424 = (((int)0) + mul_422);
			t_sample tap_432 = m_delay_42.read_linear(add_424);
			t_sample tap_427 = m_delay_41.read_linear(add_424);
			t_sample mul_425 = (tap_427 * ((t_sample)0.5));
			t_sample add_428 = (mul_430 + (tap_432 + mul_425));
			t_sample gen_436 = add_428;
			t_sample mul_413 = (gen_436 * ((t_sample)-0.5));
			t_sample mul_403 = (div_404 * escala_Size_473);
			t_sample mul_405 = (((int)341) * mul_403);
			t_sample add_407 = (((int)0) + mul_405);
			t_sample tap_415 = m_delay_40.read_linear(add_407);
			t_sample tap_410 = m_delay_39.read_linear(add_407);
			t_sample mul_408 = (tap_410 * ((t_sample)0.5));
			t_sample add_411 = (mul_413 + (tap_415 + mul_408));
			t_sample gen_419 = add_411;
			t_sample gen_472 = gen_419;
			t_sample matrizMS_c45L_626 = gen_472;
			t_sample fromFILTERS_c45R_145 = gen_278;
			t_sample mul_749 = (div_764 * escala_Size_474);
			t_sample mul_752 = (((int)1188) * mul_749);
			t_sample mul_694 = (m_history_38 * ((t_sample)0.999));
			t_sample mul_693 = (mul_752 * ((t_sample)0.001));
			t_sample add_696 = (mul_693 + mul_694);
			t_sample gen_700 = add_696;
			t_sample history_695_next_699 = fixdenorm(add_696);
			t_sample gen_781 = gen_700;
			t_sample mul_765 = (((int)1557) * mul_749);
			t_sample mul_742 = (m_history_37 * ((t_sample)0.999));
			t_sample mul_741 = (mul_765 * ((t_sample)0.001));
			t_sample add_744 = (mul_741 + mul_742);
			t_sample gen_748 = add_744;
			t_sample history_743_next_747 = fixdenorm(add_744);
			t_sample gen_775 = gen_748;
			t_sample mul_750 = (((int)1116) * mul_749);
			t_sample mul_686 = (m_history_36 * ((t_sample)0.999));
			t_sample mul_685 = (mul_750 * ((t_sample)0.001));
			t_sample add_688 = (mul_685 + mul_686);
			t_sample gen_692 = add_688;
			t_sample history_687_next_691 = fixdenorm(add_688);
			t_sample gen_782 = gen_692;
			t_sample mul_756 = (((int)1277) * mul_749);
			t_sample mul_710 = (m_history_35 * ((t_sample)0.999));
			t_sample mul_709 = (mul_756 * ((t_sample)0.001));
			t_sample add_712 = (mul_709 + mul_710);
			t_sample gen_716 = add_712;
			t_sample history_711_next_715 = fixdenorm(add_712);
			t_sample gen_779 = gen_716;
			t_sample mul_754 = (((int)1356) * mul_749);
			t_sample mul_702 = (m_history_34 * ((t_sample)0.999));
			t_sample mul_701 = (mul_754 * ((t_sample)0.001));
			t_sample add_704 = (mul_701 + mul_702);
			t_sample gen_708 = add_704;
			t_sample history_703_next_707 = fixdenorm(add_704);
			t_sample gen_780 = gen_708;
			t_sample mul_762 = (((int)1617) * mul_749);
			t_sample mul_734 = (m_history_33 * ((t_sample)0.999));
			t_sample mul_733 = (mul_762 * ((t_sample)0.001));
			t_sample add_736 = (mul_733 + mul_734);
			t_sample gen_740 = add_736;
			t_sample history_735_next_739 = fixdenorm(add_736);
			t_sample gen_776 = gen_740;
			t_sample mul_758 = (((int)1422) * mul_749);
			t_sample mul_718 = (m_history_32 * ((t_sample)0.999));
			t_sample mul_717 = (mul_758 * ((t_sample)0.001));
			t_sample add_720 = (mul_717 + mul_718);
			t_sample gen_724 = add_720;
			t_sample history_719_next_723 = fixdenorm(add_720);
			t_sample gen_778 = gen_724;
			t_sample mul_760 = (((int)1491) * mul_749);
			t_sample mul_726 = (m_history_31 * ((t_sample)0.999));
			t_sample mul_725 = (mul_760 * ((t_sample)0.001));
			t_sample add_728 = (mul_725 + mul_726);
			t_sample gen_732 = add_728;
			t_sample history_727_next_731 = fixdenorm(add_728);
			t_sample gen_777 = gen_732;
			t_sample mul_787 = (m_history_29 * rsub_785);
			t_sample add_784 = (zeroR_676 + gen_782);
			t_sample tap_793 = m_delay_30.read_linear(add_784);
			t_sample mul_790 = (tap_793 * rsub_783);
			t_sample add_789 = (mul_790 + mul_787);
			t_sample mul_786 = (add_789 * gen_620);
			t_sample add_791 = (fromFILTERS_c45R_145 + mul_786);
			t_sample gen_798 = add_791;
			t_sample history_788_next_797 = fixdenorm(add_789);
			t_sample mul_802 = (m_history_27 * rsub_800);
			t_sample add_799 = (zeroR_676 + gen_781);
			t_sample tap_808 = m_delay_28.read_linear(add_799);
			t_sample mul_805 = (tap_808 * rsub_783);
			t_sample add_804 = (mul_805 + mul_802);
			t_sample mul_801 = (add_804 * gen_620);
			t_sample add_806 = (fromFILTERS_c45R_145 + mul_801);
			t_sample gen_813 = add_806;
			t_sample history_803_next_812 = fixdenorm(add_804);
			t_sample mul_817 = (m_history_25 * rsub_815);
			t_sample add_814 = (zeroR_676 + gen_780);
			t_sample tap_823 = m_delay_26.read_linear(add_814);
			t_sample mul_820 = (tap_823 * rsub_783);
			t_sample add_819 = (mul_820 + mul_817);
			t_sample mul_816 = (add_819 * gen_620);
			t_sample add_821 = (fromFILTERS_c45R_145 + mul_816);
			t_sample gen_828 = add_821;
			t_sample history_818_next_827 = fixdenorm(add_819);
			t_sample mul_832 = (m_history_23 * rsub_830);
			t_sample add_829 = (zeroR_676 + gen_779);
			t_sample tap_838 = m_delay_24.read_linear(add_829);
			t_sample mul_835 = (tap_838 * rsub_783);
			t_sample add_834 = (mul_835 + mul_832);
			t_sample mul_831 = (add_834 * gen_620);
			t_sample add_836 = (fromFILTERS_c45R_145 + mul_831);
			t_sample gen_843 = add_836;
			t_sample history_833_next_842 = fixdenorm(add_834);
			t_sample mul_847 = (m_history_21 * rsub_845);
			t_sample add_844 = (zeroR_676 + gen_778);
			t_sample tap_853 = m_delay_22.read_linear(add_844);
			t_sample mul_850 = (tap_853 * rsub_783);
			t_sample add_849 = (mul_850 + mul_847);
			t_sample mul_846 = (add_849 * gen_620);
			t_sample add_851 = (fromFILTERS_c45R_145 + mul_846);
			t_sample gen_858 = add_851;
			t_sample history_848_next_857 = fixdenorm(add_849);
			t_sample mul_862 = (m_history_19 * rsub_860);
			t_sample add_859 = (zeroR_676 + gen_777);
			t_sample tap_868 = m_delay_20.read_linear(add_859);
			t_sample mul_865 = (tap_868 * rsub_783);
			t_sample add_864 = (mul_865 + mul_862);
			t_sample mul_861 = (add_864 * gen_620);
			t_sample add_866 = (fromFILTERS_c45R_145 + mul_861);
			t_sample gen_873 = add_866;
			t_sample history_863_next_872 = fixdenorm(add_864);
			t_sample mul_877 = (m_history_17 * rsub_875);
			t_sample add_874 = (zeroR_676 + gen_776);
			t_sample tap_883 = m_delay_18.read_linear(add_874);
			t_sample mul_880 = (tap_883 * rsub_783);
			t_sample add_879 = (mul_880 + mul_877);
			t_sample mul_876 = (add_879 * gen_620);
			t_sample add_881 = (fromFILTERS_c45R_145 + mul_876);
			t_sample gen_888 = add_881;
			t_sample history_878_next_887 = fixdenorm(add_879);
			t_sample mul_892 = (m_history_15 * rsub_890);
			t_sample add_889 = (zeroR_676 + gen_775);
			t_sample tap_898 = m_delay_16.read_linear(add_889);
			t_sample mul_895 = (tap_898 * rsub_783);
			t_sample add_894 = (mul_895 + mul_892);
			t_sample mul_891 = (add_894 * gen_620);
			t_sample add_896 = (fromFILTERS_c45R_145 + mul_891);
			t_sample gen_903 = add_896;
			t_sample history_893_next_902 = fixdenorm(add_894);
			t_sample mul_904 = ((((((((gen_903 + gen_888) + gen_873) + gen_858) + gen_843) + gen_828) + gen_813) + gen_798) * ((t_sample)0.125));
			t_sample gen_906 = mul_904;
			t_sample mul_391 = (gen_906 * ((t_sample)-0.5));
			t_sample mul_381 = (div_382 * escala_Size_400);
			t_sample mul_383 = (((int)255) * mul_381);
			t_sample add_385 = (((int)0) + mul_383);
			t_sample tap_393 = m_delay_14.read_linear(add_385);
			t_sample tap_388 = m_delay_13.read_linear(add_385);
			t_sample mul_386 = (tap_388 * ((t_sample)0.5));
			t_sample add_389 = (mul_391 + (tap_393 + mul_386));
			t_sample gen_397 = add_389;
			t_sample mul_374 = (gen_397 * ((t_sample)-0.5));
			t_sample mul_364 = (div_365 * escala_Size_400);
			t_sample mul_366 = (((int)556) * mul_364);
			t_sample add_368 = (((int)0) + mul_366);
			t_sample tap_376 = m_delay_12.read_linear(add_368);
			t_sample tap_371 = m_delay_11.read_linear(add_368);
			t_sample mul_369 = (tap_371 * ((t_sample)0.5));
			t_sample add_372 = (mul_374 + (tap_376 + mul_369));
			t_sample gen_380 = add_372;
			t_sample mul_357 = (gen_380 * ((t_sample)-0.5));
			t_sample mul_347 = (div_348 * escala_Size_400);
			t_sample mul_349 = (((int)441) * mul_347);
			t_sample add_351 = (((int)0) + mul_349);
			t_sample tap_359 = m_delay_10.read_linear(add_351);
			t_sample tap_354 = m_delay_9.read_linear(add_351);
			t_sample mul_352 = (tap_354 * ((t_sample)0.5));
			t_sample add_355 = (mul_357 + (tap_359 + mul_352));
			t_sample gen_363 = add_355;
			t_sample mul_340 = (gen_363 * ((t_sample)-0.5));
			t_sample mul_330 = (div_331 * escala_Size_400);
			t_sample mul_332 = (((int)341) * mul_330);
			t_sample add_334 = (((int)0) + mul_332);
			t_sample tap_342 = m_delay_8.read_linear(add_334);
			t_sample tap_337 = m_delay_7.read_linear(add_334);
			t_sample mul_335 = (tap_337 * ((t_sample)0.5));
			t_sample add_338 = (mul_340 + (tap_342 + mul_335));
			t_sample gen_346 = add_338;
			t_sample gen_399 = gen_346;
			t_sample matrizMS_c45R_625 = gen_399;
			t_sample add_645 = (matrizMS_c45L_626 + matrizMS_c45R_625);
			t_sample mul_643 = (add_645 * sqrt_641);
			t_sample sub_644 = (matrizMS_c45L_626 - matrizMS_c45R_625);
			t_sample mul_642 = (sub_644 * sqrt_640);
			t_sample add_639 = (mul_643 + mul_642);
			t_sample mul_630 = (add_639 * scale_631);
			t_sample filterL_315 = mul_630;
			t_sample sub_638 = (mul_643 - mul_642);
			t_sample mul_629 = (sub_638 * scale_631);
			t_sample filterR_314 = mul_629;
			t_sample return_189;
			t_sample return_190;
			eq3bandas_d_d_d_d_d_d_d_d_i(filterL_315, filterR_314, gen_313, gen_305, gen_297, gen_525, gen_517, gen_509, ((int)1), return_189, return_190);
			t_sample expr_566 = return_189;
			t_sample expr_567 = return_190;
			t_sample gen_568 = expr_566;
			t_sample gen_569 = expr_567;
			t_sample fromFilterL_317 = gen_568;
			t_sample mix_1144 = (mul_630 + (onOffEQ_279 * (fromFilterL_317 - mul_630)));
			t_sample mix_289 = mix_1144;
			t_sample fromFilterR_316 = gen_569;
			t_sample mix_1145 = (mul_629 + (onOffEQ_279 * (fromFilterR_316 - mul_629)));
			t_sample mix_288 = mix_1145;
			t_sample dbtoa_63 = dbtoa(gen_20);
			t_sample mstosamps_107 = (gen_30 * (samplerate * 0.001));
			t_sample mstosamps_106 = (gen_38 * (samplerate * 0.001));
			t_sample tap_100 = m_delay_6.read_step(((int)300));
			t_sample mul_93 = (mix_288 * mix_288);
			t_sample add_97 = (m_history_5 + mul_93);
			t_sample sub_96 = (add_97 - tap_100);
			t_sample div_94 = (sub_96 * ((t_sample)0.0033333333333333));
			t_sample sqrt_92 = sqrt(div_94);
			t_sample gen_105 = sqrt_92;
			t_sample history_95_next_104 = fixdenorm(sub_96);
			t_sample atodb_91 = atodb(gen_105);
			t_sample max_66 = ((atodb_91 < maxb_191) ? maxb_191 : atodb_91);
			int gt_90 = (max_66 > thdC_11);
			t_sample mul_69 = (m_history_4 * ((t_sample)0.999));
			t_sample mul_68 = (gt_90 * ((t_sample)0.001));
			t_sample add_71 = (mul_68 + mul_69);
			t_sample gen_75 = add_71;
			t_sample history_70_next_74 = fixdenorm(add_71);
			t_sample sub_89 = (thdC_11 - max_66);
			t_sample rdiv_113 = safediv(((int)1), gen_46);
			t_sample rsub_112 = (((int)1) - rdiv_113);
			t_sample mul_88 = (sub_89 * rsub_112);
			t_sample dbtoa_86 = dbtoa(mul_88);
			t_sample orange_1148 = (dbtoa_86 - ((int)1));
			t_sample sub_1149 = (gen_75 - ((int)0));
			t_sample scale_1146 = ((safepow((sub_1149 * ((t_sample)1)), ((int)1)) * orange_1148) + ((int)1));
			t_sample iup_193 = (1 / maximum(1, abs(mstosamps_107)));
			t_sample idown_194 = (1 / maximum(1, abs(mstosamps_106)));
			__m_slide_192 = fixdenorm((__m_slide_192 + (((scale_1146 > __m_slide_192) ? iup_193 : idown_194) * (scale_1146 - __m_slide_192))));
			t_sample slide_85 = __m_slide_192;
			t_sample mul_84 = (mix_288 * slide_85);
			t_sample mul_64 = (mul_84 * dbtoa_63);
			t_sample tap_125 = m_delay_3.read_step(((int)300));
			t_sample mul_118 = (mix_289 * mix_289);
			t_sample add_122 = (m_history_2 + mul_118);
			t_sample sub_121 = (add_122 - tap_125);
			t_sample div_119 = (sub_121 * ((t_sample)0.0033333333333333));
			t_sample sqrt_117 = sqrt(div_119);
			t_sample gen_130 = sqrt_117;
			t_sample history_120_next_129 = fixdenorm(sub_121);
			t_sample atodb_116 = atodb(gen_130);
			t_sample max_67 = ((atodb_116 < maxb_195) ? maxb_195 : atodb_116);
			int gt_115 = (max_67 > thdC_11);
			t_sample mul_77 = (m_history_1 * ((t_sample)0.999));
			t_sample mul_76 = (gt_115 * ((t_sample)0.001));
			t_sample add_79 = (mul_76 + mul_77);
			t_sample gen_83 = add_79;
			t_sample history_78_next_82 = fixdenorm(add_79);
			t_sample sub_114 = (thdC_11 - max_67);
			t_sample mul_111 = (sub_114 * rsub_112);
			t_sample dbtoa_109 = dbtoa(mul_111);
			t_sample orange_1152 = (dbtoa_109 - ((int)1));
			t_sample sub_1153 = (gen_83 - ((int)0));
			t_sample scale_1150 = ((safepow((sub_1153 * ((t_sample)1)), ((int)1)) * orange_1152) + ((int)1));
			t_sample iup_197 = (1 / maximum(1, abs(mstosamps_107)));
			t_sample idown_198 = (1 / maximum(1, abs(mstosamps_106)));
			__m_slide_196 = fixdenorm((__m_slide_196 + (((scale_1150 > __m_slide_196) ? iup_197 : idown_198) * (scale_1150 - __m_slide_196))));
			t_sample slide_108 = __m_slide_196;
			t_sample mul_131 = (mix_289 * slide_108);
			t_sample mul_65 = (mul_131 * dbtoa_63);
			t_sample mix_1154 = (mix_288 + (gen_62 * (mul_64 - mix_288)));
			t_sample mix_1155 = (mix_289 + (gen_62 * (mul_65 - mix_289)));
			t_sample mix_1156 = (mix_1134 + (gen_483 * (mix_1154 - mix_1134)));
			t_sample mul_500 = (mix_1156 * gen_499);
			t_sample dcblock_21 = __m_dcblock_199(mul_500);
			t_sample out2 = dcblock_21;
			t_sample mix_1157 = (mix_1132 + (gen_483 * (mix_1155 - mix_1132)));
			t_sample mul_501 = (mix_1157 * gen_499);
			t_sample dcblock_22 = __m_dcblock_200(mul_501);
			t_sample out1 = dcblock_22;
			m_history_135 = history_494_next_498;
			m_history_111 = history_57_next_61;
			m_history_110 = history_49_next_53;
			m_history_109 = history_41_next_45;
			m_history_108 = history_33_next_37;
			m_history_107 = history_25_next_29;
			m_history_106 = history_15_next_19;
			m_history_105 = history_658_next_662;
			m_history_104 = history_478_next_482;
			m_history_103 = history_486_next_490;
			m_history_102 = history_282_next_286;
			m_history_101 = history_650_next_654;
			m_history_100 = history_583_next_587;
			m_history_99 = history_666_next_670;
			m_history_98 = history_308_next_312;
			m_history_97 = history_300_next_304;
			m_history_96 = history_292_next_296;
			m_history_95 = history_520_next_524;
			m_history_94 = history_512_next_516;
			m_history_93 = history_504_next_508;
			m_history_92 = history_320_next_324;
			m_history_91 = history_536_next_540;
			m_history_90 = history_528_next_532;
			m_history_89 = history_615_next_619;
			m_history_88 = history_575_next_579;
			m_history_87 = history_607_next_611;
			m_history_86 = history_212_next_227;
			m_history_77 = history_163_next_183;
			m_history_76 = history_167_next_184;
			m_history_75 = history_157_next_185;
			m_history_74 = history_169_next_186;
			m_history_73 = history_159_next_187;
			m_history_72 = history_155_next_188;
			m_history_71 = history_165_next_189;
			m_history_78 = history_153_next_182;
			m_history_85 = history_198_next_228;
			m_history_84 = history_208_next_229;
			m_history_83 = history_202_next_230;
			m_history_82 = history_214_next_231;
			m_history_81 = history_204_next_232;
			m_history_80 = history_210_next_233;
			m_history_79 = history_200_next_234;
			m_history_70 = history_949_next_953;
			m_history_47 = history_1115_next_1124;
			m_delay_48.write(add_1118);
			m_history_49 = history_1100_next_1109;
			m_delay_50.write(add_1103);
			m_history_51 = history_1085_next_1094;
			m_delay_52.write(add_1088);
			m_history_53 = history_1070_next_1079;
			m_delay_54.write(add_1073);
			m_history_55 = history_1055_next_1064;
			m_delay_56.write(add_1058);
			m_history_57 = history_1040_next_1049;
			m_delay_58.write(add_1043);
			m_history_59 = history_1025_next_1034;
			m_delay_60.write(add_1028);
			m_history_61 = history_1010_next_1019;
			m_delay_62.write(add_1013);
			m_history_69 = history_909_next_913;
			m_history_68 = history_933_next_937;
			m_history_67 = history_925_next_929;
			m_history_66 = history_917_next_921;
			m_history_65 = history_941_next_945;
			m_history_64 = history_957_next_961;
			m_history_63 = history_965_next_969;
			m_delay_46.write(gen_1128);
			m_delay_39.write(add_411);
			m_delay_40.write(gen_436);
			m_delay_41.write(add_428);
			m_delay_42.write(gen_453);
			m_delay_43.write(add_445);
			m_delay_44.write(gen_470);
			m_delay_45.write(add_462);
			m_history_38 = history_695_next_699;
			m_history_15 = history_893_next_902;
			m_delay_16.write(add_896);
			m_history_17 = history_878_next_887;
			m_delay_18.write(add_881);
			m_history_19 = history_863_next_872;
			m_delay_20.write(add_866);
			m_history_21 = history_848_next_857;
			m_delay_22.write(add_851);
			m_history_23 = history_833_next_842;
			m_delay_24.write(add_836);
			m_history_25 = history_818_next_827;
			m_delay_26.write(add_821);
			m_history_27 = history_803_next_812;
			m_delay_28.write(add_806);
			m_history_29 = history_788_next_797;
			m_delay_30.write(add_791);
			m_history_37 = history_743_next_747;
			m_history_36 = history_687_next_691;
			m_history_35 = history_711_next_715;
			m_history_34 = history_703_next_707;
			m_history_33 = history_735_next_739;
			m_history_32 = history_719_next_723;
			m_history_31 = history_727_next_731;
			m_delay_14.write(gen_906);
			m_delay_7.write(add_338);
			m_delay_8.write(gen_363);
			m_delay_9.write(add_355);
			m_delay_10.write(gen_380);
			m_delay_11.write(add_372);
			m_delay_12.write(gen_397);
			m_delay_13.write(add_389);
			m_delay_6.write(mul_93);
			m_history_5 = history_95_next_104;
			m_history_4 = history_70_next_74;
			m_delay_3.write(mul_118);
			m_history_2 = history_120_next_129;
			m_history_1 = history_78_next_82;
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
			
		};
		return __exception;
		
	};
	inline void set_t_ratio(t_param _value) {
		m_t_ratio_112 = (_value < 1 ? 1 : (_value > 20 ? 20 : _value));
	};
	inline void set_n_lowFreq(t_param _value) {
		m_n_lowFreq_113 = (_value < 20 ? 20 : (_value > 800 ? 800 : _value));
	};
	inline void set_e_size(t_param _value) {
		m_e_size_114 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_r_onoffCOMP(t_param _value) {
		m_r_onoffCOMP_115 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_m_output(t_param _value) {
		m_m_output_116 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_f_st(t_param _value) {
		m_f_st_117 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_o_peakFreq(t_param _value) {
		m_o_peakFreq_118 = (_value < 100 ? 100 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_w_makeup(t_param _value) {
		m_w_makeup_119 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void set_c_reflect(t_param _value) {
		m_c_reflect_120 = (_value < 0.1 ? 0.1 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_j_hiGain(t_param _value) {
		m_j_hiGain_121 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_v_rel(t_param _value) {
		m_v_rel_122 = (_value < 5 ? 5 : (_value > 500 ? 500 : _value));
	};
	inline void set_h_lowGain(t_param _value) {
		m_h_lowGain_123 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_u_atk(t_param _value) {
		m_u_atk_124 = (_value < 5 ? 5 : (_value > 250 ? 250 : _value));
	};
	inline void set_a_input(t_param _value) {
		m_a_input_125 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_s_thd(t_param _value) {
		m_s_thd_126 = (_value < -36 ? -36 : (_value > 0 ? 0 : _value));
	};
	inline void set_b_drywet(t_param _value) {
		m_b_drywet_127 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_d_damp(t_param _value) {
		m_d_damp_128 = (_value < 0.001 ? 0.001 : (_value > 1 ? 1 : _value));
	};
	inline void set_g_freeze(t_param _value) {
		m_g_freeze_129 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_q_onoffEQ(t_param _value) {
		m_q_onoffEQ_130 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_k_lpf(t_param _value) {
		m_k_lpf_131 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_p_hiFreq(t_param _value) {
		m_p_hiFreq_132 = (_value < 800 ? 800 : (_value > 15000 ? 15000 : _value));
	};
	inline void set_i_peakGain(t_param _value) {
		m_i_peakGain_133 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_l_hpf(t_param _value) {
		m_l_hpf_134 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_148;
		t_sample return_149;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_148, return_149);
		t_sample x_560 = return_148;
		sigR = return_149;
		t_sample return_173;
		t_sample return_174;
		peak_d_d_d_d_i(x_560, sigR, pf, pg, bw, return_173, return_174);
		t_sample x_563 = return_173;
		sigR = return_174;
		t_sample return_187;
		t_sample return_188;
		hishelf_d_d_d_d(x_563, sigR, hf, hg, return_187, return_188);
		t_sample x_565 = return_187;
		sigR = return_188;
		out1 = x_565;
		out2 = sigR;
		
	};
	inline void lowshelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_143(freq) != ((int)0)) || (__m_change_144(db) != ((int)0)))) {
			m_b_142 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_f_141 = safediv(freq, m_b_142);
			m_b_140 = ((m_b_142 * m_b_142) - ((int)1));
			m_w_139 = tan(safediv((m_f_141 * ((t_sample)3.1415926535898)), samplerate));
			m_a_138 = safediv(((int)1), (m_w_139 + ((int)1)));
			m_a_137 = (m_w_139 - ((int)1));
			
		};
		t_sample outputLowShelfL = lowshelfCore_d_d_d_d_d(sigL, m_a_138, m_a_137, m_b_140, m_w_139);
		t_sample outputLowShelfR = lowshelfCore_d_d_d_d_d_146(sigR, m_a_138, m_a_137, m_b_140, m_w_139);
		out1 = outputLowShelfL;
		out2 = outputLowShelfR;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_138, t_sample m_a_137, t_sample m_b_140, t_sample m_w_139) {
		t_sample x = (m_a_138 * (input - (m_a_137 * m_z_145)));
		t_sample output = (m_w_139 * (x + m_z_145));
		m_z_145 = x;
		return ((output * m_b_140) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_146(t_sample input, t_sample m_a_138, t_sample m_a_137, t_sample m_b_140, t_sample m_w_139) {
		t_sample x = (m_a_138 * (input - (m_a_137 * m_z_147)));
		t_sample output = (m_w_139 * (x + m_z_147));
		m_z_147 = x;
		return ((output * m_b_140) + input);
		
	};
	inline void peak_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_160(freq) != ((int)0)) || (__m_change_161(db) != ((int)0))) || (__m_change_162(bw) != ((int)0)))) {
			m_w_159 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_158 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_158 * m_b_158) - ((int)1));
			m_d_157 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_163 = safediv(((m_d_157 * m_d_157) - ((int)1)), (m_d_157 * m_b_158));
			m_d_156 = ((v_163 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_163 >= ((int)100)) ? ((int)100) : v_163));
			m_d_155 = (m_d_156 * b);
			m_wq_154 = (m_d_156 * m_w_159);
			m_w_153 = (m_w_159 * m_w_159);
			m_a_152 = safediv(((int)1), ((((int)1) + m_w_153) + m_wq_154));
			m_a_151 = ((m_w_153 - ((int)1)) * ((int)2));
			m_a_150 = ((((int)1) + m_w_153) - m_wq_154);
			
		};
		t_sample outputPeakL = peakCore_d_d_d_d_d_d(sigL, m_w_159, m_d_155, m_a_152, m_a_151, m_a_150);
		t_sample outputPeakR = peakCore_d_d_d_d_d_d_168(sigR, m_w_159, m_d_155, m_a_152, m_a_151, m_a_150);
		out1 = outputPeakL;
		out2 = outputPeakR;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_159, t_sample m_d_155, t_sample m_a_152, t_sample m_a_151, t_sample m_a_150) {
		t_sample output = ((input - m_z_166) * m_w_159);
		m_z_166 = m_z_167;
		m_z_167 = input;
		t_sample output_561 = (m_a_152 * ((output - (m_a_151 * m_z_165)) - (m_a_150 * m_z_164)));
		m_z_164 = m_z_165;
		m_z_165 = output_561;
		t_sample output_562 = (input + (output_561 * m_d_155));
		return output_562;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_168(t_sample input, t_sample m_w_159, t_sample m_d_155, t_sample m_a_152, t_sample m_a_151, t_sample m_a_150) {
		t_sample output = ((input - m_z_171) * m_w_159);
		m_z_171 = m_z_172;
		m_z_172 = input;
		t_sample output_561 = (m_a_152 * ((output - (m_a_151 * m_z_170)) - (m_a_150 * m_z_169)));
		m_z_169 = m_z_170;
		m_z_170 = output_561;
		t_sample output_562 = (input + (output_561 * m_d_155));
		return output_562;
		
	};
	inline void hishelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_181(freq) != ((int)0)) || (__m_change_182(db) != ((int)0)))) {
			m_b_180 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_183 = (freq * m_b_180);
			m_f_179 = ((samplerate < mina_183) ? samplerate : mina_183);
			m_b_178 = ((m_b_180 * m_b_180) - ((int)1));
			m_w_177 = tan(safediv((((m_f_179 < ((int)0)) ? ((int)0) : m_f_179) * ((t_sample)3.1415926535898)), samplerate));
			m_a_176 = safediv(((int)1), (m_w_177 + ((int)1)));
			m_a_175 = (m_w_177 - ((int)1));
			
		};
		t_sample outputHighShelfL = hishelfCore_d_d_d_d(sigL, m_a_176, m_a_175, m_b_178);
		t_sample outputHighShelfR = hishelfCore_d_d_d_d_185(sigR, m_a_176, m_a_175, m_b_178);
		out1 = outputHighShelfL;
		out2 = outputHighShelfR;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_176, t_sample m_a_175, t_sample m_b_178) {
		t_sample x = (m_a_176 * (input - (m_a_175 * m_z_184)));
		t_sample output = (x - m_z_184);
		m_z_184 = x;
		t_sample output_564 = ((output * m_b_178) + input);
		return output_564;
		
	};
	inline t_sample hishelfCore_d_d_d_d_185(t_sample input, t_sample m_a_176, t_sample m_a_175, t_sample m_b_178) {
		t_sample x = (m_a_176 * (input - (m_a_175 * m_z_186)));
		t_sample output = (x - m_z_186);
		m_z_186 = x;
		t_sample output_564 = ((output * m_b_178) + input);
		return output_564;
		
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
		case 0: *value = self->m_a_input_125; break;
		case 1: *value = self->m_b_drywet_127; break;
		case 2: *value = self->m_c_reflect_120; break;
		case 3: *value = self->m_d_damp_128; break;
		case 4: *value = self->m_e_size_114; break;
		case 5: *value = self->m_f_st_117; break;
		case 6: *value = self->m_g_freeze_129; break;
		case 7: *value = self->m_h_lowGain_123; break;
		case 8: *value = self->m_i_peakGain_133; break;
		case 9: *value = self->m_j_hiGain_121; break;
		case 10: *value = self->m_k_lpf_131; break;
		case 11: *value = self->m_l_hpf_134; break;
		case 12: *value = self->m_m_output_116; break;
		case 13: *value = self->m_n_lowFreq_113; break;
		case 14: *value = self->m_o_peakFreq_118; break;
		case 15: *value = self->m_p_hiFreq_132; break;
		case 16: *value = self->m_q_onoffEQ_130; break;
		case 17: *value = self->m_r_onoffCOMP_115; break;
		case 18: *value = self->m_s_thd_126; break;
		case 19: *value = self->m_t_ratio_112; break;
		case 20: *value = self->m_u_atk_124; break;
		case 21: *value = self->m_v_rel_122; break;
		case 22: *value = self->m_w_makeup_119; break;
		
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
	// initialize parameter 0 ("m_a_input_125")
	pi = self->__commonstate.params + 0;
	pi->name = "a_input";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_input_125;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_drywet_127")
	pi = self->__commonstate.params + 1;
	pi->name = "b_drywet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_drywet_127;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_reflect_120")
	pi = self->__commonstate.params + 2;
	pi->name = "c_reflect";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_reflect_120;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 0.95;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_damp_128")
	pi = self->__commonstate.params + 3;
	pi->name = "d_damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_damp_128;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_size_114")
	pi = self->__commonstate.params + 4;
	pi->name = "e_size";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_size_114;
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
	// initialize parameter 6 ("m_g_freeze_129")
	pi = self->__commonstate.params + 6;
	pi->name = "g_freeze";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_freeze_129;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_lowGain_123")
	pi = self->__commonstate.params + 7;
	pi->name = "h_lowGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_lowGain_123;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_peakGain_133")
	pi = self->__commonstate.params + 8;
	pi->name = "i_peakGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_peakGain_133;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_hiGain_121")
	pi = self->__commonstate.params + 9;
	pi->name = "j_hiGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_hiGain_121;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_lpf_131")
	pi = self->__commonstate.params + 10;
	pi->name = "k_lpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_lpf_131;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_hpf_134")
	pi = self->__commonstate.params + 11;
	pi->name = "l_hpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_hpf_134;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_output_116")
	pi = self->__commonstate.params + 12;
	pi->name = "m_output";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_output_116;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_lowFreq_113")
	pi = self->__commonstate.params + 13;
	pi->name = "n_lowFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_lowFreq_113;
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
	// initialize parameter 15 ("m_p_hiFreq_132")
	pi = self->__commonstate.params + 15;
	pi->name = "p_hiFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_hiFreq_132;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 800;
	pi->outputmax = 15000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_onoffEQ_130")
	pi = self->__commonstate.params + 16;
	pi->name = "q_onoffEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_onoffEQ_130;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 17 ("m_r_onoffCOMP_115")
	pi = self->__commonstate.params + 17;
	pi->name = "r_onoffCOMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_onoffCOMP_115;
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
	pi->outputmin = -36;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_ratio_112")
	pi = self->__commonstate.params + 19;
	pi->name = "t_ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_ratio_112;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_atk_124")
	pi = self->__commonstate.params + 20;
	pi->name = "u_atk";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_atk_124;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 5;
	pi->outputmax = 250;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_rel_122")
	pi = self->__commonstate.params + 21;
	pi->name = "v_rel";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_rel_122;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 5;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_makeup_119")
	pi = self->__commonstate.params + 22;
	pi->name = "w_makeup";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_makeup_119;
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
