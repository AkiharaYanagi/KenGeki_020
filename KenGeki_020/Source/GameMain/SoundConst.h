//=================================================================================================
//
// SoundConst ファイル
//		BGMファイル指定用 定数
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

	//BGM
	constexpr char32_t BGM_GABA []		= U"00_BGM_GABA.wav";
	constexpr char32_t BGM_SAE []		= U"01_BGM_SAE.wav";
	constexpr char32_t BGM_OUKA []		= U"02_BGM_OUKA.wav";
	constexpr char32_t BGM_RETSU []		= U"03_BGM_RETSU.wav";
	constexpr char32_t BGM_ENEMY0 []	= U"04_BGM_ENEMY0.wav";
	constexpr char32_t BGM_FERA []		= U"05_BGM_FERA.wav";
	constexpr char32_t BGM_Title []		= U"10_BGM_Title.wav";
	constexpr char32_t BGM_CharaSele []	= U"11_BGM_CharaSele.wav";
	constexpr char32_t BGM_Result []	= U"12_BGM_Result.wav";


	//ID
	enum BGM_ID
	{
		BGM_ID_GABA,
		BGM_ID_OUKA,
		BGM_ID_SAE,
		BGM_ID_RETSU,
	};


	//エイリアス
	using BGM_NAME = const char32_t *;

	//BGM_ID_TO_NAME
	extern BGM_NAME		BGM_ID_TO_NAME[];
}

