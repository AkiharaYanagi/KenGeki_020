//=================================================================================================
//
// GameConst ファイル
//		ゲーム内共通定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
//	定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	// 定数宣言
	//------------------------------------------

	//キャラ名
	enum CHARA_NAME
	{
//		CHARA_NAME_NUM,
		CHARA_OUKA,
		CHARA_FERALLIA,
		CHARA_SAE,
		CHARA_RETSUDOU,
		CHARA_GABADARUGA,
		CHARA_RANDUM,
		CHARA_NAME_NUM,
	};

	//カラー指定
	enum CHARA_COLOR
	{
		CH_CLR_1,
		CH_CLR_2,
	};

	//開始状態
	enum START_MODE
	{
		START_TITLE,
		START_INTRO,
		START_CHARA_SELE,
		START_BATTLE,
		START_RESULT,
		START_TRAINING,
		TEST_VOID,
	};

	//ステージ名
	enum STAGE_NAME
	{
		STAGE_ASAHINO_HARA,
		STAGE_YUUHINO_HARA,
		STAGE_YORUNO_HARA,
		STAGE_SCHOOL_MORNING,
		STAGE_SCHOOL_NOON,
		STAGE_SCHOOL_NIGHT,
		STAGE_TAISHOU_MORNING,
		STAGE_TAISHOU_NOON,
		STAGE_TAISHOU_NINGT,
	};

}

