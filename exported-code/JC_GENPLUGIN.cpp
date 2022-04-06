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
	Change __m_change_172;
	Change __m_change_152;
	Change __m_change_173;
	Change __m_change_153;
	Change __m_change_151;
	Change __m_change_135;
	Change __m_change_134;
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
	t_sample m_w_130;
	t_sample m_w_makeup_123;
	t_sample m_history_126;
	t_sample m_o_peakFreq_124;
	t_sample m_r_onoffCOMP_125;
	t_sample m_q_onoffEQ_122;
	t_sample m_n_lowFreq_121;
	t_sample m_a_128;
	t_sample m_a_129;
	t_sample m_h_lowGain_120;
	t_sample m_a_input_119;
	t_sample m_l_hpf_116;
	t_sample m_t_ratio_117;
	t_sample m_b_drywet_106;
	t_sample m_i_peakGain_107;
	t_sample m_p_hiFreq_108;
	t_sample m_s_thd_105;
	t_sample m_f_st_103;
	t_sample m_c_reflect_104;
	t_sample m_history_102;
	t_sample m_g_freeze_118;
	t_sample m_j_hiGain_109;
	t_sample m_k_lpf_111;
	t_sample m_u_atk_115;
	t_sample m_b_131;
	t_sample m_d_damp_110;
	t_sample m_m_output_114;
	t_sample m_v_rel_112;
	t_sample m_e_size_113;
	t_sample m_f_132;
	t_sample m_w_150;
	t_sample m_z_136;
	t_sample m_z_163;
	t_sample m_a_166;
	t_sample m_z_162;
	t_sample m_z_160;
	t_sample m_z_161;
	t_sample m_z_158;
	t_sample m_a_167;
	t_sample m_b_169;
	t_sample m_z_177;
	t_sample m_w_168;
	t_sample m_z_175;
	t_sample m_f_170;
	t_sample m_b_171;
	t_sample m_b_133;
	t_sample m_z_157;
	t_sample m_z_155;
	t_sample m_a_143;
	t_sample m_w_144;
	t_sample m_a_142;
	t_sample m_z_138;
	t_sample m_a_141;
	t_sample m_z_156;
	t_sample m_wq_145;
	t_sample m_d_147;
	t_sample m_history_101;
	t_sample m_d_146;
	t_sample m_b_149;
	t_sample m_d_148;
	t_sample m_history_100;
	t_sample m_history_83;
	t_sample m_history_98;
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
	t_sample m_history_99;
	t_sample m_history_65;
	t_sample m_history_67;
	t_sample m_history_88;
	t_sample m_history_89;
	t_sample m_history_90;
	t_sample m_history_87;
	t_sample m_history_85;
	t_sample m_history_86;
	t_sample m_history_84;
	t_sample m_history_91;
	t_sample m_history_93;
	t_sample m_history_97;
	t_sample m_history_92;
	t_sample m_history_96;
	t_sample m_history_94;
	t_sample m_history_95;
	t_sample m_history_66;
	t_sample __m_slide_185;
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
	t_sample __m_slide_188;
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
        
		m_f_st_103 = 0.5;
		m_c_reflect_104 = 0.86;
		m_s_thd_105 = -12;
		m_b_drywet_106 = 0.33;
		m_i_peakGain_107 = 0;
		m_p_hiFreq_108 = 2000;
		m_j_hiGain_109 = 0;
		m_d_damp_110 = 0.8;
		m_k_lpf_111 = 20000;
		m_v_rel_112 = 100;
		m_e_size_113 = 1;
		m_m_output_114 = 1;
		m_u_atk_115 = 25;
		m_l_hpf_116 = 20;
		m_t_ratio_117 = 2;
		m_g_freeze_118 = 0;
		m_a_input_119 = 1;
		m_h_lowGain_120 = 0;
		m_n_lowFreq_121 = 500;
		m_q_onoffEQ_122 = 0;
		m_w_makeup_123 = 0;
		m_o_peakFreq_124 = 800;
		m_r_onoffCOMP_125 = 0;
        
		m_history_126 = ((int)0);
		m_a_128 = ((int)0);
		m_a_129 = ((int)0);
		m_w_130 = ((int)0);
		m_b_131 = ((int)0);
		m_f_132 = ((int)0);
		m_b_133 = ((int)0);
		__m_change_134.reset(0);
		__m_change_135.reset(0);
		m_z_136 = ((int)0);
		m_z_138 = ((int)0);
		m_a_141 = ((int)0);
		m_a_142 = ((int)0);
		m_a_143 = ((int)0);
		m_w_144 = ((int)0);
		m_wq_145 = ((int)0);
		m_d_146 = ((int)0);
		m_d_147 = ((int)0);
		m_d_148 = ((int)0);
		m_b_149 = ((int)0);
		m_w_150 = ((int)0);
		__m_change_151.reset(0);
		__m_change_152.reset(0);
		__m_change_153.reset(0);
		m_z_155 = ((int)0);
		m_z_156 = ((int)0);
		m_z_157 = ((int)0);
		m_z_158 = ((int)0);
		m_z_160 = ((int)0);
		m_z_161 = ((int)0);
		m_z_162 = ((int)0);
		m_z_163 = ((int)0);
		m_a_166 = ((int)0);
		m_a_167 = ((int)0);
		m_w_168 = ((int)0);
		m_b_169 = ((int)0);
		m_f_170 = ((int)0);
		m_b_171 = ((int)0);
		__m_change_172.reset(0);
		__m_change_173.reset(0);
		m_z_175 = ((int)0);
		m_z_177 = ((int)0);
		__m_slide_185 = 0;
		__m_slide_188 = 0;
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
		t_sample mul_2676 = (m_m_output_114 * ((t_sample)0.001));
		t_sample dbtoa_12754 = dbtoa(m_w_makeup_123);
		t_sample mul_12871 = (dbtoa_12754 * ((t_sample)0.001));
		t_sample mul_2808 = (m_b_drywet_106 * ((t_sample)0.001));
		t_sample mul_2504 = (m_q_onoffEQ_122 * ((t_sample)0.001));
		t_sample mul_2814 = (m_f_st_103 * ((t_sample)0.001));
		t_sample mul_2524 = (m_n_lowFreq_121 * ((t_sample)0.001));
		t_sample mul_2518 = (m_o_peakFreq_124 * ((t_sample)0.001));
		t_sample mul_2512 = (m_p_hiFreq_108 * ((t_sample)0.001));
		t_sample mul_2696 = (m_h_lowGain_120 * ((t_sample)0.001));
		t_sample mul_2690 = (m_i_peakGain_107 * ((t_sample)0.001));
		t_sample mul_2684 = (m_j_hiGain_109 * ((t_sample)0.001));
		t_sample mul_2802 = (m_a_input_119 * ((t_sample)0.001));
		t_sample mul_2534 = (m_e_size_113 * ((t_sample)0.001));
		t_sample mul_2708 = (m_k_lpf_111 * ((t_sample)0.001));
		t_sample mul_2702 = (m_l_hpf_116 * ((t_sample)0.001));
		t_sample rsub_2827 = (((t_sample)0.999) - m_c_reflect_104);
		t_sample mstosamps_6464 = (m_v_rel_112 * (samplerate * 0.001));
		t_sample mstosamps_6463 = (m_u_atk_115 * (samplerate * 0.001));
		t_sample iup_186 = (1 / maximum(1, abs(mstosamps_6464)));
		t_sample idown_187 = (1 / maximum(1, abs(mstosamps_6463)));
		t_sample mstosamps_2356 = (m_v_rel_112 * (samplerate * 0.001));
		t_sample mstosamps_2355 = (m_u_atk_115 * (samplerate * 0.001));
		t_sample iup_189 = (1 / maximum(1, abs(mstosamps_2356)));
		t_sample idown_190 = (1 / maximum(1, abs(mstosamps_2355)));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_2677 = (m_history_126 * ((t_sample)0.999));
			t_sample add_2679 = (mul_2676 + mul_2677);
			t_sample gen_2681 = add_2679;
			t_sample history_2678_next_2680 = fixdenorm(add_2679);
			t_sample mul_12872 = (m_history_102 * ((t_sample)0.999));
			t_sample add_12874 = (mul_12871 + mul_12872);
			t_sample gen_12876 = add_12874;
			t_sample history_12873_next_12875 = fixdenorm(add_12874);
			t_sample mul_2809 = (m_history_101 * ((t_sample)0.999));
			t_sample add_2811 = (mul_2808 + mul_2809);
			t_sample gen_2813 = add_2811;
			t_sample history_2810_next_2812 = fixdenorm(add_2811);
			t_sample dry_wet_2790 = gen_2813;
			t_sample mul_2665 = (m_history_100 * ((t_sample)0.999));
			t_sample mul_2664 = (dry_wet_2790 * ((t_sample)0.001));
			t_sample add_2667 = (mul_2664 + mul_2665);
			t_sample gen_2669 = add_2667;
			t_sample history_2666_next_2668 = fixdenorm(add_2667);
			int eq_2832 = (m_g_freeze_118 == ((int)1));
			int toSize_2751 = eq_2832;
			t_sample mul_2671 = (m_history_99 * ((t_sample)0.999));
			t_sample mul_2670 = (toSize_2751 * ((t_sample)0.001));
			t_sample add_2673 = (mul_2670 + mul_2671);
			t_sample gen_2675 = add_2673;
			t_sample history_2672_next_2674 = fixdenorm(add_2673);
			t_sample mul_2505 = (m_history_98 * ((t_sample)0.999));
			t_sample add_2507 = (mul_2504 + mul_2505);
			t_sample gen_2509 = add_2507;
			t_sample history_2506_next_2508 = fixdenorm(add_2507);
			t_sample onOffEQ_2503 = gen_2509;
			t_sample mul_2815 = (m_history_97 * ((t_sample)0.999));
			t_sample add_2817 = (mul_2814 + mul_2815);
			t_sample gen_2819 = add_2817;
			t_sample history_2816_next_2818 = fixdenorm(add_2817);
			t_sample sub_14187 = (gen_2819 - ((int)0));
			t_sample scale_14184 = ((safepow((sub_14187 * ((t_sample)1.25)), ((int)1)) * ((t_sample)0.293)) + ((t_sample)0.707));
			t_sample scale_2785 = scale_14184;
			t_sample mul_2525 = (m_history_96 * ((t_sample)0.999));
			t_sample add_2527 = (mul_2524 + mul_2525);
			t_sample gen_2529 = add_2527;
			t_sample history_2526_next_2528 = fixdenorm(add_2527);
			t_sample mul_2519 = (m_history_95 * ((t_sample)0.999));
			t_sample add_2521 = (mul_2518 + mul_2519);
			t_sample gen_2523 = add_2521;
			t_sample history_2520_next_2522 = fixdenorm(add_2521);
			t_sample mul_2513 = (m_history_94 * ((t_sample)0.999));
			t_sample add_2515 = (mul_2512 + mul_2513);
			t_sample gen_2517 = add_2515;
			t_sample history_2514_next_2516 = fixdenorm(add_2515);
			t_sample mul_2697 = (m_history_93 * ((t_sample)0.999));
			t_sample add_2699 = (mul_2696 + mul_2697);
			t_sample gen_2701 = add_2699;
			t_sample history_2698_next_2700 = fixdenorm(add_2699);
			t_sample mul_2691 = (m_history_92 * ((t_sample)0.999));
			t_sample add_2693 = (mul_2690 + mul_2691);
			t_sample gen_2695 = add_2693;
			t_sample history_2692_next_2694 = fixdenorm(add_2693);
			t_sample mul_2685 = (m_history_91 * ((t_sample)0.999));
			t_sample add_2687 = (mul_2684 + mul_2685);
			t_sample gen_2689 = add_2687;
			t_sample history_2686_next_2688 = fixdenorm(add_2687);
			t_sample mul_2803 = (m_history_90 * ((t_sample)0.999));
			t_sample add_2805 = (mul_2802 + mul_2803);
			t_sample gen_2807 = add_2805;
			t_sample history_2804_next_2806 = fixdenorm(add_2805);
			t_sample input_2733 = gen_2807;
			t_sample mul_2732 = (in2 * input_2733);
			t_sample right_2752 = mul_2732;
			t_sample right_2787 = right_2752;
			t_sample right_2754 = right_2752;
			int eq_2761 = (right_2754 == ((int)0));
			t_sample mul_2742 = (m_history_89 * ((t_sample)0.999));
			t_sample mul_2741 = (eq_2761 * ((t_sample)0.001));
			t_sample add_2744 = (mul_2741 + mul_2742);
			t_sample gen_2746 = add_2744;
			t_sample history_2743_next_2745 = fixdenorm(add_2744);
			t_sample mul_2734 = (in1 * input_2733);
			t_sample left_2782 = mul_2734;
			t_sample left_2788 = left_2782;
			t_sample mix_14188 = (left_2788 + (gen_2675 * (((int)0) - left_2788)));
			t_sample left_2758 = left_2782;
			t_sample mix_14189 = (((int)0) + (gen_2746 * (left_2758 - ((int)0))));
			t_sample mix_2757 = mix_14189;
			t_sample add_14191 = (mix_2757 + right_2787);
			t_sample mix_14190 = (add_14191 + (gen_2675 * (((int)0) - add_14191)));
			t_sample sqrt_2794 = sqrt(gen_2819);
			t_sample rsub_2820 = (((int)1) - gen_2819);
			t_sample sqrt_2795 = sqrt(rsub_2820);
			t_sample rsub_3181 = (((int)1) - m_d_damp_110);
			t_sample damp_2822 = rsub_3181;
			t_sample damp_2821 = damp_2822;
			t_sample mul_2535 = (m_history_88 * ((t_sample)0.999));
			t_sample add_2537 = (mul_2534 + mul_2535);
			t_sample gen_2539 = add_2537;
			t_sample history_2536_next_2538 = fixdenorm(add_2537);
			t_sample escala_Size_2662 = gen_2539;
			t_sample escala_Size_2661 = escala_Size_2662;
			t_sample escala_Size_2601 = escala_Size_2662;
			t_sample escala_Size_2663 = escala_Size_2662;
			t_sample mul_2709 = (m_history_87 * ((t_sample)0.999));
			t_sample add_2711 = (mul_2708 + mul_2709);
			t_sample gen_2713 = add_2711;
			t_sample history_2710_next_2712 = fixdenorm(add_2711);
			t_sample mul_2703 = (m_history_86 * ((t_sample)0.999));
			t_sample add_2705 = (mul_2702 + mul_2703);
			t_sample gen_2707 = add_2705;
			t_sample history_2704_next_2706 = fixdenorm(add_2705);
			t_sample toMoud_2762 = gen_2819;
			int toSize_2825 = toSize_2751;
			int choice_127 = toSize_2825;
			t_sample gate_2826 = ((choice_127 >= 1) ? rsub_2827 : 0);
			t_sample add_2828 = (m_c_reflect_104 + gate_2826);
			t_sample mul_2770 = (m_history_85 * ((t_sample)0.999));
			t_sample mul_2769 = (add_2828 * ((t_sample)0.001));
			t_sample add_2772 = (mul_2769 + mul_2770);
			t_sample gen_2774 = add_2772;
			t_sample history_2771_next_2773 = fixdenorm(add_2772);
			t_sample escala_Size_2542 = escala_Size_2662;
			t_sample mul_2540 = (((int)12) * escala_Size_2542);
			t_sample right_2781 = right_2752;
			t_sample left_2753 = left_2782;
			int eq_2755 = (left_2753 == right_2752);
			t_sample mul_2736 = (m_history_84 * ((t_sample)0.999));
			t_sample mul_2735 = (eq_2755 * ((t_sample)0.001));
			t_sample add_2738 = (mul_2735 + mul_2736);
			t_sample gen_2740 = add_2738;
			t_sample history_2737_next_2739 = fixdenorm(add_2738);
			t_sample add_14193 = (gen_2740 + gen_2746);
			t_sample mix_14192 = (((int)0) + (add_14193 * (toMoud_2762 - ((int)0))));
			t_sample mix_2760 = mix_14192;
			t_sample mix_14194 = (((int)0) + (mix_2760 * ((int)0)));
			t_sample mix_2778 = mix_14194;
			t_sample zeroL_2823 = mix_2778;
			t_sample mix_14195 = (((int)0) + (mix_2760 * (mul_2540 - ((int)0))));
			t_sample mix_2776 = mix_14195;
			t_sample zeroR_2824 = mix_2776;
			int rsub_2831 = (((int)1) - eq_2832);
			t_sample mul_2764 = (m_history_83 * ((t_sample)0.999));
			t_sample mul_2763 = (rsub_2831 * ((t_sample)0.001));
			t_sample add_2766 = (mul_2763 + mul_2764);
			t_sample gen_2768 = add_2766;
			t_sample history_2765_next_2767 = fixdenorm(add_2766);
			t_sample freeze_2800 = gen_2768;
			t_sample mul_2801 = ((mix_2757 + right_2781) * freeze_2800);
			t_sample toFILTERS_c45R_2408 = mul_2801;
			t_sample freeze_2829 = freeze_2800;
			t_sample mul_2830 = (left_2782 * freeze_2829);
			t_sample toFILTERS_c45L_2409 = mul_2830;
			t_sample omega = safediv((gen_2707 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn = sin(omega);
			t_sample cs = cos(omega);
			t_sample alpha = ((sn * ((t_sample)0.5)) * ((t_sample)1));
			t_sample b0 = safediv(((int)1), (((int)1) + alpha));
			t_sample a2 = (((((int)1) + cs) * ((t_sample)0.5)) * b0);
			t_sample a1 = ((-(((int)1) + cs)) * b0);
			t_sample b1 = ((((int)-2) * cs) * b0);
			t_sample b2 = ((((int)1) - alpha) * b0);
			t_sample expr_2482 = a2;
			t_sample expr_2483 = a1;
			t_sample expr_2484 = a2;
			t_sample expr_2485 = b1;
			t_sample expr_2486 = b2;
			t_sample omega_2494 = safediv((gen_2713 * ((t_sample)6.2831853071796)), samplerate);
			t_sample sn_2492 = sin(omega_2494);
			t_sample cs_2499 = cos(omega_2494);
			t_sample alpha_2500 = ((sn_2492 * ((t_sample)0.5)) * ((int)1));
			t_sample b_2497 = safediv(((int)1), (((int)1) + alpha_2500));
			t_sample a_2498 = (((((int)1) - cs_2499) * ((t_sample)0.5)) * b_2497);
			t_sample a_2493 = ((((int)1) - cs_2499) * b_2497);
			t_sample b_2496 = ((((int)-2) * cs_2499) * b_2497);
			t_sample b_2495 = ((((int)1) - alpha_2500) * b_2497);
			t_sample expr_2487 = a_2498;
			t_sample expr_2488 = a_2493;
			t_sample expr_2489 = a_2498;
			t_sample expr_2490 = b_2496;
			t_sample expr_2491 = b_2495;
			t_sample mul_2471 = (toFILTERS_c45L_2409 * expr_2487);
			t_sample mul_2461 = (toFILTERS_c45R_2408 * expr_2487);
			t_sample mul_2468 = (m_history_78 * expr_2488);
			t_sample mul_2458 = (m_history_77 * expr_2488);
			t_sample mul_2466 = (m_history_82 * expr_2489);
			t_sample mul_2456 = (m_history_79 * expr_2489);
			t_sample mul_2462 = (m_history_81 * expr_2491);
			t_sample mul_2452 = (m_history_80 * expr_2491);
			t_sample mul_2464 = (m_history_76 * expr_2490);
			t_sample sub_2470 = (((mul_2466 + mul_2468) + mul_2471) - (mul_2464 + mul_2462));
			t_sample gen_2480 = sub_2470;
			t_sample mul_2454 = (m_history_75 * expr_2490);
			t_sample sub_2460 = (((mul_2461 + mul_2458) + mul_2456) - (mul_2454 + mul_2452));
			t_sample gen_2481 = sub_2460;
			t_sample history_2467_next_2472 = fixdenorm(m_history_78);
			t_sample history_2463_next_2473 = fixdenorm(m_history_76);
			t_sample history_2453_next_2474 = fixdenorm(m_history_75);
			t_sample history_2457_next_2475 = fixdenorm(m_history_77);
			t_sample history_2469_next_2476 = fixdenorm(toFILTERS_c45L_2409);
			t_sample history_2459_next_2477 = fixdenorm(toFILTERS_c45R_2408);
			t_sample history_2465_next_2478 = fixdenorm(sub_2470);
			t_sample history_2455_next_2479 = fixdenorm(sub_2460);
			t_sample mul_2436 = (gen_2480 * expr_2482);
			t_sample mul_2426 = (gen_2481 * expr_2482);
			t_sample mul_2433 = (m_history_70 * expr_2483);
			t_sample mul_2423 = (m_history_69 * expr_2483);
			t_sample mul_2431 = (m_history_74 * expr_2484);
			t_sample mul_2421 = (m_history_72 * expr_2484);
			t_sample mul_2427 = (m_history_73 * expr_2486);
			t_sample mul_2417 = (m_history_71 * expr_2486);
			t_sample mul_2429 = (m_history_68 * expr_2485);
			t_sample sub_2435 = (((mul_2431 + mul_2433) + mul_2436) - (mul_2429 + mul_2427));
			t_sample gen_2445 = sub_2435;
			t_sample mul_2419 = (m_history_67 * expr_2485);
			t_sample sub_2425 = (((mul_2426 + mul_2423) + mul_2421) - (mul_2419 + mul_2417));
			t_sample gen_2446 = sub_2425;
			t_sample history_2432_next_2437 = fixdenorm(m_history_70);
			t_sample history_2428_next_2438 = fixdenorm(m_history_68);
			t_sample history_2422_next_2439 = fixdenorm(m_history_69);
			t_sample history_2418_next_2440 = fixdenorm(m_history_67);
			t_sample history_2434_next_2441 = fixdenorm(gen_2480);
			t_sample history_2424_next_2442 = fixdenorm(gen_2481);
			t_sample history_2430_next_2443 = fixdenorm(sub_2435);
			t_sample history_2420_next_2444 = fixdenorm(sub_2425);
			t_sample gen_2502 = gen_2446;
			t_sample gen_2501 = gen_2445;
			t_sample fromFILTERS_c45L_2411 = gen_2501;
			t_sample rsub_3080 = (((int)1) - damp_2822);
			t_sample div_3069 = (samplerate * ((t_sample)2.2675736961451e-05));
			t_sample mul_3054 = (div_3069 * escala_Size_2663);
			t_sample mul_3057 = (((int)1188) * mul_3054);
			t_sample mul_3013 = (m_history_66 * ((t_sample)0.999));
			t_sample mul_3012 = (mul_3057 * ((t_sample)0.001));
			t_sample add_3015 = (mul_3012 + mul_3013);
			t_sample gen_3017 = add_3015;
			t_sample history_3014_next_3016 = fixdenorm(add_3015);
			t_sample gen_3078 = gen_3017;
			t_sample mul_3067 = (((int)1617) * mul_3054);
			t_sample mul_3043 = (m_history_65 * ((t_sample)0.999));
			t_sample mul_3042 = (mul_3067 * ((t_sample)0.001));
			t_sample add_3045 = (mul_3042 + mul_3043);
			t_sample gen_3047 = add_3045;
			t_sample history_3044_next_3046 = fixdenorm(add_3045);
			t_sample gen_3073 = gen_3047;
			t_sample mul_3065 = (((int)1491) * mul_3054);
			t_sample mul_3037 = (m_history_64 * ((t_sample)0.999));
			t_sample mul_3036 = (mul_3065 * ((t_sample)0.001));
			t_sample add_3039 = (mul_3036 + mul_3037);
			t_sample gen_3041 = add_3039;
			t_sample history_3038_next_3040 = fixdenorm(add_3039);
			t_sample gen_3074 = gen_3041;
			t_sample mul_3059 = (((int)1356) * mul_3054);
			t_sample mul_3019 = (m_history_63 * ((t_sample)0.999));
			t_sample mul_3018 = (mul_3059 * ((t_sample)0.001));
			t_sample add_3021 = (mul_3018 + mul_3019);
			t_sample gen_3023 = add_3021;
			t_sample history_3020_next_3022 = fixdenorm(add_3021);
			t_sample gen_3077 = gen_3023;
			t_sample mul_3055 = (((int)1116) * mul_3054);
			t_sample mul_3007 = (m_history_62 * ((t_sample)0.999));
			t_sample mul_3006 = (mul_3055 * ((t_sample)0.001));
			t_sample add_3009 = (mul_3006 + mul_3007);
			t_sample gen_3011 = add_3009;
			t_sample history_3008_next_3010 = fixdenorm(add_3009);
			t_sample gen_3079 = gen_3011;
			t_sample mul_3063 = (((int)1422) * mul_3054);
			t_sample mul_3031 = (m_history_61 * ((t_sample)0.999));
			t_sample mul_3030 = (mul_3063 * ((t_sample)0.001));
			t_sample add_3033 = (mul_3030 + mul_3031);
			t_sample gen_3035 = add_3033;
			t_sample history_3032_next_3034 = fixdenorm(add_3033);
			t_sample gen_3075 = gen_3035;
			t_sample mul_3061 = (((int)1277) * mul_3054);
			t_sample mul_3025 = (m_history_60 * ((t_sample)0.999));
			t_sample mul_3024 = (mul_3061 * ((t_sample)0.001));
			t_sample add_3027 = (mul_3024 + mul_3025);
			t_sample gen_3029 = add_3027;
			t_sample history_3026_next_3028 = fixdenorm(add_3027);
			t_sample gen_3076 = gen_3029;
			t_sample mul_3070 = (((int)1557) * mul_3054);
			t_sample mul_3049 = (m_history_59 * ((t_sample)0.999));
			t_sample mul_3048 = (mul_3070 * ((t_sample)0.001));
			t_sample add_3051 = (mul_3048 + mul_3049);
			t_sample gen_3053 = add_3051;
			t_sample history_3050_next_3052 = fixdenorm(add_3051);
			t_sample gen_3072 = gen_3053;
			t_sample rsub_3082 = (((int)1) - rsub_3080);
			t_sample mul_3084 = (m_history_57 * rsub_3082);
			t_sample add_3081 = (zeroL_2823 + gen_3079);
			t_sample tap_3090 = m_delay_58.read_linear(add_3081);
			t_sample mul_3087 = (tap_3090 * rsub_3080);
			t_sample add_3086 = (mul_3087 + mul_3084);
			t_sample mul_3083 = (add_3086 * gen_2774);
			t_sample add_3088 = (fromFILTERS_c45L_2411 + mul_3083);
			t_sample gen_3092 = add_3088;
			t_sample history_3085_next_3091 = fixdenorm(add_3086);
			t_sample rsub_3094 = (((int)1) - rsub_3080);
			t_sample mul_3096 = (m_history_55 * rsub_3094);
			t_sample add_3093 = (zeroL_2823 + gen_3078);
			t_sample tap_3102 = m_delay_56.read_linear(add_3093);
			t_sample mul_3099 = (tap_3102 * rsub_3080);
			t_sample add_3098 = (mul_3099 + mul_3096);
			t_sample mul_3095 = (add_3098 * gen_2774);
			t_sample add_3100 = (fromFILTERS_c45L_2411 + mul_3095);
			t_sample gen_3104 = add_3100;
			t_sample history_3097_next_3103 = fixdenorm(add_3098);
			t_sample rsub_3106 = (((int)1) - rsub_3080);
			t_sample mul_3108 = (m_history_53 * rsub_3106);
			t_sample add_3105 = (zeroL_2823 + gen_3077);
			t_sample tap_3114 = m_delay_54.read_linear(add_3105);
			t_sample mul_3111 = (tap_3114 * rsub_3080);
			t_sample add_3110 = (mul_3111 + mul_3108);
			t_sample mul_3107 = (add_3110 * gen_2774);
			t_sample add_3112 = (fromFILTERS_c45L_2411 + mul_3107);
			t_sample gen_3116 = add_3112;
			t_sample history_3109_next_3115 = fixdenorm(add_3110);
			t_sample rsub_3118 = (((int)1) - rsub_3080);
			t_sample mul_3120 = (m_history_51 * rsub_3118);
			t_sample add_3117 = (zeroL_2823 + gen_3076);
			t_sample tap_3126 = m_delay_52.read_linear(add_3117);
			t_sample mul_3123 = (tap_3126 * rsub_3080);
			t_sample add_3122 = (mul_3123 + mul_3120);
			t_sample mul_3119 = (add_3122 * gen_2774);
			t_sample add_3124 = (fromFILTERS_c45L_2411 + mul_3119);
			t_sample gen_3128 = add_3124;
			t_sample history_3121_next_3127 = fixdenorm(add_3122);
			t_sample rsub_3130 = (((int)1) - rsub_3080);
			t_sample mul_3132 = (m_history_49 * rsub_3130);
			t_sample add_3129 = (zeroL_2823 + gen_3075);
			t_sample tap_3138 = m_delay_50.read_linear(add_3129);
			t_sample mul_3135 = (tap_3138 * rsub_3080);
			t_sample add_3134 = (mul_3135 + mul_3132);
			t_sample mul_3131 = (add_3134 * gen_2774);
			t_sample add_3136 = (fromFILTERS_c45L_2411 + mul_3131);
			t_sample gen_3140 = add_3136;
			t_sample history_3133_next_3139 = fixdenorm(add_3134);
			t_sample rsub_3142 = (((int)1) - rsub_3080);
			t_sample mul_3144 = (m_history_47 * rsub_3142);
			t_sample add_3141 = (zeroL_2823 + gen_3074);
			t_sample tap_3150 = m_delay_48.read_linear(add_3141);
			t_sample mul_3147 = (tap_3150 * rsub_3080);
			t_sample add_3146 = (mul_3147 + mul_3144);
			t_sample mul_3143 = (add_3146 * gen_2774);
			t_sample add_3148 = (fromFILTERS_c45L_2411 + mul_3143);
			t_sample gen_3152 = add_3148;
			t_sample history_3145_next_3151 = fixdenorm(add_3146);
			t_sample rsub_3154 = (((int)1) - rsub_3080);
			t_sample mul_3156 = (m_history_45 * rsub_3154);
			t_sample add_3153 = (zeroL_2823 + gen_3073);
			t_sample tap_3162 = m_delay_46.read_linear(add_3153);
			t_sample mul_3159 = (tap_3162 * rsub_3080);
			t_sample add_3158 = (mul_3159 + mul_3156);
			t_sample mul_3155 = (add_3158 * gen_2774);
			t_sample add_3160 = (fromFILTERS_c45L_2411 + mul_3155);
			t_sample gen_3164 = add_3160;
			t_sample history_3157_next_3163 = fixdenorm(add_3158);
			t_sample rsub_3166 = (((int)1) - rsub_3080);
			t_sample mul_3168 = (m_history_43 * rsub_3166);
			t_sample add_3165 = (zeroL_2823 + gen_3072);
			t_sample tap_3174 = m_delay_44.read_linear(add_3165);
			t_sample mul_3171 = (tap_3174 * rsub_3080);
			t_sample add_3170 = (mul_3171 + mul_3168);
			t_sample mul_3167 = (add_3170 * gen_2774);
			t_sample add_3172 = (fromFILTERS_c45L_2411 + mul_3167);
			t_sample gen_3176 = add_3172;
			t_sample history_3169_next_3175 = fixdenorm(add_3170);
			t_sample mul_3177 = ((((((((gen_3176 + gen_3164) + gen_3152) + gen_3140) + gen_3128) + gen_3116) + gen_3104) + gen_3092) * ((t_sample)0.125));
			t_sample gen_3178 = mul_3177;
			t_sample mul_2656 = (gen_3178 * ((t_sample)-0.5));
			t_sample div_2647 = (samplerate * ((t_sample)2.2675736961451e-05));
			t_sample mul_2646 = (div_2647 * escala_Size_2661);
			t_sample mul_2648 = (((int)255) * mul_2646);
			t_sample add_2650 = (((int)0) + mul_2648);
			t_sample tap_2658 = m_delay_42.read_linear(add_2650);
			t_sample tap_2653 = m_delay_41.read_linear(add_2650);
			t_sample mul_2651 = (tap_2653 * ((t_sample)0.5));
			t_sample add_2654 = (mul_2656 + (tap_2658 + mul_2651));
			t_sample gen_2659 = add_2654;
			t_sample mul_2642 = (gen_2659 * ((t_sample)-0.5));
			t_sample div_2633 = (samplerate * ((t_sample)2.2675736961451e-05));
			t_sample mul_2632 = (div_2633 * escala_Size_2661);
			t_sample mul_2634 = (((int)556) * mul_2632);
			t_sample add_2636 = (((int)0) + mul_2634);
			t_sample tap_2644 = m_delay_40.read_linear(add_2636);
			t_sample tap_2639 = m_delay_39.read_linear(add_2636);
			t_sample mul_2637 = (tap_2639 * ((t_sample)0.5));
			t_sample add_2640 = (mul_2642 + (tap_2644 + mul_2637));
			t_sample gen_2645 = add_2640;
			t_sample mul_2628 = (gen_2645 * ((t_sample)-0.5));
			t_sample div_2619 = (samplerate * ((t_sample)2.2675736961451e-05));
			t_sample mul_2618 = (div_2619 * escala_Size_2661);
			t_sample mul_2620 = (((int)441) * mul_2618);
			t_sample add_2622 = (((int)0) + mul_2620);
			t_sample tap_2630 = m_delay_38.read_linear(add_2622);
			t_sample tap_2625 = m_delay_37.read_linear(add_2622);
			t_sample mul_2623 = (tap_2625 * ((t_sample)0.5));
			t_sample add_2626 = (mul_2628 + (tap_2630 + mul_2623));
			t_sample gen_2631 = add_2626;
			t_sample mul_2614 = (gen_2631 * ((t_sample)-0.5));
			t_sample div_2605 = (samplerate * ((t_sample)2.2675736961451e-05));
			t_sample mul_2604 = (div_2605 * escala_Size_2661);
			t_sample mul_2606 = (((int)341) * mul_2604);
			t_sample add_2608 = (((int)0) + mul_2606);
			t_sample tap_2616 = m_delay_36.read_linear(add_2608);
			t_sample tap_2611 = m_delay_35.read_linear(add_2608);
			t_sample mul_2609 = (tap_2611 * ((t_sample)0.5));
			t_sample add_2612 = (mul_2614 + (tap_2616 + mul_2609));
			t_sample gen_2617 = add_2612;
			t_sample gen_2660 = gen_2617;
			t_sample matrizMS_c45L_2780 = gen_2660;
			t_sample fromFILTERS_c45R_2410 = gen_2502;
			t_sample rsub_2907 = (((int)1) - damp_2821);
			t_sample div_2896 = (samplerate * ((t_sample)2.2675736961451e-05));
			t_sample mul_2881 = (div_2896 * escala_Size_2662);
			t_sample mul_2884 = (((int)1188) * mul_2881);
			t_sample mul_2840 = (m_history_34 * ((t_sample)0.999));
			t_sample mul_2839 = (mul_2884 * ((t_sample)0.001));
			t_sample add_2842 = (mul_2839 + mul_2840);
			t_sample gen_2844 = add_2842;
			t_sample history_2841_next_2843 = fixdenorm(add_2842);
			t_sample gen_2905 = gen_2844;
			t_sample mul_2886 = (((int)1356) * mul_2881);
			t_sample mul_2846 = (m_history_33 * ((t_sample)0.999));
			t_sample mul_2845 = (mul_2886 * ((t_sample)0.001));
			t_sample add_2848 = (mul_2845 + mul_2846);
			t_sample gen_2850 = add_2848;
			t_sample history_2847_next_2849 = fixdenorm(add_2848);
			t_sample gen_2904 = gen_2850;
			t_sample mul_2897 = (((int)1557) * mul_2881);
			t_sample mul_2876 = (m_history_32 * ((t_sample)0.999));
			t_sample mul_2875 = (mul_2897 * ((t_sample)0.001));
			t_sample add_2878 = (mul_2875 + mul_2876);
			t_sample gen_2880 = add_2878;
			t_sample history_2877_next_2879 = fixdenorm(add_2878);
			t_sample gen_2899 = gen_2880;
			t_sample mul_2882 = (((int)1116) * mul_2881);
			t_sample mul_2834 = (m_history_31 * ((t_sample)0.999));
			t_sample mul_2833 = (mul_2882 * ((t_sample)0.001));
			t_sample add_2836 = (mul_2833 + mul_2834);
			t_sample gen_2838 = add_2836;
			t_sample history_2835_next_2837 = fixdenorm(add_2836);
			t_sample gen_2906 = gen_2838;
			t_sample mul_2894 = (((int)1617) * mul_2881);
			t_sample mul_2870 = (m_history_30 * ((t_sample)0.999));
			t_sample mul_2869 = (mul_2894 * ((t_sample)0.001));
			t_sample add_2872 = (mul_2869 + mul_2870);
			t_sample gen_2874 = add_2872;
			t_sample history_2871_next_2873 = fixdenorm(add_2872);
			t_sample gen_2900 = gen_2874;
			t_sample mul_2890 = (((int)1422) * mul_2881);
			t_sample mul_2858 = (m_history_29 * ((t_sample)0.999));
			t_sample mul_2857 = (mul_2890 * ((t_sample)0.001));
			t_sample add_2860 = (mul_2857 + mul_2858);
			t_sample gen_2862 = add_2860;
			t_sample history_2859_next_2861 = fixdenorm(add_2860);
			t_sample gen_2902 = gen_2862;
			t_sample mul_2888 = (((int)1277) * mul_2881);
			t_sample mul_2852 = (m_history_28 * ((t_sample)0.999));
			t_sample mul_2851 = (mul_2888 * ((t_sample)0.001));
			t_sample add_2854 = (mul_2851 + mul_2852);
			t_sample gen_2856 = add_2854;
			t_sample history_2853_next_2855 = fixdenorm(add_2854);
			t_sample gen_2903 = gen_2856;
			t_sample mul_2892 = (((int)1491) * mul_2881);
			t_sample mul_2864 = (m_history_27 * ((t_sample)0.999));
			t_sample mul_2863 = (mul_2892 * ((t_sample)0.001));
			t_sample add_2866 = (mul_2863 + mul_2864);
			t_sample gen_2868 = add_2866;
			t_sample history_2865_next_2867 = fixdenorm(add_2866);
			t_sample gen_2901 = gen_2868;
			t_sample rsub_2909 = (((int)1) - rsub_2907);
			t_sample mul_2911 = (m_history_25 * rsub_2909);
			t_sample add_2908 = (zeroR_2824 + gen_2906);
			t_sample tap_2917 = m_delay_26.read_linear(add_2908);
			t_sample mul_2914 = (tap_2917 * rsub_2907);
			t_sample add_2913 = (mul_2914 + mul_2911);
			t_sample mul_2910 = (add_2913 * gen_2774);
			t_sample add_2915 = (fromFILTERS_c45R_2410 + mul_2910);
			t_sample gen_2919 = add_2915;
			t_sample history_2912_next_2918 = fixdenorm(add_2913);
			t_sample rsub_2921 = (((int)1) - rsub_2907);
			t_sample mul_2923 = (m_history_23 * rsub_2921);
			t_sample add_2920 = (zeroR_2824 + gen_2905);
			t_sample tap_2929 = m_delay_24.read_linear(add_2920);
			t_sample mul_2926 = (tap_2929 * rsub_2907);
			t_sample add_2925 = (mul_2926 + mul_2923);
			t_sample mul_2922 = (add_2925 * gen_2774);
			t_sample add_2927 = (fromFILTERS_c45R_2410 + mul_2922);
			t_sample gen_2931 = add_2927;
			t_sample history_2924_next_2930 = fixdenorm(add_2925);
			t_sample rsub_2933 = (((int)1) - rsub_2907);
			t_sample mul_2935 = (m_history_21 * rsub_2933);
			t_sample add_2932 = (zeroR_2824 + gen_2904);
			t_sample tap_2941 = m_delay_22.read_linear(add_2932);
			t_sample mul_2938 = (tap_2941 * rsub_2907);
			t_sample add_2937 = (mul_2938 + mul_2935);
			t_sample mul_2934 = (add_2937 * gen_2774);
			t_sample add_2939 = (fromFILTERS_c45R_2410 + mul_2934);
			t_sample gen_2943 = add_2939;
			t_sample history_2936_next_2942 = fixdenorm(add_2937);
			t_sample rsub_2945 = (((int)1) - rsub_2907);
			t_sample mul_2947 = (m_history_19 * rsub_2945);
			t_sample add_2944 = (zeroR_2824 + gen_2903);
			t_sample tap_2953 = m_delay_20.read_linear(add_2944);
			t_sample mul_2950 = (tap_2953 * rsub_2907);
			t_sample add_2949 = (mul_2950 + mul_2947);
			t_sample mul_2946 = (add_2949 * gen_2774);
			t_sample add_2951 = (fromFILTERS_c45R_2410 + mul_2946);
			t_sample gen_2955 = add_2951;
			t_sample history_2948_next_2954 = fixdenorm(add_2949);
			t_sample rsub_2957 = (((int)1) - rsub_2907);
			t_sample mul_2959 = (m_history_17 * rsub_2957);
			t_sample add_2956 = (zeroR_2824 + gen_2902);
			t_sample tap_2965 = m_delay_18.read_linear(add_2956);
			t_sample mul_2962 = (tap_2965 * rsub_2907);
			t_sample add_2961 = (mul_2962 + mul_2959);
			t_sample mul_2958 = (add_2961 * gen_2774);
			t_sample add_2963 = (fromFILTERS_c45R_2410 + mul_2958);
			t_sample gen_2967 = add_2963;
			t_sample history_2960_next_2966 = fixdenorm(add_2961);
			t_sample rsub_2969 = (((int)1) - rsub_2907);
			t_sample mul_2971 = (m_history_15 * rsub_2969);
			t_sample add_2968 = (zeroR_2824 + gen_2901);
			t_sample tap_2977 = m_delay_16.read_linear(add_2968);
			t_sample mul_2974 = (tap_2977 * rsub_2907);
			t_sample add_2973 = (mul_2974 + mul_2971);
			t_sample mul_2970 = (add_2973 * gen_2774);
			t_sample add_2975 = (fromFILTERS_c45R_2410 + mul_2970);
			t_sample gen_2979 = add_2975;
			t_sample history_2972_next_2978 = fixdenorm(add_2973);
			t_sample rsub_2981 = (((int)1) - rsub_2907);
			t_sample mul_2983 = (m_history_13 * rsub_2981);
			t_sample add_2980 = (zeroR_2824 + gen_2900);
			t_sample tap_2989 = m_delay_14.read_linear(add_2980);
			t_sample mul_2986 = (tap_2989 * rsub_2907);
			t_sample add_2985 = (mul_2986 + mul_2983);
			t_sample mul_2982 = (add_2985 * gen_2774);
			t_sample add_2987 = (fromFILTERS_c45R_2410 + mul_2982);
			t_sample gen_2991 = add_2987;
			t_sample history_2984_next_2990 = fixdenorm(add_2985);
			t_sample rsub_2993 = (((int)1) - rsub_2907);
			t_sample mul_2995 = (m_history_11 * rsub_2993);
			t_sample add_2992 = (zeroR_2824 + gen_2899);
			t_sample tap_3001 = m_delay_12.read_linear(add_2992);
			t_sample mul_2998 = (tap_3001 * rsub_2907);
			t_sample add_2997 = (mul_2998 + mul_2995);
			t_sample mul_2994 = (add_2997 * gen_2774);
			t_sample add_2999 = (fromFILTERS_c45R_2410 + mul_2994);
			t_sample gen_3003 = add_2999;
			t_sample history_2996_next_3002 = fixdenorm(add_2997);
			t_sample mul_3004 = ((((((((gen_3003 + gen_2991) + gen_2979) + gen_2967) + gen_2955) + gen_2943) + gen_2931) + gen_2919) * ((t_sample)0.125));
			t_sample gen_3005 = mul_3004;
			t_sample mul_2596 = (gen_3005 * ((t_sample)-0.5));
			t_sample div_2587 = (samplerate * ((t_sample)2.2675736961451e-05));
			t_sample mul_2586 = (div_2587 * escala_Size_2601);
			t_sample mul_2588 = (((int)255) * mul_2586);
			t_sample add_2590 = (((int)0) + mul_2588);
			t_sample tap_2598 = m_delay_10.read_linear(add_2590);
			t_sample tap_2593 = m_delay_9.read_linear(add_2590);
			t_sample mul_2591 = (tap_2593 * ((t_sample)0.5));
			t_sample add_2594 = (mul_2596 + (tap_2598 + mul_2591));
			t_sample gen_2599 = add_2594;
			t_sample mul_2582 = (gen_2599 * ((t_sample)-0.5));
			t_sample div_2573 = (samplerate * ((t_sample)2.2675736961451e-05));
			t_sample mul_2572 = (div_2573 * escala_Size_2601);
			t_sample mul_2574 = (((int)556) * mul_2572);
			t_sample add_2576 = (((int)0) + mul_2574);
			t_sample tap_2584 = m_delay_8.read_linear(add_2576);
			t_sample tap_2579 = m_delay_7.read_linear(add_2576);
			t_sample mul_2577 = (tap_2579 * ((t_sample)0.5));
			t_sample add_2580 = (mul_2582 + (tap_2584 + mul_2577));
			t_sample gen_2585 = add_2580;
			t_sample mul_2568 = (gen_2585 * ((t_sample)-0.5));
			t_sample div_2559 = (samplerate * ((t_sample)2.2675736961451e-05));
			t_sample mul_2558 = (div_2559 * escala_Size_2601);
			t_sample mul_2560 = (((int)441) * mul_2558);
			t_sample add_2562 = (((int)0) + mul_2560);
			t_sample tap_2570 = m_delay_6.read_linear(add_2562);
			t_sample tap_2565 = m_delay_5.read_linear(add_2562);
			t_sample mul_2563 = (tap_2565 * ((t_sample)0.5));
			t_sample add_2566 = (mul_2568 + (tap_2570 + mul_2563));
			t_sample gen_2571 = add_2566;
			t_sample mul_2554 = (gen_2571 * ((t_sample)-0.5));
			t_sample div_2545 = (samplerate * ((t_sample)2.2675736961451e-05));
			t_sample mul_2544 = (div_2545 * escala_Size_2601);
			t_sample mul_2546 = (((int)341) * mul_2544);
			t_sample add_2548 = (((int)0) + mul_2546);
			t_sample tap_2556 = m_delay_4.read_linear(add_2548);
			t_sample tap_2551 = m_delay_3.read_linear(add_2548);
			t_sample mul_2549 = (tap_2551 * ((t_sample)0.5));
			t_sample add_2552 = (mul_2554 + (tap_2556 + mul_2549));
			t_sample gen_2557 = add_2552;
			t_sample gen_2600 = gen_2557;
			t_sample matrizMS_c45R_2779 = gen_2600;
			t_sample add_2799 = (matrizMS_c45L_2780 + matrizMS_c45R_2779);
			t_sample mul_2797 = (add_2799 * sqrt_2795);
			t_sample sub_2798 = (matrizMS_c45L_2780 - matrizMS_c45R_2779);
			t_sample mul_2796 = (sub_2798 * sqrt_2794);
			t_sample add_2793 = (mul_2797 + mul_2796);
			t_sample mul_2784 = (add_2793 * scale_2785);
			t_sample filterL_2531 = mul_2784;
			t_sample sub_2792 = (mul_2797 - mul_2796);
			t_sample mul_2783 = (sub_2792 * scale_2785);
			t_sample filterR_2530 = mul_2783;
			t_sample return_180;
			t_sample return_181;
			eq3bandas_d_d_d_d_d_d_d_d_i(filterL_2531, filterR_2530, gen_2529, gen_2523, gen_2517, gen_2701, gen_2695, gen_2689, ((int)1), return_180, return_181);
			t_sample expr_2728 = return_180;
			t_sample expr_2729 = return_181;
			t_sample gen_2730 = expr_2728;
			t_sample fromFilterL_2533 = gen_2730;
			t_sample mix_14196 = (mul_2784 + (onOffEQ_2503 * (fromFilterL_2533 - mul_2784)));
			t_sample mix_2511 = mix_14196;
			t_sample mix_14197 = (mul_2783 + (onOffEQ_2503 * (expr_2729 - mul_2783)));
			t_sample add_8311 = (m_r_onoffCOMP_125 + ((int)1));
			t_sample choice_182 = int(add_8311);
			t_sample gate_8119 = (((choice_182 >= 1) && (choice_182 < 2)) ? mix_2511 : 0);
			t_sample gate_8120 = ((choice_182 >= 2) ? mix_2511 : 0);
			t_sample add_8756 = (m_r_onoffCOMP_125 + ((int)1));
			t_sample choice_183 = int(add_8756);
			t_sample gate_8757 = (((choice_183 >= 1) && (choice_183 < 2)) ? mix_14197 : 0);
			t_sample gate_8758 = ((choice_183 >= 2) ? mix_14197 : 0);
			t_sample tap_6460 = m_delay_2.read_step(((int)300));
			t_sample mul_6453 = (gate_8120 * gate_8120);
			t_sample add_6457 = (m_history_1 + mul_6453);
			t_sample sub_6456 = (add_6457 - tap_6460);
			t_sample div_6454 = (sub_6456 * ((t_sample)0.0033333333333333));
			t_sample sqrt_6452 = sqrt(div_6454);
			t_sample history_6455_next_6461 = fixdenorm(sub_6456);
			t_sample atodb_6473 = atodb(sqrt_6452);
			int min_184 = (-70);
			t_sample clamp_6733 = ((atodb_6473 <= min_184) ? min_184 : ((atodb_6473 >= ((int)0)) ? ((int)0) : atodb_6473));
			int gt_6472 = (clamp_6733 > m_s_thd_105);
			t_sample sub_6471 = (m_s_thd_105 - clamp_6733);
			t_sample rdiv_6470 = safediv(((int)1), m_t_ratio_117);
			t_sample rsub_6469 = (((int)1) - rdiv_6470);
			t_sample mul_6468 = (sub_6471 * rsub_6469);
			t_sample dbtoa_6466 = dbtoa(mul_6468);
			t_sample orange_14200 = (dbtoa_6466 - ((int)1));
			int sub_14201 = (gt_6472 - ((int)0));
			t_sample scale_14198 = ((safepow((sub_14201 * ((t_sample)1)), ((int)1)) * orange_14200) + ((int)1));
			__m_slide_185 = fixdenorm((__m_slide_185 + (((scale_14198 > __m_slide_185) ? iup_186 : idown_187) * (scale_14198 - __m_slide_185))));
			t_sample slide_6465 = __m_slide_185;
			t_sample mul_6474 = (gate_8120 * slide_6465);
			t_sample mul_13346 = (mul_6474 * gen_12876);
			t_sample mix_14202 = (gate_8119 + (m_r_onoffCOMP_125 * (mul_13346 - gate_8119)));
			int gt_2364 = (clamp_6733 > m_s_thd_105);
			t_sample sub_2363 = (m_s_thd_105 - clamp_6733);
			t_sample rdiv_2362 = safediv(((int)1), m_t_ratio_117);
			t_sample rsub_2361 = (((int)1) - rdiv_2362);
			t_sample mul_2360 = (sub_2363 * rsub_2361);
			t_sample dbtoa_2358 = dbtoa(mul_2360);
			t_sample orange_14205 = (dbtoa_2358 - ((int)1));
			int sub_14206 = (gt_2364 - ((int)0));
			t_sample scale_14203 = ((safepow((sub_14206 * ((t_sample)1)), ((int)1)) * orange_14205) + ((int)1));
			__m_slide_188 = fixdenorm((__m_slide_188 + (((scale_14203 > __m_slide_188) ? iup_189 : idown_190) * (scale_14203 - __m_slide_188))));
			t_sample slide_2357 = __m_slide_188;
			t_sample mul_2377 = (gate_8758 * slide_2357);
			t_sample mul_13345 = (mul_2377 * gen_12876);
			t_sample mix_14207 = (gate_8757 + (m_r_onoffCOMP_125 * (mul_13345 - gate_8757)));
			t_sample mix_14208 = (mix_14190 + (gen_2669 * (mix_14207 - mix_14190)));
			t_sample mul_2682 = (mix_14208 * gen_2681);
			t_sample out2 = mul_2682;
			t_sample mix_14209 = (mix_14188 + (gen_2669 * (mix_14202 - mix_14188)));
			t_sample mul_2683 = (mix_14209 * gen_2681);
			t_sample out1 = mul_2683;
			m_history_126 = history_2678_next_2680;
			m_history_102 = history_12873_next_12875;
			m_history_101 = history_2810_next_2812;
			m_history_100 = history_2666_next_2668;
			m_history_99 = history_2672_next_2674;
			m_history_98 = history_2506_next_2508;
			m_history_97 = history_2816_next_2818;
			m_history_96 = history_2526_next_2528;
			m_history_95 = history_2520_next_2522;
			m_history_94 = history_2514_next_2516;
			m_history_93 = history_2698_next_2700;
			m_history_92 = history_2692_next_2694;
			m_history_91 = history_2686_next_2688;
			m_history_90 = history_2804_next_2806;
			m_history_89 = history_2743_next_2745;
			m_history_88 = history_2536_next_2538;
			m_history_87 = history_2710_next_2712;
			m_history_86 = history_2704_next_2706;
			m_history_85 = history_2771_next_2773;
			m_history_84 = history_2737_next_2739;
			m_history_83 = history_2765_next_2767;
			m_history_82 = history_2467_next_2472;
			m_history_73 = history_2428_next_2438;
			m_history_72 = history_2422_next_2439;
			m_history_71 = history_2418_next_2440;
			m_history_70 = history_2434_next_2441;
			m_history_69 = history_2424_next_2442;
			m_history_68 = history_2430_next_2443;
			m_history_67 = history_2420_next_2444;
			m_history_74 = history_2432_next_2437;
			m_history_81 = history_2463_next_2473;
			m_history_80 = history_2453_next_2474;
			m_history_79 = history_2457_next_2475;
			m_history_78 = history_2469_next_2476;
			m_history_77 = history_2459_next_2477;
			m_history_76 = history_2465_next_2478;
			m_history_75 = history_2455_next_2479;
			m_history_66 = history_3014_next_3016;
			m_history_43 = history_3169_next_3175;
			m_delay_44.write(add_3172);
			m_history_45 = history_3157_next_3163;
			m_delay_46.write(add_3160);
			m_history_47 = history_3145_next_3151;
			m_delay_48.write(add_3148);
			m_history_49 = history_3133_next_3139;
			m_delay_50.write(add_3136);
			m_history_51 = history_3121_next_3127;
			m_delay_52.write(add_3124);
			m_history_53 = history_3109_next_3115;
			m_delay_54.write(add_3112);
			m_history_55 = history_3097_next_3103;
			m_delay_56.write(add_3100);
			m_history_57 = history_3085_next_3091;
			m_delay_58.write(add_3088);
			m_history_65 = history_3044_next_3046;
			m_history_64 = history_3038_next_3040;
			m_history_63 = history_3020_next_3022;
			m_history_62 = history_3008_next_3010;
			m_history_61 = history_3032_next_3034;
			m_history_60 = history_3026_next_3028;
			m_history_59 = history_3050_next_3052;
			m_delay_42.write(gen_3178);
			m_delay_35.write(add_2612);
			m_delay_36.write(gen_2631);
			m_delay_37.write(add_2626);
			m_delay_38.write(gen_2645);
			m_delay_39.write(add_2640);
			m_delay_40.write(gen_2659);
			m_delay_41.write(add_2654);
			m_history_34 = history_2841_next_2843;
			m_history_11 = history_2996_next_3002;
			m_delay_12.write(add_2999);
			m_history_13 = history_2984_next_2990;
			m_delay_14.write(add_2987);
			m_history_15 = history_2972_next_2978;
			m_delay_16.write(add_2975);
			m_history_17 = history_2960_next_2966;
			m_delay_18.write(add_2963);
			m_history_19 = history_2948_next_2954;
			m_delay_20.write(add_2951);
			m_history_21 = history_2936_next_2942;
			m_delay_22.write(add_2939);
			m_history_23 = history_2924_next_2930;
			m_delay_24.write(add_2927);
			m_history_25 = history_2912_next_2918;
			m_delay_26.write(add_2915);
			m_history_33 = history_2847_next_2849;
			m_history_32 = history_2877_next_2879;
			m_history_31 = history_2835_next_2837;
			m_history_30 = history_2871_next_2873;
			m_history_29 = history_2859_next_2861;
			m_history_28 = history_2853_next_2855;
			m_history_27 = history_2865_next_2867;
			m_delay_10.write(gen_3005);
			m_delay_3.write(add_2552);
			m_delay_4.write(gen_2571);
			m_delay_5.write(add_2566);
			m_delay_6.write(gen_2585);
			m_delay_7.write(add_2580);
			m_delay_8.write(gen_2599);
			m_delay_9.write(add_2594);
			m_delay_2.write(mul_6453);
			m_history_1 = history_6455_next_6461;
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
	inline void set_f_st(t_param _value) {
		m_f_st_103 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_c_reflect(t_param _value) {
		m_c_reflect_104 = (_value < 0.001 ? 0.001 : (_value > 0.985 ? 0.985 : _value));
	};
	inline void set_s_thd(t_param _value) {
		m_s_thd_105 = (_value < -50 ? -50 : (_value > 0 ? 0 : _value));
	};
	inline void set_b_drywet(t_param _value) {
		m_b_drywet_106 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_i_peakGain(t_param _value) {
		m_i_peakGain_107 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_p_hiFreq(t_param _value) {
		m_p_hiFreq_108 = (_value < 800 ? 800 : (_value > 15000 ? 15000 : _value));
	};
	inline void set_j_hiGain(t_param _value) {
		m_j_hiGain_109 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_d_damp(t_param _value) {
		m_d_damp_110 = (_value < 0.001 ? 0.001 : (_value > 1 ? 1 : _value));
	};
	inline void set_k_lpf(t_param _value) {
		m_k_lpf_111 = (_value < 100 ? 100 : (_value > 20000 ? 20000 : _value));
	};
	inline void set_v_rel(t_param _value) {
		m_v_rel_112 = (_value < 10 ? 10 : (_value > 500 ? 500 : _value));
	};
	inline void set_e_size(t_param _value) {
		m_e_size_113 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_m_output(t_param _value) {
		m_m_output_114 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_u_atk(t_param _value) {
		m_u_atk_115 = (_value < 10 ? 10 : (_value > 250 ? 250 : _value));
	};
	inline void set_l_hpf(t_param _value) {
		m_l_hpf_116 = (_value < 20 ? 20 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_t_ratio(t_param _value) {
		m_t_ratio_117 = (_value < 1 ? 1 : (_value > 10 ? 10 : _value));
	};
	inline void set_g_freeze(t_param _value) {
		m_g_freeze_118 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_a_input(t_param _value) {
		m_a_input_119 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_h_lowGain(t_param _value) {
		m_h_lowGain_120 = (_value < -30 ? -30 : (_value > 30 ? 30 : _value));
	};
	inline void set_n_lowFreq(t_param _value) {
		m_n_lowFreq_121 = (_value < 20 ? 20 : (_value > 800 ? 800 : _value));
	};
	inline void set_q_onoffEQ(t_param _value) {
		m_q_onoffEQ_122 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_w_makeup(t_param _value) {
		m_w_makeup_123 = (_value < -6 ? -6 : (_value > 6 ? 6 : _value));
	};
	inline void set_o_peakFreq(t_param _value) {
		m_o_peakFreq_124 = (_value < 100 ? 100 : (_value > 2500 ? 2500 : _value));
	};
	inline void set_r_onoffCOMP(t_param _value) {
		m_r_onoffCOMP_125 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void eq3bandas_d_d_d_d_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample lf, t_sample pf, t_sample hf, t_sample lg, t_sample pg, t_sample hg, int bw, t_sample& out1, t_sample& out2) {
		t_sample return_139;
		t_sample return_140;
		lowshelf_d_d_d_d(sigL, sigR, lf, lg, return_139, return_140);
		t_sample x_2722 = return_139;
		sigR = return_140;
		t_sample return_164;
		t_sample return_165;
		peak_d_d_d_d_i(x_2722, sigR, pf, pg, bw, return_164, return_165);
		t_sample x_2725 = return_164;
		sigR = return_165;
		t_sample return_178;
		t_sample return_179;
		hishelf_d_d_d_d(x_2725, sigR, hf, hg, return_178, return_179);
		t_sample x_2727 = return_178;
		sigR = return_179;
		out1 = x_2727;
		out2 = sigR;
		
	};
	inline void lowshelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_134(freq) != ((int)0)) || (__m_change_135(db) != ((int)0)))) {
			m_b_133 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			m_f_132 = safediv(freq, m_b_133);
			m_b_131 = ((m_b_133 * m_b_133) - ((int)1));
			m_w_130 = tan(safediv((m_f_132 * ((t_sample)3.1415926535898)), samplerate));
			m_a_129 = safediv(((int)1), (m_w_130 + ((int)1)));
			m_a_128 = (m_w_130 - ((int)1));
			
		};
		t_sample outputLowShelfL = lowshelfCore_d_d_d_d_d(sigL, m_a_129, m_a_128, m_b_131, m_w_130);
		t_sample outputLowShelfR = lowshelfCore_d_d_d_d_d_137(sigR, m_a_129, m_a_128, m_b_131, m_w_130);
		out1 = outputLowShelfL;
		out2 = outputLowShelfR;
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d(t_sample input, t_sample m_a_129, t_sample m_a_128, t_sample m_b_131, t_sample m_w_130) {
		t_sample x = (m_a_129 * (input - (m_a_128 * m_z_136)));
		t_sample output = (m_w_130 * (x + m_z_136));
		m_z_136 = x;
		return ((output * m_b_131) + input);
		
	};
	inline t_sample lowshelfCore_d_d_d_d_d_137(t_sample input, t_sample m_a_129, t_sample m_a_128, t_sample m_b_131, t_sample m_w_130) {
		t_sample x = (m_a_129 * (input - (m_a_128 * m_z_138)));
		t_sample output = (m_w_130 * (x + m_z_138));
		m_z_138 = x;
		return ((output * m_b_131) + input);
		
	};
	inline void peak_d_d_d_d_i(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, int bw, t_sample& out1, t_sample& out2) {
		if ((((__m_change_151(freq) != ((int)0)) || (__m_change_152(db) != ((int)0))) || (__m_change_153(bw) != ((int)0)))) {
			m_w_150 = tan(safediv((freq * ((t_sample)3.1415926535898)), samplerate));
			m_b_149 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.5)));
			t_sample b = ((m_b_149 * m_b_149) - ((int)1));
			m_d_148 = safepow(((t_sample)1.4142135381699), bw);
			t_sample v_154 = safediv(((m_d_148 * m_d_148) - ((int)1)), (m_d_148 * m_b_149));
			m_d_147 = ((v_154 <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((v_154 >= ((int)100)) ? ((int)100) : v_154));
			m_d_146 = (m_d_147 * b);
			m_wq_145 = (m_d_147 * m_w_150);
			m_w_144 = (m_w_150 * m_w_150);
			m_a_143 = safediv(((int)1), ((((int)1) + m_w_144) + m_wq_145));
			m_a_142 = ((m_w_144 - ((int)1)) * ((int)2));
			m_a_141 = ((((int)1) + m_w_144) - m_wq_145);
			
		};
		t_sample outputPeakL = peakCore_d_d_d_d_d_d(sigL, m_w_150, m_d_146, m_a_143, m_a_142, m_a_141);
		t_sample outputPeakR = peakCore_d_d_d_d_d_d_159(sigR, m_w_150, m_d_146, m_a_143, m_a_142, m_a_141);
		out1 = outputPeakL;
		out2 = outputPeakR;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d(t_sample input, t_sample m_w_150, t_sample m_d_146, t_sample m_a_143, t_sample m_a_142, t_sample m_a_141) {
		t_sample output = ((input - m_z_157) * m_w_150);
		m_z_157 = m_z_158;
		m_z_158 = input;
		t_sample output_2723 = (m_a_143 * ((output - (m_a_142 * m_z_156)) - (m_a_141 * m_z_155)));
		m_z_155 = m_z_156;
		m_z_156 = output_2723;
		t_sample output_2724 = (input + (output_2723 * m_d_146));
		return output_2724;
		
	};
	inline t_sample peakCore_d_d_d_d_d_d_159(t_sample input, t_sample m_w_150, t_sample m_d_146, t_sample m_a_143, t_sample m_a_142, t_sample m_a_141) {
		t_sample output = ((input - m_z_162) * m_w_150);
		m_z_162 = m_z_163;
		m_z_163 = input;
		t_sample output_2723 = (m_a_143 * ((output - (m_a_142 * m_z_161)) - (m_a_141 * m_z_160)));
		m_z_160 = m_z_161;
		m_z_161 = output_2723;
		t_sample output_2724 = (input + (output_2723 * m_d_146));
		return output_2724;
		
	};
	inline void hishelf_d_d_d_d(t_sample sigL, t_sample sigR, t_sample freq, t_sample db, t_sample& out1, t_sample& out2) {
		if (((__m_change_172(freq) != ((int)0)) || (__m_change_173(db) != ((int)0)))) {
			m_b_171 = safepow(((t_sample)1.059253692627), (db * ((t_sample)0.25)));
			t_sample mina_174 = (freq * m_b_171);
			m_f_170 = ((samplerate < mina_174) ? samplerate : mina_174);
			m_b_169 = ((m_b_171 * m_b_171) - ((int)1));
			m_w_168 = tan(safediv((((m_f_170 < ((int)0)) ? ((int)0) : m_f_170) * ((t_sample)3.1415926535898)), samplerate));
			m_a_167 = safediv(((int)1), (m_w_168 + ((int)1)));
			m_a_166 = (m_w_168 - ((int)1));
			
		};
		t_sample outputHighShelfL = hishelfCore_d_d_d_d(sigL, m_a_167, m_a_166, m_b_169);
		t_sample outputHighShelfR = hishelfCore_d_d_d_d_176(sigR, m_a_167, m_a_166, m_b_169);
		out1 = outputHighShelfL;
		out2 = outputHighShelfR;
		
	};
	inline t_sample hishelfCore_d_d_d_d(t_sample input, t_sample m_a_167, t_sample m_a_166, t_sample m_b_169) {
		t_sample x = (m_a_167 * (input - (m_a_166 * m_z_175)));
		t_sample output = (x - m_z_175);
		m_z_175 = x;
		t_sample output_2726 = ((output * m_b_169) + input);
		return output_2726;
		
	};
	inline t_sample hishelfCore_d_d_d_d_176(t_sample input, t_sample m_a_167, t_sample m_a_166, t_sample m_b_169) {
		t_sample x = (m_a_167 * (input - (m_a_166 * m_z_177)));
		t_sample output = (x - m_z_177);
		m_z_177 = x;
		t_sample output_2726 = ((output * m_b_169) + input);
		return output_2726;
		
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
		case 0: *value = self->m_a_input_119; break;
		case 1: *value = self->m_b_drywet_106; break;
		case 2: *value = self->m_c_reflect_104; break;
		case 3: *value = self->m_d_damp_110; break;
		case 4: *value = self->m_e_size_113; break;
		case 5: *value = self->m_f_st_103; break;
		case 6: *value = self->m_g_freeze_118; break;
		case 7: *value = self->m_h_lowGain_120; break;
		case 8: *value = self->m_i_peakGain_107; break;
		case 9: *value = self->m_j_hiGain_109; break;
		case 10: *value = self->m_k_lpf_111; break;
		case 11: *value = self->m_l_hpf_116; break;
		case 12: *value = self->m_m_output_114; break;
		case 13: *value = self->m_n_lowFreq_121; break;
		case 14: *value = self->m_o_peakFreq_124; break;
		case 15: *value = self->m_p_hiFreq_108; break;
		case 16: *value = self->m_q_onoffEQ_122; break;
		case 17: *value = self->m_r_onoffCOMP_125; break;
		case 18: *value = self->m_s_thd_105; break;
		case 19: *value = self->m_t_ratio_117; break;
		case 20: *value = self->m_u_atk_115; break;
		case 21: *value = self->m_v_rel_112; break;
		case 22: *value = self->m_w_makeup_123; break;
		
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
	// initialize parameter 0 ("m_a_input_119")
	pi = self->__commonstate.params + 0;
	pi->name = "a_input";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_a_input_119;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_b_drywet_106")
	pi = self->__commonstate.params + 1;
	pi->name = "b_drywet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_b_drywet_106;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_c_reflect_104")
	pi = self->__commonstate.params + 2;
	pi->name = "c_reflect";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_c_reflect_104;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 0.985;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_d_damp_110")
	pi = self->__commonstate.params + 3;
	pi->name = "d_damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_d_damp_110;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.001;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_e_size_113")
	pi = self->__commonstate.params + 4;
	pi->name = "e_size";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_e_size_113;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_f_st_103")
	pi = self->__commonstate.params + 5;
	pi->name = "f_st";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_f_st_103;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_g_freeze_118")
	pi = self->__commonstate.params + 6;
	pi->name = "g_freeze";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_g_freeze_118;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_h_lowGain_120")
	pi = self->__commonstate.params + 7;
	pi->name = "h_lowGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_h_lowGain_120;
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
	// initialize parameter 9 ("m_j_hiGain_109")
	pi = self->__commonstate.params + 9;
	pi->name = "j_hiGain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_j_hiGain_109;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -30;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_k_lpf_111")
	pi = self->__commonstate.params + 10;
	pi->name = "k_lpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_k_lpf_111;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 20000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_l_hpf_116")
	pi = self->__commonstate.params + 11;
	pi->name = "l_hpf";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_l_hpf_116;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_m_output_114")
	pi = self->__commonstate.params + 12;
	pi->name = "m_output";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_m_output_114;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_n_lowFreq_121")
	pi = self->__commonstate.params + 13;
	pi->name = "n_lowFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_n_lowFreq_121;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 800;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 14 ("m_o_peakFreq_124")
	pi = self->__commonstate.params + 14;
	pi->name = "o_peakFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_o_peakFreq_124;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 100;
	pi->outputmax = 2500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_p_hiFreq_108")
	pi = self->__commonstate.params + 15;
	pi->name = "p_hiFreq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_p_hiFreq_108;
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
	// initialize parameter 17 ("m_r_onoffCOMP_125")
	pi = self->__commonstate.params + 17;
	pi->name = "r_onoffCOMP";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_r_onoffCOMP_125;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 18 ("m_s_thd_105")
	pi = self->__commonstate.params + 18;
	pi->name = "s_thd";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_s_thd_105;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -50;
	pi->outputmax = 0;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 19 ("m_t_ratio_117")
	pi = self->__commonstate.params + 19;
	pi->name = "t_ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_t_ratio_117;
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
	// initialize parameter 21 ("m_v_rel_112")
	pi = self->__commonstate.params + 21;
	pi->name = "v_rel";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_v_rel_112;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 10;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 22 ("m_w_makeup_123")
	pi = self->__commonstate.params + 22;
	pi->name = "w_makeup";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_w_makeup_123;
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
