//=================================================================================================
//
// FtgConst ファイル
//		Ftgメイン共通定義
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

	//演出時間
	enum DEMO_TIME
	{
		WIN_WAIT = 360,
		WIN_POSE_WAIT = 180,
	};

	//勝者
	enum WINNER
	{
		WINNER_DRAW,
		WINNER_1P,
		WINNER_2P,
		WINNER_DP,
	};

	//入力
	enum COMMAND
	{
		NO_COMPLETE = 0xFFFFFFFF
	};

	//キャラ定数
	enum CONST_CHARA
	{
		NUM_RECT = 8,	//判定枠配列の保持サイズ
//		NUM_RECT = 2,	//判定枠配列の保持サイズ
	};

	//枠表示(色)
	enum RECT_COLOR
	{
		RECT_COLOR_C = 0x400000ff,
		RECT_COLOR_A = 0x40ff0000,
		RECT_COLOR_H = 0x4000ff00,
		RECT_COLOR_O = 0x40ffff00,
	};

	//割合
	enum PERCENTAGE
	{
		CENT = 100,
	};

	//CPU_INPUT
	enum CPU_INPUT
	{
		CPU_INPUT_GAMEKEY_NUM = 60,
	};

	//打合結果 (左右)
	enum CLANG_DECISION_LR
	{
		CD_EQUAL,
		CD_LEFT,
		CD_RIGHT,
		CD_OFF,
	};

	//打合結果 (勝負)
	enum CLANG_DECISION_WL
	{
		CD_DRAW,
		CD_WIN,
		CD_LOSE,
	};

	//画面描画用 初期位置
	enum PLAYER_BASE_PT
	{
		GAME_WIDTH = 2048,		//ゲーム上で扱う幅
		GAME_HEIGHT = 1024,

		GAME_WIDTH_HALF = GAME_WIDTH / 2,		//ゲーム上で扱う幅

//		GROUND_Y = 750,			//地面高さ
		GROUND_Y = 800,			//地面高さ
		PLAYER_BASE_Y = GROUND_Y,

		//開始立ち位置(中心から換算)
		PLAYER_1_BASE_X = GAME_WIDTH / 2 - GAME_WINDOW_WIDTH / 2 + 200,
		PLAYER_1_BASE_Y = PLAYER_BASE_Y,
		PLAYER_2_BASE_X = GAME_WIDTH / 2 + GAME_WINDOW_WIDTH / 2 - 200,
		PLAYER_2_BASE_Y = PLAYER_BASE_Y,

		GRP_PLAYER1_X = 0,
		GRP_PLAYER1_Y = 14,
		GRP_PLAYER2_X = GAME_WINDOW_WIDTH - 64 - 0,
		GRP_PLAYER2_Y = 14,
	};

	//バトル関連定数
	enum BATTLE_CONST
	{
		//フィールドサイズ
		FIELD_BASE_X = 0,
		FIELD_WIDTH = 2048,
		FIELD_EDGE = 64,		//画面端の補正

		//ゲージ共通
		GAUGE_MAX = 10000,
		GAUGE_W = 500,

		//ゲージ類
		LIFE_MAX = 10000,
		LIFE_START = 10000,

		BALANCE_MAX = 10000,
		BALANCE_START = 5000,

		MANA_MAX = 10000,
		MANA_START = MANA_MAX,
		MANA_HALF = MANA_MAX / 2,

		ACCEL_MAX = 1000,
		ACCEL_START = -0,
		ACCEL_MIN = -500,

		//停止
//		HITSTOP_TIME = 15,
		HITSTOP_TIME = 7,
//		HITSTOP_TIME = 700,
		DOWN_TIME = 120 + 60,
		END_TIME = 60,
	};
}

