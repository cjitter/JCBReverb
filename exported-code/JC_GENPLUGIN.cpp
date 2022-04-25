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
	Delay m_delay_45;
	Delay m_delay_47;
	Delay m_delay_43;
	Delay m_delay_41;
	Delay m_delay_49;
	Delay m_delay_60;
	Delay m_delay_51;
	Delay m_delay_61;
	Delay m_delay_39;
	Delay m_delay_35;
	Delay m_delay_28;
	Delay m_delay_29;
	Delay m_delay_37;
	Delay m_delay_32;
	Delay m_delay_34;
	Delay m_delay_33;
	Delay m_delay_30;
	Delay m_delay_62;
	Delay m_delay_64;
	Delay m_delay_77;
	Delay m_delay_3;
	Delay m_delay_79;
	Delay m_delay_83;
	Delay m_delay_81;
	Delay m_delay_63;
	Delay m_delay_75;
	Delay m_delay_31;
	Delay m_delay_66;
	Delay m_delay_65;
	Delay m_delay_73;
	Delay m_delay_67;
	Delay m_delay_71;
	Delay m_delay_69;
	PlusEquals __m_pluseq_155;
	int __exception;
	int vectorsize;
	t_sample m_history_128;
	t_sample m_history_108;
	t_sample m_f_st_148;
	t_sample m_r_COMPON_149;
	t_sample m_history_107;
	t_sample m_b_drywet_150;
	t_sample m_u_COMPATK_147;
	t_sample m_w_COMPMAKEUP_146;
	t_sample m_h_lowGain_143;
	t_sample m_history_109;
	t_sample m_o_peakFreq_144;
	t_sample m_history_110;
	t_sample m_s_COMPTHD_145;
	t_sample m_d_damp_151;
	t_sample m_history_106;
	t_sample m_k_lpf_152;
	t_sample m_history_99;
	t_sample m_history_100;
	t_sample m_history_98;
	t_sample m_history_96;
	t_sample m_history_97;
	t_sample m_t_COMPRATIO_142;
	t_sample m_history_101;
	t_sample m_history_103;
	t_sample m_history_105;
	t_sample m_history_102;
	t_sample m_p_hiFreq_153;
	t_sample m_history_104;
	t_sample m_history_127;
	t_sample m_i_peakGain_141;
	t_sample m_j_hiGain_139;
	t_sample m_history_123;
	t_sample m_l_hpf_133;
	t_sample m_c_reflect_134;
	t_sample m_history_95;
	t_sample m_history_122;
	t_sample m_history_121;
	t_sample m_history_124;
	t_sample m_history_125;
	t_sample m_history_129;
	t_sample m_n_lowFreq_132;
	t_sample m_history_130;
	t_sample m_a_input_131;
	t_sample m_history_126;
	t_sample m_v_COMPREL_140;
	t_sample m_e_size_135;
	t_sample m_g_freeze_136;
	t_sample m_history_113;
	t_sample m_history_114;
	t_sample m_history_112;
	t_sample m_q_onoffEQ_138;
	t_sample m_history_111;
	t_sample m_history_120;
	t_sample m_history_115;
	t_sample m_history_117;
	t_sample m_history_119;
	t_sample m_history_116;
	t_sample m_m_output_137;
	t_sample m_history_118;
	t_sample m_history_94;
	t_sample m_history_76;
	t_sample m_history_92;
	t_sample m_history_19;
	t_sample m_history_20;
	t_sample m_history_18;
	t_sample m_history_16;
	t_sample m_history_17;
	t_sample m_history_15;
	t_sample m_history_21;
	t_sample m_history_23;
	t_sample m_history_27;
	t_sample m_history_22;
	t_sample m_history_26;
	t_sample m_history_24;
	t_sample m_history_25;
	t_sample m_history_36;
	t_sample m_history_14;
	t_sample m_history_12;
	t_sample m_history_4;
	t_sample m_history_5;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample m_history_13;
	t_sample m_history_6;
	t_sample m_history_8;
	t_sample m_history_11;
	t_sample m_history_7;
	t_sample m_history_10;
	t_sample m_history_9;
	t_sample m_history_93;
	t_sample m_history_38;
	t_sample m_history_42;
	t_sample m_history_82;
	t_sample m_history_84;
	t_sample m_history_80;
	t_sample m_history_74;
	t_sample m_history_78;
	t_sample m_history_72;
	t_sample m_history_85;
	t_sample m_history_87;
	t_sample m_history_91;
	t_sample m_history_86;
	t_sample m_history_90;
	t_sample m_history_88;
	t_sample m_history_89;
	t_sample m_history_40;
	t_sample m_history_70;
	t_sample m_history_59;
	t_sample m_history_50;
	t_sample m_history_52;
	t_sample m_history_48;
	t_sample m_history_44;
	t_sample m_history_46;
	t_sample m_history_68;
	t_sample m_history_53;
	t_sample m_history_55;
	t_sample m_history_58;
	t_sample m_history_54;
	t_sample m_history_57;
	t_sample m_history_56;
	t_sample __m_slide_157;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_delay_3.reset("m_delay_3", samplerate);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_history_17 = ((int)0);
		m_history_18 = ((int)0);
		m_history_19 = ((int)0);
		m_history_20 = ((int)0);
		m_history_21 = ((int)0);
		m_history_22 = ((int)0);
		m_history_23 = ((int)0);
		m_history_24 = ((int)0);
		m_history_25 = ((int)0);
		m_history_26 = ((int)0);
		m_history_27 = ((int)0);
		m_delay_28.reset("m_delay_28", samplerate);
		m_delay_29.reset("m_delay_29", samplerate);
		m_delay_30.reset("m_delay_30", samplerate);
		m_delay_31.reset("m_delay_31", samplerate);
		m_delay_32.reset("m_delay_32", samplerate);
		m_delay_33.reset("m_delay_33", samplerate);
		m_delay_34.reset("m_delay_34", samplerate);
		m_delay_35.reset("m_delay_35", samplerate);
		m_history_36 = ((int)0);
		m_delay_37.reset("m_delay_37", samplerate);
		m_history_38 = ((int)0);
		m_delay_39.reset("m_delay_39", samplerate);
		m_history_40 = ((int)0);
		m_delay_41.reset("m_delay_41", samplerate);
		m_history_42 = ((int)0);
		m_delay_43.reset("m_delay_43", samplerate);
		m_history_44 = ((int)0);
		m_delay_45.reset("m_delay_45", samplerate);
		m_history_46 = ((int)0);
		m_delay_47.reset("m_delay_47", samplerate);
		m_history_48 = ((int)0);
		m_delay_49.reset("m_delay_49", samplerate);
		m_history_50 = ((int)0);
		m_delay_51.reset("m_delay_51", samplerate);
		m_history_52 = ((int)0);
		m_history_53 = ((int)0);
		m_history_54 = ((int)0);
		m_history_55 = ((int)0);
		m_history_56 = ((int)0);
		m_history_57 = ((int)0);
		m_history_58 = ((int)0);
		m_history_59 = ((int)0);
		m_delay_60.reset("m_delay_60", samplerate);
		m_delay_61.reset("m_delay_61", samplerate);
		m_delay_62.reset("m_delay_62", samplerate);
		m_delay_63.reset("m_delay_63", samplerate);
		m_delay_64.reset("m_delay_64", samplerate);
		m_delay_65.reset("m_delay_65", samplerate);
		m_delay_66.reset("m_delay_66", samplerate);
		m_delay_67.reset("m_delay_67", samplerate);
		m_history_68 = ((int)0);
		m_delay_69.reset("m_delay_69", samplerate);
		m_history_70 = ((int)0);
		m_delay_71.reset("m_delay_71", samplerate);
		m_history_72 = ((int)0);
		m_delay_73.reset("m_delay_73", samplerate);
		m_history_74 = ((int)0);
		m_delay_75.reset("m_delay_75", samplerate);
		m_history_76 = ((int)0);
		m_delay_77.reset("m_delay_77", samplerate);
		m_history_78 = ((int)0);
		m_delay_79.reset("m_delay_79", samplerate);
		m_history_80 = ((int)0);
		m_delay_81.reset("m_delay_81", samplerate);
		m_history_82 = ((int)0);
		m_delay_83.reset("m_delay_83", samplerate);
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
		m_history_114 = ((int)0);
		m_history_115 = ((int)0);
		m_history_116 = ((int)0);
		m_history_117 = ((int)0);
		m_history_118 = ((int)0);
		m_history_119 = ((int)0);
		m_history_120 = ((int)0);
		m_history_121 = ((int)0);
		m_history_122 = ((int)0);
		m_history_123 = ((int)0);
		m_history_124 = ((int)0);
		m_history_125 = ((int)0);
		m_history_126 = ((int)0);
		m_history_127 = ((int)0);
		m_history_128 = ((int)0);
		m_history_129 = ((int)0);
		m_history_130 = ((int)0);
		m_a_input_131 = 0;
		m_n_lowFreq_132 = 500;
		m_l_hpf_133 = 20;
		m_c_reflect_134 = 0.86;
		m_e_size_135 = 1;
		m_g_freeze_136 = 0;
		m_m_output_137 = 0;
		m_q_onoffEQ_138 = 0;
		m_j_hiGain_139 = 0;
		m_v_COMPREL_140 = 350;
		m_i_peakGain_141 = 0;
		m_t_COMPRATIO_142 = 2;
		m_h_lowGain_143 = 0;
		m_o_peakFreq_144 = 800;
		m_s_COMPTHD_145 = -18;
		m_w_COMPMAKEUP_146 = 0;
		m_u_COMPATK_147 = 150;
		m_f_st_148 = 0.5;
		m_r_COMPON_149 = 1;
		m_b_drywet_150 = 0.33;
		m_d_damp_151 = 0.8;
		m_k_lpf_152 = 20000;
		m_p_hiFreq_153 = 2000;
		__m_pluseq_155.reset(0);
		__m_slide_157 = 0;
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
		t_sample dbtoa_4547 = dbtoa(m_m_output_137);
		t_sample mul_4817 = (dbtoa_4547 * ((t_sample)0.001));
		t_sample mul_8588 = (m_s_COMPTHD_145 * ((t_sample)0.001));
		t_sample rsub_6397 = (((int)1) - m_r_COMPON_149);
		t_sample mul_6398 = (rsub_6397 * ((t_sample)0.001));
		t_sample dbtoa_6410 = dbtoa(m_w_COMPMAKEUP_146);
		t_sample mul_6404 = (dbtoa_6410 * ((t_sample)0.001));
		t_sample mul_5163 = (m_b_drywet_150 * ((t_sample)0.001));
		int eq_5187 = (m_g_freeze_136 == ((int)1));
		int toSize_5106 = eq_5187;
		t_sample mul_4811 = (toSize_5106 * ((t_sample)0.001));
		t_sample mul_4645 = (m_q_onoffEQ_138 * ((t_sample)0.001));
		t_sample mul_5169 = (m_f_st_148 * ((t_sample)0.001));
		t_sample mul_4665 = (m_n_lowFreq_132 * ((t_sample)0.001));
		t_sample mul_4659 = (m_o_peakFreq_144 * ((t_sample)0.001));
		t_sample mul_4653 = (m_p_hiFreq_153 * ((t_sample)0.001));
		t_sample mul_4837 = (m_h_lowGain_143 * ((t_sample)0.001));
		t_sample mul_4831 = (m_i_peakGain_141 * ((t_sample)0.001));
		t_sample mul_4825 = (m_j_hiGain_139 * ((t_sample)0.001));
		t_sample dbtoa_4546 = dbtoa(m_a_input_131);
		t_sample mul_5157 = (dbtoa_4546 * ((t_sample)0.001));
		t_sample mul_4675 = (m_e_size_135 * ((t_sample)0.001));
		t_sample rsub_5536 = (((int)1) - m_d_damp_151);
		t_sample damp_5176 = rsub_5536;
		t_sample damp_5177 = damp_5176;
		t_sample mul_4849 = (m_k_lpf_152 * ((t_sample)0.001));
		t_sample mul_4843 = (m_l_hpf_133 * ((t_sample)0.001));
		int toSize_5180 = toSize_5106;
		t_sample rsub_5182 = (((t_sample)0.999) - m_c_reflect_134);
		int choice_154 = toSize_5180;
		t_sample gate_5181 = ((choice_154 >= 1) ? rsub_5182 : 0);
		t_sample add_5183 = (m_c_reflect_134 + gate_5181);
		t_sample mul_5124 = (add_5183 * ((t_sample)0.001));
		int rsub_5186 = (((int)1) - eq_5187);
		t_sample mul_5118 = (rsub_5186 * ((t_sample)0.001));
		t_sample rsub_5435 = (((int)1) - damp_5177);
		t_sample div_5424 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_5437 = (((int)1) - rsub_5435);
		t_sample rsub_5449 = (((int)1) - rsub_5435);
		t_sample rsub_5461 = (((int)1) - rsub_5435);
		t_sample rsub_5473 = (((int)1) - rsub_5435);
		t_sample rsub_5485 = (((int)1) - rsub_5435);
		t_sample rsub_5497 = (((int)1) - rsub_5435);
		t_sample rsub_5509 = (((int)1) - rsub_5435);
		t_sample rsub_5521 = (((int)1) - rsub_5435);
		t_sample div_4788 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4774 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4760 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4746 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_5262 = (((int)1) - damp_5176);
		t_sample div_5251 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_5264 = (((int)1) - rsub_5262);
		t_sample rsub_5276 = (((int)1) - rsub_5262);
		t_sample rsub_5288 = (((int)1) - rsub_5262);
		t_sample rsub_5300 = (((int)1) - rsub_5262);
		t_sample rsub_5312 = (((int)1) - rsub_5262);
		t_sample rsub_5324 = (((int)1) - rsub_5262);
		t_sample rsub_5336 = (((int)1) - rsub_5262);
		t_sample rsub_5348 = (((int)1) - rsub_5262);
		t_sample div_4728 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4714 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4700 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_4686 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample mstosamps_7460 = (m_u_COMPATK_147 * (samplerate * 0.001));
		t_sample mstosamps_7461 = (m_v_COMPREL_140 * (samplerate * 0.001));
		t_sample mstosamps_7449 = (((int)100) * (samplerate * 0.001));
		int int_7448 = int(mstosamps_7449);
		int maxb_156 = (-72);
		t_sample iup_158 = (1 / maximum(1, abs(mstosamps_7460)));
		t_sample idown_159 = (1 / maximum(1, abs(mstosamps_7461)));
		t_sample rdiv_7466 = safediv(((int)1), m_t_COMPRATIO_142);
		t_sample rsub_7465 = (((int)1) - rdiv_7466);
		t_sample rdiv_7428 = safediv(((int)1), m_t_COMPRATIO_142);
		t_sample rsub_7427 = (((int)1) - rdiv_7428);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_4818 = (m_history_130 * ((t_sample)0.999));
			t_sample add_4820 = (mul_4817 + mul_4818);
			t_sample gen_4822 = add_4820;
			t_sample history_4819_next_4821 = fixdenorm(add_4820);
			t_sample mul_8589 = (m_history_129 * ((t_sample)0.999));
			t_sample add_8591 = (mul_8588 + mul_8589);
			t_sample gen_8593 = add_8591;
			t_sample history_8590_next_8592 = fixdenorm(add_8591);
			t_sample mul_6399 = (m_history_128 * ((t_sample)0.999));
			t_sample add_6401 = (mul_6398 + mul_6399);
			t_sample gen_6403 = add_6401;
			t_sample history_6400_next_6402 = fixdenorm(add_6401);
			t_sample mul_6405 = (m_history_127 * ((t_sample)0.999));
			t_sample add_6407 = (mul_6404 + mul_6405);
			t_sample gen_6409 = add_6407;
			t_sample history_6406_next_6408 = fixdenorm(add_6407);
			t_sample mul_5164 = (m_history_126 * ((t_sample)0.999));
			t_sample add_5166 = (mul_5163 + mul_5164);
			t_sample gen_5168 = add_5166;
			t_sample history_5165_next_5167 = fixdenorm(add_5166);
			t_sample dry_wet_5145 = gen_5168;
			t_sample mul_4806 = (m_history_125 * ((t_sample)0.999));
			t_sample mul_4805 = (dry_wet_5145 * ((t_sample)0.001));
			t_sample add_4808 = (mul_4805 + mul_4806);
			t_sample gen_4810 = add_4808;
			t_sample history_4807_next_4809 = fixdenorm(add_4808);
			t_sample mul_4812 = (m_history_124 * ((t_sample)0.999));
			t_sample add_4814 = (mul_4811 + mul_4812);
			t_sample gen_4816 = add_4814;
			t_sample history_4813_next_4815 = fixdenorm(add_4814);
			t_sample mul_4646 = (m_history_123 * ((t_sample)0.999));
			t_sample add_4648 = (mul_4645 + mul_4646);
			t_sample gen_4650 = add_4648;
			t_sample history_4647_next_4649 = fixdenorm(add_4648);
			t_sample onOffEQ_4644 = gen_4650;
			t_sample mul_5170 = (m_history_122 * ((t_sample)0.999));
			t_sample add_5172 = (mul_5169 + mul_5170);
			t_sample gen_5174 = add_5172;
			t_sample history_5171_next_5173 = fixdenorm(add_5172);
			t_sample sub_10638 = (gen_5174 - ((int)0));
			t_sample scale_10635 = ((safepow((sub_10638 * ((t_sample)1.4144271570014)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_10625 = scale_10635;
			t_sample mul_4666 = (m_history_121 * ((t_sample)0.999));
			t_sample add_4668 = (mul_4665 + mul_4666);
			t_sample gen_4670 = add_4668;
			t_sample history_4667_next_4669 = fixdenorm(add_4668);
			t_sample mul_4660 = (m_history_120 * ((t_sample)0.999));
			t_sample add_4662 = (mul_4659 + mul_4660);
			t_sample gen_4664 = add_4662;
			t_sample history_4661_next_4663 = fixdenorm(add_4662);
			t_sample mul_4654 = (m_history_119 * ((t_sample)0.999));
			t_sample add_4656 = (mul_4653 + mul_4654);
			t_sample gen_4658 = add_4656;
			t_sample history_4655_next_4657 = fixdenorm(add_4656);
			t_sample mul_4838 = (m_history_118 * ((t_sample)0.999));
			t_sample add_4840 = (mul_4837 + mul_4838);
			t_sample gen_4842 = add_4840;
			t_sample history_4839_next_4841 = fixdenorm(add_4840);
			t_sample mul_4832 = (m_history_117 * ((t_sample)0.999));
			t_sample add_4834 = (mul_4831 + mul_4832);
			t_sample gen_4836 = add_4834;
			t_sample history_4833_next_4835 = fixdenorm(add_4834);
			t_sample mul_4826 = (m_history_116 * ((t_sample)0.999));
			t_sample add_4828 = (mul_4825 + mul_4826);
			t_sample gen_4830 = add_4828;
			t_sample history_4827_next_4829 = fixdenorm(add_4828);
			t_sample mul_5158 = (m_history_115 * ((t_sample)0.999));
			t_sample add_5160 = (mul_5157 + mul_5158);
			t_sample gen_5162 = add_5160;
			t_sample history_5159_next_5161 = fixdenorm(add_5160);
			t_sample mul_5088 = (in2 * gen_5162);
			t_sample right_5136 = mul_5088;
			t_sample right_5142 = right_5136;
			t_sample right_5109 = right_5136;
			int eq_5116 = (right_5109 == ((int)0));
			t_sample mul_5097 = (m_history_114 * ((t_sample)0.999));
			t_sample mul_5096 = (eq_5116 * ((t_sample)0.001));
			t_sample add_5099 = (mul_5096 + mul_5097);
			t_sample gen_5101 = add_5099;
			t_sample history_5098_next_5100 = fixdenorm(add_5099);
			t_sample mul_5089 = (in1 * gen_5162);
			t_sample left_5137 = mul_5089;
			t_sample left_5143 = left_5137;
			t_sample mix_10639 = (left_5143 + (gen_4816 * (((int)0) - left_5143)));
			t_sample left_5113 = left_5137;
			t_sample mix_10640 = (((int)0) + (gen_5101 * (left_5113 - ((int)0))));
			t_sample mix_5112 = mix_10640;
			t_sample add_10642 = (mix_5112 + right_5142);
			t_sample mix_10641 = (add_10642 + (gen_4816 * (((int)0) - add_10642)));
			t_sample sqrt_5149 = sqrt(gen_5174);
			t_sample rsub_5175 = (((int)1) - gen_5174);
			t_sample sqrt_5150 = sqrt(rsub_5175);
			t_sample mul_4676 = (m_history_113 * ((t_sample)0.999));
			t_sample add_4678 = (mul_4675 + mul_4676);
			t_sample gen_4680 = add_4678;
			t_sample history_4677_next_4679 = fixdenorm(add_4678);
			t_sample escala_Size_4803 = gen_4680;
			t_sample escala_Size_4802 = escala_Size_4803;
			t_sample escala_Size_4742 = escala_Size_4803;
			t_sample escala_Size_4804 = escala_Size_4803;
			t_sample mul_4850 = (m_history_112 * ((t_sample)0.999));
			t_sample add_4852 = (mul_4849 + mul_4850);
			t_sample gen_4854 = add_4852;
			t_sample history_4851_next_4853 = fixdenorm(add_4852);
			t_sample mul_4844 = (m_history_111 * ((t_sample)0.999));
			t_sample add_4846 = (mul_4843 + mul_4844);
			t_sample gen_4848 = add_4846;
			t_sample history_4845_next_4847 = fixdenorm(add_4846);
			t_sample toMoud_5117 = gen_5174;
			t_sample mul_5125 = (m_history_110 * ((t_sample)0.999));
			t_sample add_5127 = (mul_5124 + mul_5125);
			t_sample gen_5129 = add_5127;
			t_sample history_5126_next_5128 = fixdenorm(add_5127);
			t_sample left_5108 = left_5137;
			t_sample right_5107 = right_5136;
			int eq_5110 = (left_5108 == right_5107);
			t_sample mul_5091 = (m_history_109 * ((t_sample)0.999));
			t_sample mul_5090 = (eq_5110 * ((t_sample)0.001));
			t_sample add_5093 = (mul_5090 + mul_5091);
			t_sample gen_5095 = add_5093;
			t_sample history_5092_next_5094 = fixdenorm(add_5093);
			t_sample add_10644 = (gen_5095 + gen_5101);
			t_sample mix_10643 = (((int)0) + (add_10644 * (toMoud_5117 - ((int)0))));
			t_sample mix_5115 = mix_10643;
			t_sample mix_10645 = (((int)0) + (mix_5115 * ((int)0)));
			t_sample mix_5133 = mix_10645;
			t_sample zeroL_5178 = mix_5133;
			t_sample mix_10646 = (((int)0) + (mix_5115 * ((int)23)));
			t_sample mix_5131 = mix_10646;
			t_sample zeroR_5179 = mix_5131;
			t_sample mul_5119 = (m_history_108 * ((t_sample)0.999));
			t_sample add_5121 = (mul_5118 + mul_5119);
			t_sample gen_5123 = add_5121;
			t_sample history_5120_next_5122 = fixdenorm(add_5121);
			t_sample freeze_5184 = gen_5123;
			t_sample mul_5185 = (left_5137 * freeze_5184);
			t_sample toFILTERS_c45L_4550 = mul_5185;
			t_sample freeze_5155 = freeze_5184;
			t_sample mul_5156 = ((mix_5112 + right_5136) * freeze_5155);
			t_sample toFILTERS_c45R_4549 = mul_5156;
			t_sample omega = safediv((gen_4848 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) + cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((-(((int)1) + cs)) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_4623 = a2;
			t_sample expr_4624 = a1;
			t_sample expr_4625 = a2;
			t_sample expr_4626 = b1;
			t_sample expr_4627 = b2;
			t_sample omega_4634 = safediv((gen_4854 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_4633 = sin(omega_4634);
			t_sample cs_4640 = cos(omega_4634);
			t_sample alpha_4641 = ((sn_4633 * ((t_sample)0.5)) * ((int)1));
			t_sample b_4638 = safediv(((int)1), (((int)1) + alpha_4641));
			t_sample a_4639 = (((((int)1) - cs_4640) * ((t_sample)0.5)) * b_4638);
			t_sample a_4637 = ((((int)1) - cs_4640) * b_4638);
			t_sample b_4636 = ((((int)-2) * cs_4640) * b_4638);
			t_sample b_4635 = ((((int)1) - alpha_4641) * b_4638);
			t_sample expr_4628 = a_4639;
			t_sample expr_4629 = a_4637;
			t_sample expr_4630 = a_4639;
			t_sample expr_4631 = b_4636;
			t_sample expr_4632 = b_4635;
			t_sample mul_4597 = (m_history_104 * expr_4630);
			t_sample mul_4607 = (m_history_105 * expr_4630);
			t_sample mul_4599 = (m_history_102 * expr_4629);
			t_sample mul_4609 = (m_history_103 * expr_4629);
			t_sample mul_4602 = (toFILTERS_c45R_4549 * expr_4628);
			t_sample mul_4612 = (toFILTERS_c45L_4550 * expr_4628);
			t_sample mul_4593 = (m_history_106 * expr_4632);
			t_sample mul_4603 = (m_history_107 * expr_4632);
			t_sample mul_4595 = (m_history_101 * expr_4631);
			t_sample sub_4601 = (((mul_4602 + mul_4599) + mul_4597) - (mul_4595 + mul_4593));
			t_sample gen_4622 = sub_4601;
			t_sample mul_4605 = (m_history_100 * expr_4631);
			t_sample sub_4611 = (((mul_4607 + mul_4609) + mul_4612) - (mul_4605 + mul_4603));
			t_sample gen_4621 = sub_4611;
			t_sample history_4604_next_4613 = fixdenorm(m_history_100);
			t_sample history_4594_next_4614 = fixdenorm(m_history_101);
			t_sample history_4608_next_4615 = fixdenorm(m_history_103);
			t_sample history_4598_next_4616 = fixdenorm(m_history_102);
			t_sample history_4610_next_4617 = fixdenorm(toFILTERS_c45L_4550);
			t_sample history_4600_next_4618 = fixdenorm(toFILTERS_c45R_4549);
			t_sample history_4596_next_4619 = fixdenorm(sub_4601);
			t_sample history_4606_next_4620 = fixdenorm(sub_4611);
			t_sample mul_4562 = (m_history_97 * expr_4625);
			t_sample mul_4572 = (m_history_98 * expr_4625);
			t_sample mul_4564 = (m_history_95 * expr_4624);
			t_sample mul_4574 = (m_history_94 * expr_4624);
			t_sample mul_4567 = (gen_4622 * expr_4623);
			t_sample mul_4577 = (gen_4621 * expr_4623);
			t_sample mul_4558 = (m_history_99 * expr_4627);
			t_sample mul_4568 = (m_history_96 * expr_4627);
			t_sample mul_4560 = (m_history_93 * expr_4626);
			t_sample sub_4566 = (((mul_4567 + mul_4564) + mul_4562) - (mul_4560 + mul_4558));
			t_sample gen_4587 = sub_4566;
			t_sample mul_4570 = (m_history_92 * expr_4626);
			t_sample sub_4576 = (((mul_4572 + mul_4574) + mul_4577) - (mul_4570 + mul_4568));
			t_sample gen_4586 = sub_4576;
			t_sample history_4559_next_4578 = fixdenorm(m_history_93);
			t_sample history_4573_next_4579 = fixdenorm(m_history_94);
			t_sample history_4563_next_4580 = fixdenorm(m_history_95);
			t_sample history_4569_next_4581 = fixdenorm(m_history_92);
			t_sample history_4565_next_4582 = fixdenorm(gen_4622);
			t_sample history_4575_next_4583 = fixdenorm(gen_4621);
			t_sample history_4561_next_4584 = fixdenorm(sub_4566);
			t_sample history_4571_next_4585 = fixdenorm(sub_4576);
			t_sample gen_4642 = gen_4586;
			t_sample gen_4643 = gen_4587;
			t_sample fromFILTERS_c45L_4552 = gen_4642;
			t_sample mul_5409 = (div_5424 * escala_Size_4804);
			t_sample mul_5416 = (((int)1277) * mul_5409);
			t_sample mul_5380 = (m_history_91 * ((t_sample)0.999));
			t_sample mul_5379 = (mul_5416 * ((t_sample)0.001));
			t_sample add_5382 = (mul_5379 + mul_5380);
			t_sample gen_5384 = add_5382;
			t_sample history_5381_next_5383 = fixdenorm(add_5382);
			t_sample gen_5431 = gen_5384;
			t_sample mul_5414 = (((int)1356) * mul_5409);
			t_sample mul_5374 = (m_history_90 * ((t_sample)0.999));
			t_sample mul_5373 = (mul_5414 * ((t_sample)0.001));
			t_sample add_5376 = (mul_5373 + mul_5374);
			t_sample gen_5378 = add_5376;
			t_sample history_5375_next_5377 = fixdenorm(add_5376);
			t_sample gen_5432 = gen_5378;
			t_sample mul_5410 = (((int)1116) * mul_5409);
			t_sample mul_5362 = (m_history_89 * ((t_sample)0.999));
			t_sample mul_5361 = (mul_5410 * ((t_sample)0.001));
			t_sample add_5364 = (mul_5361 + mul_5362);
			t_sample gen_5366 = add_5364;
			t_sample history_5363_next_5365 = fixdenorm(add_5364);
			t_sample gen_5434 = gen_5366;
			t_sample mul_5420 = (((int)1491) * mul_5409);
			t_sample mul_5392 = (m_history_88 * ((t_sample)0.999));
			t_sample mul_5391 = (mul_5420 * ((t_sample)0.001));
			t_sample add_5394 = (mul_5391 + mul_5392);
			t_sample gen_5396 = add_5394;
			t_sample history_5393_next_5395 = fixdenorm(add_5394);
			t_sample gen_5429 = gen_5396;
			t_sample mul_5412 = (((int)1188) * mul_5409);
			t_sample mul_5368 = (m_history_87 * ((t_sample)0.999));
			t_sample mul_5367 = (mul_5412 * ((t_sample)0.001));
			t_sample add_5370 = (mul_5367 + mul_5368);
			t_sample gen_5372 = add_5370;
			t_sample history_5369_next_5371 = fixdenorm(add_5370);
			t_sample gen_5433 = gen_5372;
			t_sample mul_5422 = (((int)1617) * mul_5409);
			t_sample mul_5398 = (m_history_86 * ((t_sample)0.999));
			t_sample mul_5397 = (mul_5422 * ((t_sample)0.001));
			t_sample add_5400 = (mul_5397 + mul_5398);
			t_sample gen_5402 = add_5400;
			t_sample history_5399_next_5401 = fixdenorm(add_5400);
			t_sample gen_5428 = gen_5402;
			t_sample mul_5418 = (((int)1422) * mul_5409);
			t_sample mul_5386 = (m_history_85 * ((t_sample)0.999));
			t_sample mul_5385 = (mul_5418 * ((t_sample)0.001));
			t_sample add_5388 = (mul_5385 + mul_5386);
			t_sample gen_5390 = add_5388;
			t_sample history_5387_next_5389 = fixdenorm(add_5388);
			t_sample gen_5430 = gen_5390;
			t_sample mul_5425 = (((int)1557) * mul_5409);
			t_sample mul_5404 = (m_history_84 * ((t_sample)0.999));
			t_sample mul_5403 = (mul_5425 * ((t_sample)0.001));
			t_sample add_5406 = (mul_5403 + mul_5404);
			t_sample gen_5408 = add_5406;
			t_sample history_5405_next_5407 = fixdenorm(add_5406);
			t_sample gen_5427 = gen_5408;
			t_sample mul_5439 = (m_history_82 * rsub_5437);
			t_sample add_5436 = (zeroL_5178 + gen_5434);
			t_sample tap_5445 = m_delay_83.read_linear(add_5436);
			t_sample mul_5442 = (tap_5445 * rsub_5435);
			t_sample add_5441 = (mul_5442 + mul_5439);
			t_sample mul_5438 = (add_5441 * gen_5129);
			t_sample add_5443 = (fromFILTERS_c45L_4552 + mul_5438);
			t_sample gen_5447 = add_5443;
			t_sample history_5440_next_5446 = fixdenorm(add_5441);
			t_sample mul_5451 = (m_history_80 * rsub_5449);
			t_sample add_5448 = (zeroL_5178 + gen_5433);
			t_sample tap_5457 = m_delay_81.read_linear(add_5448);
			t_sample mul_5454 = (tap_5457 * rsub_5435);
			t_sample add_5453 = (mul_5454 + mul_5451);
			t_sample mul_5450 = (add_5453 * gen_5129);
			t_sample add_5455 = (fromFILTERS_c45L_4552 + mul_5450);
			t_sample gen_5459 = add_5455;
			t_sample history_5452_next_5458 = fixdenorm(add_5453);
			t_sample mul_5463 = (m_history_78 * rsub_5461);
			t_sample add_5460 = (zeroL_5178 + gen_5432);
			t_sample tap_5469 = m_delay_79.read_linear(add_5460);
			t_sample mul_5466 = (tap_5469 * rsub_5435);
			t_sample add_5465 = (mul_5466 + mul_5463);
			t_sample mul_5462 = (add_5465 * gen_5129);
			t_sample add_5467 = (fromFILTERS_c45L_4552 + mul_5462);
			t_sample gen_5471 = add_5467;
			t_sample history_5464_next_5470 = fixdenorm(add_5465);
			t_sample mul_5475 = (m_history_76 * rsub_5473);
			t_sample add_5472 = (zeroL_5178 + gen_5431);
			t_sample tap_5481 = m_delay_77.read_linear(add_5472);
			t_sample mul_5478 = (tap_5481 * rsub_5435);
			t_sample add_5477 = (mul_5478 + mul_5475);
			t_sample mul_5474 = (add_5477 * gen_5129);
			t_sample add_5479 = (fromFILTERS_c45L_4552 + mul_5474);
			t_sample gen_5483 = add_5479;
			t_sample history_5476_next_5482 = fixdenorm(add_5477);
			t_sample mul_5487 = (m_history_74 * rsub_5485);
			t_sample add_5484 = (zeroL_5178 + gen_5430);
			t_sample tap_5493 = m_delay_75.read_linear(add_5484);
			t_sample mul_5490 = (tap_5493 * rsub_5435);
			t_sample add_5489 = (mul_5490 + mul_5487);
			t_sample mul_5486 = (add_5489 * gen_5129);
			t_sample add_5491 = (fromFILTERS_c45L_4552 + mul_5486);
			t_sample gen_5495 = add_5491;
			t_sample history_5488_next_5494 = fixdenorm(add_5489);
			t_sample mul_5499 = (m_history_72 * rsub_5497);
			t_sample add_5496 = (zeroL_5178 + gen_5429);
			t_sample tap_5505 = m_delay_73.read_linear(add_5496);
			t_sample mul_5502 = (tap_5505 * rsub_5435);
			t_sample add_5501 = (mul_5502 + mul_5499);
			t_sample mul_5498 = (add_5501 * gen_5129);
			t_sample add_5503 = (fromFILTERS_c45L_4552 + mul_5498);
			t_sample gen_5507 = add_5503;
			t_sample history_5500_next_5506 = fixdenorm(add_5501);
			t_sample mul_5511 = (m_history_70 * rsub_5509);
			t_sample add_5508 = (zeroL_5178 + gen_5428);
			t_sample tap_5517 = m_delay_71.read_linear(add_5508);
			t_sample mul_5514 = (tap_5517 * rsub_5435);
			t_sample add_5513 = (mul_5514 + mul_5511);
			t_sample mul_5510 = (add_5513 * gen_5129);
			t_sample add_5515 = (fromFILTERS_c45L_4552 + mul_5510);
			t_sample gen_5519 = add_5515;
			t_sample history_5512_next_5518 = fixdenorm(add_5513);
			t_sample mul_5523 = (m_history_68 * rsub_5521);
			t_sample add_5520 = (zeroL_5178 + gen_5427);
			t_sample tap_5529 = m_delay_69.read_linear(add_5520);
			t_sample mul_5526 = (tap_5529 * rsub_5435);
			t_sample add_5525 = (mul_5526 + mul_5523);
			t_sample mul_5522 = (add_5525 * gen_5129);
			t_sample add_5527 = (fromFILTERS_c45L_4552 + mul_5522);
			t_sample gen_5531 = add_5527;
			t_sample history_5524_next_5530 = fixdenorm(add_5525);
			t_sample mul_5532 = ((((((((gen_5531 + gen_5519) + gen_5507) + gen_5495) + gen_5483) + gen_5471) + gen_5459) + gen_5447) * ((t_sample)0.125));
			t_sample gen_5533 = mul_5532;
			t_sample mul_4797 = (gen_5533 * ((t_sample)-0.5));
			t_sample mul_4787 = (div_4788 * escala_Size_4802);
			t_sample mul_4789 = (((int)255) * mul_4787);
			t_sample add_4791 = (((int)0) + mul_4789);
			t_sample tap_4799 = m_delay_67.read_linear(add_4791);
			t_sample tap_4794 = m_delay_66.read_linear(add_4791);
			t_sample mul_4792 = (tap_4794 * ((t_sample)0.5));
			t_sample add_4795 = (mul_4797 + (tap_4799 + mul_4792));
			t_sample gen_4800 = add_4795;
			t_sample mul_4783 = (gen_4800 * ((t_sample)-0.5));
			t_sample mul_4773 = (div_4774 * escala_Size_4802);
			t_sample mul_4775 = (((int)556) * mul_4773);
			t_sample add_4777 = (((int)0) + mul_4775);
			t_sample tap_4785 = m_delay_65.read_linear(add_4777);
			t_sample tap_4780 = m_delay_64.read_linear(add_4777);
			t_sample mul_4778 = (tap_4780 * ((t_sample)0.5));
			t_sample add_4781 = (mul_4783 + (tap_4785 + mul_4778));
			t_sample gen_4786 = add_4781;
			t_sample mul_4769 = (gen_4786 * ((t_sample)-0.5));
			t_sample mul_4759 = (div_4760 * escala_Size_4802);
			t_sample mul_4761 = (((int)441) * mul_4759);
			t_sample add_4763 = (((int)0) + mul_4761);
			t_sample tap_4771 = m_delay_63.read_linear(add_4763);
			t_sample tap_4766 = m_delay_62.read_linear(add_4763);
			t_sample mul_4764 = (tap_4766 * ((t_sample)0.5));
			t_sample add_4767 = (mul_4769 + (tap_4771 + mul_4764));
			t_sample gen_4772 = add_4767;
			t_sample mul_4755 = (gen_4772 * ((t_sample)-0.5));
			t_sample mul_4745 = (div_4746 * escala_Size_4802);
			t_sample mul_4747 = (((int)341) * mul_4745);
			t_sample add_4749 = (((int)0) + mul_4747);
			t_sample tap_4757 = m_delay_61.read_linear(add_4749);
			t_sample tap_4752 = m_delay_60.read_linear(add_4749);
			t_sample mul_4750 = (tap_4752 * ((t_sample)0.5));
			t_sample add_4753 = (mul_4755 + (tap_4757 + mul_4750));
			t_sample gen_4758 = add_4753;
			t_sample gen_4801 = gen_4758;
			t_sample matrizMS_c45L_5135 = gen_4801;
			t_sample fromFILTERS_c45R_4551 = gen_4643;
			t_sample mul_5236 = (div_5251 * escala_Size_4803);
			t_sample mul_5252 = (((int)1557) * mul_5236);
			t_sample mul_5231 = (m_history_59 * ((t_sample)0.999));
			t_sample mul_5230 = (mul_5252 * ((t_sample)0.001));
			t_sample add_5233 = (mul_5230 + mul_5231);
			t_sample gen_5235 = add_5233;
			t_sample history_5232_next_5234 = fixdenorm(add_5233);
			t_sample gen_5254 = gen_5235;
			t_sample mul_5247 = (((int)1491) * mul_5236);
			t_sample mul_5219 = (m_history_58 * ((t_sample)0.999));
			t_sample mul_5218 = (mul_5247 * ((t_sample)0.001));
			t_sample add_5221 = (mul_5218 + mul_5219);
			t_sample gen_5223 = add_5221;
			t_sample history_5220_next_5222 = fixdenorm(add_5221);
			t_sample gen_5256 = gen_5223;
			t_sample mul_5245 = (((int)1422) * mul_5236);
			t_sample mul_5213 = (m_history_57 * ((t_sample)0.999));
			t_sample mul_5212 = (mul_5245 * ((t_sample)0.001));
			t_sample add_5215 = (mul_5212 + mul_5213);
			t_sample gen_5217 = add_5215;
			t_sample history_5214_next_5216 = fixdenorm(add_5215);
			t_sample gen_5257 = gen_5217;
			t_sample mul_5249 = (((int)1617) * mul_5236);
			t_sample mul_5225 = (m_history_56 * ((t_sample)0.999));
			t_sample mul_5224 = (mul_5249 * ((t_sample)0.001));
			t_sample add_5227 = (mul_5224 + mul_5225);
			t_sample gen_5229 = add_5227;
			t_sample history_5226_next_5228 = fixdenorm(add_5227);
			t_sample gen_5255 = gen_5229;
			t_sample mul_5243 = (((int)1277) * mul_5236);
			t_sample mul_5207 = (m_history_55 * ((t_sample)0.999));
			t_sample mul_5206 = (mul_5243 * ((t_sample)0.001));
			t_sample add_5209 = (mul_5206 + mul_5207);
			t_sample gen_5211 = add_5209;
			t_sample history_5208_next_5210 = fixdenorm(add_5209);
			t_sample gen_5258 = gen_5211;
			t_sample mul_5239 = (((int)1188) * mul_5236);
			t_sample mul_5195 = (m_history_54 * ((t_sample)0.999));
			t_sample mul_5194 = (mul_5239 * ((t_sample)0.001));
			t_sample add_5197 = (mul_5194 + mul_5195);
			t_sample gen_5199 = add_5197;
			t_sample history_5196_next_5198 = fixdenorm(add_5197);
			t_sample gen_5260 = gen_5199;
			t_sample mul_5237 = (((int)1116) * mul_5236);
			t_sample mul_5189 = (m_history_53 * ((t_sample)0.999));
			t_sample mul_5188 = (mul_5237 * ((t_sample)0.001));
			t_sample add_5191 = (mul_5188 + mul_5189);
			t_sample gen_5193 = add_5191;
			t_sample history_5190_next_5192 = fixdenorm(add_5191);
			t_sample gen_5261 = gen_5193;
			t_sample mul_5241 = (((int)1356) * mul_5236);
			t_sample mul_5201 = (m_history_52 * ((t_sample)0.999));
			t_sample mul_5200 = (mul_5241 * ((t_sample)0.001));
			t_sample add_5203 = (mul_5200 + mul_5201);
			t_sample gen_5205 = add_5203;
			t_sample history_5202_next_5204 = fixdenorm(add_5203);
			t_sample gen_5259 = gen_5205;
			t_sample mul_5266 = (m_history_50 * rsub_5264);
			t_sample add_5263 = (zeroR_5179 + gen_5261);
			t_sample tap_5272 = m_delay_51.read_linear(add_5263);
			t_sample mul_5269 = (tap_5272 * rsub_5262);
			t_sample add_5268 = (mul_5269 + mul_5266);
			t_sample mul_5265 = (add_5268 * gen_5129);
			t_sample add_5270 = (fromFILTERS_c45R_4551 + mul_5265);
			t_sample gen_5274 = add_5270;
			t_sample history_5267_next_5273 = fixdenorm(add_5268);
			t_sample mul_5278 = (m_history_48 * rsub_5276);
			t_sample add_5275 = (zeroR_5179 + gen_5260);
			t_sample tap_5284 = m_delay_49.read_linear(add_5275);
			t_sample mul_5281 = (tap_5284 * rsub_5262);
			t_sample add_5280 = (mul_5281 + mul_5278);
			t_sample mul_5277 = (add_5280 * gen_5129);
			t_sample add_5282 = (fromFILTERS_c45R_4551 + mul_5277);
			t_sample gen_5286 = add_5282;
			t_sample history_5279_next_5285 = fixdenorm(add_5280);
			t_sample mul_5290 = (m_history_46 * rsub_5288);
			t_sample add_5287 = (zeroR_5179 + gen_5259);
			t_sample tap_5296 = m_delay_47.read_linear(add_5287);
			t_sample mul_5293 = (tap_5296 * rsub_5262);
			t_sample add_5292 = (mul_5293 + mul_5290);
			t_sample mul_5289 = (add_5292 * gen_5129);
			t_sample add_5294 = (fromFILTERS_c45R_4551 + mul_5289);
			t_sample gen_5298 = add_5294;
			t_sample history_5291_next_5297 = fixdenorm(add_5292);
			t_sample mul_5302 = (m_history_44 * rsub_5300);
			t_sample add_5299 = (zeroR_5179 + gen_5258);
			t_sample tap_5308 = m_delay_45.read_linear(add_5299);
			t_sample mul_5305 = (tap_5308 * rsub_5262);
			t_sample add_5304 = (mul_5305 + mul_5302);
			t_sample mul_5301 = (add_5304 * gen_5129);
			t_sample add_5306 = (fromFILTERS_c45R_4551 + mul_5301);
			t_sample gen_5310 = add_5306;
			t_sample history_5303_next_5309 = fixdenorm(add_5304);
			t_sample mul_5314 = (m_history_42 * rsub_5312);
			t_sample add_5311 = (zeroR_5179 + gen_5257);
			t_sample tap_5320 = m_delay_43.read_linear(add_5311);
			t_sample mul_5317 = (tap_5320 * rsub_5262);
			t_sample add_5316 = (mul_5317 + mul_5314);
			t_sample mul_5313 = (add_5316 * gen_5129);
			t_sample add_5318 = (fromFILTERS_c45R_4551 + mul_5313);
			t_sample gen_5322 = add_5318;
			t_sample history_5315_next_5321 = fixdenorm(add_5316);
			t_sample mul_5326 = (m_history_40 * rsub_5324);
			t_sample add_5323 = (zeroR_5179 + gen_5256);
			t_sample tap_5332 = m_delay_41.read_linear(add_5323);
			t_sample mul_5329 = (tap_5332 * rsub_5262);
			t_sample add_5328 = (mul_5329 + mul_5326);
			t_sample mul_5325 = (add_5328 * gen_5129);
			t_sample add_5330 = (fromFILTERS_c45R_4551 + mul_5325);
			t_sample gen_5334 = add_5330;
			t_sample history_5327_next_5333 = fixdenorm(add_5328);
			t_sample mul_5338 = (m_history_38 * rsub_5336);
			t_sample add_5335 = (zeroR_5179 + gen_5255);
			t_sample tap_5344 = m_delay_39.read_linear(add_5335);
			t_sample mul_5341 = (tap_5344 * rsub_5262);
			t_sample add_5340 = (mul_5341 + mul_5338);
			t_sample mul_5337 = (add_5340 * gen_5129);
			t_sample add_5342 = (fromFILTERS_c45R_4551 + mul_5337);
			t_sample gen_5346 = add_5342;
			t_sample history_5339_next_5345 = fixdenorm(add_5340);
			t_sample mul_5350 = (m_history_36 * rsub_5348);
			t_sample add_5347 = (zeroR_5179 + gen_5254);
			t_sample tap_5356 = m_delay_37.read_linear(add_5347);
			t_sample mul_5353 = (tap_5356 * rsub_5262);
			t_sample add_5352 = (mul_5353 + mul_5350);
			t_sample mul_5349 = (add_5352 * gen_5129);
			t_sample add_5354 = (fromFILTERS_c45R_4551 + mul_5349);
			t_sample gen_5358 = add_5354;
			t_sample history_5351_next_5357 = fixdenorm(add_5352);
			t_sample mul_5359 = ((((((((gen_5358 + gen_5346) + gen_5334) + gen_5322) + gen_5310) + gen_5298) + gen_5286) + gen_5274) * ((t_sample)0.125));
			t_sample gen_5360 = mul_5359;
			t_sample mul_4737 = (gen_5360 * ((t_sample)-0.5));
			t_sample mul_4727 = (div_4728 * escala_Size_4742);
			t_sample mul_4729 = (((int)255) * mul_4727);
			t_sample add_4731 = (((int)0) + mul_4729);
			t_sample tap_4739 = m_delay_35.read_linear(add_4731);
			t_sample tap_4734 = m_delay_34.read_linear(add_4731);
			t_sample mul_4732 = (tap_4734 * ((t_sample)0.5));
			t_sample add_4735 = (mul_4737 + (tap_4739 + mul_4732));
			t_sample gen_4740 = add_4735;
			t_sample mul_4723 = (gen_4740 * ((t_sample)-0.5));
			t_sample mul_4713 = (div_4714 * escala_Size_4742);
			t_sample mul_4715 = (((int)556) * mul_4713);
			t_sample add_4717 = (((int)0) + mul_4715);
			t_sample tap_4725 = m_delay_33.read_linear(add_4717);
			t_sample tap_4720 = m_delay_32.read_linear(add_4717);
			t_sample mul_4718 = (tap_4720 * ((t_sample)0.5));
			t_sample add_4721 = (mul_4723 + (tap_4725 + mul_4718));
			t_sample gen_4726 = add_4721;
			t_sample mul_4709 = (gen_4726 * ((t_sample)-0.5));
			t_sample mul_4699 = (div_4700 * escala_Size_4742);
			t_sample mul_4701 = (((int)441) * mul_4699);
			t_sample add_4703 = (((int)0) + mul_4701);
			t_sample tap_4711 = m_delay_31.read_linear(add_4703);
			t_sample tap_4706 = m_delay_30.read_linear(add_4703);
			t_sample mul_4704 = (tap_4706 * ((t_sample)0.5));
			t_sample add_4707 = (mul_4709 + (tap_4711 + mul_4704));
			t_sample gen_4712 = add_4707;
			t_sample mul_4695 = (gen_4712 * ((t_sample)-0.5));
			t_sample mul_4685 = (div_4686 * escala_Size_4742);
			t_sample mul_4687 = (((int)341) * mul_4685);
			t_sample add_4689 = (((int)0) + mul_4687);
			t_sample tap_4697 = m_delay_29.read_linear(add_4689);
			t_sample tap_4692 = m_delay_28.read_linear(add_4689);
			t_sample mul_4690 = (tap_4692 * ((t_sample)0.5));
			t_sample add_4693 = (mul_4695 + (tap_4697 + mul_4690));
			t_sample gen_4698 = add_4693;
			t_sample gen_4741 = gen_4698;
			t_sample matrizMS_c45R_5134 = gen_4741;
			t_sample add_5154 = (matrizMS_c45L_5135 + matrizMS_c45R_5134);
			t_sample mul_5152 = (add_5154 * sqrt_5150);
			t_sample sub_5153 = (matrizMS_c45L_5135 - matrizMS_c45R_5134);
			t_sample mul_5151 = (sub_5153 * sqrt_5149);
			t_sample add_5148 = (mul_5152 + mul_5151);
			t_sample mul_5139 = (add_5148 * scale_10625);
			t_sample filterL_4672 = mul_5139;
			t_sample sub_5147 = (mul_5152 - mul_5151);
			t_sample mul_5138 = (sub_5147 * scale_10625);
			t_sample filterR_4671 = mul_5138;
			t_sample dbtoa_4855 = dbtoa(gen_4830);
			t_sample dbtoa_4856 = dbtoa(gen_4836);
			t_sample dbtoa_4857 = dbtoa(gen_4842);
			t_sample min_4894 = ((gen_4670 < ((int)0)) ? ((int)0) : gen_4670);
			t_sample min_4893 = ((dbtoa_4857 < ((int)0)) ? ((int)0) : dbtoa_4857);
			t_sample omega_10627 = safediv((min_4894 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_10632 = sin(omega_10627);
			t_sample cs_10630 = cos(omega_10627);
			t_sample A = sqrt(min_4893);
			t_sample beta = sqrt(((((A * A) + ((int)1)) * ((t_sample)1.4144271570014)) - ((A - ((int)1)) * (A - ((int)1)))));
			t_sample b_10633 = safediv(((int)1), (((A + ((int)1)) + ((A - ((int)1)) * cs_10630)) + (beta * sn_10632)));
			t_sample a0 = ((A * (((A + ((int)1)) - ((A - ((int)1)) * cs_10630)) + (beta * sn_10632))) * b_10633);
			t_sample a_10631 = (((((int)2) * A) * ((A - ((int)1)) - ((A + ((int)1)) * cs_10630))) * b_10633);
			t_sample a_10628 = ((A * (((A + ((int)1)) - ((A - ((int)1)) * cs_10630)) - (beta * sn_10632))) * b_10633);
			t_sample b_10634 = ((((int)-2) * ((A - ((int)1)) + ((A + ((int)1)) * cs_10630))) * b_10633);
			t_sample b_10629 = ((((A + ((int)1)) + ((A - ((int)1)) * cs_10630)) - (beta * sn_10632)) * b_10633);
			t_sample expr_4910 = a0;
			t_sample expr_4911 = a_10631;
			t_sample expr_4912 = a_10628;
			t_sample expr_4913 = b_10634;
			t_sample expr_4914 = b_10629;
			t_sample mul_4904 = (filterR_4671 * expr_4910);
			t_sample mul_4901 = (m_history_25 * expr_4911);
			t_sample mul_4899 = (m_history_27 * expr_4912);
			t_sample mul_4895 = (m_history_26 * expr_4914);
			t_sample mul_4897 = (m_history_24 * expr_4913);
			t_sample sub_4903 = (((mul_4899 + mul_4901) + mul_4904) - (mul_4897 + mul_4895));
			t_sample gen_4909 = sub_4903;
			t_sample history_4900_next_4905 = fixdenorm(m_history_25);
			t_sample history_4896_next_4906 = fixdenorm(m_history_24);
			t_sample history_4902_next_4907 = fixdenorm(filterR_4671);
			t_sample history_4898_next_4908 = fixdenorm(sub_4903);
			t_sample gen_4915 = gen_4909;
			t_sample min_4923 = ((gen_4664 < ((int)0)) ? ((int)0) : gen_4664);
			t_sample min_4922 = ((dbtoa_4856 < ((int)0)) ? ((int)0) : dbtoa_4856);
			t_sample omega_5039 = safediv((min_4923 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_5041 = sin(omega_5039);
			t_sample cs_5037 = cos(omega_5039);
			t_sample alpha_10626 = ((sn_5041 * ((t_sample)0.5)) * ((t_sample)1.4144271570014));
			t_sample A_5038 = sqrt(min_4922);
			t_sample one_over_A = safediv(((int)1), A_5038);
			t_sample b_5033 = safediv(((int)1), (((int)1) + (alpha_10626 * one_over_A)));
			t_sample a_5036 = ((((int)1) + (alpha_10626 * A_5038)) * b_5033);
			t_sample b_5040 = ((((int)-2) * cs_5037) * b_5033);
			t_sample a_5034 = ((((int)1) - (alpha_10626 * A_5038)) * b_5033);
			t_sample b_5035 = ((((int)1) - (alpha_10626 * one_over_A)) * b_5033);
			t_sample expr_4939 = a_5036;
			t_sample expr_4940 = b_5040;
			t_sample expr_4941 = a_5034;
			t_sample expr_4942 = b_5040;
			t_sample expr_4943 = b_5035;
			t_sample mul_4933 = (gen_4915 * expr_4939);
			t_sample mul_4930 = (m_history_21 * expr_4940);
			t_sample mul_4928 = (m_history_22 * expr_4941);
			t_sample mul_4924 = (m_history_23 * expr_4943);
			t_sample mul_4926 = (m_history_20 * expr_4942);
			t_sample sub_4932 = (((mul_4928 + mul_4930) + mul_4933) - (mul_4926 + mul_4924));
			t_sample gen_4938 = sub_4932;
			t_sample history_4925_next_4934 = fixdenorm(m_history_20);
			t_sample history_4929_next_4935 = fixdenorm(m_history_21);
			t_sample history_4931_next_4936 = fixdenorm(gen_4915);
			t_sample history_4927_next_4937 = fixdenorm(sub_4932);
			t_sample gen_4944 = gen_4938;
			t_sample min_4865 = ((gen_4658 < ((int)0)) ? ((int)0) : gen_4658);
			t_sample min_4864 = ((dbtoa_4855 < ((int)0)) ? ((int)0) : dbtoa_4855);
			t_sample omega_5045 = safediv((min_4865 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_5048 = sin(omega_5045);
			t_sample cs_5051 = cos(omega_5045);
			t_sample A_5052 = sqrt(min_4864);
			t_sample beta_5044 = sqrt(((((A_5052 * A_5052) + ((int)1)) * ((t_sample)1.4144271570014)) - ((A_5052 - ((int)1)) * (A_5052 - ((int)1)))));
			t_sample b_5049 = safediv(((int)1), (((A_5052 + ((int)1)) - ((A_5052 - ((int)1)) * cs_5051)) + (beta_5044 * sn_5048)));
			t_sample a_5050 = ((A_5052 * (((A_5052 + ((int)1)) + ((A_5052 - ((int)1)) * cs_5051)) + (beta_5044 * sn_5048))) * b_5049);
			t_sample a_5047 = (((((int)-2) * A_5052) * ((A_5052 - ((int)1)) + ((A_5052 + ((int)1)) * cs_5051))) * b_5049);
			t_sample a_5042 = ((A_5052 * (((A_5052 + ((int)1)) + ((A_5052 - ((int)1)) * cs_5051)) - (beta_5044 * sn_5048))) * b_5049);
			t_sample b_5046 = ((((int)2) * ((A_5052 - ((int)1)) - ((A_5052 + ((int)1)) * cs_5051))) * b_5049);
			t_sample b_5043 = ((((A_5052 + ((int)1)) - ((A_5052 - ((int)1)) * cs_5051)) - (beta_5044 * sn_5048)) * b_5049);
			t_sample expr_4881 = a_5050;
			t_sample expr_4882 = a_5047;
			t_sample expr_4883 = a_5042;
			t_sample expr_4884 = b_5046;
			t_sample expr_4885 = b_5043;
			t_sample mul_4875 = (gen_4944 * expr_4881);
			t_sample mul_4872 = (m_history_17 * expr_4882);
			t_sample mul_4870 = (m_history_18 * expr_4883);
			t_sample mul_4866 = (m_history_19 * expr_4885);
			t_sample mul_4868 = (m_history_16 * expr_4884);
			t_sample sub_4874 = (((mul_4870 + mul_4872) + mul_4875) - (mul_4868 + mul_4866));
			t_sample gen_4880 = sub_4874;
			t_sample history_4867_next_4876 = fixdenorm(m_history_16);
			t_sample history_4871_next_4877 = fixdenorm(m_history_17);
			t_sample history_4873_next_4878 = fixdenorm(gen_4944);
			t_sample history_4869_next_4879 = fixdenorm(sub_4874);
			t_sample gen_4886 = gen_4880;
			t_sample gen_5087 = gen_4886;
			t_sample min_4982 = ((gen_4670 < ((int)0)) ? ((int)0) : gen_4670);
			t_sample min_4981 = ((dbtoa_4857 < ((int)0)) ? ((int)0) : dbtoa_4857);
			t_sample omega_5056 = safediv((min_4982 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_5059 = sin(omega_5056);
			t_sample cs_5062 = cos(omega_5056);
			t_sample A_5063 = sqrt(min_4981);
			t_sample beta_5055 = sqrt(((((A_5063 * A_5063) + ((int)1)) * ((t_sample)1.4144271570014)) - ((A_5063 - ((int)1)) * (A_5063 - ((int)1)))));
			t_sample b_5060 = safediv(((int)1), (((A_5063 + ((int)1)) + ((A_5063 - ((int)1)) * cs_5062)) + (beta_5055 * sn_5059)));
			t_sample a_5061 = ((A_5063 * (((A_5063 + ((int)1)) - ((A_5063 - ((int)1)) * cs_5062)) + (beta_5055 * sn_5059))) * b_5060);
			t_sample a_5058 = (((((int)2) * A_5063) * ((A_5063 - ((int)1)) - ((A_5063 + ((int)1)) * cs_5062))) * b_5060);
			t_sample a_5053 = ((A_5063 * (((A_5063 + ((int)1)) - ((A_5063 - ((int)1)) * cs_5062)) - (beta_5055 * sn_5059))) * b_5060);
			t_sample b_5057 = ((((int)-2) * ((A_5063 - ((int)1)) + ((A_5063 + ((int)1)) * cs_5062))) * b_5060);
			t_sample b_5054 = ((((A_5063 + ((int)1)) + ((A_5063 - ((int)1)) * cs_5062)) - (beta_5055 * sn_5059)) * b_5060);
			t_sample expr_4998 = a_5061;
			t_sample expr_4999 = a_5058;
			t_sample expr_5000 = a_5053;
			t_sample expr_5001 = b_5057;
			t_sample expr_5002 = b_5054;
			t_sample mul_4992 = (filterL_4672 * expr_4998);
			t_sample mul_4989 = (m_history_13 * expr_4999);
			t_sample mul_4987 = (m_history_14 * expr_5000);
			t_sample mul_4983 = (m_history_15 * expr_5002);
			t_sample mul_4985 = (m_history_12 * expr_5001);
			t_sample sub_4991 = (((mul_4987 + mul_4989) + mul_4992) - (mul_4985 + mul_4983));
			t_sample gen_4997 = sub_4991;
			t_sample history_4984_next_4993 = fixdenorm(m_history_12);
			t_sample history_4988_next_4994 = fixdenorm(m_history_13);
			t_sample history_4990_next_4995 = fixdenorm(filterL_4672);
			t_sample history_4986_next_4996 = fixdenorm(sub_4991);
			t_sample gen_5003 = gen_4997;
			t_sample min_5011 = ((gen_4664 < ((int)0)) ? ((int)0) : gen_4664);
			t_sample min_5010 = ((dbtoa_4856 < ((int)0)) ? ((int)0) : dbtoa_4856);
			t_sample omega_5072 = safediv((min_5011 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_5070 = sin(omega_5072);
			t_sample cs_5066 = cos(omega_5072);
			t_sample alpha_5073 = ((sn_5070 * ((t_sample)0.5)) * ((t_sample)1.4144271570014));
			t_sample A_5068 = sqrt(min_5010);
			t_sample one_over_A_5067 = safediv(((int)1), A_5068);
			t_sample b_5074 = safediv(((int)1), (((int)1) + (alpha_5073 * one_over_A_5067)));
			t_sample a_5071 = ((((int)1) + (alpha_5073 * A_5068)) * b_5074);
			t_sample b_5069 = ((((int)-2) * cs_5066) * b_5074);
			t_sample a_5064 = ((((int)1) - (alpha_5073 * A_5068)) * b_5074);
			t_sample b_5065 = ((((int)1) - (alpha_5073 * one_over_A_5067)) * b_5074);
			t_sample expr_5027 = a_5071;
			t_sample expr_5028 = b_5069;
			t_sample expr_5029 = a_5064;
			t_sample expr_5030 = b_5069;
			t_sample expr_5031 = b_5065;
			t_sample mul_5021 = (gen_5003 * expr_5027);
			t_sample mul_5018 = (m_history_9 * expr_5028);
			t_sample mul_5016 = (m_history_10 * expr_5029);
			t_sample mul_5012 = (m_history_11 * expr_5031);
			t_sample mul_5014 = (m_history_8 * expr_5030);
			t_sample sub_5020 = (((mul_5016 + mul_5018) + mul_5021) - (mul_5014 + mul_5012));
			t_sample gen_5026 = sub_5020;
			t_sample history_5013_next_5022 = fixdenorm(m_history_8);
			t_sample history_5017_next_5023 = fixdenorm(m_history_9);
			t_sample history_5019_next_5024 = fixdenorm(gen_5003);
			t_sample history_5015_next_5025 = fixdenorm(sub_5020);
			t_sample gen_5032 = gen_5026;
			t_sample min_4953 = ((gen_4658 < ((int)0)) ? ((int)0) : gen_4658);
			t_sample min_4952 = ((dbtoa_4855 < ((int)0)) ? ((int)0) : dbtoa_4855);
			t_sample omega_5084 = safediv((min_4953 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_5081 = sin(omega_5084);
			t_sample cs_5077 = cos(omega_5084);
			t_sample A_5078 = sqrt(min_4952);
			t_sample beta_5083 = sqrt(((((A_5078 * A_5078) + ((int)1)) * ((t_sample)1.4144271570014)) - ((A_5078 - ((int)1)) * (A_5078 - ((int)1)))));
			t_sample b_5085 = safediv(((int)1), (((A_5078 + ((int)1)) - ((A_5078 - ((int)1)) * cs_5077)) + (beta_5083 * sn_5081)));
			t_sample a_5082 = ((A_5078 * (((A_5078 + ((int)1)) + ((A_5078 - ((int)1)) * cs_5077)) + (beta_5083 * sn_5081))) * b_5085);
			t_sample a_5080 = (((((int)-2) * A_5078) * ((A_5078 - ((int)1)) + ((A_5078 + ((int)1)) * cs_5077))) * b_5085);
			t_sample a_5075 = ((A_5078 * (((A_5078 + ((int)1)) + ((A_5078 - ((int)1)) * cs_5077)) - (beta_5083 * sn_5081))) * b_5085);
			t_sample b_5079 = ((((int)2) * ((A_5078 - ((int)1)) - ((A_5078 + ((int)1)) * cs_5077))) * b_5085);
			t_sample b_5076 = ((((A_5078 + ((int)1)) - ((A_5078 - ((int)1)) * cs_5077)) - (beta_5083 * sn_5081)) * b_5085);
			t_sample expr_4969 = a_5082;
			t_sample expr_4970 = a_5080;
			t_sample expr_4971 = a_5075;
			t_sample expr_4972 = b_5079;
			t_sample expr_4973 = b_5076;
			t_sample mul_4963 = (gen_5032 * expr_4969);
			t_sample mul_4960 = (m_history_5 * expr_4970);
			t_sample mul_4958 = (m_history_7 * expr_4971);
			t_sample mul_4954 = (m_history_6 * expr_4973);
			t_sample mul_4956 = (m_history_4 * expr_4972);
			t_sample sub_4962 = (((mul_4958 + mul_4960) + mul_4963) - (mul_4956 + mul_4954));
			t_sample gen_4968 = sub_4962;
			t_sample history_4959_next_4964 = fixdenorm(m_history_5);
			t_sample history_4955_next_4965 = fixdenorm(m_history_4);
			t_sample history_4961_next_4966 = fixdenorm(gen_5032);
			t_sample history_4957_next_4967 = fixdenorm(sub_4962);
			t_sample gen_4974 = gen_4968;
			t_sample gen_5086 = gen_4974;
			t_sample fromFilterL_4674 = gen_5086;
			t_sample mix_10647 = (mul_5139 + (onOffEQ_4644 * (fromFilterL_4674 - mul_5139)));
			t_sample mix_4652 = mix_10647;
			t_sample fromFilterR_4673 = gen_5087;
			t_sample mix_10648 = (mul_5138 + (onOffEQ_4644 * (fromFilterR_4673 - mul_5138)));
			t_sample mix_4651 = mix_10648;
			t_sample mul_7446 = ((mix_4651 + mix_4652) * ((t_sample)0.5));
			t_sample tap_7457 = m_delay_3.read_step(int_7448);
			t_sample abs_7450 = fabs(mul_7446);
			t_sample sub_7455 = (abs_7450 - tap_7457);
			t_sample plusequals_7458 = __m_pluseq_155.post(sub_7455, ((int)0), 0);
			t_sample div_7454 = safediv(plusequals_7458, int_7448);
			t_sample atodb_7452 = atodb(div_7454);
			t_sample max_7451 = ((atodb_7452 < maxb_156) ? maxb_156 : atodb_7452);
			t_sample gen_7459 = max_7451;
			__m_slide_157 = fixdenorm((__m_slide_157 + (((gen_7459 > __m_slide_157) ? iup_158 : idown_159) * (gen_7459 - __m_slide_157))));
			t_sample slide_7445 = __m_slide_157;
			t_sample gen_9389 = slide_7445;
			t_sample mul_7437 = (m_history_2 * ((t_sample)0.9));
			t_sample mul_7436 = (slide_7445 * ((t_sample)0.1));
			t_sample add_7439 = (mul_7436 + mul_7437);
			t_sample gen_7441 = add_7439;
			t_sample history_7438_next_7440 = fixdenorm(add_7439);
			int gt_7468 = (gen_7441 > gen_8593);
			t_sample sub_7467 = (gen_8593 - slide_7445);
			t_sample mul_7464 = (sub_7467 * rsub_7465);
			t_sample dbtoa_7462 = dbtoa(mul_7464);
			t_sample orange_10651 = (dbtoa_7462 - ((int)1));
			int sub_10652 = (gt_7468 - ((int)0));
			t_sample scale_10649 = ((safepow((sub_10652 * ((t_sample)1)), ((int)1)) * orange_10651) + ((int)1));
			t_sample mul_7469 = (mix_4652 * scale_10649);
			t_sample mul_7412 = (mul_7469 * gen_6409);
			t_sample mix_10653 = (mix_4652 + (gen_6403 * (mul_7412 - mix_4652)));
			int gt_7430 = (gen_9389 > gen_8593);
			t_sample mul_7416 = (m_history_1 * ((t_sample)0.9));
			t_sample mul_7415 = (gt_7430 * ((t_sample)0.1));
			t_sample add_7418 = (mul_7415 + mul_7416);
			t_sample gen_7420 = add_7418;
			t_sample history_7417_next_7419 = fixdenorm(add_7418);
			t_sample sub_7429 = (gen_8593 - gen_9389);
			t_sample mul_7426 = (sub_7429 * rsub_7427);
			t_sample dbtoa_7424 = dbtoa(mul_7426);
			t_sample orange_10656 = (dbtoa_7424 - ((int)1));
			t_sample sub_10657 = (gen_7420 - ((int)0));
			t_sample scale_10654 = ((safepow((sub_10657 * ((t_sample)1)), ((int)1)) * orange_10656) + ((int)1));
			t_sample mul_7431 = (mix_4651 * scale_10654);
			t_sample mul_7411 = (mul_7431 * gen_6409);
			t_sample mix_10658 = (mix_4651 + (gen_6403 * (mul_7411 - mix_4651)));
			t_sample mix_10659 = (mix_10641 + (gen_4810 * (mix_10658 - mix_10641)));
			t_sample mul_4823 = (mix_10659 * gen_4822);
			t_sample out2 = mul_4823;
			t_sample mix_10660 = (mix_10639 + (gen_4810 * (mix_10653 - mix_10639)));
			t_sample mul_4824 = (mix_10660 * gen_4822);
			t_sample out1 = mul_4824;
			m_history_130 = history_4819_next_4821;
			m_history_129 = history_8590_next_8592;
			m_history_128 = history_6400_next_6402;
			m_history_127 = history_6406_next_6408;
			m_history_126 = history_5165_next_5167;
			m_history_125 = history_4807_next_4809;
			m_history_124 = history_4813_next_4815;
			m_history_123 = history_4647_next_4649;
			m_history_122 = history_5171_next_5173;
			m_history_121 = history_4667_next_4669;
			m_history_120 = history_4661_next_4663;
			m_history_119 = history_4655_next_4657;
			m_history_118 = history_4839_next_4841;
			m_history_117 = history_4833_next_4835;
			m_history_116 = history_4827_next_4829;
			m_history_115 = history_5159_next_5161;
			m_history_114 = history_5098_next_5100;
			m_history_113 = history_4677_next_4679;
			m_history_112 = history_4851_next_4853;
			m_history_111 = history_4845_next_4847;
			m_history_110 = history_5126_next_5128;
			m_history_109 = history_5092_next_5094;
			m_history_108 = history_5120_next_5122;
			m_history_107 = history_4604_next_4613;
			m_history_98 = history_4573_next_4579;
			m_history_97 = history_4563_next_4580;
			m_history_96 = history_4569_next_4581;
			m_history_95 = history_4565_next_4582;
			m_history_94 = history_4575_next_4583;
			m_history_93 = history_4561_next_4584;
			m_history_92 = history_4571_next_4585;
			m_history_99 = history_4559_next_4578;
			m_history_106 = history_4594_next_4614;
			m_history_105 = history_4608_next_4615;
			m_history_104 = history_4598_next_4616;
			m_history_103 = history_4610_next_4617;
			m_history_102 = history_4600_next_4618;
			m_history_101 = history_4596_next_4619;
			m_history_100 = history_4606_next_4620;
			m_history_91 = history_5381_next_5383;
			m_history_68 = history_5524_next_5530;
			m_delay_69.write(add_5527);
			m_history_70 = history_5512_next_5518;
			m_delay_71.write(add_5515);
			m_history_72 = history_5500_next_5506;
			m_delay_73.write(add_5503);
			m_history_74 = history_5488_next_5494;
			m_delay_75.write(add_5491);
			m_history_76 = history_5476_next_5482;
			m_delay_77.write(add_5479);
			m_history_78 = history_5464_next_5470;
			m_delay_79.write(add_5467);
			m_history_80 = history_5452_next_5458;
			m_delay_81.write(add_5455);
			m_history_82 = history_5440_next_5446;
			m_delay_83.write(add_5443);
			m_history_90 = history_5375_next_5377;
			m_history_89 = history_5363_next_5365;
			m_history_88 = history_5393_next_5395;
			m_history_87 = history_5369_next_5371;
			m_history_86 = history_5399_next_5401;
			m_history_85 = history_5387_next_5389;
			m_history_84 = history_5405_next_5407;
			m_delay_67.write(gen_5533);
			m_delay_60.write(add_4753);
			m_delay_61.write(gen_4772);
			m_delay_62.write(add_4767);
			m_delay_63.write(gen_4786);
			m_delay_64.write(add_4781);
			m_delay_65.write(gen_4800);
			m_delay_66.write(add_4795);
			m_history_59 = history_5232_next_5234;
			m_history_36 = history_5351_next_5357;
			m_delay_37.write(add_5354);
			m_history_38 = history_5339_next_5345;
			m_delay_39.write(add_5342);
			m_history_40 = history_5327_next_5333;
			m_delay_41.write(add_5330);
			m_history_42 = history_5315_next_5321;
			m_delay_43.write(add_5318);
			m_history_44 = history_5303_next_5309;
			m_delay_45.write(add_5306);
			m_history_46 = history_5291_next_5297;
			m_delay_47.write(add_5294);
			m_history_48 = history_5279_next_5285;
			m_delay_49.write(add_5282);
			m_history_50 = history_5267_next_5273;
			m_delay_51.write(add_5270);
			m_history_58 = history_5220_next_5222;
			m_history_57 = history_5214_next_5216;
			m_history_56 = history_5226_next_5228;
			m_history_55 = history_5208_next_5210;
			m_history_54 = history_5196_next_5198;
			m_history_53 = history_5190_next_5192;
			m_history_52 = history_5202_next_5204;
			m_delay_35.write(gen_5360);
			m_delay_28.write(add_4693);
			m_delay_29.write(gen_4712);
			m_delay_30.write(add_4707);
			m_delay_31.write(gen_4726);
			m_delay_32.write(add_4721);
			m_delay_33.write(gen_4740);
			m_delay_34.write(add_4735);
			m_history_27 = history_4900_next_4905;
			m_history_4 = history_4957_next_4967;
			m_history_5 = history_4961_next_4966;
			m_history_6 = history_4955_next_4965;
			m_history_7 = history_4959_next_4964;
			m_history_8 = history_5015_next_5025;
			m_history_9 = history_5019_next_5024;
			m_history_10 = history_5017_next_5023;
			m_history_11 = history_5013_next_5022;
			m_history_12 = history_4986_next_4996;
			m_history_13 = history_4990_next_4995;
			m_history_14 = history_4988_next_4994;
			m_history_15 = history_4984_next_4993;
			m_history_16 = history_4869_next_4879;
			m_history_17 = history_4873_next_4878;
			m_history_18 = history_4871_next_4877;
			m_history_19 = history_4867_next_4876;
			m_history_20 = history_4927_next_4937;
			m_history_21 = history_4931_next_4936;
			m_history_22 = history_4929_next_4935;
			m_history_23 = history_4925_next_4934;
			m_history_24 = history_4898_next_4908;
			m_history_25 = history_4902_next_4907;
			m_history_26 = history_4896_next_4906;
			m_delay_3.write(abs_7450);
			m_history_1 = history_7417_next_7419;
			m_history_2 = history_7438_next_7440;
			m_delay_3.step();
			m_delay_28.step();
			m_delay_29.step();
			m_delay_30.step();
			m_delay_31.step();
			m_delay_32.step();
			m_delay_33.step();
			m_delay_34.step();
			m_delay_35.step();
			m_delay_37.step();
			m_delay_39.step();
			m_delay_41.step();
			m_delay_43.step();
			m_delay_45.step();
			m_delay_47.step();
			m_delay_49.step();
			m_delay_51.step();
			m_delay_60.step();
			m_delay_61.step();
			m_delay_62.step();
			m_delay_63.step();
			m_delay_64.step();
			m_delay_65.step();
			m_delay_66.step();
			m_delay_67.step();
			m_delay_69.step();
			m_delay_71.step();
			m_delay_73.step();
			m_delay_75.step();
			m_delay_77.step();
			m_delay_79.step();
			m_delay_81.step();
			m_delay_83.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_a_input(t_param _value) {
		m_a_input_131 = (_value < -72 ? -72 : (_value > 0 ? 0 : _value));
	};
	inline void set_n_lowFreq(t_param _value) {
		m_n_lowFreq_132 = (_value < 20 ? 20 : (_value > 800 ? 800 : _value));
	};
	inline void set_l_hpf(t_param _value) {
		m_l_hpf_133 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_c_reflect(t_param _value) {
		m_c_reflect_134 = (_value < 0.001 ? 0.001 : (_value > 0.985 ? 0.985 : _value));
	};
	inline void set_e_size(t_param _value) {
		m_e_size_135 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_g_freeze(t_param _value) {
		m_g_freeze_136 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_m_output(t_param _value) {
		m_m_output_137 = (_value < -72 ? -72 : (_value > 0 ? 0 : _value));
	};
	inline void set_q_onoffEQ(t_param _value) {
		m_q_onoffEQ_138 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_j_hiGain(t_param _value) {
		m_j_hiGain_139 = (_value < -18 ? -18 : (_value > 18 ? 18 : _value));
	};
	inline void set_v_COMPREL(t_param _value) {
		m_v_COMPREL_140 = (_value < 250 ? 250 : (_value > 1500 ? 1500 : _value));
	};
	inline void set_i_peakGain(t_param _value) {
		m_i_peakGain_141 = (_value < -18 ? -18 : (_value > 18 ? 18 : _value));
	};
	inline void set_t_COMPRATIO(t_param _value) {
		m_t_COMPRATIO_142 = (_value < 1 ? 1 : (_value > 10 ? 10 : _value));
	};
	inline void set_h_lowGain(t_param _value) {
		m_h_lowGain_143 = (_value < -18 ? -18 : (_value > 18 ? 18 : _value));
	};
	inline void set_o_peakFreq(t_param _value) {
		m_o_peakFreq_144 = (_value < 100 ? 100 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_s_COMPTHD(t_param _value) {
		m_s_COMPTHD_145 = (_value < -50 ? -50 : (_value > 0 ? 0 : _value));
	};
	inline void set_w_COMPMAKEUP(t_param _value) {
		m_w_COMPMAKEUP_146 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void set_u_COMPATK(t_param _value) {
		m_u_COMPATK_147 = (_value < 100 ? 100 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_f_st(t_param _value) {
		m_f_st_148 = (_value < 0 ? 0 : (_value > 0.707 ? 0.707 : _value));
	};
	inline void set_r_COMPON(t_param _value) {
		m_r_COMPON_149 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_b_drywet(t_param _value) {
		m_b_drywet_150 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_d_damp(t_param _value) {
		m_d_damp_151 = (_value < 0.001 ? 0.001 : (_value > 1 ? 1 : _value));
	};
	inline void set_k_lpf(t_param _value) {
		m_k_lpf_152 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_p_hiFreq(t_param _value) {
		m_p_hiFreq_153 = (_value < 800 ? 800 : (_value > 15000 ? 15000 : _value));
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
		case 17: self->set_r_COMPON(value); break;
		case 18: self->set_s_COMPTHD(value); break;
		case 19: self->set_t_COMPRATIO(value); break;
		case 20: self->set_u_COMPATK(value); break;
		case 21: self->set_v_COMPREL(value); break;
		case 22: self->set_w_COMPMAKEUP(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_a_input_131; break;
		case 1: *value = self->m_b_drywet_150; break;
		case 2: *value = self->m_c_reflect_134; break;
		case 3: *value = self->m_d_damp_151; break;
		case 4: *value = self->m_e_size_135; break;
		case 5: *value = self->m_f_st_148; break;
		case 6: *value = self->m_g_freeze_136; break;
		case 7: *value = self->m_h_lowGain_143; break;
		case 8: *value = self->m_i_peakGain_141; break;
		case 9: *value = self->m_j_hiGain_139; break;
		case 10: *value = self->m_k_lpf_152; break;
		case 11: *value = self->m_l_hpf_133; break;
		case 12: *value = self->m_m_output_137; break;
		case 13: *value = self->m_n_lowFreq_132; break;
		case 14: *value = self->m_o_peakFreq_144; break;
		case 15: *value = self->m_p_hiFreq_153; break;
		case 16: *value = self->m_q_onoffEQ_138; break;
		case 17: *value = self->m_r_COMPON_149; break;
		case 18: *value = self->m_s_COMPTHD_145; break;
		case 19: *value = self->m_t_COMPRATIO_142; break;
		case 20: *value = self->m_u_COMPATK_147; break;
		case 21: *value = self->m_v_COMPREL_140; break;
		case 22: *value = self->m_w_COMPMAKEUP_146; break;
		
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
	// initialize parameter 0 ("m_a_input_131")
	pi = self->__commonstate.params + 0;
	pi->name = "a_input";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_input_131;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -72;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_drywet_150")
	pi = self->__commonstate.params + 1;
	pi->name = "b_drywet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_drywet_150;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_reflect_134")
	pi = self->__commonstate.params + 2;
	pi->name = "c_reflect";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_reflect_134;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 0.985;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_damp_151")
	pi = self->__commonstate.params + 3;
	pi->name = "d_damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_damp_151;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_size_135")
	pi = self->__commonstate.params + 4;
	pi->name = "e_size";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_size_135;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_st_148")
	pi = self->__commonstate.params + 5;
	pi->name = "f_st";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_st_148;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.707;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_freeze_136")
	pi = self->__commonstate.params + 6;
	pi->name = "g_freeze";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_freeze_136;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_lowGain_143")
	pi = self->__commonstate.params + 7;
	pi->name = "h_lowGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_lowGain_143;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -18;
	pi->outputmax = 18;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_peakGain_141")
	pi = self->__commonstate.params + 8;
	pi->name = "i_peakGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_peakGain_141;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -18;
	pi->outputmax = 18;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_hiGain_139")
	pi = self->__commonstate.params + 9;
	pi->name = "j_hiGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_hiGain_139;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -18;
	pi->outputmax = 18;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_lpf_152")
	pi = self->__commonstate.params + 10;
	pi->name = "k_lpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_lpf_152;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_hpf_133")
	pi = self->__commonstate.params + 11;
	pi->name = "l_hpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_hpf_133;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_output_137")
	pi = self->__commonstate.params + 12;
	pi->name = "m_output";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_output_137;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -72;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_lowFreq_132")
	pi = self->__commonstate.params + 13;
	pi->name = "n_lowFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_lowFreq_132;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 800;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_peakFreq_144")
	pi = self->__commonstate.params + 14;
	pi->name = "o_peakFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_peakFreq_144;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 2500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_hiFreq_153")
	pi = self->__commonstate.params + 15;
	pi->name = "p_hiFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_hiFreq_153;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 800;
	pi->outputmax = 15000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_onoffEQ_138")
	pi = self->__commonstate.params + 16;
	pi->name = "q_onoffEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_onoffEQ_138;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 17 ("m_r_COMPON_149")
	pi = self->__commonstate.params + 17;
	pi->name = "r_COMPON";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_COMPON_149;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 18 ("m_s_COMPTHD_145")
	pi = self->__commonstate.params + 18;
	pi->name = "s_COMPTHD";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_COMPTHD_145;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -50;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_COMPRATIO_142")
	pi = self->__commonstate.params + 19;
	pi->name = "t_COMPRATIO";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_COMPRATIO_142;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 20 ("m_u_COMPATK_147")
	pi = self->__commonstate.params + 20;
	pi->name = "u_COMPATK";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_u_COMPATK_147;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 21 ("m_v_COMPREL_140")
	pi = self->__commonstate.params + 21;
	pi->name = "v_COMPREL";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_COMPREL_140;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 250;
	pi->outputmax = 1500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_COMPMAKEUP_146")
	pi = self->__commonstate.params + 22;
	pi->name = "w_COMPMAKEUP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_COMPMAKEUP_146;
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
