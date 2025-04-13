//=================================================================================================
//
//	Chara_Const ヘッダファイル
//		Chara共通定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//アクション属性
	enum ACTION_CATEGORY
	{
		AC_NEUTRAL, AC_MOVE, AC_JUMP, AC_DASH,

		AC_ATTACK_L, AC_ATTACK_M, AC_ATTACK_H,
		AC_ATTACK_J,
		AC_SKILL, 
		AC_SPECIAL, AC_OVERDRIVE,

		AC_DAMAGED,
		AC_POISED, AC_CLANG, AC_AVOID,
		AC_DOTTY, AC_THROW, AC_GUARD,

		AC_DEMO, AC_OTHER,
		ACTION_CATEGORY_NUM
	};

	//アクション体勢 定義
	enum ACTION_POSTURE
	{
		AP_STAND, AP_CROUCH, AP_JUMP
	};

	//計算状態(CalcState)
	enum CLC_ST
	{
		CLC_MAINTAIN,	//持続
		CLC_SUBSTITUDE,	//代入
		CLC_ADD,		//加算
	};

	//ブランチ条件
	enum BRANCH_CONDITION
	{
		BRC_NO,		//条件無し

		BRC_CMD,	//コマンド成立

		BRC_GRD,	//着地
		BRC_WALL,	//壁接触

//		BRC_COERACION_I,	//自分強制
		BRC_COERACION,	//相手強制

		BRC_DMG_I,	//自分が喰らい
		BRC_HIT_I,	//相手にヒット(自身を変更)
		BRC_HIT_E,	//相手にヒット(相手を変更)

		//打撃がヒット→バランス値参照→０なら成立
		BRC_THR_I,	//投げ成立 (ゲームメイン指定)
		BRC_THR_E,	//投げ成立 (ゲームメイン指定)

		BRC_OFS,	//相殺時
		BRC_END,	//シークエンス終了時
		BRC_DASH,		//ダッシュ相殺

		//他、特殊フラグをゲームメインで設定できる
		BRC_FLG_0, BRC_FLG_1, BRC_FLG_2, BRC_FLG_3, BRC_FLG_4, BRC_FLG_5, BRC_FLG_6, BRC_FLG_7, 
		BRC_FLG_8, BRC_FLG_9, BRC_FLG_10, BRC_FLG_11, BRC_FLG_12, BRC_FLG_13, BRC_FLG_14, BRC_FLG_15,

		//FLG_O : 相殺フラグ


	};

	//他検索用
	enum
	{
		NO_ACTION = 0x7FFF0001,		//検索用フラグ
	};


}	//namespace GAME


