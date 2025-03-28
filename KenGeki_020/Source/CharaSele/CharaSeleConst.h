﻿//=================================================================================================
//
//	CharaSele定数 ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "../GameMain/GameConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//キャラ枠位置( 0 ~ 11 )
#if 0
	enum CHARA_SELE_ID
	{
		CHSLID_00, CHSLID_01, CHSLID_02, CHSLID_03, CHSLID_04, CHSLID_05, 
		CHSLID_06, CHSLID_07, CHSLID_08, CHSLID_09, CHSLID_10, CHSLID_11, 
	};
#endif // 0

	using CHARA_SELE_ID = uint32;

	extern const CHARA_SELE_ID		 CHSLID_00;
	extern const CHARA_SELE_ID		 CHSLID_01;
	extern const CHARA_SELE_ID		 CHSLID_02;
	extern const CHARA_SELE_ID		 CHSLID_03;
	extern const CHARA_SELE_ID		 CHSLID_04;
	extern const CHARA_SELE_ID		 CHSLID_05;
	extern const CHARA_SELE_ID		 CHSLID_06;
	extern const CHARA_SELE_ID		 CHSLID_07;
	extern const CHARA_SELE_ID		 CHSLID_08;
	extern const CHARA_SELE_ID		 CHSLID_09;
	extern const CHARA_SELE_ID		 CHSLID_10;
	extern const CHARA_SELE_ID		 CHSLID_11;

	//個数
//	enum CHARA_SELE_ID			 { CHARA_SELE_NUM = 12 }
//	constexpr CHARA_SELE_ID			CHARA_SELE_NUM = 12;


	//表示位置定数
#if 0

	enum CHARA_SELE
	{
		//CHARA_SELE_NUM = 12,

		FACE_X_0 = 362,
		FACE_X_1 = 512,
		FACE_X_2 = 662,
		FACE_Y_0 = 17,
		FACE_Y_1 = 167,
		FACE_Y_2 = 577,
		FACE_Y_3 = 727,

		LOGO_NUM = 12,
		LOGO_W = 128,
		LOGO_L_START_Y = 40,
		LOGO_L_VEL_X = -4,
		LOGO_R_START_Y = 880,
		LOGO_R_VEL_X = 4,

		//カーソル
		SELECT_1P_POS_X = 415 + 75 - 128,	//基準点 + 枠中心 + 画像半分
		SELECT_1P_POS_Y = 70 + 75 - 128,
		SELECT_2P_POS_X = 715 + 75 - 128,	//基準点 + 枠中心 + 画像半分
		SELECT_2P_POS_Y = 70 + 75 - 128,

		//キャラ立ち絵
		CHARA_1P_POS_X = -300,
		CHARA_1P_POS_Y = 100,
		CHARA_2P_POS_X = 500,
		CHARA_2P_POS_Y = 100,

		CUTIN_X = 300,
		CUTIN_VX = 60,

		//キャラ名前
		CHARA_NAME_1P_X = -30 -10,
		CHARA_NAME_1P_Y = 400,
		CHARA_NAME_2P_X = 1280 + 30 - 256 - 10,
		CHARA_NAME_2P_Y = 400,

		POS0_X = 0,
	};

#endif // 0




	//キャラ枠と移動先指定
	struct ChSlct
	{
		CHARA_SELE_ID ID = CHSLID_00;		//キャラID
		CHARA_NAME Name = CHARA_TEST;		//名前
		float x = 0;						//セレクト位置x
		float y = 0;						//セレクト位置y
		CHARA_SELE_ID UP	 = CHSLID_09;	//上移動先
		CHARA_SELE_ID DOWN	 = CHSLID_03;	//下移動先
		CHARA_SELE_ID LEFT	 = CHSLID_02;	//左移動先
		CHARA_SELE_ID RIGHT	 = CHSLID_01;	//右移動先
	};


}	//namespace GAME


