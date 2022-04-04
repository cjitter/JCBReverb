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
	Change __m_change_134;
	Change __m_change_136;
	Change __m_change_135;
	Change __m_change_118;
	Change __m_change_155;
	Change __m_change_117;
	Change __m_change_156;
	Delay m_delay_24;
	Delay m_delay_22;
	Delay m_delay_21;
	Delay m_delay_23;
	Delay m_delay_26;
	Delay m_delay_60;
	Delay m_delay_28;
	Delay m_delay_72;
	Delay m_delay_34;
	Delay m_delay_20;
	Delay m_delay_32;
	Delay m_delay_30;
	Delay m_delay_38;
	Delay m_delay_40;
	Delay m_delay_19;
	Delay m_delay_17;
	Delay m_delay_70;
	Delay m_delay_55;
	Delay m_delay_54;
	Delay m_delay_53;
	Delay m_delay_56;
	Delay m_delay_58;
	Delay m_delay_62;
	Delay m_delay_18;
	Delay m_delay_52;
	Delay m_delay_50;
	Delay m_delay_68;
	Delay m_delay_51;
	Delay m_delay_66;
	Delay m_delay_49;
	Delay m_delay_64;
	Delay m_delay_36;
	int __exception;
	int vectorsize;
	t_sample m_f_st_107;
	t_sample m_i_peakGain_97;
	t_sample m_a_input_98;
	t_sample m_b_drywet_96;
	t_sample m_c_reflect_99;
	t_sample m_history_95;
	t_sample m_history_93;
	t_sample m_history_94;
	t_sample m_history_92;
	t_sample m_g_freeze_108;
	t_sample m_m_output_100;
	t_sample m_j_hiGain_102;
	t_sample m_l_hpf_105;
	t_sample m_b_114;
	t_sample m_history_109;
	t_sample m_e_size_101;
	t_sample m_a_111;
	t_sample m_a_112;
	t_sample m_h_lowGain_104;
	t_sample m_w_113;
	t_sample m_d_damp_103;
	t_sample m_k_lpf_106;
	t_sample m_a_124;
	t_sample m_b_116;
	t_sample m_z_145;
	t_sample m_z_146;
	t_sample m_z_144;
	t_sample m_z_141;
	t_sample m_z_143;
	t_sample m_z_140;
	t_sample m_a_149;
	t_sample m_w_151;
	t_sample m_b_154;
	t_sample m_a_150;
	t_sample m_f_153;
	t_sample m_b_152;
	t_sample m_f_115;
	t_sample m_z_139;
	t_sample m_w_133;
	t_sample m_a_125;
	t_sample m_a_126;
	t_sample m_history_91;
	t_sample m_z_119;
	t_sample m_z_121;
	t_sample m_z_138;
	t_sample m_w_127;
	t_sample m_d_129;
	t_sample m_b_132;
	t_sample m_wq_128;
	t_sample m_d_131;
	t_sample m_d_130;
	t_sample m_history_90;
	t_sample m_history_74;
	t_sample m_history_88;
	t_sample m_history_27;
	t_sample m_history_29;
	t_sample m_history_25;
	t_sample m_history_15;
	t_sample m_history_16;
	t_sample m_history_14;
	t_sample m_history_31;
	t_sample m_history_35;
	t_sample m_history_41;
	t_sample m_history_33;
	t_sample m_history_39;
	t_sample m_history_37;
	t_sample m_history_42;
	t_sample m_history_13;
	t_sample m_history_11;
	t_sample m_history_3;
	t_sample m_history_4;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample m_history_12;
	t_sample m_history_5;
	t_sample m_history_7;
	t_sample m_history_10;
	t_sample m_history_6;
	t_sample m_history_9;
	t_sample m_history_8;
	t_sample m_history_89;
	t_sample m_history_43;
	t_sample m_history_45;
	t_sample m_history_80;
	t_sample m_history_81;
	t_sample m_history_79;
	t_sample m_history_77;
	t_sample m_history_78;
	t_sample m_history_76;
	t_sample m_history_82;
	t_sample m_history_84;
	t_sample m_history_87;
	t_sample m_history_83;
	t_sample m_history_86;
	t_sample m_history_85;
	t_sample m_history_44;
	t_sample m_history_75;
	t_sample m_history_73;
	t_sample m_history_57;
	t_sample m_history_59;
	t_sample m_history_48;
	t_sample m_history_46;
	t_sample m_history_47;
	t_sample m_z_158;
	t_sample m_history_61;
	t_sample m_history_65;
	t_sample m_history_71;
	t_sample m_history_63;
	t_sample m_history_69;
	t_sample m_history_67;
	t_sample m_z_160;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
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
		m_delay_17.reset("m_delay_17", samplerate);
		m_delay_18.reset("m_delay_18", samplerate);
		m_delay_19.reset("m_delay_19", samplerate);
		m_delay_20.reset("m_delay_20", samplerate);
		m_delay_21.reset("m_delay_21", samplerate);
		m_delay_22.reset("m_delay_22", samplerate);
		m_delay_23.reset("m_delay_23", samplerate);
		m_delay_24.reset("m_delay_24", samplerate);
		m_history_25 = ((int)0);
		m_delay_26.reset("m_delay_26", samplerate);
		m_history_27 = ((int)0);
		m_delay_28.reset("m_delay_28", samplerate);
		m_history_29 = ((int)0);
		m_delay_30.reset("m_delay_30", samplerate);
		m_history_31 = ((int)0);
		m_delay_32.reset("m_delay_32", samplerate);
		m_history_33 = ((int)0);
		m_delay_34.reset("m_delay_34", samplerate);
		m_history_35 = ((int)0);
		m_delay_36.reset("m_delay_36", samplerate);
		m_history_37 = ((int)0);
		m_delay_38.reset("m_delay_38", samplerate);
		m_history_39 = ((int)0);
		m_delay_40.reset("m_delay_40", samplerate);
		m_history_41 = ((int)0);
		m_history_42 = ((int)0);
		m_history_43 = ((int)0);
		m_history_44 = ((int)0);
		m_history_45 = ((int)0);
		m_history_46 = ((int)0);
		m_history_47 = ((int)0);
		m_history_48 = ((int)0);
		m_delay_49.reset("m_delay_49", samplerate);
		m_delay_50.reset("m_delay_50", samplerate);
		m_delay_51.reset("m_delay_51", samplerate);
		m_delay_52.reset("m_delay_52", samplerate);
		m_delay_53.reset("m_delay_53", samplerate);
		m_delay_54.reset("m_delay_54", samplerate);
		m_delay_55.reset("m_delay_55", samplerate);
		m_delay_56.reset("m_delay_56", samplerate);
		m_history_57 = ((int)0);
		m_delay_58.reset("m_delay_58", samplerate);
		m_history_59 = ((int)0);
		m_delay_60.reset("m_delay_60", samplerate);
		m_history_61 = ((int)0);
		m_delay_62.reset("m_delay_62", samplerate);
		m_history_63 = ((int)0);
		m_delay_64.reset("m_delay_64", samplerate);
		m_history_65 = ((int)0);
		m_delay_66.reset("m_delay_66", samplerate);
		m_history_67 = ((int)0);
		m_delay_68.reset("m_delay_68", samplerate);
		m_history_69 = ((int)0);
		m_delay_70.reset("m_delay_70", samplerate);
		m_history_71 = ((int)0);
		m_delay_72.reset("m_delay_72", samplerate);
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
		m_b_drywet_96 = 0.33;
		m_i_peakGain_97 = 0;
		m_a_input_98 = 1;
		m_c_reflect_99 = 0.86;
		m_m_output_100 = 1;
		m_e_size_101 = 1;
		m_j_hiGain_102 = 0;
		m_d_damp_103 = 0.8;
		m_h_lowGain_104 = 0;
		m_l_hpf_105 = 20;
		m_k_lpf_106 = 20000;
		m_f_st_107 = 0.5;
		m_g_freeze_108 = 0;
		m_history_109 = ((int)0);
		m_a_111 = ((int)0);
		m_a_112 = ((int)0);
		m_w_113 = ((int)0);
		m_b_114 = ((int)0);
		m_f_115 = ((int)0);
		m_b_116 = ((int)0);
		__m_change_117.reset(0);
		__m_change_118.reset(0);
		m_z_119 = ((int)0);
		m_z_121 = ((int)0);
		m_a_124 = ((int)0);
		m_a_125 = ((int)0);
		m_a_126 = ((int)0);
		m_w_127 = ((int)0);
		m_wq_128 = ((int)0);
		m_d_129 = ((int)0);
		m_d_130 = ((int)0);
		m_d_131 = ((int)0);
		m_b_132 = ((int)0);
		m_w_133 = ((int)0);
		__m_change_134.reset(0);
		__m_change_135.reset(0);
		__m_change_136.reset(0);
		m_z_138 = ((int)0);
		m_z_139 = ((int)0);
		m_z_140 = ((int)0);
		m_z_141 = ((int)0);
		m_z_143 = ((int)0);
		m_z_144 = ((int)0);
		m_z_145 = ((int)0);
		m_z_146 = ((int)0);
		m_a_149 = ((int)0);
		m_a_150 = ((int)0);
		m_w_151 = ((int)0);
		m_b_152 = ((int)0);
		m_f_153 = ((int)0);
		m_b_154 = ((int)0);
		__m_change_155.reset(0);
		__m_change_156.reset(0);
		m_z_158 = ((int)0);
		m_z_160 = ((int)0);
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
		t_sample mul_176 = (m_m_output_100 * ((t_sample)0.001));
		t_sample mul_202 = (m_h_lowGain_104 * ((t_sample)0.001));
		t_sample mul_194 = (m_i_peakGain_97 * ((t_sample)0.001));
		t_sample mul_186 = (m_j_hiGain_102 * ((t_sample)0.001));
		t_sample mul_218 = (m_k_lpf_106 * ((t_sample)0.001));
		t_sample mul_210 = (m_l_hpf_105 * ((t_sample)0.001));
		t_sample mul_505 = (m_b_drywet_96 * ((t_sample)0.001));
		t_sample mul_497 = (m_a_input_98 * ((t_sample)0.001));
		int eq_541 = (m_g_freeze_108 == ((int)1));
		int toSize_534 = eq_541;
		int toSize_442 = toSize_534;
		t_sample mul_167 = (toSize_442 * ((t_sample)0.001));
		t_sample mul_521 = (m_f_st_107 * ((t_sample)0.001));
		t_sample mul_4666 = (m_e_size_101 * ((t_sample)0.001));
		t_sample rsub_988 = (((int)1) - m_d_damp_103);
		t_sample damp_530 = rsub_988;
		t_sample damp_531 = damp_530;
		int rsub_540 = (((int)1) - eq_541);
		t_sample mul_454 = (rsub_540 * ((t_sample)0.001));
		t_sample rsub_536 = (((t_sample)0.999) - m_c_reflect_99);
		int choice_110 = toSize_534;
		t_sample gate_535 = ((choice_110 >= 1) ? rsub_536 : 0);
		t_sample add_537 = (m_c_reflect_99 + gate_535);
		t_sample mul_462 = (add_537 * ((t_sample)0.001));
		t_sample rsub_862 = (((int)1) - damp_531);
		t_sample div_843 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_864 = (((int)1) - rsub_862);
		t_sample rsub_879 = (((int)1) - rsub_862);
		t_sample rsub_894 = (((int)1) - rsub_862);
		t_sample rsub_909 = (((int)1) - rsub_862);
		t_sample rsub_924 = (((int)1) - rsub_862);
		t_sample rsub_939 = (((int)1) - rsub_862);
		t_sample rsub_954 = (((int)1) - rsub_862);
		t_sample rsub_969 = (((int)1) - rsub_862);
		t_sample div_138 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_121 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_104 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_87 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_640 = (((int)1) - damp_530);
		t_sample div_621 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample rsub_642 = (((int)1) - rsub_640);
		t_sample rsub_657 = (((int)1) - rsub_640);
		t_sample rsub_672 = (((int)1) - rsub_640);
		t_sample rsub_687 = (((int)1) - rsub_640);
		t_sample rsub_702 = (((int)1) - rsub_640);
		t_sample rsub_717 = (((int)1) - rsub_640);
		t_sample rsub_732 = (((int)1) - rsub_640);
		t_sample rsub_747 = (((int)1) - rsub_640);
		t_sample div_65 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_48 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_31 = (samplerate * ((t_sample)2.2675736961451e-05));
		t_sample div_14 = (samplerate * ((t_sample)2.2675736961451e-05));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_177 = (m_history_109 * ((t_sample)0.999));
			t_sample add_179 = (mul_176 + mul_177);
			t_sample gen_183 = add_179;
			t_sample history_178_next_182 = fixdenorm(add_179);
			t_sample mul_203 = (m_history_95 * ((t_sample)0.999));
			t_sample add_205 = (mul_202 + mul_203);
			t_sample gen_209 = add_205;
			t_sample history_204_next_208 = fixdenorm(add_205);
			t_sample mul_195 = (m_history_94 * ((t_sample)0.999));
			t_sample add_197 = (mul_194 + mul_195);
			t_sample gen_201 = add_197;
			t_sample history_196_next_200 = fixdenorm(add_197);
			t_sample mul_187 = (m_history_93 * ((t_sample)0.999));
			t_sample add_189 = (mul_186 + mul_187);
			t_sample gen_193 = add_189;
			t_sample history_188_next_192 = fixdenorm(add_189);
			t_sample mul_219 = (m_history_92 * ((t_sample)0.999));
			t_sample add_221 = (mul_218 + mul_219);
			t_sample gen_225 = add_221;
			t_sample history_220_next_224 = fixdenorm(add_221);
			t_sample mul_211 = (m_history_91 * ((t_sample)0.999));
			t_sample add_213 = (mul_210 + mul_211);
			t_sample gen_217 = add_213;
			t_sample history_212_next_216 = fixdenorm(add_213);
			t_sample mul_506 = (m_history_90 * ((t_sample)0.999));
			t_sample add_508 = (mul_505 + mul_506);
			t_sample gen_512 = add_508;
			t_sample history_507_next_511 = fixdenorm(add_508);
			t_sample dry_wet_485 = gen_512;
			t_sample mul_160 = (m_history_89 * ((t_sample)0.999));
			t_sample mul_159 = (dry_wet_485 * ((t_sample)0.001));
			t_sample add_162 = (mul_159 + mul_160);
			t_sample gen_166 = add_162;
			t_sample history_161_next_165 = fixdenorm(add_162);
			t_sample mul_498 = (m_history_88 * ((t_sample)0.999));
			t_sample add_500 = (mul_497 + mul_498);
			t_sample gen_504 = add_500;
			t_sample history_499_next_503 = fixdenorm(add_500);
			t_sample input_420 = gen_504;
			t_sample mul_421 = (in1 * input_420);
			t_sample left_483 = mul_421;
			t_sample left_449 = left_483;
			t_sample mul_168 = (m_history_87 * ((t_sample)0.999));
			t_sample add_170 = (mul_167 + mul_168);
			t_sample gen_174 = add_170;
			t_sample history_169_next_173 = fixdenorm(add_170);
			t_sample mix_5054 = (left_483 + (gen_174 * (((int)0) - left_483)));
			t_sample mul_419 = (in2 * input_420);
			t_sample right_443 = mul_419;
			t_sample right_482 = right_443;
			t_sample right_445 = right_443;
			int eq_452 = (right_445 == ((int)0));
			t_sample mul_431 = (m_history_86 * ((t_sample)0.999));
			t_sample mul_430 = (eq_452 * ((t_sample)0.001));
			t_sample add_433 = (mul_430 + mul_431);
			t_sample gen_437 = add_433;
			t_sample history_432_next_436 = fixdenorm(add_433);
			t_sample mix_5055 = (((int)0) + (gen_437 * (left_449 - ((int)0))));
			t_sample mix_448 = mix_5055;
			t_sample add_5057 = (mix_448 + right_482);
			t_sample mix_5056 = (add_5057 + (gen_174 * (((int)0) - add_5057)));
			t_sample mul_522 = (m_history_85 * ((t_sample)0.999));
			t_sample add_524 = (mul_521 + mul_522);
			t_sample gen_528 = add_524;
			t_sample history_523_next_527 = fixdenorm(add_524);
			t_sample sub_5061 = (gen_528 - ((int)0));
			t_sample scale_5058 = ((safepow((sub_5061 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_480 = scale_5058;
			t_sample sqrt_489 = sqrt(gen_528);
			t_sample rsub_529 = (((int)1) - gen_528);
			t_sample sqrt_490 = sqrt(rsub_529);
			t_sample left_477 = left_483;
			t_sample mul_4669 = (m_history_84 * ((t_sample)0.999));
			t_sample add_4 = (mul_4666 + mul_4669);
			t_sample gen_4671 = add_4;
			t_sample history_3_next_4670 = fixdenorm(add_4);
			t_sample escala_Size_158 = gen_4671;
			t_sample escala_Size_156 = escala_Size_158;
			t_sample escala_Size_83 = escala_Size_158;
			t_sample escala_Size_157 = escala_Size_158;
			t_sample right_476 = right_443;
			t_sample mul_455 = (m_history_83 * ((t_sample)0.999));
			t_sample add_457 = (mul_454 + mul_455);
			t_sample gen_461 = add_457;
			t_sample history_456_next_460 = fixdenorm(add_457);
			t_sample freeze_538 = gen_461;
			t_sample mul_539 = (left_477 * freeze_538);
			t_sample freeze_495 = freeze_538;
			t_sample mul_496 = ((mix_448 + right_476) * freeze_495);
			t_sample toMoud_453 = gen_528;
			t_sample mul_463 = (m_history_82 * ((t_sample)0.999));
			t_sample add_465 = (mul_462 + mul_463);
			t_sample gen_469 = add_465;
			t_sample history_464_next_468 = fixdenorm(add_465);
			t_sample escala_Size_11 = escala_Size_158;
			t_sample mul_9 = (((int)23) * escala_Size_11);
			t_sample left_444 = left_483;
			int eq_446 = (left_444 == right_443);
			t_sample mul_423 = (m_history_81 * ((t_sample)0.999));
			t_sample mul_422 = (eq_446 * ((t_sample)0.001));
			t_sample add_425 = (mul_422 + mul_423);
			t_sample gen_429 = add_425;
			t_sample history_424_next_428 = fixdenorm(add_425);
			t_sample add_5063 = (gen_429 + gen_437);
			t_sample mix_5062 = (((int)0) + (add_5063 * (toMoud_453 - ((int)0))));
			t_sample mix_451 = mix_5062;
			t_sample mix_5064 = (((int)0) + (mix_451 * ((int)0)));
			t_sample mix_473 = mix_5064;
			t_sample zeroL_532 = mix_473;
			t_sample mul_828 = (div_843 * escala_Size_158);
			t_sample mul_839 = (((int)1491) * mul_828);
			t_sample mul_805 = (m_history_80 * ((t_sample)0.999));
			t_sample mul_804 = (mul_839 * ((t_sample)0.001));
			t_sample add_807 = (mul_804 + mul_805);
			t_sample gen_811 = add_807;
			t_sample history_806_next_810 = fixdenorm(add_807);
			t_sample gen_856 = gen_811;
			t_sample mul_829 = (((int)1116) * mul_828);
			t_sample mul_765 = (m_history_79 * ((t_sample)0.999));
			t_sample mul_764 = (mul_829 * ((t_sample)0.001));
			t_sample add_767 = (mul_764 + mul_765);
			t_sample gen_771 = add_767;
			t_sample history_766_next_770 = fixdenorm(add_767);
			t_sample gen_861 = gen_771;
			t_sample mul_831 = (((int)1188) * mul_828);
			t_sample mul_773 = (m_history_78 * ((t_sample)0.999));
			t_sample mul_772 = (mul_831 * ((t_sample)0.001));
			t_sample add_775 = (mul_772 + mul_773);
			t_sample gen_779 = add_775;
			t_sample history_774_next_778 = fixdenorm(add_775);
			t_sample gen_860 = gen_779;
			t_sample mul_837 = (((int)1422) * mul_828);
			t_sample mul_797 = (m_history_77 * ((t_sample)0.999));
			t_sample mul_796 = (mul_837 * ((t_sample)0.001));
			t_sample add_799 = (mul_796 + mul_797);
			t_sample gen_803 = add_799;
			t_sample history_798_next_802 = fixdenorm(add_799);
			t_sample gen_857 = gen_803;
			t_sample mul_833 = (((int)1356) * mul_828);
			t_sample mul_781 = (m_history_76 * ((t_sample)0.999));
			t_sample mul_780 = (mul_833 * ((t_sample)0.001));
			t_sample add_783 = (mul_780 + mul_781);
			t_sample gen_787 = add_783;
			t_sample history_782_next_786 = fixdenorm(add_783);
			t_sample gen_859 = gen_787;
			t_sample mul_841 = (((int)1617) * mul_828);
			t_sample mul_813 = (m_history_75 * ((t_sample)0.999));
			t_sample mul_812 = (mul_841 * ((t_sample)0.001));
			t_sample add_815 = (mul_812 + mul_813);
			t_sample gen_819 = add_815;
			t_sample history_814_next_818 = fixdenorm(add_815);
			t_sample gen_855 = gen_819;
			t_sample mul_835 = (((int)1277) * mul_828);
			t_sample mul_789 = (m_history_74 * ((t_sample)0.999));
			t_sample mul_788 = (mul_835 * ((t_sample)0.001));
			t_sample add_791 = (mul_788 + mul_789);
			t_sample gen_795 = add_791;
			t_sample history_790_next_794 = fixdenorm(add_791);
			t_sample gen_858 = gen_795;
			t_sample mul_844 = (((int)1557) * mul_828);
			t_sample mul_821 = (m_history_73 * ((t_sample)0.999));
			t_sample mul_820 = (mul_844 * ((t_sample)0.001));
			t_sample add_823 = (mul_820 + mul_821);
			t_sample gen_827 = add_823;
			t_sample history_822_next_826 = fixdenorm(add_823);
			t_sample gen_854 = gen_827;
			t_sample mul_866 = (m_history_71 * rsub_864);
			t_sample add_863 = (zeroL_532 + gen_861);
			t_sample tap_872 = m_delay_72.read_linear(add_863);
			t_sample mul_869 = (tap_872 * rsub_862);
			t_sample add_868 = (mul_869 + mul_866);
			t_sample mul_865 = (add_868 * gen_469);
			t_sample add_870 = (mul_539 + mul_865);
			t_sample gen_877 = add_870;
			t_sample history_867_next_876 = fixdenorm(add_868);
			t_sample mul_881 = (m_history_69 * rsub_879);
			t_sample add_878 = (zeroL_532 + gen_860);
			t_sample tap_887 = m_delay_70.read_linear(add_878);
			t_sample mul_884 = (tap_887 * rsub_862);
			t_sample add_883 = (mul_884 + mul_881);
			t_sample mul_880 = (add_883 * gen_469);
			t_sample add_885 = (mul_539 + mul_880);
			t_sample gen_892 = add_885;
			t_sample history_882_next_891 = fixdenorm(add_883);
			t_sample mul_896 = (m_history_67 * rsub_894);
			t_sample add_893 = (zeroL_532 + gen_859);
			t_sample tap_902 = m_delay_68.read_linear(add_893);
			t_sample mul_899 = (tap_902 * rsub_862);
			t_sample add_898 = (mul_899 + mul_896);
			t_sample mul_895 = (add_898 * gen_469);
			t_sample add_900 = (mul_539 + mul_895);
			t_sample gen_907 = add_900;
			t_sample history_897_next_906 = fixdenorm(add_898);
			t_sample mul_911 = (m_history_65 * rsub_909);
			t_sample add_908 = (zeroL_532 + gen_858);
			t_sample tap_917 = m_delay_66.read_linear(add_908);
			t_sample mul_914 = (tap_917 * rsub_862);
			t_sample add_913 = (mul_914 + mul_911);
			t_sample mul_910 = (add_913 * gen_469);
			t_sample add_915 = (mul_539 + mul_910);
			t_sample gen_922 = add_915;
			t_sample history_912_next_921 = fixdenorm(add_913);
			t_sample mul_926 = (m_history_63 * rsub_924);
			t_sample add_923 = (zeroL_532 + gen_857);
			t_sample tap_932 = m_delay_64.read_linear(add_923);
			t_sample mul_929 = (tap_932 * rsub_862);
			t_sample add_928 = (mul_929 + mul_926);
			t_sample mul_925 = (add_928 * gen_469);
			t_sample add_930 = (mul_539 + mul_925);
			t_sample gen_937 = add_930;
			t_sample history_927_next_936 = fixdenorm(add_928);
			t_sample mul_941 = (m_history_61 * rsub_939);
			t_sample add_938 = (zeroL_532 + gen_856);
			t_sample tap_947 = m_delay_62.read_linear(add_938);
			t_sample mul_944 = (tap_947 * rsub_862);
			t_sample add_943 = (mul_944 + mul_941);
			t_sample mul_940 = (add_943 * gen_469);
			t_sample add_945 = (mul_539 + mul_940);
			t_sample gen_952 = add_945;
			t_sample history_942_next_951 = fixdenorm(add_943);
			t_sample mul_956 = (m_history_59 * rsub_954);
			t_sample add_953 = (zeroL_532 + gen_855);
			t_sample tap_962 = m_delay_60.read_linear(add_953);
			t_sample mul_959 = (tap_962 * rsub_862);
			t_sample add_958 = (mul_959 + mul_956);
			t_sample mul_955 = (add_958 * gen_469);
			t_sample add_960 = (mul_539 + mul_955);
			t_sample gen_967 = add_960;
			t_sample history_957_next_966 = fixdenorm(add_958);
			t_sample mul_971 = (m_history_57 * rsub_969);
			t_sample add_968 = (zeroL_532 + gen_854);
			t_sample tap_977 = m_delay_58.read_linear(add_968);
			t_sample mul_974 = (tap_977 * rsub_862);
			t_sample add_973 = (mul_974 + mul_971);
			t_sample mul_970 = (add_973 * gen_469);
			t_sample add_975 = (mul_539 + mul_970);
			t_sample gen_982 = add_975;
			t_sample history_972_next_981 = fixdenorm(add_973);
			t_sample mul_983 = ((((((((gen_982 + gen_967) + gen_952) + gen_937) + gen_922) + gen_907) + gen_892) + gen_877) * ((t_sample)0.125));
			t_sample gen_985 = mul_983;
			t_sample mul_147 = (gen_985 * ((t_sample)-0.5));
			t_sample mul_137 = (div_138 * escala_Size_156);
			t_sample mul_139 = (((int)255) * mul_137);
			t_sample add_141 = (((int)0) + mul_139);
			t_sample tap_149 = m_delay_56.read_linear(add_141);
			t_sample tap_144 = m_delay_55.read_linear(add_141);
			t_sample mul_142 = (tap_144 * ((t_sample)0.5));
			t_sample add_145 = (mul_147 + (tap_149 + mul_142));
			t_sample gen_153 = add_145;
			t_sample mul_130 = (gen_153 * ((t_sample)-0.5));
			t_sample mul_120 = (div_121 * escala_Size_156);
			t_sample mul_122 = (((int)556) * mul_120);
			t_sample add_124 = (((int)0) + mul_122);
			t_sample tap_132 = m_delay_54.read_linear(add_124);
			t_sample tap_127 = m_delay_53.read_linear(add_124);
			t_sample mul_125 = (tap_127 * ((t_sample)0.5));
			t_sample add_128 = (mul_130 + (tap_132 + mul_125));
			t_sample gen_136 = add_128;
			t_sample mul_113 = (gen_136 * ((t_sample)-0.5));
			t_sample mul_103 = (div_104 * escala_Size_156);
			t_sample mul_105 = (((int)441) * mul_103);
			t_sample add_107 = (((int)0) + mul_105);
			t_sample tap_115 = m_delay_52.read_linear(add_107);
			t_sample tap_110 = m_delay_51.read_linear(add_107);
			t_sample mul_108 = (tap_110 * ((t_sample)0.5));
			t_sample add_111 = (mul_113 + (tap_115 + mul_108));
			t_sample gen_119 = add_111;
			t_sample mul_96 = (gen_119 * ((t_sample)-0.5));
			t_sample mul_86 = (div_87 * escala_Size_156);
			t_sample mul_88 = (((int)341) * mul_86);
			t_sample add_90 = (((int)0) + mul_88);
			t_sample tap_98 = m_delay_50.read_linear(add_90);
			t_sample tap_93 = m_delay_49.read_linear(add_90);
			t_sample mul_91 = (tap_93 * ((t_sample)0.5));
			t_sample add_94 = (mul_96 + (tap_98 + mul_91));
			t_sample gen_102 = add_94;
			t_sample gen_155 = gen_102;
			t_sample matrizMS_c45L_475 = gen_155;
			t_sample mix_5065 = (((int)0) + (mix_451 * (mul_9 - ((int)0))));
			t_sample mix_471 = mix_5065;
			t_sample zeroR_533 = mix_471;
			t_sample mul_606 = (div_621 * escala_Size_157);
			t_sample mul_607 = (((int)1116) * mul_606);
			t_sample mul_543 = (m_history_48 * ((t_sample)0.999));
			t_sample mul_542 = (mul_607 * ((t_sample)0.001));
			t_sample add_545 = (mul_542 + mul_543);
			t_sample gen_549 = add_545;
			t_sample history_544_next_548 = fixdenorm(add_545);
			t_sample gen_639 = gen_549;
			t_sample mul_622 = (((int)1557) * mul_606);
			t_sample mul_599 = (m_history_47 * ((t_sample)0.999));
			t_sample mul_598 = (mul_622 * ((t_sample)0.001));
			t_sample add_601 = (mul_598 + mul_599);
			t_sample gen_605 = add_601;
			t_sample history_600_next_604 = fixdenorm(add_601);
			t_sample gen_632 = gen_605;
			t_sample mul_615 = (((int)1422) * mul_606);
			t_sample mul_575 = (m_history_46 * ((t_sample)0.999));
			t_sample mul_574 = (mul_615 * ((t_sample)0.001));
			t_sample add_577 = (mul_574 + mul_575);
			t_sample gen_581 = add_577;
			t_sample history_576_next_580 = fixdenorm(add_577);
			t_sample gen_635 = gen_581;
			t_sample mul_609 = (((int)1188) * mul_606);
			t_sample mul_551 = (m_history_45 * ((t_sample)0.999));
			t_sample mul_550 = (mul_609 * ((t_sample)0.001));
			t_sample add_553 = (mul_550 + mul_551);
			t_sample gen_557 = add_553;
			t_sample history_552_next_556 = fixdenorm(add_553);
			t_sample gen_638 = gen_557;
			t_sample mul_619 = (((int)1617) * mul_606);
			t_sample mul_591 = (m_history_44 * ((t_sample)0.999));
			t_sample mul_590 = (mul_619 * ((t_sample)0.001));
			t_sample add_593 = (mul_590 + mul_591);
			t_sample gen_597 = add_593;
			t_sample history_592_next_596 = fixdenorm(add_593);
			t_sample gen_633 = gen_597;
			t_sample mul_613 = (((int)1277) * mul_606);
			t_sample mul_567 = (m_history_43 * ((t_sample)0.999));
			t_sample mul_566 = (mul_613 * ((t_sample)0.001));
			t_sample add_569 = (mul_566 + mul_567);
			t_sample gen_573 = add_569;
			t_sample history_568_next_572 = fixdenorm(add_569);
			t_sample gen_636 = gen_573;
			t_sample mul_617 = (((int)1491) * mul_606);
			t_sample mul_583 = (m_history_42 * ((t_sample)0.999));
			t_sample mul_582 = (mul_617 * ((t_sample)0.001));
			t_sample add_585 = (mul_582 + mul_583);
			t_sample gen_589 = add_585;
			t_sample history_584_next_588 = fixdenorm(add_585);
			t_sample gen_634 = gen_589;
			t_sample mul_611 = (((int)1356) * mul_606);
			t_sample mul_559 = (m_history_41 * ((t_sample)0.999));
			t_sample mul_558 = (mul_611 * ((t_sample)0.001));
			t_sample add_561 = (mul_558 + mul_559);
			t_sample gen_565 = add_561;
			t_sample history_560_next_564 = fixdenorm(add_561);
			t_sample gen_637 = gen_565;
			t_sample mul_644 = (m_history_39 * rsub_642);
			t_sample add_641 = (zeroR_533 + gen_639);
			t_sample tap_650 = m_delay_40.read_linear(add_641);
			t_sample mul_647 = (tap_650 * rsub_640);
			t_sample add_646 = (mul_647 + mul_644);
			t_sample mul_643 = (add_646 * gen_469);
			t_sample add_648 = (mul_496 + mul_643);
			t_sample gen_655 = add_648;
			t_sample history_645_next_654 = fixdenorm(add_646);
			t_sample mul_659 = (m_history_37 * rsub_657);
			t_sample add_656 = (zeroR_533 + gen_638);
			t_sample tap_665 = m_delay_38.read_linear(add_656);
			t_sample mul_662 = (tap_665 * rsub_640);
			t_sample add_661 = (mul_662 + mul_659);
			t_sample mul_658 = (add_661 * gen_469);
			t_sample add_663 = (mul_496 + mul_658);
			t_sample gen_670 = add_663;
			t_sample history_660_next_669 = fixdenorm(add_661);
			t_sample mul_674 = (m_history_35 * rsub_672);
			t_sample add_671 = (zeroR_533 + gen_637);
			t_sample tap_680 = m_delay_36.read_linear(add_671);
			t_sample mul_677 = (tap_680 * rsub_640);
			t_sample add_676 = (mul_677 + mul_674);
			t_sample mul_673 = (add_676 * gen_469);
			t_sample add_678 = (mul_496 + mul_673);
			t_sample gen_685 = add_678;
			t_sample history_675_next_684 = fixdenorm(add_676);
			t_sample mul_689 = (m_history_33 * rsub_687);
			t_sample add_686 = (zeroR_533 + gen_636);
			t_sample tap_695 = m_delay_34.read_linear(add_686);
			t_sample mul_692 = (tap_695 * rsub_640);
			t_sample add_691 = (mul_692 + mul_689);
			t_sample mul_688 = (add_691 * gen_469);
			t_sample add_693 = (mul_496 + mul_688);
			t_sample gen_700 = add_693;
			t_sample history_690_next_699 = fixdenorm(add_691);
			t_sample mul_704 = (m_history_31 * rsub_702);
			t_sample add_701 = (zeroR_533 + gen_635);
			t_sample tap_710 = m_delay_32.read_linear(add_701);
			t_sample mul_707 = (tap_710 * rsub_640);
			t_sample add_706 = (mul_707 + mul_704);
			t_sample mul_703 = (add_706 * gen_469);
			t_sample add_708 = (mul_496 + mul_703);
			t_sample gen_715 = add_708;
			t_sample history_705_next_714 = fixdenorm(add_706);
			t_sample mul_719 = (m_history_29 * rsub_717);
			t_sample add_716 = (zeroR_533 + gen_634);
			t_sample tap_725 = m_delay_30.read_linear(add_716);
			t_sample mul_722 = (tap_725 * rsub_640);
			t_sample add_721 = (mul_722 + mul_719);
			t_sample mul_718 = (add_721 * gen_469);
			t_sample add_723 = (mul_496 + mul_718);
			t_sample gen_730 = add_723;
			t_sample history_720_next_729 = fixdenorm(add_721);
			t_sample mul_734 = (m_history_27 * rsub_732);
			t_sample add_731 = (zeroR_533 + gen_633);
			t_sample tap_740 = m_delay_28.read_linear(add_731);
			t_sample mul_737 = (tap_740 * rsub_640);
			t_sample add_736 = (mul_737 + mul_734);
			t_sample mul_733 = (add_736 * gen_469);
			t_sample add_738 = (mul_496 + mul_733);
			t_sample gen_745 = add_738;
			t_sample history_735_next_744 = fixdenorm(add_736);
			t_sample mul_749 = (m_history_25 * rsub_747);
			t_sample add_746 = (zeroR_533 + gen_632);
			t_sample tap_755 = m_delay_26.read_linear(add_746);
			t_sample mul_752 = (tap_755 * rsub_640);
			t_sample add_751 = (mul_752 + mul_749);
			t_sample mul_748 = (add_751 * gen_469);
			t_sample add_753 = (mul_496 + mul_748);
			t_sample gen_760 = add_753;
			t_sample history_750_next_759 = fixdenorm(add_751);
			t_sample mul_761 = ((((((((gen_760 + gen_745) + gen_730) + gen_715) + gen_700) + gen_685) + gen_670) + gen_655) * ((t_sample)0.125));
			t_sample gen_763 = mul_761;
			t_sample mul_74 = (gen_763 * ((t_sample)-0.5));
			t_sample mul_64 = (div_65 * escala_Size_83);
			t_sample mul_66 = (((int)255) * mul_64);
			t_sample add_68 = (((int)0) + mul_66);
			t_sample tap_76 = m_delay_24.read_linear(add_68);
			t_sample tap_71 = m_delay_23.read_linear(add_68);
			t_sample mul_69 = (tap_71 * ((t_sample)0.5));
			t_sample add_72 = (mul_74 + (tap_76 + mul_69));
			t_sample gen_80 = add_72;
			t_sample mul_57 = (gen_80 * ((t_sample)-0.5));
			t_sample mul_47 = (div_48 * escala_Size_83);
			t_sample mul_49 = (((int)556) * mul_47);
			t_sample add_51 = (((int)0) + mul_49);
			t_sample tap_59 = m_delay_22.read_linear(add_51);
			t_sample tap_54 = m_delay_21.read_linear(add_51);
			t_sample mul_52 = (tap_54 * ((t_sample)0.5));
			t_sample add_55 = (mul_57 + (tap_59 + mul_52));
			t_sample gen_63 = add_55;
			t_sample mul_40 = (gen_63 * ((t_sample)-0.5));
			t_sample mul_30 = (div_31 * escala_Size_83);
			t_sample mul_32 = (((int)441) * mul_30);
			t_sample add_34 = (((int)0) + mul_32);
			t_sample tap_42 = m_delay_20.read_linear(add_34);
			t_sample tap_37 = m_delay_19.read_linear(add_34);
			t_sample mul_35 = (tap_37 * ((t_sample)0.5));
			t_sample add_38 = (mul_40 + (tap_42 + mul_35));
			t_sample gen_46 = add_38;
			t_sample mul_23 = (gen_46 * ((t_sample)-0.5));
			t_sample mul_13 = (div_14 * escala_Size_83);
			t_sample mul_15 = (((int)341) * mul_13);
			t_sample add_17 = (((int)0) + mul_15);
			t_sample tap_25 = m_delay_18.read_linear(add_17);
			t_sample tap_20 = m_delay_17.read_linear(add_17);
			t_sample mul_18 = (tap_20 * ((t_sample)0.5));
			t_sample add_21 = (mul_23 + (tap_25 + mul_18));
			t_sample gen_29 = add_21;
			t_sample gen_82 = gen_29;
			t_sample matrizMS_c45R_474 = gen_82;
			t_sample add_494 = (matrizMS_c45L_475 + matrizMS_c45R_474);
			t_sample mul_492 = (add_494 * sqrt_490);
			t_sample sub_493 = (matrizMS_c45L_475 - matrizMS_c45R_474);
			t_sample mul_491 = (sub_493 * sqrt_489);
			t_sample add_488 = (mul_492 + mul_491);
			t_sample mul_479 = (add_488 * scale_480);
			t_sample filterL_3454 = mul_479;
			t_sample sub_487 = (mul_492 - mul_491);
			t_sample mul_478 = (sub_487 * scale_480);
			t_sample filterR_3461 = mul_478;
			t_sample clamp_389 = ((gen_217 <= ((int)20)) ? ((int)20) : ((gen_217 >= ((int)5000)) ? ((int)5000) : gen_217));
			t_sample omega = safediv((clamp_389 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) + cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((-(((int)1) + cs)) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_3251 = a2;
			t_sample expr_3252 = a1;
			t_sample expr_3253 = a2;
			t_sample expr_3254 = b1;
			t_sample expr_3255 = b2;
			t_sample return_163;
			t_sample return_164;
			eq3bandas_d_d_i_i_i_d_d_d_i(filterL_3454, filterR_3461, ((int)333), ((int)1000), ((int)7500), gen_209, gen_201, gen_193, ((int)1), return_163, return_164);
			t_sample expr_3267 = return_163;
			t_sample expr_3268 = return_164;
			t_sample clamp_388 = ((gen_225 <= ((int)500)) ? ((int)500) : ((gen_225 >= ((int)19000)) ? ((int)19000) : gen_225));
			t_sample omega_3269 = safediv((clamp_388 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_3272 = sin(omega_3269);
			t_sample cs_3276 = cos(omega_3269);
			t_sample alpha_3273 = ((sn_3272 * ((t_sample)0.5)) * ((int)1));
			t_sample b_3270 = safediv(((int)1), (((int)1) + alpha_3273));
			t_sample a_3277 = (((((int)1) - cs_3276) * ((t_sample)0.5)) * b_3270);
			t_sample a_3274 = ((((int)1) - cs_3276) * b_3270);
			t_sample b_3275 = ((((int)-2) * cs_3276) * b_3270);
			t_sample b_3271 = ((((int)1) - alpha_3273) * b_3270);
			t_sample expr_3256 = a_3277;
			t_sample expr_3257 = a_3274;
			t_sample expr_3258 = a_3277;
			t_sample expr_3259 = b_3275;
			t_sample expr_3260 = b_3271;
			t_sample mul_303 = (expr_3267 * expr_3256);
			t_sample mul_293 = (expr_3268 * expr_3256);
			t_sample mul_300 = (m_history_12 * expr_3257);
			t_sample mul_290 = (m_history_11 * expr_3257);
			t_sample mul_298 = (m_history_13 * expr_3258);
			t_sample mul_288 = (m_history_15 * expr_3258);
			t_sample mul_294 = (m_history_14 * expr_3260);
			t_sample mul_284 = (m_history_16 * expr_3260);
			t_sample mul_296 = (m_history_10 * expr_3259);
			t_sample sub_302 = (((mul_298 + mul_300) + mul_303) - (mul_296 + mul_294));
			t_sample gen_322 = sub_302;
			t_sample mul_286 = (m_history_9 * expr_3259);
			t_sample sub_292 = (((mul_293 + mul_290) + mul_288) - (mul_286 + mul_284));
			t_sample gen_323 = sub_292;
			t_sample history_285_next_314 = fixdenorm(m_history_9);
			t_sample history_289_next_315 = fixdenorm(m_history_11);
			t_sample history_295_next_316 = fixdenorm(m_history_10);
			t_sample history_299_next_317 = fixdenorm(m_history_12);
			t_sample history_301_next_318 = fixdenorm(expr_3267);
			t_sample history_291_next_319 = fixdenorm(expr_3268);
			t_sample history_297_next_320 = fixdenorm(sub_302);
			t_sample history_287_next_321 = fixdenorm(sub_292);
			t_sample mul_257 = (gen_322 * expr_3251);
			t_sample mul_247 = (gen_323 * expr_3251);
			t_sample mul_254 = (m_history_3 * expr_3252);
			t_sample mul_244 = (m_history_4 * expr_3252);
			t_sample mul_252 = (m_history_6 * expr_3253);
			t_sample mul_242 = (m_history_8 * expr_3253);
			t_sample mul_248 = (m_history_7 * expr_3255);
			t_sample mul_238 = (m_history_5 * expr_3255);
			t_sample mul_250 = (m_history_2 * expr_3254);
			t_sample sub_256 = (((mul_252 + mul_254) + mul_257) - (mul_250 + mul_248));
			t_sample gen_276 = sub_256;
			t_sample mul_240 = (m_history_1 * expr_3254);
			t_sample sub_246 = (((mul_247 + mul_244) + mul_242) - (mul_240 + mul_238));
			t_sample gen_277 = sub_246;
			t_sample history_243_next_268 = fixdenorm(m_history_4);
			t_sample history_249_next_269 = fixdenorm(m_history_2);
			t_sample history_253_next_270 = fixdenorm(m_history_3);
			t_sample history_239_next_271 = fixdenorm(m_history_1);
			t_sample history_245_next_272 = fixdenorm(gen_323);
			t_sample history_255_next_273 = fixdenorm(gen_322);
			t_sample history_251_next_274 = fixdenorm(sub_256);
			t_sample history_241_next_275 = fixdenorm(sub_246);
			t_sample mix_5066 = (mix_5054 + (gen_166 * (gen_276 - mix_5054)));
			t_sample mul_185 = (mix_5066 * gen_183);
			t_sample out1 = mul_185;
			t_sample mix_5067 = (mix_5056 + (gen_166 * (gen_277 - mix_5056)));
			t_sample mul_184 = (mix_5067 * gen_183);
			t_sample out2 = mul_184;
			m_history_109 = history_178_next_182;
			m_history_95 = history_204_next_208;
			m_history_94 = history_196_next_200;
			m_history_93 = history_188_next_192;
			m_history_92 = history_220_next_224;
			m_history_91 = history_212_next_216;
			m_history_90 = history_507_next_511;
			m_history_89 = history_161_next_165;
			m_history_88 = history_499_next_503;
			m_history_87 = history_169_next_173;
			m_history_86 = history_432_next_436;
			m_history_85 = history_523_next_527;
			m_history_84 = history_3_next_4670;
			m_history_83 = history_456_next_460;
			m_history_82 = history_464_next_468;
			m_history_81 = history_424_next_428;
			m_history_80 = history_806_next_810;
			m_history_57 = history_972_next_981;
			m_delay_58.write(add_975);
			m_history_59 = history_957_next_966;
			m_delay_60.write(add_960);
			m_history_61 = history_942_next_951;
			m_delay_62.write(add_945);
			m_history_63 = history_927_next_936;
			m_delay_64.write(add_930);
			m_history_65 = history_912_next_921;
			m_delay_66.write(add_915);
			m_history_67 = history_897_next_906;
			m_delay_68.write(add_900);
			m_history_69 = history_882_next_891;
			m_delay_70.write(add_885);
			m_history_71 = history_867_next_876;
			m_delay_72.write(add_870);
			m_history_79 = history_766_next_770;
			m_history_78 = history_774_next_778;
			m_history_77 = history_798_next_802;
			m_history_76 = history_782_next_786;
			m_history_75 = history_814_next_818;
			m_history_74 = history_790_next_794;
			m_history_73 = history_822_next_826;
			m_delay_56.write(gen_985);
			m_delay_49.write(add_94);
			m_delay_50.write(gen_119);
			m_delay_51.write(add_111);
			m_delay_52.write(gen_136);
			m_delay_53.write(add_128);
			m_delay_54.write(gen_153);
			m_delay_55.write(add_145);
			m_history_48 = history_544_next_548;
			m_history_25 = history_750_next_759;
			m_delay_26.write(add_753);
			m_history_27 = history_735_next_744;
			m_delay_28.write(add_738);
			m_history_29 = history_720_next_729;
			m_delay_30.write(add_723);
			m_history_31 = history_705_next_714;
			m_delay_32.write(add_708);
			m_history_33 = history_690_next_699;
			m_delay_34.write(add_693);
			m_history_35 = history_675_next_684;
			m_delay_36.write(add_678);
			m_history_37 = history_660_next_669;
			m_delay_38.write(add_663);
			m_history_39 = history_645_next_654;
			m_delay_40.write(add_648);
			m_history_47 = history_600_next_604;
			m_history_46 = history_576_next_580;
			m_history_45 = history_552_next_556;
			m_history_44 = history_592_next_596;
			m_history_43 = history_568_next_572;
			m_history_42 = history_584_next_588;
			m_history_41 = history_560_next_564;
			m_delay_24.write(gen_763);
			m_delay_17.write(add_21);
			m_delay_18.write(gen_46);
			m_delay_19.write(add_38);
			m_delay_20.write(gen_63);
			m_delay_21.write(add_55);
			m_delay_22.write(gen_80);
			m_delay_23.write(add_72);
			m_history_16 = history_285_next_314;
			m_history_7 = history_249_next_269;
			m_history_6 = history_253_next_270;
			m_history_5 = history_239_next_271;
			m_history_4 = history_245_next_272;
			m_history_3 = history_255_next_273;
			m_history_2 = history_251_next_274;
			m_history_1 = history_241_next_275;
			m_history_8 = history_243_next_268;
			m_history_15 = history_289_next_315;
			m_history_14 = history_295_next_316;
			m_history_13 = history_299_next_317;
			m_history_12 = history_301_next_318;
			m_history_11 = history_291_next_319;
			m_history_10 = history_297_next_320;
			m_history_9 = history_287_next_321;
			m_delay_17.step();
			m_delay_18.step();
			m_delay_19.step();
			m_delay_20.step();
			m_delay_21.step();
			m_delay_22.step();
			m_delay_23.step();
			m_delay_24.step();
			m_delay_26.step();
			m_delay_28.step();
			m_delay_30.step();
			m_delay_32.step();
			m_delay_34.step();
			m_delay_36.step();
			m_delay_38.step();
			m_delay_40.step();
			m_delay_49.step();
			m_delay_50.step();
			m_delay_51.step();
			m_delay_52.step();
			m_delay_53.step();
			m_delay_54.step();
			m_delay_55.step();
			m_delay_56.step();
			m_delay_58.step();
			m_delay_60.step();
			m_delay_62.step();
			m_delay_64.step();
			m_delay_66.step();
			m_delay_68.step();
			m_delay_70.step();
			m_delay_72.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_b_drywet(t_param _value) {
		m_b_drywet_96 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_i_peakGain(t_param _value) {
		m_i_peakGain_97 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_a_input(t_param _value) {
		m_a_input_98 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_c_reflect(t_param _value) {
		m_c_reflect_99 = (_value < 0.001 ? 0.001 : (_value > 0.999 ? 0.999 : _value));
	};
	inline void set_m_output(t_param _value) {
		m_m_output_100 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_e_size(t_param _value) {
		m_e_size_101 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_j_hiGain(t_param _value) {
		m_j_hiGain_102 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_d_damp(t_param _value) {
		m_d_damp_103 = (_value < 0.001 ? 0.001 : (_value > 1 ? 1 : _value));
	};
	inline void set_h_lowGain(t_param _value) {
		m_h_lowGain_104 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_l_hpf(t_param _value) {
		m_l_hpf_105 = (_value < 20 ? 20 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_k_lpf(t_param _value) {
		m_k_lpf_106 = (_value < 1000 ? 1000 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_f_st(t_param _value) {
		m_f_st_107 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_g_freeze(t_param _value) {
		m_g_freeze_108 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void eq3bandas_d_d_i_i_i_d_d_d_i(t_sample sigL, t_sample sigR, int lf, int pf, int hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_122;
		t_sample return_123;
		lowshelf_d_d_i_d(sigL, sigR, lf, lg, return_122, return_123);
		t_sample x_3261 = return_122;
		sigR = return_123;
		t_sample return_147;
		t_sample return_148;
		peak_d_d_i_d_i(x_3261, sigR, pf, pg, bw, return_147, return_148);
		t_sample x_3264 = return_147;
		sigR = return_148;
		t_sample return_161;
		t_sample return_162;
		hishelf_d_d_i_d(x_3264, sigR, hf, hg, return_161, return_162);
		t_sample x_3266 = return_161;
		sigR = return_162;
		out1 = x_3266;
		out2 = sigR;
		
	};
	inline void lowshelf_d_d_i_d(t_sample sigL, t_sample sigR, int freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_117(freq) != ((int)0)) || (__m_change_118(db) != ((int)0)))) {
			m_b_116 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_f_115 = safediv(freq, m_b_116);
			m_b_114 = ((m_b_116 * m_b_116) - ((int)1));
			m_w_113 = tan(safediv((m_f_115 * ((t_sample)3.1415926535898)), samplerate));
			m_a_112 = safediv(((int)1), (m_w_113 + ((int)1)));
			m_a_111 = (m_w_113 - ((int)1));
			
		};
		t_sample outputLowShelfL = lowshelfCore_d_d_d_d_d(sigL, m_a_112, m_a_111, m_b_114, m_w_113);
		t_sample outputLowShelfR = lowshelfCore_d_d_d_d_d_120(sigR, m_a_112, m_a_111, m_b_114, m_w_113);
		out1 = outputLowShelfL;
		out2 = outputLowShelfR;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_112, t_sample m_a_111, t_sample m_b_114, t_sample m_w_113) {
		t_sample x = (m_a_112 * (input - (m_a_111 * m_z_119)));
		t_sample output = (m_w_113 * (x + m_z_119));
		m_z_119 = x;
		return ((output * m_b_114) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_120(t_sample input, t_sample m_a_112, t_sample m_a_111, t_sample m_b_114, t_sample m_w_113) {
		t_sample x = (m_a_112 * (input - (m_a_111 * m_z_121)));
		t_sample output = (m_w_113 * (x + m_z_121));
		m_z_121 = x;
		return ((output * m_b_114) + input);
		
	};
	inline void peak_d_d_i_d_i(t_sample sigL, t_sample sigR, int freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_134(freq) != ((int)0)) || (__m_change_135(db) != ((int)0))) || (__m_change_136(bw) != ((int)0)))) {
			m_w_133 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_132 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_132 * m_b_132) - ((int)1));
			m_d_131 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_137 = safediv(((m_d_131 * m_d_131) - ((int)1)), (m_d_131 * m_b_132));
			m_d_130 = ((v_137 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_137 >= ((int)100)) ? ((int)100) : v_137));
			m_d_129 = (m_d_130 * b);
			m_wq_128 = (m_d_130 * m_w_133);
			m_w_127 = (m_w_133 * m_w_133);
			m_a_126 = safediv(((int)1), ((((int)1) + m_w_127) + m_wq_128));
			m_a_125 = ((m_w_127 - ((int)1)) * ((int)2));
			m_a_124 = ((((int)1) + m_w_127) - m_wq_128);
			
		};
		t_sample outputPeakL = peakCore_d_d_d_d_d_d(sigL, m_w_133, m_d_129, m_a_126, m_a_125, m_a_124);
		t_sample outputPeakR = peakCore_d_d_d_d_d_d_142(sigR, m_w_133, m_d_129, m_a_126, m_a_125, m_a_124);
		out1 = outputPeakL;
		out2 = outputPeakR;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_133, t_sample m_d_129, t_sample m_a_126, t_sample m_a_125, t_sample m_a_124) {
		t_sample output = ((input - m_z_140) * m_w_133);
		m_z_140 = m_z_141;
		m_z_141 = input;
		t_sample output_3262 = (m_a_126 * ((output - (m_a_125 * m_z_139)) - (m_a_124 * m_z_138)));
		m_z_138 = m_z_139;
		m_z_139 = output_3262;
		t_sample output_3263 = (input + (output_3262 * m_d_129));
		return output_3263;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_142(t_sample input, t_sample m_w_133, t_sample m_d_129, t_sample m_a_126, t_sample m_a_125, t_sample m_a_124) {
		t_sample output = ((input - m_z_145) * m_w_133);
		m_z_145 = m_z_146;
		m_z_146 = input;
		t_sample output_3262 = (m_a_126 * ((output - (m_a_125 * m_z_144)) - (m_a_124 * m_z_143)));
		m_z_143 = m_z_144;
		m_z_144 = output_3262;
		t_sample output_3263 = (input + (output_3262 * m_d_129));
		return output_3263;
		
	};
	inline void hishelf_d_d_i_d(t_sample sigL, t_sample sigR, int freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_155(freq) != ((int)0)) || (__m_change_156(db) != ((int)0)))) {
			m_b_154 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_157 = (freq * m_b_154);
			m_f_153 = ((samplerate < mina_157) ? samplerate : mina_157);
			m_b_152 = ((m_b_154 * m_b_154) - ((int)1));
			m_w_151 = tan(safediv((((m_f_153 < ((int)0)) ? ((int)0) : m_f_153) * ((t_sample)3.1415926535898)), samplerate));
			m_a_150 = safediv(((int)1), (m_w_151 + ((int)1)));
			m_a_149 = (m_w_151 - ((int)1));
			
		};
		t_sample outputHighShelfL = hishelfCore_d_d_d_d(sigL, m_a_150, m_a_149, m_b_152);
		t_sample outputHighShelfR = hishelfCore_d_d_d_d_159(sigR, m_a_150, m_a_149, m_b_152);
		out1 = outputHighShelfL;
		out2 = outputHighShelfR;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_150, t_sample m_a_149, t_sample m_b_152) {
		t_sample x = (m_a_150 * (input - (m_a_149 * m_z_158)));
		t_sample output = (x - m_z_158);
		m_z_158 = x;
		t_sample output_3265 = ((output * m_b_152) + input);
		return output_3265;
		
	};
	inline t_sample hishelfCore_d_d_d_d_159(t_sample input, t_sample m_a_150, t_sample m_a_149, t_sample m_b_152) {
		t_sample x = (m_a_150 * (input - (m_a_149 * m_z_160)));
		t_sample output = (x - m_z_160);
		m_z_160 = x;
		t_sample output_3265 = ((output * m_b_152) + input);
		return output_3265;
		
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
int num_params() { return 13; }

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
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_a_input_98; break;
		case 1: *value = self->m_b_drywet_96; break;
		case 2: *value = self->m_c_reflect_99; break;
		case 3: *value = self->m_d_damp_103; break;
		case 4: *value = self->m_e_size_101; break;
		case 5: *value = self->m_f_st_107; break;
		case 6: *value = self->m_g_freeze_108; break;
		case 7: *value = self->m_h_lowGain_104; break;
		case 8: *value = self->m_i_peakGain_97; break;
		case 9: *value = self->m_j_hiGain_102; break;
		case 10: *value = self->m_k_lpf_106; break;
		case 11: *value = self->m_l_hpf_105; break;
		case 12: *value = self->m_m_output_100; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(13 * sizeof(ParamInfo));
	self->__commonstate.numparams = 13;
	// initialize parameter 0 ("m_a_input_98")
	pi = self->__commonstate.params + 0;
	pi->name = "a_input";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_input_98;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_drywet_96")
	pi = self->__commonstate.params + 1;
	pi->name = "b_drywet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_drywet_96;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_reflect_99")
	pi = self->__commonstate.params + 2;
	pi->name = "c_reflect";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_reflect_99;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 0.999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_damp_103")
	pi = self->__commonstate.params + 3;
	pi->name = "d_damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_damp_103;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_size_101")
	pi = self->__commonstate.params + 4;
	pi->name = "e_size";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_size_101;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_st_107")
	pi = self->__commonstate.params + 5;
	pi->name = "f_st";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_st_107;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_freeze_108")
	pi = self->__commonstate.params + 6;
	pi->name = "g_freeze";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_freeze_108;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_lowGain_104")
	pi = self->__commonstate.params + 7;
	pi->name = "h_lowGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_lowGain_104;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_peakGain_97")
	pi = self->__commonstate.params + 8;
	pi->name = "i_peakGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_peakGain_97;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_hiGain_102")
	pi = self->__commonstate.params + 9;
	pi->name = "j_hiGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_hiGain_102;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_lpf_106")
	pi = self->__commonstate.params + 10;
	pi->name = "k_lpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_lpf_106;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1000;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_hpf_105")
	pi = self->__commonstate.params + 11;
	pi->name = "l_hpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_hpf_105;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_output_100")
	pi = self->__commonstate.params + 12;
	pi->name = "m_output";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_output_100;
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
