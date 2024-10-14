//=================================================================================================
//
// SeConst ファイル
//		サウンドエフェクトファイル指定用 定数
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//	定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	// 定数宣言
	//------------------------------------------

#if 0

	enum SE_ID
	{
		SE_Sys_Pdding,
		SE_Sys_Select,
		SE_Sys_Enter,
		SE_Sys_Cancel,
		SE_Sys_Lock,
		SE_Sys_EnterFighting,
		SE_Btl_Hit_L,
		SE_Btl_Hit_M,
		SE_Btl_Hit_H,
		SE_Btl_Jump,
		SE_Btl_Landing,
		SE_Btl_Dash,
		SE_Btl_Air,
		SE_Btl_break,
		SE_Btl_Light,
		SE_Btl_Clang,
		SE_Btl_Extract_sword,
	};

#endif // 0


	//SE
	constexpr char32_t SE_select_move []		= U"SE_01_選択_移動.wav";
	constexpr char32_t SE_select_decide []		= U"SE_02_選択_決定.wav";
	constexpr char32_t SE_select_Cancel []		= U"SE_03_選択_否定.wav";
	constexpr char32_t SE_select_Lock []		= U"SE_04_選択_不可.wav";
	constexpr char32_t SE_Sys_Enter []			= U"SE_05_キーン.wav";

	constexpr char32_t SE_Btl_Light []			= U"SE_14_キラーン.wav";
	constexpr char32_t SE_Btl_Clang []			= U"SE_15_打ち合い.wav";

}

