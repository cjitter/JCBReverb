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
	Change __m_change_129;
	Change __m_change_130;
	Change __m_change_112;
	Change __m_change_150;
	Change __m_change_113;
	Change __m_change_131;
	Change __m_change_151;
	Delay m_delay_51;
	Delay m_delay_29;
	Delay m_delay_43;
	Delay m_delay_27;
	Delay m_delay_53;
	Delay m_delay_26;
	Delay m_delay_31;
	Delay m_delay_50;
	Delay m_delay_33;
	Delay m_delay_39;
	Delay m_delay_46;
	Delay m_delay_41;
	Delay m_delay_25;
	Delay m_delay_47;
	Delay m_delay_48;
	Delay m_delay_37;
	Delay m_delay_49;
	Delay m_delay_35;
	Delay m_delay_24;
	Delay m_delay_20;
	Delay m_delay_22;
	Delay m_delay_63;
	Delay m_delay_61;
	Delay m_delay_65;
	Delay m_delay_23;
	Delay m_delay_59;
	Delay m_delay_67;
	Delay m_delay_55;
	Delay m_delay_57;
	Delay m_delay_21;
	Delay m_delay_44;
	Delay m_delay_45;
	Delta __m_delta_100;
	Delta __m_delta_104;
	Phasor __m_phasor_102;
	Phasor __m_phasor_98;
	SineCycle __m_cycle_99;
	SineCycle __m_cycle_103;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_a_120;
	t_sample m_a_145;
	t_sample m_w_146;
	t_sample __m_latch_101;
	t_sample m_a_144;
	t_sample m_a_106;
	t_sample __m_latch_105;
	t_sample m_w_108;
	t_sample m_a_107;
	t_sample m_b_147;
	t_sample m_f_148;
	t_sample m_b_149;
	t_sample m_c_size_93;
	t_sample m_k_lpf_92;
	t_sample m_b_drywet_91;
	t_sample m_z_141;
	t_sample m_f_st_94;
	t_sample m_history_96;
	t_sample m_g_freeze_95;
	t_sample samples_to_seconds;
	t_sample m_a_input_90;
	t_sample m_b_109;
	t_sample m_f_110;
	t_sample m_d_125;
	t_sample m_d_126;
	t_sample m_a_119;
	t_sample m_b_127;
	t_sample m_d_124;
	t_sample m_w_122;
	t_sample m_wq_123;
	t_sample m_a_121;
	t_sample m_z_140;
	t_sample m_z_116;
	t_sample m_z_114;
	t_sample m_z_138;
	t_sample m_b_111;
	t_sample m_z_139;
	t_sample m_w_128;
	t_sample m_z_136;
	t_sample m_z_134;
	t_sample m_z_135;
	t_sample m_z_133;
	t_sample m_d_damp_89;
	t_sample m_history_72;
	t_sample m_j_hiGain_87;
	t_sample m_history_18;
	t_sample m_history_19;
	t_sample m_history_17;
	t_sample m_history_15;
	t_sample m_history_16;
	t_sample m_history_14;
	t_sample m_history_28;
	t_sample m_history_32;
	t_sample m_history_38;
	t_sample m_history_30;
	t_sample m_history_36;
	t_sample m_history_34;
	t_sample m_history_40;
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
	t_sample m_h_lowGain_88;
	t_sample m_history_42;
	t_sample m_history_54;
	t_sample m_history_79;
	t_sample m_history_80;
	t_sample m_history_78;
	t_sample m_history_76;
	t_sample m_history_77;
	t_sample m_history_75;
	t_sample m_history_81;
	t_sample m_i_peakGain_83;
	t_sample m_m_output_86;
	t_sample m_history_82;
	t_sample m_l_hpf_85;
	t_sample m_e_diffusion_84;
	t_sample m_history_52;
	t_sample m_history_74;
	t_sample m_z_153;
	t_sample m_history_60;
	t_sample m_history_62;
	t_sample m_history_58;
	t_sample m_history_56;
	t_sample m_history_73;
	t_sample m_history_64;
	t_sample m_history_68;
	t_sample m_history_71;
	t_sample m_history_66;
	t_sample m_history_70;
	t_sample m_history_69;
	t_sample m_z_155;
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
		m_history_17 = ((int)0);
		m_history_18 = ((int)0);
		m_history_19 = ((int)0);
		m_delay_20.reset("m_delay_20", samplerate);
		m_delay_21.reset("m_delay_21", samplerate);
		m_delay_22.reset("m_delay_22", samplerate);
		m_delay_23.reset("m_delay_23", samplerate);
		m_delay_24.reset("m_delay_24", samplerate);
		m_delay_25.reset("m_delay_25", samplerate);
		m_delay_26.reset("m_delay_26", samplerate);
		m_delay_27.reset("m_delay_27", samplerate);
		m_history_28 = ((int)0);
		m_delay_29.reset("m_delay_29", samplerate);
		m_history_30 = ((int)0);
		m_delay_31.reset("m_delay_31", samplerate);
		m_history_32 = ((int)0);
		m_delay_33.reset("m_delay_33", samplerate);
		m_history_34 = ((int)0);
		m_delay_35.reset("m_delay_35", samplerate);
		m_history_36 = ((int)0);
		m_delay_37.reset("m_delay_37", samplerate);
		m_history_38 = ((int)0);
		m_delay_39.reset("m_delay_39", samplerate);
		m_history_40 = ((int)0);
		m_delay_41.reset("m_delay_41", samplerate);
		m_history_42 = ((int)0);
		m_delay_43.reset("m_delay_43", samplerate);
		m_delay_44.reset("m_delay_44", samplerate);
		m_delay_45.reset("m_delay_45", samplerate);
		m_delay_46.reset("m_delay_46", samplerate);
		m_delay_47.reset("m_delay_47", samplerate);
		m_delay_48.reset("m_delay_48", samplerate);
		m_delay_49.reset("m_delay_49", samplerate);
		m_delay_50.reset("m_delay_50", samplerate);
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
		m_delay_65.reset("m_delay_65", samplerate);
		m_history_66 = ((int)0);
		m_delay_67.reset("m_delay_67", samplerate);
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
		m_i_peakGain_83 = 0;
		m_e_diffusion_84 = 0.5;
		m_l_hpf_85 = 33;
		m_m_output_86 = 1;
		m_j_hiGain_87 = 0;
		m_h_lowGain_88 = 0;
		m_d_damp_89 = 0.8;
		m_a_input_90 = 1;
		m_b_drywet_91 = 0.33;
		m_k_lpf_92 = 19000;
		m_c_size_93 = 0.86;
		m_f_st_94 = 0.5;
		m_g_freeze_95 = 0;
		m_history_96 = ((int)0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_98.reset(0);
		__m_cycle_99.reset(samplerate, 0);
		__m_delta_100.reset(0);
		__m_latch_101 = 0;
		__m_phasor_102.reset(0);
		__m_cycle_103.reset(samplerate, 0);
		__m_delta_104.reset(0);
		__m_latch_105 = 0;
		m_a_106 = ((int)0);
		m_a_107 = ((int)0);
		m_w_108 = ((int)0);
		m_b_109 = ((int)0);
		m_f_110 = ((int)0);
		m_b_111 = ((int)0);
		__m_change_112.reset(0);
		__m_change_113.reset(0);
		m_z_114 = ((int)0);
		m_z_116 = ((int)0);
		m_a_119 = ((int)0);
		m_a_120 = ((int)0);
		m_a_121 = ((int)0);
		m_w_122 = ((int)0);
		m_wq_123 = ((int)0);
		m_d_124 = ((int)0);
		m_d_125 = ((int)0);
		m_d_126 = ((int)0);
		m_b_127 = ((int)0);
		m_w_128 = ((int)0);
		__m_change_129.reset(0);
		__m_change_130.reset(0);
		__m_change_131.reset(0);
		m_z_133 = ((int)0);
		m_z_134 = ((int)0);
		m_z_135 = ((int)0);
		m_z_136 = ((int)0);
		m_z_138 = ((int)0);
		m_z_139 = ((int)0);
		m_z_140 = ((int)0);
		m_z_141 = ((int)0);
		m_a_144 = ((int)0);
		m_a_145 = ((int)0);
		m_w_146 = ((int)0);
		m_b_147 = ((int)0);
		m_f_148 = ((int)0);
		m_b_149 = ((int)0);
		__m_change_150.reset(0);
		__m_change_151.reset(0);
		m_z_153 = ((int)0);
		m_z_155 = ((int)0);
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
		t_sample mul_6640 = (m_m_output_86 * ((t_sample)0.001));
		t_sample mul_5033 = (m_h_lowGain_88 * ((t_sample)0.001));
		t_sample mul_5161 = (m_i_peakGain_83 * ((t_sample)0.001));
		t_sample mul_5289 = (m_j_hiGain_87 * ((t_sample)0.001));
		t_sample mul_4777 = (m_k_lpf_92 * ((t_sample)0.001));
		t_sample mul_4905 = (m_l_hpf_85 * ((t_sample)0.001));
		t_sample mul_392 = (m_b_drywet_91 * ((t_sample)0.001));
		int eq_430 = (m_g_freeze_95 == ((int)1));
		int toSize_296 = eq_430;
		t_sample mul_11763 = (toSize_296 * ((t_sample)0.001));
		t_sample mul_408 = (m_f_st_94 * ((t_sample)0.001));
		t_sample mul_384 = (m_a_input_90 * ((t_sample)0.001));
		t_sample mul_400 = (m_e_diffusion_84 * ((t_sample)0.001));
		t_sample rsub_696 = (((int)1) - m_d_damp_89);
		t_sample damp_420 = rsub_696;
		t_sample damp_419 = damp_420;
		int rsub_429 = (((int)1) - eq_430);
		t_sample mul_308 = (rsub_429 * ((t_sample)0.001));
		int toSize_423 = toSize_296;
		t_sample rsub_425 = (((t_sample)0.999) - m_c_size_93);
		int choice_97 = toSize_423;
		t_sample gate_424 = ((choice_97 >= 1) ? rsub_425 : 0);
		t_sample add_426 = (m_c_size_93 + gate_424);
		t_sample mul_316 = (add_426 * ((t_sample)0.001));
		samples_to_seconds = (1 / samplerate);
		t_sample rsub_556 = (((int)1) - damp_420);
		t_sample rsub_663 = (((int)1) - rsub_556);
		t_sample rsub_648 = (((int)1) - rsub_556);
		t_sample rsub_633 = (((int)1) - rsub_556);
		t_sample rsub_618 = (((int)1) - rsub_556);
		t_sample rsub_603 = (((int)1) - rsub_556);
		t_sample rsub_588 = (((int)1) - rsub_556);
		t_sample rsub_573 = (((int)1) - rsub_556);
		t_sample rsub_558 = (((int)1) - rsub_556);
		t_sample rsub_431 = (((int)1) - damp_419);
		t_sample rsub_433 = (((int)1) - rsub_431);
		t_sample rsub_448 = (((int)1) - rsub_431);
		t_sample rsub_463 = (((int)1) - rsub_431);
		t_sample rsub_478 = (((int)1) - rsub_431);
		t_sample rsub_493 = (((int)1) - rsub_431);
		t_sample rsub_508 = (((int)1) - rsub_431);
		t_sample rsub_523 = (((int)1) - rsub_431);
		t_sample rsub_538 = (((int)1) - rsub_431);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_6641 = (m_history_96 * ((t_sample)0.999));
			t_sample add_6643 = (mul_6640 + mul_6641);
			t_sample gen_6645 = add_6643;
			t_sample history_6642_next_6644 = fixdenorm(add_6643);
			t_sample mul_5034 = (m_history_82 * ((t_sample)0.999));
			t_sample add_5036 = (mul_5033 + mul_5034);
			t_sample gen_5038 = add_5036;
			t_sample history_5035_next_5037 = fixdenorm(add_5036);
			t_sample lowGain_75 = gen_5038;
			t_sample mul_5162 = (m_history_81 * ((t_sample)0.999));
			t_sample add_5164 = (mul_5161 + mul_5162);
			t_sample gen_5166 = add_5164;
			t_sample history_5163_next_5165 = fixdenorm(add_5164);
			t_sample peakGain_1626 = gen_5166;
			t_sample mul_5290 = (m_history_80 * ((t_sample)0.999));
			t_sample add_5292 = (mul_5289 + mul_5290);
			t_sample gen_5294 = add_5292;
			t_sample history_5291_next_5293 = fixdenorm(add_5292);
			t_sample hiGain_1810 = gen_5294;
			t_sample mul_4778 = (m_history_79 * ((t_sample)0.999));
			t_sample add_4780 = (mul_4777 + mul_4778);
			t_sample gen_4782 = add_4780;
			t_sample history_4779_next_4781 = fixdenorm(add_4780);
			t_sample lpf_77 = gen_4782;
			t_sample mul_4906 = (m_history_78 * ((t_sample)0.999));
			t_sample add_4908 = (mul_4905 + mul_4906);
			t_sample gen_4910 = add_4908;
			t_sample history_4907_next_4909 = fixdenorm(add_4908);
			t_sample hpf_76 = gen_4910;
			t_sample mul_393 = (m_history_77 * ((t_sample)0.999));
			t_sample add_395 = (mul_392 + mul_393);
			t_sample gen_399 = add_395;
			t_sample history_394_next_398 = fixdenorm(add_395);
			t_sample dry_wet_371 = gen_399;
			t_sample mul_12014 = (m_history_76 * ((t_sample)0.999));
			t_sample mul_12013 = (dry_wet_371 * ((t_sample)0.001));
			t_sample add_12016 = (mul_12013 + mul_12014);
			t_sample gen_12018 = add_12016;
			t_sample history_12015_next_12017 = fixdenorm(add_12016);
			t_sample mul_11764 = (m_history_75 * ((t_sample)0.999));
			t_sample add_11766 = (mul_11763 + mul_11764);
			t_sample gen_11768 = add_11766;
			t_sample history_11765_next_11767 = fixdenorm(add_11766);
			t_sample mul_409 = (m_history_74 * ((t_sample)0.999));
			t_sample add_411 = (mul_408 + mul_409);
			t_sample gen_415 = add_411;
			t_sample history_410_next_414 = fixdenorm(add_411);
			t_sample sub_12896 = (gen_415 - ((int)0));
			t_sample scale_12893 = ((safepow((sub_12896 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_12385 = scale_12893;
			t_sample mul_385 = (m_history_73 * ((t_sample)0.999));
			t_sample add_387 = (mul_384 + mul_385);
			t_sample gen_391 = add_387;
			t_sample history_386_next_390 = fixdenorm(add_387);
			t_sample input_266 = gen_391;
			t_sample mul_267 = (in1 * input_266);
			t_sample left_368 = mul_267;
			t_sample mix_12897 = (left_368 + (gen_11768 * (((int)0) - left_368)));
			t_sample left_303 = left_368;
			t_sample sqrt_376 = sqrt(gen_415);
			t_sample mul_265 = (in2 * input_266);
			t_sample right_297 = mul_265;
			t_sample right_367 = right_297;
			t_sample right_299 = right_297;
			int eq_306 = (right_299 == ((int)0));
			t_sample mul_277 = (m_history_72 * ((t_sample)0.999));
			t_sample mul_276 = (eq_306 * ((t_sample)0.001));
			t_sample add_279 = (mul_276 + mul_277);
			t_sample gen_283 = add_279;
			t_sample history_278_next_282 = fixdenorm(add_279);
			t_sample mix_12898 = (((int)0) + (gen_283 * (left_303 - ((int)0))));
			t_sample mix_302 = mix_12898;
			t_sample add_12900 = (mix_302 + right_367);
			t_sample mix_12899 = (add_12900 + (gen_11768 * (((int)0) - add_12900)));
			t_sample rsub_416 = (((int)1) - gen_415);
			t_sample sqrt_377 = sqrt(rsub_416);
			t_sample mul_401 = (m_history_71 * ((t_sample)0.999));
			t_sample add_403 = (mul_400 + mul_401);
			t_sample gen_407 = add_403;
			t_sample history_402_next_406 = fixdenorm(add_403);
			t_sample diffusion_688 = gen_407;
			t_sample diffusion_684 = diffusion_688;
			t_sample diffusion_689 = diffusion_688;
			t_sample diffusion_685 = diffusion_688;
			t_sample diffusion_690 = diffusion_688;
			t_sample diffusion_686 = diffusion_688;
			t_sample diffusion_691 = diffusion_688;
			t_sample diffusion_687 = diffusion_688;
			t_sample left_333 = left_368;
			t_sample right_332 = right_297;
			t_sample mul_309 = (m_history_70 * ((t_sample)0.999));
			t_sample add_311 = (mul_308 + mul_309);
			t_sample gen_315 = add_311;
			t_sample history_310_next_314 = fixdenorm(add_311);
			t_sample freeze_427 = gen_315;
			t_sample mul_428 = (left_333 * freeze_427);
			t_sample mul_373 = (mul_428 * ((int)1));
			t_sample freeze_382 = freeze_427;
			t_sample mul_383 = ((mix_302 + right_332) * freeze_382);
			t_sample mul_555 = (mul_383 * ((int)1));
			t_sample toMoud_307 = gen_415;
			t_sample mul_317 = (m_history_69 * ((t_sample)0.999));
			t_sample add_319 = (mul_316 + mul_317);
			t_sample gen_323 = add_319;
			t_sample history_318_next_322 = fixdenorm(add_319);
			t_sample size_417 = gen_323;
			t_sample size_418 = size_417;
			t_sample left_298 = left_368;
			int eq_300 = (left_298 == right_297);
			t_sample mul_269 = (m_history_68 * ((t_sample)0.999));
			t_sample mul_268 = (eq_300 * ((t_sample)0.001));
			t_sample add_271 = (mul_268 + mul_269);
			t_sample gen_275 = add_271;
			t_sample history_270_next_274 = fixdenorm(add_271);
			t_sample add_12902 = (gen_275 + gen_283);
			t_sample mix_12901 = (((int)0) + (add_12902 * (toMoud_307 - ((int)0))));
			t_sample mix_305 = mix_12901;
			t_sample mix_12903 = (((int)0) + (mix_305 * ((int)0)));
			t_sample mix_329 = mix_12903;
			t_sample mix_12904 = (((int)0) + (mix_305 * ((int)10)));
			t_sample mix_326 = mix_12904;
			t_sample noise_359 = noise();
			t_sample phasor_364 = __m_phasor_98(mix_329, samples_to_seconds);
			t_sample wrap_360 = wrap(phasor_364, ((int)0), ((int)1));
			__m_cycle_99.phase(wrap_360);
			t_sample cycle_362 = __m_cycle_99(__sinedata);
			t_sample cycleindex_363 = __m_cycle_99.phase();
			t_sample orange_12907 = (mix_326 - ((int)0));
			t_sample sub_12908 = (cycle_362 - (-1));
			t_sample scale_12905 = ((safepow((sub_12908 * ((t_sample)0.5)), ((int)1)) * orange_12907) + ((int)0));
			t_sample scale_361 = scale_12905;
			t_sample delta_356 = __m_delta_100(wrap_360);
			int lt_355 = (delta_356 < ((int)0));
			__m_latch_101 = ((lt_355 != 0) ? noise_359 : __m_latch_101);
			t_sample latch_358 = __m_latch_101;
			t_sample orange_12911 = (mix_326 - ((int)0));
			t_sample sub_12912 = (latch_358 - (-1));
			t_sample scale_12909 = ((safepow((sub_12912 * ((t_sample)0.5)), ((int)1)) * orange_12911) + ((int)0));
			t_sample scale_357 = scale_12909;
			t_sample gen_366 = (scale_361 + scale_357);
			t_sample zeroL_421 = gen_366;
			t_sample mul_665 = (m_history_66 * rsub_663);
			t_sample add_662 = (zeroL_421 + ((int)1557));
			t_sample tap_671 = m_delay_67.read_linear(add_662);
			t_sample mul_668 = (tap_671 * rsub_556);
			t_sample add_667 = (mul_668 + mul_665);
			t_sample mul_664 = (add_667 * size_418);
			t_sample add_669 = (mul_373 + mul_664);
			t_sample gen_676 = add_669;
			t_sample history_666_next_675 = fixdenorm(add_667);
			t_sample mul_650 = (m_history_64 * rsub_648);
			t_sample add_647 = (zeroL_421 + ((int)1617));
			t_sample tap_656 = m_delay_65.read_linear(add_647);
			t_sample mul_653 = (tap_656 * rsub_556);
			t_sample add_652 = (mul_653 + mul_650);
			t_sample mul_649 = (add_652 * size_418);
			t_sample add_654 = (mul_373 + mul_649);
			t_sample gen_661 = add_654;
			t_sample history_651_next_660 = fixdenorm(add_652);
			t_sample mul_635 = (m_history_62 * rsub_633);
			t_sample add_632 = (zeroL_421 + ((int)1491));
			t_sample tap_641 = m_delay_63.read_linear(add_632);
			t_sample mul_638 = (tap_641 * rsub_556);
			t_sample add_637 = (mul_638 + mul_635);
			t_sample mul_634 = (add_637 * size_418);
			t_sample add_639 = (mul_373 + mul_634);
			t_sample gen_646 = add_639;
			t_sample history_636_next_645 = fixdenorm(add_637);
			t_sample mul_620 = (m_history_60 * rsub_618);
			t_sample add_617 = (zeroL_421 + ((int)1422));
			t_sample tap_626 = m_delay_61.read_linear(add_617);
			t_sample mul_623 = (tap_626 * rsub_556);
			t_sample add_622 = (mul_623 + mul_620);
			t_sample mul_619 = (add_622 * size_418);
			t_sample add_624 = (mul_373 + mul_619);
			t_sample gen_631 = add_624;
			t_sample history_621_next_630 = fixdenorm(add_622);
			t_sample mul_605 = (m_history_58 * rsub_603);
			t_sample add_602 = (zeroL_421 + ((int)1277));
			t_sample tap_611 = m_delay_59.read_linear(add_602);
			t_sample mul_608 = (tap_611 * rsub_556);
			t_sample add_607 = (mul_608 + mul_605);
			t_sample mul_604 = (add_607 * size_418);
			t_sample add_609 = (mul_373 + mul_604);
			t_sample gen_616 = add_609;
			t_sample history_606_next_615 = fixdenorm(add_607);
			t_sample mul_590 = (m_history_56 * rsub_588);
			t_sample add_587 = (zeroL_421 + ((int)1356));
			t_sample tap_596 = m_delay_57.read_linear(add_587);
			t_sample mul_593 = (tap_596 * rsub_556);
			t_sample add_592 = (mul_593 + mul_590);
			t_sample mul_589 = (add_592 * size_418);
			t_sample add_594 = (mul_373 + mul_589);
			t_sample gen_601 = add_594;
			t_sample history_591_next_600 = fixdenorm(add_592);
			t_sample mul_575 = (m_history_54 * rsub_573);
			t_sample add_572 = (zeroL_421 + ((int)1188));
			t_sample tap_581 = m_delay_55.read_linear(add_572);
			t_sample mul_578 = (tap_581 * rsub_556);
			t_sample add_577 = (mul_578 + mul_575);
			t_sample mul_574 = (add_577 * size_418);
			t_sample add_579 = (mul_373 + mul_574);
			t_sample gen_586 = add_579;
			t_sample history_576_next_585 = fixdenorm(add_577);
			t_sample mul_560 = (m_history_52 * rsub_558);
			t_sample add_557 = (zeroL_421 + ((int)1116));
			t_sample tap_566 = m_delay_53.read_linear(add_557);
			t_sample mul_563 = (tap_566 * rsub_556);
			t_sample add_562 = (mul_563 + mul_560);
			t_sample mul_559 = (add_562 * size_418);
			t_sample add_564 = (mul_373 + mul_559);
			t_sample gen_571 = add_564;
			t_sample history_561_next_570 = fixdenorm(add_562);
			t_sample mul_677 = ((((((((gen_571 + gen_586) + gen_601) + gen_616) + gen_631) + gen_646) + gen_661) + gen_676) * ((t_sample)0.125));
			t_sample gen_679 = mul_677;
			t_sample mul_809 = (diffusion_691 * (-1));
			t_sample mul_810 = (gen_679 * mul_809);
			t_sample tap_812 = m_delay_51.read_step(((int)255));
			t_sample tap_807 = m_delay_50.read_step(((int)255));
			t_sample mul_805 = (tap_807 * diffusion_691);
			t_sample add_808 = (mul_810 + (tap_812 + mul_805));
			t_sample gen_816 = add_808;
			t_sample mul_796 = (diffusion_690 * (-1));
			t_sample mul_797 = (gen_816 * mul_796);
			t_sample tap_799 = m_delay_49.read_step(((int)556));
			t_sample tap_794 = m_delay_48.read_step(((int)556));
			t_sample mul_792 = (tap_794 * diffusion_690);
			t_sample add_795 = (mul_797 + (tap_799 + mul_792));
			t_sample gen_803 = add_795;
			t_sample mul_783 = (diffusion_689 * (-1));
			t_sample mul_784 = (gen_803 * mul_783);
			t_sample tap_786 = m_delay_47.read_step(((int)441));
			t_sample tap_781 = m_delay_46.read_step(((int)441));
			t_sample mul_779 = (tap_781 * diffusion_689);
			t_sample add_782 = (mul_784 + (tap_786 + mul_779));
			t_sample gen_790 = add_782;
			t_sample mul_770 = (diffusion_688 * (-1));
			t_sample mul_771 = (gen_790 * mul_770);
			t_sample tap_773 = m_delay_45.read_step(((int)341));
			t_sample tap_768 = m_delay_44.read_step(((int)341));
			t_sample mul_766 = (tap_768 * diffusion_688);
			t_sample add_769 = (mul_771 + (mul_766 + tap_773));
			t_sample gen_12765 = add_769;
			t_sample matrizMS_c45L_331 = gen_12765;
			t_sample noise_344 = noise();
			t_sample mul_339 = (mix_326 * (-1));
			t_sample phasor_351 = __m_phasor_102(mix_329, samples_to_seconds);
			t_sample add_346 = (phasor_351 + ((int)0));
			t_sample wrap_345 = wrap(add_346, ((int)0), ((int)1));
			__m_cycle_103.phase(wrap_345);
			t_sample cycle_349 = __m_cycle_103(__sinedata);
			t_sample cycleindex_350 = __m_cycle_103.phase();
			t_sample orange_12915 = (((int)0) - mul_339);
			t_sample sub_12916 = (cycle_349 - (-1));
			t_sample scale_12913 = ((safepow((sub_12916 * ((t_sample)0.5)), ((int)1)) * orange_12915) + mul_339);
			t_sample scale_348 = scale_12913;
			t_sample delta_341 = __m_delta_104(wrap_345);
			int lt_340 = (delta_341 < ((int)0));
			__m_latch_105 = ((lt_340 != 0) ? noise_344 : __m_latch_105);
			t_sample latch_343 = __m_latch_105;
			t_sample orange_12919 = (((int)0) - mul_339);
			t_sample sub_12920 = (latch_343 - (-1));
			t_sample scale_12917 = ((safepow((sub_12920 * ((t_sample)0.5)), ((int)1)) * orange_12919) + mul_339);
			t_sample scale_342 = scale_12917;
			t_sample gen_353 = (scale_348 + scale_342);
			t_sample zeroR_422 = gen_353;
			t_sample mul_435 = (m_history_42 * rsub_433);
			t_sample add_432 = (zeroR_422 + ((int)1116));
			t_sample tap_441 = m_delay_43.read_linear(add_432);
			t_sample mul_438 = (tap_441 * rsub_431);
			t_sample add_437 = (mul_438 + mul_435);
			t_sample mul_434 = (add_437 * size_417);
			t_sample add_439 = (mul_555 + mul_434);
			t_sample gen_446 = add_439;
			t_sample history_436_next_445 = fixdenorm(add_437);
			t_sample mul_450 = (m_history_40 * rsub_448);
			t_sample add_447 = (zeroR_422 + ((int)1188));
			t_sample tap_456 = m_delay_41.read_linear(add_447);
			t_sample mul_453 = (tap_456 * rsub_431);
			t_sample add_452 = (mul_453 + mul_450);
			t_sample mul_449 = (add_452 * size_417);
			t_sample add_454 = (mul_555 + mul_449);
			t_sample gen_461 = add_454;
			t_sample history_451_next_460 = fixdenorm(add_452);
			t_sample mul_465 = (m_history_38 * rsub_463);
			t_sample add_462 = (zeroR_422 + ((int)1356));
			t_sample tap_471 = m_delay_39.read_linear(add_462);
			t_sample mul_468 = (tap_471 * rsub_431);
			t_sample add_467 = (mul_468 + mul_465);
			t_sample mul_464 = (add_467 * size_417);
			t_sample add_469 = (mul_555 + mul_464);
			t_sample gen_476 = add_469;
			t_sample history_466_next_475 = fixdenorm(add_467);
			t_sample mul_480 = (m_history_36 * rsub_478);
			t_sample add_477 = (zeroR_422 + ((int)1277));
			t_sample tap_486 = m_delay_37.read_linear(add_477);
			t_sample mul_483 = (tap_486 * rsub_431);
			t_sample add_482 = (mul_483 + mul_480);
			t_sample mul_479 = (add_482 * size_417);
			t_sample add_484 = (mul_555 + mul_479);
			t_sample gen_491 = add_484;
			t_sample history_481_next_490 = fixdenorm(add_482);
			t_sample mul_495 = (m_history_34 * rsub_493);
			t_sample add_492 = (zeroR_422 + ((int)1422));
			t_sample tap_501 = m_delay_35.read_linear(add_492);
			t_sample mul_498 = (tap_501 * rsub_431);
			t_sample add_497 = (mul_498 + mul_495);
			t_sample mul_494 = (add_497 * size_417);
			t_sample add_499 = (mul_555 + mul_494);
			t_sample gen_506 = add_499;
			t_sample history_496_next_505 = fixdenorm(add_497);
			t_sample mul_510 = (m_history_32 * rsub_508);
			t_sample add_507 = (zeroR_422 + ((int)1491));
			t_sample tap_516 = m_delay_33.read_linear(add_507);
			t_sample mul_513 = (tap_516 * rsub_431);
			t_sample add_512 = (mul_513 + mul_510);
			t_sample mul_509 = (add_512 * size_417);
			t_sample add_514 = (mul_555 + mul_509);
			t_sample gen_521 = add_514;
			t_sample history_511_next_520 = fixdenorm(add_512);
			t_sample mul_525 = (m_history_30 * rsub_523);
			t_sample add_522 = (zeroR_422 + ((int)1617));
			t_sample tap_531 = m_delay_31.read_linear(add_522);
			t_sample mul_528 = (tap_531 * rsub_431);
			t_sample add_527 = (mul_528 + mul_525);
			t_sample mul_524 = (add_527 * size_417);
			t_sample add_529 = (mul_555 + mul_524);
			t_sample gen_536 = add_529;
			t_sample history_526_next_535 = fixdenorm(add_527);
			t_sample mul_540 = (m_history_28 * rsub_538);
			t_sample add_537 = (zeroR_422 + ((int)1557));
			t_sample tap_546 = m_delay_29.read_linear(add_537);
			t_sample mul_543 = (tap_546 * rsub_431);
			t_sample add_542 = (mul_543 + mul_540);
			t_sample mul_539 = (add_542 * size_417);
			t_sample add_544 = (mul_555 + mul_539);
			t_sample gen_551 = add_544;
			t_sample history_541_next_550 = fixdenorm(add_542);
			t_sample mul_552 = ((((((((gen_551 + gen_536) + gen_521) + gen_506) + gen_491) + gen_476) + gen_461) + gen_446) * ((t_sample)0.125));
			t_sample gen_554 = mul_552;
			t_sample mul_749 = (diffusion_687 * (-1));
			t_sample mul_750 = (gen_554 * mul_749);
			t_sample tap_752 = m_delay_27.read_step(((int)255));
			t_sample tap_747 = m_delay_26.read_step(((int)255));
			t_sample mul_745 = (tap_747 * diffusion_687);
			t_sample add_748 = (mul_750 + (tap_752 + mul_745));
			t_sample gen_756 = add_748;
			t_sample mul_736 = (diffusion_686 * (-1));
			t_sample mul_737 = (gen_756 * mul_736);
			t_sample tap_739 = m_delay_25.read_step(((int)556));
			t_sample tap_734 = m_delay_24.read_step(((int)556));
			t_sample mul_732 = (tap_734 * diffusion_686);
			t_sample add_735 = (mul_737 + (tap_739 + mul_732));
			t_sample gen_743 = add_735;
			t_sample mul_723 = (diffusion_685 * (-1));
			t_sample mul_724 = (gen_743 * mul_723);
			t_sample tap_726 = m_delay_23.read_step(((int)441));
			t_sample tap_721 = m_delay_22.read_step(((int)441));
			t_sample mul_719 = (tap_721 * diffusion_685);
			t_sample add_722 = (mul_724 + (tap_726 + mul_719));
			t_sample gen_730 = add_722;
			t_sample mul_710 = (diffusion_684 * (-1));
			t_sample mul_711 = (gen_730 * mul_710);
			t_sample tap_713 = m_delay_21.read_step(((int)341));
			t_sample tap_708 = m_delay_20.read_step(((int)341));
			t_sample mul_706 = (tap_708 * diffusion_684);
			t_sample add_709 = (mul_711 + (mul_706 + tap_713));
			t_sample gen_12701 = add_709;
			t_sample matrizMS_c45R_330 = gen_12701;
			t_sample add_381 = (matrizMS_c45L_331 + matrizMS_c45R_330);
			t_sample mul_379 = (add_381 * sqrt_377);
			t_sample sub_380 = (matrizMS_c45L_331 - matrizMS_c45R_330);
			t_sample mul_378 = (sub_380 * sqrt_376);
			t_sample add_375 = (mul_379 + mul_378);
			t_sample mul_335 = (add_375 * scale_12385);
			t_sample sub_374 = (mul_379 - mul_378);
			t_sample mul_334 = (sub_374 * scale_12385);
			t_sample clamp_126 = ((lpf_77 <= ((int)500)) ? ((int)500) : ((lpf_77 >= ((int)19000)) ? ((int)19000) : lpf_77));
			t_sample omega = safediv((clamp_126 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((int)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) - cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((((int)1) - cs) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_5758 = a2;
			t_sample expr_5759 = a1;
			t_sample expr_5760 = a2;
			t_sample expr_5761 = b1;
			t_sample expr_5762 = b2;
			t_sample clamp_79 = ((hpf_76 <= ((int)20)) ? ((int)20) : ((hpf_76 >= ((int)5000)) ? ((int)5000) : hpf_76));
			t_sample omega_5771 = safediv((clamp_79 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_5775 = sin(omega_5771);
			t_sample cs_5778 = cos(omega_5771);
			t_sample alpha_5776 = ((sn_5775 * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b_5772 = safediv(((int)1), (((int)1) + alpha_5776));
			t_sample a_5773 = (((((int)1) + cs_5778) * ((t_sample)0.5)) * b_5772);
			t_sample a_5774 = ((-(((int)1) + cs_5778)) * b_5772);
			t_sample b_5777 = ((((int)-2) * cs_5778) * b_5772);
			t_sample b_5779 = ((((int)1) - alpha_5776) * b_5772);
			t_sample expr_5753 = a_5773;
			t_sample expr_5754 = a_5774;
			t_sample expr_5755 = a_5773;
			t_sample expr_5756 = b_5777;
			t_sample expr_5757 = b_5779;
			t_sample mul_192 = (m_history_19 * ((t_sample)0.999));
			t_sample mul_193 = (lowGain_75 * ((t_sample)0.001));
			t_sample add_194 = (mul_193 + mul_192);
			t_sample gen_198 = add_194;
			t_sample history_191_next_197 = fixdenorm(add_194);
			t_sample mul_184 = (m_history_18 * ((t_sample)0.999));
			t_sample mul_185 = (peakGain_1626 * ((t_sample)0.001));
			t_sample add_186 = (mul_185 + mul_184);
			t_sample gen_190 = add_186;
			t_sample history_183_next_189 = fixdenorm(add_186);
			t_sample mul_176 = (m_history_17 * ((t_sample)0.999));
			t_sample mul_177 = (hiGain_1810 * ((t_sample)0.001));
			t_sample add_178 = (mul_177 + mul_176);
			t_sample gen_182 = add_178;
			t_sample history_175_next_181 = fixdenorm(add_178);
			t_sample return_158;
			t_sample return_159;
			eq3bandas_d_d_i_i_i_d_d_d_i(mul_335, mul_334, ((int)333), ((int)1000), ((int)7500), gen_198, gen_190, gen_182, ((int)1), return_158, return_159);
			t_sample expr_5769 = return_158;
			t_sample expr_5770 = return_159;
			t_sample mul_136 = (m_history_16 * expr_5760);
			t_sample mul_146 = (m_history_14 * expr_5760);
			t_sample mul_138 = (m_history_12 * expr_5759);
			t_sample mul_148 = (m_history_11 * expr_5759);
			t_sample mul_141 = (expr_5770 * expr_5758);
			t_sample mul_151 = (expr_5769 * expr_5758);
			t_sample mul_132 = (m_history_15 * expr_5762);
			t_sample mul_142 = (m_history_13 * expr_5762);
			t_sample mul_134 = (m_history_10 * expr_5761);
			t_sample sub_140 = (((mul_141 + mul_138) + mul_136) - (mul_134 + mul_132));
			t_sample gen_171 = sub_140;
			t_sample mul_144 = (m_history_9 * expr_5761);
			t_sample sub_150 = (((mul_146 + mul_148) + mul_151) - (mul_144 + mul_142));
			t_sample gen_170 = sub_150;
			t_sample history_137_next_162 = fixdenorm(m_history_12);
			t_sample history_133_next_163 = fixdenorm(m_history_10);
			t_sample history_147_next_164 = fixdenorm(m_history_11);
			t_sample history_143_next_165 = fixdenorm(m_history_9);
			t_sample history_139_next_166 = fixdenorm(expr_5770);
			t_sample history_149_next_167 = fixdenorm(expr_5769);
			t_sample history_135_next_168 = fixdenorm(sub_140);
			t_sample history_145_next_169 = fixdenorm(sub_150);
			t_sample mul_104 = (gen_170 * expr_5753);
			t_sample mul_94 = (gen_171 * expr_5753);
			t_sample mul_101 = (m_history_3 * expr_5754);
			t_sample mul_91 = (m_history_4 * expr_5754);
			t_sample mul_99 = (m_history_7 * expr_5755);
			t_sample mul_89 = (m_history_8 * expr_5755);
			t_sample mul_95 = (m_history_5 * expr_5757);
			t_sample mul_85 = (m_history_6 * expr_5757);
			t_sample mul_97 = (m_history_2 * expr_5756);
			t_sample sub_103 = (((mul_99 + mul_101) + mul_104) - (mul_97 + mul_95));
			t_sample gen_123 = sub_103;
			t_sample mul_87 = (m_history_1 * expr_5756);
			t_sample sub_93 = (((mul_94 + mul_91) + mul_89) - (mul_87 + mul_85));
			t_sample gen_124 = sub_93;
			t_sample history_90_next_115 = fixdenorm(m_history_4);
			t_sample history_100_next_116 = fixdenorm(m_history_3);
			t_sample history_86_next_117 = fixdenorm(m_history_1);
			t_sample history_96_next_118 = fixdenorm(m_history_2);
			t_sample history_92_next_119 = fixdenorm(gen_171);
			t_sample history_102_next_120 = fixdenorm(gen_170);
			t_sample history_98_next_121 = fixdenorm(sub_103);
			t_sample history_88_next_122 = fixdenorm(sub_93);
			t_sample mix_12921 = (mix_12897 + (gen_12018 * (gen_123 - mix_12897)));
			t_sample mul_7013 = (mix_12921 * gen_6645);
			t_sample out1 = mul_7013;
			t_sample mix_12922 = (mix_12899 + (gen_12018 * (gen_124 - mix_12899)));
			t_sample mul_7075 = (mix_12922 * gen_6645);
			t_sample out2 = mul_7075;
			m_history_96 = history_6642_next_6644;
			m_history_82 = history_5035_next_5037;
			m_history_81 = history_5163_next_5165;
			m_history_80 = history_5291_next_5293;
			m_history_79 = history_4779_next_4781;
			m_history_78 = history_4907_next_4909;
			m_history_77 = history_394_next_398;
			m_history_76 = history_12015_next_12017;
			m_history_75 = history_11765_next_11767;
			m_history_74 = history_410_next_414;
			m_history_73 = history_386_next_390;
			m_history_72 = history_278_next_282;
			m_history_71 = history_402_next_406;
			m_history_70 = history_310_next_314;
			m_history_69 = history_318_next_322;
			m_history_68 = history_270_next_274;
			m_delay_67.write(add_669);
			m_history_52 = history_561_next_570;
			m_delay_53.write(add_564);
			m_history_54 = history_576_next_585;
			m_delay_55.write(add_579);
			m_history_56 = history_591_next_600;
			m_delay_57.write(add_594);
			m_history_58 = history_606_next_615;
			m_delay_59.write(add_609);
			m_history_60 = history_621_next_630;
			m_delay_61.write(add_624);
			m_history_62 = history_636_next_645;
			m_delay_63.write(add_639);
			m_history_64 = history_651_next_660;
			m_delay_65.write(add_654);
			m_history_66 = history_666_next_675;
			m_delay_51.write(gen_679);
			m_delay_50.write(add_808);
			m_delay_49.write(gen_816);
			m_delay_48.write(add_795);
			m_delay_47.write(gen_803);
			m_delay_46.write(add_782);
			m_delay_45.write(gen_790);
			m_delay_44.write(add_769);
			m_delay_43.write(add_439);
			m_history_28 = history_541_next_550;
			m_delay_29.write(add_544);
			m_history_30 = history_526_next_535;
			m_delay_31.write(add_529);
			m_history_32 = history_511_next_520;
			m_delay_33.write(add_514);
			m_history_34 = history_496_next_505;
			m_delay_35.write(add_499);
			m_history_36 = history_481_next_490;
			m_delay_37.write(add_484);
			m_history_38 = history_466_next_475;
			m_delay_39.write(add_469);
			m_history_40 = history_451_next_460;
			m_delay_41.write(add_454);
			m_history_42 = history_436_next_445;
			m_delay_27.write(gen_554);
			m_delay_26.write(add_748);
			m_delay_25.write(gen_756);
			m_delay_24.write(add_735);
			m_delay_23.write(gen_743);
			m_delay_22.write(add_722);
			m_delay_21.write(gen_730);
			m_delay_20.write(add_709);
			m_history_19 = history_191_next_197;
			m_history_7 = history_100_next_116;
			m_history_6 = history_86_next_117;
			m_history_5 = history_96_next_118;
			m_history_4 = history_92_next_119;
			m_history_3 = history_102_next_120;
			m_history_2 = history_98_next_121;
			m_history_1 = history_88_next_122;
			m_history_8 = history_90_next_115;
			m_history_15 = history_133_next_163;
			m_history_14 = history_147_next_164;
			m_history_13 = history_143_next_165;
			m_history_12 = history_139_next_166;
			m_history_11 = history_149_next_167;
			m_history_10 = history_135_next_168;
			m_history_9 = history_145_next_169;
			m_history_16 = history_137_next_162;
			m_history_17 = history_175_next_181;
			m_history_18 = history_183_next_189;
			m_delay_20.step();
			m_delay_21.step();
			m_delay_22.step();
			m_delay_23.step();
			m_delay_24.step();
			m_delay_25.step();
			m_delay_26.step();
			m_delay_27.step();
			m_delay_29.step();
			m_delay_31.step();
			m_delay_33.step();
			m_delay_35.step();
			m_delay_37.step();
			m_delay_39.step();
			m_delay_41.step();
			m_delay_43.step();
			m_delay_44.step();
			m_delay_45.step();
			m_delay_46.step();
			m_delay_47.step();
			m_delay_48.step();
			m_delay_49.step();
			m_delay_50.step();
			m_delay_51.step();
			m_delay_53.step();
			m_delay_55.step();
			m_delay_57.step();
			m_delay_59.step();
			m_delay_61.step();
			m_delay_63.step();
			m_delay_65.step();
			m_delay_67.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_i_peakGain(t_param _value) {
		m_i_peakGain_83 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_e_diffusion(t_param _value) {
		m_e_diffusion_84 = (_value < 0.01 ? 0.01 : (_value > 0.7 ? 0.7 : _value));
	};
	inline void set_l_hpf(t_param _value) {
		m_l_hpf_85 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_m_output(t_param _value) {
		m_m_output_86 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_j_hiGain(t_param _value) {
		m_j_hiGain_87 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_h_lowGain(t_param _value) {
		m_h_lowGain_88 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_d_damp(t_param _value) {
		m_d_damp_89 = (_value < 0.001 ? 0.001 : (_value > 1 ? 1 : _value));
	};
	inline void set_a_input(t_param _value) {
		m_a_input_90 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_b_drywet(t_param _value) {
		m_b_drywet_91 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_k_lpf(t_param _value) {
		m_k_lpf_92 = (_value < 500 ? 500 : (_value > 19000 ? 19000 : _value));
	};
	inline void set_c_size(t_param _value) {
		m_c_size_93 = (_value < 0.001 ? 0.001 : (_value > 0.999 ? 0.999 : _value));
	};
	inline void set_f_st(t_param _value) {
		m_f_st_94 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_g_freeze(t_param _value) {
		m_g_freeze_95 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void eq3bandas_d_d_i_i_i_d_d_d_i(t_sample sigL, t_sample sigR, int lf, int pf, int hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_117;
		t_sample return_118;
		lowshelf_d_d_i_d(sigL, sigR, lf, lg, return_117, return_118);
		t_sample x_5763 = return_117;
		sigR = return_118;
		t_sample return_142;
		t_sample return_143;
		peak_d_d_i_d_i(x_5763, sigR, pf, pg, bw, return_142, return_143);
		t_sample x_5766 = return_142;
		sigR = return_143;
		t_sample return_156;
		t_sample return_157;
		hishelf_d_d_i_d(x_5766, sigR, hf, hg, return_156, return_157);
		t_sample x_5768 = return_156;
		sigR = return_157;
		out1 = x_5768;
		out2 = sigR;
		
	};
	inline void lowshelf_d_d_i_d(t_sample sigL, t_sample sigR, int freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_112(freq) != ((int)0)) || (__m_change_113(db) != ((int)0)))) {
			m_b_111 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_f_110 = safediv(freq, m_b_111);
			m_b_109 = ((m_b_111 * m_b_111) - ((int)1));
			m_w_108 = tan(safediv((m_f_110 * ((t_sample)3.1415926535898)), samplerate));
			m_a_107 = safediv(((int)1), (m_w_108 + ((int)1)));
			m_a_106 = (m_w_108 - ((int)1));
			
		};
		t_sample outputLowShelfL = lowshelfCore_d_d_d_d_d(sigL, m_a_107, m_a_106, m_b_109, m_w_108);
		t_sample outputLowShelfR = lowshelfCore_d_d_d_d_d_115(sigR, m_a_107, m_a_106, m_b_109, m_w_108);
		out1 = outputLowShelfL;
		out2 = outputLowShelfR;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_107, t_sample m_a_106, t_sample m_b_109, t_sample m_w_108) {
		t_sample x = (m_a_107 * (input - (m_a_106 * m_z_114)));
		t_sample output = (m_w_108 * (x + m_z_114));
		m_z_114 = x;
		return ((output * m_b_109) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_115(t_sample input, t_sample m_a_107, t_sample m_a_106, t_sample m_b_109, t_sample m_w_108) {
		t_sample x = (m_a_107 * (input - (m_a_106 * m_z_116)));
		t_sample output = (m_w_108 * (x + m_z_116));
		m_z_116 = x;
		return ((output * m_b_109) + input);
		
	};
	inline void peak_d_d_i_d_i(t_sample sigL, t_sample sigR, int freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_129(freq) != ((int)0)) || (__m_change_130(db) != ((int)0))) || (__m_change_131(bw) != ((int)0)))) {
			m_w_128 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_127 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_127 * m_b_127) - ((int)1));
			m_d_126 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_132 = safediv(((m_d_126 * m_d_126) - ((int)1)), (m_d_126 * m_b_127));
			m_d_125 = ((v_132 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_132 >= ((int)100)) ? ((int)100) : v_132));
			m_d_124 = (m_d_125 * b);
			m_wq_123 = (m_d_125 * m_w_128);
			m_w_122 = (m_w_128 * m_w_128);
			m_a_121 = safediv(((int)1), ((((int)1) + m_w_122) + m_wq_123));
			m_a_120 = ((m_w_122 - ((int)1)) * ((int)2));
			m_a_119 = ((((int)1) + m_w_122) - m_wq_123);
			
		};
		t_sample outputPeakL = peakCore_d_d_d_d_d_d(sigL, m_w_128, m_d_124, m_a_121, m_a_120, m_a_119);
		t_sample outputPeakR = peakCore_d_d_d_d_d_d_137(sigR, m_w_128, m_d_124, m_a_121, m_a_120, m_a_119);
		out1 = outputPeakL;
		out2 = outputPeakR;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_128, t_sample m_d_124, t_sample m_a_121, t_sample m_a_120, t_sample m_a_119) {
		t_sample output = ((input - m_z_135) * m_w_128);
		m_z_135 = m_z_136;
		m_z_136 = input;
		t_sample output_5764 = (m_a_121 * ((output - (m_a_120 * m_z_134)) - (m_a_119 * m_z_133)));
		m_z_133 = m_z_134;
		m_z_134 = output_5764;
		t_sample output_5765 = (input + (output_5764 * m_d_124));
		return output_5765;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_137(t_sample input, t_sample m_w_128, t_sample m_d_124, t_sample m_a_121, t_sample m_a_120, t_sample m_a_119) {
		t_sample output = ((input - m_z_140) * m_w_128);
		m_z_140 = m_z_141;
		m_z_141 = input;
		t_sample output_5764 = (m_a_121 * ((output - (m_a_120 * m_z_139)) - (m_a_119 * m_z_138)));
		m_z_138 = m_z_139;
		m_z_139 = output_5764;
		t_sample output_5765 = (input + (output_5764 * m_d_124));
		return output_5765;
		
	};
	inline void hishelf_d_d_i_d(t_sample sigL, t_sample sigR, int freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_150(freq) != ((int)0)) || (__m_change_151(db) != ((int)0)))) {
			m_b_149 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_152 = (freq * m_b_149);
			m_f_148 = ((samplerate < mina_152) ? samplerate : mina_152);
			m_b_147 = ((m_b_149 * m_b_149) - ((int)1));
			m_w_146 = tan(safediv((((m_f_148 < ((int)0)) ? ((int)0) : m_f_148) * ((t_sample)3.1415926535898)), samplerate));
			m_a_145 = safediv(((int)1), (m_w_146 + ((int)1)));
			m_a_144 = (m_w_146 - ((int)1));
			
		};
		t_sample outputHighShelfL = hishelfCore_d_d_d_d(sigL, m_a_145, m_a_144, m_b_147);
		t_sample outputHighShelfR = hishelfCore_d_d_d_d_154(sigR, m_a_145, m_a_144, m_b_147);
		out1 = outputHighShelfL;
		out2 = outputHighShelfR;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_145, t_sample m_a_144, t_sample m_b_147) {
		t_sample x = (m_a_145 * (input - (m_a_144 * m_z_153)));
		t_sample output = (x - m_z_153);
		m_z_153 = x;
		t_sample output_5767 = ((output * m_b_147) + input);
		return output_5767;
		
	};
	inline t_sample hishelfCore_d_d_d_d_154(t_sample input, t_sample m_a_145, t_sample m_a_144, t_sample m_b_147) {
		t_sample x = (m_a_145 * (input - (m_a_144 * m_z_155)));
		t_sample output = (x - m_z_155);
		m_z_155 = x;
		t_sample output_5767 = ((output * m_b_147) + input);
		return output_5767;
		
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
		case 2: self->set_c_size(value); break;
		case 3: self->set_d_damp(value); break;
		case 4: self->set_e_diffusion(value); break;
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
		case 0: *value = self->m_a_input_90; break;
		case 1: *value = self->m_b_drywet_91; break;
		case 2: *value = self->m_c_size_93; break;
		case 3: *value = self->m_d_damp_89; break;
		case 4: *value = self->m_e_diffusion_84; break;
		case 5: *value = self->m_f_st_94; break;
		case 6: *value = self->m_g_freeze_95; break;
		case 7: *value = self->m_h_lowGain_88; break;
		case 8: *value = self->m_i_peakGain_83; break;
		case 9: *value = self->m_j_hiGain_87; break;
		case 10: *value = self->m_k_lpf_92; break;
		case 11: *value = self->m_l_hpf_85; break;
		case 12: *value = self->m_m_output_86; break;
		
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
	// initialize parameter 0 ("m_a_input_90")
	pi = self->__commonstate.params + 0;
	pi->name = "a_input";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_input_90;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_drywet_91")
	pi = self->__commonstate.params + 1;
	pi->name = "b_drywet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_drywet_91;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_size_93")
	pi = self->__commonstate.params + 2;
	pi->name = "c_size";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_size_93;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 0.999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_damp_89")
	pi = self->__commonstate.params + 3;
	pi->name = "d_damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_damp_89;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_diffusion_84")
	pi = self->__commonstate.params + 4;
	pi->name = "e_diffusion";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_diffusion_84;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.01;
	pi->outputmax = 0.7;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_st_94")
	pi = self->__commonstate.params + 5;
	pi->name = "f_st";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_st_94;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_freeze_95")
	pi = self->__commonstate.params + 6;
	pi->name = "g_freeze";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_freeze_95;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_lowGain_88")
	pi = self->__commonstate.params + 7;
	pi->name = "h_lowGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_lowGain_88;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_i_peakGain_83")
	pi = self->__commonstate.params + 8;
	pi->name = "i_peakGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_i_peakGain_83;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_j_hiGain_87")
	pi = self->__commonstate.params + 9;
	pi->name = "j_hiGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_hiGain_87;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_lpf_92")
	pi = self->__commonstate.params + 10;
	pi->name = "k_lpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_lpf_92;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 500;
	pi->outputmax = 19000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_hpf_85")
	pi = self->__commonstate.params + 11;
	pi->name = "l_hpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_hpf_85;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_output_86")
	pi = self->__commonstate.params + 12;
	pi->name = "m_output";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_output_86;
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
