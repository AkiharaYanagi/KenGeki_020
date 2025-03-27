//=================================================================================================
//
//	CharaSele定数 ソースファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSeleConst.h"
#include "CharaSele.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{


	//---------------------------------------------------------
	//カーソル
	//表示位置定数
#if 0
	const float	CharaSele_Player::FACE_X_0 = 362;
	const float	CharaSele_Player::FACE_X_1 = 512;
	const float	CharaSele_Player::FACE_X_2 = 662;
	const float	CharaSele_Player::FACE_Y_0 =  17;
	const float	CharaSele_Player::FACE_Y_1 = 167;
	const float	CharaSele_Player::FACE_Y_2 = 577;
	const float	CharaSele_Player::FACE_Y_3 = 727;
#endif // 0
	const float	CharaSele_Player::FACE_X_0 = 410 - 2;
	const float	CharaSele_Player::FACE_X_1 = FACE_X_0 + 150;
	const float	CharaSele_Player::FACE_X_2 = FACE_X_1 + 150;
	const float	CharaSele_Player::FACE_Y_0 =  70 - 2;
	const float	CharaSele_Player::FACE_Y_1 = FACE_Y_0 + 150;
	const float	CharaSele_Player::FACE_Y_2 = FACE_Y_0 + 560;
	const float	CharaSele_Player::FACE_Y_3 = FACE_Y_2 + 150;

	const float	CharaSele_Player::LOGO_NUM = 12;
	const float	CharaSele_Player::LOGO_W = 128;
	const float	CharaSele_Player::LOGO_L_START_Y = 40;
	const float	CharaSele_Player::LOGO_L_VEL_X = -4;
	const float	CharaSele_Player::LOGO_R_START_Y = 880;
	const float	CharaSele_Player::LOGO_R_VEL_X = 4;

	//カーソル
#if 0
	const float	CharaSele_Player::SELECT_1P_POS_X = 415 + 75 - 128;	//基準点 + 枠中心 + 画像半分
	const float	CharaSele_Player::SELECT_1P_POS_Y = 70 + 75 - 128;
	const float	CharaSele_Player::SELECT_2P_POS_X = 715 + 75 - 128;	//基準点 + 枠中心 + 画像半分
	const float	CharaSele_Player::SELECT_2P_POS_Y = 70 + 75 - 128;
#endif // 0

	//キャラ立ち絵
	const float	CharaSele_Player::CHARA_1P_POS_X = -300;
	const float	CharaSele_Player::CHARA_1P_POS_Y = 50;
	const float	CharaSele_Player::CHARA_2P_POS_X = 500;
	const float	CharaSele_Player::CHARA_2P_POS_Y = 50;

	const float	CharaSele_Player::CUTIN_X = 300;
	const float	CharaSele_Player::CUTIN_VX = 60;

	//キャラ名前
	const float	CharaSele_Player::CHARA_NAME_1P_X = -30 -10;
	const float	CharaSele_Player::CHARA_NAME_1P_Y = 400;
	const float	CharaSele_Player::CHARA_NAME_2P_X = 1280 + 30 - 256 - 10;
	const float	CharaSele_Player::CHARA_NAME_2P_Y = 400;

	const float	CharaSele_Player::POS0_X = 0;


	//---------------------------------------------------------
	//枠位置定数
	//	キャラID, 名前, セレクト位置x, セレクト位置y, 上移動先, 下移動先, 左移動先, 右移動先

	const ChSlct CharaSele_Player::m_pos [ CHARA_SELE_NUM ] = 
	{
{ CHSLID_00, CHARA_OUKA,		FACE_X_0, FACE_Y_0, CHSLID_03, CHSLID_03, CHSLID_02, CHSLID_02 }, 
{ CHSLID_01, CHARA_TEST,		FACE_X_1, FACE_Y_0, CHSLID_10, CHSLID_04, CHSLID_00, CHSLID_02 }, 
{ CHSLID_02, CHARA_SAE ,		FACE_X_2, FACE_Y_0, CHSLID_03, CHSLID_03, CHSLID_00, CHSLID_00 }, 
{ CHSLID_03, CHARA_RETSUDOU,	FACE_X_0, FACE_Y_1, CHSLID_00, CHSLID_00, CHSLID_02, CHSLID_02 }, 
{ CHSLID_04, CHARA_TEST,		FACE_X_1, FACE_Y_1, CHSLID_01, CHSLID_07, CHSLID_03, CHSLID_05 }, 
{ CHSLID_05, CHARA_TEST,		FACE_X_2, FACE_Y_1, CHSLID_02, CHSLID_02, CHSLID_05, CHSLID_05 },  
{ CHSLID_06, CHARA_TEST,		FACE_X_0, FACE_Y_2, CHSLID_03, CHSLID_09, CHSLID_08, CHSLID_07 }, 
{ CHSLID_07, CHARA_TEST,		FACE_X_1, FACE_Y_2, CHSLID_04, CHSLID_10, CHSLID_06, CHSLID_08 }, 
{ CHSLID_08, CHARA_TEST,		FACE_X_2, FACE_Y_2, CHSLID_05, CHSLID_11, CHSLID_07, CHSLID_06 }, 
{ CHSLID_09, CHARA_TEST,		FACE_X_0, FACE_Y_3, CHSLID_06, CHSLID_00, CHSLID_11, CHSLID_10 }, 
{ CHSLID_10, CHARA_TEST,		FACE_X_1, FACE_Y_3, CHSLID_07, CHSLID_01, CHSLID_09, CHSLID_11 }, 
{ CHSLID_11, CHARA_TEST,		FACE_X_2, FACE_Y_3, CHSLID_08, CHSLID_02, CHSLID_10, CHSLID_09 }, 
	};



}	//namespace GAME


