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
	Change __m_change_143;
	Change __m_change_126;
	Change __m_change_142;
	Change __m_change_144;
	Change __m_change_163;
	Change __m_change_164;
	Change __m_change_125;
	Delay m_delay_48;
	Delay m_delay_24;
	Delay m_delay_42;
	Delay m_delay_44;
	Delay m_delay_22;
	Delay m_delay_46;
	Delay m_delay_40;
	Delay m_delay_33;
	Delay m_delay_34;
	Delay m_delay_20;
	Delay m_delay_37;
	Delay m_delay_39;
	Delay m_delay_38;
	Delay m_delay_50;
	Delay m_delay_52;
	Delay m_delay_35;
	Delay m_delay_4;
	Delay m_delay_5;
	Delay m_delay_6;
	Delay m_delay_3;
	Delay m_delay_1;
	Delay m_delay_2;
	Delay m_delay_18;
	Delay m_delay_7;
	Delay m_delay_10;
	Delay m_delay_54;
	Delay m_delay_16;
	Delay m_delay_8;
	Delay m_delay_14;
	Delay m_delay_12;
	Delay m_delay_56;
	Delay m_delay_36;
	int __exception;
	int vectorsize;
	t_sample m_k_lpf_113;
	t_sample m_z_147;
	t_sample m_g_freeze_114;
	t_sample m_p_hiFreq_112;
	t_sample m_f_st_111;
	t_sample m_h_lowGain_115;
	t_sample m_b_drywet_116;
	t_sample m_history_117;
	t_sample m_w_121;
	t_sample m_n_lowFreq_110;
	t_sample m_a_120;
	t_sample m_a_119;
	t_sample m_b_122;
	t_sample m_a_input_109;
	t_sample m_i_peakGain_107;
	t_sample m_history_99;
	t_sample m_d_damp_100;
	t_sample m_history_98;
	t_sample m_history_96;
	t_sample m_history_97;
	t_sample m_o_peakFreq_108;
	t_sample m_q_onoffEQ_101;
	t_sample m_j_hiGain_103;
	t_sample m_l_hpf_106;
	t_sample m_c_reflect_102;
	t_sample m_m_output_105;
	t_sample m_e_size_104;
	t_sample m_z_146;
	t_sample m_f_123;
	t_sample m_b_162;
	t_sample m_history_95;
	t_sample m_w_141;
	t_sample m_b_140;
	t_sample m_a_157;
	t_sample m_d_139;
	t_sample m_z_154;
	t_sample m_z_152;
	t_sample m_z_148;
	t_sample m_z_153;
	t_sample m_z_149;
	t_sample m_z_151;
	t_sample m_b_124;
	t_sample m_a_158;
	t_sample m_w_159;
	t_sample m_a_132;
	t_sample m_a_133;
	t_sample m_z_129;
	t_sample m_z_127;
	t_sample m_d_138;
	t_sample m_a_134;
	t_sample m_f_161;
	t_sample m_d_137;
	t_sample m_w_135;
	t_sample m_b_160;
	t_sample m_wq_136;
	t_sample m_history_94;
	t_sample m_history_78;
	t_sample m_history_92;
	t_sample m_history_45;
	t_sample m_history_47;
	t_sample m_history_43;
	t_sample m_history_32;
	t_sample m_history_41;
	t_sample m_history_31;
	t_sample m_history_49;
	t_sample m_history_53;
	t_sample m_history_59;
	t_sample m_history_51;
	t_sample m_history_58;
	t_sample m_history_55;
	t_sample m_history_57;
	t_sample m_history_60;
	t_sample m_history_30;
	t_sample m_history_28;
	t_sample m_history_13;
	t_sample m_history_15;
	t_sample m_history_11;
	t_sample samplerate;
	t_sample m_history_9;
	t_sample m_history_29;
	t_sample m_history_17;
	t_sample m_history_21;
	t_sample m_history_27;
	t_sample m_history_19;
	t_sample m_history_26;
	t_sample m_history_23;
	t_sample m_history_25;
	t_sample m_history_93;
	t_sample m_history_61;
	t_sample m_history_63;
	t_sample m_history_83;
	t_sample m_history_84;
	t_sample m_history_82;
	t_sample m_history_80;
	t_sample m_history_81;
	t_sample m_history_79;
	t_sample m_history_85;
	t_sample m_history_87;
	t_sample m_history_91;
	t_sample m_history_86;
	t_sample m_history_90;
	t_sample m_history_88;
	t_sample m_history_89;
	t_sample m_history_62;
	t_sample m_z_166;
	t_sample m_history_76;
	t_sample m_history_67;
	t_sample m_history_68;
	t_sample m_history_66;
	t_sample m_history_64;
	t_sample m_history_65;
	t_sample m_history_77;
	t_sample m_history_69;
	t_sample m_history_71;
	t_sample m_history_75;
	t_sample m_history_70;
	t_sample m_history_74;
	t_sample m_history_72;
	t_sample m_history_73;
	t_sample m_z_168;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_delay_1.reset("m_delay_1", samplerate);
		m_delay_2.reset("m_delay_2", samplerate);
		m_delay_3.reset("m_delay_3", samplerate);
		m_delay_4.reset("m_delay_4", samplerate);
		m_delay_5.reset("m_delay_5", samplerate);
		m_delay_6.reset("m_delay_6", samplerate);
		m_delay_7.reset("m_delay_7", samplerate);
		m_delay_8.reset("m_delay_8", samplerate);
		m_history_9 = ((int)0);
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
		m_history_26 = ((int)0);
		m_history_27 = ((int)0);
		m_history_28 = ((int)0);
		m_history_29 = ((int)0);
		m_history_30 = ((int)0);
		m_history_31 = ((int)0);
		m_history_32 = ((int)0);
		m_delay_33.reset("m_delay_33", samplerate);
		m_delay_34.reset("m_delay_34", samplerate);
		m_delay_35.reset("m_delay_35", samplerate);
		m_delay_36.reset("m_delay_36", samplerate);
		m_delay_37.reset("m_delay_37", samplerate);
		m_delay_38.reset("m_delay_38", samplerate);
		m_delay_39.reset("m_delay_39", samplerate);
		m_delay_40.reset("m_delay_40", samplerate);
		m_history_41 = ((int)0);
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
		m_history_58 = ((int)0);
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
		m_d_damp_100 = 0.8;
		m_q_onoffEQ_101 = 0;
		m_c_reflect_102 = 0.86;
		m_j_hiGain_103 = 0;
		m_e_size_104 = 1;
		m_m_output_105 = 1;
		m_l_hpf_106 = 20;
		m_i_peakGain_107 = 0;
		m_o_peakFreq_108 = 800;
		m_a_input_109 = 1;
		m_n_lowFreq_110 = 500;
		m_f_st_111 = 0.5;
		m_p_hiFreq_112 = 2000;
		m_k_lpf_113 = 20000;
		m_g_freeze_114 = 0;
		m_h_lowGain_115 = 0;
		m_b_drywet_116 = 0.33;
		m_history_117 = ((int)0);
		m_a_119 = ((int)0);
		m_a_120 = ((int)0);
		m_w_121 = ((int)0);
		m_b_122 = ((int)0);
		m_f_123 = ((int)0);
		m_b_124 = ((int)0);
		__m_change_125.reset(0);
		__m_change_126.reset(0);
		m_z_127 = ((int)0);
		m_z_129 = ((int)0);
		m_a_132 = ((int)0);
		m_a_133 = ((int)0);
		m_a_134 = ((int)0);
		m_w_135 = ((int)0);
		m_wq_136 = ((int)0);
		m_d_137 = ((int)0);
		m_d_138 = ((int)0);
		m_d_139 = ((int)0);
		m_b_140 = ((int)0);
		m_w_141 = ((int)0);
		__m_change_142.reset(0);
		__m_change_143.reset(0);
		__m_change_144.reset(0);
		m_z_146 = ((int)0);
		m_z_147 = ((int)0);
		m_z_148 = ((int)0);
		m_z_149 = ((int)0);
		m_z_151 = ((int)0);
		m_z_152 = ((int)0);
		m_z_153 = ((int)0);
		m_z_154 = ((int)0);
		m_a_157 = ((int)0);
		m_a_158 = ((int)0);
		m_w_159 = ((int)0);
		m_b_160 = ((int)0);
		m_f_161 = ((int)0);
		m_b_162 = ((int)0);
		__m_change_163.reset(0);
		__m_change_164.reset(0);
		m_z_166 = ((int)0);
		m_z_168 = ((int)0);
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
		t_sample mul_358 = (m_m_output_105 * ((t_sample)0.001));
		t_sample mul_522 = (m_b_drywet_116 * ((t_sample)0.001));
		int eq_550 = (m_g_freeze_114 == ((int)1));
		int toSize_459 = eq_550;
		t_sample mul_350 = (toSize_459 * ((t_sample)0.001));
		t_sample mul_146 = (m_q_onoffEQ_101 * ((t_sample)0.001));
		t_sample mul_530 = (m_f_st_111 * ((t_sample)0.001));
		t_sample mul_172 = (m_n_lowFreq_110 * ((t_sample)0.001));
		t_sample mul_164 = (m_o_peakFreq_108 * ((t_sample)0.001));
		t_sample mul_156 = (m_p_hiFreq_112 * ((t_sample)0.001));
		t_sample mul_384 = (m_h_lowGain_115 * ((t_sample)0.001));
		t_sample mul_376 = (m_i_peakGain_107 * ((t_sample)0.001));
		t_sample mul_368 = (m_j_hiGain_103 * ((t_sample)0.001));
		t_sample mul_514 = (m_a_input_109 * ((t_sample)0.001));
		t_sample rsub_997 = (((int)1) - m_d_damp_100);
		t_sample damp_540 = rsub_997;
		t_sample damp_539 = damp_540;
		t_sample mul_184 = (m_e_size_104 * ((t_sample)0.001));
		t_sample mul_400 = (m_k_lpf_113 * ((t_sample)0.001));
		t_sample mul_392 = (m_l_hpf_106 * ((t_sample)0.001));
		int toSize_543 = toSize_459;
		t_sample rsub_545 = (((t_sample)0.999) - m_c_reflect_102);
		int choice_118 = toSize_543;
		t_sample gate_544 = ((choice_118 >= 1) ? rsub_545 : 0);
		t_sample add_546 = (m_c_reflect_102 + gate_544);
		t_sample mul_479 = (add_546 * ((t_sample)0.001));
		int rsub_549 = (((int)1) - eq_550);
		t_sample mul_471 = (rsub_549 * ((t_sample)0.001));
		t_sample rsub_871 = (((int)1) - damp_540);
		t_sample div_852 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_873 = (((int)1) - rsub_871);
		t_sample rsub_888 = (((int)1) - rsub_871);
		t_sample rsub_903 = (((int)1) - rsub_871);
		t_sample rsub_918 = (((int)1) - rsub_871);
		t_sample rsub_933 = (((int)1) - rsub_871);
		t_sample rsub_948 = (((int)1) - rsub_871);
		t_sample rsub_963 = (((int)1) - rsub_871);
		t_sample rsub_978 = (((int)1) - rsub_871);
		t_sample div_321 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_304 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_287 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_270 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_649 = (((int)1) - damp_539);
		t_sample div_630 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_651 = (((int)1) - rsub_649);
		t_sample rsub_666 = (((int)1) - rsub_649);
		t_sample rsub_681 = (((int)1) - rsub_649);
		t_sample rsub_696 = (((int)1) - rsub_649);
		t_sample rsub_711 = (((int)1) - rsub_649);
		t_sample rsub_726 = (((int)1) - rsub_649);
		t_sample rsub_741 = (((int)1) - rsub_649);
		t_sample rsub_756 = (((int)1) - rsub_649);
		t_sample div_248 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_231 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_214 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_197 = (samplerate * ((t_sample)2.2675736961451e-05));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_359 = (m_history_117 * ((t_sample)0.999));
			t_sample add_361 = (mul_358 + mul_359);
			t_sample gen_365 = add_361;
			t_sample history_360_next_364 = fixdenorm(add_361);
			t_sample mul_523 = (m_history_99 * ((t_sample)0.999));
			t_sample add_525 = (mul_522 + mul_523);
			t_sample gen_529 = add_525;
			t_sample history_524_next_528 = fixdenorm(add_525);
			t_sample dry_wet_502 = gen_529;
			t_sample mul_343 = (m_history_98 * ((t_sample)0.999));
			t_sample mul_342 = (dry_wet_502 * ((t_sample)0.001));
			t_sample add_345 = (mul_342 + mul_343);
			t_sample gen_349 = add_345;
			t_sample history_344_next_348 = fixdenorm(add_345);
			t_sample mul_351 = (m_history_97 * ((t_sample)0.999));
			t_sample add_353 = (mul_350 + mul_351);
			t_sample gen_357 = add_353;
			t_sample history_352_next_356 = fixdenorm(add_353);
			t_sample mul_147 = (m_history_96 * ((t_sample)0.999));
			t_sample add_149 = (mul_146 + mul_147);
			t_sample gen_153 = add_149;
			t_sample history_148_next_152 = fixdenorm(add_149);
			t_sample mul_531 = (m_history_95 * ((t_sample)0.999));
			t_sample add_533 = (mul_530 + mul_531);
			t_sample gen_537 = add_533;
			t_sample history_532_next_536 = fixdenorm(add_533);
			t_sample sub_1001 = (gen_537 - ((int)0));
			t_sample scale_998 = ((safepow((sub_1001 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample mul_173 = (m_history_94 * ((t_sample)0.999));
			t_sample add_175 = (mul_172 + mul_173);
			t_sample gen_179 = add_175;
			t_sample history_174_next_178 = fixdenorm(add_175);
			t_sample mul_165 = (m_history_93 * ((t_sample)0.999));
			t_sample add_167 = (mul_164 + mul_165);
			t_sample gen_171 = add_167;
			t_sample history_166_next_170 = fixdenorm(add_167);
			t_sample mul_157 = (m_history_92 * ((t_sample)0.999));
			t_sample add_159 = (mul_156 + mul_157);
			t_sample gen_163 = add_159;
			t_sample history_158_next_162 = fixdenorm(add_159);
			t_sample mul_385 = (m_history_91 * ((t_sample)0.999));
			t_sample add_387 = (mul_384 + mul_385);
			t_sample gen_391 = add_387;
			t_sample history_386_next_390 = fixdenorm(add_387);
			t_sample mul_377 = (m_history_90 * ((t_sample)0.999));
			t_sample add_379 = (mul_376 + mul_377);
			t_sample gen_383 = add_379;
			t_sample history_378_next_382 = fixdenorm(add_379);
			t_sample mul_369 = (m_history_89 * ((t_sample)0.999));
			t_sample add_371 = (mul_368 + mul_369);
			t_sample gen_375 = add_371;
			t_sample history_370_next_374 = fixdenorm(add_371);
			t_sample mul_515 = (m_history_88 * ((t_sample)0.999));
			t_sample add_517 = (mul_514 + mul_515);
			t_sample gen_521 = add_517;
			t_sample history_516_next_520 = fixdenorm(add_517);
			t_sample input_437 = gen_521;
			t_sample mul_438 = (in1 * input_437);
			t_sample left_466 = mul_438;
			t_sample left_500 = left_466;
			t_sample mix_1002 = (left_500 + (gen_357 * (((int)0) - left_500)));
			t_sample mul_436 = (in2 * input_437);
			t_sample right_460 = mul_436;
			t_sample right_499 = right_460;
			t_sample right_462 = right_460;
			int eq_469 = (right_462 == ((int)0));
			t_sample mul_448 = (m_history_87 * ((t_sample)0.999));
			t_sample mul_447 = (eq_469 * ((t_sample)0.001));
			t_sample add_450 = (mul_447 + mul_448);
			t_sample gen_454 = add_450;
			t_sample history_449_next_453 = fixdenorm(add_450);
			t_sample mix_1003 = (((int)0) + (gen_454 * (left_466 - ((int)0))));
			t_sample mix_465 = mix_1003;
			t_sample add_1005 = (mix_465 + right_499);
			t_sample mix_1004 = (add_1005 + (gen_357 * (((int)0) - add_1005)));
			t_sample sqrt_506 = sqrt(gen_537);
			t_sample rsub_538 = (((int)1) - gen_537);
			t_sample sqrt_507 = sqrt(rsub_538);
			t_sample mul_185 = (m_history_86 * ((t_sample)0.999));
			t_sample add_187 = (mul_184 + mul_185);
			t_sample gen_191 = add_187;
			t_sample history_186_next_190 = fixdenorm(add_187);
			t_sample escala_Size_341 = gen_191;
			t_sample escala_Size_339 = escala_Size_341;
			t_sample escala_Size_266 = escala_Size_341;
			t_sample escala_Size_340 = escala_Size_341;
			t_sample mul_401 = (m_history_85 * ((t_sample)0.999));
			t_sample add_403 = (mul_400 + mul_401);
			t_sample gen_407 = add_403;
			t_sample history_402_next_406 = fixdenorm(add_403);
			t_sample mul_393 = (m_history_84 * ((t_sample)0.999));
			t_sample add_395 = (mul_392 + mul_393);
			t_sample gen_399 = add_395;
			t_sample history_394_next_398 = fixdenorm(add_395);
			t_sample toMoud_470 = gen_537;
			t_sample mul_480 = (m_history_83 * ((t_sample)0.999));
			t_sample add_482 = (mul_479 + mul_480);
			t_sample gen_486 = add_482;
			t_sample history_481_next_485 = fixdenorm(add_482);
			t_sample escala_Size_194 = escala_Size_341;
			t_sample mul_192 = (((int)23) * escala_Size_194);
			t_sample left_494 = left_466;
			t_sample right_493 = right_460;
			t_sample left_461 = left_466;
			int eq_463 = (left_461 == right_460);
			t_sample mul_440 = (m_history_82 * ((t_sample)0.999));
			t_sample mul_439 = (eq_463 * ((t_sample)0.001));
			t_sample add_442 = (mul_439 + mul_440);
			t_sample gen_446 = add_442;
			t_sample history_441_next_445 = fixdenorm(add_442);
			t_sample add_1007 = (gen_446 + gen_454);
			t_sample mix_1006 = (((int)0) + (add_1007 * (toMoud_470 - ((int)0))));
			t_sample mix_468 = mix_1006;
			t_sample mix_1008 = (((int)0) + (mix_468 * ((int)0)));
			t_sample mix_490 = mix_1008;
			t_sample zeroL_541 = mix_490;
			t_sample mix_1009 = (((int)0) + (mix_468 * (mul_192 - ((int)0))));
			t_sample mix_488 = mix_1009;
			t_sample zeroR_542 = mix_488;
			t_sample mul_472 = (m_history_81 * ((t_sample)0.999));
			t_sample add_474 = (mul_471 + mul_472);
			t_sample gen_478 = add_474;
			t_sample history_473_next_477 = fixdenorm(add_474);
			t_sample freeze_547 = gen_478;
			t_sample mul_548 = (left_494 * freeze_547);
			t_sample toFILTERS_c45L_10 = mul_548;
			t_sample freeze_512 = freeze_547;
			t_sample mul_513 = ((mix_465 + right_493) * freeze_512);
			t_sample toFILTERS_c45R_9 = mul_513;
			t_sample omega = safediv((gen_399 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) + cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((-(((int)1) + cs)) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_124 = a2;
			t_sample expr_125 = a1;
			t_sample expr_126 = a2;
			t_sample expr_127 = b1;
			t_sample expr_128 = b2;
			t_sample omega_135 = safediv((gen_407 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_134 = sin(omega_135);
			t_sample cs_141 = cos(omega_135);
			t_sample alpha_142 = ((sn_134 * ((t_sample)0.5)) * ((int)1));
			t_sample b_139 = safediv(((int)1), (((int)1) + alpha_142));
			t_sample a_140 = (((((int)1) - cs_141) * ((t_sample)0.5)) * b_139);
			t_sample a_138 = ((((int)1) - cs_141) * b_139);
			t_sample b_137 = ((((int)-2) * cs_141) * b_139);
			t_sample b_136 = ((((int)1) - alpha_142) * b_139);
			t_sample expr_129 = a_140;
			t_sample expr_130 = a_138;
			t_sample expr_131 = a_140;
			t_sample expr_132 = b_137;
			t_sample expr_133 = b_136;
			t_sample mul_67 = (m_history_80 * expr_131);
			t_sample mul_77 = (m_history_78 * expr_131);
			t_sample mul_69 = (m_history_75 * expr_130);
			t_sample mul_79 = (m_history_76 * expr_130);
			t_sample mul_72 = (toFILTERS_c45R_9 * expr_129);
			t_sample mul_82 = (toFILTERS_c45L_10 * expr_129);
			t_sample mul_63 = (m_history_77 * expr_133);
			t_sample mul_73 = (m_history_79 * expr_133);
			t_sample mul_65 = (m_history_74 * expr_132);
			t_sample sub_71 = (((mul_72 + mul_69) + mul_67) - (mul_65 + mul_63));
			t_sample gen_102 = sub_71;
			t_sample mul_75 = (m_history_73 * expr_132);
			t_sample sub_81 = (((mul_77 + mul_79) + mul_82) - (mul_75 + mul_73));
			t_sample gen_101 = sub_81;
			t_sample history_68_next_93 = fixdenorm(m_history_75);
			t_sample history_74_next_94 = fixdenorm(m_history_73);
			t_sample history_78_next_95 = fixdenorm(m_history_76);
			t_sample history_64_next_96 = fixdenorm(m_history_74);
			t_sample history_80_next_97 = fixdenorm(toFILTERS_c45L_10);
			t_sample history_70_next_98 = fixdenorm(toFILTERS_c45R_9);
			t_sample history_66_next_99 = fixdenorm(sub_71);
			t_sample history_76_next_100 = fixdenorm(sub_81);
			t_sample mul_37 = (gen_101 * expr_124);
			t_sample mul_27 = (gen_102 * expr_124);
			t_sample mul_34 = (m_history_68 * expr_125);
			t_sample mul_24 = (m_history_67 * expr_125);
			t_sample mul_32 = (m_history_72 * expr_126);
			t_sample mul_22 = (m_history_71 * expr_126);
			t_sample mul_28 = (m_history_69 * expr_128);
			t_sample mul_18 = (m_history_70 * expr_128);
			t_sample mul_30 = (m_history_66 * expr_127);
			t_sample sub_36 = (((mul_32 + mul_34) + mul_37) - (mul_30 + mul_28));
			t_sample gen_56 = sub_36;
			t_sample mul_20 = (m_history_65 * expr_127);
			t_sample sub_26 = (((mul_27 + mul_24) + mul_22) - (mul_20 + mul_18));
			t_sample gen_57 = sub_26;
			t_sample history_33_next_48 = fixdenorm(m_history_68);
			t_sample history_23_next_49 = fixdenorm(m_history_67);
			t_sample history_19_next_50 = fixdenorm(m_history_65);
			t_sample history_29_next_51 = fixdenorm(m_history_66);
			t_sample history_35_next_52 = fixdenorm(gen_101);
			t_sample history_25_next_53 = fixdenorm(gen_102);
			t_sample history_31_next_54 = fixdenorm(sub_36);
			t_sample history_21_next_55 = fixdenorm(sub_26);
			t_sample mul_837 = (div_852 * escala_Size_341);
			t_sample mul_848 = (((int)1491) * mul_837);
			t_sample mul_814 = (m_history_64 * ((t_sample)0.999));
			t_sample mul_813 = (mul_848 * ((t_sample)0.001));
			t_sample add_816 = (mul_813 + mul_814);
			t_sample gen_820 = add_816;
			t_sample history_815_next_819 = fixdenorm(add_816);
			t_sample gen_865 = gen_820;
			t_sample mul_853 = (((int)1557) * mul_837);
			t_sample mul_830 = (m_history_63 * ((t_sample)0.999));
			t_sample mul_829 = (mul_853 * ((t_sample)0.001));
			t_sample add_832 = (mul_829 + mul_830);
			t_sample gen_836 = add_832;
			t_sample history_831_next_835 = fixdenorm(add_832);
			t_sample gen_863 = gen_836;
			t_sample mul_838 = (((int)1116) * mul_837);
			t_sample mul_774 = (m_history_62 * ((t_sample)0.999));
			t_sample mul_773 = (mul_838 * ((t_sample)0.001));
			t_sample add_776 = (mul_773 + mul_774);
			t_sample gen_780 = add_776;
			t_sample history_775_next_779 = fixdenorm(add_776);
			t_sample gen_870 = gen_780;
			t_sample mul_842 = (((int)1356) * mul_837);
			t_sample mul_790 = (m_history_61 * ((t_sample)0.999));
			t_sample mul_789 = (mul_842 * ((t_sample)0.001));
			t_sample add_792 = (mul_789 + mul_790);
			t_sample gen_796 = add_792;
			t_sample history_791_next_795 = fixdenorm(add_792);
			t_sample gen_868 = gen_796;
			t_sample mul_846 = (((int)1422) * mul_837);
			t_sample mul_806 = (m_history_60 * ((t_sample)0.999));
			t_sample mul_805 = (mul_846 * ((t_sample)0.001));
			t_sample add_808 = (mul_805 + mul_806);
			t_sample gen_812 = add_808;
			t_sample history_807_next_811 = fixdenorm(add_808);
			t_sample gen_866 = gen_812;
			t_sample mul_840 = (((int)1188) * mul_837);
			t_sample mul_782 = (m_history_59 * ((t_sample)0.999));
			t_sample mul_781 = (mul_840 * ((t_sample)0.001));
			t_sample add_784 = (mul_781 + mul_782);
			t_sample gen_788 = add_784;
			t_sample history_783_next_787 = fixdenorm(add_784);
			t_sample gen_869 = gen_788;
			t_sample mul_844 = (((int)1277) * mul_837);
			t_sample mul_798 = (m_history_58 * ((t_sample)0.999));
			t_sample mul_797 = (mul_844 * ((t_sample)0.001));
			t_sample add_800 = (mul_797 + mul_798);
			t_sample gen_804 = add_800;
			t_sample history_799_next_803 = fixdenorm(add_800);
			t_sample gen_867 = gen_804;
			t_sample mul_850 = (((int)1617) * mul_837);
			t_sample mul_822 = (m_history_57 * ((t_sample)0.999));
			t_sample mul_821 = (mul_850 * ((t_sample)0.001));
			t_sample add_824 = (mul_821 + mul_822);
			t_sample gen_828 = add_824;
			t_sample history_823_next_827 = fixdenorm(add_824);
			t_sample gen_864 = gen_828;
			t_sample mul_875 = (m_history_55 * rsub_873);
			t_sample add_872 = (zeroL_541 + gen_870);
			t_sample tap_881 = m_delay_56.read_linear(add_872);
			t_sample mul_878 = (tap_881 * rsub_871);
			t_sample add_877 = (mul_878 + mul_875);
			t_sample mul_874 = (add_877 * gen_486);
			t_sample add_879 = (gen_56 + mul_874);
			t_sample history_876_next_885 = fixdenorm(add_877);
			t_sample mul_890 = (m_history_53 * rsub_888);
			t_sample add_887 = (zeroL_541 + gen_869);
			t_sample tap_896 = m_delay_54.read_linear(add_887);
			t_sample mul_893 = (tap_896 * rsub_871);
			t_sample add_892 = (mul_893 + mul_890);
			t_sample mul_889 = (add_892 * gen_486);
			t_sample add_894 = (gen_56 + mul_889);
			t_sample history_891_next_900 = fixdenorm(add_892);
			t_sample mul_905 = (m_history_51 * rsub_903);
			t_sample add_902 = (zeroL_541 + gen_868);
			t_sample tap_911 = m_delay_52.read_linear(add_902);
			t_sample mul_908 = (tap_911 * rsub_871);
			t_sample add_907 = (mul_908 + mul_905);
			t_sample mul_904 = (add_907 * gen_486);
			t_sample add_909 = (gen_56 + mul_904);
			t_sample history_906_next_915 = fixdenorm(add_907);
			t_sample mul_920 = (m_history_49 * rsub_918);
			t_sample add_917 = (zeroL_541 + gen_867);
			t_sample tap_926 = m_delay_50.read_linear(add_917);
			t_sample mul_923 = (tap_926 * rsub_871);
			t_sample add_922 = (mul_923 + mul_920);
			t_sample mul_919 = (add_922 * gen_486);
			t_sample add_924 = (gen_56 + mul_919);
			t_sample history_921_next_930 = fixdenorm(add_922);
			t_sample mul_935 = (m_history_47 * rsub_933);
			t_sample add_932 = (zeroL_541 + gen_866);
			t_sample tap_941 = m_delay_48.read_linear(add_932);
			t_sample mul_938 = (tap_941 * rsub_871);
			t_sample add_937 = (mul_938 + mul_935);
			t_sample mul_934 = (add_937 * gen_486);
			t_sample add_939 = (gen_56 + mul_934);
			t_sample history_936_next_945 = fixdenorm(add_937);
			t_sample mul_950 = (m_history_45 * rsub_948);
			t_sample add_947 = (zeroL_541 + gen_865);
			t_sample tap_956 = m_delay_46.read_linear(add_947);
			t_sample mul_953 = (tap_956 * rsub_871);
			t_sample add_952 = (mul_953 + mul_950);
			t_sample mul_949 = (add_952 * gen_486);
			t_sample add_954 = (gen_56 + mul_949);
			t_sample history_951_next_960 = fixdenorm(add_952);
			t_sample mul_965 = (m_history_43 * rsub_963);
			t_sample add_962 = (zeroL_541 + gen_864);
			t_sample tap_971 = m_delay_44.read_linear(add_962);
			t_sample mul_968 = (tap_971 * rsub_871);
			t_sample add_967 = (mul_968 + mul_965);
			t_sample mul_964 = (add_967 * gen_486);
			t_sample add_969 = (gen_56 + mul_964);
			t_sample history_966_next_975 = fixdenorm(add_967);
			t_sample mul_980 = (m_history_41 * rsub_978);
			t_sample add_977 = (zeroL_541 + gen_863);
			t_sample tap_986 = m_delay_42.read_linear(add_977);
			t_sample mul_983 = (tap_986 * rsub_871);
			t_sample add_982 = (mul_983 + mul_980);
			t_sample mul_979 = (add_982 * gen_486);
			t_sample add_984 = (gen_56 + mul_979);
			t_sample history_981_next_990 = fixdenorm(add_982);
			t_sample mul_992 = ((((((((add_984 + add_969) + add_954) + add_939) + add_924) + add_909) + add_894) + add_879) * ((t_sample)0.125));
			t_sample mul_330 = (mul_992 * ((t_sample)-0.5));
			t_sample mul_320 = (div_321 * escala_Size_339);
			t_sample mul_322 = (((int)255) * mul_320);
			t_sample add_324 = (((int)0) + mul_322);
			t_sample tap_332 = m_delay_40.read_linear(add_324);
			t_sample tap_327 = m_delay_39.read_linear(add_324);
			t_sample mul_325 = (tap_327 * ((t_sample)0.5));
			t_sample add_328 = (mul_330 + (tap_332 + mul_325));
			t_sample mul_313 = (add_328 * ((t_sample)-0.5));
			t_sample mul_303 = (div_304 * escala_Size_339);
			t_sample mul_305 = (((int)556) * mul_303);
			t_sample add_307 = (((int)0) + mul_305);
			t_sample tap_315 = m_delay_38.read_linear(add_307);
			t_sample tap_310 = m_delay_37.read_linear(add_307);
			t_sample mul_308 = (tap_310 * ((t_sample)0.5));
			t_sample add_311 = (mul_313 + (tap_315 + mul_308));
			t_sample mul_296 = (add_311 * ((t_sample)-0.5));
			t_sample mul_286 = (div_287 * escala_Size_339);
			t_sample mul_288 = (((int)441) * mul_286);
			t_sample add_290 = (((int)0) + mul_288);
			t_sample tap_298 = m_delay_36.read_linear(add_290);
			t_sample tap_293 = m_delay_35.read_linear(add_290);
			t_sample mul_291 = (tap_293 * ((t_sample)0.5));
			t_sample add_294 = (mul_296 + (tap_298 + mul_291));
			t_sample mul_279 = (add_294 * ((t_sample)-0.5));
			t_sample mul_269 = (div_270 * escala_Size_339);
			t_sample mul_271 = (((int)341) * mul_269);
			t_sample add_273 = (((int)0) + mul_271);
			t_sample tap_281 = m_delay_34.read_linear(add_273);
			t_sample tap_276 = m_delay_33.read_linear(add_273);
			t_sample mul_274 = (tap_276 * ((t_sample)0.5));
			t_sample add_277 = (mul_279 + (tap_281 + mul_274));
			t_sample mul_615 = (div_630 * escala_Size_340);
			t_sample mul_628 = (((int)1617) * mul_615);
			t_sample mul_600 = (m_history_32 * ((t_sample)0.999));
			t_sample mul_599 = (mul_628 * ((t_sample)0.001));
			t_sample add_602 = (mul_599 + mul_600);
			t_sample gen_606 = add_602;
			t_sample history_601_next_605 = fixdenorm(add_602);
			t_sample gen_642 = gen_606;
			t_sample mul_624 = (((int)1422) * mul_615);
			t_sample mul_584 = (m_history_31 * ((t_sample)0.999));
			t_sample mul_583 = (mul_624 * ((t_sample)0.001));
			t_sample add_586 = (mul_583 + mul_584);
			t_sample gen_590 = add_586;
			t_sample history_585_next_589 = fixdenorm(add_586);
			t_sample gen_644 = gen_590;
			t_sample mul_622 = (((int)1277) * mul_615);
			t_sample mul_576 = (m_history_30 * ((t_sample)0.999));
			t_sample mul_575 = (mul_622 * ((t_sample)0.001));
			t_sample add_578 = (mul_575 + mul_576);
			t_sample gen_582 = add_578;
			t_sample history_577_next_581 = fixdenorm(add_578);
			t_sample gen_645 = gen_582;
			t_sample mul_620 = (((int)1356) * mul_615);
			t_sample mul_568 = (m_history_29 * ((t_sample)0.999));
			t_sample mul_567 = (mul_620 * ((t_sample)0.001));
			t_sample add_570 = (mul_567 + mul_568);
			t_sample gen_574 = add_570;
			t_sample history_569_next_573 = fixdenorm(add_570);
			t_sample gen_646 = gen_574;
			t_sample mul_631 = (((int)1557) * mul_615);
			t_sample mul_608 = (m_history_28 * ((t_sample)0.999));
			t_sample mul_607 = (mul_631 * ((t_sample)0.001));
			t_sample add_610 = (mul_607 + mul_608);
			t_sample gen_614 = add_610;
			t_sample history_609_next_613 = fixdenorm(add_610);
			t_sample gen_641 = gen_614;
			t_sample mul_626 = (((int)1491) * mul_615);
			t_sample mul_592 = (m_history_27 * ((t_sample)0.999));
			t_sample mul_591 = (mul_626 * ((t_sample)0.001));
			t_sample add_594 = (mul_591 + mul_592);
			t_sample gen_598 = add_594;
			t_sample history_593_next_597 = fixdenorm(add_594);
			t_sample gen_643 = gen_598;
			t_sample mul_618 = (((int)1188) * mul_615);
			t_sample mul_560 = (m_history_26 * ((t_sample)0.999));
			t_sample mul_559 = (mul_618 * ((t_sample)0.001));
			t_sample add_562 = (mul_559 + mul_560);
			t_sample gen_566 = add_562;
			t_sample history_561_next_565 = fixdenorm(add_562);
			t_sample gen_647 = gen_566;
			t_sample mul_616 = (((int)1116) * mul_615);
			t_sample mul_552 = (m_history_25 * ((t_sample)0.999));
			t_sample mul_551 = (mul_616 * ((t_sample)0.001));
			t_sample add_554 = (mul_551 + mul_552);
			t_sample gen_558 = add_554;
			t_sample history_553_next_557 = fixdenorm(add_554);
			t_sample gen_648 = gen_558;
			t_sample mul_653 = (m_history_23 * rsub_651);
			t_sample add_650 = (zeroR_542 + gen_648);
			t_sample tap_659 = m_delay_24.read_linear(add_650);
			t_sample mul_656 = (tap_659 * rsub_649);
			t_sample add_655 = (mul_656 + mul_653);
			t_sample mul_652 = (add_655 * gen_486);
			t_sample add_657 = (gen_57 + mul_652);
			t_sample history_654_next_663 = fixdenorm(add_655);
			t_sample mul_668 = (m_history_21 * rsub_666);
			t_sample add_665 = (zeroR_542 + gen_647);
			t_sample tap_674 = m_delay_22.read_linear(add_665);
			t_sample mul_671 = (tap_674 * rsub_649);
			t_sample add_670 = (mul_671 + mul_668);
			t_sample mul_667 = (add_670 * gen_486);
			t_sample add_672 = (gen_57 + mul_667);
			t_sample history_669_next_678 = fixdenorm(add_670);
			t_sample mul_683 = (m_history_19 * rsub_681);
			t_sample add_680 = (zeroR_542 + gen_646);
			t_sample tap_689 = m_delay_20.read_linear(add_680);
			t_sample mul_686 = (tap_689 * rsub_649);
			t_sample add_685 = (mul_686 + mul_683);
			t_sample mul_682 = (add_685 * gen_486);
			t_sample add_687 = (gen_57 + mul_682);
			t_sample history_684_next_693 = fixdenorm(add_685);
			t_sample mul_698 = (m_history_17 * rsub_696);
			t_sample add_695 = (zeroR_542 + gen_645);
			t_sample tap_704 = m_delay_18.read_linear(add_695);
			t_sample mul_701 = (tap_704 * rsub_649);
			t_sample add_700 = (mul_701 + mul_698);
			t_sample mul_697 = (add_700 * gen_486);
			t_sample add_702 = (gen_57 + mul_697);
			t_sample history_699_next_708 = fixdenorm(add_700);
			t_sample mul_713 = (m_history_15 * rsub_711);
			t_sample add_710 = (zeroR_542 + gen_644);
			t_sample tap_719 = m_delay_16.read_linear(add_710);
			t_sample mul_716 = (tap_719 * rsub_649);
			t_sample add_715 = (mul_716 + mul_713);
			t_sample mul_712 = (add_715 * gen_486);
			t_sample add_717 = (gen_57 + mul_712);
			t_sample history_714_next_723 = fixdenorm(add_715);
			t_sample mul_728 = (m_history_13 * rsub_726);
			t_sample add_725 = (zeroR_542 + gen_643);
			t_sample tap_734 = m_delay_14.read_linear(add_725);
			t_sample mul_731 = (tap_734 * rsub_649);
			t_sample add_730 = (mul_731 + mul_728);
			t_sample mul_727 = (add_730 * gen_486);
			t_sample add_732 = (gen_57 + mul_727);
			t_sample history_729_next_738 = fixdenorm(add_730);
			t_sample mul_743 = (m_history_11 * rsub_741);
			t_sample add_740 = (zeroR_542 + gen_642);
			t_sample tap_749 = m_delay_12.read_linear(add_740);
			t_sample mul_746 = (tap_749 * rsub_649);
			t_sample add_745 = (mul_746 + mul_743);
			t_sample mul_742 = (add_745 * gen_486);
			t_sample add_747 = (gen_57 + mul_742);
			t_sample history_744_next_753 = fixdenorm(add_745);
			t_sample mul_758 = (m_history_9 * rsub_756);
			t_sample add_755 = (zeroR_542 + gen_641);
			t_sample tap_764 = m_delay_10.read_linear(add_755);
			t_sample mul_761 = (tap_764 * rsub_649);
			t_sample add_760 = (mul_761 + mul_758);
			t_sample mul_757 = (add_760 * gen_486);
			t_sample add_762 = (gen_57 + mul_757);
			t_sample history_759_next_768 = fixdenorm(add_760);
			t_sample mul_770 = ((((((((add_762 + add_747) + add_732) + add_717) + add_702) + add_687) + add_672) + add_657) * ((t_sample)0.125));
			t_sample mul_257 = (mul_770 * ((t_sample)-0.5));
			t_sample mul_247 = (div_248 * escala_Size_266);
			t_sample mul_249 = (((int)255) * mul_247);
			t_sample add_251 = (((int)0) + mul_249);
			t_sample tap_259 = m_delay_8.read_linear(add_251);
			t_sample tap_254 = m_delay_7.read_linear(add_251);
			t_sample mul_252 = (tap_254 * ((t_sample)0.5));
			t_sample add_255 = (mul_257 + (tap_259 + mul_252));
			t_sample mul_240 = (add_255 * ((t_sample)-0.5));
			t_sample mul_230 = (div_231 * escala_Size_266);
			t_sample mul_232 = (((int)556) * mul_230);
			t_sample add_234 = (((int)0) + mul_232);
			t_sample tap_242 = m_delay_6.read_linear(add_234);
			t_sample tap_237 = m_delay_5.read_linear(add_234);
			t_sample mul_235 = (tap_237 * ((t_sample)0.5));
			t_sample add_238 = (mul_240 + (tap_242 + mul_235));
			t_sample mul_223 = (add_238 * ((t_sample)-0.5));
			t_sample mul_213 = (div_214 * escala_Size_266);
			t_sample mul_215 = (((int)441) * mul_213);
			t_sample add_217 = (((int)0) + mul_215);
			t_sample tap_225 = m_delay_4.read_linear(add_217);
			t_sample tap_220 = m_delay_3.read_linear(add_217);
			t_sample mul_218 = (tap_220 * ((t_sample)0.5));
			t_sample add_221 = (mul_223 + (tap_225 + mul_218));
			t_sample mul_206 = (add_221 * ((t_sample)-0.5));
			t_sample mul_196 = (div_197 * escala_Size_266);
			t_sample mul_198 = (((int)341) * mul_196);
			t_sample add_200 = (((int)0) + mul_198);
			t_sample tap_208 = m_delay_2.read_linear(add_200);
			t_sample tap_203 = m_delay_1.read_linear(add_200);
			t_sample mul_201 = (tap_203 * ((t_sample)0.5));
			t_sample add_204 = (mul_206 + (tap_208 + mul_201));
			t_sample add_511 = (add_277 + add_204);
			t_sample mul_509 = (add_511 * sqrt_507);
			t_sample sub_510 = (add_277 - add_204);
			t_sample mul_508 = (sub_510 * sqrt_506);
			t_sample add_505 = (mul_509 + mul_508);
			t_sample mul_496 = (add_505 * scale_998);
			t_sample sub_504 = (mul_509 - mul_508);
			t_sample mul_495 = (sub_504 * scale_998);
			t_sample return_171;
			t_sample return_172;
			eq3bandas_d_d_d_d_d_d_d_d_i(mul_496, mul_495, gen_179, gen_171, gen_163, gen_391, gen_383, gen_375, ((int)1), return_171, return_172);
			t_sample expr_432 = return_171;
			t_sample expr_433 = return_172;
			t_sample mix_1010 = (mul_496 + (gen_153 * (expr_432 - mul_496)));
			t_sample mix_1011 = (mul_495 + (gen_153 * (expr_433 - mul_495)));
			t_sample mix_1012 = (mix_1011 + (((int)0) * (((int)1) - mix_1011)));
			t_sample mix_1013 = (mix_1010 + (((int)0) * (((int)1) - mix_1010)));
			t_sample mix_1014 = (mix_1002 + (gen_349 * (mix_1013 - mix_1002)));
			t_sample mul_367 = (mix_1014 * gen_365);
			t_sample out1 = mul_367;
			t_sample mix_1015 = (mix_1004 + (gen_349 * (mix_1012 - mix_1004)));
			t_sample mul_366 = (mix_1015 * gen_365);
			t_sample out2 = mul_366;
			m_history_117 = history_360_next_364;
			m_history_99 = history_524_next_528;
			m_history_98 = history_344_next_348;
			m_history_97 = history_352_next_356;
			m_history_96 = history_148_next_152;
			m_history_95 = history_532_next_536;
			m_history_94 = history_174_next_178;
			m_history_93 = history_166_next_170;
			m_history_92 = history_158_next_162;
			m_history_91 = history_386_next_390;
			m_history_90 = history_378_next_382;
			m_history_89 = history_370_next_374;
			m_history_88 = history_516_next_520;
			m_history_87 = history_449_next_453;
			m_history_86 = history_186_next_190;
			m_history_85 = history_402_next_406;
			m_history_84 = history_394_next_398;
			m_history_83 = history_481_next_485;
			m_history_82 = history_441_next_445;
			m_history_81 = history_473_next_477;
			m_history_80 = history_68_next_93;
			m_history_71 = history_23_next_49;
			m_history_70 = history_19_next_50;
			m_history_69 = history_29_next_51;
			m_history_68 = history_35_next_52;
			m_history_67 = history_25_next_53;
			m_history_66 = history_31_next_54;
			m_history_65 = history_21_next_55;
			m_history_72 = history_33_next_48;
			m_history_79 = history_74_next_94;
			m_history_78 = history_78_next_95;
			m_history_77 = history_64_next_96;
			m_history_76 = history_80_next_97;
			m_history_75 = history_70_next_98;
			m_history_74 = history_66_next_99;
			m_history_73 = history_76_next_100;
			m_history_64 = history_815_next_819;
			m_history_41 = history_981_next_990;
			m_delay_42.write(add_984);
			m_history_43 = history_966_next_975;
			m_delay_44.write(add_969);
			m_history_45 = history_951_next_960;
			m_delay_46.write(add_954);
			m_history_47 = history_936_next_945;
			m_delay_48.write(add_939);
			m_history_49 = history_921_next_930;
			m_delay_50.write(add_924);
			m_history_51 = history_906_next_915;
			m_delay_52.write(add_909);
			m_history_53 = history_891_next_900;
			m_delay_54.write(add_894);
			m_history_55 = history_876_next_885;
			m_delay_56.write(add_879);
			m_history_63 = history_831_next_835;
			m_history_62 = history_775_next_779;
			m_history_61 = history_791_next_795;
			m_history_60 = history_807_next_811;
			m_history_59 = history_783_next_787;
			m_history_58 = history_799_next_803;
			m_history_57 = history_823_next_827;
			m_delay_40.write(mul_992);
			m_delay_33.write(add_277);
			m_delay_34.write(add_294);
			m_delay_35.write(add_294);
			m_delay_36.write(add_311);
			m_delay_37.write(add_311);
			m_delay_38.write(add_328);
			m_delay_39.write(add_328);
			m_history_32 = history_601_next_605;
			m_history_9 = history_759_next_768;
			m_delay_10.write(add_762);
			m_history_11 = history_744_next_753;
			m_delay_12.write(add_747);
			m_history_13 = history_729_next_738;
			m_delay_14.write(add_732);
			m_history_15 = history_714_next_723;
			m_delay_16.write(add_717);
			m_history_17 = history_699_next_708;
			m_delay_18.write(add_702);
			m_history_19 = history_684_next_693;
			m_delay_20.write(add_687);
			m_history_21 = history_669_next_678;
			m_delay_22.write(add_672);
			m_history_23 = history_654_next_663;
			m_delay_24.write(add_657);
			m_history_31 = history_585_next_589;
			m_history_30 = history_577_next_581;
			m_history_29 = history_569_next_573;
			m_history_28 = history_609_next_613;
			m_history_27 = history_593_next_597;
			m_history_26 = history_561_next_565;
			m_history_25 = history_553_next_557;
			m_delay_8.write(mul_770);
			m_delay_1.write(add_204);
			m_delay_2.write(add_221);
			m_delay_3.write(add_221);
			m_delay_4.write(add_238);
			m_delay_5.write(add_238);
			m_delay_6.write(add_255);
			m_delay_7.write(add_255);
			m_delay_1.step();
			m_delay_2.step();
			m_delay_3.step();
			m_delay_4.step();
			m_delay_5.step();
			m_delay_6.step();
			m_delay_7.step();
			m_delay_8.step();
			m_delay_10.step();
			m_delay_12.step();
			m_delay_14.step();
			m_delay_16.step();
			m_delay_18.step();
			m_delay_20.step();
			m_delay_22.step();
			m_delay_24.step();
			m_delay_33.step();
			m_delay_34.step();
			m_delay_35.step();
			m_delay_36.step();
			m_delay_37.step();
			m_delay_38.step();
			m_delay_39.step();
			m_delay_40.step();
			m_delay_42.step();
			m_delay_44.step();
			m_delay_46.step();
			m_delay_48.step();
			m_delay_50.step();
			m_delay_52.step();
			m_delay_54.step();
			m_delay_56.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_d_damp(t_param _value) {
		m_d_damp_100 = (_value < 0.001 ? 0.001 : (_value > 1 ? 1 : _value));
	};
	inline void set_q_onoffEQ(t_param _value) {
		m_q_onoffEQ_101 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_c_reflect(t_param _value) {
		m_c_reflect_102 = (_value < 0.001 ? 0.001 : (_value > 0.999 ? 0.999 : _value));
	};
	inline void set_j_hiGain(t_param _value) {
		m_j_hiGain_103 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_e_size(t_param _value) {
		m_e_size_104 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_m_output(t_param _value) {
		m_m_output_105 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_l_hpf(t_param _value) {
		m_l_hpf_106 = (_value < 20 ? 20 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_i_peakGain(t_param _value) {
		m_i_peakGain_107 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_o_peakFreq(t_param _value) {
		m_o_peakFreq_108 = (_value < 100 ? 100 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_a_input(t_param _value) {
		m_a_input_109 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_n_lowFreq(t_param _value) {
		m_n_lowFreq_110 = (_value < 20 ? 20 : (_value > 800 ? 800 : _value));
	};
	inline void set_f_st(t_param _value) {
		m_f_st_111 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_p_hiFreq(t_param _value) {
		m_p_hiFreq_112 = (_value < 800 ? 800 : (_value > 15000 ? 15000 : _value));
	};
	inline void set_k_lpf(t_param _value) {
		m_k_lpf_113 = (_value < 1000 ? 1000 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_g_freeze(t_param _value) {
		m_g_freeze_114 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_h_lowGain(t_param _value) {
		m_h_lowGain_115 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_b_drywet(t_param _value) {
		m_b_drywet_116 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_130;
		t_sample return_131;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_130, return_131);
		t_sample x_426 = return_130;
		sigR = return_131;
		t_sample return_155;
		t_sample return_156;
		peak_d_d_d_d_i(x_426, sigR, pf, pg, bw, return_155, return_156);
		t_sample x_429 = return_155;
		sigR = return_156;
		t_sample return_169;
		t_sample return_170;
		hishelf_d_d_d_d(x_429, sigR, hf, hg, return_169, return_170);
		t_sample x_431 = return_169;
		sigR = return_170;
		out1 = x_431;
		out2 = sigR;
		
	};
	inline void lowshelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_125(freq) != ((int)0)) || (__m_change_126(db) != ((int)0)))) {
			m_b_124 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_f_123 = safediv(freq, m_b_124);
			m_b_122 = ((m_b_124 * m_b_124) - ((int)1));
			m_w_121 = tan(safediv((m_f_123 * ((t_sample)3.1415926535898)), samplerate));
			m_a_120 = safediv(((int)1), (m_w_121 + ((int)1)));
			m_a_119 = (m_w_121 - ((int)1));
			
		};
		t_sample outputLowShelfL = lowshelfCore_d_d_d_d_d(sigL, m_a_120, m_a_119, m_b_122, m_w_121);
		t_sample outputLowShelfR = lowshelfCore_d_d_d_d_d_128(sigR, m_a_120, m_a_119, m_b_122, m_w_121);
		out1 = outputLowShelfL;
		out2 = outputLowShelfR;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_120, t_sample m_a_119, t_sample m_b_122, t_sample m_w_121) {
		t_sample x = (m_a_120 * (input - (m_a_119 * m_z_127)));
		t_sample output = (m_w_121 * (x + m_z_127));
		m_z_127 = x;
		return ((output * m_b_122) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_128(t_sample input, t_sample m_a_120, t_sample m_a_119, t_sample m_b_122, t_sample m_w_121) {
		t_sample x = (m_a_120 * (input - (m_a_119 * m_z_129)));
		t_sample output = (m_w_121 * (x + m_z_129));
		m_z_129 = x;
		return ((output * m_b_122) + input);
		
	};
	inline void peak_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_142(freq) != ((int)0)) || (__m_change_143(db) != ((int)0))) || (__m_change_144(bw) != ((int)0)))) {
			m_w_141 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_140 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_140 * m_b_140) - ((int)1));
			m_d_139 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_145 = safediv(((m_d_139 * m_d_139) - ((int)1)), (m_d_139 * m_b_140));
			m_d_138 = ((v_145 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_145 >= ((int)100)) ? ((int)100) : v_145));
			m_d_137 = (m_d_138 * b);
			m_wq_136 = (m_d_138 * m_w_141);
			m_w_135 = (m_w_141 * m_w_141);
			m_a_134 = safediv(((int)1), ((((int)1) + m_w_135) + m_wq_136));
			m_a_133 = ((m_w_135 - ((int)1)) * ((int)2));
			m_a_132 = ((((int)1) + m_w_135) - m_wq_136);
			
		};
		t_sample outputPeakL = peakCore_d_d_d_d_d_d(sigL, m_w_141, m_d_137, m_a_134, m_a_133, m_a_132);
		t_sample outputPeakR = peakCore_d_d_d_d_d_d_150(sigR, m_w_141, m_d_137, m_a_134, m_a_133, m_a_132);
		out1 = outputPeakL;
		out2 = outputPeakR;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_141, t_sample m_d_137, t_sample m_a_134, t_sample m_a_133, t_sample m_a_132) {
		t_sample output = ((input - m_z_148) * m_w_141);
		m_z_148 = m_z_149;
		m_z_149 = input;
		t_sample output_427 = (m_a_134 * ((output - (m_a_133 * m_z_147)) - (m_a_132 * m_z_146)));
		m_z_146 = m_z_147;
		m_z_147 = output_427;
		t_sample output_428 = (input + (output_427 * m_d_137));
		return output_428;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_150(t_sample input, t_sample m_w_141, t_sample m_d_137, t_sample m_a_134, t_sample m_a_133, t_sample m_a_132) {
		t_sample output = ((input - m_z_153) * m_w_141);
		m_z_153 = m_z_154;
		m_z_154 = input;
		t_sample output_427 = (m_a_134 * ((output - (m_a_133 * m_z_152)) - (m_a_132 * m_z_151)));
		m_z_151 = m_z_152;
		m_z_152 = output_427;
		t_sample output_428 = (input + (output_427 * m_d_137));
		return output_428;
		
	};
	inline void hishelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_163(freq) != ((int)0)) || (__m_change_164(db) != ((int)0)))) {
			m_b_162 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_165 = (freq * m_b_162);
			m_f_161 = ((samplerate < mina_165) ? samplerate : mina_165);
			m_b_160 = ((m_b_162 * m_b_162) - ((int)1));
			m_w_159 = tan(safediv((((m_f_161 < ((int)0)) ? ((int)0) : m_f_161) * ((t_sample)3.1415926535898)), samplerate));
			m_a_158 = safediv(((int)1), (m_w_159 + ((int)1)));
			m_a_157 = (m_w_159 - ((int)1));
			
		};
		t_sample outputHighShelfL = hishelfCore_d_d_d_d(sigL, m_a_158, m_a_157, m_b_160);
		t_sample outputHighShelfR = hishelfCore_d_d_d_d_167(sigR, m_a_158, m_a_157, m_b_160);
		out1 = outputHighShelfL;
		out2 = outputHighShelfR;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_158, t_sample m_a_157, t_sample m_b_160) {
		t_sample x = (m_a_158 * (input - (m_a_157 * m_z_166)));
		t_sample output = (x - m_z_166);
		m_z_166 = x;
		t_sample output_430 = ((output * m_b_160) + input);
		return output_430;
		
	};
	inline t_sample hishelfCore_d_d_d_d_167(t_sample input, t_sample m_a_158, t_sample m_a_157, t_sample m_b_160) {
		t_sample x = (m_a_158 * (input - (m_a_157 * m_z_168)));
		t_sample output = (x - m_z_168);
		m_z_168 = x;
		t_sample output_430 = ((output * m_b_160) + input);
		return output_430;
		
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
int num_params() { return 17; }

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
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_a_input_109; break;
		case 1: *value = self->m_b_drywet_116; break;
		case 2: *value = self->m_c_reflect_102; break;
		case 3: *value = self->m_d_damp_100; break;
		case 4: *value = self->m_e_size_104; break;
		case 5: *value = self->m_f_st_111; break;
		case 6: *value = self->m_g_freeze_114; break;
		case 7: *value = self->m_h_lowGain_115; break;
		case 8: *value = self->m_i_peakGain_107; break;
		case 9: *value = self->m_j_hiGain_103; break;
		case 10: *value = self->m_k_lpf_113; break;
		case 11: *value = self->m_l_hpf_106; break;
		case 12: *value = self->m_m_output_105; break;
		case 13: *value = self->m_n_lowFreq_110; break;
		case 14: *value = self->m_o_peakFreq_108; break;
		case 15: *value = self->m_p_hiFreq_112; break;
		case 16: *value = self->m_q_onoffEQ_101; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(17 * sizeof(ParamInfo));
	self->__commonstate.numparams = 17;
	// initialize parameter 0 ("m_a_input_109")
	pi = self->__commonstate.params + 0;
	pi->name = "a_input";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_input_109;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_drywet_116")
	pi = self->__commonstate.params + 1;
	pi->name = "b_drywet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_drywet_116;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_reflect_102")
	pi = self->__commonstate.params + 2;
	pi->name = "c_reflect";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_reflect_102;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 0.999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_damp_100")
	pi = self->__commonstate.params + 3;
	pi->name = "d_damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_damp_100;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_size_104")
	pi = self->__commonstate.params + 4;
	pi->name = "e_size";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_size_104;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_st_111")
	pi = self->__commonstate.params + 5;
	pi->name = "f_st";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_st_111;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_freeze_114")
	pi = self->__commonstate.params + 6;
	pi->name = "g_freeze";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_freeze_114;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_lowGain_115")
	pi = self->__commonstate.params + 7;
	pi->name = "h_lowGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_lowGain_115;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_peakGain_107")
	pi = self->__commonstate.params + 8;
	pi->name = "i_peakGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_peakGain_107;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_hiGain_103")
	pi = self->__commonstate.params + 9;
	pi->name = "j_hiGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_hiGain_103;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_lpf_113")
	pi = self->__commonstate.params + 10;
	pi->name = "k_lpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_lpf_113;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1000;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_hpf_106")
	pi = self->__commonstate.params + 11;
	pi->name = "l_hpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_hpf_106;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_output_105")
	pi = self->__commonstate.params + 12;
	pi->name = "m_output";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_output_105;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_lowFreq_110")
	pi = self->__commonstate.params + 13;
	pi->name = "n_lowFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_lowFreq_110;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 800;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_peakFreq_108")
	pi = self->__commonstate.params + 14;
	pi->name = "o_peakFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_peakFreq_108;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 2500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_hiFreq_112")
	pi = self->__commonstate.params + 15;
	pi->name = "p_hiFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_hiFreq_112;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 800;
	pi->outputmax = 15000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 16 ("m_q_onoffEQ_101")
	pi = self->__commonstate.params + 16;
	pi->name = "q_onoffEQ";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_q_onoffEQ_101;
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


} // JC_GENPLUGIN::
