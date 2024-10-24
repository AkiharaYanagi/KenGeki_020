﻿//=================================================================================================
//
//	Effect ヘッダファイル
//		スクリプトの一連
//
//
//		◆◆◆　ver 020 でアクションと統合
//
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Action.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Effect : public Action 
	{
		//エフェクト属性

	public:
		Effect ();
		Effect ( const Effect & rhs ) = delete;
		~Effect ();
	};

	using P_Effect = std::shared_ptr < Effect >;
	using VP_Effect = std::vector < P_Effect >;
	using PVP_Effect = std::shared_ptr < VP_Effect >;

	using AP_Effect = s3d::Array < P_Effect >;
	using PAP_Effect = std::shared_ptr < AP_Effect >;


}	//namespace GAME


