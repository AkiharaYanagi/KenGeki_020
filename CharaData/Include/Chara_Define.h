﻿//=================================================================================================
//
//	Chara_Define ヘッダファイル
//		Chara共通定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Siv3D.hpp"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//エイリアス
	using P_Tx = std::shared_ptr < s3d::Texture >;
	using AP_Tx = s3d::Array < P_Tx >;
	using PAP_Tx = std::shared_ptr < AP_Tx >;


}	//namespace GAME

