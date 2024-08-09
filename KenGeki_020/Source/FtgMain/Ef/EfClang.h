﻿//=================================================================================================
//
//	EfClang ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/FtgConst.h"
#include "../G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
//	class EfClang : public GrpEf
	class EfClang : public GameGraphic
	{
	public:
		EfClang ();
		EfClang ( const EfClang & rhs ) = delete;
		~EfClang ();

		void Move ();

		void On ( VEC2 center );
	};

	using P_EfClang = std::shared_ptr < EfClang >;


}	//namespace GAME

