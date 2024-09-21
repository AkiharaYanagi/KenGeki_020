﻿//=================================================================================================
//
//	PauseMenu_Const
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "PauseMenu_Const.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//--------------------------------------
	//メニュ 描画Z位置(後:1.f ～ 0.0f:前)

	//@info 大きい方が奥
	const float Z_MENU_BG		= Z_MENU - 0.01f;
	const float Z_MENU_STR		= Z_MENU - 0.02f;
	const float Z_MENU_YN_BG	= Z_MENU - 0.03f;
	const float Z_MENU_YN_STR	= Z_MENU - 0.04f;
	const float Z_MENU_KI_BG	= Z_MENU - 0.05f;
	const float Z_MENU_KI_STR	= Z_MENU - 0.06f;
	//@info 小さい方が手前

	//--------------------------------------

}	//namespace GAME
